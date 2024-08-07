#include <cmath>
#include <utility>
#include <algorithm>
#include "RayCaster.h"

Pixel::Coordinate RayCaster::getGridCoordinate(double x, double y) {
    return Pixel::Coordinate{static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y))};
}

void RayCaster::computeVisibilityForPixel(int x, int y) {
    // Compute the center of the pixel that the rays are going to be cast from
    std::pair<double, double> center = getMiddle(x, y);

    // Cast a ray from the pixel to each edge pixel and add the corresponding pixels to the visibility field of the pixels.
    for(auto edgePixel : edges){
        // Cast ray
        std::vector<Pixel::Coordinate> rayPixels = castRay(center.first, center.second,  edgePixel.first, edgePixel.second);

        // Go through ray and add visible pixels until an obstacle is hit.
        std::vector<Pixel::Coordinate> visiblePixels{};
        for(int j = 1; j < rayPixels.size(); j++){
            // Get current pixel
            Pixel::Coordinate rayPixel = rayPixels[j];

            // Check if a pixel should be added, ending loop if an object has been hit
            if(image->getPixelType(rayPixel) == Pixel::EMPTY_SPACE){
                visiblePixels.push_back(rayPixel);
            }
            else{
                break;
            }
        }
        // Add the information about visible pixels to the pixel
        image->addVisiblePixels(x, y, visiblePixels);
    }

}

RayCaster::RayCaster(const std::shared_ptr<Image>& image, int rayNum): image{image} {
    initializeEdges(image->getWidth(), image->getHeight());
    numRays = rayNum;
}

std::pair<double, double> RayCaster::getMiddle(int x, int y) {
    return std::pair<double, double>{x + 0.5, y + 0.5};
}

void RayCaster::computeVisibility() {
    std::vector<Pixel::Coordinate> surface = image->getSurfacePixels();
    for(auto surfacePixel : surface){
        computeVisibilityForPixel(surfacePixel.x, surfacePixel.y);
    }
}

void RayCaster::initializeEdges(int width, int height) {
    // Reserve space for edges
    edges.reserve(height * 2 + (width - 2) * 2);

    // Left edge
    for(int y = 0; y < height; y++){
        edges.emplace_back(getMiddle(0, y).first, getMiddle(0, y).second);
    }

    // Right edge
    for(int y = 0; y < height; y++){
        edges.emplace_back(getMiddle(width - 1, y).first, getMiddle(width - 1, y).second);
    }

    // Upper edge
    for(int x = 1; x < width - 1; x++){
        edges.emplace_back(getMiddle(x, height - 1).first, getMiddle(x, height - 1).second);
    }

    // Lower edge
    for(int x = 1; x < width - 1; x++){
        edges.emplace_back(getMiddle(x, 0).first, getMiddle(x, 0).second);
    }
}

void RayCaster::setImage(std::shared_ptr<Image> imageInput) {
    image = std::move(imageInput);
    initializeEdges(image->getWidth(), image->getHeight());
}

std::vector<Pixel::Coordinate> RayCaster::castRay(double xStart, double yStart, double xEnd, double yEnd) {
    // DDA
    // Calculate the normalized direction vector of the ray
    double rayDirX = xEnd - xStart;
    double rayDirY = yEnd - yStart;
    double d = sqrt(pow(rayDirX, 2) + pow(rayDirY, 2));
    rayDirX = rayDirX / d;
    rayDirY = rayDirY / d;

    // Calculate the unit step size vector (How much along the ray do I need to go to march length one along the x or y-axis).
    double unitStepSizeX = sqrt(1 + pow(rayDirY / rayDirX, 2));
    double unitStepSizeY = sqrt(1 + pow(rayDirX / rayDirY, 2));

    // Get starting pixel
    Pixel::Coordinate currentGridCoordinate = getGridCoordinate(xStart, yStart);

    // Length of the ray that goes towards the next intersection in the x or y direction
    double currentRayLengthX;
    double currentRayLengthY;

    // General direction of the ray (up / down / left / right)
    int stepX = rayDirX < 0 ? -1 : 1;
    int stepY = rayDirY < 0 ? -1 : 1;

    // Find the intersection from the starting point to the edge of the current cell
    // Ray goes from right to left
    if(stepX < 0){
        currentRayLengthX = (xStart - currentGridCoordinate.x ) * unitStepSizeX;
    }
        // Ray goes from left to right
    else{
        currentRayLengthX = (currentGridCoordinate.x + 1 - xStart) * unitStepSizeX;
    }
    // Ray goes upwards
    if(stepY < 0){
        currentRayLengthY = (yStart - currentGridCoordinate.y) * unitStepSizeY;
    }
        // Ray goes downwards
    else{
        currentRayLengthY = (currentGridCoordinate.y + 1 - yStart) * unitStepSizeY;
    }

    bool obstacleHit = false;
    std::vector<Pixel::Coordinate> intersectedPixels{};
    while(currentGridCoordinate != getGridCoordinate(xEnd, yEnd)){
        // Add the current pixel
        intersectedPixels.push_back(currentGridCoordinate);

        // Determine if we should walk in the x or y direction and update the current pixel
        if(currentRayLengthX < currentRayLengthY){
            currentGridCoordinate.x += stepX;
            currentRayLengthX += unitStepSizeX;
        }
        else{
            currentGridCoordinate.y += stepY;
            currentRayLengthY += unitStepSizeY;
        }
    }

    intersectedPixels.push_back(getGridCoordinate(xEnd, yEnd));

    return intersectedPixels;
}

void RayCaster::setCameraView(Camera& camera) {
    // Compute the center of the pixel that the rays are going to be cast from
    std::pair<double, double> center = getMiddle(camera.getPosition().x, camera.getPosition().y);

    std::vector<std::pair<double, double>> dirs = generateDirections(camera, numRays);
    for(auto direction : dirs){
        // Cast ray
        Pixel::Coordinate hitPixel = castRayDir(center.first, center.second, direction.first, direction.second);
        if(hitPixel != Pixel::Coordinate{-1, -1}){
            camera.addVisibleSurfacePixels({hitPixel});
        }
    }
}

bool RayCaster::isInView(Camera camera, int x, int y) {
    // Create vector from the camera to the edge pixel (x,y)
    std::pair<double, double> cameraMiddle = getMiddle(camera.getPosition().x, camera.getPosition().y);
    std::pair<double, double> edgePixelMiddle = getMiddle(x, y);
    std::pair<double, double> edgeVector{edgePixelMiddle.first - cameraMiddle.first, edgePixelMiddle.second - cameraMiddle.second};

    // Calculate cos of the angle between the camera direction vector and the vector from the camera to (x,y)
    double cosAngle = dotProduct(edgeVector.first, edgeVector.second, camera.getDirection().first, camera.getDirection().second) /
            (magnitude(edgeVector.first, edgeVector.second) * magnitude(camera.getDirection().first, camera.getDirection().second));

    // Get the actual angle in degrees
    double angle = acos(cosAngle) * (180 / M_PI);

    // Check that the vector is within the visible angle of the camera
    return fabs(angle) <= camera.getOpeningAngle() / 2;
}

Pixel::Coordinate RayCaster::castRayDir(double xStart, double yStart, double xDir, double yDir) {
    // DDA
    double d = sqrt(pow(xDir, 2) + pow(yDir, 2));
    xDir = xDir / d;
    yDir = yDir / d;

    // Calculate the unit step size vector (How much along the ray do I need to go to march length one along the x or y-axis).
    double unitStepSizeX = sqrt(1 + pow(yDir / xDir, 2));
    double unitStepSizeY = sqrt(1 + pow(xDir / yDir, 2));

    // Get starting pixel
    Pixel::Coordinate currentGridCoordinate = getGridCoordinate(xStart, yStart);

    // Length of the ray that goes towards the next intersection in the x or y direction
    double currentRayLengthX;
    double currentRayLengthY;

    // General direction of the ray (up / down / left / right)
    int stepX = xDir < 0 ? -1 : 1;
    int stepY = yDir < 0 ? -1 : 1;

    // Find the intersection from the starting point to the edge of the current cell
    // Ray goes from right to left
    if(stepX < 0){
        currentRayLengthX = (xStart - currentGridCoordinate.x ) * unitStepSizeX;
    }
        // Ray goes from left to right
    else{
        currentRayLengthX = (currentGridCoordinate.x + 1 - xStart) * unitStepSizeX;
    }
    // Ray goes upwards
    if(stepY < 0){
        currentRayLengthY = (yStart - currentGridCoordinate.y) * unitStepSizeY;
    }
        // Ray goes downwards
    else{
        currentRayLengthY = (currentGridCoordinate.y + 1 - yStart) * unitStepSizeY;
    }

    bool obstacleHit = false;
    while(image->isWithin(currentGridCoordinate)){
        if(image->getPixelType(currentGridCoordinate) == Pixel::SURFACE){
            return currentGridCoordinate;
        }

        // Determine if we should walk in the x or y direction and update the current pixel
        if(currentRayLengthX < currentRayLengthY){
            currentGridCoordinate.x += stepX;
            currentRayLengthX += unitStepSizeX;
        }
        else{
            currentGridCoordinate.y += stepY;
            currentRayLengthY += unitStepSizeY;
        }
    }

    return {-1, -1};
}

std::vector<std::pair<double, double>> RayCaster::generateDirections(Camera cam, int numDirs) {

    std::pair<double, double> currentVector = rotateVector(cam.getDirection(), -cam.getOpeningAngle() / 2);
    double division = cam.getOpeningAngle() < 360 ? numDirs - 1 : numDirs;
    std::vector<std::pair<double, double>> result{};
    for(int i = 0; i < numDirs; i++){
        result.push_back(currentVector);
        currentVector = rotateVector(currentVector, cam.getOpeningAngle() / division);
    }
    return result;
}

std::pair<double, double> RayCaster::rotateVector(std::pair<double, double> vector, double rotationAngle) {
    // Convert to radians
    double angleRadians = rotationAngle * (M_PI / 180);

    // Calculate result
    double x = vector.first * cos(angleRadians) + vector.second * sin(angleRadians);
    double y = -vector.first * sin(angleRadians) + vector.second * cos(angleRadians);

    std::pair<double, double> result{x, y};
    return result;
}

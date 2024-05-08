#include <cmath>
#include <utility>
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

RayCaster::RayCaster(std::shared_ptr<Image> image): image{std::move(image)} {
    initializeEdges(image->getWidth(), image->getHeight());
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

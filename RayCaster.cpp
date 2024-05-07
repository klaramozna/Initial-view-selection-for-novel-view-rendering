#include <cmath>
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
    // Reserve space for edges
    edges.reserve(image->getHeight() * 2 + (image->getWidth() - 2) * 2);

    // Left edge
    for(int y = 0; y < image->getHeight(); y++){
        edges.emplace_back(getMiddle(0, y).first, getMiddle(0, y).second);
    }

    // Right edge
    for(int y = 0; y < image->getHeight(); y++){
        edges.emplace_back(getMiddle(image->getWidth() - 1, y).first, getMiddle(image->getWidth() - 1, y).second);
    }

    // Upper edge
    for(int x = 1; x < image->getWidth() - 1; x++){
        edges.emplace_back(getMiddle(x, image->getHeight() - 1).first, getMiddle(x, image->getHeight() - 1).second);
    }

    // Lower edge
    for(int x = 1; x < image->getWidth() - 1; x++){
        edges.emplace_back(getMiddle(x, 0).first, getMiddle(x, 0).second);
    }
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

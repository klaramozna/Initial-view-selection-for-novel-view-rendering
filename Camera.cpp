#include "Camera.h"

void Camera::addVisibleSurfacePixels(std::vector<Pixel::Coordinate> visiblePixels) {
    for(auto pixel : visiblePixels){
        visibleSurfacePixels.insert(pixel);
    }
}

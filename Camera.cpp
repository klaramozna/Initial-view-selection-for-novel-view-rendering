#include "Camera.h"
#include <cmath>

void Camera::addVisibleSurfacePixels(std::vector<Pixel::Coordinate> visiblePixels) {
    for(auto pixel : visiblePixels){
        visibleSurfacePixels.insert(pixel);
    }
}

bool Camera::operator==(const Camera &other) const {
    return position == other.position &&
           fabs(direction.first - other.getDirection().first) < 1e-9 &&
            fabs(direction.second - other.getDirection().second) < 1e-9 &&
           openingAngle == other.openingAngle;
}

bool Camera::operator<(const Camera &other) const {
    return position < other.position;
}

bool Camera::operator!=(const Camera &other) const {
    return !(other == *this);
}

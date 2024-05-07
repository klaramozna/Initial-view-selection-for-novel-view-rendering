#include <cmath>
#include "RayCaster.h"

Pixel::Coordinate RayCaster::getGridCoordinate(double x, double y) {
    return Pixel::Coordinate{static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y))};
}

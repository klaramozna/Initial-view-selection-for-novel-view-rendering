#include "SimpleRayCast.h"
#include <cmath>

std::vector<Pixel::Coordinate> SimpleRayCast::castRay(double xStart, double yStart, double xEnd, double yEnd) {
    // Any step size between 1 and 1.41 (diagonal of a 1x1 square) is suitable
    double stepSize = 1.3;

    // Slope of the ray
    double m = (yEnd - yStart) / (xEnd - xStart);

    // Intersection of the ray with the y-axis
    double b = yStart - m * xStart;

    // Figure out the direction of the ray (downwards / upwards, left / right)
    int xDirection = xStart <= xEnd ? 1 : -1;
    int yDirection = yStart <= yEnd ? 1 : -1;

    // Initialize current position
    double currentX = xStart;
    double currentY = yStart;
    Pixel::Coordinate currentGridCoordinate = getGridCoordinate(currentX, currentY);
    std::vector<Pixel::Coordinate> intersectedPixels{};

    while(currentX * xDirection <= xEnd * xDirection && currentY * yDirection <= yEnd * yDirection){
        // Add the current pixel and make sure nothing is added multiple times.
        if(!intersectedPixels.empty() && intersectedPixels[intersectedPixels.size() - 1] != currentGridCoordinate){
            intersectedPixels.push_back(currentGridCoordinate);
        }

        // Get the next point along the line
        std::pair<double, double> nextPoint = getNextPoint(xStart, yStart, xEnd, yEnd, stepSize);
        currentX = nextPoint.first;
        currentY = nextPoint.second;
        currentGridCoordinate = getGridCoordinate(currentX, currentY);
    }

    // Add the last point if it has not been added yet.
    currentGridCoordinate = getGridCoordinate(xEnd, yEnd);
    if(!intersectedPixels.empty() && intersectedPixels[intersectedPixels.size() - 1] != currentGridCoordinate){
        intersectedPixels.push_back(currentGridCoordinate);
    }

    return intersectedPixels;
}

std::pair<double, double>
SimpleRayCast::getNextPoint(double xStart, double yStart, double xEnd, double yEnd, double stepSize) {
    // Calculating the distance between the start end point.
    double d = sqrt(pow((xEnd - xStart), 2) + pow((yEnd - yStart), 2));

    // Calculating the ratio of distances.
    double t = stepSize / d;

    return std::pair<double, double>{(1 - t) * xStart + t * xEnd, (1 - t) * yStart + t * yEnd};
}

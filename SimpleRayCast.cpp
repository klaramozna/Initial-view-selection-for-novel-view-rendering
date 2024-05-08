#include "SimpleRayCast.h"
#include <cmath>

std::vector<Pixel::Coordinate> SimpleRayCast::castRay(double xStart, double yStart, double xEnd, double yEnd) {
    // The smaller, the higher the accuracy
    double stepSize = 0.1;

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
        if(intersectedPixels.empty() || (!intersectedPixels.empty() && intersectedPixels[intersectedPixels.size() - 1] != currentGridCoordinate)){
            intersectedPixels.push_back(currentGridCoordinate);
        }

        // Get the next point along the line
        std::pair<double, double> nextPoint = getNextPoint(currentX, currentY, xEnd, yEnd, stepSize);
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
    // Calculate the direction vector of the ray
    double resultX = xEnd - xStart;
    double resultY = yEnd - yStart;

    // Normalize the direction vector
    double d = sqrt(pow(resultX, 2) + pow(resultY, 2));
    resultX = resultX / d;
    resultY = resultY / d;

    // Scale the direction vector, such as it has length stepSize
    resultX = stepSize * resultX;
    resultY = stepSize * resultY;

    // Calculate final point
    resultX = resultX + xStart;
    resultY = resultY + yStart;

    return std::pair<double, double>{resultX, resultY};
}

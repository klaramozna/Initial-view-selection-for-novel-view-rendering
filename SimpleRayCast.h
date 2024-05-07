#ifndef SIMPLERAYCAST_H
#define SIMPLERAYCAST_H

#include "RayCaster.h"

/**
 * @brief Uses a fixed step size to find pixels on the ray.
 */
class SimpleRayCast : public RayCaster {
private:
    /**
     * @brief Computes which pixels the line between (xStart, yStart) and (xEnd, yEmd) crosses. It is assumed that the given coordinates are within the image. The pixels are found through choosing a step size smaller than the diagonal of a pixel and then looking in which pixel each point is.
     * @param xStart X coordinate of the starting point of the line.
     * @param yStart Y coordinate of the starting point of the line.
     * @param xEnd X coordinate of the ending point of the line.
     * @param yEnd Y coordinate of the ending point of the line.
     * @return Vector of the coordinates of pixels that the line crosses.
     */
    std::vector<Pixel::Coordinate> castRay(double xStart, double yStart, double xEnd, double yEnd) override;

    /**
     * @brief Given two points, forming a line, another point in between them is returned, such that the distance from the starting point is stepSize.
     * @param xStart X coordinate of the starting point.
     * @param yStart Y coordinate of the starting point.
     * @param xEnd X coordinate of the end point (determines the direction).
     * @param yEnd Y Coordinate of the end point (determines the direction).
     * @param stepSize Distance from the starting point to the point that is returned.
     * @return The coordinates of the calculated point.
     */
    static std::pair<double, double> getNextPoint(double xStart, double yStart, double xEnd, double yEnd, double stepSize);
};


#endif //SIMPLERAYCAST_H

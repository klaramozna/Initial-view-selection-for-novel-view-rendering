#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <memory>
#include <utility>
#include "Image.h"

/**
 * @brief Responsible for computing the the visible area for each pixel.
 */
class RayCaster {
public:

    /**
     * @brief Creates a RayCaster object with the given image.
     * @param image The image for which the visibility cones will be computed.
     */
    explicit RayCaster(std::shared_ptr<Image> image);

    /**
     * @brief For each pixel, all pixels that "see" it are stored.
     */
    void computeVisibility();

private:

    /**
     * @brief Image to be modified.
     */
    std::shared_ptr<Image> image;

    /**
     * @brief Stores the center points of all edge pixels of the image.
     */
    std::vector<std::pair<double, double>> edges;

    /**
     * @brief Computes the pixels from which the pixel at location x,y can be "seen".
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    void computeVisibilityForPixel(int x, int y);

    /**
     * @brief Returns the center point of the pixel with the given coordinates.
     * @param x X coordinate of the pixel.
     * @param y Y coordinate of the pixel.
     * @return Center point of the pixel.
     */
    static std::pair<double, double> getMiddle(int x, int y);

protected:

    /**
     * @brief Computes which pixels the line between (xStart, yStart) and (xEnd, yEmd) crosses. It is assumed that the given coordinates are within the image.
     * @param xStart X coordinate of the starting point of the line.
     * @param yStart Y coordinate of the starting point of the line.
     * @param xEnd X coordinate of the ending point of the line.
     * @param yEnd Y coordinate of the ending point of the line.
     * @return Vector of the coordinates of pixels that the line crosses.
     */
    virtual std::vector<Pixel::Coordinate> castRay(double xStart, double yStart, double xEnd, double yEnd) = 0;

    /**
     * @brief Returns the (integer) coordinates of the pixel in which the given coordinates lie.
     * @param x X coordinate to be converted.
     * @param y Y coordinate to be converted.
     * @return The integer coordinate of the corresponding pixel ((0,0) is in the lower-left corner of the image).
     */
    static Pixel::Coordinate getGridCoordinate(double x, double y);
};


#endif //RAYCASTER_H

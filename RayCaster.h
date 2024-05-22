#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <memory>
#include <utility>
#include "Image.h"
#include "Camera.h"

/**
 * @brief Responsible for computing the the visible area for each pixel.
 */
class RayCaster {
public:

    RayCaster() = default;

    /**
     * @brief Creates a RayCaster object with the given image.
     * @param image The image for which the visibility cones will be computed.
     */
    explicit RayCaster(std::shared_ptr<Image> image);

    /**
     * @brief For each pixel, all pixels that "see" it are stored.
     */
    void computeVisibility();

    /**
     * @brief Sets the image to the given image
     * @param imageInput The image to be set.
     */
    void setImage(std::shared_ptr<Image> imageInput);

    /**
     * @brief Computes the surface pixels that the camera sees.
     * @param camera The camera that the results get stored to.
     */
    void setCameraView(Camera& camera);

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

    /**
     * @brief Store the coordinates of the edges of the image.
     * @param width Width of the image in pixels.
     * @param height Height of the image in pixels.
     */
    void initializeEdges(int width, int height);

    /**
     * @brief Returns true if the ray cast from the camera to the given pixel coordinates lies within the cameras view.
     * @param camera The camera.
     * @param x X coordinate of the pixel.
     * @param y Y coordinate of the pixel.
     * @return True if the ray cast from the camera to the given pixel coordinates lies within the cameras view.
     */
    static bool isInView(Camera camera, int x, int y);

    //TODO: manage this
    std::pair<double, double> normalize(double x, double y) {
        double magnitude = sqrt(x * x + y * y);
        x /= magnitude;
        y /= magnitude;
    }

    double dotProduct(double x1, double y1, double x2, double y2) {
        return x1 * x2 + y1 * y2;
    }

    double crossProduct(double x1, double y1, double x2, double y2) {
        return x1 * y2 - y1 * x2;
    }

    static double normalizeAngle(double angle){
        while (angle < 0.0) {
            angle += 360.0;
        }
        while (angle >= 360.0) {
            angle -= 360.0;
        }
        return angle;
    }

protected:

    /**
     * @brief Computes which pixels the line between (xStart, yStart) and (xEnd, yEmd) crosses. It is assumed that the given coordinates are within the image.
     * @param xStart X coordinate of the starting point of the line.
     * @param yStart Y coordinate of the starting point of the line.
     * @param xEnd X coordinate of the ending point of the line.
     * @param yEnd Y coordinate of the ending point of the line.
     * @return Vector of the coordinates of pixels that the line crosses.
     */
    static std::vector<Pixel::Coordinate> castRay(double xStart, double yStart, double xEnd, double yEnd);

    /**
     * @brief Returns the (integer) coordinates of the pixel in which the given coordinates lie.
     * @param x X coordinate to be converted.
     * @param y Y coordinate to be converted.
     * @return The integer coordinate of the corresponding pixel ((0,0) is in the lower-left corner of the image).
     */
    static Pixel::Coordinate getGridCoordinate(double x, double y);
};


#endif //RAYCASTER_H

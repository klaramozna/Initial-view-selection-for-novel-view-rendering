#ifndef CAMERA_H
#define CAMERA_H

#include "Pixel.h"
#include <set>

class Camera {
public:

    Camera() = default;

    /**
     * @brief Creates a camera with the given parameters.
     * @param pos The pixel in which the camera is located.
     * @param dir Direction vector of the direction the camera is facing.
     * @param angle Angle of view of the camera.
     * @param pixels The surface pixels that the camera sees.
     */
    Camera(Pixel::Coordinate pos, std::pair<double, double> dir, double angle): position{pos}, direction{dir}, openingAngle{angle}, visibleSurfacePixels{}{};

    /**
     * @brief Returns the pixel that the camera is in.
     * @return Pixel that the camera is in.
     */
    const Pixel::Coordinate &getPosition() const {return position;}

    /**
     * @brief Returns a normalized vector of the direction the camera is facing.
     * @return Normalized vector of the direction the camera is facing.
     */
    const std::pair<double, double> &getDirection() const {return direction;}

    /**
     * @brief Returns the opening angle of the camera.
     * @return Opening angle of the camera (determines how far to the sides the camera can see).
     */
    double getOpeningAngle() const {return openingAngle;}

    /**
     * @brief Returns the pixels that the camera sees.
     * @return The pixels that the camera sees.
     */
    const std::set<Pixel::Coordinate> &getVisibleSurfacePixels() const {return visibleSurfacePixels;}

    /**
     * @brief Adds the given pixels to the field of view of the camera if they are not there yet.
     * @param visiblePixels Surface pixels that the camera sees.
     */
    void addVisibleSurfacePixels(std::vector<Pixel::Coordinate> visiblePixels);

    bool operator==(const Camera& other) const;

    bool operator<(const Camera& other) const;

private:
    /**
     * @brief The pixel in which the camera is located.
     */
    Pixel::Coordinate position;

    /**
     * @brief Direction vector of the direction the camera is facing.
     */
    std::pair<double, double> direction;

    /**
     * @brief Angle of view of the camera.
     */
    double openingAngle;

    /**
     * @brief The surface pixels that the camera sees.
     */
    std::set<Pixel::Coordinate> visibleSurfacePixels;
};


#endif //CAMERA_H

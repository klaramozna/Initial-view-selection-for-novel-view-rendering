#ifndef INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDER_H
#define INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDER_H

#include "Camera.h"
#include "Image.h"

class CameraPlacementFinder {
public:

    CameraPlacementFinder() = default;

    /**
     * @brief Creates a CameraPlacementFinder object with the given parameters.
     * @param cameras All possible cameras.
     * @param imageHeight Height of the image in which the cameras are placed.
     * @param imageWidth Width of the image in which the cameras are placed.
     */
    CameraPlacementFinder(const std::vector<Camera>& cameras, int imageHeight, int imageWidth);

    /**
     * @brief Returns a vector of cameras that together "see" the entire surface of the object, using the greedy strategy (number of cameras not guaranteed to be minimal).
     * @return Vector of cameras that together "see" the entire surface of the object in the image.
     */
    std::vector<Camera> solveGreedyStrategy();

    /**
     * @brief Sets the width and height of the image the cameras are placed on.
     * @param width Width of the image.
     * @param height Height of the image.
     */
    void setImageDimensions(int width, int height){imWidth = width; imHeight = height;};

    /**
     * @brief Sets the initial camera possibilities.
     * @param cameras The cameras.
     */
    void setInitialCameras(const std::vector<Camera>& cameras);

    void setImage(Image im){image = im;}

private:

    /**
     * @brief All possible cameras. For each camera, the second value is true if it has not been iterated over yet.
     */
    std::vector<std::pair<Camera, bool>> allCameras;

    /**
     * @brief Height of the image in which the cameras are placed.
     */
    int imHeight;

    /**
     * @brief Width of the image in which the cameras are placed.
     */
    int imWidth;

    /**
     * @brief Image for which the camera placement should be found.
     */
    Image image;

    /**
     * @brief Returns the camera from allCameras that "sees" the largest amount of uncovered pixels.
     * @param uncoveredPixels Pixels in the uncovered set.
     * @return Camera from allCameras that "sees" the largest amount of uncovered pixels.
     */
    Camera getBestSubset(const std::set<Pixel::Coordinate>& uncoveredPixels);

    /**
     * @brief Removes any redundant cameras from the result.
     * @param cameras The intermediate result.
     * @param pixelsToCover Pixels that need to be seen by the cameras.
     * @return Final vector of cameras without any redundant ones.
     */
    std::vector<Camera> removeRedundantCameras(std::vector<Camera> cameras, std::set<Pixel::Coordinate> pixelsToCover);

};


#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDER_H

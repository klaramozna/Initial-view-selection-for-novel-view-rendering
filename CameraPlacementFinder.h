#ifndef INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDER_H
#define INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDER_H

#include "Camera.h"

class CameraPlacementFinder {
public:

    /**
     * @brief Creates a CameraPlacementFinder object with the given parameters.
     * @param cameras All possible cameras.
     * @param imageHeight Height of the image in which the cameras are placed.
     * @param imageWidth Width of the image in which the cameras are placed.
     */
    CameraPlacementFinder(std::vector<Camera> cameras, int imageHeight, int imageWidth);

    /**
     * @brief Returns a vector of cameras that together "see" the entire surface of the object, using the greedy strategy (number of cameras not guaranteed to be minimal).
     * @return Vector of cameras that together "see" the entire surface of the object in the image.
     */
    std::vector<Camera> solveGreedyStrategy();

private:

    /**
     * @brief All possible cameras.
     */
    std::set<Camera> allCameras;

    /**
     * @brief Height of the image in which the cameras are placed.
     */
    int imHeight;

    /**
     * @brief Width of the image in which the cameras are placed.
     */
    int imWidth;

    /**
     * @brief Returns the camera from allCameras that "sees" the largest amount of uncovered pixels.
     * @param uncoveredPixels Pixels in the uncovered set.
     * @return Camera from allCameras that "sees" the largest amount of uncovered pixels.
     */
    Camera getBestSubset(std::set<Pixel::Coordinate> uncoveredPixels);

};


#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDER_H

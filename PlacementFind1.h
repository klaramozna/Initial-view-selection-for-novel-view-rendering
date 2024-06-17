
#ifndef INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_PLACEMENTFIND1_H
#define INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_PLACEMENTFIND1_H

#include "Image.h"
#include "RayCaster.h"

class PlacementFind1 {
public:

    PlacementFind1() = default;
    /**
     * @brief Creates a PlacementFind1 object with the given parameters.
     * @param image Image that the camera placement should be determined for.
     * @param rayCaster The rayCaster to be used for calculating the field of view of the cameras.
     */
    PlacementFind1(Image image, RayCaster rayCaster, double camAngle): im{image}, rayCast{rayCaster}, cameraAngle{camAngle}{};

    /**
     * @brief Returns a vector of cameras that together "see" the entire object on the image.
     * @return Vector of cameras that together "see" the entire object on the image.
     */
    std::vector<Camera> solve();

    void setImage(Image image){im = image;};

    void setRayCast(RayCaster rayCaster){rayCast = rayCaster;};

    void setAngle(double angle){cameraAngle = angle;};

private:
    /**
     * @brief Image that the cameras will be placed in.
     */
    Image im;

    /**
     * @brief Algorithm used for ray-casting.
     */
    RayCaster rayCast;

    /**
     * @brief Width of the view of each camera.
     */
    double cameraAngle;

    /**
     * @brief Removes any redundant cameras from the result.
     * @param cameras The intermediate result.
     * @param pixelsToCover Pixels that need to be seen by the cameras.
     * @return Final vector of cameras without any redundant ones.
     */
    std::vector<Camera> removeRedundantCameras(std::vector<Camera> cameras, std::set<Pixel::Coordinate> pixelsToCover);

    /**
     * @brief Returns a camera right next to the given pixel, pointing in its direction.
     * @param x X Coordinate of the pixel.
     * @param y Y Coordinate of the pixel.
     * @return The camera next to the pixel pointing at it. If no such camera can be placed, a camera on the pixel itself is returned.
     */
    Camera getNeighbourCamera(int x, int y);
};


#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_PLACEMENTFIND1_H

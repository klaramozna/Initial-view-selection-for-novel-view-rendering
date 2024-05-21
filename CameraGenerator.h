#ifndef CAMERAGENERATOR_H
#define CAMERAGENERATOR_H


#include "Image.h"
#include "Camera.h"

class CameraGenerator {
public:
    /**
     * @brief Creates a camera generator with the given parameters.
     * @param directions Number of cameras generated per each possible position (each in a different direction).
     * @param angle View angle of the cameras.
     * @param im The image in which visibility is computed.
     */
    CameraGenerator(int directions, double angle, Image im): numDirections{directions}, cameraViewAngle{angle}, image{im}{this->directions = getDirections();};

    /**
     * @brief Generates all possible cameras.
     * @return The generated cameras.
     */
    std::vector<Camera> generateCameras();

private:

    /**
     * @brief Number of cameras generated per each possible position.
     */
    int numDirections;

    /**
     * @brief View angle of the cameras.
     */
    double cameraViewAngle;

    /**
     * @brief The image in which visibility is computed.
     */
    Image image;

    /**
     * @brief Generates the directions of the cameras.
     * @return Normalized vectors of directions generated.
     */
    std::vector<std::pair<double, double>> getDirections() const;

    /**
     * @brief Normalized vectors of the possible directions of cameras.
     */
    std::vector<std::pair<double, double>> directions;
};


#endif //CAMERAGENERATOR_H

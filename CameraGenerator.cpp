#include "CameraGenerator.h"
#include <cmath>
#include "RayCaster.h"


std::vector<std::pair<double, double>> CameraGenerator::getDirections() const {
    // Generate angles
    std::vector<double> angles{};
    for(int i = 0; i < numDirections; i++){
        angles.push_back((360.0 / numDirections) * i);
    }

    // Generate normalized vectors of the directions
    std::vector<std::pair<double, double>> dirs{};
    for(int i = 0; i < numDirections; i++){
        std::pair<double, double> vector{cos(angles[i] * M_PI / 180), sin(angles[i] * M_PI / 180)};
        dirs.push_back(vector);
    }

    return dirs;
}

std::vector<Camera> CameraGenerator::generateCameras() {
    std::vector<Camera> result{};
    for(int x = 0; x < image.getWidth(); x++){
        for(int y = 0; y < image.getHeight(); y++){
            if(image.getPixelType(x, y) == Pixel::EMPTY_SPACE){
                for(auto direction : directions){
                    Camera cam{Pixel::Coordinate{x, y}, direction, cameraViewAngle};
                    rayCaster.setCameraView(cam);
                    result.push_back(cam);
                }
            }
        }
    }
    return result;
}

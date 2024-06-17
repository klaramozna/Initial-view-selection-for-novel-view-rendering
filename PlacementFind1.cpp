#include "PlacementFind1.h"

std::vector<Camera> PlacementFind1::solve() {
    std::vector<Camera> result{};

    // Place cameras on the edges of the image
    std::pair<double, double> middle{im.getWidth() / 2.0, im.getHeight() / 2.0};
    for(int x = 0; x < im.getWidth(); x++){
        for(int y = 0; y < im.getHeight(); y++){
            if(im.getPixelType(x, y) == Pixel::EMPTY_SPACE){
                std::pair<double, double> dir{middle.first - (x + 0.5), middle.second - (y + 0.5)};
                Camera cam{{x, y}, dir, cameraAngle};
                rayCast.setCameraView(cam);
                result.push_back(cam);
            }
        }
    }

    // Find out which pixels have and have not been seen yet
    std::set<Pixel::Coordinate> pixelsCovered{};
    for(auto cam : result){
        pixelsCovered.insert(cam.getVisibleSurfacePixels().begin(), cam.getVisibleSurfacePixels().end());
    }

    // For each pixel that has not been seen yet, place a camera right next to it, facing the pixel
    for(int x = 0; x < im.getWidth(); x++){
        for(int y = 0; y < im.getHeight(); y++) {
            if(im.getPixelType(x, y) == Pixel::SURFACE && pixelsCovered.count({x, y}) <= 0){
                Camera cam = getNeighbourCamera(x, y);
                if(Pixel::Coordinate{x, y} != cam.getPosition()){
                    result.push_back(cam);
                }
            }
        }
    }

    // Remove redundant cameras.
    pixelsCovered = {};
    for(auto cam : result){
        pixelsCovered.insert(cam.getVisibleSurfacePixels().begin(), cam.getVisibleSurfacePixels().end());
    }
    result = removeRedundantCameras(result, pixelsCovered);

    return result;
}

std::vector<Camera>
PlacementFind1::removeRedundantCameras(std::vector<Camera> cameras, std::set<Pixel::Coordinate> pixelsToCover) {
    std::vector<std::pair<Camera, bool>> cams{};
    for(auto cam : cameras){
        cams.emplace_back(cam, true);
    }

    std::vector<Camera> finalResult{};
    for(int i = 0; i < cams.size(); i++){
        std::set<Pixel::Coordinate> coveredWithoutThisCam{};
        for(int j = 0; j < cams.size(); j++){
            if(cams[j].first != cams[i].first && cams[j].second){
                coveredWithoutThisCam.insert(cams[j].first.getVisibleSurfacePixels().begin(), cams[j].first.getVisibleSurfacePixels().end());
            }
        }
        if(coveredWithoutThisCam != pixelsToCover){
            finalResult.push_back(cams[i].first);
        }
        else{
            cams[i].second = false;
        }
    }
    return finalResult;
}

Camera PlacementFind1::getNeighbourCamera(int x, int y) {
    for(int i : {-1, 0, 1}){
        for(int j : {-1, 0, 1}){
            if(i != 0 || j != 0){
                if(x + i >= 0 && x + i < im.getWidth() && y + j >= 0 && y + j < im.getHeight() && im.getPixelType(x + i, y + j) == Pixel::EMPTY_SPACE){
                    Camera cam{{x+i, y+j}, {i, j}, cameraAngle};
                    rayCast.setCameraView(cam);
                    return cam;
                }
            }
        }
    }
    return Camera{{x, y}, {0, 0}, 0};
}

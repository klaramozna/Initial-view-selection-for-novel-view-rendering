#include "CameraPlacementFinder.h"

std::vector<Camera> CameraPlacementFinder::solveGreedyStrategy() {
    // Generate a set of all the uncovered pixels
    std::set<Pixel::Coordinate> uncoveredPixels{};
    for(int x = 0; x < imWidth; x++){
        for(int y = 0; y < imHeight; y++){
            if(image.getPixelType(x, y) == Pixel::SURFACE){
                uncoveredPixels.insert(Pixel::Coordinate{x, y});
            }
        }
    }

    std::set<Pixel::Coordinate> uncoveredPixelsUnchanged = uncoveredPixels;

    std::vector<Camera> result{};
    while(!uncoveredPixels.empty()){
        // Check if any more cameras are left, if yes, this indicates there is no solution.
        if(allCameras.empty()){
            return{};
        }
        // Find the camera that "sees" the largest number of uncovered pixels and add it to the result.
        Camera nextCam = getBestSubset(uncoveredPixels);
        result.push_back(nextCam);

        // Remove the pixels that this camera "sees" from the uncovered set.
        std::set<Pixel::Coordinate> cameraPixels = nextCam.getVisibleSurfacePixels();
        for(auto pixel : cameraPixels){
            uncoveredPixels.erase(pixel);
        }

        // Remove the camera just added from allCameras
        for(int i = 0; i < allCameras.size(); i++){
            if(allCameras[i].first == nextCam){
                allCameras[i].second = false;
            }
        }
    }
    return removeRedundantCameras(result, uncoveredPixelsUnchanged);
}

Camera CameraPlacementFinder::getBestSubset(const std::set<Pixel::Coordinate>& uncoveredPixels) {
    Camera finalCamera{};
    int maxCount = 0;
    for(const auto& cam : allCameras){
        std::set<Pixel::Coordinate> seenSet = cam.first.getVisibleSurfacePixels();
        int currentCount = 0;
        for(auto pixel : seenSet){
            if(uncoveredPixels.count(pixel) > 0) currentCount++;
        }
        if(currentCount >= maxCount){
            maxCount = currentCount;
            finalCamera = cam.first;
        }
    }
    return finalCamera;
}

CameraPlacementFinder::CameraPlacementFinder(const std::vector<Camera>& cameras, int imageHeight, int imageWidth): imHeight{imageHeight}, imWidth{imageWidth} {
    for (const auto& camera: cameras){
        allCameras.push_back({camera, true});
    }
}

void CameraPlacementFinder::setInitialCameras(const std::vector<Camera> &cameras) {
    for(auto cam : cameras){
        allCameras.push_back({cam, true});
    }
}

std::vector<Camera>
CameraPlacementFinder::removeRedundantCameras(std::vector<Camera> cameras, std::set<Pixel::Coordinate> pixelsToCover) {
    /*std::vector<Camera> finalResult{};
    for(auto camRemove : cameras){
        std::set<Pixel::Coordinate> coveredWithoutThisCam{};
        for(auto cam : cameras){
            if(cam != camRemove){
                coveredWithoutThisCam.insert(cam.getVisibleSurfacePixels().begin(), cam.getVisibleSurfacePixels().end());
            }
        }
        if(coveredWithoutThisCam != pixelsToCover){
            finalResult.push_back(camRemove);
        }
    }
    return finalResult;*/
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

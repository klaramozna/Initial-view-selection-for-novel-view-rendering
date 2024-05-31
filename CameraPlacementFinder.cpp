#include "CameraPlacementFinder.h"

std::vector<Camera> CameraPlacementFinder::solveGreedyStrategy() {
    // Generate a set of all the uncovered pixels
    std::set<Pixel::Coordinate> uncoveredPixels{};
    for(int x = 0; x < imWidth; x++){
        for(int y = 0; y < imHeight; y++){
            uncoveredPixels.insert(Pixel::Coordinate{x, y});
        }
    }

    std::vector<Camera> result{};
    while(!uncoveredPixels.empty()){
        // Find the camera that "sees" the largest number of uncovered pixels and add it to the result.
        Camera nextCam = getBestSubset(uncoveredPixels);
        result.push_back(nextCam);

        // Remove the pixels that this camera "sees" from the uncovered set.
        std::set<Pixel::Coordinate> cameraPixels = nextCam.getVisibleSurfacePixels();
        for(auto pixel : cameraPixels){
            uncoveredPixels.erase(pixel);
        }

        // Remove the camera just added from allCameras
        allCameras.erase(nextCam);
    }

    return result;
}

Camera CameraPlacementFinder::getBestSubset(std::set<Pixel::Coordinate> uncoveredPixels) {
    Camera finalCamera{};
    int maxCount = 0;
    for(auto cam : allCameras){
        std::set<Pixel::Coordinate> seenSet = cam.getVisibleSurfacePixels();
        int currentCount = 0;
        for(auto pixel : seenSet){
            if(uncoveredPixels.count(pixel) > 0) currentCount++;
        }
        if(currentCount >= maxCount){
            maxCount = currentCount;
            finalCamera = cam;
        }
    }
    return finalCamera;
}

CameraPlacementFinder::CameraPlacementFinder(std::vector<Camera> cameras, int imageHeight, int imageWidth): imHeight{imageHeight}, imWidth{imageWidth} {
    for (auto camera: cameras){
        allCameras.insert(camera);
    }
}

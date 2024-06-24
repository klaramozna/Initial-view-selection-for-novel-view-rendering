#include "PlacementFind1Test.h"
#include "../DebugVisualize.h"

void PlacementFind1Test::SetUp() {
    image3.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input1.ssv");
}

TEST_F(PlacementFind1Test, onePixel){
    std::shared_ptr<Image> imPtr = std::make_shared<Image>(image3);
    RayCaster rayCaster{imPtr, 1000};
    placementFinder.setImage(image3);
    placementFinder.setAngle(360);
    placementFinder.setRayCast(rayCaster);
    std::vector<Camera> result = placementFinder.solve();
    DebugVisualize visualize(image3);
    visualize.visualizeCameras(result);
    std::cout << std::endl;
    for(auto cam : result){
        visualize.visualizeCamera(cam);
        std::cout << "-------------" << std::endl;
    }
}
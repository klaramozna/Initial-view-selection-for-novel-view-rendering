#include "CameraPlacementFinderTest.h"
#include "../CameraGenerator.h"
#include "../DebugVisualize.h"
#include <memory>

TEST_F(CameraPlacementFinderTest, onePixel){
    std::shared_ptr<Image> imPtr = std::make_shared<Image>(image3);
    RayCaster rayCaster{imPtr, 1000};
    CameraGenerator generator{1, 360, image3, rayCaster};
    auto cams = generator.generateCameras();
    placementFinder.setInitialCameras(cams);
    placementFinder.setImage(image3);
    std::vector<Camera> result = placementFinder.solveGreedyStrategy();
    DebugVisualize visualize(image3);
    visualize.visualizeCameras(result);

}

void CameraPlacementFinderTest::SetUp() {
    image3.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input3.ssv");
    placementFinder.setImageDimensions(image3.getWidth(), image3.getHeight());
}

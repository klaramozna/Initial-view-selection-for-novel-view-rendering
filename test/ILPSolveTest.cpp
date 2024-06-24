

#include "ILPSolveTest.h"
#include "../RayCaster.h"
#include "../CameraGenerator.h"
#include "../DebugVisualize.h"

TEST_F(ILPSolveTest, onePixel){
    std::shared_ptr<Image> imPtr = std::make_shared<Image>(image3);
    RayCaster rayCaster{imPtr, 1000};
    CameraGenerator generator{4, 90, image3, rayCaster};
    auto cams = generator.generateCameras();
    solver.setCameras(cams);
    solver.setImage(image3);
    std::vector<Camera> result = solver.solve();
    DebugVisualize visualize(image3);
    visualize.visualizeCameras(result);
    std::cout << std::endl;
    for(auto cam : result){
        visualize.visualizeCamera(cam);
        std::cout << "-------------" << std::endl;
    }


}

void ILPSolveTest::SetUp() {
    image3.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input1.ssv");
}

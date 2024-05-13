#include <iostream>
#include "Image.h"
#include <memory>
#include "DebugVisualize.h"
#include "RayCaster.h"
#include "SimpleRayCast.h"

int main(){

    Image image{};
    std::shared_ptr<Image> testImage1 = std::make_shared<Image>(image);
    testImage1->readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input1.ssv");
    SimpleRayCast cast{};
    cast.setImage(testImage1);
    cast.computeVisibility();
    DebugVisualize visu(*testImage1);
    visu.visualizePixelVisibility(9, 8);



};

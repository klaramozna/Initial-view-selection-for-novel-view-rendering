#include <algorithm>
#include "SimpleRayCastTest.h"
#include "../DebugVisualize.h"

void SimpleRayCastTest::SetUp() {
    testImage0->readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input0.ssv");
    testImage1->readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input1.ssv");
}

// Simple case with only one surface pixel in the middle and 360 degree view
TEST_F(SimpleRayCastTest, noObstacles){
    Camera cam{Pixel::Coordinate{5, 3}, std::pair<double, double>{1, 1}, 360};
    rayCast.setImage(testImage0);
    rayCast.setCameraView(cam);

    // Create the set for the correct answer (all pixels except for the single surface pixel)
    std::set<Pixel::Coordinate> correctAnswer;
    std::set<Pixel::Coordinate> emptySet{};
    for(int x = 0; x < testImage0->getWidth(); x++) {
        for (int y = 0; y < testImage0->getHeight(); y++) {
            if(x != 5 || y != 3){
                correctAnswer.emplace(x, y);
            }
        }
    }

    // Print differences if the answer is false
    if(correctAnswer != cam.getVisibleSurfacePixels()){
        printSetDifference(correctAnswer, cam.getVisibleSurfacePixels());
        DebugVisualize visualize(*testImage0);
        visualize.visualizeCamera(cam);
    }

    // Compare
    ASSERT_EQ(correctAnswer, cam.getVisibleSurfacePixels());
}

// Simple obstacle - straight line parallel to the grid
TEST_F(SimpleRayCastTest, simpleObstacle){
    /*rayCast.setImage(testImage1);
    rayCast.computeVisibility();
    DebugVisualize visualize(*testImage1);
    visualize.visualizePixelVisibility(9, 8);*/

}

void SimpleRayCastTest::printSetDifference(const std::set<Pixel::Coordinate>& correct, const std::set<Pixel::Coordinate>& answer) {
    std::vector<Pixel::Coordinate> diff;

    std::set_difference(correct.begin(), correct.end(), answer.begin(), answer.end(), std::back_inserter(diff));
    if (!diff.empty()) {
        std::cout << "In correct answer but not in the real answer:\n";
        for (const auto& item : diff) {
            std::cout << "(" << item.x << ", " << item.y << ")\n";
        }
    }

    diff.clear();
    std::set_difference(answer.begin(), answer.end(), correct.begin(), correct.end(), std::back_inserter(diff));
    if (!diff.empty()) {
        std::cout << "In real answer but not in the correct answer:\n";
        for (const auto& item : diff) {
            std::cout << "(" << item.x << ", " << item.y << ")\n";
        }
    }
}

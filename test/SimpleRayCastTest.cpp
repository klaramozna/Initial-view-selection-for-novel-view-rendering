#include <algorithm>
#include "SimpleRayCastTest.h"
#include "../DebugVisualize.h"

void SimpleRayCastTest::SetUp() {
    testImage0->readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input0.ssv");
    rayCast.setImage(testImage0);
}

// Simple case with only one surface pixel in the middle
TEST_F(SimpleRayCastTest, noObstacles){
    rayCast.computeVisibility();

    // Create the set for the correct answer (all pixels except for the single surface pixel)
    std::set<Pixel::Coordinate> correctAnswer;
    std::set<Pixel::Coordinate> emptySet{};
    for(int x = 0; x < testImage0->getWidth(); x++) {
        for (int y = 0; y < testImage0->getHeight(); y++) {
            if(x != 5 || y != 3){
                correctAnswer.emplace(x, y);
                // Make sure visibility was not calculated for non-surface pixels
                ASSERT_EQ(testImage0->getVisiblePixels(x, y), emptySet);
            }
        }
    }

    // Print differences if the answer is false
    if(correctAnswer != testImage0->getVisiblePixels(5, 3)){
        printSetDifference(correctAnswer, testImage0->getVisiblePixels(5, 3));
        DebugVisualize visualize(*testImage0);
        visualize.visualizePixelVisibility(5, 3);
    }

    // Compare
    ASSERT_EQ(correctAnswer, testImage0->getVisiblePixels(5, 3));
}

TEST_F(SimpleRayCastTest, simpleObstacles){

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

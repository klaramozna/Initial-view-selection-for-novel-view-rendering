#include <iostream>
#include "Image.h"
#include <memory>
#include "DebugVisualize.h"
#include "RayCaster.h"
#include "Visualizer.h"
#include "CameraGenerator.h"
#include "ILPSolve.h"

// Define the constants
const int GRID_WIDTH = 20;     // Width of the grid in cells
const int GRID_HEIGHT = 10;    // Height of the grid in cells
const int CELL_SIZE = 30;      // Size of each cell in pixels

// Calculate window dimensions based on grid and cell size
const int WINDOW_WIDTH = GRID_WIDTH * CELL_SIZE;  // Width of the window
const int WINDOW_HEIGHT = GRID_HEIGHT * CELL_SIZE; // Height of the window

int main(){
    Image image3;
    image3.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input1.ssv");
    std::shared_ptr<Image> imPtr = std::make_shared<Image>(image3);
    RayCaster rayCaster{imPtr, 1000};
    CameraGenerator generator{4, 90, image3, rayCaster};
    auto cams = generator.generateCameras();
    ILPSolve solver{};
    solver.setCameras(cams);
    solver.setImage(image3);
    std::vector<Camera> result = solver.solve();
    Visualizer visualizer(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE, image3, result);
    visualizer.visualize();

    return 0;

};

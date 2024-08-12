#include <iostream>
#include "Image.h"
#include <memory>
#include "DebugVisualize.h"
#include "RayCaster.h"
#include "Visualizer.h"
#include "CameraGenerator.h"
#include "ILPSolve.h"
#include "CameraPlacementFinder.h"
#include "PlacementFind1.h"
#include <fstream>
#include <chrono>

// Define the constants
const int GRID_WIDTH = 21;     // Width of the grid in cells
const int GRID_HEIGHT = 17;    // Height of the grid in cells
const int CELL_SIZE = 20;      // Size of each cell in pixels

// Calculate window dimensions based on grid and cell size
const int WINDOW_WIDTH = GRID_WIDTH * CELL_SIZE;  // Width of the window
const int WINDOW_HEIGHT = GRID_HEIGHT * CELL_SIZE; // Height of the window

int main(){
    /*Image image3;
    image3.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input0.ssv");
    std::shared_ptr<Image> imPtr = std::make_shared<Image>(image3);
    RayCaster rayCaster{imPtr, 1000};
    CameraGenerator generator{16, 90, image3, rayCaster};
    auto cams = generator.generateCameras();
    ILPSolve solver{};
    solver.setCameras(cams);
    solver.setImage(image3);
    CameraPlacementFinder finder{cams, image3.getHeight(), image3.getWidth()};
    finder.setImage(image3);
    std::vector<Camera> resultGreedy = finder.solveGreedyStrategy();
    std::vector<Camera> resultILP = solver.solve();
    PlacementFind1 find{image3, rayCaster, 90};
    std::vector<Camera> resultNaive = find.solve();
    DebugVisualize visualize(image3);
    for(auto cam : resultGreedy){
        visualize.visualizeCamera(cam);
        std::cout << "-------------" << std::endl;
    }
    Visualizer visualizer(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE, image3, {});
    visualizer.visualize();*/

    Image image3;
    image3.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input1.ssv");
    std::shared_ptr<Image> imPtr = std::make_shared<Image>(image3);

    auto basePath = "/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/squares/";
    std::vector<Image> images{};
    for(auto i = 1; i <= 50; i++){
        std::string realpath = basePath + std::to_string(i) + "x" + std::to_string(i) + ".ssv";
        Image im;
        im.readFromFile(realpath);
        images.push_back(im);
    }

    std::ofstream outputFile("execution_times.txt");
    std::ofstream outputFile1("exe-times2.txt");
    std::ofstream outputFile3("num-cams.txt");
    if (!outputFile.is_open() || !outputFile1.is_open()) {
        std::cerr << "Failed to open file for writing" << std::endl;
        return 1;
    }

    // Test different values of the variable
    for (int variable = 4; variable <= 50; ++variable) {
        std::shared_ptr<Image> ptr = std::make_shared<Image>(image3);
        RayCaster rayCaster{ptr, 1000};


        CameraGenerator generator{variable, 90, image3, rayCaster};


        auto cams = generator.generateCameras();

        ILPSolve finder{cams, image3};
        CameraPlacementFinder finderGreedy{cams, image3.getHeight(), image3.getWidth()};
        finderGreedy.setImage(image3);

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<Camera> resultILP = finder.solve();
        auto end = std::chrono::high_resolution_clock::now();

        auto startGreedy = std::chrono::high_resolution_clock::now();
        auto resGreedy = finderGreedy.solveGreedyStrategy();
        auto endGreedy = std::chrono::high_resolution_clock::now();




        if(!resultILP.empty()){
            std::cout << "success" << std::endl;
        }


        std::chrono::duration<double> elapsed = end - start;
        std::chrono::duration<double> elapsedGreedy = endGreedy - startGreedy;

        // Write the variable value and execution time to the file
        outputFile << variable << " " << elapsed.count() << std::endl;
        outputFile1 << variable << " " << elapsedGreedy.count() << std::endl;
    }

    outputFile.close();
    outputFile1.close();
    outputFile3.close();
    std::cout << "Execution times written to execution_times.txt" << std::endl;

    return 0;


};

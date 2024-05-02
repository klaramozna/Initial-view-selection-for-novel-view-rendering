#include "InputHandler.h"
#include <fstream>
#include <sstream>

InputHandler::Status InputHandler::readFile(const std::string& filePath) {
    // Open the file and check if it was successful
    std::ifstream file(filePath);
    if (!file.is_open()) {
        status = FAILURE;
        return FAILURE;
    }

    // Read the file, line by line
    std::string line;
    int width = 0;
    bool isFirstPass = true;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<Pixel> vectorLine;
        int value;

        // Read values within a line
        while (lineStream >> value) {
            Pixel::PixelType type;

            // Convert value to type, handle invalid values
            switch (value) {
                case 0:
                    type = Pixel::EMPTY_SPACE;
                    break;
                case 1:
                    type = Pixel::INTERIOR;
                    break;
                case 2:
                    type = Pixel::SURFACE;
                    break;
                default:
                    status = FAILURE;
                    pixels = std::vector<std::vector<Pixel>>{};
                    return FAILURE;
            }

            // Add values the vector
            vectorLine.emplace_back(type);

            // Determine the width of the first line
            if (isFirstPass) {
                width++;
            }
        }

        isFirstPass = false;

        // Return failure if there are rows of different sizes
        if(vectorLine.size() != width){
            status = FAILURE;
            pixels = std::vector<std::vector<Pixel>>{};
            return FAILURE;
        }

        // Add row to vector
        pixels.push_back(vectorLine);
    }

    file.close();
    return SUCCESS;
}

std::vector<std::vector<Pixel>> InputHandler::getPixels() {
    return pixels;
}

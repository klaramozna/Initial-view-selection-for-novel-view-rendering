//
// Created by klara on 03.05.24.
//

#include "Image.h"
#include <fstream>
#include <sstream>

Image::Status Image::readFromFile(const std::string &filePath) {
    // Open the file and check if it was successful
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return FAILURE;
    }

    // Read the file, line by line
    std::string line;
    width = 0;
    height = 0;
    bool isFirstPass = true;
    while (std::getline(file, line)) {
        int currentWidth = 0;
        height++;
        std::istringstream lineStream(line);
        int value;

        // Read values within a line
        while (lineStream >> value) {
            currentWidth++;
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
                    return FAILURE;
            }

            // Add values the vector
            pixels.emplace_back(type);

            // Determine the width of the first line
            if (isFirstPass) {
                width++;
            }
        }

        isFirstPass = false;

        // Return failure if there are rows of different sizes
        if(currentWidth != width){
            return FAILURE;
        }
    }

    file.close();
    return SUCCESS;
}

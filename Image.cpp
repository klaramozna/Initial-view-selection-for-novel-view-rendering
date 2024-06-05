//
// Created by klara on 03.05.24.
//

#include "Image.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

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

Pixel::PixelType Image::getPixelType(int x, int y) const {
    // Get index in the pixels vector
    int index = getIndex(x, y);

    // Check that the pixel coordinates are valid.
    if(index < 0 || index >= pixels.size()){
        throw std::runtime_error("x or y coordinate out of image.");
    }

    return pixels[index].getType();
}

Pixel::PixelType Image::getPixelType(Pixel::Coordinate coordinate) const {
    // Get index in the pixels vector
    int index = getIndex(coordinate.x, coordinate.y);

    // Check that the pixel coordinates are valid.
    if(index < 0 || index >= pixels.size()){
        throw std::runtime_error("x or y coordinate out of image.");
    }

    return pixels[index].getType();
}

void Image::addVisiblePixels(Pixel::Coordinate coordinate, const std::vector<Pixel::Coordinate>& visiblePixels) {
    // Get index in the pixels vector
    int index = getIndex(coordinate.x, coordinate.y);

    // Check that the pixel coordinates are valid.
    if(index < 0 || index >= pixels.size()){
        throw std::runtime_error("x or y coordinate out of image.");
    }

    pixels[index].addVisiblePixels(visiblePixels);
}

void Image::addVisiblePixels(int x, int y, const std::vector<Pixel::Coordinate>& visiblePixels) {
    // Get index in the pixels vector
    int index = getIndex(x, y);

    // Check that the pixel coordinates are valid.
    if(index < 0 || index >= pixels.size()){
        throw std::runtime_error("x or y coordinate out of image.");
    }

    pixels[index].addVisiblePixels(visiblePixels);
}

std::vector<Pixel::Coordinate> Image::getSurfacePixels() {
    std::vector<Pixel::Coordinate> surfacePixels{};
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if(pixels[getIndex(x, y)].getType() == Pixel::SURFACE){
                surfacePixels.emplace_back(x, y);
            }
        }
    }
    return surfacePixels;
}

std::set<Pixel::Coordinate> Image::getVisiblePixels(int x, int y) {
    // Get index in the pixels vector
    int index = getIndex(x, y);

    // Check that the pixel coordinates are valid.
    if(index < 0 || index >= pixels.size()){
        throw std::runtime_error("x or y coordinate out of image.");
    }

    return pixels[index].getVisiblePixels();
}

bool Image::isWithin(Pixel::Coordinate coor) {
     return coor.x >= 0 && coor.y >= 0 && coor.x <= width - 1 && coor.y <= height - 1;
}

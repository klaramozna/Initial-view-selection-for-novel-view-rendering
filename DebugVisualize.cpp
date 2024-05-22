#include "DebugVisualize.h"
#include <iostream>
#include <algorithm>


// OBJECT - part of the object
// PIXEL - the pixel for which visibility is visualized
// VISIBLE - visible surface pixel from thr camera
// EMPTY - empty space
// ERROR - a pixel that should not be visible is visible
void DebugVisualize::visualizeCamera(Camera cam) {
    enum pixelType{EMPTY, OBJECT, CAMERA, VISIBLE, ERROR};
    std::vector<pixelType> pixels{};
    for(int yCoord = 0; yCoord < image.getHeight(); yCoord++){
        for(int xCoord = 0; xCoord < image.getWidth(); xCoord++){
            // Surface pixel visible from camera
            if(cam.getVisibleSurfacePixels().count(Pixel::Coordinate{xCoord, yCoord}) > 0){
                if(image.getPixelType(xCoord, yCoord) != Pixel::SURFACE){
                    pixels.push_back(ERROR);
                }
                else{
                    pixels.push_back(VISIBLE);
                }
            }
            // Camera pixel
            else if(xCoord == cam.getPosition().x && yCoord == cam.getPosition().y){
                pixels.push_back(CAMERA);
            }
            // Part of the object, but not visible by camera
            else if(image.getPixelType(xCoord, yCoord) != Pixel::EMPTY_SPACE){
                pixels.push_back(OBJECT);
            }
            // Empty space
            else{
                pixels.push_back(EMPTY);
            }
        }
    }

    Color color;
    for(int yCoord = 0; yCoord < image.getHeight(); yCoord++){
        for(int xCoord = 0; xCoord < image.getWidth(); xCoord++){
            char pixel;
            switch(pixels[yCoord * image.getWidth() + xCoord]){
                case ERROR: pixel = 'X'; color = RED;break;
                case OBJECT: pixel = 'O';color = YELLOW;break;
                case CAMERA: pixel = 'P'; color = RED;break;
                case VISIBLE: pixel = 'V'; color = GREEN; break;
                case EMPTY: pixel = 'E'; color = BLUE;
            }
            setOutputColor(color);
            std::cout << "▄" << ' ' << ' ';
        }
        std::cout << std::endl;
    }

    setOutputColor(RESET);

}

void DebugVisualize::setOutputColor(DebugVisualize::Color color) {
    int colorCode;
    switch(color){
        case RED: colorCode = 31; break;
        case YELLOW: colorCode = 33; break;
        case BLUE: colorCode = 34; break;
        case GREEN: colorCode = 32; break;
        default:colorCode = 0;
    }
    std::cout << "\033[" << colorCode << "m";
}

void DebugVisualize::visualizeCameras(std::vector<Camera> cams) {
    // Create a set of all visible pixels
    std::set<Pixel::Coordinate> visiblePixels{};
    for(auto cam : cams){
        for(auto pixel : cam.getVisibleSurfacePixels()){
            visiblePixels.insert(pixel);
        }
    }

    // Create a vector of all camera coordinates
    std::vector<Pixel::Coordinate> positions{};
    for(auto cam : cams){
        positions.push_back(cam.getPosition());
    }


    enum pixelType{EMPTY, OBJECT, CAMERA, VISIBLE, ERROR};
    std::vector<pixelType> pixels{};
    for(int yCoord = 0; yCoord < image.getHeight(); yCoord++){
        for(int xCoord = 0; xCoord < image.getWidth(); xCoord++){
            // Surface pixel visible from camera
            if(visiblePixels.count(Pixel::Coordinate{xCoord, yCoord}) > 0){
                if(image.getPixelType(xCoord, yCoord) != Pixel::SURFACE){
                    pixels.push_back(ERROR);
                }
                else{
                    pixels.push_back(VISIBLE);
                }
            }
                // Camera pixel
            else if(std::find(positions.begin(), positions.end(), Pixel::Coordinate{xCoord, yCoord}) != positions.end()){
                pixels.push_back(CAMERA);
            }
                // Part of the object, but not visible by camera
            else if(image.getPixelType(xCoord, yCoord) != Pixel::EMPTY_SPACE){
                pixels.push_back(OBJECT);
            }
                // Empty space
            else{
                pixels.push_back(EMPTY);
            }
        }
    }

    Color color;
    for(int yCoord = 0; yCoord < image.getHeight(); yCoord++){
        for(int xCoord = 0; xCoord < image.getWidth(); xCoord++){
            char pixel;
            switch(pixels[yCoord * image.getWidth() + xCoord]){
                case ERROR: pixel = 'X'; color = RED;break;
                case OBJECT: pixel = 'O';color = YELLOW;break;
                case CAMERA: pixel = 'P'; color = RED;break;
                case VISIBLE: pixel = 'V'; color = GREEN; break;
                case EMPTY: pixel = 'E'; color = BLUE;
            }
            setOutputColor(color);
            std::cout << "▄" << ' ' << ' ';
        }
        std::cout << std::endl;
    }

    setOutputColor(RESET);
}

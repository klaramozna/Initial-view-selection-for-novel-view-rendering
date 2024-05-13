#include "DebugVisualize.h"
#include <iostream>

// ERROR - a pixel marked that should never be marked visisble is marked as visible
// OBJECT - part of the object
// PIXEL - the pixel for which visibility is visualized
// VISIBLE - visible pixel
// EMPTY - not visible outside of object
void DebugVisualize::visualizePixelVisibility(int x, int y) {
    enum pixelType{EMPTY, OBJECT, PIXEL, VISIBLE, ERROR};
    std::vector<pixelType> pixels{};
    auto visibilitySet = image.getVisiblePixels(x, y);
    for(int yCoord = 0; yCoord < image.getHeight(); yCoord++){
        for(int xCoord = 0; xCoord < image.getWidth(); xCoord++){
            if(visibilitySet.count(Pixel::Coordinate(xCoord, yCoord)) > 0){
                if(image.getPixelType(xCoord, yCoord) != Pixel::EMPTY_SPACE || (xCoord == x && yCoord == y)){
                    pixels.push_back(ERROR);
                }
                else{
                    pixels.push_back(VISIBLE);
                }
            }
            else{
                if(xCoord == x && yCoord == y){
                    pixels.push_back(PIXEL);
                }
                else if(image.getPixelType(xCoord, yCoord) == Pixel::EMPTY_SPACE){
                    pixels.push_back(EMPTY);
                }
                else{
                    pixels.push_back(OBJECT);
                }
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
                case PIXEL: pixel = 'P'; color = RED;break;
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

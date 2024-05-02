#include <iostream>
#include "InputHandler.h"

int main(){
    InputHandler handler{};
    if(handler.readFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/input_test.ssv") == InputHandler::FAILURE){
        std::cout << "wronh" << std::endl;
    };
    std::vector<std::vector<Pixel>> vec = handler.getPixels();


};

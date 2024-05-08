#include <iostream>
#include "Image.h"

int main(){
    Image image{};
    if(image.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input0.ssv") == Image::FAILURE){
        std::cout << "wronh" << std::endl;
    };


};

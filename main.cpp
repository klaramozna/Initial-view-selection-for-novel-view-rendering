#include <iostream>
#include "Image.h"

int main(){
    Image image{};
    if(image.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/input_test.ssv") == Image::FAILURE){
        std::cout << "wronh" << std::endl;
    };


};

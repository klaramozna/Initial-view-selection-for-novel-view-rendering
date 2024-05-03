//
// Created by klara on 03.05.24.
//

#include "Image.h"

Image::Image(const std::vector<std::vector<Pixel>>& pixels) {
    // Set height and width
    height = pixels.size();
    if(pixels.size() >= 1) width = pixels[0].size();

    // Go through array and copy elements
    for(const auto & pixel : pixels){
        for(const auto & j : pixel){
            this->pixels.push_back(j);
        }
    }
}

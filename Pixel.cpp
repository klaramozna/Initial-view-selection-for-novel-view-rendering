#include "Pixel.h"

void Pixel::addVisiblePixels(const std::vector<Coordinate>& visiblePixels) {
    for(auto pixel : visiblePixels){
        seenFrom.insert(pixel);
    }
}

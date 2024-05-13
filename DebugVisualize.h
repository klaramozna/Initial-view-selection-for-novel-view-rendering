#ifndef DEBUGVISUALIZE_H
#define DEBUGVISUALIZE_H

#include <utility>

#include "Image.h"

class DebugVisualize {
public:
    explicit DebugVisualize(Image imageInput): image{std::move(imageInput)}{};
    void visualizePixelVisibility(int x, int y);

private:
    Image image;
    enum Color{RED, YELLOW, BLUE, GREEN, RESET};
    void setOutputColor(Color color);
};


#endif //DEBUGVISUALIZE_H

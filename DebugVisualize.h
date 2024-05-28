#ifndef DEBUGVISUALIZE_H
#define DEBUGVISUALIZE_H

#include <utility>

#include "Image.h"
#include "Camera.h"

class DebugVisualize {
public:
    explicit DebugVisualize(Image imageInput): image{std::move(imageInput)}{};
    void visualizeCamera(Camera cam);
    void visualizeCameras(std::vector<Camera> cams);

private:
    Image image;
    std::vector<Camera> cams;
    enum Color{RED, YELLOW, BLUE, GREEN, RESET};
    void setOutputColor(Color color);
};


#endif //DEBUGVISUALIZE_H

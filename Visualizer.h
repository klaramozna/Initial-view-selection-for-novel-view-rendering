#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SDL2/SDL.h>
#include <vector>
#include "Image.h"
#include "Camera.h"

enum CellType {
    AIR,
    OBJECT,
    CAMERA
};

struct Cam {
    int x;
    int y;
    double direction;
    double openingAngle;
};

class Visualizer {
public:
    Visualizer(int windowWidth, int windowHeight, int gridWidth, int gridHeight, int cellSize, Image im, std::vector<Camera> cams);
    ~Visualizer();
    void visualize();

private:
    bool initSDL();
    void cleanupSDL();
    void renderGrid();
    bool saveScreenshotBMP(const char* filepath);
    double degToRad(double degrees);
    Pixel::Coordinate getGridCoordinate(double x, double y);
    void drawArrow(int startX, int startY, int endX, int endY);
    void drawFOV(int camX, int camY, double directionX, double directionY, double fovAngle);
    void drawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness);
    void drawArrow(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness, int arrowSize);
    SDL_Window* window;
    SDL_Renderer* renderer;
    int windowWidth;
    int windowHeight;
    int gridWidth;
    int gridHeight;
    int cellSize;
    std::vector<Camera> cameras;
    Image image;
};

#endif // VISUALIZER_H

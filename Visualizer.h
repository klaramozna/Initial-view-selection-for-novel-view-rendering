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
    std::vector<Pixel::Coordinate> castRayDir(double xStart, double yStart, double xDir, double yDir);
    Pixel::Coordinate getGridCoordinate(double x, double y);
    std::vector<std::pair<int, int>> setCameraView(Camera& camera);

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

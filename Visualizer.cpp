#include "Visualizer.h"
#include <iostream>
#include <cmath>
#include <set>
#include <vector>

const double PI = 3.14159265358979323846;

std::pair<double, double> getMiddle(int x, int y) {
    return std::pair<double, double>{x + 0.5, y + 0.5};
}

Pixel::Coordinate Visualizer::getGridCoordinate(double x, double y) {
    return Pixel::Coordinate{static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y))};
}

Visualizer::Visualizer(int windowWidth, int windowHeight, int gridWidth, int gridHeight, int cellSize, Image im, std::vector<Camera> cams)
        : window(nullptr), renderer(nullptr), windowWidth(windowWidth), windowHeight(windowHeight),
          gridWidth(gridWidth), gridHeight(gridHeight), cellSize(cellSize) {

    cameras = cams;
    image = im;

    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL." << std::endl;
    }
}

Visualizer::~Visualizer() {
    cleanupSDL();
}

bool Visualizer::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Grid Visualization", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}

void Visualizer::cleanupSDL() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

double Visualizer::degToRad(double degrees) {
    return degrees * PI / 180.0;
}

void Visualizer::drawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness) {
    for (int i = -thickness / 2; i <= thickness / 2; ++i) {
        SDL_RenderDrawLine(renderer, x1 + i, y1, x2 + i, y2);
        SDL_RenderDrawLine(renderer, x1, y1 + i, x2, y2 + i);
    }
}

void Visualizer::drawArrow(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness, int arrowSize) {
    drawThickLine(renderer, x1, y1, x2, y2, thickness);

    double angle = std::atan2(y2 - y1, x2 - x1);

    int arrowX1 = x2 - arrowSize * std::cos(angle - PI / 6);
    int arrowY1 = y2 - arrowSize * std::sin(angle - PI / 6);
    int arrowX2 = x2 - arrowSize * std::cos(angle + PI / 6);
    int arrowY2 = y2 - arrowSize * std::sin(angle + PI / 6);

    drawThickLine(renderer, x2, y2, arrowX1, arrowY1, thickness);
    drawThickLine(renderer, x2, y2, arrowX2, arrowY2, thickness);
}

void Visualizer::renderGrid() {
    std::set<std::pair<int, int>> visiblePixels;
    for (Camera& camera : cameras) {
        auto visible = camera.getVisibleSurfacePixels();
        for(auto vis : visible){
            visiblePixels.insert({vis.x, vis.y});
        }
    }

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            SDL_Rect cellRect = { x * cellSize, y * cellSize, cellSize, cellSize };
            if (visiblePixels.find({x, y}) != visiblePixels.end()) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 139, 255); // Dark blue for visible pixels
            } else if (image.getPixelType(x, y) != Pixel::EMPTY_SPACE) {
                SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // Medium blue for objects
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for empty space
            }
            SDL_RenderFillRect(renderer, &cellRect);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cellRect);
        }
    }

    for (Camera& camera : cameras) {
        SDL_Rect cameraRect = { camera.getPosition().x * cellSize + cellSize / 4, camera.getPosition().y * cellSize + cellSize / 4, cellSize / 2, cellSize / 2 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for cameras
        SDL_RenderFillRect(renderer, &cameraRect);

        auto [camX, camY] = getMiddle(camera.getPosition().x, camera.getPosition().y);
        auto [dirX, dirY] = std::make_pair(camX + camera.getDirection().first, camY + camera.getDirection().second);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for direction arrow
        drawArrow(renderer, camX * cellSize, camY * cellSize, dirX * cellSize, dirY * cellSize, 3, 10);

        double fov = camera.getOpeningAngle();
        double leftAngle = std::atan2(camera.getDirection().second, camera.getDirection().first) - degToRad(fov / 2.0);
        double rightAngle = std::atan2(camera.getDirection().second, camera.getDirection().first) + degToRad(fov / 2.0);
        double fovLength = 1.5;

        auto [leftX, leftY] = std::make_pair(camX + fovLength * std::cos(leftAngle), camY + fovLength * std::sin(leftAngle));
        auto [rightX, rightY] = std::make_pair(camX + fovLength * std::cos(rightAngle), camY + fovLength * std::sin(rightAngle));

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for FOV arrows
        drawArrow(renderer, camX * cellSize, camY * cellSize, leftX * cellSize, leftY * cellSize, 3, 10);
        drawArrow(renderer, camX * cellSize, camY * cellSize, rightX * cellSize, rightY * cellSize, 3, 10);
    }
}

bool Visualizer::saveScreenshotBMP(const char* filepath) {
    SDL_Surface* saveSurface = nullptr;
    SDL_Surface* infoSurface = SDL_GetWindowSurface(window);
    if (infoSurface == nullptr) {
        std::cerr << "Failed to get the window surface: " << SDL_GetError() << std::endl;
        return false;
    }

    saveSurface = SDL_CreateRGBSurface(0, infoSurface->w, infoSurface->h, 32,
                                       0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (saveSurface == nullptr) {
        std::cerr << "Failed to create save surface: " << SDL_GetError() << std::endl;
        return false;
    }

    if (SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_ARGB8888, saveSurface->pixels, saveSurface->pitch) != 0) {
        std::cerr << "Failed to read pixels from renderer: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(saveSurface);
        return false;
    }

    if (SDL_SaveBMP(saveSurface, filepath) != 0) {
        std::cerr << "Failed to save BMP file: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(saveSurface);
        return false;
    }

    SDL_FreeSurface(saveSurface);
    return true;
}

void Visualizer::visualize() {
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_s) {
                    if (saveScreenshotBMP("screenshot.bmp")) {
                        std::cout << "Screenshot saved successfully!" << std::endl;
                    } else {
                        std::cerr << "Failed to save screenshot." << std::endl;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        renderGrid();

        SDL_RenderPresent(renderer);
    }
}

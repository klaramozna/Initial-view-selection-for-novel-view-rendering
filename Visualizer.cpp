#include "Visualizer.h"
#include <iostream>
#include <cmath>

const double PI = 3.14159265358979323846;

std::pair<double, double> getMiddle(int x, int y) {
    return std::pair<double, double>{x + 0.5, y + 0.5};
}

std::pair<double, double> rotateVector(std::pair<double, double> vector, double rotationAngle) {
    // Convert to radians
    double angleRadians = rotationAngle * (M_PI / 180);

    // Calculate result
    double x = vector.first * cos(angleRadians) + vector.second * sin(angleRadians);
    double y = -vector.first * sin(angleRadians) + vector.second * cos(angleRadians);

    std::pair<double, double> result{x, y};
    return result;
}

std::vector<std::pair<double, double>> generateDirections(Camera cam, int numDirs) {

    std::pair<double, double> currentVector = rotateVector(cam.getDirection(), -cam.getOpeningAngle() / 2);
    double division = cam.getOpeningAngle() < 360 ? numDirs - 1 : numDirs;
    std::vector<std::pair<double, double>> result{};
    for(int i = 0; i < numDirs; i++){
        result.push_back(currentVector);
        currentVector = rotateVector(currentVector, cam.getOpeningAngle() / division);
    }
    return result;
}

std::vector<std::pair<int, int>> Visualizer::setCameraView(Camera& camera) {
    // Compute the center of the pixel that the rays are going to be cast from
    std::pair<double, double> center = getMiddle(camera.getPosition().x, camera.getPosition().y);
    std::vector<std::pair<int, int>> result{};

    std::vector<std::pair<double, double>> dirs = generateDirections(camera, 2);
    Pixel::Coordinate rayPixel{0, 0};
    for(auto direction : dirs){
        // Cast ray
        std::vector<Pixel::Coordinate> rayPixels = castRayDir(center.first, center.second, direction.first, direction.second);

        // Go through ray and add visible pixels until an obstacle is hit.
        for(int j = 1; j < rayPixels.size(); j++){
            // Get current pixel
            rayPixel = rayPixels[j];

            // Check if a pixel should be added, ending loop if an object has been hit
            if(image.getPixelType(rayPixel) == Pixel::INTERIOR){
                break; // should not happen, given that the input is formatted correctly
            }
            if(image.getPixelType(rayPixel) == Pixel::SURFACE){
                result.emplace_back(rayPixel.x, rayPixel.y);
                break;
            }
        }
        if(image.getPixelType(rayPixel) == Pixel::EMPTY_SPACE){
            result.emplace_back(rayPixels[rayPixels.size() - 1].x, rayPixels[rayPixels.size() - 1].y );
        }

    }
    return result;
}

Pixel::Coordinate Visualizer::getGridCoordinate(double x, double y) {
    return Pixel::Coordinate{static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y))};
}

std::vector<Pixel::Coordinate> Visualizer::castRayDir(double xStart, double yStart, double xDir, double yDir) {
    // DDA
    double d = sqrt(pow(xDir, 2) + pow(yDir, 2));
    xDir = xDir / d;
    yDir = yDir / d;

    // Calculate the unit step size vector (How much along the ray do I need to go to march length one along the x or y-axis).
    double unitStepSizeX = sqrt(1 + pow(yDir / xDir, 2));
    double unitStepSizeY = sqrt(1 + pow(xDir / yDir, 2));

    // Get starting pixel
    Pixel::Coordinate currentGridCoordinate = getGridCoordinate(xStart, yStart);

    // Length of the ray that goes towards the next intersection in the x or y direction
    double currentRayLengthX;
    double currentRayLengthY;

    // General direction of the ray (up / down / left / right)
    int stepX = xDir < 0 ? -1 : 1;
    int stepY = yDir < 0 ? -1 : 1;

    // Find the intersection from the starting point to the edge of the current cell
    // Ray goes from right to left
    if(stepX < 0){
        currentRayLengthX = (xStart - currentGridCoordinate.x ) * unitStepSizeX;
    }
        // Ray goes from left to right
    else{
        currentRayLengthX = (currentGridCoordinate.x + 1 - xStart) * unitStepSizeX;
    }
    // Ray goes upwards
    if(stepY < 0){
        currentRayLengthY = (yStart - currentGridCoordinate.y) * unitStepSizeY;
    }
        // Ray goes downwards
    else{
        currentRayLengthY = (currentGridCoordinate.y + 1 - yStart) * unitStepSizeY;
    }

    bool obstacleHit = false;
    std::vector<Pixel::Coordinate> intersectedPixels{};
    while(image.isWithin(currentGridCoordinate)){
        // Add the current pixel
        intersectedPixels.push_back(currentGridCoordinate);

        // Determine if we should walk in the x or y direction and update the current pixel
        if(currentRayLengthX < currentRayLengthY){
            currentGridCoordinate.x += stepX;
            currentRayLengthX += unitStepSizeX;
        }
        else{
            currentGridCoordinate.y += stepY;
            currentRayLengthY += unitStepSizeY;
        }
    }

    return intersectedPixels;
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

void Visualizer::renderGrid() {
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            SDL_Rect cellRect = { x * cellSize, y * cellSize, cellSize, cellSize };
            if (image.getPixelType(x, y) != Pixel::EMPTY_SPACE) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for objects
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for air
            }
            SDL_RenderFillRect(renderer, &cellRect);

            // Draw grid lines
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cellRect);
        }
    }

    // Draw cameras and their rays
    for ( Camera& camera : cameras) {
        SDL_Rect cameraRect = { camera.getPosition().x * cellSize + cellSize / 4, camera.getPosition().y * cellSize + cellSize / 4, cellSize / 2, cellSize / 2 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for cameras
        SDL_RenderFillRect(renderer, &cameraRect);

        int x1 = camera.getPosition().x * cellSize + cellSize / 2;
        int y1 = camera.getPosition().y * cellSize + cellSize / 2;

        // TODO: get the right pixel
        int x2Left = setCameraView(camera)[0].first  * cellSize + cellSize / 2;;
        int y2Left = setCameraView(camera)[0].second * cellSize + cellSize / 2;;
        int x2Right = setCameraView(camera)[1].first * cellSize + cellSize / 2;;
        int y2Right = setCameraView(camera)[1].second * cellSize + cellSize / 2;;

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for rays
        SDL_RenderDrawLine(renderer, x1, y1, x2Left, y2Left);
        SDL_RenderDrawLine(renderer, x1, y1, x2Right, y2Right);
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
                    // Save screenshot when 's' key is pressed
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

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include "Pixel.h"

/**
 * @brief Stores an image of pixels
 */
class Image {
public:

    Image() = default;

    /**
     * @brief Indicates whether reading the file was successful (correct format, file could be opened, path valid etc).
     */
    enum Status {SUCCESS, FAILURE};

    /**
     * @brief Reads the file in the given path. The file has to be in the ssv format. Additionally, each row has to be of the same length. Possible values are: 0 - empty space, 1 - a pixel inside of the volume, 3 - a pixel on the surface of the volume.
     * @param filePath Path to the file that is supposed to be read.
     * @return Either SUCCESS if the file was read successfully. FAILURE if not.
     */
    Status readFromFile(const std::string& filePath);

    /**
     * @brief Returns the width of the image in pixels.
     * @return Width of the image in pixels.
     */
    int getWidth() const{return width;};

    /**
    * @brief Returns the height of the image in pixels.
    * @return Height of the image in pixels.
    */
    int getHeight() const{return height;};

    /**
     * @brief Returns the type of the pixel at the given location.
     * @param x X coordinate of the pixel.
     * @param y Y coordinate of the pixel.
     * @return Type of the pixel.
     */
    Pixel::PixelType getPixelType(int x, int y) const;

    /**
     * @brief Returns the type of the pixel at the given location.
     * @param coordinate Coordinate of the pixel.
     * @return Type of the pixel.
     */
    Pixel::PixelType getPixelType(Pixel::Coordinate coordinate) const;

    /**
     * @brief Returns the pixels from which the pixel at (x,y) is visible.
     * @param x X coordinate of the pixel.
     * @param y Y coordinate of the pixel.
     * @return Pixels from which the pixel can be seen.
     */
    std::set<Pixel::Coordinate> getVisiblePixels(int x, int y);

    /**
     * @brief Sets the visible pixels of the pixel at the given coordinates.
     * @param coordinate The coordinate of the pixel.
     * @param visiblePixels Pixels from which the pixel can be seen.
     */
    void addVisiblePixels(Pixel::Coordinate coordinate, const std::vector<Pixel::Coordinate>& visiblePixels);

    /**
     * @brief Sets the visible pixels of the pixel at the given coordinates.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param visiblePixels Pixels from which the pixel can be seen.
     */
    void addVisiblePixels(int x, int y, const std::vector<Pixel::Coordinate>& visiblePixels);

    /**
     * @brief Return the coordinates of all surface pixels.
     * @return Coordinates of all surface pixels.
     */
    std::vector<Pixel::Coordinate> getSurfacePixels();

private:

    /**
     * @brief The pixels of the image.
     */
    std::vector<Pixel> pixels;

    /**
     * @brief Height of the image in pixels.
     */
    int height{};

    /**
     * @brief Width of the image in pixels.
     */
    int width{};

    /**
     * @brief Transforms the coordinates into an index of the stored pixels vector.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @return Corresponding index in the pixels vector.
     */
    int getIndex(int x, int y) const {return y * width + x;};

};


#endif //IMAGE_H

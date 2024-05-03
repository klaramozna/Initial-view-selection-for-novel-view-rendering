#ifndef PIXEL_H
#define PIXEL_H


#include <vector>

/**
 * @brief Represents a pixel. Each pixel contains information about its relationship to the volume as well as the pixels that it can be seen from.
 */
class Pixel {
public:

    /**
     * @brief Type of the pixel. EMPTY_SPACE - pixel that is not a part of the volume, INTERIOR - pixel inside of the volume, SURFACE - pixel on the surface of the volume.
     */
    enum PixelType {EMPTY_SPACE, INTERIOR, SURFACE};

    /**
     * @brief Creates a pixel of the given type.
     * @param type Type of the pixel.
     */
    explicit Pixel(PixelType type): type{type}, seenFrom{}{};

    /**
     * @brief Returns the type of the pixel.
     * @return Type of the pixel.
     */
    PixelType getType(){return type;}

    /**
     * @brief Represents 2d coordinates.
     */
    struct Coordinate{
        int x;
        int y;
    };

private:

    /**
     * @brief Type of the pixel (either space, a pixel inside of the volume or a pixel on the surface if the volume).
     */
    PixelType type;

    /**
     * @brief Indices of pixels from which this pixel can be seen.
     */
    std::vector<Coordinate> seenFrom;
};


#endif //PIXEL_H

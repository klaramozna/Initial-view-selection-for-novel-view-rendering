#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "Pixel.h"

/**
 * @brief Stores an image of pixels
 */
class Image {
public:
    /**
     * @brief Creates an image with the given pixels.Each "inner" vector is interpreted as a row. It is assumed that all rows are of the same length.
     * @param pixels Pixels to be stored.
     */
    Image(const std::vector<std::vector<Pixel>>& pixels);

private:

    /**
     * @brief The pixels of the image.
     */
    std::vector<Pixel> pixels;

    /**
     * @brief Height of the image in pixels.
     */
    int height;

    /**
     * @brief Width of the image in pixels.
     */
    int width;



};


#endif //IMAGE_H

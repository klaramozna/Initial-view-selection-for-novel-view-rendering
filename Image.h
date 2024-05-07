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

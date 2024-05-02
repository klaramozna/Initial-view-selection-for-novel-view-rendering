#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
#include <vector>
#include "Pixel.h"


/**
 * @brief Reads a ssv file amd stores the read pixels in a two-dimensional vector.
 */
class InputHandler {
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
    Status readFile(const std::string& filePath);

    /**
     * @brief Returns the pixels that were previously read from a file. If the function readFile was not called before or if it was unsuccessful, an empty vector is returned.
     * @return Vector of pixels previously read from a file.
     */
    std::vector<std::vector<Pixel>> getPixels();

private:
    /**
     * @brief If a readFile was called previously, indicates whether the operation was successful.
     */
    Status status;

    /**
     * @brief Grid of pixels read from a file.
     */
    std::vector<std::vector<Pixel>> pixels;
};


#endif //INPUTHANDLER_H

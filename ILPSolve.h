#ifndef INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_ILPSOLVE_H
#define INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_ILPSOLVE_H

#include "Camera.h"
#include "Image.h"
#include <coin/ClpSimplex.hpp>
#include <coin/OsiClpSolverInterface.hpp>
#include <coin/CbcModel.hpp>
#include <coin/CbcHeuristic.hpp>
#include <coin/CbcCutGenerator.hpp>
#include <coin/CbcEventHandler.hpp>

class ILPSolve {
public:

    ILPSolve(std::vector<Camera> cameras, Image im): cams{cameras}, image{im}{};

    ILPSolve() = default;

    /**
     * @brief Returns the cameras such that they "see" all surface pixels. The number of cameras is guaranteed to be minimal.
     * @return
     */
    std::vector<Camera> solve();

    void setCameras(std::vector<Camera> cameras){cams = cameras;};
    void setImage(Image im){image = im;};

private:

    /**
     * @brief Adds the constrains to the solver (each pixel has to be seen at least once)
     * @param solver Solver to add the constraints to
     * @param coverage Sets of pixels that each camera "sees".
     */
    void addConstraints(OsiClpSolverInterface &solver);

    Image image;

    std::vector<Camera> cams;
};


#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_ILPSOLVE_H

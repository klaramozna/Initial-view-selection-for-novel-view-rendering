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

class ILPSolveMulti {
public:

    ILPSolveMulti(std::vector<Camera> cameras, Image im, int minCoverage): cams{cameras}, image{im}, minCoverage{minCoverage} {}

    ILPSolveMulti() = default;

    /**
     * @brief Returns the cameras such that each surface pixel is covered at least minCoverage times.
     * @return Vector of cameras
     */
    std::vector<Camera> solve();

    void setCameras(std::vector<Camera> cameras) { cams = cameras; }
    void setImage(Image im) { image = im; }

private:

    /**
     * @brief Adds the constraints to the solver (each surface pixel has to be seen at least minCoverage times).
     * @param solver Solver to add the constraints to
     */
    void addConstraints(OsiClpSolverInterface &solver);

    Image image;
    std::vector<Camera> cams;
    int minCoverage; // Minimum number of times each surface pixel must be covered
};

#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_ILPSOLVE_H

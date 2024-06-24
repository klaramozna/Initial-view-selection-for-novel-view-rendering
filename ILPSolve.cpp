#include "ILPSolve.h"

void ILPSolve::addConstraints(OsiClpSolverInterface &solver) {
    for(int x = 0; x < image.getWidth(); x++){
        for(int y = 0; y < image.getHeight(); y++){
            if(image.getPixelType(x, y) == Pixel::SURFACE){
                // Create a constraint that ensures each pixel is covered by at least one camera
                std::vector<int> indices; // indices representing the cameras
                std::vector<double> coefficients;

                for (int i = 0; i < cams.size(); i++) {
                    if (cams[i].getVisibleSurfacePixels().count({x,y}) >= 1) {
                        indices.push_back(i);
                        coefficients.push_back(1.0);
                    }
                }

                // Add the constraint to the solver
                solver.addRow(indices.size(), indices.data(), coefficients.data(), 1.0, solver.getInfinity());
            }
        }
    }
}

class MyMessageHandler : public CoinMessageHandler {
public:
    int print() override { return 0; } // Suppress all messages
};

std::vector<Camera> ILPSolve::solve() {
    OsiClpSolverInterface solver;

    // Add variables to the solver (one for each camera)
    solver.setObjSense(1.0); // Set the solver to minimize the objective function
    for (int i = 0; i < cams.size(); ++i) {
        double coefficient = 1.0;
        // 0 represents a camera not being selected. 1 represents a camera being selected.
        double lowerBound = 0.0;
        double upperBound = 1.0;

        // This will be added later by addConstraints
        double* elements = nullptr;
        int* indices = nullptr;
        int numElems = 0;
        solver.addCol(numElems, indices, elements, lowerBound, upperBound, coefficient);
        solver.setInteger(i);
    }

    // Add constraints to ensure all pixels are covered
    addConstraints(solver);

    // Create the CBC model
    CbcModel model(solver);

    // Turn off messages
    model.passInMessageHandler(new MyMessageHandler());

    // Solve the problem
    model.branchAndBound();

    // Get the solution
    const double *solution = model.bestSolution();

    if(!model.isProvenOptimal() || solution == nullptr){
        return{};
    }


    // Output the solution
    std::vector<Camera> result{};
    for(int i = 0; i < cams.size(); i++){
        if(solution[i] == 1){
            result.push_back(cams[i]);
        }
        else if(solution[i] != 0){
            std::cout << "non integer val" << std::endl;
            return{};
        }
    }
    return result;
}

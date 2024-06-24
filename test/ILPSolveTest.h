#ifndef INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_ILPSOLVETEST_H
#define INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_ILPSOLVETEST_H

#include <gtest/gtest.h>
#include "../ILPSolve.h"

class ILPSolveTest : public testing::Test{
protected:
    ILPSolve solver;
    Image image3;
    void SetUp() override;
    ILPSolveTest() = default;
};


#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_ILPSOLVETEST_H

#ifndef INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_PLACEMENTFIND1TEST_H
#define INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_PLACEMENTFIND1TEST_H

#include <gtest/gtest.h>
#include "../PlacementFind1.h"
#include "../Image.h"

class PlacementFind1Test : public testing::Test{
protected:
    PlacementFind1 placementFinder;
    Image image3;
    void SetUp() override;
    PlacementFind1Test() = default;
};


#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_PLACEMENTFIND1TEST_H

#ifndef INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDERTEST_H
#define INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDERTEST_H

#include <gtest/gtest.h>
#include "../CameraPlacementFinder.h"
#include "../Image.h"

class CameraPlacementFinderTest : public testing::Test{
protected:
    CameraPlacementFinder placementFinder;
    Image image3;
    void SetUp() override;
    CameraPlacementFinderTest() = default;
};


#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAPLACEMENTFINDERTEST_H

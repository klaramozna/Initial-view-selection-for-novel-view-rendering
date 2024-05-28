#ifndef INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAGENERATORTEST_H
#define INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAGENERATORTEST_H

#include <gtest/gtest.h>
#include "../CameraGenerator.h"

class CameraGeneratorTest : public testing::Test{
protected:
    Image image0;
    void compareOutputs(std::vector<Camera> correct, std::vector<Camera> realAnswer);
};


#endif //INITIAL_VIEW_SELECTION_FOR_NOVEL_VIEW_RENDERING_CAMERAGENERATORTEST_H

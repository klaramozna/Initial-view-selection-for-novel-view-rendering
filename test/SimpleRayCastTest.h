#ifndef SIMPLERAYCASTTEST_H
#define SIMPLERAYCASTTEST_H

#include <gtest/gtest.h>
#include "../Image.h"
#include "../RayCaster.h"
#include <memory>

class SimpleRayCastTest : public testing::Test{
protected:
    std::shared_ptr<Image> testImage0;
    std::shared_ptr<Image> testImage1;
    RayCaster rayCast;
    void SetUp() override;
    void printSetDifference(const std::set<Pixel::Coordinate>& a, const std::set<Pixel::Coordinate>& b);
    SimpleRayCastTest() : testImage0(std::make_shared<Image>()), testImage1(std::make_shared<Image>()) {}
};


#endif //SIMPLERAYCASTTEST_H

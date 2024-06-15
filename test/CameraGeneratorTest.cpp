#include "CameraGeneratorTest.h"

TEST_F(CameraGeneratorTest, oneCamPerDir){
    image0.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input2.ssv");
    std::shared_ptr<Image> im = std::make_shared<Image>(image0);
    RayCaster rayCaster{im, 50};
    CameraGenerator generator{1, 47, image0, rayCaster};

    // Create correct answer
    std::vector<Camera> cameras{};
    for(int x = 0; x < image0.getWidth(); x++){
        for(int y = 0; y < image0.getHeight(); y++){
            if(image0.getPixelType(x, y) == Pixel::EMPTY_SPACE){
                Camera cam{Pixel::Coordinate{x, y}, std::pair<double, double>{1, 0}, 47};
                cameras.push_back(cam);
            }
        }
    }

    compareOutputs(cameras, generator.generateCameras());
    ASSERT_EQ(cameras, generator.generateCameras());
}

TEST_F(CameraGeneratorTest, twoCamsPerDir){
    image0.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input2.ssv");
    std::shared_ptr<Image> im = std::make_shared<Image>(image0);
    RayCaster rayCaster{im, 50};
    CameraGenerator generator{2, 47, image0, rayCaster};

    // Create correct answer
    std::vector<Camera> cameras{};
    for(int x = 0; x < image0.getWidth(); x++){
        for(int y = 0; y < image0.getHeight(); y++){
            if(image0.getPixelType(x, y) == Pixel::EMPTY_SPACE){
                Camera cam1{Pixel::Coordinate{x, y}, std::pair<double, double>{1, 0}, 47};
                cameras.push_back(cam1);
                Camera cam2{Pixel::Coordinate{x, y}, std::pair<double, double>{-1, 0}, 47};
                cameras.push_back(cam2);
            }
        }
    }

    compareOutputs(cameras, generator.generateCameras());
    ASSERT_EQ(cameras, generator.generateCameras());
}

TEST_F(CameraGeneratorTest, fourCamsPerDir){
    image0.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input2.ssv");
    std::shared_ptr<Image> im = std::make_shared<Image>(image0);
    RayCaster rayCaster{im, 50};
    CameraGenerator generator{4, 47, image0, rayCaster};

    // Create correct answer
    std::vector<Camera> cameras{};
    for(int x = 0; x < image0.getWidth(); x++){
        for(int y = 0; y < image0.getHeight(); y++){
            if(image0.getPixelType(x, y) == Pixel::EMPTY_SPACE){
                Camera cam1{Pixel::Coordinate{x, y}, std::pair<double, double>{1, 0}, 47};
                cameras.push_back(cam1);
                Camera cam2{Pixel::Coordinate{x, y}, std::pair<double, double>{0, 1}, 47};
                cameras.push_back(cam2);
                Camera cam3{Pixel::Coordinate{x, y}, std::pair<double, double>{-1, 0}, 47};
                cameras.push_back(cam3);
                Camera cam4{Pixel::Coordinate{x, y}, std::pair<double, double>{0, -1}, 47};
                cameras.push_back(cam4);
            }
        }
    }

    compareOutputs(cameras, generator.generateCameras());
    ASSERT_EQ(cameras, generator.generateCameras());
}

TEST_F(CameraGeneratorTest, threeCamsPerDir){
    image0.readFromFile("/home/klara/CLionProjects/Initial-view-selection-for-novel-view-rendering/input/test_input2.ssv");
    std::shared_ptr<Image> im = std::make_shared<Image>(image0);
    RayCaster rayCaster{im, 50};
    CameraGenerator generator{3, 47, image0, rayCaster};

    // Create correct answer
    std::vector<Camera> cameras{};
    for(int x = 0; x < image0.getWidth(); x++){
        for(int y = 0; y < image0.getHeight(); y++){
            if(image0.getPixelType(x, y) == Pixel::EMPTY_SPACE){
                Camera cam1{Pixel::Coordinate{x, y}, std::pair<double, double>{1, 0}, 47};
                cameras.push_back(cam1);
                Camera cam2{Pixel::Coordinate{x, y}, std::pair<double, double>{0.86602540378, -0.5}, 47};
                cameras.push_back(cam2);
                Camera cam3{Pixel::Coordinate{x, y}, std::pair<double, double>{-1, 0}, 47};
                cameras.push_back(cam3);
            }
        }
    }
    generator.generateCameras();

    compareOutputs(cameras, generator.generateCameras());
    ASSERT_EQ(cameras, generator.generateCameras());
}


void CameraGeneratorTest::compareOutputs(std::vector<Camera> correct, std::vector<Camera> realAnswer) {
    for(int i = 0; i < correct.size(); i++){
        std::cout << "pos: (" << correct[i].getPosition().x << "," << correct[i].getPosition().y
        << ") | (" << realAnswer[i].getPosition().x << "," << realAnswer[i].getPosition().y << ")"
        << std::endl;
        std::cout << "fit: (" << correct[i].getDirection().first << "," << correct[i].getDirection().second
                     << ") | (" << realAnswer[i].getDirection().first << "," << realAnswer[i].getDirection().second << ")"
                     << std::endl;
        std::cout << "angle: " << correct[i].getOpeningAngle() << " | " << realAnswer[i].getOpeningAngle() << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
}

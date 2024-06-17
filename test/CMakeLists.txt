cmake_minimum_required(VERSION 3.28)

enable_testing()

add_executable(
        test_my_project
        ../DebugVisualize.h
        ../DebugVisualize.cpp
        ../Pixel.h
        ../Pixel.cpp
        ../Image.h
        ../Image.cpp
        ../RayCaster.h
        ../RayCaster.cpp
        ../Camera.h
        ../Camera.cpp
        ../CameraGenerator.h
        ../CameraGenerator.cpp
        ../CameraPlacementFinder.h
        ../CameraPlacementFinder.cpp
        ../PlacementFind1.h
        ../PlacementFind1.cpp
        SimpleRayCastTest.cpp
        SimpleRayCastTest.h
        CameraGeneratorTest.cpp
        CameraGeneratorTest.h
        CameraPlacementFinderTest.cpp
        CameraPlacementFinderTest.h
        PlacementFind1Test.cpp
        PlacementFind1Test.h
)

target_link_libraries(
        test_my_project
        gtest_main  # This links both gtest and gtest_main
        # my_project_lib  # Uncomment and edit if your tests need to link against your main project library
)

include(GoogleTest)
gtest_discover_tests(test_my_project)
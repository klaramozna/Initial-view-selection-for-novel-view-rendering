cmake_minimum_required(VERSION 3.28)

enable_testing()

# Set the path to Coin-OR installation (adjust paths as per your installation)
set(COINOR_INCLUDE_DIR /usr/include/coin)
set(COINOR_LIB_DIR /usr/lib/x86_64-linux-gnu)  # or /usr/lib/ if not on a 64-bit system

# Add include directories
include_directories(${COINOR_INCLUDE_DIR})

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
        ../ILPSolve.h
        ../ILPSolve.cpp
        SimpleRayCastTest.cpp
        SimpleRayCastTest.h
        CameraGeneratorTest.cpp
        CameraGeneratorTest.h
        CameraPlacementFinderTest.cpp
        CameraPlacementFinderTest.h
        PlacementFind1Test.cpp
        PlacementFind1Test.h
        ILPSolveTest.cpp
        ILPSolveTest.h
)

target_link_libraries(
        test_my_project
        gtest_main  # This links both gtest and gtest_main
        # my_project_lib  # Uncomment and edit if your tests need to link against your main project library
        ${COINOR_LIB_DIR}/libClp.so
        ${COINOR_LIB_DIR}/libCbc.so
        ${COINOR_LIB_DIR}/libOsi.so
        ${COINOR_LIB_DIR}/libOsiClp.so
        ${COINOR_LIB_DIR}/libCgl.so
        ${COINOR_LIB_DIR}/libCoinUtils.so
)

include(GoogleTest)
gtest_discover_tests(test_my_project)
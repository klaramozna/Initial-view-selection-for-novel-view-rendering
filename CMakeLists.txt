cmake_minimum_required(VERSION 3.28)
project(Initial_view_selection_for_novel_view_rendering)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0  # Specify a commit, tag, or branch
)

FetchContent_MakeAvailable(googletest)

# Set the path to Coin-OR installation (adjust paths as per your installation)
set(COINOR_INCLUDE_DIR /usr/include/coin)
set(COINOR_LIB_DIR /usr/lib/x86_64-linux-gnu)  # or /usr/lib/ if not on a 64-bit system

# Find SDL2 library
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add include directories
include_directories(${COINOR_INCLUDE_DIR})

add_executable(Initial_view_selection_for_novel_view_rendering
        main.cpp
        Pixel.cpp
        Pixel.h
        Image.cpp
        Image.h
        RayCaster.cpp
        RayCaster.h
        DebugVisualize.cpp
        DebugVisualize.h
        Camera.cpp
        Camera.h
        CameraGenerator.cpp
        CameraGenerator.h
        CameraPlacementFinder.cpp
        CameraPlacementFinder.h
        PlacementFind1.cpp
        PlacementFind1.h
        ILPSolve.cpp
        ILPSolve.h
        ILPSolve.cpp
        Visualizer.cpp
        Visualizer.h
        ILPSolveMulti.cpp
        ILPSolveMulti.h
)
# Link Coin-OR libraries
target_link_libraries(Initial_view_selection_for_novel_view_rendering
        ${COINOR_LIB_DIR}/libClp.so
        ${COINOR_LIB_DIR}/libCbc.so
        ${COINOR_LIB_DIR}/libOsi.so
        ${COINOR_LIB_DIR}/libOsiClp.so
        ${COINOR_LIB_DIR}/libCgl.so
        ${COINOR_LIB_DIR}/libCoinUtils.so
        ${SDL2_LIBRARIES}
        # Add other required Coin-OR libraries here if any
)

add_subdirectory(test)


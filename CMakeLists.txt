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
)

add_subdirectory(test)


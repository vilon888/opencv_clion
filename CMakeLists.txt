cmake_minimum_required(VERSION 3.5)
project(opencv_clion)

# add OpenCV_DIR to find OpenCVConfig.cmake and OpenCVConfig-version.cmake
set(OpenCV_DIR "/home/vilon_tao/Projects/cv/opencv/cmake-build-debug")
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
add_executable(opencv_clion ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv_clion ${OpenCV_LIBS})
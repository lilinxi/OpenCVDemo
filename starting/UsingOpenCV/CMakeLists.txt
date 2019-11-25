cmake_minimum_required(VERSION 3.14)
project(UsingOpenCV)

#OpenCV 4.x+ requires enabled C++11 support
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_DIRS})

add_executable(UsingOpenCV UsingOpenCV.cpp)
target_link_libraries(UsingOpenCV ${OpenCV_LIBS})

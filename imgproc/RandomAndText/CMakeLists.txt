#https://github.com/opencv/opencv/blob/master/samples/cpp/example_cmake/CMakeLists.txt

cmake_minimum_required(VERSION 3.14)
project(RandomAndText)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(RandomAndText RandomAndText.cpp)
target_link_libraries(RandomAndText LINK_PRIVATE ${OpenCV_LIBS})

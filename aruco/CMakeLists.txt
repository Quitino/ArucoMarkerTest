cmake_minimum_required(VERSION 2.8.3)
project(aruco)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 3 REQUIRED)
include_directories(
    ${PROJECT_SOURCE_DIR} 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/opencv2
    ${CMAKE_CURRENT_BINARY_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

file(GLOB_RECURSE ARUCO_SRCS "${PROJECT_SOURCE_DIR}/src/*.cc"
                              "${PROJECT_SOURCE_DIR}/src/*.cpp")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(aruco SHARED ${ARUCO_SRCS})
target_link_libraries(aruco ${OpenCV_LIB})

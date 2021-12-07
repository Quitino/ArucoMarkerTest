cmake_minimum_required(VERSION 3.0)

project(aruco_test)

SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-g)

# set(Aruco_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/aruco/include/opencv2/)
# set(Aruco_LIBS ${PROJECT_SOURCE_DIR}/auco/lib/libaruco.so)

include_directories( "/usr/include/eigen3" )


# SET(OpenCV_DIR /usr/local/opencv-3.1.0/share/OpenCV) 
# SET(OpenCV_INCLUDE_DIRS /usr/local/opencv-3.1.0/include) 
# SET(OpenCV_LIBRARIES /usr/local/opencv-3.1.0/lib)
find_package(OpenCV 3.4.15 REQUIRED)
# find_package(aruco REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    # ${aruco_INCLUDE_DIRS}
    # ${aruco_INCLUDE_DIRS}/aruco
)

add_executable(aruco_test
aruco_test.cpp
        )
target_link_libraries(aruco_test
${OpenCV_LIBRARIES}
# ${aruco_LIBS}
)





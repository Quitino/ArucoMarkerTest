cmake_minimum_required(VERSION 3.0)

project(aruco_test)

SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-g)

# find_package(OpenCV 3 REQUIRED)
# if(OpenCV_FOUND)
#     message(STATUS "OpenCV Found")
# endif(OpenCV_FOUND)


# set(Aruco_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/aruco/include/opencv2/)
# set(Aruco_LIBS ${PROJECT_SOURCE_DIR}/auco/lib/libaruco.so)

include_directories( "/usr/include/eigen3" )


SET(OpenCV_DIR /usr/local/opencv-3.1.0/share/OpenCV) 
SET(OpenCV_INCLUDE_DIRS /usr/local/opencv-3.1.0/include) 
SET(OpenCV_LIBRARIES /usr/local/opencv-3.1.0/lib)
find_package(OpenCV 3.1.0 REQUIRED)
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



# cmake_minimum_required( VERSION 2.8 )
# project( useEigen )

# set( CMAKE_BUILD_TYPE "Release" )
# set( CMAKE_CXX_FLAGS "-O3" )

# # 添加Eigen头文件
# include_directories( "/usr/include/eigen3" )

# # in osx and brew install
# # include_directories( /usr/local/Cellar/eigen/3.3.3/include/eigen3 )
# # eigen 是现编译的 没有调用 动态链接库
# add_executable( eigenMatrix eigenMatrix.cpp )





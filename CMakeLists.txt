cmake_minimum_required(VERSION 2.8.3)
project(kalman_filter_pos)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Eigen3 3.0.1 REQUIRED)

set(source
    src/main.cpp
    src/robot.cpp
    src/engine.cpp
    include/engine.h
    include/robot.h)

set(libraries GL GLU glut)

include_directories(${EIGEN3_INCLUDE_DIR}
                    include)

add_executable(kalman_filter_pos ${source})
target_link_libraries(kalman_filter_pos ${libraries})


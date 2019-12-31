cmake_minimum_required(VERSION 3.1) # setting this is required
project(yolov3-trt)            # this sets the project name



add_executable(yolov3-trt samples/sample_detector.cpp)


set(CMAKE_CXX_COMPILIER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-write-strings")

LINK_DIRECTORIES(${CMAKE_BINARY_DIR})
message(STATUS "${CMAKE_BINARY_DIR}")
message(STATUS "${CMAKE_SOURCE_DIR}")

add_library(detector SHARED IMPORTED)
set_target_properties(detector PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libdetector.so)

find_package(OpenCV REQUIRED)


target_include_directories(yolov3-trt PRIVATE modules/ ./)
					  
target_link_libraries(yolov3-trt detector opencv_core opencv_calib3d opencv_dnn)






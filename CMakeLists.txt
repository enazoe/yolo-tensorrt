cmake_minimum_required(VERSION 3.1) 
project(yolo-trt VERSION 1.0)   
set(CMAKE_CUDA_COMPILE "/usr/loacl/cuda/bin/nvcc")         
enable_language(CUDA)

set(CMAKE_CXX_COMPILIER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -Wno-write-strings")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")

#cuda
#export PATH=/usr/local/cuda-11.0/bin:$PATH
#include_directories(/usr/local/cuda/include)
#link_directories(/usr/local/cuda/lib64)
find_package(CUDA REQUIRED)

#opencv
#set(OpenCV_DIR /opt/opencv-4.1.2/share/OpenCV)
find_package(OpenCV REQUIRED)

#detector lib (cuda)
file(GLOB_RECURSE sources modules/*.hpp modules/*.cpp modules/*.h modules/*.cu extra/*.h)
add_library(detector SHARED ${sources})
target_include_directories(detector PRIVATE extra/ modules/ ${OpenCV_INCLUDE_DIRS} ${CUDA_TOOLKIT_ROOT_DIR}/include)
target_link_libraries(detector nvinfer nvinfer_plugin nvparsers "stdc++fs")

#sample
add_executable(yolo-trt samples/sample_detector.cpp)				  
target_include_directories(yolo-trt PRIVATE modules/ extra/)
target_link_libraries(yolo-trt detector ${OpenCV_LIBS})




cmake_minimum_required(VERSION 3.1) 
project(yolov3-trt)            

file(GLOB_RECURSE sources     	modules/*.hpp modules/*.cpp modules/*.h modules/*.cu extra/*.h)

find_Package(gflags REQUIRED)

find_package(OpenCV 3.4 REQUIRED)
if(gflags_FOUND)
message("-- gflags found")
endif()

set(CMAKE_CXX_COMPILIER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-write-strings -O3 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")

#cudaS
find_package(CUDA REQUIRED)
include_directories(/home/xuhao/source/TensorRT-5.1.5.0/include extra)
link_directories(/home/xuhao/source/TensorRT-5.1.5.0/lib)

message("-- CUDA version:$(CUDA_VERSION)")

if(CUDA_VERSION_MAJOR GREATER 9)
	message("-- CUDA ${CUDA_VERSION_MAJOR} detected")
	set(
		CUDA_NVCC_FLAGS
		${CUDA_NVCC_FLAGS}; 
		# -gencode arch=compute_61,code=sm_61
	)
find_package(OpenCV REQUIRED)
endif()

add_executable(yolov3-trt samples/sample_detector.cpp)

cuda_add_library(detector SHARED ${sources})
target_include_directories(detector PRIVATE modules/ ${CUDA_TOOLKIT_ROOT_DIR}/include  ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
target_include_directories(yolov3-trt PRIVATE modules/ extra/)
target_link_libraries(detector nvinfer nvinfer_plugin nvcaffe_parser gflags "stdc++fs")

if(CUDA_VERSION_MAJOR GREATER 9)
	target_link_libraries(yolov3-trt detector opencv_core opencv_calib3d opencv_dnn opencv_highgui)
endif()






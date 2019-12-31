cmake_minimum_required(VERSION 3.1) 
project(yolov3-trt)            

file(GLOB_RECURSE sources     	modules/*.hpp modules/*.cpp modules/*.h modules/*.cu extra/*.h)
add_executable(yolov3-trt samples/sample_detector.cpp)

find_Package(gflags REQUIRED)

if(gflags_FOUND)
message("-- gflags found")
endif()

set(CMAKE_CXX_COMPILIER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-write-strings")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")

#cudaS
find_package(CUDA REQUIRED)

message("-- CUDA version:$(CUDA_VERSION)")

if(CUDA_VERSION_MAJOR GREATER 9)
	message("-- CUDA ${CUDA_VERSION_MAJOR} detected")
	set(
		CUDA_NVCC_FLAGS
		${CUDA_NVCC_FLAGS}; 
		-gencode arch=compute_53,code=sm_53
	)
find_package(OpenCV REQUIRED)
endif()


cuda_add_library(detector SHARED ${sources})
target_include_directories(detector PRIVATE modules/ D:/dependency/gflag/include ${CUDA_TOOLKIT_ROOT_DIR}/include D:/dependency/TensorRT-5.1.5.0_cuda-10.0_cudnn-7.5/include D:/dependency/OPENCV341/include extra/ ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

target_include_directories(yolov3-trt PRIVATE modules/ extra/)
target_link_libraries(detector nvinfer nvinfer_plugin nvcaffe_parser gflags "stdc++fs")
				  
if(CUDA_VERSION_MAJOR GREATER 9)
	target_link_libraries(yolov3-trt detector opencv_core opencv_calib3d opencv_dnn)
endif()






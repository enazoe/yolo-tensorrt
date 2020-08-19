//sys
#include <cmath>
#include <stdio.h>
#include <cassert>
#include <iostream>
#include <cuda_runtime.h>
//my
#include "detect.h"

#define NV_CUDA_CHECK(status)                                                                      \
    {                                                                                              \
        if (status != 0)                                                                           \
        {                                                                                          \
            std::cout << "Cuda failure: " << cudaGetErrorString(status) << " in file " << __FILE__ \
                      << " at line " << __LINE__ << std::endl;                                     \
            abort();                                                                               \
        }                                                                                          \
    }

namespace nvinfer1
{
	

}//end namespace nvinfer1

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
	Detect::Detect(const void* data, size_t length)
	{

	}

	Detect::Detect(const uint32_t &n_anchor_, const uint32_t &n_classes_,
		const uint32_t &n_grid_h_, const uint32_t &n_grid_w_):
		_n_anchor(n_anchor_),
		_n_classes(n_classes_),
		_n_grid_h(n_grid_h_),
		_n_grid_w(n_grid_w_)
	{
		_n_output_size = (5 + _n_classes)*_n_anchor*_n_grid_h*_n_grid_w;
	}
	Detect::~Detect()
	{}

	int Detect::enqueue(int batchSize, const void* const* inputs, void** outputs, void* workspace,
		cudaStream_t stream)
	{
		return 0;
	}

	size_t Detect::getSerializationSize() const
	{
		return sizeof(_n_anchor) + sizeof(_n_classes) + sizeof(_n_grid_h) + sizeof(_n_grid_w) + sizeof(_n_output_size);
	}

	void Detect::serialize(void *buffer) const
	{

	}

	void Detect::configurePlugin(const PluginTensorDesc* in, int nbInput, const PluginTensorDesc* out, int nbOutput) override
	{

	}
	IPluginV2IOExt* Detect::clone() const
	{
		Detect *p = new Detect(_n_anchor,_n_classes,_n_grid_h,_n_grid_w);
		p->setPluginNamespace(_s_plugin_namespace.c_str());
		return p;
	}
}//end namespace nvinfer1

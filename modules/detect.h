#ifndef _DETECT_H_
#define _DETECT_H_

#include <string>
#include <vector>
#include "NvInfer.h"

namespace nvinfer1
{
	class Detect :public IPluginV2IOExt
	{
	public:
		Detect();
		~Detect();
		int getNbOutputs()const override;
		Dims getOutputDimensions(int index, const Dims* inputs, int nbInputDims) override;
		int initialize() override;
		void terminate() override;
		size_t getWorkspaceSize(int maxBatchSize) const override;
		int enqueue(int batchSize, const void* const* inputs, void** outputs, void* workspace, cudaStream_t stream)override;
		size_t getSerializationSize() const override;
		void serialize(void* buffer) const override;
		const char* getPluginType() const override;
		const char* getPluginVersion() const override;
		void destroy() override;
		void setPluginNamespace(const char* pluginNamespace) override;
		const char* getPluginNamespace() const override;
		DataType getOutputDataType(int index, const nvinfer1::DataType* inputTypes, int nbInputs) const override;
		bool isOutputBroadcastAcrossBatch(int outputIndex, const bool* inputIsBroadcasted, int nbInputs) const override;
		bool canBroadcastInputAcrossBatch(int inputIndex) const override;
		void attachToContext(
			cudnnContext* cudnnContext, cublasContext* cublasContext, IGpuAllocator* gpuAllocator) override;
		void configurePlugin(const PluginTensorDesc* in, int nbInput, const PluginTensorDesc* out, int nbOutput) override;
		void detachFromContext() override;
		bool supportsFormatCombination(int pos, const PluginTensorDesc* inOut, int nbInputs, int nbOutputs) const override
		{
			return inOut[pos].format == TensorFormat::kLINEAR && inOut[pos].type == DataType::kFLOAT;
		}
		IPluginV2IOExt* clone() const override;
	private:

	}; //end detect

	class DetectPluginCreator : public IPluginCreator
	{
	public:
		DetectPluginCreator();
		~DetectPluginCreator() override = default;
		const char* getPluginName()const override;
		const char* getPluginVersion() const override;
		const PluginFieldCollection* getFieldNames() override;
		IPluginV2IOExt* createPlugin(const char* name, const PluginFieldCollection* fc) override;
		IPluginV2IOExt* deserializePlugin(const char* name, const void* serialData, size_t serialLength) override;
		void setPluginNamespace(const char* libNamespace) override;
		const char* getPluginNamespace() const override;
	private:
		static PluginFieldCollection _fc;
		static std::vector<PluginField> _vec_plugin_attributes;
	};//end detect creator

}//end namespace nvinfer1



#endif

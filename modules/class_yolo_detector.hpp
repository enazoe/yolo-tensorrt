#ifndef CLASS_YOLO_DETECTOR_HPP_
#define CLASS_YOLO_DETECTOR_HPP_

#include <opencv2/opencv.hpp>
#include "ds_image.h"
#include "trt_utils.h"
#include "yolo.h"
#include "yolov2.h"
#include "yolov3.h"
#include "yolov4.h"
#include "yolov5.h"

#include <experimental/filesystem>
#include <fstream>
#include <string>
#include <chrono>
#include <stdio.h>  /* defines FILENAME_MAX */

#include "class_detector.h"
#include "class_timer.hpp"
class YoloDectector
{
public:
	YoloDectector()
	{

	}
	~YoloDectector()
	{

	}

	void init(const Config &config)
	{
		_config = config;

		this->set_gpu_id(_config.gpu_id);

		this->parse_config();

		this->build_net();
	}

	void detect(const std::vector<cv::Mat>	&vec_image,
				std::vector<BatchResult> &vec_batch_result)
	{
		Timer timer;
		std::vector<DsImage> vec_ds_images;
		vec_batch_result.clear();
		vec_batch_result.resize(vec_image.size());
		for (const auto &img:vec_image)
		{
			vec_ds_images.emplace_back(img, _vec_net_type[_config.net_type], _p_net->getInputH(), _p_net->getInputW());
		}
		cv::Mat trtInput = blobFromDsImages(vec_ds_images, _p_net->getInputH(),_p_net->getInputW());
		timer.out("pre");
		_p_net->doInference(trtInput.data, vec_ds_images.size());
		timer.reset();
		for (uint32_t i = 0; i < vec_ds_images.size(); ++i)
		{
			auto curImage = vec_ds_images.at(i);
			auto binfo = _p_net->decodeDetections(i, curImage.getImageHeight(), curImage.getImageWidth());
			auto remaining = nmsAllClasses(_p_net->getNMSThresh(),
				binfo,
				_p_net->getNumClasses(),
				_vec_net_type[_config.net_type]);
			if (remaining.empty())
			{
				continue;
			}
			std::vector<Result> vec_result(0);
			for (const auto &b : remaining)
			{
				Result res;
				res.id = b.label;
				res.prob = b.prob;
				const int x = b.box.x1;
				const int y = b.box.y1;
				const int w = b.box.x2 - b.box.x1;
				const int h = b.box.y2 - b.box.y1;
				res.rect = cv::Rect(x, y, w, h);
				vec_result.push_back(res);
			}
			vec_batch_result[i] = vec_result;
		}
		timer.out("post");
	}

private:

	void set_gpu_id(const int id = 0)
	{
		cudaError_t status = cudaSetDevice(id);
		if (status != cudaSuccess)
		{
			std::cout << "gpu id :" + std::to_string(id) + " not exist !" << std::endl;
			assert(0);
		}
	}

	void parse_config()
	{
		_yolo_info.networkType = _vec_net_type[_config.net_type];
		_yolo_info.configFilePath = _config.file_model_cfg;
		_yolo_info.wtsFilePath = _config.file_model_weights;
		_yolo_info.precision = _vec_precision[_config.inference_precison];
		_yolo_info.deviceType = "kGPU";
		auto npos = _yolo_info.wtsFilePath.find(".weights");
		assert(npos != std::string::npos
			&& "wts file file not recognised. File needs to be of '.weights' format");
		_yolo_info.data_path = _yolo_info.wtsFilePath.substr(0, npos);
		_yolo_info.calibrationTablePath = _yolo_info.data_path + "-calibration.table";
		_yolo_info.inputBlobName = "data";

		_infer_param.printPerfInfo = false;
		_infer_param.printPredictionInfo = false;
		_infer_param.calibImages = _config.calibration_image_list_file_txt;
		_infer_param.calibImagesPath = "";
		_infer_param.probThresh = _config.detect_thresh;
		_infer_param.nmsThresh = 0.5;
	}

	void build_net()
	{
		if (_config.net_type == YOLOV3) 
		{
			_p_net = std::unique_ptr<Yolo>{ new YoloV3(_yolo_info, _infer_param) };
		}
		else if( _config.net_type == YOLOV4)
		{
			_p_net = std::unique_ptr<Yolo>{ new YoloV4(_yolo_info,_infer_param) };
		}
		else if (_config.net_type == YOLOV5)
		{
			_p_net = std::unique_ptr<Yolo>{ new YoloV5(_yolo_info,_infer_param) };
		}
		else
		{
			assert(false && "Unrecognised network_type.");
		}
	}

private:
	Config _config;
	NetworkInfo _yolo_info;
	InferParams _infer_param;
	std::vector<std::string> _vec_net_type{ "yolov3","yolov4","yolov5" };
	std::vector<std::string> _vec_precision{ "kINT8","kHALF","kFLOAT" };
	std::unique_ptr<Yolo> _p_net = nullptr;
	Timer _m_timer;
};


#endif

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

#include <fstream>
#include <string>
#include <chrono>
#include <stdio.h>  /* defines FILENAME_MAX */

#include "class_detector.h"
#include "class_timer.hpp"
class YoloDectector
{
public:
	YoloDectector() = default;
	~YoloDectector() = default;

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
		std::vector<DsImage> vec_ds_images;
		vec_batch_result.clear();
		if (vec_batch_result.capacity() < vec_image.size())
			vec_batch_result.reserve(vec_image.size());
		for (const auto &img:vec_image)
		{
			vec_ds_images.emplace_back(img, _vec_net_type[_config.net_type], _p_net->getInputH(), _p_net->getInputW());
		}
        blobFromDsImages(vec_ds_images, m_blob, _p_net->getInputH(),_p_net->getInputW());
        _p_net->doInference(m_blob.data, static_cast<uint32_t>(vec_ds_images.size()));
		for (size_t i = 0; i < vec_ds_images.size(); ++i)
		{
			auto curImage = vec_ds_images.at(i);
			auto binfo = _p_net->decodeDetections(static_cast<int>(i), curImage.getImageHeight(), curImage.getImageWidth());
            auto remaining = (_p_net->getNMSThresh() > 0) ? nmsAllClasses(_p_net->getNMSThresh(), binfo, _p_net->getNumClasses(), _vec_net_type[_config.net_type]) : binfo;

			std::vector<Result> vec_result;
			if (!remaining.empty())
			{
				vec_result.reserve(remaining.size());
				for (const auto &b : remaining)
				{
					const int x = cvRound(b.box.x1);
					const int y = cvRound(b.box.y1);
					const int w = cvRound(b.box.x2 - b.box.x1);
					const int h = cvRound(b.box.y2 - b.box.y1);
					vec_result.emplace_back(b.label, b.prob, cv::Rect(x, y, w, h));
				}
			}
			vec_batch_result.emplace_back(vec_result);
		}
	}

	cv::Size get_input_size() const
	{
		return cv::Size(_p_net->getInputW(), _p_net->getInputH());
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
		_infer_param.batchSize = _config.batch_size;
	}

	void build_net()
	{
		if (_config.net_type == YOLOV3)
		{
			_p_net = std::unique_ptr<Yolo>{ new YoloV3(_yolo_info, _infer_param) };
		}
		else if (_config.net_type == YOLOV4 || _config.net_type == YOLOV4_TINY)
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
	std::vector<std::string> _vec_net_type{ "yolov3", "yolov4", "yolov4-tiny", "yolov5" };
	std::vector<std::string> _vec_precision{ "kINT8","kHALF","kFLOAT" };
	std::unique_ptr<Yolo> _p_net = nullptr;
	Timer _m_timer;
    cv::Mat m_blob;
};


#endif

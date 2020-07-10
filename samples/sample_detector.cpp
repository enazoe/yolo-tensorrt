#include "class_timer.hpp"
#include "class_detector.h"

#include <memory>
#include <thread>

void thread_function(
	const Config config_,
	const cv::Mat &mat_image_,
	const int index)
{
	std::unique_ptr<Detector> detector_ = std::make_unique<Detector>();
	detector_->init(config_);
	std::vector<Result> res;
	Timer timer;
	for (;;)
	{
		timer.reset();
		detector_->detect(mat_image_, res);
		timer.out(std::to_string(index));
		/*	for (const auto &r : res)
			{
				std::cout<<index << " id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
			}*/
	}
}


int main()
{
	Config config_v3;
	config_v3.net_type = YOLOV3;
	config_v3.file_model_cfg = "../configs/yolov3.cfg";
	config_v3.file_model_weights = "../configs/yolov3.weights";
	config_v3.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config_v3.inference_precison = FP32;

	Config config_v4;
	config_v4.net_type = YOLOV4;
	config_v4.file_model_cfg = "../configs/yolov4.cfg";
	config_v4.file_model_weights = "../configs/yolov4.weights";
	config_v4.inference_precison = FP32;

	cv::Mat mat_image = cv::imread("../configs/dog.jpg", cv::IMREAD_UNCHANGED);
	std::unique_ptr<Detector> detector_ = std::make_unique<Detector>();
	detector_->init(config_v4);
	std::vector<Result> res;
	for (;;)
	{
		cv::Mat mat_temp = mat_image.clone();
		Timer timer;
		detector_->detect(mat_temp, res);
		timer.out("detect");
		for (const auto &r : res)
		{
			std::cout << "id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
			cv::rectangle(mat_temp, r.rect, cv::Scalar(255, 0, 0), 2);
		}
		cv::imshow("image", mat_temp);
		cv::waitKey(10);
	}
	cv::waitKey();
}

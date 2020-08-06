#include "class_timer.hpp"
#include "class_detector.h"

#include <memory>
#include <thread>


int main()
{
	Config config_v3;
	config_v3.net_type = YOLOV3;
	config_v3.file_model_cfg = "../configs/yolov3.cfg";
	config_v3.file_model_weights = "../configs/yolov3.weights";
	config_v3.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config_v3.inference_precison = FP32;

	Config config_v3_tiny;
	config_v3_tiny.net_type = YOLOV3_TINY;
	config_v3_tiny.detect_thresh = 0.5;
	config_v3_tiny.file_model_cfg = "../configs/yolov3-tiny.cfg";
	config_v3_tiny.file_model_weights = "../configs/yolov3-tiny.weights";
	config_v3_tiny.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config_v3_tiny.inference_precison = FP32;

	Config config_v4;
	config_v4.net_type = YOLOV4;
	config_v4.file_model_cfg = "../configs/yolov4.cfg";
	config_v4.file_model_weights = "../configs/yolov4.weights";
	config_v4.inference_precison = FP32;

	Config config_v4_tiny;
	config_v4_tiny.net_type = YOLOV4_TINY;
	config_v4_tiny.detect_thresh = 0.5;
	config_v4_tiny.file_model_cfg = "../configs/yolov4-tiny.cfg";
	config_v4_tiny.file_model_weights = "../configs/yolov4-tiny.weights";
	config_v4_tiny.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config_v4_tiny.inference_precison = FP32;

	cv::Mat mat_image = cv::imread("../configs/dog.jpg", cv::IMREAD_UNCHANGED);
	std::unique_ptr<Detector> detector(new Detector());
	detector->init(config_v4);
	std::vector<Result> res;
	Timer timer;
	for (;;)
	{
		cv::Mat mat_temp = mat_image.clone();
		timer.reset();
		detector->detect(mat_temp, res);
		timer.out("detect");
		for (const auto &r : res)
		{
			std::cout << "id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
			cv::rectangle(mat_temp, r.rect, cv::Scalar(255, 0, 0), 2);
			std::stringstream stream;
			stream<< std::fixed << std::setprecision(2)<< "id:" << r.id << "  score:"<<r.prob;
			cv::putText(mat_temp,stream.str() , cv::Point(r.rect.x, r.rect.y-5), 0, 0.5, cv::Scalar(0, 0, 255),2);
		}
		cv::imshow("image", mat_temp);
		cv::waitKey(10);
	}
	cv::waitKey();
}

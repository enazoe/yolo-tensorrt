#include <time.h>
#include "class_detector.h"

int main()
{
	Detector detector;
	Config config;
	config.file_model_cfg = "../configs/yolov3.cfg";
	config.file_model_weights = "../configs/yolov3.weights";
	config.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config.inference_precison = FP32;
	detector.init(config);

	cv::Mat mat_image = cv::imread("../configs/dog.jpg", cv::IMREAD_UNCHANGED);

	std::vector<Result> res;
	std::clock_t t_strat = std::clock();
	detector.detect(mat_image, res);
	std::cout << "detect time = " << double(std::clock() - t_strat) << "ms" << std::endl;
	for (const auto &r : res)
	{
		std::cout << "id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
		cv::rectangle(mat_image, r.rect, cv::Scalar(255, 0, 0), 2);
	}
	cv::imshow("image", mat_image);
	cv::waitKey();
	std::cin.get();
}

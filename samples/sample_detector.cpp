
#include "class_detector.h"

int main()
{
	Detector detector;
	Config config;
	config.inference_precison = FP32;
	detector.init(config);

	cv::Mat mat_image = cv::imread("data/0.jpg", cv::IMREAD_UNCHANGED);

	std::vector<Result> res;
	detector.detect(mat_image, res);

	for (const auto &r:res)
	{
		std::cout << "id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
		cv::rectangle(mat_image, r.rect, cv::Scalar(255, 0, 0), 2);
	}
	cv::imshow("image", mat_image);
	cv::waitKey();
	std::cin.get();
}

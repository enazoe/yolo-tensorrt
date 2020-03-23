#include <time.h>
#include "class_detector.h"
#include <ctime>
#include <cstdlib>
#include <chrono>

class TicToc
{
  public:
    TicToc()
    {
        tic();
    }

    void tic()
    {
        start = std::chrono::system_clock::now();
    }

    double toc()
    {
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        return elapsed_seconds.count() * 1000;
    }

  private:
    std::chrono::time_point<std::chrono::system_clock> start, end;
};

int main()
{
	Detector detector;
	Config config;
	config.file_model_cfg = "/home/xuhao/swarm_ws/src/swarm_detector/config/drone_yolov3-tiny.cfg";
	config.file_model_weights = "/home/xuhao/swarm_ws/src/swarm_detector/config/drone_yolov3-tiny.weights";
	config.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config.inference_precison = FP32;
	detector.init(config);

	cv::Mat mat_image = cv::imread("../configs/drone.jpg", cv::IMREAD_UNCHANGED);

	std::vector<Result> res;
	std::clock_t t_strat = std::clock();
	detector.detect(mat_image, res);
	std::cout << "detect time = " << double(std::clock() - t_strat) << "us" << std::endl;
	// t_strat = std::clock();
	for (int i = 0;i < 10; i ++ ) {
		TicToc tic;
		detector.detect(mat_image, res);
		std::cout << "detect time = " << double(tic.toc()) << "ms" << std::endl;
	}
	
	for (const auto &r : res)
	{
		std::cout << "id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
		cv::rectangle(mat_image, r.rect, cv::Scalar(255, 0, 0), 2);
	}
	cv::imshow("image", mat_image);
	cv::waitKey();
	std::cin.get();
}

#include "class_timer.hpp"
#include "class_detector.h"
#include "../sln/map/maputil.hpp"
#include <memory>
#include <thread>
#define runtest
//#define countMap

int main()
{
#ifdef runtest
	Config config_v3;
	config_v3.net_type = YOLOV3;
	config_v3.file_model_cfg = "../configs/yolov3.cfg";
	config_v3.file_model_weights = "../configs/yolov3.weights";
	config_v3.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config_v3.inference_precison = FP32;
	config_v3.detect_thresh = 0.5;

	Config config_v3_tiny;
	config_v3_tiny.net_type = YOLOV3_TINY;
	config_v3_tiny.detect_thresh = 0.7;
	config_v3_tiny.file_model_cfg = "../configs/yolov3-tiny.cfg";
	config_v3_tiny.file_model_weights = "../configs/yolov3-tiny.weights";
	config_v3_tiny.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config_v3_tiny.inference_precison = FP32;

	Config config_v4;
	config_v4.net_type = YOLOV4;
	config_v4.file_model_cfg = "../configs/yolov4.cfg";
	config_v4.file_model_weights = "../configs/yolov4.weights";
	config_v4.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config_v4.inference_precison = INT8_;
	config_v4.detect_thresh = 0.5;

	Config config_v4_tiny;
	config_v4_tiny.net_type = YOLOV4_TINY;
	config_v4_tiny.detect_thresh = 0.5;
	config_v4_tiny.file_model_cfg = "./configs/yolov4-tiny.cfg";
	config_v4_tiny.file_model_weights = "../configs/yolov4-tiny.weights";
	config_v4_tiny.calibration_image_list_file_txt = "../configs/calibration_images.txt";
	config_v4_tiny.inference_precison = FP32;

	Config config_v5;
	config_v5.net_type = YOLOV5;
	config_v5.detect_thresh = 0.5;
	config_v5.file_model_cfg = "../configs/yolov5l1.cfg";
	config_v5.file_model_weights = "../configs/best.weights";
	config_v5.inference_precison = FP32;

	std::unique_ptr<Detector> detector(new Detector());
	detector->init(config_v5);
	cv::VideoCapture cap("boat.mp4");
	//cv::Mat image0 = cv::imread("../configs/dog.jpg", cv::IMREAD_UNCHANGED);
	//cv::Mat image1 = cv::imread("../configs/person.jpg", cv::IMREAD_UNCHANGED);
	std::vector<BatchResult> batch_res;
	Timer timer;
	for (;;)
	{
		cv::Mat image0;
		cap.read(image0);
		//prepare batch data
		std::vector<cv::Mat> batch_img;
		cv::Mat temp0 = image0.clone();
		// cv::Mat temp1 = image1.clone();
		batch_img.push_back(temp0);
		//batch_img.push_back(temp1);

		//detect
		timer.reset();
		detector->detect(batch_img, batch_res);
		timer.out("detect");

		//disp
		for (int i = 0;i<batch_img.size();++i)
		{
			for (const auto &r : batch_res[i])
			{
				std::cout << "batch " << i << " id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
				cv::rectangle(batch_img[i], r.rect, cv::Scalar(255, 0, 0), 2);
				std::stringstream stream;
				stream << std::fixed << std::setprecision(2) << "id:" << r.id << "  score:" << r.prob;
				cv::putText(batch_img[i], stream.str(), cv::Point(r.rect.x, r.rect.y - 5), 0, 0.5, cv::Scalar(0, 0, 255), 2);
			}
			cv::imshow("image" + std::to_string(i), batch_img[i]);
		}
		cv::waitKey(10);
	}
#endif // runtest
#ifdef countMap 
	Config config_v4;
	config_v4.net_type = YOLOV4;
	config_v4.file_model_cfg = "../configs/yolov4-boat.cfg";
	config_v4.file_model_weights = "../configs/yolov4-boat_best.weights";
	config_v4.inference_precison = FP32;
	config_v4.detect_thresh = 0.5;

	Config config_v5;
	config_v5.net_type = YOLOV5;
	config_v5.detect_thresh = 0.7;
	config_v5.file_model_cfg = "../configs/yolov5l.cfg";
	config_v5.file_model_weights = "../configs/best.weights";
	config_v5.inference_precison = FP32;

	std::unique_ptr<Detector> detector(new Detector());
	detector->init(config_v4);

	std::vector<BatchResult> batch_res;

	// 获取路径下的所有文件名
	std::vector<std::string> files;
	// getFile(filepath, files);
	char FilePath[255], path[256], resultPath[256], resultroot[256];
	GetModuleFileName(NULL, FilePath, 255); // 获取当前程序路径
	(strrchr(FilePath, '\\'))[1] = 0; // 从右往左查找第一个\，
	sprintf(path, "%s\\map\\img\\", FilePath); // 测试数据目录路径
	sprintf(resultroot, "%s\\map\\input", FilePath);
	getFiles(path, "", files); // 
	if (_access(resultroot, 00) == -1)
	{
		_mkdir(resultroot);
	}
	sprintf(resultPath, "%smap\\input\\detection-results", FilePath); 


	if (_access(resultPath, 00) == -1)
	{
		// 创建目录
		try
		{
			_mkdir(resultPath);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			system("pause");
		}


	}
	Timer timer;
	std::string strpath = path;
	if (strpath.back() != '\\')
	{
		strcat(path, "\\");
	}
	for (auto img0 : files)
	{

		//prepare batch data
		char path2[256];
		memcpy(path2, path, 256);
		std::cout << strcat(path2, img0.c_str()) << std::endl;
		std::string img = path2;
		// sprintf(img, "%")
		std::vector<cv::Mat> batch_img;
		cv::Mat temp0;
		if (strrchr(img.c_str(), '.')[1] == 't') 
		{
			continue;
		}
		cv::Mat temp1 = cv::imread(img, cv::IMREAD_UNCHANGED);
		if (!temp1.data)
		{
			std::cout << "读取失败" << std::endl;
		}
		std::cout << temp1.channels() << std::endl;
		if (temp1.channels() < 3) // 通道小于3，非bgr图片
		{
			cv::cvtColor(temp1, temp0, CV_GRAY2BGR);
		}
		else
		{
			temp0 = temp1;
		}

		batch_img.push_back(temp0);

		timer.reset();
		detector->detect(batch_img, batch_res);
		timer.out("detect");


		std::vector<my_Detectbox> DetectionPerFrame;
		std::vector<std::string> vector_detectStr;

		//disp
		/**/
		for (int i = 0;i<batch_img.size();++i)
		{
			for (const auto &r : batch_res[i])
			{
				std::cout << "batch " << i << " id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl; // 
				cv::rectangle(batch_img[i], r.rect, cv::Scalar(255, 0, 0), 2);
				std::stringstream stream;
				stream << std::fixed << std::setprecision(2) << "id:" << r.id << "  score:" << r.prob;
				cv::putText(batch_img[i], stream.str(), cv::Point(r.rect.x, r.rect.y - 5), 0, 0.5, cv::Scalar(0, 0, 255), 2);

				my_Detectbox detectBox_PerBatch;
				detectBox_PerBatch.x = r.rect.x<0 ? 1 : r.rect.x;
				detectBox_PerBatch.y = r.rect.y<0 ? 1 : r.rect.y;
				detectBox_PerBatch.w = (r.rect.x + r.rect.width)>temp0.cols ? temp0.cols : (r.rect.x + r.rect.width);
				detectBox_PerBatch.h = (r.rect.y + r.rect.height) > temp0.rows ? temp0.rows : (r.rect.y + r.rect.height);
				detectBox_PerBatch.classIndex = r.id;
				float confidence = r.prob;
				char detectStr[256];
				sprintf(detectStr, "%d %f %d %d %d %d\0", detectBox_PerBatch.classIndex, confidence, detectBox_PerBatch.x, detectBox_PerBatch.y, detectBox_PerBatch.w, detectBox_PerBatch.h);

				vector_detectStr.push_back(detectStr);

			}
			cv::imshow("image" + std::to_string(i), batch_img[i]);
			//cv::waitKey(10);
		}

		std::ofstream ofile;// 写文件
		const char * pImg = img0.c_str();
		char * pimg = const_cast<char *>(pImg); // 去除const
		strrchr(pimg, '.')[1] = 0;


		strcat(pimg, "txt");
		std::cout << pimg << std::endl;
		char imgpath[256];
		std::string strResultPath = resultPath;

		if (strResultPath.back() != '\\')
		{
			strcat(resultPath, "\\");
		}
		sprintf(imgpath, "%s%s", resultPath, pimg);
		ofile.open(imgpath);
		if (!ofile.is_open())
		{
			std::cout << "open file failed" << std::endl;
		}
		for (auto detectResult : vector_detectStr)
		{
			ofile << detectResult << std::endl;
		}


		cv::waitKey(10);
	}

	transportYoloGroundTruth(); 
	system("python  E:\\work\\TensorRT\\TrtDetectNewer\\yolo-tensorrt\\sln\\map\\get_map.py"); // 根据自己的路径修改， conda 中的python没跑成功；
	system("pause");

#endif // countMap
	
}

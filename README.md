# yolo-tensorrt

## INTRODUCTION

the project is the encapsulation  of tensorrt yolo implementation. The origin code is [here](https://github.com/mj8ac/trt-yolo-app_win64). And you must have the trained yolo model(__.weights__) and __.cfg__ file from the darknet.

|  model   | gpu  |precision|inference time|
|  :----:  | :----:  |:---:|:--:|
| yolov3-416x416  | gtx1050 |INT8|25ms|
| yolov3-416x416  | gtx1050 |FLOAT32|50ms|
| yolov3-416x416  | jetson nano (15w) |HALF(FP16)|250ms|

## WRAPPER

user-friendly

```c++
Detector detector;
Config config;
config.inference_precison = INT8;
detector.init(config);

cv::Mat mat_image = cv::imread("dog.jpg");
std::vector<Result> res;
detector.detect(mat_image, res)
```

## How to use yolo-trt as DLL and SO libraries

download the pretrained model 

```
git clone https://github.com/enazoe/yolo-tensorrt.git
cd scripts/
python3 download.py
//python3.exe download
```

### windows10

- requirements : cuda 10.0 , cudnn 7.5 , TensorRT 5.1.5 , opencv3.3 , gflags , vs2015
- build:
    
    open _sln/sln.sln_ file 
    - dll project : the interface of the trt yolo lib
    - demo project : test of the dll

### ubuntu

#### jetson nano 
- requirements : gflags , JetPack 4.2.2
- make
    ```
    sudo apt-get install libgflags-dev
    cd yolo-tensorrt/
    mkdir build
    cd build/
    cmake ..
    make
    ```
the code generate the libdetector.so lib, and the test code


__note:__ when the platform is jetson nano the gencode arch must be set _compute_53,code=sm_53_

## API

```
struct Config
{
	std::string file_model_cfg = "configs/yolov3.cfg";

	std::string file_model_weights = "configs/yolov3.weights";

	float detect_thresh = 0.9;

	ModelType net_type = YOLOV3;

	Precision inference_precison = INT8;
	
	int gpu_id = 0;

	std::string calibration_image_list_file_txt = "configs/calibration_images.txt";
};

class API Detector
{
public:
	explicit Detector();
	~Detector();

	void init(const Config &config);

	void detect(const cv::Mat &mat_image, std::vector<Result> &vec_result);

private:
	Detector(const Detector &);
	const Detector &operator =(const Detector &);
	class Impl;
	Impl *_impl;
};
```

## REFERENCE

- https://github.com/mj8ac/trt-yolo-app_win64
- https://github.com/NVIDIA-AI-IOT/deepstream_reference_apps
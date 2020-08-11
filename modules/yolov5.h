#ifndef CLASS_YOLOV5_H_
#define CLASS_YOLOV5_H_
#include "yolo.h"
class YoloV5 :public Yolo
{
public:
	YoloV5(const uint32_t batch_size_,
		const NetworkInfo &network_info_,
		const InferParams &infer_params_);
private:
	std::vector<BBoxInfo> decodeTensor(const int imageIdx,
		const int imageH,
		const int imageW,
		const TensorInfo& tensor) override;
};

#endif
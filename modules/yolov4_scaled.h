#ifndef CLASS_YOLOV4_SCALED_H_
#define CLASS_YOLOV4_SCALED_H_
#include "yolo.h"
class YoloV4Scaled :public Yolo
{
public:
	YoloV4Scaled(
		const NetworkInfo &network_info_,
		const InferParams &infer_params_);
private:
	std::vector<BBoxInfo> decodeTensor(const int imageIdx,
		const int imageH,
		const int imageW,
		const TensorInfo& tensor) override;
};

#endif
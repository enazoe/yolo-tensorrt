# yolo-tensorrt

## INTRODUCTION

the project is the encapsulation  of tensorrt yolo implementation. The origin code is [here](https://github.com/mj8ac/trt-yolo-app_win64). And you must have the trained yolo model(.weights) and cfg file from the darknet.

|  model   | gpu  |precision|inference time|
|  :----:  | :----:  |:---:|:--:|
| yolov3-416x416  | gtx1050 |INT8|25ms|
| yolov3-416x416  | gtx1050 |FLOAT32|50ms|
| yolov3-416x416  | jetson nano (15w) |HALF(FP16)|250ms|
## INSTALL

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
    ```
the code generate the libdetector.so lib, and the test code


__note:__ when the platform is jetson nano the gencode arch must be set _compute_53,code=sm_53_

## REFERENCE

- https://github.com/mj8ac/trt-yolo-app_win64
- https://github.com/NVIDIA-AI-IOT/deepstream_reference_apps
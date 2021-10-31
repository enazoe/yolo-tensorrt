# YOLOV5

## INTRODUCTION

This is tensorrt c++ api implementation of yolov5.

![](./configs/yolo-trt.png)

## Feature

- [x] yolov5 n,s,m,l,x
- [x] inequal net input  size
- [x] batch inference
- [x] support FP32,FP16,INT8

## Build

- clone the project

    ```shell
    git clone https://github.com/ultralytics/yolov5.git
    git clone https://github.com/enazoe/yolo-tensorrt.git
    ```

- get .cfg and .weights file

    copy the [script](./scripts/yaml2cfg.py) to yolov5 root dir and generate the cfg and weigths file.
    ```shell
    cp yolo-tensorrt/scripts/yaml2cfg.py yolov5/
    python yaml2cfg.py
    mv yolov5/models/yolov5.cfg yolo-tensorrt/configs/yolov5-4.0
    mv yolov5/weights/yolov5.weights yolo-tensorrt/configs/yolov5-4.0
    ```
    
    transformed models

    |  model   |                             .cfg                             |                           .weights                           |
    | :------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
    | yolov5n | [yolov5n.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5n.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5s | [yolov5s.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5s.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5m | [yolov5m.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5m.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5l | [yolov5l.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5l.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5x  | [yolov5x.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5x.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    
    |    model     |                            .yaml                             |                             .pt                              |                             .cfg                             |                           .weights                           |
    | :----------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
    | yolov5s-v4.0 | [yolov5s.yaml](https://github.com/ultralytics/yolov5/releases/tag/v4.0) | [yolov5s.pt](https://github.com/ultralytics/yolov5/releases/tag/v4.0) | [yolov5s.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5s.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5m-v4.0 | [yolov5m.yaml](https://github.com/ultralytics/yolov5/releases/tag/v4.0) | [yolov5m.pt](https://github.com/ultralytics/yolov5/releases/tag/v4.0) | [yolov5m.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5m.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5l-v4.0 | [yolov5l.yaml](https://github.com/ultralytics/yolov5/releases/tag/v4.0) | [yolov5l.pt](https://github.com/ultralytics/yolov5/releases/tag/v4.0) | [yolov5l.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5l.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5x-v4.0 | [yolov5x.yaml](https://github.com/ultralytics/yolov5/releases/tag/v4.0) | [yolov5x.pt](https://github.com/ultralytics/yolov5/releases/tag/v4.0) | [yolov5x.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5x.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    
    
    |    model     |                            .yaml                             |                             .pt                              |                             .cfg                             |                           .weights                           |
    | :----------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
    | yolov5s-v3.0 | [yolov5s.yaml](https://github.com/ultralytics/yolov5/releases/tag/v3.0) | [yolov5s.pt](https://github.com/ultralytics/yolov5/releases/tag/v3.0) | [yolov5s.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5s.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5m-v3.0 | [yolov5m.yaml](https://github.com/ultralytics/yolov5/releases/tag/v3.0) | [yolov5m.pt](https://github.com/ultralytics/yolov5/releases/tag/v3.0) | [yolov5m.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5m.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5l-v3.0 | [yolov5l.yaml](https://github.com/ultralytics/yolov5/releases/tag/v3.0) | [yolov5l.pt](https://github.com/ultralytics/yolov5/releases/tag/v3.0) | [yolov5l.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5l.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5x-v3.0 | [yolov5x.yaml](https://github.com/ultralytics/yolov5/releases/tag/v3.0) | [yolov5x.pt](https://github.com/ultralytics/yolov5/releases/tag/v3.0) | [yolov5x.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5x.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    
    |    model     |                            .yaml                             |                             .pt                              |                             .cfg                             |                           .weights                           |
    | :----------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
    | yolov5s-v2.0 | [yolov5s.yaml](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5s.pt](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5s.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5s.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5m-v2.0 | [yolov5m.yaml](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5m.pt](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5m.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5m.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5l-v2.0 | [yolov5l.yaml](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5l.pt](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5l.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5l.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5x-v2.0 | [yolov5x.yaml](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5x.pt](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5x.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5x.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    
- build and run

    reference the readme.md

    - win10: open sln/sln.sln file using the visual studio 2015
    - ubuntu: cmake


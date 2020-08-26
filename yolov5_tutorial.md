# YOLOV5

## INTRODUCTION

This is tensorrt c++ api implementation of yolov5.

## Feature

- [x] yolov5 s,m,l,x
- [x] inequal sized net input
- [x] batch inference
- [x] support FP32,FP16,INT8

## Build

- clone the project

    ```shell
    git clone https://github.com/ultralytics/yolov5.git
    git clone https://github.com/enazoe/yolo-tensorrt.git
    ```

- get .cfg and .weights file

    copy the script to yolov5 root dir and generate the cfg and weigths file.
    ```shell
    cp yolo-tensorrt/scripts/yaml2cfg.py yolov5/
    python yaml2cfg.py
    ```
    
    transformed models
    
    |    model     |                             yaml                             |                             cfg                              |                              pt                              |                           weights                            |
    | :----------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
    | yolov5s-v2.0 | [yolov5s.yaml](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5s.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5s.pt](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5s.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5m-v2.0 | [yolov5m.yaml](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5m.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5m.pt](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5m.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5l-v2.0 | [yolov5l.yaml](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5l.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5l.pt](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5l.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    | yolov5x-v2.0 | [yolov5x.yaml](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5x.cfg](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) | [yolov5x.pt](https://github.com/ultralytics/yolov5/releases/tag/v2.0) | [yolov5x.weights](https://mega.nz/folder/7iYTSARZ#-T3xXHBjRAUhOwdEe_ajKw) |
    
    __note:__ the performance of yolov5-v3.0 has some problem ,I will fix it soon.
    
- build

    reference the readme.md

    - win: open sln/sli.sln file using the visual studio 2015
    - ubuntu: cmake


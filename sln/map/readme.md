# map 

The folder is about caculating map.

![](https://gitee.com/sangwz/img/raw/master/20210129210011.png)

* img: The test image;

* testLables: 测试图片的ground_truth, yolo格式，也就是归一化之后的“x_center, y_center, width, height”

  ```
  0 0.4992 0.4718 0.9984 0.7468
  ```

  如果你有 left_top, right_bottom格式，而且是实际大小的标签文件，直接复制到 "./input/ground-truth"文件夹下，并将sample_detector.cpp中的

  `transportYoloGroundTruth();`这行代码注释掉；

  如果你的数据格式是VOC格式，也就是.xml格式的文件，使用xml2txt.py生成yolo-label的txt文件；

* results: map计算结果；

* input:  detection-results存放的是检测输出结果；

--------

》getmap.py文件来自：代码克隆自https://github.com/Cartucho/mAP

* requires: numpy, matplotlib, 

-------

* **-->**代码在windows下实现的，如果是linux系统，注意修改“\\\\”为“/”；

调用python执行getmap.py文件是本地环境下的python解释器，conda环境下的未执行成功。

如果

```
system("python  E:\\work\\TensorRT\\TrtDetectNewer\\yolo-tensorrt\\sln\\map\\get_map.py"); 
```

执行不成功，可以手动执行。^_^
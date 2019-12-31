#!/usr/bin/env python3

import requests
print("download cfg file from https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov3.cfg ...")
url = 'https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov3.cfg'
r = requests.get(url)

with open('../configs/yolov3.cfg', 'wb') as f:
    f.write(r.content)
print("done!")
print("download weights file from https://pjreddie.com/media/files/yolov3.weights ...")

url = 'https://pjreddie.com/media/files/yolov3.weights'
r = requests.get(url)

with open('../configs/yolov3.weights', 'wb') as f:
    f.write(r.content)
print("done!")

url = 'https://raw.githubusercontent.com/pjreddie/darknet/master/data/dog.jpg'
r = requests.get(url)

with open('../configs/dog.jpg', 'wb') as f:
    f.write(r.content)
print("complete !")
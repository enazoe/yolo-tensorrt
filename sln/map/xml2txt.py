import xml.etree.ElementTree as ET
import pickle
import os
from os import listdir, getcwd
from os.path import join

classes = ['boat']  # 注意修改你的类别
 
 
 
def convert(size, box):
    dw = 1./(size[0])
    dh = 1./(size[1])
    x = (box[0] + box[1])/2.0 - 1
    y = (box[2] + box[3])/2.0 - 1
    w = box[1] - box[0]
    h = box[3] - box[2]
    x = x*dw
    w = w*dw
    y = y*dh
    h = h*dh
    return (x,y,w,h)
 
def convert_annotation(image_id):
    in_file = open('./Annotations/%s.xml'%(image_id), encoding="UTF-8") # where is your annotations
    out_file = open('./TestLabels/%s.txt'%(image_id), 'w', encoding="UTF-8")
    tree=ET.parse(in_file)
    root = tree.getroot()
    size = root.find('size')
    w = int(size.find('width').text)
    h = int(size.find('height').text)
 
    for obj in root.iter('object'):
        difficult = obj.find('difficult').text
        cls = obj.find('name').text
        print(cls)
        if cls not in classes or int(difficult)==1:
            continue
        cls_id = classes.index(cls)
        xmlbox = obj.find('bndbox')
        b = (float(xmlbox.find('xmin').text), float(xmlbox.find('xmax').text), float(xmlbox.find('ymin').text), float(xmlbox.find('ymax').text))
        bb = convert((w,h), b)
        out_file.write(str(cls_id) + " " + " ".join([str(a) for a in bb]) + '\n')
 
 
data_path = './img/'
img_names = os.listdir(data_path)
 
list_file = open('./class_train.txt', 'w')
for img_name in img_names:
    if not os.path.exists('./testLabels'):
        os.makedirs('./testLabels')
 
    list_file.write('./img/%s\n'%img_name)
    image_id = img_name[:-4]
    convert_annotation(image_id)
 
list_file.close()

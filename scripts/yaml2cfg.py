import torch
import argparse
from utils.downloads import *
import struct
import yaml

def yaml2cfg(opt):
    with open(opt.yaml,'r') as f:
        with open(opt.yaml.split(".")[0]+".cfg", 'w') as cfg:
            f = yaml.load(f,Loader=yaml.FullLoader)
            net = 0
            for k in f:
                if ((k != 'anchors')and(k !='backbone')and(k !='head')):
                    if net == 0:
                        cfg.write('\n[net]\n')
                        cfg.write("width={}\n".format(opt.net_w))
                        cfg.write("height={}\n".format(opt.net_h))
                        cfg.write("channels={}\n".format(3))
                        cfg.write("batch={}\n".format(opt.batch))
                        net =1
                    cfg.write("{}={}\n".format(k,f[k]))
                elif (k == 'anchors'):
                    anchors = []
                    for v in f[k]:
                        anchors.extend(v)
                    cfg.write("anchors={}\n".format(str(anchors)[1:-1]))
                elif((k == 'backbone') or (k =='head')): 
                    for vector in f[k]:
                        #net type
                        cfg.write('\n[{}]\n'.format(vector[2]))
                        #from
                        if type(vector[0]) == int:
                            cfg.write("from={}\n".format(str(vector[0])))
                        elif type(vector[0]) == list:
                            cfg.write("from={}\n".format(str(vector[0])[1:-1]))
                        #number
                        if type(vector[1]) == int:
                            cfg.write("number={}\n".format(str(vector[1])))
                        elif type(vector[1]) == list:
                            cfg.write("number={}\n".format(str(vector[1])[1:-1]))
                        #params
                        if type(vector[3]) == int:
                            cfg.write("args={}\n".format(str(vector[3])))
                        elif type(vector[3]) == list:
                            cfg.write("args={}\n".format(str(vector[3])[1:-1]))

def pt2weight(weights):
    model = torch.load(weights, map_location="cpu")['model'].eval().float()
    with open(weights.split(".")[0]+".weights",'w') as f:
        for k,v in model.state_dict().items():
            list_data = list(v.reshape(-1).numpy())
            f.write('{}'.format(k))
            for value in list_data:
                f.write(" ")
                f.write(struct.pack('>f',float(value)).hex())
            f.write('\n')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--weights', type=str, default='weights/yolov5s.pt', help='model.pt path')
    parser.add_argument('--yaml', type=str, default='models/yolov5s.yaml', help='model.yaml path')
    parser.add_argument('--net_w', type=int, default=640, help='net width (pixels)')
    parser.add_argument('--net_h', type=int, default=320, help='net height (pixels)')
    parser.add_argument('--batch', type=int, default=1, help='inference batch size')
    parser.add_argument('--classes', type=int,default=80, help='filter by class: --class 0, or --class 0 2 3')
    opt = parser.parse_args()
    print(opt)
    attempt_download(opt.weights)
    yaml2cfg(opt)  
    print("convert {} to {} success".format(opt.yaml,opt.yaml.split(".")[0]+".cfg"))
    pt2weight(opt.weights)
    print("convert {} to {} success".format(opt.weights,opt.weights.split(".")[0]+".weights"))
    print("complete")
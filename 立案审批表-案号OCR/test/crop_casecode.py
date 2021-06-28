import cv2
import os
import re
import argparse

import numpy as np

from PIL import Image


parser = argparse.ArgumentParser()
parser.add_argument('-d', '--dir', help='scan this directory', type=str, default=os.getcwd())

args = parser.parse_args()


def gray_and_crop(file_path):
    img = cv2.cvtColor(np.asarray(Image.open(file_path)),cv2.COLOR_RGB2GRAY)
    sobel = cv2.Sobel(img, -1, 1, 1)
    ret, threshold_sobel_img = cv2.threshold(sobel, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    
    kernel_1 = cv2.getStructuringElement(cv2.MORPH_RECT, (100, 10))
    kernel_2 = cv2.getStructuringElement(cv2.MORPH_RECT, (50, 10))
    kernel_3 = cv2.getStructuringElement(cv2.MORPH_RECT, (10, 10))

    morphology_img1 = cv2.morphologyEx(threshold_sobel_img, cv2.MORPH_CLOSE, kernel_1, 1)
    morphology_img2 = cv2.morphologyEx(morphology_img1, cv2.MORPH_OPEN, kernel_3, 1)
    morphology_img3 = cv2.morphologyEx(morphology_img2, cv2.MORPH_DILATE, kernel_2, 1)

    #  查找和筛选文字区域
    region = []

    #  查找轮廓
    contours, hierarchy = cv2.findContours(morphology_img3, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # 遍历所有轮廓
    for cnt in contours:
        # cnt是一个点集
        # 找到最小的矩形，该矩形可能有方向
        rect = cv2.minAreaRect(cnt)
        # box是四个点的坐标
        box = np.int0(cv2.boxPoints(rect))
        # 计算高和宽
        width, height = abs(box[0][0] - box[2][0]), abs(box[0][1] - box[2][1])
        # 宽高比 大于 10
        if(width < 100 or height < 40 or width / height < 10):
            continue
        region.append(box)
    
    box = region[-1]
    x1, y1 = box[1][0], box[1][1]
    x2, y2 = box[3][0], box[3][1]
    x1, x2 = min(x1, x2), max(x1, x2)
    y1, y2 = min(y1, y2) - 10, max(y1, y2) + 10
 
    img = cv2.morphologyEx(cv2.threshold(cv2.GaussianBlur(img[y1:y2, x1:x2], (3,3), 0), 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)[1], cv2.MORPH_OPEN, cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3)), 3)
    
    contours, hierarchy = cv2.findContours(img, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours:
        if cv2.contourArea(cnt) < 20:
            cv2.drawContours(img, [cnt], -1, (255, 255, 255), -1)
    
    return img


if __name__ == '__main__':
   
    dirpath = args.dir

    if not os.path.exists(os.path.join(dirpath, 'casecode')):
        os.mkdir(os.path.join(dirpath, 'casecode'))
    
    files = os.listdir(dirpath)
    for name in files:
        f = os.path.join(dirpath, name)
        if os.path.splitext(name)[1] in ['.jpg', '.png']:
            save_path = os.path.join(dirpath, 'casecode', name)
            cv2.imencode('.jpg', gray_and_crop(f))[1].tofile(save_path)
            print(save_path)

#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==>
'''
import h5py
import cv2
import random
import numpy as np
import matplotlib.pyplot as plt

with h5py.File('D:\\googleDrive\\private2\\dataset_ML\\visualComputing_hangeul\\kalph_train.hf', 'r') as hf:
    images = np.array(hf['images'])
    labels = np.array(hf['labels'])

kernel = np.ones((2,2), np.uint8)
len_image = len(images)


# 데이터를 19600x52x52 처럼 3차원 배열데이터로 만들어주는 코드들
aa = np.dstack((images[0], images[1])).swapaxes(0,2)
bb = np.array([images[0],images[1]])

modified = []

for i in range(0, len_image):
    rNum = random.randrange(1,8)

    if(rNum == 1):
        erosion = cv2.erode(images[0],kernel,iterations = 1)
    dilation = cv2.dilate(images[0],kernel,iterations = 1)
    opening = cv2.morphologyEx(images[0], cv2.MORPH_OPEN, kernel)
    gradient = cv2.morphologyEx(images[0], cv2.MORPH_GRADIENT, kernel)
    closing = cv2.morphologyEx(images[0], cv2.MORPH_CLOSE, kernel)
    tophat = cv2.morphologyEx(images[0], cv2.MORPH_TOPHAT, kernel)
    blackhat = cv2.morphologyEx(images[0], cv2.MORPH_BLACKHAT, kernel)









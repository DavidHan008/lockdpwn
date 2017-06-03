#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 비주얼컴퓨팅,

'''
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
import scipy.misc
import scipy.io
import random
import cv2
from math import * 


def derivate(img):





def getAngle_Magnitude(dImgX, dImgY):
    
    if dImgY != 0:
        angle = atan(dImgX / dImgY)
    else:
        angle = 0 

    if(angle < 255 - 90)
        angle += 90
    
    magnitude = sqrt(dImgX **2 + dImgY **2)





def getHOGFeature(img):







#-----------------------------------------------------------------
# train
train_images = []
tlabels = []

# train Image 데이터 700장을 불러온다
for num in range(1,701):
    train_images.append(scipy.misc.imread('D:\\edward\\visualComputing_faceDetection\\train_image\\train_'+ str(num)+'.bmp'))

# train Label 데이터를 불러온다
with open("D:\\edward\\visualComputing_faceDetection\train_label.txt") as f:
    line = [line.rstrip() for line in f]
    tlabels.append(line)

# Image 데이터와 Label 데이터를 numpy 데이터로 수정한다
train_images = np.array(train_images)
# LBP 연산을 위해 train_images2 선언해준다
train_images2 = np.array(train_images)
train_images = train_images.reshape(700, 2200, )


tlabels = np.array(tlabels)     # tlabels = (1,700)
tlabels = tlabels.reshape(700,1)

# train Label 데이터를 [1 x 100] 의 행렬로 표현한다
#           예를 들어 3이면 [0,0,1,0,.....,0] 과 같이 설정한다
train_labels  = np.array(np.zeros(70000).reshape(700,100))
for num in range(0,700):
    train_labels[num][int(tlabels[num][0]) - 1] = 1




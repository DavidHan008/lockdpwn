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

modified_images = np.array(np.zeros(52998400).reshape(19600,52,52))
modified_labels = labels


# images 이미지들을 랜덤으로 모폴로지 연산을 수행한다
for i in range(0, len_image):
    rNum = random.randrange(1,8)

    if(rNum == 1):
        modified_images[i] = cv2.erode(images[i],kernel,iterations = 1)
    elif(rNum == 2):
        modified_images[i] = cv2.dilate(images[i],kernel,iterations = 1)
    elif(rNum == 3):
        modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_OPEN, kernel)
    elif(rNum == 4):
        modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_GRADIENT, kernel)
    elif(rNum == 5):
        modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_CLOSE, kernel)
    elif(rNum == 6):
        modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_TOPHAT, kernel)
    elif(rNum == 7):
        modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_BLACKHAT, kernel)
    else:
        continue


# 이미지들을 랜덤순서로 섞는다
shuf = np.arange(len_image)
np.random.shuffle(shuf)
modified_images = modified_images[shuf]
modified_labels = modified_labels[shuf]


# hdf5 파일 포맷으로 위의 데이터를 저장한다 :-)
f = h5py.File('modified_file.hf','w')

f.create_dataset('modified_images',data=modified_images, compression_opts=9, compression='gzip')
f.create_dataset('modified_labels',data=modified_labels, compression_opts=9, compression='gzip')

f.close()



# 저장된 데이터를 불러온다
g = h5py.File('modified_file.hf','r')

# 키를 확인한다
for keys in g:
    print(keys, "---------->" , g[keys])

mod_images = np.array(g['modified_images'])
mod_labels = np.array(g['modified_labels'])


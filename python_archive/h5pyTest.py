#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> h5py 패키지로 hdf5 파일 포맷의 데이터를 다뤄본 코드
                머신러닝에 자주 활용되는 데이터타입이라고 한다
'''
import h5py
import numpy as np
import matplotlib.pyplot as plt

hf = h5py.File('D:\\googleDrive\\private2\\dataset_ML\\visualComputing_hangeul\\kalph_train.hf', 'r')

# 해당파일을 읽은 다음 images, labels 변수에 데이터를 저장합니다
with h5py.File('D:\\googleDrive\\private2\\dataset_ML\\visualComputing_hangeul\\kalph_train.hf', 'r') as hf:
    images = np.array(hf['images'])
    labels = np.array(hf['labels'])


# hf에 포함된 키들을 확인합니다
for keys in hf:
    print(keys, "---------->" , hf[keys])




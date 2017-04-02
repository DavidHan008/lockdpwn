#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 비주얼컴퓨팅, 프로젝트2
'''
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sympy import *
from sympy import solve
from mpl_toolkits.mplot3d import Axes3D

class Perceptron():
	def __init__(self, thresholds=0.0, eta=0.01, n_iter=10):
		self.thresholds = thresholds
		self.eta = eta
		self.n_iter = n_iter

	def fit(self,X,y):
		self.w_ = np.zeros(1 + X.shape[1])
		self.errors_ = []

		for _ in range(self.n_iter):
			errors = 0
			for xi, target in zip(X,y):
				update = self.eta * (target - self.predict(xi))
				self.w_[1:] += update * xi
				self.w_[0] += update
				errors += int(update != 0.0)
			self.errors_.append(errors)
			print(self.w_)
		return self

	def net_input(self, X):
		return np.dot(X, self.w_[1:]) + self.w_[0]

	def predict(self, X):
		return np.where(self.net_input(X) > self.thresholds, 1, -1)



				


project2Data = './project2Data.dat'
names = ['x1', 'x2', 'class']
data = pd.read_csv(project2Data, header=None, names=names)

Class = data['class']
Data = np.array(data)

data1 = data[0:10]
data2 = data[10:20]
data3 = data[20:30]

class1 = data1['class']
class2 = data2['class']
class3 = data3['class']

del data['class']
del data1['class']
del data2['class']
del data3['class']

plt.plot(data1['x1'],data1['x2'],'ro',data2['x1'],data2['x2'],'bo',data3['x1'],data3['x2'],'go')
plt.grid()
plt.show()

w1Init = 0
w2Init = 0
w3Init = 0



















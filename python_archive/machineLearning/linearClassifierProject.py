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

# Sympy 기초 세팅을 한다
x, y, z, w = symbols('x y z w')
init_printing()

#--------------------------------------------------------------
# 1. Perceptron algorithm을 사용하여 w1, w2를 구분하는 선형분류기를 작성하라. 초기 weight vector와 학습율을 다양하게 시도해 볼 것.

class Perceptron():
	def __init__(self, thresholds=0.0, eta=0.01, n_iter=10):
		self.thresholds = thresholds
		self.eta = eta
		self.n_iter = n_iter

	def fit(self,X,y):
		self.w_ = np.zeros(1 + X.shape[1])
		self.errors_ = []
		self.y_ = zip(one, X[:,0], X[:,1])
		self.y_ = np.array(self.y_)

		for _ in range(self.n_iter):
			errors = 0
			for xi, target,i in zip(X,y,range(0,len(X))):
				update = (target - self.predict(xi))
				self.w_ += self.eta * update * self.y_[i]
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

data12 = np.vstack((data1,data2))
dataC12 = np.hstack((class1,class2))
dataC12 = np.where(dataC12 == 'w1' ,-1,1)

data13 = np.vstack((data1,data3))
dataC13 = np.hstack((class1,class3))
dataC13 = np.where(dataC13 == 'w1' ,-1,1)

ptron1 = Perceptron(eta = 0.1)
ptron2 = Perceptron(eta = 0.2)
ptron3 = Perceptron(eta = 0.3)

ptron1.fit(data12, dataC12)
print("\n")
ptron2.fit(data12, dataC12)
print("\n")
ptron3.fit(data12, dataC12)
print("\n")

print(ptron1.errors_)
print(ptron2.errors_)
print(ptron3.errors_)

def frange(x, y, jump):
  while x < y:
    yield x
    x += jump


yy = []
for i in frange(-10,10,0.1):
    yy.append(-(-103*i + 130)/116)

xx = np.linspace(-10,10,201)
plt.plot(xx,yy) 
plt.plot(data1['x1'],data1['x2'],'ro',data2['x1'],data2['x2'],'bo')
plt.grid()
plt.show()








#--------------------------------------------------------------
# 2. Batch relaxation algorithm을 사용하여 w1과 w3를 구분하는 선형분류기를 작성하라. Margin b를 0.1과 0.5, 초기 weight vector를 (0, 0, 0)로 하였을 경우의 결과들을 보여라.


class BatchRelaxationWithMargin():
	def __init__(self, thresholds=0.0, eta=0.01, n_iter=10, margin = 0.1):
		self.thresholds = thresholds
		self.eta = eta
		self.n_iter = n_iter
		self.margin = margin

	def fit(self,X,y):
		self.w_ = np.zeros(1 + X.shape[1])
		self.errors_ = []
		self.y_ = zip(one, X[:,0], X[:,1])
		self.y_ = np.array(self.y_)

		for _ in range(self.n_iter):
			errors = 0
			for xi, target,i in zip(X,y,range(0,len(X))):
				update = (target - self.predict(xi))
				if(update != 0):
					delta = (update * self.y_[i] * (self.margin - self.w_ * update * self.y_[i] )) / ((np.linalg.norm(update * self.y_[i]))**2)
					self.w_ += delta * self.eta
				errors += int(update != 0.0)
			self.errors_.append(errors)
			print(self.w_)
		return self

	def net_input(self, X):
		return np.dot(X, self.w_[1:]) + self.w_[0]

	def predict(self, X):
		return np.where(self.net_input(X) > self.thresholds, 1, -1)


bat = BatchRelaxationWithMargin(eta = 0.1, margin = 0.1)
bat.fit(data13, dataC13)

bat2 = BatchRelaxationWithMargin(eta = 0.1, margin = 0.5)
bat2.fit(data13, dataC13)

yy2 = []
xx = np.linspace(-10,10,201)

for i in frange(-10,10,0.1):
    yy2.append(0.16708*i + 1.1202)



plt.plot(xx,yy2) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.grid()
plt.show()


yy3 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy3.append(0.18656*i + 0.15223)

plt.plot(xx,yy3) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.grid()
plt.show()









#--------------------------------------------------------------
# 3. Widrow-Hoff (LMS) algorithm을 사용하여 w1과 w3를 구분하는 선형분류기를 작성하라. 다양한 initial weight vector a, margin vector b, threshold, learning rate를 시도해 볼 것.


class WidrowHoff():
	def __init__(self, thresholds=0.0, eta=0.01, n_iter=10, b_ = 0.1):
		self.thresholds = thresholds
		self.eta = eta
		self.n_iter = n_iter
		self.margin = margin
		self.b_ = b_

	def fit(self,X,y):
		self.w_ = np.zeros(1 + X.shape[1])
		self.errors_ = []
		self.y_ = zip(one, X[:,0], X[:,1])
		self.y_ = np.array(self.y_)

		for _ in range(self.n_iter):
			errors = 0
			for xi, target, i in zip(X, y, range(0, len(X))):
				update = (target - self.predict(xi))
				if(update != 0):
					delta = np.dot(update * self.y_[i], self.b_ - np.dot(update * self.y_[i], self.w_.T)) / self.n_iter
					self.w_ += delta * self.eta
				errors += int(update != 0.0)
			self.errors_.append(errors)
			print(self.w_)
		return self

	def net_input(self, X):
		return np.dot(X, self.w_[1:]) + self.w_[0]

	def predict(self, X):
		return np.where(self.net_input(X) > self.thresholds, 1, -1)


wid = WidrowHoff(eta = 0.1, b_ = 0.001, n_iter = 20)
wid.fit(data13,dataC13)


yy4 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy4.append(1.0244*i + 1.3034)

plt.plot(xx,yy4) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.grid()
plt.show()


yy5 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy5.append(0.6899*i + 0.959)

plt.plot(xx,yy5) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.grid()
plt.show()





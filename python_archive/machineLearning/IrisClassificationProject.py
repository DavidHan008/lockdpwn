#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 비주얼컴퓨팅수업,
'''
import pandas
from pandas.tools.plotting import scatter_matrix
import matplotlib.pyplot as plt
import numpy as np
from sympy import *
from sympy import solve

from sklearn import model_selection
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.naive_bayes import GaussianNB

x, y, z, w = symbols('x y z w')
init_printing()

names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'class']

# 훈련용 데이터 설정
train_filepath = "./Iris_train.dat"
train_dataset = pandas.read_csv(train_filepath, names = names)
# 테스트용 데이터 설정 
test_filepath = "./Iris_test.dat"
test_dataset = pandas.read_csv(test_filepath, names = names)

testClass = test_dataset['class']
del test_dataset['class']
testData = np.array(test_dataset)

##array = train_dataset.values
#X = array[:,0:4]
#Y = array[:,4]

#array2 = test_dataset.values
#X_test = array2[:,0:4]
#Y_test = array2[:,4]

class1 = train_dataset[0:40]
class2 = train_dataset[40:80]
class3 = train_dataset[80:120]

class15 = class1['class']
class25 = class2['class']
class35 = class3['class']

del class1['class']
del class2['class']
del class3['class']

class1.describe()
class2.describe()
class3.describe()

class1 = np.array(class1)
class2 = np.array(class2)
class3 = np.array(class3)

meanvec1 = np.matrix('4.9975; 3.4175; 1.4425; 0.2525')
meanvec2 = np.matrix('5.99; 2.7775; 4.31; 1.3325')
meanvec3 = np.matrix('6.61; 2.97; 5.5575; 2.03')

cov1 = np.cov(class1.T)
cov2 = np.cov(class2.T)
cov3 = np.cov(class3.T)

icov1 = np.linalg.inv(cov1)
icov2 = np.linalg.inv(cov2)
icov3 = np.linalg.inv(cov3)

xvec = Matrix([x,y,z,w]).T

# BAYES.pdf 61페이지에 있는 CASE 3의 공식을 사용해서 결정함수들을 구한다 good!!
d1First = -0.5 * xvec * icov1 * xvec.T
d1Second = xvec * icov1 * meanvec1
d1Third = -0.5 * meanvec1.T * icov1 * meanvec1 -0.5 * log(np.linalg.det(cov1))

d2First = -0.5 * xvec * icov2 * xvec.T
d2Second = xvec * icov2 * meanvec2
d2Third = -0.5 * meanvec2.T * icov2 * meanvec2 -0.5 * log(np.linalg.det(cov2))

d3First = -0.5 * xvec * icov3 * xvec.T
d3Second = xvec * icov3 * meanvec3
d3Third = -0.5 * meanvec3.T * icov3 * meanvec3 -0.5 * log(np.linalg.det(cov3))

d1 = d1First + d1Second + d1Third
d2 = d2First + d2Second + d2Third
d3 = d3First + d3Second + d3Third


def substitute(func,li):
    print(func.subs({x:li[0],y:li[1],z:li[2],w:li[3]}))
    return func.subs({x:li[0],y:li[1],z:li[2],w:li[3]})

value1 = []; value2 = []; value3 = []
value4 = []; value5 = []; value6 = []
value7 = []; value8 = []; value9 = []

for i in range(0,len(testData)):
    if(i < 10):
        value1.append(substitute(d1,testData[i]))
    elif(i < 20 and i >= 10):
        value2.append(substitute(d1,testData[i]))
    elif(i < len(testData) and i >= 20):
        value3.append(substitute(d1,testData[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value1 = np.array(value1)
value2 = np.array(value2)
value3 = np.array(value3)

print("<%.3f, %.3f, %.3f>\n" % (value1.mean(),value2.mean(),value3.mean()))

for i in range(0,len(testData)):
    if(i < 10):
        value4.append(substitute(d2,testData[i]))
    elif(i < 20 and i >= 10):
        value5.append(substitute(d2,testData[i]))
    elif(i < len(testData) and i >= 20):
        value6.append(substitute(d2,testData[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value4 = np.array(value4)
value5 = np.array(value5)
value6 = np.array(value6)
print("<%.3f, %.3f, %.3f>\n" % (value4.mean(),value5.mean(),value6.mean()))

for i in range(0,len(testData)):
    if(i < 10):
        value7.append(substitute(d3,testData[i]))
    elif(i < 20 and i >= 10):
        value8.append(substitute(d3,testData[i]))
    elif(i < len(testData) and i >= 20):
        value9.append(substitute(d3,testData[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value7 = np.array(value7)
value8 = np.array(value8)
value9 = np.array(value9)

print("<%.3f, %.3f, %.3f>\n" % (value7.mean(),value8.mean(),value9.mean()))




#print(train_dataset.shape)
#print(train_dataset.head(20))
#print(train_dataset.describe())
#print(train_dataset.groupby('class').size())

#train_dataset.plot(kind='box', subplots=True, layout=(2,2), sharex=False, sharey=False)
#plt.show()
#train_dataset.hist()
#plt.show()

#scatter_matrix(train_dataset)
#plt.show()

''' seed=7 '''
''' scoring = 'accuracy' '''

''' models = [] '''
''' models.append(('Naive Bayes', GaussianNB())) '''

''' results = [] '''
''' names = [] '''

''' # Naive Bayes와 SVM 알고리즘의 성능을 평가한다 '''
''' for name,model in models: '''
''' 	kfold = model_selection.KFold(n_splits=10, random_state=seed) '''
''' 	cv_results = model_selection.cross_val_score(model, X, Y, cv=kfold, scoring=scoring) '''
''' 	results.append(cv_results) '''
''' 	names.append(name) '''
''' 	msg = "%s: %f (%f)" % (name, cv_results.mean(), cv_results.std()) '''
''' 	print(msg) '''

''' # 성능을 평가한 다음 도식한다 '''
''' fig = plt.figure() '''
''' fig.suptitle('Algorithm Comparison') '''
''' ax = fig.add_subplot(111) '''
''' plt.boxplot(results) '''
''' ax.set_xticklabels(names) '''
''' plt.show() '''

''' # Naive Bayes를 선택하고 정확도와 Confusion Matrix를 설정한다 '''
''' NB = GaussianNB() '''
''' NB.fit(X, Y) '''
''' predictions = NB.predict(X_test) '''
''' print(accuracy_score(Y_test, predictions)) '''
''' print(confusion_matrix(Y_test, predictions)) '''
''' print(classification_report(Y_test, predictions)) '''

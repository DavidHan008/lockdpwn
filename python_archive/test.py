import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sympy import *
from sympy import solve
from mpl_toolkits.mplot3d import Axes3D

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






















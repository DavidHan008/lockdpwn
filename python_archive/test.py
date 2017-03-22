
from sympy import *
from sympy import solve

def s(func,li):
    print func.subs({x:li[0],y:li[1],z:li[2],t:li[3]})
    

for i in range(0,len(test_dataset)):
    s(d3,test_dataset[i])
    if(i % 10 == 9 and i != 0):
        print('\n')

























#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 진자의 스프링운동을 애니메이션 해 본 코드
'''
from visual import *
from math import *

scene.range = (10,10,10)
scene.center = (0,-4,0)
scene.width = 400
scene.height = 700

massa = sphere(pos=(0,0,0), radius=0.5, color=color.blue, opacity=0.8)
base = box(pos=(0,-10,-2), size=(7,0.5,7))
haste = box(pos=(0,-4,-2), size=(0.6,12,0.6))
pitoco = cylinder(pos=(0,0,-2), radius=0.2, axis=(0,0,2), color=color.yellow)
mola = helix(pos=(0,0,0), axis=(0,-7,0), radius=0.2, coils=8, thickness=0.05, color=color.gray(0.5))

L0 = 6.
r = 6.
teta0 = 30
k = 40
m = 5
pi = 3.1415
teta = (180 - teta0)*pi / 180
g = -9.81
omega = 0
alfa = 0
v = 0
a = 0

t = 0
dt = 0.01

while True:
    rate(250)
    alfa = (-g*r*sin(teta) -2*v*r*omega)/r**2
    omega += alfa*dt
    teta += omega*dt
    
    a =  r*omega**2 + g*cos(teta) -k/m*(r-L0)
    v += a*dt
    r += v*dt

    mola.axis = massa.pos - pitoco.pos + (0,0,-1.9)
    massa.pos = (r*sin(teta), r*cos(teta), 0)


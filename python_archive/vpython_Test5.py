#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 스프링 + 질량 + 진자의 운동을 애니메이션한 코드
                https://youtu.be/H8CzQtx9vds
'''
from visual import *
from math import *

scene.range = (8,17,10)
scene.center = (3,-2,0)
scene.width = 800
scene.height = 500
scene.background = (.5,.5,.5)

mass1 = box(pos=(0,0,0), size=(1,1,1), color=(1.0,1.0,0.1))
mass2 = sphere(pos=(0,0,0), radius=.5, color=(0.1,0.5,1))

wall = box(pos=(-3,0,0), size = (1,4,4))
barra = cylinder(pos = (-3,0,0), axis=(12,0,0), radius = 0.1)
mola = helix(pos=(-3,0,0), axis=(7,0,0), radius=.3, coils=8, thickness=0.07, color=color.red)
fio = curve(pos=[(mass1.pos), (mass2.pos)], color=(0,0,0), radius=.03)

L0 = 3
L = 5.
teta0 = 10.
k = 100.
m1 = 1
m2 = .1
teta = (180-teta0)*pi / 180
dt = 0.01
g = -9.81
t = 0.
omega= 0.
v = 0.
a = 0.
alfa = 0.
x = 3.3

while True:
    rate(60)
    a = (m2*L*sin(teta)*omega**2 - m2*g*L*sin(teta)*cos(teta) - k*(x-L0)) / (m1 + m2 + m2*L*(cos(teta))**2)

    alfa = -g*sin(teta) + a*cos(teta)
    v += a*dt
    x += v*dt
    omega += alfa*dt
    teta += omega*dt

    mass1.pos = (x,0,0)
    mass2.pos = (x+L*sin(teta), L*cos(teta), 0)
    mola.axis = mass1.pos - wall.pos
    fio.pos = [(mass1.pos), (mass2.pos)]

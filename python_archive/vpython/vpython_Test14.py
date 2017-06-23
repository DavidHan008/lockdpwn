#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 2개의 진자의 운동을 애니메이션 해 본 코드 
 
             code from https://youtu.be/oMBohUQz3NI
'''
from visual import *
from math import *

scene.range = (10,10,10)
scene.center = (0,-4,0)
scene.width = 400
scene.height = 700

mass1 = sphere(pos=(0,0,0), radius=0.5, color=color.red, opacity=0.7, make_trail=True)
mass2 = sphere(pos=(0,0,0), radius=0.5, color=color.red, opacity=0.7, make_trail=True)

base = box(pos=(0,-10,-2), size=(7,0.5,7))
wall = box(pos=(0,-4,-2), size=(0.6,12,0.6))
bar = cylinder(pos=(0,0,-2), radius=0.2, axis=(0,0,2), color=color.yellow)
line1 = curve(pos=[(0,0,0),(mass1.pos)], color=color.gray(0.5))
line2 = curve(pos=[(mass1.pos),(mass2.pos)], color=color.gray(0.5))

theta01 = 30.
theta02 = 30.
l = 4.5
pi = 3.1415
theta1 = (180-theta01)*pi/180
theta2 = (180-theta02)*pi/180
g = -9.81
omega1 = 0.
omega2 = 0.
alpha1 = 0.
alpha2 = 0.

a = cos(theta1 - theta2)
b = sin(theta1 - theta2)

t = 0
dt = 0.01

label1 = label()

while True:
    rate(250)
    t += dt
    alpha1 = (g/l*(sin(theta2)*a -2*sin(theta1)) - omega1**2*b*a -omega2**2*b) / (2-a**2)
    alpha2 = omega1**2*b - g/l*sin(theta2) - alpha1*a

    omega1 += alpha1*dt
    omega2 += alpha2*dt

    theta1 += omega1*dt
    theta2 += omega2*dt

    mass1.pos =(l*sin(theta1), l*cos(theta1), 0)
    mass2.pos =(l*sin(theta1) + l*sin(theta2), l*cos(theta1) + l*cos(theta2), 0)

    line1.pos =[(0,0,0), (mass1.pos)]
    line2.pos =[(mass1.pos), (mass2.pos)]

    label1.pos = base.pos + vector(0,-1,0)
    label1.text = 'time : %.2f s' % t


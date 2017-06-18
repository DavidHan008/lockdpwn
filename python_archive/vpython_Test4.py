#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython에서 2 mass-spring System의 운동을 애니메이션 해 본 코드
                https://youtu.be/H8CzQtx9vds

'''
from visual import *
from math import *

scene.range = (16,12,12)
scene.center = (0,0,0)
scene.width = 800
scene.height = 300

block1 = box(pos=(-3,0,0), size=(2,2,2), color=color.red, opacity=0.8)
block2 = box(pos=(3,0,0), size=(2,2,2), color=color.red, opacity=0.8)

bottom_wall = box(pos=(0,-1.25,0), size=(25,0.5,7))
wall1 = box(pos=(-12,1,0), size=(.5,4,7))
wall2 = box(pos=(12,1,0), size=(.5,4,7))

spring1 = helix(pos=(-12,0,0), axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))
spring2 = helix(pos=block1.pos, axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))
spring3 = helix(pos=block2.pos, axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))

x1 = 2.
x2 = -1.
x3 = 0.
k = 1.
m = 5.
dt = 0.1
v1 = 0.
v2 = 0.

while True:
    rate(100)
    a1 = k/m *(x2 - 2*x1)
    a2 = k/m *(x3 - 2*x2 + x1)

    v1 += a1*dt
    x1 += v1*dt
    v2 += a2*dt
    x2 += v2*dt

    block1.pos.x = x1 -4
    block2.pos.x = x2 +4

    spring2.pos = block1.pos
    spring3.pos = block2.pos
    spring1.axis = block1.pos.x - wall1.pos.x
    spring2.axis = block2.pos.x - block1.pos.x
    spring3.axis = wall2.pos.x - block2.pos.x


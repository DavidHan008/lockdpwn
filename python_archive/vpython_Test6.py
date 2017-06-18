#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 구슬이 자유낙하하는 궤적 + 속도를 애니메이션한 코드
                https://youtu.be/H8CzQtx9vds
'''
from visual import *
from math import *

#scene.range = (8,17,10)
#scene.center = (3,-2,0)
#scene.width = 800
#scene.height = 500
#scene.background = (.5,.5,.5)

bola = sphere(pos=(-5,18,0), radius=1, color=color.green)
piso = box(pos=(0,-9,0), size=(25,0.5,25))

v = vector(0.7, 0,0)
y = bola.pos
g = vector(0, -10, 0)
dt = 0.005
t = 0.0

bola.trail = curve(color=bola.color)
seta = arrow(pos=bola.pos, axis=v, color=color.yellow)

while True:
    rate(300)
    v += g*dt
    y += v*dt + 0.5*g*dt**2

    if bola.pos.y < (piso.pos.y + 1):
        v.y = -v.y

    bola.pos = y
    bola.trail.append(pos = bola.pos)
    seta.pos = bola.pos
    seta.axis = v*0.3

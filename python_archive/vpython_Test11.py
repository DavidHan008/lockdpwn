#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 물체의 자유낙하 + 바닥에 탄성충돌 운동을 x,v,a 그래프로 애니메이션해 본 코드
'''
from visual import *
from visual.graph import *

display(autoscale=False)

size = 0.2  # m
g = -9.81
t = 0
dt = 0.0001   # 0.01s

ant = sphere(radius=size, color=color.white)
ant.pos = (0,0,0)
ant.v = vector(0,10,0)

bottom = box(pos=(0,-size,0), length=5, heigth=0.1, width=5, material=materials.wood)

gd = gdisplay(x=450, y=0, title='y vs t', xtitle='t', ytitle='x', ymax=6, ymin=-6, xmax=10)
gd2 = gdisplay(x=450, y=200, title='v vs t', xtitle='t', ytitle='vel', ymax=20, ymin=-20, xmax=10)
gd3 = gdisplay(x=450, y=400, title='a vs t', xtitle='t', ytitle='acc', ymax=10, ymin=-10, xmax=10)

xt = gcurve(gdisplay=gd, color=color.cyan)
vt = gcurve(gdisplay=gd2, color=color.cyan)
at = gcurve(gdisplay=gd3, color=color.cyan)

while True:
    rate(10000)
    t += dt

    if ant.pos.y <= 0:
        ant.v.y = abs(ant.v.y)

    xt.plot(pos=(t, ant.pos.y))
    vt.plot(pos=(t,ant.v.y))
    at.plot(pos=(t,g))

    ant.pos += ant.v*dt
    ant.v.y += g*dt

    if t >= 10: 
        break

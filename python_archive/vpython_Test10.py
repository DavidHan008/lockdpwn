#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 진자의 원운동을 그래프를 통해 애니메이션한 코드
'''
from visual import *
from visual.graph import *

scene = display(width=600, height=600, fov = 0.01*pi)
gd = gdisplay(x=600, y=0, title='x v.s. t', xtitle='t', ytitle='x', ymax=1, ymin=-1, xmax=10, background=(.3,.3,.3))
xt = gcurve(gdisplay=gd, color=color.orange, size=20, dot=False)

wall = box(pos=(0,1,-2), length=4, height=3, width=0.01)
ball = sphere(pos=(-1,0,0), radius=0.1, make_trail=True)

ball.a = 3
ball.w = abs(ball.a)/abs(ball.pos)
shadow = cylinder(axis=(0,0,wall.width), radius=ball.radius, color=(0.1,0.1,0.1))
shadow.pos.z = wall.pos.z
label1 = label()
label2 = label()

disk = cylinder(axis=(0,0.01,0), radius=1.5, material=materials.silver)
disk.pos.y = -ball.radius

number = 4000
l = [0]*number
m = [0]*number
line = curve(y=linspace(0,2.5,number), z=-2+0.01, color=color.black)

t = 0
dt = 0.001

while True:
    rate(100)
    t += dt
    ball.pos = rotate(ball.pos, ball.w*dt, (0,1,0))
    shadow.pos.x = ball.pos.x
    xt.plot(pos=(t,ball.pos.x))
    label1.pos = ball.pos + vector(0,0.2,0)
    label1.text = '(%1.2f, %1.2f, %1.2f)' % (ball.pos.x, ball.pos.y,ball.pos.z)
    label2.pos = shadow.pos + vector(0,0.2,0)
    label2.text = '(%1.2f)' % (shadow.pos.x)

    l.append(ball.pos.x)
    l.pop(0)

    for j in range(number):
        m[number-1-j] = l[j]

    line.x = array(m)
    if t > 10:
        break



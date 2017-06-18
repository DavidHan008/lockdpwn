#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 스프링 + 질량 시스템을 마찰력을 고려해서 애니메이션한 코드 (T+U = E 전부 그래픽으로 표현했다)

                    https://youtu.be/UoN70GjnBTI
'''
from visual import *

dt = 0.0001
m = 0.5
k = 20.0
v0 = 4.0
#mu_k = 0.1
#mu_s = 0.5
#g = 9.81

scene = display(width=600, height=600, background=(0.5,0.6,0.5))
bottom = box(length=3, height=0.01, width=1, material=materials.silver)
wall = box(length=0.01, height=0.5, width=1, material=materials.silver)

square = box(length=0.2, height=0.2, width=0.2, material=materials.wood)
spring = helix(pos=(-bottom.length/2, 0,0), coils=15, radius=0.08,  thickness=0.02)

bottom.pos = (0, -square.height/2, 0)
wall.pos = (-bottom.length/2, 0.5/2-square.height/2, 0)
square.vx = v0

rod_k = cylinder(pos=(-bottom.length/2, -0.5,0), axis=(0.1,0,0), radius=0.05, opacity=0.5)
rod_u = cylinder(pos=(-bottom.length/2, -0.7,0), axis=(0.1,0,0), radius=0.05, opacity=0.5)
rod_e = cylinder(pos=(-bottom.length/2, -0.9,0), axis=(0.1,0,0), radius=0.05, opacity=0.5)

label_k = label(pos=(-bottom.length/2-0.1, -0.5, 0), text='K')
label_u = label(pos=(-bottom.length/2-0.1, -0.7, 0), text='U')
label_e = label(pos=(-bottom.length/2-0.1, -0.9, 0), text='E')

label1 = label()
label2 = label()
label3 = label()


while True:
    rate(2000)

    square.a = -(k/m) * square.pos.x

#   if square.vx * (square.vx + square.a*dt) > 0:
#       square.a = (-k/m)*square.pos.x - mu_k*g*abs(square.vx)/square.vx
#   elif abs(k*square.pos.x) > mu_s*m*g:
#       square.a = -(k/m)*square.pos.x
#   else:
#       square.a = 0

    square.vx += square.a*dt
    square.pos.x += square.vx*dt

    spring.length = (square.pos.x - square.length/2) - spring.pos.x

    rod_k.axis.x = 0.5*m*square.vx**2/5    # 왜 5로 나누지? 스케일을 줄이기 위해!
    rod_u.axis.x = 0.5*k*square.pos.x**2/5
    rod_e.axis.x = rod_k.axis.x + rod_u.axis.x

    label1.pos = bottom.pos + vector(0,-0.1,0)
    label1.text = 'box position is : %.2f' % square.pos.x
    label2.pos = bottom.pos + vector(0,-0.3,0)
    label2.text = 'box length is : %.2f ' % square.length
    label3.pos = bottom.pos + vector(1.2,-0.1,0)
    label3.text = 'm : %.2f kg, k : %.2f N/m' % (m,k)

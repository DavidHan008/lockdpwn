#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 이용해 두 물체의 충돌을 애니메이션해 본 코드
                https://youtu.be/l5IiPG5_Xa0

'''
from visual import *

size = 0.07
scene = display(width=600, height=600, x=0, y=0, background=(0.5,0.6,0.5))

b1 = sphere(radius = size, color=color.yellow, make_trail=True, trail_type="points", interval=100)
b2 = sphere(radius = size, color=color.green, make_trail=True, trail_type="points", interval=100)
b1.m = 1.0
b2.m = 1.0

rod_1 = cylinder(pos=(-0.1,-0.4,0), axis=(0.1,0,0), radius=0.05)
rod_2 = cylinder(pos=(-0.1,-0.6,0), axis=(0.1,0,0), radius=0.05)
rod_e = cylinder(pos=(-0.1,-0.8,0), axis=(0.1,0,0), radius=0.05)

label_1 = label(pos=(-0.2,-0.4,0), text='K1')
label_2 = label(pos=(-0.2,-0.6,0), text='K2')
label_e = label(pos=(-0.2,-0.8,0), text='E')

def vcollision(b1, b2):
    v1prime = b1.v - (2*b2.m)/(b1.m+b2.m)*(b1.pos-b2.pos) * dot(b1.v - b2.v, b1.pos-b2.pos) / abs(b1.pos - b2.pos)**2
    v2prime = b2.v - (2*b1.m)/(b1.m+b2.m)*(b2.pos-b1.pos) * dot(b2.v-b1.v, b2.pos-b1.pos)/abs(b2.pos - b1.pos)**2
    return v1prime, v2prime

b1.pos = vector(0.55, 0.075, 0)
b2.pos = vector(0,0,0)
b1.v = vector(-0.2, 0,0)
b2.v = vector(0,0,0)

dt= 0.001

while abs(b1.pos-b2.pos) < 1.2:
    rate(1000)

    b1.pos += b1.v * dt
    b2.pos += b2.v * dt

    if abs(b1.pos - b2.pos) <= 2*size and dot(b1.pos-b2.pos, b1.v-b2.v) <= 0:
            b1.v, b2.v = vcollision(b1, b2)

    rod_1.axis.x = 0.5*b1.m*abs(b1.v)**2 * 5
    rod_2.axis.x = 0.5*b2.m*abs(b2.v)**2 * 5
    rod_e.axis.x = rod_1.axis.x + rod_2.axis.x




#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 Spring, Mass System의 운동을 그래픽으로 표현한 코드

                code from https://www.youtube.com/watch?v=9n8XCwCmBho
'''
from __future__ import division, print_function
from visual import *

Lo = 4
Lvec = vector(0,3,0)
Lhat = vector(0,1,0)
Ks = 7
Pi = vector(0,0,0)
Blockm = 1.3
g = vector(0, -9.8, 0)

time = 0
deltaT = 0.01

spring = helix(pos=(0,0,0), axis=(0,3,0), radius=.5)
block = box(pos= (0,3,0), size = (1.2,1,1.2), color=color.blue)
track = box(pos=(0,-0.5,0), size=(4,1,1))

while time < 10:
    rate(100)  # frequency, Hz
    time = time + deltaT
    Fearth = Blockm * g
    Lmag = abs(Lvec.y)
    Fs = (-Ks) * (Lmag - Lo) * Lhat
    Fnet = Fs + Fearth
    Pf = Pi + (Fnet * deltaT)
    Pi = Pf
    Vavg = Pf/ Blockm
    Xf = Lvec + Vavg * deltaT
    Lvec = Xf
    spring.axis = Xf
    block.pos = Xf

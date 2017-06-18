'''
    python ==> vpython을 사용해 spring + mass 시스템의 동역학을 애니메이션 해 본 코드 

            code from https://www.youtube.com/watch?v=c3tX_qReGIM
'''
from visual import *

g = 9.81

scene = display(background = (0.36, 0.47, 0.23), center = vector(0, -0.7, -0.5))
ceiling = box(length = 1, width = 1, height = 0.01, material = materials.wood, color = color.orange)

ball = sphere(radius = 0.1, color = color.green, opacity=0.8)
ball.pos = vector(0, -0.5, 0)
ball.m = 0.5
ball.v = vector(0,0,0)

spring = helix(coils = 15, radius = 0.05, thickness = 0.01)
spring.pos = ceiling.pos
spring.axis = ball.pos - spring.pos
spring.L = abs(ball.pos)
spring.k = 10.0

label1 = label()
label2 = label()
label3 = label()

def spring_F(spring):
    return -spring.k * (spring.length - spring.L) * spring.axis.norm()

dt = 0.01
t = 0

while True:
    rate(100)

    F = spring_F(spring)

    ball.a = vector(0, -g, 0) + F / ball.m
    ball.v += ball.a * dt
    ball.pos += ball.v  * dt

    spring.axis = ball.pos - spring.pos

    t += dt

    label1.pos = ceiling.pos + vector(0.5,0.2,0)
    label1.text = ('position is : %1.2f' % ball.pos.y)
    label2.pos = ceiling.pos + vector(0.5,0.05,0)
    label2.text = ('velocity is : %1.2f' % ball.v.y)
    label3.pos = ceiling.pos + vector(0.5,-0.10,0)
    label3.text = ('acc is : %1.2f' % ball.a.y)

    #if ball.v.y >= 0 and ball.v.y + ball.a.y * dt <= 0:
     #   print (t)


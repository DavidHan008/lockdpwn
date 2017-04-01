#-*- coding: utf-8 -*-
'''
    python ==> 시스템최신기술, LED 1개가 켜진 후 스위치를 누른 시간차이를 계산하는 코드
'''
import RPi.GPIO as GPIO
import time
import random

pin=[7,11,12,13,15,18,29,31,32,33]

GPIO.setmode(GPIO.BOARD)
GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setwarnings(False)

def setup(p):
    GPIO.setup(pin[p], GPIO.OUT)

def out(p, v):
    GPIO.output(pin[i], v)

for i in range(0, len(pin)):
    setup(i)

for i in range(0, len(pin)):
    out(i, 0)


while True:
    rand= random.randint(5,10)
    time.sleep(rand)
    start = time.time()
    out(1,1)

    if(GPIO.wait_for_edge(16, GPIO.RISING)):
        out(1,0)
        end = time.time()
        print("%f second spent!" %(end-start))

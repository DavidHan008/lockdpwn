#-*- coding: utf-8 -*-
'''
    python ==> 시스템최신기술, LED 10개를 연쇄적으로 불이 들어왔다 꺼지게 하는 코드
'''
import RPi.GPIO as GPIO
import time

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
    for i in range(0, len(pin)):
        out(i, 1);
        time.sleep(0.1)

    for i in range(len(pin)-1, -1, -1):
        out(i, 0);
        time.sleep(0.1)

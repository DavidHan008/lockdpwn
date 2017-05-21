#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
<<<<<<< HEAD
<<<<<<< HEAD
    python ==> 비주얼컴퓨팅, LBP 알고리즘을 학습해본 코드 
                            Local Binary Pattern
                            1 2 3
                            4 5 6
                            7 8 9 
                                  이런 3x3 필터를 만들어서 중앙 5점을 중심으로 주변 값이 크면 1, 작으면 0을 넣어서 새로운 사진을 만들어봤다.
=======
	python ==>
>>>>>>> 5d5e02a825b684d91025e9d5d60f1fb2a8ef6b25
'''
# license removed for brevity

<<<<<<< HEAD
import numpy as np
import cv2

file_name = './twicesana.jpg'
img = cv2.imread(file_name, 0)
rows, cols = img.shape
lbp_img = np.zeros(((rows -1 )//2, (cols -1)//2), np.uint8)

# 한 점으로부터 3x3의 픽셀데이터를 반환하는 함수 
def neighborpixels(img, x, y):
    npixels = []

    npixels.append(img[x-1, y-1])
    npixels.append(img[x, y-1])
    npixels.append(img[x+1, y-1])
    npixels.append(img[x-1, y])
    npixels.append(img[x+1, y])
    npixels.append(img[x-1, y+1])
    npixels.append(img[x, y+1])
    npixels.append(img[x+1, y+1])

    return np.array(npixels)


# 중앙 center 점보다 neighbor_p 값이 크면 1을, 아니면 0을 반환하는 함수
def thresholded(center, neighbor_p):
    out = []
    for a in neighbor_p:
        if a >= center:
            out.append(1)
        else:
            out.append(0)

    return out



# LBP 메인 알고리즘
for x in range(1, rows-1, 3):
    for y in range(1, cols -1, 3):
        center = img[x,y]   # 중앙 픽셀값을 받아온다
        neighbor_p = neighborpixels(img, x, y)  # 주변 점들의 값을 받아온다
        values = thresholded(center, neighbor_p) # center 점보다 주변값이 크면 1 아니면 0 을 반환한다

        weights = [1,2,4,8,16,32,64,128]
        res = 0

        for a in range(0, len(values)):
            res += weights[a] + values[a]
            lbp_img.itemset((x//2, y//2), res)


cv2.imshow('image', img)
cv2.imshow('lbp image', lbp_img)

cv2.waitKey(0)
cv2.destroyAllWindows()
=======
import rospy
from dataservice.msg import TimeData
from barc.msg import SPEED
from math import pi, sin
import time
import serial
from numpy import zeros ,hstack ,cos ,array ,dot ,arctan
from manuevers import TestSettings , StraightBrake

=======
	python ==>
'''
# license removed for brevity

import rospy
from dataservice.msg import TimeData
from barc.msg import SPEED
from math import pi, sin
import time
import serial
from numpy import zeros ,hstack ,cos ,array ,dot ,arctan
from manuevers import TestSettings , StraightBrake

>>>>>>> 5d5e02a825b684d91025e9d5d60f1fb2a8ef6b25
def driver():
	pub = rospy.Publisher('speed', SPEED, queue_size = 10)
	rospy.init_node('driver', anonymous=True)

	rateHz = 50
	dt = 1.0 /rateHz
	rate = rospy.Rate(rateHz)
	t_i  = 0

	speed = rospy.get_param("driver/speed")
	t_0 = rospy.get_param("driver/t_0")
	t_exp = rospy.get_param("driver/t_exp")

	opt = TestSettings(SPD = speed, turn=0, dt =t_exp)
	opt.t_0 = t_0

	while not rospy.is_shutdown():
		(motorCMD, _) = StraightBrake(opt, rateHz, t_i)
		pub.publish(SPEED(motorCMD))
		rate.sleep()
		t_i += 1



if __name__ == '__main__':
	try:
		driver()
	except rospy.ROSInterruptException:
		pass
<<<<<<< HEAD
>>>>>>> 5d5e02a825b684d91025e9d5d60f1fb2a8ef6b25
=======
>>>>>>> 5d5e02a825b684d91025e9d5d60f1fb2a8ef6b25

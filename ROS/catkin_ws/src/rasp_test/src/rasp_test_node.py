#!/usr/bin/env python
'''
    python ==> ROS, mylab  오드로이드와 라즈베리파이 통신용 코드
'''
import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float32
import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BOARD)
GPIO.setup(8,GPIO.OUT)

TRIG = 11
ECHO = 12

GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)

pwm = GPIO.PWM(8, 50)   
pwm.start(7.5) 

GPIO.output(TRIG,False)

def calculateDistance():
	GPIO.output(TRIG,True)
	time.sleep(0.00001)
	GPIO.output(TRIG,False)
	
	while GPIO.input(ECHO) == 0:
	    pulse_start = time.time()
	
	while GPIO.input(ECHO) == 1:
	    pulse_end = time.time()
	
	pulse_duration = pulse_end - pulse_start
	
	distance = pulse_duration * 17150
	distance = round(distance, 2)

	return distance


def setServo(data):
	serv = data.data


def rosTest():
	rospy.init_node('rasp_py_test_node', anonymous=True)
	rate = rospy.Rate(10)
	rospy.Subscriber('setServoAngle', Int32, setServo)
	pub = rospy.Publisher('getUltraData', Float32, queue_size=10)

try:
	rosTest()
	while not rospy.is_shutdown():
		dist = calculateDisatnce()
		pub.publish(dist)
		
		pwm.ChangeDutyCycle(serv)  # 90 deg
		print "angle: ", serv, " cm"
		
		rate.sleep()

except KeyboardInterrupt:
	pwm.stop()
	GPIO.cleanup()





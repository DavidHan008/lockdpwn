#!/usr/bin/env python
'''
    python ==> ROS, mylab  오드로이드와 라즈베리파이 통신용 코드
'''
import rospy
from std_msgs.msg import Float32
from std_msgs.msg import Int32

ult = 0

def getUltra(data):
	ult = data.data


rospy.init_node('odroid_py_test_node', anonymous=True)
rate = rospy.Rate(10)
rospy.Subscriber('getUltraData', Int32, getUltra)
pub = rospy.Publisher('setServoAngle', Int32, queue_size=10)

while not rospy.is_shutdown():
		pub.publish(ult)
		rate.sleep()
		print "ult : " , ult



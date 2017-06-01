#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32
from std_msgs.msg import Int32

ult = 0

def getUltra(data):
	ult = data.data


def rosTest():
	rospy.init_node('odroid_py_test_node', anonymous=True)
	rate = rospy.Rate(10)
	rospy.Subscriber('getUltraData', Float32, getUltra)
	pub = rospy.Publisher('setServoAngle', Int32, queue_size=10)

rosTest()
while not rospy.is_shutdown():
	if ult > 2.5 and ult < 12.5:
		pub.publish(ult)
		rate.sleep()


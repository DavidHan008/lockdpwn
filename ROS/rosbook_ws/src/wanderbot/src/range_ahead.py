#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> ROS programming, turtlebot gazebo에서 로봇이 센서를 통해 몇 m앞에 물체가 있는지 확인해보는 코드
'''
import rospy
from sensor_msgs.msg import LaserScan

def scan_callback(msg):
	range_ahead = msg.ranges[len(msg.ranges) /2 ]
	print "range ahead: %0.1f" % range_ahead


rospy.init_node('range_ahead')
scan_sub = rospy.Subscriber('scan', LaserScan, scan_callback)
rospy.spin()

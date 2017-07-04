#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> ROS programming, 퍼블리셔의 데이터를 받아오는 섭스크라이버를 구현한 코드
'''
import rospy
from std_msgs.msg import Int32

def callback(msg):
    print msg.data

rospy.init_node('topic_subscriber')
sub = rospy.Subscriber('counter', Int32, callback)

rospy.spin()


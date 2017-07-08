#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> ROS programming, R2 로봇의 팔을 moveit을 사용해 랜덤으로 움직여보는 코드
'''
import sys, rospy, tf, moveit_commander, random
from geometry_msgs.msg import Pose, Point, Quaternion
from math import pi

# 오일러각을 쿼터니안으로 변형시킨 후 orient변수에 저장한다
orient = [Quaternion(*tf.transformations.quaternion_from_euler(pi, -pi/2, -pi/2)),
          Quaternion(*tf.transformations.quaternion_from_euler(pi, -pi/2, -pi/2))]

# Pose 메세지를 설정한다
pose = [Pose(Point(0.5, -0.5, 1.3), orient[0]),
         Pose(Point(-0.5, -0.5, 1.3), orient[1])]


# moveit_commander는 무브잇 모션플래너로 파이썬 인터페이스이다
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('r2_wave_arm', anonymous=True)
group = [moveit_commander.MoveGroupCommander("left_arm"),
		 moveit_commander.MoveGroupCommander("right_arm")]


# 이제 팔을 주변에 무작위로 흔든다
while not rospy.is_shutdown():
	pose[0].position.x = 0.5 + random.uniform(-0.1, 0.1)
	pose[1].position.x = -0.5 + random.uniform(-0.1, 0.1)

	for side in [0,1]:
		pose[side].position.z = 1.5 + random.uniform(-0.1, 0.1)
		group[side].set_pose_target(pose[side])
		group[side].go(True)

moveit_commander.roscpp_shutdown()

#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> ROS programming,
'''
import sys, rospy, tf, moveit_commander, random
from geometry_msgs.msg import Pose ,Point, Quaternion

class R2Hand:
	def __init__(self):
		self.left_hand = moveit_commander.MoveGroupCommander("left_hand")

	def setGroup(self, state):
		if state == "pre-pinch":
			vec = [0.3, 0, 1.57, 0,     # 검지
			        -0.1, 0, 1.57, 0,   # 중지
			          0,0,0,            # 약지
			          0,0,0,            # 새끼
			           0, 1.1, 0, 0]    # 엄지
		elif state == "pinch":
			vec = [-0.1, 0, 1.57, 0,
			       0, 0, 1.57, 0,
			        0, 0, 0,
			        0, 0, 0,
				   0, 1.1, 0, 0]
		elif state == "open":
			vec = [0] * 18
		else:
			raise ValueError("unknown hand state: %s" % state)

		self.left_hand.set_joint_value_target(vec)
		self.left_hand.go(True)


if __name__ == '__main__':
	moveit_commander.roscpp_initialize(sys.argv)
	rospy.init_node('r2_hand')
	argv = rospy.myargv(argv = sys.argv)

	if len(argv) != 2:
		print "usage: r2_hand.py STATE"
		sys.exit(1)

	r2w = R2Hand()
	r2w.setGroup(argv[1])

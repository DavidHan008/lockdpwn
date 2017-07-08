#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> ROS programming, 터미널에서 파라미터를 통해 R2의 팔을 움직여보는 코드
'''
import sys, rospy, tf, moveit_commander, random
from geometry_msgs.msg import Pose, Point, Quaternion

class R2Wrapper:
	def __init__(self):
		self.group = {'left' : moveit_commander.MoveGroupCommander("left_arm"),
					  'right':moveit_commander.MoveGroupCommander("right_arm")}

	def setPose(self, arm, x, y, z, phi, theta, psi):
		if arm != 'left' and arm != 'right':
			raise ValueError("unknown arm: '%s'" % arm)

		orient = Quaternion(*tf.transformations.quaternion_from_euler(phi, theta, psi))

		pose = Pose(Point(x,y,z), orient)
		self.group[arm].set_pose_target(pose)
		self.group[arm].go(True)


if __name__ == '__main__':
	moveit_commander.roscpp_initialize(sys.argv)
	rospy.init_node('r2_cli', anonymous=True)

	# ROS에서 사용하는 인자를 사용
	argv = rospy.myargv(argv=sys.argv)

	if len(argv) != 8:
		print "usage: r2_cli.py arm X Y Z phi theta psi"
		sys.exit(1)

	r2w = R2Wrapper()
	r2w.setPose(argv[1], *[float(num) for num in sys.argv[2:]])

	moveit_commander.roscpp_shutdown()

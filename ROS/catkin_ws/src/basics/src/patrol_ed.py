#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> ROS programming, 액션을 사용해 터틀봇을 순찰시키는 코드

                                $ roslaunch turtlebot_stage tuetlebot_in_stage.launch
                                $ rosrun ... patrol.py
'''
import rospy
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal

# 로봇이 순찰해야하는 경유지점들의 목록
waypoints = [
	[(2.1, 2.2, 0.0), (0.0, 0.0, 0.0, 1.0)],
	[(6.5, 4.43, 0.0), (0.0, 0.0, -0.984047240305, 0.177907360295)]
]

# 경유지점을 MoveBaseGoal로 바꾸는 함수
def goal_pose(pose):
	goal_pose = MoveBaseGoal()

	goal_pose.target_pose.header.frame_id = 'map'
	goal_pose.target_pose.pose.position.x = pose[0][0]
	goal_pose.target_pose.pose.position.y = pose[0][1]
	goal_pose.target_pose.pose.position.z = pose[0][2]

	goal_pose.target_pose.pose.orientation.x = pose[1][0]
	goal_pose.target_pose.pose.orientation.y = pose[1][1]
	goal_pose.target_pose.pose.orientation.z = pose[1][2]
	goal_pose.target_pose.pose.orientation.w = pose[1][3]

	return goal_pose


if __name__ == '__main__':
	rospy.init_node('patrol')

	# 액션 클라이언트를 생성한다
	client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
	client.wait_for_server()

	# 각 경유지점을 액션 목표 메세지로 만들어 보내며 반복한다
	while True:
		for pose in waypoints:
			goal = goal_pose(pose)
			client.send_goal(goal)
			client.wait_for_result()

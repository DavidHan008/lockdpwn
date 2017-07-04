#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> ROS programming, 간단한 Timer action 서버를 구현한 코드
'''
import rospy
import time
import actionlib
from basics.msg import TimerAction, TimerGoal, TimerResult



def do_timer(goal):
    start_time = time.time()
    time.sleep(goal.time_to_wait.to_sec())

    # TimerResult 자료형인 결과 메세지를 만든다
    result = TimerResult()
    result.time_elapsed = rospy.Duration.from_sec(time.time() - start_time)
    result.updates_sent = 0

    # 목표를 성공적으로 달성했음을 SimpleActionServer에 알린다
    server.set_succeeded(result)



rospy.init_node('timer_action_server')
server = actionlib.SimpleActionServer('timer', TimerAction, do_timer, False)
server.start()
rospy.spin()

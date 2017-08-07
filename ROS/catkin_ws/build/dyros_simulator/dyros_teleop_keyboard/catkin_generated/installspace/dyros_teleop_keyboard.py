#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> dyros, 키보드를 통해 가제보로 Twist 메세지를 퍼블리시하는 코드
'''

import roslib; roslib.load_manifest('dyros_teleop_keyboard')
import rospy
import sys, select, termios, tty

from geometry_msgs.msg import Twist
from std_msgs.msg import Bool         ## ed: 자동주차를 위해 추가한 메시지
from dbw_mkz_msgs.msg import GearCmd  ## ed: 기어를 바꾸기 위해 추가한 메세지


## ed: 자동추차를 위한 토글변수 선언
mode_toggle = False


msg = """
Reading from the keyboard  and Publishing to Twist!
---------------------------
Moving around:
   u    i    o
   j    k    l
   m    ,    .

For Holonomic mode (strafing), hold down the shift key:
---------------------------
   U    I    O
   J    K    L
   M    <    >

t : up (+z)
b : down (-z)

anything else : stop

q/z : increase/decrease max speeds by 10%
w/x : increase/decrease only linear speed by 10%
e/c : increase/decrease only angular speed by 10%

CTRL-C to quit
"""

moveBindings = {
		'i':(1,0,0,0),
		'o':(1,0,0,-1),
		'j':(0,0,0,1),
		'l':(0,0,0,-1),
		'k':(0,0,0,0),
		'u':(1,0,0,1),

## ed: 후진용 코드 수정
		',':(1,0,0,0),
		'.':(1,0,0,-1),
		'm':(1,0,0,1),


		'O':(1,-1,0,0),
		'I':(1,0,0,0),
		'J':(0,1,0,0),
		'L':(0,-1,0,0),
		'U':(1,1,0,0),
		'<':(-1,0,0,0),
		'>':(-1,-1,0,0),
		'M':(-1,1,0,0),
		't':(0,0,1,0),
		'b':(0,0,-1,0),
	       }

speedBindings={
		'q':(1.1,1.1),
		'z':(.9,.9),
		'w':(1.1,1),
		'x':(.9,1),
		'e':(1,1.1),
		'c':(1,.9),
	      }

def getKey():
	tty.setraw(sys.stdin.fileno())
	select.select([sys.stdin], [], [], 0)
	key = sys.stdin.read(1)
	termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
	return key



def vels(speed,turn):
	return "currently:\tspeed %s\tturn %s " % (speed,turn)



if __name__=="__main__":
	rospy.init_node('dyros_teleop_keyboard')
	settings = termios.tcgetattr(sys.stdin)

	## ed: 기어 변경용 퍼블리셔
	pub_gear = rospy.Publisher('dyros/gear_cmd', GearCmd, queue_size=1)
	pub = rospy.Publisher('/dyros/cmd_vel', Twist, queue_size = 1)

    ## ed: 자동주차의 모드 ON/OFF를 토글하는 퍼블리셔 선언
	mode_pub = rospy.Publisher('/dyros/mode_Toggle', Bool, queue_size = 1)


	gc = GearCmd()
	speed = rospy.get_param("~speed", 0.5)
	turn = rospy.get_param("~turn", 1.0)
	x = 0
	y = 0
	z = 0
	th = 0
	status = 0

	try:
		print msg
		print vels(speed,turn)
		while(1):
			key = getKey()

			if key in moveBindings.keys():
				## ed: 후진용 코드 추가
				if key == ',' or key == '.' or key == 'm':
					gc.cmd.gear = 2   ## ed: Reverse
				elif key =='k' or key == 'j' or key =='l':
					gc.cmd.gear = 1   ## ed : Park
				else:
					gc.cmd.gear = 4   ## ed: Drive

				x = moveBindings[key][0]
				y = moveBindings[key][1]
				z = moveBindings[key][2]
				th = moveBindings[key][3]

			elif key in speedBindings.keys():
				speed = speed * speedBindings[key][0]
				turn = turn * speedBindings[key][1]

				print vels(speed,turn)
				if (status == 14):
					print msg
				status = (status + 1) % 15
			else:
				x = 0
				y = 0
				z = 0
				th = 0
				if (key == '\x03'):
					break

			## ed: 자동주차용 코드 추가
			if key == 'p':
				if mode_toggle == True:
					mode_toggle = False
				elif mode_toggle == False:
					mode_toggle = True

				print "[*] Parking Mode : %r" % mode_toggle
				mode_pub.publish(mode_toggle)


			twist = Twist()
			twist.linear.x = x*speed; twist.linear.y = y*speed; twist.linear.z = z*speed;
			twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = th*turn
			pub.publish(twist)
			pub_gear.publish(gc)

	except:
		print e

	finally:
		twist = Twist()
		twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
		twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0
		pub.publish(twist)
		pub_gear.publish(gc)

    	termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

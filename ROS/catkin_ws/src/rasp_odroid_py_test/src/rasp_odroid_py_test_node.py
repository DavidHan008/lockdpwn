from rospy import init_node, Subscriber, Publisher, get_param
from rospy import Rate, is_shutdown, ROSInterruptException
from numpy import pi
import rospy
from std_msgs.msg import Int32


def ultraData(data):
	rospy.loginfo("Ultra data is: [%d]", data.data)
	servo.data = data.data;

	if servo.data > 175:
		servo.data =175
	


def main_auto():
	init_node("rasp_odroid_py_test_node")

	nh = Publisher("setServoData", Int32 , queue_size=1000)
	Subscriber("getUltrasonicData", Int32, ultraData);

	rateHz = 50
	rate = Rate(rateHz)

	while not is_shutdown():
		nh.publish(servo)
		rate.sleep()


























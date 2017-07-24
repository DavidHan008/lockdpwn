#!/usr/bin/env python
#-*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String, Float64, Float32MultiArray
from geometry_msgs.msg import Twist, Pose
import sys, getopt, math

class cmdvel2gazebo:
    def __init__(self,ns):
        self.ns = ns
        rospy.init_node('cmdvel2gazebo', anonymous=True)

        # the format(ns) looks for the namespace in the ros parameter server, I guess
        rospy.Subscriber('cmd_vel'.format(ns), Twist, self.callback)


        ## ed: 서브스크라이버들 추가
        rospy.Subscriber('VelocityCtrlData'.format(ns), Float32MultiArray, self.callback_vel_ed)
        rospy.Subscriber('SteerAngleData'.format(ns), Float32MultiArray, self.callback_steer_ed)


                ## ed: 최종적으로 gazebo로 퍼블리시되는 값들
        self.pub_steerL = rospy.Publisher('front_left_steering_position_controller/command'.format(ns), Float64, queue_size=1)
        self.pub_steerR = rospy.Publisher('front_right_steering_position_controller/command'.format(ns), Float64, queue_size=1)
        self.pub_rearL = rospy.Publisher('joint1_velocity_controller/command'.format(ns), Float64, queue_size=1)
        self.pub_rearR = rospy.Publisher('joint2_velocity_controller/command'.format(ns), Float64, queue_size=1)



        # initial velocity and tire angle are 0
        self.x = 0
        self.z = 0

        # TODO: get wheelbase and treadwidth from SDF or 
        #       params database instead of hardcoded here

        # car Wheelbase (in m)
        # simulator value matches the 'real' car
        ## ed: 휠베이스
        self.L = 2.62

        # car Tread
        # this value is from the car's manual
        # self.T=1.55

        # car Tread
        # this value is from the simulator
        ## ed: 차량 트레드 길이
        self.T=1.301

        # how many seconds delay for the dead man's switch
        # TODO: set timeout from launch file or rosparam
        self.timeout=rospy.Duration.from_sec(0.2);
        self.lastMsg=rospy.Time.now()

        ## ed: maxsteerInside 값이 0.6 rad == 34 deg로 정해져있는듯하다
        # we want maxsteer to be that of the "inside" tire, and since it is 0.6 in gazebo, we
        # set our ideal steering angle max to be less than that, based on geometry
        self.maxsteerInside=0.6;
        # tan(maxsteerInside) = wheelbase/radius --> solve for max radius at this angle
        rMax = self.L/math.tan(self.maxsteerInside);
        # radius of inside tire is rMax, so radius of the ideal middle tire (rIdeal) is rMax+treadwidth/2
        rIdeal = rMax+(self.T/2.0)
        # tan(angle) = wheelbase/radius
        self.maxsteer=math.atan2(self.L,rIdeal)
        # the ideal max steering angle we can command is now set
        rospy.loginfo(rospy.get_caller_id() + " maximum ideal steering angle set to {0}.".format(self.maxsteer))


    ## ed: 속도를 입력받는 함수 추가
    def callback_vel_ed(self, vel):
        self.x = 2.8101* vel.data[0]
        #print("vel: %lf, %lf" % (vel.data[0], vel.data[1]))

        self.lastMsg = rospy.Time.now()


    ## ed: 각도를 입력받는 함수 추가
    def callback_steer_ed(self, steer):
        self.z = max(-self.maxsteer, min(self.maxsteer, steer.data[0]))
        #print("steer %lf" % steer.data[0])

        self.lastMsg = rospy.Time.now()


    ## ed: data는 Twist 메세지다
    def callback(self,data):
        # 2.8101 is the gain factor in order to account for mechanical reduction of the tyres
        ## ed: 휠의 반지름이 0.356m = 1/2.81이므로 2.81을 곱해준다. 굳굳
        self.x = 2.8101*data.linear.x

        ## ed: z는 최대조향각인듯 하다
        # constrain the ideal steering angle such that the ackermann steering is maxed out
        self.z = max(-self.maxsteer,min(self.maxsteer,data.angular.z))
        self.lastMsg = rospy.Time.now()


    def publish(self):
        # now that these values are published, we
        # reset the velocity, so that if we don't hear new
        # ones for the next timestep that we time out; note
        # that the tire angle will not change
        # NOTE: we only set self.x to be 0 after 200ms of timeout
        ## ed: 특정시간간격으로 서브스크라이브가 안되면 경고를 발생하고 속도를 0으로 하는듯하다
        if rospy.Time.now() - self.lastMsg > self.timeout:
            rospy.loginfo(rospy.get_caller_id() + " timed out waiting for new input, setting velocity to 0.")

            self.x = 0
            return

        if self.z != 0:
            T=self.T
            L=self.L

            ## ed: r = 휠베이스/tan(최대조향각)
            # self.v is the linear *velocity*
            r = L/math.fabs(math.tan(self.z))

            ## ed: T: car thread
            rL = r-(math.copysign(1,self.z)*(T/2.0));
            rR = r+(math.copysign(1,self.z)*(T/2.0))

            msgRearR = Float64()
            # the right tire will go a little faster when we turn left (positive angle)
            # amount is proportional to the radius of the outside/ideal
            msgRearR.data = self.x*rR/r;
            msgRearL = Float64()
            # the left tire will go a little slower when we turn left (positive angle)
            # amount is proportional to the radius of the inside/ideal
            msgRearL.data = self.x*rL/r;

            ## ed: 차량의 뒷바퀴 속도를 퍼블리시하는 코드
            #     타이어의 반지름이 0.356 = 1/2.8101이므로 이 값이 곱해져서  퍼블리시되는 것 같다. (m/s)
            self.pub_rearL.publish(msgRearL)
            self.pub_rearR.publish(msgRearR)

            msgSteerL = Float64()
            msgSteerR = Float64()

            ## ed: 차량의 스티어링값을 퍼블리시하는 코드
            #     L : wheel base
            # the left tire's angle is solved directly from geometry
            msgSteerL.data = math.atan2(L,rL)*math.copysign(1,self.z)
            self.pub_steerL.publish(msgSteerL)

            # the right tire's angle is solved directly from geometry
            msgSteerR.data = math.atan2(L,rR)*math.copysign(1,self.z)
            self.pub_steerR.publish(msgSteerR)

        else:
            # if we aren't turning, everything is easy!
            msgRear = Float64()
            msgRear.data = self.x;
            self.pub_rearL.publish(msgRear)
            self.pub_rearR.publish(msgRear)

            msgSteer = Float64()
            msgSteer.data = self.z

            self.pub_steerL.publish(msgSteer)
            self.pub_steerR.publish(msgSteer)


def usage():
    print('cmdvel2gazebo -n all_in_one')



def main(argv):
    # we eventually get the ns (namespace) from the ROS parameter server for this node
    ns=''
    node = cmdvel2gazebo(ns)
    rate = rospy.Rate(100) # run at 10Hz

    while not rospy.is_shutdown():
        node.publish()
        rate.sleep()



if __name__ == '__main__':
    main(sys.argv[1:])
    try:
        listener('all_in_one')
    except rospy.ROSInterruptException:
        pass



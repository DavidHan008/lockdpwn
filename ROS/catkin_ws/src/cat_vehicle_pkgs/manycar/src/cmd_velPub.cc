#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<sstream>
#include<iostream>
int main(int argc, char **argv)
{
    ROS_INFO_STREAM("\nargc=" << argc);
    if(argc != 4)
    {
        ROS_ERROR("Usage: rosrun manycar CarSimPub manycar1 4 0.1");
        return 0;
    }
    std::string topicName = std::string(argv[1]) + "/cmd_vel";
    ros::init(argc, argv, "CarSimPub");
    ros::NodeHandle ros_node;
    ros::Publisher pub = ros_node.advertise<geometry_msgs::Twist>(topicName, 100);

    ros::Rate rate(10);
    while(ros::ok())
    {
        geometry_msgs::Twist msg;
        msg.linear.x  = atof(argv[2]);
        msg.angular.z = atof(argv[3]);
        pub.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}

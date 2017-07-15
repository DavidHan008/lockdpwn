#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<nav_msgs/Odometry.h>
#include<gazebo_msgs/ModelStates.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
void modelRead(const gazebo_msgs::ModelStates::ConstPtr& msg)
{
    vector<string> modelNames;
    vector<geometry_msgs::Pose> poses;
    vector<geometry_msgs::Twist> twists;
    modelNames = msg->name;
    poses = msg->pose;
    twists = msg->twist;

    for(int i = 0; i < modelNames.size(); i++)
    {
        cout <<"\n---\n";
        cout << "\nModel Name: " << modelNames[i];
        cout << "\nPosition x: " << poses[i].position.x;
        cout << "\nPosition y: " << poses[i].position.y;
        cout << "\nPosition z: " << poses[i].position.z;
        cout << "\nOrientation x: " <<poses[i].orientation.x;
        cout << "\nOrientation y: " <<poses[i].orientation.y;
        cout << "\nOrientation z: " <<poses[i].orientation.z;
        cout << "\nOrientation w: " <<poses[i].orientation.w;

        cout << "\nTwist Linear x: " <<twists[i].linear.x;
        cout << "\nTwist Linear y: " <<twists[i].linear.y;
        cout << "\nTwist Linear z: " <<twists[i].linear.z;
        cout << "\nTwist Angular x: " <<twists[i].angular.x;
        cout << "\nTwist Angular y: " <<twists[i].angular.y;
        cout << "\nTwist Angular z: " <<twists[i].angular.z;

    }
}
int main(int argc, char**argv)
{
    ros::init(argc, argv, "odomstate");
    ros::NodeHandle nodehandle;
    ros::Subscriber sub = nodehandle.subscribe("gazebo/model_states", 1, modelRead);
    ros::spin();
    return 0;
}

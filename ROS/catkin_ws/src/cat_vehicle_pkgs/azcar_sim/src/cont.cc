#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <cstdio>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
// JMS added Wrench for steering info
#include "geometry_msgs/Wrench.h"
#include <gazebo/physics/Joint.hh>
#include <cstdlib>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include<iostream>
#include<string>
#include<vector>
#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<nav_msgs/Odometry.h>
#include "std_msgs/String.h"
#include "azcar_sim/cont.hh"
#include <tf/transform_broadcaster.h>

using namespace std;

//string logFile = "//home//"+std::string(getpwuid (getuid())->pw_name)+"//azcar_speed//vData.mat";
//fstream logOut(logFile.c_str(),ios_base::out | ios_base::app);

namespace gazebo
{
    CatSteering::CatSteering()
    {
    }
    void CatSteering::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {
        // Store the pointer to the model
        this->model = _parent;
        this->world = _parent->GetWorld();

        this->robotNamespace = "";
        // get namespace from launch file
        if (_sdf->HasElement("robotNamespace"))
        {
            this->robotNamespace = _sdf->GetElement("robotNamespace")->Get<std::string>();
        }  
        this->speedTopic = this->robotNamespace + "/vel";

    	this->tireTopic = this->robotNamespace + "/steering";

        this->odomTopic = this->robotNamespace + "/odom";

        this->tfScope = this->robotNamespace.substr(1,this->robotNamespace.size()-1);
        

        //Start up ros_node
        int argc = 0;
        char** argv = NULL;
        ros::init(argc, argv, "cat_sim", ros::init_options::NoSigintHandler | ros::init_options::AnonymousName);
        rosnode_ = new ros::NodeHandle(this->robotNamespace);

        ros_pub = rosnode_->advertise<geometry_msgs::Twist>(speedTopic, 10);
        steering_pub = rosnode_->advertise<geometry_msgs::Wrench>(tireTopic, 10);
        odom_pub = rosnode_->advertise<nav_msgs::Odometry>(odomTopic, 10);
        

        //rosnode_ = new ros::NodeHandle(robot_namespace);
        this->ros_spinner_thread_ = boost::thread( boost::bind( &CatSteering::CatVehicleSimROSThread, this ) );
    } //end Load

    void CatSteering::CatVehicleSimROSThread()
    {
        ROS_INFO_STREAM("$ Callback thread id=" << boost::this_thread::get_id());

        //Added by Rahul
        ros::NodeHandle nodehandle;
        //modelRead calback function is necessary in order to get instantaneous velocity vector
        ros::Subscriber sub = nodehandle.subscribe("gazebo/model_states", 1, &CatSteering::modelRead, this);

        ros::Rate loop_rate(10);

        while (this->rosnode_->ok())
        {
            ros::spinOnce();
            loop_rate.sleep( );       
        }
    } //end CatVehicleSimROSThread

    //Added by Rahul
    void CatSteering::modelRead(const gazebo_msgs::ModelStates::ConstPtr& msg)
    {
        ros::Time current_time = ros::Time::now();
        vector<string> modelNames = msg->name;
        int index=-1;

        // figure out which index we are in the msg list of model states
        for( int i=0; i<modelNames.size() && index<0; i++ )
        {
            if( this->robotNamespace == std::string("/"+modelNames[i]) )
            {
//                ROS_INFO_STREAM(this->robotNamespace << " comparing to " << std::string("/"+modelNames[i]) << "[" << i << "]");
                index = i;
            }
        }

        double Vx, Vy, Vz, V;
        //Variable to story velocity vector that will be used  for publishing on speed topic
        geometry_msgs::Twist out_vel;
	    // JMS: output to give steering information
	    geometry_msgs::Wrench steering_msg;

        linear_vel = model->GetRelativeLinearVel();
        angular_vel = model->GetRelativeAngularVel();
        Vx = out_vel.linear.x = linear_vel.x;
        Vy = out_vel.linear.y = linear_vel.y;
        Vz = out_vel.linear.z = linear_vel.z;
        out_vel.angular.x = angular_vel.x;
        out_vel.angular.y = angular_vel.y;
        out_vel.angular.z = angular_vel.z;
        V = sqrt(Vx*Vx + Vy*Vy + Vz*Vz);


        //Publish the velocity as string to speed topic
        ros_pub.publish(out_vel);
        //      logOut << V << ";\n";
	
	    // JMS: get information about the steering joints
	    physics::JointPtr steering_joints[2];
	    steering_joints[0] = model->GetJoint("front_left_steering_joint");
	    steering_joints[1] = model->GetJoint("front_right_steering_joint");
	    //physics::JointState j_state0 = new physics::JointState(steering_joints[0]);
	    //physics::JointState j_state1 = new physics::JointState(steering_joints[1]);

	    double a0,a1;
	    a0 = steering_joints[0]->GetAngle(0).Radian();
	    a1 = steering_joints[1]->GetAngle(0).Radian();
	    // average these values, though in most modes they will be equal
	
	    steering_msg.torque.z = (a0+a1)/2.0;
	    steering_pub.publish(steering_msg);

        if( index == -1 )
        {
            ROS_ERROR_STREAM("Unable to find odometry for model name " << this->robotNamespace << "=" << index);
        }
        else
        {
            static tf::TransformBroadcaster br;
            tf::Transform transform;
            transform.setOrigin( tf::Vector3(msg->pose[index].position.x, 
                                            msg->pose[index].position.y, 
                                            msg->pose[index].position.z) );
            tf::Quaternion q(msg->pose[index].orientation.x,
                             msg->pose[index].orientation.y,
                             msg->pose[index].orientation.z,
                             msg->pose[index].orientation.w);
            transform.setRotation(q);
            br.sendTransform(tf::StampedTransform(transform, current_time, 
                            this->tfScope + "/odom", 
                            this->tfScope + "/base_link") );
//            br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), 
//                            this->tfScope + "/odom", 
//                            this->tfScope + "/base_link") );

            // grab the odometry from the incoming msg and post it
            nav_msgs::Odometry odom;
            odom.header.stamp = current_time;
            odom.header.frame_id = this->tfScope + "/odom";
            // we calculate our index in the pose msg by 
            odom.child_frame_id = this->tfScope + "/base_link";
            odom.pose.pose = msg->pose[index];
            odom.twist.twist = msg->twist[index];
          
            odom_pub.publish(odom);
        }
    }
    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(CatSteering)
}

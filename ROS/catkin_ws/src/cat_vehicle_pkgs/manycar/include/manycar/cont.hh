#ifndef CONT_HH
#define CONT_HH
#include<map>
#include<boost/bind.hpp>
#include<boost/thread.hpp>
#include<gazebo/gazebo.hh>
#include<gazebo/physics/physics.hh>
#include<gazebo/common/common.hh>
#include<cstdio>
#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<nav_msgs/Odometry.h>
#include<gazebo/physics/Joint.hh>
#include<cstdlib>
#include<gazebo_msgs/ModelStates.h>
// Custom Callback Queue
#include<ros/callback_queue.h>
#include<ros/advertise_options.h>
#include<iostream>
#include<string>
#include<vector>
namespace gazebo
{
    class CatSteering: public ModelPlugin
    {
        public:
            CatSteering();
            ~CatSteering();
            void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
            void OnUpdate(const common::UpdateInfo & _info);
        private:
            event::ConnectionPtr updateConnection;
            physics::ModelPtr model;
            physics::WorldPtr world;


            std::string robotNamespace;
            std::string topicName;
            std::string odomTopic;
            std::string speedTopic;

            // Simulation time of the last update
            common::Time prevTime;
            common::Time newTime;
            float velocity;
            float steering_angle;
            double odomPose[3];
            double speed;

            physics::JointPtr steering_joints_left;
            physics::JointPtr steering_joints_right;

            physics::JointPtr back_right_wheel_joint;
            physics::JointPtr back_left_wheel_joint;
            physics::JointController *steering;

            ros::NodeHandle* rosnode;
            ros::Subscriber ros_sub;
            ros::Publisher ros_pub;

            // Custom Callback Queue
            ros::CallbackQueue queue;
            boost::mutex lock;
            boost::thread ros_spinner_thread;
//            boost::thread callback_queue_thread;
  //          void QueueThread();
    
            void modelRead(const gazebo_msgs::ModelStates::ConstPtr& msg);
            void CallBackFn(const geometry_msgs::Twist::ConstPtr& cmd_msg);
            void CatVehicleSimROSThread();
    };
}

#endif

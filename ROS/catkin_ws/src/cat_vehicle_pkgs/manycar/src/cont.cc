#include <algorithm>
#include <assert.h>
#include<boost/bind.hpp>
#include<boost/thread.hpp>
#include<gazebo/gazebo.hh>
#include<gazebo/physics/physics.hh>
#include<gazebo/common/common.hh>
#include<gazebo/physics/Joint.hh>
#include<cstdlib>
#include<cstdio>
// Custom Callback Queue
#include <ros/callback_queue.h>
#include <ros/advertise_options.h>
#include<iostream>
#include<string>
#include<vector>
#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<nav_msgs/Odometry.h>
#include "manycar/cont.hh"
#include <sstream>
#include "std_msgs/String.h"
using namespace std;
namespace gazebo
{
    CatSteering::CatSteering()
    {
        velocity = 0;
        steering_angle = 0;
    }

    CatSteering::~CatSteering()
    {
        delete rosnode;
    }
    void CatSteering::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {
        this->model = _parent;
        this->world = _parent->GetWorld();

        // Make sure the ROS node for Gazebo has already been initialized                                                                                    
        if (!ros::isInitialized())
        {
            ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
                    << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
            return;
        }

        gzdbg << "\nModel name is: "<<model->GetName()<<"\n";
        this->robotNamespace = "";
        if (_sdf->HasElement("robotNamespace"))
        {
            this->robotNamespace = _sdf->GetElement("robotNamespace")->Get<std::string>();
            //this->robotNamespace = _sdf->GetElement("robotNamespace")->GetValueString() + "/";
        }

        this->topicName = "";
        if(_sdf->HasElement("topicName"))
        {
            this->topicName = _sdf->GetElement("topicName")->Get<std::string>();
        }
        this->topicName = this->robotNamespace + "/" + this->topicName;
        this->odomTopic = this->robotNamespace + "/odom";
        this->speedTopic = this->robotNamespace + "/speed";
        gzdbg << "\n*** "<< this->topicName <<" *** \n";

        gzdbg << "\n$$$$ "<< this->robotNamespace <<" $$$$ \n";
        steering = new physics::JointController(model);
        steering_joints_left =  model->GetJoint("front_left_steering_joint");
        steering_joints_right = model->GetJoint("front_right_steering_joint");
        back_right_wheel_joint = model->GetJoint("back_right_wheel_joint");
        back_left_wheel_joint = model->GetJoint("back_left_wheel_joint");
        odomPose[0] = odomPose[1] = odomPose[2] = 0.0;

        if(!steering_joints_left)
        {
            gzdbg <<"\n!!!! Controller couldn't get left steering joint !!!!\n";
        }
        if(!steering_joints_right)
        {
            gzdbg <<"\n!!!! Controller couldn't get right steering joint !!!!\n";
        }
        if(!back_right_wheel_joint)
        {
            gzdbg <<"\n!!!! Controller couldn't get back right wheel joint !!!!\n";
        }
        if(!back_left_wheel_joint)
        {
            gzdbg <<"\n!!!! Controller couldn't get back left wheel joint !!!!\n";
        }

        int argc = 0;
        char** argv = NULL;
        ros::init(argc, argv, "Carsim", ros::init_options::NoSigintHandler | ros::init_options::AnonymousName);
        rosnode = new ros::NodeHandle(this->robotNamespace);
        ros_pub = rosnode->advertise<std_msgs::String>(speedTopic, 100);

        this->ros_spinner_thread = boost::thread( boost::bind( &CatSteering::CatVehicleSimROSThread,this ) );
        this->updateConnection = event::Events::ConnectWorldUpdateBegin(
                boost::bind(&CatSteering::OnUpdate, this, _1));
    }

    void CatSteering::CatVehicleSimROSThread()
    {
        ROS_INFO_STREAM("Callback thread id=" << boost::this_thread::get_id() << ", Topic Name= " << this->topicName);
        ros_sub = rosnode->subscribe<geometry_msgs::Twist>(this->topicName, 10, &CatSteering::CallBackFn, this);
        //        ros_pub = rosnode->advertise<nav_msgs::Odometry>(odomTopic, 1);

        ros::NodeHandle nodehandle;
        newTime = world->GetSimTime();
        ros::Subscriber sub = nodehandle.subscribe("gazebo/model_states", 1, &CatSteering::modelRead, this);
        ros::Rate loop_rate(10);

        while (this->rosnode->ok())
        {
            //       usleep(1000);
            ros::spinOnce();
            loop_rate.sleep( );
        }

    }

    void CatSteering::modelRead(const gazebo_msgs::ModelStates::ConstPtr& msg)
    {
        vector<string> modelNames;
        vector<geometry_msgs::Pose> poses;
        vector<geometry_msgs::Twist> twists;
        modelNames = msg->name;
        poses = msg->pose;
        twists = msg->twist;
        prevTime = newTime;
        newTime = world->GetSimTime();
        double odomPoseOldX, odomPoseOldY, odomPoseOldZ, Vx, Vy, Vz, V;
        for(int i = 0; i < modelNames.size(); i++)
        {
            if(modelNames[i] == "manycar1")
            {
                //Calculate the instantaneous velocity in X direction and Y direction
                odomPoseOldX = odomPose[0];
                odomPose[0] = poses[i].position.x;
                Vx = (odomPose[0] - odomPoseOldX)/(newTime.Double() - prevTime.Double());
                odomPoseOldY = odomPose[1];
                odomPose[1] = poses[i].position.y;
                Vy  = (odomPose[1] - odomPoseOldY)/(newTime.Double() - prevTime.Double());
                odomPoseOldZ = odomPose[2];
                odomPose[2] = poses[i].position.z;
                Vz  = (odomPose[2] - odomPoseOldZ)/(newTime.Double() - prevTime.Double());
                V = sqrt(Vx*Vx + Vy*Vy + Vz*Vz);
                std::stringstream ss;
                ss << V;
                std_msgs::String testmsg;
                testmsg.data = ss.str();
                //Publish the velocity as string to speed topic
                ros_pub.publish(testmsg);
            }
        }   
    }

    void CatSteering::CallBackFn(const geometry_msgs::Twist::ConstPtr& cmd_msg)
    {
        lock.lock();
        velocity = cmd_msg->linear.x;
        steering_angle = cmd_msg->angular.z;
        gzdbg << "\nVelocity: " << velocity << ", Steering Angle: " << steering_angle << "\n";

        lock.unlock();
    }
    void CatSteering::OnUpdate(const common::UpdateInfo & _info)
    {
        //steering_joints_left->SetVelocity(0, 12);
        //steering_joints_right->SetVelocity(0, 12);
        back_right_wheel_joint->SetVelocity(0, velocity);
        back_left_wheel_joint->SetVelocity(0, velocity);
        steering->SetJointPosition(steering_joints_left, steering_angle);
        steering->SetJointPosition(steering_joints_right, steering_angle);
        //this->model->SetLinearVel(math::Vector3(2.5, 0, 0));

    }
    GZ_REGISTER_MODEL_PLUGIN(CatSteering)
}



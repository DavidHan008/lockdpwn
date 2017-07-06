#pragma once
#include <QtGui/QMainWindow>
#include <QtCore>
#include <vector>
#include <Eigen/Core>
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32MultiArray.h>
#include <visualization_msgs/Marker.h>  	//Marker messages to visualize objects in Rviz

#include "../../../build/motion_planner/ui_motion_planner_gui.h"

using namespace std;
using namespace Eigen;

class LocalPlannerThread : public QThread
{
    Q_OBJECT;

private :
    int init_argc;
    char** init_argv;

    ros::Subscriber possub;
    ros::Subscriber possub2;
    ros::Publisher msgpub;
    ros::Publisher msgpub2;
    ros::Publisher msgpub3;
    ////////////////////////////////
    // Message Definition
    
    // Look ahead msg 
    visualization_msgs::Marker m_model;
    // Control Data for Path Tracking & Velocity Control
    std_msgs::Float32MultiArray m_msg;

    ////////////////////////////////
    bool m_bThreadStop;
    QMutex m_mutex;
    Vector3d m_pos;
    float m_vel;
    vector<Vector2d> m_LocalSplinePath;
public :
    void SubTopicProcess1(const std_msgs::Float32MultiArray::ConstPtr& msg);
    void SubTopicProcess2(const nav_msgs::Path::ConstPtr& msg);
    
    void publish_local_path(vector<Vector2d> path);
    void GetLookAheadPt(double lookAheadDist,double& x, double& y, double &resdist);

    LocalPlannerThread(int argc, char** argv);
    ~LocalPlannerThread();

    void PubMsg();
    void Compute();

	double m_LookAhead_X;	//JW 16.07.14.
	double m_LookAhead_Y;	//JW 16.07.14.
	double m_LookAhead_X_pre;	//JW 16.07.14.
	double m_LookAhead_Y_pre;	//JW 16.07.14.

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW


	
    public slots:
	
        void stop();
private:
    void run();

};

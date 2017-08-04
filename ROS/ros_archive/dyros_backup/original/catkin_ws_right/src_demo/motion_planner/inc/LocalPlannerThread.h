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

#include <iostream>
#include <fstream>

#include "../../../build/motion_planner/ui_motion_planner_gui.h"

using namespace std;
using namespace Eigen;
using std::ifstream;

#define _RAD2DEG 180 / M_PI
#define _DEG2RAD M_PI / 180

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
    ros::Publisher msgpub_car;//jw 16.07.07
    ros::Publisher msgpub_Look_orig;//jw 16.07.
    ros::Publisher msgpub_err;//jw 16.07.11
    ros::Publisher msgpub3;
    ////////////////////////////////
    // Message Definition
    
    
    // My_pose msg
    visualization_msgs::Marker m_CarPos;
    visualization_msgs::Marker m_line_strip;//jw 16.07.07
    // Look ahead msg 
    visualization_msgs::Marker m_model_jw;
    visualization_msgs::Marker m_model_orig;//jw 16.07.08
    // Control Data for Path Tracking & Velocity Control
    std_msgs::Float32MultiArray m_msg;
    // Err msg
    std_msgs::Float32MultiArray m_err;//jw 16.07.11


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
    void GetLookAheadPt(double lookAheadDist,double& x, double& y, double &resdist);//JW 16.06.24.
    //void GetLookAheadPt_JW(double &lookAheadDist,double& x, double& y, double &resdist);
    void GetLookAheadPt_JW(double &lookAheadDist,double& x, double& y, double &resdist);//JW 16.06.24.

    LocalPlannerThread(int argc, char** argv);
    ~LocalPlannerThread();

    void PubMsg();
    void Pub_JWPathMsg();
    void Compute();

	double m_LookAhead_X;	//JW 16.06.24.
	double m_LookAhead_Y;	//JW 16.06.24.
	double m_LookAhead_X_pre;	//JW 16.06.24.
	double m_LookAhead_Y_pre;	//JW 16.06.24.
 	int lookAheadIndex;//JW 16.06.24.
	double pre_turning_rad;//JW 16.07.18.

double m_th_Err; //JW 16.07.11.
double m_dist_Err;//JW 16.07.11.
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW


	
    public slots:
	
        void stop();
private:
    void run();

};

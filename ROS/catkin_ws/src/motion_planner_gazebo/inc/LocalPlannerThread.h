#pragma once
#include <QtGui/QMainWindow>
#include <QtCore>

#include <vector>
#include <Eigen/Core>
#include <ros/ros.h>

#include <nav_msgs/Path.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32MultiArray.h>
#include <visualization_msgs/Marker.h>  //Marker messages to visualize objects in Rviz

#include <iostream>
#include <fstream>

#include "../../../build/motion_planner/ui_motion_planner_gui.h"

using namespace std;
using namespace Eigen;
using std::ifstream;

#define _RAD2DEG 180 / M_PI
#define _DEG2RAD M_PI / 180

class LocalPlannerThread : public QThread {
    Q_OBJECT;

private :
    int init_argc;
    char** init_argv;

    ros::Subscriber possub;
    ros::Subscriber possub2;

    ros::Publisher msgpub;
    ros::Publisher msgpub_Look_JW;
    ros::Publisher msgpub_Look_JW_exp;
    ros::Publisher msgpub_car;         //jw 16.07.07
    ros::Publisher msgpub_Look_orig;   //jw 16.07.
    ros::Publisher msgpub_err_JW;      //jw 16.07.11
    ros::Publisher msgpub_err_Orig;    //jw 16.07.11
    ros::Publisher msgpub3;
    ros::Publisher msg_steer;

    ros::Subscriber possub_gazebo;   // ed: 가제보용 섭,펍 추가
    ros::Publisher msgpub_gazebo;

    ////////////////////////////////
    // Message Definition
    // My_pose msg
    visualization_msgs::Marker m_CarPos;
    visualization_msgs::Marker m_line_strip;          //jw 16.07.07

    // Look ahead msg 
    visualization_msgs::Marker m_model_jw;
    visualization_msgs::Marker m_model_jw_exp;
    visualization_msgs::Marker m_model_jw_exp_line;
    visualization_msgs::Marker m_model_orig;          //jw 16.07.08

    // Control Data for Path Tracking & Velocity Control
    std_msgs::Float32MultiArray m_msg;

    // ed: 가제보용 변수 추가
    std_msgs::Float32MultiArray m_msg_gazebo;


    double m_len_c2r;
    double m_len_f2r;
    double m_overall;	double m_overall_rev;
    int m_resolution;
    double m_line_add;

    ////////////////////////////////

    bool m_bThreadStop;
    QMutex m_mutex;
    Vector3d m_pos;
    float m_vel;
    vector<Vector2d> m_LocalSplinePath;


public :
    void callback_gazebo(const std_msgs::Float32MultiArray::ConstPtr& msg);  // ed: 함수 추가

    void SubTopicProcess1(const std_msgs::Float32MultiArray::ConstPtr& msg);
    void SubTopicProcess2(const nav_msgs::Path::ConstPtr& msg);
    
    double SteeringAng_PurePursuit(double lookX, double lookY, double resdist);
    double SteeringAng_Radius(int carIdx);
    void publish_local_path(vector<Vector2d> path);
    void GetLookAheadPt_For(double lookAheadDist,double& x, double& y, double &resdist, int &carIdx);//JW 16.06.24.
    void GetLookAheadPt_Rev(double lookAheadDist,double& x, double& y, double &resdist, int &carIdx);//JW 16.06.24.
    //void GetLookAheadPt_JW(double &lookAheadDist,double& x, double& y, double &resdist);
    void GetLookAheadPt_DE_for(int &carIdx,double& x, double& y, double &resdist);//JW 16.08.24.
    void GetLookAheadPt_JW_rev(int &carIdx, double& x, double& y, double &resdist);//JW 16.08.24.
    double cur_rad(double x1, double y1,
                   double x2, double y2,
                   double x3, double y3);

    LocalPlannerThread(int argc, char** argv);
    ~LocalPlannerThread();

    void PubMsg();
    void Pub_JWPathMsg();
    void Compute();

    double m_LookAhead_X;	//JW 16.06.24.
    double m_LookAhead_Y;	//JW 16.06.24.
    double m_LookAhead_X_pre;	//JW 16.06.24.
    double m_LookAhead_Y_pre;	//JW 16.06.24.
    int m_lookAheadIndex;       //JW 16.06.24.
    //double pre_Rad_V;         //JW 16.07.28.
    char m_dir_mode;            //JW


    char m_switch_flag;         //JW 17.01.05.
    char m_start_flag;          //JW 17.01.05.
    int _cut_switch;
    int _cut_back;
    char m_LocalSplinePath_cnt_flag;
    int m_LocalSplinePath_cnt;
    int m_pre_waypoint;
    double m_r_min;              // 0215
    double m_CrossTrack_ERR;     // 0215
    double m_cur_wp;             // 0215
    double m_cur_lp;             // 0215
    double m_pre_lookAheadDist;  // 0216
    double m_pre_len_dist;       // 0216
    double m_pre_steer_Radius;

    double m_TH_ERR;
    double m_len_dist;
    double m_ratio_s2w;
    double m_limit_steerAngle;
    double m_switch_X;
    double m_switch_Y;
    double m_switch_idx;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

            public slots:

            void stop();

private:
            void run();

};


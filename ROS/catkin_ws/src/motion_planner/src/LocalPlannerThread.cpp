#include "../inc/LocalPlannerThread.h"
#include <QPointF>  
#include <QDebug>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include "../inc/CatmullRomSpline.h"

#define MAP_RESOL 100
#define SPLINE_RESOL 500

#define FR_V_MAX 21.0/2.24
#define REV_V_MAX 5.0
#define TH_SCALE 0.79
#define lps_a 0.5     //low pre //high now
#define Radius_points 4
#define dist_thresh 0.5
#define th_err_range 90*2


// ed: LocalizationData 섭스크라이브용 콜백함수
// From Localization Module
void LocalPlannerThread::SubTopicProcess1(const std_msgs::Float32MultiArray::ConstPtr& msg){
    m_pos[0] = msg->data.at(0);  // ed: x
    m_pos[1] = msg->data.at(1);  //     y
    m_pos[2] = msg->data.at(2);  //     theta

    //    printf("good");
    m_vel = msg->data.at(3); // m/s

    //    double switch_dist = sqrt(pow(m_switch_X - msg->data.at(0),2) + pow(m_switch_Y - msg->data.at(1),2));
    //    if(switch_dist < 0.9)
    //    {
    //        m_dir_mode = -1;
    //        //cout << "SWITCH" << endl;
    //    }

    Compute();
}

void LocalPlannerThread::SubTopicProcess2(const nav_msgs::Path::ConstPtr& msg){
    cout << "sub path" << endl;
    // Insertion Global Path Data to Vector Struct
    vector<Vector2d> nodeVec;

    //    printf("good333");

    for( int i=0; i<msg->poses.size(); i++){
        nodeVec.push_back(Vector2d(msg->poses[i].pose.position.x, msg->poses[i].pose.position.y));
    }

    // Generation of Interpolation Curve
    CatmullRomSpline spline;
    vector<Vector2d> curvePath = spline.PathToCurve( nodeVec, 1, 1);
    m_LocalSplinePath = curvePath;
    //m_LocalSplinePath = nodeVec;

    cout << m_LocalSplinePath.size() <<endl;

    // Publish for Visualization
    publish_local_path(m_LocalSplinePath);
    m_dir_mode = 1;
}

// ed: Path 데이터를 받아 rviz상에 초록색선을 그려주는 함수
void LocalPlannerThread::publish_local_path(vector<Vector2d> path){
    nav_msgs::Path msg;
    std::vector<geometry_msgs::PoseStamped> waypoints;
    msg.header.frame_id = "/camera_init";
    msg.header.stamp = ros::Time::now();

    ofstream fout;

    // ed: rviz에 초록색선을 그리고 해당 좌표파일을 저장한다
    //fout.open("/home/dyros-vehicle/Documents/00_DATA/bag/map/MAP170705_spline.txt");

    //////////////////////////////////////////
    // POSE STAMPED
    for(int i=0; i<path.size(); i++){
        geometry_msgs::PoseStamped waypt;

        waypt.header.frame_id = "/camera_init";
        waypt.header.stamp = ros::Time::now();

        // ed: 아래코드 path ==> waypt ==> waypoints ==> msg ==> publish(msg) 순서로 데이터를 저장한다
        // ed: 초록색 Path Line을 회전해서 정확히 Loam축과 맞도록 아래 코드를 수정했다
        //waypt.pose.position.x = path[i][0];
        //waypt.pose.position.y = path[i][1];
        waypt.pose.position.x = path[i][1];
        waypt.pose.position.y = -path[i][0];
        waypt.pose.position.z = 0;

        waypoints.push_back(waypt);

        fout << path[i][0] << " " << path[i][1] << endl;
    }

    fout.close();
    msg.poses.resize(waypoints.size());

    // Extract the plan in world coordinates, we assume the path is all in the same frame
    for(unsigned int i=0; i < waypoints.size(); i++){
        msg.poses[i] = waypoints[i];
    }


    // ed: /LocalPathData 토픽으로 퍼블리시
    //      초록색 선을 퍼블리시하는 코드
    msgpub.publish(msg);
}


void LocalPlannerThread::GetLookAheadPt_JW_rev(int &carIdx,double& x, double& y, double &resdist){
    double heading_Err = 0.0; //JW 16.07.11.
    double cross_track_Err = 0.0;//JW 16.07.11.
    double delta_LookAhead = 0.0;
    double curvature_norm = 0;
    double car_heading = 0.0;


    if (m_LocalSplinePath.size() > 1){
        double minDist = 99999;
        int car_waypoint = -1;
        //for(int i = (m_cut_back+m_cut_switch)*SPLINE_RESOL ; i < m_LocalSplinePath.size(); i++)
        for(int i = m_pre_waypoint; i<m_LocalSplinePath.size(); i++) {
            double x2 = m_LocalSplinePath[i][0] - m_pos[0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_pos[1];
            y2 *= y2;
            double dist = sqrt(x2+y2);//distŽÂ

            if ( dist < minDist ) {
                minDist = dist;
                car_waypoint = i;
            }
        }
        carIdx = car_waypoint;
        m_pre_waypoint = car_waypoint;

        //JW 17.01.09 car pose marker
        m_model_orig.header.stamp = ros::Time::now();

        // ed: motion_planner의 좌표축을 회전하기 위해 아래와 같이 코드를 수정했다
        //m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][0];//+ m_overall*// comments(th);
        //m_model_orig.pose.position.y = m_LocalSplinePath[car_waypoint][1] ;//+ m_overall*sin(th);
        m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][1];//+ m_overall*cos(th);
        m_model_orig.pose.position.y = -m_LocalSplinePath[car_waypoint][0] ;//+ m_overall*sin(th);

        // ed: /LookAheadPos_oirg (blue ball) 토픽으로 퍼블리시
        msgpub_Look_orig.publish(m_model_orig);



        //Velodyne to car rearwheel
        //m_pos[0] -= m_len_c2r*cos(car_heading);
        //m_pos[1] -= m_len_c2r*sin(car_heading);

        //Error
        //cross-track
        cross_track_Err = minDist;//sqrt((m_LocalSplinePath[car_waypoint][1] - m_pos[1])*(m_LocalSplinePath[car_waypoint][1] - m_pos[1]) + (m_LocalSplinePath[car_waypoint][0] - m_pos[0])*(m_LocalSplinePath[car_waypoint][0] - m_pos[0])); //JW 07.28.
        m_CrossTrack_ERR = cross_track_Err;
        if(cross_track_Err > FR_V_MAX)	cross_track_Err = FR_V_MAX;//prohibit the cross-track err overflow

        ////////////////////////////////////////////////////////////////////
        car_heading = m_pos[2]; //range 0 ~ M_PI*2

        //car_dir diff
        double tmp_dir = atan2((m_LocalSplinePath[car_waypoint][1] - m_LocalSplinePath[car_waypoint+1][1]),
                               (m_LocalSplinePath[car_waypoint][0] - m_LocalSplinePath[car_waypoint+1][0]))-M_PI;
        if(tmp_dir < 0)	tmp_dir = M_PI*2 + tmp_dir;
        m_TH_ERR = abs(car_heading - tmp_dir);
        //cout << "tmp_dir : " << tmp_dir << ", car_heading : " << car_heading<<endl;
        /////////////////////////////////////////////////////////////
        //car_heading diff
        //range 0 ~ M_PI*2
        //JW 16.06.24.test1

        double tmp_th = atan2((m_LookAhead_Y - m_pos[1]), (m_LookAhead_X - m_pos[0]));
        if(tmp_th < 0)	tmp_th = M_PI*2 + tmp_th;

        heading_Err = abs(car_heading - tmp_th);
        if (heading_Err > M_PI)	heading_Err = abs(heading_Err - 2*M_PI)/(M_PI);
        else heading_Err /= (M_PI);

        /////////////////////////////////////////////////////////////
        double TH_ERR = TH_SCALE*(1.0 - sin(heading_Err*M_PI/2));
        m_TH_ERR = TH_ERR;
        double LEN_ERR = (1.0 - TH_SCALE)*sin(heading_Err*M_PI/2)*cross_track_Err;

        delta_LookAhead = REV_V_MAX*(TH_ERR + LEN_ERR);//curvature_norm*10;//*(LEN_ERR);
        //delta_LookAhead = curvature_norm*REV_V_MAX*(TH_ERR + LEN_ERR);

        double min_delta = 3.0;
        if( delta_LookAhead < min_delta ) delta_LookAhead = min_delta;

        double lookAheadDist = (int)(delta_LookAhead*10) * 0.1;

        //lookAheadDist = delta_LookAhead - m_overall_rev;
        //lookAheadDist = delta_LookAhead - m_overall;
        //JW 16.06.24.test1


        cout << "th_err : " << (1.0-sin(heading_Err*M_PI/2)) << ", dist_err : " << cross_track_Err << ", rad : " << curvature_norm << endl;
        cout << "JoonWoo Delta : " << lookAheadDist << ", TH_ERR : " << TH_ERR << ", Dist_ERR : "<< LEN_ERR << endl<< endl;

        double dist = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //1. just car car_heading to dist
        //	x = m_LookAhead_X = m_LocalSplinePath[car_waypoint][0] + lookAheadDist*cos(car_heading);
        //	y = m_LookAhead_Y = m_LocalSplinePath[car_waypoint][1] + lookAheadDist*sin(car_heading);

        for( int i = car_waypoint ; i < m_LocalSplinePath.size()-1 ; i++ )
            //	for( int i = m_lookAheadIndex; i<m_LocalSplinePath.size()-1; i++ )
        {
            double x2 = m_LocalSplinePath[i][0] - m_LocalSplinePath[i+1][0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_LocalSplinePath[i+1][1];
            y2 *= y2;
            dist += sqrt(x2+y2);

            if( lookAheadDist <= dist ) {
                cout << "m_lookAheadIndex : " << i <<endl;

                m_lookAheadIndex = i;
                x = m_LookAhead_X = m_LocalSplinePath[m_lookAheadIndex][0];
                y = m_LookAhead_Y = m_LocalSplinePath[m_lookAheadIndex][1];

                resdist = lookAheadDist;

                std_msgs::Float32MultiArray m_err;//jw 16.07.11
                m_err.data.clear();
                m_err.data.push_back(m_pos[0]);
                m_err.data.push_back(m_pos[1]);
                m_err.data.push_back(m_pos[2]);
                m_err.data.push_back(x);
                m_err.data.push_back(y);
                m_err.data.push_back(lookAheadDist);
                m_err.data.push_back(m_vel);
                m_err.data.push_back(heading_Err*180);
                m_err.data.push_back(cross_track_Err);
                msgpub_err_JW.publish(m_err);

                break;
            }
            if(i == m_LocalSplinePath.size()-2){
                m_lookAheadIndex = m_LocalSplinePath.size()-2;
                x = m_LookAhead_X = m_LocalSplinePath[m_lookAheadIndex][0];
                y = m_LookAhead_Y = m_LocalSplinePath[m_lookAheadIndex][1];

                resdist = lookAheadDist;

                std_msgs::Float32MultiArray m_err;//jw 16.07.11
                m_err.data.clear();
                m_err.data.push_back(m_pos[0]);
                m_err.data.push_back(m_pos[1]);
                m_err.data.push_back(m_pos[2]);
                m_err.data.push_back(x);
                m_err.data.push_back(y);
                m_err.data.push_back(lookAheadDist);
                m_err.data.push_back(m_vel);
                m_err.data.push_back(heading_Err*180);
                m_err.data.push_back(cross_track_Err);
                msgpub_err_JW.publish(m_err);

                cout << "no Index !!!!" <<endl;
                resdist = lookAheadDist;
                break;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if( m_lookAheadIndex == -1 ) {
            x = m_LocalSplinePath[m_LocalSplinePath.size()-1][0];
            y = m_LocalSplinePath[m_LocalSplinePath.size()-1][1];
            resdist = -1;
        }
    }
}

void LocalPlannerThread::GetLookAheadPt_DE_for(int &carIdx,double& x, double& y, double &resdist){
    double heading_Err = 0.0;        //JW 16.07.11.
    double cross_track_Err = 0.0;    //JW 16.07.11.

    double delta_LookAhead = 0.0;

    double curvature_norm = 0;
    double m_velo = 0;
    double car_heading = 0.0;

    if (m_LocalSplinePath.size() > 1){
        double minDist = 99999;
        int car_waypoint = -1;
        for(int i = 0 ; i<m_LocalSplinePath.size(); i++)
        {
            double x2 = m_LocalSplinePath[i][0] - m_pos[0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_pos[1];
            y2 *= y2;
            double dist = sqrt(x2+y2);//distŽÂ
            if ( dist < minDist )
            {
                minDist = dist;
                car_waypoint = i;
            }
        }

        carIdx = car_waypoint;
        //cout << "car_waypoint : " << car_waypoint <<endl;
        m_pre_waypoint = car_waypoint;
        //JW 17.01.09 car pose marker
        m_model_orig.header.stamp = ros::Time::now();

        // ed: motion_planner의 좌표축을 회전하기 위해 아래와 같이 코드를 수정했다
        //m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][0];//+ m_overall*cos(th);
        //m_model_orig.pose.position.y = m_LocalSplinePath[car_waypoint][1];//+ m_overall*sin(th);
        m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][1];//+ m_overall*cos(th);
        m_model_orig.pose.position.y = -m_LocalSplinePath[car_waypoint][0];//+ m_overall*sin(th);

        // ed: /LookAheadPos_oirg (blue ball) 토픽으로 퍼블리시
        msgpub_Look_orig.publish(m_model_orig);



        //Error
        //cross-track
        cross_track_Err = minDist;//sqrt((m_LocalSplinePath[car_waypoint][1] - m_pos[1])*(m_LocalSplinePath[car_waypoint][1] - m_pos[1]) + (m_LocalSplinePath[car_waypoint][0] - m_pos[0])*(m_LocalSplinePath[car_waypoint][0] - m_pos[0])); //JW 07.28.        
        m_CrossTrack_ERR = cross_track_Err;
        if(cross_track_Err > FR_V_MAX)	cross_track_Err = FR_V_MAX;//prohibit the cross-track err overflow

        ////////////////////////////////////////////////////////////////////
        car_heading = m_pos[2];//range 0 ~ M_PI*2
        //car_dir diff
        double tmp_dir = atan2((m_LocalSplinePath[car_waypoint][1] - m_LocalSplinePath[car_waypoint+1][1]),
                               (m_LocalSplinePath[car_waypoint][0] - m_LocalSplinePath[car_waypoint+1][0]))-M_PI;
        if(tmp_dir < 0)	tmp_dir = M_PI*2 + tmp_dir;
        m_TH_ERR = abs(car_heading - tmp_dir);
        //cout << "tmp_dir : " << tmp_dir << ", car_heading : " << car_heading<<endl;
        /////////////////////////////////////////////////////////////
        //car_heading diff
        //range 0 ~ M_PI*2
        //JW 16.06.24.test1

        double tmp_th = atan2((m_LookAhead_Y - m_pos[1]), (m_LookAhead_X - m_pos[0]));
        if(tmp_th < 0)	tmp_th = M_PI*2 + tmp_th;

        heading_Err = abs(car_heading - tmp_th);
        if (heading_Err > M_PI)	heading_Err = abs(heading_Err - 2*M_PI)/(M_PI);
        else heading_Err /= (M_PI);

        /////////////////////////////////////////////////////////////

        double TH_ERR = TH_SCALE*(1.0 - sin(heading_Err*M_PI/2));
        //TH_ERR *= TH_ERR;
        double LEN_ERR = (1.0-TH_SCALE)*sin(heading_Err*M_PI/2)*cross_track_Err;

        //point
        delta_LookAhead = FR_V_MAX*(TH_ERR + LEN_ERR) ;
        ////////////////////////////////////////////////////////////////

        double lookAhead_Dist = 0;//- m_len_dist;

        if( delta_LookAhead < 3) lookAhead_Dist = 3;
        else if(delta_LookAhead > 12) lookAhead_Dist = 12.0;
        else lookAhead_Dist = delta_LookAhead ;

        double lookAheadDist = (1.0-lps_a)*m_pre_lookAheadDist + lps_a*lookAhead_Dist;
        m_pre_lookAheadDist = lookAheadDist;

        //lookAheadDist = (int)(lookAheadDist*10)*0.1;
        //cout << "delta_LookAhead : " << lookAheadDist << ", delta_LookAhead : " << delta_LookAhead << ", m_len_dist : " << m_len_dist << endl;
        //cout << "vel : " << lookAheadDist*2.24 << ", real_vel : " << m_vel*3.6 << ", TH_ERR : " << TH_ERR << ", Dist_ERR : "<< LEN_ERR << endl<< endl;

        double dist = 0;
        for( int i = car_waypoint ; i < m_LocalSplinePath.size()-1 ; i++ )
            //for( int i = m_lookAheadIndex ; i < m_LocalSplinePath.size()-1; i++ )
        {
            double x2 = m_LocalSplinePath[i][0] - m_LocalSplinePath[i+1][0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_LocalSplinePath[i+1][1];
            y2 *= y2;
            dist += sqrt(x2+y2);

            if( lookAheadDist <= dist )
            {
                //cout << "m_lookAheadIndex : " << i <<endl;

                m_lookAheadIndex = i;
                x = m_LookAhead_X = m_LocalSplinePath[m_lookAheadIndex][0];
                y = m_LookAhead_Y = m_LocalSplinePath[m_lookAheadIndex][1];

                /*
                  double cur_tmp;
                  cur_rad(m_LocalSplinePath[m_lookAheadIndex-1][0], m_LocalSplinePath[m_lookAheadIndex-1][1],
                  m_LocalSplinePath[m_lookAheadIndex][0], m_LocalSplinePath[m_lookAheadIndex][1],
                  m_LocalSplinePath[m_lookAheadIndex+1][0], m_LocalSplinePath[m_lookAheadIndex+1][1],
                  cur_tmp);
                  m_cur_lp = cur_tmp;
                */
                //if(cur_tmp < 100)   m_cur_lp = cur_tmp;
                //else m_cur_lp = 0;

                resdist = lookAheadDist;

                std_msgs::Float32MultiArray m_err;//jw 16.07.11
                m_err.data.clear();
                m_err.data.push_back(m_pos[0]);
                m_err.data.push_back(m_pos[1]);
                m_err.data.push_back(x);
                m_err.data.push_back(y);
                m_err.data.push_back(minDist);
                msgpub_err_JW.publish(m_err);

                break;
            }

            if(i >= m_LocalSplinePath.size()- 2) {
                m_lookAheadIndex = m_LocalSplinePath.size()-2;
                x = m_LookAhead_X = m_LocalSplinePath[m_lookAheadIndex][0];
                y = m_LookAhead_Y = m_LocalSplinePath[m_lookAheadIndex][1];

                resdist = lookAheadDist;

                std_msgs::Float32MultiArray m_err;//jw 16.07.11
                m_err.data.clear();
                m_err.data.push_back(m_pos[0]);
                m_err.data.push_back(m_pos[1]);
                m_err.data.push_back(x);
                m_err.data.push_back(y);
                m_err.data.push_back(minDist);
                msgpub_err_JW.publish(m_err);

                cout << "no Index !!!!" <<endl;
                resdist = lookAheadDist;
                break;
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if( m_lookAheadIndex == -1 ){
            x = m_LocalSplinePath[m_LocalSplinePath.size()-1][0];
            y = m_LocalSplinePath[m_LocalSplinePath.size()-1][1];
            resdist = -1;
        }
    }
}

double LocalPlannerThread::cur_rad(double x1, double y1,
                                   double x2, double y2,
                                   double x3, double y3
                                   ){
    double rad;
    double d1 = (x2-x1)/(y2-y1);
    double d2 = (x3-x2)/(y3-y2);
    double c_x = ((y3-y1)+(x2+x3)*d2-(x1+x2)*d1)/(2*(d2-d1));
    double c_y = -d1*(c_x-((x1+x2)/2))+(y1+y2)/2;

    return rad = sqrt(pow((x1-c_x),2)+pow(y1-c_y,2));
}

void LocalPlannerThread::GetLookAheadPt_For(double lookAheadDist,double& x, double& y, double &resdist, int &carIdx){
    double heading_Err = 0.0;      //JW 16.07.11.
    double cross_track_Err = 0.0;  //JW 16.07.11.

    if (m_LocalSplinePath.size() > 1){
        double minDist = 99999;
        int car_waypoint = -1;

        //for(int i = 0 ; i < m_switch_idx; i++)
        for(int i = 0 ; i < m_LocalSplinePath.size(); i++) {
            double x2 = m_LocalSplinePath[i][0] - m_pos[0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_pos[1];
            y2 *= y2;
            double dist = sqrt(x2+y2);//distŽÂ
            if ( dist < minDist ) {
                minDist = dist;
                car_waypoint = i;
            }
        }

        carIdx = car_waypoint;
        //cout << "car_waypoint : " << car_waypoint <<endl;
        m_pre_waypoint = car_waypoint;
        //JW 17.01.09 car pose marker
        m_model_orig.header.stamp = ros::Time::now();

        // ed: motion_planner의 좌표축을 회전하기 위해 아래와 같이 코드를 수정했다
        //m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][0];//+ m_overall*cos(th);
        //m_model_orig.pose.position.y = m_LocalSplinePath[car_waypoint][1];//+ m_overall*sin(th);
        m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][1];//+ m_overall*cos(th);
        m_model_orig.pose.position.y = -m_LocalSplinePath[car_waypoint][0];//+ m_overall*sin(th);

        // ed: /LookAheadPos_oirg (blue ball) 토픽으로 퍼블리시
        msgpub_Look_orig.publish(m_model_orig);

        m_CrossTrack_ERR = minDist;

        double dist = 0;
        int m_lookAheadIndex = -1;
        for( int i=car_waypoint; i<m_LocalSplinePath.size()-1; i++ ){
            double x2 = m_LocalSplinePath[i][0] - m_LocalSplinePath[i+1][0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_LocalSplinePath[i+1][1];
            y2 *= y2;
            dist += sqrt(x2+y2);

            if( lookAheadDist <= dist)
            {
                m_lookAheadIndex = i;
                x = m_LocalSplinePath[i][0];
                y = m_LocalSplinePath[i][1];
                resdist = dist;

                //range 0 ~ M_PI*2
                double tmp_th = atan2((y - m_pos[1]), (x - m_pos[0]));
                if(tmp_th < 0)	tmp_th = M_PI*2 + tmp_th;

                heading_Err = abs(m_pos[2] - tmp_th);
                if (heading_Err > M_PI)	heading_Err = abs(heading_Err - 2*M_PI)/M_PI;
                else heading_Err /= M_PI;

                // cross_track_Err = minDist;//sqrt((m_LocalSplinePath[car_waypoint][1] - m_pos[1])*(m_LocalSplinePath[car_waypoint][1] - m_pos[1]) + (m_LocalSplinePath[car_waypoint][0] - m_pos[0])*(m_LocalSplinePath[car_waypoint][0] - m_pos[0])); //JW 07.28.

                std_msgs::Float32MultiArray m_err;//jw 16.07.11
                m_err.data.clear();
                m_err.data.push_back(m_pos[0]);
                m_err.data.push_back(m_pos[1]);
                m_err.data.push_back(x);
                m_err.data.push_back(y);
                m_err.data.push_back(minDist);
                msgpub_err_JW.publish(m_err);

                break;
            }
        }

        if( m_lookAheadIndex == -1 )
        {
            x = m_LocalSplinePath[m_LocalSplinePath.size()-1][0];
            y = m_LocalSplinePath[m_LocalSplinePath.size()-1][1];
            resdist = -1;
        }
    }
}


void LocalPlannerThread::GetLookAheadPt_Rev(double lookAheadDist,double& x, double& y, double &resdist, int &carIdx){

    double heading_Err = 0.0; //JW 16.07.11.
    double cross_track_Err = 0.0;//JW 16.07.11.

    if (m_LocalSplinePath.size() > 1){
        double minDist = 99999;
        int car_waypoint = -1;

        for(int i = m_switch_idx ; i <= m_LocalSplinePath.size(); i++){
            double x2 = m_LocalSplinePath[i][0] - m_pos[0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_pos[1];
            y2 *= y2;

            double dist = sqrt(x2+y2);//distŽÂ
            if ( dist < minDist ){
                minDist = dist;
                car_waypoint = i;
            }
        }

        carIdx = car_waypoint;
        //cout << "car_waypoint : " << car_waypoint <<endl;
        m_pre_waypoint = car_waypoint;

        //JW 17.01.09 car pose marker
        m_model_orig.header.stamp = ros::Time::now();

        // ed: motion_planner의 좌표축을 회전하기 위해 아래와 같이 코드를 수정했다
        //m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][0];//+ m_overall*cos(th);
        //m_model_orig.pose.position.y = m_LocalSplinePath[car_waypoint][1];//+ m_overall*sin(th);
        m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][1];//+ m_overall*cos(th);
        m_model_orig.pose.position.y = -m_LocalSplinePath[car_waypoint][0];//+ m_overall*sin(th);

        // ed: msgpub_Look_orig, LookAheadPos_orig 토픽으로 퍼블리시한다
        msgpub_Look_orig.publish(m_model_orig);

        m_CrossTrack_ERR = minDist;

        double dist = 0;
        int m_lookAheadIndex = -1;
        for( int i=car_waypoint; i<m_LocalSplinePath.size()-1; i++ )
        {
            double x2 = m_LocalSplinePath[i][0] - m_LocalSplinePath[i+1][0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_LocalSplinePath[i+1][1];
            y2 *= y2;
            dist += sqrt(x2+y2);

            if( lookAheadDist <= dist)
            {
                m_lookAheadIndex = i;
                x = m_LocalSplinePath[i][0];
                y = m_LocalSplinePath[i][1];
                resdist = dist;

                //range 0 ~ M_PI*2
                double tmp_th = atan2((y - m_pos[1]), (x - m_pos[0]));
                if(tmp_th < 0)	tmp_th = M_PI*2 + tmp_th;

                heading_Err = abs(m_pos[2] - tmp_th);
                if (heading_Err > M_PI)	heading_Err = abs(heading_Err - 2*M_PI)/M_PI;
                else heading_Err /= M_PI;

                // cross_track_Err = minDist;//sqrt((m_LocalSplinePath[car_waypoint][1] - m_pos[1])*(m_LocalSplinePath[car_waypoint][1] - m_pos[1]) + (m_LocalSplinePath[car_waypoint][0] - m_pos[0])*(m_LocalSplinePath[car_waypoint][0] - m_pos[0])); //JW 07.28.

                std_msgs::Float32MultiArray m_err;//jw 16.07.11
                m_err.data.clear();
                m_err.data.push_back(m_pos[0]);
                m_err.data.push_back(m_pos[1]);
                m_err.data.push_back(x);
                m_err.data.push_back(y);
                m_err.data.push_back(minDist);
                msgpub_err_JW.publish(m_err);



                break;
            }
        }

        if( m_lookAheadIndex == -1 ) {
            x = m_LocalSplinePath[m_LocalSplinePath.size()-1][0];
            y = m_LocalSplinePath[m_LocalSplinePath.size()-1][1];
            resdist = -1;
        }
    }
}

// ed: 생성자코드
LocalPlannerThread::LocalPlannerThread(int argc, char** argv)
        :m_bThreadStop(false),init_argc(argc), init_argv(argv){
    //    printf("good777");
    m_ratio_s2w = 18.6;
    m_limit_steerAngle = 540.0;
    m_CrossTrack_ERR = 0.0;
    m_r_min = 4.85;
    m_len_dist = 0;
    m_resolution = 100;
    m_lookAheadIndex = 0;

    m_len_c2r = 1.10;
    m_len_f2r = 2.845;
    //m_overall = 1.613/2;

    ros::init(init_argc, init_argv, "LocalPlannerThread");
    ros::NodeHandle n;

    msg_steer = n.advertise<std_msgs::Float32MultiArray>("SteerAngleData", 10);


    // ed: m_CarPos, m_line_strip, m_model_jw, m_model_jw_exp, m_model_jw_exp_line, m_model_orig의 속성을 설정하는 코드들
    //     크기, 색깔, frame_id등의 정보를 설정한다

    //JW 16.07.07//jw 16.07.08
    //my_pose
    m_CarPos.header.frame_id =  m_line_strip.header.frame_id = "/camera_init";
    m_CarPos.ns = m_line_strip.ns = "RegionOfInterest";
    m_CarPos.id = 0;
    m_line_strip.id = 1;

    //m_CarPos.type= visualization_msgs::Marker::SPHERE;
    m_CarPos.type= visualization_msgs::Marker::ARROW;
    m_line_strip.type = visualization_msgs::Marker::LINE_STRIP;

    m_CarPos.action = m_line_strip.action = visualization_msgs::Marker::ADD;
    m_CarPos.pose.position.z = 0;

    m_CarPos.scale.x = 1.9;
    m_CarPos.scale.y = 1.1;
    m_CarPos.scale.z = 0.1;
    m_CarPos.color.a = 1.0;
    m_CarPos.color.r = 1.0f;
    m_CarPos.color.g = 0.0f;
    m_CarPos.color.b = 0.0f;

    m_line_strip.scale.x = 0.09;
    m_line_strip.pose.position.z = 0.1;
    m_line_strip.color.r = 1.0;
    m_line_strip.color.a = 1.0;
    //JW 16.07.07 //jw 16.07.08

    //LookAhead
    m_model_jw.header.frame_id = m_model_jw_exp.header.frame_id = m_model_jw_exp_line.header.frame_id = "/camera_init";
    m_model_jw.ns = m_model_jw_exp.ns = m_model_jw_exp_line.ns = "RegionOfInterest";
    m_model_jw.id = m_model_jw_exp.id = 0;	m_model_jw_exp_line.id = 1;

    m_model_jw.type= visualization_msgs::Marker::SPHERE;
    m_model_jw_exp.type= visualization_msgs::Marker::SPHERE;
    m_model_jw_exp_line.type= visualization_msgs::Marker::LINE_STRIP;   //LINE_LIST
    //m_model_jw_exp_line.type= visualization_msgs::Marker::LINE_LIST;  //

    m_model_jw.action = visualization_msgs::Marker::ADD;
    m_model_jw_exp.action = visualization_msgs::Marker::ADD;
    m_model_jw_exp_line.action = visualization_msgs::Marker::ADD;
    m_model_jw.pose.position.z = 0;
    m_model_jw_exp.pose.position.z = 0;


    m_model_jw.scale.x = 1.0;	m_model_jw_exp.scale.x = 0.1;
    m_model_jw.scale.y = 1.0;	m_model_jw_exp.scale.y = 0.1;
    m_model_jw.scale.z = 1.0;	m_model_jw_exp.scale.z = 0.1;
    m_model_jw.color.a = 1.0;	m_model_jw_exp.color.a = 1.0;
    m_model_jw.color.r = 0.0f;	m_model_jw_exp.color.r = 0.0f;
    m_model_jw.color.g = 1.0f;	m_model_jw_exp.color.g = 1.0f;
    m_model_jw.color.b = 0.0f;	m_model_jw_exp.color.b = 0.0f;


    // ed: m_model_jw_exp_line의 크기와 색깔을 설정한다
    m_model_jw_exp_line.scale.x = 0.09;
    m_model_jw_exp_line.pose.position.z = 0.05;
    m_model_jw_exp_line.color.r = 0.0;
    m_model_jw_exp_line.color.g = 1.0;
    m_model_jw_exp_line.color.a = 1.0;

    //jw 16.07.08
    m_model_orig.header.frame_id= "/camera_init";
    m_model_orig.ns = "RegionOfInterest";
    m_model_orig.id = 0;

    m_model_orig.type= visualization_msgs::Marker::SPHERE;
    //m_model_orig.type= visualization_msgs::Marker::ARROW;
    m_model_orig.action = visualization_msgs::Marker::ADD;
    m_model_orig.pose.position.z = 0;

    // ed: m_model_orig의 크기와 색깔을 설정한다(파란색)
    m_model_orig.scale.x = 1.0;
    m_model_orig.scale.y = 1.0;
    m_model_orig.scale.z = 1.0;
    m_model_orig.color.a = 1.0;
    m_model_orig.color.r = 0.0f;
    m_model_orig.color.g = 0.0f;
    m_model_orig.color.b = 1.0f;
    //jw 16.07.08

    m_LookAhead_X_pre = 0.0;    //JW 16.06.24.test1
    m_LookAhead_Y_pre = 0.0;    //JW 16.06.24.test1

    // ed: Publishers--------------------------------------------------------------------------
    // ed: rviz상에 초록색선을 표시하는 퍼블리셔
    msgpub = n.advertise<nav_msgs::Path>("LocalPathData", 10);

    msgpub_Look_JW = n.advertise<visualization_msgs::Marker>("LookAheadPos_exp", 10);     //real use data
    msgpub_Look_JW_exp = n.advertise<visualization_msgs::Marker>("LookAheadPos", 10);     //real use data
    msgpub_Look_orig = n.advertise<visualization_msgs::Marker>("LookAheadPos_oirg", 10);  //just visualization
    msgpub_car = n.advertise<visualization_msgs::Marker>("Car_Pos", 10);                  //car_pos_ visualization
    msgpub_err_JW = n.advertise<std_msgs::Float32MultiArray>("err_JW", 5 );      //err_
    msgpub_err_Orig = n.advertise<std_msgs::Float32MultiArray>("err_Orig", 5 );  //err_

    msgpub3 = n.advertise<std_msgs::Float32MultiArray>("ControlData", 1 );

    // ed: Subscriber--------------------------------------------------------------------------
    possub = n.subscribe("LocalizationData", 10, &LocalPlannerThread::SubTopicProcess1, this);
    possub2 = n.subscribe("RNDFPathData", 10, &LocalPlannerThread::SubTopicProcess2, this);

}

LocalPlannerThread::~LocalPlannerThread()
{}

void LocalPlannerThread::stop(){
    qDebug() << "Thread::stop called from main thread:" << currentThreadId();
    QMutexLocker locker(&m_mutex);
    m_bThreadStop = true;
}

void LocalPlannerThread::PubMsg(){
    publish_local_path(m_LocalSplinePath);
}

// ed: JW Path 버튼을 누르면 실행되는 함수
////JW 16.07.11.test1
void LocalPlannerThread::Pub_JWPathMsg(){
    //	int count = 0;
    //	double X,Y;
    //	string garbage_X,garbage_Y;

    //	ifstream fin_X, fin_Y;
    //	vector<Vector2d> nodeVec;

    //	fin_X.open("/home/dyros-vehicle/00_DATA/bag/output_X.txt");
    //	fin_Y.open("/home/dyros-vehicle/00_DATA/bag/output_Y.txt");

    //	while(fin_X != NULL)
    //	//for(int i = 0 ; i < 30 ; i++)
    //	{
    //
    //		fin_X >> X >> garbage_X;
    //		fin_Y >> Y >> garbage_Y;
    //
    //		nodeVec.push_back(Vector2d(X, Y));
    //		printf("[%d] X : %lf,  Y : %lf\n",count++,X,Y);
    //	}
    /////////////////////////////////////////////////////////////////////////////////////
    int map_cnt = 0;
    int _cnt = 0;
    double X,Y,th;
    char char1,char2;
    double vel;

    string gar_num;
    string garbage1,garbage2,garbage3,garbage4,garbage5,garbage6,garbage7,garbage8,garbage9,garbage10,garbage11,garbage12,garbage13;

    ifstream fin;
    vector<Vector2d> nodeVec;

    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/Map_0722_test2.txt");
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/Map_0722_parking2.txt");
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/Map_0722_test1.txt");
    //fin_Y.open("/home/dyros-vehicle/00_DATA/bag/output_Y.txt");
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/0808map.txt");//garage
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/0902map.txt");
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/0902map2.txt");
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/final_test_0219.txt");//circle+lane change
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/parking_complex.txt");//complex
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/map_170322.txt");//21
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/final_test_0219.txt");//complex
    ///fin.open("/home/dyros-vehicle/00_DATA/bag/map/map170105.txt");//17.01.05 parking for+rev ver1 //near
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/parking_back_short.txt");//17.01.05 parking for+rev ver2 //far
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/MAP170112.txt");//17.01.12 parking for+rev ver3 //far
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/Map170106.txt");//17.01.12 parking for+rev ver3 //
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/MAP170117.txt");//17.01.12 robot schoool
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/MAP170118.txt");//17.01.12 parking for+rev ver3 //far
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/path_seho.txt");//circle+lane change


    // ed: /LocalizationData 데이터를 기록한 웨이포인트 데이터를 읽어온다
    //                     rostopic echo /LocalizationData > waypoints.txt
    //fin.open("/home/dyros-vehicle/bag_files/0903map.txt");  //circle+lane change
    fin.open("/home/dyros-vehicle/bag_files/waypoints.txt");  //circle+lane change


    // ed: 이 루프를 통해 nodeVec에 들어가는 X, Y 값이 rviz에서 초록색선을 나타낸다
    //     publish_local_path 함수에서 실제적인 방향이 결정된다
    while(fin != NULL){
        _cnt++;

        // ed: map file로부터 x,y, theta, vel 값을 읽어온다
        fin >> garbage1>> garbage2 >> garbage3 >> garbage4 >>garbage5 >> garbage6 >> char1 >> X >> garbage8 >> Y >> garbage9 >> th >> garbage10 >> vel >> char2 >> garbage11;

        if ( vel == 9999) {
            m_switch_X = X;
            m_switch_Y = Y;
            nodeVec.push_back(Vector2d(X, Y));
            printf("[%d] X : %lf,  Y : %lf\n",map_cnt++,X,Y);
        }

        if (_cnt % MAP_RESOL == 0){  // forward push back
            nodeVec.push_back(Vector2d(X, Y));
            printf("[%d] X : %lf,  Y : %lf\n",map_cnt++,X,Y);
        }

    }

    cout << "Finish" << endl;
    //    printf("good222");
    nodeVec.push_back(Vector2d(X, Y));
    printf("[%d] X : %lf,  Y : %lf\n",map_cnt++, X, Y);

    // Generation of Interpolation Curve
    CatmullRomSpline spline;
    vector<Vector2d> curvePath = spline.PathToCurve( nodeVec, 1, SPLINE_RESOL);
    m_LocalSplinePath = curvePath;

    cout << "m_LocalSplinePath.size() : " << m_LocalSplinePath.size() << endl;

    for(int i = 0 ; i < m_LocalSplinePath.size() ; i ++){
        if(m_LocalSplinePath[i][0] == m_switch_X && m_LocalSplinePath[i][1] == m_switch_Y)
            m_switch_idx = i;
    }

    cout << "m_switch_idx : " << m_switch_idx <<endl;

    // ed: publish_local_path() 함수를 호출해서 해당 초록색 Path를 그린다
    // Publish for Visualization
    publish_local_path(m_LocalSplinePath);

    m_dir_mode = 1;
    /////////////////
    /*
      while(fin != NULL)
      {
      fin >> X >> Y >> th >> vel ;
      X = X + m_len_c2r*cos(th+1.57);
      Y = Y + m_len_c2r*sin(th+1.57);

      Y += 1.5;
      nodeVec.push_back(Vector2d(X, Y));

      if ( vel == 1)
      {
      m_switch_X = X;
      m_switch_Y = Y;
      nodeVec.push_back(Vector2d(X, Y));
      }
      printf("[%d] X : %lf,  Y : %lf\n",map_cnt++,X,Y);
      }

      // Generation of Interpolation Curve
      CatmullRomSpline spline;
      vector<Vector2d> curvePath = spline.PathToCurve( nodeVec, 1, 1);
      m_LocalSplinePath = curvePath;

      for(int i = 0 ; i < m_LocalSplinePath.size() ; i ++)
      {
      if(m_LocalSplinePath[i][0] == m_switch_X && m_LocalSplinePath[i][1] == m_switch_Y)
      m_switch_idx = i;
      }

      cout << ", m_LocalSplinePath.size() : " << m_LocalSplinePath.size() << endl;
      // Publish for Visualization
      publish_local_path(m_LocalSplinePath);

      m_dir_mode = 1;
    */
}


// ed:
//     $ rosbag play 0903map.bag 을 통해서 LocalizationData 토픽을 섭스크라이브 하면서 아래의 함수가 실행된다

//JW 16.07.11.test1
void LocalPlannerThread::Compute(){
    //printf("Car_x : %lf, Car_y : %lf\n",m_pos[0],m_pos[1]);
    //printf("good555\n");

    int carIdx;
    double vel_orig, x, y, resdist;
    double steer_Purepursuit = 0.0, steer_Radius = 0.0;
    double steer = 0.0;

    if (m_LocalSplinePath.size() > 1){

        // ed: 라디오버튼이 forward인 경우
        if (m_dir_mode == 1) {           //m_switch_flag

            if( m_vel > 5.0 * 0.278 ) {
                //printf("%lf\n",m_vel);
                GetLookAheadPt_For(2.24*m_vel, x, y, resdist, carIdx);
            }
            else{
                GetLookAheadPt_For(3.3, x, y, resdist, carIdx);
            }

            //cout << "FORWARD" <<endl;
            //cout << "CrossTrack_ERR: " << m_CrossTrack_ERR <<endl;

            //Get Look-ahead point
            //GetLookAheadPt_JW_for(carIdx, x, y, resdist);	//JW 16.07.14.test1

            ///////
            double a_ = 0.0;
            if (m_CrossTrack_ERR > dist_thresh) a_ = 1.0;
            else a_ = m_CrossTrack_ERR/dist_thresh;

            m_model_jw.header.stamp = ros::Time::now();

            // ed: motion_planner의 좌표축을 회전하기 위해 아래와 같이 코드를 수정했다
            //m_model_jw.pose.position.x = x;
            //m_model_jw.pose.position.y = y;
            m_model_jw.pose.position.x = y;
            m_model_jw.pose.position.y = -x;

            steer_Purepursuit = SteeringAng_PurePursuit(x, y, resdist);

            steer_Radius = ((steer_Purepursuit >= 0) ? 1 : (steer_Purepursuit < 0) ? -1 :0)
                           *SteeringAng_Radius(carIdx);
            steer = a_*steer_Purepursuit + (1.0-a_)*steer_Radius*0.9;

            //steer = steer_Radius;
            /*
            //
            steer_Purepursuit = a_*SteeringAng_PurePursuit(x, y, resdist);
            //
            steer_Radius = ((steer_Purepursuit>0) ? 1 : (steer_Purepursuit < 0) ? -1 :0)*SteeringAng_Radius(carIdx);
            //
            steer = steer_Radius;
            */

            //cout <<"steer : " << steer
            //     << ", steer_Purepursuit : " << steer_Purepursuit
            //     << ", steer_Radius : " << steer_Radius
            //     <<endl;

            //if(a_ > a_thresh)

            // ed: /LookAheadPos_exp로 퍼블리시
            msgpub_Look_JW.publish(m_model_jw);
        }

        // ed: 라디오버튼이 reverse인 경우
        else if (m_dir_mode == -1) {
            cout << "BBBBACKWARD" <<endl;

            GetLookAheadPt_Rev(1.0, x, y, resdist, carIdx);
            //GetLookAheadPt_JW_rev(carIdx,x,y,resdist);
            double a_ = 0.0;
            if (m_CrossTrack_ERR > dist_thresh) a_ = 1.0;
            else a_ = m_CrossTrack_ERR/dist_thresh;

            //
            steer_Purepursuit = SteeringAng_PurePursuit(x, y, resdist);
            //
            steer_Radius = ((steer_Purepursuit >= 0) ? 1 : (steer_Purepursuit < 0) ? -1 :0)
                           *SteeringAng_Radius(carIdx);
            //
            //steer = a_*steer_Purepursuit + (1.0-a_)*steer_Radius*0.8;
            steer = steer_Radius;
            /*
            //
            steer_Purepursuit = a_*SteeringAng_PurePursuit(x, y, resdist);
            //
            steer_Radius = ((steer_Purepursuit>0) ? 1 : (steer_Purepursuit < 0) ? -1 :0)*SteeringAng_Radius(carIdx);
            //
            steer = steer_Radius;
            */
            cout <<"steer : " << steer
                 << ", steer_Purepursuit : " << steer_Purepursuit
                 << ", steer_Radius : " << steer_Radius
                 <<endl;
        }
    }

    std_msgs::Float32MultiArray msg;

    // ed: 여기서 스티어링각도가 설정된다. radian으로 변환해서 퍼블리시
    msg.data.push_back(steer * _DEG2RAD);
    //msg.data.push_back(2);  // ed: velocity [m/s]
    //     velocity용 publisher만들어서 1,2는 엑셀,브레이크로 정해져있고 3,4를 속도, gear값을 추가해서 테스트해보기

    // msg.data.push_back(500);

    // ed: msg_steer, SteeringAngleData 토픽으로 퍼블리시한다
    msg_steer.publish(msg);


    //////////////////////////////////////////////////////////////
    // ControlData Message
    m_msg.data.clear();
    m_msg.data.push_back(x);
    m_msg.data.push_back(y);
    m_msg.data.push_back(resdist);
    m_msg.data.push_back(m_pos[0]);
    m_msg.data.push_back(m_pos[1]);
    m_msg.data.push_back(m_pos[2]);

    // ed: 단위는 m/s
    float targetVel = 2;

    // ed: targetVel을 설정하는 코드인듯하다
    if( resdist == -1)
        m_msg.data.push_back(0);
    else
        m_msg.data.push_back(2);  // ed: [m/s] 단위


    // ed: ControlData 토픽으로 퍼블리시한다
    msgpub3.publish(m_msg);

    // ed: 제대로 작동하는지 속도를 보는 코드
    //printf("target : %lf m/s\n current : %lf m/s\n", targetVel , m_vel);

    m_model_jw_exp.header.stamp = ros::Time::now();

    // ed: motion_planner의 좌표축을 회전하기 위해 아래와 같이 코드를 수정했다
    //   m_model_jw_exp.pose.position.x = x;
    // m_model_jw_exp.pose.position.y = y;
    m_model_jw_exp.pose.position.x = y;
    m_model_jw_exp.pose.position.y = -x;

    // ed: msgpub_Look_JW_exp, LookAheadPos 토픽으로 퍼블리시한다
    msgpub_Look_JW_exp.publish(m_model_jw_exp);

    //JW 16.07.07
    // My_pos Message Red
    m_CarPos.header.stamp = ros::Time::now();

    double heading = m_pos[2];

    if ( heading > M_PI )  heading = heading - M_PI*2;

    // ed: motion_planner의 좌표축을 회전하기 위해 아래와 같이 코드를 수정했다
    //     화살표의 방향을 90도 회전시킨다
    heading = heading - 0.5 * M_PI;
    //m_CarPos.pose.position.x = m_pos[0];
    //m_CarPos.pose.position.y = m_pos[1];
    m_CarPos.pose.position.x = m_pos[1];
    m_CarPos.pose.position.y = -m_pos[0];

    geometry_msgs::Quaternion m_CarPos_odom_quat = tf::createQuaternionMsgFromYaw(heading);
    m_CarPos.pose.orientation = m_CarPos_odom_quat;

    // ed: /Car_Pos 토픽으로 퍼블리시
    msgpub_car.publish(m_CarPos);

    static int pub_cnt;
    pub_cnt++;
    //cout << pub_cnt <<endl;
    if(pub_cnt == 55){
        //JW 16.07.08 Trajectory Red
        m_line_strip.points.push_back(m_CarPos.pose.position);
        m_model_jw_exp_line.points.push_back(m_model_jw.pose.position);
        pub_cnt=0;
    }

    // ed: /LookAheadPos_exp 토픽으로 퍼블리시
    msgpub_Look_JW.publish(m_model_jw_exp_line);
    // ed: /Car_Pos 토픽으로 퍼블리시
    msgpub_car.publish(m_line_strip);


    //JW 16.07.08
    ////////////////////////////////////////////////////////////////
}

double LocalPlannerThread::SteeringAng_PurePursuit(double lookX, double lookY, double resdist){
    double steerAngle = 0.0;
    double heading = m_pos[2]*_RAD2DEG;
    double lookAheadLength = 0.0;

    if( resdist == -1.0){
        steerAngle = 0.0;
    }
    else if(resdist > 0.0) { //forward
        // Pure Pursuit Algorithm
        //m_pos[0] = m_pos[0] - m_len_c2r*cos(heading*_DEG2RAD);
        //m_pos[1] = m_pos[1] - m_len_c2r*sin(heading*_DEG2RAD);

        ////eta
        double m_LookAhead_vec = atan2((lookY - m_pos[1]), (lookX - m_pos[0]));
        if(m_LookAhead_vec < 0)	m_LookAhead_vec = M_PI*2 + m_LookAhead_vec;
        // cout << "m_LookAhead_vec : " << m_LookAhead_vec*_RAD2DEG << endl;
        // cout << "heading : " << heading << endl;

        double m_eta = -(heading*_DEG2RAD - m_LookAhead_vec);		//cout << "eta [" << i + 1 << "] : " << m_eta*_RAD2DEG << endl;
        //cout << "eta : " << m_eta*_RAD2DEG << endl;
        ////Lfw
        double m_Lx = abs(lookX - m_pos[0]);		//cout << "Lx [" << i + 1 << "] : " << m_Lx << endl;
        double m_Ly = abs(lookY - m_pos[1]);		//cout << "Ly [" << i + 1 << "] : " << m_Ly << endl;
        double m_Lfw = sqrt(m_Lx*m_Lx + m_Ly*m_Ly);		//cout << "Lfw [" << i + 1 << "] : " << m_Lfw << endl;

        //cout << "m_Lfw : " << m_Lfw << endl;
        // double steerAngle = 90 * _DEG2RAD - atan2((m_Lfw / 2 + m_len_c2r*cos(m_eta)), (m_len_f2r * sin(m_eta)));
        steerAngle = -atan((m_len_f2r * sin(m_eta)) / (m_Lfw / 2 + m_len_c2r*cos(m_eta)));
        //if (abs(steerAngle) > 30 * _DEG2RAD)	break;
        steerAngle *= _RAD2DEG;
        steerAngle *= m_ratio_s2w;
        //cout << "steer1 : " << (steerAngle) << endl << endl;
        if(abs(steerAngle) > m_limit_steerAngle)
            steerAngle = ((steerAngle>0) ? 1 : (steerAngle < 0) ? -1 :0) * m_limit_steerAngle;

        lookAheadLength = m_Lfw;
        //cout << "[for] steer : " << steerAngle << endl << endl;

        return steerAngle;
    }
    else if(resdist < 0.0){  //reverse
        // Pure Pursuit Algorithm
        //m_pos[0] = m_pos[0] - 2*m_len_c2r*cos(heading*_DEG2RAD);
        // m_pos[1] = m_pos[1] - 2*m_len_c2r*sin(heading*_DEG2RAD);

        ////eta
        double m_LookAhead_vec = atan2((lookY - m_pos[1]), (lookX - m_pos[0]));
        if(m_LookAhead_vec < 0)	m_LookAhead_vec = M_PI*2 + m_LookAhead_vec;
        // cout << "m_LookAhead_vec : " << m_LookAhead_vec*_RAD2DEG << endl;
        // cout << "heading : " << heading << endl;

        double m_eta = 3.14+(heading*_DEG2RAD - m_LookAhead_vec);		//cout << "eta [" << i + 1 << "] : " << m_eta*_RAD2DEG << endl;
        //cout << "eta : " << m_eta*_RAD2DEG << endl;
        ////Lfw
        double m_Lx = abs(lookX - m_pos[0]);		//cout << "Lx [" << i + 1 << "] : " << m_Lx << endl;
        double m_Ly = abs(lookY - m_pos[1]);		//cout << "Ly [" << i + 1 << "] : " << m_Ly << endl;
        double m_Lfw = sqrt(m_Lx*m_Lx + m_Ly*m_Ly);		//cout << "Lfw [" << i + 1 << "] : " << m_Lfw << endl;

        //cout << "m_Lfw : " << m_Lfw << endl;
        // double steerAngle = 90 * _DEG2RAD - atan2((m_Lfw / 2 + m_len_c2r*cos(m_eta)), (m_len_f2r * sin(m_eta)));
        steerAngle = -atan((m_len_f2r * sin(m_eta)) / (m_Lfw / 2 + m_len_c2r*cos(m_eta)));
        //if (abs(steerAngle) > 30 * _DEG2RAD)	break;
        steerAngle *= _RAD2DEG;
        steerAngle *= m_ratio_s2w;
        //cout << "steer1 : " << (steerAngle) << endl << endl;
        if(abs(steerAngle) > m_limit_steerAngle)
            steerAngle = ((steerAngle>0) ? 1 : (steerAngle < 0) ? -1 :0) * m_limit_steerAngle;

        lookAheadLength = m_Lfw;
        //cout << "[rev] steer : " << steerAngle << endl << endl;

        return steerAngle;
    }
}

double LocalPlannerThread::SteeringAng_Radius(int carIdx){
    //radius
    double Steer_Radius = 0.0;
    double Radius = cur_rad(m_LocalSplinePath[carIdx-Radius_points][1], m_LocalSplinePath[carIdx-Radius_points][0],
                            m_LocalSplinePath[carIdx][1], m_LocalSplinePath[carIdx][0],
                            m_LocalSplinePath[carIdx+Radius_points][1], m_LocalSplinePath[carIdx+Radius_points][0]
                            );

    //cout << ", Radius : " << Radius << endl;

    double tmp_steer_Radius = m_limit_steerAngle*m_r_min/(Radius);
    if(tmp_steer_Radius > m_limit_steerAngle) tmp_steer_Radius = m_limit_steerAngle;

    double steer_Radius = tmp_steer_Radius;
    //double steer_Radius = (1.0-lps_a)*m_pre_steer_Radius + lps_a*tmp_steer_Radius;
    //m_pre_steer_Radius = tmp_steer_Radius;

    //th err
    double tmp_th = atan2((m_LocalSplinePath[carIdx+Radius_points][1]- m_LocalSplinePath[carIdx][1]),
                          (m_LocalSplinePath[carIdx+Radius_points][0] - m_LocalSplinePath[carIdx][0]));
    //if(tmp_th < 0)	tmp_th = M_PI*2 + tmp_th;
    double heading = m_pos[2];
    if ( heading > M_PI )  heading = heading - M_PI*2;
    double heading_Err = abs(abs(heading) - abs(tmp_th))*_RAD2DEG*m_limit_steerAngle/(2*th_err_range);
    //cout << heading << " " << tmp_th << endl;
    if(heading_Err > m_limit_steerAngle) heading_Err = m_limit_steerAngle;

    // cout << "steer_Radius : " << steer_Radius << ", heading_Err : " << heading_Err <<endl;
    return Steer_Radius = steer_Radius + heading_Err;
}

void LocalPlannerThread::run(){
    int cntLoop =0;
    int index =0;
    ros::Rate loop_rate(10);

    while(1){
        if(m_bThreadStop)
            break;

        loop_rate.sleep();
        ros::spinOnce();
    }
}

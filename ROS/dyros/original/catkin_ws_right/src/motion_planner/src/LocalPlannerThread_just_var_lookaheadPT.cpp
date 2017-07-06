#include "../inc/LocalPlannerThread.h"
#include <QPointF>  
#include <QDebug>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include "../inc/CatmullRomSpline.h"

#define MAP_RESOL 200
#define SPLINE_RESOL 1000


#define FR_V_MAX 25.0/2.24
#define REV_V_MAX 7.0
#define TH_SCALE 0.79
#define lps_a 0.1
#define Thre_L 0.3

// From Localization Module
void LocalPlannerThread::SubTopicProcess1(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
    m_pos[0] = msg->data.at(0);
    m_pos[1] = msg->data.at(1);
    m_pos[2] = msg->data.at(2);
    m_vel = msg->data.at(3); // m/s

    Compute();
}

void LocalPlannerThread::SubTopicProcess2(const nav_msgs::Path::ConstPtr& msg)
{
    // Insertion Global Path Data to Vector Struct
    vector<Vector2d> nodeVec;
    for( int i=0; i<msg->poses.size(); i++)
    {
        nodeVec.push_back(Vector2d(msg->poses[i].pose.position.x, msg->poses[i].pose.position.y));
    }

    // Generation of Interpolation Curve
    CatmullRomSpline spline;
    vector<Vector2d> curvePath = spline.PathToCurve( nodeVec, 1, 1000);
    m_LocalSplinePath = curvePath;

    // Publish for Visualization
    publish_local_path(m_LocalSplinePath);
}

void LocalPlannerThread::publish_local_path(vector<Vector2d> path)
{
    nav_msgs::Path msg;
    std::vector<geometry_msgs::PoseStamped> waypoints;
    msg.header.frame_id = "/camera_init";
    msg.header.stamp = ros::Time::now();


    ofstream fout;
    fout.open("/home/dyros-vehicle/00_DATA/bag/map/MAP170118_spline.txt");

    //////////////////////////////////////////
    // POSE STAMPED
    for(int i=0; i<path.size(); i++)
    {
        geometry_msgs::PoseStamped waypt;
        waypt.header.frame_id = "/camera_init";
        waypt.header.stamp = ros::Time::now();

        waypt.pose.position.x = path[i][0];
        waypt.pose.position.y = path[i][1];
        waypt.pose.position.z = 0;
        waypoints.push_back(waypt);

        fout << path[i][0] << " " << path[i][1] << endl;
    }

    fout.close();
    msg.poses.resize(waypoints.size());

    // Extract the plan in world coordinates, we assume the path is all in the same frame
    for(unsigned int i=0; i < waypoints.size(); i++)
    {
        msg.poses[i] = waypoints[i];
    }
    msgpub.publish(msg);

}


void LocalPlannerThread::GetLookAheadPt_JW_rev(double &carIdx,double& x, double& y, double &resdist)
{
    double heading_Err = 0.0; //JW 16.07.11.
    double cross_track_Err = 0.0;//JW 16.07.11.
    double delta_LookAhead = 0.0;
    double curvature_norm = 0;
    double car_heading = 0.0;

    if (m_LocalSplinePath.size() > 1)
    {
        double minDist = 99999;
        int car_waypoint = -1;
        for(int i = m_pre_waypoint; i < m_LocalSplinePath.size(); i++)
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
        m_pre_waypoint = car_waypoint;
//JW 17.01.09 car pose marker
        m_model_orig.header.stamp = ros::Time::now();
        m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][0];//+ m_overall*cos(th);
        m_model_orig.pose.position.y = m_LocalSplinePath[car_waypoint][1] ;//+ m_overall*sin(th);
        msgpub_Look_orig.publish(m_model_orig);

        //Velodyne to car rearwheel
        //m_pos[0] -= m_len_c2r*cos(car_heading);
        //m_pos[1] -= m_len_c2r*sin(car_heading);
//Error
    //car_heading
        //range 0 ~ M_PI*2
        //JW 16.06.24.test1
        car_heading = m_pos[2];//range 0 ~ M_PI*2

        //range 0 ~ M_PI*2
        double tmp_th = atan2((m_LookAhead_Y - m_pos[1]), (m_LookAhead_X - m_pos[0]));
        if(tmp_th < 0)	tmp_th = M_PI*2 + tmp_th;

        heading_Err = M_PI - abs(car_heading - tmp_th);//JW Rev
        if (heading_Err > M_PI)	heading_Err = abs(heading_Err - 2*M_PI)/M_PI;
        else heading_Err /= M_PI;
    //cross-track
        cross_track_Err = minDist;//sqrt((m_LocalSplinePath[car_waypoint][1] - m_pos[1])*(m_LocalSplinePath[car_waypoint][1] - m_pos[1]) + (m_LocalSplinePath[car_waypoint][0] - m_pos[0])*(m_LocalSplinePath[car_waypoint][0] - m_pos[0])); //JW 07.28.

        m_CrossTrack_ERR = cross_track_Err;

        ////////////////////////////////////////////////////////////////////
        if(cross_track_Err > FR_V_MAX)	cross_track_Err = FR_V_MAX;//prohibit the cross-track err overflow

        //double TH_ERR = TH_SCALE*(1.0-sin(heading_Err*M_PI/2));
        //if ( heading_Err >= 0.5 ) heading_Err = 0.5;
        double TH_ERR = TH_SCALE*heading_Err;

        m_TH_ERR = heading_Err;
        double LEN_ERR = (1.0-TH_SCALE)*(heading_Err)*cross_track_Err;

        //TH_ERR *= TH_ERR;TH_ERR *= TH_ERR;
        //point
        delta_LookAhead = REV_V_MAX*(TH_ERR + LEN_ERR);//curvature_norm*10;//*(LEN_ERR);

        ////////////////////////////////////////////////////////////////

        double lookAhead_Dist = 0;//;

        if( delta_LookAhead < 3) lookAhead_Dist = 3;
        else if(delta_LookAhead > 12) lookAhead_Dist = 12.0;
        else lookAhead_Dist = delta_LookAhead ;

        double lookAheadDist = (1.0-lps_a)*m_pre_lookAheadDist + lps_a*lookAhead_Dist;
        m_pre_lookAheadDist = lookAheadDist;

        cout << "delta_LookAhead : " << lookAheadDist << ", delta_LookAhead : " << delta_LookAhead << ", m_len_dist : " << m_len_dist << endl;
        cout << "vel : " << lookAheadDist*2.24 << ", real_vel : " << m_vel*3.6 << ", TH_ERR : " << TH_ERR << ", Dist_ERR : "<< LEN_ERR << endl<< endl;

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

            if( lookAheadDist <= dist )
            {
                //cout << "m_lookAheadIndex : " << i <<endl;

                m_lookAheadIndex = i;
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

                break;
            }
            if(i == m_LocalSplinePath.size()-2)
            {
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

        if( m_lookAheadIndex == -1 )
        {
            x = m_LocalSplinePath[m_LocalSplinePath.size()-1][0];
            y = m_LocalSplinePath[m_LocalSplinePath.size()-1][1];
            resdist = -1;
        }
    }
}

void LocalPlannerThread::GetLookAheadPt_JW_for(double &carIdx,double& x, double& y, double &resdist)
{
    double heading_Err = 0.0; //JW 16.07.11.
    double cross_track_Err = 0.0;//JW 16.07.11.

    double delta_LookAhead = 0.0;

    double curvature_norm = 0;
    double m_velo = 0;
    double car_heading = 0.0;

    if (m_LocalSplinePath.size() > 1)
    {
        double minDist = 99999;
        int car_waypoint = -1;
        for(int i = m_pre_waypoint ; i<m_LocalSplinePath.size(); i++)
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
        m_model_orig.pose.position.x = m_LocalSplinePath[car_waypoint][0];//+ m_overall*cos(th);
        m_model_orig.pose.position.y = m_LocalSplinePath[car_waypoint][1];//+ m_overall*sin(th);
        msgpub_Look_orig.publish(m_model_orig);

        /*
        double cur_tmp;
        cur_rad(m_LocalSplinePath[car_waypoint-1][0], m_LocalSplinePath[car_waypoint-1][1],
                m_LocalSplinePath[car_waypoint][0], m_LocalSplinePath[car_waypoint][1],
                m_LocalSplinePath[car_waypoint+1][0], m_LocalSplinePath[car_waypoint+1][1],
                cur_tmp);
        m_cur_wp = cur_tmp;
        */
        //if(cur_tmp < 100)   m_cur_wp = cur_tmp;
        //else m_cur_wp = 0;

        //Velodyne to car rearwheel
        //m_pos[0] -= m_len_c2r*cos(car_heading);
        //m_pos[1] -= m_len_c2r*sin(car_heading);

//Error
    //cross-track
        cross_track_Err = minDist;//sqrt((m_LocalSplinePath[car_waypoint][1] - m_pos[1])*(m_LocalSplinePath[car_waypoint][1] - m_pos[1]) + (m_LocalSplinePath[car_waypoint][0] - m_pos[0])*(m_LocalSplinePath[car_waypoint][0] - m_pos[0])); //JW 07.28.        
        m_CrossTrack_ERR = cross_track_Err;
        if(cross_track_Err > FR_V_MAX)	cross_track_Err = FR_V_MAX;//prohibit the cross-track err overflow

////////////////////////////////////////////////////////////////////
    //car_heading
        //range 0 ~ M_PI*2
        //JW 16.06.24.test1
        car_heading = m_pos[2];//range 0 ~ M_PI*2

        double tmp_th = atan2((m_LookAhead_Y - m_pos[1]), (m_LookAhead_X - m_pos[0]));
        if(tmp_th < 0)	tmp_th = M_PI*2 + tmp_th;
        heading_Err = abs(car_heading - tmp_th);
        //if (heading_Err > M_PI)	heading_Err = abs(heading_Err - 2*M_PI);
        if (heading_Err >= M_PI/2 ) heading_Err = M_PI/2;
        //double TH_ERR = TH_SCALE*(1.0-sin(heading_Err*M_PI/2));
        if ( heading_Err >= 0.5 ) heading_Err = 0.5;

/////////////////////////////////////////////////////////////

        double TH_ERR = TH_SCALE*(1.0-sin(heading_Err*M_PI));
        //TH_ERR *= TH_ERR;
        m_TH_ERR = TH_ERR;        
        double LEN_ERR = (1.0-TH_SCALE)*sin(heading_Err*M_PI/2)*cross_track_Err;

        //point
        delta_LookAhead = FR_V_MAX*(TH_ERR + LEN_ERR) - m_len_dist;//curvature_norm*10;//*(LEN_ERR);

////////////////////////////////////////////////////////////////

        double lookAhead_Dist = 0;//- m_len_dist;

        if( delta_LookAhead < 3) lookAhead_Dist = 3;
        else if(delta_LookAhead > 12) lookAhead_Dist = 12.0;
        else lookAhead_Dist = delta_LookAhead ;

        double lookAheadDist = (1.0-lps_a)*m_pre_lookAheadDist + lps_a*lookAhead_Dist;
        m_pre_lookAheadDist = lookAheadDist;

        //lookAheadDist = (int)(lookAheadDist*10)*0.1;
        cout << "delta_LookAhead : " << lookAheadDist << ", delta_LookAhead : " << delta_LookAhead << ", m_len_dist : " << m_len_dist << endl;
        cout << "vel : " << lookAheadDist*2.24 << ", real_vel : " << m_vel*3.6 << ", TH_ERR : " << TH_ERR << ", Dist_ERR : "<< LEN_ERR << endl<< endl;

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

            if(i >= m_LocalSplinePath.size()- 2)
            {
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

        if( m_lookAheadIndex == -1 )
        {
            x = m_LocalSplinePath[m_LocalSplinePath.size()-1][0];
            y = m_LocalSplinePath[m_LocalSplinePath.size()-1][1];
            resdist = -1;
        }
    }
}
void LocalPlannerThread::cur_rad(double x1, double y1,
                                double x2, double y2,
                                double x3, double y3,
                                double &rad)
{
    double d1 = (x2-x1)/(y2-y1);
    double d2 = (x3-x2)/(y3-y2);
    double c_x = ((y3-y1)+(x2-x3)*d2-(x1+x2)*d1)/(2*(d2-d1));
    double c_y = -d1*(c_x-((x1+x2)/2))+(y1+y2)/2;
    rad = sqrt(pow((x1-c_x),2)+pow(y1-c_y,2));
}

void LocalPlannerThread::GetLookAheadPt(double lookAheadDist,double& x, double& y, double &resdist)
{

    double heading_Err = 0.0; //JW 16.07.11.
    double cross_track_Err = 0.0;//JW 16.07.11.


    if (m_LocalSplinePath.size() > 1)
    {
        double minDist = 99999;
        int car_waypoint = -1;
        int lookIndex = -1;
        for(int i = 0; i<m_LocalSplinePath.size(); i++)
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

        if( m_lookAheadIndex == -1 )
        {
            x = m_LocalSplinePath[m_LocalSplinePath.size()-1][0];
            y = m_LocalSplinePath[m_LocalSplinePath.size()-1][1];
            resdist = -1;
        }

    }


}

LocalPlannerThread::LocalPlannerThread(int argc, char** argv)
    :m_bThreadStop(false),init_argc(argc), init_argv(argv)
{
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
    //JW 16.07.07//jw 16.07.08

    //LookAhead
    m_model_jw.header.frame_id = m_model_jw_exp.header.frame_id = m_model_jw_exp_line.header.frame_id = "/camera_init";
    m_model_jw.ns = m_model_jw_exp.ns = m_model_jw_exp_line.ns = "RegionOfInterest";
    m_model_jw.id = m_model_jw_exp.id = 0;	m_model_jw_exp_line.id = 1;

    m_model_jw.type= visualization_msgs::Marker::SPHERE;
    m_model_jw_exp.type= visualization_msgs::Marker::SPHERE;
    m_model_jw_exp_line.type= visualization_msgs::Marker::LINE_STRIP;//LINE_LIST
    //m_model_jw_exp_line.type= visualization_msgs::Marker::LINE_LIST;//

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

    m_model_orig.scale.x = 1.0;
    m_model_orig.scale.y = 1.0;
    m_model_orig.scale.z = 1.0;
    m_model_orig.color.a = 1.0;
    m_model_orig.color.r = 0.0f;
    m_model_orig.color.g = 0.0f;
    m_model_orig.color.b = 1.0f;
    //jw 16.07.08

    m_LookAhead_X_pre = 0.0;//JW 16.06.24.test1
    m_LookAhead_Y_pre = 0.0;//JW 16.06.24.test1


    msgpub = n.advertise<nav_msgs::Path>("LocalPathData", 10);
    msgpub_Look_JW = n.advertise<visualization_msgs::Marker>("LookAheadPos_exp", 10);//real use data
    msgpub_Look_JW_exp = n.advertise<visualization_msgs::Marker>("LookAheadPos", 10);//real use data
    msgpub_Look_orig = n.advertise<visualization_msgs::Marker>("LookAheadPos_oirg", 10);//just visualization
    msgpub_car = n.advertise<visualization_msgs::Marker>("Car_Pos", 10);//car_pos_ visualization
    msgpub_err_JW = n.advertise<std_msgs::Float32MultiArray>("err_JW", 5 );//err_
    msgpub_err_Orig = n.advertise<std_msgs::Float32MultiArray>("err_Orig", 5 );//err_
    msgpub3 = n.advertise<std_msgs::Float32MultiArray>("ControlData", 1 );



    possub = n.subscribe("LocalizationData", 10, &LocalPlannerThread::SubTopicProcess1, this);
    possub2 = n.subscribe("RNDFPathData", 10, &LocalPlannerThread::SubTopicProcess2, this);

}

LocalPlannerThread::~LocalPlannerThread()
{

}

void LocalPlannerThread::stop()
{
    qDebug()<<"Thread::stop called from main thread:"<<currentThreadId();
    QMutexLocker locker(&m_mutex);
    m_bThreadStop = true;
}

void LocalPlannerThread::PubMsg()
{
    publish_local_path(m_LocalSplinePath);
}

////JW 16.07.11.test1
void LocalPlannerThread::Pub_JWPathMsg()
{
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
    fin.open("/home/dyros-vehicle/00_DATA/bag/map/parking_complex.txt");//complex

    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/final_test_0219.txt");//complex
    ///fin.open("/home/dyros-vehicle/00_DATA/bag/map/map170105.txt");//17.01.05 parking for+rev ver1 //near
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/parking_back_short.txt");//17.01.05 parking for+rev ver2 //far
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/MAP170112.txt");//17.01.12 parking for+rev ver3 //far
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/Map170106.txt");//17.01.12 parking for+rev ver3 //
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/MAP170117.txt");//17.01.12 robot schoool
    //fin.open("/home/dyros-vehicle/00_DATA/bag/map/MAP170118.txt");//17.01.12 parking for+rev ver3 //far

    while(fin != NULL)
    {
        _cnt++;

        fin >> garbage1>> garbage2 >> garbage3 >> garbage4 >>garbage5 >> garbage6 >>char1 >> X >>garbage8 >> Y>>garbage9 >> th >>garbage10 >> vel >>char2 >> garbage11;

        //cout <<"["<<map_cnt++ <<"] "<< garbage1 <<" "<<garbage2<<" "<< garbage3<<" "<< garbage4<<" " <<garbage5<<" "<< garbage6<<" "<<char1<<" "<< X<<" "<<garbage8<<" "<< Y<<" "<<garbage9<<" "<< th<<" "<<garbage10<<" "<< vel<<char2<<" " << garbage11 <<endl <<endl;
        //cout <<"["<<map_cnt++ <<"] "<< X<<", "<< Y<<", "<<th<<", "<<vel << ", "<<pre_vel <<endl;


        if (_cnt % MAP_RESOL == 0) // forward push back
        {
            nodeVec.push_back(Vector2d(X, Y));
            printf("[%d] X : %lf,  Y : %lf\n",map_cnt++,X,Y);
        }
    }

    cout << "Finish" << endl;
    nodeVec.push_back(Vector2d(X, Y));
    printf("[%d] X : %lf,  Y : %lf\n",map_cnt++,X,Y);

    // Generation of Interpolation Curve
    CatmullRomSpline spline;
    vector<Vector2d> curvePath = spline.PathToCurve( nodeVec, 1, SPLINE_RESOL);
    m_LocalSplinePath = curvePath;

    cout << ", m_LocalSplinePath.size() : " << m_LocalSplinePath.size() << endl;
    // Publish for Visualization
    publish_local_path(m_LocalSplinePath);


}
////JW 16.07.11.test1

void LocalPlannerThread::Compute()
{
    //printf("Car_x : %lf, Car_y : %lf\n",m_pos[0],m_pos[1]);

    double vel_orig, carIdx, x, y, resdist;
    double x_orig, y_orig;

    if (m_dir_mode == 1)//m_switch_flag
    {
        //cout << "FORWARD" <<endl;
        GetLookAheadPt_JW_for(carIdx, x, y, resdist);	//JW 16.07.14.test1
        m_model_jw.header.stamp = ros::Time::now();

        m_model_jw.pose.position.x = x;
        m_model_jw.pose.position.y = y;

        msgpub_Look_JW.publish(m_model_jw);
    }
    else if (m_dir_mode == -1)
    {
    }

    //////////////////////////////////////////////////////////////
    // ControlData Message
    m_msg.data.clear();
    m_msg.data.push_back(x);
    m_msg.data.push_back(y);
    m_msg.data.push_back(resdist);
    m_msg.data.push_back(m_pos[0]);
    m_msg.data.push_back(m_pos[1]);
    m_msg.data.push_back(m_pos[2]);

    if( resdist == -1)
    {
        m_msg.data.push_back(0.0*0.278);
    }
    else
    {
        m_msg.data.push_back(4.8*0.278);
    }
    msgpub3.publish(m_msg);
    m_model_jw_exp.header.stamp = ros::Time::now();
    m_model_jw_exp.pose.position.x = x;
    m_model_jw_exp.pose.position.y = y;
    msgpub_Look_JW_exp.publish(m_model_jw_exp);

    //JW 16.07.07
    // My_pos Message Red
    m_CarPos.header.stamp = ros::Time::now();
    if ( m_pos[2] > M_PI )
        m_pos[2] = m_pos[2] - M_PI*2;
    m_CarPos.pose.position.x = m_pos[0];
    m_CarPos.pose.position.y = m_pos[1];
    geometry_msgs::Quaternion m_CarPos_odom_quat = tf::createQuaternionMsgFromYaw(m_pos[2]);
    m_CarPos.pose.orientation = m_CarPos_odom_quat;
    msgpub_car.publish(m_CarPos);

    static int pub_cnt;
    pub_cnt++;
    //cout << pub_cnt <<endl;
    if(pub_cnt == 55)
    {
        //JW 16.07.08 Trajectory Red
        m_line_strip.points.push_back(m_CarPos.pose.position);
        m_model_jw_exp_line.points.push_back(m_model_jw.pose.position);
        pub_cnt=0;
    }


    msgpub_Look_JW.publish(m_model_jw_exp_line);
    msgpub_car.publish(m_line_strip);

    //JW 16.07.08

    ////////////////////////////////////////////////////////////////
}

void LocalPlannerThread::run()
{
    int cntLoop =0;
    int index =0;
    ros::Rate loop_rate(10);

    while(1)
    {
        if(m_bThreadStop) break;


        ros::spinOnce();
        loop_rate.sleep();

    }
}

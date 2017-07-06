#include "../inc/LocalPlannerThread.h"
#include <QPointF>
#include <QDebug>
#include "../inc/CatmullRomSpline.h"

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
        vector<Vector2d> curvePath = spline.PathToCurve( nodeVec, 1, 100);
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

    }

    msg.poses.resize(waypoints.size());

    // Extract the plan in world coordinates, we assume the path is all in the same frame
    for(unsigned int i=0; i < waypoints.size(); i++)
    {
        msg.poses[i] = waypoints[i];
    }
    msgpub.publish(msg);

}

void LocalPlannerThread::GetLookAheadPt(double lookAheadDist,double& x, double& y, double &resdist)
{
    if (m_LocalSplinePath.size() > 1)
    {

        double minDist = 99999;
        int cIndex = -1;
        int lookIndex = -1;
        for(int i = 0; i<m_LocalSplinePath.size(); i++)
        {
            double x2 = m_LocalSplinePath[i][0] - m_pos[0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_pos[1];
            y2 *= y2;
            double dist = sqrt(x2+y2);
            if ( dist < minDist )
            {
                minDist = dist;
                cIndex = i;
            }
        }

        double dist = 0;
        int lookAheadIndex = -1;
        for( int i=cIndex; i<m_LocalSplinePath.size()-1; i++ )
        {
            double x2 = m_LocalSplinePath[i][0] - m_LocalSplinePath[i+1][0];
            x2 *= x2;
            double y2 = m_LocalSplinePath[i][1] - m_LocalSplinePath[i+1][1];
            y2 *= y2;
            dist += sqrt(x2+y2);

            if( lookAheadDist <= dist)
            {
                lookAheadIndex = i;
                x = m_LocalSplinePath[i+1][0];
                y = m_LocalSplinePath[i+1][1];
                resdist = dist;
                break;
            }
        }

        if( lookAheadIndex == -1 )
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
    ros::init(init_argc, init_argv, "LocalPlannerThread");
    ros::NodeHandle n;

    m_model.header.frame_id= "/camera_init";
    m_model.ns = "RegionOfInterest";
    m_model.id = 0;

    m_model.type= visualization_msgs::Marker::SPHERE;
    m_model.action = visualization_msgs::Marker::ADD;
    m_model.pose.position.z = 0;

    m_model.scale.x = 1.0;
    m_model.scale.y = 1.0;
    m_model.scale.z = 1.0;
    m_model.color.a = 1.0;
    m_model.color.r = 1.0f;
    m_model.color.g = 0.0f;
    m_model.color.b = 0.0f;

    msgpub = n.advertise<nav_msgs::Path>("LocalPathData", 10);
    msgpub2 = n.advertise<visualization_msgs::Marker>("LookAheadPos", 10);
    msgpub3 = n.advertise<std_msgs::Float32MultiArray>("ControlData", 10);


    possub = n.subscribe("LocalizationData2", 10, &LocalPlannerThread::SubTopicProcess1, this);
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

void LocalPlannerThread::Compute()
{
  	double x, y, resdist;

	if( m_vel > 8.0 * 0.278 )
	{
		//printf("%lf\n",m_vel);
		GetLookAheadPt(4.0*m_vel, x, y, resdist);
	}	
	else
	{
		GetLookAheadPt(6.0, x, y, resdist);
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

	// Look Ahead Message 
	m_model.header.stamp = ros::Time::now();
	m_model.pose.position.x = x;
	m_model.pose.position.y = y;
	msgpub2.publish(m_model);
	////////////////////////////////////////////////////////////////
}

void LocalPlannerThread::run()
{
    int cntLoop =0;
    int index =0;
    ros::Rate loop_rate(1000);

    while(1)
    {
        if(m_bThreadStop) break;


        ros::spinOnce();
        loop_rate.sleep();
        
    }
}

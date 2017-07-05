
#ifndef _GPS_TEST_H_
#define _GPS_TEST_H_

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <visualization_msgs/Marker.h>

namespace gps_test {

class GPS_data
{

public:

	GPS_data(ros::NodeHandle node);
	~GPS_data();
//private:

	void msgCallback(const std_msgs::Float32MultiArray::ConstPtr& msg);

//public:
	visualization_msgs::Marker m_points, m_line_strip; 

	ros::Subscriber gps_sub;
	ros::Publisher gps_pub;
	
	geometry_msgs::Point p;
};

}// namespace gps_test

#endif

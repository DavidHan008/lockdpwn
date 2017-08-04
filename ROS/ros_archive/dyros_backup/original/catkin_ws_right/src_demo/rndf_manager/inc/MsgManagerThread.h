#pragma once
#include <QtGui/QMainWindow>
#include <QtCore>
//#include <Eigen/Core>
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include "../../../build/rndf_manager/ui_rndf_manager_gui.h"
#include "./RNDF_LIB/rndf_mdf_reader.h"

//using namespace Eigen;

class MsgManagerThread : public QThread
{
	Q_OBJECT;
	
	private :
		int init_argc;
		char** init_argv;
		
        struct RNDF *m_pRNDF;
            struct MDF *m_pMDF;
		
		ros::Subscriber possub;
        ros::Publisher msgpub;
		////////////////////////////////
		bool m_bThreadStop;
		bool m_bSubTopicUpdated;
		QMutex m_mutex;
	public :
		//void SubTopicProcess(const MotionPlanner::LocalizationData::ConstPtr& msg);
        MsgManagerThread(int argc, char** argv, struct RNDF *pRNDF, struct MDF* pMDF);
		~MsgManagerThread();

		void PubSegMsg(int segNum);
		void PubAllSegMsg();
		
		void GraphGeneration();

		nav_msgs::Path SegmentPathMsg(int segNum);
		//EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	public slots:
		void stop();
	private:		
		void run();
		
};

#include "../inc/VelocityCtrlThread.h"
#include "../inc/PurePursuitThread.h"
#include <QDebug>
#include <std_msgs/Float32MultiArray.h>
//#include <iostream>

#define _RAD2DEG	(180./M_PI)
#define _DEG2RAD	(M_PI/180.)
using namespace std;

// ed: /ControlData 토픽을 섭스크라이브하는 콜백함수
void PurePursuitThread::SubscribeTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg){
  //qDebug()<<"Thread::LocalizationTopicProcess x:"<<msg->x<<" y:"<<msg->y;
  m_lookX =msg->data.at(0);
  m_lookY = msg->data.at(1);
  m_resdist =msg->data.at(2);

  m_pos[0] = msg->data.at(3);
  m_pos[1] = msg->data.at(4);


  m_heading = msg->data.at(5)*_RAD2DEG;

  //printf("good");
  Compute();
  /*
    if( msg->data.at(5)*_RAD2DEG < 0 )
    {
    m_heading = 360.0 + msg->data.at(5)*_RAD2DEG;
    }
    else
    {
    m_heading = msg->data.at(5)*_RAD2DEG;
    }

    m_heading += 90.0;
    if( m_heading > 360.0)
    {
    m_heading = m_heading - 360.0;
    }
  */
  //m_heading = m_heading ;
  //std::cout << "heading " << m_heading << " " << msg->data.at(5)<<std::endl;
       

}


PurePursuitThread::PurePursuitThread(int argc, char** argv, Ui::MainWindow* ui)
    :m_bThreadStop(false)
    , init_argc(argc), init_argv(argv), _ui(ui)  {

  ros::init(init_argc, init_argv, "PurePursuitThread");
  ros::NodeHandle n;

  pVelocityCtrlThread = NULL; //JW

  _cnt =0;
  m_lookX = 0.0;
  m_lookY = 0.0;
  m_resdist = -1.0;

  // receive topic
  // topicName, queue size
  m_len_c2r = 1.10;
  m_len_f2r = 2.845;
  m_ratio_s2w = 18.6;
  m_limit_steerAngle = 540.0;
  m_bPosTopicUpdated = false;

  possub = n.subscribe("ControlData", 10, &PurePursuitThread::SubscribeTopicProcess, this);

  // publish data
  msgpub = n.advertise<std_msgs::Float32MultiArray>("SteerAngleData", 10);

  //_ui->label_sas->setText(QString::number(0));
  _ui->label_sas->setText(QString::number(m_steerAngle));
}


void PurePursuitThread::stop(){
  qDebug()<<"Thread::stop called from main thread:"<<currentThreadId();
  QMutexLocker locker(&m_mutex);
  m_bThreadStop = true;
  _ui->label_sas->setText("---");
}


void PurePursuitThread::Compute(){
  if( _ui->checkBox_Manual->isChecked() ) {
    std_msgs::Float32MultiArray msg;
    msg.data.push_back(_ui->lcdNumber->value());
    msgpub.publish(msg);
  }
  else
  {
    if( m_resdist == -1.0)  {
      m_steerAngle = 0;
    }
    else if(m_resdist > 0.0) { //forward

      m_lookAheadPos[0] = m_lookX;
      m_lookAheadPos[1] = m_lookY;


      // Pure Pursuit Algorithm
      //m_pos[0] = m_pos[0] - m_len_c2r*cos(m_heading*_DEG2RAD);
      //m_pos[1] = m_pos[1] - m_len_c2r*sin(m_heading*_DEG2RAD);
				
      ////eta
      double m_LookAhead_vec = atan2((m_lookAheadPos[1] - m_pos[1]), (m_lookAheadPos[0] - m_pos[0]));

      if(m_LookAhead_vec < 0)	m_LookAhead_vec = M_PI*2 + m_LookAhead_vec;

      // cout << "m_LookAhead_vec : " << m_LookAhead_vec*_RAD2DEG << endl;
      // cout << "m_heading : " << m_heading << endl;

      double m_eta = -(m_heading*_DEG2RAD - m_LookAhead_vec);		//cout << "eta [" << i + 1 << "] : " << m_eta*_RAD2DEG << endl;
      //cout << "eta : " << m_eta*_RAD2DEG << endl;

      ////Lfw
      double m_Lx = abs(m_lookAheadPos[0] - m_pos[0]);		//cout << "Lx [" << i + 1 << "] : " << m_Lx << endl;
      double m_Ly = abs(m_lookAheadPos[1] - m_pos[1]);		//cout << "Ly [" << i + 1 << "] : " << m_Ly << endl;
      double m_Lfw = sqrt(m_Lx*m_Lx + m_Ly*m_Ly);		//cout << "Lfw [" << i + 1 << "] : " << m_Lfw << endl;


      //cout << "m_Lfw : " << m_Lfw << endl;
      // double m_steerAngle = 90 * _DEG2RAD - atan2((m_Lfw / 2 + m_len_c2r*cos(m_eta)), (m_len_f2r * sin(m_eta)));
      m_steerAngle = -atan((m_len_f2r * sin(m_eta)) / (m_Lfw / 2 + m_len_c2r*cos(m_eta)));
      //if (abs(m_steerAngle) > 30 * _DEG2RAD)	break;
      m_steerAngle *= _RAD2DEG;
      m_steerAngle *= m_ratio_s2w;
      //cout << "steer1 : " << (m_steerAngle) << endl << endl;
      if(m_steerAngle>m_limit_steerAngle) {
        m_steerAngle=m_limit_steerAngle;
      }
      else if(m_steerAngle<-m_limit_steerAngle) {
        m_steerAngle=-m_limit_steerAngle;
      }

      m_lookAheadLength = m_Lfw;
      cout << "[for] steer : " << (m_steerAngle) << endl << endl;

      /////////////////////////////DYROS Steer
      //Vector2d L = m_lookAheadPos-m_pos;
      //Vector2d Yv(-sin(m_heading*_DEG2RAD),cos(m_heading*_DEG2RAD));
      //Vector2d YL(L[0]*Yv[0],L[1]*Yv[1]);


      //float YLtemp = YL[0]+YL[1];

      //       if( YLtemp != 0 )
      //       {
      //           m_lookAheadLength = L.norm();

      //           m_steerAngle = (m_ratio_s2w*m_len_f2r*2.0*YLtemp)/(m_lookAheadLength*m_lookAheadLength);
      //           m_steerAngle *= _RAD2DEG;
      //           m_steerAngle *= -1.0;
      //           if(m_steerAngle>m_limit_steerAngle)
      //           {
      //m_steerAngle=m_limit_steerAngle;
      //           }
      //           else if(m_steerAngle<-m_limit_steerAngle)
      //           {
      //               m_steerAngle=-m_limit_steerAngle;
      //           }
      //           //printf("Pos:(%f,%f) LookPos:(%f,%f) lookLength:%f(%f) steer:%f steer(before):%f heading:%f(%f)\n",m_pos[0], m_pos[1], m_lookAheadPos[0], m_lookAheadPos[1],m_lookAheadLength,resdist,m_steerAngle,tmpSteer,m_heading,m_heading_ori);
      //           //printf("Pos:(%f,%f) LookPos:(%f,%f) L:(%f,%f) Yv:(%f,%f) YL:(%f,%f) YLtemp:%f lookLength:%f(%f) steer:%f steer(before):%f heading:%f\n",m_pos[0], m_pos[1], m_lookAheadPos[0], m_lookAheadPos[1],L[0],L[1],Yv[0],Yv[1],YL[0],YL[1],YLtemp,m_lookAheadLength,resdist,m_steerAngle,tmpSteer,m_heading);

      //       }
      //       else
      //       {
      //           m_steerAngle = 0;
      //       }
    }
    else if(m_resdist < 0.0)//reverse
    {
      m_lookAheadPos[0] = m_lookX;
      m_lookAheadPos[1] = m_lookY;


      // Pure Pursuit Algorithm
      m_pos[0] = m_pos[0] - 2*m_len_c2r*cos(m_heading*_DEG2RAD);
      m_pos[1] = m_pos[1] - 2*m_len_c2r*sin(m_heading*_DEG2RAD);
				
      ////eta
      double m_LookAhead_vec = atan2((m_lookAheadPos[1] - m_pos[1]), (m_lookAheadPos[0] - m_pos[0]));
      if(m_LookAhead_vec < 0)	m_LookAhead_vec = M_PI*2 + m_LookAhead_vec;
      // cout << "m_LookAhead_vec : " << m_LookAhead_vec*_RAD2DEG << endl;
      // cout << "m_heading : " << m_heading << endl;

      double m_eta = 3.14+(m_heading*_DEG2RAD - m_LookAhead_vec);		//cout << "eta [" << i + 1 << "] : " << m_eta*_RAD2DEG << endl;
      //cout << "eta : " << m_eta*_RAD2DEG << endl;
      ////Lfw
      double m_Lx = abs(m_lookAheadPos[0] - m_pos[0]);		//cout << "Lx [" << i + 1 << "] : " << m_Lx << endl;
      double m_Ly = abs(m_lookAheadPos[1] - m_pos[1]);		//cout << "Ly [" << i + 1 << "] : " << m_Ly << endl;
      double m_Lfw = sqrt(m_Lx*m_Lx + m_Ly*m_Ly);		//cout << "Lfw [" << i + 1 << "] : " << m_Lfw << endl;
					
      //cout << "m_Lfw : " << m_Lfw << endl;
      // double m_steerAngle = 90 * _DEG2RAD - atan2((m_Lfw / 2 + m_len_c2r*cos(m_eta)), (m_len_f2r * sin(m_eta)));
      m_steerAngle = -atan((m_len_f2r * sin(m_eta)) / (m_Lfw / 2 + m_len_c2r*cos(m_eta)));
      //if (abs(m_steerAngle) > 30 * _DEG2RAD)	break;
      m_steerAngle *= _RAD2DEG;
      m_steerAngle *= m_ratio_s2w;
      //cout << "steer1 : " << (m_steerAngle) << endl << endl;
      if(m_steerAngle>m_limit_steerAngle)
      {
        m_steerAngle=m_limit_steerAngle;
      }
      else if(m_steerAngle<-m_limit_steerAngle)
      {
        m_steerAngle=-m_limit_steerAngle;
      }
      m_lookAheadLength = m_Lfw;
      cout << "[rev] steer : " << (m_steerAngle) << endl << endl;

      /////////////////////////////DYROS Steer
      //Vector2d L = m_lookAheadPos-m_pos;
      //Vector2d Yv(-sin(m_heading*_DEG2RAD),cos(m_heading*_DEG2RAD));
      //Vector2d YL(L[0]*Yv[0],L[1]*Yv[1]);


      //float YLtemp = YL[0]+YL[1];

      //       if( YLtemp != 0 )
      //       {
      //           m_lookAheadLength = L.norm();

      //           m_steerAngle = (m_ratio_s2w*m_len_f2r*2.0*YLtemp)/(m_lookAheadLength*m_lookAheadLength);
      //           m_steerAngle *= _RAD2DEG;
      //           m_steerAngle *= -1.0;
      //           if(m_steerAngle>m_limit_steerAngle)
      //           {
      //m_steerAngle=m_limit_steerAngle;
      //           }
      //           else if(m_steerAngle<-m_limit_steerAngle)
      //           {
      //               m_steerAngle=-m_limit_steerAngle;
      //           }
      //           //printf("Pos:(%f,%f) LookPos:(%f,%f) lookLength:%f(%f) steer:%f steer(before):%f heading:%f(%f)\n",m_pos[0], m_pos[1], m_lookAheadPos[0], m_lookAheadPos[1],m_lookAheadLength,resdist,m_steerAngle,tmpSteer,m_heading,m_heading_ori);
      //           //printf("Pos:(%f,%f) LookPos:(%f,%f) L:(%f,%f) Yv:(%f,%f) YL:(%f,%f) YLtemp:%f lookLength:%f(%f) steer:%f steer(before):%f heading:%f\n",m_pos[0], m_pos[1], m_lookAheadPos[0], m_lookAheadPos[1],L[0],L[1],Yv[0],Yv[1],YL[0],YL[1],YLtemp,m_lookAheadLength,resdist,m_steerAngle,tmpSteer,m_heading);

      //       }
      //       else
      //       {
      //           m_steerAngle = 0;
      //       }
    }


    //m_steerAngle = ((int)(m_steerAngle*0.1) * 10);
    //_cnt++;
    //if( _cnt == 25 )
    //{
    //printf("Steer : %lf\n",m_steerAngle);
			

    //_ui->label_sas->setText(QString::number(m_steerAngle));
    //qDebug()<<"steerAngle : "<<m_steerAngle ;
    //_cnt =0;

    //}


    if(pVelocityCtrlThread != NULL)
    {
      //std::cout << "ang : "  << m_steerAngle << std::endl;
      //std::cout << "vel : "  << m_lookAheadLength << "km/h" << std::endl;
      if(m_lookAheadLength > 8)
        m_lookAheadLength = 8;
      pVelocityCtrlThread->TargetVelUpdate(m_lookAheadLength*0.278);
    }
			
    std_msgs::Float32MultiArray msg;
    msg.data.push_back(m_steerAngle);
    msgpub.publish(msg);
  }

}
void PurePursuitThread::run()
{
    
  ros::Rate loop_rate(100);
  while(1)
  {
        
    {
      QMutexLocker locker(&m_mutex);
      if(m_bThreadStop) break;
    }
    ros::spinOnce();
    loop_rate.sleep();

  }
}

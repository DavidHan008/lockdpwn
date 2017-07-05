#include <QtGui>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QImage>
#include <stdio.h>
#include <iostream>
#include <AngleUtils.h>
#include "../inc/rndf_manager_main.h"

using namespace std;

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent), _argc(argc), _argv(argv)
{
    ros::init(_argc, _argv, "MsgManagerThread");
    ros::NodeHandle n;

    //possub = n.subscribe("LocalizationData", 10, &MsgManagerThread::SubTopicProcess, this);
    msgpub = n.advertise<nav_msgs::Path>("RNDFPathData", 100);

    ////////////////////////////////////////////////////////////////////////////////////////////
    ui.setupUi(this);

    // Initialization UI
    connect( ui.checkBox_TargetNode1, SIGNAL(clicked()), this, SLOT(OnCheckBoxTarNode1_clicked()) );
    connect( ui.checkBox_TargetNode2, SIGNAL(clicked()), this, SLOT(OnCheckBoxTarNode2_clicked()) );

    ui.spinBox_TarSeg->setEnabled(true);
    ui.spinBox_TarLane->setEnabled(true);
    ui.spinBox_TarWaypt->setEnabled(true);

    ui.mRNDFFileName->setText("/home/dyros-vehicle/00_DATA/rndf.txt");
    ui.mMDFFileName->setText("/home/dyros-vehicle/00_DATA/mdf.txt");

    ////////////////////////////////////////////////////////////////////////////////////////////

    m_pMDF = NULL;
    m_pRNDF = NULL;
    m_pImg = NULL;
    m_pBuffer =NULL;

    QString filename = "/home/dyros-vehicle/00_DATA/RDNF/mapimage.png";

    m_pImg = new QImage();
    m_pBuffer = new QPixmap();

    if(m_pImg->load(filename))
    {
        *m_pBuffer = QPixmap::fromImage(*m_pImg);
        *m_pBuffer = m_pBuffer->scaled(m_pImg->width()*0.64,m_pImg->height()*0.64);
    }
    else
    {
        QMessageBox::about(0, QString::fromAscii("Image load Error"),QString::fromAscii("Image load Error"));
    }
    ui.label_map->setPixmap(*m_pBuffer);

    pMsgManagerThread = NULL;
    m_pShortestPath = NULL;
    m_bRNDFLoaded = false;
    m_bMDFLoaded = false;

    m_pRNDFFILE = NULL;
    m_pMDFFILE = NULL;
    
     // service for potential map
    service_client = n.serviceClient<rndf_manager::srvHeightMap>("height_map_srv");
}


MainWindow::~MainWindow()
{
    if( m_pImg != NULL )
        delete m_pImg;
    if( m_pBuffer != NULL )
        delete m_pBuffer;

    if( m_pShortestPath != NULL )
    {
        delete m_pShortestPath;
        m_pShortestPath = NULL;
    }

    if( m_pMDF != NULL )
        freeMDF(m_pMDF);
    if( m_pRNDF != NULL )
        freeRNDF(m_pRNDF);

    if(pMsgManagerThread != NULL)
    {
        pMsgManagerThread->stop();
        pMsgManagerThread->wait();
        delete pMsgManagerThread;
        pMsgManagerThread = NULL;
    }

    if( m_pRNDFFILE != NULL ) fclose(m_pRNDFFILE);
    if( m_pMDFFILE != NULL ) fclose(m_pMDFFILE);
    //printf("FREE RNDF\n");
    
}

void MainWindow::OnCheckBoxTarNode1_clicked()
{

    ui.checkBox_TargetNode2->setCheckState(Qt::Unchecked);
    ui.spinBox_CheckTarPt->setEnabled(false);

    ui.spinBox_TarSeg->setEnabled(true);
    ui.spinBox_TarLane->setEnabled(true);
    ui.spinBox_TarWaypt->setEnabled(true);

}

void MainWindow::OnCheckBoxTarNode2_clicked()
{
    ui.checkBox_TargetNode1->setCheckState(Qt::Unchecked);
    ui.spinBox_CheckTarPt->setEnabled(true);

    ui.spinBox_TarSeg->setEnabled(false);
    ui.spinBox_TarLane->setEnabled(false);
    ui.spinBox_TarWaypt->setEnabled(false);
}

void MainWindow::on_RNDFFileFindBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open RNDF File"), "/home/dyros-vehicle/00_DATA/RNDF/", tr("TXT Files (*.txt)"));
    ui.mRNDFFileName->setText(fileName);  
}

void MainWindow::on_MDFFileFindBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open MDF File"), "/home/dyros-vehicle/00_DATA/RNDF/", tr("TXT Files (*.txt)"));
    ui.mMDFFileName->setText(fileName);
}

void MainWindow::on_BuildGraph_clicked()
{
    if( m_pRNDFFILE != NULL )
    {
	fclose(m_pRNDFFILE);
	m_pRNDFFILE = NULL;
    }
    if( m_pMDFFILE != NULL ) 
    {
        fclose(m_pMDFFILE);
        m_pMDFFILE = NULL;
    }

    QString str = ui.mRNDFFileName->text();
    m_pRNDFFILE = fopen(str.toStdString().c_str(),"r");
    if( m_pRNDFFILE != NULL)
    {
	//printf("RNDF File is loading... \n ");
        m_pRNDF = parseAnalyzeRndfFile(m_pRNDFFILE);
        m_bRNDFLoaded = true;
        printf("RNDF File is successfully loaded. \n ");
    }
    else
    {
        m_bRNDFLoaded = false;
        printf("RDNF is not loaded. \n ");
    }

    QString str2 = ui.mMDFFileName->text();
   // m_pMDFFILE = fopen(str2.toStdString().c_str(),"r");
  //  if( m_pMDFFILE != NULL)
   // {
	//printf("MDF File is loading... \n ");
   //     m_pMDF = parseAnalyzeMdfFile(m_pMDFFILE);
//	m_bMDFLoaded = true;        
//	printf("MDF File is successfully loaded. \n ");        
  //  }
   // else
  //  {
  //      printf("MDF File is not loaded. \n ");
//m_bMDFLoaded = false;
  //  }


    if( m_bRNDFLoaded)// && m_bMDFLoaded)
    {
        if( m_pShortestPath != NULL )
        {
            delete m_pShortestPath;
            m_pShortestPath = NULL;
        }
        m_pShortestPath = new CShortestPath(m_pRNDF,m_pMDF);
	printf("1\n");
        m_pShortestPath->BuildGraph();
	printf("2\n");
    }

}

void MainWindow::on_pushButton_check1_clicked()
{
    ui.spinBox_CheckTarPt->setValue(1);
}

void MainWindow::on_pushButton_check2_clicked()
{
    ui.spinBox_CheckTarPt->setValue(2);
}

void MainWindow::on_pushButton_check3_clicked()
{
    ui.spinBox_CheckTarPt->setValue(3);
}

void MainWindow::on_pushButton_check4_clicked()
{
    ui.spinBox_CheckTarPt->setValue(4);
}

void MainWindow::on_pushButton_check5_clicked()
{
    ui.spinBox_CheckTarPt->setValue(5);
}

void MainWindow::on_SearchBtn_clicked()
{
    if( m_pShortestPath != NULL )
    {

        id startId;
        startId.x = ui.spinBox_CurSeg->value();
        startId.y = ui.spinBox_CurLane->value();
        startId.z = ui.spinBox_CurWaypt->value();
        if( m_pShortestPath->ValidVertexId(&startId) )
        {

            id targetId;
            if( ui.checkBox_TargetNode2->checkState() == Qt::Checked )
            {
                int index = ui.spinBox_CheckTarPt->value();

                if( m_pShortestPath->ValidCheckPointId(index,&targetId) )
                {
                    float lat, lon;
                    if( m_pShortestPath->GetIndexPosition(&targetId, lat, lon) )
                    {
                        std::cout<< targetId.x << "." << targetId.y <<"." << targetId.z <<"="<< lat << " " << lon <<std::endl;
                    }

                    m_pShortestPath->GetPathCurrentPosToCheckPoint2(&startId, &targetId);
                }
                else
                {
                    std::cout<<"Invalid target Id\n"<<std::endl;
                }
            }
            else
            {
                targetId.x = ui.spinBox_TarSeg->value();
                targetId.y = ui.spinBox_TarLane->value();
                targetId.z = ui.spinBox_TarWaypt->value();
                if( m_pShortestPath->ValidVertexId(&targetId) )
                {
                    m_pShortestPath->GetPathCurrentPosToCheckPoint2(&startId, &targetId);
                }
                else
                {
                    std::cout<<"Invalid target Id\n"<<std::endl;
                }
            }

        }
        else
        {
            std::cout<<"Invalid start Id\n"<<std::endl;
        }

    }
    publish_Global_path();
}

void MainWindow::on_StartPubMsgBtn_clicked()
{
    if(pMsgManagerThread == NULL)
    {
        if( m_pShortestPath != NULL)
        {
            pMsgManagerThread = new MsgManagerThread(_argc,_argv,m_pRNDF, m_pMDF);
            pMsgManagerThread->start();
        }
    }
}

void MainWindow::on_StopPubMsgBtn_clicked()
{
    if(pMsgManagerThread != NULL)
    {
        pMsgManagerThread->stop();
        pMsgManagerThread->wait();
        delete pMsgManagerThread;
        pMsgManagerThread = NULL;
    }
}

void MainWindow::on_PubSegMsgBtn_clicked()
{
    if(pMsgManagerThread != NULL)
    {
        pMsgManagerThread->PubSegMsg(ui.segNumSpinBox->value());
    }
}

void MainWindow::publish_Global_path()
{
    if( m_pShortestPath != NULL )
    {
        nav_msgs::Path msg;
        std::vector<geometry_msgs::PoseStamped> waypoints;
        msg.header.frame_id = "/camera_init";
        msg.header.stamp = ros::Time::now();


        //////////////////////////////////////////
        // POSE STAMPED
        vector<Vector2d> path = m_pShortestPath->GetResolvedPath();
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
        
        
        
        //////////////////////////////////////////// 
        // Height Map Service
        Vector2d vec1 = path[path.size()-1];
		Vector2d vec2 = path[path.size()-2];

		rndf_manager::srvHeightMap srv;
		srv.request.x = vec1(0);
		srv.request.y = vec1(1);
		srv.request.theta = AngleUtils::angle(vec2 - vec1);
		srv.request.mode = 2.0;

		if( service_client.call(srv) )
		{
			std::cout << " receive from heightmap srv !\n";
		}
		// Revised by shinsh - 21.10.2015
		/////////////////////////////////////////////
    }
}

void MainWindow::on_PubAllSegMsgBtn_clicked()
{
    if(pMsgManagerThread != NULL)
    {
        pMsgManagerThread->PubSegMsg(-1);
    }
}

int main(int argc, char** argv)
{

    QApplication app(argc, argv);
    MainWindow w(argc, argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

    return app.exec();
}

#include <QtGui>
#include <QApplication>
//#include "NameThread.h"
#include <stdio.h>
#include <iostream>
#include "../inc/motion_planner_main.h"
#include "../inc/LocalPlannerThread.h"
using namespace std;


CmdCommandThread::CmdCommandThread(QString cmd, QObject * parent)
    : QThread(parent)
    , cmd(cmd)
{

    threadStop = false;
}

void CmdCommandThread::stop()
{
    threadStop = true;
    char cmd[1024];

    sprintf(cmd, "kill -SIGINT %lld", pid);

    printf("%s\n", cmd);

    QProcess kill;
    kill.start(cmd);
    kill.waitForFinished(-1);

}


void CmdCommandThread::run()
{
//	qDebug("cmd Thread Start");

    QProcess process;
    process.start(cmd);
    pid = process.pid();
    process.waitForFinished(-1);


//	QString p_stdout = process.readAllStandardOutput();
//	QString p_stderr = process.readAllStandardError();


//	qDebug("cmd Thread End");

}
///////////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	
	connect(ui.horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(Set_tar_vel(int)));//10.14
	connect(ui.horizontalScrollBar_2,SIGNAL(valueChanged(int)),this,SLOT(Set_tar_rot(int)));//10.14


	connect( ui.forward, SIGNAL(clicked()), this, SLOT(drive_dir()) );
	connect( ui.reverse, SIGNAL(clicked()), this, SLOT(drive_dir()) );

	ui.forward->setEnabled(true);
	ui.reverse->setEnabled(true);

	    pLocalPlannerThread = NULL;
	    trakerThread = NULL;
	    rndfThread = NULL;
	    rvizThread = NULL;

	    if(pLocalPlannerThread == NULL)
	    {
		    pLocalPlannerThread = new LocalPlannerThread(argc,argv);
		    pLocalPlannerThread->start(); 
	    }
}

MainWindow::~MainWindow() 
{
    if(pLocalPlannerThread != NULL)
    {
        pLocalPlannerThread->stop();
        pLocalPlannerThread->wait();
        delete pLocalPlannerThread;
        pLocalPlannerThread = NULL;
    }

    if( rvizThread != NULL )
    {
        rvizThread->stop();
        rvizThread->wait();
	rvizThread = NULL;
    }

    if( trakerThread != NULL )
    {
        trakerThread->stop();
        trakerThread->wait();
	trakerThread = NULL;
      //  ui.label_traker1->setText("OFF");
    }
}


void MainWindow::Set_tar_vel(int value)//10cm
{
	//cout << "Offset Val : " << value << endl;
	pLocalPlannerThread->TargetVelUpdate(value*0.1);//10cm->1m
	ui.lcdNumber->display(value*0.1);
}

void MainWindow::Set_tar_rot(int value)//10cm
{
	//cout << "Offset Val : " << value << endl;
	pLocalPlannerThread->TargetRotUpdate(value);//10cm->1m
	ui.lcdNumber_2->display(value);
}

void MainWindow::on_pushButton_traker1_off_clicked()
{
	if( trakerThread != NULL )
    {
        trakerThread->stop();
        trakerThread->wait();
	trakerThread = NULL;
      //  ui.label_traker1->setText("OFF");
    }
}
void MainWindow::on_pushButton_traker1_on_clicked()
{
    if( trakerThread == NULL )
    {
    	QString cmd = "rosrun controller controller";
    	trakerThread = new CmdCommandThread(cmd);
    	trakerThread->start();
      //  ui.label_traker1->setText("ON");
    }
}

void MainWindow::on_pushButton_rviz_off_clicked()
{
	if( rvizThread != NULL )
    {
        rvizThread->stop();
        rvizThread->wait();
	rvizThread = NULL;
    }
}

void MainWindow::on_pushButton_rviz_on_clicked()
{
    if( rvizThread == NULL )
    {
    	QString cmd = "rosrun rviz rviz";
    	rvizThread = new CmdCommandThread(cmd);
    	rvizThread->start();
    }
}

void MainWindow::on_pushButton_PubMsg_clicked()
{
	if( pLocalPlannerThread != NULL)
	{
		pLocalPlannerThread->PubMsg();
	}
}

void MainWindow::on_pushButton_JWPath_clicked()
{
	if( pLocalPlannerThread != NULL)
	{
		pLocalPlannerThread->Pub_JWPathMsg();
	}

}

void MainWindow::on_pushButton_offsetreset_clicked()
{ 
	pLocalPlannerThread->TargetVelUpdate(0);//10cm->1m
	ui.lcdNumber->display(0);
	ui.horizontalScrollBar->setValue(0);		

}

void MainWindow::on_pushButton_offsetreset_2_clicked()
{ 
	pLocalPlannerThread->TargetRotUpdate(0);//10cm->1m
	ui.lcdNumber_2->display(0);
	ui.horizontalScrollBar_2->setValue(0);		

}
void MainWindow::drive_dir()
{
	if( pLocalPlannerThread != NULL)
	{
		if( ui.forward->isChecked() )
		{
			pLocalPlannerThread->dir_mode = 1;
			//printf("forward\n");
			
		}
		else if(ui.reverse->isChecked() )
		{	
			pLocalPlannerThread->dir_mode = -1;
			//printf("reverse\n");
		}
		else
		{
			pLocalPlannerThread->dir_mode = 0;
			//printf("None\n");
		}
		

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

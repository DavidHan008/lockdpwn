#include <QtGui>
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include "../inc/controller_main.h"
#include "../inc/PurePursuitThread.h"
#include "../inc/VelocityCtrlThread.h"

using namespace std;

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
        : QMainWindow(parent),_argc(argc),_argv(argv)
{
    ui.setupUi(this);
    recordStop = false;

    pPurePursuitThread = NULL;
    
    pPurePursuitThread = new PurePursuitThread(_argc,_argv,&ui);
    pPurePursuitThread->start();
    

    pVelocityCtrlThread = NULL;
	

	
    
    connect(ui.horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(setLCDValue(int)));

    connect(ui.horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(setLCDValue_tar_vel(int)));
    connect(ui.horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(Set_tar_vel(int)));
    
}

void MainWindow::on_pushButton_LF_clicked()
{
    ui.lcdNumber->display(-538);
}
void MainWindow::on_pushButton_Z_clicked()
{
    ui.lcdNumber->display(0);
}
void MainWindow::on_pushButton_RF_clicked()
{
    ui.lcdNumber->display(538);
}
void MainWindow::setLCDValue(int value)
{
    ui.lcdNumber->display(value);
}

void MainWindow::setLCDValue_tar_vel(int value)
{
    ///QString str;
    //str.format("%dkm/h", value);
    //ui.label_tarvel->setText(str);
    ui.lcdNumber_tar_vel->display(value);
}

void MainWindow::Set_tar_vel(int value)
{
    if(pVelocityCtrlThread != NULL)
	pVelocityCtrlThread->TargetVelUpdate(value*0.278);
}


MainWindow::~MainWindow()
{
    if(pPurePursuitThread != NULL)
    {
        pPurePursuitThread->stop();
        pPurePursuitThread->wait();
        delete pPurePursuitThread;
        pPurePursuitThread = NULL;
    }
    if(pVelocityCtrlThread != NULL)
    {
        pVelocityCtrlThread->stop();
        pVelocityCtrlThread->wait();
        delete pVelocityCtrlThread;
        pVelocityCtrlThread = NULL;
    }
}

void MainWindow::on_pushButton_stop_2_clicked()
{
    ui.label_state->setText("stop");
    if(pPurePursuitThread != NULL)
    {
        pPurePursuitThread->stop();
        pPurePursuitThread->wait();
        delete pPurePursuitThread;
        pPurePursuitThread = NULL;
    }
}

void MainWindow::on_pushButton_start_2_clicked()
{

    ui.label_state->setText("start");
    if(pPurePursuitThread == NULL)
    {
        pPurePursuitThread = new PurePursuitThread(_argc,_argv,&ui);
        pPurePursuitThread->start();
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    if(pVelocityCtrlThread == NULL)
    {
        pVelocityCtrlThread = new VelocityCtrlThread(_argc,_argv,&ui);
        pPurePursuitThread->pVelocityCtrlThread = pVelocityCtrlThread;//JW
        pVelocityCtrlThread->start();
	
    }
    
}

void MainWindow::on_pushButton_stop_clicked()
{
    
    if(pVelocityCtrlThread != NULL)
    {
        pVelocityCtrlThread->stop();
        pVelocityCtrlThread->wait();
        delete pVelocityCtrlThread;
        pVelocityCtrlThread = NULL;
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



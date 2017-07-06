#include <QtGui>
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include "../inc/motion_planner_main.h"
#include "../inc/LocalPlannerThread.h"
//#include "NameThread.h"

using namespace std;

CmdCommandThread::CmdCommandThread(QString cmd, QObject * parent)
    : QThread(parent), cmd(cmd) {
  threadStop = false;
}

void CmdCommandThread::stop(){
  threadStop = true;
  char cmd[1024];

  sprintf(cmd, "kill -SIGINT %lld", pid);

  printf("%s\n", cmd);

  QProcess kill;
  kill.start(cmd);
  kill.waitForFinished(-1);

}

void CmdCommandThread::run(){
  // qDebug("cmd Thread Start");

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
    : QMainWindow(parent){
  ui.setupUi(this);

  // ed: GUI에 forward, reverse 라디오버튼에 대한 코드인듯
  connect( ui.forward, SIGNAL(clicked()), this, SLOT(drive_dir()) );
  connect( ui.reverse, SIGNAL(clicked()), this, SLOT(drive_dir()) );

  ui.forward->setEnabled(true);
  ui.reverse->setEnabled(true);

  pLocalPlannerThread = NULL;
  trakerThread = NULL;
  rndfThread = NULL;
  rvizThread = NULL;

  if(pLocalPlannerThread == NULL){
    pLocalPlannerThread = new LocalPlannerThread(argc,argv);
    pLocalPlannerThread->start();
  }
}

MainWindow::~MainWindow() {
  if(pLocalPlannerThread != NULL){
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
    ui.label_traker1->setText("OFF");
  }
}

void MainWindow::on_pushButton_traker1_off_clicked(){
  if( trakerThread != NULL ){
    trakerThread->stop();
    trakerThread->wait();
    trakerThread = NULL;
    ui.label_traker1->setText("OFF");
  }
}

void MainWindow::on_pushButton_traker1_on_clicked(){
  if( trakerThread == NULL ){
    QString cmd = "rosrun controller controller";
    trakerThread = new CmdCommandThread(cmd);
    trakerThread->start();
    ui.label_traker1->setText("ON");
  }
}

// ed: rviz를 종료하는 함수
void MainWindow::on_pushButton_rviz_off_clicked(){
  if( rvizThread != NULL ){
    rvizThread->stop();
    rvizThread->wait();
    rvizThread = NULL;
  }
}

// ed: rviz를 실행하는 함수
void MainWindow::on_pushButton_rviz_on_clicked(){
  if( rvizThread == NULL ){
    QString cmd = "rosrun rviz rviz";
    rvizThread = new CmdCommandThread(cmd);
    rvizThread->start();
  }
}

void MainWindow::on_pushButton_PubMsg_clicked(){
  if( pLocalPlannerThread != NULL)
    pLocalPlannerThread->PubMsg();
}

// ed: JW Path 버튼을 클릭하면 실행되는 함수
void MainWindow::on_pushButton_JWPath_clicked(){
  if( pLocalPlannerThread != NULL)
    pLocalPlannerThread->Pub_JWPathMsg();
}

// ed: forward, reverse 라디오버튼을 클릭하면 트리거되는 함수
//     drive_direction 운전방향에 대한 함수인듯
void MainWindow::drive_dir(){
  if( pLocalPlannerThread != NULL){
    if( ui.forward->isChecked() ){
      pLocalPlannerThread->m_dir_mode = 1;
      //printf("forward\n");
    }
    else if(ui.reverse->isChecked() ){
      pLocalPlannerThread->m_dir_mode = -1;
      //printf("reverse\n");
    }
    else{
      pLocalPlannerThread->m_dir_mode = 0;
      //printf("None\n");
    }
  }
}

int main(int argc, char** argv){
  QApplication app(argc, argv);
  MainWindow w(argc, argv);

  w.show();
  app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

  return app.exec();
}

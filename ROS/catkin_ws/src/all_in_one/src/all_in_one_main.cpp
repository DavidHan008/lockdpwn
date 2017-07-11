#include <QtGui>
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include "../inc/all_in_one_main.h"

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


//--------------------------------------------------------------------------------
MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent){
  ui.setupUi(this);

  // ed: GUI에 forward, reverse 라디오버튼에 대한 코드인듯
  //  connect( ui.forward, SIGNAL(clicked()), this, SLOT(drive_dir()) );
  //  connect( ui.reverse, SIGNAL(clicked()), this, SLOT(drive_dir()) );

}

MainWindow::~MainWindow() {

}


int main(int argc, char** argv){
  QApplication app(argc, argv);
  MainWindow w(argc, argv);

  w.show();
  app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

  return app.exec();
}

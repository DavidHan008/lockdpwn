#include <QtGui/QMainWindow>
#include <QThread>
#include <QMutex>
#include "../../../build/car_can/ui_car_can_gui.h"
#include "qnode.h"
#include <ros/ros.h>

#include "CAN_OBD2.h"

// can 수신 스레드
class CanReceiveThread : public QThread{
  Q_OBJECT;
	
 private :
  bool threadStop;
  CAN_OBD2* m_pCarCan;
  QMutex mutex;
 public :
  CanReceiveThread(CAN_OBD2* pCarCan, QObject *parent = 0);

  void stop();
  void run();
};

// 메인.
class MainWindow : public QMainWindow{
  Q_OBJECT

 public:
  MainWindow(int argc, char** argv, QWidget *parent = 0);
  ~MainWindow();

  CAN_OBD2 * m_pCarCan;
  QTimer *timer;

 public slots:
  void OnTimer();
  void on_startButton_clicked();


 private :
  int can_I;
  Ui::MainWindow ui;
  QNode* qnode;

  CanReceiveThread* canThread;

  int _argc;
  char** _argv;

};






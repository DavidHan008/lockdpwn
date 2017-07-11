#include <QtGui/QMainWindow>
#include <QThread>
#include <QProcess>
#include <ros/ros.h>
#include "../../../build/all_in_one/ui_all_in_one_gui.h" // ui_*.h

// 메인.
class ParkingPlannerThread;

class CmdCommandThread :public QThread {
  Q_OBJECT;

private :
  bool threadStop;
  QString cmd;
  long long int pid;

public :
  CmdCommandThread(QString cmd, QObject *parent = 0);

  void stop();
  void run();
};


class MainWindow : public QMainWindow{
  Q_OBJECT

public:
  MainWindow(int argc, char** argv, QWidget *parent = 0);
  ~MainWindow();
       
  public slots:


private :
      Ui::MainWindow ui;
      CmdCommandThread* trakerThread;
      CmdCommandThread* rndfThread;
      CmdCommandThread* rvizThread;
};

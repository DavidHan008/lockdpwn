#include <QtGui/QMainWindow>
#include <QThread>
#include <QProcess>
//#include <Eigen/Core>
#include <ros/ros.h>
#include "../../../build/motion_planner/ui_motion_planner_gui.h" // ui_*.h

// 메인.
class LocalPlannerThread;
class ParkingPlannerThread;
class CmdCommandThread : public QThread
{
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
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(int argc, char** argv, QWidget *parent = 0);
        ~MainWindow();
       
    public slots:

      void on_pushButton_traker1_on_clicked();
      void on_pushButton_traker1_off_clicked();
      void on_pushButton_rviz_on_clicked();
      void on_pushButton_rviz_off_clicked();
      void on_pushButton_PubMsg_clicked();
      void on_pushButton_JWPath_clicked();
	void drive_dir();


    private :
        Ui::MainWindow ui;
        LocalPlannerThread* pLocalPlannerThread;
	CmdCommandThread* trakerThread;
        CmdCommandThread* rndfThread;
        CmdCommandThread* rvizThread;

};

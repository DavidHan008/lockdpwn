#include <QtGui/QMainWindow>
#include <QThread>
#include <QProcess>

#include <ros/ros.h>
#include "../../../build/controller/ui_controller_gui.h" // ui_*.h
class PurePursuitThread;
class VelocityCtrlThread;
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(int argc, char** argv, QWidget *parent = 0);
        ~MainWindow();
        bool recordStop;

    public slots:
	void setLCDValue(int value);
	void setLCDValue_tar_vel(int value);
	void Set_tar_vel(int value);
	int getLCDValue(){ return m_lcdValue;}
	void on_pushButton_start_2_clicked();
	void on_pushButton_stop_2_clicked();
	void on_pushButton_start_clicked();
	void on_pushButton_stop_clicked();
	void on_pushButton_LF_clicked();
	void on_pushButton_RF_clicked();
	void on_pushButton_Z_clicked();

    private :
        Ui::MainWindow ui;
        PurePursuitThread* pPurePursuitThread;
	VelocityCtrlThread* pVelocityCtrlThread;
	int _argc;
	char** _argv;
	int m_lcdValue;
};

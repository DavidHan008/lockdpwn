#include <QtGui/QMainWindow>
#include <QThread>
#include "../../../build/mcu_can/ui_mcu_can_gui.h"
#include "qnode.h"
#include <ros/ros.h>

#include "CAN_MCU.h"

// can 수신 스레드.
class CanReceiveThread : public QThread
{
	Q_OBJECT;
	
	private :
		bool threadStop;
		CAN_MCU* m_pCanMCU;

	public :
		CanReceiveThread(CAN_MCU* _pCanMCU, QObject *parent = 0);

		void stop();
		void run();
};

// 메인.
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(int argc, char** argv, QWidget *parent = 0);
		~MainWindow();

		

		CAN_MCU * m_pCanMCU;
		QTimer *timer;


	public slots:
		
		void OnTimer();

		void on_startButton_clicked();

		void on_armBox_valueChanged();
		void on_accBox_valueChanged();
		void on_steerBox_valueChanged();
		void on_pushButton_Z_clicked();
		void on_pushButton_LF_clicked();
		void on_pushButton_RF_clicked();
		void OnDrivingMode();


	private :
		int can_I;
		int nMode;
		Ui::MainWindow ui;
		QNode* qnode;

		CanReceiveThread* canThread;

		int _argc;
		char** _argv;

		double mComputedSteerAng;
		double mCommandedSteerAng;
		int mComputedAccAng;
		int mCommandedAccAng;
		int mComputedBrkAng;
		int mCommandedBrkAng;
		

		void VelModeTransmit(int mode);
		void SteerModeTransmit(int mode);
		void GearModeTransmit(bool power, int mode);
};






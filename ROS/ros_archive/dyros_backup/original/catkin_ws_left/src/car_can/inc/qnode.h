#include <ros/ros.h>
#include <string>
#include <QtGui/QMainWindow>
#include <QThread>
#include <QStringListModel>

#include "../../../build/car_can/ui_car_can_gui.h"
#include "CAN_OBD2.h"
#include <car_can/CarCanData.h>



class QNode : public QThread {
	Q_OBJECT
public:
	QNode(int argc, char** argv, Ui::MainWindow* ui, CAN_OBD2* pCarCan, QObject *parent = 0);

	void run();
	void stop();


private:
	int init_argc;
	char** init_argv;

	ros::Publisher carData_publisher;

	bool threadStop;
	Ui::MainWindow* _ui;

	CAN_OBD2* m_pCarCan;	

};



#include <QtGui>
#include <QApplication>
#include <stdio.h>
#include "../inc/main.h"
 

CanReceiveThread::CanReceiveThread(CAN_OBD2* pCarCan, QObject * parent)
	: QThread(parent)
	, m_pCarCan(pCarCan)
{
	threadStop = false;
}

void CanReceiveThread::stop()
{
	threadStop = true;

}
void CanReceiveThread::run()
{
	qDebug("can Thread Start");
	while(!threadStop)
	{
		m_pCarCan->m_canport->ReadCanBuffer();

		if(m_pCarCan->GetCANdata())
			m_pCarCan->DoIMUFilter();
		m_pCarCan->GetObdSAS();
		m_pCarCan->GetObdVelocity1();
		m_pCarCan->GetObdVelocity2();
	}
	threadStop = false;
	qDebug("can Thread End");
}


/////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, _argc(argc), _argv(argv)
{
	ui.setupUi(this);
	m_pCarCan = NULL;
	canThread = NULL;

	qnode = NULL;
	
	timer = new QTimer(this);
	connect( timer, SIGNAL(timeout()), this, SLOT(OnTimer()) );

}



MainWindow::~MainWindow() {}


void MainWindow::OnTimer()
{
	char text[2048];

	// OBD SAS
	sprintf(text, "%s", m_pCarCan->m_canport->s_vehicle_obd[0].text);
	ui.lineEdit_2B0->setText(text);
	if(strcmp(m_pCarCan->m_canport->s_vehicle_obd[0].text, "no data") != 0)
	{
		sprintf(text, "%f", m_pCarCan->m_steeringAngle);
		ui.lineEdit_2B0_2->setText(text);
	}

	// OBD VEL1
	sprintf(text, "%s", m_pCarCan->m_canport->s_vehicle_obd[1].text);
	ui.lineEdit_316->setText(text);
	if(strcmp(m_pCarCan->m_canport->s_vehicle_obd[1].text, "no data") != 0)
	{
		sprintf(text, "%f", m_pCarCan->m_speed1);
		ui.lineEdit_316_2->setText(text);		
	}

	// OBD VEL2
	sprintf(text, "%s", m_pCarCan->m_canport->s_vehicle_obd[2].text);
	ui.lineEdit_4F0->setText(text);
	if(strcmp(m_pCarCan->m_canport->s_vehicle_obd[2].text, "no data") != 0)
	{
		sprintf(text, "%f", m_pCarCan->m_speed2);
		ui.lineEdit_4F0_2->setText(text);
	}

	// OBD IMU
	sprintf(text, "%s", m_pCarCan->m_canport->s_vehicle_obd[3].text);
	ui.lineEdit_220->setText(text);
	if(strcmp(m_pCarCan->m_canport->s_vehicle_obd[3].text, "no data") != 0)
	{
		sprintf (text, "% 8.3f, % 8.3f, % 8.3f", m_pCarCan->m_gyro[0], m_pCarCan->m_gyro[1], m_pCarCan->m_gyro[2]);
		ui.lineEdit_220_2->setText(text);

		sprintf (text, "% 8.3f, % 8.3f, % 8.3f", m_pCarCan->m_accl[0]*9.80665, m_pCarCan->m_accl[1]*9.80665, m_pCarCan->m_accl[2]*9.81);
		ui.lineEdit_220_3->setText(text);
	}
}


void MainWindow::on_startButton_clicked()
{
	
	if(!m_pCarCan)
	{
		ui.startButton->setText("Stop");

		m_pCarCan = new CAN_OBD2(ui.canPort2->value());

		canThread = new CanReceiveThread(m_pCarCan);
		canThread->start();

		qnode = new QNode(_argc, _argv, &ui, m_pCarCan);
		qnode->start();


		timer->start(500);

	}
	else
	{
		ui.startButton->setText("Start");

		timer->stop();

		canThread->stop();
		canThread->wait();

		
		qnode->stop();
		qnode->wait();		


		delete canThread;
		canThread = NULL;


		
		delete qnode;
		qnode = NULL;

		delete m_pCarCan;
		m_pCarCan = NULL;

		printf("thread clear\n");
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

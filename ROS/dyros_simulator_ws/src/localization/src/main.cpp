#include <QtGui>
#include <QApplication>

#include <stdio.h>
#include "../inc/main.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, _argc(argc), _argv(argv)
{
	ui.setupUi(this);

	_ins = NULL;
	qnode = NULL;
	
	timer = new QTimer(this);
	connect( timer, SIGNAL(timeout()), this, SLOT(OnTimer()) );

}


MainWindow::~MainWindow(){
	if(qnode!=NULL)	{
		qnode->stop();
		qnode->wait();
		delete qnode;
		qnode = NULL;
	}

	if(_ins!=NULL) {
		delete _ins;
		_ins = NULL;
	}
}

void MainWindow::OnTimer(){
	char text[1024];

	sprintf (text, "%6.3f(sen %6.3f) e: %6.3f", _ins->m_heading, _ins->m_gps.heading, _ins->m_heading-_ins->m_gps.heading);
	ui.lineEdit_6->setText(text);

	sprintf (text, "%2.8f m", _ins->m_p[0]);
	ui.lineEdit_7->setText(text);

	sprintf (text, "%2.8f m", _ins->m_p[1]);
	ui.lineEdit_8->setText(text);
}


void MainWindow::on_startButton_clicked(){
	if(!_ins)	{
		ui.startButton->setText("Stop");
		
		_ins = new Filter();

		qnode = new QNode(_argc, _argv, &ui, _ins);

		qnode ->start();

		timer->start(100);
	}
	else	{
		ui.startButton->setText("Start");

		qnode->stop();
		qnode->wait();
		timer->stop();
		//sleep(2);

		delete qnode;
		qnode = NULL;

		delete _ins;
		_ins = NULL;

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

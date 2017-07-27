#include <QtGui/QMainWindow>
#include <QThread>
#include <QProcess>
#include "../../../build/localization/ui_localization_gui.h"
#include "qnode.h"
#include <ros/ros.h>

#include "Filter.h"

// 메인.
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(int argc, char** argv, QWidget *parent = 0);
		~MainWindow();
		Filter *_ins;

		QTimer *timer;


	public slots:
		
		void OnTimer();
		void on_startButton_clicked();


	private :
		int can_I;
		Ui::MainWindow ui;
		QNode* qnode;

	

		int _argc;
		char** _argv;

};






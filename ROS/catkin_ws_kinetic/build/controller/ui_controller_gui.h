/********************************************************************************
** Form generated from reading UI file 'controller_gui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLLER_GUI_H
#define UI_CONTROLLER_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollBar>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton_start;
    QPushButton *pushButton_stop;
    QLabel *label_sas;
    QLabel *label_tarvel;
    QLabel *label_curvel;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_stop_2;
    QPushButton *pushButton_start_2;
    QLabel *label_5;
    QCheckBox *checkBox_Manual;
    QLCDNumber *lcdNumber;
    QCheckBox *checkBox_Vel;
    QSlider *horizontalSlider;
    QPushButton *pushButton_LF;
    QPushButton *pushButton_Z;
    QPushButton *pushButton_RF;
    QLabel *label_state;
    QLabel *label_4;
    QScrollBar *horizontalScrollBar;
    QLCDNumber *lcdNumber_tar_vel;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(572, 283);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 151, 17));
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(320, 20, 99, 27));
        pushButton_stop = new QPushButton(centralWidget);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(430, 20, 99, 27));
        label_sas = new QLabel(centralWidget);
        label_sas->setObjectName(QString::fromUtf8("label_sas"));
        label_sas->setGeometry(QRect(106, 40, 41, 17));
        label_tarvel = new QLabel(centralWidget);
        label_tarvel->setObjectName(QString::fromUtf8("label_tarvel"));
        label_tarvel->setGeometry(QRect(350, 70, 41, 17));
        label_curvel = new QLabel(centralWidget);
        label_curvel->setObjectName(QString::fromUtf8("label_curvel"));
        label_curvel->setGeometry(QRect(504, 70, 51, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 70, 81, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(410, 70, 91, 17));
        pushButton_stop_2 = new QPushButton(centralWidget);
        pushButton_stop_2->setObjectName(QString::fromUtf8("pushButton_stop_2"));
        pushButton_stop_2->setGeometry(QRect(130, 70, 99, 27));
        pushButton_start_2 = new QPushButton(centralWidget);
        pushButton_start_2->setObjectName(QString::fromUtf8("pushButton_start_2"));
        pushButton_start_2->setGeometry(QRect(20, 70, 99, 27));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 40, 91, 17));
        checkBox_Manual = new QCheckBox(centralWidget);
        checkBox_Manual->setObjectName(QString::fromUtf8("checkBox_Manual"));
        checkBox_Manual->setGeometry(QRect(10, 100, 91, 31));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(60, 110, 111, 51));
        checkBox_Vel = new QCheckBox(centralWidget);
        checkBox_Vel->setObjectName(QString::fromUtf8("checkBox_Vel"));
        checkBox_Vel->setGeometry(QRect(280, 20, 31, 31));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 230, 160, 29));
        horizontalSlider->setMinimum(-539);
        horizontalSlider->setMaximum(539);
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_LF = new QPushButton(centralWidget);
        pushButton_LF->setObjectName(QString::fromUtf8("pushButton_LF"));
        pushButton_LF->setGeometry(QRect(10, 180, 51, 41));
        pushButton_Z = new QPushButton(centralWidget);
        pushButton_Z->setObjectName(QString::fromUtf8("pushButton_Z"));
        pushButton_Z->setGeometry(QRect(80, 180, 51, 41));
        pushButton_RF = new QPushButton(centralWidget);
        pushButton_RF->setObjectName(QString::fromUtf8("pushButton_RF"));
        pushButton_RF->setGeometry(QRect(150, 180, 51, 41));
        label_state = new QLabel(centralWidget);
        label_state->setObjectName(QString::fromUtf8("label_state"));
        label_state->setGeometry(QRect(210, 40, 41, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 40, 41, 17));
        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(230, 180, 321, 21));
        horizontalScrollBar->setMaximum(20);
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        lcdNumber_tar_vel = new QLCDNumber(centralWidget);
        lcdNumber_tar_vel->setObjectName(QString::fromUtf8("lcdNumber_tar_vel"));
        lcdNumber_tar_vel->setGeometry(QRect(240, 110, 111, 51));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 572, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LogPlot", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Pure Pursuit Tracker", 0, QApplication::UnicodeUTF8));
        pushButton_start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButton_stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        label_sas->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        label_tarvel->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        label_curvel->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Target Vel:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Current Vel:", 0, QApplication::UnicodeUTF8));
        pushButton_stop_2->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        pushButton_start_2->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Target SAS:", 0, QApplication::UnicodeUTF8));
        checkBox_Manual->setText(QString());
        checkBox_Vel->setText(QString());
        pushButton_LF->setText(QApplication::translate("MainWindow", "LF", 0, QApplication::UnicodeUTF8));
        pushButton_Z->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pushButton_RF->setText(QApplication::translate("MainWindow", "RF", 0, QApplication::UnicodeUTF8));
        label_state->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "State", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLLER_GUI_H

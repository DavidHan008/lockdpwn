/********************************************************************************
** Form generated from reading UI file 'motion_planner_gui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTION_PLANNER_GUI_H
#define UI_MOTION_PLANNER_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton_traker1_on;
    QLabel *label_traker1;
    QPushButton *pushButton_traker1_off;
    QLabel *label_traker1_2;
    QPushButton *pushButton_PubMsg;
    QPushButton *pushButton_rviz_on;
    QLabel *label_traker1_3;
    QPushButton *pushButton_rviz_off;
    QPushButton *pushButton_JWPath;
    QRadioButton *forward;
    QRadioButton *reverse;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(496, 174);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(8, 114, 101, 17));
        pushButton_traker1_on = new QPushButton(centralWidget);
        pushButton_traker1_on->setObjectName(QString::fromUtf8("pushButton_traker1_on"));
        pushButton_traker1_on->setGeometry(QRect(54, 50, 61, 27));
        label_traker1 = new QLabel(centralWidget);
        label_traker1->setObjectName(QString::fromUtf8("label_traker1"));
        label_traker1->setGeometry(QRect(6, 50, 41, 17));
        pushButton_traker1_off = new QPushButton(centralWidget);
        pushButton_traker1_off->setObjectName(QString::fromUtf8("pushButton_traker1_off"));
        pushButton_traker1_off->setGeometry(QRect(126, 50, 61, 27));
        label_traker1_2 = new QLabel(centralWidget);
        label_traker1_2->setObjectName(QString::fromUtf8("label_traker1_2"));
        label_traker1_2->setGeometry(QRect(60, 20, 101, 17));
        pushButton_PubMsg = new QPushButton(centralWidget);
        pushButton_PubMsg->setObjectName(QString::fromUtf8("pushButton_PubMsg"));
        pushButton_PubMsg->setGeometry(QRect(110, 100, 151, 41));
        pushButton_rviz_on = new QPushButton(centralWidget);
        pushButton_rviz_on->setObjectName(QString::fromUtf8("pushButton_rviz_on"));
        pushButton_rviz_on->setGeometry(QRect(350, 110, 61, 27));
        label_traker1_3 = new QLabel(centralWidget);
        label_traker1_3->setObjectName(QString::fromUtf8("label_traker1_3"));
        label_traker1_3->setGeometry(QRect(310, 110, 31, 17));
        pushButton_rviz_off = new QPushButton(centralWidget);
        pushButton_rviz_off->setObjectName(QString::fromUtf8("pushButton_rviz_off"));
        pushButton_rviz_off->setGeometry(QRect(420, 110, 61, 27));
        pushButton_JWPath = new QPushButton(centralWidget);
        pushButton_JWPath->setObjectName(QString::fromUtf8("pushButton_JWPath"));
        pushButton_JWPath->setGeometry(QRect(310, 60, 161, 41));
        forward = new QRadioButton(centralWidget);
        forward->setObjectName(QString::fromUtf8("forward"));
        forward->setGeometry(QRect(220, 10, 81, 22));
        reverse = new QRadioButton(centralWidget);
        reverse->setObjectName(QString::fromUtf8("reverse"));
        reverse->setGeometry(QRect(350, 10, 81, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 496, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LogPlot", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Local Planner", 0, QApplication::UnicodeUTF8));
        pushButton_traker1_on->setText(QApplication::translate("MainWindow", "ON", 0, QApplication::UnicodeUTF8));
        label_traker1->setText(QApplication::translate("MainWindow", "OFF", 0, QApplication::UnicodeUTF8));
        pushButton_traker1_off->setText(QApplication::translate("MainWindow", "OFF", 0, QApplication::UnicodeUTF8));
        label_traker1_2->setText(QApplication::translate("MainWindow", "Tracker Status", 0, QApplication::UnicodeUTF8));
        pushButton_PubMsg->setText(QApplication::translate("MainWindow", "Publish Smooth Path", 0, QApplication::UnicodeUTF8));
        pushButton_rviz_on->setText(QApplication::translate("MainWindow", "ON", 0, QApplication::UnicodeUTF8));
        label_traker1_3->setText(QApplication::translate("MainWindow", "RVIZ", 0, QApplication::UnicodeUTF8));
        pushButton_rviz_off->setText(QApplication::translate("MainWindow", "OFF", 0, QApplication::UnicodeUTF8));
        pushButton_JWPath->setText(QApplication::translate("MainWindow", "Jw Path.", 0, QApplication::UnicodeUTF8));
        forward->setText(QApplication::translate("MainWindow", "forward", 0, QApplication::UnicodeUTF8));
        reverse->setText(QApplication::translate("MainWindow", "reverse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTION_PLANNER_GUI_H

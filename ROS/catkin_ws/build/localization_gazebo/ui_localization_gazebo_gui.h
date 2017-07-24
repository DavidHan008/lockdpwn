/********************************************************************************
** Form generated from reading UI file 'localization_gazebo_gui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCALIZATION_GAZEBO_GUI_H
#define UI_LOCALIZATION_GAZEBO_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *startButton;
    QLineEdit *lineEdit_6;
    QLabel *label_10;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_9;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_5;
    QLabel *label_11;
    QLineEdit *lineEdit_7;
    QLabel *label_12;
    QLineEdit *lineEdit_8;
    QLabel *label_13;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(669, 525);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(540, 30, 99, 27));
        lineEdit_6 = new QLineEdit(centralWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(275, 350, 241, 27));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(207, 350, 71, 17));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(275, 176, 361, 27));
        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(275, 206, 361, 27));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(25, 120, 251, 17));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(275, 146, 361, 27));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(65, 210, 211, 17));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(275, 116, 361, 27));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(59, 150, 221, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(155, 180, 121, 17));
        lineEdit_5 = new QLineEdit(centralWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(275, 260, 241, 27));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(100, 260, 171, 17));
        lineEdit_7 = new QLineEdit(centralWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(275, 390, 241, 27));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(255, 390, 21, 17));
        lineEdit_8 = new QLineEdit(centralWidget);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(275, 430, 241, 27));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(255, 430, 21, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 20, 191, 41));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(270, 80, 131, 17));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_5->setFont(font1);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(280, 320, 191, 17));
        label_6->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 669, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "localization", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "heading :", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Latitude, Longitutde, Altitude, UTC :", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "TM Coordinates (X-SN, Y-EW) : ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "GPS Quality, #Satellite, HDOP :", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Heading, Speed : ", 0, QApplication::UnicodeUTF8));
        lineEdit_5->setText(QString());
        label_11->setText(QApplication::translate("MainWindow", "gryo[0], gyro[1], gyro[2] :", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "x :", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "y :", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Localization", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Receive Data", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Localization Result", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCALIZATION_GAZEBO_GUI_H

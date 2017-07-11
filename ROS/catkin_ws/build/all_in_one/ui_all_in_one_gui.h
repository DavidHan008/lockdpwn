/********************************************************************************
** Form generated from reading UI file 'all_in_one_gui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALL_IN_ONE_GUI_H
#define UI_ALL_IN_ONE_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollBar>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionA3;
    QWidget *centralWidget;
    QLabel *label_main_name;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_19;
    QLineEdit *lineEdit_4F0_2;
    QLineEdit *lineEdit_316_2;
    QLineEdit *lineEdit_2B0_2;
    QLabel *label_21;
    QLabel *label_20;
    QLabel *label_24;
    QLineEdit *lineEdit_220_3;
    QLabel *label_23;
    QLineEdit *lineEdit_220_2;
    QPushButton *startButton;
    QLabel *label_9;
    QLineEdit *lineEdit_7;
    QLabel *label_2;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_2;
    QLabel *label_10;
    QLabel *label_6;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_12;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_11;
    QLineEdit *lineEdit_5;
    QFrame *line;
    QRadioButton *reverse;
    QRadioButton *forward;
    QLabel *label_13;
    QLabel *label_8;
    QFrame *line_2;
    QCheckBox *checkBox_Vel;
    QPushButton *pushButton_stop_2;
    QLabel *label_sas;
    QScrollBar *horizontalScrollBar;
    QLabel *label_14;
    QLabel *label_curvel;
    QPushButton *pushButton_stop;
    QLabel *label_state;
    QLabel *label_15;
    QLabel *label_16;
    QLCDNumber *lcdNumber;
    QSlider *horizontalSlider;
    QPushButton *pushButton_LF;
    QPushButton *pushButton_Z;
    QCheckBox *checkBox_Manual;
    QLabel *label_tarvel;
    QLabel *label_17;
    QLabel *label_18;
    QPushButton *pushButton_start_2;
    QLCDNumber *lcdNumber_tar_vel;
    QPushButton *pushButton_start;
    QPushButton *pushButton_RF;
    QFrame *line_3;
    QFrame *line_4;
    QRadioButton *DrivingMode5;
    QGroupBox *groupBox;
    QRadioButton *DrivingMode1;
    QRadioButton *DrivingMode6;
    QRadioButton *DrivingMode3;
    QRadioButton *DrivingMode2;
    QRadioButton *DrivingMode4;
    QPushButton *startButton_2;
    QPushButton *startButton_3;
    QPushButton *startButton_4;
    QFrame *frame;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(904, 679);
        actionA3 = new QAction(MainWindow);
        actionA3->setObjectName(QString::fromUtf8("actionA3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_main_name = new QLabel(centralWidget);
        label_main_name->setObjectName(QString::fromUtf8("label_main_name"));
        label_main_name->setGeometry(QRect(20, 10, 351, 31));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_main_name->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 56, 171, 31));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(190, 60, 48, 27));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(50, 110, 67, 17));
        lineEdit_4F0_2 = new QLineEdit(centralWidget);
        lineEdit_4F0_2->setObjectName(QString::fromUtf8("lineEdit_4F0_2"));
        lineEdit_4F0_2->setEnabled(true);
        lineEdit_4F0_2->setGeometry(QRect(10, 250, 141, 27));
        lineEdit_4F0_2->setAlignment(Qt::AlignCenter);
        lineEdit_4F0_2->setReadOnly(true);
        lineEdit_316_2 = new QLineEdit(centralWidget);
        lineEdit_316_2->setObjectName(QString::fromUtf8("lineEdit_316_2"));
        lineEdit_316_2->setEnabled(true);
        lineEdit_316_2->setGeometry(QRect(10, 190, 141, 27));
        lineEdit_316_2->setAlignment(Qt::AlignCenter);
        lineEdit_316_2->setReadOnly(true);
        lineEdit_2B0_2 = new QLineEdit(centralWidget);
        lineEdit_2B0_2->setObjectName(QString::fromUtf8("lineEdit_2B0_2"));
        lineEdit_2B0_2->setEnabled(true);
        lineEdit_2B0_2->setGeometry(QRect(10, 130, 141, 27));
        lineEdit_2B0_2->setAlignment(Qt::AlignCenter);
        lineEdit_2B0_2->setReadOnly(true);
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(50, 230, 67, 17));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(50, 170, 67, 17));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(170, 170, 171, 17));
        lineEdit_220_3 = new QLineEdit(centralWidget);
        lineEdit_220_3->setObjectName(QString::fromUtf8("lineEdit_220_3"));
        lineEdit_220_3->setEnabled(true);
        lineEdit_220_3->setGeometry(QRect(170, 190, 161, 27));
        lineEdit_220_3->setMaxLength(100);
        lineEdit_220_3->setAlignment(Qt::AlignCenter);
        lineEdit_220_3->setReadOnly(true);
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(164, 110, 171, 17));
        lineEdit_220_2 = new QLineEdit(centralWidget);
        lineEdit_220_2->setObjectName(QString::fromUtf8("lineEdit_220_2"));
        lineEdit_220_2->setEnabled(true);
        lineEdit_220_2->setGeometry(QRect(170, 130, 161, 27));
        lineEdit_220_2->setMaxLength(100);
        lineEdit_220_2->setAlignment(Qt::AlignCenter);
        lineEdit_220_2->setReadOnly(true);
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(480, 570, 141, 27));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(390, 314, 211, 17));
        lineEdit_7 = new QLineEdit(centralWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(680, 140, 171, 27));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(390, 60, 251, 17));
        lineEdit_6 = new QLineEdit(centralWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(680, 80, 171, 27));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(390, 146, 231, 27));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(680, 60, 71, 17));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(680, 20, 191, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label_6->setFont(font2);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(390, 254, 121, 17));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(390, 280, 231, 27));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(680, 120, 41, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(390, 120, 221, 17));
        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(390, 340, 231, 27));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(390, 20, 261, 31));
        label_5->setFont(font2);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(390, 86, 231, 27));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(390, 186, 171, 17));
        lineEdit_5 = new QLineEdit(centralWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(390, 216, 231, 27));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(343, 50, 20, 341));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        reverse = new QRadioButton(centralWidget);
        reverse->setObjectName(QString::fromUtf8("reverse"));
        reverse->setGeometry(QRect(250, 360, 81, 22));
        forward = new QRadioButton(centralWidget);
        forward->setObjectName(QString::fromUtf8("forward"));
        forward->setGeometry(QRect(170, 360, 81, 22));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(30, 360, 131, 21));
        label_13->setFont(font1);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 330, 281, 21));
        label_8->setFont(font2);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(10, 300, 341, 21));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        checkBox_Vel = new QCheckBox(centralWidget);
        checkBox_Vel->setObjectName(QString::fromUtf8("checkBox_Vel"));
        checkBox_Vel->setGeometry(QRect(300, 480, 31, 31));
        pushButton_stop_2 = new QPushButton(centralWidget);
        pushButton_stop_2->setObjectName(QString::fromUtf8("pushButton_stop_2"));
        pushButton_stop_2->setGeometry(QRect(160, 460, 99, 27));
        label_sas = new QLabel(centralWidget);
        label_sas->setObjectName(QString::fromUtf8("label_sas"));
        label_sas->setGeometry(QRect(136, 430, 41, 17));
        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(170, 580, 111, 21));
        horizontalScrollBar->setMaximum(20);
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(190, 430, 41, 17));
        label_curvel = new QLabel(centralWidget);
        label_curvel->setObjectName(QString::fromUtf8("label_curvel"));
        label_curvel->setGeometry(QRect(400, 610, 51, 17));
        pushButton_stop = new QPushButton(centralWidget);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(300, 540, 99, 27));
        label_state = new QLabel(centralWidget);
        label_state->setObjectName(QString::fromUtf8("label_state"));
        label_state->setGeometry(QRect(240, 430, 41, 17));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(40, 430, 91, 17));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(310, 580, 81, 17));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(40, 510, 111, 51));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(50, 610, 101, 29));
        horizontalSlider->setMinimum(-539);
        horizontalSlider->setMaximum(539);
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_LF = new QPushButton(centralWidget);
        pushButton_LF->setObjectName(QString::fromUtf8("pushButton_LF"));
        pushButton_LF->setGeometry(QRect(40, 570, 31, 31));
        pushButton_Z = new QPushButton(centralWidget);
        pushButton_Z->setObjectName(QString::fromUtf8("pushButton_Z"));
        pushButton_Z->setGeometry(QRect(80, 570, 31, 31));
        checkBox_Manual = new QCheckBox(centralWidget);
        checkBox_Manual->setObjectName(QString::fromUtf8("checkBox_Manual"));
        checkBox_Manual->setGeometry(QRect(10, 510, 31, 31));
        label_tarvel = new QLabel(centralWidget);
        label_tarvel->setObjectName(QString::fromUtf8("label_tarvel"));
        label_tarvel->setGeometry(QRect(400, 580, 41, 17));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(310, 610, 91, 17));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(40, 400, 151, 17));
        pushButton_start_2 = new QPushButton(centralWidget);
        pushButton_start_2->setObjectName(QString::fromUtf8("pushButton_start_2"));
        pushButton_start_2->setGeometry(QRect(40, 460, 99, 27));
        lcdNumber_tar_vel = new QLCDNumber(centralWidget);
        lcdNumber_tar_vel->setObjectName(QString::fromUtf8("lcdNumber_tar_vel"));
        lcdNumber_tar_vel->setGeometry(QRect(170, 510, 111, 51));
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(300, 510, 99, 27));
        pushButton_RF = new QPushButton(centralWidget);
        pushButton_RF->setObjectName(QString::fromUtf8("pushButton_RF"));
        pushButton_RF->setGeometry(QRect(120, 570, 31, 31));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(350, 383, 551, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(430, 390, 20, 251));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        DrivingMode5 = new QRadioButton(centralWidget);
        DrivingMode5->setObjectName(QString::fromUtf8("DrivingMode5"));
        DrivingMode5->setGeometry(QRect(680, 480, 171, 22));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(480, 410, 101, 21));
        groupBox->setFont(font2);
        DrivingMode1 = new QRadioButton(centralWidget);
        DrivingMode1->setObjectName(QString::fromUtf8("DrivingMode1"));
        DrivingMode1->setEnabled(true);
        DrivingMode1->setGeometry(QRect(480, 440, 191, 22));
        DrivingMode1->setCheckable(true);
        DrivingMode1->setChecked(false);
        DrivingMode1->setAutoRepeat(false);
        DrivingMode6 = new QRadioButton(centralWidget);
        DrivingMode6->setObjectName(QString::fromUtf8("DrivingMode6"));
        DrivingMode6->setGeometry(QRect(680, 520, 151, 22));
        DrivingMode6->setAutoFillBackground(false);
        DrivingMode6->setAutoExclusive(true);
        DrivingMode3 = new QRadioButton(centralWidget);
        DrivingMode3->setObjectName(QString::fromUtf8("DrivingMode3"));
        DrivingMode3->setGeometry(QRect(480, 520, 191, 22));
        DrivingMode2 = new QRadioButton(centralWidget);
        DrivingMode2->setObjectName(QString::fromUtf8("DrivingMode2"));
        DrivingMode2->setGeometry(QRect(480, 480, 191, 22));
        DrivingMode4 = new QRadioButton(centralWidget);
        DrivingMode4->setObjectName(QString::fromUtf8("DrivingMode4"));
        DrivingMode4->setGeometry(QRect(680, 440, 161, 22));
        startButton_2 = new QPushButton(centralWidget);
        startButton_2->setObjectName(QString::fromUtf8("startButton_2"));
        startButton_2->setGeometry(QRect(480, 610, 141, 27));
        startButton_3 = new QPushButton(centralWidget);
        startButton_3->setObjectName(QString::fromUtf8("startButton_3"));
        startButton_3->setGeometry(QRect(630, 570, 141, 27));
        startButton_4 = new QPushButton(centralWidget);
        startButton_4->setObjectName(QString::fromUtf8("startButton_4"));
        startButton_4->setGeometry(QRect(630, 610, 141, 27));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 361, 31));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 904, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LogPlot", 0, QApplication::UnicodeUTF8));
        actionA3->setText(QApplication::translate("MainWindow", "a3", 0, QApplication::UnicodeUTF8));
        label_main_name->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#00007f;\">Integrated Vehicle Control Manager</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Can Port Select (0 or 1)", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "Steering", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "Velocity", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "Velocity", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("MainWindow", "accl[0], accl[1], accl[2]", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("MainWindow", "gyro[0], gyro[1], gyro[2]", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "CAN Start", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "TM Coordinates (X-SN, Y-EW) : ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Latitude, Longitutde, Altitude, UTC :", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "heading :", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#940000;\">Localization Result</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Heading, Speed : ", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "x & y :", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "GPS Quality, #Satellite, HDOP :", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#00aa00;\">Localization Receive Data</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "gryo[0], gyro[1], gyro[2] :", 0, QApplication::UnicodeUTF8));
        lineEdit_5->setText(QString());
        reverse->setText(QApplication::translate("MainWindow", "reverse", 0, QApplication::UnicodeUTF8));
        forward->setText(QApplication::translate("MainWindow", "forward", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Vehicle Direction", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#bd3f00;\">Motion Planner &amp; Controller</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        checkBox_Vel->setText(QString());
        pushButton_stop_2->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        label_sas->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "State", 0, QApplication::UnicodeUTF8));
        label_curvel->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        pushButton_stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        label_state->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Target SAS:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "Target Vel:", 0, QApplication::UnicodeUTF8));
        pushButton_LF->setText(QApplication::translate("MainWindow", "LF", 0, QApplication::UnicodeUTF8));
        pushButton_Z->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        checkBox_Manual->setText(QString());
        label_tarvel->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "Current Vel:", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "Pure Pursuit Tracker", 0, QApplication::UnicodeUTF8));
        pushButton_start_2->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButton_start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButton_RF->setText(QApplication::translate("MainWindow", "RF", 0, QApplication::UnicodeUTF8));
        DrivingMode5->setText(QApplication::translate("MainWindow", "5.Steering Input Test", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Mode Select", 0, QApplication::UnicodeUTF8));
        DrivingMode1->setText(QApplication::translate("MainWindow", "1.Fully Autonomous", 0, QApplication::UnicodeUTF8));
        DrivingMode6->setText(QApplication::translate("MainWindow", "6.Driver Mode", 0, QApplication::UnicodeUTF8));
        DrivingMode3->setText(QApplication::translate("MainWindow", "3.Velocity Autonomous", 0, QApplication::UnicodeUTF8));
        DrivingMode2->setText(QApplication::translate("MainWindow", "2.Steering Autonomous", 0, QApplication::UnicodeUTF8));
        DrivingMode4->setText(QApplication::translate("MainWindow", "4.Velocity Input Test", 0, QApplication::UnicodeUTF8));
        startButton_2->setText(QApplication::translate("MainWindow", "RViz ON", 0, QApplication::UnicodeUTF8));
        startButton_3->setText(QApplication::translate("MainWindow", "Read Path Data", 0, QApplication::UnicodeUTF8));
        startButton_4->setText(QApplication::translate("MainWindow", "Play Bag File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALL_IN_ONE_GUI_H

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
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionA3;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *startButton_4;
    QRadioButton *forward;
    QPushButton *startButton_2;
    QRadioButton *reverse;
    QPushButton *startButton_3;
    QLabel *label_curvel;
    QLabel *label_main_name;
    QPushButton *startButton;
    QLabel *label_13;
    QSpinBox *spinBox;
    QFrame *frame;
    QLabel *label;
    QWidget *tab_2;
    QRadioButton *DrivingMode2;
    QGroupBox *groupBox;
    QRadioButton *DrivingMode5;
    QRadioButton *DrivingMode4;
    QRadioButton *DrivingMode1;
    QRadioButton *DrivingMode6;
    QRadioButton *DrivingMode3;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QLabel *label_7;
    QLabel *label_14;
    QGroupBox *groupBox_2;
    QWidget *tab_3;
    QLabel *label_9;
    QLineEdit *lineEdit_3;
    QLabel *label_2;
    QLabel *label_4;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_5;
    QLabel *label_12;
    QLineEdit *lineEdit_2;
    QLabel *label_10;
    QLabel *label_3;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QLabel *label_11;
    QLineEdit *lineEdit_2B0_2;
    QLabel *label_20;
    QLineEdit *lineEdit_316_2;
    QLabel *label_24;
    QLineEdit *lineEdit_220_2;
    QLabel *label_23;
    QLabel *label_19;
    QLineEdit *lineEdit_220_3;
    QLabel *label_8;
    QMenuBar *menuBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(904, 679);
        actionA3 = new QAction(MainWindow);
        actionA3->setObjectName(QString::fromUtf8("actionA3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 911, 611));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        startButton_4 = new QPushButton(tab);
        startButton_4->setObjectName(QString::fromUtf8("startButton_4"));
        startButton_4->setGeometry(QRect(750, 580, 141, 27));
        forward = new QRadioButton(tab);
        forward->setObjectName(QString::fromUtf8("forward"));
        forward->setGeometry(QRect(160, 60, 81, 22));
        startButton_2 = new QPushButton(tab);
        startButton_2->setObjectName(QString::fromUtf8("startButton_2"));
        startButton_2->setGeometry(QRect(600, 580, 141, 27));
        reverse = new QRadioButton(tab);
        reverse->setObjectName(QString::fromUtf8("reverse"));
        reverse->setGeometry(QRect(240, 60, 81, 22));
        startButton_3 = new QPushButton(tab);
        startButton_3->setObjectName(QString::fromUtf8("startButton_3"));
        startButton_3->setGeometry(QRect(170, 90, 141, 27));
        label_curvel = new QLabel(tab);
        label_curvel->setObjectName(QString::fromUtf8("label_curvel"));
        label_curvel->setGeometry(QRect(400, 614, 51, 17));
        label_main_name = new QLabel(tab);
        label_main_name->setObjectName(QString::fromUtf8("label_main_name"));
        label_main_name->setGeometry(QRect(20, 14, 351, 31));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_main_name->setFont(font);
        startButton = new QPushButton(tab);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(20, 90, 141, 27));
        label_13 = new QLabel(tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 60, 131, 21));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_13->setFont(font1);
        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(560, 14, 48, 27));
        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 14, 361, 31));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(390, 10, 171, 31));
        label->setFont(font1);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        DrivingMode2 = new QRadioButton(tab_2);
        DrivingMode2->setObjectName(QString::fromUtf8("DrivingMode2"));
        DrivingMode2->setGeometry(QRect(260, 150, 191, 22));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(380, 70, 101, 21));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        groupBox->setFont(font2);
        DrivingMode5 = new QRadioButton(tab_2);
        DrivingMode5->setObjectName(QString::fromUtf8("DrivingMode5"));
        DrivingMode5->setGeometry(QRect(460, 150, 171, 22));
        DrivingMode4 = new QRadioButton(tab_2);
        DrivingMode4->setObjectName(QString::fromUtf8("DrivingMode4"));
        DrivingMode4->setGeometry(QRect(460, 110, 161, 22));
        DrivingMode1 = new QRadioButton(tab_2);
        DrivingMode1->setObjectName(QString::fromUtf8("DrivingMode1"));
        DrivingMode1->setEnabled(true);
        DrivingMode1->setGeometry(QRect(260, 110, 191, 22));
        DrivingMode1->setCheckable(true);
        DrivingMode1->setChecked(false);
        DrivingMode1->setAutoRepeat(false);
        DrivingMode6 = new QRadioButton(tab_2);
        DrivingMode6->setObjectName(QString::fromUtf8("DrivingMode6"));
        DrivingMode6->setGeometry(QRect(460, 190, 151, 22));
        DrivingMode6->setAutoFillBackground(false);
        DrivingMode6->setAutoExclusive(true);
        DrivingMode3 = new QRadioButton(tab_2);
        DrivingMode3->setObjectName(QString::fromUtf8("DrivingMode3"));
        DrivingMode3->setGeometry(QRect(260, 190, 191, 22));
        comboBox = new QComboBox(tab_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(340, 340, 231, 27));
        comboBox_2 = new QComboBox(tab_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(340, 380, 231, 27));
        comboBox_3 = new QComboBox(tab_2);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(340, 420, 231, 27));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(250, 390, 81, 17));
        label_14 = new QLabel(tab_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(220, 340, 111, 17));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(380, 300, 141, 21));
        groupBox_2->setFont(font2);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(380, 384, 211, 17));
        lineEdit_3 = new QLineEdit(tab_3);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(380, 350, 231, 27));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 130, 251, 17));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(380, 190, 221, 17));
        lineEdit_7 = new QLineEdit(tab_3);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(670, 210, 171, 27));
        lineEdit_6 = new QLineEdit(tab_3);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(670, 150, 171, 27));
        lineEdit_5 = new QLineEdit(tab_3);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(380, 286, 231, 27));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(670, 190, 41, 20));
        lineEdit_2 = new QLineEdit(tab_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(380, 216, 231, 27));
        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(670, 130, 71, 17));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(380, 324, 121, 17));
        lineEdit_4 = new QLineEdit(tab_3);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(380, 410, 231, 27));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(380, 90, 261, 31));
        label_5->setFont(font2);
        lineEdit = new QLineEdit(tab_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(380, 156, 231, 27));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(670, 90, 191, 31));
        label_6->setFont(font2);
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(380, 256, 171, 17));
        lineEdit_2B0_2 = new QLineEdit(tab_3);
        lineEdit_2B0_2->setObjectName(QString::fromUtf8("lineEdit_2B0_2"));
        lineEdit_2B0_2->setEnabled(true);
        lineEdit_2B0_2->setGeometry(QRect(46, 160, 281, 27));
        lineEdit_2B0_2->setAlignment(Qt::AlignCenter);
        lineEdit_2B0_2->setReadOnly(true);
        label_20 = new QLabel(tab_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(150, 200, 67, 17));
        lineEdit_316_2 = new QLineEdit(tab_3);
        lineEdit_316_2->setObjectName(QString::fromUtf8("lineEdit_316_2"));
        lineEdit_316_2->setEnabled(true);
        lineEdit_316_2->setGeometry(QRect(46, 220, 281, 27));
        lineEdit_316_2->setAlignment(Qt::AlignCenter);
        lineEdit_316_2->setReadOnly(true);
        label_24 = new QLabel(tab_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(110, 330, 171, 17));
        lineEdit_220_2 = new QLineEdit(tab_3);
        lineEdit_220_2->setObjectName(QString::fromUtf8("lineEdit_220_2"));
        lineEdit_220_2->setEnabled(true);
        lineEdit_220_2->setGeometry(QRect(50, 280, 271, 27));
        lineEdit_220_2->setMaxLength(100);
        lineEdit_220_2->setAlignment(Qt::AlignCenter);
        lineEdit_220_2->setReadOnly(true);
        label_23 = new QLabel(tab_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(100, 260, 171, 17));
        label_19 = new QLabel(tab_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(150, 140, 67, 17));
        lineEdit_220_3 = new QLineEdit(tab_3);
        lineEdit_220_3->setObjectName(QString::fromUtf8("lineEdit_220_3"));
        lineEdit_220_3->setEnabled(true);
        lineEdit_220_3->setGeometry(QRect(50, 350, 271, 27));
        lineEdit_220_3->setMaxLength(100);
        lineEdit_220_3->setAlignment(Qt::AlignCenter);
        lineEdit_220_3->setReadOnly(true);
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 100, 181, 21));
        label_8->setFont(font2);
        tabWidget->addTab(tab_3, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 904, 25));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LogPlot", 0, QApplication::UnicodeUTF8));
        actionA3->setText(QApplication::translate("MainWindow", "a3", 0, QApplication::UnicodeUTF8));
        startButton_4->setText(QApplication::translate("MainWindow", "Play Bag File", 0, QApplication::UnicodeUTF8));
        forward->setText(QApplication::translate("MainWindow", "forward", 0, QApplication::UnicodeUTF8));
        startButton_2->setText(QApplication::translate("MainWindow", "RViz ON", 0, QApplication::UnicodeUTF8));
        reverse->setText(QApplication::translate("MainWindow", "reverse", 0, QApplication::UnicodeUTF8));
        startButton_3->setText(QApplication::translate("MainWindow", "Read Path Data", 0, QApplication::UnicodeUTF8));
        label_curvel->setText(QApplication::translate("MainWindow", "---", 0, QApplication::UnicodeUTF8));
        label_main_name->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#00007f;\">Integrated Vehicle Control Manager</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "CAN Start", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Vehicle Direction", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Can Port Select (0 or 1)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Main Window", 0, QApplication::UnicodeUTF8));
        DrivingMode2->setText(QApplication::translate("MainWindow", "2.Steering Autonomous", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Mode Select", 0, QApplication::UnicodeUTF8));
        DrivingMode5->setText(QApplication::translate("MainWindow", "5.Steering Input Test", 0, QApplication::UnicodeUTF8));
        DrivingMode4->setText(QApplication::translate("MainWindow", "4.Velocity Input Test", 0, QApplication::UnicodeUTF8));
        DrivingMode1->setText(QApplication::translate("MainWindow", "1.Fully Autonomous", 0, QApplication::UnicodeUTF8));
        DrivingMode6->setText(QApplication::translate("MainWindow", "6.Driver Mode", 0, QApplication::UnicodeUTF8));
        DrivingMode3->setText(QApplication::translate("MainWindow", "3.Velocity Autonomous", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Controller", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Motion Planner", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Choose One Type", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Mode Select", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "TM Coordinates (X-SN, Y-EW) : ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Latitude, Longitutde, Altitude, UTC :", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "GPS Quality, #Satellite, HDOP :", 0, QApplication::UnicodeUTF8));
        lineEdit_5->setText(QString());
        label_12->setText(QApplication::translate("MainWindow", "x & y :", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "heading :", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Heading, Speed : ", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#00aa00;\">Localization Receive Data</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#940000;\">Localization Result</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "gryo[0], gyro[1], gyro[2] :", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "Velocity", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("MainWindow", "accl[0], accl[1], accl[2]", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("MainWindow", "gyro[0], gyro[1], gyro[2]", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "Steering", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#bd3f00;\">MCU Data Monitoring</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Monitoring", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALL_IN_ONE_GUI_H

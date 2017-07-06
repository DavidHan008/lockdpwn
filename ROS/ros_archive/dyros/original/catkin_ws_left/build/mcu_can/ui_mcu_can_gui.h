/********************************************************************************
** Form generated from reading UI file 'mcu_can_gui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MCU_CAN_GUI_H
#define UI_MCU_CAN_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *startButton;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_201;
    QLineEdit *lineEdit_205;
    QLineEdit *lineEdit_205_2;
    QLineEdit *lineEdit_205_3;
    QLineEdit *lineEdit_205_4;
    QLineEdit *lineEdit_205_5;
    QLineEdit *lineEdit_201_2;
    QLineEdit *lineEdit_201_3;
    QLineEdit *lineEdit_202;
    QLineEdit *lineEdit_301_2;
    QLineEdit *lineEdit_301_3;
    QLineEdit *lineEdit_301_4;
    QLineEdit *lineEdit_301_5;
    QLineEdit *lineEdit_301;
    QLabel *label_11;
    QSpinBox *canPort1;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_26;
    QLabel *label_3;
    QRadioButton *DrivingMode1;
    QRadioButton *DrivingMode5;
    QRadioButton *DrivingMode3;
    QRadioButton *DrivingMode4;
    QRadioButton *DrivingMode2;
    QRadioButton *DrivingMode6;
    QGroupBox *groupBox;
    QSpinBox *armBox;
    QSpinBox *accBox;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QDoubleSpinBox *steerBox;
    QPushButton *pushButton_LF;
    QPushButton *pushButton_Z;
    QPushButton *pushButton_RF;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(654, 616);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 121, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(19, 40, 16, 17));
        label_2->setAlignment(Qt::AlignCenter);
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(480, 30, 99, 27));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 89, 221, 17));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 149, 221, 17));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 209, 241, 17));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 269, 181, 17));
        lineEdit_201 = new QLineEdit(centralWidget);
        lineEdit_201->setObjectName(QString::fromUtf8("lineEdit_201"));
        lineEdit_201->setEnabled(false);
        lineEdit_201->setGeometry(QRect(20, 169, 311, 27));
        lineEdit_205 = new QLineEdit(centralWidget);
        lineEdit_205->setObjectName(QString::fromUtf8("lineEdit_205"));
        lineEdit_205->setEnabled(false);
        lineEdit_205->setGeometry(QRect(20, 110, 311, 27));
        lineEdit_205->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_205->setReadOnly(true);
        lineEdit_205_2 = new QLineEdit(centralWidget);
        lineEdit_205_2->setObjectName(QString::fromUtf8("lineEdit_205_2"));
        lineEdit_205_2->setEnabled(true);
        lineEdit_205_2->setGeometry(QRect(350, 109, 31, 27));
        lineEdit_205_2->setAlignment(Qt::AlignCenter);
        lineEdit_205_2->setReadOnly(true);
        lineEdit_205_3 = new QLineEdit(centralWidget);
        lineEdit_205_3->setObjectName(QString::fromUtf8("lineEdit_205_3"));
        lineEdit_205_3->setEnabled(true);
        lineEdit_205_3->setGeometry(QRect(470, 110, 31, 27));
        lineEdit_205_3->setAlignment(Qt::AlignCenter);
        lineEdit_205_3->setReadOnly(true);
        lineEdit_205_4 = new QLineEdit(centralWidget);
        lineEdit_205_4->setObjectName(QString::fromUtf8("lineEdit_205_4"));
        lineEdit_205_4->setEnabled(true);
        lineEdit_205_4->setGeometry(QRect(390, 109, 71, 27));
        lineEdit_205_4->setMaxLength(7);
        lineEdit_205_4->setAlignment(Qt::AlignCenter);
        lineEdit_205_4->setReadOnly(true);
        lineEdit_205_5 = new QLineEdit(centralWidget);
        lineEdit_205_5->setObjectName(QString::fromUtf8("lineEdit_205_5"));
        lineEdit_205_5->setEnabled(true);
        lineEdit_205_5->setGeometry(QRect(510, 109, 71, 27));
        lineEdit_205_5->setMaxLength(7);
        lineEdit_205_5->setAlignment(Qt::AlignCenter);
        lineEdit_205_5->setReadOnly(true);
        lineEdit_201_2 = new QLineEdit(centralWidget);
        lineEdit_201_2->setObjectName(QString::fromUtf8("lineEdit_201_2"));
        lineEdit_201_2->setEnabled(true);
        lineEdit_201_2->setGeometry(QRect(350, 169, 31, 27));
        lineEdit_201_2->setAlignment(Qt::AlignCenter);
        lineEdit_201_2->setReadOnly(true);
        lineEdit_201_3 = new QLineEdit(centralWidget);
        lineEdit_201_3->setObjectName(QString::fromUtf8("lineEdit_201_3"));
        lineEdit_201_3->setEnabled(true);
        lineEdit_201_3->setGeometry(QRect(390, 169, 191, 27));
        lineEdit_201_3->setMaxLength(10);
        lineEdit_201_3->setAlignment(Qt::AlignCenter);
        lineEdit_201_3->setReadOnly(true);
        lineEdit_202 = new QLineEdit(centralWidget);
        lineEdit_202->setObjectName(QString::fromUtf8("lineEdit_202"));
        lineEdit_202->setEnabled(false);
        lineEdit_202->setGeometry(QRect(20, 229, 311, 27));
        lineEdit_301_2 = new QLineEdit(centralWidget);
        lineEdit_301_2->setObjectName(QString::fromUtf8("lineEdit_301_2"));
        lineEdit_301_2->setEnabled(true);
        lineEdit_301_2->setGeometry(QRect(350, 289, 71, 27));
        lineEdit_301_2->setMaxLength(7);
        lineEdit_301_2->setAlignment(Qt::AlignCenter);
        lineEdit_301_2->setReadOnly(true);
        lineEdit_301_3 = new QLineEdit(centralWidget);
        lineEdit_301_3->setObjectName(QString::fromUtf8("lineEdit_301_3"));
        lineEdit_301_3->setEnabled(true);
        lineEdit_301_3->setGeometry(QRect(420, 289, 71, 27));
        lineEdit_301_3->setMaxLength(7);
        lineEdit_301_3->setAlignment(Qt::AlignCenter);
        lineEdit_301_3->setReadOnly(true);
        lineEdit_301_4 = new QLineEdit(centralWidget);
        lineEdit_301_4->setObjectName(QString::fromUtf8("lineEdit_301_4"));
        lineEdit_301_4->setEnabled(true);
        lineEdit_301_4->setGeometry(QRect(490, 289, 71, 27));
        lineEdit_301_4->setMaxLength(7);
        lineEdit_301_4->setAlignment(Qt::AlignCenter);
        lineEdit_301_4->setReadOnly(true);
        lineEdit_301_5 = new QLineEdit(centralWidget);
        lineEdit_301_5->setObjectName(QString::fromUtf8("lineEdit_301_5"));
        lineEdit_301_5->setEnabled(true);
        lineEdit_301_5->setGeometry(QRect(560, 289, 71, 27));
        lineEdit_301_5->setMaxLength(7);
        lineEdit_301_5->setAlignment(Qt::AlignCenter);
        lineEdit_301_5->setReadOnly(true);
        lineEdit_301 = new QLineEdit(centralWidget);
        lineEdit_301->setObjectName(QString::fromUtf8("lineEdit_301"));
        lineEdit_301->setEnabled(false);
        lineEdit_301->setGeometry(QRect(20, 289, 311, 27));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(125, 10, 67, 17));
        label_11->setAlignment(Qt::AlignCenter);
        canPort1 = new QSpinBox(centralWidget);
        canPort1->setObjectName(QString::fromUtf8("canPort1"));
        canPort1->setEnabled(true);
        canPort1->setGeometry(QRect(42, 36, 48, 27));
        canPort1->setAlignment(Qt::AlignCenter);
        canPort1->setReadOnly(false);
        canPort1->setMaximum(1);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(376, 269, 16, 17));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(446, 269, 21, 17));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(520, 269, 16, 17));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(584, 269, 21, 17));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(450, 149, 67, 17));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(410, 89, 31, 17));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(532, 89, 31, 17));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(10, 70, 67, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(190, 20, 271, 61));
        QFont font;
        font.setPointSize(30);
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        DrivingMode1 = new QRadioButton(centralWidget);
        DrivingMode1->setObjectName(QString::fromUtf8("DrivingMode1"));
        DrivingMode1->setEnabled(true);
        DrivingMode1->setGeometry(QRect(20, 370, 191, 22));
        DrivingMode1->setCheckable(true);
        DrivingMode1->setChecked(false);
        DrivingMode1->setAutoRepeat(false);
        DrivingMode5 = new QRadioButton(centralWidget);
        DrivingMode5->setObjectName(QString::fromUtf8("DrivingMode5"));
        DrivingMode5->setGeometry(QRect(320, 410, 171, 22));
        DrivingMode3 = new QRadioButton(centralWidget);
        DrivingMode3->setObjectName(QString::fromUtf8("DrivingMode3"));
        DrivingMode3->setGeometry(QRect(20, 450, 191, 22));
        DrivingMode4 = new QRadioButton(centralWidget);
        DrivingMode4->setObjectName(QString::fromUtf8("DrivingMode4"));
        DrivingMode4->setGeometry(QRect(320, 370, 161, 22));
        DrivingMode2 = new QRadioButton(centralWidget);
        DrivingMode2->setObjectName(QString::fromUtf8("DrivingMode2"));
        DrivingMode2->setGeometry(QRect(20, 410, 191, 22));
        DrivingMode6 = new QRadioButton(centralWidget);
        DrivingMode6->setObjectName(QString::fromUtf8("DrivingMode6"));
        DrivingMode6->setGeometry(QRect(320, 450, 151, 22));
        DrivingMode6->setAutoFillBackground(false);
        DrivingMode6->setAutoExclusive(true);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 330, 511, 161));
        armBox = new QSpinBox(centralWidget);
        armBox->setObjectName(QString::fromUtf8("armBox"));
        armBox->setGeometry(QRect(171, 505, 48, 27));
        accBox = new QSpinBox(centralWidget);
        accBox->setObjectName(QString::fromUtf8("accBox"));
        accBox->setGeometry(QRect(278, 505, 48, 27));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(140, 510, 31, 17));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(250, 510, 31, 17));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(360, 510, 67, 17));
        steerBox = new QDoubleSpinBox(centralWidget);
        steerBox->setObjectName(QString::fromUtf8("steerBox"));
        steerBox->setGeometry(QRect(421, 505, 69, 27));
        steerBox->setMinimum(-540);
        steerBox->setMaximum(540);
        pushButton_LF = new QPushButton(centralWidget);
        pushButton_LF->setObjectName(QString::fromUtf8("pushButton_LF"));
        pushButton_LF->setGeometry(QRect(370, 540, 61, 27));
        pushButton_Z = new QPushButton(centralWidget);
        pushButton_Z->setObjectName(QString::fromUtf8("pushButton_Z"));
        pushButton_Z->setGeometry(QRect(440, 540, 61, 27));
        pushButton_RF = new QPushButton(centralWidget);
        pushButton_RF->setObjectName(QString::fromUtf8("pushButton_RF"));
        pushButton_RF->setGeometry(QRect(510, 540, 61, 27));
        MainWindow->setCentralWidget(centralWidget);
        groupBox->raise();
        label->raise();
        label_2->raise();
        startButton->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        label_7->raise();
        lineEdit_201->raise();
        lineEdit_205->raise();
        lineEdit_205_2->raise();
        lineEdit_205_3->raise();
        lineEdit_205_4->raise();
        lineEdit_205_5->raise();
        lineEdit_201_2->raise();
        lineEdit_201_3->raise();
        lineEdit_202->raise();
        lineEdit_301_2->raise();
        lineEdit_301_3->raise();
        lineEdit_301_4->raise();
        lineEdit_301_5->raise();
        lineEdit_301->raise();
        label_11->raise();
        canPort1->raise();
        label_12->raise();
        label_13->raise();
        label_14->raise();
        label_15->raise();
        label_16->raise();
        label_17->raise();
        label_18->raise();
        label_26->raise();
        label_3->raise();
        DrivingMode5->raise();
        DrivingMode2->raise();
        DrivingMode3->raise();
        DrivingMode4->raise();
        DrivingMode1->raise();
        DrivingMode6->raise();
        armBox->raise();
        accBox->raise();
        label_19->raise();
        label_20->raise();
        label_21->raise();
        steerBox->raise();
        pushButton_LF->raise();
        pushButton_Z->raise();
        pushButton_RF->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 654, 25));
        MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(startButton, lineEdit_201);
        QWidget::setTabOrder(lineEdit_201, lineEdit_205);
        QWidget::setTabOrder(lineEdit_205, lineEdit_205_2);
        QWidget::setTabOrder(lineEdit_205_2, lineEdit_205_3);
        QWidget::setTabOrder(lineEdit_205_3, lineEdit_205_4);
        QWidget::setTabOrder(lineEdit_205_4, lineEdit_205_5);
        QWidget::setTabOrder(lineEdit_205_5, lineEdit_201_2);
        QWidget::setTabOrder(lineEdit_201_2, lineEdit_201_3);
        QWidget::setTabOrder(lineEdit_201_3, lineEdit_202);
        QWidget::setTabOrder(lineEdit_202, lineEdit_301_2);
        QWidget::setTabOrder(lineEdit_301_2, lineEdit_301_3);
        QWidget::setTabOrder(lineEdit_301_3, lineEdit_301_4);
        QWidget::setTabOrder(lineEdit_301_4, lineEdit_301_5);
        QWidget::setTabOrder(lineEdit_301_5, lineEdit_301);
        QWidget::setTabOrder(lineEdit_301, canPort1);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CAN Receiver", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Can Port Select", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "CAR_MONITOR_BRK_ACC (205)", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "CAR_MONITOR_STEER (201)", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "CAR_MONITOR_WHL_SPD (202)", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "CAR_WHL_SPD_RAW (301)", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "( 0 or 1)", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "FL", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "FR", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "RL", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "RR", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "Steering", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "Arm", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "Acc", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#00ff00;\">MCU</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "MCU Can(0)", 0, QApplication::UnicodeUTF8));
        DrivingMode1->setText(QApplication::translate("MainWindow", "1.Fully Autonomous", 0, QApplication::UnicodeUTF8));
        DrivingMode5->setText(QApplication::translate("MainWindow", "5.Steering Input Test", 0, QApplication::UnicodeUTF8));
        DrivingMode3->setText(QApplication::translate("MainWindow", "3.Velocity Autonomous", 0, QApplication::UnicodeUTF8));
        DrivingMode4->setText(QApplication::translate("MainWindow", "4.Velocity Input Test", 0, QApplication::UnicodeUTF8));
        DrivingMode2->setText(QApplication::translate("MainWindow", "2.Steering Autonomous", 0, QApplication::UnicodeUTF8));
        DrivingMode6->setText(QApplication::translate("MainWindow", "6.Driver Mode", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Mode Select", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "Arm", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "Acc", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "Steering", 0, QApplication::UnicodeUTF8));
        pushButton_LF->setText(QApplication::translate("MainWindow", "-539", 0, QApplication::UnicodeUTF8));
        pushButton_Z->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pushButton_RF->setText(QApplication::translate("MainWindow", "539", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MCU_CAN_GUI_H

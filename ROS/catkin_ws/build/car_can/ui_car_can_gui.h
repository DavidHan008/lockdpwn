/********************************************************************************
** Form generated from reading UI file 'car_can_gui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAR_CAN_GUI_H
#define UI_CAR_CAN_GUI_H

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
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *startButton;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_2B0;
    QLineEdit *lineEdit_316;
    QLineEdit *lineEdit_4F0;
    QLineEdit *lineEdit_2B0_2;
    QLineEdit *lineEdit_316_2;
    QLineEdit *lineEdit_4F0_2;
    QSpinBox *canPort2;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *lineEdit_220;
    QLineEdit *lineEdit_220_2;
    QLabel *label_25;
    QLineEdit *lineEdit_220_3;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_2;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(639, 418);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 34, 171, 17));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(410, 30, 99, 27));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 90, 181, 17));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 150, 181, 17));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 210, 181, 17));
        lineEdit_2B0 = new QLineEdit(centralWidget);
        lineEdit_2B0->setObjectName(QString::fromUtf8("lineEdit_2B0"));
        lineEdit_2B0->setEnabled(false);
        lineEdit_2B0->setGeometry(QRect(20, 110, 311, 27));
        lineEdit_316 = new QLineEdit(centralWidget);
        lineEdit_316->setObjectName(QString::fromUtf8("lineEdit_316"));
        lineEdit_316->setEnabled(false);
        lineEdit_316->setGeometry(QRect(20, 170, 311, 27));
        lineEdit_4F0 = new QLineEdit(centralWidget);
        lineEdit_4F0->setObjectName(QString::fromUtf8("lineEdit_4F0"));
        lineEdit_4F0->setEnabled(false);
        lineEdit_4F0->setGeometry(QRect(20, 230, 311, 27));
        lineEdit_2B0_2 = new QLineEdit(centralWidget);
        lineEdit_2B0_2->setObjectName(QString::fromUtf8("lineEdit_2B0_2"));
        lineEdit_2B0_2->setEnabled(true);
        lineEdit_2B0_2->setGeometry(QRect(350, 110, 141, 27));
        lineEdit_2B0_2->setAlignment(Qt::AlignCenter);
        lineEdit_2B0_2->setReadOnly(true);
        lineEdit_316_2 = new QLineEdit(centralWidget);
        lineEdit_316_2->setObjectName(QString::fromUtf8("lineEdit_316_2"));
        lineEdit_316_2->setEnabled(true);
        lineEdit_316_2->setGeometry(QRect(350, 170, 141, 27));
        lineEdit_316_2->setAlignment(Qt::AlignCenter);
        lineEdit_316_2->setReadOnly(true);
        lineEdit_4F0_2 = new QLineEdit(centralWidget);
        lineEdit_4F0_2->setObjectName(QString::fromUtf8("lineEdit_4F0_2"));
        lineEdit_4F0_2->setEnabled(true);
        lineEdit_4F0_2->setGeometry(QRect(350, 230, 141, 27));
        lineEdit_4F0_2->setAlignment(Qt::AlignCenter);
        lineEdit_4F0_2->setReadOnly(true);
        canPort2 = new QSpinBox(centralWidget);
        canPort2->setObjectName(QString::fromUtf8("canPort2"));
        canPort2->setEnabled(true);
        canPort2->setGeometry(QRect(290, 30, 48, 27));
        canPort2->setAlignment(Qt::AlignCenter);
        canPort2->setReadOnly(false);
        canPort2->setMaximum(1);
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(390, 90, 67, 17));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(390, 150, 67, 17));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(390, 210, 67, 17));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(20, 270, 181, 17));
        lineEdit_220 = new QLineEdit(centralWidget);
        lineEdit_220->setObjectName(QString::fromUtf8("lineEdit_220"));
        lineEdit_220->setEnabled(false);
        lineEdit_220->setGeometry(QRect(20, 290, 311, 27));
        lineEdit_220_2 = new QLineEdit(centralWidget);
        lineEdit_220_2->setObjectName(QString::fromUtf8("lineEdit_220_2"));
        lineEdit_220_2->setEnabled(true);
        lineEdit_220_2->setGeometry(QRect(350, 290, 281, 27));
        lineEdit_220_2->setMaxLength(100);
        lineEdit_220_2->setAlignment(Qt::AlignCenter);
        lineEdit_220_2->setReadOnly(true);
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(10, 70, 67, 17));
        lineEdit_220_3 = new QLineEdit(centralWidget);
        lineEdit_220_3->setObjectName(QString::fromUtf8("lineEdit_220_3"));
        lineEdit_220_3->setEnabled(true);
        lineEdit_220_3->setGeometry(QRect(350, 350, 281, 27));
        lineEdit_220_3->setMaxLength(100);
        lineEdit_220_3->setAlignment(Qt::AlignCenter);
        lineEdit_220_3->setReadOnly(true);
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(410, 270, 171, 17));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(416, 330, 171, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 330, 261, 51));
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 639, 25));
        MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(startButton, lineEdit_2B0);
        QWidget::setTabOrder(lineEdit_2B0, lineEdit_316);
        QWidget::setTabOrder(lineEdit_316, lineEdit_4F0);
        QWidget::setTabOrder(lineEdit_4F0, lineEdit_2B0_2);
        QWidget::setTabOrder(lineEdit_2B0_2, lineEdit_316_2);
        QWidget::setTabOrder(lineEdit_316_2, lineEdit_4F0_2);
        QWidget::setTabOrder(lineEdit_4F0_2, canPort2);
        QWidget::setTabOrder(canPort2, lineEdit_220);
        QWidget::setTabOrder(lineEdit_220, lineEdit_220_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CAN Receiver", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Can Port Select ( 0 or 1)", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "SAS (2B0)", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Velocity1 (316)", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Velocity2 (4F0)", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "Steering", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "Velocity", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "Velocity", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("MainWindow", "CAN_IMU (220)", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">OBD</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("MainWindow", "gyro[0], gyro[1], gyro[2]", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("MainWindow", "accl[0], accl[1], accl[2]", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "CAR Can(1)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAR_CAN_GUI_H

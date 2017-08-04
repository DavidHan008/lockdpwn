/********************************************************************************
** Form generated from reading UI file 'rndf_manager_gui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RNDF_MANAGER_GUI_H
#define UI_RNDF_MANAGER_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_8;
    QSpinBox *spinBox_TarWaypt;
    QPushButton *GetCurrentNodeBtn;
    QPushButton *BuildGraph;
    QPushButton *SearchBtn;
    QLabel *label_10;
    QCheckBox *checkBox_TargetNode1;
    QCheckBox *checkBox_TargetNode2;
    QSpinBox *spinBox_TarLane;
    QLabel *label_11;
    QPushButton *RNDFFileFindBtn;
    QSpinBox *spinBox_CheckTarPt;
    QSpinBox *spinBox_TarSeg;
    QLabel *label_13;
    QSpinBox *spinBox_CurSeg;
    QLabel *label_12;
    QSpinBox *spinBox_CurWaypt;
    QLineEdit *mMDFFileName;
    QLabel *label_map;
    QPushButton *MDFFileFindBtn;
    QSpinBox *spinBox_CurLane;
    QLineEdit *mRNDFFileName;
    QLabel *label_7;
    QLabel *label_14;
    QPushButton *pushButton_check2;
    QPushButton *pushButton_check1;
    QPushButton *pushButton_check4;
    QPushButton *pushButton_check3;
    QPushButton *pushButton_check5;
    QWidget *tab_2;
    QWebView *mWebView;
    QPushButton *StartPubMsgBtn;
    QLabel *label_9;
    QPushButton *StopPubMsgBtn;
    QSpinBox *segNumSpinBox;
    QPushButton *PubAllSegMsgBtn;
    QLabel *label_15;
    QPushButton *PubSegMsgBtn;
    QMenuBar *menuBar;
    QMenu *menuRNDF_Manager;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(826, 663);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 811, 621));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 36, 51, 17));
        spinBox_TarWaypt = new QSpinBox(tab);
        spinBox_TarWaypt->setObjectName(QString::fromUtf8("spinBox_TarWaypt"));
        spinBox_TarWaypt->setGeometry(QRect(553, 86, 48, 27));
        spinBox_TarWaypt->setReadOnly(false);
        spinBox_TarWaypt->setMinimum(1);
        spinBox_TarWaypt->setMaximum(500);
        spinBox_TarWaypt->setValue(1);
        GetCurrentNodeBtn = new QPushButton(tab);
        GetCurrentNodeBtn->setObjectName(QString::fromUtf8("GetCurrentNodeBtn"));
        GetCurrentNodeBtn->setGeometry(QRect(110, 126, 151, 27));
        BuildGraph = new QPushButton(tab);
        BuildGraph->setObjectName(QString::fromUtf8("BuildGraph"));
        BuildGraph->setGeometry(QRect(666, 2, 141, 61));
        SearchBtn = new QPushButton(tab);
        SearchBtn->setObjectName(QString::fromUtf8("SearchBtn"));
        SearchBtn->setGeometry(QRect(632, 90, 171, 61));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(100, 72, 191, 17));
        checkBox_TargetNode1 = new QCheckBox(tab);
        checkBox_TargetNode1->setObjectName(QString::fromUtf8("checkBox_TargetNode1"));
        checkBox_TargetNode1->setGeometry(QRect(420, 89, 21, 22));
        checkBox_TargetNode1->setChecked(true);
        checkBox_TargetNode2 = new QCheckBox(tab);
        checkBox_TargetNode2->setObjectName(QString::fromUtf8("checkBox_TargetNode2"));
        checkBox_TargetNode2->setGeometry(QRect(420, 126, 21, 22));
        checkBox_TargetNode2->setChecked(false);
        spinBox_TarLane = new QSpinBox(tab);
        spinBox_TarLane->setObjectName(QString::fromUtf8("spinBox_TarLane"));
        spinBox_TarLane->setGeometry(QRect(498, 86, 48, 27));
        spinBox_TarLane->setReadOnly(false);
        spinBox_TarLane->setValue(1);
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(433, 66, 191, 17));
        RNDFFileFindBtn = new QPushButton(tab);
        RNDFFileFindBtn->setObjectName(QString::fromUtf8("RNDFFileFindBtn"));
        RNDFFileFindBtn->setGeometry(QRect(630, 6, 31, 27));
        spinBox_CheckTarPt = new QSpinBox(tab);
        spinBox_CheckTarPt->setObjectName(QString::fromUtf8("spinBox_CheckTarPt"));
        spinBox_CheckTarPt->setGeometry(QRect(529, 124, 71, 27));
        spinBox_CheckTarPt->setMinimum(1);
        spinBox_TarSeg = new QSpinBox(tab);
        spinBox_TarSeg->setObjectName(QString::fromUtf8("spinBox_TarSeg"));
        spinBox_TarSeg->setGeometry(QRect(443, 86, 48, 27));
        spinBox_TarSeg->setReadOnly(false);
        spinBox_TarSeg->setMinimum(1);
        spinBox_TarSeg->setValue(9);
        label_13 = new QLabel(tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(0, 96, 101, 17));
        spinBox_CurSeg = new QSpinBox(tab);
        spinBox_CurSeg->setObjectName(QString::fromUtf8("spinBox_CurSeg"));
        spinBox_CurSeg->setGeometry(QRect(110, 92, 48, 27));
        spinBox_CurSeg->setReadOnly(false);
        spinBox_CurSeg->setMinimum(1);
        spinBox_CurSeg->setValue(6);
        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(444, 128, 91, 17));
        spinBox_CurWaypt = new QSpinBox(tab);
        spinBox_CurWaypt->setObjectName(QString::fromUtf8("spinBox_CurWaypt"));
        spinBox_CurWaypt->setGeometry(QRect(220, 92, 48, 27));
        spinBox_CurWaypt->setReadOnly(false);
        spinBox_CurWaypt->setMinimum(1);
        spinBox_CurWaypt->setMaximum(500);
        spinBox_CurWaypt->setValue(1);
        mMDFFileName = new QLineEdit(tab);
        mMDFFileName->setObjectName(QString::fromUtf8("mMDFFileName"));
        mMDFFileName->setGeometry(QRect(50, 36, 571, 27));
        mMDFFileName->setReadOnly(true);
        label_map = new QLabel(tab);
        label_map->setObjectName(QString::fromUtf8("label_map"));
        label_map->setGeometry(QRect(0, 160, 811, 431));
        label_map->setFrameShape(QFrame::Box);
        label_map->setFrameShadow(QFrame::Sunken);
        MDFFileFindBtn = new QPushButton(tab);
        MDFFileFindBtn->setObjectName(QString::fromUtf8("MDFFileFindBtn"));
        MDFFileFindBtn->setGeometry(QRect(630, 36, 31, 27));
        spinBox_CurLane = new QSpinBox(tab);
        spinBox_CurLane->setObjectName(QString::fromUtf8("spinBox_CurLane"));
        spinBox_CurLane->setGeometry(QRect(165, 92, 48, 27));
        spinBox_CurLane->setReadOnly(false);
        spinBox_CurLane->setValue(1);
        mRNDFFileName = new QLineEdit(tab);
        mRNDFFileName->setObjectName(QString::fromUtf8("mRNDFFileName"));
        mRNDFFileName->setGeometry(QRect(50, 6, 571, 27));
        mRNDFFileName->setReadOnly(true);
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(0, 6, 51, 17));
        label_14 = new QLabel(tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(330, 90, 91, 20));
        pushButton_check2 = new QPushButton(tab);
        pushButton_check2->setObjectName(QString::fromUtf8("pushButton_check2"));
        pushButton_check2->setGeometry(QRect(403, 366, 16, 21));
        pushButton_check1 = new QPushButton(tab);
        pushButton_check1->setObjectName(QString::fromUtf8("pushButton_check1"));
        pushButton_check1->setGeometry(QRect(419, 366, 16, 21));
        pushButton_check4 = new QPushButton(tab);
        pushButton_check4->setObjectName(QString::fromUtf8("pushButton_check4"));
        pushButton_check4->setGeometry(QRect(403, 319, 16, 21));
        pushButton_check3 = new QPushButton(tab);
        pushButton_check3->setObjectName(QString::fromUtf8("pushButton_check3"));
        pushButton_check3->setGeometry(QRect(419, 319, 16, 21));
        pushButton_check5 = new QPushButton(tab);
        pushButton_check5->setObjectName(QString::fromUtf8("pushButton_check5"));
        pushButton_check5->setGeometry(QRect(510, 410, 16, 21));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        mWebView = new QWebView(tab_2);
        mWebView->setObjectName(QString::fromUtf8("mWebView"));
        mWebView->setGeometry(QRect(20, 170, 761, 471));
        mWebView->setProperty("url", QVariant(QUrl(QString::fromUtf8("http://copina20.cafe24.com/map.html"))));
        StartPubMsgBtn = new QPushButton(tab_2);
        StartPubMsgBtn->setObjectName(QString::fromUtf8("StartPubMsgBtn"));
        StartPubMsgBtn->setGeometry(QRect(121, 22, 81, 27));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(123, 67, 81, 17));
        StopPubMsgBtn = new QPushButton(tab_2);
        StopPubMsgBtn->setObjectName(QString::fromUtf8("StopPubMsgBtn"));
        StopPubMsgBtn->setGeometry(QRect(211, 22, 81, 27));
        segNumSpinBox = new QSpinBox(tab_2);
        segNumSpinBox->setObjectName(QString::fromUtf8("segNumSpinBox"));
        segNumSpinBox->setGeometry(QRect(213, 61, 101, 27));
        PubAllSegMsgBtn = new QPushButton(tab_2);
        PubAllSegMsgBtn->setObjectName(QString::fromUtf8("PubAllSegMsgBtn"));
        PubAllSegMsgBtn->setGeometry(QRect(410, 60, 141, 27));
        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(30, 25, 101, 17));
        PubSegMsgBtn = new QPushButton(tab_2);
        PubSegMsgBtn->setObjectName(QString::fromUtf8("PubSegMsgBtn"));
        PubSegMsgBtn->setGeometry(QRect(320, 60, 81, 27));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 826, 25));
        menuRNDF_Manager = new QMenu(menuBar);
        menuRNDF_Manager->setObjectName(QString::fromUtf8("menuRNDF_Manager"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuRNDF_Manager->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RNDF Manager", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "MDF", 0, QApplication::UnicodeUTF8));
        GetCurrentNodeBtn->setText(QApplication::translate("MainWindow", "Current Node", 0, QApplication::UnicodeUTF8));
        BuildGraph->setText(QApplication::translate("MainWindow", "Build Graph", 0, QApplication::UnicodeUTF8));
        SearchBtn->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Segment . Lane . Waypoint", 0, QApplication::UnicodeUTF8));
        checkBox_TargetNode1->setText(QString());
        checkBox_TargetNode2->setText(QString());
        label_11->setText(QApplication::translate("MainWindow", "Segment . Lane . Waypoint", 0, QApplication::UnicodeUTF8));
        RNDFFileFindBtn->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Current Node", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Check Point", 0, QApplication::UnicodeUTF8));
        label_map->setText(QString());
        MDFFileFindBtn->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "RNDF", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Target Node", 0, QApplication::UnicodeUTF8));
        pushButton_check2->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        pushButton_check1->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        pushButton_check4->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        pushButton_check3->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        pushButton_check5->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "RNDF Manager", 0, QApplication::UnicodeUTF8));
        StartPubMsgBtn->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Segment #", 0, QApplication::UnicodeUTF8));
        StopPubMsgBtn->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        PubAllSegMsgBtn->setText(QApplication::translate("MainWindow", "Send All Segments", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Publish Meg", 0, QApplication::UnicodeUTF8));
        PubSegMsgBtn->setText(QApplication::translate("MainWindow", "Send", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Online Map", 0, QApplication::UnicodeUTF8));
        menuRNDF_Manager->setTitle(QApplication::translate("MainWindow", "RNDF Manager", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RNDF_MANAGER_GUI_H

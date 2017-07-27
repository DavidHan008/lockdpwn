#include <QtGui/QMainWindow>
#include <QThread>
#include <QProcess>

#include <ros/ros.h>
#include "../../../build/rndf_manager/ui_rndf_manager_gui.h"
#include "./RNDF_LIB/rndf_mdf_reader.h"
#include "rndf_manager/srvHeightMap.h" // Revised by shinsh - 21.10.2015
// Thread header
#include "MsgManagerThread.h"
#include "ShortestPath.h"
class QImage;
class QPixel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();
    struct RNDF *m_pRNDF;
    struct MDF *m_pMDF;

public slots:
    void on_RNDFFileFindBtn_clicked();
    void on_MDFFileFindBtn_clicked();

    void on_StartPubMsgBtn_clicked();
    void on_StopPubMsgBtn_clicked();

    void on_BuildGraph_clicked();
    void on_SearchBtn_clicked();
    void on_PubSegMsgBtn_clicked();
    void on_PubAllSegMsgBtn_clicked();
    void on_pushButton_check1_clicked();
    void on_pushButton_check2_clicked();
    void on_pushButton_check3_clicked();
    void on_pushButton_check4_clicked();
    void on_pushButton_check5_clicked();
    ////////////////////////////////////
    void OnCheckBoxTarNode1_clicked();
    void OnCheckBoxTarNode2_clicked();

public:
    void publish_RNDF_path();
    void publish_MDF_path();
    void publish_Global_path();

private :
    int _argc;
    char** _argv;
    ros::Subscriber possub;
    ros::Publisher msgpub;

    Ui::MainWindow ui;
    MsgManagerThread* pMsgManagerThread;
    bool m_bRNDFLoaded;
    bool m_bMDFLoaded;
    CShortestPath* m_pShortestPath;
    QImage *m_pImg;;       //이미지를 로드하기 위한 QImage 선언
    QPixmap *m_pBuffer;  //버퍼로 사용할 QPixmap 선언

    FILE* m_pRNDFFILE;
    FILE* m_pMDFFILE;
    
    ros::ServiceClient service_client;// added by shinsh - 151006

};

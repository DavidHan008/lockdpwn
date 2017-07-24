#include <QtGui>
#include <QApplication>
#include <stdio.h>
#include "../inc/main.h"


CanReceiveThread::CanReceiveThread(CAN_MCU* _pCanMCU, QObject * parent)
    : QThread(parent)
    , m_pCanMCU(_pCanMCU)
{
  threadStop = false;
}

void CanReceiveThread::stop()
{
  threadStop = true;

}
void CanReceiveThread::run()
{
  qDebug("can Thread Start");
  while(!threadStop)
  {
    m_pCanMCU->_canport->ReadCanBuffer();

    m_pCanMCU->GetOdometrydata();
    m_pCanMCU->GetMcuBrkAcc();
    m_pCanMCU->GetMcuSAS();
  }

  threadStop = false;
  qDebug("can Thread End");
}


/////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , _argc(argc), _argv(argv)
{
  nMode = 6;
	
  ui.setupUi(this);

	
  connect( ui.DrivingMode1, SIGNAL(clicked()), this, SLOT(OnDrivingMode()) );
  connect( ui.DrivingMode2, SIGNAL(clicked()), this, SLOT(OnDrivingMode()) );
  connect( ui.DrivingMode3, SIGNAL(clicked()), this, SLOT(OnDrivingMode()) );
  connect( ui.DrivingMode4, SIGNAL(clicked()), this, SLOT(OnDrivingMode()) );
  connect( ui.DrivingMode5, SIGNAL(clicked()), this, SLOT(OnDrivingMode()) );
  connect( ui.DrivingMode6, SIGNAL(clicked()), this, SLOT(OnDrivingMode()) );
  ui.DrivingMode1->setEnabled(false);
  ui.DrivingMode2->setEnabled(false);
  ui.DrivingMode3->setEnabled(false);
  ui.DrivingMode4->setEnabled(false);
  ui.DrivingMode5->setEnabled(false);
  ui.DrivingMode6->setEnabled(false);

  ui.armBox->setEnabled(false);
  ui.accBox->setEnabled(false);
  ui.steerBox->setEnabled(false);

  m_pCanMCU = NULL;

  canThread = NULL;
	
  qnode = NULL;
	
  timer = new QTimer(this);
  connect( timer, SIGNAL(timeout()), this, SLOT(OnTimer()) );
  //connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
  //connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));
}



MainWindow::~MainWindow() {}

void MainWindow::VelModeTransmit(int mode)
{
  if( m_pCanMCU )
  {
    uint8_t CanDataBuf[8];
    uint8_t* pCanData = CanDataBuf;
	
    // Acc/Brake
    UINT8 Temp0_8 = 0;
    int8_t Temp1_8 = 0;
    UINT8 Temp2_8 = 0;

    if( mode == 1 ) // auto
    {
      Temp0_8 = 4;
      Temp1_8 = mComputedBrkAng;
      Temp2_8 = mComputedAccAng;
		
    }
    else if( mode == 2 ) // manual
    {
      Temp0_8 = 4;
      Temp1_8 = mCommandedBrkAng;
      Temp2_8 = mCommandedAccAng;
		
    }
    else if( mode == 3 ) // driver
    {
      Temp0_8 = 0;
      Temp1_8 = 0;
      Temp2_8 = 0;
    }

    if( Temp1_8 > 100 )
    {
      Temp1_8 = 100;
    }
    else if( Temp1_8 < -100 )
    {
      Temp1_8 = -100;
    }

    if( Temp2_8 > 100 )
    {
      Temp2_8 = 100;
    }
    else if( Temp2_8 <= 0 )
    {
      Temp2_8 = 0;
    }
	
	
	
    //SAS
    pCanData[0] = Temp0_8;
    pCanData[1] = Temp1_8;
    pCanData[2] = Temp2_8;
    pCanData[3] = 0;
    pCanData[4] = 0;
    pCanData[5] = 0;
    pCanData[6] = 0;
    pCanData[7] = 0;

    m_pCanMCU->_canport->TransmitCanMsg(pCanData,0x105);
  }
}

void MainWindow::SteerModeTransmit(int mode)
{
  if( m_pCanMCU )
  {
    uint8_t CanDataBuf[8];
    uint8_t* pCanData = CanDataBuf;

    UINT16 Temp_16 = 0;
    if( mode == 4 )
    {
      pCanData[0] = 1;
      Temp_16 = mComputedSteerAng;
    }
    else if( mode == 5 )
    {
      pCanData[0] = 1;
      Temp_16 = mCommandedSteerAng;
    }
    else if( mode == 6 )
    {
      pCanData[0] = 0;
      Temp_16 = 0;
    }
	
    //SAS
    pCanData[1] = Temp_16 & 0xFF;
    pCanData[2] = (Temp_16>>8) & 0xFF;
    pCanData[3] = 0;
    pCanData[4] = 0;
    pCanData[5] = 0;
    pCanData[6] = 0;
    pCanData[7] = 0;

    m_pCanMCU->_canport->TransmitCanMsg(pCanData,0x101);
  }

}

void MainWindow::GearModeTransmit(bool power, int mode)
{
  if( m_pCanMCU )
  {
    uint8_t CanDataBuf[8];
    uint8_t* pCanData = CanDataBuf;
	
    // Acc/Brake
    int8_t Temp0_8 = 0;
    UINT8 Temp1_8 = 0x00;
		
    if( power )
      Temp1_8 = 0x11;
    Temp0_8 = mode;
		
    //SAS
    pCanData[0] = Temp0_8;
    pCanData[1] = Temp1_8;
    pCanData[2] = 0;
    pCanData[3] = 0;
    pCanData[4] = 0;
    pCanData[5] = 0;
    pCanData[6] = 0;
    pCanData[7] = 0;

    m_pCanMCU->_canport->TransmitCanMsg(pCanData,0x2B1);
  }
}
void MainWindow::OnDrivingMode()
{
  if(m_pCanMCU)
  {
    mComputedSteerAng = m_pCanMCU->_mcuSAS.SteeringAngle;
    mCommandedSteerAng = m_pCanMCU->_mcuSAS.SteeringAngle;

    mComputedAccAng = m_pCanMCU->_mcuBrkAcc.AccVoltage;
    mCommandedAccAng = m_pCanMCU->_mcuBrkAcc.AccVoltage;

    mComputedBrkAng = m_pCanMCU->_mcuBrkAcc.ArmAngle;
    mCommandedBrkAng = m_pCanMCU->_mcuBrkAcc.ArmAngle;

		
    if( ui.DrivingMode1->isChecked() )
    {
      // fully auto
      qnode->m_velMode = 1;
      qnode->m_steerMode = 4;
      qnode->m_autonomousMode = true;
      //VelModeTransmit(1);
      //SteerModeTransmit(4);
			
    }
    else if(ui.DrivingMode2->isChecked() )
    {
      // semi auto - only steer
      qnode->m_velMode = 3;
      qnode->m_steerMode = 4;
			
      qnode->m_autonomousMode = true;
      //VelModeTransmit(3);
      //SteerModeTransmit(4);
    }
    else if(ui.DrivingMode3->isChecked() )
    {
      // semi auto - only vel
      qnode->m_velMode = 1;
      qnode->m_steerMode = 6;
			
      qnode->m_autonomousMode = true;
		
      //VelModeTransmit(1);
      //SteerModeTransmit(6);
    }
    else if(ui.DrivingMode4->isChecked() )
    {
      qnode->m_autonomousMode = false;
      VelModeTransmit(2);
      SteerModeTransmit(6);
      ui.armBox->setEnabled(true);
      ui.accBox->setEnabled(true);
      ui.steerBox->setEnabled(false);
    }
    else if(ui.DrivingMode5->isChecked() )
    {
      qnode->m_autonomousMode = false;
      VelModeTransmit(3);
      SteerModeTransmit(5);
      ui.armBox->setEnabled(false);
      ui.accBox->setEnabled(false);
      ui.steerBox->setEnabled(true);
    }
    else if(ui.DrivingMode6->isChecked() )
    {
      qnode->m_autonomousMode = false;
      VelModeTransmit(3);
      SteerModeTransmit(6);
      ui.armBox->setEnabled(false);
      ui.accBox->setEnabled(false);
      ui.steerBox->setEnabled(false);
    }
    else
    {
      VelModeTransmit(3);
      SteerModeTransmit(6);
    }
    printf("---------------------\n");
  }
}
void MainWindow::OnTimer()
{
  char text[2048];
  // MCU BRK, ACC
  sprintf(text, "%s", m_pCanMCU->_canport->CAR_MONITOR_BRK_ACC.text);
  ui.lineEdit_205->setText(text);
  if(strcmp(m_pCanMCU->_canport->CAR_MONITOR_BRK_ACC.text, "no data") != 0)
  {
    sprintf(text, "%d", m_pCanMCU->_mcuBrkAcc.BrkCtlBit);
    ui.lineEdit_205_2->setText(text);

    sprintf(text, "%d", m_pCanMCU->_mcuBrkAcc.AccCtlBit);
    ui.lineEdit_205_3->setText(text);

    sprintf(text, "%f", m_pCanMCU->_mcuBrkAcc.ArmAngle);
    ui.lineEdit_205_4->setText(text);

    sprintf(text, "%f", m_pCanMCU->_mcuBrkAcc.AccVoltage);
    ui.lineEdit_205_5->setText(text);
  }


  // MCU STEER
  sprintf(text, "%s", m_pCanMCU->_canport->CAR_MONITOR_STEER.text);
  ui.lineEdit_201->setText(text);
  if(strcmp(m_pCanMCU->_canport->CAR_MONITOR_STEER.text, "no data") != 0)
  {
    sprintf(text, "%d",m_pCanMCU->_mcuSAS.SteerCtlBit);
    ui.lineEdit_201_2->setText(text);

    sprintf(text, "%f", m_pCanMCU->_mcuSAS.SteeringAngle);
    ui.lineEdit_201_3->setText(text);
  }

  // MCU WHL_SPD
  sprintf(text, "%s", m_pCanMCU->_canport->CAR_MONITOR_WHL_SPD.text);
  ui.lineEdit_202->setText(text);

  // MCU CAR_WHL_SPD_RAW
  sprintf(text, "%s", m_pCanMCU->_canport->CAR_WHL_SPD_RAW.text);
  ui.lineEdit_301->setText(text);
  if(strcmp(m_pCanMCU->_canport->CAR_WHL_SPD_RAW.text, "no data") != 0)
  {
    sprintf(text, "%f", m_pCanMCU->_mcuOdometry.WheelSpeed_FL);
    ui.lineEdit_301_2->setText(text);

    sprintf(text, "%f", m_pCanMCU->_mcuOdometry.WheelSpeed_FR);
    ui.lineEdit_301_3->setText(text);

    sprintf(text, "%f", m_pCanMCU->_mcuOdometry.WheelSpeed_RL);
    ui.lineEdit_301_4->setText(text);

    sprintf(text, "%f", m_pCanMCU->_mcuOdometry.WheelSpeed_RR);
    ui.lineEdit_301_5->setText(text);
  }
}
void MainWindow::on_pushButton_Z_clicked()
{
  GearModeTransmit(true, 1);
  //ui.steerBox->setValue(0);
}
void MainWindow::on_pushButton_LF_clicked()
{
  GearModeTransmit(true, 2);
  //ui.steerBox->setValue(-536);
}
void MainWindow::on_pushButton_RF_clicked()
{
  GearModeTransmit(true, 4);
  //ui.steerBox->setValue(536);
}
void MainWindow::on_armBox_valueChanged()
{
  if(ui.DrivingMode4->isChecked())
  {
    mCommandedBrkAng = ui.armBox->value();
    //printf("%d\n", mCommandedBrkAng);
    VelModeTransmit(2);
  }
  printf("---------------------\n");
}

void MainWindow::on_accBox_valueChanged()
{
  if(ui.DrivingMode4->isChecked())
  {
    mCommandedAccAng = ui.accBox->value();
    //printf("%d\n", mCommandedAccAng);
    VelModeTransmit(2);
  }
  printf("---------------------\n");
}

void MainWindow::on_steerBox_valueChanged()
{
  if(ui.DrivingMode5->isChecked())
  {
    mCommandedSteerAng = ui.steerBox->value()*10.0;
    //printf("%f\n", mCommandedSteerAng);
    SteerModeTransmit(5);
  }
  printf("---------------------\n");
}


void MainWindow::on_startButton_clicked()
{
	
  if(!m_pCanMCU)
  {
		
    ui.startButton->setText("Stop");

    m_pCanMCU = new CAN_MCU(ui.canPort1->value());
    printf("can port[%d]\n", ui.canPort1->value());

    canThread = new CanReceiveThread(m_pCanMCU);
    canThread->start();

    qnode = new QNode(_argc, _argv, &ui, m_pCanMCU);
    qnode->start();


    //timer->start(500); // ontimer. 밀리초단위.
    timer->start(100); // ontimer. 밀리초단위.

		
    /////////////////////////////////////////////////
    ui.DrivingMode1->setEnabled(true);
    ui.DrivingMode2->setEnabled(true);
    ui.DrivingMode3->setEnabled(true);
    ui.DrivingMode4->setEnabled(true);
    ui.DrivingMode5->setEnabled(true);
    ui.DrivingMode6->setEnabled(true);

    ui.DrivingMode6->setChecked(true);
    OnDrivingMode();
  }
  else
  {
    ui.DrivingMode6->setChecked(true);
    OnDrivingMode();

    ui.startButton->setText("Start");

    timer->stop();

    canThread->stop();
    canThread->wait();
    qnode->stop();
    qnode->wait();
    delete canThread;
    canThread = NULL;
		
    delete qnode;
    qnode = NULL;

    delete m_pCanMCU;
    m_pCanMCU = NULL;

    printf("thread clear\n");
    ////////////////////////////////////////////////
    ui.DrivingMode1->setEnabled(false);
    ui.DrivingMode2->setEnabled(false);
    ui.DrivingMode3->setEnabled(false);
    ui.DrivingMode4->setEnabled(false);
    ui.DrivingMode5->setEnabled(false);
    ui.DrivingMode6->setEnabled(false);
    ui.armBox->setEnabled(false);
    ui.accBox->setEnabled(false);
    ui.steerBox->setEnabled(false);
  }
}









int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  MainWindow w(argc, argv);
  w.show();

  app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

  return app.exec();
}







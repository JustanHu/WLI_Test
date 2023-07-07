#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <thread>

using namespace std;
static bool th_threadOpenFlag = FALSE;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MRe-WLI Test Program");

    // 创建pmac对象和电机对象
    pmacDevice = new PmacClass();
    motorPX = new MotorClass(pmacDevice,"PX");
    motorPZ = new MotorClass(pmacDevice,"PZ");
    motorPR = new MotorClass(pmacDevice,"PR");
}

MainWindow::~MainWindow()
{
    delete pmacDevice;
    delete motorPX;
    delete motorPZ;
    delete motorPR;
    th_threadOpenFlag = TRUE;

    delete WLITest;
    delete ui;
}


void MainWindow::on_btn_Connect_clicked() //TCP连接按钮
{
    WLITest = new brukerWLI(ui->le_IP->text().toStdString(),ui->le_Port->text().toUInt()); //获取IP和端口号
    bool connectStatus = WLITest->tcpBrukerConnect();
    if(connectStatus)
    {
        ui->btn_Connect->setEnabled(false);
        ui->btn_tcpDisconnect->setEnabled(true);
        ui->wd_Turret_MMD->setEnabled(true);
        ui->wd_Turret_Init->setEnabled(true);
        ui->wd_Autofocus->setEnabled(true);
        ui->wd_SingleAcquisition->setEnabled(true);
        ui->wd_Measurement->setEnabled(true);
        ui->wd_ZScanner->setEnabled(true);
        ui->wd_Intensity->setEnabled(true);
        ui->wd_LockMode->setEnabled(true);
        ui->statusbar->showMessage("TCP server is successfully connected. Procedure"); //状态栏显示当前状态
    }
    else
        ui->statusbar->showMessage("TCP server connection failed. Procedure");
};

void MainWindow::on_btn_tcpDisconnect_clicked()//TCP断开连接按钮
{
     bool disconnectStatus = WLITest->tcpBrukerDisconnect();
     if(disconnectStatus)
     {
         ui->btn_Connect->setEnabled(true);
         ui->btn_tcpDisconnect->setEnabled(false);
         ui->wd_Turret_MMD->setEnabled(false);
         ui->wd_Turret_Init->setEnabled(false);
         ui->wd_Autofocus->setEnabled(false);
         ui->wd_SingleAcquisition->setEnabled(false);
         ui->wd_Measurement->setEnabled(false);
         ui->wd_ZScanner->setEnabled(false);
         ui->wd_Intensity->setEnabled(false);
         ui->wd_LockMode->setEnabled(false);
         ui->statusbar->showMessage("TCP server is successfully disconnected. Procedure"); //状态栏显示当前状态
     }
     else
         ui->statusbar->showMessage("TCP server disconnected failed. Procedure");
}

void MainWindow::on_cmb_turretChange_activated(int index) //切换Turret
{
    switch (index){
       case 0:{
            bool changeTurretStatus = WLITest->changeTurret(MRe3DSensor);
            if(changeTurretStatus)
                ui->statusbar->showMessage("Change sensor successfully"); //切换为传感器
            else
                ui->statusbar->showMessage("Sensor change failure");
            break;
        }
        case 1:{
            bool changeTurretStatus = WLITest->changeTurret(bruker10Turret);
            if(changeTurretStatus)
                ui->statusbar->showMessage("Change 10X Turret successfully"); //切换为10倍镜
            else
                ui->statusbar->showMessage("10X Turret change failure");
            break;
        }
        case 2:{
            bool changeTurretStatus = WLITest->changeTurret(bruker20Turret);
            if(changeTurretStatus)
                ui->statusbar->showMessage("Change 20X Turret successfully"); //切换为20倍镜
            else
                ui->statusbar->showMessage("20X Turret change failure");
            break;
        }
        case 3:{
            bool changeTurretStatus = WLITest->changeTurret(bruker50Turret);
            if(changeTurretStatus)
                ui->statusbar->showMessage("Change 50X Turret successfully"); //切换为50倍镜
            else
                ui->statusbar->showMessage("50X Turret change failure");
            break;
        }
      }

}

void MainWindow::on_cmb_MMDChange_activated(int index) //切换MMD
{
    switch (index){
       case 0:{
            bool changeMMDStatus = WLITest->changeMMD(bruker55MMD);
            if(changeMMDStatus)
                ui->statusbar->showMessage("Change .55MMD successfully"); //切换为.55倍镜
            else
                ui->statusbar->showMessage(".55MMD change failure");
            break;
        }
        case 1:{
            bool changeMMDStatus = WLITest->changeMMD(bruker1MMD);
            if(changeMMDStatus)
                ui->statusbar->showMessage("Change 1MMD successfully"); //切换为1倍镜
            else
                ui->statusbar->showMessage("1MMD change failure");
            break;
        }
        case 2:{
            bool changeMMDStatus = WLITest->changeMMD(bruker2MMD);
            if(changeMMDStatus)
                ui->statusbar->showMessage("Change 2MMD successfully"); //切换为2倍镜
            else
                ui->statusbar->showMessage("2MMD Turret change failure");
            break;
        }
     }
}

void MainWindow::on_btn_getTurret_clicked() //获取当前Turret倍数
{
    int Turret_temp = WLITest->getTurretPosition();
    switch(Turret_temp){
        case 0:
            ui->statusbar->showMessage("Turret is currently in the sensor position."); //当前处于传感器位置
        break;
        case 1:
            ui->statusbar->showMessage("Turret is currently in the 10X position."); //当前处于10X位置
        break;
        case 2:
            ui->statusbar->showMessage("Turret is currently in the 20X position."); //当前处于20X位置
        break;
        case 3:
            ui->statusbar->showMessage("Turret is currently in the 50X position."); //当前处于50X位置
        break;
        default:
            ui->statusbar->showMessage("Get Turret position error!"); //当前处于50X位置
    }

}

void MainWindow::on_btn_getMMD_clicked()//获取当前MMD倍数
{
    int MMD_temp = WLITest->getMMDPosition();
    switch(MMD_temp){
        case 0:
            ui->statusbar->showMessage("MMD is currently in the .55X position."); //当前处于.55X倍镜
        break;
        case 1:
            ui->statusbar->showMessage("MMD is currently in the 1X position."); //当前处于1X位置
        break;
        case 2:
            ui->statusbar->showMessage("MMD is currently in the 2X position."); //当前处于2X位置
        break;
        default:
            ui->statusbar->showMessage("Get MMD position error!"); //当前处于50X位置
    }
}

void MainWindow::on_btn_Turret_Init_clicked()//初始化Turret
{
    bool initStatus = WLITest->initTurret();
    if(initStatus)
        ui->statusbar->showMessage("Initializing the Turret succeeded. Procedure.");
    else
        ui->statusbar->showMessage("Failed to initialize the Turret.");
}

void MainWindow::on_btn_Autofocus_clicked()//执行布鲁克初始化按钮
{
    // 创建一个消息框，并询问用户是否进行了Bruker的Teach操作
    QMessageBox msgBox;
    msgBox.setText("Is Bruker's Teach operation running?       ");
    msgBox.setWindowTitle("Bruker Autofocus");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int result = msgBox.exec();

    // 根据用户的选择执行相应的操作
    if (result == QMessageBox::Yes)
    {
        bool AutofocusStatus = WLITest->doAutofocus();
        if(AutofocusStatus)
            ui->statusbar->showMessage("The Autofocus operation succeeded. Procedure");
        else
            ui->statusbar->showMessage("The Autofocus operation failed. Procedure");
    }
    else if (result == QMessageBox::No)
    {
        ui->statusbar->showMessage("Perform the Bruker Teach operation first!"); //提醒用户进行Bruker的Teach操作
        // 退出槽函数
        return;
    }

}

void MainWindow::on_btn_SingleAcquisition_clicked()//单次测量
{
    bool acquisitionStatus = WLITest->doSingleAcquisition();
    if(acquisitionStatus)
        ui->statusbar->showMessage("Do single Acquisition succeeded. Procedure");
    else
        ui->statusbar->showMessage("Do single Acquisition failed. Procedure");
}

void MainWindow::on_btn_Measurement_clicked()//按配方测量
{
    bool measurementStatus = WLITest->doMeasurement();
    if(measurementStatus)
        ui->statusbar->showMessage("Do Measurement succeeded. Procedure");
    else
        ui->statusbar->showMessage("Do Measurement failed. Procedure");
}

void MainWindow::on_btn_getZScanner_clicked()//获取当前Z Scanner位置
{
    float scannerPos = WLITest->getZScannerPos();
    QString message = QString("Scanner Position: %1").arg(QString::number(scannerPos, 'f', 2));
    ui->statusbar->showMessage(message+" nm");
}

void MainWindow::on_spb_setZScanner_editingFinished()//设置当前Z Scanner位置（绝对位置）
{
    bool setZScannerStatus = WLITest->setZScannerPos(ui->spb_setZScanner->value());
    if(setZScannerStatus)
        ui->statusbar->showMessage("Set Z Scanner Position succeeded. Procedure");
    else
        ui->statusbar->showMessage("Set Z Scanner Position failed. Procedure");
}

void MainWindow::on_btn_getIntensity_clicked()//获取当前白光强度值
{
    float Intensity = WLITest->getIntensity();
    QString message = QString("Intendity: %1").arg(QString::number(Intensity, 'f', 2));
    ui->statusbar->showMessage(message+" %");
}

void MainWindow::on_dspb_setIntensity_editingFinished()//设置当前白光强度值
{
    bool setIntensityStatus = WLITest->setIntensity(ui->dspb_setIntensity->value());
    if(setIntensityStatus)
        ui->statusbar->showMessage("Set Intensityn succeeded. Procedure");
    else
        ui->statusbar->showMessage("Set Intensity failed. Procedure");
}

void MainWindow::on_btn_getMode_clicked()//获取当前白光锁定模式
{
    int modeStatus = WLITest->getLockoutMode();
    switch(modeStatus){
        case 0:
            ui->statusbar->showMessage("WLI is currently in normal mode."); //当前处于正常模式
        break;
        case 1:
            ui->statusbar->showMessage("WLI is currently in instrument-only control mode"); //当前处于仅仪表控制模式
        break;
        case 2:
            ui->statusbar->showMessage("WLI is currently in full lock mode."); //当前处于完全锁定模式
        break;
        default:
            ui->statusbar->showMessage("Get lock mode error!"); //获取模式错误
    }
}

void MainWindow::on_btn_Lockout_clicked()//设置当前白光为全锁定模式
{
    bool lockoutStatus = WLITest->setLockoutMode();
    if(lockoutStatus)
        ui->statusbar->showMessage("Set Lockout mode succeeded. Procedure");
    else
        ui->statusbar->showMessage("Set Lockout mode failed. Procedure");
}

void MainWindow::on_btn_InstrumentControlOnly_clicked()//设置当前白光为仅仪表控制模式
{
    bool instrumentControlOnlyStatus = WLITest->setInstrumentControlOnlyMode();
    if(instrumentControlOnlyStatus)
        ui->statusbar->showMessage("Set Instrument Control Onlys mode succeeded. Procedure");
    else
        ui->statusbar->showMessage("Set Instrument Control Onlys mode failed. Procedure");
}

void MainWindow::on_btn_Normal_clicked()//设置当前白光为仅仪表控制模式
{
    bool normalStatus = WLITest->setNormalMode();
    if(normalStatus)
        ui->statusbar->showMessage("Set Normal mode succeeded. Procedure");
    else
        ui->statusbar->showMessage("Set Normal mode failed. Procedure");
}






// Pmac 测试
void MainWindow::on_btn_pmacTest_Connect_clicked() // PMAC 连接按钮
{
    switch(pmacDevice->devInit()) {
    case -1: {
        ui->statusbar->showMessage("Pmac Connect Failed!");
        break; }
    case 1: {
        ui->statusbar->showMessage("Pmac Connect Succeeded!");
        break; }
    }
}


void MainWindow::on_btn_pmacTest_Close_clicked() // PMAC 断开按钮
{
    switch(pmacDevice->devClose()) {
    case -1: {
        ui->statusbar->showMessage("Pmac Close Failed!");
        break; }
    case 1: {
        ui->statusbar->showMessage("Pmac Close Successed!");
        break; }
    }
}

// IO 测试
void MainWindow::on_btn_ioTest_Open_clicked() // 开 IO 按钮
{
    switch(pmacDevice->setIOStatus(1,0)) { // M1 高电平
    case -1: {
        ui->statusbar->showMessage("Pmac Set IO Failed!");
        break; }
    case 1: {
        ui->statusbar->showMessage("Pmac Set IO Successed!");
        setLabelColor(ui->lbl_ioTest_M1,QString("#76EE00"));
        break; }
    }
}

void MainWindow::on_btn_ioTest_Close_clicked() // 关 IO 按钮
{
    switch(pmacDevice->setIOStatus(1,1)) { // M1 低电平
    case -1: {
        ui->statusbar->showMessage("Pmac Set IO Failed!");
        break; }
    case 1: {
        ui->statusbar->showMessage("Pmac Set IO Successed!");
        setLabelColor(ui->lbl_ioTest_M1,QString("#76EE00"));
        break; }
    }
}

// MOTOR 测试
void MainWindow::on_lbl_motorTest_PX_ConstSpeed_clicked() // PX轴定速运动
{
    int dir = 0;
    if(ui->cb_motorTest_Forward->isChecked())   dir = 1;    // 正转
    if(ui->cb_motorTest_Reversal->isChecked())  dir = 0;    // 反转
    motorPX->singleConstSpeedMove(motorPX->axisNumber,ui->spb_motorTest_PX_InitSpeed->value(),dir);
}

void MainWindow::on_lbl_motorTest_PR_ConstSpeed_clicked()   // PR轴定速运动
{
    int dir = 0;
    if(ui->cb_motorTest_Forward->isChecked())   dir = 1;    // 正转
    if(ui->cb_motorTest_Reversal->isChecked())  dir = 0;    // 反转
    motorPR->singleConstSpeedMove(motorPR->axisNumber,ui->spb_motorTest_PR_InitSpeed->value(),dir);
}

void MainWindow::on_lbl_motorTest_PZ_ConstSpeed_clicked()   // PZ轴定速运动
{
    int dir = 0;
    if(ui->cb_motorTest_Forward->isChecked())   dir = 1;    // 正转
    if(ui->cb_motorTest_Reversal->isChecked())  dir = 0;    // 反转
    motorPZ->singleConstSpeedMove(motorPZ->axisNumber,ui->spb_motorTest_PZ_InitSpeed->value(),dir);
}


void MainWindow::on_lbl_motorTest_PX_ConstLength_clicked()  // PX轴定长运动
{
    int dir = 0;
    if(ui->cb_motorTest_Forward->isChecked())   dir = 1;    // 正转
    if(ui->cb_motorTest_Reversal->isChecked())  dir = 0;    // 反转

    if(ui->cb_motorTest_Absolute->isChecked())  // 绝对
        motorPX->singleConstLengthMoveTo(motorPX->axisNumber,ui->spb_motorTest_PX_InitSpeed->value(),ui->spb_motorTest_PX_MovDis->value(),dir);
    if(ui->cb_motorTest_Relative->isChecked())  // 相对
        motorPX->singleConstLengthMove(motorPX->axisNumber,ui->spb_motorTest_PX_InitSpeed->value(),ui->spb_motorTest_PX_MovDis->value(),dir);
}


void MainWindow::on_lbl_motorTest_PR_ConstLength_clicked()  // PR轴定长运动
{
    int dir = 0;
    if(ui->cb_motorTest_Forward->isChecked())   dir = 1;    // 正转
    if(ui->cb_motorTest_Reversal->isChecked())  dir = 0;    // 反转

    if(ui->cb_motorTest_Absolute->isChecked())  // 绝对
        motorPR->singleConstLengthMoveTo(motorPR->axisNumber,ui->spb_motorTest_PR_InitSpeed->value(),ui->spb_motorTest_PR_MovDis->value(),dir);
    if(ui->cb_motorTest_Relative->isChecked())  // 相对
        motorPR->singleConstLengthMove(motorPR->axisNumber,ui->spb_motorTest_PR_InitSpeed->value(),ui->spb_motorTest_PR_MovDis->value(),dir);
}


void MainWindow::on_lbl_motorTest_PZ_ConstLength_clicked()  // PZ轴定长运动
{
    int dir = 0;
    if(ui->cb_motorTest_Forward->isChecked())   dir = 1;    // 正转
    if(ui->cb_motorTest_Reversal->isChecked())  dir = 0;    // 反转

    if(ui->cb_motorTest_Absolute->isChecked())  // 绝对
        motorPZ->singleConstLengthMoveTo(motorPZ->axisNumber,ui->spb_motorTest_PZ_InitSpeed->value(),ui->spb_motorTest_PZ_MovDis->value(),dir);
    if(ui->cb_motorTest_Relative->isChecked())  // 相对
        motorPZ->singleConstLengthMove(motorPZ->axisNumber,ui->spb_motorTest_PZ_InitSpeed->value(),ui->spb_motorTest_PZ_MovDis->value(),dir);
}


void MainWindow::on_lbl_motorTest_PX_Stop_clicked()     // PX轴停止
{
    motorPX->singleStop(motorPX->axisNumber);
}

void MainWindow::on_lbl_motorTest_PR_Stop_clicked()     // PR轴停止
{
    motorPR->singleStop(motorPR->axisNumber);
}

void MainWindow::on_lbl_motorTest_PZ_Stop_clicked()     // PZ轴停止
{
    motorPZ->singleStop(motorPZ->axisNumber);
}

void MainWindow::on_btn_motorTest_OpenLimit_clicked()    // PX\PR\PZ 开限位
{
    motorPX->setLimitStatus(motorPX->axisNumber,1);
    motorPR->setLimitStatus(motorPR->axisNumber,1);
    motorPZ->setLimitStatus(motorPZ->axisNumber,1);
}


void MainWindow::on_btn_motorTest_CloseLimit_clicked()    // PX\PR\PZ 关限位
{
    motorPX->setLimitStatus(motorPX->axisNumber,0);
    motorPR->setLimitStatus(motorPR->axisNumber,0);
    motorPZ->setLimitStatus(motorPZ->axisNumber,0);
}



// THREAD 测试
void MainWindow::on_btn_threadTest_Open_clicked()       // 开启 PMAC 实时线程
{
    std::thread th_threadOpen (&MainWindow::th_threadOpen,this);
    std::cout << "th_threadOpen ID:" << th_threadOpen.get_id() << std::endl;
    th_threadOpen.join();
}

void MainWindow::th_threadOpen()
{
    double value;
    while(!th_threadOpenFlag)
    {
        // 读取位置
        value = motorPX->getPosStatus(motorPX->axisNumber);
        ui->lbl_threadTest_PX_Pos->setText(QString::number(value, 'f', 2));

        value = motorPR->getPosStatus(motorPR->axisNumber);
        ui->lbl_threadTest_PR_Pos->setText(QString::number(value, 'f', 2));

        value = motorPZ->getPosStatus(motorPZ->axisNumber);
        ui->lbl_threadTest_PZ_Pos->setText(QString::number(value, 'f', 2));

        // 读取速度
        value = motorPX->getVelStatus(motorPX->axisNumber);
        ui->lbl_threadTest_PX_Vel->setText(QString::number(value, 'f', 2));

        value = motorPR->getVelStatus(motorPR->axisNumber);
        ui->lbl_threadTest_PR_Vel->setText(QString::number(value, 'f', 2));

        value = motorPZ->getVelStatus(motorPZ->axisNumber);
        ui->lbl_threadTest_PZ_Vel->setText(QString::number(value, 'f', 2));

        // 读取IO
        if(!pmacDevice->getIOStatus(1))     // 高电平
            setLabelColor(ui->lbl_ioTest_M1,QString("#76EE00"));
        else                                // 低电平
            setLabelColor(ui->lbl_ioTest_M1,QString("#FF4040"));

        if(!pmacDevice->getIOStatus(2))     // 高电平
            setLabelColor(ui->lbl_ioTest_M2,QString("#76EE00"));
        else                                // 低电平
            setLabelColor(ui->lbl_ioTest_M2,QString("#FF4040"));

        if(!pmacDevice->getIOStatus(3))     // 高电平
            setLabelColor(ui->lbl_ioTest_M3,QString("#76EE00"));
        else                                // 低电平
            setLabelColor(ui->lbl_ioTest_M3,QString("#FF4040"));

        this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


void MainWindow::on_btn_threadTest_PX_SetZero_clicked()
{
    motorPX->setZeroPoint(motorPZ->axisNumber);
}

void MainWindow::on_btn_threadTest_PR_SetZero_clicked()
{
    motorPR->setZeroPoint(motorPR->axisNumber);
}

void MainWindow::on_btn_threadTest_PZ_SetZero_clicked()
{
    motorPZ->setZeroPoint(motorPZ->axisNumber);
}





void MainWindow::on_pushButton_clicked()
{
    setLabelColor(ui->lbl_ioTest_M1,QString("#76EE00"));
}








void MainWindow::setLabelColor(QLabel* label, QString color)
{
    const QString SheetStyle =
           "min-width:14px;         \
            min-height:14px;        \
            max-width:14px;         \
            max-height:14px;        \
            border-radius:9px;      \
            border:2px solid gray;  \
            background:" + color;
    label->setStyleSheet(SheetStyle);
}



















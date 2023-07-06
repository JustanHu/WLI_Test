#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MRe-WLI Test Program");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete WLITest;
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





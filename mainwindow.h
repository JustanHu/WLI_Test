#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MotorClass.h"
#include <QMainWindow>
#include "brukerWLI.h"
#include <QTimer>
#include <QMessageBox>


QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }

QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    brukerWLI *WLITest;

private slots:

/***************** TCP测试函数 *****************/
/**
 * @brief  建立tcp连接
 */
    void on_btn_Connect_clicked();

/**
 * @brief 更换Turret倍数
 * @param index: 当前cmb的下标
 */
    void on_cmb_turretChange_activated(int index);

/**
 * @brief 更换MMD倍数
 * @param index: 当前cmb的下标
 */
    void on_cmb_MMDChange_activated(int index);

/**
 * @brief 获取当前Turret倍数
 */
    void on_btn_getTurret_clicked();

/**
 * @brief 获取当前MMD倍数
 */
    void on_btn_getMMD_clicked();

/**
 * @brief 初始化Turret
 */
    void on_btn_Turret_Init_clicked();

/**
 * @brief 执行布鲁克自动聚焦
 */
    void on_btn_Autofocus_clicked();

/**
 * @brief 单次测量
 */
    void on_btn_SingleAcquisition_clicked();

/**
 * @brief 按配方测量
 */
    void on_btn_Measurement_clicked();

/**
 * @brief 获取当前Z Scanner位置
 */
    void on_btn_getZScanner_clicked();

/**
 * @brief 移动当前Z Scanner位置
 */
    void on_spb_setZScanner_editingFinished();

/**
 * @brief 获取当前白光强度值
 */
    void on_btn_getIntensity_clicked();

/**
 * @brief 设置当前白光强度值
 */
    void on_dspb_setIntensity_editingFinished();

/**
 * @brief 获取当前白光锁定模式
 */
    void on_btn_getMode_clicked();

/**
 * @brief 设置当前白光为全锁定模式
 */
    void on_btn_Lockout_clicked();

/**
 * @brief 设置当前白光为仅仪表控制模式
 */
    void on_btn_InstrumentControlOnly_clicked();

/**
 * @brief 设置当前白光为正常模式
 */
    void on_btn_Normal_clicked();

/**
 * @brief tcp断开连接
 */
    void on_btn_tcpDisconnect_clicked();

/***************** PMAC测试函数 *****************/
/**
 * @brief Pmac 连接
 */
    void on_btn_pmacTest_Connect_clicked();

/**
 * @brief Pmac 断开
 */
    void on_btn_pmacTest_Close_clicked();

/**
 * @brief 设置 IO 高电平
 */
    void on_btn_ioTest_Open_clicked();

/**
 * @brief 设置 IO 低电平
 */

    void on_btn_ioTest_Close_clicked();

/**
 * @brief PX定速运动
 */
    void on_lbl_motorTest_PX_ConstSpeed_clicked();

/**
 * @brief PR定速运动
 */
    void on_lbl_motorTest_PR_ConstSpeed_clicked();

/**
 * @brief PZ定速运动
 */
    void on_lbl_motorTest_PZ_ConstSpeed_clicked();

/**
 * @brief PX定长运动
 */
    void on_lbl_motorTest_PX_ConstLength_clicked();

/**
 * @brief PR定长运动
 */
    void on_lbl_motorTest_PR_ConstLength_clicked();

/**
 * @brief PZ定长运动
 */
    void on_lbl_motorTest_PZ_ConstLength_clicked();

/**
 * @brief PX停止运动
 */
    void on_lbl_motorTest_PX_Stop_clicked();

/**
 * @brief PR停止运动
 */
    void on_lbl_motorTest_PR_Stop_clicked();


/**
 * @brief PZ停止运动
 */
    void on_lbl_motorTest_PZ_Stop_clicked();

/**
 * @brief 开启监控线程
 */
    void on_btn_threadTest_Open_clicked();

/**
 * @brief PX设置零点
 */
    void on_btn_threadTest_PX_SetZero_clicked();

/**
 * @brief PR设置零点
 */
    void on_btn_threadTest_PR_SetZero_clicked();

/**
 * @brief PZ设置零点
 */
    void on_btn_threadTest_PZ_SetZero_clicked();

/**
 * @brief 使能限位
 */
    void on_btn_motorTest_OpenLimit_clicked();

/**
 * @brief 失能限位
 */
    void on_btn_motorTest_CloseLimit_clicked();

/**
 * @brief 测试函数
 */
    void on_pushButton_clicked();

private:
/**
 * @brief 设置 Label 状态灯颜色
 */
    void setLabelColor(QLabel* label, QString color);

/**
 * @brief 监控线程函数
 */
    void th_threadOpen();

private:
    Ui::MainWindow *ui;
    PmacClass* pmacDevice;
    MotorClass* motorPX;
    MotorClass* motorPZ;
    MotorClass* motorPR;
};




#endif // MAINWINDOW_H

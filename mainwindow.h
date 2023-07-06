#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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



private:
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H

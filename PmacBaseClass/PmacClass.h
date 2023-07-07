#pragma once

#if !defined(AFX_PMACCONTROL_H__AFA2FD3A_3AFA_45FD_93E1_75A9EAB03284__INCLUDED_)
#define AFX_PMACCONTROL_H__AFA2FD3A_3AFA_45FD_93E1_75A9EAB03284__INCLUDED_

#include "pmacserver.h"

// 为了让QT也能使用这个动态库，必须2个下划线！
#ifdef _USRDLL
#define EXPORT_CLASS __declspec(dllexport)
#else
#define EXPORT_CLASS __declspec(dllimport)
#endif


class EXPORT_CLASS PmacClass
{
public:
	PmacClass();
	virtual ~PmacClass();

public:

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    devInit，PMAC 设备连接
	  @param    none
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE devInit();

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    devClose，PMAC 设备断开连接
	  @param    none
	  @return   none
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE devClose();

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    setIOStatus，设置电机IO电平
	  @param    sPin	IO引脚
	  @param    bStatus	使能状态（1：低电平；0：高电平）
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE setIOStatus(short sPin, bool bStatus);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getIOStatus，获取IO状态
	  @param    sPin	IO引脚
	  @return   0 高电平； 1 低电平
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE getIOStatus(short sPin);


public:
	long			testInterface, dwDevice;
	BOOL			pbSuccess;
	static BOOL		pbDriverOpen;
	IPmacDevice*	pmacDevice;
};

#endif
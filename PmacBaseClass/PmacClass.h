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
	  @return   -1 执行异常； 1 执行正常
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
	void devClose();

public:
	long			testInterface, dwDevice;
	BOOL			pbSuccess;
	static BOOL		pbDriverOpen;
	IPmacDevice* pmacDevice;
};

#endif
#pragma once

#if !defined(AFX_PMACCONTROL_H__AFA2FD3A_3AFA_45FD_93E1_75A9EAB03284__INCLUDED_)
#define AFX_PMACCONTROL_H__AFA2FD3A_3AFA_45FD_93E1_75A9EAB03284__INCLUDED_

#include "pmacserver.h"

// Ϊ����QTҲ��ʹ�������̬�⣬����2���»��ߣ�
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
	  @brief    devInit��PMAC �豸����
	  @param    none
	  @return   -1 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE devInit();

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    devClose��PMAC �豸�Ͽ�����
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
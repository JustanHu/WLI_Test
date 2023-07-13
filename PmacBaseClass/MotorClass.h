#pragma once

#include "PmacClass.h"
#include <string>
using namespace std;

class EXPORT_CLASS MotorClass
{
public:
	MotorClass(string motorName);
	virtual ~MotorClass();

public:

	// Motor Setting ����
	/*-------------------------------------------------------------------------*/
	/**
	  @brief    setInitVel�����õ����ʼ�ٶ�
	  @param    sAxis	������
	  @param    dbVel	��ʼ�ٶ�
	  @return   0 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE setInitVel(short sAxis, double dbVel);

	/*-------------------------------------------------------------------------*/
	/**
	@brief    setHomeVel�����õ�������ٶ�
	@param    sAxis	������
	@param    dbVel	��ʼ�ٶ�
	@return   0 ִ���쳣�� 1 ִ������
	*/
	/*--------------------------------------------------------------------------*/
	BYTE setHomeVel(short sAxis, double dbVel);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    setZeroPoint�����ƶ������õ����ǰλ��Ϊ0
	  @param    sAxis	������
	  @return   0 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE setZeroPoint(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    setLimitStatus�����õ����λ�Ƿ�ʹ��
	  @param    sAxis	������
	  @param    bStatus	ʹ��״̬��1��ʹ�ܣ�0��ʧ�ܣ�
	  @return   0 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE setLimitStatus(short sAxis, bool bStatus);


	// Check Status ����
	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getPosStatus����ȡ�����ǰλ��
	  @param    sAxis	������
	  @return   double	���λ��ֵ
	 */
	 /*--------------------------------------------------------------------------*/
	double	getPosStatus(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getVelStatus����ȡ�����ǰ�ٶ�
	  @param    sAxis	������
	  @return   double	����ٶ�ֵ
	 */
	 /*--------------------------------------------------------------------------*/
	double	getVelStatus(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getRunStatus����ȡ����˶�״̬
	  @param    sAxis	������
	  @return   0 �˶��У�1 �˶�����
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE getRunStatus(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getPLimitStatus����ȡ����λ״̬
	  @param    sAxis	������
	  @return   0 δ��λ�� 1 ��λ
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE getPLimitStatus(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getPLimitStatus����ȡ����λ״̬
	  @param    sAxis	������
	  @return   0 δ��λ�� 1 ��λ
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE getNLimitStatus(short sAxis);


	// Motion Control ����
	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleConstSpeedMove�����ᶨ���˶�
	  @param    sAxis	������
	  @param    dbVel	�˶��ٶ�
	  @param    bDir	�˶�����0 ������ 1 ������
	  @return   0 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleConstSpeedMove(short sAxis, double dbVel, bool bDir);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleConstLengthMove�����ᶨ���˶�����ԣ�
	  @param    sAxis	������
	  @param    dbVel	�˶��ٶ�
	  @param    iPos	�˶�����
	  @param    bDir	�˶�����0 ������ 1 ������
	  @return   0 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleConstLengthMove(short sAxis, double dbVel, int iPos, bool bDir);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleConstLengthMoveTo�����ᶨ���˶������ԣ�
	  @param    sAxis	������
	  @param    dbVel	�˶��ٶ�
	  @param    iPos	�˶�����
	  @param    bDir	�˶�����0 ������ 1 ������
	  @return   0 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleConstLengthMoveTo(short sAxis, double dbVel, int iPos, bool bDir);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleHome����������˶�
	  @param    sAxis	������
	  @return   0 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleHome();

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleStop���������˶�ֹͣ
	  @param    sAxis	������
	  @return   0 ִ���쳣�� 1 ִ������
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleStop(short sAxis);

public:
	short	axisNumber;		// ���
	int		initSpeed;		// ��ʼ�ٶ�
	int		homeSpeed;		// �����ٶ�
	double	rev;			// �ֱ���

};

//#endif
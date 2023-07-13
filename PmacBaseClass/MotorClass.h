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

	// Motor Setting 部分
	/*-------------------------------------------------------------------------*/
	/**
	  @brief    setInitVel，设置电机初始速度
	  @param    sAxis	电机轴号
	  @param    dbVel	初始速度
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE setInitVel(short sAxis, double dbVel);

	/*-------------------------------------------------------------------------*/
	/**
	@brief    setHomeVel，设置电机回零速度
	@param    sAxis	电机轴号
	@param    dbVel	初始速度
	@return   0 执行异常； 1 执行正常
	*/
	/*--------------------------------------------------------------------------*/
	BYTE setHomeVel(short sAxis, double dbVel);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    setZeroPoint，无移动地设置电机当前位置为0
	  @param    sAxis	电机轴号
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE setZeroPoint(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    setLimitStatus，设置电机限位是否使能
	  @param    sAxis	电机轴号
	  @param    bStatus	使能状态（1：使能；0：失能）
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE setLimitStatus(short sAxis, bool bStatus);


	// Check Status 部分
	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getPosStatus，获取电机当前位置
	  @param    sAxis	电机轴号
	  @return   double	电机位置值
	 */
	 /*--------------------------------------------------------------------------*/
	double	getPosStatus(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getVelStatus，获取电机当前速度
	  @param    sAxis	电机轴号
	  @return   double	电机速度值
	 */
	 /*--------------------------------------------------------------------------*/
	double	getVelStatus(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getRunStatus，获取电机运动状态
	  @param    sAxis	电机轴号
	  @return   0 运动中；1 运动结束
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE getRunStatus(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getPLimitStatus，获取正限位状态
	  @param    sAxis	电机轴号
	  @return   0 未限位； 1 限位
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE getPLimitStatus(short sAxis);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    getPLimitStatus，获取负限位状态
	  @param    sAxis	电机轴号
	  @return   0 未限位； 1 限位
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE getNLimitStatus(short sAxis);


	// Motion Control 部分
	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleConstSpeedMove，单轴定速运动
	  @param    sAxis	电机轴号
	  @param    dbVel	运动速度
	  @param    bDir	运动方向（0 负方向； 1 正方向）
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleConstSpeedMove(short sAxis, double dbVel, bool bDir);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleConstLengthMove，单轴定长运动（相对）
	  @param    sAxis	电机轴号
	  @param    dbVel	运动速度
	  @param    iPos	运动距离
	  @param    bDir	运动方向（0 负方向； 1 正方向）
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleConstLengthMove(short sAxis, double dbVel, int iPos, bool bDir);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleConstLengthMoveTo，单轴定长运动（绝对）
	  @param    sAxis	电机轴号
	  @param    dbVel	运动速度
	  @param    iPos	运动距离
	  @param    bDir	运动方向（0 负方向； 1 正方向）
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleConstLengthMoveTo(short sAxis, double dbVel, int iPos, bool bDir);

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleHome，单轴回零运动
	  @param    sAxis	电机轴号
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleHome();

	/*-------------------------------------------------------------------------*/
	/**
	  @brief    singleStop，单轴电机运动停止
	  @param    sAxis	电机轴号
	  @return   0 执行异常； 1 执行正常
	 */
	 /*--------------------------------------------------------------------------*/
	BYTE singleStop(short sAxis);

public:
	short	axisNumber;		// 轴号
	int		initSpeed;		// 初始速度
	int		homeSpeed;		// 回零速度
	double	rev;			// 分辨率

};

//#endif
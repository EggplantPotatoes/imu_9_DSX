/*
 * attitude_algorithm.c
 *
 *  Created on: Jan 25, 2024
 *      Author: smile
 */

#include "math.h"
#include "attitude_algorithm.h"
#include "imu_9.h"
#include "stdio.h"
#include "data_filter.h"
#include "debug.h"

// 互补滤波参数
#define ALPHA 0.98 // 加速度计和磁力计权重
#define BETA 0.02 // 陀螺仪权重

// Kalman filter parameters
#define Q_angle 0.001
#define Q_gyro 0.003
#define Q_mag 0.01
#define R_angle 0.03

#define RAD_TO_DEG 57.2957795131f
#define DT  0.001f


/*
偏航角（Yaw）
绕着Z轴旋转，向右转动为正(逆时针方向为正)。。

俯仰角（Pitch）
绕着X轴旋转，抬头为正(y轴正方向为头)。

横滚角（Roll）
绕着Y轴旋转，向右转动为正(x轴正方向为右)。
*/


Out_Euler out_euler;

//加速度计，陀螺仪互补滤波得到倾角
Out_Euler complementaryFilter(AXIS gyr, AXIS acc)
{
	Out_Euler euler;

	static float roll = 0.0f;
	static float pitch = 0.0f;
	static float yaw = 0.0f;

    // 加速度计测量值转换为欧拉角（俯仰角和横滚角）
	float accelRoll = atan2(acc.y, acc.z) * RAD_TO_DEG;
	float accelPitch = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z)) * RAD_TO_DEG;
//	float accelYaw = 0.0;  // 加速度计无法直接测量偏航角

    // 陀螺仪积分计算欧拉角变化率
	float gyroRollRate = gyr.x;
	float gyroPitchRate = gyr.y;
	float gyroYawRate = gyr.z;
    // 使用互补滤波器融合传感器数据
    roll = ALPHA * (roll + gyroRollRate * DT) + (1 - ALPHA) * accelRoll;
    pitch = ALPHA * (pitch + gyroPitchRate * DT) + (1 - ALPHA) * accelPitch;

    euler.pitch  = pitch;
    euler.roll = roll;

    return euler;
}

void complementary_get_euler(void)
{
	AXIS gyr,acc;


	gyr.x = imu_9.f_gyro[0];
	gyr.y = imu_9.f_gyro[1];
	gyr.z = imu_9.f_gyro[2];

	acc.x = imu_9.f_acc[0];
	acc.y = imu_9.f_acc[1];
	acc.z = imu_9.f_acc[2];

	out_euler  = complementaryFilter(gyr,acc); //得到输出角度
	//输出
//	vofa_JustFloat_USB_output(out_euler.roll, out_euler.pitch, out_euler.yaw,0);
}



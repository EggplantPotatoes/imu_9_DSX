#ifndef _ATTITUDE_H
#define _ATTITUDE_H

#include "main.h"

#ifndef XYZ_Data
#define XYZ_Data
typedef struct XYZ_Data_f
{
	float x;
	float y;
	float z;
}XYZ_Data_f;

typedef struct XYZ_Data_s32
{
	long x;
	long y;
	long z;
}XYZ_Data_s32;

typedef struct XYZ_Data_s16
{
	short x;
	short y;
	short z;
}XYZ_Data_s16;

typedef struct XYZ_Data_s8
{
	char x;
	char y;
	char z;
}XYZ_Data_s8;
#endif

////////////////////////////////////////////////////
typedef struct Pose_Flag
{
	uint8_t run;
	uint8_t use_mag;
}Flag;
////////////////////////////////////////////////////
typedef struct Pose_DInterface
{
	float a_x;
	float a_y;
	float a_z;
	
	float g_x;
	float g_y;
	float g_z;
	
	float m_x;
	float m_y;
	float m_z;
}DATA_IN;

typedef struct Pose_Interface
{
	DATA_IN data;
}Pose_Interface;
////////////////////////////////////////////////////
typedef struct Pose_Data
{
	float yaw;
	float rol;
	float pitch;
	
	float rotate_matrix[3][3];	//旋转矩阵
	
	XYZ_Data_f acc_world;				//世界坐标系下的加速度
	XYZ_Data_f mag_world;				//世界坐标系下的磁场强度	--	只与无人机位置有关的量
	
	XYZ_Data_f acc_correct;			//机体坐标系下的加速度	--	矫正了俯仰翻滚后的加速度
	XYZ_Data_f mag_correct;			//机体坐标系下的磁场强度	--	矫正了俯仰翻滚后的磁场强度
	XYZ_Data_f gyro_correct;		//融合加速度和磁力计数据，矫正后的陀螺仪值
}Pose_Data;
////////////////////////////////////////////////////
typedef struct Pose_Process
{
	float mag_yaw;							//磁力计的偏航角
	float mag_yaw_bias;					//磁力计矫正的偏航角偏差
	float quaternion[4];				//四元数
	XYZ_Data_f error;						//由加速度计与等效重力的偏差
	XYZ_Data_f error_integral;	//误差积分
}Pose_Process;
////////////////////////////////////////////////////
typedef struct Pose_Parameter
{
	float correct_kp;
	float error_kp;
	float error_ki;
}Pose_Parameter;
////////////////////////////////////////////////////
typedef struct Pose_Module
{
	Flag flag;
	Pose_Interface interface;
	Pose_Process process;
	Pose_Data data;
	Pose_Parameter parameter;
}ATT_Module;

extern ATT_Module attitude;

//初始化结构体
void init_attitude(ATT_Module *pose);
//计算姿态
void calculate_attitude(ATT_Module *attitude, float cycle);
#endif


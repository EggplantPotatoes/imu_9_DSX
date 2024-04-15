/*
 * imu_9.c
 *
 *  Created on: Jan 23, 2024
 *      Author: smile
 */

#include "imu_9.h"
#include "stdio.h"
#include "data_filter.h"
#include "debug.h"
#include "attitude_algorithm.h"
#include "in_flash.h"
#include "attitude.h"



extern TIM_HandleTypeDef htim2;

imu_t imu_9;


int16_t window_ax[WIN_NUM];
int16_t window_ay[WIN_NUM];
int16_t window_az[WIN_NUM];

int16_t window_gx[WIN_NUM];
int16_t window_gy[WIN_NUM];
int16_t window_gz[WIN_NUM];

int16_t window_mx[WIN_NUM];
int16_t window_my[WIN_NUM];
int16_t window_mz[WIN_NUM];


void read_flash_information(void)
{

	STMFLASH_Read(ACC_ZERO_ADDR,(uint8_t*)&imu_9.acc_zero,6); //读取加速度零点
	STMFLASH_Read(GYRO_ZERO_ADDR,(uint8_t*)&imu_9.gyro_zero,6); //读取陀螺仪零点
	STMFLASH_Read(MAG_ZERO_ADDR,(uint8_t*)&imu_9.mag_zero,6);  //读取磁力计零点

    if(imu_9.acc_zero[0]==-1) //默认0点是0
    {
    	imu_9.acc_zero[0] = 0;
    }
    if(imu_9.acc_zero[1]==-1)
    {
    	imu_9.acc_zero[1] = 0;
    }
    if(imu_9.acc_zero[2]==-1)
    {
    	imu_9.acc_zero[2] = 0;
    }

    if(imu_9.gyro_zero[0]==-1)
    {
    	imu_9.gyro_zero[0] = 0;
    }
    if(imu_9.gyro_zero[1]==-1)
    {
    	imu_9.gyro_zero[1] = 0;
    }
    if(imu_9.gyro_zero[2]==-1)
    {
    	imu_9.acc_zero[2] = 0;
    }

//    if(imu_9.mag_zero[0]==-1)
//    {
//    	imu_9.mag_zero[0] = 0;
//    }
//    if(imu_9.mag_zero[1]==-1)
//    {
//    	imu_9.mag_zero[1] = 0;
//    }
//    if(imu_9.mag_zero[2]==-1)
//    {
//    	imu_9.mag_zero[2] = 0;
//    }


    STMFLASH_Read(OUTPUT_ADDR,(uint8_t*)&imu_9.output_mode,1); //读取数据输出模式
    if(imu_9.output_mode==0xFF)
    {
    	imu_9.output_mode = 0; //默认欧拉角输出
    }

}


void imu_init(void)
{
	uint8_t test_id_ag = 0;
	uint8_t test_id_mag = 0;
	test_id_ag = acc_gyro_init();
    test_id_mag = mag_init();

    read_flash_information();
    init_attitude(&attitude);

    HAL_Delay(100);
    HAL_TIM_Base_Start_IT(&htim2);
}


void imu_sample_data(void)
{
	acc_gyro_sample_data(imu_9.i_gyro,imu_9.i_acc);
	mag_sample_data(imu_9.i_mag);

//    usb_printf("gyro_x=%d , gyro_y=%d,gyro_z=%d\r\n",imu_9.i_gyro[0],imu_9.i_gyro[1],imu_9.i_gyro[2]);
//    usb_printf("acc_x=%d , acc_y=%d,acc_z=%d\r\n",imu_9.i_acc[0],imu_9.i_acc[1],imu_9.i_acc[2]);
//    usb_printf("mag_x=%d , mag_y=%d,mag_z=%d\r\n",imu_9.i_mag[0],imu_9.i_mag[1],imu_9.i_mag[2]);
//	usb_printf("\r\n");
}

//将九轴数据转换为实际物理数据
void imu_data_transition(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz,int16_t mx,int16_t my,int16_t mz)
{

	imu_9.f_acc[0] = (float)(ax-imu_9.acc_zero[0])/ 16393.0f;  // 加速度量程为:±2G      获取到的加速度计数据 除以 16393 ，可以转化为带物理单位的数据，单位：g(m/s^2)
	imu_9.f_acc[1] = (float)(ay-imu_9.acc_zero[1]) / 16393.0f;
	imu_9.f_acc[2] = (float)(az-imu_9.acc_zero[2]) / 16393.0f;

	imu_9.f_gyro[0] = (float)(gx-imu_9.gyro_zero[0]) / 57.1f; //  陀螺仪量程为:±500dps  获取到的陀螺仪数据除以 57.1，    可以转化为带物理单位的数据，单位为：°/s
	imu_9.f_gyro[1] = (float)(gy-imu_9.gyro_zero[1]) / 57.1f;
	imu_9.f_gyro[2] = (float)(gz-imu_9.gyro_zero[2]) / 57.1f;

	imu_9.f_mag[0] = (float)(mx+imu_9.mag_zero[0]) * 1.5f;
	imu_9.f_mag[1] = (float)(my+imu_9.mag_zero[1]) * 1.5f;
	imu_9.f_mag[2] = (float)(mz+imu_9.mag_zero[2]) * 1.5f;



}

void imu_final_data_get(void)
{
	int16_t filter_ax ,filter_ay,filter_az ;
	int16_t filter_gx ,filter_gy,filter_gz ;
	int16_t filter_mx ,filter_my,filter_mz ;

	  imu_sample_data(); //采样得到九轴原始数据
	  //原始数据窗口滤波
	  filter_ax = window_filter(imu_9.i_acc[0],window_ax,WIN_NUM);
	  filter_ay = window_filter(imu_9.i_acc[1],window_ay,WIN_NUM);
	  filter_az = window_filter(imu_9.i_acc[2],window_az,WIN_NUM);

	  filter_gx = window_filter(imu_9.i_gyro[0],window_gx,WIN_NUM);
	  filter_gy = window_filter(imu_9.i_gyro[1],window_gy,WIN_NUM);
	  filter_gz = window_filter(imu_9.i_gyro[2],window_gz,WIN_NUM);

	  filter_mx = window_filter(imu_9.i_mag[0],window_mx,WIN_NUM);
	  filter_my = window_filter(imu_9.i_mag[1],window_my,WIN_NUM);
	  filter_mz = window_filter(imu_9.i_mag[2],window_mz,WIN_NUM);
	  //转换成实际物理量
	  imu_data_transition(filter_ax,filter_ay,filter_az,filter_gx,filter_gy,filter_gz,filter_mx,filter_my,filter_mz);

}


void imu_9_shell_cmd_to_do(void)
{
	if(imu_9.shell_cmd_ok==1)
	{
		imu_9.shell_cmd_ok = 0;
	    if(imu_9.cali_flag!=0)  //校准
	    {
	    	if(imu_9.cali_flag==1)
	    	{
	    		set_acc_gyro_offset();
	    		imu_9.cali_flag = 0;
	    	}
	    	else if(imu_9.cali_flag==2)
	    	{
	    		mag_set_offset();
	    		imu_9.cali_flag = 0;
	    	}
	    }
	    if(imu_9.output_flag!=0)  //数据输出
	    {
	    	STMFLASH_Write(OUTPUT_ADDR,&imu_9.output_mode,1);
	    	imu_9.output_flag = 0;
	    }

	}

}

void data_output_mode(uint8_t mode)  //数据输出模式,vofa+查看曲线图形
{
	switch(mode)
	{
	case 0:  //欧拉角输出
		vofa_FireWater_USB_output(attitude.data.rol, attitude.data.pitch, attitude.data.yaw,0.0f);
		break;
	case 1: //四元数输出
		vofa_FireWater_USB_output(attitude.process.quaternion[0],attitude.process.quaternion[1],attitude.process.quaternion[2],attitude.process.quaternion[3]);

		break;
	case 2://世界加速度输出
		vofa_FireWater_USB_output(attitude.data.acc_world.x,attitude.data.acc_world.y,attitude.data.acc_world.z,2.0f);
		break;
	case 3://加速度 数据输出  单位：g(m/s^2)
		vofa_FireWater_USB_output(imu_9.f_acc[0],imu_9.f_acc[1],imu_9.f_acc[2],3.0f);
		break;
	case 4://陀螺仪数据输出  单位为：°/s
		vofa_FireWater_USB_output(imu_9.f_gyro[0],imu_9.f_gyro[1],imu_9.f_gyro[2],4.0f);
		break;
	case 5://地磁数据输出
		vofa_FireWater_USB_output(imu_9.f_mag[0],imu_9.f_mag[1],imu_9.f_mag[2],5.0f);
		break;
	case 6://地磁数据输出
		usb_printf("simples:%f,%f,%f,%f,%f,%f,%f,%f,%f\n",imu_9.f_acc[0],imu_9.f_acc[1],imu_9.f_acc[2],imu_9.f_gyro[0],imu_9.f_gyro[1],imu_9.f_gyro[2],imu_9.f_mag[0],imu_9.f_mag[1],imu_9.f_mag[2]);
		break;
	default:

		break;
	}

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint16_t TimerCount = 0;
	float mag_yaw_test;
	if (htim == (&htim2))  //
	{
		TimerCount++;
		if(TimerCount >= 1)  //1ms采集一次传感器数据  1KHz
		{
			if(imu_9.cali_flag==0) //校准时不采集输出
			{
				HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin); //测试引脚PA7，可使用示波器测量，确定采样时间是否准确
				imu_final_data_get(); //原始数据采样
				calculate_attitude(&attitude, 0.001) ; //姿态解算
//				mag_yaw_test = atan2(imu_9.f_mag[1],imu_9.f_mag[0])*57.2957795131f;

				data_output_mode(imu_9.output_mode);  //数据输出,vofa+查看曲线图形
			}

			TimerCount = 0;
		}

	}

}

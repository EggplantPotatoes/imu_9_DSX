/*
 * acc_gry.c
 *
 *  Created on: Jan 22, 2024
 *      Author: smile
 */

#include "acc_gry.h"
#include "IIC_bus.h"
#include "imu_9.h"
#include "in_flash.h"

reg_cfg_t acc_gyro_init_reg[20] =
{
		{ CTRL3_C, 0x01 },
		{ CTRL3_C, 0x44 },
		{ CTRL1_XL, ODR_1660HZ | ACC_SCALE_2g | 0x02 },
		{ CTRL8_XL, 0xa8 },
		{ CTRL2_G, ODR_1660HZ | GRY_SCALE_500},
};
/**
 * @brief  imu初始化
 * @author
 * @param  void
 * @return 0-成功 1-失败
 */
uint8_t acc_gyro_init(void)
{
	uint8_t id = 0;
	uint8_t cfg_index = 0;

	BSP_I2C3_ReadReg(LSM6DS3_ADDR, WHO_AM_I, &id, 1);

    for (cfg_index=0; cfg_index<sizeof(acc_gyro_init_reg)/sizeof(reg_cfg_t); cfg_index++)
    {
    	if(acc_gyro_init_reg[cfg_index].reg==0&&acc_gyro_init_reg[cfg_index].dat==0)
    	{
    		continue;
    	}
    	BSP_I2C3_WriteReg(LSM6DS3_ADDR,acc_gyro_init_reg[cfg_index].reg, &acc_gyro_init_reg[cfg_index].dat,1);
        HAL_Delay(1);

    }

	return id;
}

/**
 * @brief  6轴采样
 * @author
 * @param  gyro-脱落仪数据 acc-加速度数据
 * @return void
 */
void acc_gyro_sample_data(int16_t *gyro,int16_t *acc )
{
	uint8_t r_data[6];

	BSP_I2C3_ReadReg(LSM6DS3_ADDR, ACCEL_XOUT_L, r_data, 6);

	acc[0] = (int16_t)(r_data[0] + (r_data[1] << 8));
	acc[1] = (int16_t)(r_data[2] + (r_data[3] << 8));
	acc[2] = (int16_t)(r_data[4] + (r_data[5] << 8));

	BSP_I2C3_ReadReg(LSM6DS3_ADDR, GYRO_XOUT_L, r_data, 6);
	gyro[0] = (int16_t)(r_data[0] + (r_data[1] << 8));
	gyro[1] = (int16_t)(r_data[2] + (r_data[3] << 8));
	gyro[2] = (int16_t)(r_data[4] + (r_data[5] << 8));



}


void set_acc_gyro_offset(void)
{
    uint8_t i;
    int16_t ax_offset, ay_offset, az_offset, gx_offset, gy_offset, gz_offset;
    int32_t ax_offset_sum, ay_offset_sum, az_offset_sum, gx_offset_sum, gy_offset_sum, gz_offset_sum;
    int16_t gyro_off[3],acc_off[3];

    ax_offset_sum = 0;
    ay_offset_sum = 0;
    az_offset_sum = 0;
    gx_offset_sum = 0;
    gy_offset_sum = 0;
    gz_offset_sum = 0;

    for (i = 0; i < 20; i++)
   {
	  acc_gyro_sample_data(gyro_off,acc_off);

	   ax_offset = acc_off[0];
	   ay_offset = acc_off[1];
	   az_offset = acc_off[2];
	   ax_offset_sum = ax_offset_sum + ax_offset;
	   ay_offset_sum = ay_offset_sum + ay_offset;
	   az_offset_sum = az_offset_sum + az_offset;

	   gx_offset = gyro_off[0];
	   gy_offset = gyro_off[1];
	   gz_offset = gyro_off[2];
	   gx_offset_sum = gx_offset_sum + gx_offset;
	   gy_offset_sum = gy_offset_sum + gy_offset;
	   gz_offset_sum = gz_offset_sum + gz_offset;
   }
    imu_9.acc_zero[0] = ax_offset_sum/20;
    imu_9.acc_zero[1] = ay_offset_sum/20;
    imu_9.acc_zero[2] = az_offset_sum/20 - 16384;
    imu_9.gyro_zero[0] = gx_offset_sum/20;
    imu_9.gyro_zero[1] = gy_offset_sum/20;
    imu_9.gyro_zero[2] = gz_offset_sum/20;

    //存入
    STMFLASH_Write(ACC_ZERO_ADDR,(uint8_t*)&imu_9.acc_zero,6);
    STMFLASH_Write(GYRO_ZERO_ADDR,(uint8_t*)&imu_9.gyro_zero,6);





}

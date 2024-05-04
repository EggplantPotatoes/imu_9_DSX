/*
 * magnetic.c
 *
 *  Created on: Jan 22, 2024
 *      Author: smile
 */

#include "magnetic.h"
#include "IIC_bus.h"
#include "imu_9.h"
#include "in_flash.h"

reg_cfg_t mag_init_reg[10] =
{
		{LIS2MDL_CFG_REG_A,LIS2MDL_CFGA_TEMP_EN | LIS2MDL_CFGA_ODR_100HZ | LIS2MDL_CFGA_MODE_CONTINUE},/* 温度补偿,100HZ,连续模式 */
		{LIS2MDL_CFG_REG_B,LIS2MDL_CFGB_OFF_CANC_EN | LIS2MDL_CFGB_LPF_EN},/* 偏移抵消,启用低通滤波 */
		{LIS2MDL_CFG_REG_C,LIS2MDL_CFGC_BDU}, /* 开启数据完整性保护 */

};




void mag_sample_offset_data(int16_t *mag_offset ) //读零点
{

	uint8_t r_data[6];

	BSP_I2C1_ReadReg(LIS2MDL_I2C_ADD, LIS2MDL_OFFSET_X_REG_L, r_data, 6);

	mag_offset[0] = (int16_t)(r_data[0] + (r_data[1] << 8));
	mag_offset[1] = (int16_t)(r_data[2] + (r_data[3] << 8));
	mag_offset[2] = (int16_t)(r_data[4] + (r_data[5] << 8));

}



void mag_Write_Offset(int16_t x_offset,int16_t y_offset,int16_t z_offset)  //写零点
{
	uint8_t w_buf[6];

	w_buf[0] =  x_offset & 0xFF;
	w_buf[1] = (x_offset >> 8) & 0xFF;
	w_buf[2] =  y_offset & 0xFF;
	w_buf[3] = (y_offset >> 8) & 0xFF;
	w_buf[4] =  z_offset & 0xFF;
	w_buf[5] = (z_offset >> 8) & 0xFF;


	BSP_I2C1_WriteReg(LIS2MDL_I2C_ADD,LIS2MDL_OFFSET_X_REG_L, w_buf,6);
}


void software_Delay(uint32_t ms)
{
    uint32_t Delay = ms * 20;
    do
    {
        __NOP();
    }
    while (Delay --);
}

static void mag_wait_data_update(void)
{
	uint8_t sta = 0;
	while((sta & 0x08)==0)
	{
		BSP_I2C1_ReadReg(LIS2MDL_I2C_ADD,LIS2MDL_STATUS_REG,&sta,1);
		software_Delay(2);
	}
}



void mag_sample_data(int16_t *mag )
{
	uint8_t r_data[6];
//	mag_wait_data_update();
	BSP_I2C1_ReadReg(LIS2MDL_I2C_ADD, LIS2MDL_OUTX_L_REG, r_data, 6);  //读地磁原始数据
    mag[0] = (int16_t)(r_data[0] + (r_data[1] << 8));
	mag[1] = (int16_t)(r_data[2] + (r_data[3] << 8));
	mag[2] = (int16_t)(r_data[4] + (r_data[5] << 8));



}

uint8_t mag_init(void)
{
	uint8_t id = 0;
	uint8_t cfg_index = 0;
	uint8_t read_reg_data[3];
	int16_t mag_hard_iron[3];

	BSP_I2C1_ReadReg(LIS2MDL_I2C_ADD, LIS2MDL_WHO_AM_I, &id, 1);//

    for (cfg_index=0; cfg_index<sizeof(mag_init_reg)/sizeof(reg_cfg_t); cfg_index++) //写配置寄存器
    {
    	if(mag_init_reg[cfg_index].reg==0&&mag_init_reg[cfg_index].dat==0)
    	{
    		continue;
    	}
    	BSP_I2C1_WriteReg(LIS2MDL_I2C_ADD,mag_init_reg[cfg_index].reg, &mag_init_reg[cfg_index].dat,1);
        HAL_Delay(1);
    }
      BSP_I2C1_ReadReg(LIS2MDL_I2C_ADD,LIS2MDL_CFG_REG_A,read_reg_data,3);/* 回读寄存器校验 */
      HAL_Delay(20);

//      mag_sample_data(mag_hard_iron);

//      mag_Write_Offset(mag_hard_iron[0],mag_hard_iron[1],mag_hard_iron[2]);

	return id;
}


int16_t mag_x_max=0,mag_x_min=0;
int16_t mag_y_max=0,mag_y_min=0;
int16_t mag_z_max=0,mag_z_min=0;



/*校准过程
 * 一段时间内连续采集地磁xyz三个轴向上的最大值和最小值，做运算
 *
 */
void mag_set_offset(void)
{

	uint32_t cnt = 0;
	uint8_t r_data[6];
	int16_t mag_off[3];
	int16_t Xoffset,Yoffset,Zoffset;

	static float Xsf;
	static float Ysf;

    int16_t xsf_buf,ysf_buf;

	while(cnt<MAG_OFFSET_TIMES)
	{
		cnt++;
		BSP_I2C1_ReadReg(LIS2MDL_I2C_ADD, LIS2MDL_OUTX_L_REG, r_data, 6);  //读地磁原始数据
		mag_off[0] = (int16_t)(r_data[0] + (r_data[1] << 8));
		mag_off[1] = (int16_t)(r_data[2] + (r_data[3] << 8));
		mag_off[2] = (int16_t)(r_data[4] + (r_data[5] << 8));

        if(mag_off[0]<mag_x_min)
        	mag_x_min = mag_off[0];
        else if(mag_off[0]>mag_x_max)
        	mag_x_max = mag_off[0];


        if(mag_off[1]<mag_y_min)
        	mag_y_min = mag_off[1];
        else if(mag_off[1]>mag_y_max)
        	mag_y_max = mag_off[1];

            if(mag_off[2]<mag_z_min)
            	mag_z_min = mag_off[2];
        else if(mag_off[2]>mag_z_max)
        	mag_z_max = mag_off[2];

        HAL_Delay(1);
	}
	cnt = 0;

    Xsf = (mag_y_max - mag_y_min) / (mag_x_max - mag_x_min);
    Ysf = (mag_x_max - mag_x_min) / (mag_y_max - mag_y_min);

    if (Xsf < 1)
    {
    	Xsf = 1;
    }

    if (Ysf < 1)
    {
    	Ysf = 1;
    }

    Xoffset = ( (mag_x_max - mag_x_min)/2 - mag_x_max) *Xsf;
    Yoffset = ( (mag_y_max - mag_y_min)/2 - mag_y_max) *Ysf;
//    Zoffset = ( (mag_z_max-mag_z_min)/2 - mag_z_max) *Xsf;

    imu_9.mag_xsf = Xsf;
    imu_9.mag_ysf = Ysf;

    imu_9.mag_zero[0] = Xoffset;
    imu_9.mag_zero[1] = Yoffset;
//    imu_9.mag_zero[2] = Zoffset;
    imu_9.mag_zero[2] = 0.0f;

    xsf_buf =(uint16_t) (Xsf*1000);
    ysf_buf =(uint16_t) (Ysf*1000);

	    //存入
	STMFLASH_Write(MAG_ZERO_ADDR,(uint8_t*)&imu_9.mag_zero,6);
	STMFLASH_Write(MAG_OFFSET_XSF_ADDR,(uint8_t*)&xsf_buf,2);
	STMFLASH_Write(MAG_OFFSET_YSF_ADDR,(uint8_t*)&ysf_buf,2);

}


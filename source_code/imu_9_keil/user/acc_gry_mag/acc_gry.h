/*
 * acc_gry.h
 *
 *  Created on: Jan 22, 2024
 *      Author: smile
 */

#ifndef ACC_GRY_H_
#define ACC_GRY_H_

#include "main.h"

#define LSM6DS3_GYRO_LSB 0.0175 //����500dpsʱ��Ӧ����,��λdps
#define LSM6DS3_ACC_LSB 0.061	//����Ϊ2gʱ��Ӧ����,��λmg

#define LSM6DS3_ADDR 0XD4
#define LSM6DS3TRC_ID 0X6A
#define LSM6DS3_ID 0X69

// CTRL1_XL bits Set
#define POWER_DOWN 0X00
#define ODR_208HZ 0X50
#define ODR_416HZ 0X60
#define ODR_833HZ 0X70
#define ODR_1660HZ 0X80
#define ODR_3330HZ 0X90
#define ODR_6660HZ 0XA0

#define ACC_SCALE_2g 0X00
#define ACC_SCALE_16g 0X04
#define ACC_SCALE_4g 0X08
#define ACC_SCALE_8g 0X0C

#define ACC_BW_400HZ 0X00
#define ACC_BW_200HZ 0X01
#define ACC_BW_100HZ 0X02
#define ACC_BW_50HZ 0X03
// CTRL2_G bits Set
#define GRY_SCALE_245 0X00
#define GRY_SCALE_500 0X04
#define GRY_SCALE_1K 0X08
#define GRY_SCALE_2K 0X0C
#define GRY_SCALE_125 0X02
// CTRL7_G bits Set
#define HP_G_EN 0X40
#define HP_CUTOFF_0081 0X00
#define HP_CUTOFF_0324 0X01
#define HP_CUTOFF_2Hz 0X02
#define HP_CUTOFF_16Hz 0X03
// CTRL8_XL bits
#define LPF2_XL_EN 0X80
#define HPCF_XL1 0X40
#define HPCF_XL0 0X20
#define HP_SLOPE_XL_EN 0X04
#define LOW_PASS_ON_6D 0X01
// CTRL9_XL bits
#define SOFT_EN 0X04
// CTRL10_C bits
#define FUNC_EN 0X04
// STATUS_REG BITS
#define EV_BOOT 0X08 // 0-not boot running
#define TDA 0X04	 // 0-not available at temperature sensor output
#define GDA 0X02	 // 0-not available at gyroscope output
#define XLDA 0X01	 // 0-not available at accelerometer output

// register mapping
#define WHO_AM_I 0X0F
#define CTRL1_XL 0X10
#define CTRL2_G 0X11
#define CTRL3_C 0X12
#define CTRL4_C 0X13
#define CTRL6_C 0X15
#define CTRL7_G 0X16
#define CTRL8_XL 0X17
#define CTRL9_XL 0X18
#define CTRL10_C 0X19
#define TEMP_OUT_L 0X20
#define TEMP_OUT_H 0X21
#define STATUS_REG 0X1E
#define GYRO_XOUT_L 0X22
#define GYRO_XOUT_H 0X23
#define GYRO_YOUT_L 0X24
#define GYRO_YOUT_H 0X25
#define GYRO_ZOUT_L 0X26
#define GYRO_ZOUT_H 0X27
#define ACCEL_XOUT_L 0X28
#define ACCEL_XOUT_H 0X29
#define ACCEL_YOUT_L 0X2A
#define ACCEL_YOUT_H 0X2B
#define ACCEL_ZOUT_L 0X2C
#define ACCEL_ZOUT_H 0X2D
#define TAP_CFG 0X58







uint8_t acc_gyro_init(void);
void acc_gyro_sample_data(int16_t *gyro,int16_t *acc);
void set_acc_gyro_offset(void);
#endif /* ACC_GRY_H_ */

/*
 * imu_9.h
 *
 *  Created on: Jan 23, 2024
 *      Author: smile
 */

#ifndef IMU_9_H_
#define IMU_9_H_

#include "main.h"
#include "acc_gry.h"
#include "magnetic.h"


#define USE_FUSION    0


#define MOTION_THRESHOLD  1.025f




typedef struct
{
	int16_t i_gyro[3];
	int16_t i_acc[3];
	int16_t i_mag[3];
	float f_gyro[3];
	float f_acc[3];
	float f_mag[3];
	float mag_xsf;
	float mag_ysf;
	int16_t gyro_zero[3];
	int16_t acc_zero[3];
	int16_t mag_zero[3];

	float pitch;
	float roll;
	float yaw;
	float mag_yaw_test;
	float yaw_temp;
	float velocity[3];
	float displacement[3];
	uint8_t cali_flag;
	float accelerationMagnitude;
	uint8_t shell_cmd_ok;
	uint8_t output_mode;
	uint8_t output_flag;
	uint16_t output_freq;
	uint32_t time_tick;

} imu_t;

extern imu_t imu_9;

void imu_init(void);
void imu_sample_data(void);
void imu_final_data_get(void);
void Kalman_cal_yaw_angle(void);
void imu_9_shell_cmd_to_do(void);
void data_output_mode(uint8_t mode);
#endif /* imu_9_H_ */

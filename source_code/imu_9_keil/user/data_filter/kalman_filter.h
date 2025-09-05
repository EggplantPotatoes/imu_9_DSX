/*
 * kalman_filter.h
 *
 *  Created on: Mar 4, 2024
 *      Author: smile
 */

#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_

#include "main.h"

#define KALMAN_DT  0.001;

typedef struct
{
  float p;
  float q;//过程噪声协方差
  float r;//测量噪声协方差
  float k;//卡尔曼增益
  float pre_x;//先验预测
  float x;//输出值
} Kalman_node;

extern Kalman_node  kalman_this_time, kalman_last_time;

void kalman_init(void);
void loop_kalman(float gyro_z,float magYaw,float kalman_dt );

#endif /* KALMAN_FILTER_H_ */

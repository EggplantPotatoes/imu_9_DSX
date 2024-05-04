/*
 * kalman_filter.c
 *
 *  Created on: Mar 4, 2024
 *      Author: smile
 */

#include "kalman_filter.h"
#include "imu_9.h"
#include "math.h"

Kalman_node  kalman_this_time, kalman_last_time;


float a; //地磁偏角α,通过查表得到

void kalman_init(void)
{

    a=0;//地磁偏角α,通过查表得到,查表过程从略

    //初始化卡尔曼时间节点
    //本次时间
    kalman_this_time.k=0;
    kalman_this_time.p=0;
    kalman_this_time.q = 0.0001;   //过程噪声方差,经验值是0.0025-0.003
    kalman_this_time.r = 0.01f;   //测量噪声方差,经验值是0.001

    //上一次时间
    kalman_last_time.k=0;
    kalman_last_time.p=1;
    kalman_last_time.q = kalman_this_time.q;
    kalman_last_time.r = kalman_this_time.r;
    kalman_last_time.x = 0.0f; //给一个初始值,假定是地磁的数值
}

////第三层处理角速度和地磁数据融合,如果把角速度来源改为车轮,也可以得到地磁和车轮的数据融合.
void loop_kalman(float gyro_z,float magYaw,float kalman_dt )//
{
    //卡尔曼先验预测 pre_x
     kalman_this_time.pre_x = kalman_last_time.x + gyro_z * kalman_dt; //计算先验预测=上一时刻的卡尔曼输出值+当前时刻角速度(dω)*测量周期(dt)
    //卡尔曼估计方差p
     kalman_this_time.p = kalman_last_time.p + kalman_last_time.q; //计算先验预测方差=上一时刻的先验预测方差+Q
    //卡尔曼增益 k
     kalman_this_time.k = kalman_this_time.p / (kalman_this_time.p + kalman_this_time.r); //计算卡尔曼增益=本次估计方差/(本次估计方差+R)
    //卡尔曼输出 x
     kalman_this_time.x = kalman_this_time.pre_x + kalman_this_time.k * (magYaw - kalman_this_time.pre_x);
    //卡尔曼刷新 p
     kalman_this_time.p = (1-kalman_this_time.k)*kalman_this_time.p;
    //推动时间节点
    kalman_last_time=kalman_this_time;//把this time 推成last time
    kalman_last_time.x = kalman_this_time.x;
    kalman_last_time.p = kalman_this_time.p;
    kalman_last_time.k = kalman_this_time.k;

}

#include "attitude.h"
#include "my_math.h"
#include "imu_9.h"

ATT_Module attitude;

void init_attitude(ATT_Module *attitude)
{
//标志位初始化
	attitude->flag.run = 1;						//开启计算
	attitude->flag.use_mag = 1;				//使用地磁
//接口初始化
	attitude->interface.data.a_x = 0;
	attitude->interface.data.a_y = 0;
	attitude->interface.data.a_z = 0;
	attitude->interface.data.g_x = 0;
	attitude->interface.data.g_y = 0;
	attitude->interface.data.g_z = 0;
	attitude->interface.data.m_x = 0;
	attitude->interface.data.m_y = 0;
	attitude->interface.data.m_z = 0;
//参数初始化	
	attitude->parameter.error_ki = 1.25f;
	attitude->parameter.error_kp = 5.5f;
	attitude->parameter.correct_kp = 0.4f;
//中间变量清空	
	attitude->process.error.x = 0;
	attitude->process.error.y = 0;
	attitude->process.error.z = 0;
	attitude->process.error_integral.x = 0;
	attitude->process.error_integral.y = 0;
	attitude->process.error_integral.z = 0;
	
	attitude->process.quaternion[0] = 1;
	attitude->process.quaternion[1] = 0;
	attitude->process.quaternion[2] = 0;
	attitude->process.quaternion[3] = 0;
//数据初始化
	attitude->data.rotate_matrix[0][0] = 0;
	attitude->data.rotate_matrix[0][1] = 0;
	attitude->data.rotate_matrix[0][2] = 0;
	attitude->data.rotate_matrix[1][0] = 0;
	attitude->data.rotate_matrix[1][1] = 0;
	attitude->data.rotate_matrix[1][2] = 0;
	attitude->data.rotate_matrix[2][0] = 0;
	attitude->data.rotate_matrix[2][1] = 0;
	attitude->data.rotate_matrix[2][2] = 0;
	
	attitude->data.mag_world.x = 0;
	attitude->data.mag_world.y = 0;
	attitude->data.mag_world.z = 0;
	
	attitude->data.acc_world.x = 0;
	attitude->data.acc_world.y = 0;
	attitude->data.acc_world.z = 0;
	
	attitude->data.mag_correct.x = 0;
	attitude->data.mag_correct.y = 0;
	attitude->data.mag_correct.z = 0;
	
	attitude->data.acc_correct.x = 0;
	attitude->data.acc_correct.y = 0;
	attitude->data.acc_correct.z = 0;
	
	attitude->data.gyro_correct.x = 0;
	attitude->data.gyro_correct.y = 0;
	attitude->data.gyro_correct.z = 0;
	
	attitude->data.pitch = 0;
	attitude->data.rol = 0;
	attitude->data.yaw = 0;
}


void simple_3d_trans(XYZ_Data_f *ref, XYZ_Data_f *in, XYZ_Data_f *out) //小范围内正确。
{
	static char pn;
	static float h_tmp_x,h_tmp_y;
	
	h_tmp_x = fast_sqrt(ref->z * ref->z + ref->y * ref->y);
	h_tmp_y = fast_sqrt(ref->z * ref->z + ref->x * ref->x);
	
	pn = ref->z < 0 ? -1 : 1;
	
	out->x = ( h_tmp_x *in->x - pn *ref->x *in->z ) ;
	out->y = ( pn *h_tmp_y *in->y - ref->y *in->z ) ;
	out->z = ref->x *in->x + ref->y *in->y + ref->z *in->z ;

}



void calculate_attitude(ATT_Module *attitude, float cycle)
{
	float length;
	XYZ_Data_f acc_tmp; 
	XYZ_Data_f error;

	attitude->interface.data.a_x = imu_9.f_acc[0]*1000.0f;
	attitude->interface.data.a_y = imu_9.f_acc[1]*1000.0f;
	attitude->interface.data.a_z = imu_9.f_acc[2]*1000.0f;
	attitude->interface.data.g_x = imu_9.f_gyro[0];
	attitude->interface.data.g_y = imu_9.f_gyro[1];
	attitude->interface.data.g_z = imu_9.f_gyro[2];
	attitude->interface.data.m_x = imu_9.f_mag[1];
	attitude->interface.data.m_y = imu_9.f_mag[0];
	attitude->interface.data.m_z = -imu_9.f_mag[2];


	
	if (attitude->flag.run == 0)
		return;
	
/////////////////////////////////////////////////////////////////////////////////////////////////		
	//电子罗盘处理
	if (attitude->flag.use_mag == 1)
	{	
		//利用电子罗盘计算yaw
		length = fast_sqrt(attitude->data.mag_correct.x * attitude->data.mag_correct.x + attitude->data.mag_correct.y * attitude->data.mag_correct.y);
		if( attitude->data.mag_correct.x != 0 && attitude->data.mag_correct.y != 0 && attitude->data.mag_correct.z != 0 && length != 0)
		{
			attitude->process.mag_yaw = arctan2(attitude->data.mag_correct.y / length, attitude->data.mag_correct.x / length);
//			attitude->process.mag_yaw = arctan2(attitude->data.mag_correct.y , attitude->data.mag_correct.x);
		}

		//计算yaw偏差
		if(attitude->data.rotate_matrix[2][2] > 0.0f )
		{
			attitude->process.mag_yaw_bias = attitude->parameter.correct_kp * translateAngle(attitude->data.yaw - attitude->process.mag_yaw);
			//矫正值过大 -- 矫正值错误
			if(attitude->process.mag_yaw_bias > 360 || attitude->process.mag_yaw_bias < -360)
			{
				attitude->process.mag_yaw_bias = 0;
			}
		}
		
		else
		{
			attitude->process.mag_yaw_bias = 0; //角度过大，停止修正，修正的目标值可能不正确
		}
	}

	else
	{
		attitude->process.mag_yaw_bias = 0;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////	
	//加速度计处理
	length = fast_sqrt(	(attitude->interface.data.a_x) * (attitude->interface.data.a_x) +
									(attitude->interface.data.a_y) * (attitude->interface.data.a_y) +
									(attitude->interface.data.a_z) * (attitude->interface.data.a_z));
	
	if(	ABS((attitude->interface.data.a_x)) < 1050.0f &&
			ABS((attitude->interface.data.a_y)) < 1050.0f &&
			ABS((attitude->interface.data.a_z)) < 1050.0f )
	{
		//加速度计归一化
		acc_tmp.x = (attitude->interface.data.a_x) / length;
		acc_tmp.y = (attitude->interface.data.a_y) / length;
		acc_tmp.z = (attitude->interface.data.a_z) / length;
		
		//叉乘计算偏差	--
		if(800.0f < length && length < 1200.0f)
		{
			/* 叉乘得到误差 */
			error.x = (acc_tmp.y * attitude->data.rotate_matrix[2][2] - acc_tmp.z * attitude->data.rotate_matrix[1][2]);
			error.y = (acc_tmp.z * attitude->data.rotate_matrix[0][2] - acc_tmp.x * attitude->data.rotate_matrix[2][2]);
	        error.z = (acc_tmp.x * attitude->data.rotate_matrix[1][2] - acc_tmp.y * attitude->data.rotate_matrix[0][2]);
			
			/* 误差低通 */
			attitude->process.error.x += 1.0f * 3.14f * cycle *(error.x  - attitude->process.error.x );
			attitude->process.error.y += 1.0f * 3.14f * cycle *(error.y  - attitude->process.error.y );
			attitude->process.error.z += 1.0f * 3.14f * cycle *(error.z  - attitude->process.error.z );
		}
	}
	else
	{
		attitude->process.error.x = 0;
		attitude->process.error.y = 0  ;
		attitude->process.error.z = 0 ;
	}

	// 误差积分	
	attitude->process.error_integral.x += attitude->process.error.x * attitude->parameter.error_ki * cycle;
	attitude->process.error_integral.y += attitude->process.error.y * attitude->parameter.error_ki * cycle;
	attitude->process.error_integral.z += attitude->process.error.z * attitude->parameter.error_ki * cycle;
	
	//积分限幅 -- 2°以内
	attitude->process.error_integral.x = LIMIT(attitude->process.error_integral.x, - 0.035f ,0.035f );
	attitude->process.error_integral.y = LIMIT(attitude->process.error_integral.y, - 0.035f ,0.035f );
	attitude->process.error_integral.z = LIMIT(attitude->process.error_integral.z, - 0.035f ,0.035f );
	
/////////////////////////////////////////////////////////////////////////////////////////////////
	//开始修正陀螺仪值
	attitude->data.gyro_correct.x = ((attitude->interface.data.g_x) - attitude->data.rotate_matrix[0][2] * attitude->process.mag_yaw_bias) * 0.01745329f +
						(attitude->parameter.error_kp * attitude->process.error.x + attitude->process.error_integral.x) ;
	attitude->data.gyro_correct.y = ((attitude->interface.data.g_y) - attitude->data.rotate_matrix[1][2] * attitude->process.mag_yaw_bias) * 0.01745329f +
						(attitude->parameter.error_kp * attitude->process.error.y + attitude->process.error_integral.y) ;
	attitude->data.gyro_correct.z = ((attitude->interface.data.g_z) - attitude->data.rotate_matrix[2][2] * attitude->process.mag_yaw_bias) * 0.01745329f +
						(attitude->parameter.error_kp * attitude->process.error.z + attitude->process.error_integral.z) ;
	
/////////////////////////////////////////////////////////////////////////////////////////////////
	// 一阶龙格库塔更新四元数值
	attitude->process.quaternion[0] += (-attitude->process.quaternion[1] * attitude->data.gyro_correct.x - attitude->process.quaternion[2] * attitude->data.gyro_correct.y - attitude->process.quaternion[3] * attitude->data.gyro_correct.z) * cycle / 2.0f;
	attitude->process.quaternion[1] +=  (attitude->process.quaternion[0] * attitude->data.gyro_correct.x + attitude->process.quaternion[2] * attitude->data.gyro_correct.z - attitude->process.quaternion[3] * attitude->data.gyro_correct.y) * cycle / 2.0f;
	attitude->process.quaternion[2] +=  (attitude->process.quaternion[0] * attitude->data.gyro_correct.y - attitude->process.quaternion[1] * attitude->data.gyro_correct.z + attitude->process.quaternion[3] * attitude->data.gyro_correct.x) * cycle / 2.0f;
	attitude->process.quaternion[3] +=  (attitude->process.quaternion[0] * attitude->data.gyro_correct.z + attitude->process.quaternion[1] * attitude->data.gyro_correct.y - attitude->process.quaternion[2] * attitude->data.gyro_correct.x) * cycle / 2.0f;

	//四元数归一化
	length = fast_sqrt(attitude->process.quaternion[0] * attitude->process.quaternion[0] +
								attitude->process.quaternion[1] * attitude->process.quaternion[1] +
								attitude->process.quaternion[2] * attitude->process.quaternion[2] +
								attitude->process.quaternion[3] * attitude->process.quaternion[3]);
		
	if (length != 0)
	{
		attitude->process.quaternion[0] /= length;
		attitude->process.quaternion[1] /= length;
		attitude->process.quaternion[2] /= length;
		attitude->process.quaternion[3] /= length;
	}
	
///////////////////////////////////////////////////////////////////////////////////////////////////	
	//计算旋转矩阵
	attitude->data.rotate_matrix[0][0] = 	attitude->process.quaternion[0] * attitude->process.quaternion[0] + attitude->process.quaternion[1] * attitude->process.quaternion[1] -
																		attitude->process.quaternion[2] * attitude->process.quaternion[2] - attitude->process.quaternion[3] * attitude->process.quaternion[3];
	attitude->data.rotate_matrix[0][1] = 	2 * (attitude->process.quaternion[1] * attitude->process.quaternion[2] + attitude->process.quaternion[0] * attitude->process.quaternion[3]);
	attitude->data.rotate_matrix[0][2] =  2 * (attitude->process.quaternion[1] * attitude->process.quaternion[3] - attitude->process.quaternion[0] * attitude->process.quaternion[2]);
	
	attitude->data.rotate_matrix[1][0] =  2 * (attitude->process.quaternion[1] * attitude->process.quaternion[2] - attitude->process.quaternion[0] * attitude->process.quaternion[3]);
	attitude->data.rotate_matrix[1][1] = 	attitude->process.quaternion[0] * attitude->process.quaternion[0] - attitude->process.quaternion[1] * attitude->process.quaternion[1] +
																		attitude->process.quaternion[2] * attitude->process.quaternion[2] - attitude->process.quaternion[3] * attitude->process.quaternion[3];
	attitude->data.rotate_matrix[1][2] =  2 * (attitude->process.quaternion[2] * attitude->process.quaternion[3] + attitude->process.quaternion[0] * attitude->process.quaternion[1]);
	
	attitude->data.rotate_matrix[2][0] = 	2 * (attitude->process.quaternion[1] * attitude->process.quaternion[3] + attitude->process.quaternion[0] * attitude->process.quaternion[2]);
	attitude->data.rotate_matrix[2][1] = 	2 * (attitude->process.quaternion[2] * attitude->process.quaternion[3] - attitude->process.quaternion[0] * attitude->process.quaternion[1]);
	attitude->data.rotate_matrix[2][2] = 	attitude->process.quaternion[0] * attitude->process.quaternion[0] - attitude->process.quaternion[1] * attitude->process.quaternion[1] -
																		attitude->process.quaternion[2] * attitude->process.quaternion[2] + attitude->process.quaternion[3] * attitude->process.quaternion[3];
	
	//计算世界坐标系下的磁力计值
	if (attitude->flag.use_mag == 1)
	{
		attitude->data.mag_world.x = 	attitude->data.rotate_matrix[0][0] * (attitude->interface.data.m_x) +
															attitude->data.rotate_matrix[1][0] * (attitude->interface.data.m_y) +
															attitude->data.rotate_matrix[2][0] * (attitude->interface.data.m_z) ;
															
		attitude->data.mag_world.y = 	attitude->data.rotate_matrix[0][1] * (attitude->interface.data.m_x) +
															attitude->data.rotate_matrix[1][1] * (attitude->interface.data.m_y) +
															attitude->data.rotate_matrix[2][1] * (attitude->interface.data.m_z) ;
															
		attitude->data.mag_world.z = 	attitude->data.rotate_matrix[0][2] * (attitude->interface.data.m_x) +
															attitude->data.rotate_matrix[1][2] * (attitude->interface.data.m_y) +
															attitude->data.rotate_matrix[2][2] * (attitude->interface.data.m_z) ;
	}
	
	//计算世界坐标系下的加速度值
	attitude->data.acc_world.x = 	attitude->data.rotate_matrix[0][0] * (attitude->interface.data.a_x) +
														attitude->data.rotate_matrix[1][0] * (attitude->interface.data.a_y) +
														attitude->data.rotate_matrix[2][0] * (attitude->interface.data.a_z) ;
														
	attitude->data.acc_world.y = 	attitude->data.rotate_matrix[0][1] * (attitude->interface.data.a_x) +
														attitude->data.rotate_matrix[1][1] * (attitude->interface.data.a_y) +
														attitude->data.rotate_matrix[2][1] * (attitude->interface.data.a_z) ;
														
	attitude->data.acc_world.z = 	attitude->data.rotate_matrix[0][2] * (attitude->interface.data.a_x) +
														attitude->data.rotate_matrix[1][2] * (attitude->interface.data.a_y) +
														attitude->data.rotate_matrix[2][2] * (attitude->interface.data.a_z) ;
	
	//求解欧拉角
	attitude->data.rol = arctan2(attitude->data.rotate_matrix[2][2], attitude->data.rotate_matrix[1][2]);
	attitude->data.pitch = -arcsin(attitude->data.rotate_matrix[0][2]);
	attitude->data.yaw = arctan2(attitude->data.rotate_matrix[0][0], attitude->data.rotate_matrix[0][1]);
	
/////////////////////////////////////////////////////////////////////////////////////////////////			
	//计算机体坐标系矫正后的加速度--不受俯仰和翻滚影响
	attitude->data.acc_correct.x =   attitude->data.acc_world.x * my_cos(attitude->data.yaw) + attitude->data.acc_world.y * my_sin(attitude->data.yaw);
	attitude->data.acc_correct.y =  -attitude->data.acc_world.x * my_sin(attitude->data.yaw) + attitude->data.acc_world.y * my_cos(attitude->data.yaw);
	attitude->data.acc_correct.z =   attitude->data.acc_world.z;
	
	//计算机体坐标系矫正后的磁场--不受俯仰和翻滚影响
	if (attitude->flag.use_mag == 1)
	{
		XYZ_Data_f ref_v = (XYZ_Data_f){attitude->data.rotate_matrix[0][2], attitude->data.rotate_matrix[1][2], attitude->data.rotate_matrix[2][2]};
		XYZ_Data_f mag_tmp = (XYZ_Data_f){attitude->interface.data.m_x, attitude->interface.data.m_y, attitude->interface.data.m_z};
		
		length = 	fast_sqrt(	(attitude->interface.data.m_x) * (attitude->interface.data.m_x) +
										(attitude->interface.data.m_y) * (attitude->interface.data.m_y) +
										(attitude->interface.data.m_z) * (attitude->interface.data.m_z));

		if (length != 0)
		{
			simple_3d_trans(&ref_v, &mag_tmp, &attitude->data.mag_correct);//地磁坐标变换
//			attitude->data.mag_correct.z = pose->data.mag_world.z;
//			attitude->data.mag_correct.x = fast_sqrt(1 - (attitude->data.mag_correct.z / length) * (attitude->data.mag_correct.z / length)) * *(attitude->interface.data.m_x);
//			attitude->data.mag_correct.y = fast_sqrt(1 - (attitude->data.mag_correct.z / length) * (pose->data.mag_correct.z / length)) * *(attitude->interface.data.m_y);
		}
	}
	
}

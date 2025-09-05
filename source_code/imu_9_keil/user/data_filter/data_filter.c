/*
 * data_filter.c
 *
 *  Created on: Jan 23, 2024
 *      Author: smile
 */

#include "data_filter.h"
#include "stdlib.h"

/**
 * @brief  高通滤波器
 * @author
 * @param  in-输入数据 out-滤波输出数据
 * @return void
 */
void high_pass_filter(float in, float *out)
{
	float rc, coff;
	static float in_p, out_p;

	rc = 1.0 / 2.0 / Pi / HP_CUT_FRQ;
	coff = rc / (rc + 1 / SAMPLE_RATE);
	*out = (in - in_p + out_p) * coff;

	out_p = *out;
	in_p = in;
}

/**
  * @brief  implement 1 order RC low pass filter
  *         raw data filtered by a simple RC low pass filter@cufoff=5Hz
  * @param  Vi 		: 	Vi(k)
  * @param  Vi_p 	: 	Vi(k-1)
  * @param  Vo 		: 	Vo(k)
  * @param  Vo_p 	: 	Vo(k-1)
  * @note   This example shows a simple way to report end of conversion
  *         and get conversion result. You can add your own implementation.
  * @retval None
  */
void LowPassFilter_RC(float Vi, float *Vo)
{
	float CutFrq, RC, Cof1, Cof2;
	static float	*Vo_p;
	//low pass filter @cutoff frequency = 5 Hz
	CutFrq = 2.0f;
	RC = (float)1.0f/2.0f/Pi/CutFrq;
	Cof1 = 1.0f/(1.0f+RC*SAMPLE_RATE);
	Cof2 = RC*SAMPLE_RATE/(1.0f+RC*SAMPLE_RATE);
	*Vo = Cof1 * (Vi) + Cof2 * (*Vo_p);

	//update
	*Vo_p = *Vo;
}

// 冒泡排序
void bubblesort(int32_t *arr, uint8_t len) // 小--》大
{
	int32_t temp;
	uint8_t i, j;
	for (i = 0; i < len - 1; i++) /* 外循环为排序趟数，len个数进行len-1趟 */
	{
		for (j = 0; j < len - 1 - i; j++)
		{ /* 内循环为每趟比较的次数，第i趟比较len-i次 */
			if (arr[j] > arr[j + 1])
			{ /* 相邻元素比较，若逆序则交换（升序为左大于右，降序反之） */
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

/**
 * @brief
 *
 * @param in
 * @param out
 * @param window_Array
 * @param i
 * @param sliding_Window_Length
 */
int16_t window_filter(int16_t data, int16_t *buf, uint8_t len)
{
	uint8_t i;
	int32_t sum = 0;

	for (i = 1; i < len; i++)
	{
		buf[i - 1] = buf[i];
	}
	buf[len - 1] = data;

	for (i = 0; i < len; i++)
	{
		sum += buf[i];
	}

	sum /= len;

	return sum;
}




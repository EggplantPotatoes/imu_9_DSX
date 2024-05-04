/*
 * attitude_algorithm.h
 *
 *  Created on: Jan 25, 2024
 *      Author: smile
 */

#ifndef ATTITUDE_ALGORITHM_H_
#define ATTITUDE_ALGORITHM_H_

#include "main.h"

#define MOTION_THRESHOLD  1.025f

typedef struct
{
	float x;
	float y;
	float z;

} AXIS;

typedef struct
{
	float roll;
	float pitch;
	float yaw;
} Out_Euler;


extern Out_Euler out_euler;
void complementary_get_euler(void);

#endif /* ATTITUDE_ALGORITHM_H_ */

#ifndef __DEBUG_H
#define __DEBUG_H

#include "stm32g4xx_hal.h"


void uart_debug_init(void);
void vofa_FireWater_output(float s1,float s2,float s3);
void vofa_JustFloat_output(float s1,float s2,float s3,float s4);
void usb_printf(const char *format, ...);
void vofa_JustFloat_USB_output(float s1, float s2, float s3, float s4);
void vofa_FireWater_USB_output(float s1, float s2, float s3,float s4);
#endif



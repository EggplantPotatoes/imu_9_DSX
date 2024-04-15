/*
 * @FilePath: \wifi_robot\src\tool\crc8_table.h
 * @brief: 
 * @author: liumingming
 * @Date: 2023-10-13 10:24:59
 * @Version: 1.0
 */
#pragma once

#include "main.h"




uint8_t Calc_CRC8(uint8_t *ptr, uint16_t len);
uint16_t crc16Calculate(uint8_t * pbuf, int cal_length);

/*
 * magnetic.h
 *
 *  Created on: Jan 22, 2024
 *      Author: smile
 */

#ifndef MAGNETIC_H_
#define MAGNETIC_H_

#include "main.h"

/** I2C Device Address 8 bit format **/
#define LIS2MDL_I2C_ADD                 0x3CU

/** Device Identification (Who am I) **/
#define LIS2MDL_ID                      0x40U

#define LIS2MDL_OFFSET_X_REG_L          0x45U
#define LIS2MDL_OFFSET_X_REG_H          0x46U
#define LIS2MDL_OFFSET_Y_REG_L          0x47U
#define LIS2MDL_OFFSET_Y_REG_H          0x48U
#define LIS2MDL_OFFSET_Z_REG_L          0x49U
#define LIS2MDL_OFFSET_Z_REG_H          0x4AU
#define LIS2MDL_WHO_AM_I                0x4FU
#define LIS2MDL_CFG_REG_A               0x60U
#define LIS2MDL_CFG_REG_B               0x61U
#define LIS2MDL_CFG_REG_C               0x62U
#define LIS2MDL_INT_CRTL_REG            0x63U
#define LIS2MDL_INT_SOURCE_REG          0x64U
#define LIS2MDL_INT_THS_L_REG           0x65U
#define LIS2MDL_INT_THS_H_REG           0x66U
#define LIS2MDL_STATUS_REG              0x67U
#define LIS2MDL_OUTX_L_REG              0x68U
#define LIS2MDL_OUTX_H_REG              0x69U
#define LIS2MDL_OUTY_L_REG              0x6AU
#define LIS2MDL_OUTY_H_REG              0x6BU
#define LIS2MDL_OUTZ_L_REG              0x6CU
#define LIS2MDL_OUTZ_H_REG              0x6DU
#define LIS2MDL_TEMP_OUT_L_REG          0x6EU
#define LIS2MDL_TEMP_OUT_H_REG          0x6FU

/* 设备寄存器参数值 */
#define LIS2MDL_CFGA_TEMP_EN                    (1 << 7)
#define LIS2MDL_CFGA_REBOOT                     (1 << 6)
#define LIS2MDL_CFGA_SOFT_RST                   (1 << 5)
#define LIS2MDL_CFGA_LP                         (1 << 4)
#define LIS2MDL_CFGA_ODR_10HZ                   (0 << 3) | (0 << 2)
#define LIS2MDL_CFGA_ODR_20HZ                   (0 << 3) | (1 << 2)
#define LIS2MDL_CFGA_ODR_50HZ                   (1 << 3) | (0 << 2)
#define LIS2MDL_CFGA_ODR_100HZ                  (1 << 3) | (1 << 2)
#define LIS2MDL_CFGA_MODE_CONTINUE              (0 << 1) | (0 << 0)
#define LIS2MDL_CFGA_MODE_SINGLE                (0 << 1) | (1 << 0)
#define LIS2MDL_CFGA_MoDE_IDLE                  (1 << 1) | (1 << 0)

#define LIS2MDL_CFGB_OFF_CANC_ONE_SHOT_EN       (1 << 4)
#define LIS2MDL_CFGB_INT_EN                     (1 << 3)
#define LIS2MDL_CFGB_SET_FREQ                   (1 << 2)
#define LIS2MDL_CFGB_OFF_CANC_EN                (1 << 1)
#define LIS2MDL_CFGB_LPF_EN                     (1 << 0)

#define LIS2MDL_CFGC_INT_ON_PIN                 (1 << 6)
#define LIS2MDL_CFGC_I2C_DIS                    (1 << 5)
#define LIS2MDL_CFGC_BDU                        (1 << 4)
#define LIS2MDL_CFGC_BLE                        (1 << 3)
#define LIS2MDL_CFGC_SPI                        (1 << 2)
#define LIS2MDL_CFGC_SELF_TEST                  (1 << 1)
#define LIS2MDL_CFGC_DRDY_ON_PIN                (1 << 0)


#define MAG_OFFSET_TIMES    5000

uint8_t mag_init(void);
void mag_sample_data(int16_t *mag );
void mag_sample_offset_data(int16_t *mag_offset );
void mag_set_offset(void);
#endif /* MAGNETIC_H_ */

/*
 * IIC_bus.c
 *
 *  Created on: Dec 7, 2023
 *      Author: smile
 */
#include "IIC_bus.h"

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c3;

/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  DevAddr    Device address on Bus.
  * @param  MemAddSize Size of internal memory address
  * @param  Reg        The target register address to write
  * @param  pData      The target register value to be written
  * @param  Length     data length in bytes
  * @retval BSP status
  */
static int32_t I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{
  if(HAL_I2C_Mem_Write(&hi2c1, DevAddr, Reg, MemAddSize, pData, Length, 1000) == HAL_OK)
  {
    return HAL_OK;
  }

  return HAL_ERROR;
}

/**
  * @brief  Read a register of the device through BUS
  * @param  DevAddr    Device address on BUS
  * @param  MemAddSize Size of internal memory address
  * @param  Reg        The target register address to read
  * @param  pData      The target register value to be read
  * @param  Length     data length in bytes
  * @retval BSP status
  */
static int32_t I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{
  if (HAL_I2C_Mem_Read(&hi2c1, DevAddr, Reg, MemAddSize, pData, Length, 1000) == HAL_OK)
  {
    return HAL_OK;
  }

  return HAL_ERROR;
}

/**
  * @brief  Write a 8bit value in a register of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg    The target register address to write
  * @param  pData  The target register value to be written
  * @param  Length buffer size to be written
  * @retval BSP status
  */
int32_t BSP_I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  if(I2C1_WriteReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length) == 0)
  {
	 return HAL_OK;
  }
  return HAL_ERROR;
}


/**
  * @brief  Read a 8bit register of the device through BUS
  * @param  DevAddr Device address on BUS
  * @param  Reg     The target register address to read
  * @param  pData   Pointer to data buffer
  * @param  Length  Length of the data
  * @retval BSP status
  */
int32_t BSP_I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  if(I2C1_ReadReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length) == HAL_OK)
  {
	 return HAL_OK;
  }
  return HAL_ERROR;
}

/**
  * @brief  Read a register of the device through BUS
  * @param  DevAddr    Device address on BUS
  * @param  MemAddSize Size of internal memory address
  * @param  Reg        The target register address to read
  * @param  pData      The target register value to be read
  * @param  Length     data length in bytes
  * @retval BSP status
  */
static int32_t I2C3_ReadReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{
  if (HAL_I2C_Mem_Read(&hi2c3, DevAddr, Reg, MemAddSize, pData, Length, 1000) == HAL_OK)
  {
    return HAL_OK;
  }

  return HAL_ERROR;
}


static int32_t I2C3_WriteReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{
  if(HAL_I2C_Mem_Write(&hi2c3, DevAddr, Reg, MemAddSize, pData, Length, 1000) == HAL_OK)
  {
    return HAL_OK;
  }

  return HAL_ERROR;
}

/**
  * @brief  Write a 8bit value in a register of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg    The target register address to write
  * @param  pData  The target register value to be written
  * @param  Length buffer size to be written
  * @retval BSP status
  */
int32_t BSP_I2C3_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  if(I2C3_WriteReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length) == 0)
  {
	 return HAL_OK;
  }
  return HAL_ERROR;
}


/**
  * @brief  Read a 8bit register of the device through BUS
  * @param  DevAddr Device address on BUS
  * @param  Reg     The target register address to read
  * @param  pData   Pointer to data buffer
  * @param  Length  Length of the data
  * @retval BSP status
  */
int32_t BSP_I2C3_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  if(I2C3_ReadReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length) == HAL_OK)
  {
	 return HAL_OK;
  }
  return HAL_ERROR;
}



///**
//  * @brief  Write a 16bit value in a register of the device through BUS.
//  * @param  DevAddr Device address on Bus.
//  * @param  Reg    The target register address to write
//  * @param  pData  The target register value to be written
//  * @param  Length buffer size to be written
//  * @retval BSP status
//  */
//int32_t BSP_I2C2_WriteReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
//{
//  if(I2C1_WriteReg(DevAddr, Reg, I2C_MEMADD_SIZE_16BIT, pData, Length) == 0)
//  {
//	 return HAL_OK;
//  }
//  return HAL_ERROR;
//}
//
///**
//  * @brief  Read a 16bit register of the device through BUS
//  * @param  DevAddr Device address on BUS
//  * @param  Reg     The target register address to read
//  * @param  pData   Pointer to data buffer
//  * @param  Length  Length of the data
//  * @retval BSP status
//  */
//int32_t BSP_I2C2_ReadReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
//{
//  if(I2C1_ReadReg(DevAddr, Reg, I2C_MEMADD_SIZE_16BIT, pData, Length) == 0)
//  {
//	 return HAL_OK;
//  }
//  return HAL_ERROR;
//}


#ifndef _FLASH_H
#define _FLASH_H

#include "main.h"

#define PAGE_SIZE 2048 // 芯片flash大小

//#define FLASH_BASE 0x08000000      // STM32 FLASH起始地址
#define USER_FLASH_ADDR_START 0x0801F800 // 用户使用的flash起始地址

#define ACC_ZERO_ADDR  USER_FLASH_ADDR_START
#define GYRO_ZERO_ADDR  ACC_ZERO_ADDR+6
#define MAG_ZERO_ADDR  GYRO_ZERO_ADDR+6

#define OUTPUT_ADDR      MAG_ZERO_ADDR+6
#define MAG_OFFSET_XSF_ADDR      OUTPUT_ADDR+2
#define MAG_OFFSET_YSF_ADDR      MAG_OFFSET_XSF_ADDR+2

typedef union
{
	uint64_t eight[PAGE_SIZE>>3];
	uint32_t four[PAGE_SIZE>>2];
	uint16_t two[PAGE_SIZE>>1];
	uint8_t	 one[PAGE_SIZE];
}union_t;

extern union_t  f_data;


void STMFLASH_Write(uint32_t WriteAddr, uint8_t *pBuffer, uint32_t NumToWrite);
void STMFLASH_Read(uint32_t ReadAddr, uint8_t *pBuffer, uint32_t NumToRead);
int FLASH_ErasePage(uint32_t pageAddress, uint32_t nbPages);

#endif

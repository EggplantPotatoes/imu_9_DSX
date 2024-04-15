#include "in_flash.h"

union_t  f_data;

void STMFLASH_Write_NoCheck(uint32_t WriteAddr, uint8_t *pBuffer, uint32_t NumToWrite)
{
    for(int i=0;i<(NumToWrite>>3);i++)
    {
  	  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,WriteAddr,f_data.eight[i]);
  	  WriteAddr += 8;
    }
}

/**
 @brief 内部Flash页擦除
 @param pageAddress -[in] 擦除的起始地址
 @param nbPages -[in] 擦除页数
 @return 0 - 成功；-1 - 失败
*/
int FLASH_ErasePage(uint32_t pageAddress, uint32_t nbPages)
{
	uint32_t pageError = 0;
	FLASH_EraseInitTypeDef eraseInit;
	eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	eraseInit.Page = (pageAddress - FLASH_BASE)/PAGE_SIZE;
	eraseInit.Banks = FLASH_BANK_1;
	eraseInit.NbPages = nbPages;
	if(HAL_FLASHEx_Erase(&eraseInit, &pageError) != HAL_OK)
	{
		return -1;
	}
	return 0;
}

void STMFLASH_Write(uint32_t WriteAddr, uint8_t *pBuffer, uint32_t NumToWrite)
{
	uint8_t STMFLASH_BUF[PAGE_SIZE];
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;
	uint16_t i;
	uint32_t offaddr;

	HAL_FLASH_Unlock();
	offaddr = WriteAddr - USER_FLASH_ADDR_START;
	secpos = offaddr / PAGE_SIZE;
	secoff = (offaddr % PAGE_SIZE);
	secremain = PAGE_SIZE  - secoff;
	if (NumToWrite <= secremain)
		secremain = NumToWrite;
//	while (1)
//	{
		STMFLASH_Read(secpos * PAGE_SIZE + USER_FLASH_ADDR_START, STMFLASH_BUF, PAGE_SIZE);
//		for (i = 0; i < secremain; i++)
//		{
//			if (STMFLASH_BUF[secoff + i] != 0XFFFFFFFF)
//				break;
//		}
//		if (i < secremain)
//		{
			FLASH_ErasePage(secpos * PAGE_SIZE + USER_FLASH_ADDR_START,1);
			for (i = 0; i < secremain; i++)
			{
				f_data.one[i + secoff] = pBuffer[i];
			}
			STMFLASH_Write_NoCheck(secpos * PAGE_SIZE + USER_FLASH_ADDR_START, STMFLASH_BUF, PAGE_SIZE);
//		}
//		else
//			STMFLASH_Write_NoCheck(WriteAddr, pBuffer, secremain);
//		if (NumToWrite == secremain)
//			break;
//		else
//		{
//			secpos++;
//			secoff = 0;
//			pBuffer += secremain;
//			WriteAddr += secremain;
//			NumToWrite -= secremain;
//			if (NumToWrite > (PAGE_SIZE))
//				secremain = PAGE_SIZE;
//			else
//				secremain = NumToWrite;
//		}
//	};
	HAL_FLASH_Lock();
}

void STMFLASH_Read(uint32_t ReadAddr, uint8_t *pBuffer, uint32_t NumToRead)
{
	uint64_t data;
	uint32_t temp1,temp2;

	temp1 = NumToRead/8;
	temp2 = NumToRead%8;
	if(temp2>0)
	{
		temp1 = temp1 + 1 ;

	}
	 for(uint32_t i=0; i<(PAGE_SIZE>>3); i++)
	  {
		 data = *(__IO uint64_t *)(USER_FLASH_ADDR_START+i*8);
	    f_data.eight[i] = data;
	  }

     for(int i=0;i<NumToRead;i++)
     {
    	 pBuffer[i] = f_data.one[ReadAddr - USER_FLASH_ADDR_START+i];

     }
}



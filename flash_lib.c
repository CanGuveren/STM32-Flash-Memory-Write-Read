#include "flash_lib.h"

/**
  * @brief  Writes 64-bit data to flash memory
	*
  * @param  Address variable indicates the flash memory address. 
  *
	* @param  Data pointer contains the data to be written to the flash memory 
	*
	* @param  NumberOfData data size to be written
	*
  * @retval void
  */
void Write_Flash_64BIT (uint32_t Address, uint64_t *Data, uint16_t NumberOfData)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError;
	uint32_t DataSize = 0;

	
	uint32_t FirstPage = PageFound(Address);
	uint32_t EndAddress = ( Address + ( NumberOfData * 8 ) );
	uint32_t LastPage = PageFound(EndAddress);
	
	HAL_FLASH_Unlock();	
	
	
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = Address;
	EraseInitStruct.NbPages     = (LastPage - FirstPage) + 1;
	
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	while (DataSize<NumberOfData)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, Data[DataSize]) == HAL_OK)
	  {
			Address += 8; 
			DataSize++;
	  }
	}
		 
	HAL_FLASH_Lock();
}


/**
  * @brief  Writes 32-bit data to flash memory
	*
  * @param  Address variable indicates the flash memory address. 
  *
	* @param  Data pointer contains the data to be written to the flash memory 
	*
	* @param  NumberOfData data size to be written
	*
  * @retval void
  */
void Write_Flash_32BIT (uint32_t Address, uint32_t *Data, uint16_t NumberOfData)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError;
	uint32_t DataSize = 0;

	
	uint32_t FirstPage = PageFound(Address);
	uint32_t EndAddress = ( Address + ( NumberOfData * 4 ) );
	uint32_t LastPage = PageFound(EndAddress);
	
	HAL_FLASH_Unlock();	
	
	
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = Address;
	EraseInitStruct.NbPages     = (LastPage - FirstPage) + 1;
	
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	while (DataSize<NumberOfData)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data[DataSize]) == HAL_OK)
	  {
			Address += 4; 
			DataSize++;
	  }
	}
		 
	HAL_FLASH_Lock();
}

/**
  * @brief  Writes 16-bit data to flash memory
	*
  * @param  Address variable indicates the flash memory address. 
  *
	* @param  Data pointer contains the data to be written to the flash memory 
	*
	* @param  NumberOfData data size to be written
	*
  * @retval void
  */
void Write_Flash_16BIT (uint32_t Address, uint16_t *Data, uint16_t NumberOfData)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError;
	uint32_t DataSize = 0;

	
	uint32_t FirstPage = PageFound(Address);
	uint32_t EndAddress = ( Address + ( NumberOfData * 2 ) );
	uint32_t LastPage = PageFound(EndAddress);
	
	HAL_FLASH_Unlock();	
	
	
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = Address;
	EraseInitStruct.NbPages     = (LastPage - FirstPage) + 1;
	
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	while (DataSize<NumberOfData)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address, Data[DataSize]) == HAL_OK)
	  {
			Address += 2; 
			DataSize++;
	  }
	}
		 
	HAL_FLASH_Lock();
}

/**
  * @brief  Writes 8-bit data to flash memory
	*
  * @param  Address variable indicates the flash memory address. 
  *
	* @param  Data pointer contains the data to be written to the flash memory 
	*
	* @param  NumberOfData data size to be written
	*
  * @retval void
  */
void Write_Flash_8BIT (uint32_t Address, uint8_t *Data, uint16_t NumberOfData)
{
	uint8_t i;
	uint8_t DataStep;
	uint8_t ArraySize;
	uint32_t PageError;
	int DataSize = 0;
	
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t FirstPage = PageFound(Address);
	uint32_t EndAddress = ( Address + ( NumberOfData * 2 ) );
	uint32_t LastPage = PageFound(EndAddress);
	
	if(NumberOfData % 2 == 1)	{	ArraySize = ((NumberOfData / 2) + 1);	}
	else											{	ArraySize = NumberOfData / 2;	}
	
	uint16_t FlashArray[ArraySize];
	
	for(i = 0; i < ArraySize; i++)
	{
		FlashArray[i] = (Data[DataStep] + (Data[DataStep + 1] << 8));
		DataStep += 2;
	}
	
	HAL_FLASH_Unlock();
	
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = Address;
	EraseInitStruct.NbPages     = (LastPage - FirstPage) + 1;
	
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	
	while (DataSize<ArraySize)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address, FlashArray[DataSize]) == HAL_OK)
	     {
	    	 Address += 2; 
	    	 DataSize++;
	     }
	   }
		 
	   HAL_FLASH_Lock();
}

/**
  * @brief  Reads 64-bit data from flash memory
	*
  * @param  Address variable indicates the flash memory address. 
  *
	* @param  Data pointer contains the data to be read from the flash memory 
	*
	* @param  NumberOfData data size to be read
	*
  * @retval void
  */
void Read_Flash_64BIT (uint32_t Address, uint16_t *FlashData, uint16_t NumberOfData)
{
	while (NumberOfData-- > 0)
	{
		*(FlashData) = *((__IO uint32_t *)Address);
		Address += 8;
		FlashData++;
	}
}

/**
  * @brief  Reads 32-bit data from flash memory
	*
  * @param  Address variable indicates the flash memory address. 
  *
	* @param  Data pointer contains the data to be read from the flash memory 
	*
	* @param  NumberOfData data size to be read
	*
  * @retval void
  */
void Read_Flash_32BIT (uint32_t Address, uint16_t *FlashData, uint16_t NumberOfData)
{
	while (NumberOfData-- > 0)
	{
		*(FlashData) = *((__IO uint32_t *)Address);
		Address += 4;
		FlashData++;
	}
}

/**
  * @brief  Reads 16-bit data from flash memory
	*
  * @param  Address variable indicates the flash memory address. 
  *
	* @param  Data pointer contains the data to be read from the flash memory 
	*
	* @param  NumberOfData data size to be read
	*
  * @retval void
  */
void Read_Flash_16BIT (uint32_t Address, uint16_t *FlashData, uint16_t NumberOfData)
{
	while (NumberOfData-- > 0)
	{
		*(FlashData) = *((__IO uint32_t *)Address);
		Address += 2;
		FlashData++;
	}
}

/**
  * @brief  Reads 8-bit data from flash memory
	*
  * @param  Address variable indicates the flash memory address. 
  *
	* @param  Data pointer contains the data to be read from the flash memory 
	*
	* @param  NumberOfData data size to be read
	*
  * @retval void
  */
void Read_Flash_8BIT (uint32_t Address, uint8_t *FlashData, uint16_t NumberOfData)
{
	
	union 
	{
		struct
		{
			uint8_t LSB;
			uint8_t MSB;
		}Data_8BIT;
			
		uint16_t Data_16BIT;
		
	}Convert_8BIT;
	
	uint8_t i = 0, m = 0;
	uint8_t ArraySize;
	
	if(NumberOfData % 2 == 1)
	{
		ArraySize = ((NumberOfData / 2) + 1);
	}
	else
	{
		ArraySize = NumberOfData / 2;
	}
	
	uint16_t FlashArray[ArraySize];
	
	for(i = 0; i < ArraySize; i++)
	{
		FlashArray[i] = *((__IO uint32_t *)Address);
		Address += 2;
	}
	
	for(i = 0; i < ArraySize; i++)
	{
	  Convert_8BIT.Data_16BIT = FlashArray[i];
		*(FlashData + m) = Convert_8BIT.Data_8BIT.LSB;
		*(FlashData + (m + 1)) = Convert_8BIT.Data_8BIT.MSB;
		m += 2;
	}		
	
}

void Erase_Flash(uint8_t Page)
{
	HAL_FLASH_Unlock();
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError;
	
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = PageToAddress(Page);
	EraseInitStruct.NbPages     = 1;
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	
	 HAL_FLASH_Lock();
}



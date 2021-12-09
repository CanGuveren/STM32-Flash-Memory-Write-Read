#ifndef INC_FLASH_LIB_H_
#define INC_FLASH_LIB_H_

#include "stdint.h"
#include "stm32f1xx.h"

#define PageFound(__ADDRESS__) 	( ( __ADDRESS__ - (uint32_t)(0x08000000 ) ) / 1024 )
#define PageToAddress(__PAGE__) ( (uint32_t)( 0x08000000 + 1024*__PAGE__ ) )

void Write_Flash_64BIT(uint32_t StartPageAddress, uint64_t *Data, uint16_t NumberOfData);
void Write_Flash_32BIT(uint32_t StartPageAddress, uint32_t *Data, uint16_t NumberOfData);
void Write_Flash_16BIT(uint32_t StartPageAddress, uint16_t *Data, uint16_t NumberOfData);
void Write_Flash_8BIT (uint32_t StartPageAddress, uint8_t *Data, uint16_t NumberOfData);
void Read_Flash_64BIT (uint32_t StartPageAddress, uint16_t *FlashData, uint16_t NumberOfData);
void Read_Flash_32BIT (uint32_t StartPageAddress, uint16_t *FlashData, uint16_t NumberOfData);
void Read_Flash_16BIT (uint32_t StartPageAddress, uint16_t *FlashData, uint16_t NumberOfData);
void Read_Flash_8BIT (uint32_t StartPageAddress, uint8_t *FlashData, uint16_t NumberOfData);
void Erase_Flash(uint8_t Page);


#endif /* INC_FLASH_LIB_H_ */

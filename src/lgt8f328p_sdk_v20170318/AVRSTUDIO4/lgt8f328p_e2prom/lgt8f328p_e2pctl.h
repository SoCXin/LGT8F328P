#ifndef _LGT8F328P_E2PCTL_H_
#define _LGT8F328P_E2PCTL_H_

#include <stdint.h>


/**********************************************************************************
*** MACROS AND DEFINITIONS							***
**********************************************************************************/ 
#define	MMAP_FLASH_BASE		0x4000
#define	flashReadByte(address)	(*(uint8_t *)(MMAP_FLASH_BASE + address))

#define	e2pReset()	do { ECCR |= 0x20; } while(0)
#define e2pSWMON()	do { ECCR = 0x80; ECCR |= 0x10; } while(0)
#define e2pSWMOFF()	do { ECCR = 0x80; ECCR &= 0xEF; } while(0)
	
/**********************************************************************************
*** 	EXPORTED FUNCTIONS							***
**********************************************************************************/
void e2pInit();

void e2pWriteByte(uint16_t wAddr, uint8_t bData);
void e2pWriteWord(uint16_t wAddr, uint32_t bData);

uint8_t e2pReadByte(uint16_t wAddr);
uint32_t e2pReadWord(uint16_t wAddr);

void e2pSWMWriteWords(uint16_t swAddr, uint32_t *pData, uint8_t length);
void e2pSWMReadWords(uint16_t swAddr, uint32_t *pData, uint8_t length);

#endif
/**********************************************************************************
***	EOF									***
**********************************************************************************/

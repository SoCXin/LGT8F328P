/**********************************************************************************
** API implementation for USART module
***********************************************************************************
*/

#include <avr/io.h>
#include <stdint.h>

#include "lgt8f328p_spec.h"
#include "lgt8f328p_conf.h"

/**********************************************************************************
*** 								LOCAL VARIABLES 							***
**********************************************************************************/


/**********************************************************************************
*** 						  EXPORTED FUNCTIONS								***
**********************************************************************************/
// ----------------------------------------------------------------------
// public: e2pctl module initialization
// 	- For LGT8F328P: 
//		1. enable E2PROM emulator
//		2. configure 1KByte E2PROM (only first 2046 bytes avaliable)
//  - If you want more information, please refer to E2PCTL details inside of databook			
// ----------------------------------------------------------------------
void e2pInit(void)
{

	ECCR = 0x80;
	ECCR = 0x4C;
}

// ----------------------------------------------------------------------
// public: write byte to emulated E2PROM			
// ----------------------------------------------------------------------
void e2pWriteByte(uint16_t wAddr, uint8_t bData)
{
	sysCLRI();
	
	// address
	EEARH = wAddr >> 8;
	EEARL = wAddr & 0xff;
	// data
	EEDR = bData;
	// Program Mode
	EECR = 0x04;
	EECR = 0x02;

	// retore interrupt settings
	sysRESI();
}

// ----------------------------------------------------------------------
// public: read and return byte from emulated E2PROM			
// ----------------------------------------------------------------------
uint8_t e2pReadByte(uint16_t wAddr)
{

	// address
	EEARH = wAddr >> 8;
	EEARL = (wAddr) & 0xff;
	// start eeprom read by writting EERE
	EECR |= (1 << EERE);

	nop(); nop();
	// return data from data register
	return EEDR;
}

// ----------------------------------------------------------------------
// public: write double word(32bits) to emulated E2PROM			
// ----------------------------------------------------------------------
void e2pWriteWord(uint16_t wAddr, uint32_t dwData)
{
	sysCLRI();

	EEARL = 0;
	EEDR = dwData;
	EEARL = 1;
	EEDR = dwData >> 8;
	EEARL = 2;
	EEDR = dwData >> 16;
	EEARL = 3;
	EEDR = dwData >> 24;

	EEARH = wAddr >> 8;
	EEARL = wAddr & 0xff;

	// Program Mode
	EECR = 0x44;
	EECR = 0x42;	
		
	sysRESI();
} 

// ----------------------------------------------------------------------
// public: read then return double words(32bits) from emulated E2PROM			
// ----------------------------------------------------------------------
uint32_t e2pReadWord(uint16_t wAddr)
{
	uint32_t dwTmp;

	// address
	EEARH = wAddr >> 8;
	EEARL = (wAddr) & 0xff;

	// start eeprom read by writting EERE
	EECR |= (1 << EERE);

	nop(); nop();

	dwTmp = E2PD0;
	dwTmp |= ((uint32_t)E2PD1 << 8);
	dwTmp |= ((uint32_t)E2PD2 << 16);
	dwTmp |= ((uint32_t)E2PD3 << 24);

	// return data from data register
	return dwTmp;
}

// ----------------------------------------------------------------------
// public: write bundle of data to E2PROM with SWM mode enable
// ----------------------------------------------------------------------
void e2pSWMWriteWords(uint16_t swAddr, uint32_t *pData, uint8_t length)
{
	uint8_t i;

	e2pReset();
	e2pSWMON();

	EEARH = swAddr >> 8;
	EEARL = swAddr;

	for(i = 0; i < length; i++) {
		if(i == (length - 1)) // the last word
			e2pSWMOFF();

		E2PD0 = (uint8_t)pData[i];
		E2PD1 = (uint8_t)(pData[i] >> 8);
		E2PD2 = (uint8_t)(pData[i] >> 16);
		E2PD3 = (uint8_t)(pData[i] >> 24);

		sysCLRI(); 

		EECR = 0x44;
		EECR = 0x42;

		sysRESI();
	}
}

// ----------------------------------------------------------------------
// public: read bundle of data to E2PROM with SWM mode enable
// ----------------------------------------------------------------------
void e2pSWMReadWords(uint16_t swAddr, uint32_t *pData, uint8_t length)
{
	uint8_t i;

	e2pReset();
	e2pSWMON();

	EEARH = swAddr >> 8;
	EEARL = swAddr;

	for(i = 0; i < length; i++) {
		if(i == (length - 1)) // the last word
			e2pSWMOFF();

		EECR |= (1 << EERE);
		nop(); nop();

		pData[i] = (uint32_t)E2PD0;
		pData[i] |= ((uint32_t)E2PD1 << 8);
		pData[i] |= ((uint32_t)E2PD2 << 16);
		pData[i] |= ((uint32_t)E2PD3 << 24);
	}
}

/**********************************************************************************
*** 										EOF 								*** 													
**********************************************************************************/


/**********************************************************************************
** API implementation for USART module
***********************************************************************************
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>

#include "lgt8f328p_spec.h"
#include "lgt8f328p_conf.h"


/**********************************************************************************
***					            MACRO AND DEFINITIONS							***													  	
**********************************************************************************/  


/**********************************************************************************
***					            EXPORTED FUNCTIONS								***													  	
**********************************************************************************/  
void pwrInit(void)
{
	// Set power/off lock
	pwrSleepLock();
}

// ----------------------------------------------------------------------
// public: sleep with power mode settings
// 	- arg: mode, to set target sleep mode
//			sleep mode can be one of follow settings:
//			 - SLEEP_DILE
//			 - SLEEP_ANRM
//			 - SLEEP_SAVE
//			 - SLEEP_DPS1
//			 - SLEEP_DPS0
//			 - SLEEP_DPS2
// ----------------------------------------------------------------------
void pwrSleep(uint8_t mode)
{
	uint8_t CLKPR_reg = CLKPR;
	uint8_t LDOCR_reg = LDOCR;
	uint8_t MCUSR_reg = MCUSR | 0x7f;
	uint8_t SREG_reg = SREG;

	// global interrupt disable
	cli();

	// disable SWD interface to release PE0/2
	MCUSR = 0x80;
	MCUSR = 0xff;

	// minimize system power before LDO power/down
	CLKPR = 0x80;
	CLKPR = 0x08;

	//nop(); nop(); nop(); nop();

	LDOCR = 0x80;
	LDOCR = 0x02; // LDO power/down
	
	//nop(); nop(); nop(); nop();	
	//nop(); nop(); nop(); nop();

	// bring system to sleep
	SMCR = ((mode & 0x7) << 1) | 0x1; 	
	sleep();

	//nop(); nop(); // nop(); nop();

	// restore LDO settings
	LDOCR = 0x80;
	LDOCR = LDOCR_reg;

	//nop(); nop(); nop(); nop();	
	nop(); nop(); nop(); nop();

	// restore system clock prescaler
	CLKPR = 0x80;
	CLKPR = CLKPR_reg;

	// restore SWD/SWC interface
	MCUSR = 0x80;
	MCUSR = MCUSR_reg;

	// restore interrupt settings
	SREG = SREG_reg;
}

/**********************************************************************************
*** 									EOF 									*** 													
**********************************************************************************/  


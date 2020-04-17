#ifndef _LGT8F328P_SLEEP_H_
#define _LGT8F328P_SLEEP_H_

#include <stdint.h>

// module power control
#define	PRR_ADC		0x0001
#define	PRR_USART0	0x0002
#define	PRR_SPI		0x0004
#define	PRR_TIM1	0x0008
#define	PRR_TIM0	0x0020
#define	PRR_TIM2	0x0040
#define	PRR_TWI		0x0080

#define	PRR_PINC	0x0200
#define	PRR_E2PC	0x0400
#define	PRR_TIM3	0x0800
#define	PRR_WDT		0x2000

#define	PRRC	(*(volatile uint16_t *)0x0064)

// sleep mode definition
#define	SLEEP_IDLE	0x0
#define	SLEEP_ANRM	0x1
#define	SLEEP_SAVE	0x2
#define	SLEEP_DPS1	0x3
#define	SLEEP_DPS0	0x6
#define	SLEEP_DPS2	0x7

// DPS2 control and mode definiton
#define DPS2_LPRC_OFF	0x0
#define	DPS2_LPRC_128MS	0x4
#define	DPS2_LPRC_256MS	0x5
#define	DPS2_LPRC_512MS	0x6
#define	DPS2_LPRC_1S	0x7

/**********************************************************************************
***					     	 MACROS AND DEFINITIONS								***													  	
**********************************************************************************/ 
#ifndef sleep
#define	sleep()	__asm__ __volatile__ ("sleep" ::)
#endif

#ifndef nop
#define nop() __asm__ __volatile__ ("nop" ::)
#endif

#define	pwrModuleClockEnable(MID) do { PRRC &= ~MID; } while(0)
#define	pwrModuleClockDisable(MID) do { PRRC |= MID; } while(0)

#define	pwrSleepLock() do { SMCR = 0x8; } while(0)

// DPS2 mode control
#define	pwrDPS2Enable() do { DPS2R |= (1 << DPS2E); } while(0)
#define pwrDPS2Disable() do { DPS2R &= ~(1 << DPS2E); } while(0)
#define	pwrDPS2LPRCMode(mode) do { DPS2R &= 0xf8; DPS2R |= (mode & 0x7); } while(0)

// PD group I/O level change wake-up control
// args: pid
//		pid can be one of _BV(PDn) or combined of them
// example:
//		pwrIOCDForWakeup(_BV(PD2) | _BV(PD3));
//		- will enable PD2/3 level change for wake-up.
//
#define pwrIOCDForWakeup(pid) do { IOCWK = pid; } while(0)
	
/**********************************************************************************
*** 						  	EXPORTED FUNCTIONS								*** 													
**********************************************************************************/
void pwrInit();
void pwrSleep(uint8_t);

#endif
/**********************************************************************************
***					          			EOF										***													  	
**********************************************************************************/

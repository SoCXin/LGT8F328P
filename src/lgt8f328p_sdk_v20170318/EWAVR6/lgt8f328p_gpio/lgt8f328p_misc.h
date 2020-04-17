#ifndef _LGT8F328P_MISC_H_
#define	_LGT8F328P_MISC_H_

/**********************************************************************************
*** Miscelliance defintions and functions for LGT8F328P
*** This file impelemented tied with EWAVR environment 
*** Be careful when porting to other compiler system
**********************************************************************************/ 
#include <intrinsics.h>

#include "lgt8f328p_stdbits.h"
#include "lgt8f328p_spec.h"

typedef signed char 	int8_t;
typedef unsigned char 	uint8_t;
typedef signed int 	int16_t;
typedef unsigned int 	uint16_t;
typedef signed long 	int32_t;
typedef unsigned long 	uint32_t;

// system settings definiton
// ===========================================================
// Modify F_CPU accroding to your system clock settings
// by default, system clock = 32MHz HFRC/8 = 4MHz
#ifndef F_CPU
#define F_CPU           16000000UL
#endif

#define INT_OSC         0
#define EXT_OSC         1

#define SYSCLK_DIV_0    0x0
#define SYSCLK_DIV_2    0x1
#define SYSCLK_DIV_4    0x2
#define SYSCLK_DIV_8    0x3
#define SYSCLK_DIV_16   0x4
#define SYSCLK_DIV_32   0x5
#define SYSCLK_DIV_64   0x6
#define SYSCLK_DIV_128  0x7

// helper macros definiton
// ===========================================================
#ifndef nop
#define nop()	__no_operation()
#endif

#ifndef sleep
#define sleep()	__sleep()	
#endif

#ifndef wdr
#define wdr()	__watchdog_reset()	
#endif

#ifndef cli
#define cli()	__disable_interrupt()	
#endif

#ifndef sei
#define sei()	__enable_interrupt()
#endif

#ifndef NUM_CYCLES_OF_US
#define NUM_CYCLES_OF_US      (F_CPU/1000000)
#endif

#ifndef NUM_CYCLES_OF_MS
#define NUM_CYCLES_OF_MS      (F_CPU/1000)
#endif

#define delay_us(n)   __delay_cycles(n*NUM_CYCLES_OF_US)
#define delay_ms(n)   __delay_cycles(n*NUM_CYCLES_OF_MS)   

/**********************************************************************************
*** public API decelaration	
**********************************************************************************/ 
void sysCLRI();
void sysRESI();

void sysSWDDisable();
void sysSWDEnable();
void sysAVREFDisable();
void sysAVREFEnable();
void sysEXRESETDisable();
void sysEXRESTEnable();

void sysClockSource(uint8_t);
void sysClockPrescale(uint8_t);

// replacement for standard libc's utoa which not implemented in IAR/AVR
char* utoa(uint16_t, char *, uint8_t);

#endif
/**********************************************************************************
*** EOF 
**********************************************************************************/ 

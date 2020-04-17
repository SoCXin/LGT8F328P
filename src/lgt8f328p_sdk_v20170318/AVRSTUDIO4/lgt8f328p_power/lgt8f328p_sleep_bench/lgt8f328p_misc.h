#ifndef _LGT8F328P_MISC_H_
#define	_LGT8F328P_MISC_H_

#include <avr/io.h>
#include <stdint.h>

#include "lgt8f328p_spec.h"

/**********************************************************************************
*** Miscelliance defintions and functions for LGT8F328P
*** This file impelemented tied with AVR-GCC/WinAVR environment 
*** Be careful when porting to other compiler system
**********************************************************************************/ 

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
#define nop()	__asm__ __volatile__ ("nop" ::)
#endif

#ifndef sleep
#define sleep()	__asm__ __volatile__ ("sleep" ::)
#endif

#ifndef wdr
#define wdr()	__asm__ __volatile__ ("wdr" ::)
#endif

#ifndef cli
#define cli()	__asm__ __volatile__ ("cli" ::)
#endif

#ifndef sei
#define sei()	__asm__ __volatile__ ("sei" ::)
#endif

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

#endif
/**********************************************************************************
*** EOF 
**********************************************************************************/ 

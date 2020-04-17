#ifndef _LGT8F328P_CONF_H_
#define	_LGT8F328P_CONF_H_

/**********************************************************************************
***	Implementation configurations for demo
***
**********************************************************************************/ 
#include "lgt8f328p_misc.h"
#include "lgt8f328p_gpp.h"

// system settings definiton
// ===========================================================
// Modify FCLK accroding to your system clock settings
// by default, system clock = 32MHz HFRC/8 = 4MHz
#ifndef F_CPU
#define	F_CPU	4000000L
#endif

#endif

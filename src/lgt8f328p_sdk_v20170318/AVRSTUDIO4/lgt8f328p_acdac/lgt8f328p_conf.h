#ifndef _LGT8F328P_CONF_H_
#define	_LGT8F328P_CONF_H_

/**********************************************************************************
***	Implementation configurations for demo
***
**********************************************************************************/ 
#include "lgt8f328p_misc.h"
#include "lgt8f328p_gpp.h"
#include "lgt8f328p_acdac.h"

// Analog Comparator settings definiton
// ===========================================================
// configuration for analog comparator 0
// ----------------------------------------------------------
// AC0 posedge input selection
#define		AC0_PSEL		AC0_PSEL_DAC	// from pin of AC0P

// AC0 negedge input selection
#define		AC0_NSEL		AC0_NSEL_ACXN	// from DAC's output

// AC0 interrupt sense mode selection
#define		AC0_ISS			AC0_ISS_POS		// interrupt if posedge of ACO

// AC0 output to PD2
#define		AC0_C0OE		0				// disable ACO output to I/O

// AC0 interrupt control
#define		AC0_C0IE		1				// disable AC0 interrupt function

// AC0 hystersis control
#define		AC0_C0HYSE		0				// hysteresis disable

// AC0 digital filter control
#define		AC0_C0FEN		1				// digital filter enable

// AC0 digital filter selection
#define		AC0_C0FS		AC0_C0FS_96US	// 96us digital filter

// configuration for analog comparator 1
// ----------------------------------------------------------
// AC0 posedge input selection
#define		AC1_PSEL		AC1_PSEL_DAC	// from pin of AC0P

// AC0 negedge input selection
#define		AC1_NSEL		AC1_NSEL_ACXN	// from DAC's output

// AC0 interrupt sense mode selection
#define		AC1_ISS			AC1_ISS_POS		// interrupt if posedge of ACO

// AC0 output to PD2
#define		AC1_C1OE		0				// disable ACO output to I/O

// AC0 interrupt control
#define		AC1_C1IE		0				// disable AC0 interrupt function

// AC0 hystersis control
#define		AC1_C1HYSE		0				// hysteresis disable

// AC0 digital filter control
#define		AC1_C1FEN		1				// digital filter enable

// AC0 digital filter selection
#define		AC1_C1FS		AC1_C1FS_96US	// 96us digital filter


#endif

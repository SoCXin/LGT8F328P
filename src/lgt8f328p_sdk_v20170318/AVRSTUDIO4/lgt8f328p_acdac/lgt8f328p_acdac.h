#ifndef _LGT8F328P_ACDAC_H_
#define _LGT8F328P_ACDAC_H_

/**********************************************************************************
***					     	 MACROS AND DEFINITIONS								***													  	
**********************************************************************************/ 

// DAC voltage source selection
#define	DAC_DVS_VCC		0x0		// DAC source from VCC (power supply)
#define	DAC_DVS_AVREF	0x1		// DAC source from AVREF(external referece input)
#define	DAC_DVS_IVREF	0x2		// DAC source from internal Reference
#define	DAC_DVS_OFF		0x3		// DAC disabled

// Defintions for AC0/1
#define	AC0_PSEL_AC0P	0x0		// AC0 posedge input from AC0P
#define	AC0_PSEL_ACXP	0x1		// AC0 posedge input from ACXP
#define	AC0_PSEL_DAC	0x2		// AC0 posedge input from DAC's output
#define	AC0_PSEL_OFF	0x3		// floating posedge input

#define	AC1_PSEL_AC1P	0x0		// AC1 posedge input from AC1P
#define	AC1_PSEL_ACXP	0x1		// AC1 posedge input from ACXP
#define	AC1_PSEL_DAC	0x2		// AC1 posedge input from DAC's output
#define	AC1_PSEL_OFF	0x3		// floating posedge input

#define	AC0_NSEL_ACXN	0x0		// AC0 negedge input from ACXN
#define	AC0_NSEL_ADMX	0x1		// AC0 negedge input from ADC's sample-hold channel
#define	AC0_NSEL_DAP	0x2		// AC0 negedge input from DAP's output
#define	AC0_NSEL_OFF	0x3		// floating negedge input

#define	AC1_NSEL_ACXN	0x0		// AC1 negedge input from ACXN
#define	AC1_NSEL_AC1N	0x1		// AC1 negedge input from AC1N
#define	AC1_NSEL_V5D1	0x2		// AC1 negedge input from VDS(1/5 divider)
#define	AC1_NSEL_DAP	0x3 	// AC1 negedge input from DAP's output

#define	AC0_ISS_ANY		0x0		// interrupt if any edge of AC's output
#define	AC0_ISS_NEG		0x2		// interrupt if negedge of AC's output
#define	AC0_ISS_POS		0x3		// interrupt if posedge of AC's output

#define	AC1_ISS_ANY		0x0
#define	AC1_ISS_NEG		0x2
#define	AC1_ISS_POS		0x3

#define	AC0_C0FS_32US	0x1		// 32us AC0 digital-filter for output
#define	AC0_C0FS_64US	0x2		// 64us	AC0 digital-filter for output
#define	AC0_C0FS_96US	0x3		// 96us AC0 digital-filter for output
#define	AC0_C0FS_OFF	0x0		// disable AC0's output digital-filter

#define	AC1_C1FS_32US	0x1
#define	AC1_C1FS_64US	0x2
#define	AC1_C1FS_96US	0x3
#define	AC1_C1FS_OFF	0x0


/**********************************************************************************
*** 						  	EXPORTED FUNCTIONS								*** 													
**********************************************************************************/
// macro definition for DAC module
#define dacEnable()		do { DACON |= (1 << DACEN); } while(0)
#define dacDisable()	do { DACON &= ~(1 << DACEN); } while(0)

// bring DAC's output to (PD4)
#define	dacDAOEnable()	do { DACON |= (1 << DAOE); } while(0)
#define dacDAODisable()	do { DACON &= ~(1 << DAOE); } while(0)

#define	dacInit(dvs, val) do {\
	DACON = 0x03 | (dvs & 0x3); \
	DALR = val; \
} while(0) 

#define	dacOutput(val)	do { DALR = val; } while(0)

// macro defintion for AC0/1
// --------------------------------------------------------------------------
// ac0 module enable/disable control
#define	ac0Enable()		do { C0SR &= 0x7f; } while(0)
#define ac0Disable()	do { C0SR |= 0x80; } while(0)

// ac0 interrupt control
#define ac0IntEnable()	do { C0SR |= (1 << C0IE); } while(0)
#define ac0IntDisable()	do { C0SR &= ~(1 << C0IE); } while(0)

// get ac0's output status
#define ac0Read()		((C0SR >> 5) & 0x1)

#define ac0OutputEnable() do { C0XR |= (1 << C0OE); } while(0)
#define ac0OutputDisable() do { C0XR &= ~(1 << C0OE); } while(0)

// ac0 output hypersis control
#define	ac0HysEnable()	do { C0XR |= (1 << C0HYSE); } while(0)
#define	ac0HysDisable()	do { C0XR &= ~(1 << C0HYSE); } while(0)

// ac0 digital filter control
#define	ac0SetDigiFilter(dfs)	do { C0XR |= (1 << C0FEN) | (dfs & 0x3); } while(0)
#define ac0DigiFilterDisable() do { C0XR &= ~(1 << C0FEN); } while(0)

#define	ac0SetPosedge(psel) do { \
	C0SR &= ~(1 << C0BG); \
	C0SR |= ((psel & 0x2) << 5); \
	C0XR &= ~(1 << C0PS0); \
	C0XR |= ((psel & 0x1) << C0PS0); \
} while(0)

#define	ac0SetNegedge(nsel) do { \
	ADCSRB &= 0x3f; \
	ADCSRB |= (nsel & 0x3) << 6; \
} while(0)

// ac1 module enable/disable control
#define	ac1Enable()		do { C1SR &= 0x7f; } while(0)
#define ac1Disable()	do { C1SR |= 0x80; } while(0)

// ac1 interrupt control
#define ac1IntEnable()	do { C1SR |= (1 << C1IE); } while(0)
#define ac1IntDisable()	do { C1SR &= ~(1 << C1IE); } while(0)

// get ac1's output status
#define ac1Read()		((C1SR >> 5) & 0x1)

#define ac1OutputEnable() do { C1XR |= (1 << C1OE); } while(0)
#define ac1OutputDisable() do { C1XR &= ~(1 << C1OE); } while(0)

// ac1 output hypersis control
#define	ac1HysEnable()	do { C1XR |= (1 << C1HYSE); } while(0)
#define	ac1HysDisable()	do { C1XR &= ~(1 << C1HYSE); } while(0)

// ac1 digital filter control
#define	ac1SetDigiFilter(dfs)	do { C1XR |= (1 << C1FEN) | (dfs & 0x3); } while(0)
#define ac1DigiFilterDisable() do { C1XR &= ~(1 << C1FEN); } while(0)

#define	ac1SetPosedge(psel) do { \
	C1SR &= ~(1 << C1BG); \
	C1SR |= ((psel & 0x2) << 5); \
	C1XR &= ~(1 << C1PS0); \
	C1XR |= ((psel & 0x1) << C1PS0); \
} while(0)

#define	ac1SetNegedge(nsel) do { \
	ADCSRB &= 0x3f; \
	ADCSRB |= (nsel & 0x3) << 4; \
} while(0)
	

void ac0Init();
void ac1Init();


#endif
/**********************************************************************************
***					          			EOF										***													  	
**********************************************************************************/

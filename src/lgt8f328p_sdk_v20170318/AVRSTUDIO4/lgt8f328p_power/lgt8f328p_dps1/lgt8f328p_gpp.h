#ifndef _LGT8F328P_GPP_H_
#define _LGT8F328P_GPP_H_

#ifndef LOW
#define	LOW		0
#endif

#ifndef HIGH	
#define	HIGH	1
#endif

#define	P0		0x01
#define	P1		0x02
#define	P2		0x04
#define	P3		0x08
#define	P4		0x10
#define	P5		0x20
#define	P6		0x40
#define	P7		0x80
#define PALL	0xff

#define	IN_P0	0x0
#define	IN_P1	0x1
#define	IN_P2	0x2
#define	IN_P3	0x3
#define	IN_P4	0x4
#define	IN_P5	0x5
#define	IN_P6	0x6
#define	IN_P7	0x7

#define	GPPB	((volatile unsigned char *)0x25)
#define	GPPC	((volatile unsigned char *)0x28)
#define	GPPD	((volatile unsigned char *)0x2B)
#define	GPPE	((volatile unsigned char *)0x2E)
#define	GPPF	((volatile unsigned char *)0x34)

#define	PCN_GPPB	0x0
#define	PCN_GPPC	0x1
#define	PCN_GPPD	0x2
#define	PCN_GPPE	0x3
#define	PCN_GPPF	0x4

#define	PCI_GPPB	0x01
#define	PCI_GPPC	0x02
#define	PCI_GPPD	0x04
#define	PCI_GPPE	0x08
#define	PCI_GPPF	0x10
#define	PCI_PALL	0x1f

#define	PCMSK_GPPB	(*((volatile unsigned char *)0x6B))
#define	PCMSK_GPPC	(*((volatile unsigned char *)0x6C))
#define	PCMSK_GPPD	(*((volatile unsigned char *)0x6D))
#define	PCMSK_GPPE	(*((volatile unsigned char *)0x73))
#define	PCMSK_GPPF	(*((volatile unsigned char *)0x74))

/**********************************************************************************
***					     	 MACROS AND DEFINITIONS								***													  	
**********************************************************************************/ 
// set port to output mode
// ------------------------------------------------------------------------------
// usage: gppEnableOutput(GPPA, P0|P1|P5);
//	- will set PA0/PA1/PA5 to output mode
//	- usign PALL to set all port to output
#define	gppEnableOutput(gpp, pn)	do { *(gpp - 1) |= (pn); } while(0)

// set port to input mode
// ------------------------------------------------------------------------------
// usage: gppEnableInput(GPPA, P0|P1|P5);
//	- will set PA0/PA1/PA5 to input mode
//	- usign PALL to set all port to input
#define gppEnableInput(gpp, pn)	do { *(gpp - 1) &= ~(pn); } while(0)

// read status of a group of port
// ------------------------------------------------------------------------------
// usage: gppRead(GPPA);
//	- read status of PA
#define	gppRead(gpp)			(*(gpp - 2))

// read status of a single pin
// ------------------------------------------------------------------------------
// usage: gppRead(GPPA, P2);
//	- read pin status of PA2
//	0 = low level
//	1 = high level 
#define	gppReadSingle(gpp, pn)	((*(gpp - 2) & (1 << IN_##pn)) >> IN_##pn)

// drive port output level to high (1)
// ------------------------------------------------------------------------------
// usage: gppSetHigh(GPPA, P0|P1|P5);
//	- will drive output of PA0/PA1/PA5 to high level
//	- usign PALL to set all port output high level
#define gppSetHigh(gpp, pn)	do { *gpp |= (pn); } while(0)

// drive port output level to low (0)
// ------------------------------------------------------------------------------
// usage: gppSetLow(GPPA, P0|P1|P5);
//	- will drive output of PA0/PA1/PA5 to low level
//	- usign PALL to set all port output low level
#define	gppSetLow(gpp, pn)	do { *gpp &= ~(pn); } while(0)

// toggle port output level
// ------------------------------------------------------------------------------
// usage: gppToggle(GPPA, P0|P1|P5);
//	- will toggle output of PA0/PA1/PA5
//	- usign PALL to toggle all port of this group
#define	gppToggle(gpp, pn)	do { *(gpp - 2) = (pn); } while(0)
//#define	gppToggle(gpp, pn)	do { *gpp ^= (pn); } while(0)

// enable internal pullup
// ------------------------------------------------------------------------------
// usage: gppEnablePullup(GPPA, P0|P1|P5);
//	- will enable internal pullup of PA0/PA1/PA5
//	- usign PALL to enable all pullup of this group
#define gppEnablePullup(gpp, pn)	do { gppEnableInput(gpp, pn); gppSetHigh(gpp, pn); } while(0)
	
// disable internal pullup
// ------------------------------------------------------------------------------
// usage: gppDisablePullup(GPPA, P0|P1|P5);
//	- will disable internal pullup of PA0/PA1/PA5
//	- usign PALL to disable all pullup of this group
#define	gppDisablePullup(gpp, pn)	gppSetLow(gpp, pn)

// enable pin-change interrupt
// ------------------------------------------------------------------------------
// usage: gppEnablePCI(GPPB, P0|P1|P5);
//	- will enable pin change interrupt of PB0/PB1/PB5
//	- usign PALL to enable all 
#define	gppEnablePCI(gpp, pn) do { PCICR |= PCI_##gpp; PCMSK_##gpp |= (pn); } while(0)	

// disable pin-change interrupt
// ------------------------------------------------------------------------------
// usage: gppDisablePCI(GPPB, P0|P1|P5);
//	- will disable pin change interrupt of PB0/PB1/PB5
//	- usign PALL to disable all
#define	gppDisablePCI(gpp, pn) do { PCMSK_##gpp &= ~(pn); } while(0)

// read PCI flag of ports
// ------------------------------------------------------------------------------
// usage: gppReadPCIFlag(PALL);
//	- will read pin change flag PB
//	- using PALL to read all
#define gppReadPCIFlag(gpp) (PCIFR & PCI_##gpp)

// clear PCI flag of ports
// ------------------------------------------------------------------------------
// usage: gppClrPCIFlag(PALL);
//	- will read pin change flag PB
//	- using PALL to clear all
#define gppClrPCIFlag(gpp)	do { PCIFR = PCI_##gpp; } while(0)

/**********************************************************************************
*** 						  	EXPORTED FUNCTIONS								*** 													
**********************************************************************************/


#endif
/**********************************************************************************
***					          			EOF										***													  	
**********************************************************************************/

#ifndef _LGT8F328P_DAP_H_
#define _LGT8F328P_DAP_H_

#include <stdint.h>

// DAP gain settings
#define DAP_GAIN_X1	0x0
#define	DAP_GAIN_X8	0x1
#define	DAP_GAIN_X16	0x2
#define	DAP_GAIN_X32	0x3

// DAP inverting inputs
#define	DAP_DNS_ADC2	0x0		// ADC2
#define	DAP_DNS_ADC3	0x1		// ADC3
#define	DAP_DNS_ADC8	0x2		// ADC8
#define	DAP_DNS_ADC9	0x3		// ADC9
#define	DAP_DNS_PE0	0x4		// PE0
#define	DAP_DNS_ADMX	0x5		// ADMUX (from CHMUX)
#define	DAP_DNS_AGND	0x6		// tie to ground
#define	DAP_DNS_NONE	0x7		// floating DNS

// DAP non-inverting inputs
#define	DAP_DPS_ADMX	0x0		// ADMUX (from CHMUX) 
#define	DAP_DPS_ADC0	0x1		// ADC0
#define	DAP_DPS_ADC1	0x2		// ADC1
#define	DAP_DPS_AGND	0x3		// tie to ground

/**********************************************************************************
***		 MACROS AND DEFINITIONS						***
**********************************************************************************/ 
#define	dapDisable()	do { DAPCR &= 0x7F; } while(0)
#define dapEnable()	do { DAPCR |= 0x80; } while(0)

#define	dapInit(gain, dns, dps) do { \
	DAPCR = 0x80 | (gain << GA0) | (dns << DNS0) | (dps << DPS0); \
} while(0)	

/**********************************************************************************
***	  	EXPORTED FUNCTIONS
**********************************************************************************/

#endif
/**********************************************************************************
***		EOF								***
**********************************************************************************/

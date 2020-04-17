#include <stdlib.h>
#include <ioavr.h>

#include "lgt8f328p_conf.h"

// global definitions
// ===================================================================
char	caTmp[5];

uint16_t adcVal;
uint16_t adcTmp[5];

// Main program
// ===================================================================
int main()
{
	uint8_t i;
        
        // set system clock to internal 16MHz
        // ==============================================================
        // DO NOT forget to set right F_CPU according to your 
        //      system clock settings
        // F_CPU is defined inside of 'lgt8f328p_misc.h'
        // ==============================================================
        sysClockPrescale(SYSCLK_DIV_2);

	// initialize adc module
	// See API implementation inside of lgt8f328p_adc.c
	// where we can give ADC's initial settings by macro definitions.
	// here is settings for this demo:
	// ===============================================================
	// ADC reference: internal 2.048V
	// ADC sample clock: 512KHz (4MHz system clock with 1/8 prescaler)
	// ADC interrupt: disabled
	// ADC auto-trigger mode: disabled
	// ===============================================================
	adcInit();

	while(1)
	{
		adcTmp[4] = adcReadChannel(ADC_CHMUX_ADC4);
		adcTmp[3] = adcReadChannel(ADC_CHMUX_ADC4);
		adcTmp[2] = adcReadChannel(ADC_CHMUX_ADC4);
		adcTmp[1] = adcReadChannel(ADC_CHMUX_ADC4);
		adcTmp[0] = adcReadChannel(ADC_CHMUX_ADC4);

		adcVal = 0;
		for(i = 0; i < 4; i++)
			adcVal += adcTmp[i];
	
		// average of 4x oversample	
		adcVal >>= 2; 

		// covert to real voltage (unit: mV)
		adcVal >>= 1;

		// just for breakpoint here
		delay_ms(100);
	}
}

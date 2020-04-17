#include <ioavr.h>

#include "lgt8f328p_conf.h"

// global defintions
// ===================================================================
char 	caTmp[5];

uint16_t adcVal;
uint16_t adcTmp[5];

int main()
{
	uint8_t i;

    // configure system clock to 16MHz
    // ==============================================================
    // DO NOT forget to set right F_CPU definition according to 
    // your system clock settings
    // F_CPU is defined inside of 'lgt8f328p_misc.h'
    // =============================================================
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

	// configure ADC S/H to sample from DAP
	adcSetChannel(ADC_CHMUX_DAP);

	// initialize dap module
	// See implementation inside of lgt8f328p_dap.h
	// here is settings for this demo:
	// ===============================================================
	// DAP gain: x8
	// DAP inverting inputs: tied to ground
	// DAP non-inverting inputs: from ADC1/PC1
	// ===============================================================
	dapInit(DAP_GAIN_X8, DAP_DNS_ADC2, DAP_DPS_ADC0);

	// enable ADC's test mode to drive
	// ADC's S/H channel to PE6 (for test purpose)
	// for this case, DAP's output can be measured directly from PE6
	adcTestOn();
	
	// DAP trimming settings
	//DAPTC = 0x80;
	//DAPTR = 0x86;

	// initial other modules
	usartInit();

	// banner 
	usartPutStr("\r\n============================================ \r\n");
	usartPutStr("LGT8F328P Software Developement Kits \r\n");
	usartPutStr("**** ADC/DAP Module Usage **** \r\n");
	usartPutStr("============================================ \r\n");

	// here we use internal 2.048V for adc's reference
	// DAP is configured with x8 gain amplifier, 
	// ADC will be overflow at point of 2.048V/8 = 0.256V

	while(1)
	{
		adcTmp[4] = adcReadChannel(ADC_CHMUX_DAP);
		adcTmp[3] = adcReadChannel(ADC_CHMUX_DAP);  
		adcTmp[2] = adcReadChannel(ADC_CHMUX_DAP);
		adcTmp[1] = adcReadChannel(ADC_CHMUX_DAP);
		adcTmp[0] = adcReadChannel(ADC_CHMUX_DAP);

		adcVal = 0;
		for(i = 0; i < 4; i++)
			adcVal += adcTmp[i];
		
		// average of 4x oversample	
		adcVal >>= 2; 

		// covert to real voltage (unit: mV)
		adcVal = adcVal >> 1;

		// convert binary to printabe string
		utoa(adcVal, caTmp, 10);
		
		// print to UART interface
		usartPutStr(">> DAP Output := ");
		usartPutStr(caTmp);
		usartPutStr("mV\r\n");

		// just for breakpoint here
		delay_ms(1000);
	}
}

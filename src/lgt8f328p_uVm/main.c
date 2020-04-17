#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include <avr/io.h>

#include "lgt8f328p_conf.h"

// included after definition of F_CPU
#include <util/delay.h>

// global defintions
// ===================================================================
#define APP_DAP_GAIN	DAP_GAIN_X16

// global defintions
// ===================================================================
char 	caTmp[10];

uint16_t adcVal;
float fadcVal;
float fadcRem;

volatile uint16_t dapOfs;

// DAP auto-trimming for 25mV offset
// should be called in stage of early initialization
uint16_t dap8xOffset25mVTrim();

int main()
{

	//OSCCAL = 0xae;

    // configure system clock to 4MHz (default settings)
    // ==============================================================
    // DO NOT forget to set right F_CPU definition according to 
    // your system clock settings
    // F_CPU is defined inside of 'lgt8f328p_misc.h'
    // =============================================================
    //sysClockPrescale(SYSCLK_DIV_8);  

	_delay_ms(50);

	// early stage for analog calibration/trimming
	dapOfs = dap8xOffset25mVTrim();

	// initialize adc module
	// See API implementation inside of lgt8f328p_adc.c
	// where we can give ADC's initial settings by macro definitions.
	// here is settings for this demo:
	// ===============================================================
	// ADC reference: internal 1.024V
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
	// DAP inverting inputs:  for ADC2/APN0/PC2
	// DAP non-inverting inputs: from ADC1/APN1/PC1
	// ===============================================================
	dapInit(APP_DAP_GAIN, DAP_DNS_ADC2, DAP_DPS_ADC1);

	// enable ADC's test mode to drive
	// ADC's S/H channel to PE6 (for test purpose)
	// for this case, DAP's output can be measured directly from PE6
	adcTestOn();

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
		adcVal = adcReadChannelEx(ADC_CHMUX_DAP);

		if(adcVal > dapOfs)
			adcVal -= dapOfs;

		// covert to 0.1mV
#if APP_DAP_GAIN == DAP_GAIN_X1
		fadcVal = ((float)adcVal * 100.0) / 4.0;
#elif APP_DAP_GAIN == DAP_GAIN_X8
		fadcVal = ((float)adcVal * 100.0) / 32.0;
#elif APP_DAP_GAIN == DAP_GAIN_X16		
		fadcVal = ((float)adcVal * 100.0) / 64.0;
#elif APP_DAP_GAIN == DAP_GAIN_X32
		fadcVal = ((float)adcVal * 100.0) / 128.0;
#endif

		fadcRem = fmod(fadcVal, 100);

		fadcVal = fadcVal/100.0;

		// convert binary to printabe string
		utoa((uint16_t)fadcVal, caTmp, 10);

		// print to UART interface
		usartPutStr(">> DAP Output := ");
		usartPutStr(caTmp);
		usartPutChar('.');
		utoa((uint16_t)fadcRem, caTmp, 10);
		usartPutStr(caTmp);
		usartPutStr("mV\r\n");

		// just for breakpoint here
		asm __volatile__ ("nop");

		_delay_ms(300);
	}
}


uint16_t dap8xOffset25mVTrim()
{
	uint16_t dapOff = 0;

	adcInit();

	adcTestOn();

	// initial dap settings for trimming
#if 0
	dapInit(APP_DAP_GAIN, DAP_DNS_AGND, DAP_DPS_AGND);	
#else
	adcSetChannel(ADC_CHMUX_ADC1);
	dapInit(APP_DAP_GAIN, DAP_DNS_ADMX, DAP_DPS_ADMX);
#endif
	
	adcSetChannel(ADC_CHMUX_DAP);

	// initial dap trimming to give postive offset
	DAPTC = 0x80;
	DAPTR = 0xa;

	_delay_ms(1);

	// invert direction
	dapOff = adcReadChannelEx(ADC_CHMUX_DAP);

	return dapOff;
}

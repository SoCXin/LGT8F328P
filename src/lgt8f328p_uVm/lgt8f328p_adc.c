/**************************************************************************
***************************************************************************
*/

#include <avr/io.h>
#include <stdint.h>

#include "lgt8f328p_spec.h"
#include "lgt8f328p_conf.h"

// ----------------------------------------------------------------------
// public: adc module initialization
// ----------------------------------------------------------------------
void adcInit()
{
	// update calibration if needed
#if (ADC_REFS == ADC_REFS_2V048)
	VCAL = VCAL2;	// calibration for 2.048V
#elif (ADC_REFS == ADC_REFS_4V096)
	VCAL = VCAL3;	// calibration for 4.096V
	ADCSRD |= (1 << REFS2);	// See register definition of ADCSRD and ADMUX
#endif

	// (optional) write to clear ADIF
	ADCSRA = 0x10;

	// set voltage reference
#if (ADC_REFS == ADC_REFS_4V096)
	ADMUX = ADC_REFS_DEFV << REFS0;
#else
 	ADMUX = ADC_REFS << REFS0;
#endif

	// ADC Control and Status Register A
	ADCSRA = (ADC_ADATEN  << ADATE) |	// auto-trigger bit 
				(ADC_ADIE << ADIE) | 	// interrupt control bit
				ADC_ADPS;				// ADC clock prescaler bits

	// ADC Control and Status Register B
#if (ADC_ADATEN == 1)
	ADCSRB = ADC_ADTS;	// source select for auto-trigger mode
#endif

	// Enable ADC
	ADCSRA |= (1 << ADEN);
}

// ----------------------------------------------------------------------
// public: start adc coversation by software
// ----------------------------------------------------------------------
void adcSoftStart()
{
	// set ADSC bit to start a conversation
	ADCSRA |= (1 << ADSC);

	// wait until it's done
	while((ADCSRA & (1 << ADSC)) != 0x00);
}

// ----------------------------------------------------------------------
// public: select a different ADC's channel
// ----------------------------------------------------------------------
void adcSetChannel(uint8_t chMUX)
{
	// select DAP channel
	if(chMUX == ADC_CHMUX_DAP) {
		ADCSRC |= (1 << DIFS);
	} else {
		ADCSRC &= ~(1 << DIFS);
		ADMUX &= 0xE0;		// cleanup CHMUX bits
		ADMUX |= (chMUX & 0x1F);	// set target CHMUX
	}
}

// ----------------------------------------------------------------------
// public: set ADC's reference dynamically
// ----------------------------------------------------------------------
void adcSetReference(uint8_t adcREFS)
{
	// update calibration if needed
	if(adcREFS == ADC_REFS_4V096) {
		VCAL = VCAL3;	// calibration for 4.096V
		ADCSRD |= (1 << REFS2);	// See register definition of ADCSRD and ADMUX
	} else if (adcREFS == ADC_REFS_2V048) {
		VCAL = VCAL2;	// calibration for 2.048V
	} else {
		VCAL = VCAL1;	// calibration for 1.024V
	} 

	// set voltage reference
	if(adcREFS == ADC_REFS_4V096)
		ADMUX = ADC_REFS_DEFV << REFS0;
	else
 		ADMUX = adcREFS << REFS0;
}

// ----------------------------------------------------------------------
// private : start ADC conversation and return back its result
// ----------------------------------------------------------------------
uint16_t adcRead()
{
	volatile uint8_t tmp = 0;

	adcSoftStart();

	tmp = ADCL;			// Be care: read low byte first, then high byte
	return (ADCH << 8) | tmp;
}

// ----------------------------------------------------------------------
// public: return adc's value of a given channel
//		with offset/gain error correction
// ----------------------------------------------------------------------
uint16_t adcReadChannel(uint8_t chMUX)
{
	uint16_t pVal, nVal;

	// set target channel
	adcSetChannel(chMUX);

	// SPN1 conversation
	ADCSRC |= (1 << SPN);
	nVal = adcRead();

	// SPN0 conversation
	ADCSRC &= ~(1 << SPN);
	pVal = adcRead();

	// average
	pVal = (pVal + nVal) >> 1;

	// gain-error correction
	pVal -= (pVal >> 6);

	return pVal;
}

uint16_t adcReadChannelEx(uint8_t chMUX)
{
	uint16_t adcVal = 0;

	for(uint8_t i = 0; i < 8; i++) {
		adcVal += adcReadChannel(chMUX);
	}

	adcVal = adcVal >> 3;

	return adcVal;
}

/**********************************************************************************
*** 									EOF 									*** 													
**********************************************************************************/

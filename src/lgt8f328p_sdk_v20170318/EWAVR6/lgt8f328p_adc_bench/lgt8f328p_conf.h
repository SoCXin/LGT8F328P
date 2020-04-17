#ifndef _LGT8F328P_CONF_H_
#define	_LGT8F328P_CONF_H_

/**********************************************************************************
***	Implementation configurations for demo
***
**********************************************************************************/ 
#include "lgt8f328p_misc.h"
#include "lgt8f328p_adc.h"
#include "lgt8f328p_usart.h"

// ADC settings definition
// ===========================================================
// set ADC's reference
#define	ADC_REFS	ADC_REFS_2V048	// using internal 2.048V
					// ADC_REFS_1V024
					// ADC_REFS_4V096
					// ADC_REFS_AVCC
					// ADC_REFS_AVREF

// set ADC's sample clock prescaler
#define	ADC_ADPS	ADC_ADPS_DIV8	// ADC_CLK = SYSCLK/8 (512KHz by default)

// interrupter settings
#define	ADC_ADIE	0	// disable

// auto-trigger convert mode
#define	ADC_ADATEN	0				// disable auto-trigger mode
#define	ADC_ADTS	ADC_ADTS_FRUN	// auto-trigger source


// USART settings definition
// ===========================================================
// define USART working mode
#define	USART_UMSEL0	E_UMSEL0_UART	// asynchrouns uart
						// E_UMSEL0_USART
						// E_UMSEL0_SSPI
						// E_UMSEL0_MSPI

// baudrate definition
#define	USART_BDR0		19200UL		// 19200bps

// data length 
#define	USART_UCSZ0		E_UCSZ0_8B

// stop bits definiton
#define	USART_USBS0		E_USBS0_1B	// 1 stop

// parity mode definition
#define	USART_UPM0		E_UPM0_NONE	// no parity bit

// USART RX/TX interface control
// -----------------------------
// USART receive interface control
#define	USART_RXEN		1	// enable

// USART transmit interface control
#define	USART_TXEN		1	// enable

// Interrupt control
// -----------------------------
// receive completion interrupt request
#define	USART_RXC		0	// disable 

// transmit completion interrupt request
#define	USART_TXC		0	// disable

// USART data register empty interrupt request
#define	USART_UDRE		0	// disable

// ******************************************************************
// DO NOT TRY TO MODIFY FOLLOWING SETTINGS
// unless you know exactly what you wanna.
// ******************************************************************
// USART double-speed mode control
#define	USART_U2X0		0	// disable

// USART clock sensitive for synchronous mode
#define USART_UCPOL0	E_UCPOL0_TRE_SFE
			// refer to E_UCP0L0_TRE_SFE definiton inside of lgt8f328p_usart.h
			// or refer to LGT8F328P databook for more details.

#ifndef F_CPU
#warning F_CPU should be defined for BAUDRATE generation
#endif

// USART multi-processor mode
#define	USART_MPCM0		0	// disable

// baudrate calculation
#if (USART_UMSEL0 == E_UMSEL0_UART)
	#if (USART_U2X0 == 1)
		#define USART_UBRR	(uint16_t)(((((F_CPU / USART_BDR0) >> 2) + 1) >> 1) - 1)
	#else
		#define USART_UBRR	(uint16_t)(((((F_CPU / USART_BDR0) >> 3) + 1) >> 1) - 1)
	#endif
#else
	#define USART_UBRR	(uint16_t)(((((F_CPU / USART_BDR0)) + 1) >> 1) - 1)
#endif


#endif

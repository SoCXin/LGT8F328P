#include <avr/io.h>
#include <stdint.h>

#include "lgt8f328p_conf.h"

int main()
{
	uint8_t u8Temp;

    // configure system clock to 16MHz
    // ==============================================================
    // DO NOT forget to set right F_CPU definition according to 
    // your system clock settings
    // F_CPU is defined inside of 'lgt8f328p_misc.h'
    // =============================================================
    sysClockPrescale(SYSCLK_DIV_2);  


	// initialize usart module
	// See API implementation inside of lgt8f328p_usart.c
	// implementation definitions can be found inside of lgt8f328p_conf.h
	// here is USART configuration for this demo:
	// ===============================================================
	// USART mode: asynchrouns uart
	// Baudrate: 19200bps
	// Data Length: 8bits
	// Stop bits: 1bits
	// Parity Mode: None
	// Interrupt: disabled
	// ===============================================================
	usartInit();

	// Say hello to world.
	usartPutStr("Hello from LGT8F328P! \r\n");

	while(1)
	{
		// echo everything its received.
		u8Temp = usartGetChar();

		usartPutChar(u8Temp);

		// just for breakpoint here
		nop();
	}
}

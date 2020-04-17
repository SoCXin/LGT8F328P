#include <avr/io.h>
#include <stdint.h>

#include "lgt8f328p_conf.h"

// inlcuded after definition of F_CPU
#include <util/delay.h>

int main()
{  
    // configure system clock to 16MHz
    // ==============================================================
    // DO NOT forget to set right F_CPU definition according to 
    // your system clock settings
    // F_CPU is defined inside of 'lgt8f328p_misc.h'
    // =============================================================
    sysClockPrescale(SYSCLK_DIV_2);  


	// initial other helper function
	gppEnablePullup(GPPB, PALL);
	gppEnablePullup(GPPC, PALL);
	gppEnablePullup(GPPD, PALL);
	gppEnablePullup(GPPE, PALL);
	gppEnablePullup(GPPF, PALL);

	// set PB0/1 to output mode
	gppEnableOutput(GPPE, P7);

	while(1)
	{
		// toggle PB0/1
		gppToggle(GPPE, P7);		

		if(gppReadSingle(GPPF, P2) == LOW)
			_delay_us(10);

		if(gppReadSingle(GPPC, P0) == LOW)
			_delay_us(100);
	}
}

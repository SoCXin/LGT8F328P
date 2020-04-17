#include <avr/io.h>
#include <stdint.h>

#include "lgt8f328p_spec.h"
#include "lgt8f328p_conf.h"

// inlcuded after definition of F_CPU
#include <util/delay.h>

int main()
{  
	// initialize power control module
	// ===============================================================
	// pwrInit() is optional
	// ===============================================================
	pwrInit();

	// initial other helper function
	// drive GPIO to stable state for minimize power leakage
	gppEnablePullup(GPPB, PALL);
	gppEnablePullup(GPPC, PALL);
	gppEnablePullup(GPPD, PALL);
	gppEnablePullup(GPPE, PALL);
	gppEnablePullup(GPPF, PALL);

	_delay_us(10);


	gppEnablePCI(GPPC, P3|P2|P1|P0);
	//gppClrPCIFlag(GPPC);
	gppClrPCIFlag(PALL);

	while(1)
	{

		if(gppReadSingle(GPPF, P2) == LOW) {
			// set PB0/1 to input mode
			gppEnableInput(GPPB, P0|P1);

			// goto sleep
			pwrSleep(SLEEP_DPS1);
		}

		// I am working now...
		gppEnableOutput(GPPB, P0|P1);

		// toggle PB0/1
		gppToggle(GPPB, P0|P1);		

		_delay_us(10);
	}
}

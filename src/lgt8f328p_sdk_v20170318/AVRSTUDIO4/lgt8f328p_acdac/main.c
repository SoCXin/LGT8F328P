#include <avr/io.h>
#include <stdint.h>

#include "lgt8f328p_spec.h"
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


	// ac0 module initilization
	// ==============================================
	// default setting:
	// 	- posedge : input from internal DAC
	//	- negedge : input from external ACXN/PD7
	//	- enable internal 96us digital filter
	//	- enable ac interrupt
	// ===============================================
	ac0Init();

	// AC0 settings can be modified any time if needed.
	// 
	//ac0SetPosedge(AC0_PSEL_DAC);
	//ac0SetNegedge(AC0_NSEL_ACXN);
	//ac0SetDigiFilter(AC0_C0FS_96US);
	//ac0IntEnable();

	// initial other helper function

	// set PB0/1 to output mode
	gppEnableOutput(GPPB, P0|P1);

	// enable global interrupt
	sei();

	while(1)
	{
		// toggle PB0/1
		gppToggle(GPPB, P1);
		_delay_ms(1);		
	}
}

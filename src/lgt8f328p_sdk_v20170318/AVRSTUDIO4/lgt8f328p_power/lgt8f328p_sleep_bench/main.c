#include <avr/io.h>
#include <stdint.h>

#include "lgt8f328p_conf.h"

// inlcuded after definition of F_CPU
#include <util/delay.h>

void printHelper()
{
	usartPutStr("\r\n=================================================\r\n");
	usartPutStr("LGT8F328P Software Design Kit \r\n");
	usartPutStr("**** Power/Sleep Usage **** \r\n");
	usartPutStr("-------------------------------------------------\r\n");
	usartPutStr("Commands defintion: \r\n");
	usartPutStr(" h - print help information\r\n");
	usartPutStr(" 0 - bring mcu to idle mode\r\n");
	usartPutStr(" 1 - bring mcu to save mode\r\n");
	usartPutStr(" 2 - bring mcu to dps0 mode\r\n");
	usartPutStr(" 3 - bring mcu to dps1 mode\r\n");
	usartPutStr(" 4 - bring mcu to dps2 mode\r\n");
	usartPutStr("=================================================\r\n");
	usartPutStr(">> Issue command for test cases: ");
}

void gppPullupAll()
{
	// Enable pullup of all unused GPIO
	// Note:
	//	- drive I/O of input mode to high, will enable its pullup
	gppEnablePullup(GPPB, PALL);
	gppEnablePullup(GPPC, PALL);
	gppEnablePullup(GPPD, PALL);
	gppEnablePullup(GPPE, PALL);
	gppEnablePullup(GPPF, PALL);
}

int main()
{
	uint8_t cmd = 0xff;

    // configure system clock to 16MHz
    // ==============================================================
    // DO NOT forget to set right F_CPU definition according to 
    // your system clock settings
    // F_CPU is defined inside of 'lgt8f328p_misc.h'
    // =============================================================
    sysClockPrescale(SYSCLK_DIV_2);  


	// initialize power control module
	// ===============================================================
	// pwrInit() is optional
	// ===============================================================
	pwrInit();

	// initial other helper function
	usartInit();

	// drive GPIO to stable state for minimize power leakage
	gppPullupAll();

	// demo banner
	// ---------------------------------------------------------------
	printHelper();

	while(1)
	{
		// waiting for commands
		if((UCSR0A & (1 << RXC0))) {
			cmd = usartGetChar();
		} else {
			//cmd = 0xff;
			continue;
		}

		if(cmd == 0x30) {
			usartPutStr("\r\n>> System now sleep to IDLE mode!\r\n");
			pwrSleep(SLEEP_IDLE);
		} else if(cmd == 0x31) {
			usartPutStr("\r\n>> System now sleep to SAVE mode!\r\n");
			pwrSleep(SLEEP_SAVE);
		} else if(cmd == 0x32) {
			usartPutStr("\r\n>> System now sleep to DPS0 mode!\r\n");
			pwrSleep(SLEEP_DPS0);
		} else if(cmd == 0x33) {
			usartPutStr("\r\n>> System now sleep to DPS1 mode!\r\n");
			pwrSleep(SLEEP_DPS1);
		} else if(cmd == 0x34) {
			// DPS2 settings
			// ---------------------------------------
			// disable LPRC for DPS2 mode
			pwrDPS2LPRCMode(DPS2_LPRC_OFF);
			// enable PD2/3 level change for wakeup
			//pwrIOCDForWakeup(_BV(PD2) | _BV(PD3));  
			// enable DPS2 mode
			pwrDPS2Enable();
			
			usartPutStr("\r\n>> System now sleep to DPS2 mode!\r\n");
			// bring system to DPS2
			// ---------------------------------------
			pwrSleep(SLEEP_DPS2);
		} else {
			printHelper();
		}

		_delay_ms(500);
	}
}

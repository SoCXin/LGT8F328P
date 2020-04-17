#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <avr/io.h>

#include "lgt8f328p_conf.h"

// included after definition of F_CPU
#include <util/delay.h>

// global definitions
// ===================================================================
char	caTmp[8];

static uint8_t adcVREFSel;
static uint16_t adcTmp[5];

static uint16_t chipAVCC;	// mV
static uint16_t chipAVREF;	// mV

static uint16_t adcVREF; // mV

uint16_t adcReadByAverage(uint8_t chn)
{
	uint8_t i;
	uint16_t iTmp = 0;

	// dummy read
	adcReadChannel(chn);

	for(i = 0; i < 4; i++)
		iTmp += adcReadChannel(chn);
	
	// average of 4x oversample	
	iTmp >>= 2; 

	return iTmp;
}

void adcGetVCCAndAVREF()
{
	// set Reference to internal 2.048V
	adcSetReference(ADC_REFS_2V048);

	// set VDS source from VCC
	ADCSRD = 0x06;
	
	_delay_us(200); // wait for stable
	
	chipAVCC = adcReadByAverage(ADC_CHMUX_V5D1);
	chipAVCC >>= 1; // convert to mV
	chipAVCC *= 5; // upscale

	// set VDS source from AVREF
	ADCSRD = 0x05;

	_delay_us(200); // wait for stable

	chipAVREF = adcReadByAverage(ADC_CHMUX_V5D1);
	chipAVREF >>= 1; // convert to mV
	chipAVREF *= 5; // upscale
	
	// set VDS to source from AVCC
	ADCSRD = 0x06;

	// restore Reference settings
	adcSetReference(adcVREFSel);
}

void adcDoCommand(uint8_t chn)
{
	uint8_t i;
	uint16_t adcVal = 0;
	uint32_t dwTmp = 0UL;

	adcTmp[4] = adcReadChannel(chn);
	adcTmp[3] = adcReadChannel(chn);
	adcTmp[2] = adcReadChannel(chn);
	adcTmp[1] = adcReadChannel(chn);
	adcTmp[0] = adcReadChannel(chn);

	for(i = 0; i < 4; i++)
		adcVal += adcTmp[i];
	
	// average of 4x oversample	
	adcVal >>= 2; 

	// print what we got:
	usartPutStr("\r\n>> ADC channel (");
	utoa(chn, caTmp, 10);
	usartPutStr(caTmp);
	usartPutStr(") 4x samples: ");
	for(i = 0; i < 4; i++) {
		usartPutStr("0x");
		utoa(adcTmp[i], caTmp, 16);
		usartPutStr(caTmp);
		if(i < 3) usartPutStr(", ");
	}
	
	usartPutStr("\r\n");
	usartPutStr(">> Average = 0x");
	utoa(adcVal, caTmp, 16);
	usartPutStr(caTmp);
	usartPutStr(" (");

	// covert to real voltage
	dwTmp = ((uint32_t)adcVREF * (uint32_t)adcVal)/4096UL;
	utoa((uint16_t)dwTmp, caTmp, 10);
	usartPutStr(caTmp);
	usartPutStr("mV)\r\n");

	// return to command prompt:
	usartPutStr("-------------------------------------------------\r\n");
	usartPutStr(">> Waiting your command: ");

}

// helper function definitions
// ===================================================================
void printCurrentReference()
{
	switch(adcVREFSel) {
		case 0x0: 
			adcVREF = chipAVREF;
			usartPutStr("Current ADC Reference: AVREF(PE6) = ");
			utoa(chipAVREF, caTmp, 10);
			usartPutStr(caTmp);
			usartPutStr("mV\r\n");
			break;
		case 0x1:
			adcVREF = chipAVCC;
			usartPutStr("Current ADC Reference: AVCC = ");
			utoa(chipAVCC, caTmp, 10);
			usartPutStr(caTmp);
			usartPutStr("mV\r\n");
			break;
		case 0x2:
			adcVREF = 2048;
			usartPutStr("Current ADC Reference: Internal 2.048V\r\n");
			break;		
		case 0x3:
			adcVREF = 1024;
			usartPutStr("Current ADC Reference: Internal 1.024V\r\n");
			break;
		case 0x4:
			adcVREF = 4096;
			usartPutStr("Current ADC Reference: Internal 4.096V\r\n");
			usartPutStr(" - Note that this option should be used with VCC higher than 4.7V\r\n");
			usartPutStr(" - Also, make sure this reference is calibrated.\r\n");
			break;
		default:
			adcVREF = 2048;
			adcVREFSel = 2;
			usartPutStr("Current ADC Reference: Wrong settings!!!\r\n");
			usartPutStr(" - Force to use internal 2.048V now!!!\r\n");
			break;
	}
}

void printMainHelper()
{
	// get current VCC and AVREF
	adcGetVCCAndAVREF();

	usartPutStr("\r\n=================================================\r\n");
	usartPutStr("LGT8F328P Software Design Kit \r\n");
	usartPutStr("**** ADC Module Usage **** \r\n");
	usartPutStr("-------------------------------------------------\r\n");
	usartPutStr("Command for channel selection: \r\n");
	usartPutStr(" h - print help information\r\n");
	usartPutStr(" s - Set/Test Reference Volage\r\n");
	usartPutStr(" 0 - ADC external channel 00 (PC0)\r\n");
	usartPutStr(" 1 - ADC external channel 01 (PC1)\r\n");
	usartPutStr(" 2 - ADC external channel 02 (PC2)\r\n");
	usartPutStr(" 3 - ADC external channel 03 (PC3)\r\n");
	usartPutStr(" 4 - ADC external channel 04 (PC4)\r\n");
	usartPutStr(" 5 - ADC external channel 05 (PC5)\r\n");
	usartPutStr(" 6 - ADC external channel 06 (PE1)\r\n");
	usartPutStr(" 7 - ADC external channel 07 (PE3)\r\n");
	usartPutStr(" 8 - ADC internal channel 08 (1/5VCC)\r\n");
	usartPutStr(" 9 - ADC external channel 09 (PC7)\r\n");
	usartPutStr(" a - ADC external channel 10 (PF0)\r\n");
	usartPutStr(" b - ADC external channel 11 (PE6)\r\n");
	usartPutStr(" c - ADC external channel 12 (PE7)\r\n");
	usartPutStr(" d - ADC internal channel 13 (IVREF)\r\n");
	usartPutStr(" e - ADC internal channel 14 (4/5VCC)\r\n");
	usartPutStr(" f - ADC internal channel 15 (AGND)\r\n");
	usartPutStr("=================================================\r\n");

	usartPutStr("Analog Power(AVCC) = ");
	utoa(chipAVCC, caTmp, 10);
	usartPutStr(caTmp);
	usartPutStr("mV\r\n");
	
	usartPutStr("External Reference(AVREF) = ");
	utoa(chipAVREF, caTmp, 10);
	usartPutStr(caTmp);
	usartPutStr("mV\r\n");	

	printCurrentReference();

	usartPutStr("-------------------------------------------------\r\n");
	usartPutStr(">> Waiting your command: ");
}

// Note:
//	internal 4.096V is not calibrated by now....
//	so it is deleted from list.
void printSubHelper()
{
	usartPutStr("\r\n=================================================\r\n");
	usartPutStr("**** Voltage Reference Selection **** \r\n");
	usartPutStr("-------------------------------------------------\r\n");
	usartPutStr("Command definition: \r\n");
	usartPutStr(" q - do nothing then back to main menu\r\n");
	usartPutStr(" t - output internal reference to AVREF(PE6)\r\n");
	usartPutStr(" 0 - set Reference to AVREF(PE6)\r\n");
	usartPutStr(" 1 - set Reference to AVCC\r\n");
	usartPutStr(" 2 - set Reference to internal 2.048V\r\n");
	usartPutStr(" 3 - set Reference to internal 1.024V\r\n");
	//usartPutStr(" 4 - set Reference to internal 4.096V\r\n");
	//usartPutStr(" Note: VCC should be higher than 4.7V for item 4\r\n");
	usartPutStr("=================================================\r\n");
	printCurrentReference();
	usartPutStr("-------------------------------------------------\r\n");
	usartPutStr(">> Waiting your command: ");
}

// Main program
// ===================================================================
int main()
{
	uint8_t isSubMenu = 0;
	uint8_t cmd = 0xff;

    // configure system clock to 16MHz
    // ==============================================================
    // DO NOT forget to set right F_CPU definition according to 
    // your system clock settings
    // F_CPU is defined inside of 'lgt8f328p_misc.h'
    // =============================================================
    sysClockPrescale(SYSCLK_DIV_2);  


 	// default reference from internal 2.048V
	adcVREFSel = ADC_REFS_2V048;

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

	// intialize other modules
	usartInit();

	// print banner
	printMainHelper();
	
	while(1)
	{
		// waiting for commands
		if(usartIsRxReady()) {
			cmd = usartGetChar();
		} else {
			continue;
		}

		usartPutChar(cmd);

		if(isSubMenu == 0) {
			if(cmd >= 0x30 && cmd <= 0x39) {
				cmd -= 0x30;
				adcDoCommand(cmd);
			} else if(cmd >= 0x61 && cmd <= 0x66) {
				cmd -= 0x57;
				adcDoCommand(cmd);
			} else if(cmd == 's') {
				isSubMenu = 1;
				printSubHelper();
			} else {
				printMainHelper();
			}
		} else {
			if(cmd >= 0x30 && cmd <= 0x33) {
				cmd -= 0x30;
				adcVREFSel = cmd;
				adcSetReference(cmd);			
			}

			if(cmd == 't') {
				adcSetChannel(ADC_CHMUX_IVREF);
				adcADTMON();
				if(adcVREFSel == 2)
					usartPutStr("\r\n>> internal 2.048V now output to AVREF/PE6!\r\n");
				else if(adcVREFSel == 3)
					usartPutStr("\r\n>> internal 1.024V now output to AVREF/PE6!\r\n");
				else if(adcVREFSel == 4)
					usartPutStr("\r\n>> internal 4.096V now output to AVREF/PE6!\r\n");
				else
					usartPutStr("\r\n>> please select internal referece for this test!\r\n");
				usartPutStr(">> Waiting your command: ");
			} else if(cmd == 'q') {
				adcADTMOFF();
				isSubMenu = 0;
				printMainHelper();
			} else {
				printSubHelper();
			}
		}
	}
}

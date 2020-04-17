#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <avr/io.h>
#include "lgt8f328p_spec.h"
#include "lgt8f328p_conf.h"

#include <avr/pgmspace.h>

// included after definition of F_CPU
#include <util/delay.h>

#define	isNum(c)		((c >= 0x30) && (c <= 0x39)) // 0 ~ 9
#define isHex(c)		(c >= 0x61 && c <= 0x66)	// a ~ f
#define	isCharLower(c)	((c >= 0x61) && (c <= 0x7a)) // a ~ z
#define	isSpace(c)		(c == 0x20)
#define isDigital(c)	(isNum(c) || isHex(c))
#define isValidKey(c)	(isDigital(c) || isCharLower(c) || isSpace(c))

// global definitions
// ===================================================================
char strBanner01[] PROGMEM = "\r\n=================================================\r\n";
char strHelper01[] PROGMEM = "LGT8F328P Software Design Kit \r\n";
char strHelper02[] PROGMEM = "**** E2PCTL Module Usage **** \r\n";
char strBanner00[] PROGMEM = "-------------------------------------------------\r\n";
char strHelper04[] PROGMEM = "Command definitions: \r\n";
char strHelper05[] PROGMEM = " help - print help information\r\n";
char strHelper06[] PROGMEM = " w[b] address data\r\n";
char strHelper07[] PROGMEM = "    w  - write 32bit data to address\r\n";
char strHelper08[] PROGMEM = "    wb - write 8bit data to address\r\n";
char strHelper09[] PROGMEM = " r[b] address length\r\n";
char strHelper10[] PROGMEM = "    r  - read 32bit data start from address\r\n";
char strHelper11[] PROGMEM = "    rb - read 8bit data start from address\r\n";
char strBanner10[] PROGMEM = "=================================================";

char strUnknown[] PROGMEM = "\r\n>> Unknown command!";
char strReturn[] PROGMEM = "\r\n";
char strPrompt[] PROGMEM = ">> ";
char strNewLine[] PROGMEM = "\r\n>> ";
char strCmdHelp[] PROGMEM = "help";

PGM_P strMainHelperTable[] PROGMEM = 
{
	strBanner01, strHelper01, strHelper02, strBanner00, strHelper04,
	strHelper05, strHelper06, strHelper07, strHelper08, strHelper09,
	strHelper10, strHelper11, strBanner10
};

// helper function definitions
// ===================================================================
void printMainHelper()
{
	char buffer[64];

	for(uint8_t i = 0; i < 13; i++) {
		strcpy_P(buffer, (PGM_P)pgm_read_word(&(strMainHelperTable[i])));
		usartPutStr(buffer);
	}
}

void showstr_P(const char *src)
{
	char buffer[64];
	
	strcpy_P(buffer, src);
	usartPutStr(buffer);
}

#define	showPrompt()	showstr_P(strPrompt)
#define	showReturn()	showstr_P(strReturn)
#define	showTopBanner()	showstr_P(strBanner01)
#define	showBotBanner()	showstr_P(strBanner10)
#define showNewLine()	showstr_P(strNewLine);
#define	showUnknown()	showstr_P(strUnknown);


void cmdExecute(const char *cmd, const char *arg0, const char *arg1)
{
	uint8_t length;
	uint16_t address;
	uint32_t data;
	char caTmp[16];
	char *pEnd0, *pEnd1;

	if(0 == strcmp_P(cmd, strCmdHelp)) {
		printMainHelper();
	} else {
		address = (uint16_t)strtoul(arg0, &pEnd0, 0);
		data = strtoul(arg1, &pEnd1, 0);
		
		length = (uint8_t)data;

		// invalid parameters
		if(*pEnd0 != 0 || *pEnd1 != 0) {
			showUnknown();
			showNewLine();
			return;
		}

		if(0 == strcmp(cmd, "rb")) {
			showReturn();

			for(uint8_t i = 0; i < length; i++)
			{
				utoa(e2pReadByte(address + i), caTmp, 16);
				usartPutStr(caTmp);
				if(i % 10 == 9) showReturn();
				else usartPutChar(0x20);
			}
		} else if(0 == strcmp(cmd, "r")) {
			showReturn();

			for(uint8_t i = 0; i < length; i++)
			{
				ultoa(e2pReadWord((address & 0xfffc) + i*4), caTmp, 16);
				usartPutStr(caTmp);
				if(i % 10 == 9) showReturn();
				else usartPutChar(0x20);
			}
		} else if(0 == strcmp(cmd, "w")) {
			e2pWriteWord((address & 0xfffc), data);
		} else if(0 == strcmp(cmd, "wb")) {
			e2pWriteByte(address, (uint8_t)data);
		} else {
			showUnknown();
		}
	}

	showNewLine();
}

// Main program
// ===================================================================
int main()
{
	char ch, buff[100], *ptok;
	char cmd[16], arg0[16], arg1[16];
	uint8_t len = 0;

    // configure system clock to 16MHz
    // ==============================================================
    // DO NOT forget to set right F_CPU definition according to 
    // your system clock settings
    // F_CPU is defined inside of 'lgt8f328p_misc.h'
    // =============================================================
    sysClockPrescale(SYSCLK_DIV_2);  


	// initialize e2pctl module
	e2pInit();

	// initialize other modules
	usartInit();

	// print banner
	printMainHelper();
	showNewLine();	

	while(1)
	{
		// waiting for commands
		if(usartIsRxReady()) {
			ch = usartGetChar();
			buff[len++] = ch;
			len &= 0x3f;
		} else {
			continue;
		}

		usartPutChar(ch);

		if(ch == 0x0d) {
			if(len == 1) 
				showNewLine();

			buff[len-1] = 0;
			len = 0;
		} else if(0 == isValidKey(ch)) {
			len = 0;
			showUnknown();
		} else continue;

		// command parse
		ptok = strtok(buff, " ");

		if(ptok == NULL) continue;

		strcpy(cmd, ptok);
		ptok = strtok(NULL, " ");

		if(ptok != NULL) {
			strcpy(arg0, ptok);
			ptok = strtok(NULL, " ");
		}

		if(ptok != NULL) {
			strcpy(arg1, ptok);
			ptok = strtok(NULL, " ");
		}

		cmdExecute(cmd, arg0, arg1);
	}
}

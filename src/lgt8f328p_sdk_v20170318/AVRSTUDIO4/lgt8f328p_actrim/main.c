//===================================================
// Auto generated file : 2017/1/21 10:58:53
//===================================================
#include <stdlib.h>

#include <avr/io.h>

#include "lgt8f328p_conf.h"

// include after definition of F_CPU
#include <util/delay.h>

// read AC's output
#define	ac0Read()	((C0SR >> 5) & 0x01)
#define	ac1Read()	((C1SR >> 5) & 0x01)

uint8_t acRead(uint8_t acn)
{
	if(acn == 0)
		return ac0Read();

	return ac1Read();
}

// read AC's output with status flag
//	return :
//		0x80	- stable 0
//		0x81	- stable 1
//		0x00	- unstable
uint8_t acReadStable(uint8_t acn)
{
	uint8_t acTgcnt = 0;
	uint8_t acTmp = acRead(acn);

	for(uint8_t i = 0; i < 0xff; i++) {
		if(acTgcnt > 0x3f)
			return 0;

		if(acTmp != acRead(acn)) {
			i = 0;
			acTgcnt++;
			acTmp = acRead(acn);
		}
	}

	return 0x80 | acTmp;
}

// do calibration work
// return:
//		0x00	- failed
//		others	- C0TR
uint8_t acDoCalibration(uint8_t acn)
{
	uint8_t acdir;
	uint8_t failed = 0;
	
	volatile uint8_t *pCXTR = (acn == 0) ? &C0TR : &C1TR; 

	// trimming data initilize
	*pCXTR = 0xC0;

	acdir = acReadStable(acn);

	// compensate for posedge
	if(acdir == 0x80) {
		*pCXTR = 0x80;
		//_delay_us(10);
	}

	while(acdir == 0x80) {
		if(*pCXTR >= 0xBF) {
			failed = 1;
			break;
		} else if(acReadStable(acn) == 0x81) {
			break;
		} else if(acReadStable(acn) == 0x00) {
			acdir = 0x00;
			break;
		} else {
			*pCXTR = *pCXTR + 1;
			//_delay_us(10);
		}
	}

	// compenstate for negedge
	while(acdir == 0x81) {
		if(*pCXTR == 0xFF) {
			failed = 1;
			break;
		} else if(acReadStable(acn) == 0x80) {
			break;
		} else if(acReadStable(acn) == 0x00) {
			acdir = 0x00;
			break;
		} else {
			*pCXTR = *pCXTR + 1;
			//_delay_us(10);
		}
	}

	while(acdir == 0x00) {
		// do nothing...
		break;
	}

	if(failed == 1) {
		// failed for ac0 trimming
		// so disable trimming circuit
		*pCXTR = 0xC0; // recommended value
	}

	return *pCXTR;
}

// ======================================================
// MAIN PROGRAM START
//
//	drive PC2 = 0 for test AC0
//	drive PC2 = 1 for test AC1
//
// ======================================================
int main(void)
{
	char data[10];
	uint8_t acn = 0;

	sysClockPrescale(SYSCLK_DIV_2);


	// enable PC2's pullup
	PORTC |= 0x04;

	_delay_us(100);

	// which AC for test?
	if((PINC & 0x04) == 0x04)
		acn = 1;

	// initial USART for terminal
	usartInit();

	// internal reference
	ADMUX = 0xD0;	// internal 1.024V BGR
	ADCSRC |= (1 << ADTM);	// for test purpose

	//VCAL = 0x00;

	// DAC source from IVREF
	DACON = (1 << DACEN) | 0x2;

	// minimal DAC output
	DALR = 0;

	// AC inputs settings
	// POS : DAC's output
	// NEG : ACXN/PD7
	if(acn == 0) {
		C0XR = (1 << C0FEN) | (3 << C0FS) | (1 << C0OE);
		C0SR = (1 << C0BG);
	} else {	
		C1XR = (1 << C1FEN) | (3 << C1FS) | (1 << C1OE);
		C1SR = (1 << C1BG);	
	}

	// drive ACXN to ground (by drive PD7)
	DDRD |= 0x80;
	PORTD &= 0x7f;

	acDoCalibration(acn);

	// release PD7
	DDRD &= 0x7f;

	if(acn == 0) {
		usartPutStr("\r\n AC0 trimming done!");
		usartPutStr("\r\n C0TR = 0x");
		utoa(C0TR, data, 16);
	} else {
		usartPutStr("\r\n AC1 trimming done!");
		usartPutStr("\r\n C1TR = 0x");
		utoa(C1TR, data, 16);
	}

	usartPutStr(data);
	
	// bingo...
	while(1) {
		__asm__ __volatile__ ("nop" ::);
	}

	return 0;
}

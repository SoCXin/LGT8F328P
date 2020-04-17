/**********************************************************************************
** Interrupt request server routines impelementation
***********************************************************************************
*/

#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "lgt8f328p_spec.h"
#include "lgt8f328p_conf.h"

// interrupt function for AC0 module
#if AC0_C0IE == 1
ISR(_VECTOR(23))
{
	// Add your code here
	if(HIGH == ac0Read())
		gppSetHigh(GPPB, P0);
	else
		gppSetLow(GPPB, P0);
}
#endif


// interrupt function for AC1 module
#if AC1_C1IE == 1
ISR(_VECTOR(25))
{
	// Add your code here
}
#endif

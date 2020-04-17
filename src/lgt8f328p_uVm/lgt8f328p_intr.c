/**********************************************************************************
** Interrupt request server routines impelementation
***********************************************************************************
*/

#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "lgt8f328p_spec.h"
#include "lgt8f328p_conf.h"

#if ADC_ADIE == 1
ISR(ADC_vect)
{
	// Add your code here
}
#endif

#if USART_RXC == 1
ISR(USART_RX_vect)
{
	// Add your code here
}
#endif

#if USART_TXC == 1
ISR(USART_TX_vect)
{
	// Add your code here
}
#endif


#if USART_UDRE == 1
ISR(USART_UDRE_vect)
{
	// Add your code here
}
#endif

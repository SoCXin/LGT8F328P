/**********************************************************************************
** Interrupt request server routines impelementation
***********************************************************************************
*/

#include <ioavr.h>

#include "lgt8f328p_conf.h"

#if USART_RXC == 1
#pragma vector = USART_RX_vect
__interrupt void USART_RX_isr(void)
{
	// Add your code here
	while(1);
}
#endif

#if USART_TXC == 1
#pragma vector = USART_TX_vect
__interrupt void USART_TX_isr(void)
{
	// Add your code here
	while(1);
}
#endif


#if USART_UDRE == 1
#pragma vector = USART_UDRE_vect
__interrupt void USART_UDRE_isr(void)
{
	// Add your code here
	while(1);
}
#endif

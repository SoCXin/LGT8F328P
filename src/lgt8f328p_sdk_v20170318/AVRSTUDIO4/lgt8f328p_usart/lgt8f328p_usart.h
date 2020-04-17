#ifndef _LGT8F328P_USART_H_
#define _LGT8F328P_USART_H_

#include <stdint.h>

// USART working mode
#define E_UMSEL0_UART	0x0		/**< Asynchronous USART */
#define E_UMSEL0_USRT	0x1		/**< Synchronous USART */
#define E_UMSEL0_SPIS	0x2		/**< Slave SPI */
#define E_UMSEL0_SPIM	0x3		/**< Master SPI */

// USART Parity mode
#define	E_UPM0_NONE		0x0		/**< Disable Parity */
#define	E_UPM0_EVEN		0x2		/**< Enable, Even Parity */
#define	E_UPM0_ODD		0x3		/**< Enable, Odd Parity */

// USART stop bit
#define	E_USBS0_1B		0x0		/**< 1 Stop Bit */
#define	E_USBS0_2B		0x1		/**< 2 Stop Bit */

// USART frame size
#define	E_UCSZ0_5B		0x0		/**< USART Character Size: 5-bit */
#define	E_UCSZ0_6B		0x1		/**< USART Character Size: 6-bit */
#define	E_UCSZ0_7B		0x2		/**< USART Character Size: 7-bit */
#define	E_UCSZ0_8B		0x3		/**< USART Character Size: 8-bit */
#define	E_UCSZ0_9B		0x7		/**< USART Character Size: 9-bit */

// USART clock polarity
#define	E_UCPOL0_TRE_SFE	0x0	/**< Transmit Data on Rising XCK1 Edge, 
								Sample Data on Falling XCK1 Edge */							
#define	E_UCPOL0_TFE_SRE	0x1	/**< Transmitted Data on Falling XCK1 Edge, 
								Sample Data on Rising XCK1 Edge */


/**********************************************************************************
***					     	 MACROS AND DEFINITIONS								***													  	
**********************************************************************************/ 

	
/**********************************************************************************
*** 						  	EXPORTED FUNCTIONS								*** 													
**********************************************************************************/
void usartInit();

void usartPutChar(uint8_t);
void usartPutStr(char *);

uint8_t usartGetChar();

#endif
/**********************************************************************************
***					          			EOF										***													  	
**********************************************************************************/

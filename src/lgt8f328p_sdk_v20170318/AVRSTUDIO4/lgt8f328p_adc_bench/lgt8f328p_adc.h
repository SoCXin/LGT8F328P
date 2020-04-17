#ifndef _LGT8F328P_ADC_H_
#define _LGT8F328P_ADC_H_

#include <stdint.h>

#define ADC_REFS_DEFV		0x0
// ADC references definition
#define ADC_REFS_AVREF		0x0		/**< AVREF */
#define	ADC_REFS_AVCC		0x1		/**< AVCC */
#define	ADC_REFS_2V048		0x2		/**< Internal 2.048V voltage Reference */
#define ADC_REFS_1V024		0x3		/**< Internal 1.024V voltage Reference */
#define	ADC_REFS_4V096		0x4

// ADC data align format
#define	ADC_ADLAR_R			0x0		/**< right adjust the result */
#define	ADC_ADLAR_L			0x1		/**< left adjust the result */

// ADC analog channel definition
#define	ADC_CHMUX_ADC0		0x00		/** Select ADC0(PC0) connect to ADC */
#define	ADC_CHMUX_ADC1		0x01		/** Select ADC1(PC1) connect to ADC */		
#define	ADC_CHMUX_ADC2		0x02		/** Select ADC2(PC2) connect to ADC */
#define	ADC_CHMUX_ADC3		0x03		/** Select ADC3(PC3) connect to ADC */
#define	ADC_CHMUX_ADC4		0x04		/** Select ADC4(PC4) connect to ADC */
#define	ADC_CHMUX_ADC5		0x05		/** Select ADC5(PC5) connect to ADC */
#define	ADC_CHMUX_ADC6		0x06		/** Select ADC6(PE1) connect to ADC */
#define	ADC_CHMUX_ADC7		0x07		/** Select ADC7(PE3) connect to ADC */
#define	ADC_CHMUX_V5D1		0x08		
#define	ADC_CHMUX_ADC8		0x09
#define	ADC_CHMUX_ADC9		0x0A
#define	ADC_CHMUX_ADC10		0x0B
#define	ADC_CHMUX_ADC11		0x0C
#define	ADC_CHMUX_IVREF		0x0D
#define	ADC_CHMUX_V5D4		0x0E		/** select VCC*4/5 Monitor */
#define	ADC_CHMUX_GND		0x0F		/** select analog ground */
#define	ADC_CHMUX_DAC		0x10		/** select DAC's output */
#define	ADC_CHMUX_DAP		0x3F  		/** select DAP's output */

// ADC sample clock prescaler settings
#define	ADC_ADPS_DIV2		0x1			/**< Division Factor is 2 */
#define	ADC_ADPS_DIV4		0x2			/**< Division Factor is 4 */
#define	ADC_ADPS_DIV8		0x3			/**< Division Factor is 8 */
#define	ADC_ADPS_DIV16		0x4			/**< Division Factor is 16 */
#define	ADC_ADPS_DIV32		0x5			/**< Division Factor is 32 */  
#define	ADC_ADPS_DIV64		0x6			/**< Division Factor is 64 */
#define	ADC_ADPS_DIV128		0x7			/**< Division Factor is 128 */

// ADC auto-trigger mode definition
#define	ADC_ADTS_FRUN		0x0			/**< Trigger Source is Free Running */
#define	ADC_ADTS_ACX		0x1			/**< Trigger Source is AC Comparator */
#define	ADC_ADTS_EINT0		0x2			/**< Trigger Source is External Interrupt Request 0 */
#define	ADC_ADTS_OCF0A		0x3			/**< Trigger Source is TC0 Compare Match */
#define	ADC_ADTS_TOV0		0x4			/**< Trigger Source is TC0 Overflow */
#define	ADC_ADTS_OCF1B		0x5			/**< Trigger Source is TC1 Compare Match B */
#define	ADC_ADTS_TOV1		0x6			/**< Trigger Source is TC1 Overflow */
#define	ADC_ADTS_ICP1		0x7			/**< Trigger Source is TC1 Capture Event */

/**********************************************************************************
***					     	 MACROS AND DEFINITIONS								***													  	
**********************************************************************************/ 
#define	adcDisable()	do { ADCSRA &= 0x7F; } while(0)
#define adcEnable()		do { ADCSRA |= 0x80; } while(0)

#define	adcADTMON()		do { ADCSRC |= (1 << ADTM); } while(0)
#define	adcADTMOFF()	do { ADCSRC &= ~(1 << ADTM); } while(0)
	
/**********************************************************************************
*** 						  	EXPORTED FUNCTIONS								*** 													
**********************************************************************************/
void adcInit();
void adcSoftStart();
void adcSetReference(uint8_t);
void adcSetChannel(uint8_t);

uint16_t adcReadChannel(uint8_t);

#endif
/**********************************************************************************
***					          			EOF										***													  	
**********************************************************************************/

#ifndef __LGT8F328P_BITS_H__
#define __LGT8F328P_BITS_H__

/* Bit definitions for use with the IAR Assembler   
   The Register Bit names are represented by their bit number (0-7).
*/

/* UCSR0C */
#define UMSEL01 7
#define UMSEL00 6
#define UPM01 5
#define UPM00 4
#define USBS0 3
#define UCSZ01 2
#define UCSZ00 1
#define UCPOL0 0
#define UDORD0 UCSZ01
#define UCPHA0 UCSZ00

/* UCSR0B */
#define RXCIE0 7
#define TXCIE0 6
#define UDRIE0 5
#define RXEN0 4
#define TXEN0 3
#define UCSZ02 2
#define RXB80 1
#define TXB80 0

/* UCSR0A */
#define RXC0 7
#define TXC0 6
#define UDRE0 5
#define FE0 4
#define DOR0 3
#define UPE0 2
#define U2X0 1
#define MPCM0 0

/* TWAMR */
#define TWAM6 7
#define TWAM5 6
#define TWAM4 5
#define TWAM3 4
#define TWAM2 3
#define TWAM1 2
#define TWAM0 1

/* TWCR */
#define TWINT 7
#define TWEA 6
#define TWSTA 5
#define TWSTO 4
#define TWWC 3
#define TWEN 2
#define TWIE 0

/* TWAR */
#define TWA6 7
#define TWA5 6
#define TWA4 5
#define TWA3 4
#define TWA2 3
#define TWA1 2
#define TWA0 1
#define TWGCE 0

/* TWSR */
#define TWS7 7
#define TWS6 6
#define TWS5 5
#define TWS4 4
#define TWS3 3
#define TWPS1 1
#define TWPS0 0

/* ASSR */
#define EXCLK 6
#define AS2 5
#define TCN2UB 4
#define OCR2AUB 3
#define OCR2BUB 2
#define TCR2AUB 1
#define TCR2BUB 0

/* TCCR2B */
#define FOC2A 7
#define FOC2B 6
#define WGM22 3
#define CS22 2
#define CS21 1
#define CS20 0

/* TCCR2A */
#define COM2A1 7
#define COM2A0 6
#define COM2B1 5
#define COM2B0 4
#define WGM21 1
#define WGM20 0

/* TCCR1C */
#define FOC1A 7
#define FOC1B 6

/* TCCR1B */
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

/* TCCR1A */
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define WGM11 1
#define WGM10 0

/* DIDR1 */
#define AIN1D 1
#define AIN0D 0

/* DIDR0 */
#define ADC5D 5
#define ADC4D 4
#define ADC3D 3
#define ADC2D 2
#define ADC1D 1
#define ADC0D 0

/* ADMUX */
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX3 3
#define MUX2 2
#define MUX1 1
#define MUX0 0

/* ADCSRB */
#define ACME 6
#define ADTS2 2
#define ADTS1 1
#define ADTS0 0

/* ADCSRA */
#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

/* TIMSK2 */
#define OCIE2B 2
#define OCIE2A 1
#define TOIE2 0

/* TIMSK1 */
#define ICIE1 5
#define OCIE1B 2
#define OCIE1A 1
#define TOIE1 0

/* TIMSK0 */
#define OCIE0B 2
#define OCIE0A 1
#define TOIE0 0

/* PCMSK2 */
#define PCINT23 7
#define PCINT22 6
#define PCINT21 5
#define PCINT20 4
#define PCINT19 3
#define PCINT18 2
#define PCINT17 1
#define PCINT16 0

/* PCMSK1 */
#define PCINT14 6
#define PCINT13 5
#define PCINT12 4
#define PCINT11 3
#define PCINT10 2
#define PCINT9 1
#define PCINT8 0

/* PCMSK0 */
#define PCINT7 7
#define PCINT6 6
#define PCINT5 5
#define PCINT4 4
#define PCINT3 3
#define PCINT2 2
#define PCINT1 1
#define PCINT0 0

/* EICRA */
#define ISC11 3
#define ISC10 2
#define ISC01 1
#define ISC00 0

/* PCICR */
#define PCIE2 2
#define PCIE1 1
#define PCIE0 0

/* PRR */
#define PRTWI 7
#define PRTIM2 6
#define PRTIM0 5
#define PRTIM1 3
#define PRSPI 2
#define PRUSART0 1
#define PRADC 0

/* CLKPR */
#define CLKPCE 7
#define CLKPS3 3
#define CLKPS2 2
#define CLKPS1 1
#define CLKPS0 0

/* WDTCSR */
#define WDIF 7
#define WDIE 6
#define WDP3 5
#define WDCE 4
#define WDE 3
#define WDP2 2
#define WDP1 1
#define WDP0 0

/* SPH */
#define SP10 2
#define SP9 1
#define SP8 0

/* SPL */
#define SP7 7
#define SP6 6
#define SP5 5
#define SP4 4
#define SP3 3
#define SP2 2
#define SP1 1
#define SP0 0

/* SPMCSR */
#define SPMIE 7
#define RWWSB 6
#define RWWSRE 4
#define BLBSET 3
#define PGWRT 2
#define PGERS 1
#define SELFPRGEN 0

/* MCUCR */
#define BODS 6
#define BODSE 5
#define PUD 4
#define IVSEL 1
#define IVCE 0

/* MCUSR */
#define WDRF 3
#define BORF 2
#define EXTRF 1
#define PORF 0

/* SMCR */
#define SM2 3
#define SM1 2
#define SM0 1
#define SE 0

/* ACSR */
#define ACD 7
#define ACBG 6
#define ACO 5
#define ACI 4
#define ACIE 3
#define ACIC 2
#define ACIS1 1
#define ACIS0 0

/* SPSR */
#define SPIF 7
#define WCOL 6
#define SPI2X 0

/* SPCR */
#define SPIE 7
#define SPE 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

/* TCCR0B */
#define FOC0A 7
#define FOC0B 6
#define WGM02 3
#define CS02 2
#define CS01 1
#define CS00 0

/* TCCR0A */
#define COM0A1 7
#define COM0A0 6
#define COM0B1 5
#define COM0B0 4
#define WGM01 1
#define WGM00 0

/* GTCCR */
#define TSM 7
#define PSRASY1 1
#define PSRSYNC 0

/* EECR */
#define EEPM1 5
#define EEPM0 4
#define EERIE 3
#define EEMPE 2
#define EEPE 1
#define EERE 0

/* EIMSK */
#define INT1 1
#define INT0 0

/* EIFR */
#define INTF1 1
#define INTF0 0

/* PCIFR */
#define PCIF2 2
#define PCIF1 1
#define PCIF0 0

/* TIFR2 */
#define OCF2B 2
#define OCF2A 1
#define TOV2 0

/* TIFR1 */
#define ICF1 5
#define OCF1B 2
#define OCF1A 1
#define TOV1 0

/* TIFR0 */
#define OCF0B 2
#define OCF0A 1
#define TOV0 0

/* PORTD */
#define PORTD7 7
#define PORTD6 6
#define PORTD5 5
#define PORTD4 4
#define PORTD3 3
#define PORTD2 2
#define PORTD1 1
#define PORTD0 0

#define PD7 7
#define PD6 6
#define PD5 5
#define PD4 4
#define PD3 3
#define PD2 2
#define PD1 1
#define PD0 0

/* DDRD */
#define DDD7 7
#define DDD6 6
#define DDD5 5
#define DDD4 4
#define DDD3 3
#define DDD2 2
#define DDD1 1
#define DDD0 0

/* PIND */
#define PIND7 7
#define PIND6 6
#define PIND5 5
#define PIND4 4
#define PIND3 3
#define PIND2 2
#define PIND1 1
#define PIND0 0

/* PORTC */
#define PORTC6 6
#define PORTC5 5
#define PORTC4 4
#define PORTC3 3
#define PORTC2 2
#define PORTC1 1
#define PORTC0 0

#define PC6 6
#define PC5 5
#define PC4 4
#define PC3 3
#define PC2 2
#define PC1 1
#define PC0 0

/* DDRC */
#define DDC6 6
#define DDC5 5
#define DDC4 4
#define DDC3 3
#define DDC2 2
#define DDC1 1
#define DDC0 0

/* PINC */
#define PINC6 6
#define PINC5 5
#define PINC4 4
#define PINC3 3
#define PINC2 2
#define PINC1 1
#define PINC0 0

/* PORTB */
#define PORTB7 7
#define PORTB6 6
#define PORTB5 5
#define PORTB4 4
#define PORTB3 3
#define PORTB2 2
#define PORTB1 1
#define PORTB0 0

#define PB7 7
#define PB6 6
#define PB5 5
#define PB4 4
#define PB3 3
#define PB2 2
#define PB1 1
#define PB0 0

/* DDRB */
#define DDB7 7
#define DDB6 6
#define DDB5 5
#define DDB4 4
#define DDB3 3
#define DDB2 2
#define DDB1 1
#define DDB0 0

/* PINB */
#define PINB7 7
#define PINB6 6
#define PINB5 5
#define PINB4 4
#define PINB3 3
#define PINB2 2
#define PINB1 1
#define PINB0 0

/* Extended Fuse Byte */
#define BOOTSZ1   2
#define BOOTSZ0   1
#define BOOTRST   0

/* High Fuse Byte */
#define RSTDISBL  7
#define DWEN      6
#define SPIEN     5
#define WDTON     4
#define EESAVE    3
#define BODLEVEL2 2
#define BODLEVEL1 1
#define BODLEVEL0 0

/* Low Fuse Byte */
#define CKDIV8    7
#define CKOUT     6
#define SUT1      5
#define SUT0      4
#define CKSEL3    3
#define CKSEL2    2
#define CKSEL1    1
#define CKSEL0    0

/* Pointer definition */
#define    XL     r26
#define    XH     r27
#define    YL     r28
#define    YH     r29
#define    ZL     r30
#define    ZH     r31

/* Constants */
#define    RAMEND   0x08FF    /*Last On-Chip SRAM location*/
#define    XRAMEND  0x08FF
#define    E2END    0x03FF
#define    FLASHEND 0x7FFF


#define FLASH_PAGE_SIZE  0x80
#define EEPROM_PAGE_SIZE 0x04

#endif /* ENABLE_BIT_DEFINITIONS */ 

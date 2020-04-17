/**********************************************************************************
** API implementation for system micelliance module
***********************************************************************************
*/

#include <avr/io.h>

#include "lgt8f328p_misc.h"

// including after definition of F_CPU
#include <util/delay.h>


/**********************************************************************************
*** 	EXPORTED FUNCTIONS							***
**********************************************************************************/

// ----------------------------------------------------------------------
// local variable for SREG backup and restore
// ----------------------------------------------------------------------
static uint8_t __bk_sreg;

// ----------------------------------------------------------------------
// public: backup SREG register, then disable global interrupt
// ----------------------------------------------------------------------
void sysCLRI()
{
    __bk_sreg = SREG;
    cli();
}

// ----------------------------------------------------------------------
// public: restore SREG register, so restore previous interrupt settings
// ----------------------------------------------------------------------
void sysRESI()
{
    SREG = __bk_sreg;
}

// ----------------------------------------------------------------------
// public: disalbe SWD/SWC interface to release PE0/2
// ----------------------------------------------------------------------
inline void sysSWDDisable()
{
    MCUSR = 0xff;
    MCUSR = 0xff;
}

inline void sysSWDEnable()
{
    MCUSR = 0x7f;
    MCUSR = 0x7f;
}

// ----------------------------------------------------------------------
// public: disable AVREF to release PE6 for GPIO
// ----------------------------------------------------------------------
void sysAVREFDisable()
{
    uint8_t btmp = PMX2 | (1 << E6EN);
    PMX2 = 0x80;
    PMX2 = btmp;
}

void sysAVREFEnable()
{
    uint8_t btmp = PMX2 & ~(1 << E6EN);
    PMX2 = 0x80;
    PMX2 = btmp;
}

// ----------------------------------------------------------------------
// public: disable EXRESET to release PC6 for GPIO
// ----------------------------------------------------------------------
void sysEXRESETDisable()
{
    uint8_t btmp = PMX2 | (1 << C6EN);
    PMX2 = 0x80;
    PMX2 = btmp;
}

void sysEXRESETEnable()
{
    uint8_t btmp = PMX2 & ~(1 << C6EN);
    PMX2 = 0x80;
    PMX2 = btmp;
}

// ----------------------------------------------------------------------
// public: Switch system clock between internal 32MHz RC and
//              external high speed crystal
// note:
//     set prescale will disable system clock output on either PE5/PB0
//      please re-enable system clock output if necessary    
// ----------------------------------------------------------------------
void sysClockSource(uint8_t mode)
{
    uint8_t btmp;
  
    if(mode == EXT_OSC) {
            // enable external crystal
            btmp = PMCR | 0x04;
            PMCR = 0x80;
            PMCR = btmp;
            
            // waiting for crystal stable
            _delay_us(20);

            // switch to external crystal
            btmp = (PMCR & 0x9f) | 0x20;
            PMCR = 0x80;
            PMCR = btmp;

            // set to right prescale
            CLKPR = 0x80;
            CLKPR = 0x00;	
    } else if(mode == INT_OSC) {
            // prescaler settings
            CLKPR = 0x80;
            CLKPR = 0x01;	

            // switch to internal crystal
            btmp = PMCR & 0x9f;
            PMCR = 0x80;
            PMCR = btmp;

            // disable external crystal
            btmp = PMCR & 0xfb;
            PMCR = 0x80;
            PMCR = btmp;
    }
}

// ----------------------------------------------------------------------
// public: set main clock prescale
//      - prescale options:
//              SYSCLK_DIV_0 ~ SYSCLK_DIV_128
// ----------------------------------------------------------------------
inline void sysClockPrescale(uint8_t divn)
{
    uint8_t btmp = 0x80 | (divn & 0xf);
    CLKPR = 0x80;
    CLKPR = btmp;
}

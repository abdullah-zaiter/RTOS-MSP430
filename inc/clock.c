#include <msp430.h>
#include <stdint.h>
#include "clock.h"

void clockInit () {
#if defined(__MSP430FR5994__)
    /* Clock Configuration */
    // Connect XTAL pins to CS module
    PJSEL1 &= ~(BIT4 | BIT5 | BIT6 | BIT7); // PSEL = 01 => XTAL
    PJSEL0 |=  (BIT4 | BIT5 | BIT6 | BIT7); //

    CSCTL0 = 0xA500;                        // Password - Enable configuration

    CSCTL1 = DCORSEL |                      // Top tier clock speeds
             DCOFSEL_4;                     // 16 MHz clock

    CSCTL2 = SELA__LFXTCLK |                // ACLK  => XTAL (32kHz)
             SELS__DCOCLK  |                // SMCLK => DCO  (16MHz/16)
             SELM__DCOCLK;                  // MCLK  => DCO  (16MHz)

    CSCTL3 = DIVA__1  |                     // Clock dividers
             DIVS__16 |                     // SMCLK / 16
             DIVM__1 ;                      //

    CSCTL4 = HFXTDRIVE_0 | HFXTBYPASS_0 |   // HF XTAL is disabled
             HFXTOFF_1   | HFFREQ_0     |
             LFXTDRIVE_3 | LFXTBYPASS_0 |   // High drive for fast start-up
             LFXTOFF_0   |                  // LF XTAL is enabled
             VLOOFF_0    |                  // VLO   => on
             SMCLKOFF_0;                    // SMCLK => on

    CSCTL5 = ENSTFCNT1__ENABLE |            // Fault counters enabled
             ENSTFCNT2__ENABLE |            //
             HFXTOFFG_0 | LFXTOFFG_0;       // Reset fault flags

    CSCTL6 = MODCLKREQEN__ENABLE |          // Enable conditional
             SMCLKREQEN__ENABLE  |          // clock requests
             MCLKREQEN__ENABLE   |
             ACLKREQEN__ENABLE;

    do {                                    // Check if all clocks are oscillating
        CSCTL5 &= ~(HFXTOFFG | LFXTOFFG);   // Clear HFXT,LFXT fault flags;
        SFRIFG1 &= ~OFIFG;                  // Clear general oscillator fault flag
    } while (SFRIFG1 & OFIFG);              // Test oscillator fault flag

    CSCTL4 &= ~LFXTDRIVE_3;                 // Once XTAL is running, reduce
                                            // drive to save power
#elif defined(__MSP430F5529__)
    // Configure crystal ports
    P5SEL |= BIT2 | BIT3 | BIT4 | BIT5;     // Configure P5 to use Crystals

    UCSCTL6 = XT2DRIVE_3      |             // XT2 and XT1 drive can be
              XT1DRIVE_3      |             // lowered to 0 (default is 3)
              XCAP_3          |             // This is the default (3).
//            XT1OFF          |             // Turns off XT1 when set
//            XT2OFF          |             // Turns off XT2 when set
//            XT1BYPASS       |             // Not using external clock source
//            XT2BYPASS       |             // Not using external clock source
//            XTS                           //
              0;

    UCSCTL0 = 0x00;                         // Let FLL manage DCO and MOD

    UCSCTL1 = DCORSEL_1       |             // Select DCO range to 1MHz
//            DISMOD          |             // Enable modulator
              0;

    UCSCTL2 = FLLD__16        |             // Set FLL dividers
              FLLN(32);

    UCSCTL3 = SELREF__XT1CLK  |             // Use Crystal 1 Oscillator divided
              FLLREFDIV__16;                // by 16 for better precision

    UCSCTL5 = DIVPA__1        |             // Output dividers to 1
              DIVA__1         |             // ACLK  divider 1
              DIVS__1         |             // SMCLK divider 4
              DIVM__1;                      // MCLK  divider 1

    UCSCTL7 = 0;                            // Clear XT2,XT1,DCO fault flags

    UCSCTL8 = SMCLKREQEN      |             // Enable conditional requests for
               MCLKREQEN      |             // SMCLK, MCLK and ACLK
               ACLKREQEN;

    do {                                    // Check if all clocks are oscillating
      UCSCTL7 &= ~( XT2OFFG   |             // Clear XT2,XT1,DCO fault flags
                    XT1LFOFFG |
                    DCOFFG);
      SFRIFG1 &= ~OFIFG;                    // Clear fault flags
    } while (SFRIFG1 & OFIFG);              // Test oscillator fault flag

    UCSCTL6 &= ~(XT1DRIVE_3   |             // Xtal is now stable,
                 XT2DRIVE_3);               // reduce drive strength (to save power)

    UCSCTL4 = SELA__XT1CLK    |             // ACLK  = Crystal 1  =>     32.768 Hz
              SELS__XT1CLK    |             // SMCLK = Crystal 1  =>     32.768 Hz
              SELM__XT2CLK;                 // MCLK  = Crystal 2  =>  1.000.000 Hz
#endif
}
#if defined(__MSP430F5529__)
uint8_t clockSelect(uint16_t source, uint16_t destination)
{
    // ACLK is reserved for Timer A2
    if (destination == ACLK)
        return ACLK_RESERVED;
    // Use destination as a mask
    UCSCTL4 = (UCSCTL4 & ~destination) | (destination & source);
    return SUCCESS;
}

uint8_t clockDivide(uint16_t destination, uint8_t divider)
{
    // ACLK is reserved for Timer A2
    if (destination == ACLK) {
        return ACLK_RESERVED;
    }
    // If number is a power of two and not zero.
    //if ( (divider != 0) && (divider & (divider-1) ) {
    UCSCTL5 = (UCSCTL5 & ~destination) | // Clear destination bits
              (divider &  destination);  // And set only bits masked by dst
    return SUCCESS;
}


uint16_t clockSetDCO(uint32_t targetFrequency ){

    unsigned long int divider;
    unsigned long int refFrequency;

    // Auto-choose reference range
    if (targetFrequency <=  200000) return FREQ_TOO_LOW;
    if (targetFrequency >   200000) UCSCTL1 = DCORSEL_0;
    if (targetFrequency >   500000) UCSCTL1 = DCORSEL_1;
    if (targetFrequency >  1000000) UCSCTL1 = DCORSEL_2;
    if (targetFrequency >  2000000) UCSCTL1 = DCORSEL_3;
    if (targetFrequency >  4000000) UCSCTL1 = DCORSEL_4;
    if (targetFrequency > 10000000) UCSCTL1 = DCORSEL_5;
    if (targetFrequency > 18000000) UCSCTL1 = DCORSEL_6;
    if (targetFrequency > 30000000) UCSCTL1 = DCORSEL_7;

    // If divisible by 250kHz -> should pick 4MHz/16
    if(!(targetFrequency % 250000)) {
        // Select XT2 as reference
        UCSCTL3 = SELREF__XT2CLK | FLLREFDIV__16;
        refFrequency = 250000ul;
    } else {
        // Else, use XT1
        UCSCTL3 = SELREF__XT1CLK | FLLREFDIV__16;
        refFrequency = 2048ul;
    }

    divider = targetFrequency/refFrequency;

    if (                      (divider <  1024)) UCSCTL2 = FLLD__1  | FLLN(divider);
    if ((divider >=  1024) && (divider <  2048)) UCSCTL2 = FLLD__2  | FLLN(divider >> 1);
    if ((divider >=  2048) && (divider <  4096)) UCSCTL2 = FLLD__4  | FLLN(divider >> 2);
    if ((divider >=  4096) && (divider <  8192)) UCSCTL2 = FLLD__8  | FLLN(divider >> 3);
    if ((divider >=  8192) && (divider < 16384)) UCSCTL2 = FLLD__16 | FLLN(divider >> 4);
    if ((divider >= 16384) && (divider < 32768)) UCSCTL2 = FLLD__32 | FLLN(divider >> 5);
    if ((divider >= 32768)                     ) return FREQ_TOO_HIGH;

    return SUCCESS;
    //return (divider >> 10);
}
#endif

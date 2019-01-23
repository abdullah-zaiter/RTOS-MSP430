#include <msp430.h>

void SetVCoreUp (unsigned int level)
{

    PMMCTL0_H = 0xA5;                       // Open PMM registers for write access

//    while ((PMMIFG & SVSMHDLYIFG) == 0);    // Make sure no flags are set for
//    while ((PMMIFG & SVSMLDLYIFG) == 0);    // iterative sequences

    SVSMHCTL =                              // Set SVS/SVM high side new level
            SVSHE            +
            SVSHRVL0 * level +
            SVMHE            +
            SVSMHRRL0 * level;

    SVSMLCTL =                              // Set SVM low side to new level
            SVSLE            +
//          SVSLRVL0 * level +              // but not SVS, not yet..
            SVMLE            +
            SVSMLRRL0 * level;

    while ((PMMIFG & SVSMLDLYIFG) == 0);    // Wait till SVM is settled

    PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);      // Clear already set flags

    PMMCTL0_L = PMMCOREV0 * level;          // Set VCore to new level

    if ((PMMIFG & SVMLIFG))                 // Wait till new level reached
        while ((PMMIFG & SVMLVLRIFG) == 0);

    SVSMLCTL =                              // Set SVS/SVM low side to new level
            SVSLE            +
            SVSLRVL0 * level +
            SVMLE            +
            SVSMLRRL0 * level;

    PMMCTL0_H = 0x00;                       // Lock PMM registers for write access
}

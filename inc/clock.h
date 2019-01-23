#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

#define FLLN(x) ((x)-1)

// Clock names
#define MCLK    0x0007u
#define SMCLK   0x0070u
#define ACLK    0x0700u
#define PACLK   0x7000u

// Clock sources
#define XT1     0x0000u
#define VLO     0x1111u
#define REFO    0x2222u
#define DCO     0x3333u
#define DCODIV  0x4444u
#define XT2     0x5555u

// Dividers
#define DIV_1   0x0
#define DIV_2   0x1
#define DIV_4   0x2
#define DIV_8   0x3
#define DIV_16  0x4
#define DIV_32  0x5

// Order of magnitude
#define MHz     *1E6
#define kHz     *1E3
#define  Hz     *1E0

// Errors
#define SUCCESS                0x00
#define FREQ_TOO_LOW           0x02
#define FREQ_TOO_HIGH          0x04
#define TARGET_LOWER_THAN_REF  0x08
#define NOT_POWER_OF_2         0x10
#define ACLK_RESERVED          0x20


void  clockInit();
uint16_t  clockSetDCO(uint32_t targetFrequency);
uint8_t  clockSelect(uint16_t source, uint16_t destination);
uint8_t  clockDivide(uint16_t destination, uint8_t divider);

#endif /* CLOCK_H_ */

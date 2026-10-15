/* 74LS164.c */
#include "defines.h"
#include "delays.h"
#include <LPC21xx.h>

// Display 1
#define SIN1   8     //p0.8
#define CP1    9     //p0.9
// Display 2
#define SIN2   10    //p0.10
#define CP2    11    //p0.11
// Display 3
#define SIN3   12    //p0.12
#define CP3    13    //p0.13
// Display 4
#define SIN4   14    //p0.14
#define CP4    15    //p0.15

void Init_74LS164(void)
{
	IODIR0 |= (1<<SIN1)|(1<<CP1)|
	          (1<<SIN2)|(1<<CP2)|
	          (1<<SIN3)|(1<<CP3)|
	          (1<<SIN4)|(1<<CP4);
}

/* generic shift-out: pushes one byte (8 bits, MSB first) into the
   74LS164 connected to the given SIN/CP pin pair */
static void SIPO_pins(unsigned char sDat, unsigned char sinPin, unsigned char cpPin)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		// Set data bit MSB-first using IOSET0/IOCLR0 (IOPIN0 write is unreliable)
		if((sDat>>(7-i))&1)
			IOSET0 = (1UL<<sinPin);   // data = 1
		else
			IOCLR0 = (1UL<<sinPin);   // data = 0

		delay_us(1);                 // let data settle before clock edge

		IOSET0 = (1UL<<cpPin);       // clock high - 74LS164 shifts in bit
		delay_us(1);
		IOCLR0 = (1UL<<cpPin);       // clock low
		delay_us(1);
	}
}

/* kept for backward compatibility - drives Display 1 only */
void SIPO_74LS164(unsigned char sDat)
{
	SIPO_pins(sDat,SIN1,CP1);
}

void SIPO_74LS164_1(unsigned char sDat) { SIPO_pins(sDat,SIN1,CP1); }
void SIPO_74LS164_2(unsigned char sDat) { SIPO_pins(sDat,SIN2,CP2); }
void SIPO_74LS164_3(unsigned char sDat) { SIPO_pins(sDat,SIN3,CP3); }
void SIPO_74LS164_4(unsigned char sDat) { SIPO_pins(sDat,SIN4,CP4); }

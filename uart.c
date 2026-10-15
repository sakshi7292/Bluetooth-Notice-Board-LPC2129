#include <LPC21xx.H>
#include "uart.h"

#define MSGSIZE 64

volatile unsigned char buff[MSGSIZE];
volatile unsigned char idx=0;
volatile unsigned char r_flag=0;

void UART0_isr(void) __irq
{
	unsigned char ch;
	unsigned char iir_id = (U0IIR >> 1) & 0x07;   // isolate interrupt-ID bits [3:1]

	if(iir_id == 0x02 || iir_id == 0x06)   // RDA or Character-Timeout: real data
	{
		ch = U0RBR;
		if(ch != '$')
		{
			if(idx < MSGSIZE-1)
				buff[idx++] = ch;
		}
		else
		{
			buff[idx] = '\0';
			idx = 0;
			r_flag = 1;
		}
	}
	else if(iir_id == 0x03)   // Receive Line Status error: discard, clear by reading LSR
	{
		ch = U0LSR;
	}
	else
	{
		ch = U0IIR;
	}
	VICVectAddr = 0;
}

void InitUART0(void)
{
	PINSEL0 |= 0x00000005;
	U0LCR = 0x83;
	U0DLL = 97;
	U0LCR = 0x03;

	VICIntSelect = 0x00000000;
	VICVectAddr0 = (unsigned)UART0_isr;
	VICVectCntl0 = 0x20 | 6;
	VICIntEnable = 1 << 6;

	U0IER = 0x01;
}

void UART0_Tx(unsigned char ch)
{
	while(!(U0LSR & 0x20));
	U0THR = ch;
}

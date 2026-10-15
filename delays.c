#include <LPC21xx.H>

/* One-time timer setup: call this once from main() before using delay_us/delay_ms */
void Init_Timer0(void)
{
	T0TCR = 0x02;        // reset timer0
	T0PR  = 14;           // PCLK=15MHz -> prescale so T0TC increments every 1us (15MHz/(14+1)=1MHz)
	T0TCR = 0x01;        // enable timer0, free-running
}

void delay_us(unsigned int dlyUS)
{
	unsigned int start = T0TC;
	while((T0TC - start) < dlyUS);   // wait until dlyUS microseconds have elapsed
}

void delay_ms(unsigned int dlyMS)
{
	while(dlyMS--)
		delay_us(1000);
}

void delay_s(unsigned int dlyS)
{
	while(dlyS--)
		delay_ms(1000);
}

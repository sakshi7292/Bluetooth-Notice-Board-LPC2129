#include <LPC21xx.H>
#include "delays.h"
#include "defines.h"
#include "74LS164.h"
#include "dml.h"
#include "uart.h"
#include "i2c.h"
#include "i2c_eeprom.h"

#define MSGSIZE 64
#define EEPROM_ADDR 0x50      // AT24Cxx default 7-bit slave address
#define MSG_EEPROM_LOC 0x00   // EEPROM address where message is stored
#define PASSWORD "@1234"       // change this to set your own password

extern volatile unsigned char buff[64];
extern volatile unsigned char r_flag;

unsigned char dispMsg[MSGSIZE];
unsigned char waiting_for_password = 1;

void Init_DotMatrix(void)
{
	IODIR1 |= (0xFFUL<<23);
}


int main()
{
	unsigned char i=0,l;
	Init_Timer0();
	Init_DotMatrix();
	Init_74LS164();
	init_i2c();
	InitUART0();

	//load_msg_from_eeprom();
	//i2c_eeprom_page_write(0x50,0x10,"READY",5);
	//i2c_eeprom_write(0x50,0x00,5);
	l=i2c_eeprom_read(0x50,0x00);
	i2c_eeprom_seq_read(0x50,0x10,dispMsg,l);
	while(1)
	{
		do
		{
			/*	while(buff[i] && i<MSGSIZE-1)
				{
					dispMsg[i]=buff[i];
					i++;
				}
				dispMsg[i]='\0';

				//save_msg_to_eeprom(dispMsg);

				waiting_for_password = 1;*/
		scroll_string((unsigned char*)dispMsg,450);
		}while(r_flag==0);
		r_flag=0;
		if(strstr((unsigned char*)buff,PASSWORD))
		{
					memset(dispMsg,'\0',64);
					i2c_eeprom_page_write(0x50,0x10,(unsigned char *)buff+5,strlen((const char *)buff+5));
					i2c_eeprom_seq_read(0x50,0x10,(unsigned char *)dispMsg,strlen((const char *)buff+5));
				i2c_eeprom_write(0x50,0x00,strlen((const char *)buff+5));
					memset(buff,'\0',64);
		}
		else
		{
				scroll_string((unsigned char*)"WRONG",450);
		}
	}
}

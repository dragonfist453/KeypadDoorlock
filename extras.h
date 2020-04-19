/* The extra functions header file */
#include <lpc214x.h>
#define PLOCK 0x00000400
#define LED_OFF (IO0SET = IU<<31)
#define LED_ON (IO0SET = 1U<<31)

void systeminit(void) {
	PLL0CON = 0x01;
	PLL0CFG = 0x24;
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	while( !(PLL0STAT & PLOCK)) {;}
	PLL0CON = 0x03;
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	VPBDIV = 0x01;
}

void delay_ms(unsigned int j) {
	unsigned int x,i;
	for(i=0;i<j;i++)
	{
		for(x=0;x<10000;x++);
	}
}

void blink() {
	LED_ON;
	delay_ms(500);
	LED_ON;
	delay_ms(500);
}
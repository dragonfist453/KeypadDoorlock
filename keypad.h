/* Keypad data receieve functions
	 Keypad on board is connected as follows: -
	     1 |	2	 |	3	 |	R	 |
P0.16 -----------------------
       4 |  5  |  6  |  S  |
P0.17 -----------------------
			 7 |  8  |  9  |  L  |
P0.18 -----------------------
			 * |  0  |  #  |  U  |
P0.19 -----------------------
				 |     |     |     |
			 P1.19 P1.18 P1.17 P1.16
			 
Columns and rows are pulled to +5v, if no key press, '1' is received on columns.
0 is sent to each row and 0 is checked on column to check keypress

R - Reset keypad code to 1234 on entering manufacturer number 4539 next
S - Set a keypad code
L - Lock door
U - Unlock door
*/
#define COL0 (IO1PIN & 1<<19)
#define COL1 (IO1PIN & 1<<18)
#define COL2 (IO1PIN & 1<<17)
#define COl3 (IO1PIN & 1<<16)
#include <lpc214x.h>
#include "extras.h"

unsigned char lookup_table[4][4] = { {'1', '2', '3', 'R'},
																		 {'4', '5', '6', 'S'},
																		 {'7', '8', '9', 'L'},
																		 {'*', '0', '#', 'U'} };
unsigned int rowsel = 0, colsel = 0;												

unsigned char getKeypress() {
	while(1) {
		//check in row 0 by making row 1, 2, 3 as 1 and row 0 as 0
		rowsel = 0;
		IO0SET = 0x000F0000;
		IO0CLR = 1<<16;
		if(COL0==0) {colsel=0;break;}
		if(COL1==0) {colsel=1;break;}
		if(COL2==0) {colsel=2;break;}
		if(COl3==0) {colsel=3;break;}
		
		//check in row 1
		rowsel = 1;
		IO0SET = 0x000F0000;
		IO0CLR = 1<<17;
		if(COL0==0) {colsel=0;break;}
		if(COL1==0) {colsel=1;break;}
		if(COL2==0) {colsel=2;break;}
		if(COl3==0) {colsel=3;break;}
		
		//check in row 2
		rowsel = 2;
		IO0SET = 0x000F0000;
		IO0CLR = 1<<18;
		if(COL0==0) {colsel=0;break;}
		if(COL1==0) {colsel=1;break;}
		if(COL2==0) {colsel=2;break;}
		if(COl3==0) {colsel=3;break;}
		
		//check in row 3
		rowsel = 3;
		IO0SET = 0x000F0000;
		IO0CLR = 1<<19;
		if(COL0==0) {colsel=0;break;}
		if(COL1==0) {colsel=1;break;}
		if(COL2==0) {colsel=2;break;}
		if(COl3==0) {colsel=3;break;}
	}
	delay_ms(50);
	while(COL0==0 || COL1 == 0 || COL2 == 0 || COl3 == 0);
	delay_ms(50);
	IO0SET = 0x000F0000;
	return lookup_table[rowsel][colsel];
}

unsigned char* getCode() {
	unsigned char* code;
	unsigned int length = 4;
	unsigned int i = 0;
	for(i=0;i<length;i++) {
		*(code+i) = getKeypress();
	}
	return code;
}	
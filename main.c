/* Logical working
	 User clicks on any alphabet key, Lock, Unlock, reset or set. If the number keys are pressed, it is irrelevant and waits for an alphabet key.
	 According to each key, 
	 R - Resets the unlock code to manufacturer default "1234" upon entering the unique manufacturer code right after pressing R. If wrong, buzzer rings and nothing happens.
	 S - Set the unlock code to something else. Press S, enter earlier code, if correct, enter new code by hearing buzzer ring thrice at a high tempo. If wrong, buzzer rings.
	 L - Lock the door by moving servo back in place. No keypad action required. 
	 U - Unlock the door. Press U, then the set keypad code to unlock.
	 
	 Locking is assumed to be at 90 degrees angle anticlockwise of servo
	 Unlocking is assumed to be at 0 degrees
*/
#include<lpc214x.h>
#include<string.h>
#include "buzzer.h"
#include "servo.h"
#include "keypad.h"
#define CODE_LENGTH 4
const unsigned char man_code[CODE_LENGTH] = "4539";
const unsigned char default_code[CODE_LENGTH] = "1234";

unsigned char code[CODE_LENGTH] = "1234";
void reset_button();
void set_button();
void lock_button();
void unlock_button();

int main() {
	systeminit();
	IO0DIR |= 1U<<31 | 0x00FF0000;
	blink();
	unsigned char ch;
	while(1) {
		ch = getKeypress();
		switch(ch) {
			case 'R': reset_button();
								break;
			case 'S': set_button();
								break;
			case 'L': lock_button();
								break;
			case 'U': unlock_button();
								break;
			default: break;
		}				
	}	
	return 0;
}	
void reset_button() {
	if(strcmp((char*)man_code, (char*)getCode())==0)
		strcpy((char*)code, (char*)default_code);
	else {
		startBuzzer(1023);
		delay_ms(1000);
		stopBuzzer();
	}	
}
void set_button() {
	if(strcmp((char*)code, (char*)getCode())==0) {
		int i = 0;
		for(i=0;i<3;i++)
		{
			startBuzzer(600);
			delay_ms(200);
			stopBuzzer();
			delay_ms(50);
		}	
		strcpy((char*)code, (char*)getCode());
	}
	else {
		startBuzzer(1023);
		delay_ms(1000);
		stopBuzzer();
	}		
}
void lock_button() {
	lock();
}
void unlock_button() {
	if(strcmp((char*)code, (char*)getCode())==0)
		unlock();
}

/* Servo motor related functions
	 PWM values of P0.
*/
#include<lpc214x.h>
const unsigned int upper_limit = 2450; //+90 degree rotation
const unsigned int lower_limit = 650; //-90 degree rotation
__irq void PWM_ISR (void)
{
	if ( PWMIR & 0x0001 )
	{
		PWMIR = 0x0001;
	}
	
	if ( PWMIR & 0x0008 )
	{
		PWMIR = 0x0008;
	}	
	
	VICVectAddr = 0x00000000;
}

void servo_init() {
	PINSEL0 = PINSEL0 | 0x00000008; /* Configure P0.1 as PWM3 */
	VICVectAddr0 = (unsigned) PWM_ISR; /* PWM ISR Address */
	VICVectCntl0 = (0x00000020 | 8); /* Enable PWM IRQ slot */
	VICIntEnable = VICIntEnable | 0x00000100; /* Enable PWM interrupt */
	VICIntSelect = VICIntSelect | 0x00000000; /* PWM configured as IRQ */
	PWMTCR = 0x02; /* Reset and disable counter for PWM */
	PWMPR = 0x1D; /* Prescale Register value */
	PWMMR0 = 20000; /* Time period of PWM wave, 20msec */
	PWMMR3 = 1600;	/* Ton of PWM wave 1.60 msec */
	PWMMCR = 0x00000203;	/* Reset and interrupt on MR0 match, interrupt on MR3 match */
	PWMLER = 0x09;	/* Latch enable for PWM3 and PWM0 */
	PWMPCR = 0x0800;	/* Enable PWM3 and PWM 0, single edge controlled PWM */
	PWMTCR = 0x09;	/* Enable PWM and counter */
}	

void lock() {
	PWMMR3 = 2450;	
	PWMLER = 0x08;
}
void unlock() {
	PWMMR3 = 1600;	
	PWMLER = 0x08;
}
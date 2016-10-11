#include <stdlib.h>
#include "hal_timer.h"
#include "HardwareProfile.h"
#include <xc.h>

static timer_handler cb = NULL;
void hal_timer_init(int period, timer_handler fn)
{
	T0CON = 0X00;
	T0CONbits.T0PS = 0x07;
	T0CONbits.PSA = 0;
	T0CONbits.T08BIT = 1;
	INTCONbits.T0IF = 0;
	INTCONbits.T0IE = 1;               // Enable interrupt on TMR0 overflow
	INTCON2bits.TMR0IP = 0x01;
	T0CONbits.TMR0ON = 1;
	cb = fn;
}


void hal_timer_service(void)                            //Low priority interrupt
{
	if (INTCONbits.T0IF && INTCONbits.T0IE) {       // If Timer flag is set & Interrupt is enabled
		INTCONbits.T0IF = 0;                    // Clear the interrupt flag
		if (cb)
			cb();
	}
}

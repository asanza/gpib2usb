/*
 * hal_sys.c
 *
 * Copyright (c) 2016, Diego F. Asanza. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * Created on June 29, 2016, 9:27 PM
 */

#include <xc.h>
#include <usb_config.h>

#include "HardwareProfile.h"

void hal_sys_init(){
TRISBbits.TRISB5 = 0;
LATBbits.LATB5 = 1;

PinAsOutput(RED_LED);
PinAsOutput(GREEN_LED);
PinAsOutput(YELLOW_LED);

PinClearValue(RED_LED);
PinClearValue(GREEN_LED);
PinClearValue(YELLOW_LED);

/* Configure interrupts, per architecture */
#ifdef USB_USE_INTERRUPTS
	#if defined (_PIC18) || defined(_PIC14E)
		INTCONbits.PEIE = 1;
		INTCONbits.GIE = 1;
	#elif __PIC32MX__
		INTCONbits.MVEC = 1; /* Multi-vector interrupts */
		IPC11bits.USBIP = 4; /* Interrupt priority, must set to != 0. */
		__asm volatile("ei");
	#endif
#endif

}

void hal_sys_green_led_on(void){
    PinSetValue(GREEN_LED);
}

void hal_sys_green_led_toggle(void){
    PinToggleValue(GREEN_LED);
}

void hal_sys_red_led_on(void){
    PinSetValue(RED_LED);
}

void hal_sys_yellow_led_on(void){
    PinSetValue(YELLOW_LED);
}

void hal_sys_yellow_led_toggle(void){
    PinToggleValue(YELLOW_LED);
}

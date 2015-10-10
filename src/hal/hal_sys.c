/*
 * hal_sys.c
 *
 * Copyright (c) 2015, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
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
 * Created on September 14, 2015, 10:23 PM
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal_sys.h"
#include "HardwareProfile.h"

void hal_sys_init(void){
    PortSetInput(_DIO);
    PinSetOutput(_GPIO1);
    PinSetOutput(_GPIO2);
    PinSetOutput(_GPIO3);
    PinSetOutput(_GPIO4);
    PinSetOutput(_GPIO5);
    PinSetOutput(_DAV);
    PinSetOutput(_ATN);
    PinSetOutput(_EOI);
    PinSetInput(_SRQ);
    PinSetInput(_NRFD);
    PinSetInput(_NDAC);
    PinSetOutput(_TE);
    PinSetOutput(_PE);
    PinSetOutput(_DC);
    /* Set bus outputs on tri-state mode */
    PortClearPin(_TE);
    PortClearPin(_PE);
    PortClearPin(_DC);
    PortSetOutput(_SYSLED);
    sei();
}


void hal_sys_enter_critical(void){
    cli();
}

void hal_sys_exit_critical(void){
    sei();
}

void hal_sysled_on(void){
    PortSetPin(_SYSLED);
}

void hal_sysled_off(void){
    PortClearPin(_SYSLED);
}

void hal_sysled_toggle(void){
    PortTogglePin(_SYSLED);
}
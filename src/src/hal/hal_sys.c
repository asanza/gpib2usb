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
    PortSetInput(DIO);
    PinSetOutput(GPIO1);
    PinSetOutput(GPIO2);
    PinSetOutput(GPIO3);
    PinSetOutput(GPIO4);
    PinSetOutput(GPIO5);
    PinSetOutput(DAV);
    PinSetOutput(ATN);
    PinSetOutput(TXD);
    PinSetOutput(EOI);
    PinSetInput(RXD);
    PinSetInput(SRQ);
    PinSetInput(NRFD);
    PinSetInput(NDAC);
    PinSetOutput(TE);
    PinSetOutput(PE);
    PinSetOutput(DC);
    /* Set bus outputs on tri-state mode */
    PortClearPin(TE);
    PortClearPin(PE);
    PortClearPin(DC);
}

void hal_sys_enter_critical(void){
    cli();
}

void hal_sys_exit_critical(void){
    sei();
}
/*
 * hal_uart.c
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
 * Created on July 8, 2016, 9:50 PM
 */

#include <xc.h>
#include <p18f4550.h>


void putch(char data)
{
    while( ! TXIF)
        continue;
    TXREG = data;
}

void hal_uart_init(void)
{
    SPBRG = 78;           // 9600 baud @ 4 MHz
    SYNC = 0;
    TXEN = 1;               // enable transmitter
    BRGH = 0;               // select high baud rate
    BRG16 = 0;
    SPEN = 1;               // enable serial port
    CREN = 1;               // enable continuous operation
}

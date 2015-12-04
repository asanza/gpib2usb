/*
 * system.c
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
 * Created on October 9, 2015, 8:44 PM
 */

#include <avr/eeprom.h>
#include <diag.h>
#include "system.h"
#include "lib/lib_gpib.h"

#define DEVICE_ADDRESS (uint8_t*) 1

void sys_init(void)
{
    /* initialize in controller mode */
    GPIB_Init(0x00);
}

syserr sys_set_addr(uint8_t addr)
{
    if (addr > 30) return SYSERR_WRONG_PARAMETER;
    eeprom_update_byte(DEVICE_ADDRESS, addr);
    return SYSERR_NONE;
}

uint8_t sys_get_addr(void)
{
    return eeprom_read_byte(DEVICE_ADDRESS);
}

void sys_gpib_read(char* buffer, int size, sysread until, int charval) {
 }

syserr sys_gpib_write(char* buffer, int size)
{
    DIAG("%s, %d", buffer, size);
    int err = GPIB_Send(UNL,1);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(LAD, 12);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(MTA,1);
    if(err) return SYSERR_WRITE_ERROR;
    size --;
    while(size--){
        err = GPIB_Send(DAB, *buffer++);
        if(err) return SYSERR_WRITE_ERROR;
    }
    err = GPIB_Send(UNT, 12);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(UNL, 12);
    if(err) return SYSERR_WRITE_ERROR;
    return SYSERR_NONE;
}
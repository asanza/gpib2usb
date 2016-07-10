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

#include <xc.h>
#include "system.h"
#include "lib/lib_gpib.h"
#include "hal/hal_gpib.h"

#define DEVICE_ADDRESS (uint8_t*) 1

static uint8_t sysaddr = 0;

void sys_init(void)
{
    /* initialize in controller mode */
    GPIB_Init(0x00);
    sysaddr = sys_get_addr();
}

syserr sys_set_addr(uint8_t addr)
{
    if (addr > 30) return SYSERR_WRONG_PARAMETER;
    sysaddr = addr;
    eeprom_update_byte(DEVICE_ADDRESS, addr);
    return SYSERR_NONE;
}

uint8_t sys_get_addr(void)
{
    return eeprom_read_byte(DEVICE_ADDRESS);
}

syserr sys_gpib_read(char* buffer, int size, sysread until, int charval) {
    int err = GPIB_Send(UNL,1);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(TAD, sysaddr);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(MLA, 1);
    while(GPIB_Receive(buffer) >= 0 && size-- > 0){
        if(*buffer == '\n') break;
        //printf("%c", *buffer);
        buffer++;
    };
    err = GPIB_Send(UNT, 1);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(UNL, 1);
    if(err) return SYSERR_WRITE_ERROR;
    return SYSERR_NONE;   
}

syserr sys_gpib_write(char* buffer, int size)
{
    int err = GPIB_Send(UNL,1);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(LAD, sysaddr);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(MTA,1);
    if(err) return SYSERR_WRITE_ERROR;
    size --;
    while(size--){
        err = GPIB_Send(DAB, *buffer++);
        if(err) return SYSERR_WRITE_ERROR;
    }
    err = GPIB_Send(UNT, sysaddr);
    if(err) return SYSERR_WRITE_ERROR;
    err = GPIB_Send(UNL, sysaddr);
    if(err) return SYSERR_WRITE_ERROR;
    return SYSERR_NONE;
}
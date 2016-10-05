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
 * Created on September 18, 2016, 19:45 PM
 */

 #include "system.h"
 #include "gpib/gpib.h"
 #include "hal/hal_sys.h"
 #include <string.h>
 #include <stdio.h>
 #include <assert.h>

#define GPIB_BUFFER_SIZE	256
static int addr;

static char gpib_buffer[GPIB_BUFFER_SIZE];
static int buffer_size = 0;
static int char_sent = 0;

int sys_set_address(uint8_t address, uint8_t subaddress)
{
	if (address > 32  || subaddress > 255 ) return -1;
	addr = address;
	return 0;
}

int sys_get_address(void)
{
	return addr;
}

void sys_start_read(void){

}

system_event_t sys_write_gpib(char* data, int size){
	if(buffer_size != 0) return SYSEVT_BUFFER_NOT_EMPTY;
	memcpy(gpib_buffer, data, size);
	buffer_size = data;
	char_sent = 0;
}


system_event_t sys_tasks(void){
	GPIB_Event evt = GPIB_Tasks();
}

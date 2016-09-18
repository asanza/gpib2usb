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

static int addr;
/* internal gpib buffer for send and receive operations */
#define GPIB_BUFFER_SIZE 256
static char gpib_buffer[GPIB_BUFFER_SIZE];
static int bsz = 0;
static int bsent = 0;

static sys_state state = IDLE;
static int do_sending(void);
static int do_receiving(void);

int timer_counter = 0;
long int timeout = 0;

#define TIMEOUT 100000UL;
#define TIMER_COUNTER_OVERFLOW 10000

int sys_set_address(uint8_t address, uint8_t subaddress)
{
	if (address > 32  || subaddress > 255 ) return -1;
	addr = address;
	return 0;
}

sys_state sys_get_state(void)
{
	return state;
}

int sys_get_address(void)
{
	return addr;
}

int sys_get_gpib_buffer(char** data)
{
	*data = gpib_buffer;
	return bsz;
}

void sys_start_read(void)
{
	state = RECEIVING;
	bsz = 0;
}

int sys_write_gpib(char* data, int size)
{
	if (size > GPIB_BUFFER_SIZE) return -1;
	memcpy(gpib_buffer, data, size);
	bsz = size;
	bsent = 0;
	state = SENDING;
	return 0;
}

int sys_tasks(void)
{
	GPIB_Event evt = GPIB_Tasks();
	if (evt == GPIB_EVT_DATA_AVAILABLE) {
		gpib_buffer[0] = GPIB_Get();
		bsz = 1;
		return -2;
	}
	switch (state) {
	case SENDING:
		timeout--;
		if (GPIB_State() == GPIB_IDLE) {
			timeout = TIMEOUT;
			return do_sending();
		}
		break;
	case RECEIVING:
		timeout--;
		if (GPIB_State() == GPIB_IDLE) {
			timeout = TIMEOUT;
			return do_receiving();
		}
		break;
	case IDLE:
		// toggle green led
		if (timer_counter++ > TIMER_COUNTER_OVERFLOW) {
			hal_sys_yellow_led_toggle();
			timer_counter = 0;
		}
		timeout = TIMEOUT;
		break;
	}
	if (!timeout && state != IDLE) {
		timeout = TIMEOUT;
		sprintf(gpib_buffer, "Timeout\r\n");
		bsz = strlen(gpib_buffer);
		state = IDLE;
		GPIB_Reset();
		return -1;
	}
	return 0;
}

static int do_receiving(void)
{
	static int index = 0;
	int retval = 0;

	switch (index) {
	case 0: retval = GPIB_Send(UNL, 1); index++; break;
	case 1: retval = GPIB_Send(TAD, addr); index++; break;
	case 2: retval = GPIB_Send(MLA, 1); index++; break;
	case 3: retval = GPIB_Receive(); break;
	case 4: retval = GPIB_Send(UNT, 1); index++; break;
	case 5: retval = GPIB_Send(UNL, 1); index = 0; break;
	default: index = 0;
	}
	if (retval != GPIB_EVT_NONE) {
		sprintf(gpib_buffer, "Reception error\r\n");
		bsz = strlen(gpib_buffer);
		state = IDLE;
		index = 0;
		return -1;
	}
	return 0;
}

static int do_sending(void)
{
	static int index = 0;
	int retval = 0;

	switch (index) {
	case 0: retval = GPIB_Send(UNL, 1); index++; break;
	case 1: retval = GPIB_Send(LAD, addr); index++; break;
	case 2: retval = GPIB_Send(MTA, 1); index++; break;
	case 3: retval = GPIB_Send(DAB, gpib_buffer[bsent++]);
		if (bsent == bsz && !retval) {
			bsent = 0; bsz = 0;
			index++;
			state = IDLE;
			return -1;
		}
		break;
	case 4: retval = GPIB_Send(UNT, addr); index++;
	case 5: retval = GPIB_Send(UNL, addr); index = 0;
	default: index = 0;
	}
	if (retval != GPIB_EVT_NONE) {
		sprintf(gpib_buffer, "Transmission error\r\n");
		bsz = strlen(gpib_buffer);
		state = IDLE;
		index = 0;
		return -1;
	}
	return 0;
}

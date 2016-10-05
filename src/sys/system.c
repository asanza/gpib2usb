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

#define TRUE 1
#define FALSE 0

#define GPIB_BUFFER_SIZE	256
static int addr;
static int reading = FALSE;

/* allocate memory for gpib buffer */
static char gpib_buffer[GPIB_BUFFER_SIZE];
/* utility pointer */
static char* buffer_ptr = gpib_buffer;

void do_rx_sm(void); // rx state machine
void do_tx_sm(void); // tx state machine

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
	reading = true;
	do_rx_sm();
}

system_event_t sys_write_gpib(char* data, int size){
	if(gpib_buffer != buffer_ptr) return SYSEVT_BUFFER_NOT_EMPTY;
	memcpy(gpib_buffer, data, size);
	buffer_ptr = gpib_buffer + size;
	return SYSEVT_IDLE;
}


system_event_t sys_tasks(void){
	GPIB_Event evt = GPIB_Tasks();
	if(evt == GPIB_EVT_DATA_AVAILABLE)
		return SYSEVT_DATA_RECEIVED;
	else if (evt == GPIB_EVT_TX_ERROR)
		return SYSEVT_TX_ERROR;
	else if (evt == GPIB_EVT_RX_ERROR);
		return SYSEVT_RX_ERROR;
	switch(GPIB_State()){
		case GPIB_TALK: return SYSEVT_TRANSMITTING;
		case GPIB_LISTEN: return SYSEVT_RECEIVING;
		default: break;
	}

	if(buffer_ptr == gpib_buffer){
		/* if set, eoi or lf not yet received */
		if(reading) {
			/* advance rx state machine */
			do_rx_sm();
			return SYSEVT_RECEIVING;
		}
		return SYSEVT_IDLE;
	}
	/* advance tx state machine  */
	do_tx_sm();
	return SYSEVT_TRANSMITTING;
}

void do_tx_sm(void){
	static int state = 0;
	switch(state){
		case 0: GPIB_Send(UNL, 1); state++; break;
		case 1: GPIB_Send(LAD, addr); state++; break;
		case 2: GPIB_Send(MTA, 1); state++; break;
		case 4:
			GPIB_Send(DAB, *(--buffer_ptr));
			if(buffer_ptr == gpib_buffer) state++;
			break;
		case 5: GPIB_Send(UNT, sysaddr); state++; break;
		case 6: GPIB_Send(UNL, sysaddr); state = 0; break;
		default: break;
	}
}

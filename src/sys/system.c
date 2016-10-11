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
 * Created on October 8, 2016, 10:08 PM
 */

#include <stdio.h>
#include <string.h>
#include "gpib/gpib.h"
#include "utils.h"
#include "utils/fifo.h"
#include "system.h"
#include "sysdefs.h"

#ifdef TEST
#define REPOVERSION "1"
#define REPOBRANCH "master"
#endif

#define GPIB_BUFFER_SIZE 200
static fifo_t gpib_fifo;
static char gpib_buffer[GPIB_BUFFER_SIZE];

static sys_state_t state = { 0, 3000,   0, 0, 1 };

#define SET_STATE(str, token, state, valmin, valmax, msg) do { \
		int val;																		\
		token = strtok(NULL, " ");									\
		if ( token == NULL ) {												 \
			sprintf(str, "%d\r\n", state);						\
		} else {																		\
			val = str2int(token);											\
			if (val > valmin && val <= valmax) {					  \
				state = val;														\
				sprintf(str, "Ok\r\n");									\
			} else {																	\
				sprintf(str, msg);											\
			}																					\
		}																						\
} while (0);

void sys_init(void)
{
	fifo_init(&gpib_fifo, &gpib_buffer, GPIB_BUFFER_SIZE);
}

int sys_process_input(char* str, int len)
{
	char* msg = "Error: passing data not implemented\r\n";
	fifo_write(&gpib_fifo, msg, strlen(msg));
	return strlen(str);
}

int sys_process_command(char*str, int len)
{
	char* token = strtok(str, " ");

	if ( !strcasecmp(token, "++addr") ) {
		SET_STATE(str, token, state.address, 0, 32, "Error: Wrong Address\r\n");
	} else if ( !strcasecmp(token, "++clr") ) {
		sprintf(str, "Error: ++clr not implemented\r\n");
	} else if ( !strcasecmp(token, "++eoi") ) {
		SET_STATE(str, token, state.eoi, 0, 1, "Error: Wrong eoi\r\n");
	} else if ( !strcasecmp(token, "++eos") ) {
		SET_STATE(str, token, state.eos, 0, 3, "Error: Wrong eos\r\n");
	} else if ( !strcasecmp(token, "++ifc") ) {
		sprintf(str, "Error: ++ifc not implemented\r\n");
	} else if ( !strcasecmp(token, "++loc") ) {
		sprintf(str, "Error: ++loc not implemented\r\n");
	} else if ( !strcasecmp(token, "++spoll") ) {
		sprintf(str, "Error: ++spoll not implemented\r\n");
	} else if ( !strcasecmp(token, "++srq") ) {
		sprintf(str, "Error: ++srq not implemented\r\n");
	} else if ( !strcasecmp(token, "++trg") ) {
		sprintf(str, "Error: ++trg not implemented\r\n");
	} else if ( !strcasecmp(token, "++ver") ) {
		sprintf(str, "%s-%s\r\n", REPOVERSION, REPOBRANCH);
	} else if ( !strcasecmp(token, "++help") ) {
		sprintf(str, "Error: ++help not implemented\r\n");
	} else if ( !strcasecmp(token, "++read") ){
		sprintf(str, "Error: ++read not implemented\r\n");
	} else if ( !strcasecmp(token, "++read_tmo_ms") ) {
		SET_STATE(str, token, state.timeout, 0, 3000, "Error: Wrong timeout\r\n");
	} else {
		sprintf(str, "Error: Command Unknown\r\n");
	}
	return strlen(str);
}

int sys_gpib_get_buffer(char* out_buf, int len)
{
	int sz = fifo_read(&gpib_fifo, out_buf, len);
}

int sys_gpib_write(char* buffer, int size)
{
  int err = GPIB_Send(UNL,1);
  if(err) return -1;
  err = GPIB_Send(LAD, state.address);
  if(err) return -1;
  err = GPIB_Send(MTA,1);
  if(err) return -1;
  size --;
  while(size--){
      err = GPIB_Send(DAB, *buffer++);
      if(err) return -1;
  }
  err = GPIB_Send(UNT, state.address);
  if(err) return -1;
  err = GPIB_Send(UNL, state.address);
  if(err) return -1;
  return 0;
}

int sys_gpib_read(fifo_t* fifo) {
	char c;
  int err = GPIB_Send(UNL,1);
  if(err) return -1;
  err = GPIB_Send(TAD, state.address);
  if(err) return -1;
  err = GPIB_Send(MLA, 1);
  while( ( GPIB_Receive(&c) >= 0 )
			&& ( fifo_write(fifo, &c, 1) == 1 )){
      if(c == '\n') break;
  };
  err = GPIB_Send(UNT, 1);
  if(err) return -1;
  err = GPIB_Send(UNL, 1);
  if(err) return -1;
  return 0;
}

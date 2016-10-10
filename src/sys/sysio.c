/*
* sysio.c
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
* Created on October 10, 2016, 10:08 PM
*/

#include "sysio.h"
#include <stdio.h>
#include "sysdefs.h"
#include <string.h>

#define INBUFFSIZE 200
#ifdef TEST
char inbuff[INBUFFSIZE];
#else
static char inbuff[INBUFFSIZE];
#endif
static int buffpos = 0;

#define ERROVERFLOW -1
#define ERRNONE 		-2
#define ISCMD 			-3
#define ISDATA 			-4
#define ISBUSY 			-5


static sysio_state_t state;

static int on_char_received(char c);

int sysio_data_received(char* str, int len){
	char* data = str;
	int i = 0;
	for(i = 0; i < len; i++){
		switch(on_char_received(*data++)){
			case ERRNONE: continue;
			case ERROVERFLOW:
				sprintf(str, "Error: Overflow\r\n");
				buffpos = 0;
				return strlen(str);
			case ISCMD:
				state = SYSIO_CMD_AVAILABLE;
				return 0;
			case ISDATA:
				state = SYSIO_DATA_AVAILABLE;
				return 0;
			case ISBUSY:
				sprintf(str, "Error: Busy\r\n");
				return strlen(str);
			default:
				sprintf(str, "Error: unknown\r\n");
				return strlen(str);
		}
	}
	return 0;
}

void sysio_release(void){
	state = SYSIO_EMPTY;
	buffpos = 0;
}

sysio_state_t sysio_get_state(void){
	return state;
}

static int on_char_received(char c){
	static int cmd = 0, esc = 0;
	int out = ERRNONE;
	if(state != SYSIO_EMPTY){
		out = ISBUSY;
	} else	if(buffpos > INBUFFSIZE){
		out = ERROVERFLOW;
	} else if( !esc && ( c==LF || c==CR )){
		if(cmd)
			out = ISCMD;
		else
			out = ISDATA;
		inbuff[buffpos] = 0;
	} else if( !esc && c=='+' ){
		cmd = 1;
		inbuff[buffpos++] = c;
	} else if( !esc && ( c==ESC )){
		esc = 1;
	} else {
		inbuff[buffpos++] = c;
		esc = 0;
	}
	return out;
}

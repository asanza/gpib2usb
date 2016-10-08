/*
* input.h
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
#include "sysdefs.h"
#include "system.h"
#include <string.h>
#include "input.h"

#define INBUFFSIZE 200
#ifdef TEST
char inbuff[INBUFFSIZE];
#else
static char inbuff[INBUFFSIZE];
#endif

static int buffpos = 0;

#define ERROVERFLOW -1
#define ERROK -2

static int on_char_received(char c);

int sys_on_usb_data_received(char* str, int len){
	char* data = str;
	int i = 0;
	for(i = 0; i < len; i++){
		switch(on_char_received(*data++)){
			case ERROK: continue;
			case ERROVERFLOW:
				sprintf(str, "Error: Overflow\r\n");
				return strlen(str);
			case SYS_ERR_COMMAND_UNKNOWN:
				sprintf(str, "Error: Unknown Command\r\n");
				return strlen(str);
			case SYS_ERR_NONE:
				return 0;
		}
	}
}

static int on_char_received(char c){
	static int esc = 0;
	int out = ERROK;
	if(buffpos > INBUFFSIZE){
		buffpos = 0;
		return ERROVERFLOW;
	} else if( !esc && ( c==LF || c==CR )){
		out = sys_process_input(inbuff, buffpos);
		buffpos = 0;
	} else if( !esc && ( c==ESC )){
		esc = 1;
	} else{
		inbuff[buffpos++] = c;
		esc = 0;
	}
	return out;
}

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
#include "system.h"
#include "sysdefs.h"

#ifdef TEST
#define REPOVERSION "1"
#define REPOBRANCH "master"
#endif

static sys_state_t state = { 0, 3000,	0, 0, 1 };

#define SET_STATE(str, token, state, valmin, valmax, msg) do { \
	int val; 																		\
	token = strtok(NULL, " ");									\
	if( token == NULL ) {												\
		sprintf(str, "%d\r\n", state);						\
	} else {																		\
		val = str2int(token);											\
		if(val > valmin && val <= valmax){					\
			state = val;														\
			sprintf(str, "Ok\r\n");									\
		} else {																	\
			sprintf(str, msg);											\
		}																					\
	}																						\
} while(0);

int sys_process_input(char* str, int len){
	GPIB_Mode(GPIB_MODE_CONTROLLER);
  sprintf(str, "Error: passing data not implemented\r\n");
  return strlen(str);
}

int sys_process_command(char*str, int len){
	char* token = strtok(str, " ");
	if( !strcasecmp(token, "++addr") ){
		SET_STATE(str, token, state.address, 0, 32, "Error: Wrong Address\r\n");
	} else if ( !strcasecmp(token, "++clr") ){
    sprintf(str, "Error: ++clr not implemented\r\n");
	} else if ( !strcasecmp(token, "++eoi") ){
		SET_STATE(str, token, state.eoi, 0, 1, "Error: Wrong eoi\r\n");
	} else if ( !strcasecmp(token, "++eos") ){
		SET_STATE(str, token, state.eos, 0, 3, "Error: Wrong eos\r\n");
	} else if ( !strcasecmp(token, "++ifc") ){
    sprintf(str, "Error: ++ifc not implemented\r\n");
	} else if ( !strcasecmp(token, "++loc") ){
    sprintf(str, "Error: ++loc not implemented\r\n");
	} else if ( !strcasecmp(token, "++spoll") ){
    sprintf(str, "Error: ++spoll not implemented\r\n");
	} else if ( !strcasecmp(token, "++srq") ){
    sprintf(str, "Error: ++srq not implemented\r\n");
	} else if ( !strcasecmp(token, "++trg") ){
    sprintf(str, "Error: ++trg not implemented\r\n");
	} else if ( !strcasecmp(token, "++ver") ){
//    sprintf(str, "%s-%s\r\n",REPOVERSION, REPOBRANCH);
	} else if ( !strcasecmp(token, "++help") ){
  	sprintf(str, "Error: ++help not implemented\r\n");
	} else if( !strcasecmp(token, "++read") ){
		sprintf(str, "Error: ++read not implemented\r\n");
	} else if( !strcasecmp(token, "++read_tmo_ms") ){
		SET_STATE(str, token, state.timeout, 0, 3000, "Error: Wrong timeout\r\n");
	} else {
    sprintf(str, "Error: Command Unknown\r\n");
  }
	return strlen(str);
}

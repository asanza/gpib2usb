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
#include "utils.h"
#include "system.h"

#ifdef TEST
#define REPOVERSION "1"
#define REPOBRANCH "master"
#endif

static int addr = 0;

int sys_process_input(char* str, int len){
    sprintf(str, "Error: passing data not implemented\r\n");
    return strlen(str);
}

int sys_process_command(char*str, int len){
	int val;
	char* token = strtok(str, " ");
	if( !strcasecmp(token, "++addr") ){
		token = strtok(NULL, " ");
		if( token == NULL ) {
			sprintf(str, "%d\r\n", addr);
			return strlen(str);
		} else {
			val = str2int(token);
			if(val > 0 && val < 33){
				addr = val;
			} else {
				sprintf(str, "Error: wrong address\r\n");
				return strlen(str);
			}
		}
	} else if ( !strcasecmp(token, "++clr") ){
        sprintf(str, "Error: ++clr not implemented\r\n");
        return strlen(str);
	} else if ( !strcasecmp(token, "++eoi") ){
        sprintf(str, "Error: ++eoi not implemented\r\n");
        return strlen(str);
	} else if ( !strcasecmp(token, "++eos") ){
        sprintf(str, "Error: ++eos not implemented\r\n");
        return strlen(str);
	} else if ( !strcasecmp(token, "++ifc") ){
        sprintf(str, "Error: ++ifc not implemented\r\n");
        return strlen(str);
	} else if ( !strcasecmp(token, "++loc") ){
        sprintf(str, "Error: ++loc not implemented\r\n");
        return strlen(str);
	} else if ( !strcasecmp(token, "++spoll") ){
        sprintf(str, "Error: ++spoll not implemented\r\n");
        return strlen(str);
	} else if ( !strcasecmp(token, "++srq") ){
        sprintf(str, "Error: ++srq not implemented\r\n");
        return strlen(str);
	} else if ( !strcasecmp(token, "++trg") ){
        sprintf(str, "Error: ++trg not implemented\r\n");
        return strlen(str);
	} else if ( !strcasecmp(token, "++ver") ){
        sprintf(str, "%s-%s\r\n",REPOVERSION, REPOBRANCH);
        return strlen(str);
	} else if ( !strcasecmp(token, "++help") ){
        sprintf(str, "Error: ++help implemented\r\n");
        return strlen(str);
	} else {
        sprintf(str, "Error: Command Unknown\r\n");
        return strlen(str);
    }
}

/*
 * input.c
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
 * Created on October 8, 2015, 10:08 PM
 */

#include "input.h"
#include "sysdefs.h"
#include "system.h"
#include "parser.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>


static char ibuffer[INPUT_SIZE];
static int olen = 0;

static int check_input(char** str, char* data, size_t sz){
	devcmd cmd;
    int len = parse_input(&cmd, data, sz);
	switch(cmd){
        case CMD_ADDR:
            if(len > 1){
                sz = parse_address(data, len);
                if(sys_set_address(sz,0)){
                    sprintf(ibuffer, "Error: Invalid Address\r\n");
                }else{
                    sprintf(ibuffer, "OK\r\n");
                }
            } else {
                sprintf(ibuffer, "%d\r\n", sys_get_address());
            }
            break;
	    case CMD_AUTO:              sprintf(ibuffer, "auto\r\n");
            break;
        case CMD_CLR:               sprintf(ibuffer, "clr\r\n");
            break;
        case CMD_EOI:               sprintf(ibuffer, "eoi\r\n");
            break;
        case CMD_EOS:               sprintf(ibuffer, "eos\r\n");
            break;
        case CMD_EOT_ENABLE:        sprintf(ibuffer, "enable\r\n");
            break;
        case CMD_EOT_CHAR:          sprintf(ibuffer, "char\r\n");
            break;
        case CMD_IFC:               sprintf(ibuffer, "ifc  \r\n");
            break;
        case CMD_LLO:               sprintf(ibuffer, "llo \r\n");
            break;
        case CMD_LOC:               sprintf(ibuffer, "loc \r\n");
            break;
        case CMD_LON:               sprintf(ibuffer, "lon \r\n");
            break;
        case CMD_MODE:              sprintf(ibuffer, "mode\r\n");
            break;
        case CMD_READ:
            //if( sys_listen() ){
                sprintf(ibuffer, "Cannot Read\r\n");
            //} else {
            //    ibuffer[0] = 0;
            //}
            break;
        case CMD_READ_TMO_MS:       sprintf(ibuffer, "tmo\r\n");
            break;
        case CMD_RST:               sprintf(ibuffer, "rst\r\n");
            break;
        case CMD_SAVE_CONFIG:       sprintf(ibuffer, "config\r\n");
            break;
        case CMD_RST_FACTORY:       sprintf(ibuffer, "factory\r\n");
            break;
        case CMD_SPOLL:             sprintf(ibuffer, "spoll\r\n");
            break;
        case CMD_SRQ:               sprintf(ibuffer, "srq\r\n");
            break;
        case CMD_STATUS:            sprintf(ibuffer, "status\r\n");
            break;
        case CMD_TRG:               sprintf(ibuffer, "trg\r\n");
            break;
        case CMD_VER:               sprintf(ibuffer, "ver\r\n");
            break;
        case CMD_HELP:              sprintf(ibuffer, "help\r\n");
            break;
        default:
            len = sys_write_gpib(data, sz);
            if(len){
                sprintf(ibuffer, "Error: cannot write\r\n");
            }else{
                return 0;
            }
            break;
    }
    *str = ibuffer;
		olen = strlen(ibuffer);
    return olen;
}

int read_line(const char* buffer, size_t size){
    static int len = 0;
	char *dst = &ibuffer[len];
	while(size--){
		*dst++ = *buffer++; len++;
		if(len >= INPUT_SIZE){
			len = 0;
			return -1;
		}
		if(ibuffer[len - 1] == CR || ibuffer[len - 1] == LF){
			if(len > 1 ){
				if(ibuffer[len - 2] == ESC)
					continue;
			}
			olen = len;
			len = 0;
			return 1;
		}
	}
	return 0;
}


int process_input(char** str){
	return check_input(str, ibuffer, olen);
}

int get_input_buffer(char** buffer){
	*buffer = &ibuffer[0];
	return olen;
}

int set_input_buffer(char* data, int sz){
	if(sz > INPUT_SIZE) return -1;
	memcpy(ibuffer, data, sz);
	olen = sz;
	return 0;
}

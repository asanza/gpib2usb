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
#include "parser.h"
#include "utils.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

/* posible system states */
enum{
	INIT,
	TALKING,
	LISTENING,
	IDLE
};


static char ibuffer[INPUT_SIZE];
static int olen = 0, len = 0;
static int address;
static int actual_state = INIT;

static int init(int actual_state);
static int talk(int actual_state);
static int listen(int actual_state);
static int idle(int actual_state, char** str, int* len, char* data, size_t sz);

static int set_address(int actual_state, char* data, size_t len);
static void perform_tasks(char* data, size_t len);


void sys_tasks(void){
	/* in idle state, just do nothing */
	if( actual_state == IDLE ) return;
	switch(actual_state){
        case INIT:
            actual_state = IDLE;
            break;
		case TALKING:
			printf("State talk:\r\n");
			break;
		case LISTENING:
			printf("State listen:\r\n");
			break;
		default: assert(0);
	}
}

static int init(int actual_state){
}

static int talk(int actual_state){

}

static int listen(int actual_state){

}

static int idle(int actual_state, char** str, int* len, char* data, size_t sz){
	devcmd cmd;
	*len = parse_input(&cmd, data, sz);
	switch(cmd){
        case CMD_ADDR:
        	if(*len > 0){
                data[*len] = 0;
        		sz = str2int(data);
               	if(sz > 32){
               		sprintf(ibuffer, "Error: Invalid Address\r\n");
            		*str = ibuffer;
            		*len = strlen(ibuffer);
            		return actual_state;
            	}else{
    				address = sz;	        		
            	}
            }
			sprintf(ibuffer, "%d\r\n", address);
			*str = ibuffer;
			*len = strlen(ibuffer);
			return actual_state;
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
        case CMD_READ:              //err = do_read_gpib(inbuff, size);
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
        default:                    //err = do_write_gpib(inbuff, size);
            sprintf(ibuffer, "Unknown\r\n");
            break;
    }
    *len = strlen(ibuffer);
    return actual_state;	
}

int read_line(const char* buffer, size_t size){
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

int get_input_buffer(char** str){
	*str = ibuffer;
	return olen;
}

int process_input(char** str){
	int sz;
	if(actual_state == IDLE){
		actual_state = idle(actual_state, str, &sz, ibuffer, olen);
		return sz;
	}else{
		printf("Error: not in idle state\r\n");
		*str = ibuffer;
		return strlen(*str);
	}
}
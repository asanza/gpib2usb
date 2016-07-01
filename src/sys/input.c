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
#include <assert.h>
#include <string.h>
#include <stdio.h>

static char ibuffer[INPUT_SIZE];
static int olen = 0;

int read_line(const char* buffer, size_t size){
	char *dst = ibuffer;
	int len = 0;
	while(size--){
		*dst++ = *buffer++; len++;
		if(len >= INPUT_SIZE){
			len = 0;
			return -1;
		}
		if(ibuffer[len - 1] == '\r' || ibuffer[len - 1] == '\n'){
			if(len > 1 ){
				if(ibuffer[len - 2] == 0x1B)
					continue;
			}
			olen = len;
			len = 0;
			return 1;
		}
	}
	return 0;
}

int get_input_buffer(char** buffer){
	*buffer = ibuffer;
	return olen;
}
/*
 * stdiodrv.c
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
 * Created on October 7, 2015, 9:59 PM
 */

#include "stdiodrv.h"
#include <hal_uart.h>

#define ESC 27

int uart_putchar(char c, FILE* stream){
    hal_uart_send_byte(c);
    return 0;
}

char uart_getchar(FILE *stream){
    char c = hal_uart_receive_byte();
    if(c == '\r')
        return '\n';
    else
        return c;
}

static char last_received = 0x00;
int uart_fgets(char *str, int size, FILE *stream)
{
	char *cp;
	int c;
	int recN = size;

	if ((stream->flags & __SRD) == 0 || size <= 0)
		return NULL;
	size--;
	for (c = 0, cp = str; size > 0; size--, cp++) {
		if ((c = getc(stream)) == EOF)
			return NULL;
                if(c == '\n' || c == '\r'){
                    if(last_received != ESC)
			    break;
                }
                last_received = (char)c;
		*cp = (char)c;
	}
	*cp = '\0';

	return recN - size;
}

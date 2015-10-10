/*
 * stdiodrv.h
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
 * Created on October 7, 2015, 9:58 PM
 */
#ifndef STDIODRV_H
#define	STDIODRV_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
    
int uart_putchar(char c, FILE* stream);

char uart_getchar(FILE *stream);

char *uart_fgets(char *str, int size, FILE *stream);

#ifdef	__cplusplus
}
#endif

#endif	/* STDIODRV_H */


/*
 *  hal_gpib.h
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
 * Created on September 14, 2015, 10:22 PM
 */

#ifndef HAL_GPIB_H
#define	HAL_GPIB_H

#ifdef	__cplusplus
extern "C" {
#endif
#define GPIB_PORT 1

    /* exported pin interface */
#define IFC     0
#define REN     1

#define DAV     2
#define ATN     3
#define EOI     4
#define SRQ     5
#define NRFD    6
#define NDAC    7
#define TE      8
#define DC      9
#define PE      10

#define GPIO1   11
#define GPIO2   12
#define GPIO3   13
#define GPIO4   14
#define GPIO5   15
#define TXD     16
#define RXD     17

    int hal_gpib_read_pin(int pin);
    void hal_gpib_set_pin(int pin);
    void hal_gpib_clear_pin(int pin);
    void hal_gpib_put_data(char c);
    char hal_gpib_read_data(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_GPIB_H */


/*
 * hal_gpib.h
 *
 * Copyright (c) 2016, Diego F. Asanza. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
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
 * Created on June 29, 2016, 9:28 PM
 */


#ifndef hal_gpib_H
#define hal_gpib_H

/* exported pin interface */
#define ATN_PIN     0x01
#define REN_PIN     0x02
#define IFC_PIN     0x04
#define SRQ_PIN     0x08

#define DAV_PIN     0x10
#define NDAC_PIN    0x20
#define NRFD_PIN    0x40

#define EOI_PIN     0x80


#define GPIO1   11
#define GPIO2   12
#define GPIO3   13
#define GPIO4   14
#define GPIO5   15
#define TXD     16
#define RXD     17

typedef enum {
	CONTROLLER = 0x01,
	DEVICE = 0x02,
}hal_gpib_driver_mode;

typedef enum {
	TALKER = 0x04,
	LISTENER = 0x08
}hal_gpib_data_direction;

void hal_gpib_set_driver_direction(hal_gpib_data_direction direction);
void hal_gpib_init(void);
int hal_gpib_is_signal_true(int pin);
void hal_gpib_set_signal_false(int pin);
void hal_gpib_set_signal_true(int pin);
void hal_gpib_put_data(char c);
char hal_gpib_read_data(void);
void hal_gpib_set_driver_mode(hal_gpib_driver_mode mode);



#endif // hal_gpib_H

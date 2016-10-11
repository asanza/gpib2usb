/*
 * hal_gpib.c
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

#include "hal_gpib.h"
#include "HardwareProfile.h"
#include <assert.h>

#if defined _18F2550
void hal_gpib_set_driver_direction(hal_gpib_data_direction direction);
void hal_gpib_set_driver_mode(hal_gpib_driver_mode mode);
void hal_gpib_init(void);
int hal_gpib_is_signal_true(int pin);
void hal_gpib_set_signal_false(int pin);
void hal_gpib_set_signal_true(int pin);
void hal_gpib_put_data(char c);
char hal_gpib_read_data(void);
#else
#define _spinmcr(pin, func)do {	\
		switch (pin) { \
		case IFC_PIN: func(_IFC); break; \
		case REN_PIN: func(_REN); break; \
		case DAV_PIN: func(_DAV); break; \
		case ATN_PIN: func(_ATN); break; \
		case EOI_PIN: func(_EOI); break; \
		case SRQ_PIN: func(_SRQ); break; \
		case NRFD_PIN: func(_NRFD); break; \
		case NDAC_PIN: func(_NDAC); break; \
		} } while (0);

/* manage data transfer channels (te line in hardware driver)*/
void hal_gpib_set_driver_direction(hal_gpib_data_direction direction)
{
	if (direction & LISTENER) {
		/* disable talker in hardware controller.*/
		PinClearValue(_TE_CTRL);
		PinClearValue(_TE_DATA);
		/* set microcontroller direction lines */
		PinAsOutput(_NDAC);
		PinAsOutput(_NRFD);
		PinAsInput(_DAV);
	}else if (direction & TALKER) {
		/* enable talker in hardware controller */
		PinSetValue(_TE_CTRL);
		PinSetValue(_TE_DATA);
		/* set microcontroller lines accordly */
		PinAsInput(_NDAC);
		PinAsInput(_NRFD);
		PinAsOutput(_DAV);
	}
}

/* manage bus management channels (dc line on hardware driver) */
void hal_gpib_set_driver_mode(hal_gpib_driver_mode mode)
{
	if (mode & CONTROLLER) {
		PinClearValue(_DC);
		PinAsOutput(_REN);
		PinAsOutput(_ATN);
		PinAsOutput(_IFC);
		PinAsInput(_SRQ);
		PinClearValue(_REN);
	}else if (mode & DEVICE) {
		PinSetValue(_DC);
		PinAsInput(_REN);
		PinAsInput(_ATN);
		PinAsInput(_IFC);
		PinAsOutput(_SRQ);
		PinSetValue(_REN);
	}
}

void hal_gpib_init(void)
{
	PinAsOutput(_PE);
	PinAsOutput(_TE_DATA);
	PinAsOutput(_DC);
	PinSetValue(_PE);
	PinClearValue(_TE_CTRL);
	PinClearValue(_DC);
}

int hal_gpib_is_signal_true(int pin)
{
	switch (pin) {
	case IFC_PIN:  pin = PinReadValue(_IFC); break;
	case REN_PIN:  pin = PinReadValue(_REN); break;
	case DAV_PIN:  pin = PinReadValue(_DAV); break;
	case ATN_PIN:  pin = PinReadValue(_ATN); break;
	case EOI_PIN:  pin = PinReadValue(_EOI); break;
	case SRQ_PIN:  pin = PinReadValue(_SRQ); break;
	case NRFD_PIN: pin = PinReadValue(_NRFD); break;
	case NDAC_PIN: pin = PinReadValue(_NDAC); break;
	default:
		assert(0);
	}
	return !pin;
}

void hal_gpib_set_signal_false(int pin)
{
	_spinmcr(pin, PinSetValue);
}

void hal_gpib_set_signal_true(int pin)
{
	_spinmcr(pin, PinClearValue);
}

void hal_gpib_put_data(char c)
{
	PinSetValue(_TE_DATA);
	PinClearValue(_PE);
	PortAsOutput(_DIO);
	PortSetValue(_DIO, ~c);
}

char hal_gpib_read_data(void)
{
	PinClearValue(_TE_DATA);
	PinClearValue(_PE);
	PortAsInput(_DIO);
	char val = PortReadValue(_DIO);
	return ~val;
}
#endif

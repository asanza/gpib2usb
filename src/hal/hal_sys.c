/*
 * hal_sys.c
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
 * Created on September 14, 2015, 10:23 PM
 */

#include "hal_sys.h"
#include "HardwareProfile.h"

void hal_sys_init(void)
{
    PinAsOutput(_SYSLED);
    sei();
}

void hal_sys_enter_critical(void)
{
    cli();
}

void hal_sys_exit_critical(void)
{
    sei();
}

void hal_sysled_on(void)
{
    PinSetValue(_SYSLED);
}

void hal_sysled_off(void)
{
    PinClearValue(_SYSLED);
}

void hal_sysled_toggle(void)
{
    PinToggleValue(_SYSLED);
}
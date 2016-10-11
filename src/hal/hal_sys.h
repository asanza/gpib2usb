/*
 * hal_sys.h
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


#ifndef HAL_SYS_H
#define HAL_SYS_H

#ifdef  __cplusplus
extern "C" {
#endif

void hal_sys_init(void);

void hal_sys_green_led_on(void);
void hal_sys_green_led_toggle(void);

void hal_sys_red_led_on(void);

void hal_sys_yellow_led_on(void);

void hal_sys_yellow_led_toggle(void);

void hal_sys_enter_critical(void);
void hal_sys_exit_critical(void);

#ifdef  __cplusplus
}
#endif

#endif  /* HAL_SYS_H */

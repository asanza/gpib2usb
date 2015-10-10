/*
 * hal_uart.h
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
#ifndef HAL_UART_H
#define	HAL_UART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef void(*data_received_callback)(char data);

    void hal_uart_init(data_received_callback on_data_received);

    void hal_uart_send_byte(char data);
    char hal_uart_receive_byte(void);
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_UART_H */


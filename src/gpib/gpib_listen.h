/*
 * gpib_listen.h
 *
 * Copyright (c) 2016, Diego F. Asanza. All rights reserved.
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
 * Created on September 17, 2016, 19:38 PM
 */

#ifndef gpib_listen_H
#define gpib_listen_H

typedef enum{
	GPIB_LISTEN_IDLE,
	GPIB_LISTEN_WAIT_FOR_DAV_TRUE,
	GPIB_LISTEN_WAIT_FOR_DAV_FALSE,
	GPIB_LISTEN_NUM_STATES
}gpib_listen_state_t;

typedef enum{
	GPIB_LISTEN_ERR_NONE,
	GPIB_LISTEN_ERR_TIMEOUT
}gpib_listen_error_t;

gpib_listen_error_t gpib_listen_tasks(void);

gpib_listen_error_t gpib_listen(void);

gpib_listen_state_t gpib_listen_state(void);

char gpib_listen_data(void);

void gpib_listen_reset(void);

#endif // gpib_listen_H

/*
 * sysio.h
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
 * Created on October 10, 2016, 10:08 PM
 */

#ifndef sysio_H
#define sysio_H

#include <stdbool.h>

typedef enum {
	SYSIO_EMPTY, // input empty, available for data
	SYSIO_DATA_AVAILABLE,
	SYSIO_CMD_AVAILABLE,
	SYSIO_LOCKED
}sysio_state_t;


/* returns len of error message */
int sysio_data_received(char* data, int len);
sysio_state_t sysio_get_state(void);
void sysio_release(void);



#endif // sysio_H

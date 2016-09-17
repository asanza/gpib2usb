/*
 * gpib_talk.h
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


#ifndef gpib_talk_H
#define gpib_talk_H

typedef enum{
	GPIB_TALK_IDLE,
	GPIB_TALK_WAIT_NRFD,
	GPIB_TALK_WAIT_NDAC,
	GPIB_TALK_NUM_STATES
}gpib_talk_state_t;

typedef enum{
	GPIB_TALK_ERR_NONE,
	GPIB_TALK_ERR_DEVICE_NOT_PRESENT,
	GPIB_TALK_ERR_LISTENER_TIMEOUT
}gpib_talk_error_t;

gpib_talk_error_t gpib_talk_tasks(void);

gpib_talk_error_t gpib_talk(char data);

gpib_talk_state_t gpib_talk_state(void);

void gpib_talk_reset(void);


#endif // gpib_send_H

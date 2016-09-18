/*
 * gpib_talk.c
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

#include "gpib_talk.h"
#include "hal/hal_gpib.h"

static gpib_talk_state_t state;

static gpib_talk_error_t on_talk_idle(void);
static gpib_talk_error_t on_talk_wait_nrfd(void);
static gpib_talk_error_t on_talk_wait_ndac(void);

typedef gpib_talk_error_t te_function_t(void);

static te_function_t* const state_table[GPIB_TALK_NUM_STATES] = {
	on_talk_idle,
	on_talk_wait_nrfd,
	on_talk_wait_ndac
};

gpib_talk_error_t gpib_talk_tasks(void){
	return state_table[state]();
}

gpib_talk_error_t gpib_talk(char data){
	hal_gpib_set_signal_false(DAV_PIN);
	if(!hal_gpib_is_signal_true(NDAC_PIN) &&
			!hal_gpib_is_signal_true(NRFD_PIN)){
		return GPIB_TALK_ERR_DEVICE_NOT_PRESENT;
	}
	hal_gpib_put_data(data);
	state = GPIB_TALK_WAIT_NRFD;
	return GPIB_TALK_ERR_NONE;
}


gpib_talk_state_t gpib_talk_state(void){
	return state;
}

void gpib_talk_reset(void){
	hal_gpib_set_signal_false(DAV_PIN);
	state = GPIB_TALK_IDLE;
}

static gpib_talk_error_t on_talk_idle(void){
	return GPIB_TALK_ERR_NONE;
}

static gpib_talk_error_t on_talk_wait_nrfd(void){
	if(hal_gpib_is_signal_true(NRFD_PIN)){
		return GPIB_TALK_ERR_NONE;
	}
	hal_gpib_set_signal_true(DAV_PIN);
	state = GPIB_TALK_WAIT_NDAC;
	return GPIB_TALK_ERR_NONE;
}

static gpib_talk_error_t on_talk_wait_ndac(void){
	if(hal_gpib_is_signal_true(NDAC_PIN)){
		return GPIB_TALK_ERR_NONE;
	}
	hal_gpib_set_signal_false(DAV_PIN);
	state = GPIB_TALK_IDLE;
	return GPIB_TALK_ERR_NONE;
}

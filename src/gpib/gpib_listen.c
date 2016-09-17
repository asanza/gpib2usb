/*
 * gpib_listen.c
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

#include "gpib_listen.h"
#include "hal/hal_gpib.h"

static gpib_listen_state_t state;

static char gdata;

static gpib_listen_error_t on_listen_idle(void);
static gpib_listen_error_t on_listen_wait_for_dav_true(void);
static gpib_listen_error_t on_listen_wait_for_dav_false(void);

typedef gpib_listen_error_t le_function_t(void);

static le_function_t const state_table[GPIB_LISTEN_NUM_STATES] = {
	on_listen_idle,
	on_listen_wait_for_dav_true,
	on_listen_wait_for_dav_false
}

gpib_listen_error_t gpib_listen_tasks(void){
	return state_table[state]();
}

gpib_listen_error_t gpib_listen(void){
	return GPIB_LISTEN_ERR_NONE;
}

gpib_listen_state_t gpib_listen_state(void){
	return GPIB_LISTEN_ERR_NONE;
}

void gpib_listen_reset(void){

}

char gpib_listen_data(void){
	
}

static gpib_listen_error_t on_listen_idle(void){
	return GPIB_LISTEN_ERR_NONE;
}

static gpib_listen_error_t on_listen_wait_for_dav_true(void){
	return GPIB_LISTEN_ERR_NONE;
}

static gpib_listen_error_t on_listen_wait_for_dav_false(void){
	return GPIB_LISTEN_ERR_NONE;
}

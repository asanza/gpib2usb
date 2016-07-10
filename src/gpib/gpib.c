/*
 * gpib.c
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
 * Created on October 8, 2015, 10:08 PM
 */

#include "gpib.h"
#include <sys/parser.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MLA_CODE 0x20
#define MTA_CODE 0x40
#define LAD_CODE 0x20
#define UNL_CODE 0x3F
#define TAD_CODE 0x40
#define UNT_CODE 0x5F
#define SAD_CODE 0x60
#define LLO_CODE 0x11
#define DCL_CODE 0x14
#define PPU_CODE 0x15
#define SPE_CODE 0x18
#define SPD_CODE 0x19
#define GTL_CODE 0x01
#define SDC_CODE 0x04
#define PPC_CODE 0x05
#define GET_CODE 0x08
#define TCT_CODE 0x09
#define PPE_CODE 0x60
#define PPD_CODE 0x70

typedef enum{
	IDLE,
	NO_READY_FOR_DATA,
	NO_DATA_ACCEPTED,
	DATA_AVAILABLE,
	NO_DATA_AVAILABLE,
	NUM_STATES
}state_t;

static state_t actual_st = IDLE;
static char buff;

static GPIB_Event st_idle(state_t* state);
static GPIB_Event st_no_ready_for_data(state_t* state);
static GPIB_Event st_no_data_accepted(state_t* state);
static GPIB_Event st_data_available(state_t* state);
static GPIB_Event st_no_data_available(state_t* state);

typedef GPIB_Event st_function_t(state_t* state);

static st_function_t* const state_table[NUM_STATES] = {
	st_idle,
	st_no_ready_for_data,
	st_no_data_accepted,
	st_data_available,
	st_no_data_available
};

GPIB_Event GPIB_Tasks(void){
	return state_table[actual_st](&actual_st);
}


static GPIB_Event st_idle(state_t* state){
	assert(*state == IDLE);
	return GPIB_EVT_NONE;
}

static GPIB_Event st_no_ready_for_data(state_t* state){
	assert(*state == NO_READY_FOR_DATA);
	*state = NO_DATA_ACCEPTED;
	return GPIB_EVT_NONE;
}

static GPIB_Event st_no_data_accepted(state_t* state){
	assert(*state == NO_DATA_ACCEPTED);
	*state = IDLE;
	return GPIB_EVT_NONE;
}

static GPIB_Event st_data_available(state_t* state){
	assert(*state == DATA_AVAILABLE);
	*state = NO_DATA_AVAILABLE;
	return GPIB_EVT_NONE;
}

static GPIB_Event st_no_data_available(state_t* state){
	assert(*state == NO_DATA_AVAILABLE);
	return GPIB_EVT_DATA_AVAILABLE;
}

int GPIB_Send(GPIB_Command cmd, char data){
	if(actual_st != IDLE) return -1;
	buff = data;
	actual_st = NO_READY_FOR_DATA;
}

char GPIB_Receive(void){
	actual_st = DATA_AVAILABLE;
	return buff;
}
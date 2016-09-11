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
#include "hal/hal_gpib.h"
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

static state_t actual_st = GPIB_IDLE;
static char buff;

static GPIB_Event st_idle(state_t* state);
static GPIB_Event st_no_ready_for_data(state_t* state);
static GPIB_Event st_no_data_accepted(state_t* state);
static GPIB_Event st_data_available(state_t* state);
static GPIB_Event st_no_data_available(state_t* state);

typedef GPIB_Event st_function_t (state_t * state);

static st_function_t* const state_table[NUM_STATES] = {
	st_idle,
	st_no_ready_for_data,
	st_no_data_accepted,
	st_data_available,
	st_no_data_available
};

void GPIB_Reset(void)
{
	actual_st = GPIB_IDLE;
}

state_t GPIB_State(void)
{
	return actual_st;
}

GPIB_Event GPIB_Tasks(void)
{
	return state_table[actual_st](&actual_st);
}


static GPIB_Event st_idle(state_t* state)
{
	assert(*state == GPIB_IDLE);
	return GPIB_EVT_NONE;
}

static GPIB_Event gpib_send(state_t* state, char data)
{
	assert(*state == GPIB_IDLE);
	hal_gpib_set_driver_direction(TALKER);
	hal_gpib_set_signal_false(DAV_PIN);
	if (!hal_gpib_is_signal_true(NRFD_PIN) &&
	    !hal_gpib_is_signal_true(NDAC_PIN)) {
		*state = GPIB_IDLE;
		return GPIB_EVT_RX_ERROR;
	}
	hal_gpib_put_data(data);
	*state = NO_READY_FOR_DATA;
	return GPIB_EVT_NONE;
}

static GPIB_Event gpib_send_cmd(state_t* state, char cmd)
{
	hal_gpib_set_signal_true(ATN_PIN);
	return gpib_send(state, cmd);
}

static GPIB_Event st_no_ready_for_data(state_t* state)
{
	assert(*state == NO_READY_FOR_DATA);
	if (hal_gpib_is_signal_true(NRFD_PIN))
		return GPIB_EVT_NONE;
	hal_gpib_set_signal_true(DAV_PIN);
	*state = NO_DATA_ACCEPTED;
	return GPIB_EVT_NONE;
}

static GPIB_Event st_no_data_accepted(state_t* state)
{
	assert(*state == NO_DATA_ACCEPTED);
	if (hal_gpib_is_signal_true(NDAC_PIN))
		return GPIB_EVT_NONE;
	hal_gpib_set_signal_false(DAV_PIN);
	/* TODO: check if this do what you think */
	if (hal_gpib_is_signal_true(ATN_PIN))
		hal_gpib_set_signal_false(ATN_PIN);
	*state = GPIB_IDLE;
	return GPIB_EVT_NONE;
}

static GPIB_Event st_data_available(state_t* state)
{
	assert(*state == DATA_AVAILABLE);
	if (!hal_gpib_is_signal_true(DAV_PIN))
		return GPIB_EVT_NONE;
	hal_gpib_set_signal_true(NRFD_PIN);
	buff = hal_gpib_read_data();
	*state = NO_DATA_AVAILABLE;
	return GPIB_EVT_NONE;
}

static GPIB_Event st_no_data_available(state_t* state)
{
	assert(*state == NO_DATA_AVAILABLE);
	if (hal_gpib_is_signal_true(DAV_PIN))
		return GPIB_EVT_NONE;
	hal_gpib_set_signal_true(NDAC_PIN);
	return GPIB_EVT_DATA_AVAILABLE;
}

int GPIB_Send(GPIB_Command cmd, char data)
{
	if (actual_st != GPIB_IDLE) return GPIB_EVT_TX_ERROR;
	char code;
	switch (cmd) {
	case ATN:
		if (data)
			hal_gpib_set_signal_true(ATN_PIN);
		else
			hal_gpib_set_signal_false(ATN_PIN);
		break;
	case IFC:
		if (data)
			hal_gpib_set_signal_true(IFC_PIN);
		else
			hal_gpib_set_signal_false(IFC_PIN);
		break;
	case SRQ:
		if (data)
			hal_gpib_set_signal_true(SRQ_PIN);
		else
			hal_gpib_set_signal_false(SRQ_PIN);
		break;
	case REN:
		if (data)
			hal_gpib_set_signal_true(REN_PIN);
		else
			hal_gpib_set_signal_false(REN_PIN);
		break;
	case EOI:
		if (data)
			hal_gpib_set_signal_true(EOI_PIN);
		else
			hal_gpib_set_signal_false(EOI_PIN);
		break;
	case MLA: code = MLA_CODE; break;
	case MTA: code = MTA_CODE; break;
	case LAD: code = LAD_CODE + data; break;
	case UNL: code = UNL_CODE; break;
	case TAD: code = TAD_CODE + data; break;
	case UNT: code = UNT_CODE; break;
	case SAD: code = SAD_CODE + data; break;
	case LLO: code = LLO_CODE; break;
	case DCL: code = DCL_CODE; break;
	case PPU: code = PPU_CODE; break;
	case _SPE: code = SPE_CODE; break;
	case SPD: code = SPD_CODE; break;
	case GTL: code = GTL_CODE; break;
	case SDC: code = SDC_CODE; break;
	case PPC: code = PPC_CODE; break;
	case GET: code = GET_CODE; break;
	case TCT: code = TCT_CODE; break;
	case PPE: code = PPE_CODE; break;
	case PPD: code = PPD_CODE; break;
	case DAB:
		hal_gpib_set_signal_false(ATN_PIN);
		return gpib_send(&actual_st, data);
	default: assert(0);
	}
	return gpib_send_cmd(&actual_st, code);
}

void GPIB_Receive(void)
{
	hal_gpib_set_driver_direction(LISTENER);
	hal_gpib_set_signal_true(NDAC_PIN);
	hal_gpib_set_signal_false(NRFD_PIN);
	actual_st = DATA_AVAILABLE;
}

char GPIB_Get(void)
{
	return buff;
}

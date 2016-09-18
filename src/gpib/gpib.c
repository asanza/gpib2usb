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
#include "gpib_talk.h"
#include "gpib_listen.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static GPIB_state_t state = GPIB_IDLE;
static char buff;

static GPIB_Event on_gpib_idle(void);
static GPIB_Event on_gpib_talk(void);
static GPIB_Event on_gpib_listen(void);

static GPIB_Event gpib_send_data(char data);
static GPIB_Event gpib_send_cmd(char cmd);

typedef GPIB_Event st_function_t (void);

static st_function_t* const state_table[NUM_STATES] = {
	on_gpib_idle,
	on_gpib_talk,
	on_gpib_listen
};

void GPIB_Mode(int mode){
	hal_gpib_set_driver_mode(CONTROLLER);
}

void GPIB_Reset(void)
{
	state = GPIB_IDLE;
}

GPIB_state_t GPIB_State(void)
{
	return state;
}

GPIB_Event GPIB_Tasks(void)
{
	return state_table[state]();
}

static GPIB_Event on_gpib_talk(void){
	gpib_talk_error_t err;
	err = gpib_talk_tasks();
	if(err == GPIB_EVT_NONE){
		if(gpib_talk_state() == GPIB_TALK_IDLE){
			/* done with transmission */
			state = GPIB_IDLE;
		}
		return GPIB_EVT_NONE;
	} else {
		state = GPIB_IDLE;
		gpib_talk_reset();
		return GPIB_EVT_TX_ERROR;
	}
}

static GPIB_Event on_gpib_listen(void){
	gpib_talk_error_t err;
	err = gpib_listen_tasks();
	if(err == GPIB_EVT_NONE){
		if(gpib_listen_state() == GPIB_LISTEN_IDLE){
			state = GPIB_IDLE;
			return GPIB_EVT_DATA_AVAILABLE;
		}
		return GPIB_EVT_NONE;
	} else {
		state = GPIB_IDLE;
		gpib_listen_reset();
		return GPIB_EVT_RX_ERROR;
	}
}

static GPIB_Event on_gpib_idle(void){
	return GPIB_EVT_NONE;
}

static GPIB_Event gpib_send_data(char data)
{
	gpib_talk_error_t err;
	err = gpib_talk(data);
	if(err == GPIB_TALK_ERR_NONE){
		state = GPIB_TALK;
		return GPIB_EVT_NONE;
	} else {
		return GPIB_EVT_TX_ERROR;
	}
}

static GPIB_Event gpib_send_cmd(char cmd)
{
	if(!cmd){
		return GPIB_EVT_NONE;
	}
	hal_gpib_set_signal_true(ATN_PIN);
	return gpib_send_data(cmd);
}

GPIB_Event GPIB_Send(GPIB_Command cmd, char data)
{
	if (state != GPIB_IDLE) return GPIB_EVT_TX_ERROR;
	char code = 0x00;
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
		return gpib_send_data(data);
	default: assert(0);
	}
	return gpib_send_cmd(code);
}

GPIB_Event GPIB_Receive(void)
{
	gpib_listen_error_t err;
	err = gpib_listen();
	if(err != GPIB_LISTEN_ERR_NONE)
		return GPIB_EVT_RX_ERROR;
	state = GPIB_LISTEN;
	return GPIB_EVT_NONE;
}

char GPIB_Get(void)
{
	return gpib_listen_data();
}

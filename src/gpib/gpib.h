/*
 * gpib.h
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

#ifndef gpib_H
#define gpib_H

#ifndef lib_gpib_h
#define lib_gpib_h

typedef enum {
    /* uniline */
    ATN,
    IFC,
    REN,
    SRQ,
    EOI,
    /* universal */
    DCL,
    LLO,
    _SPE,
    SPD,
    PPU,
    /* addressed */
    MLA,
    MTA,
    LAD,
    UNL,
    TAD,
    UNT,
    SAD,
    GTL,
    SDC,
    PPC,
    GET,
    TCT,
    PPE,
    PPD,
    DAB
} GPIB_Command;

typedef enum {
	GPIB_EVT_NONE = 0x00,
	GPIB_EVT_DATA_AVAILABLE = 0x01,
  GPIB_EVT_TX_ERROR = 0x02,
  GPIB_EVT_RX_ERROR
} GPIB_Event;

typedef enum{
	GPIB_IDLE,
	NO_READY_FOR_DATA,
	NO_DATA_ACCEPTED,
	DATA_AVAILABLE,
	NO_DATA_AVAILABLE,
	NUM_STATES
}state_t;

state_t GPIB_State(void);

/**
 * @brief      Initializes the gpib driver with a given address.
 *
 * @param[in]  our_address  Address of this device.
 *
 * @return     -1 if address invalid.
 */
int GPIB_Init(int our_address);

/**
 * @brief      Send a GPIB command to the attached bus.
 * 			   This is an asynchronous call. cmd and data are copied
 * 			   into a buffer, and then send sequentially by calling the
 * 			   GPIB_Task function.
 *
 * @param[in]  cmd   The command
 * @param[in]  data  The data
 *
 * @return     0 if data could be sent. -1 if buffer is not empty.
 */
int GPIB_Send(GPIB_Command cmd, char data);

/**
 * @brief      Set the bus to listen communications.
 *             after calling this function, the bus changes to
 *             listen. It will listen on each GPIB_Task call. GPIB_
 *             task then returns GPIB_EVT_DATA_AVAILABLE when new data
 *             arrives. Call GPIB_Get to get the last received data.
 *
 */
void GPIB_Receive(void);

/**
 * @brief      get the last received byte
 *
 * @return     the last received byte
 */
char GPIB_Get(void);

/**
 * @brief      Perform gpib tasks.
 * 			   This library provides an asynchronous interface to the gpib
 * 			   bus. As such, all function calls are non-blocking. I/O is
 * 			   performed calling this functions.
 * @return 	   GPIB_EVT_DATA_AVAILABLE if data is available in the input buffer
 * 			   GPIB_EVT_TX_READY if the tx buffer is empty.
 */
GPIB_Event GPIB_Tasks(void);

/**
 * @brief Reset GPIB Statemachine
 */
void GPIB_Reset(void);

#endif


#endif // gpib_H

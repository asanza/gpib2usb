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

/* Initializes the GPIB driver with a given gpib address.
 * returns -1 in case of error.
 */
int GPIB_Init(int our_address);

int GPIB_Send(GPIB_Command cmd, char data);

int GPIB_Receive(char* data);

#endif // gpib_H

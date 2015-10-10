/*
 * input.h
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
#ifndef INPUT_H
#define	INPUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CR 13
#define LF 10
#define ESC 27

    typedef enum {
        CMD_ADDR,
        CMD_AUTO,
        CMD_CLR,
        CMD_EOI,
        CMD_EOS,
        CMD_EOT_ENABLE,
        CMD_EOT_CHAR,
        CMD_IFC,
        CMD_LLO,
        CMD_LOC,
        CMD_LON,
        CMD_MODE,
        CMD_READ,
        CMD_READ_TMO_MS,
        CMD_RST,
        CMD_SAVE_CONFIG,
        CMD_RST_FACTORY,
        CMD_SPOLL,
        CMD_SRQ,
        CMD_STATUS,
        CMD_TRG,
        CMD_VER,
        CMD_HELP,
        CMD_COUNT
    } devcmd;

    /* Parse input string. Return pointer to processed string.
     * Input string contains scape characters. Return pointer do not contain
     * escape characters. */
    int parse_input(devcmd* cmd, char* input, int buffer_size);

#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_H */


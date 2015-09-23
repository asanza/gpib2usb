/*
 *  hal_gpib.h
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
 * Created on September 14, 2015, 10:22 PM
 */

#ifndef HAL_GPIB_H
#define	HAL_GPIB_H

#ifdef	__cplusplus
extern "C" {
#endif

    /* Initializes the GPIB driver with a given gpib address. 
     * returns -1 in case of error.
     */
    int GPIB_Init(int our_address);
    
    /* sends a single character to the gpib device addressed
     * by listen. returns -1 in case of error */
    int GPIB_Send(int listen, char what);
    
    /* sends a string of bytes to the gpib device addressed by listen. 
     * Returns -1 in case of error. */
    int GPIB_PutStr(int listen, char *string, int count);

    /* simply return the status of the GPIB status lines. These are 
     * encoded in the lower 8 bits of the return value as:
     * IFC REN EOI SRQ NDAC NRF ATN DAV
     */
    int GPIB_Stat(void);
    
    /* read a character from the GPIB device addressed by listen. 
     * Returns the character or -1 in case of error */
    int GPIB_Get(int listen);
    
    /* reads a string of data from the device addressed by listen. 
     * Returns the number of bytes read into buf or -1 if error. */
    int GPIB_GetStr(int listen, char*buf);
    
    /* Returns the serial poll on the device at listen. Returnss
     * the serial poll status in the lower 8 bits or -1 if error */
    int GPIB_SerPoll(int listen);
    
    /* puts value what out as an address byte. return -1 if error. */
    int GPIB_PutAdd(char what);
    
    /* puts what on the gpib bus as data. returns -1 if error. */
    int GPIB_PutData(char what);
    
    /* read the value on the gpib bus as data value and returns it or -1 in case of error. */
    int GPIB_GetData(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_GPIB_H */


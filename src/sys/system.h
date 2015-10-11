/*
 * system.h
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
 * Created on October 9, 2015, 8:44 PM
 */
#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum{
        SYSERR_NONE,
                SYSERR_WRONG_PARAMETER,
                SYSERR_NOT_IMPLEMENTED,
                SYSERR_WRITE_ERROR
    }syserr;
    
    typedef enum{
        SYSREAD_UNTIL_TIMEOUT,
                SYSREAD_UNTIL_EOI,
                SYSREAD_UNTIL_CHAR
    }sysread;
    
    void sys_init(void);
    syserr sys_set_addr(uint8_t addr);
    uint8_t sys_get_addr(void);
    void sys_gpib_read(char* buffer, int size, sysread until, int charval);
    syserr sys_gpib_write(char* buffer, int size);
    

#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */


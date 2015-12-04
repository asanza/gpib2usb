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

    /* exported pin interface */
#define ATN_PIN     0x01
#define REN_PIN     0x02
#define IFC_PIN     0x04
#define SRQ_PIN     0x08
    
#define DAV_PIN     0x10
#define NDAC_PIN    0x20
#define NRFD_PIN    0x40

#define EOI_PIN     0x80

    
#define GPIO1   11
#define GPIO2   12
#define GPIO3   13
#define GPIO4   14
#define GPIO5   15
#define TXD     16
#define RXD     17
    
    typedef enum{
    CONTROLLER = 0x01,
            DEVICE = 0x02,
            TALKER = 0x04,
            LISTENER = 0x08
}driver_mode;
    
/*
#define TE_DATA      18
#define TE_CTRL      8
#define DC      9
#define PE      10
*/
    void hal_gpib_init(void);
    int hal_gpib_is_signal_true(int pin);
    void hal_gpib_set_signal_false(int pin);
    void hal_gpib_set_signal_true(int pin);
    void hal_gpib_put_data(char c);
    char hal_gpib_read_data(void);
void driver_switch_mode(driver_mode mode);
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_GPIB_H */


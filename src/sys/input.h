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
* Created on October 8, 2016, 10:08 PM
*/

#ifndef input_H
#define input_H

/** returns len of error message on str */
int sys_on_usb_data_received(char* str, int len);

int sys_get_input(char** input, int* len);

void sys_release_input(void);

#endif // input_H

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
* Created on October 8, 2016, 10:08 PM
*/

#ifndef system_H
#define system_H
#include <stdbool.h>

typedef enum{
	SYS_ERR_NONE,
	SYS_ERR_COMMAND_UNKNOWN,
}sys_error_t;

int sys_process_input(char* str, int len);
int sys_process_command(char*str, int len);
bool sys_gpib_has_data(void);
int sys_gpib_get_buffer(char** out_buf);


#endif // system_H

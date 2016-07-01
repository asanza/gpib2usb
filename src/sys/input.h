/*
 * input.c
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
#ifndef input_H
#define input_H

#define INPUT_SIZE 256

#include <stdlib.h>

/**
 * @brief      concatenate incomming data from buffer to an
 *internal buffer, until a carriage return or line feed.
 *
 * @param[in]  buffer  The incomming data
 * @param[in]  size    The incomming data size
 *
 * @return     -1 if overflow, 0 if no linefeed or carriage
 * 				return received, 
 * 				1 if linefeed or 
 * 				carriage return received.
 */
int read_line(const char* buffer, size_t size);

/**
 * @brief      get a pointer to the incomming input buffer.
 *
 * @param      buffer  The buffer
 *
 * @return     The input buffer.
 */
int get_input_buffer(char** buffer);

#endif // input_H

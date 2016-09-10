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
 * @param[in]  size    The incomming data size (less than 256)
 *
 * @return     -1 if overflow, 0 if no linefeed or carriage
 * 				return received,
 * 				1 if linefeed or
 * 				carriage return received.
 */
int read_line(const char* buffer, size_t size);

/**
 * @brief      process incomming data.
 * 			   call this function when readline returns 1 in order
 * 			   to process the incomming data.
 *
 * @param      str  Pointer to the internal error buffer. The
 * 				error buffer contains the error (or success) messa
 * 				ge after processing the incoming data (string).
 *
 * @return     { len of the internal error buffer. }
 */
int process_input(char** out);

/**
 * @brief      get a pointer to the internal buffer
 * 			   this function should not be used. only here to make test easy.
 *
 * @param      str  Pointer to the internal buffer
 *
 * @return    len of the internal buffer
 */
int get_input_buffer(char** buffer);

#endif // input_H

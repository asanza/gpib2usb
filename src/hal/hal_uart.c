/*
 * hal.c
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
#include "HardwareProfile.h"
#include "hal_uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

data_received_callback on_data_received;

void hal_uart_init(data_received_callback _on_data_received){
    	// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR0H = (BAUD_PRESCALE >> 8);
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRR0L = BAUD_PRESCALE;
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C = (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);//|(1<<RXCIE0);
        // Enable internal pullup on rx pin
        PortSetPin(_RXD);
        on_data_received = _on_data_received;
}

void hal_uart_send_byte(char data) {
    if (data == '\n') {
        hal_uart_send_byte('\r');
    }    // Wait if a byte is being transmitted, after finished transmit new data
    while ((UCSR0A & (1 << UDRE0)) == 0);
    UDR0 = data;
}

char hal_uart_receive_byte(){
    while ((UCSR0A & (1 << RXC)) == 0) {}; 
      return UDR0; 
}

ISR(USART0_RX_vect) {
    // Fetch the received byte value into the variable "USART_ReceivedByte"
    char data = UDR0;
    if(on_data_received)
        on_data_received(data);
}

#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

#define DIO PORTA

#define IFC PORTC6
#define REN PORTC7

#define DAV PORTC3
#define ATN PORTC1
#define EOI PORTC2
#define SRQ PORTC0
#define NRFD PORTC4
#define NDAC PORTC5

#define TE PORTD4
#define DC PORTD5
#define PE PORTD1

#define GPIO1 PORTB0
#define GPIO2 PORTB4
#define GPIO3 PORTB5
#define GPIO4 PORTB6
#define GPIO5 PORTB7

// Internal RC oscillator, 8MHz
#define F_CPU 8000000UL

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#endif /*_HARDWAREPROFILE_H_*/

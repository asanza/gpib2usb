#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_
#include <avr/io.h>
#define BIT0 0x00
#define BIT1 0x01
#define BIT2 0x02
#define BIT3 0x03
#define BIT4 0x04
#define BIT5 0x05
#define BIT6 0x06
#define BIT7 0x07


#define _DIO PORTA

#define _IFC PORTC, BIT6
#define _REN PORTC, BIT7

#define _DAV PORTC, BIT3
#define _ATN PORTC, BIT1
#define _EOI PORTC, BIT2
#define _SRQ PORTC, BIT0
#define _NRFD PORTC, BIT4
#define _NDAC PORTC, BIT5

#define _TE PORTD, BIT4
#define _DC PORTD, BIT5
#define _PE PORTD, BIT1

#define _GPIO1 PORTB, BIT0
#define _GPIO2 PORTB, BIT4
#define _GPIO3 PORTB, BIT5
#define _GPIO4 PORTB, BIT6
#define _GPIO5 PORTB, BIT7

#define _TXD   PORTE, BIT0
#define _RXD   PORTE, BIT1

#define _SYSLED PORTF, BIT1

#define USART_BAUDRATE 115200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/* Auxiliar macros */
#define PinSetInput(val) _PinSetInput(val)
#define PinSetOutput(val) _PinSetOutput(val)

#define _PinSetInput(port, pin)do{ \
        if(port == PORTA) DDRA &= ~_BV(pin); \
        if(port == PORTB) DDRB &= ~_BV(pin); \
        if(port == PORTC) DDRC &= ~_BV(pin); \
        if(port == PORTD) DDRD &= ~_BV(pin); \
        if(port == PORTE) DDRE &= ~_BV(pin); \
        if(port == PORTF) DDRF &= ~_BV(pin); }while(0);

#define _PinSetOutput(port, pin)do{ \
        if(port == PORTA) DDRA |= _BV(pin); \
        if(port == PORTB) DDRB |= _BV(pin); \
        if(port == PORTC) DDRC |= _BV(pin); \
        if(port == PORTD) DDRD |= _BV(pin); \
        if(port == PORTE) DDRE |= _BV(pin); \
        if(port == PORTF) DDRF |= _BV(pin); }while(0);

#define PortSetInput(port)do{ \
        if(port == PORTA) DDRA = 0x00; \
        if(port == PORTB) DDRB = 0x00; \
        if(port == PORTC) DDRC = 0x00; \
        if(port == PORTD) DDRD = 0x00; \
        if(port == PORTE) DDRE = 0x00; \
        if(port == PORTF) DDRF = 0x00; }while(0);

#define PortSetOutput(port)do{ \
        if(port == PORTA) DDRA = 0xFF; \
        if(port == PORTB) DDRB = 0xFF; \
        if(port == PORTC) DDRC = 0xFF; \
        if(port == PORTD) DDRD = 0xFF; \
        if(port == PORTE) DDRE = 0xFF; \
        if(port == PORTF) DDRF = 0xFF; }while(0);

#define PortSetPin(val) _PortSetPin(val)
#define PortClearPin(val) _PortClearPin(val)
#define PortTogglePin(val)_PortTogglePin(val)
#define _PortTogglePin(port, pin){port ^= _BV(pin);}
#define _PortSetPin(port, pin){port |= _BV(pin);}
#define _PortClearPin(port, pin){port &= ~_BV(pin);}
#define PortReadPin(val) _PortReadPin(val)
#define _PortReadPin(port, pin){ }

#endif /*_HARDWAREPROFILE_H_*/

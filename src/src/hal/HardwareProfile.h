#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

#define BIT0 0x00
#define BIT1 0x01
#define BIT2 0x02
#define BIT3 0x03
#define BIT4 0x04
#define BIT5 0x05
#define BIT6 0x06
#define BIT7 0x07


#define DIO PORTA

#define IFC PORTC, BIT6
#define REN PORTC, BIT7

#define DAV PORTC, BIT3
#define ATN PORTC, BIT1
#define EOI PORTC, BIT2
#define SRQ PORTC, BIT0
#define NRFD PORTC, BIT4
#define NDAC PORTC, BIT5

#define TE PORTD, BIT4
#define DC PORTD, BIT5
#define PE PORTD, BIT1

#define GPIO1 PORTB, BIT0
#define GPIO2 PORTB, BIT4
#define GPIO3 PORTB, BIT5
#define GPIO4 PORTB, BIT6
#define GPIO5 PORTB, BIT7

#define TXD   PORTE, BIT0
#define RXD   PORTE, BIT1

// Internal RC oscillator, 8MHz
#define F_CPU 8000000UL

#define USART_BAUDRATE 9600
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
#define _PortSetPin(port, pin){port |= _BV(pin);}
#define _PortClearPin(port, pin){port &= ~_BV(pin);}

#endif /*_HARDWAREPROFILE_H_*/

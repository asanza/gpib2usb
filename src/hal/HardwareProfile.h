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

/* define pins, Format: PORT NAME, PIN NAME*/

/* data port */
#define _DIO A
#define _PE D, BIT1
#define _TE_DATA B, BIT4
/* bus management lines */
#define _ATN C, BIT1
#define _IFC C, BIT6
#define _REN C, BIT7
#define _EOI C, BIT2
#define _SRQ C, BIT0
/* talker enable for control */
#define _TE_CTRL D, BIT4
/* data direction control */
#define _DC D, BIT5

/* bus handshake lines */
#define _DAV C, BIT3
#define _NRFD C, BIT4
#define _NDAC C, BIT5


#define _GPIO1 B, BIT0
#define _GPIO2 B, BIT4
#define _GPIO3 B, BIT5
#define _GPIO4 B, BIT6
#define _GPIO5 B, BIT7

#define _TXD   E, BIT0
#define _RXD   E, BIT1

#define _SYSLED F, BIT1

#define USART_BAUDRATE 57600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/* Auxiliar macros */
#define PinSetInput(val)        _PinSetInput(val)
#define PinSetOutput(val)       _PinSetOutput(val)
#define PinSetValue(val)        _PinSetValue(val)
#define PinClearValue(val)      _PinClearValue(val)
#define PinToggleValue(val)     _PinToggleValue(val)
#define PinReadValue(val)       _PinReadValue(val)

#define PortSetInput(val)       _PortSetInput(val)
#define PortSetOutput(val)      _PortSetOutput(val)
#define PortSetValue(port, val)       _PortSetValue(port, val)
#define PortReadValue(port)      _PortReadValue(port)

#define _PinSetInput(port, pin) DDR##port &= ~_BV(pin)
#define _PinSetOutput(port, pin) DDR##port |= _BV(pin)
#define _PinToggleValue(port, pin) PORT##port ^= _BV(pin)
#define _PinSetValue(port, pin) PORT##port |= _BV(pin)
#define _PinClearValue(port, pin) PORT##port &= ~_BV(pin)
#define _PinReadValue(port, pin) PIN##port & _BV(pin)

#define _PortSetInput(port) DDR##port = 0x00
#define _PortSetOutput(port) DDR##port = 0xFF
#define _PortSetValue(port, value) PORT##port = value
#define _PortReadValue(port) PIN##port


#endif /*_HARDWAREPROFILE_H_*/

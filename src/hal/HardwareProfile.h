#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

#include <xc.h>

#define BIT0 0x00
#define BIT1 0x01
#define BIT2 0x02
#define BIT3 0x03
#define BIT4 0x04
#define BIT5 0x05
#define BIT6 0x06
#define BIT7 0x07

#define _BV(val) (1 << val);

/* define pins, Format: PORT NAME, PIN NAME*/

/* data port */
#define _DIO D
#define _PE E, BIT1
#define _TE_DATA B, BIT3
/* bus management lines */
#define _ATN E, BIT0
#define _IFC A, BIT1
#define _REN A, BIT0
#define _EOI A, BIT5
#define _SRQ B, BIT0
/* talker enable for control */
#define _TE_CTRL B, BIT3
/* data direction control */
#define _DC B, BIT4

/* bus handshake lines */
#define _DAV A, BIT4
#define _NRFD A, BIT3
#define _NDAC A, BIT2

/* LEDS */
#define GREEN_LED   C, BIT2
#define YELLOW_LED  C, BIT1
#define RED_LED     C, BIT0

/* Auxiliary macros */
#define PinAsInput(val)        _PinAsInput(val)
#define PinAsOutput(val)       _PinAsOutput(val)
#define PinSetValue(val)        _PinSetValue(val)
#define PinClearValue(val)      _PinClearValue(val)
#define PinToggleValue(val)     _PinToggleValue(val)
#define PinReadValue(val)       _PinReadValue(val)
#define PinDirection(val)		_PinDirection(val)

#define PortAsInput(val)       _PortAsInput(val)
#define PortAsOutput(val)      _PortAsOutput(val)
#define PortDirection(val)	   _PortDirection(val)
#define PortSetValue(port, val)       _PortSetValue(port, val)
#define PortReadValue(port)      _PortReadValue(port)

#define _PinAsInput(port, pin) TRIS##port |= _BV(pin)
#define _PinAsOutput(port, pin) TRIS##port &= ~_BV(pin)
#define _PinToggleValue(port, pin) LAT##port ^= _BV(pin)
#define _PinSetValue(port, pin) LAT##port |= _BV(pin)
#define _PinClearValue(port, pin) LAT##port &= ~_BV(pin)
#define _PinReadValue(port, pin) PORT##port & _BV(pin)
#define _PinDirection(port, pin) TRIS##port &= _BV(pin)

#define _PortAsInput(port) TRIS##port = 0x00
#define _PortAsOutput(port) TRIS##port = 0xFF
#define _PortSetValue(port, value) LAT##port = value
#define _PortReadValue(port) PORT##port
#define _PortDirection(port) TRIS##port


#endif /*_HARDWAREPROFILE_H_*/

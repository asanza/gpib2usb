#include "HardwareProfile.h"
#include <assert.h>
#include "hal_gpib.h"

#define _spinmcr(pin, func)do{ \
switch(pin){ \
        case IFC: func(_IFC); break; \
        case REN: func(_REN); break; \
        case DAV: func(_DAV); break; \
        case ATN: func(_ATN); break; \
        case EOI: func(_EOI); break; \
        case SRQ: func(_SRQ); break; \
        case NRFD: func(_NRFD); break; \
        case NDAC: func(_NDAC); break; \
}}while(0);

void hal_gpib_init(){
    PinSetOutput(_PE);
    PinSetOutput(_TE_DATA);
    PinSetOutput(_TE_CTRL);
    PinSetOutput(_DC);
    PinSetValue(_PE);
    PinSetValue(_TE_DATA);
    PinClearValue(_TE_CTRL);
    PinClearValue(_DC);
}

int hal_gpib_is_signal_true(int pin)
{
    _spinmcr(pin, PinSetInput);
    switch(pin){ 
    case IFC:  pin = PinReadValue(_IFC); break; 
    case REN:  pin = PinReadValue(_REN); break; 
    case DAV:  pin = PinReadValue(_DAV); break; 
    case ATN:  pin = PinReadValue(_ATN); break; 
    case EOI:  pin = PinReadValue(_EOI); break; 
    case SRQ:  pin = PinReadValue(_SRQ); break; 
    case NRFD: pin = PinReadValue(_NRFD); break; 
    case NDAC: pin = PinReadValue(_NDAC); break;
    default:
        assert(0);
    }
    return pin;
}

void hal_gpib_set_signal_false(int pin)
{
    _spinmcr(pin, PinSetOutput);    
    _spinmcr(pin, PinSetValue);
}

void hal_gpib_set_signal_true(int pin)
{
    _spinmcr(pin, PinSetOutput);    
    _spinmcr(pin, PinClearValue);
}

void hal_gpib_put_data(char c)
{
    PortSetOutput(_DIO);
    PortSetValue(_DIO,c);
}

char hal_gpib_read_data(void)
{
    PortSetInput(_DIO);
    char val = PortReadValue(_DIO);
    return val;
}
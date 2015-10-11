#include "HardwareProfile.h"
#include <assert.h>
#include "hal_gpib.h"

#define _spinmcr(pin, func)do{ \
switch(pin){ \
        case IFC_PIN: func(_IFC); break; \
        case REN_PIN: func(_REN); break; \
        case DAV_PIN: func(_DAV); break; \
        case ATN_PIN: func(_ATN); break; \
        case EOI_PIN: func(_EOI); break; \
        case SRQ_PIN: func(_SRQ); break; \
        case NRFD_PIN: func(_NRFD); break; \
        case NDAC_PIN: func(_NDAC); break; \
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
    case IFC_PIN:  pin = PinReadValue(_IFC); break; 
    case REN_PIN:  pin = PinReadValue(_REN); break; 
    case DAV_PIN:  pin = PinReadValue(_DAV); break; 
    case ATN_PIN:  pin = PinReadValue(_ATN); break; 
    case EOI_PIN:  pin = PinReadValue(_EOI); break; 
    case SRQ_PIN:  pin = PinReadValue(_SRQ); break; 
    case NRFD_PIN: pin = PinReadValue(_NRFD); break; 
    case NDAC_PIN: pin = PinReadValue(_NDAC); break;
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
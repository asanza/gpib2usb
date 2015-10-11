#include "HardwareProfile.h"
#include <assert.h>
#include <diag.h>
#include "hal_gpib.h"

/* mask used to see if a pin belongs to 
 * control group or flow group. 
 * TE = Control. DC = Flow */

#define DC_75161 0x0F // ATN, SRQ, REN, IFC
#define TE_75161 0x70 // DAV, NDAC, NRFD

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
    DIAG("%x", pin);
    if( pin&TE_75161 ) PinSetValue(_TE_CTRL);
    else if(pin & DC_75161) PinSetValue(_DC);
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
    DIAG("%x, %x", pin, !pin);
    return !pin;
}

void hal_gpib_set_signal_false(int pin)
{
    if( pin&TE_75161 ) PinClearValue(_TE_CTRL);
    else if(pin & DC_75161) PinClearValue(_DC);
    _spinmcr(pin, PinSetOutput);    
    _spinmcr(pin, PinSetValue);
}

void hal_gpib_set_signal_true(int pin)
{
    if( pin&TE_75161 ) PinClearValue(_TE_CTRL);
    else if(pin & DC_75161) PinClearValue(_DC);
    _spinmcr(pin, PinSetOutput);    
    _spinmcr(pin, PinClearValue);
}

void hal_gpib_put_data(char c)
{
    PinSetValue(_TE_DATA);
    PinClearValue(_PE);
    PortSetOutput(_DIO);
    PortSetValue(_DIO,c);
}

char hal_gpib_read_data(void)
{
    PinClearValue(_TE_DATA);
    PinClearValue(_PE);
    PortSetInput(_DIO);
    char val = PortReadValue(_DIO);
    return val;
}
#include "HardwareProfile.h"
#include <assert.h>
#include <diag.h>
#include "hal_gpib.h"

typedef enum{
    CONTROLLER = 0x01,
            DEVICE = 0x02,
            TALKER = 0x04,
            LISTENER = 0x08
}driver_mode;

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

static void set_7516x_mode(driver_mode mode){
    DIAG("%d", mode);
    if(mode & CONTROLLER){
        PinClearValue(_DC);
        PinAsOutput(_REN);
        PinClearValue(_REN);
    }
    if(mode & DEVICE){
        PinAsInput(_REN);
        PinSetValue(_DC);
    }
    if(mode & LISTENER){
        PinClearValue(_TE_CTRL);
        PinClearValue(_TE_DATA);
    }
    if(mode & TALKER){
        PinSetValue(_TE_CTRL);
        PinSetValue(_TE_DATA);
    }
}

static void driver_switch_mode(int pin){
    if(pin & (ATN_PIN|REN_PIN|IFC_PIN)) set_7516x_mode(CONTROLLER);
    if(pin & (SRQ_PIN)) set_7516x_mode(DEVICE);
    if(pin & (DAV_PIN)) set_7516x_mode(TALKER);
    if(pin & (NRFD_PIN | NDAC_PIN)) set_7516x_mode(LISTENER);
}

void hal_gpib_init(){
    PinAsOutput(_PE);
    PinAsOutput(_TE_DATA);
    PinAsOutput(_TE_CTRL);
    PinAsOutput(_DC);
    PinSetValue(_PE);
    PinSetValue(_TE_DATA);
    PinClearValue(_TE_CTRL);
    PinClearValue(_DC);
}

int hal_gpib_is_signal_true(int pin)
{
    driver_switch_mode(pin);
    _spinmcr(pin, PinAsInput);
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
    DIAG("%d", !pin);
    return !pin;
}

void hal_gpib_set_signal_false(int pin)
{
    driver_switch_mode(pin);
    _spinmcr(pin, PinAsOutput);    
    _spinmcr(pin, PinSetValue);
}

void hal_gpib_set_signal_true(int pin)
{
    driver_switch_mode(pin);
    _spinmcr(pin, PinAsOutput);    
    _spinmcr(pin, PinClearValue);
}

void hal_gpib_put_data(char c)
{
    DIAG("0x%x",c);
    set_7516x_mode(TALKER);
    PinSetValue(_TE_DATA);
    PinClearValue(_PE);
    PortAsOutput(_DIO);
    PortSetValue(_DIO,c);
}

char hal_gpib_read_data(void)
{
    set_7516x_mode(LISTENER);
    PinClearValue(_TE_DATA);
    PinClearValue(_PE);
    PortAsInput(_DIO);
    char val = PortReadValue(_DIO);
    return val;
}
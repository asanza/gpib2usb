#include "HardwareProfile.h"
#include <assert.h>
#include <diag.h>
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

/* manage data transfer channels (te line in hardware driver)*/
void hal_gpib_set_driver_direction(hal_gpib_data_direction direction){
    DIAG("%d", direction);
    if(direction & LISTENER){
        /* disable talker in hardware controller.*/
        PinClearValue(_TE_CTRL);
        PinClearValue(_TE_DATA);
        /* set microcontroller direction lines */
        PinAsOutput(_NDAC);
        PinAsOutput(_NRFD);
        PinAsInput(_DAV);
    }
    else if(direction & TALKER){
        /* enable talker in hardware controller */
        PinSetValue(_TE_CTRL);
        PinSetValue(_TE_DATA);
        /* set microcontroller lines accordly */
        PinAsInput(_NDAC);
        PinAsInput(_NRFD);
        PinAsOutput(_DAV);
    }
}

/* manage bus management channels (dc line on hardware driver) */
void hal_gpib_set_driver_mode(hal_gpib_driver_mode mode){
    if(mode & CONTROLLER){
        PinClearValue(_DC);
        PinAsOutput(_REN);
        PinAsOutput(_ATN);
        PinAsOutput(_IFC);
        PinAsInput(_SRQ);
        PinClearValue(_REN);
    }else if(mode & DEVICE){
        PinSetValue(_DC);
        PinAsInput(_REN);
        PinAsInput(_ATN);
        PinAsInput(_IFC);
        PinAsOutput(_SRQ);
        PinSetValue(_REN);
    }
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
    return !pin;
}

void hal_gpib_set_signal_false(int pin)
{
    _spinmcr(pin, PinSetValue);
}

void hal_gpib_set_signal_true(int pin)
{
    _spinmcr(pin, PinClearValue);
}

void hal_gpib_put_data(char c)
{
    PinSetValue(_TE_DATA);
    PinClearValue(_PE);
    PortAsOutput(_DIO);
    PortSetValue(_DIO,~c);
}

char hal_gpib_read_data(void)
{
    PinClearValue(_TE_DATA);
    PinClearValue(_PE);
    PortAsInput(_DIO);
    char val = PortReadValue(_DIO);
    return ~val;
}
#include "HardwareProfile.h"
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
        case TE: func(_TE); break; \
        case DC: func(_DC); break; \
        case PE: func(_PE); break; \
}}while(0);

int hal_gpib_read_pin(int pin){
   _spinmcr(pin, PortReadPin);
   return pin;
}

void hal_gpib_set_pin(int pin){
   _spinmcr(pin, PortSetPin);    
}

void hal_gpib_clear_pin(int pin){
   _spinmcr(pin, PortClearPin);        
}

void hal_gpib_put_data(char c){
    _DIO = c;
}

char hal_gpib_read_data(void){
    return _DIO;
}
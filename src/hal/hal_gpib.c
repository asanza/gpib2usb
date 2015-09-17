#include "HardwareProfile.h"
#include "hal_gpib.h"



static void send_uniline(gpib_command command){
    switch(command){
        case ATN:
        case IFC:
        case SRQ:
        case REN:
        case EOI:
            break;
    }
}

static void send_multiline(gpib_command command, int address, char data){
    
}



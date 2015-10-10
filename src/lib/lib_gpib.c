#include "hal/hal_gpib.h"

static char myAddress = 0xFF;

int GPIB_Init(int our_address){
    if(myAddress != 0xFF)
        return -1; // already initialized
    myAddress = our_address + 0x20;
    /* initialize hardware stuff */
}

int GPIB_gpiSend(int listen, char what){
    hal_gpib_set_pin(DAV);
    if( hal_gpib_read_pin(NRFD)|| hal_gpib_read_pin(NDAC))
        return -1;
    hal_gpib_put_data(what);
    while(hal_gpib_read_pin(NRFD));
    hal_gpib_clear_pin(DAV);
    while(!hal_gpib_read_pin(NDAC));
    hal_gpib_set_pin(DAV);
}

int GPIB_PutStr(int listen, char *string, int count){
    
}

int GPIB_Stat(void){
    
}

int GPIB_Get(int listen){
    
}

int GPIB_GetStr(int listen, char*buf){
    
}

int GPIB_SerPoll(int listen){
    
}

int GPIB_PutAdd(char what){
    
}

int GPIB_PutData(char what){
    
}

int GPIB_GetData(void){
    
}
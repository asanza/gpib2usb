#include "system.h"
#include "gpib/gpib.h"

static int addr;

#define WRITE 1
#define READ  2
#define NONE  0

#define BUFFER_SIZE 255

static int mode = NONE;
static char buffer[BUFFER_SIZE];
static int bindex = 0;
static int bsize = 0;

static const int start_write_cmd[] = {
	UNL, LAD, MTA
};

static const int end_cmd[] = {
	UNT, UNL
};

static const int start_read_cmd[] = {
	UNL, TAD, MLA
};


int sys_tasks(void){
	return GPIB_Tasks();
}

int sys_get_data(void){
	return GPIB_Get();
}

void sys_listen(void){
	GPIB_Receive();
}

int sys_start_write_gpib(void){
    int err = GPIB_Send(UNL,1);
//    if(err) return SYSERR_WRITE_ERROR;
//    err = GPIB_Send(LAD, sysaddr);
//    if(err) return SYSERR_WRITE_ERROR;
//    err = GPIB_Send(MTA,1);
//    if(err) return SYSERR_WRITE_ERROR;

}

int sys_stop_write_gpib(void){
//    err = GPIB_Send(UNT, sysaddr);
//    if(err) return SYSERR_WRITE_ERROR;
//    err = GPIB_Send(UNL, sysaddr);
//    if(err) return SYSERR_WRITE_ERROR;
//    return SYSERR_NONE;	
}

int sys_write_gpib(char* data, size_t len){
	 // if buffer not empty return.
//    size --;
//    while(size--){
//        err = GPIB_Send(DAB, *buffer++);
//        if(err) return SYSERR_WRITE_ERROR;
//    }
}

int sys_set_address(uint8_t address, uint8_t subaddress){
	if(address > 32  || subaddress > 255 ) return -1;
	addr = address;
	return 0;
}

int sys_get_address(void){
	return addr;
}
#include "system.h"
#include "gpib/gpib.h"
#include <assert.h>

static int addr;

int sys_set_address(uint8_t address, uint8_t subaddress){
	if(address > 32  || subaddress > 255 ) return -1;
	addr = address;
	return 0;
}

int sys_get_address(void){
	return addr;
}

int sys_read_gpib(char** data){

}

int sys_write_gpib(char* data, int size){

}

int sys_tasks(void){
	
}
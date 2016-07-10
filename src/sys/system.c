#include "system.h"

static int addr;

int sys_tasks(void){

}

int sys_get_data(void){

}

int sys_listen(void){

}

int sys_write_gpib(char* data, size_t len){

}

int sys_set_address(uint8_t address, uint8_t subaddress){
	if(address > 32  || subaddress > 255 ) return -1;
	addr = address;
	return 0;
}

int sys_get_address(void){
	return addr;
}
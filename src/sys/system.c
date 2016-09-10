#include "system.h"
#include "gpib/gpib.h"
#include "hal/hal_sys.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

static int addr;
/* internal gpib buffer for send and receive operations */
#define GPIB_BUFFER_SIZE 256
static char gpib_buffer[GPIB_BUFFER_SIZE];
static int bsz = 0;
static int bsent = 0;
typedef enum{
	SENDING,
	RECEIVING,
	IDLE
} sys_state;

static sys_state state = IDLE;
static int do_sending(void);
static int do_receiving(void);

int timer_counter = 0;
#define TIMER_COUNTER_OVERFLOW 1000

int sys_set_address(uint8_t address, uint8_t subaddress){
	if(address > 32  || subaddress > 255 ) return -1;
	addr = address;
	return 0;
}

int sys_get_address(void){
	return addr;
}

int sys_read_gpib(char** data){
	*data = gpib_buffer;
	return bsz;
}

void sys_start_read(void){
	state = RECEIVING;
	bsz = 0;
}

int sys_write_gpib(char* data, int size){
	if (size > GPIB_BUFFER_SIZE) return -1;
	memcpy(gpib_buffer, data, size);
	bsz = size;
	bsent = 0;
	state = SENDING;
	return 0;
}

int sys_tasks(void){
	GPIB_Event evt = GPIB_Tasks();
	switch (state) {
		case SENDING:
			if(GPIB_State() == GPIB_IDLE)
				if(do_sending())
					return -1;
		break;
		case RECEIVING:
			if(GPIB_State() == GPIB_IDLE)
				if(do_receiving())
					return -1;
		break;
		case IDLE:
			// toggle green led
			if(timer_counter++ > TIMER_COUNTER_OVERFLOW){
				hal_sys_yellow_led_toggle();
				timer_counter = 0;
			}
		break;
	}
	return 0;
}

static int do_receiving(void){
	static int index = 0;
	int retval = 0;
	switch(index){
		case 0: retval = GPIB_Send(UNL, 1); index++; break;
		case 1: retval = GPIB_Send(TAD, addr); index++; break;
		case 2: retval = GPIB_Send(MLA, 1); index++; break;
		//case 3: retval = GPIB_Receive(&gpib_bufer[bsz++]);
		//	if ( ( bsz == GPIB_BUFFER_SIZE || gpib_buffer[bsz - 1] == '\n' )
		//				&& !retval){
		//		bsent = 0;
		//		index++;
		//		state = IDLE;
		//	}
		//	break;
		case 4: retval = GPIB_Send(UNT, 1); index++;
		case 5: retval = GPIB_Send(UNL, 1); index = 0;
		default: index = 0;
	}
	if(retval){
			sprintf(gpib_buffer, "Reception error");
			state = IDLE;
			index = 0;
	}
}

static int do_sending(void){
	static int index = 0;
	int retval = 0;
	switch(index){
		case 0: retval = GPIB_Send(UNL, 1); index++; break;
		case 1: retval = GPIB_Send(LAD, addr); index++; break;
		case 2: retval = GPIB_Send(MTA, 1); index++; break;
		case 3: retval = GPIB_Send(DAB, gpib_buffer[bsent++]);
			if (bsent == bsz && !retval){
				bsent = 0; bsz = 0;
				index++;
				state = IDLE;
			}
			break;
		case 4: retval = GPIB_Send(UNT, addr); index++;
		case 5: retval = GPIB_Send(UNL, addr); index = 0;
		default: index = 0;
	}
	if(retval){
			sprintf(gpib_buffer, "Transmission error");
			state = IDLE;
			index = 0;
	}
}

#ifndef system_H
#define system_H

#include <stdlib.h>
#include <stdint.h>

typedef enum{
	SYSEVT_IDLE,		// system is idle. Wait for new data
	SYSEVT_DATA_RECEIVED, // new data received from gpib bus
	SYSEVT_NO_DEVICE_ATTACHED,
	SYSEVT_BUFFER_NOT_EMPTY
}system_event_t;

/**
 * @brief perform periodic system tasks.
 * return SYSEVT_IDLE if system idle.
 * 				SYSEVT_DATA_RECEIVED if data received
 */
system_event_t sys_tasks(void);

/**
 * @brief   get a pointer of the internal gpib buffer.
 * @param[in] data variable where to copy the pointer.
 *
 * @return  length of the buffer
 */
int sys_get_gpib_buffer(char** data);

/* start a gpib read */
void sys_start_read(void);

system_event_t sys_write_gpib(char* data, int size);

/**
 * @brief      Set system address.
 *
 * @param[in]  address  The address
 * @param[in]  subaddress, optional subaddress or zero if not subaddress.
 *
 * @return     0 if successfull, -1 if address is not in range.
 */
int sys_set_address(uint8_t address, uint8_t subaddress);

int sys_get_address(void);

#endif // system_H

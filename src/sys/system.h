#ifndef system_H
#define system_H

#include <stdlib.h>
#include <stdint.h>

typedef enum{
	SENDING,
	RECEIVING,
	IDLE
}sys_state;

sys_state sys_get_state(void);

/**
 * @brief perform periodic system tasks.
 * return 1 if new data arrived by gpib interface
 *        0 if nothing happened.
 */
int sys_tasks(void);

/**
 * @brief   get a pointer of the internal gpib buffer.
 * @param[in] data variable where to copy the pointer.
 *
 * @return  length of the buffer
 */
int sys_get_gpib_buffer(char** data);

/* start a gpib read */
void sys_start_read(void);

int sys_write_gpib(char* data, int size);

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

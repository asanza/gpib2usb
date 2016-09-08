#ifndef system_H
#define system_H

#include <stdlib.h>
#include <stdint.h>

int sys_tasks(void);
int sys_get_data(void);
int sys_write_gpib(char* data, size_t size);
void sys_listen(void);
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

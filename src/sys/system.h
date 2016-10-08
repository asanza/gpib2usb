#ifndef system_H
#define system_H

typedef enum{
	SYS_ERR_NONE,
	SYS_ERR_COMMAND_UNKNOWN,
}sys_error_t;

int sys_process_input(char* str, int len);

#endif // system_H

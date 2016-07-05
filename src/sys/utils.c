#include "utils.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

int str2uint(char* str){
	char* t = str;
	while(*str){
		if(!isdigit(*str)){
			if(*str != ' ' && *str != '\r' && *str != '\n'
				&& *str != '\t'){
				errno = EDOM;
				return 0;
			}
		}
		str++;		
	}
	int val = strtol(t, NULL, 10);
	return val;
}
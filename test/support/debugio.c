#include "debugio.h"
#include "stdio.h"
/* This port correponds to the "-W 0x20,-" command line option. */
#define special_output_port (*((volatile char *)0x20))

/* This port correponds to the "-R 0x22,-" command line option. */
#define special_input_port  (*((volatile char *)0x22))

void _putchar(char c){
  special_output_port = c;
}

FILE _output = FDEV_SETUP_STREAM(_putchar, NULL, _FDEV_SETUP_WRITE);

void debugio_init(void){
  stdout = &_output;
}

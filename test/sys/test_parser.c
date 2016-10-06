#include "unity.h"
#include "parser.h"
#include "string.h"


#include <xc.h>
#include <p18f4550.h>

// disable watchdog
#pragma WDT=OFF

void putch(char data)
{
    while( ! TXIF)
        continue;
    TXREG = data;
}

void init_uart(void)
{
    SPBRG = 0x19;           // 9600 baud @ 4 MHz
    TXEN = 1;               // enable transmitter
    BRGH = 1;               // select high baud rate
    SPEN = 1;               // enable serial port
    CREN = 1;               // enable continuous operation
}

void setUp(void)
{
	init_uart();
}

void tearDown(void)
{
}

#define BUFFSIZE 200
void test_input_data(void)
{
  char buf[BUFFSIZE] = "ATN 1";
  char* exp = "1";
  GPIB_Command cmd;
  cmd = parse_input(buf);
  TEST_ASSERT_EQUAL_INT(ATN, cmd);
  TEST_ASSERT_EQUAL_MEMORY(exp, buf, 1);
}

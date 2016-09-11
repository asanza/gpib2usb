#include "unity.h"
#include "system.h"
#include <string.h>
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

void test_sys_write_gpib(void)
{
  char* buf[20] = "Hello World!";
  char* outbuf;
  int sz = strlen(buf);
  int retval = sys_write_gpib(buf, 10000);
  TEST_ASSERT_EQUAL(-1, retval);
  retval = sys_write_gpib(buf, sz);
  TEST_ASSERT_EQUAL(0, retval);
  retval = sys_get_gpib_buffer(&outbuf);
  TEST_ASSERT_EQUAL(sz, retval);
  TEST_ASSERT_EQUAL_MEMORY(buf, outbuf, sz);
}

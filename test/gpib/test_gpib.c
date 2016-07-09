#include "unity.h"
#include "gpib.h"

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

void test_module_generator_needs_to_be_implemented(void)
{
	TEST_IGNORE_MESSAGE("Implement me!");
}

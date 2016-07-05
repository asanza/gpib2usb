#include "unity.h"
#include "utils.h"

#include <string.h>
#include <errno.h>

#include <xc.h>
#include <p18f4550.h>


void putch(char data)
{
    while( ! TXIF)
        continue;
    TXREG = data;
    while(!TXIF);
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

void test_number2string(void)
{
	char str[] = {"12\r\n"};
	int  val = str2uint(str);
	TEST_ASSERT_EQUAL(12, val);
	TEST_ASSERT_EQUAL(0, errno);
}


void test_notnumber2string(void)
{
	char str[] = {"31adf12\r\n"};
	errno = 0;
	int  val = str2uint(str);
	TEST_ASSERT_EQUAL(0, val);
	TEST_ASSERT_EQUAL(EDOM, errno);	
}

void test_ignore_whitespaces(void){
	char str[] = {"		 31123\r\n"};
	errno = 0;
	int  val = str2uint(str);
	TEST_ASSERT_EQUAL(31123, val);
	TEST_ASSERT_EQUAL(0, errno);		
}
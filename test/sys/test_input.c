#include "unity.h"
#include "input.h"
#include "system.h"
#include "parser.h"
#include "utils.h"
#include <string.h>

#include <xc.h>
#include <p18f4550.h>


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

void test_read_line(void)
{
	char* T1 = "assdaf123jlafs\n";
	int len = read_line(T1, strlen(T1));
	char* buffer;
	TEST_ASSERT_EQUAL(1, len);
	TEST_ASSERT_EQUAL(strlen(T1), get_input_buffer(&buffer));
	TEST_ASSERT_EQUAL_MEMORY(T1, buffer, strlen(T1));
}

void test_read_line_cr(void)
{
	char* T1 = "assdaf123jlafs\r";
	int len = read_line(T1, strlen(T1));
	char* buffer;
	TEST_ASSERT_EQUAL(1, len);
	TEST_ASSERT_EQUAL(strlen(T1), get_input_buffer(&buffer));
	TEST_ASSERT_EQUAL_MEMORY(T1, buffer, strlen(T1));
}


void test_read_line_esc(void)
{
	char* T1 = "assdaf123jlafs\x1B\n\n";
	int len = read_line(T1, strlen(T1));
	char* buffer;
	TEST_ASSERT_EQUAL(1, len);
	TEST_ASSERT_EQUAL(strlen(T1), get_input_buffer(&buffer));
	TEST_ASSERT_EQUAL_MEMORY(T1, buffer, strlen(T1));
}


void test_read_line_esc2(void)
{
	char* T1 = "\x1B\n\x1B\n\x1B\n\x1B\n\r";
	int len = read_line(T1, strlen(T1));
	char* buffer;
	TEST_ASSERT_EQUAL(1, len);
	TEST_ASSERT_EQUAL(strlen(T1), get_input_buffer(&buffer));
	TEST_ASSERT_EQUAL_MEMORY(T1, buffer, strlen(T1));
}

void test_accumulation(void){
	char* T1 = "\x1B\n\x1B\n\x1B\n\x1B\n";
	char* T2 = "HELLO\n";
	int len = read_line(T1, strlen(T1));
	TEST_ASSERT_EQUAL(0, len);
	len = read_line(T2, strlen(T2));
	char* buffer;
	TEST_ASSERT_EQUAL(1, len);
	TEST_ASSERT_EQUAL(strlen(T1) + strlen(T2), get_input_buffer(&buffer));
	TEST_ASSERT_EQUAL_MEMORY(T1, buffer, strlen(T1));
	TEST_ASSERT_EQUAL_MEMORY(T2, buffer + strlen(T1), strlen(T2));
}

void test_parse_command_write(void){
  char inbuf*;
  char *outbuf;
  int sz = strlen(inbuff);
  sz = process_input(&inbuff);
  TEST_ASSERT_EQUAL(0, sz);
  sz = sys_get_gpib_buffer(&outbuf);
  TEST_ASSERT_EQUAL(strlen(inbuff), sz);
  TEST_ASSERT_EQUAL_MEMORY(inbuff, outbuf, sz);
}

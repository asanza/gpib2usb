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
  char buf[BUFFSIZE] = "Hello23\0\x1B\n\x1B\n";
  char* exp = "Hello23\0\n\n";
  devcmd cmd;
  int recv = parse_input(&cmd, buf, 12);
  TEST_ASSERT_EQUAL_INT(10, recv);
  TEST_ASSERT_EQUAL_INT(CMD_COUNT, cmd);
  TEST_ASSERT_EQUAL_MEMORY(exp, buf, 10);
}

void test_input_addr(void){
  char buff[BUFFSIZE];
  char* command = "++addr\n";
  devcmd cmd;
  memcpy(buff, command, strlen(command));
  int recv = parse_input(&cmd, buff, strlen(command));
  TEST_ASSERT_EQUAL(1, recv);
  TEST_ASSERT_EQUAL(CMD_ADDR, cmd);
  TEST_ASSERT_EQUAL_MEMORY(command+6,buff,1);
}

void test_input_addr_cmd(void){
  char buff[BUFFSIZE];
  char* command = "++addr 32\n";
  devcmd cmd;
  memcpy(buff, command, strlen(command));
  int recv = parse_input(&cmd, buff, strlen(command));
  TEST_ASSERT_EQUAL(3, recv);
  TEST_ASSERT_EQUAL(CMD_ADDR, cmd);
  TEST_ASSERT_EQUAL_MEMORY(command + 7, buff, 3);
}

void test_input_addr_cmd_2(void){
	char buff[BUFFSIZE];
  char* command = "++addr  32\n";
  devcmd cmd;
  memcpy(buff, command, strlen(command));
  int recv = parse_input(&cmd, buff, strlen(command));
  TEST_ASSERT_EQUAL(3, recv);
  TEST_ASSERT_EQUAL(CMD_ADDR, cmd);
  TEST_ASSERT_EQUAL_MEMORY(command + 8, buff, 3);
}

void test_input_addr_cmd_3(void){
	char buff[BUFFSIZE];
  char* command = "++addr	 	 	32\n";
  devcmd cmd;
  memcpy(buff, command, strlen(command));
  int recv = parse_input(&cmd, buff, strlen(command));
  TEST_ASSERT_EQUAL(3, recv);
  TEST_ASSERT_EQUAL(CMD_ADDR, cmd);
  TEST_ASSERT_EQUAL_MEMORY(command + 11, buff, 3);
}

void test_input_data2(void){
	char buff[BUFFSIZE];
  char* command = "\x1b+IDN?\n";
  devcmd cmd;
  memcpy(buff, command, strlen(command));
  int recv = parse_input(&cmd, buff, strlen(command));
  TEST_ASSERT_EQUAL(6, recv);
  TEST_ASSERT_EQUAL(CMD_COUNT, cmd);
  TEST_ASSERT_EQUAL_MEMORY(command + 1, buff, 6);
}

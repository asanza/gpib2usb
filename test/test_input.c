#include "unity.h"
#include "input.h"
#include "string.h"


void setUp(void)
{
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
  TEST_ASSERT_EQUAL(4, recv);
  TEST_ASSERT_EQUAL(CMD_ADDR, cmd);
  TEST_ASSERT_EQUAL_MEMORY(command + 6, buff, 4);
}

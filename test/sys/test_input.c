#include "unity.h"
#include "input.h"
#include "mock_system.h"
#include "support_uart.h"

void setUp(void)
{
	support_init_uart();
}

void tearDown(void)
{
}

extern char inbuff[];

void test_sys_on_usb_data_received(void)
{
	int ret = 0;
	char testin[200] = {"HELLO WORLD\x1B\n\n"};
	sys_process_input_ExpectAndReturn(inbuff, 12, SYS_ERR_NONE);
	ret = sys_on_usb_data_received(testin, 14);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL_MEMORY("HELLO WORLD\n", inbuff, 12);
}

void test_sys_on_usb_command_received(void){
	int ret = 0;
	char testin[200] = {"HE+LO WORLD\x1B\n\n"};
	sys_process_command_ExpectAndReturn(inbuff, 12, SYS_ERR_NONE);
	ret = sys_on_usb_data_received(testin, 14);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL_MEMORY("HE+LO WORLD\n", inbuff, 12);
}

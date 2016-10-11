#include "unity.h"
#include "sysio.h"
#include "mock_hal_sys.h"
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
	ret = sysio_data_received(testin, 14);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL_MEMORY("HELLO WORLD\n", inbuff, 12);
	hal_sys_enter_critical_Ignore();
	hal_sys_exit_critical_Ignore();
	TEST_ASSERT_EQUAL(SYSIO_DATA_AVAILABLE, sysio_get_state());
	ret = sysio_data_received(testin, 14);
}

void test_sys_on_usb_command_received(void){
	int ret = 0;
	char testin[200] = {"HE+LO WORLD\x1B\n\n"};
	hal_sys_enter_critical_Ignore();
	hal_sys_exit_critical_Ignore();
	sysio_release();
	ret = sysio_data_received(testin, 14);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL_MEMORY("HE+LO WORLD\n", inbuff, 12);
	TEST_ASSERT_EQUAL(SYSIO_CMD_AVAILABLE, sysio_get_state());
}

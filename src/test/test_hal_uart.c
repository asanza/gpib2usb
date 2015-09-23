#include "unity.h"
#include "hal_uart.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_module_generator_needs_to_be_implemented(void)
{
	int a = hal_uart_init();
	TEST_ASSERT_EQUAL(1,a);
}

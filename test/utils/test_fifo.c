#include "unity.h"
#include "fifo.h"
#include "support_uart.h"

void setUp(void)
{
	support_init_uart();
}

void tearDown(void)
{
}

void test_module_generator_needs_to_be_implemented(void)
{
	TEST_IGNORE_MESSAGE("Implement me!");
}

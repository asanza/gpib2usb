#include "unity.h"

#include "support_uart.h"
#include "gpib_listen.h"

void setUp(void)
{
	support_init_uart();
}

void tearDown(void)
{
}

void test_gpib_listen(void)
{
	TEST_IGNORE_MESSAGE("Implement me!");
}

#include "unity.h"
#include "gpib_talk.h"
#include "support_uart.h"
#include "mock_hal_gpib.h"

#define TRUE 1
#define FALSE 0

void setUp(void)
{
	support_init_uart();
}

void tearDown(void)
{
}

void test_gpib_talk_device_not_present(void)
{
	char tdat = 'a';
	gpib_talk_error_t err;
	TEST_ASSERT_EQUAL(GPIB_TALK_IDLE, gpib_talk_state());
	hal_gpib_set_signal_false_Expect(DAV_PIN);
	hal_gpib_is_signal_true_ExpectAndReturn(NDAC_PIN, FALSE);
	hal_gpib_is_signal_true_ExpectAndReturn(NRFD_PIN, FALSE);
	err = gpib_talk(tdat);
	TEST_ASSERT_EQUAL(GPIB_TALK_ERR_DEVICE_NOT_PRESENT, err);
	TEST_ASSERT_EQUAL(GPIB_TALK_IDLE, gpib_talk_state());
}

void test_gpib_talk_device_present_ndac_true(void){
	char tdat = 'a';
	gpib_talk_error_t err;
	TEST_ASSERT_EQUAL(GPIB_TALK_IDLE, gpib_talk_state());
	hal_gpib_set_signal_false_Expect(DAV_PIN);
	hal_gpib_is_signal_true_ExpectAndReturn(NDAC_PIN, TRUE);
	hal_gpib_put_data_Expect(tdat);
	err = gpib_talk(tdat);
	TEST_ASSERT_EQUAL(GPIB_TALK_ERR_NONE, err);
	TEST_ASSERT_EQUAL(GPIB_TALK_WAIT_NRFD, gpib_talk_state());
}

void test_gpib_talk_device_present_nrfd_true(void){
	char tdat = 'a';
	gpib_talk_error_t err;
	hal_gpib_set_signal_false_Expect(DAV_PIN);
	gpib_talk_reset();
	TEST_ASSERT_EQUAL(GPIB_TALK_IDLE, gpib_talk_state());
	hal_gpib_set_signal_false_Expect(DAV_PIN);
	hal_gpib_is_signal_true_ExpectAndReturn(NDAC_PIN, FALSE);
	hal_gpib_is_signal_true_ExpectAndReturn(NRFD_PIN, TRUE);
	hal_gpib_put_data_Expect(tdat);
	err = gpib_talk(tdat);
	TEST_ASSERT_EQUAL(GPIB_TALK_ERR_NONE, err);
	TEST_ASSERT_EQUAL(GPIB_TALK_WAIT_NRFD, gpib_talk_state());
}

void test_gpib_talk_wait_for_nrfd(void){
	gpib_talk_error_t err;
	/* set on previous test */
	TEST_ASSERT_EQUAL(GPIB_TALK_WAIT_NRFD, gpib_talk_state());
	hal_gpib_is_signal_true_ExpectAndReturn(NRFD_PIN, TRUE);
	err = gpib_talk_tasks();
	TEST_ASSERT_EQUAL(GPIB_TALK_ERR_NONE, err);
	TEST_ASSERT_EQUAL(GPIB_TALK_WAIT_NRFD, gpib_talk_state());
	/* nrfd true */
	hal_gpib_is_signal_true_ExpectAndReturn(NRFD_PIN, FALSE);
	hal_gpib_set_signal_true_Expect(DAV_PIN);
	err = gpib_talk_tasks();
	TEST_ASSERT_EQUAL(GPIB_TALK_ERR_NONE, err);
	TEST_ASSERT_EQUAL(GPIB_TALK_WAIT_NDAC, gpib_talk_state());
}

void test_gpib_talk_wait_for_ndac(void){
	gpib_talk_error_t err;
	/* set on previous test */
	TEST_ASSERT_EQUAL(GPIB_TALK_WAIT_NDAC, gpib_talk_state());
	hal_gpib_is_signal_true_ExpectAndReturn(NDAC_PIN, TRUE);
	err = gpib_talk_tasks();
	TEST_ASSERT_EQUAL(GPIB_TALK_ERR_NONE, err);
	TEST_ASSERT_EQUAL(GPIB_TALK_WAIT_NDAC, gpib_talk_state());
	/* ndac false */
	hal_gpib_is_signal_true_ExpectAndReturn(NDAC_PIN, FALSE);
	hal_gpib_set_signal_false_Expect(DAV_PIN);
	err = gpib_talk_tasks();
	TEST_ASSERT_EQUAL(GPIB_TALK_ERR_NONE, err);
	TEST_ASSERT_EQUAL(GPIB_TALK_IDLE, gpib_talk_state());
}

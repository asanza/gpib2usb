#include "unity.h"
#include "gpib.h"

#include "mock_hal_gpib.h"
#include "mock_gpib_listen.h"
#include "mock_gpib_talk.h"

#include <xc.h>
#include <p18f4550.h>

// disable watchdog
#pragma WDT=OFF

#define TRUE 1
#define FALSE 0

void putch(char data)
{
    TXREG = data;
    while( ! TXIF);
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

void test_gpib_receive(void){
	GPIB_Event evt;
	gpib_listen_IgnoreAndReturn(GPIB_LISTEN_ERR_NONE);
	evt = GPIB_Receive();
	TEST_ASSERT_EQUAL(GPIB_EVT_NONE, evt);
	TEST_ASSERT_EQUAL(GPIB_LISTEN, GPIB_State());
	gpib_listen_tasks_IgnoreAndReturn(GPIB_EVT_NONE);
	gpib_listen_state_IgnoreAndReturn(GPIB_LISTEN_IDLE);
	GPIB_Tasks();
	TEST_ASSERT_EQUAL(GPIB_IDLE, GPIB_State());
}

void test_gpib_state_machine_send_command(void)
{
	GPIB_Event evt;
	TEST_ASSERT_EQUAL(GPIB_IDLE, GPIB_State());
	hal_gpib_set_signal_true_Expect(ATN_PIN);
	gpib_talk_ExpectAndReturn(UNL_CODE, GPIB_TALK_ERR_NONE);
	evt = GPIB_Send(UNL, 1);
	TEST_ASSERT_EQUAL(GPIB_EVT_NONE, evt);
	TEST_ASSERT_EQUAL(GPIB_TALK, GPIB_State());
	gpib_talk_tasks_IgnoreAndReturn(GPIB_EVT_NONE);
	gpib_talk_state_IgnoreAndReturn(GPIB_TALK_WAIT_NRFD);
	TEST_ASSERT_EQUAL(GPIB_EVT_NONE, GPIB_Tasks());
	TEST_ASSERT_EQUAL(GPIB_TALK, GPIB_State());

	/* Done with talking. ready for next command */
	gpib_talk_tasks_IgnoreAndReturn(GPIB_EVT_NONE);
	gpib_talk_state_IgnoreAndReturn(GPIB_TALK_IDLE);
	TEST_ASSERT_EQUAL(GPIB_EVT_NONE, GPIB_Tasks());
	TEST_ASSERT_EQUAL(GPIB_IDLE, GPIB_State());
}

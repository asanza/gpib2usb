#include "unity.h"
#include "hal_gpib.h"


#include <xc.h>
#include <p18f4550.h>

#pragma WDT=OFF
#define _XTAL_FREQ 48000000

/* data port */
#define DIO_DIR TRISD
#define DIO_VAL LATD
#define PE_DIR TRISEbits.TRISE1
#define PE_VAL LATEbits.LATE1
#define TE_DIR TRISBbits.TRISB3
#define TE_VAL LATBbits.LATB3
/* bus management lines */
#define ATN_DIR TRISEbits.TRISE0
#define ATN_VAL LATEbits.LATE0
#define IFC_DIR TRISAbits.TRISA1
#define IFC_VAL LATAbits.LATA1
#define REN_DIR TRISAbits.TRISA0
#define REN_VAL LATAbits.LATA0
// #define _EOI A, BIT5
#define SRQ_DIR TRISBbits.TRISB0
#define SRQ_VAL LATBbits.LATB0
/* talker enable for control */
// #define _TE_CTRL B, BIT3
/* data direction control */
#define DC_DIR TRISBbits.TRISB4
#define DC_VAL LATBbits.LATB4

/* bus handshake lines */
// #define _DAV A, BIT4
// #define _NRFD A, BIT3
// #define _NDAC A, BIT2

#define OUT 0
#define IN  1

#define GPIB_FALSE  1
#define GPIB_TRUE   0

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
    // small delay to allow the printf function put all the buffer out.
    __delay_us(100);
}

void test_hal_gpib_init(void)
{
    hal_gpib_init();
    /* trisbits, 1 = input, 0 = output */
    TEST_ASSERT_EQUAL(OUT, PE_DIR); // PE
    TEST_ASSERT_EQUAL(OUT, TE_DIR); // TE_CTRL
    TEST_ASSERT_EQUAL(OUT, DC_DIR); // DC

    TEST_ASSERT_EQUAL(1, PE_VAL);
    TEST_ASSERT_EQUAL(0, TE_VAL);
    TEST_ASSERT_EQUAL(0, DC_VAL);
}

void test_hal_gpib_set_signal_(void)
{
    hal_gpib_set_signal_false(ATN_PIN);
    TEST_ASSERT_EQUAL(1, ATN_VAL);
    hal_gpib_set_signal_true(ATN_PIN);
    TEST_ASSERT_EQUAL(0, ATN_VAL);
}

void test_hal_gpib_set_driver_mode(void){
    hal_gpib_set_driver_mode(CONTROLLER);
    TEST_ASSERT_EQUAL(0, DC_VAL);
    TEST_ASSERT_EQUAL(OUT, REN_DIR);
    TEST_ASSERT_EQUAL(OUT, ATN_DIR);
    TEST_ASSERT_EQUAL(OUT, IFC_DIR);
    TEST_ASSERT_EQUAL(IN, SRQ_DIR);
    hal_gpib_set_driver_mode(DEVICE);
    TEST_ASSERT_EQUAL(1, DC_VAL);
    TEST_ASSERT_EQUAL(IN, REN_DIR);
    TEST_ASSERT_EQUAL(IN, ATN_DIR);
    TEST_ASSERT_EQUAL(IN, IFC_DIR);
    TEST_ASSERT_EQUAL(OUT, SRQ_DIR);
    TEST_ASSERT_EQUAL(1, REN_VAL);
}

void test_hal_gpib_set_signal(void){
  hal_gpib_set_signal_false(ATN_PIN);
  TEST_ASSERT_EQUAL(GPIB_FALSE, ATN_VAL);
  hal_gpib_set_signal_true(ATN_PIN);
  TEST_ASSERT_EQUAL(GPIB_TRUE, ATN_VAL);
}

void test_hal_gpib_put_data(void){
  char data = 'x';
  hal_gpib_put_data(data);
  TEST_ASSERT_EQUAL_UINT8(~data, DIO_VAL);
  TEST_ASSERT_EQUAL(0xFF, DIO_DIR);
  TEST_ASSERT_EQUAL(0, PE_VAL);
  TEST_ASSERT_EQUAL(1, TE_VAL);
}

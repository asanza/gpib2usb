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

void support_init_uart(void)
{
    SPBRG = 0x19;           // 9600 baud @ 4 MHz
    TXEN = 1;               // enable transmitter
    BRGH = 1;               // select high baud rate
    SPEN = 1;               // enable serial port
    CREN = 1;               // enable continuous operation
}

#include "hal/hal_gpib.h"
#include <diag.h>

static char myAddress = 0xFF;

int GPIB_Init(int our_address)
{
    if (myAddress != 0xFF)
        return -1; // already initialized
    myAddress = our_address + 0x20;
    /* initialize hardware stuff */
    return 0;
}

int GPIB_gpiSend(int listen, char what)
{
    DIAG("0x%x ", what);
    hal_gpib_set_pin(DAV);
    if (hal_gpib_read_pin(NRFD) || hal_gpib_read_pin(NDAC))
        return -1;
    hal_gpib_put_data(what);
    while (hal_gpib_read_pin(NRFD));
    hal_gpib_clear_pin(DAV);
    while (!hal_gpib_read_pin(NDAC));
    hal_gpib_set_pin(DAV);
    return 0;
}

int GPIB_PutStr(int listen, char *string, int count)
{
    return 0;
}

int GPIB_Stat(void)
{
    return 0;
}

int GPIB_Get(int listen)
{
    return 0;
}

int GPIB_GetStr(int listen, char*buf)
{
    return 0;
}

int GPIB_SerPoll(int listen)
{
    return 0;
}

int GPIB_PutAdd(char what)
{
    return 0;
}

int GPIB_PutData(char what)
{
    return 0;
}

int GPIB_GetData(void)
{
    return 0;
}
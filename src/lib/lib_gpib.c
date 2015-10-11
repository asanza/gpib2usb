#include "hal/hal_gpib.h"
#include "lib_gpib.h"
#include <diag.h>

static char myAddress = 0xFF;

/** Send GPIB Data
 * @param data
 * @param length
 * @param atn 1 if atn should be true, false otherwise.
 * @return -1 if error.
 */
static int _gpib_write(char* data, int length, int atn);

int GPIB_Init(int our_address)
{
    if (myAddress != 0xFF)
        return -1; // already initialized
    myAddress = our_address + 0x20;
    /* initialize hardware stuff */
    hal_gpib_init();
    hal_gpib_set_signal_false(ATN);
    hal_gpib_set_signal_false(IFC);
    hal_gpib_set_signal_false(SRQ);
    hal_gpib_set_signal_false(REN);
    hal_gpib_set_signal_false(EOI);
    hal_gpib_set_signal_false(DAV);
    hal_gpib_set_signal_true(NRFD);
    hal_gpib_set_signal_true(NDAC);
    return 0;
}

static int _gpib_write(char* data, int length, int atn){
    int i = 0;
    if(atn){
        hal_gpib_set_signal_true(ATN);
    }
    hal_gpib_set_signal_false(EOI);
    hal_gpib_set_signal_false(DAV);
    hal_gpib_set_signal_false(NRFD);
	for (i = 0; i < length; i++) {
        hal_gpib_set_signal_false(NDAC);
#ifdef WITH_TIMEOUT
		timeout = s + 5;
		//gpib_info();
		while ((PIND & _BV(G_NDAC)) && (s <= timeout)) {
			if (s == timeout) {
				uart_puts("\n\rError: NDAC timeout\n\r");
				//gpib_info();
				debugshell();
				return 0xff;
			}
		}
#else
        while(!hal_gpib_is_signal_true(NDAC));
#endif
		// put data on bus
		hal_gpib_put_data(data[i]);
		// wait until listeners release NRFD
		//uart_puts("1");
        hal_gpib_set_signal_false(NRFD);
#ifdef WITH_TIMEOUT
		//gpib_info();
		timeout = s + 5;
		while (!(PIND & _BV(G_NRFD)) && (s <= timeout)) {
			if (s == timeout) {
				uart_puts("\n\rError: NRFD timeout\n\r");
				//gpib_info();
				debugshell();
				return 0xff;
			}
		}
#else
        while(!hal_gpib_is_signal_true(NRFD));
#endif

		// assign EOI during transmission of only last byte
		if ((i == length - 1) && !atn) {
			//uart_puts("\n\rE\n\r");
            hal_gpib_set_signal_true(EOI);
		}

		// assign DAV, data valid for listeners
        hal_gpib_set_signal_true(DAV);

		// wait for NDAC release
		//uart_puts("2");
        hal_gpib_set_signal_false(NDAC);
        while(!hal_gpib_is_signal_true(NDAC));
		// release DAV, data not valid anymore
        hal_gpib_set_signal_false(DAV);
		//uart_puts("3\r\n");
	}

	if (atn) {
		// assign ATN for commands
		hal_gpib_set_signal_false(ATN);
	}

	return 0x00;
    
}

int GPIB_Cmd(int listen, char what)
{
    DIAG("0x%x ", what);
    hal_gpib_set_signal_true(ATN);
    return 0;
}

int GPIB_PutStr(int listen, char *string, int count)
{
    //_gpib_write(string, count, 0);
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
    hal_gpib_set_signal_false(DAV);
    if (hal_gpib_is_signal_true(NRFD) || hal_gpib_is_signal_true(NDAC))
        return -1;
    hal_gpib_put_data(what);
    while (hal_gpib_is_signal_true(NRFD));
    hal_gpib_set_signal_true(DAV);
    while (!hal_gpib_is_signal_true(NDAC));
    hal_gpib_set_signal_false(DAV);
    return 0;
}

int GPIB_GetData(void)
{
    return 0;
}

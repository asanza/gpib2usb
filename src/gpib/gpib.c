/*
 * gpib.c
 *
 * Copyright (c) 2015, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * Created on October 8, 2015, 10:08 PM
 */

 #include "hal/hal_gpib.h"
 #include "gpib.h"
 #include <assert.h>

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
     hal_gpib_set_signal_false(ATN_PIN);
     hal_gpib_set_signal_false(IFC_PIN);
     hal_gpib_set_signal_false(SRQ_PIN);
     hal_gpib_set_signal_false(REN_PIN);
     hal_gpib_set_signal_false(EOI_PIN);
     hal_gpib_set_signal_false(DAV_PIN);
     hal_gpib_set_signal_true(NRFD_PIN);
     hal_gpib_set_signal_true(NDAC_PIN);
     return 0;
 }

 static int _gpib_write(char* data, int length, int atn){
     int i = 0;
     if(atn){
         hal_gpib_set_signal_true(ATN_PIN);
     }
     hal_gpib_set_signal_false(EOI_PIN);
     hal_gpib_set_signal_false(DAV_PIN);
     hal_gpib_set_signal_false(NRFD_PIN);
 	for (i = 0; i < length; i++) {
         hal_gpib_set_signal_false(NDAC_PIN);
 #ifdef WITH_TIMEOUT
 		timeout = s + 5;
 		//gpib_info();
 		while ((PIND & _BV(G_NDAC_PIN)) && (s <= timeout)) {
 			if (s == timeout) {
 				uart_puts("\n\rError: NDAC_PIN timeout\n\r");
 				//gpib_info();
 				debugshell();
 				return 0xff;
 			}
 		}
 #else
         while(!hal_gpib_is_signal_true(NDAC_PIN));
 #endif
 		// put data on bus
 		hal_gpib_put_data(data[i]);
 		// wait until listeners release NRFD_PIN
 		//uart_puts("1");
         hal_gpib_set_signal_false(NRFD_PIN);
 #ifdef WITH_TIMEOUT
 		//gpib_info();
 		timeout = s + 5;
 		while (!(PIND & _BV(G_NRFD_PIN)) && (s <= timeout)) {
 			if (s == timeout) {
 				uart_puts("\n\rError: NRFD_PIN timeout\n\r");
 				//gpib_info();
 				debugshell();
 				return 0xff;
 			}
 		}
 #else
         while(!hal_gpib_is_signal_true(NRFD_PIN));
 #endif

 		// assign EOI during transmission of only last byte
 		if ((i == length - 1) && !atn) {
 			//uart_puts("\n\rE\n\r");
             hal_gpib_set_signal_true(EOI);
 		}

 		// assign DAV_PIN, data valid for listeners
         hal_gpib_set_signal_true(DAV_PIN);

 		// wait for NDAC_PIN release
 		//uart_puts("2");
         hal_gpib_set_signal_false(NDAC_PIN);
         while(!hal_gpib_is_signal_true(NDAC_PIN));
 		// release DAV_PIN, data not valid anymore
         hal_gpib_set_signal_false(DAV_PIN);
 		//uart_puts("3\r\n");
 	}

 	if (atn) {
 		// assign ATN_PIN_PIN for commands
 		hal_gpib_set_signal_false(ATN_PIN);
 	}

 	return 0x00;

 }

 int GPIB_Cmd(int listen, char what)
 {
     DIAG("0x%x ", what);
     hal_gpib_set_signal_true(ATN_PIN);
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
     hal_gpib_set_signal_false(DAV_PIN);
     if (hal_gpib_is_signal_true(NRFD_PIN) || hal_gpib_is_signal_true(NDAC_PIN))
         return -1;
     hal_gpib_put_data(what);
     while (hal_gpib_is_signal_true(NRFD_PIN));
     hal_gpib_set_signal_true(DAV_PIN);
     while (!hal_gpib_is_signal_true(NDAC_PIN));
     hal_gpib_set_signal_false(DAV_PIN);
     return 0;
 }

 int GPIB_GetData(void)
 {
     return 0;
 }

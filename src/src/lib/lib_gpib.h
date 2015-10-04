#ifndef lib_gpib_h
#define lib_gpib_h

    /* Initializes the GPIB driver with a given gpib address. 
     * returns -1 in case of error.
     */
    int GPIB_Init(int our_address);
    
    /* sends a single character to the gpib device addressed
     * by listen. returns -1 in case of error */
    int GPIB_Send(int listen, char what);
    
    /* sends a string of bytes to the gpib device addressed by listen. 
     * Returns -1 in case of error. */
    int GPIB_PutStr(int listen, char *string, int count);

    /* simply return the status of the GPIB status lines. These are 
     * encoded in the lower 8 bits of the return value as:
     * IFC REN EOI SRQ NDAC NRF ATN DAV
     */
    int GPIB_Stat(void);
    
    /* read a character from the GPIB device addressed by listen. 
     * Returns the character or -1 in case of error */
    int GPIB_Get(int listen);
    
    /* reads a string of data from the device addressed by listen. 
     * Returns the number of bytes read into buf or -1 if error. */
    int GPIB_GetStr(int listen, char*buf);
    
    /* Returns the serial poll on the device at listen. Returnss
     * the serial poll status in the lower 8 bits or -1 if error */
    int GPIB_SerPoll(int listen);
    
    /* puts value what out as an address byte. return -1 if error. */
    int GPIB_PutAdd(char what);
    
    /* puts what on the gpib bus as data. returns -1 if error. */
    int GPIB_PutData(char what);
    
    /* read the value on the gpib bus as data value and returns it or -1 in case of error. */
    int GPIB_GetData(void);

#endif

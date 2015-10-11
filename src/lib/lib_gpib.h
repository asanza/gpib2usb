#ifndef lib_gpib_h
#define lib_gpib_h

typedef enum {
    /* uniline */
    ATN,
    IFC,
    REN,
    SRQ,
    EOI,
    /* universal */
    DCL,
    LLO,
    _SPE,
    SPD,
    PPU,
    /* addressed */
    MLA,
    MTA,
    LAD,
    UNL,
    TAD,
    UNT,
    SAD,
    GTL,
    SDC,
    PPC,
    GET,
    TCT,
    PPE,
    PPD,
    DAB
} GPIB_Command;

/* Initializes the GPIB driver with a given gpib address. 
 * returns -1 in case of error.
 */
int GPIB_Init(int our_address);

int GPIB_Send(GPIB_Command cmd, char data);

#endif

#ifndef lib_gpib_h
#define lib_gpib_h

typedef enum {
    /*    GPIB_ATN,
        GPIB_IFC,
        GPIB_SRQ,  uniline messages. Implicit managed.
        GPIB_REN,
        GPIB_EOI, */
    GPIB_MLA,
    GPIB_MTA,
    GPIB_LAD,
    GPIB_UNL,
    GPIB_TAD,
    GPIB_UNT,
    GPIB_SAD,
    GPIB_LLO,
    GPIB_DCL,
    GPIB_PPU,
    GPIB_SPE,
    GPIB_SPD,
    GPIB_GTL,
    GPIB_SDC,
    GPIB_PPC,
    GPIB_GET,
    GPIB_TCT,
    GPIB_PPE,
    GPIB_PPD,
    GPIB_DAB
} gpib_message;

void gpib_send_command(gpib_message message, char data);


/********************************************/




#endif

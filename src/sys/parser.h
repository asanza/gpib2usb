#ifndef parser_H
#define parser_H

#include <stdlib.h>

    typedef enum {
        CMD_ADDR,
        CMD_AUTO,
        CMD_CLR,
        CMD_EOI,
        CMD_EOS,
        CMD_EOT_ENABLE,
        CMD_EOT_CHAR,
        CMD_IFC,
        CMD_LLO,
        CMD_LOC,
        CMD_LON,
        CMD_MODE,
        CMD_READ,
        CMD_READ_TMO_MS,
        CMD_RST,
        CMD_SAVE_CONFIG,
        CMD_RST_FACTORY,
        CMD_SPOLL,
        CMD_SRQ,
        CMD_STATUS,
        CMD_TRG,
        CMD_VER,
        CMD_HELP,
        CMD_COUNT
    } devcmd;

    /* Parse input string. Return pointer to processed string.
     * Input string contains scape characters. Return pointer do not contain
     * escape characters. */
    int parse_input(devcmd* cmd, char* input, int buffer_size);


    int parse_address(char* data, size_t size);


#endif // parser_H

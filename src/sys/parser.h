#ifndef parser_H
#define parser_H

#include <gpib/gpib.h>
#include <stdlib.h>

    /* Parse input string. Return pointer to processed string.
     * Input string contains scape characters. Return pointer do not contain
     * escape characters. */
    GPIB_Command parse_input(char* input_str);


#endif // parser_H

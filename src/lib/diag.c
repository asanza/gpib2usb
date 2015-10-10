#include "diag.h"
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

uint32_t gui32DebugFlags;			// runtime debug flags.

void diag_setflag(unsigned int flag)
{
    gui32DebugFlags |= flag;
}
void diag_resetflag(unsigned int  flag)
{
    gui32DebugFlags &= ~flag;
}
unsigned int  diag_getflag()
{
    return gui32DebugFlags;
}

void diag_printf(const char* file, const char* func, int line, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printf("%s: ", func);
    vprintf(fmt, ap);
    printf("\r\n");
    va_end(ap);
}

void diag_printf_nt(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}

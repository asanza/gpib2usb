#include <stdio.h>
#include <HardwareProfile.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib/lib_gpib.h"
#include "hal/hal_uart.h"
#include "hal/hal_sys.h"
#include "drivers/stdiodrv.h"
#include "input/input.h"
#include "sys/system.h"

#define BUFFER_SIZE 250
char inbuff[BUFFER_SIZE];
// Stdout definition. Used for printf.
static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

static int _isdigit(char* args);
static void do_print_syserror(syserr err);
static syserr do_address(char* args, int size);
static syserr do_read_gpib(char* args, int size);
static syserr do_write_gpib(char* args, int size);

int main(void)
{
    // Interrupts disabled at boot
    hal_sys_enter_critical();
    hal_sys_init();
    hal_uart_init(NULL);
    stdout = &uart_stdout;
    stdin = &uart_stdout;
    // Interrupts enable9R4d after configuration
    hal_sys_exit_critical();
    sys_init();
    devcmd cmd;
    syserr err;
    while (1) {
        do_write_gpib("Hello", 5);
/*        int recv = uart_fgets(inbuff, BUFFER_SIZE, stdin);
        int size = parse_input(&cmd, inbuff, recv);
        switch (cmd) {
        case CMD_ADDR:              err = do_address(inbuff, size);
            break;
        case CMD_AUTO:              printf("auto\n");
            break;
        case CMD_CLR:               printf("clr\n");
            break;
        case CMD_EOI:               printf("eoi\n");
            break;
        case CMD_EOS:               printf("eos\n");
            break;
        case CMD_EOT_ENABLE:        printf("enable\n");
            break;
        case CMD_EOT_CHAR:          printf("char\n");
            break;
        case CMD_IFC:               printf("ifc  \n");
            break;
        case CMD_LLO:               printf("llo \n");
            break;
        case CMD_LOC:               printf("loc \n");
            break;
        case CMD_LON:               printf("lon \n");
            break;
        case CMD_MODE:              printf("mode\n");
            break;
        case CMD_READ:              err = do_read_gpib(inbuff, size);
            break;
        case CMD_READ_TMO_MS:       printf("tmo\n");
            break;
        case CMD_RST:               printf("rst\n");
            break;
        case CMD_SAVE_CONFIG:       printf("config\n");
            break;
        case CMD_RST_FACTORY:       printf("factory\n");
            break;
        case CMD_SPOLL:             printf("spoll\n");
            break;
        case CMD_SRQ:               printf("srq\n");
            break;
        case CMD_STATUS:            printf("status\n");
            break;
        case CMD_TRG:               printf("trg\n");
            break;
        case CMD_VER:               printf("ver\n");
            break;
        case CMD_HELP:              printf("help\n");
            break;
        default:                    err = do_write_gpib(inbuff, size);
            break;
        }
        do_print_syserror(err);*/
    }
}

static void do_print_syserror(syserr err)
{
    switch (err) {
    case SYSERR_WRONG_PARAMETER: printf("Wrong parameter\n");
        break;
    case SYSERR_NOT_IMPLEMENTED: printf("Not Implemented\n");
        break;
    case SYSERR_WRITE_ERROR: printf("GPIB Write Error\n");
    default: break;
    }
}

static syserr do_address(char* args, int size)
{
    char* token = strtok(args, " ");
    if (!token) {
        printf("%d\n", sys_get_addr());
        return SYSERR_NONE;
    }
    if (!_isdigit(token)) return SYSERR_WRONG_PARAMETER;
    int addr = atoi(token);
    token = strtok(NULL, " ");
    if (!token) return sys_set_addr(addr);
    printf("set subaddr not yet implemented\n");
    return SYSERR_NOT_IMPLEMENTED;
}

static syserr do_read_gpib(char* args, int size)
{
    char* token = strtok(args, " ");
    if (!token) {
        sys_gpib_read(inbuff, BUFFER_SIZE, SYSREAD_UNTIL_TIMEOUT, 0);
        printf("%s", inbuff);
        return SYSERR_NONE;
    }
    if (!strcmp(token, "eoi")) {
        sys_gpib_read(inbuff, BUFFER_SIZE, SYSREAD_UNTIL_EOI, 0);
        printf("%s", inbuff);
        return SYSERR_NONE;
    } else {
        if (!_isdigit(token)) return SYSERR_WRONG_PARAMETER;
        int var = atoi(token);
        if (var > 255) return SYSERR_WRONG_PARAMETER;
        sys_gpib_read(inbuff, BUFFER_SIZE, SYSREAD_UNTIL_CHAR, var);
        printf("%s", inbuff);
        return SYSERR_NONE;
    }
}

static int _isdigit(char* args)
{
    while (*args) {
        if (!isdigit(*args++)) return 0;
    }
    return 1;
}

syserr do_write_gpib(char* args, int size)
{
    return sys_gpib_write(args, size);
}
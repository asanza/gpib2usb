/*
 * input.c
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

#include "input.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

struct command_t {
    devcmd command;
    const char* string;
};

static const struct command_t command_strings[] = {
    {CMD_ADDR, "++addr"},
    {CMD_AUTO, "++auto"},
    {CMD_CLR, "++clr"},
    {CMD_EOI, "++eoi"},
    {CMD_EOS, "++eos"},
    {CMD_EOT_ENABLE, "++eot_enable"},
    {CMD_EOT_CHAR, "++eot_char"},
    {CMD_IFC, "++ifc"},
    {CMD_LLO, "++llo"},
    {CMD_LOC, "++loc"},
    {CMD_LON, "++lon"},
    {CMD_MODE, "++mode"},
    {CMD_READ, "++read"},
    {CMD_READ_TMO_MS, "++read_tmo_ms"},
    {CMD_RST, "++rst"},
    {CMD_SAVE_CONFIG, "++save_cfg"},
    {CMD_RST_FACTORY, "++factory_reset"},
    {CMD_SPOLL, "++spoll"},
    {CMD_SRQ, "++srq"},
    {CMD_STATUS, "++status"},
    {CMD_TRG, "++trg"},
    {CMD_VER, "++ver"},
    {CMD_HELP, "++help"},
};
static int parse_command(devcmd* cmd, char* input, int size);
static int delchar(char* input, char val, int size);
static int starts_with(const char *pre, const char *str);

int parse_input(devcmd* cmd, char* input, int buffer_size) {
    assert(cmd);
    assert(input);
    *cmd = CMD_COUNT;
    if(!starts_with("++",input)) return delchar(input, ESC, buffer_size);
    return parse_command(cmd, input, buffer_size);
}

static int parse_command(devcmd* cmd, char* input, int size){
    if(*(input + strlen(input) - 1) == '\n'){
        if(*(input+strlen(input)-2)!=ESC)
                *(input + strlen(input) - 1) = 0x00;
    }
    char* p = strchr(input, ' ');
    if(p != NULL) *p = 0x00;
    int offset = 0;
    int i;
    for(i = 0; i < CMD_COUNT; i++ ){
        if(!strcmp(input,command_strings[i].string)){
            *cmd = command_strings[i].command;
            offset = strlen(command_strings[i].string);
            break;
        }
    }
    if(*cmd == CMD_COUNT) return delchar(input, ESC, size);
    return delchar(input+offset+1, ESC, offset+1);
}

static int delchar(char* input, char val, int size){
    char* p = input;
    char* q = input;
    int count = 0;
    while(--size){
        if(*++p == val){
            *++q = *++p;
        } else{
            *++q = *p;
	    count++;
        }
    }
    return count + 1;
}

static int starts_with(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

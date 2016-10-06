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

#include "parser.h"
#include "sysdefs.h"
#include "utils.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "gpib/gpib.h"

struct command_t {
	GPIB_Command command;
	const char* string;
};

static const struct command_t command_strings[] = {
	{ ATN,	"atn" },
	{ IFC,	"ifc" },
	{ REN,	"ren" },
	{ SRQ,	"srq" },
	{ EOI,	"eoi" },
	{ DCL,	"dlc" },
	{ LLO,	"llo" },
	{ _SPE, "spe" },
	{ SPD,	"spd" },
	{ PPU,	"ppu" },
	{ MLA,	"mla" },
	{ MTA,	"mta" },
	{ LAD,	"lad" },
	{ UNL,	"unl" },
	{ TAD,	"tad" },
	{ UNT,	"unt" },
	{ SAD,	"sad" },
	{ GTL,	"gtl" },
	{ SDC,	"sdc" },
	{ PPC,	"ppc" },
	{ GET,	"get" },
	{ TCT,	"tct" },
	{ PPE,	"ppe" },
	{ PPD,	"ppd" },
	{ DAB,	"dab" }
};



typedef unsigned char u_char;

/*
 * This array is designed for mapping upper and lower case letter
 * together for a case independent comparison.  The mappings are
 * based upon ascii character sequences.
 */
static const u_char charmap[] = {
	'\000', '\001', '\002', '\003', '\004', '\005', '\006', '\007',
	'\010', '\011', '\012', '\013', '\014', '\015', '\016', '\017',
	'\020', '\021', '\022', '\023', '\024', '\025', '\026', '\027',
	'\030', '\031', '\032', '\033', '\034', '\035', '\036', '\037',
	'\040', '\041', '\042', '\043', '\044', '\045', '\046', '\047',
	'\050', '\051', '\052', '\053', '\054', '\055', '\056', '\057',
	'\060', '\061', '\062', '\063', '\064', '\065', '\066', '\067',
	'\070', '\071', '\072', '\073', '\074', '\075', '\076', '\077',
	'\100', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
	'\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
	'\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
	'\170', '\171', '\172', '\133', '\134', '\135', '\136', '\137',
	'\140', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
	'\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
	'\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
	'\170', '\171', '\172', '\173', '\174', '\175', '\176', '\177',
	'\200', '\201', '\202', '\203', '\204', '\205', '\206', '\207',
	'\210', '\211', '\212', '\213', '\214', '\215', '\216', '\217',
	'\220', '\221', '\222', '\223', '\224', '\225', '\226', '\227',
	'\230', '\231', '\232', '\233', '\234', '\235', '\236', '\237',
	'\240', '\241', '\242', '\243', '\244', '\245', '\246', '\247',
	'\250', '\251', '\252', '\253', '\254', '\255', '\256', '\257',
	'\260', '\261', '\262', '\263', '\264', '\265', '\266', '\267',
	'\270', '\271', '\272', '\273', '\274', '\275', '\276', '\277',
	'\300', '\301', '\302', '\303', '\304', '\305', '\306', '\307',
	'\310', '\311', '\312', '\313', '\314', '\315', '\316', '\317',
	'\320', '\321', '\322', '\323', '\324', '\325', '\326', '\327',
	'\330', '\331', '\332', '\333', '\334', '\335', '\336', '\337',
	'\340', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
	'\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
	'\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
	'\370', '\371', '\372', '\373', '\374', '\375', '\376', '\377',
};

int
strcasecmp(s1, s2)
const char *s1, *s2;
{
	register const u_char *cm = charmap,
	*us1 = (const u_char*)s1,
	*us2 = (const u_char*)s2;

	while (cm[*us1] == cm[*us2++])
		if (*us1++ == '\0')
			return 0;
	return cm[*us1] - cm[*--us2];
}

int strncasecmp(s1, s2, n)
const char *s1, *s2;
register size_t n;
{
	if (n != 0) {
		register const u_char *cm = charmap,
		*us1 = (const u_char*)s1,
		*us2 = (const u_char*)s2;

		do {
			if (cm[*us1] != cm[*us2++])
				return cm[*us1] - cm[*--us2];
			if (*us1++ == '\0')
				break;
		} while (--n != 0);
	}
	return 0;
}


static GPIB_Command get_command_from_str(char* token)
{
	/* iterate and look for a matching string */
	int i = 0;

	for (i = 0; i < GPIB_COMMAND_COUNT; i++)
		if (!strcasecmp(command_strings[i].string, token))
			return command_strings[i].command;
	return GPIB_COMMAND_COUNT;
}


GPIB_Command parse_input(char* input)
{
	assert(input);
	char* token;
	GPIB_Command cmd;
	token = strtok(input, " ");
	cmd = get_command_from_str(token);
	token = strtok(NULL, " ");
	memcpy(input, token, 5);
	return cmd;
}

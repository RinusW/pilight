/*
	Copyright (C) 2013 CurlyMo

	This file is part of the Raspberry Pi 433.92Mhz transceiver.

    Raspberry Pi 433.92Mhz transceiver is free software: you can redistribute
	it and/or modify it under the terms of the GNU General Public License as
	published by the Free Software Foundation, either version 3 of the License,
	or (at your option) any later version.

    Raspberry Pi 433.92Mhz transceiver is distributed in the hope that it will
	be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Raspberry Pi 433.92Mhz transceiver. If not, see
	<http://www.gnu.org/licenses/>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "log.h"
#include "protocol.h"
#include "binary.h"
#include "raw.h"

void rawCreateCode(struct options_t *options) {
	char *code = NULL;
	if(getOptionValById(&options, 'C') != NULL) 
		code = getOptionValById(&options, 'C');
	else {
		logprintf(LOG_ERR, "raw: insufficient number of arguments");
		exit(EXIT_FAILURE);
	}
	char *pch;
	int i=0;
	pch = strtok(code, " ");
	while(pch != NULL) {
		raw.raw[i]=atoi(pch);
		pch = strtok(NULL, " ");
		i++;
	}
	raw.rawLength=i;
}

void rawPrintHelp() {
	printf("\t -C --code=\"raw\"\t\traw code devided by spaces\n\t\t\t\t\t(just like the output of debug)\n");
}

void rawInit() {

	strcpy(raw.id, "raw");
	addDevice(&raw, "raw", "Raw codes");
	raw.type = RAW;

	addOption(&raw.options, 'c', "code", required_argument, 0, NULL);

	raw.createCode=&rawCreateCode;
	raw.printHelp=&rawPrintHelp;

	protocol_register(&raw);
}

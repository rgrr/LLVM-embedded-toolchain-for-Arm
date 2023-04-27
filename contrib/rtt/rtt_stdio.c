/*===- rtt_stdio.c - Write instrumentation to a file --------===*\
|*
|* Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
|* See https://llvm.org/LICENSE.txt for license information.
|* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
|*
\*===----------------------------------------------------------------------===*/

#include <stdio.h>
#include <stdint.h>
#include "RTT/SEGGER_RTT.h"

static int rtt_putc(char c, FILE *file)
{
	(void) file;
	SEGGER_RTT_Write(0, &c, 1);
	return c;
}   // rtt_putc

static int rtt_getc(FILE *file)
{
	(void) file;
	uint8_t buf;
	unsigned r = SEGGER_RTT_Read(0, &buf, sizeof(buf));
	return (r == 0) ? EOF : buf;
}   // rtt_getc

static FILE __stdio = FDEV_SETUP_STREAM(rtt_putc, rtt_getc, NULL, _FDEV_SETUP_RW);

//FILE *const stdout = &__stdio;
FILE *const stdin = &__stdio;
__strong_reference(stdin, stdout);
__strong_reference(stdin, stderr);

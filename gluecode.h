/*
 * gluecode.h
 * 
 * Copyright 2014 Benjamin Gould <bgould@github.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef TMK_GLUECODE_H
#define TMK_GLUECODE_H 1

#define _USE_XFUNC_OUT	1	/* 1: Use output functions */
#define	_CR_CRLF		1	/* 1: Convert \n ==> \r\n in the output char */

#define _USE_XFUNC_IN	0	/* 1: Use input function */
#define	_LINE_ECHO		1	/* 1: Echo back input chars in xgets function */

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "tmk_keyboard/xprintf.h"
#include "tmk_keyboard/tmk_debug_config.h"
#include "tmk_keyboard/tmk_keymap.h"
#include "tmk_keyboard/tmk_ps2.h"
#include "tmk_keyboard/tmk_report.h"
#include "tmk_keyboard/tmk_matrix.h"
#include "tmk_keyboard/tmk_action.h"
#include "tmk_keyboard/tmk_util.h"
#include "tmk_keyboard/tmk_host.h"

void arduino_tmk_sendchar(uint8_t c);

void exec_action(uint8_t r, uint8_t c, matrix_row_t matrix_row);

#define dprint(s)           do { xputs(s); } while (0)
#define dprintln()          do { xputs("\n"); } while (0)
#define dprintf(fmt, ...)   do { xprintf(PSTR(fmt), ##__VA_ARGS__); } while (0)
#define dmsg(s)             dprintf("%s at %s: %S\n", __FILE__, __LINE__, PSTR(s))

#ifdef __cplusplus
}
#endif

#endif

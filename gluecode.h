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

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "tmk_keyboard/tmk_keymap.h"
#include "tmk_keyboard/tmk_ps2.h"
#include "tmk_keyboard/tmk_report.h"
#include "tmk_keyboard/tmk_matrix.h"
#include "tmk_keyboard/tmk_action.h"
#include "tmk_keyboard/tmk_util.h"
#include "tmk_keyboard/tmk_host.h"

void exec_action(uint8_t r, uint8_t c, matrix_row_t matrix_row);

#ifdef __cplusplus
}
#endif

#endif

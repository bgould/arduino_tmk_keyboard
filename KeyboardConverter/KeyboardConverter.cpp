/*
 * KeyboardConverter.cpp
 * 
 * Copyright 2013 Benjamin Gould <bcg@bcg-office>
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

#include "Arduino.h"

#define NO_DEBUG

#include "config.h"
#include "KeyboardConverter.h"
#include "action_code.h"
#include "action.h"
#include "action_util.h"
#include "keymap.h"

KeyboardConverter::KeyboardConverter(KeyboardHost *host)
{
    _host = host;
}

void KeyboardConverter::init()
{
    keyboard_init();
}

void KeyboardConverter::run_task()
{
    keyboard_task();
}

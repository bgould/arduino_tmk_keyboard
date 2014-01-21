/*
 * KeyboardReport.cpp
 * 
 * Copyright 2013 Benjamin Gould
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

#include "KeyboardReport.h"

KeyboardReport::KeyboardReport(report_keyboard_t *report)
{
    _report = report;
}

uint8_t KeyboardReport::getModifiers()
{
    return _report->mods;
}

uint8_t KeyboardReport::getReserved()
{
    return _report->reserved;
}    

uint8_t KeyboardReport::getKey(uint8_t keyIndex)
{
    return _report->keys[keyIndex];
}

uint8_t KeyboardReport::getReportKeys()
{
    return REPORT_KEYS;
}

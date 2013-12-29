/*
 * PS2toBluefruitConverter.h
 * 
 * Copyright 2013 Benjamin Gould <bgould@github.com>
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


#ifndef PS2TOBLUEFRUITCONVERTER_H
#define PS2TOBLUEFRUITCONVERTER_H

#include <KeyboardConverter.h>

class PS2toBluefruitConverter: public KeyboardConverter
{
    public:
        PS2toBluefruitConverter();
        void init();
		void run_task();
};

#endif /* PS2TOBLUEFRUITCONVERTER_H */ 

/*
 * BluefruitHost.cpp
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

// see: http://learn.adafruit.com/introducing-bluefruit-ez-key-diy-bluetooth-hid-keyboard
// TODO: add logic for using software serial as well - BCG

#include "BluefruitHost.h"

static inline void bluefruit_trace_header()
{
    dprint("bluefruit: ");
}

static inline void bluefruit_trace_footer()
{
    dprintln();
}

BluefruitHost::BluefruitHost() {
}

void BluefruitHost::begin()
{
    Serial1.begin(9600);
}

uint8_t BluefruitHost::getLEDs()
{
    // not implemented on Bluefruit; method is virtual so feel free to override
    return 0;
}

void BluefruitHost::sendKeyboard(KeyboardReport &report)
{
    bluefruit_trace_header();
    dprintf("(keyboard) ");
    _serial_send(0xFD);
    _serial_send(report.getModifiers());
    _serial_send(report.getReserved());
    for (short i = 0; i < REPORT_SIZE; i++)
    {
        _serial_send(report.getKey(i));
    }
    bluefruit_trace_footer();
}

void BluefruitHost::sendMouse(MouseReport &report)
{
    bluefruit_trace_header();
    dprintf("(mouse) ");
    _serial_send(0xFD);
    _serial_send(0x00);
    _serial_send(0x03);
    _serial_send(report.getButtons());
    _serial_send(report.getX());
    _serial_send(report.getY());
    _serial_send(report.getV()); // TODO: determine if bluefruit 
    _serial_send(report.getH()); //       supports mouse wheel - BCG
    _serial_send(0x00);
    bluefruit_trace_footer();
};

/*
+-----------------+-------------------+-------+
| Consumer Key    | Bit Map           | Hex   |
+-----------------+-------------------+-------+
| Home            | 00000001 00000000 | 01 00 |
| KeyboardLayout  | 00000010 00000000 | 02 00 |
| Search          | 00000100 00000000 | 04 00 |
| Snapshot        | 00001000 00000000 | 08 00 |
| VolumeUp        | 00010000 00000000 | 10 00 |
| VolumeDown      | 00100000 00000000 | 20 00 |
| Play/Pause      | 01000000 00000000 | 40 00 |
| Fast Forward    | 10000000 00000000 | 80 00 |
| Rewind          | 00000000 00000001 | 00 01 |
| Scan Next Track | 00000000 00000010 | 00 02 |
| Scan Prev Track | 00000000 00000100 | 00 04 |
| Random Play     | 00000000 00001000 | 00 08 |
| Stop            | 00000000 00010000 | 00 10 |
+-------------------------------------+-------+
*/
#define CONSUMER2BLUEFRUIT(usage) \
    (usage == AUDIO_MUTE           ? 0x0000  : \
    (usage == AUDIO_VOL_UP         ? 0x1000  : \
    (usage == AUDIO_VOL_DOWN       ? 0x2000  : \
    (usage == TRANSPORT_NEXT_TRACK ? 0x0002  : \
    (usage == TRANSPORT_PREV_TRACK ? 0x0004  : \
    (usage == TRANSPORT_STOP       ? 0x0010  : \
    (usage == TRANSPORT_STOP_EJECT ? 0x0000  : \
    (usage == TRANSPORT_PLAY_PAUSE ? 0x4000  : \
    (usage == AL_CC_CONFIG         ? 0x0000  : \
    (usage == AL_EMAIL             ? 0x0000  : \
    (usage == AL_CALCULATOR        ? 0x0000  : \
    (usage == AL_LOCAL_BROWSER     ? 0x0000  : \
    (usage == AC_SEARCH            ? 0x0400  : \
    (usage == AC_HOME              ? 0x0100  : \
    (usage == AC_BACK              ? 0x0000  : \
    (usage == AC_FORWARD           ? 0x0000  : \
    (usage == AC_STOP              ? 0x0000  : \
    (usage == AC_REFRESH           ? 0x0000  : \
    (usage == AC_BOOKMARKS         ? 0x0000  : 0)))))))))))))))))))
void BluefruitHost::sendConsumer(uint16_t data)
{
    if (data == _last_consumer_data) return;
    _last_consumer_data = data;
    
    uint16_t bitmap = CONSUMER2BLUEFRUIT(data);
    bluefruit_trace_header();
    dprintf("(consumer) ");
    _serial_send(0xFD);
    _serial_send(0x00);
    _serial_send(0x02);
    _serial_send((bitmap>>8)&0xFF);
    _serial_send(bitmap&0xFF); 
    _serial_send(0x00);
    _serial_send(0x00);
    _serial_send(0x00);
    _serial_send(0x00);
    bluefruit_trace_footer();
};

void BluefruitHost::sendSystem(uint16_t data)
{
    // not implemented in Bluefruit
}

void BluefruitHost::_serial_send(uint8_t data)
{
	dprint(" ");
	dprintf("%02x", data);
    Serial1.write(data);
}

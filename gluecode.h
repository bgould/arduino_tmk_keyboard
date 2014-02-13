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

#define NO_ACTION_MACRO
#define NO_ACTION_ONESHOT

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DEBUG_H
#define DEBUG_H 1

void print_set_sendchar(int8_t (*print_sendchar_func)(uint8_t));

#if DEBUG_ENABLE

#define dprint(s)           do { if (debug_enable) xputs(PSTR(s)); } while (0)
#define dprintln()          do { if (debug_enable) xputs(PSTR("\n")); } while (0)
#define dprintf(fmt, ...)   do { if (debug_enable) xprintf(PSTR(fmt), ##__VA_ARGS__); } while (0)
#define dmsg(s)             dprintf("%s at %s: %S\n", __FILE__, __LINE__, PSTR(s))

/* for old name */
#define pdec(data)              print_dec(data)
#define pdec16(data)            print_dec(data)
#define phex(data)              print_hex8(data)
#define phex16(data)            print_hex16(data)
#define pbin(data)              print_bin8(data)
#define pbin16(data)            print_bin16(data)
#define pbin_reverse(data)      print_bin_reverse8(data)
#define pbin_reverse16(data)    print_bin_reverse16(data)

/* print value utility */
#define print_val_dec(v)           dprintf(#v ": %u\n", v)
#define print_val_decs(v)          dprintf(#v ": %d\n", v)
#define print_val_hex8(v)          dprintf(#v ": %X\n", v)
#define print_val_hex16(v)         dprintf(#v ": %02X\n", v)
#define print_val_hex32(v)         dprintf(#v ": %04lX\n", v)
#define print_val_bin8(v)          dprintf(#v ": %08b\n", v)
#define print_val_bin16(v)         dprintf(#v ": %016b\n", v)
#define print_val_bin32(v)         dprintf(#v ": %032lb\n", v)
#define print_val_bin_reverse8(v)  dprintf(#v ": %08b\n", bitrev(v))
#define print_val_bin_reverse16(v) dprintf(#v ": %016b\n", bitrev16(v))
#define print_val_bin_reverse32(v) dprintf(#v ": %032lb\n", bitrev32(v))

/* print string stored in program memory(FLASH)
 *     print_P(PSTR("hello world");
 * This consumes relatively abundant FLASH memory area not SRAM.
 */
#define print_P(s)          xputs(PSTR(s))

/* decimal */
#define print_dec(i)        dprintf("%u", i)
#define print_decs(i)       dprintf("%d", i)

/* hex */
#define print_hex4(i)       dprintf("%X", i)
#define print_hex8(i)       dprintf("%02X", i)
#define print_hex16(i)      dprintf("%04X", i)
#define print_hex32(i)      dprintf("%08lX", i)

/* binary */
#define print_bin4(i)       dprintf("%04b", i)
#define print_bin8(i)       dprintf("%08b", i)
#define print_bin16(i)      dprintf("%016b", i)
#define print_bin32(i)      dprintf("%032lb", i)

#define print_bin_reverse8(i)   dprintf("%08b", bitrev(i))
#define print_bin_reverse16(i)  dprintf("%016b", bitrev16(i))
#define print_bin_reverse32(i)  dprintf("%032lb", bitrev32(i))

/* DO NOT USE these anymore */
#define debug(s)                  do { if (debug_enable) xputs(PSTR(s)); } while (0)
#define debugln(s)                do { if (debug_enable) xputs(PSTR("\n")); } while (0)
//#define debug_S(s)                do { if (debug_enable) print_S(s); } while (0)
#define debug_P(s)                do { if (debug_enable) print_P(s); } while (0)
#define debug_msg(s)              do { \
    if (debug_enable) { \
        print_P(__FILE__); print_P(" at "); print_dec(__LINE__); print_P(" in "); print_P(": "); print_P(s); \
    } \
} while (0)
#define debug_dec(data)           do { if (debug_enable) print_dec(data); } while (0)
#define debug_decs(data)          do { if (debug_enable) print_decs(data); } while (0)
#define debug_hex4(data)          do { if (debug_enable) print_hex4(data); } while (0)
#define debug_hex8(data)          do { if (debug_enable) print_hex8(data); } while (0)
#define debug_hex16(data)         do { if (debug_enable) print_hex16(data); } while (0)
#define debug_hex32(data)         do { if (debug_enable) print_hex32(data); } while (0)
#define debug_bin8(data)          do { if (debug_enable) print_bin8(data); } while (0)
#define debug_bin16(data)         do { if (debug_enable) print_bin16(data); } while (0)
#define debug_bin32(data)         do { if (debug_enable) print_bin32(data); } while (0)
#define debug_bin_reverse8(data)  do { if (debug_enable) print_bin_reverse8(data); } while (0)
#define debug_bin_reverse16(data) do { if (debug_enable) print_bin_reverse16(data); } while (0)
#define debug_bin_reverse32(data) do { if (debug_enable) print_bin_reverse32(data); } while (0)
#define debug_hex(data)           debug_hex8(data)
#define debug_bin(data)           debug_bin8(data)
#define debug_bin_reverse(data)   debug_bin8(data)

#else
#include "tmk/tmk_keyboard/common/nodebug.h"

#define print_S(s)
#define print_P(s)
#define print_dec(data)
#define print_decs(data)
#define print_hex4(data)
#define print_hex8(data)
#define print_hex16(data)
#define print_hex32(data)
#define print_bin4(data)
#define print_bin8(data)
#define print_bin16(data)
#define print_bin32(data)
#define print_bin_reverse8(data)
#define print_bin_reverse16(data)
#define print_bin_reverse32(data)

#endif

#endif

#ifndef NODEBUG_H
#define NODEBUG_H 1
#endif

#include "tmk/xprintf.h"
#include "tmk/tmk_keyboard/common/debug_config.h"
#include "tmk/tmk_keyboard/common/keymap.h"
#include "tmk/tmk_keyboard/protocol/ps2.h"
#include "tmk/tmk_keyboard/common/report.h"
#include "tmk/tmk_keyboard/common/matrix.h"
#include "tmk/tmk_keyboard/common/action.h"
#include "tmk/tmk_keyboard/common/action_layer.h"
#include "tmk/tmk_keyboard/common/util.h"
#include "tmk/tmk_keyboard/common/host.h"
#include "tmk/tmk_keyboard/common/timer.h"
#include "tmk/tmk_keyboard/common/command.h"

#if MOUSEKEY_ENABLE
#include "tmk/tmk_keyboard/common/mousekey.h"
#endif

int8_t arduino_tmk_sendchar(uint8_t c);

void exec_action(uint8_t r, uint8_t c, matrix_row_t matrix_row);


#ifdef __cplusplus
}
#endif

#endif

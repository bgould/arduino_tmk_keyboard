#include "Arduino.h"

#ifndef TMK_KEYBOARD_H
#define TMK_KEYBOARD_H

#if (defined(PS2_CODESET_2) || defined(PS2_CODESET_3))

#define PS2_USE_BUSYWAIT 1
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   1

#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    0

// Codeset 3; this is used on Model M terminal keyboards
#ifdef PS2_CODESET_3
#define     MATRIX_ROWS 17  // keycode bit: 3-0
#define     MATRIX_COLS 8   // keycode bit: 6-4
#include    "ps2_codeset3_matrix.h"
#endif

// Codeset 2; this is the "standard" PS/2 codeset for most keyboards
#ifdef PS2_CODESET_2
#define MATRIX_ROWS 32  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4
#include "ps2_codeset2_matrix.h"
#endif

#endif

#endif

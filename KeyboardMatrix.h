#ifndef KEYBOARDMATRIX_H
#define KEYBOARDMATRIX_H 1

#include "KeyboardFirmware.h"

/* translates Fn keycode to action */
//action_t keymap_fn_to_action(uint8_t keycode);

#if (MATRIX_COLS <= 8)
typedef  uint8_t    matrix_row_t;
#elif (MATRIX_COLS <= 16)
typedef  uint16_t   matrix_row_t;
#elif (MATRIX_COLS <= 32)
typedef  uint32_t   matrix_row_t;
#else
#error "MATRIX_COLS: invalid value"
#endif

#define MATRIX_IS_ON(row, col)  (matrix_get_row(row) && (1<<col))

class KeyboardMatrix
{
    public:
        virtual void begin() = 0;
        virtual uint8_t scan() = 0;
        virtual uint8_t getRows() = 0;
        virtual uint8_t getCols() = 0;
        virtual bool isOn(uint8_t row, uint8_t col) = 0;
        virtual bool isGhostInRow(uint8_t row) = 0;
        virtual matrix_row_t getRow(uint8_t row) = 0;
        virtual void debugPrint(void) = 0;
};

#endif

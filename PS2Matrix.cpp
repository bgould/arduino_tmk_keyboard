#include "PS2Matrix.h"
#include "tmk_ps2.h"
//#include "tmk_util.h"


PS2Matrix::PS2Matrix()
{
}

void PS2Matrix::begin()
{
#if DEBUG_ENABLE
    KeyboardDebug.println(F("[ Initializing PS2 matrix ]"));
#endif
    ps2_host_init();

    for (uint8_t i = 0, c = getRows(); i < c; i++) _matrix[i] = 0x00;
}

bool PS2Matrix::isOn(uint8_t row, uint8_t col)
{
    return (_matrix[row] & (1<<col));
}

matrix_row_t PS2Matrix::getRow(uint8_t row)
{
    return _matrix[row];
}

#if DEBUG_ENABLE
void PS2Matrix::debugPrint(void)
{
    #if DEBUG_MATRIX
    KeyboardDebug.print(F("\nr/c 01234567\n"));
    for (uint8_t row = 0, c = getRows(); row < c; row++) {
        KeyboardDebug.print(row, HEX);
        KeyboardDebug.print(F(": "));
        uint8_t bits = getRow(row); // bitrev(row);
        KeyboardDebug.print(bits, BIN);
#ifdef PS2_HAS_GHOSTING
        if (isGhostInRow(row)) {
            KeyboardDebug.print(F(" <ghost"));
        }
#endif
        KeyboardDebug.print(F("\n"));
    }
    #endif
}
#endif

bool PS2Matrix::isGhostInRow(uint8_t row)
{
#if PS2_HAS_GHOSTING
    // no ghost exists in case less than 2 keys on
    if (((_matrix[row] - 1) & _matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (i != row && (_matrix[i] & _matrix[row]) == _matrix[row])
            return true;
    }
#endif
    return false;
}

void PS2Matrix::_make(uint8_t code)
{
    if (!isOn(PS2_ROW(code), PS2_COL(code))) {
        _matrix[PS2_ROW(code)] |= 1<<PS2_COL(code);
        _is_modified = true;
    }
}

void PS2Matrix::_break(uint8_t code)
{
    if (isOn(PS2_ROW(code), PS2_COL(code))) {
        _matrix[PS2_ROW(code)] &= ~(1<<PS2_COL(code));
        _is_modified = true;
    }
}

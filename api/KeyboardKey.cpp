#include "KeyboardKey.h"

KeyboardKey::KeyboardKey(uint8_t row, uint8_t col) {
    _row = row;
    _col = col;
}

uint8_t KeyboardKey::getRow() {
    return _row;
}

uint8_t KeyboardKey::getCol() {
    return _col;
}

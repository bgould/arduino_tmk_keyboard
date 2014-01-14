#ifndef KEYBOARD_KEY_H
#define KEYBOARD_KEY_H 1

#include "Arduino.h"

class KeyboardKey {
    public:
        KeyboardKey(uint8_t row, uint8_t col);
        uint8_t getRow(void);
        uint8_t getCol(void);
    private:
        uint8_t _row;
        uint8_t _col;
};

#endif


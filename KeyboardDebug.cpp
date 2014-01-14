#include "KeyboardDebug.h"

size_t KeyboardDebug_::write(uint8_t c) {
    return Serial.write(c);
}

KeyboardDebug_ KeyboardDebug;

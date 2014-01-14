#ifndef KEYBOARDDEBUG_H
#define KEYBOARDDEBUG_H 1

#include "Arduino.h"

class KeyboardDebug_ : public Print
{
    public:
        size_t write(uint8_t c);
};

#endif

extern KeyboardDebug_ KeyboardDebug;

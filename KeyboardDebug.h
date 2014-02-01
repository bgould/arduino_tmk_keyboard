#ifndef KEYBOARDDEBUG_H
#define KEYBOARDDEBUG_H 1

#include "Arduino.h"

#define kb_dprint(s)           do { KeyboardDebug.print(F(s)); } while (0)
#define kb_dprintln(s)         do { KeyboardDebug.print(F(s)); KeyboardDebug.println(); } while (0)
#define kb_dprintf(s, fmt)     do { KeyboardDebug.print(s, fmt); } while (0)
#define kb_dmsg(s)             kb_dprintf("%s at %s: %S\n", __FILE__, __LINE__, PSTR(s))

class KeyboardDebug_ : public Print
{
    public:
        size_t write(uint8_t c);
};

#endif

extern KeyboardDebug_ KeyboardDebug;

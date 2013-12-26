/*

*/

#ifndef KeyboardProtocol_h
#define KeyboardProtocol_h

#include "Arduino.h"
#include "KeyboardReport.h"

class KeyboardProtocol
{
    public:
        KeyboardProtocol();
        virtual void init();
        virtual KeyboardReport receive();
};

#endif

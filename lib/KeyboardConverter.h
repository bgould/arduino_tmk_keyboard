
#ifndef KeyboardConverter_h
#define KeyboardConverter_h

#include "Arduino.h"

#include "KeyboardHost.h"

class KeyboardConverter
{
    public:
        KeyboardConverter();
        virtual void init();
		virtual void run_task();
    protected:
        KeyboardHost  *_host; 
};

#endif

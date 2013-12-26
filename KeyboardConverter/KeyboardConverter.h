
#ifndef KeyboardConverter_h
#define KeyboardConverter_h

#include "Arduino.h"

#include "KeyboardHost.h"



class KeyboardConverter
{
    public:
        KeyboardConverter(KeyboardHost *host);
        void init();
		void run_task();
    private:
        KeyboardHost      *_host; 
};

#endif

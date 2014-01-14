#ifndef KEYBOARDHOST_H
#define KEYBOARDHOST_H

#include "KeyboardReport.h"
#include "MouseReport.h"

class KeyboardHost
{
	public:
		virtual void begin() = 0;
		virtual void sendKeyboard(KeyboardReport &report) = 0;
		virtual void sendMouse(MouseReport &report) = 0;
		virtual void sendConsumer(uint16_t data) = 0;
        virtual void sendSystem(uint16_t data) = 0;
        virtual uint8_t getLEDs(void) = 0;
};

#endif

#ifndef KeyboardHost_h
#define KeyboardHost_h

#include "KeyboardReport.h"
#include "MouseReport.h"

class KeyboardHost
{
	public:
		virtual void init() = 0;
		virtual void sendKeyboard(KeyboardReport *report) = 0;
		virtual void sendMouse(MouseReport *report) = 0;
		virtual void sendConsumer(uint16_t data) = 0;
};

#endif

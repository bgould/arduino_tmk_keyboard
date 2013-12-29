#ifndef KeyboardHost_h
#define KeyboardHost_h

#include "KeyboardReport.h"
#include "MouseReport.h"

#include "host_driver.h"

class KeyboardHost
{
	public:
		virtual void init();
		virtual void sendKeyboard(KeyboardReport *report);
		virtual void sendMouse(MouseReport *report);
		virtual void sendConsumer(uint16_t data);
        host_driver_t* asHostDriver();
};

#endif

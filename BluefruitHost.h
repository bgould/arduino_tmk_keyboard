#ifndef BLUEFRUITHOST_H
#define BLUEFRUITHOST_H 1

#include "KeyboardFirmware.h"

class BluefruitHost : public KeyboardHost
{
	public:
		BluefruitHost();
		virtual void begin();
		virtual void sendKeyboard(KeyboardReport &report);
		virtual void sendMouse(MouseReport &report);
		virtual void sendConsumer(uint16_t data);
        virtual void sendSystem(uint16_t data);
        virtual uint8_t getLEDs();
    protected:
        void _serial_send(uint8_t data);
	private:
        uint16_t _last_consumer_data;
};

#endif

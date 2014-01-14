#ifndef BluefruitHost_h
#define BluefruitHost_h

#include "KeyboardFirmware.h"

class BluefruitHost : public KeyboardHost
{
	public:
		BluefruitHost(int rxPin, int txPin);
		virtual void begin();
		virtual void sendKeyboard(KeyboardReport &report);
		virtual void sendMouse(MouseReport &report);
		virtual void sendConsumer(uint16_t data);
        virtual void sendSystem(uint16_t data);
        virtual uint8_t getLEDs();
    protected:
        void _serial_send(uint8_t data);
	private:
        SoftwareSerial _serial;
        uint16_t _last_consumer_data;
};

#endif

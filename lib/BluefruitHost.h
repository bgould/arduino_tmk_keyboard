#ifndef BluefruitHost_h
#define BluefruitHost_h

#include "KeyboardHost.h"
#include "HardwareSerial.h"

class BluefruitHost : public KeyboardHost
{
	public:
		BluefruitHost(HardwareSerial *serial);
		void init();
		void sendKeyboard(KeyboardReport *report);
		void sendMouse(MouseReport *report);
		void sendConsumer(uint16_t data);
    protected:
        void _serial_send(uint8_t data);
	private:
		HardwareSerial *_hw_serial;
        uint16_t _last_consumer_data;
};

#endif

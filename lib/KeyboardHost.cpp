#include "KeyboardHost.h"

static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

// Not implemented yet
static uint8_t keyboard_leds(void) {}
static void send_system(uint16_t data) {}

// Ugly. We'll keep the last KeyboardHost in a global
// Better might be to use a data structure to support multiple hosts
static KeyboardHost *_global_host;

static void send_keyboard(report_keyboard_t *report_t) {
    KeyboardReport *report = new KeyboardReport(report_t);
    _global_host->sendKeyboard(report);
    delete report;
}

static void send_mouse(report_mouse_t *report_t) {
    MouseReport *report = new MouseReport(report_t);
    _global_host->sendMouse(report);
    delete report;
}

static void send_consumer(uint16_t data) {
    _global_host->sendConsumer(data);
}

host_driver_t* KeyboardHost::asHostDriver()
{
    _global_host = this;
    host_driver_t driver = {
        keyboard_leds,
        send_keyboard,
        send_mouse,
        send_system,
        send_consumer
    };
    return &driver;
}

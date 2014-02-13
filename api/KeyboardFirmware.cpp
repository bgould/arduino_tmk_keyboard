#include "KeyboardFirmware.h"
#include "gluecode.h"

static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

static host_driver_t _global_host_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};

static bool _global_host_driver_set = false;

extern "C" int8_t arduino_tmk_sendchar(uint8_t c) {
#if DEBUG_ENABLE
	return Serial.write(c);
#else
    return 0;
#endif
}

KeyboardFirmware_::KeyboardFirmware_()
{

}

void KeyboardFirmware_::begin(KeyboardHost &host, KeyboardMatrix &matrix)
{
	timer_init();
	
    _host = &host;
    _matrix = &matrix;
    _host->begin();
    _matrix->begin();
    
    if (!_global_host_driver_set) {
        dprint("setting global host driver\n");
        host_set_driver(&_global_host_driver);
    }
}

void KeyboardFirmware_::runTask()
{
    static matrix_row_t matrix_prev[MATRIX_ROWS];
    static uint8_t led_status = 0;
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;
    
    _matrix->scan();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row = _matrix->getRow(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change)
            _matrix->debugPrint();
        if (_matrix->isGhostInRow(r)) {
            matrix_prev[r] = matrix_row;
            continue;
        }
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            if (matrix_change & ((matrix_row_t)1<<c)) {
                dprint("{ .row = "); 
                dprintf("%u", r);
                dprint(", .col = "); 
                dprintf("%u", c);
                dprint(", .layer = ");
                dprintf("%032b", (layer_state | default_layer_state));
                dprint(", .pressed = "); 
                dprintf("%08b", matrix_row & ((matrix_row_t)1<<c));
                dprint(", .time = "); 
                dprintf("%lu", timer_read32());
                dprint(" }");
                dprintln();
                exec_action(r, c, matrix_row);
                // record a processed key
                matrix_prev[r] ^= ((matrix_row_t)1<<c);
                // process a key per task call
                goto MATRIX_LOOP_END;
            }
        }
    }
MATRIX_LOOP_END:

#ifdef MOUSEKEY_ENABLE
    // mousekey repeat & acceleration
    mousekey_task();
#endif

#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_task();
#endif

    // update LED
    if (led_status != _host->getLEDs()) {
        led_status = _host->getLEDs();
        setLEDs(led_status);
    }
}

void KeyboardFirmware_::setLEDs(uint8_t leds)
{
    //if (debug_keyboard) { dprint("keyboard_set_led: "); dprintf("02X"); dprintln(); }
    //_host->setLEDs(leds);
}

KeyboardHost* KeyboardFirmware_::getHost() {
    return _host;
}

KeyboardFirmware_ KeyboardFirmware;

// Not implemented yet
static uint8_t keyboard_leds(void) {
    return KeyboardFirmware.getHost()->getLEDs();
}

static void send_system(uint16_t data) {
    KeyboardFirmware.getHost()->sendSystem(data);
}

static void send_keyboard(report_keyboard_t *report_t) {
    KeyboardReport report(report_t);
    KeyboardFirmware.getHost()->sendKeyboard(report);
    //delete &report;
}

static void send_mouse(report_mouse_t *report_t) {
    MouseReport report(report_t);
    KeyboardFirmware.getHost()->sendMouse(report);
    //delete &report;
}

static void send_consumer(uint16_t data) {
    KeyboardFirmware.getHost()->sendConsumer(data);
}

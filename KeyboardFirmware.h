#ifndef KEYBOARDFIRMWARE_H
#define KEYBOARDFIRMWARE_H 1

#define START_KEYMAPS extern "C" {

#define KEYMAPS static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] 

#define FN_ACTIONS static const uint16_t fn_actions[] PROGMEM

#define KEYMAPS_FINISHED uint8_t keymap_key_to_keycode(uint8_t layer, key_t key) { \
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]); \
    } \
    action_t keymap_fn_to_action(uint8_t keycode) { \
        action_t action; \
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]); \
        return action; \
    } \
}

#include "Arduino.h"
#include "gluecode.h"
#include "KeyboardKey.h"
#include "KeyboardMatrix.h"
#include "KeyboardHost.h"
#include "KeyboardReport.h"
#include "MouseReport.h"
#include "BluefruitHost.h"
#include "PS2Matrix.h"
#include "PS2MatrixCodeset3.h"

class KeyboardFirmware_
{
    public:
        KeyboardFirmware_();
        void runTask(void);
        void begin(KeyboardHost &host, KeyboardMatrix &matrix);
        void setLEDs(uint8_t leds);
        KeyboardHost* getHost();
        KeyboardMatrix* getMatrix();
    private:
        KeyboardHost *_host;
        KeyboardMatrix *_matrix;
};

extern KeyboardFirmware_ KeyboardFirmware;

#endif

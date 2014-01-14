#ifndef KEYBOARDFIRMWARE_H
#define KEYBOARDFIRMWARE_H 1

#define MATRIX_ROWS 17
#define MATRIX_COLS 8

#define DEBUG_ENABLE true
#define DEBUG_MATRIX false

#include <SoftwareSerial.h>
#include "gluecode.h"
#include "KeyboardKey.h"
#include "KeyboardMatrix.h"
#include "KeyboardHost.h"
#include "KeyboardDebug.h"
#include "KeyboardReport.h"
#include "MouseReport.h"

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

#ifndef MOUSEREPORT_H
#define MOUSEREPORT_H

#include "KeyboardFirmware.h"

class MouseReport
{
    public:
		MouseReport(report_mouse_t *report);
        uint8_t getButtons();
        uint8_t getX();
        uint8_t getY();
        uint8_t getV();
        uint8_t getH();
    private:
		report_mouse_t *_report;
};

#endif

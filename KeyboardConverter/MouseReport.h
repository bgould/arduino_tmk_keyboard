#ifndef MouseReport_h
#define MouseReport_h

#include "Arduino.h"
#include "report.h"

class MouseReport
{
    public:
		MouseReport(report_mouse_t *report);
        byte getButtons();
        byte getX();
        byte getY();
        byte getV();
        byte getH();
    private:
		report_mouse_t *_report;
};

#endif

#include "MouseReport.h"

MouseReport::MouseReport(report_mouse_t *report)
{
    _report = report;
}

byte MouseReport::getButtons()
{
    return _report->buttons;
}

byte MouseReport::getX()
{
    return _report->x;
}

byte MouseReport::getY()
{
    return _report->y;
}

byte MouseReport::getV()
{
    return _report->v;
}

byte MouseReport::getH()
{
    return _report->h;
}

#ifndef PS2MATRIX_H
#define PS2MATRIX_H 1

#include "KeyboardFirmware.h"

#define PS2_ROW(code)      (code>>3)
#define PS2_COL(code)      (code&0x07)

class PS2Matrix : public KeyboardMatrix
{
    public:
        PS2Matrix();
        virtual void begin();
        virtual uint8_t scan() = 0;
        virtual uint8_t getRows() = 0;
        virtual uint8_t getCols() = 0;
        virtual bool isOn(uint8_t row, uint8_t col);
        bool isGhostInRow(uint8_t row);
        virtual matrix_row_t getRow(uint8_t row);
        virtual void debugPrint(void);
    protected:
        void _make(uint8_t code);
        void _break(uint8_t code); 
        uint8_t _matrix[MATRIX_ROWS];
        bool _is_modified;
};

#endif

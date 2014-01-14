#if 0

#ifndef DUMMYMATRIX_H
#define DUMMYMATRIX_H 1

#define MATRIX_ROWS 1
#define MATRIX_COLS 8

#include "KeyboardFirmware.h"

class DummyMatrix : public KeyboardMatrix
{
    public:
        DummyMatrix();
        void begin();
        uint8_t scan(void);
        uint8_t getRows();
        uint8_t getCols();
        bool isOn(uint8_t row, uint8_t col);
        matrix_row_t getRow(uint8_t row);
#if DEBUG_ENABLE
        void debugPrint(void);
#endif
    private:
        uint8_t _row;
        int _loops;
};

#endif

#endif

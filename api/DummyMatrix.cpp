#if 0

#include "DummyMatrix.h"

DummyMatrix::DummyMatrix(void) {
}

void DummyMatrix::begin(void) {
    _loops = 0;
    _row = 0;
}

uint8_t DummyMatrix::scan(void) {
    if ((_loops++ / 10000) % 2 == 0) {
        _row = 0;
    } else {
        _row = (1<<7);
    }
    return 1;
}

uint8_t DummyMatrix::getRows(void) {
    return MATRIX_ROWS;
}

uint8_t DummyMatrix::getCols(void) {
    return MATRIX_COLS;
}

bool DummyMatrix::isOn(uint8_t row, uint8_t col) {
    return _row && (1<<col);
}

matrix_row_t DummyMatrix::getRow(uint8_t row) {
    if (row == 0) {
        return _row;
    } else {
        return 0;
    }
}

#if DEBUG_ENABLE
void DummyMatrix::debugPrint(void) {
    KeyboardDebug.print(F("[row : "));
    KeyboardDebug.print(_row);
    KeyboardDebug.println(F(" ]"));
}
#endif

#endif

#include "PS2MatrixCodeset3.h"

PS2MatrixCodeset3::PS2MatrixCodeset3() {
}

uint8_t PS2MatrixCodeset3::scan()
{
    // scan code reading states
    static enum {
        RESET,
        RESET_RESPONSE,
        KBD_ID0,
        KBD_ID1,
        CONFIG,
        READY,
        F0,
    } state = RESET;

    _is_modified = false;

    uint8_t code;
    if ((code = ps2_host_recv())) {
#if DEBUG_ENABLE
        KeyboardDebug.print(F("r")); KeyboardDebug.print(code, HEX); KeyboardDebug.print(F(" "));
#endif
    }

    uint8_t response;
    switch (state) {
        case RESET:
#if DEBUG_ENABLE
            KeyboardDebug.print(F("wFF "));
#endif
            response = ps2_host_send(0xFF);
            if (response == 0xFA) {
#if DEBUG_ENABLE
                KeyboardDebug.print(F("[ack]\nRESET_RESPONSE: "));
#endif
                state = RESET_RESPONSE;
            } else {
#if DEBUG_ENABLE
    KeyboardDebug.print(F("{ response: "));
    KeyboardDebug.print(response, HEX);
    KeyboardDebug.print(F(", error: "));
    KeyboardDebug.print(ps2_error);
    KeyboardDebug.println(F("} "));
#endif
            }
            break;
        case RESET_RESPONSE:
            if (code == 0xAA) {
#if DEBUG_ENABLE
                KeyboardDebug.print(F("[ok]\nKBD_ID: "));
#endif
                state = KBD_ID0;
            } else if (code) {
#if DEBUG_ENABLE
                KeyboardDebug.print(F("err\nRESET: "));
#endif
                state = RESET;
            }
            break;
        // after reset receive keyboad ID(2 bytes)
        case KBD_ID0:
            if (code) {
                state = KBD_ID1;
            }
            break;
        case KBD_ID1:
            if (code) {
#if DEBUG_ENABLE
                KeyboardDebug.print(F("\nCONFIG: "));
#endif
                state = CONFIG;
            }
            break;
        case CONFIG:
#if DEBUG_ENABLE
            KeyboardDebug.print("wF8 ");
#endif
            if (ps2_host_send(0xF8) == 0xFA) {
#if DEBUG_ENABLE
                KeyboardDebug.print(F("[ack]\nREADY\n"));
#endif
                state = READY;
            }
            break;
        case READY:
            switch (code) {
                case 0x00:
                    break;
                case 0xF0:
                    state = F0;
#if DEBUG_ENABLE
                    KeyboardDebug.print(" ");
#endif
                    break;
                default:    // normal key make
                    if (code < 0x88) {
                        _make(code);
                    } else {
#if DEBUG_ENABLE
                        KeyboardDebug.print(F("unexpected scan code at READY: ")); KeyboardDebug.print(code, HEX); KeyboardDebug.print(F("\n"));
#endif
                    }
                    state = READY;
#if DEBUG_ENABLE
                    KeyboardDebug.print(F("\n"));
#endif
            }
            break;
        case F0:    // Break code
            switch (code) {
                case 0x00:
                    break;
                default:
                    if (code < 0x88) {
                        _break(code);
                    } else {
#if DEBUG_ENABLE
                        KeyboardDebug.print(F("unexpected scan code at F0: ")); KeyboardDebug.print(code, HEX); KeyboardDebug.print(F("\n"));
#endif
                    }
                    state = READY;
#if DEBUG_ENABLE
                    KeyboardDebug.print(F("\n"));
#endif
            }
            break;
    }
    return 1;
}

uint8_t PS2MatrixCodeset3::getRows()
{
    return MATRIX_ROWS;
}

uint8_t PS2MatrixCodeset3::getCols()
{
    return MATRIX_COLS;
}

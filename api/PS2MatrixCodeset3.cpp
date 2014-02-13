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
		CODESET_QUERY,
		CODESET_RESPONSE,
		CODESET_REQUEST,
        CONFIG,
        READY,
        F0,
    } state = RESET;

    _is_modified = false;

    uint8_t code;
    if ((code = ps2_host_recv())) {
		dprint("r"); 
		dprintf("%02X", code); 
		dprint(" ");
    }

    uint8_t response;
    switch (state) {
        case RESET:
            dprint("wFF ");
            response = ps2_host_send(0xFF);
            if (response == 0xFA) {
				dprint("[ack]\nRESET_RESPONSE: ");
                state = RESET_RESPONSE;
            } else {
				dprint("{ response: ");
				dprintf("%02x", response);
				dprint(", error: ");
				dprintf("%x", ps2_error);
				dprint("} ");
				dprintln();
            }
            break;
        case RESET_RESPONSE:
            if (code == 0xAA) {
                dprint("[ok]\nKBD_ID: ");
                state = KBD_ID0;
            } else if (code) {
                dprint("err\nRESET: ");
                state = RESET;
            }
            break;
        // after reset receive keyboard ID(2 bytes)
        case KBD_ID0:
            if (code) {
                state = KBD_ID1;
            }
            break;
        case KBD_ID1:
            if (code) {
                dprint("\nCODESET_QUERY: ");
                state = CODESET_QUERY;
            }
            break;
		case CODESET_QUERY:
			dprint("wF0 ");
			response = ps2_host_send(0xF0);
			if (response == 0xFA) {
				dprint("[ack] w00 ");
				response = ps2_host_send(0x00);
				dprint("[codeset] ");
				dprintf("%02X ", response);
				if (response == 0xFA) {
					dprint("[ack]\nCODESET_RESPONSE: ");
					state = CODESET_RESPONSE;
				} else {
					dprint("[err: ");
					dprintf("%02X", response);
					dprint("]\nRESET: ");
					state = RESET;
				}
			} else if (response == 0xFE) {
				dprint("[codeset req cmd not supported; assume ok]\nCONFIG: ");
				state = CONFIG;
			} else {
				dprint("[err: ");
				dprintf("%02X", response);
				dprint("]\nRESET: ");
				state = RESET;
			}
			break;
		case CODESET_RESPONSE:
			dprintf("%02X ", code);
			if (code == 0x03) {
                dprint("[ok]\nCONFIG: ");
                state = CONFIG;
            } else if (code == 0x02) {
                dprint("[ok]\nCODESET_REQUEST: ");
				state = CODESET_REQUEST;
			} else {
				dprint("[err]\nRESET: ");
                state = RESET;
            }
            break;
		case CODESET_REQUEST:
			dprint("wF0 ");
			response = ps2_host_send(0xF0);
			if (response == 0xFA) {
				dprint("[ack] w03 ");
				response = ps2_host_send(0x03);
				if (response == 0xFA) {
					dprint("[ok]\nCODESET_QUERY: ");
					state = CODESET_QUERY;
				} else {
					dprint("[err]\nRESET: ");
					state = RESET;
				}
			} else {
				dprint("[err]\nRESET: ");
				state = RESET;
			}
			break;
        case CONFIG:
            dprint("wF8 ");
            if (ps2_host_send(0xF8) == 0xFA) {
                dprint("[ack]\nREADY\n");
                state = READY;
            }
            break;
        case READY:
            switch (code) {
                case 0x00:
                    break;
                case 0xF0:
                    state = F0;
                    dprint(" ");
                    break;
                default:    // normal key make
                    if (code < 0x88) {
                        _make(code);
                    } else {
                        dprint("unexpected scan code at READY: "); 
                        dprintf("%02X", code); 
                        dprint("\n");
                    }
                    state = READY;
                    dprint("\n");
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
                        dprint("unexpected scan code at F0: "); 
                        dprintf("%02X", code); 
                        dprint("\n");
                    }
                    state = READY;
                    dprint("\n");
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

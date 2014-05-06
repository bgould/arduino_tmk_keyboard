#include "config.h"
#include <KeyboardFirmware.h>

BluefruitHost host;
PS2MatrixCodeset3 matrix;
static uint16_t reset_press_time = 0;

void setup() {

    pinMode(KEY_LED_PIN, INPUT);
    pinMode(PAIR_LED_PIN, INPUT);
    pinMode(PAIR_BUTTON_PIN, OUTPUT);
    pinMode(RESET_BUTTON_PIN, OUTPUT);
    pinMode(DEBUGGING_LED, OUTPUT);

    digitalWrite(PAIR_BUTTON_PIN, LOW);            // write high for 5 seconds to reset pairing
    digitalWrite(RESET_BUTTON_PIN, LOW);           // pull low to reset the bluefruit module
    digitalWrite(OUTPUT_LED_PIN, OUTPUT_LED_OFF);

#if DEBUG_ENABLE    
    debug_enable = true;
    while (!Serial) ;
#endif

    print_set_sendchar(arduino_tmk_sendchar);
    dprint("started logging\n");    
    
    digitalWrite(DEBUGGING_LED, DEBUGGING_LED_ON);
    KeyboardFirmware.begin(host, matrix);
    digitalWrite(DEBUGGING_LED, DEBUGGING_LED_OFF);
    
    digitalWrite(RESET_BUTTON_PIN, HIGH);  // turn on bluefruit
}

void loop() {

    // this the main hook into the tmk firmware that handles all the heavy lifting
    KeyboardFirmware.runTask();
    
    // Now sync the pair button light with the output pin
    if (digitalRead(PAIR_LED_PIN) == HIGH) {
        digitalWrite(OUTPUT_LED_PIN, OUTPUT_LED_ON);
    } else {
        digitalWrite(OUTPUT_LED_PIN, OUTPUT_LED_OFF);
    }
    
    // receive any messages from Bluefruit and output them if necessary
    unsigned char c;
    while (Serial1.available()) {
        c = (unsigned char) Serial1.read();
        if (debug_enable) Serial.write(c);
    }
    
    // next we'll check if the reset key was held down for 5 seconds
    if (reset_press_time && timer_elapsed(reset_press_time) > 5000) {
        dprintf("= setting reset low\n");
        digitalWrite(RESET_BUTTON_PIN, LOW);
        delay(10);
        digitalWrite(RESET_BUTTON_PIN, HIGH);
        dprintf("= restored reset high\n");
        reset_press_time = 0;
    }
    
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    bool pressed = record->event.pressed;
    dprint("== action function called"); dprintln();
    dprint("=  id:      "); debug_dec(id); dprintln();
    dprint("=  pressed: "); debug_dec(record->event.pressed); dprintln();
    if (id == 0) {
        if (pressed) {
            layer_on(1);
        } else {
            layer_clear();
        }
    } else if (id == 1) {  // bluefruit pair button
        if (pressed) {
            dprintf("= setting pair button HIGH\n");
            digitalWrite(PAIR_BUTTON_PIN, HIGH);
        } else {
            dprintf("= setting pair button LOW\n");
            digitalWrite(PAIR_BUTTON_PIN, LOW);
        }
    } else if (id == 2) {
        if (pressed) {
            if (reset_press_time == 0) {
                reset_press_time = timer_read();
            }
        } else {
            reset_press_time = 0;
        }
    }
    dprint("== end of action function\n");
}

START_KEYMAPS

KEYMAPS = {
    /* 0: default
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|BS | |Ins|Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|  +|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  #|Retu|               |  4|  5|  6|   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl|    |Alt |          Space              |Alt |    |Ctrl| |Lef|Dow|Rig| |      0|  .|   |
     * `----'    `---------------------------------------'    `----' `-----------' `---------------'
     */
    PS2_CODESET3_KEYMAP(
                     FN2, F14, F15, F16, F17, F18, F19, F20, F21, F22, PSCR,SLCK,
                     F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,

    PSCR,ESC,   GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,  INS, HOME,PGUP,  NLCK,PSLS,PAST,PMNS,
    SLCK,INT4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,  DEL, END, PGDN,  P7,  P8,  P9,  PPLS,
    PAUS,INT5,  LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NUHS,ENT,        UP,         P4,  P5,  P6,  PCMM,
    APP, INT6,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RO,  RSFT,  LEFT,PAUS,RGHT,  P1,  P2,  P3,  PENT,
    RGUI,LGUI,  FN0,      LALT,               SPC,                          RALT,     RCTL,       DOWN,       NO,  P0,  PDOT,NO
    ),
    PS2_CODESET3_KEYMAP(
                     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,

    TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  FN1, LGUI,VOLU,  TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,  FN2, APP, VOLD,  BTN1,MS_U,BTN2,TRNS,
    TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,       TRNS,       MS_L,MS_D,MS_R,TRNS,
    TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,  TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,  TRNS,     TRNS,               TRNS,                         LGUI,     APP,        TRNS,       TRNS,TRNS,TRNS,TRNS
    ),
};

FN_ACTIONS = {
    ACTION_FUNCTION(0),
    ACTION_FUNCTION(1),
    ACTION_FUNCTION(2),
};

KEYMAPS_FINISHED

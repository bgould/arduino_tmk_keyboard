#include "PS2MatrixCodeset3.h"
#include "BluefruitHost.h"
#include "SoftwareSerial.h"

extern "C" {

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
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
                     F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
                     F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,

    PSCR,ESC,   GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,  INS, HOME,PGUP,  NLCK,PSLS,PAST,PMNS,
    SLCK,INT4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,  DEL, END, PGDN,  P7,  P8,  P9,  PPLS,
    PAUS,INT5,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NUHS,ENT,        UP,         P4,  P5,  P6,  PCMM,
    APP, INT6,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RO,  RSFT,  LEFT,INT2,RGHT,  P1,  P2,  P3,  PENT,
    RGUI,LGUI,  LCTL,     LALT,               SPC,                          RALT,     RCTL,       DOWN,       NO,  P0,  PDOT,NO
    ),

};

static const uint16_t fn_actions[] PROGMEM = {
    ACTION_DEFAULT_LAYER_SET(0),
    ACTION_LAYER_MOMENTARY(1),
};

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    return action;
}


/* translates Fn keycode to action */
//action_t keymap_fn_to_action(uint8_t keycode)
//{
//    return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
//}

}

BluefruitHost host(11, 10);
PS2MatrixCodeset3 matrix;

void setup() {
  pinMode(10, INPUT_PULLUP);
  delay(2000);
  if (Serial)
    Serial.begin(57600);
#if DEBUG_ENABLE
  KeyboardDebug.println("started logging");
#endif
  KeyboardFirmware.begin(host, matrix);
}

void loop() {
    KeyboardFirmware.runTask();
}

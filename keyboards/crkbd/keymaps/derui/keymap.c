#include QMK_KEYBOARD_H
#include <stdio.h>
#include "custom_keycodes.h"
#include "next_util.h"
#include "action_util.h"

static bool is_mac = false;
static bool is_roma = true;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _GAMING 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

#define KC_GRAT LSFT(KC_DOT)
#define KC_LESS LSFT(KC_COMM)
#define KC_CLN  LSFT(KC_SCLN)

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER MO(_LOWER)
#define KC_RAISE LT(_RAISE, KC_MHEN)
#define KC_ADJUST MO(_ADJUST)
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD
#define KC_CTLTB CTL_T(KC_TAB)

#define KC_SFT_ENT LSFT_T(KC_ENT)
#define KC_SFT_SPC LSFT_T(KC_SPC)
#define KC_M_KANA M_KANA
#define KC_M_EISU M_EISU
#define KC_JARO M_JAPAN_ROMA
#define KC_JAKA M_JAPAN_KANA
#define KC_GAME M_GAMING
#define KC_EMAC M_ENABLE_MAC
#define KC_DMAC M_DISABLE_MAC
#define KC_LGS M_LSFT_LGUI
#define KC_RGS M_RSFT_RGUI
#define KC_LEISU M_LOWER_EISU
#define KC_RKANA M_RAISE_KANA
#define KC_RTAB M_RAISE_TAB
// L-Shift & L-Control
#define KC_OSMSC OSM(MOD_LSFT | MOD_LCTL)
// L-GUI & L-Alt
#define KC_OSMGA OSM(MOD_LGUI | MOD_LALT)
// L-GUI & L-Alt & L-Control
#define KC_OSMGAC OSM(MOD_LGUI | MOD_LALT | MOD_LCTL)
// L-GUI & L-Shit & L-Control
#define KC_OSMGSC OSM(MOD_LGUI | MOD_LSFT | MOD_LCTL)
// L-Alt & L-Control
#define KC_OSMAC OSM(MOD_LALT | MOD_LCTL)
// Alt & Control & GUI & Shift
#define KC_OSMHYP OSM(MOD_HYPR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LGS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_M_EISU,KC_LOWER, KC_SFT_SPC, KC_SFT_ENT, KC_RAISE, KC_M_KANA
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_M_EISU,KC_LOWER, KC_SPC,     KC_ENT,KC_RAISE, KC_M_KANA
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_F11, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX,                      XXXXXXX, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,KC_ADJUST,_______
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CTLTB, KC_EMAC, DF(_QWERTY), XXXXXXX,  KC_GRV, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_QUOT,
  //|--------+--------+--------+--------+--------,--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_DMAC, DF(_GAMING), XXXXXXX, KC_TILD, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,  KC_INS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,KC_ADJUST,_______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),


  [_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      XXXXXXX,    KC_W,    KC_E,    KC_S,    KC_B,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX,                      KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, KC_SCLN,    KC_R,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_OSMHYP,KC_OSMSC,KC_OSMGA,KC_OSMGAC,KC_OSMGSC,KC_OSMAC,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_V, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           LOWER , _______, KC_TRNS,    KC_TRNS, _______,    RAISE \
                                      //`--------------------------'  `--------------------------'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  der_init_variables();
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_GAMING 2
#define L_LOWER 4
#define L_RAISE 8
#define L_ADJUST 16

void oled_render_layer_state(void) {
  oled_write_P(PSTR("Layer: "), false);
  switch (layer_state) {
  case L_BASE:
    oled_write_ln_P(PSTR("Default"), false);
    break;
  case L_GAMING:
    oled_write_ln_P(PSTR("Gaming"), false);
    break;
  case L_LOWER:
    oled_write_ln_P(PSTR("Lower"), false);
    break;
  case L_RAISE:
    oled_write_ln_P(PSTR("Raise"), false);
    break;
  case L_ADJUST:
  case L_ADJUST|L_LOWER:
  case L_ADJUST|L_RAISE:
  case L_ADJUST|L_LOWER|L_RAISE:
    oled_write_ln_P(PSTR("Adjust"), false);
    break;
  }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
  oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
  /* Show Ctrl-Gui Swap options */
  static const char PROGMEM logo[][2][3] = {
    {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
    {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
  };
  if (status) {
    oled_write_ln_P(logo[0][0], false);
    oled_write_ln_P(logo[0][1], false);
  } else {
    oled_write_ln_P(logo[1][0], false);
    oled_write_ln_P(logo[1][1], false);
  }
}

void oled_render_logo(void) {
  static const char PROGMEM crkbd_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0};
  oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_layer_state();
    oled_render_keylog();
  } else {
    oled_render_logo();
  }
}

#endif // OLED_DRIVER_ENABLE

static bool interrupt_in_layer = false;
static bool enable_lalt = false;
static bool enable_lgui = false;
static bool enable_lower = false;
static bool enable_raise = false;

void der_switch_to_kana(void) {
  SEND_STRING(SS_TAP(X_INT4));
  SEND_STRING(SS_TAP(X_LANG1));
  if (!is_roma) {
    layer_on(_GAMING);
  }
  der_init_variables();
}

void der_switch_to_eisu(void) {
  SEND_STRING(SS_TAP(X_INT5));
  SEND_STRING(SS_TAP(X_LANG2));
  if (!is_roma) {
    layer_off(_GAMING);
  }
  der_init_variables();
}

bool der_is_special_key(uint16_t keycode) {
  switch(keycode) {
  case M_JAPAN_ROMA:
  case M_JAPAN_KANA:
  case M_ENABLE_MAC:
  case M_DISABLE_MAC:
  case M_LSFT_LGUI:
  case M_RSFT_RGUI:
  case M_LOWER_EISU:
  case M_EISU:
  case M_RAISE_KANA:
  case M_KANA:
  case M_RAISE_TAB:
    return true;
  default:
    break;
  }

  return false;
}

bool der_is_any_flag_enabled(void) {
  return enable_lalt || enable_lgui || enable_lower || enable_raise;
}

void der_register_special_mod(void) {
  if (interrupt_in_layer) {
    if (enable_lalt) {
      register_mods(MOD_LALT);
    }

    if (enable_lgui) {
      register_mods(MOD_LGUI);
    }

    if (enable_lower) {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }

    if (enable_raise) {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
  }
}

void der_unregister_special_mod(void) {
  if (interrupt_in_layer) {
    if (!enable_lalt) {
      unregister_mods(MOD_LALT);
    }

    if (!enable_lgui) {
      unregister_mods(MOD_LGUI);
    }

    if (!enable_lower) {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }

    if (!enable_raise) {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
  }
}

bool der_press_special_key(uint16_t keycode) {
  if (der_is_any_flag_enabled()) {
    interrupt_in_layer = true;
    der_register_special_mod();
  }

  switch(keycode) {
  case M_JAPAN_ROMA:
    is_roma = true;
    default_layer_set(_QWERTY);
    break;
  case M_JAPAN_KANA:
    is_roma = false;
    break;
  case M_ENABLE_MAC:
    is_mac = true;
    break;
  case M_DISABLE_MAC:
    is_mac = false;
    break;
  case M_GAMING:
    default_layer_set(_GAMING);
    break;
  case M_LSFT_LGUI:
  case M_RSFT_RGUI:
    if (is_mac) {
      register_mods(MOD_LGUI);
    } else {
      register_mods(MOD_LSFT);
    }
    break;
  case M_LOWER_EISU:
    enable_lower = true;
    break;
  case M_EISU:
    enable_lalt = true;
    break;
  case M_RAISE_TAB:
  case M_RAISE_KANA:
    enable_raise = true;
    break;
  case M_KANA:
    enable_lgui = true;
    break;
  default:
    break;
  }

  der_register_special_mod();

  if (der_is_special_key(keycode)) {
    return false;
  }

  return true;
}


bool der_release_special_key(uint16_t keycode) {
  switch(keycode) {
  case M_LSFT_LGUI:
  case M_RSFT_RGUI:
    if (is_mac) {
      unregister_mods(MOD_LGUI);
    } else {
      unregister_mods(MOD_LSFT);
    }
    break;
  case M_LOWER_EISU:
    if (enable_lower && !interrupt_in_layer) {
      /* KC_MHEN equals KC_INT5 */
      der_switch_to_eisu();
    }

    enable_lower = false;
    break;
  case M_EISU:
    if (enable_lalt && !interrupt_in_layer) {
      /* KC_MHEN equals KC_INT5 */
      der_switch_to_eisu();
    }

    enable_lalt = false;
    break;
  case M_RAISE_TAB:

    if (enable_raise && !interrupt_in_layer) {
      tap_code(KC_TAB);
    }

    enable_raise = false;
    break;
  case M_RAISE_KANA:

    if (enable_raise && !interrupt_in_layer) {
      /* KC_HENK equals KC_INT4 */
      der_switch_to_kana();
    }

    enable_raise = false;
    break;
  case M_KANA:
    if (enable_lgui && !interrupt_in_layer) {
      /* KC_HENK equals KC_INT4 */
      der_switch_to_kana();
    }

    enable_lgui = false;
    break;
  default:
    break;
  }

  if (!der_is_any_flag_enabled()) {
    der_unregister_special_mod();
    interrupt_in_layer = false;
  }

  if (der_is_special_key(keycode)) {
    return false;
  }

  return true;
}

bool process_record_derui(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
    return der_press_special_key(keycode);
  } else {
    return der_release_special_key(keycode);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
  }

  if (!process_record_derui(keycode, record)) {
    return false;
  }

  if (!is_roma && !has_anymod()) {
    switch (layer_state) {
    case (1 << _GAMING):
      return der_process_nn(keycode, record); break;
    default:
      break;
    }
  }

  return true;
}

/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "custom_keycodes.h"
#include "next_util.h"
#include "action_util.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _GAMING,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define KC_GRAT LSFT(KC_DOT)
#define KC_LESS LSFT(KC_COMM)
#define KC_CLN  LSFT(KC_SCLN)

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER MO(_LOWER)
#define KC_RAISE LT(_RAISE, KC_INT5)
#define KC_ADJUST MO(_ADJUST)
#define KC_RST   QK_BOOT
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
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LGS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                KC_M_EISU,KC_LOWER,KC_SFT_SPC, _______,  _______, KC_SFT_ENT, KC_RAISE, KC_M_KANA
    //                        `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_GAMING] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                KC_M_EISU,KC_LOWER,KC_SPC, _______,  _______, KC_ENT, KC_RAISE, KC_M_KANA
    //                        `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_F11, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX,                      XXXXXXX, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                _______, _______,  _______, _______,   _______,  _______, KC_ADJUST,  _______
    //                        `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CTLTB, KC_EMAC, DF(_QWERTY), XXXXXXX,  KC_GRV, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_QUOT,
  //|--------+--------+--------+--------+--------,--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_DMAC, DF(_GAMING), XXXXXXX, KC_TILD, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,  KC_INS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 _______, KC_ADJUST, _______, _______,   _______,  _______, _______,  _______
     //                        `--------+--------+--------+--------'  `--------+--------+--------+--------'
  ),


  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_RST ,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      XXXXXXX,    KC_W,    KC_E,    KC_S,    KC_B,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX,                      KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, KC_SCLN,    KC_R,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_OSMHYP,KC_OSMSC,KC_OSMGA,KC_OSMGAC,KC_OSMGSC,KC_OSMAC,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_V, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                LOWER,    _______, KC_TRNS, _______,   _______,  KC_TRNS, _______,  RAISE
     //                        `--------+--------+--------+--------'  `--------+--------+--------+--------'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  der_init_variables();
}

static bool interrupt_in_layer = false;
static bool enable_lalt = false;
static bool enable_lgui = false;
static bool enable_lower = false;
static bool enable_raise = false;
static bool is_mac = false;
static bool is_roma = true;

void der_switch_to_kana(void) {
  SEND_STRING(SS_TAP(X_INT4));
  SEND_STRING(SS_TAP(X_LNG1));

  if (!is_roma) {
    layer_on(_GAMING);
  }

  der_init_variables();
}

void der_switch_to_eisu(void) {
  SEND_STRING(SS_TAP(X_INT5));
  SEND_STRING(SS_TAP(X_LNG2));

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

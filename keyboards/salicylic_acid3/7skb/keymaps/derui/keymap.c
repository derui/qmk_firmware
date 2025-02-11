#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "custom_key_handling.h"
#include "keymap_japanese.h"
#include "custom_keys.h"
#include "keymap_8x3.h"

#define KC_ELSFT M_LSFTESC
#define KC_LOWER M_LOWER
#define KC_RAISE M_RAISE
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _KANA,
  _MAC,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      M_CTLTB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,KC_ENTER,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
    M_LSFTESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, MO(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LGUI, KC_LALT,  KC_LOWER,        M_SPACE,     M_ENTER,         KC_RAISE, KC_RALT, KC_RGUI
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_KANA] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      M_CTLTB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,KC_ENTER,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
    M_LSFTESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, MO(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LGUI, KC_LALT, M_LOWER,     M_KANA_SHIFT,    M_KANA_SHIFT,     KC_RAISE, KC_RALT, KC_RGUI
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_MAC] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______,_______,  _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LALT, KC_LGUI, _______,          _______,     _______,          _______, KC_RGUI, KC_RALT
          //`---------------------------------------------|   |--------------------------------------------'
   ),

    [_LOWER] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,  _______,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, KC_LBRC, KC_RBRC, _______, _______,     _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______,          _______,     _______,          _______, _______, _______
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, KC_MINS, KC_UNDS, KC_EQUAL, _______, _______, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     KC_BSPC, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, KC_PLUS, KC_PIPE, KC_BSLS,  KC_GRV, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______,              _______, _______,          _______, _______ 
          //`---------------------------------------------|   |--------------------------------------------'
  ),
  [_ADJUST] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______, _______,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,       KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______,     KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______,              _______, _______,          _______, _______ 
          //`---------------------------------------------|   |--------------------------------------------'
  ),
  [_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      QK_BOOT, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,TG(_MAC),  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, KC_PSCR, KC_SCRL,KC_PAUSE,   KC_UP, _______,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, KC_HOME, KC_PGUP, KC_LEFT,KC_RIGHT, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______,  KC_END, KC_PGDN, KC_DOWN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______,              _______, _______,          KC_STOP, _______ 
          //`---------------------------------------------|   |--------------------------------------------'
  )
};


//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _FN:
      rgblight_sethsv_at(HSV_GOLD, 0);
      break;
    case _MAC:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    case _LOWER:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case _RAISE:
      rgblight_sethsv_at(HSV_RED, 0);
      break;
    case _ADJUST:
      rgblight_sethsv_at(HSV_GREEN, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at( 0, 0, 0, 0);
      break;
    }
    rgblight_set_effect_range(1, 11);
#endif
return state;
}

int RGB_current_mode;
bool kana_mode = false;

// my configurations
void tapped_kc_raise() {
  SEND_STRING(SS_TAP(X_INT4));
  SEND_STRING(SS_TAP(X_LNG1));
  layer_on(_KANA);
  kana_mode = true;
}

void interrupted_kc_raise() {
  layer_on(_RAISE);
  update_tri_layer(_LOWER, _RAISE, _ADJUST);
}

void release_holding_kc_raise() {
  layer_off(_RAISE);
  update_tri_layer(_LOWER, _RAISE, _ADJUST);
}

void tapped_kc_lower() {
  SEND_STRING(SS_TAP(X_INT5));
  SEND_STRING(SS_TAP(X_LNG2));
  layer_off(_KANA);
  kana_mode = false;
}

void interrupted_kc_lower() {
  layer_on(_LOWER);
  update_tri_layer(_LOWER, _RAISE, _ADJUST);
}

void release_holding_kc_lower() {
  layer_off(_LOWER);
  update_tri_layer(_LOWER, _RAISE, _ADJUST);
}

void tapped_m_ctltb() {
  tap_code(KC_TAB);
}

void interrupted_m_ctltb() {
  register_code(KC_LCTL);
}

void release_holding_m_ctltb() {
  unregister_code(KC_LCTL);
}

void tapped_m_enter() {
  tap_code(KC_ENTER);
}

void tapped_m_space() {
  tap_code(KC_SPACE);
}

void interrupted_m_space() {
  register_code(KC_LSFT);
}

void release_holding_m_space() {
  unregister_code(KC_LSFT);
}

void tapped_m_lsftesc() {
  tap_code(KC_ESC);
}

void interrupted_m_lsftesc() {
  register_code(KC_LSFT);
}

void release_holding_m_lsftesc() {
  unregister_code(KC_LSFT);
}


custom_key_t m_ctltb = {
  M_CTLTB,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_m_ctltb,
  .on_interrupted = interrupted_m_ctltb,
  .on_start_holding = interrupted_m_ctltb,
  .on_release_holding = release_holding_m_ctltb,
};

custom_key_t kc_raise = {
  KC_RAISE,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_kc_raise,
  .on_interrupted = interrupted_kc_raise,
  .on_start_holding = interrupted_kc_raise,
  .on_release_holding = release_holding_kc_raise,
};

custom_key_t kc_lower = {
  KC_LOWER,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_kc_lower,
  .on_interrupted = interrupted_kc_lower,
  .on_start_holding = interrupted_kc_lower,
  .on_release_holding = release_holding_kc_lower,
};

custom_key_t m_enter = {
  M_ENTER,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_m_enter,
  .on_interrupted = interrupted_m_space,
  .on_start_holding = interrupted_m_space,
  .on_release_holding = release_holding_m_space,
};

custom_key_t m_space = {
  M_SPACE,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_m_space,
  .on_interrupted = interrupted_m_space,
  .on_start_holding = interrupted_m_space,
  .on_release_holding = release_holding_m_space,
};

custom_key_t m_lsftesc = {
  M_LSFTESC,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_m_lsftesc,
  .on_interrupted = interrupted_m_lsftesc,
  .on_start_holding = interrupted_m_lsftesc,
  .on_release_holding = release_holding_m_lsftesc,
};

int all_defined_key_count = 6;
custom_key_t *local_keys[] = {
  &kc_lower,
  &kc_raise,
  &m_ctltb,
  &m_enter,
  &m_lsftesc,
  &m_space,
};
custom_key_t **defined_keys = local_keys;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  if (!process_record_derui(keycode, record)) {
    return false;
  }

  /* when kana_mode enabled, all keys handling on user's process */
  if (kana_mode && !has_anymod()) {
    result = process_record_ng(keycode, record);
  }

  return result;
}

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "custom_key_handling.h"
#include "custom_keys.h"
#include "ng_layer.h"
#include "layer.h"

// my configurations
void tapped_kc_raise() {
  SEND_STRING(SS_TAP(X_INT4));
  SEND_STRING(SS_TAP(X_LNG1));

  if (ng_is_enabled()) {
    SEND_STRING(SS_TAP(X_SCLN));
  }
  
  ng_enable();

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
  ng_disable();
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
  if (ng_is_enabled()) {
    return;
  }
  tap_code(KC_ENTER);
}

void tapped_m_space() {
  if (ng_is_enabled()) {
    return;
  }
  tap_code(KC_SPACE);
}

void interrupted_m_space() {
  if (ng_is_enabled()) {
    return;
  }
  register_code(KC_LSFT);
}

void release_holding_m_space() {
  if (ng_is_enabled()) {
    return;
  }
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

void tapped_m_rsftesc() {
  tap_code(KC_ESC);
}

void interrupted_m_rsftesc() {
  register_code(KC_RSFT);
}

void release_holding_m_rsftesc() {
  unregister_code(KC_RSFT);
}

void tapped_m_qwerty() {
  layer_on(_QWERTY);
  layer_off(_STURDY);
  ng_set_qwerty_mode();
}

void tapped_m_sturdy() {
  layer_on(_STURDY);
  layer_off(_QWERTY);
  ng_set_sturdy_mode();
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
  M_RAISE,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_kc_raise,
  .on_interrupted = interrupted_kc_raise,
  .on_start_holding = interrupted_kc_raise,
  .on_release_holding = release_holding_kc_raise,
};

custom_key_t kc_lower = {
  M_LOWER,
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

custom_key_t m_rsftesc = {
  M_RSFTESC,  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_m_rsftesc,
  .on_interrupted = interrupted_m_rsftesc,
  .on_start_holding = interrupted_m_rsftesc,
  .on_release_holding = release_holding_m_rsftesc,
};

custom_key_t m_qwerty = {
  M_QWERTY,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_m_qwerty,
  .on_interrupted = der_nop,
  .on_start_holding = der_nop,
  .on_release_holding = der_nop,
};

custom_key_t m_sturdy = {
  M_STURDY,
  RELEASED,
  0,
  .on_pressed = der_nop,
  .on_tapped = tapped_m_sturdy,
  .on_interrupted = der_nop,
  .on_start_holding = der_nop,
  .on_release_holding = der_nop,
};

int all_defined_key_count = 9;
custom_key_t *local_keys[] = {
  &kc_lower,
  &kc_raise,
  &m_ctltb,
  &m_enter,
  &m_lsftesc,
  &m_rsftesc,
  &m_space,
  &m_qwerty,
  &m_sturdy
};
custom_key_t **defined_keys = local_keys;

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "custom_key_handling.h"
#include "keymap_japanese.h"
#include "custom_keys.h"
#include "ng_layer.h"
#include "layer.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  M_CTLTB,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  M_LSFTESC,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, M_RSFTESC,
                        KC_LGUI, KC_LALT, M_LOWER, M_SPACE, M_ENTER, M_RAISE, KC_RGUI, KC_RALT
),
[_MAC] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, KC_LGUI, _______, _______, _______,  _______, KC_RALT, KC_RGUI
),
[_LOWER] = LAYOUT(
  _______,  _______, _______, _______, _______, _______,                     _______, _______, _______,_______, _______, KC_INS,
  _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   _______, _______, _______,_______, _______, _______,
  _______, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, KC_LPRN,                   _______, _______, _______,_______, _______, _______,
  _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_RPRN, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______,                     KC_MINS, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_PIPE,
  _______, _______, _______, _______, _______, _______,  _______, _______,   KC_GRV,  KC_EQL, KC_UNDS, KC_PLUS, KC_BSLS, _______,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
  [_ADJUST] = LAYOUT(
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_MAC),
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_F1,   KC_F2,   KC_F3, KC_F4,    KC_F5,   KC_DEL,
  XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, KC_F11,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F6,   KC_F7,   KC_F8, KC_F9,    KC_F10,  KC_F12,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
void render_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    /* oled_write_ln(read_keylog(), false); */
    /* oled_write_ln(read_keylogs(), false); */
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    render_logo();
  }
  
  return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = true;

  if (!process_record_derui(keycode, record)) {
    return false;
  }

  /* かなは、他のレイヤーが有効ではないときにだけにしておく */
  uint16_t current_layer = get_highest_layer(layer_state);
  if (!has_anymod() && (current_layer == _QWERTY || current_layer == _MAC) && ng_is_enabled()) {
    result = process_record_ng(keycode, record);
  }

  return result;
}

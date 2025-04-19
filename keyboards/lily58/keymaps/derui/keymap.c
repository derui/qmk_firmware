#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "custom_key_handling.h"
#include "keymap_japanese.h"
#include "custom_keys.h"
#include "ng_layer.h"
#include "layer.h"
#include "kana.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_BASE] = LAYOUT(
  KC_ESC,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TAB,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  M_CTLTB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  M_LSFTESC,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(_RAISE),
                              KC_LGUI, KC_LALT, M_LOWER, M_SPACE, M_ENTER, M_RAISE, KC_RGUI, KC_RALT
),
 [_QWERTY] = LAYOUT(
  _______, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  _______, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  _______, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  _______, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______
),
 /* The gallium layout https://github.com/GalileoBlues/Gallium */
 [_GALLIUM] = LAYOUT(
  _______, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  _______, KC_B,   KC_L,    KC_D,    KC_C,    KC_V,                     KC_J,    KC_F,    KC_O,    KC_U,    KC_COMM, KC_BSPC,
  _______, KC_N,   KC_R,    KC_T,    KC_S,    KC_G,                     KC_Y,    KC_H,    KC_A,    KC_E,    KC_I,    KC_SLSH,
  _______, KC_X,   KC_Q,    KC_M,    KC_W,    KC_Z, KC_LBRC,  KC_RBRC,  KC_K,    KC_P,    KC_QUOT, KC_SCLN, KC_DOT,  _______,
                        _______, _______, _______, _______, _______, _______, _______, _______
),
 [_JAPANESE] = LAYOUT(
  _______, KC_1,  KC_2,   KC_3,   KC_4,   KC_5,                    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_GRV,
  _______, N_Q,   N_W,    N_E,    N_R,    N_T,                     N_Y,    N_U,    N_I,    N_O,    N_P,    _______,
  _______, N_A,   N_S,    N_D,    N_F,    N_G,                     N_H,    N_J,    N_K,    N_L,    N_SCLN, _______,
  _______, N_Z,   N_X,    N_C,    N_V,    N_B,  _______, _______,  N_N,    N_M,    N_COMM, N_DOT,  N_SLSH, _______,
                      _______, _______, _______, N_SPACE, M_ENTER, _______, _______, _______
),
[_MAC] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, KC_LGUI, _______, _______, _______, _______, KC_RALT, KC_RGUI
),
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_INS,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     _______, _______, _______, _______, _______, _______,
  _______, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, KC_LBRC, KC_LABK, KC_SLSH, KC_RABK, KC_RBRC,                    _______, KC_MINS, KC_EQL,  KC_GRV,  KC_PIPE, _______,
  _______, _______, KC_LCBR, _______, KC_RCBR, _______,  _______, _______, _______, KC_UNDS, KC_PLUS, KC_TILD, KC_BSLS, _______,
                             _______, _______, _______,  _______, _______, _______, _______, _______
),
  [_ADJUST] = LAYOUT(
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, M_QWERTY, M_GALLIUM , TG(_MAC),
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_F1,   KC_F2,   KC_UP,   KC_F3,    KC_F4,   KC_DEL,
  XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX,                   KC_F5,   KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, KC_F11,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F12,
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
  if (!process_record_derui(keycode, record)) {
    return false;
  }

  if (!der_process_record_kana(keycode, record)) {
    return false;
  }

  return true;
}

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "next_util.h"
#include "keymap_japanese.h"

#define KC_SFT_ENT LSFT_T(KC_ENT)
#define KC_SFT_SPC LSFT_T(KC_SPC)
#define KC_M_KANA M_KANA
#define KC_M_EISU M_EISU
#define KC_LEISU M_LOWER_EISU
#define KC_RKANA M_RAISE_KANA
#define KC_LOWER LT(MO(_LOWER), KC_ESC)
#define KC_RAISE LT(MO(_RAISE), KC_ESC)

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
  _FN,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC, MO(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LGUI, KC_M_EISU,  KC_LOWER,   KC_SFT_SPC,  KC_SFT_ENT,  KC_RAISE,     KC_M_KANA, KC_RGUI 
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TG(_ADJUST),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, KC_PSCR, KC_SCRL,KC_PAUSE,   KC_UP, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, KC_HOME, KC_PGUP, KC_LEFT,KC_RIGHT, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______,  KC_END, KC_PGDN, KC_DOWN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______,              _______, _______,          KC_STOP, _______ 
          //`---------------------------------------------|   |--------------------------------------------'
  ),
    [_LOWER] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______,KC_LOWER, _______,            _______, KC_RAISE,    _______, _______ 
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     _______, _______, _______, _______, _______, _______, _______,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______,              _______, _______,          _______, _______ 
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_ADJUST] = LAYOUT( /* Base */
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TG(_ADJUST), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX,          KC_STOP, XXXXXXX 
          //`---------------------------------------------|   |--------------------------------------------'
  )
};


//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _FN:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case _LOWER:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case _RAISE:
      rgblight_sethsv_at(HSV_RED, 0);
      break;
    case _ADJUST:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at( 0, 0, 0, 0);
      break;
    }
    rgblight_set_effect_range( 1, 11);
#endif
return state;
}

int RGB_current_mode;

// my configurations
void matrix_init_user(void) {
}

static bool interrupt_in_layer = false;
static bool enable_lalt = false;
static bool enable_lower = false;
static bool enable_raise = false;
static bool is_mac = false;
static bool is_roma = true;

void der_switch_to_kana(void) {
  SEND_STRING(SS_TAP(X_INT4));
  SEND_STRING(SS_TAP(X_LNG1));
}

void der_switch_to_eisu(void) {
  SEND_STRING(SS_TAP(X_INT5));
  SEND_STRING(SS_TAP(X_LNG2));
}

bool der_is_special_key(uint16_t keycode) {
  switch(keycode) {
  case M_JAPAN_ROMA:
  case M_JAPAN_KANA:
  case M_ENABLE_MAC:
  case M_DISABLE_MAC:
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
  return enable_lalt || enable_lower || enable_raise;
}

void der_register_special_mod(void) {
  if (interrupt_in_layer) {
    if (enable_lalt) {
      register_mods(MOD_LALT);
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
  case M_LOWER_EISU:
    enable_lower = true;
    break;
  case M_EISU:
  case M_KANA:
    enable_lalt = true;
    break;
  case M_RAISE_TAB:
  case M_RAISE_KANA:
    enable_raise = true;
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
  case M_KANA:
    if (enable_lalt && !interrupt_in_layer) {
      /* KC_MHEN equals KC_INT5 */
      der_switch_to_kana();
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

  return result;
}

#include QMK_KEYBOARD_H
#include "./custom_keycodes.h"
#include "./custom_key_handling.h"

/* provide default no-op handler */
void der_nop(void) {}

/* defined keys */

void matrix_scan_user(void) {
  for (int i = 0; i < all_defined_key_count;i++) {
    custom_key_t* key = defined_keys[i];
    if (key->key_state == PRESSED) {
      if (timer_elapsed(key->pressed_timer) > TAPPING_TERM) {
        key->on_start_holding();
        key->key_state = HOLDING;
      }
    }
  }
}

bool process_record_derui(uint16_t keycode, keyrecord_t *record) {
  for (int i = 0; i < all_defined_key_count;i++) {
    custom_key_t* key = defined_keys[i];
    
    if (key->custom_keycode == keycode) {
      if (record->event.pressed) {
          key->key_state = PRESSED;
          key->pressed_timer = timer_read();
          key->on_pressed();
      } else {
          if (key->key_state == PRESSED) {
            if (timer_elapsed(key->pressed_timer) < TAPPING_TERM) {
              key->on_tapped();
            }
          } else if (key->key_state == HOLDING) {
            key->on_release_holding();
          }
          key->key_state = RELEASED;
      }
    } else {
      if (key->key_state == PRESSED && record->event.pressed) {
        key->on_interrupted();

        /* change state if it interrupted. */
        key->key_state = HOLDING;
      }
    }
  }

  return true;
}

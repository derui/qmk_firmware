#ifndef CONFIG_DERUI_NEXT_UTIL_H
#define CONFIG_DERUI_NEXT_UTIL_H

enum key_state {
  PRESSED,
  RELEASED,
  HOLDING,
};

typedef struct {
  enum custom_keycodes custom_keycode;
  enum key_state key_state;
  uint16_t pressed_timer;

  /* invoke on key pressed */
  void (* on_pressed)(void);
  /* invoke on key tapped */
  void (* on_tapped)(void);
  /* invoke on interrupted other key pressed while this key pressed */
  void (* on_interrupted)(void);
  /* invoke on release holding key is released. Holding state is activated after interrupted */
  void (* on_release_holding)(void);
} custom_key_t;

int all_defined_key_count;
custom_key_t** defined_keys;

void der_nop(void);
bool process_record_derui(uint16_t keycode, keyrecord_t *record);

#endif

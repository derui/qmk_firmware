#ifndef CONFIG_DERUI_KEYMAP_8X3_H
#define CONFIG_DERUI_KEYMAP_8X3_H

enum shift_state {
  NO_SHIFT,
  REDUCING,
};

/* シフトキーを定義する構造体。 */
typedef struct {
  uint16_t keycodes[2];
  enum shift_state shift_state;
  const char* sequence;
} shift_definition_t;

/* 単打を定義する構造体 */
typedef struct {
  uint16_t keycode;
  enum key_state tap_state;
  const char* sequence;
} single_tap_definition_t;

void reset_states_8x3(void);
bool process_record_8x3(uint16_t keycode, keyrecord_t *record);

#endif

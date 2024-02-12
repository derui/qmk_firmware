#ifndef CONFIG_DERUI_KEYMAP_8X3_H
#define CONFIG_DERUI_KEYMAP_8X3_H

enum ng_key {
  N_A = 1,
  N_B,
  N_C,
  N_D,
  N_E,
  N_F,
  N_G,
  N_H,
  N_I,
  N_J,
  N_K,
  N_L,
  N_M,
  N_N,
  N_O,
  N_P,
  N_Q,
  N_R,
  N_S,
  N_T,
  N_U,
  N_V,
  N_W,
  N_X,
  N_Y,
  N_Z,
  N_COMM,
  N_DOT,
  N_SLSH,
  N_SCLN,
  N_SFT,
  N_UNKNOWN
};

/* シフトキーを定義する構造体。 */
typedef struct {
  /* LSB is shift mark. */
  uint16_t keycodes;
  const char* sequence;
} seq_definition_t;

void ng_reset_state(void);
bool process_record_ng(uint16_t keycode, keyrecord_t *record);

#endif

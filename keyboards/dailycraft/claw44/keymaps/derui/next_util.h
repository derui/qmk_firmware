#ifndef CONFIG_DERUI_NEXT_UTIL_H
#define CONFIG_DERUI_NEXT_UTIL_H

#define KC_M_KANA M_KANA
#define KC_M_EISU M_EISU

void der_init_variables(void);
bool der_is_any_key_pressed(void);
bool der_is_shifting_repeated(void);
bool der_is_key_pressed(uint8_t key);
bool der_process_nn(uint16_t keycode, keyrecord_t *record);
void der_update_timer(void);
bool der_is_shifting(void);

#endif

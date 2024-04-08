#ifndef CONFIG_DERUI_NG_LAYER_H
#define CONFIG_DERUI_NG_LAYER_H

void ng_reset_state(void);

bool ng_is_enabled(void);
void ng_enable(void);
void ng_disable(void);

bool process_record_ng(uint16_t keycode, keyrecord_t *record);

#endif

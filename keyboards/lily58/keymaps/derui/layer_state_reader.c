#include "quantum.h"
#include <stdio.h>

#define L_BASE 0
#define L_STURDY (1 << 1)
#define L_MAC (1 << 2)
#define L_LOWER (1 << 3)
#define L_RAISE (1 << 4)
#define L_ADJUST (1 << 5)
#define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)
#define L_STURDY_MAC (L_STURDY | L_MAC)

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: qwerty");
    break;
  case L_MAC:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: qwerty+mac");
    break;
  case L_STURDY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: sturdy");
    break;
  case L_STURDY_MAC:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: sturdy+mac");
    break;
  case L_RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case L_ADJUST:
  case L_ADJUST_TRI:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%u", layer_state);
  }

  return layer_state_str;
}

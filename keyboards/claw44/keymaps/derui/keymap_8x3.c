#include QMK_KEYBOARD_H
#include <string.h>
#include "custom_keycodes.h"
#include "next_util.h"

#define NN_COMBINATION_NOT_FOUND -1

/*******
        Definitions for NAGINATA-STYLE arrays
 *******/
/*
  Implementation memo for hachimitsu-koume layout.

  1. Time-base and pressed only detection
  2. Time-base and pressed and released detection
  3. No time-base and pressed and released detection

  If choose 1., this method has one advantage that is more simple 2. . But this method will cause more longer time to show character.
  If choose 2., this method has detail control between other methods. But this method will be more complex of implementation.
  If choose 3., this method will need large configuration for layout, But this method implementation will be more simply than other methods.
 */
enum der_nn_keys {
  NN_NO = 0x00,
  NN_A,
  NN_B,
  NN_C,
  NN_D,
  NN_E,
  NN_F,
  NN_G,
  NN_H,
  NN_I,
  NN_J,
  NN_K,
  NN_L,
  NN_M,               /* 0x10 */
  NN_N,
  NN_O,
  NN_P,
  NN_Q,
  NN_R,
  NN_S,
  NN_T,
  NN_U,
  NN_V,
  NN_W,
  NN_X,
  NN_Y,
  NN_Z,
  NN_SCOLON,          /* ; and : */
  NN_SQ,          /* ' and " */
  NN_COMMA,           /* , and < */
  NN_DOT,             /* . and > */
  NN_SLASH,           /* / and ? */
  NN_LEFT_SHIFT,
  NN_RIGHT_SHIFT,
  NN_LAST_RANGE,
};


/* variables to implement same-key shift */
static uint8_t nn_pressed[2] = {NN_NO};
static uint8_t nn_pressed_key_count = 0;
const static uint8_t nn_max_combination = 2;

/* key sequence mapped keycode what is shifted  */
typedef struct {
  uint8_t key_combo[2];
  char key_sequence[4];
} der_nn_key_combination_t;

/* Define keycode and sequence when some key shifted */
const der_nn_key_combination_t PROGMEM der_nn_key_combinations[] =
  {
   /* left hand */
   /* qwert */

   /* Q */
   {.key_combo = {NN_Q, NN_NO}, .key_sequence = "."},
   {.key_combo = {NN_Q, NN_LEFT_SHIFT}, .key_sequence = "pe"},
   {.key_combo = {NN_Q, NN_RIGHT_SHIFT}, .key_sequence = "pa"},

   /* W */
   {.key_combo = {NN_W, NN_NO}, .key_sequence = "na"},
   {.key_combo = {NN_W, NN_LEFT_SHIFT}, .key_sequence = "ke"},
   {.key_combo = {NN_W, NN_RIGHT_SHIFT}, .key_sequence = "ge"},

  /* E */
   {.key_combo = {NN_E, NN_NO}, .key_sequence = "te"},
   {.key_combo = {NN_E, NN_LEFT_SHIFT}, .key_sequence = "yo"},
   {.key_combo = {NN_E, NN_RIGHT_SHIFT}, .key_sequence = "de"},

  /* R */
   {.key_combo = {NN_R, NN_NO}, .key_sequence = "se"},
   {.key_combo = {NN_R, NN_LEFT_SHIFT}, .key_sequence = "pi"},
   {.key_combo = {NN_R, NN_RIGHT_SHIFT}, .key_sequence = "ze"},

  /* T */
   {.key_combo = {NN_T, NN_NO}, .key_sequence = "so"},
   {.key_combo = {NN_T, NN_RIGHT_SHIFT}, .key_sequence = "zo"},


  /* asdfg */

   /* A */
   {.key_combo = {NN_A, NN_NO}, .key_sequence = "ko"},
   {.key_combo = {NN_A, NN_LEFT_SHIFT}, .key_sequence = "me"},
   {.key_combo = {NN_A, NN_RIGHT_SHIFT}, .key_sequence = "me"},

   /* S */
   {.key_combo = {NN_S, NN_NO}, .key_sequence = "ta"},
   {.key_combo = {NN_S, NN_LEFT_SHIFT}, .key_sequence = "ya"},
   {.key_combo = {NN_S, NN_RIGHT_SHIFT}, .key_sequence = "da"},

  /* D */
   {.key_combo = {NN_D, NN_NO}, .key_sequence = "ka"},
   {.key_combo = {NN_D, NN_LEFT_SHIFT}, .key_sequence = "mo"},
   {.key_combo = {NN_D, NN_RIGHT_SHIFT}, .key_sequence = "ga"},

  /* F */
   {.key_combo = {NN_F, NN_NO}, .key_sequence = "ru"},
   {.key_combo = {NN_F, NN_LEFT_SHIFT}, .key_sequence = "sa"},
   {.key_combo = {NN_F, NN_RIGHT_SHIFT}, .key_sequence = "za"},

  /* G */
   {.key_combo = {NN_G, NN_NO}, .key_sequence = "ha"},
   {.key_combo = {NN_G, NN_LEFT_SHIFT}, .key_sequence = "xu"},
   {.key_combo = {NN_G, NN_RIGHT_SHIFT}, .key_sequence = "ba"},

  /* zxcvb */

   /* Z */
   {.key_combo = {NN_Z, NN_NO}, .key_sequence = "yu"},
   {.key_combo = {NN_Z, NN_LEFT_SHIFT}, .key_sequence = "xyu"},
   {.key_combo = {NN_Z, NN_RIGHT_SHIFT}, .key_sequence = "po"},

   /* X */
   {.key_combo = {NN_X, NN_NO}, .key_sequence = "ho"},
   {.key_combo = {NN_X, NN_LEFT_SHIFT}, .key_sequence = "xya"},
   {.key_combo = {NN_X, NN_RIGHT_SHIFT}, .key_sequence = "bo"},

   /* C */
   {.key_combo = {NN_C, NN_NO}, .key_sequence = "ma"},
   {.key_combo = {NN_C, NN_LEFT_SHIFT}, .key_sequence = "hu"},
   {.key_combo = {NN_C, NN_RIGHT_SHIFT}, .key_sequence = "bu"},

   /* V */
   {.key_combo = {NN_V, NN_NO}, .key_sequence = "ro"},
   {.key_combo = {NN_V, NN_LEFT_SHIFT}, .key_sequence = "xyo"},
   {.key_combo = {NN_V, NN_RIGHT_SHIFT}, .key_sequence = "pu"},

   /* B */
   {.key_combo = {NN_B, NN_NO}, .key_sequence = "ma"},
   {.key_combo = {NN_B, NN_LEFT_SHIFT}, .key_sequence = "xo"},
   {.key_combo = {NN_B, NN_RIGHT_SHIFT}, .key_sequence = "ba"},

   /* right hand */
   /* yuiop */

   /* NN_Y */
   {.key_combo = {NN_Y, NN_NO}, .key_sequence = "/"},

   /* NN_U */
   {.key_combo = {NN_U, NN_NO}, .key_sequence = "o"},
   {.key_combo = {NN_U, NN_LEFT_SHIFT}, .key_sequence = "bi"},
   {.key_combo = {NN_U, NN_RIGHT_SHIFT}, .key_sequence = "hi"},

   /* NN_I */
   {.key_combo = {NN_I, NN_NO}, .key_sequence = "no"},
   {.key_combo = {NN_I, NN_LEFT_SHIFT}, .key_sequence = "gi"},
   {.key_combo = {NN_I, NN_RIGHT_SHIFT}, .key_sequence = "ki"},

   /* NN_O */
   {.key_combo = {NN_O, NN_NO}, .key_sequence = "ni"},
   {.key_combo = {NN_O, NN_LEFT_SHIFT}, .key_sequence = "du"},
   {.key_combo = {NN_O, NN_RIGHT_SHIFT}, .key_sequence = "tu"},

   /* NN_P */
   {.key_combo = {NN_P, NN_NO}, .key_sequence = ","},
   {.key_combo = {NN_P, NN_RIGHT_SHIFT}, .key_sequence = "ne"},

   /* hjkl;: */
   /* H */
   {.key_combo = {NN_H, NN_NO}, .key_sequence = "-"},
   {.key_combo = {NN_H, NN_LEFT_SHIFT}, .key_sequence = "xi"},
   {.key_combo = {NN_H, NN_RIGHT_SHIFT}, .key_sequence = "mu"},

   /* J */
   {.key_combo = {NN_J, NN_NO}, .key_sequence = "nn"},
   {.key_combo = {NN_J, NN_LEFT_SHIFT}, .key_sequence = "xa"},
   {.key_combo = {NN_J, NN_RIGHT_SHIFT}, .key_sequence = "re"},

   /* K */
   {.key_combo = {NN_K, NN_NO}, .key_sequence = "i"},
   {.key_combo = {NN_K, NN_LEFT_SHIFT}, .key_sequence = "gu"},
   {.key_combo = {NN_K, NN_RIGHT_SHIFT}, .key_sequence = "ku"},

   /* L */
   {.key_combo = {NN_L, NN_NO}, .key_sequence = "si"},
   {.key_combo = {NN_L, NN_LEFT_SHIFT}, .key_sequence = "zi"},
   {.key_combo = {NN_L, NN_RIGHT_SHIFT}, .key_sequence = "ri"},

   /* NN_SCOLON */
   {.key_combo = {NN_SCOLON, NN_NO}, .key_sequence = "to"},
   {.key_combo = {NN_SCOLON, NN_LEFT_SHIFT}, .key_sequence = "do"},
   {.key_combo = {NN_SCOLON, NN_RIGHT_SHIFT}, .key_sequence = "wa"},

   /* /\* NN_SQ *\/ */
   /* {.key_combo = {NN_SQ, NN_NO}, .key_sequence = {KC_BSPC}}, */
   /* {.key_combo = {NN_SQ, NN_LEFT_SHIFT}, .key_sequence = KS_PI}, */
   /* {.key_combo = {NN_SQ, NN_RIGHT_SHIFT}, .key_sequence = KS_NE}, */

   /* nm,./ */
   /* N */
   {.key_combo = {NN_N, NN_NO}, .key_sequence = "xtu"},
   {.key_combo = {NN_N, NN_LEFT_SHIFT}, .key_sequence = "xe"},
   {.key_combo = {NN_N, NN_RIGHT_SHIFT}, .key_sequence = "mi"},

   /* M */
   {.key_combo = {NN_M, NN_NO}, .key_sequence = "u"},
   {.key_combo = {NN_M, NN_LEFT_SHIFT}, .key_sequence = "vu"},
   {.key_combo = {NN_M, NN_RIGHT_SHIFT}, .key_sequence = "a"},

   /* , */
   {.key_combo = {NN_COMMA, NN_NO}, .key_sequence = "su"},
   {.key_combo = {NN_COMMA, NN_LEFT_SHIFT}, .key_sequence = "zu"},
   {.key_combo = {NN_COMMA, NN_RIGHT_SHIFT}, .key_sequence = "e"},
   {.key_combo = {NN_COMMA, NN_G}, .key_sequence = "thi"},
   {.key_combo = {NN_COMMA, NN_S}, .key_sequence = "thu"},

   /* . */
   {.key_combo = {NN_DOT, NN_NO}, .key_sequence = "ra"},
   {.key_combo = {NN_DOT, NN_LEFT_SHIFT}, .key_sequence = "di"},
   {.key_combo = {NN_DOT, NN_RIGHT_SHIFT}, .key_sequence = "ti"},

   /* / */
   {.key_combo = {NN_SLASH, NN_NO}, .key_sequence = "he"},
   {.key_combo = {NN_SLASH, NN_LEFT_SHIFT}, .key_sequence = "be"},
   {.key_combo = {NN_SLASH, NN_RIGHT_SHIFT}, .key_sequence = "nu"},

   /* 拗音拡張 */
   {.key_combo = {NN_L, NN_Q}, .key_sequence = "rye"},
   {.key_combo = {NN_L, NN_W}, .key_sequence = "ryu"},
   {.key_combo = {NN_L, NN_E}, .key_sequence = "ryo"},
   {.key_combo = {NN_L, NN_R}, .key_sequence = "rya"},
   {.key_combo = {NN_L, NN_T}, .key_sequence = "ryi"},

   {.key_combo = {NN_L, NN_A}, .key_sequence = "sye"},
   {.key_combo = {NN_L, NN_S}, .key_sequence = "syu"},
   {.key_combo = {NN_L, NN_D}, .key_sequence = "syo"},
   {.key_combo = {NN_L, NN_F}, .key_sequence = "sya"},
   {.key_combo = {NN_L, NN_G}, .key_sequence = "syi"},

   {.key_combo = {NN_L, NN_Z}, .key_sequence = "zye"},
   {.key_combo = {NN_L, NN_X}, .key_sequence = "zyu"},
   {.key_combo = {NN_L, NN_C}, .key_sequence = "zyo"},
   {.key_combo = {NN_L, NN_V}, .key_sequence = "zya"},
   {.key_combo = {NN_L, NN_B}, .key_sequence = "zyi"},

   /* Y */
   {.key_combo = {NN_Y, NN_S}, .key_sequence = "xyu"},
   {.key_combo = {NN_Y, NN_D}, .key_sequence = "xyo"},
   {.key_combo = {NN_Y, NN_F}, .key_sequence = "xya"},

   /* U */
   {.key_combo = {NN_U, NN_Q}, .key_sequence = "hye"},
   {.key_combo = {NN_U, NN_W}, .key_sequence = "hyu"},
   {.key_combo = {NN_U, NN_E}, .key_sequence = "hyo"},
   {.key_combo = {NN_U, NN_R}, .key_sequence = "hya"},
   {.key_combo = {NN_U, NN_T}, .key_sequence = "hyi"},

   {.key_combo = {NN_U, NN_Z}, .key_sequence = "bye"},
   {.key_combo = {NN_U, NN_X}, .key_sequence = "byu"},
   {.key_combo = {NN_U, NN_C}, .key_sequence = "byo"},
   {.key_combo = {NN_U, NN_V}, .key_sequence = "bya"},
   {.key_combo = {NN_U, NN_B}, .key_sequence = "byi"},

   /* I */
   {.key_combo = {NN_I, NN_Q}, .key_sequence = "kye"},
   {.key_combo = {NN_I, NN_W}, .key_sequence = "kyu"},
   {.key_combo = {NN_I, NN_E}, .key_sequence = "kyo"},
   {.key_combo = {NN_I, NN_R}, .key_sequence = "kya"},
   {.key_combo = {NN_I, NN_T}, .key_sequence = "kyi"},

   {.key_combo = {NN_I, NN_Z}, .key_sequence = "gye"},
   {.key_combo = {NN_I, NN_X}, .key_sequence = "gyu"},
   {.key_combo = {NN_I, NN_C}, .key_sequence = "gyo"},
   {.key_combo = {NN_I, NN_V}, .key_sequence = "gya"},
   {.key_combo = {NN_I, NN_B}, .key_sequence = "gyi"},

   /* O */
   {.key_combo = {NN_O, NN_Q}, .key_sequence = "tse"},
   {.key_combo = {NN_O, NN_E}, .key_sequence = "tso"},
   {.key_combo = {NN_O, NN_R}, .key_sequence = "tsa"},
   {.key_combo = {NN_O, NN_T}, .key_sequence = "tsi"},

   {.key_combo = {NN_O, NN_A}, .key_sequence = "nye"},
   {.key_combo = {NN_O, NN_S}, .key_sequence = "nyu"},
   {.key_combo = {NN_O, NN_D}, .key_sequence = "nyo"},
   {.key_combo = {NN_O, NN_F}, .key_sequence = "nya"},
   {.key_combo = {NN_O, NN_G}, .key_sequence = "nyi"},

   {.key_combo = {NN_O, NN_Z}, .key_sequence = "dse"},
   {.key_combo = {NN_O, NN_C}, .key_sequence = "dso"},
   {.key_combo = {NN_O, NN_V}, .key_sequence = "dsa"},
   {.key_combo = {NN_O, NN_B}, .key_sequence = "dsi"},

   /* J */
   {.key_combo = {NN_J, NN_A}, .key_sequence = "fe"},
   {.key_combo = {NN_J, NN_S}, .key_sequence = "fu"},
   {.key_combo = {NN_J, NN_D}, .key_sequence = "fo"},
   {.key_combo = {NN_J, NN_F}, .key_sequence = "fa"},
   {.key_combo = {NN_J, NN_G}, .key_sequence = "fi"},

   /* QUOTE */
   {.key_combo = {NN_SQ, NN_A}, .key_sequence = "pe"},
   {.key_combo = {NN_SQ, NN_S}, .key_sequence = "pu"},
   {.key_combo = {NN_SQ, NN_D}, .key_sequence = "po"},
   {.key_combo = {NN_SQ, NN_F}, .key_sequence = "pa"},
   {.key_combo = {NN_SQ, NN_G}, .key_sequence = "pi"},

   {.key_combo = {NN_SQ, NN_Z}, .key_sequence = "pye"},
   {.key_combo = {NN_SQ, NN_X}, .key_sequence = "pyu"},
   {.key_combo = {NN_SQ, NN_C}, .key_sequence = "pyo"},
   {.key_combo = {NN_SQ, NN_V}, .key_sequence = "pya"},
   {.key_combo = {NN_SQ, NN_B}, .key_sequence = "pyi"},

   /* N */
   {.key_combo = {NN_N, NN_Q}, .key_sequence = "mye"},
   {.key_combo = {NN_N, NN_W}, .key_sequence = "myu"},
   {.key_combo = {NN_N, NN_E}, .key_sequence = "myo"},
   {.key_combo = {NN_N, NN_R}, .key_sequence = "mya"},
   {.key_combo = {NN_N, NN_T}, .key_sequence = "myi"},

   /* M */
   {.key_combo = {NN_M, NN_Q}, .key_sequence = "xe"},
   {.key_combo = {NN_M, NN_W}, .key_sequence = "xu"},
   {.key_combo = {NN_M, NN_E}, .key_sequence = "xo"},
   {.key_combo = {NN_M, NN_R}, .key_sequence = "xa"},
   {.key_combo = {NN_M, NN_T}, .key_sequence = "xi"},

   /* DOT */
   {.key_combo = {NN_DOT, NN_Q}, .key_sequence = "tye"},
   {.key_combo = {NN_DOT, NN_W}, .key_sequence = "tye"},
   {.key_combo = {NN_DOT, NN_E}, .key_sequence = "tye"},
   {.key_combo = {NN_DOT, NN_R}, .key_sequence = "tye"},
   {.key_combo = {NN_DOT, NN_T}, .key_sequence = "tye"},

   {.key_combo = {NN_DOT, NN_Z}, .key_sequence = "dye"},
   {.key_combo = {NN_DOT, NN_X}, .key_sequence = "dyo"},
   {.key_combo = {NN_DOT, NN_C}, .key_sequence = "dyu"},
   {.key_combo = {NN_DOT, NN_V}, .key_sequence = "dya"},
   {.key_combo = {NN_DOT, NN_B}, .key_sequence = "dyi"},

   /* special */
   {.key_combo = {NN_D, NN_K}, .key_sequence = "wo"},
   /* for SKK */
   {.key_combo = {NN_V, NN_M}, .key_sequence = ";"},
   /* type assist */
   {.key_combo = {NN_S, NN_D}, .key_sequence = "demo"},
   {.key_combo = {NN_D, NN_F}, .key_sequence = "mase"},
   {.key_combo = {NN_W, NN_E}, .key_sequence = "dake"},
   {.key_combo = {NN_X, NN_C}, .key_sequence = "made"},
   {.key_combo = {NN_I, NN_O}, .key_sequence = "iki"},
   {.key_combo = {NN_J, NN_K}, .key_sequence = "kure"},
   {.key_combo = {NN_K, NN_L}, .key_sequence = "ari"},
   {.key_combo = {NN_DOT, NN_COMMA}, .key_sequence = "iti"},

  };

/* Initialize variables for japanese implement */
void der_init_variables(void) {
  for (int i = 0; i < nn_max_combination; i++){
    nn_pressed[i] = NN_NO;
  }
  nn_pressed_key_count = 0;
}

/* convert keycode to shift id */
uint16_t der_conv_kc_to_custom_key(uint16_t keycode) {
  switch (keycode) {
  case KC_Q: return NN_Q; break;
  case KC_W: return NN_W; break;
  case KC_E: return NN_E; break;
  case KC_R: return NN_R; break;
  case KC_T: return NN_T; break;
  case KC_Y: return NN_Y; break;
  case KC_U: return NN_U; break;
  case KC_I: return NN_I; break;
  case KC_O: return NN_O; break;
  case KC_P: return NN_P; break;
  case KC_A: return NN_A; break;
  case KC_S: return NN_S; break;
  case KC_D: return NN_D; break;
  case KC_F: return NN_F; break;
  case KC_G: return NN_G; break;
  case KC_H: return NN_H; break;
  case KC_J: return NN_J; break;
  case KC_K: return NN_K; break;
  case KC_L: return NN_L; break;
  case KC_SCLN: return NN_SCOLON; break;
  case KC_Z: return NN_Z; break;
  case KC_X: return NN_X; break;
  case KC_C: return NN_C; break;
  case KC_V: return NN_V; break;
  case KC_B: return NN_B; break;
  case KC_N: return NN_N; break;
  case KC_M: return NN_M; break;
  case KC_COMM: return NN_COMMA; break;
  case KC_DOT: return NN_DOT; break;
  case KC_SLSH: return NN_SLASH; break;
  case KC_QUOT: return NN_SQ; break;
  case KC_NN_LSHIFT: return NN_LEFT_SHIFT; break;
  case KC_NN_RSHIFT: return NN_RIGHT_SHIFT; break;
  }

  return NN_NO;
}

der_nn_key_combination_t der_get_mapping(int index) {
  der_nn_key_combination_t data;
  memcpy_P(&data, &der_nn_key_combinations[index], sizeof(der_nn_key_combination_t));
  return data;
}

uint32_t der_key_to_bits(uint8_t key) {
  return ((uint32_t)1) << key;
}

bool der_match_sequence_pressed(uint8_t* seq, uint8_t* pressed_keys) {
  if (seq[0] == pressed_keys[0]) {
    return seq[1] == pressed_keys[1];
  }
  if (seq[1] == pressed_keys[0]) {
    return seq[0] == pressed_keys[1];
  }
  if (seq[0] == pressed_keys[1]) {
    return seq[1] == pressed_keys[0];
  }
  if (seq[1] == pressed_keys[1]) {
    return seq[0] == pressed_keys[0];
  }

  return false;
}

/* find shift */
bool der_match_combination_pressed(der_nn_key_combination_t* combination, uint8_t* pressed_keys) {
  uint8_t combination_seq[2] = {NN_NO};
  memcpy(combination_seq, combination->key_combo, nn_max_combination * sizeof(uint8_t));

  return der_match_sequence_pressed(combination_seq, pressed_keys);
}

/* return index of key_shifters if found shifter */
int der_find_mapping_on_combinations(uint8_t *pressed_keys) {
  int length = sizeof(der_nn_key_combinations) / sizeof(der_nn_key_combination_t);
  for (int i = 0; i < length; i++) {
    der_nn_key_combination_t data = der_get_mapping(i);

    if (der_match_combination_pressed(&data, pressed_keys)) {
      return i;
    }
  }

  return NN_COMBINATION_NOT_FOUND;
}

/* send keycodes in specified key mapping */
void der_send_key_sequence(int index) {

  if (NN_COMBINATION_NOT_FOUND == index) {
    return;
  }

  der_nn_key_combination_t mapping = der_get_mapping(index);

  send_string(mapping.key_sequence);
}

bool der_is_any_key_pressed() {
  return nn_pressed_key_count > 0;
}

/* Process to resolve key combination from user pressed key */
bool der_process_nn_combination_pressed(uint8_t custom_key) {

  /* when key pressed anything, only register it pressed */

  if (!der_is_any_key_pressed()) {
    nn_pressed[0] = custom_key;
    nn_pressed_key_count = 1;
    return false;
  }

  /* when any key already pressed, find first combination that contains new key.
     if found any combination, only register and return.
   */
  uint8_t tmp_pressed[2] = {NN_NO};
  memcpy(tmp_pressed, nn_pressed, sizeof(uint8_t) * nn_max_combination);
  tmp_pressed[nn_pressed_key_count] = custom_key;
  int index = der_find_mapping_on_combinations(tmp_pressed);
  if (index != NN_COMBINATION_NOT_FOUND && nn_pressed_key_count < nn_max_combination) {
    nn_pressed[nn_pressed_key_count++] = custom_key;
    return false;
  }

  return false;
}

/* Process to resolve key sequence when user released key */
bool der_process_nn_combination_released(uint8_t custom_key) {
  /* get current combination, and release current key. */
  int index = der_find_mapping_on_combinations(nn_pressed);

  der_send_key_sequence(index);

  /* when release any key, reset state */
  der_init_variables();

  return false;
}

/* Process keycodes as hachimitsu-koume keycodes */
bool der_process_nn(uint16_t keycode, keyrecord_t *record) {
  if (has_anymod()) {
    return true;
  }

  uint16_t custom_key = der_conv_kc_to_custom_key(keycode);
  if (record->event.pressed) {

    switch (custom_key) {
    case NN_NO:
      der_init_variables();
      break;
    default:
      return der_process_nn_combination_pressed(custom_key);
    }
  } else {
    /* If key released when current shifter is NOSHIFT, pass through keycode to common process.  */
    switch (custom_key) {
    case NN_NO:
      /* initialize all variables */
      der_init_variables();
      break;
    default:
      return der_process_nn_combination_released(custom_key);
    }
  }

  return true;
}

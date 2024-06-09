#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "ng_layer.h"

/* 内部で利用するkeycode。1から始まっているのは、これらを16bitにおしこめるため */
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

/* 薙刀式を実装する */
#define MAX_KEY_CODES 3
#define KEY_DEF_BITS 5
#define SHIFT_BIT 0x8000

/* 各シフトシーケンスを生成するためのdefinition
   次のように使う。

   NSI(A) => Aの単打
   NM2(F, K) => FとKの同時シフト
   MN3(F, K, Q) => AとKとQの同時シフト
 */
#define NSI(k, seq) { N_ ## k, seq }
#define NSS(k, seq) { SHIFT_BIT | N_ ## k, seq }
#define NM2(k1, k2, seq) { (N_ ## k2 | (N_ ## k1 << 5)), seq }

/* シフトキーを定義する構造体。 */
typedef struct {
  /* LSB is shift mark. */
  uint16_t keycodes;
  const char* sequence;
} seq_definition_t;

/* 複数キーの定義 */
seq_definition_t seq_definitions[] = {
  
  /* Q行 */
  NSI(Q, "ku"),
  NSI(W, "no"),
  NSI(E, "i"),
  NSI(R, "ru"),
  NSI(T, "tu"),
  NSI(Y, "sa"),
  NSI(U, "na"),
  NSI(I, "ma"),
  NSI(O, "ni"),
  NSI(P, "mo"),

  /* A行 */
  NSI(A, "u"),
  NSI(S, "si"),
  NSI(F, "nn"),
  NSI(G, "xtu"),
  NSI(H, "xyo"),
  NSI(J, "te"),
  NSI(L, "ka"),
  NSI(SCLN, "ta"),
  
  /* Z行 */
  NSI(Z, "ra"),
  NSI(X, "ri"),
  NSI(C, "su"),
  NSI(V, "ki"),
  NSI(B, "o"),
  NSI(N, "wo"),
  NSI(M, "to"),
  NSI(COMM, "a"),
  NSI(DOT, "ko"),
  NSI(SLSH, "ha"),

  /* シフト面の定義 */
  /* Q行 */
  NM2(K, Q, "nu"),
  NM2(K, W, "xyu"),
  NM2(K, E, "so"),
  NM2(K, R, "me"),
  NM2(K, T, "xu"),
  NM2(D, U, "ho"),
  NM2(D, I, "xe"),
  NM2(D, O, "hu"),
  NM2(D, P, "xo"),

  /* A行 */
  NM2(K, A, "ke"),
  NM2(K, S, "re"),
  NM2(K, F, "ti"),
  NM2(K, G, "xya"),
  NM2(D, H, "xi"),
  NM2(D, J, "wa"),
  NM2(D, L, SS_TAP(X_MINS)),
  NM2(D, SCLN, "e"),
  
  /* Z行 */
  NM2(K, Z, "hi"),
  NM2(K, X, "mi"),
  NM2(K, C, "ne"),
  NM2(K, V, SS_TAP(X_COMM)),
  NM2(K, B, "mu"),
  NM2(D, N, "he"),
  NM2(D, M, "ro"),
  NM2(D, COMM, "se"),
  NM2(D, DOT, SS_TAP(X_DOT)),
  NM2(D, SLSH, "xa"),

  /* 濁音 */
  NM2(D, Q, "gu"),
  NM2(D, W, "yu"),
  NM2(D, E, "zo"),
  NM2(D, R, "pe"),
  NM2(D, T, "du"),
  NM2(K, Y, "za"),
  NM2(K, U, "bo"),
  NM2(K, I, "pa"),
  NM2(K, O, "bu"),
  NM2(K, P, "po"),

  /* A行 */
  NM2(D, A, "ge"),
  NM2(D, S, "ji"),
  NM2(D, F, "di"),
  NM2(D, G, "ya"),
  NM2(K, H, "yo"),
  NM2(K, J, "de"),
  NM2(K, L, "ga"),
  NM2(K, SCLN, "da"),
  
  /* Z行 */
  NM2(D, Z, "bi"),
  NM2(D, X, "pi"),
  NM2(D, C, "zu"),
  NM2(D, V, "gi"),
  NM2(D, B, "pu"),
  NM2(K, N, "be"),
  NM2(K, M, "do"),
  NM2(K, COMM, "ze"),
  NM2(K, DOT, "go"),
  NM2(K, SLSH, "ba"),
  
  /* 特殊 */
  NM2(J, K, SS_TAP(X_SLSH)),
};

/* global states */
uint16_t key_buffer = 0;
/*
  薙刀式全体を管理するためのconfig。booleanそれだけで8bit消費してしまうので、各bitごとに意味を持たせる。
  1: 薙刀式が有効かどうか
  2: 連続シフト中かどうか
  4: シフトしたキーがspaceかenterか。1ならばenter
  5: 英字モードかどうか

 */
uint8_t naginata_config = 0;

bool ng_is_enabled(void) {
  return (naginata_config & 0x1) == 0x1;
}

void ng_enable(void) {
  naginata_config |= 0x1;
}

void ng_disable(void) {
  naginata_config &= ~0x1;

  ng_reset_state();
}

bool ng_is_cont_shift(void) {
  return (naginata_config & 0x2) == 0x2;
}

void ng_set_cont_shift(void) {
  naginata_config |= 0x2;
}

void ng_unset_cont_shift(void) {
  naginata_config &= ~0x2;
}

void ng_shifted_by_space(void) {
  naginata_config &= ~0x4;
}

void ng_shifted_by_enter(void) {
  naginata_config |= 0x4;
}

uint16_t ng_shifted_key(void) {
  return (naginata_config & 0x4) ? KC_ENTER : KC_SPACE;
}

void ng_set_alphabet_mode(void) {
  naginata_config |= 0b1000;
}

void ng_unset_alphabet_mode(void) {
  naginata_config &= ~0b1000;
}

bool ng_is_alphabet_mode(void) {
  return (naginata_config & 0b1000) == 0b1000;
}

enum ng_key ng_keycode_to_ng_key(uint16_t keycode) {
  switch (keycode) {
  case KC_A:
    return N_A;
  case KC_B:
    return N_B;
  case KC_C:
    return N_C;
  case KC_D:
    return N_D;
  case KC_E:
    return N_E;
  case KC_F:
    return N_F;
  case KC_G:
    return N_G;
  case KC_H:
    return N_H;
  case KC_I:
    return N_I;
  case KC_J:
    return N_J;
  case KC_K:
    return N_K;
  case KC_L:
    return N_L;
  case KC_M:
    return N_M;
  case KC_N:
    return N_N;
  case KC_O:
    return N_O;
  case KC_P:
    return N_P;
  case KC_Q:
    return N_Q;
  case KC_R:
    return N_R;
  case KC_S:
    return N_S;
  case KC_T:
    return N_T;
  case KC_U:
    return N_U;
  case KC_V:
    return N_V;
  case KC_W:
    return N_W;
  case KC_X:
    return N_X;
  case KC_Y:
    return N_Y;
  case KC_Z:
    return N_Z;
  case KC_COMM:
    return N_COMM;
  case KC_DOT:
    return N_DOT;
  case KC_SLSH:
    return N_SLSH;
  case KC_SCLN:
    return N_SCLN;
  case M_SPACE:
  case M_ENTER:
    return N_SFT;
  default:
    return N_UNKNOWN;
  }
}

uint32_t ng_bits_to_32bit(uint16_t bits) {
  uint32_t result = 0;
  
  for (int i = 0; i < MAX_KEY_CODES; i++) {
    uint8_t value = (bits >> (KEY_DEF_BITS * i)) & 0x1F;
    if (value == 0) {
      continue;
    }
    result |= (1 << (value - 1));
  }

  return result;
}

/* key bufferを比較する */
bool ng_match_key_bits(uint16_t a, uint16_t b) {
    return a == b;
}

bool ng_is_key_pressed(enum ng_key key, uint16_t buffer) {
  uint16_t buf = buffer;

  if (key == N_SFT) {
    return ng_is_cont_shift();
  }
  
  for (int i = 0; i < MAX_KEY_CODES; i++) {
    if ((buf & 0x1F) == key) {
      return true;
    }
    buf = buf >> KEY_DEF_BITS;
  }

  return false;
}

void ng_update_buffer_pressed(uint16_t keycode) {
  enum ng_key key = ng_keycode_to_ng_key(keycode);
  if (key == N_SFT) {
    ng_set_cont_shift();
  } else {
    /* バッファがあふれるのをさけるために、一回32bitにつめなおしている */
    uint32_t current = key_buffer & 0x7FFF;

    if (current != 0 && current >> KEY_DEF_BITS != 0) {
      current = 0;
    }
    current = (current << KEY_DEF_BITS) | key;
    
    key_buffer = current & 0x7FFF;
  }
}

void ng_update_state_released(uint16_t keycode) {
  enum ng_key key = ng_keycode_to_ng_key(keycode);
  key_buffer = 0;

  if (key == N_SFT) {
    /* シフトキーの場合、contを初期化する */
    ng_unset_cont_shift();
  }
}

seq_definition_t* ng_find_seq_definition(uint16_t buffer) {
  int count = sizeof(seq_definitions) / sizeof(seq_definition_t);

  seq_definition_t* result = NULL;
  
  for (int i = 0; i < count; i++) {
    if (ng_match_key_bits(buffer, seq_definitions[i].keycodes)) {
      result = &seq_definitions[i];
      return result;
    }
  }

  return result;
}

/* 全体の状態を元に戻す */
void ng_reset_state() {
  key_buffer = 0;
  ng_unset_cont_shift();
  ng_unset_alphabet_mode();
}

bool process_record_ng(uint16_t keycode, keyrecord_t *record) {
  enum ng_key key = ng_keycode_to_ng_key(keycode);

  /* サポートできないキーの場合は無視する */
  if (key == N_UNKNOWN || (ng_is_alphabet_mode() && key != N_SFT)) {
    return true;
  }

  /* 押された時点で決定する */
  if (record->event.pressed) {
    ng_update_buffer_pressed(keycode);

    // shiftキーの場合は設定を記録しておく
    if (key == N_SFT) {
      ng_unset_alphabet_mode();

      if (keycode == M_ENTER) {
        ng_shifted_by_enter();
      } else if (keycode == M_SPACE) {
        ng_shifted_by_space();
      }
    } else if (ng_is_cont_shift()) {
      /* 連続シフトのときに他のキーを押下すると、英字モードに入る */
      ng_unset_cont_shift();
      ng_set_alphabet_mode();
      
      register_code(KC_LSFT);
      tap_code(keycode);
      unregister_code(KC_LSFT);
    } else {
      seq_definition_t* def = ng_find_seq_definition(key_buffer);
      if (def != NULL) {
        send_string(def->sequence);
        ng_reset_state();
      }
    }

    return false;
  } else {
    /* Do not send string if shift key is released and other sequence already sent */
    if (key == N_SFT) {
      // シフトキーが単体で離されたら、最後に押されたshiftキーに対応する処理を返す
      if (!ng_is_alphabet_mode()) {
        tap_code(ng_shifted_key());
      }
      ng_reset_state();
    }

    return false;
  }
}

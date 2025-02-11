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
#define NM2(k1, k2, seq) { (N_ ## k1 | (N_ ## k2 << 5)), seq }
#define NM3(k1, k2, k3, seq) { N_ ## k1 | (N_ ## k2 << 5) | (N_ ## k3 << 10), seq}

/* シフトキーを定義する構造体。 */
typedef struct {
  /* LSB is shift mark. */
  uint16_t keycodes;
  const char* sequence;
} seq_definition_t;

/* 複数キーの定義 */
seq_definition_t seq_definitions[] = {
  
  /* Q行 */
  NSI(W, "ru"),
  NSI(E, "to"),
  NSI(R, "ra"),
  NSI(U, "ti"),
  NSI(I, "su"),
  NSI(O, "ku"),

  /* A行 */
  NSI(A, "ta"),
  NSI(S, "nn"),
  NSI(D, "na"),
  NSI(F, "no"),
  NSI(G, "ni"),
  NSI(H, "ki"),
  NSI(J, "ka"),
  NSI(K, "u"),
  NSI(L, "i"),
  NSI(SCLN, "si"),
  
  /* Z行 */
  NSI(Z, "mo"),
  NSI(X, "te"),
  NSI(C, "tu"),
  NSI(V, "ma"),
  NSI(B, "wo"),
  NSI(N, "o"),
  NSI(M, "ha"),
  NSI(COMM, "xtu"),
  NSI(DOT, "ri"),
  NSI(SLSH, "ko"),

  /* シフト面の定義 */
  /* Q行 */
  NM2(K, W, "hi"),
  NM2(K, E, "me"),
  NM2(K, R, "ke"),
  NM2(D, U, "ya"),
  /* NM2(D, I, "yo"), */
  /* NM2(D, O, "nu"), */

  /* A行 */
  NM2(K, A, "mi"),
  NM2(K, S, "hu"),
  NM2(K, D, "mu"),
  NM2(K, F, SS_TAP(X_MINS)),
  NM2(K, G, "he"),
  NM2(D, H, "nu"),
  /* NM2(D, J, "re"), */
  NM2(D, K, "mu"),
  NM2(D, L, "ho"),
  NM2(D, SCLN, "yu"),
  
  /* Z行 */
  NM2(K, Z, "a"),
  NM2(K, X, "e"),
  NM2(K, C, "ne"),
  NM2(K, V, "re"),
  NM2(K, B, "se"),
  NM2(D, N, "sa"),
  NM2(D, M, "wa"),
  NM2(D, COMM, "so"),
  NM2(D, DOT, "yo"),
  NM2(D, SLSH, "ro"),

  /* 濁音 */
  /* あ行 */
  NSI(Q, "vu"),
  
  /* か行 */
  NM2(F, J, "ga"),
  NM2(F, H, "gi"),
  NM2(F, O, "gu"),
  NM2(J, R, "ge"),
  NM2(F, SLSH, "go"),

  /* さ行 */
  NM2(F, N, "za"),
  NM2(J, SCLN, "zi"),
  NM2(F, I, "zu"),
  NM2(J, B, "ze"),
  NM2(J, COMM, "zo"),

  /* た行 */
  NM2(J, A, "da"),
  NM2(F, U, "di"),
  NM2(J, C, "du"),
  NM2(J, X, "de"),
  NM2(J, E, "do"),

  /* は行 */
  NM2(F, M, "ba"),
  NM2(J, W, "bi"),
  NM2(J, S, "bu"),
  NM2(J, G, "be"),
  NM2(F, L, "bo"),

  /* 半濁音 */
  /* は行 */
  NM2(V, M, "pa"),
  NM2(M, W, "pi"),
  NM2(M, S, "pu"),
  NM2(M, G, "pe"),
  NM2(V, L, "po"),
  
  /* 小書き */
  NM2(P, Z, "xa"),
  NM2(Q, L, "xi"),
  NM2(Q, K, "xu"),
  NM2(P, X, "xe"),
  NM2(Q, N, "xo"),
  NM2(Q, DOT, "xyo"),
  NM2(Q, SCLN, "xyu"),
  NM2(Q, U, "xya"),
  
  /* 特殊 */
  NM2(K, J, SS_TAP(X_DOT)),
  NM2(D, F, SS_TAP(X_COMM)),
  NM3(J, K, E, SS_TAP(X_SLSH)),
  NM3(J, K, D, "?"),
  NM3(J, K, C, "!"),

  /* 拗音拡張 */
  /* 濁音 */
  /* か行 */
  NM2(A, H, "kya"),
  NM2(W, H, "kyu"),
  NM2(E, H, "kyo"),
  NM3(F, A, H, "gya"),
  NM3(F, W, H, "gyu"),
  NM3(F, E, H, "gyo"),

  /* さ行 */
  NM2(A, SCLN, "sya"),
  NM2(W, SCLN, "syu"),
  NM2(E, SCLN, "syo"),
  NM3(J, A, SCLN, "zya"),
  NM3(J, W, SCLN, "zyu"),
  NM3(J, E, SCLN, "zyo"),

  /* た行 */
  NM2(A, U, "tya"),
  NM2(W, U, "tyu"),
  NM2(E, U, "tyo"),
  NM3(F, A, U, "dya"),
  NM3(F, W, U, "dyu"),
  NM3(F, E, U, "dyo"),

  /* は行 */
  NM2(SCLN, W, "hya"),
  NM2(O, W, "hyu"),
  NM2(I, W, "hyo"),
  NM3(J, SCLN, W, "bya"),
  NM3(J, O, W, "byu"),
  NM3(J, I, W, "byo"),
  NM3(M, SLSH, W, "pya"),
  NM3(M, L, W, "pyu"),
  NM3(M, K, W, "pyo"),

  /* な行 */
  NM2(SLSH, G, "nya"),
  NM2(O, G, "nyu"),
  NM2(I, G, "nyo"),

  /* ま行 */
  NM2(SLSH, A, "mya"),
  NM2(O, A, "myu"),
  NM2(I, A, "myo"),

  /* ら行 */
  NM2(A, DOT, "rya"),
  NM2(W, DOT, "ryu"),
  NM2(E, DOT, "ryo"),
};

/* global states */
uint16_t key_buffer = 0;
/*
  薙刀式全体を管理するためのconfig。booleanそれだけで8bit消費してしまうので、各bitごとに意味を持たせる。
  0: 薙刀式が有効かどうか
  1: 連続シフト中かどうか
  2: シフトしたキーがspaceかenterか。1ならばenter
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

uint8_t ng_sort_patterns_3[8][3] = {
  {2, 1, 0},
  {0, 2, 1},
  {1,0,2},
  {0,1,2},
  {2,1,0},
  {2,0,1},
  {1,2,0},
  {0,1,2}
};

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

/* キー配列を特定の流れに変換して、比較をしやすくする */
uint16_t ng_normalized_key_bits(uint16_t bits) {
  uint8_t temp[MAX_KEY_CODES];
  uint8_t result[MAX_KEY_CODES];
  
  for (int i = 0; i < MAX_KEY_CODES; i++) {
    temp[i] = (bits >> (KEY_DEF_BITS * i)) & 0x1F;
  }

  int sort_pattern = ((temp[0] <= temp[1]) ? 1 : 0) + ((temp[1] <= temp[2]) ? 2 : 0) + ((temp[2] <= temp[0]) ? 4 : 0);
  result[0] = temp[ng_sort_patterns_3[sort_pattern][0]];
  result[1] = temp[ng_sort_patterns_3[sort_pattern][1]];
  result[2] = temp[ng_sort_patterns_3[sort_pattern][2]];

  return (bits & 0x8000) | (result[0] << (KEY_DEF_BITS * 2)) | (result[1] << KEY_DEF_BITS) | result[2];
}

bool ng_match_key_bits(uint16_t a, uint16_t b) {
  uint16_t normalized_a = ng_normalized_key_bits(a);
  uint16_t normalized_b = ng_normalized_key_bits(b);
  
  return normalized_a == normalized_b;
}

/* 現在入力されているキーの一覧が含まれるような場合を検出する */
bool ng_similar_key_bits(uint16_t source, uint16_t target) {
  uint32_t normalized_source = ng_bits_to_32bit(source);
  uint32_t normalized_target = ng_bits_to_32bit(target);
  
  return (normalized_source & normalized_target) == normalized_source;
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

seq_definition_t* ng_find_seq_definition(uint16_t buffer, bool contain_similar) {
  int count = sizeof(seq_definitions) / sizeof(seq_definition_t);

  seq_definition_t* result = NULL;
  bool found_other_def = false;
  
  for (int i = 0; i < count; i++) {
    if (ng_match_key_bits(buffer, seq_definitions[i].keycodes)) {
      result = &seq_definitions[i];
      /* 一致する物自体は高々一つしか存在していない */
      if (!contain_similar) {
        return result;
      }
    } else if (contain_similar && ng_similar_key_bits(buffer, seq_definitions[i].keycodes)) {
      found_other_def = true;
    }
  }

  if (found_other_def) {
    return NULL;
  }

  return result;
}

/* 全体の状態を元に戻す */
void ng_reset_state() {
  key_buffer = 0;
  ng_unset_cont_shift();
}

/* shiftされている場合には、先頭だけ大文字にする */
void send_string_shifted(const char* sequence) {
  for (int i = 0; i < strlen(sequence); i++) {
    char shifted[2] = {sequence[i], '\0'};
    if (i == 0 && 'a' <= sequence[i] && sequence[i] <= 'z' && ng_is_cont_shift()) {
      register_code(KC_LSFT);
      send_string(shifted);
      unregister_code(KC_LSFT);
    } else {
      send_string(shifted);
    }
  }
}

bool process_record_ng(uint16_t keycode, keyrecord_t *record) {
  enum ng_key key = ng_keycode_to_ng_key(keycode);

  /* サポートできないキーの場合は無視する */
  if (key == N_UNKNOWN) {
    return true;
  }

  /* 押された場合は、単にbufferに積むのみとする */
  if (record->event.pressed) {
    ng_update_buffer_pressed(keycode);

    // shiftキーの場合は設定を記録しておく
    if (key == N_SFT) {
      ng_set_cont_shift();
      if (keycode == M_ENTER) {
        ng_shifted_by_enter();
      } else if (keycode == M_SPACE) {
        ng_shifted_by_space();
      }
    }

    return false;
  } else {
    /* キーがおされていない場合は何もしない */
    if (!ng_is_key_pressed(key, key_buffer)) {
      return false;
    }

    /* releaseされた場合、現在のバッファと一致するものを強制する */
    seq_definition_t* def = ng_find_seq_definition(key_buffer, false);
    ng_update_state_released(keycode);

    if (!def && key != N_SFT) {
      return false;
    }

    /* Do not send string if shift key is released and other sequence already sent */
    if (key == N_SFT) {
      if (!ng_is_cont_shift()) {
        // シフトキーが単体で離されたら、最後に押されたshiftキーに対応する処理を返す
        tap_code(ng_shifted_key());
        ng_unset_cont_shift();
      }

      return false;
    }

    send_string_shifted(def->sequence);

    return false;
  }
}

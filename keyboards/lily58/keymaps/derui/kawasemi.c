#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "kawasemi.h"

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
  N_UNKNOWN
};

/* 薙刀式を実装する */
#define MAX_KEY_CODES 3
#define KEY_DEF_BITS 5

/* 各シフトシーケンスを生成するためのdefinition
   次のように使う。

   NSI(A) => Aの単打
   NS2(F, K) => FとKの同時シフト
 */
#define NSI(k, seq) { N_ ## k, seq }
#define NS2(k1, k2, seq) { (N_ ## k1 | (N_ ## k2 << 5)), seq }

/* シフトキーを定義する構造体。 */
typedef struct {
  /* LSB is shift mark. */
  uint16_t keycodes;
  const char* sequence;
} seq_definition_t;

/* 複数キーの定義 */
const seq_definition_t PROGMEM seq_definitions[] = {

  /* Q行 */
  NSI(Q, "ni"),
  NSI(W, "ga"),
  NSI(E, "ji"),
  NSI(R, "de"),
  NSI(T, "ba"),

  NSI(Y, "re"),
  NSI(U, "yo"),
  NSI(I, "yu"),
  NSI(O, "ya"),
  NSI(P, "wo"),

  /* A行 */
  NSI(A, "no"),
  NSI(S, "ka"),
  NSI(D, "si"),
  NSI(F, "to"),
  NSI(G, "ha"),
  NSI(H, "e"),
  NSI(J, "o"),
  NSI(K, "u"),
  NSI(L, "i"),
  NSI(SCLN, "a"),
  
  /* Z行 */
  NSI(Z, "na"),
  NSI(X, "ru"),
  NSI(C, "ma"),
  NSI(V, "te"),
  NSI(B, "wa"),
  NSI(N, "xtu"),
  NSI(M, "nn"),
  NSI(COMM, SS_TAP(X_COMM)),
  NSI(DOT, SS_TAP(X_DOT)),
  NSI(SLSH, SS_TAP(X_MINS)),

  /* 行段系の定義 */
  /* Q行 */
  NS2(W, H, "ge"),
  NS2(W, J, "go"),
  NS2(W, K, "gu"),
  NS2(W, L, "gi"),
  NS2(W, SCLN, "ga"),
  NS2(E, H, "ze"),
  NS2(E, J, "zo"),
  NS2(E, K, "zu"),
  NS2(E, L, "zi"),
  NS2(E, SCLN, "za"),
  NS2(R, H, "de"),
  NS2(R, J, "do"),
  NS2(R, K, "du"),
  NS2(R, L, "di"),
  NS2(R, SCLN, "da"),
  NS2(T, H, "be"),
  NS2(T, J, "bo"),
  NS2(T, K, "bu"),
  NS2(T, L, "bi"),
  NS2(T, SCLN, "ba"),

  /* A行 */
  NS2(A, H, "ne"),
  NS2(A, J, "no"),
  NS2(A, K, "nu"),
  NS2(A, L, "ni"),
  NS2(A, SCLN, "na"),
  NS2(S, H, "ke"),
  NS2(S, J, "ko"),
  NS2(S, K, "ku"),
  NS2(S, L, "ki"),
  NS2(S, SCLN, "ka"),
  NS2(D, H, "se"),
  NS2(D, J, "so"),
  NS2(D, K, "su"),
  NS2(D, L, "si"),
  NS2(D, SCLN, "sa"),
  NS2(F, H, "te"),
  NS2(F, J, "to"),
  NS2(F, K, "tu"),
  NS2(F, L, "ti"),
  NS2(F, SCLN, "ta"),
  NS2(G, H, "he"),
  NS2(G, J, "ho"),
  NS2(G, K, "hu"),
  NS2(G, L, "hi"),
  NS2(G, SCLN, "ha"),

  /* Z行 */
  NS2(X, H, "re"),
  NS2(X, J, "ro"),
  NS2(X, K, "ru"),
  NS2(X, L, "ri"),
  NS2(X, SCLN, "ra"),
  NS2(C, H, "me"),
  NS2(C, J, "mo"),
  NS2(C, K, "mu"),
  NS2(C, L, "mi"),
  NS2(C, SCLN, "ma"),
  NS2(B, H, "pe"),
  NS2(B, J, "po"),
  NS2(B, K, "pu"),
  NS2(B, L, "pi"),
  NS2(B, SCLN, "pa"),

  /* 拗音 - 清音 */
  /* き */
  NS2(S, O, "kya"),
  NS2(S, I, "kyu"),
  NS2(S, U, "kyo"),

  /* し */
  NS2(D, O, "sya"),
  NS2(D, I, "syu"),
  NS2(D, U, "syo"),

  /* ち */
  NS2(F, O, "tya"),
  NS2(F, I, "tyu"),
  NS2(F, U, "tyo"),

  /* に */
  NS2(A, O, "nya"),
  NS2(A, I, "nyu"),
  NS2(A, U, "nyo"),

  /* ひ */
  NS2(G, O, "hya"),
  NS2(G, I, "hyu"),
  NS2(G, U, "hyo"),

  /* み */
  NS2(C, O, "mya"),
  NS2(C, I, "myu"),
  NS2(C, U, "myo"),

  /* り */
  NS2(X, O, "rya"),
  NS2(X, I, "ryu"),
  NS2(X, U, "ryo"),

  /* 拗音 - 濁音 */
  /* ぎ */
  NS2(W, O, "gya"),
  NS2(W, I, "gyu"),
  NS2(W, U, "gyo"),

  /* し */
  NS2(E, O, "zya"),
  NS2(E, I, "zyu"),
  NS2(E, U, "zyo"),

  /* ち */
  NS2(R, O, "dya"),
  NS2(R, I, "dyu"),
  NS2(R, U, "dyo"),

  /* ひ */
  NS2(T, O, "bya"),
  NS2(T, I, "byu"),
  NS2(T, U, "byo"),

  /* 拗音 - 半濁音 */
  /* ひ */
  NS2(B, O, "pya"),
  NS2(B, I, "pyu"),
  NS2(B, U, "pyo"),

  /* 小書き */
  NS2(Q, H, "xe"),
  NS2(Q, J, "xo"),
  NS2(Q, K, "xu"),
  NS2(Q, L, "xi"),
  NS2(Q, SCLN, "xa"),
  NS2(Q, U, "xyo"),
  NS2(Q, I, "xyu"),
  NS2(Q, O, "xya"),

  /* 撥音拡張 */
  /* Q行 */
  NS2(W, N, "genn"),
  NS2(W, M, "gonn"),
  NS2(W, COMM, "gunn"),
  NS2(W, DOT, "ginn"),
  NS2(W, SLSH, "gann"),
  NS2(E, N, "zenn"),
  NS2(E, M, "zonn"),
  NS2(E, COMM, "zunn"),
  NS2(E, DOT, "zinn"),
  NS2(E, SLSH, "zann"),
  NS2(E, N, "denn"),
  NS2(E, M, "donn"),
  NS2(E, COMM, "dunn"),
  NS2(E, DOT, "dinn"),
  NS2(E, SLSH, "dann"),
  NS2(T, N, "benn"),
  NS2(T, M, "bonn"),
  NS2(T, COMM, "bunn"),
  NS2(T, DOT, "binn"),
  NS2(T, SLSH, "bann"),

  /* A行 */
  NS2(A, N, "nenn"),
  NS2(A, M, "nonn"),
  NS2(A, COMM, "nunn"),
  NS2(A, DOT, "ninn"),
  NS2(A, SLSH, "nann"),
  NS2(S, N, "kenn"),
  NS2(S, M, "konn"),
  NS2(S, COMM, "kunn"),
  NS2(S, DOT, "kinn"),
  NS2(S, SLSH, "kann"),
  NS2(D, N, "senn"),
  NS2(D, M, "sonn"),
  NS2(D, COMM, "sunn"),
  NS2(D, DOT, "sinn"),
  NS2(D, SLSH, "sann"),
  NS2(F, N, "tenn"),
  NS2(F, M, "tonn"),
  NS2(F, COMM, "tunn"),
  NS2(F, DOT, "tinn"),
  NS2(F, SLSH, "tann"),
  NS2(G, N, "henn"),
  NS2(G, M, "honn"),
  NS2(G, COMM, "hunn"),
  NS2(G, DOT, "hinn"),
  NS2(G, SLSH, "hann"),

  /* Z行 */
  NS2(X, N, "renn"),
  NS2(X, M, "ronn"),
  NS2(X, COMM, "runn"),
  NS2(X, DOT, "rinn"),
  NS2(X, SLSH, "rann"),

  NS2(C, N, "menn"),
  NS2(C, M, "monn"),
  NS2(C, COMM, "munn"),
  NS2(C, DOT, "minn"),
  NS2(C, SLSH, "mann"),

  NS2(B, N, "penn"),
  NS2(B, M, "ponn"),
  NS2(B, COMM, "punn"),
  NS2(B, DOT, "pinn"),
  NS2(B, SLSH, "pann"),
  
  /* 特殊 */
  NS2(V, J, SS_TAP(X_SLSH)),
};

/* global states */
uint16_t key_buffer = 0;
/*
  全体を管理するためのconfig。booleanそれだけで8bit消費してしまうので、各bitごとに意味を持たせる。
  0: かわせみ配列が有効かどうか
 */
uint8_t kawasemi_config = 0;

bool ng_is_enabled(void) {
  return (kawasemi_config & 0x1) == 0x1;
}

void ng_enable(void) {
  kawasemi_config |= 0x1;
}

void ng_disable(void) {
  kawasemi_config &= ~0x1;
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
  /* バッファがあふれるのをさけるために、一回32bitにつめなおしている */
  uint32_t current = key_buffer & 0x7FFF;
  current = (current << KEY_DEF_BITS) | key;
    
  key_buffer = current & 0x7FFF;
}

void ng_update_state_released(uint16_t keycode) {
  key_buffer = 0;
}

seq_definition_t ng_find_seq_definition(uint16_t buffer, bool contain_similar) {
  int count = sizeof(seq_definitions) / sizeof(seq_definition_t);

  seq_definition_t result = {0, NULL};
  bool found_other_def = false;
  
  for (int i = 0; i < count; i++) {
    memcpy_P(&result, &seq_definitions[i], sizeof(seq_definition_t));
    if (ng_match_key_bits(buffer, result.keycodes)) {
      
      /* 一致する物自体は高々一つしか存在していない */
      if (!contain_similar) {
        return result;
      }
    } else if (contain_similar && ng_similar_key_bits(buffer, result.keycodes)) {
      found_other_def = true;
    }
  }

  if (found_other_def) {
    seq_definition_t failed = {0, NULL};
    return failed;
  }

  return result;
}

/* 全体の状態を元に戻す */
void ng_reset_state() {
  key_buffer = 0;
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

    return false;
  } else {
    /* キーがおされていない場合は何もしない */
    if (!ng_is_key_pressed(key, key_buffer)) {
      return false;
    }

    /* releaseされた場合、現在のバッファと一致するものを強制する */
    seq_definition_t def = ng_find_seq_definition(key_buffer, false);
    ng_update_state_released(keycode);

    if (!def.sequence) {
      return false;
    }

    send_string(def.sequence);

    return false;
  }
}

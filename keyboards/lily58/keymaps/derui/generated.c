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
  NSI(W, "ha"),
  NSI(E, "si"),
  NSI(R, "xtu"),
  NSI(U, "ko"),
  NSI(I, "te"),
  NSI(O, "ku"),

  /* A行 */
  NSI(A, "ta"),
  NSI(S, "nn"),
  NSI(D, "u"),
  NSI(F, "no"),
  NSI(G, "ni"),
  NSI(H, "ki"),
  NSI(J, "ka"),
  NSI(K, "na"),
  NSI(L, "i"),
  NSI(SCLN, "to"),
  
  /* Z行 */
  NSI(Z, "ra"),
  NSI(X, "ru"),
  NSI(C, "ri"),
  NSI(V, "wo"),
  NSI(B, "o"),
  NSI(N, "mo"),
  NSI(M, "ma"),
  NSI(COMM, "su"),
  NSI(DOT, "a"),
  NSI(SLSH, "tu"),

  /* シフト面の定義 */
  /* Q行 */
  NM2(K, W, "yu"),
  NM2(K, E, "e"),
  NM2(K, R, "ho"),
  NM2(D, U, "ro"),
  NM2(D, I, "yo"),
  NM2(D, O, "re"),

  /* A行 */
  NM2(K, A, "mi"),
  NM2(K, S, "so"),
  NM2(K, D, "mu"),
  NM2(K, F, "wa"),
  NM2(K, G, "sa"),
  /* NM2(D, H, "mi"), */
  /* NM2(D, J, "re"), */
  NM2(D, K, "mu"),
  NM2(D, L, "hu"),
  NM2(D, SCLN, "nu"),
  
  /* Z行 */
  NM2(K, Z, "ke"),
  NM2(K, X, "ti"),
  NM2(K, C, "se"),
  NM2(K, V, SS_TAP(X_MINS)),
  NM2(K, B, "hi"),
  NM2(D, N, "me"),
  NM2(D, M, "he"),
  NM2(D, COMM, "ne"),
  /* NM2(D, DOT, "yo"), */
  NM2(D, SLSH, "ya"),

  /* 濁音 */
  /* あ行 */
  NSI(Q, "vu"),
  
  /* か行 */
  NM2(F, J, "ga"),
  NM2(F, H, "gi"),
  NM2(F, O, "gu"),
  NM2(J, Z, "ge"),
  NM2(F, U, "go"),

  /* さ行 */
  NM2(J, G, "za"),
  NM2(J, E, "zi"),
  NM2(F, COMM, "zu"),
  NM2(J, C, "ze"),
  NM2(J, S, "zo"),

  /* た行 */
  NM2(J, A, "da"),
  NM2(J, X, "di"),
  NM2(F, SLSH, "du"),
  NM2(F, I, "de"),
  NM2(F, SCLN, "do"),

  /* は行 */
  NM2(J, W, "ba"),
  NM2(J, B, "bi"),
  NM2(F, L, "bu"),
  NM2(F, M, "be"),
  NM2(J, R, "bo"),

  /* 半濁音 */
  /* は行 */
  NM2(M, W, "pa"),
  NM2(M, B, "pi"),
  NM2(V, L, "pu"),
  NM2(V, M, "pe"),
  NM2(M, R, "po"),
  
  /* 小書き */
  NM2(Q, DOT, "xa"),
  NM2(Q, L, "xi"),
  NM2(P, D, "xu"),
  NM2(P, E, "xe"),
  NM2(P, B, "xo"),
  NM2(Q, SLSH, "xyo"),
  NM2(P, W, "xyu"),
  NM2(P, A, "xya"),
  
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
  NM2(SCLN, E, "sya"),
  NM2(O, E, "syu"),
  NM2(I, E, "syo"),
  NM3(J, SCLN, E, "zya"),
  NM3(J, O, E, "zyu"),
  NM3(J, I, E, "zyo"),

  /* た行 */
  NM2(SCLN, X, "tya"),
  NM2(O, X, "tyu"),
  NM2(I, X, "tyo"),
  NM3(J, SCLN, X, "dya"),
  NM3(J, O, X, "dyu"),
  NM3(J, I, X, "dyo"),

  /* は行 */
  NM2(SCLN, B, "hya"),
  NM2(O, B, "hyu"),
  NM2(I, B, "hyo"),
  NM3(J, SCLN, B, "bya"),
  NM3(J, O, B, "byu"),
  NM3(J, I, B, "byo"),
  NM3(M, SLSH, B, "pya"),
  NM3(M, L, B, "pyu"),
  NM3(M, K, B, "pyo"),

  /* な行 */
  NM2(SCLN, G, "nya"),
  NM2(O, G, "nyu"),
  NM2(I, G, "nyo"),

  /* ま行 */
  NM2(SCLN, A, "mya"),
  NM2(O, A, "myu"),
  NM2(I, A, "myo"),
  
  /* ら行 */
  NM2(SCLN, C, "rya"),
  NM2(O, C, "ryu"),
  NM2(I, C, "ryo"),
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
  if ('a' <= sequence[0] && sequence[0] <= 'z' && ng_is_cont_shift()) {
    char shifted[2] = {sequence[0], '\0'};
    register_code(KC_LSFT);
    send_string(shifted);
    unregister_code(KC_LSFT);
    
    for (int i = 1; i < strlen(sequence); i++) {
      char shifted[2] = {sequence[i], '\0'};
      send_string(shifted);
    }
    ng_unset_cont_shift();
  } else {
    send_string(sequence);
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
      // シフトキーが単体で離されたら、最後に押されたshiftキーに対応する処理を返す
      tap_code(ng_shifted_key());
      ng_unset_cont_shift();

      return false;
    }

    send_string_shifted(def->sequence);

    return false;
  }
}

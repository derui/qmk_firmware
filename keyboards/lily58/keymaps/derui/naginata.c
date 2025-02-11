#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "naginata.h"

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
   NSS(A) => Aのシフト面単打
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
  {SHIFT_BIT, SS_TAP(X_SPACE)},
  
  /* Q行 */
  NSI(Q, "vu"),
  NSI(W, "ki"),
  NSI(E, "te"),
  NSI(R, "si"),
  NSI(T, SS_TAP(X_LEFT)),
  NSI(Y, SS_TAP(X_RIGHT)),
  NSI(U, SS_TAP(X_BSPC)),
  NSI(I, "ru"),
  NSI(O, "su"),
  NSI(P, "he"),

  /* A行 */
  NSI(A, "ro"),
  NSI(S, "ke"),
  NSI(D, "to"),
  NSI(F, "ka"),
  NSI(G, "xtu"),
  NSI(H, "ku"),
  NSI(J, "a"),
  NSI(K, "i"),
  NSI(L, "u"),
  NSI(SCLN, SS_TAP(X_MINS)),
  
  /* Z行 */
  NSI(Z, "ho"),
  NSI(X, "hi"),
  NSI(C, "ha"),
  NSI(V, "ko"),
  NSI(B, "so"),
  NSI(N, "ta"),
  NSI(M, "na"),
  NSI(COMM, "nn"),
  NSI(DOT, "ra"),
  NSI(SLSH, "re"),

  /* シフト面の定義 */
  /* Q行 */
  /* NSS(Q, "vu"), */
  NSS(W, "nu"),
  NSS(E, "ri"),
  NSS(R, "me"),
  /* NSS(T, SS_TAP(X_RIGHT)), */
  /* NSS(Y, SS_TAP(X_LEFT)), */
  NSS(U, "sa"),
  NSS(I, "yo"),
  NSS(O, "e"),
  NSS(P, "yu"),

  /* A行 */
  NSS(A, "se"),
  NSS(S, "mi"),
  NSS(D, "ni"),
  NSS(F, "ma"),
  NSS(G, "ti"),
  NSS(H, "ya"),
  NSS(J, "no"),
  NSS(K, "mo"),
  NSS(L, "tu"),
  NSS(SCLN, "hu"),
  
  /* Z行 */
  /* NSS(Z, "ho"), */
  /* NSS(X, "hi"), */
  NSS(C, "wo"),
  NSS(V, SS_TAP(X_COMM)),
  NSS(B, "ne"),
  NSS(N, "o"),
  NSS(M, SS_TAP(X_DOT)),
  NSS(COMM, "mu"),
  NSS(DOT, "wa"),
  /* NSS(SLSH, "re"),   */

  /* 濁音 */
  /* か行 */
  NM2(J, F, "ga"),
  NM2(J, W, "gi"),
  NM2(F, H, "gu"),
  NM2(J, S, "ge"),
  NM2(J, V, "go"),

  /* さ行 */
  NM2(F, U, "za"),
  NM2(J, R, "zi"),
  NM2(F, O, "zu"),
  NM2(J, A, "ze"),
  NM2(J, B, "zo"),

  /* た行 */
  NM2(F, N, "da"),
  NM2(J, G, "di"),
  NM2(F, L, "du"),
  NM2(J, E, "de"),
  NM2(J, D, "do"),

  /* は行 */
  NM2(J, C, "ba"),
  NM2(J, X, "bi"),
  NM2(F, SCLN, "bu"),
  NM2(F, P, "be"),
  NM2(J, Z, "bo"),

  /* 半濁音 */
  /* は行 */
  NM2(M, C, "pa"),
  NM2(M, X, "pi"),
  NM2(V, SCLN, "pu"),
  NM2(V, P, "pe"),
  NM2(M, Z, "po"),

  /* 拗音 - 清音 */
  /* き */
  NM2(W, H, "kya"),
  NM2(W, P, "kyu"),
  NM2(W, I, "kyo"),

  /* し */
  NM2(R, H, "sya"),
  NM2(R, P, "syu"),
  NM2(R, I, "syo"),

  /* ち */
  NM2(G, H, "tya"),
  NM2(G, P, "tyu"),
  NM2(G, I, "tyo"),

  /* に */
  NM2(D, H, "nya"),
  NM2(D, P, "nyu"),
  NM2(D, I, "nyo"),

  /* ひ */
  NM2(X, H, "hya"),
  NM2(X, P, "hyu"),
  NM2(X, I, "hyo"),

  /* み */
  NM2(S, H, "mya"),
  NM2(S, P, "myu"),
  NM2(S, I, "myo"),

  /* り */
  NM2(E, H, "rya"),
  NM2(E, P, "ryu"),
  NM2(E, I, "ryo"),

  /* 拗音 - 濁音 */
  /* き */
  NM3(W, H, J, "gya"),
  NM3(W, P, J, "gyu"),
  NM3(W, I, J, "gyo"),

  /* し */
  NM3(R, H, J, "zya"),
  NM3(R, P, J, "zyu"),
  NM3(R, I, J, "zyo"),

  /* ち */
  NM3(G, H, J, "dya"),
  NM3(G, P, J, "dyu"),
  NM3(G, I, J, "dyo"),

  /* ひ */
  NM3(X, H, J, "bya"),
  NM3(X, P, J, "byu"),
  NM3(X, I, J, "byo"),

  /* 拗音 - 半濁音 */
  /* ひ */
  NM3(X, H, M, "pya"),
  NM3(X, P, M, "pyu"),
  NM3(X, I, M, "pyo"),

  /* 小書き */
  NM2(Q, J, "xa"),
  NM2(Q, K, "xi"),
  NM2(Q, L, "xu"),
  NM2(Q, O, "xe"),
  NM2(Q, N, "xo"),
  NM2(Q, P, "xyu"),
  NM2(Q, I, "xyo"),
  NM2(Q, H, "xya"),

  /* 外来語 */
  NM3(E, M, K, "texi"),
  NM3(E, M, P, "texyu"),
  NM3(G, M, O, "tixe"),
  NM3(D, M, L, "toxu"),
  NM3(D, J, L, "doxu"),
  NM3(R, M, O, "sixe"),
  NM3(V, J, SCLN, "fa"),        /* ふぁ */
  NM3(V, K, SCLN, "fi"),        /* ふぃ */
  NM3(V, O, SCLN, "fe"),        /* ふぇ */
  NM3(V, N, SCLN, "fo"),        /* ふぉ */
  
  /* 特殊 */
  NM2(V, M, SS_TAP(X_ENTER)),
  NM3(J, K, T, SS_TAP(X_SLSH)),
  NM3(J, K, D, "?"),
  NM3(J, K, C, "!"),

  /* 編集モード */
  /* SKKとか用 */
  NM3(D, F, I, ";"),
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
    return (buf & SHIFT_BIT) == SHIFT_BIT;
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
    key_buffer = key_buffer | SHIFT_BIT;
  } else {
    /* バッファがあふれるのをさけるために、一回32bitにつめなおしている */
    uint32_t current = key_buffer & 0x7FFF;
    current = (current << KEY_DEF_BITS) | key;
    
    key_buffer = (key_buffer & 0x8000) | (current & 0x7FFF);
  }
}

void ng_update_state_released(uint16_t keycode) {
  enum ng_key key = ng_keycode_to_ng_key(keycode);
  if (key == N_SFT) {
    /* シフトキーの場合、全体をリセットする必要がある */
    key_buffer = 0;
  } else {
    /* シフトキー以外の場合、そもそも確定していないのであれば、シフト部分以外をresetする */
    key_buffer &= SHIFT_BIT;
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

    if (!def) {
      return false;
    }

    /* Do not send string if shift key is released and other sequence already sent */
    if (key == N_SFT && def->keycodes == SHIFT_BIT) {
      if (!ng_is_cont_shift()) {
        // シフトキーが単体で離されたら、最後に押されたshiftキーに対応する処理を返す
        tap_code(ng_shifted_key());
      }

      ng_reset_state();
      
      return false;
    }

    send_string(def->sequence);

    /* If shift key is pressing, set mark. */
    if (key_buffer & SHIFT_BIT) {
      ng_set_cont_shift();
    }

    return false;
  }
}

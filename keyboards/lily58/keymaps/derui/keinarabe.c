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

/* けいならべ配列を実装する */
#define MAX_KEY_CODES 3
#define KEY_DEF_BITS 5
#define SHIFT_BIT 0x8000

/* 各シーケンスを生成するためのdefinition
   次のように使う。

   NSI(A) => Aの単打
   NM2(F, K) => FとKの同時シフト
 */
#define NSI(k, seq) { N_ ## k, seq }
#define NM2(k1, k2, seq) { (N_ ## k1 | (N_ ## k2 << 5)), seq }

/* シフトキーを定義する構造体。 */
typedef struct {
  /* LSB is shift mark. */
  uint16_t keycodes;
  const char* sequence;
} seq_definition_t;

/* 複数キーの定義 */
seq_definition_t seq_definitions[] = {
  /* シフトキーの単押しに対応する */
  {SHIFT_BIT, ""},
  
  /* Q行 */
  NSI(Q, "ni"),
  NSI(W, "ru"),
  NSI(E, "ma"),
  NSI(R, "ha"),
  NSI(T, "ba"),
  NSI(Y, SS_TAP(X_SLSH)),
  NSI(U, "yo"),
  NSI(I, "u"),
  NSI(O, "o"),
  NSI(P, "wo"),

  /* A行 */
  NSI(A, "no"),
  NSI(S, "ta"),
  NSI(D, "si"),
  NSI(F, "ka"),
  NSI(G, "xtu"),
  NSI(H, "yu"),
  NSI(J, "a"),
  NSI(K, "i"),
  NSI(L, "e"),
  NSI(SCLN, "nn"),
  
  /* Z行 */
  NSI(Z, "na"),
  NSI(X, "de"),
  NSI(C, "zi"),
  NSI(V, "ga"),
  NSI(B, "wa"),
  NSI(N, "ya"),
  NSI(M, "wo"),
  NSI(COMM, SS_TAP(X_COMM)),
  NSI(DOT, SS_TAP(X_DOT)),
  NSI(SLSH, SS_TAP(X_MINS)),

  /* 同時押しの定義 */
  NM2(A, J, "na"),
  NM2(A, K, "ni"),
  NM2(A, I, "nu"),
  NM2(A, O, "no"),
  NM2(A, L, "ne"),  

  NM2(S, J, "ta"),
  NM2(S, K, "ti"),
  NM2(S, I, "tu"),
  NM2(S, O, "to"),
  NM2(S, L, "te"),  

  NM2(D, J, "sa"),
  NM2(D, K, "si"),
  NM2(D, I, "su"),
  NM2(D, O, "so"),
  NM2(D, L, "se"),  

  NM2(F, J, "ka"),
  NM2(F, K, "ki"),
  NM2(F, I, "ku"),
  NM2(F, O, "ko"),
  NM2(F, L, "ke"),  

  NM2(R, J, "ha"),
  NM2(R, K, "hi"),
  NM2(R, I, "hu"),
  NM2(R, O, "ho"),
  NM2(R, L, "he"),  

  NM2(W, J, "ra"),
  NM2(W, K, "ri"),
  NM2(W, I, "ru"),
  NM2(W, O, "ro"),
  NM2(W, L, "re"),  

  NM2(E, J, "ma"),
  NM2(E, K, "mi"),
  NM2(E, I, "mu"),
  NM2(E, O, "mo"),
  NM2(E, L, "me"),  

  /* 濁音 */
  /* か行 */
  NM2(X, J, "da"),
  NM2(X, K, "di"),
  NM2(X, I, "du"),
  NM2(X, O, "do"),
  NM2(X, L, "de"),  

  NM2(C, J, "za"),
  NM2(C, K, "zi"),
  NM2(C, I, "zu"),
  NM2(C, O, "zo"),
  NM2(C, L, "ze"),  

  NM2(V, J, "ga"),
  NM2(V, K, "gi"),
  NM2(V, I, "gu"),
  NM2(V, O, "go"),
  NM2(V, L, "ge"),  

  NM2(T, J, "ba"),
  NM2(T, K, "bi"),
  NM2(T, I, "bu"),
  NM2(T, O, "bo"),
  NM2(T, L, "be"),  

  /* 半濁音 */
  /* は行 */
  NM2(Z, J, "pa"),
  NM2(Z, K, "pi"),
  NM2(Z, I, "pu"),
  NM2(Z, O, "po"),
  NM2(Z, L, "pe"),  

  /* 拗音 - 清音 */
  /* き */
  NM2(F, U, "kyo"),
  NM2(F, H, "kyu"),
  NM2(F, N, "kya"),

  /* し */
  NM2(D, U, "syo"),
  NM2(D, H, "syu"),
  NM2(D, N, "sya"),

  /* ち */
  NM2(S, U, "tyo"),
  NM2(S, H, "tyu"),
  NM2(S, N, "tya"),

  /* に */
  NM2(A, U, "nyo"),
  NM2(A, H, "nyu"),
  NM2(A, N, "nya"),

  /* ひ */
  NM2(R, U, "hyo"),
  NM2(R, H, "hyu"),
  NM2(R, N, "hya"),

  /* み */
  NM2(E, U, "myo"),
  NM2(E, H, "myu"),
  NM2(E, N, "mya"),

  /* り */
  NM2(W, U, "ryo"),
  NM2(W, H, "ryu"),
  NM2(W, N, "rya"),

  /* 拗音 - 濁音 */
  /* き */
  NM2(V, U, "gyo"),
  NM2(V, H, "gyu"),
  NM2(V, N, "gya"),

  /* し */
  NM2(C, U, "zyo"),
  NM2(C, H, "zyu"),
  NM2(C, N, "zya"),

  /* ち */
  NM2(X, U, "dyo"),
  NM2(X, H, "dyu"),
  NM2(X, N, "dya"),

  /* ひ */
  NM2(T, U, "byo"),
  NM2(T, H, "byu"),
  NM2(T, N, "bya"),

  /* 拗音 - 半濁音 */
  /* ひ */
  NM2(Z, U, "pyo"),
  NM2(Z, H, "pyu"),
  NM2(Z, N, "pya"),

  /* 小書き */
  NM2(Q, J, "xa"),
  NM2(Q, K, "xi"),
  NM2(Q, I, "xu"),
  NM2(Q, O, "xo"),
  NM2(Q, L, "xe"),
  NM2(Q, U, "xyo"),
  NM2(Q, H, "xyu"),
  NM2(Q, N, "xya"),

  /* 外来語 */
  
  /* 特殊 */
};

/* global states */
uint16_t key_buffer = 0;
/*
  全体を管理するためのconfig。booleanそれだけで8bit消費してしまうので、各bitごとに意味を持たせる。
  0: 有効かどうか
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
    return;
  }
  
  /* バッファがあふれるのをさけるために、一回32bitにつめなおしている */
  uint32_t current = key_buffer & 0x7FFF;
  current = (current << KEY_DEF_BITS) | key;
    
  key_buffer = (key_buffer & 0x8000) | (current & 0x7FFF);
}

void ng_update_state_released(uint16_t keycode) {
  key_buffer = 0;
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

/*
 対象のdefから、shiftingしている文字列を返す。
  */
void ng_send_string_capitalize_if_shifting(seq_definition_t* def, bool shifting) {
  char buffer[10] =  {};
  strcpy(buffer, def->sequence);

  if (shifting && 'a' <= buffer[0] && buffer[0] <= 'z') {
    /* asciiだった場合だけ大文字にしておく */
    buffer[0] -= 'a' - 'A';
  }

  send_string(buffer);
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
      ng_set_cont_shift();
    }

    return false;
  } else {
    /* Do not send string if shift key is released and other sequence already sent */
    if (key == N_SFT && ng_is_cont_shift()) {
      // シフトキーが単体で離されたら、最後に押されたshiftキーに対応する処理を返す
      tap_code(ng_shifted_key());
      
      ng_reset_state();
        
      return false;
    }
    
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

    bool shifting = ng_is_cont_shift();
    ng_send_string_capitalize_if_shifting(def, shifting);

    ng_unset_cont_shift();

    return false;
  }
}

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "custom_key_handling.h"
#include "keymap_8x3.h"

/* シン蜂蜜小梅配列を実装する。 */
#define MAX_KEY_CODES 2

/* 各シフトシーケンスを生成するためのdefinition
   次のように使う。

   LSFT8(A) => Aと左親指の同時シフト
   RSFT8(A) => Aと右親指の同時シフト
   SFT8(A, K) => AとKの同時シフト
 */
#define LSFT8(k) {M_SPACE, KC_ ## k}
#define RSFT8(k) {M_ENTER, KC_ ## k}
#define SFT8(k1, k2) {KC_ ## k1, KC_ ## k2}

/* 単打の定義 */
single_tap_definition_t single_tap_definitions[] = {
  {M_SPACE, RELEASED, SS_TAP(X_SPACE)},
  {M_ENTER, RELEASED, SS_TAP(X_ENTER)},
  /* Q行 */
  {KC_Q, RELEASED, SS_TAP(X_DOT)},
  {KC_W, RELEASED, "na"},
  {KC_E, RELEASED, "te"},
  {KC_R, RELEASED, "se"},
  {KC_T, RELEASED, "so"},
  {KC_Y, RELEASED, SS_TAP(X_SLSH)},
  {KC_U, RELEASED, "o"},
  {KC_I, RELEASED, "no"},
  {KC_O, RELEASED, "ni"},
  /* {KC_P, RELEASED, "na"}, */
  {KC_LBRC, RELEASED, SS_TAP(X_COMMA)},
  /* A行 */
  {KC_A, RELEASED, "ko"},
  {KC_S, RELEASED, "ta"},
  {KC_D, RELEASED, "ka"},
  {KC_F, RELEASED, "ru"},
  {KC_G, RELEASED, "ha"},
  {KC_H, RELEASED, SS_TAP(X_MINS)},
  {KC_J, RELEASED, "nn"},
  {KC_K, RELEASED, "i"},
  {KC_L, RELEASED, "si"},
  {KC_SCLN, RELEASED, "to"},
  {KC_QUOT, RELEASED, SS_TAP(X_BSPC)},
  /* Z行 */
  {KC_Z, RELEASED, "yu"},
  {KC_X, RELEASED, "ho"},
  {KC_C, RELEASED, "ma"},
  {KC_V, RELEASED, "ro"},
  /* {KC_B, RELEASED, "so"}, */
  {KC_N, RELEASED, "xtu"},
  {KC_M, RELEASED, "u"},
  {KC_COMM, RELEASED, "su"},
  {KC_DOT, RELEASED, "ra"},
  {KC_SLSH, RELEASED, "he"},
};

/* シフトの定義 */
shift_definition_t shift_definitions[] = {
  /* 左シフト */
  /* Q行 */
  /* {LSFT8(Q), NO_SHIFT, "pe"}, */
  {LSFT8(W), NO_SHIFT, "ke"},
  {LSFT8(E), NO_SHIFT, "yo"},
  /* {LSFT8(R), NO_SHIFT, "so"}, */
  /* {LSFT8(T), NO_SHIFT, "na"}, */
  /* {LSFT8(Y), NO_SHIFT, "o"}, */
  {LSFT8(U), NO_SHIFT, "bi"},
  {LSFT8(I), NO_SHIFT, "gi"},
  {LSFT8(O), NO_SHIFT, "du"},
  /* {LSFT8(P), NO_SHIFT, "ni"}, */
  /* {LSFT8(LBRC), NO_SHIFT, "na"}, */
  /* A行 */
  {LSFT8(A), NO_SHIFT, "me"},
  {LSFT8(S), NO_SHIFT, "ya"},
  {LSFT8(D), NO_SHIFT, "mo"},
  {LSFT8(F), NO_SHIFT, "sa"},
  {LSFT8(G), NO_SHIFT, "xu"},
  {LSFT8(H), NO_SHIFT, "xi"},
  {LSFT8(J), NO_SHIFT, "xa"},
  {LSFT8(K), NO_SHIFT, "gu"},
  {LSFT8(L), NO_SHIFT, "ji"},
  {LSFT8(SCLN), NO_SHIFT, "do"},
  /* {LSFT8(QUOT), NO_SHIFT, "pi"}, */
  /* Z行 */
  {LSFT8(Z), NO_SHIFT, "xyu"},
  {LSFT8(X), NO_SHIFT, "xya"},
  {LSFT8(C), NO_SHIFT, "hu"},
  {LSFT8(V), NO_SHIFT, "xyo"},
  {LSFT8(B), NO_SHIFT, "xo"},
  {LSFT8(N), NO_SHIFT, "xe"},
  {LSFT8(M), NO_SHIFT, "vu"},
  {LSFT8(COMMA), NO_SHIFT, "zu"},
  {LSFT8(DOT), NO_SHIFT, "di"},
  {LSFT8(SLSH), NO_SHIFT, "be"},

  /* 右シフト */
  /* Q行 */
  /* {RSFT8(Q), NO_SHIFT, "pa"}, */
  {RSFT8(W), NO_SHIFT, "ge"},
  {RSFT8(E), NO_SHIFT, "de"},
  {RSFT8(R), NO_SHIFT, "ze"},
  {RSFT8(T), NO_SHIFT, "zo"},
  /* {RSFT8(Y), NO_SHIFT, "o"}, */
  {RSFT8(U), NO_SHIFT, "hi"},
  {RSFT8(I), NO_SHIFT, "ki"},
  {RSFT8(O), NO_SHIFT, "tu"},
  /* {RSFT8(P), NO_SHIFT, "ni"}, */
  /* {RSFT8(LBRC), NO_SHIFT, "na"}, */
  /* A行 */
  {RSFT8(A), NO_SHIFT, "go"},
  {RSFT8(S), NO_SHIFT, "da"},
  {RSFT8(D), NO_SHIFT, "ga"},
  {RSFT8(F), NO_SHIFT, "za"},
  {RSFT8(G), NO_SHIFT, "ba"},
  {RSFT8(H), NO_SHIFT, "mu"},
  {RSFT8(J), NO_SHIFT, "re"},
  {RSFT8(K), NO_SHIFT, "ku"},
  {RSFT8(L), NO_SHIFT, "ri"},
  {RSFT8(SCLN), NO_SHIFT, "wa"},
  {RSFT8(QUOT), NO_SHIFT, "ne"},
  /* Z行 */
  /* {RSFT8(Z), NO_SHIFT, "po"}, */
  {RSFT8(X), NO_SHIFT, "bo"},
  {RSFT8(C), NO_SHIFT, "bu"},
  {RSFT8(V), NO_SHIFT, "pu"},
  {RSFT8(B), NO_SHIFT, "xwa"},
  {RSFT8(N), NO_SHIFT, "mi"},
  {RSFT8(M), NO_SHIFT, "a"},
  {RSFT8(COMMA), NO_SHIFT, "e"},
  {RSFT8(DOT), NO_SHIFT, "ti"},
  {RSFT8(SLSH), NO_SHIFT, "nu"},

  /* 特殊打鍵 */
  {SFT8(D, K), NO_SHIFT, "wo"},


  /* 8x3のマトリックス定義 */
  /* Pa/Pi/Pu/Pe/Po */
  {SFT8(G, H), NO_SHIFT, "pa"},
  {SFT8(G, U), NO_SHIFT, "pi"},
  {SFT8(C, H), NO_SHIFT, "pu"},
  {SFT8(G, SLSH), NO_SHIFT, "pe"},
  {SFT8(H, X), NO_SHIFT, "po"},
  
  /* あ */
  {SFT8(M, Q), NO_SHIFT, "xe"},
  {SFT8(M, W), NO_SHIFT, "xu"},
  {SFT8(M, E), NO_SHIFT, "xo"},
  {SFT8(M, R), NO_SHIFT, "xa"},
  {SFT8(M, T), NO_SHIFT, "xi"},

  /* き */
  {SFT8(I, Q), NO_SHIFT, "kye"},
  {SFT8(I, W), NO_SHIFT, "kyu"},
  {SFT8(I, E), NO_SHIFT, "kyo"},
  {SFT8(I, R), NO_SHIFT, "kya"},
  {SFT8(I, T), NO_SHIFT, "kyi"},

  /* ぎ */
  {SFT8(I, Z), NO_SHIFT, "gye"},
  {SFT8(I, X), NO_SHIFT, "gyu"},
  {SFT8(I, C), NO_SHIFT, "gyo"},
  {SFT8(I, V), NO_SHIFT, "gya"},
  {SFT8(I, B), NO_SHIFT, "gyi"},

  /* し */
  {SFT8(L, A), NO_SHIFT, "sye"},
  {SFT8(L, S), NO_SHIFT, "syu"},
  {SFT8(L, D), NO_SHIFT, "syo"},
  {SFT8(L, F), NO_SHIFT, "sya"},
  {SFT8(L, G), NO_SHIFT, "syi"},

  /* じ */
  {SFT8(L, Z), NO_SHIFT, "zye"},
  {SFT8(L, X), NO_SHIFT, "zyu"},
  {SFT8(L, C), NO_SHIFT, "zyo"},
  {SFT8(L, V), NO_SHIFT, "zya"},
  {SFT8(L, B), NO_SHIFT, "zyi"},

  /* ち */
  {SFT8(DOT, Q), NO_SHIFT, "tye"},
  {SFT8(DOT, W), NO_SHIFT, "tyu"},
  {SFT8(DOT, E), NO_SHIFT, "tyo"},
  {SFT8(DOT, R), NO_SHIFT, "tya"},
  {SFT8(DOT, T), NO_SHIFT, "tyi"},

  /* ぢ */
  {SFT8(DOT, Z), NO_SHIFT, "dye"},
  {SFT8(DOT, X), NO_SHIFT, "dyu"},
  {SFT8(DOT, C), NO_SHIFT, "dyo"},
  {SFT8(DOT, V), NO_SHIFT, "dya"},
  {SFT8(DOT, B), NO_SHIFT, "dyi"},

  /* て */
  {SFT8(COMM, S), NO_SHIFT, "texi"},
  {SFT8(COMM, G), NO_SHIFT, "texyu"},

  /* で */
  {SFT8(COMM, X), NO_SHIFT, "dexi"},
  {SFT8(COMM, B), NO_SHIFT, "dexyu"},

  /* に */
  {SFT8(O, A), NO_SHIFT, "nye"},
  {SFT8(O, S), NO_SHIFT, "nyu"},
  {SFT8(O, D), NO_SHIFT, "nyo"},
  {SFT8(O, F), NO_SHIFT, "nya"},
  {SFT8(O, G), NO_SHIFT, "nyi"},

  /* ひ */
  {SFT8(U, Q), NO_SHIFT, "hye"},
  {SFT8(U, W), NO_SHIFT, "hyu"},
  {SFT8(U, E), NO_SHIFT, "hyo"},
  {SFT8(U, R), NO_SHIFT, "hya"},
  {SFT8(U, T), NO_SHIFT, "hyi"},
  
  /* び */
  {SFT8(U, Z), NO_SHIFT, "bye"},
  {SFT8(U, X), NO_SHIFT, "byu"},
  {SFT8(U, C), NO_SHIFT, "byo"},
  {SFT8(U, V), NO_SHIFT, "bya"},
  {SFT8(U, B), NO_SHIFT, "byi"},

  /* ぴ */
  {SFT8(H, Q), NO_SHIFT, "pye"},
  {SFT8(H, W), NO_SHIFT, "pyu"},
  {SFT8(H, E), NO_SHIFT, "pyo"},
  {SFT8(H, R), NO_SHIFT, "pya"},
  {SFT8(H, T), NO_SHIFT, "pyi"},

  /* ふ */
  {SFT8(J, A), NO_SHIFT, "fe"},
  {SFT8(J, S), NO_SHIFT, "fyu"},
  {SFT8(J, D), NO_SHIFT, "fo"},
  {SFT8(J, F), NO_SHIFT, "fa"},
  {SFT8(J, G), NO_SHIFT, "fi"},

  /* ぶ */
  {SFT8(J, Z), NO_SHIFT, "buxa"},
  {SFT8(J, X), NO_SHIFT, "buxu"},
  {SFT8(J, C), NO_SHIFT, "buxo"},
  {SFT8(J, V), NO_SHIFT, "buxa"},
  {SFT8(J, B), NO_SHIFT, "buxi"},

  /* み */
  {SFT8(N, Q), NO_SHIFT, "mye"},
  {SFT8(N, W), NO_SHIFT, "myu"},
  {SFT8(N, E), NO_SHIFT, "myo"},
  {SFT8(N, R), NO_SHIFT, "mya"},
  {SFT8(N, T), NO_SHIFT, "myi"},

  /* り */
  {SFT8(L, Q), NO_SHIFT, "rye"},
  {SFT8(L, W), NO_SHIFT, "ryu"},
  {SFT8(L, E), NO_SHIFT, "ryo"},
  {SFT8(L, R), NO_SHIFT, "rya"},
  {SFT8(L, T), NO_SHIFT, "ryi"},
};

/* キーコードが対象のdefinitionに含まれるかどうかを返す */
bool contains_keycodes(uint16_t keycode, shift_definition_t* shift_definition) {
  return shift_definition->keycodes[0] == keycode || shift_definition->keycodes[1] == keycode;
}

/*
  必要ならreduce、つまりsequenceを送信する。
  reduceの条件としては、
- すでにreducing = なんらかのキーでシフトが行われている
- その状態でもう一回同じdefinitionに対してこの処理が呼ばれる

となる。
 */
bool reduce_shift_if_necessary(uint16_t keycode, shift_definition_t* shift_definition) {
  if (!contains_keycodes(keycode, shift_definition)) {
    return false;
  }
  
  if (shift_definition->shift_state == REDUCING) {
    shift_definition->shift_state = NO_SHIFT;
    send_string(shift_definition->sequence);

    return true;
  }

  shift_definition->shift_state = REDUCING;
  return false;
}

/* 全体の状態を元に戻す */
void reset_states_8x3() {
  int count = sizeof(shift_definitions) / sizeof(shift_definition_t);
  for (int i = 0; i < count;i++) {
    shift_definitions[i].shift_state = NO_SHIFT;
  }

  int single_tap_definition_count = sizeof(single_tap_definitions) / sizeof(single_tap_definition_t);
  for (int i = 0; i < single_tap_definition_count;i++) {
    single_tap_definitions[i].tap_state = RELEASED;
  }
}

bool process_record_8x3(uint16_t keycode, keyrecord_t *record) {
  /* シフト→単打の順で判定を行う */
  int shift_definition_count = sizeof(shift_definitions) / sizeof(shift_definition_t);
  int single_tap_definition_count = sizeof(single_tap_definitions) / sizeof(single_tap_definition_t);

  bool shift_reduced = false;

  for (int i = 0; i < shift_definition_count;i++) {
    shift_definition_t* def = &shift_definitions[i];

    if (record->event.pressed) {
      /* シフトに含まれる場合、その状態を判定する。 */
      shift_reduced = reduce_shift_if_necessary(keycode, def);

      if (shift_reduced) {
        reset_states_8x3();
        break;
      }
    }
  }

  if (shift_reduced) {
    return false;
  }

  for (int i = 0; i < single_tap_definition_count;i++) {
    single_tap_definition_t* def = &single_tap_definitions[i];

    if (def->keycode == keycode) {
      if (record->event.pressed) {
        if (def->tap_state == RELEASED) {
          def->tap_state = PRESSED;
          return false;
        }
      } else {
        if (def->tap_state == PRESSED) {
          def->tap_state = RELEASED;
          send_string(def->sequence);
          reset_states_8x3();
          return false;
        }
      }
    }
  }

  return true;
}

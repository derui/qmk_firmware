#include <stdint.h>
#include "action.h"
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "./custom_keycodes.h"

#define MAX_KEY_CODES 3
#define KEY_DEF_BITS 5
#define SHIFT_BIT 0x8000
#define BASE_RANGE (M_SAFE_RANGE - 1)

/* 各シフトシーケンスを生成するためのdefinition
   次のように使う。

   NS(A, "a") => Aの単打
   NSS(A, "A") => Aとシフトキーの同時シフト
   ND(F, K, "") => FとKの同時シフト
   NDS(F, K, "") => FとKとシフトキーの同時シフト
   NT(F, K, D) => F/K/Dの同時シフト
 */
#define NS(k, seq) {(N_##k - BASE_RANGE), seq}
#define NSS(k, seq) {SHIFT_BIT | (N_##k - BASE_RANGE), seq}
#define ND(k1, k2, seq) {((N_##k1 - BASE_RANGE) | ((N_##k2 - BASE_RANGE) << KEY_DEF_BITS)), seq}
#define NDS(k1, k2, seq) {SHIFT_BIT | ((N_##k1 - BASE_RANGE) | ((N_##k2 - BASE_RANGE) << KEY_DEF_BITS)), seq}
#define NT(k1, k2, k3, seq) {((N_##k1 - BASE_RANGE) | ((N_##k2 - BASE_RANGE) << KEY_DEF_BITS) | ((N_##k3 - BASE_RANGE) << KEY_DEF_BITS * 2)), seq}

/**
   イベントの種類
 */
enum der_kana_event {
    DER_KANA_NONE = 0,
    // 通常キーを押下した
    DER_KANA_NORMAL_KEY_PRESSED,
    // 通常キーを離した
    DER_KANA_NORMAL_KEY_RELEASED,
    // シフトキーを押下した
    DER_KANA_SHIFT_KEY_PRESSED,
    // シフトキーを押下した
    DER_KANA_SHIFT_KEY_RELEASED,
};

// 3配列を高速に並べ替えるための配列
uint8_t der_sort_patterns_3[8][3] = {{2, 1, 0}, {0, 2, 1}, {1, 0, 2}, {0, 1, 2}, {2, 1, 0}, {2, 0, 1}, {1, 2, 0}, {0, 1, 2}};

/**
   全体で処理したキーコード及びシフトキーの状態。

   連続シフトを有効にしているので、カスタムキーコードを入力する限りはハンドルできる。
 */
static uint16_t der_processed_keycodes = 0;

/**
   現在押されているshift keyのキーコードを設定する
   */
static uint16_t der_stored_shift_key = 0;

/**
   連続シフトであるかどうかを保持する。

連続シフトは、シフトキーを離さない状態で他のキーを押下したときを指す。シフトキー自体を離した場合は連続の判定にはならない
 */
static bool der_continuous_shift = false;

/**
   かなのキー定義。
 */
typedef struct {
    // キー定義として利用する。
    // custom_keysからSAFE_RANGEを引いたものが使われる。順序は不動である。
    //
    // 1         00000 00000 00000
    // shift bit
    //                 char1 char2
    uint16_t keycodes;

    // 入力の結果として利用する文字列。そのままsend_stringされる。
    const char *represents;
} der_seq_def;

// キーの定義
static der_seq_def der_seq_defs[] = {
    NS(Q, "vu"),
    NS(W, "su"),
    NS(E, "i"),
    NS(R, "xtu"),
    NS(U, "ko"),
    NS(I, "to"),
    NS(O, "ta"),
    NS(A, "shi"),
    NS(S, "no"),
    NS(D, "ku"),
    NS(F, "ru"),
    NS(G, "ni"),
    NS(H, "mo"),
    NS(J, "ka"),
    NS(K, "nn"),
    NS(L, "na"),
    NS(SCLN, "u"),

    NS(Z, "re"),
    NS(X, "ri"),
    NS(C, "ki"),
    NS(V, "wo"),
    NS(B, "o"),
    NS(N, "a"),
    NS(M, "ha"),
    NS(COMM, "te"),
    NS(DOT, "ma"),
    NS(SLSH, "ti"),

  // shift
    NSS(W, "me"),
    NSS(E, "-"),
    NSS(R, "he"),
    NSS(U, "yu"),
    NSS(I, "wa"),
    NSS(O, "ro"),
    NSS(A, "e"),
    NSS(S, "se"),
    NSS(D, "mi"),
    NSS(F, "ra"),
    NSS(G, "ho"),
    NSS(H, "so"),
    NSS(J, "yo"),
    NSS(K, "tu"),
    NSS(L, "sa"),
    NSS(SCLN, "ke"),
    NSS(Z, "hi"),
    NSS(X, "fu"),

    NSS(M, "ne"),
    NSS(COMM, "ya"),
    NSS(DOT, "mu"),
    NSS(SLSH, "nu"),

    // turbids
    ND(W, J, "zu"),
    ND(R, J, "be"),
    ND(U, F, "go"),
    ND(I, F, "do"),
    ND(O, F, "da"),
    ND(A, J, "zi"),
    ND(S, J, "ze"),
    ND(D, J, "gu"),
    ND(G, J, "bo"),
    ND(H, F, "zo"),
    ND(J, F, "ga"),
    ND(K, F, "du"),
    ND(L, F, "za"),
    ND(SCLN, F, "ge"),
    ND(Z, J, "bi"),
    ND(X, J, "bu"),
    ND(C, J, "gi"),
    ND(M, F, "ba"),
    ND(COMM, F, "de"),
    ND(SLSH, F, "di"),

    ND(R, M, "pe"),
    ND(G, M, "po"),
    ND(Z, M, "pi"),
    ND(X, M, "pu"),
    ND(V, M, "pa"),

    // special keys
    NS(ENTER, "\n"),
    NS(SPACE, " "),
    NSS(C, "."),
    NSS(V, ","),

    // 小書き
    ND(Y, B, "xo"),
    ND(T, N, "xa"),
    ND(Y, E, "xi"),
    ND(Y, A, "xe"),
    ND(T, SCLN, "xu"),
    ND(T, U, "xyu"),
    ND(T, J, "xyo"),
    ND(T, COMM, "xya"),

    // 拗音拡張
    ND(A, I, "syu"),
    ND(A, K, "syo"),
    ND(A, COMM, "sya"),

    ND(C, I, "kyu"),
    ND(C, K, "kyo"),
    ND(C, COMM, "kya"),

    ND(SLSH, E, "tyu"),
    ND(SLSH, D, "tyo"),
    ND(SLSH, C, "tya"),

    ND(G, I, "nyu"),
    ND(G, K, "nyo"),
    ND(G, COMM, "nya"),

    ND(D, I, "myu"),
    ND(D, K, "myo"),
    ND(D, COMM, "mya"),

    ND(Z, I, "hyu"),
    ND(Z, K, "hyo"),
    ND(Z, COMM, "hya"),

    ND(X, I, "ryu"),
    ND(X, K, "ryo"),
    ND(X, COMM, "rya"),
    
    NT(A, I, O, "zyu"),
    NT(A, K, L, "zyo"),
    NT(A, COMM, DOT, "zya"),

    NT(C, I, O, "gyu"),
    NT(C, K, L, "gyo"),
    NT(C, COMM, DOT, "gya"),

    NT(SLSH, E, W, "dyu"),
    NT(SLSH, D, S, "dyo"),
    NT(SLSH, C, X, "dya"),

    NT(Z, I, O, "byu"),
    NT(Z, K, L, "byo"),
    NT(Z, COMM, DOT, "bya"),

    NT(Z, I, U, "pyu"),
    NT(Z, K, J, "pyo"),
    NT(Z, COMM, M, "pya"),

};

/// functions

/**
   状態を初期化する。特定のmodeが存在しないmodelessの設計として必要。
  */
void der_reset_state(void) {
    der_processed_keycodes = 0;
    der_stored_shift_key   = 0;
    der_continuous_shift   = false;
}

/* キー配列を特定の流れに変換して、比較をしやすくする */
uint16_t der_normalized_key_bits(uint16_t bits) {
    uint8_t temp[MAX_KEY_CODES];
    uint8_t result[MAX_KEY_CODES];

    for (int i = 0; i < MAX_KEY_CODES; i++) {
        temp[i] = (bits >> (KEY_DEF_BITS * i)) & 0x1F;
    }

    int sort_pattern = ((temp[0] <= temp[1]) ? 1 : 0) + ((temp[1] <= temp[2]) ? 2 : 0) + ((temp[2] <= temp[0]) ? 4 : 0);
    result[0]        = temp[der_sort_patterns_3[sort_pattern][0]];
    result[1]        = temp[der_sort_patterns_3[sort_pattern][1]];
    result[2]        = temp[der_sort_patterns_3[sort_pattern][2]];

    return (bits & SHIFT_BIT) | (result[0] << (KEY_DEF_BITS * 2)) | (result[1] << KEY_DEF_BITS) | result[2];
}

/**
   現状のkeycodeに一致するkey defを探索する
 */
der_seq_def *der_find_der_seq_def_by_keycode(uint16_t keycode) {
    uint16_t normalized_keycode = der_normalized_key_bits(keycode);

    for (size_t i = 0; i < sizeof(der_seq_defs) / sizeof(der_seq_defs[0]); ++i) {
        // Normalize the keycodes in the current entry
        uint16_t stored_normalized_keycodes = der_normalized_key_bits(der_seq_defs[i].keycodes);

        if (stored_normalized_keycodes == normalized_keycode) {
            return &der_seq_defs[i];
        }
    }

    return NULL;
}

/**
   keycodeに対応する文字列を発行する

   対応する定義がない場合は何も行わない。
 */
bool der_send_string_of_keycode(uint16_t keycode) {
    der_seq_def *seq_def = der_find_der_seq_def_by_keycode(keycode);

    if (seq_def) {
        send_string(seq_def->represents);
        return true;
    }

    return false;
}

/**
   Check given keycode is in custom_keys
 */
bool der_is_kana_keycode(uint16_t keycode) {
    return (keycode >= N_A) && (keycode <= N_ENTER);
}

/**
   対象のキーがシフトキーかどうかを返す
 */
bool der_is_kana_shift_key(uint16_t keycode) {
  return (keycode == (N_SPACE - BASE_RANGE)) || (keycode == (N_ENTER - BASE_RANGE));
}

/**
   Match two keycode with normalizer
 */
bool der_match_keycodes(uint16_t keycode1, uint16_t keycode2) {
    return (der_normalized_key_bits(keycode1) == der_normalized_key_bits(keycode2));
}

/**
   キーコードとkeyrecord_tから `der_kana_event` を導出する
 */
enum der_kana_event der_get_kana_event(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (der_is_kana_shift_key(keycode)) {
            return DER_KANA_SHIFT_KEY_PRESSED;
        }
        return DER_KANA_NORMAL_KEY_PRESSED;
    } else {
        if (der_is_kana_shift_key(keycode)) {
            return DER_KANA_SHIFT_KEY_RELEASED;
        }
        return DER_KANA_NORMAL_KEY_RELEASED;
    }
}

/**
   Check if a keycode is present in der_processed_keycodes
 */
bool der_is_keycode_in_processed_keycodes(uint16_t keycode) {
    for (int i = 0; i < MAX_KEY_CODES; ++i) {
        uint16_t stored_keycode = (der_processed_keycodes >> (i * KEY_DEF_BITS)) & 0x1F;
        if (stored_keycode == (keycode & 0x1F)) {
            return true;
        }
    }
    return false;
}

/**
   通常のキーを押下したときの処理を定義する
   */
void der_handle_kana_normal_key_pressed(uint16_t keycode, keyrecord_t *record) {
    uint16_t shifted       = der_processed_keycodes & SHIFT_BIT;
    der_processed_keycodes = shifted | (0x7fff & (der_processed_keycodes << KEY_DEF_BITS | (keycode & 0x1f)));
}

/**
   通常のキーを離したときの処理を定義する
   */
void der_handle_kana_normal_key_released(uint16_t keycode, keyrecord_t *record) {
    if (!der_is_keycode_in_processed_keycodes(keycode)) {
        return;
    }

    der_send_string_of_keycode(der_processed_keycodes);

    // shift bitだけ残す
    der_processed_keycodes &= SHIFT_BIT;

    if ((der_processed_keycodes & SHIFT_BIT) != 0) {
        der_continuous_shift = true;
    }
}

/**
   シフトキーを押下したときの処理を定義する
   */
void der_handle_kana_shift_key_pressed(uint16_t keycode, keyrecord_t *record) {
    der_processed_keycodes |= SHIFT_BIT;

    if (!der_stored_shift_key) {
        der_stored_shift_key = keycode;
    }
}

/**
   シフトキーを離したときの処理を定義する
   */
void der_handle_kana_shift_key_released(uint16_t keycode, keyrecord_t *record) {
    if (der_processed_keycodes != SHIFT_BIT) {
        // shift key以外が押下されている場合は、全体をresetする
        der_send_string_of_keycode(der_processed_keycodes);
        der_reset_state();
        return;
    }

    if (der_continuous_shift) {
        // 連続シフトしていて、shiftだけ離したら何もしない
    } else {
        if (der_stored_shift_key == (N_ENTER - BASE_RANGE)) {
            register_code(KC_ENTER);
            unregister_code(KC_ENTER);
        } else if (der_stored_shift_key == (N_SPACE - BASE_RANGE)) {
            register_code(KC_SPACE);
            unregister_code(KC_SPACE);
        }
    }
    der_reset_state();
}

/**
   イベントハンドラ
 */
void der_handle_kana_event(enum der_kana_event event, uint16_t keycode, keyrecord_t *record) {
    switch (event) {
        case DER_KANA_NORMAL_KEY_PRESSED:
            der_handle_kana_normal_key_pressed(keycode, record);
            break;
        case DER_KANA_NORMAL_KEY_RELEASED:
            der_handle_kana_normal_key_released(keycode, record);
            break;
        case DER_KANA_SHIFT_KEY_PRESSED:
            der_handle_kana_shift_key_pressed(keycode, record);
            break;
        case DER_KANA_SHIFT_KEY_RELEASED:
            der_handle_kana_shift_key_released(keycode, record);
            break;
        default:
            break;
    }
}

bool der_process_record_kana(uint16_t keycode, keyrecord_t *record) {
    if (!der_is_kana_keycode(keycode)) {
        der_reset_state();
        return true;
    }

    uint16_t formatted_keycode = keycode - BASE_RANGE;

    enum der_kana_event event = der_get_kana_event(formatted_keycode, record);

    der_handle_kana_event(event, formatted_keycode, record);

    return false;
}

/* french_oss_keycodes.h */


#pragma once
#include "keycodes.h"
// clang-format off


// BASE Keycodes
#define FR_AMPR  KC_1     // &
#define FR_EACU  KC_2     // é
#define FR_DQUO  KC_3     // "
#define FR_QUOT  KC_4     // '
#define FR_LPRN  KC_5     // (
#define FR_MINS  KC_6     // -
#define FR_EGRV  KC_7     // è
#define FR_UNDS  KC_8     // _
#define FR_CCED  KC_9     // ç
#define FR_AGRV  KC_0     // à
#define FR_RPRN  KC_MINS  // )
#define FR_EQL   KC_EQL   // =

#define FR_A     KC_Q     // A
#define FR_Z     KC_W     // Z
#define FR_E     KC_E     // E
#define FR_R     KC_R     // R
#define FR_T     KC_T     // T
#define FR_Y     KC_Y     // Y
#define FR_U     KC_U     // U
#define FR_I     KC_I     // I
#define FR_O     KC_O     // O
#define FR_P     KC_P     // P
#define FR_DCIR  KC_LBRC  // ^ (dead)
#define FR_DLR   KC_RBRC  // $

#define FR_Q     KC_A     // Q
#define FR_S     KC_S     // S
#define FR_D     KC_D     // D
#define FR_F     KC_F     // F
#define FR_G     KC_G     // G
#define FR_H     KC_H     // H
#define FR_J     KC_J     // J
#define FR_K     KC_K     // K
#define FR_L     KC_L     // L
#define FR_M     KC_SCLN  // M
#define FR_UGRV  KC_QUOT  // ù
#define FR_ASTR  KC_NUHS  // *

#define FR_LABK  KC_NUBS  // <
#define FR_W     KC_Z     // W
#define FR_X     KC_X     // X
#define FR_C     KC_C     // C
#define FR_V     KC_V     // V
#define FR_B     KC_B     // B
#define FR_N     KC_N     // N
#define FR_COMM  KC_M     // ,
#define FR_SCLN  KC_COMM  // ;
#define FR_COLN  KC_DOT   // :
#define FR_EXLM  KC_SLSH  // !

// LSFT Keycodes
#define FR_1     LSFT(KC_1)     // 1
#define FR_2     LSFT(KC_2)     // 2
#define FR_3     LSFT(KC_3)     // 3
#define FR_4     LSFT(KC_4)     // 4
#define FR_5     LSFT(KC_5)     // 5
#define FR_6     LSFT(KC_6)     // 6
#define FR_7     LSFT(KC_7)     // 7
#define FR_8     LSFT(KC_8)     // 8
#define FR_9     LSFT(KC_9)     // 9
#define FR_0     LSFT(KC_0)     // 0
#define FR_DEG   LSFT(KC_MINS)  // °
#define FR_PLUS  LSFT(KC_EQL)   // +

#define FR_DDIA  LSFT(KC_LBRC)  // ¨ (dead)

#define FR_PERC  LSFT(KC_QUOT)  // %

#define FR_RABK  LSFT(KC_NUBS)  // >
#define FR_QUES  LSFT(KC_M)     // ?
#define FR_DOT   LSFT(KC_COMM)  // .
#define FR_SLSH  LSFT(KC_DOT)   // /


// RALT Keycodes
#define FR_TILD  RALT(KC_2)     // ~
#define FR_HASH  RALT(KC_3)     // #
#define FR_LCBR  RALT(KC_4)     // {
#define FR_LBRC  RALT(KC_5)     // [
#define FR_PIPE  RALT(KC_6)     // |
#define FR_GRV   RALT(KC_7)     // `
#define FR_BSLS  RALT(KC_8)     // (backslash)
#define FR_CIRC  RALT(KC_9)     // ^
#define FR_AT    RALT(KC_0)     // @
#define FR_RBRC  RALT(KC_MINS)  // ]
#define FR_RCBR  RALT(KC_EQL)   // }

#define FR_AELG  RALT(KC_Q)     // Æ
#define FR_ACIR  RALT(KC_W)     // Â
#define FR_EURO  RALT(KC_E)     // €
#define FR_ECIR  RALT(KC_R)     // Ê
#define FR_YDIA  RALT(KC_Y)     // Ÿ
#define FR_UCIR  RALT(KC_U)     // Û
#define FR_ICIR  RALT(KC_I)     // Î
#define FR_OELG  RALT(KC_O)     // Œ
#define FR_OCIR  RALT(KC_P)     // Ô

#define FR_ADIA  RALT(KC_A)     // Ä
#define FR_EDIA  RALT(KC_D)     // Ë
#define FR_UDIA  RALT(KC_J)     // Ü
#define FR_IDIA  RALT(KC_K)     // Ï
#define FR_ODIA  RALT(KC_SCLN)  // Ö

#define FR_OG    RALT(KC_Z)     // «
#define FR_FG    RALT(KC_X)     // »


// SAGR Keycodes
#define FR_EM    SAGR(KC_4)     // —
#define FR_EN    SAGR(KC_5)     // –

#define FR_DOTS  SAGR(KC_M)     // …


/*************************
 *** Send String Codes ***
 *************************/


#define SS_FG    SS_RALT("x")

#define SS_LEFT  SS_TAP(X_LEFT)

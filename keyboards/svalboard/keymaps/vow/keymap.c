/* keymaps/vow/keymap.c */


#include QMK_KEYBOARD_H


#include "vow.h"


/***************
 *** Keymaps ***
 ***************/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LYR_DEF] = LAYOUT(
    FR_X,    FR_Q,    FR_Y,    FR_P,    FR_E,     /**/  KC_SPC,  FR_M,    FR_L,    FR_J,    FR_K,
    FR_O,    FR_A,    FR_I,    FR_T,    OS_LSFT,  /**/  OSL_SYM, FR_S,    FR_N,    FR_R,    FR_U,
    FR_AGRV, FR_EGRV, FR_EACU, FR_D,    KC_ESC,   /**/  QK_REP,  FR_C,    FR_H,    FR_W,    FR_Z,
    FR_COMM, FR_QUES, FR_AT,   FR_B,    OSL_DIA,  /**/  KC_ENT,  FR_F,    FR_MINS, FR_EXLM, FR_DOT,
    FR_SCLN, FR_DQUO, FR_UNDS, FR_V,    CW_TOGG,  /**/  KC_TAB,  FR_G,    FR_HASH, FR_QUOT, FR_COLN,
    /**/                                KC_DEL,   /**/  KC_BSPC
  ),

  [LYR_SYM] = LAYOUT(
    FR_7,    FR_5,    FR_1,    FR_3,    _______,  /**/  _______, FR_2,    FR_0,    FR_4,    FR_6,
    FR_EQL,  FR_LBRC, FR_LPRN, FR_LCBR, _______,  /**/  _______, FR_RCBR, FR_RPRN, FR_RBRC, FR_TILD,
    FR_BSLS, FR_PIPE, FR_SLSH, FR_MINS, _______,  /**/  _______, FR_PLUS, FR_ASTR, FR_AMPR, FR_PERC,
    _______, _______, FR_CIRC, FR_LABK, _______,  /**/  _______, FR_RABK, FR_DLR,  _______, _______,
    _______, _______, _______, FR_9,    _______,  /**/  _______, FR_8,    _______, _______, _______,
    /**/                                _______,  /**/  _______
  ),

  [LYR_NAV] = LAYOUT(
    FR_7,    FR_5,    FR_1,    FR_3,    _______,  /**/  _______, FR_2,    FR_0,    FR_4,    FR_6,
    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,  /**/  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,  /**/  _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    _______, _______, _______, _______, _______,  /**/  _______, _______, _______, _______, _______,
    _______, _______, _______, FR_9,    _______,  /**/  _______, FR_8,    _______, _______, _______,
    /**/                                _______,  /**/  _______
  ),

  [LYR_DIA] = LAYOUT(
    _______, _______, _______, _______, _______,  /**/  _______, _______, _______, _______, _______,
    FR_OCIR, FR_ACIR, FR_ICIR, _______, _______,  /**/  _______, _______, _______, _______, FR_UCIR,
    _______, FR_ECIR, FR_EDIA, _______, _______,  /**/  _______, FR_CCED, _______, _______, _______,
    FR_ODIA, FR_ADIA, FR_IDIA, FR_OG,   _______,  /**/  _______, FR_FG,   _______, _______, FR_UDIA,
    FR_OELG, FR_AELG, _______, _______, _______,  /**/  _______, _______, _______, _______, FR_UGRV,
    /**/                                _______,  /**/  _______
  ),

  [LYR_FUN] = LAYOUT(
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  /**/  _______, KC_BRID, KC_BRIU, KC_PSCR, _______,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,  /**/  _______, KC_MPRV, KC_MNXT, KC_MPLY, _______,
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,  /**/  _______, KC_VOLD, KC_VOLU, KC_MUTE, _______,
    _______, _______, _______, _______, _______,  /**/  _______, _______, KC_MFFD, _______, _______,
    _______, _______, _______, _______, _______,  /**/  _______, KC_MRWD, _______, _______, _______,
    /**/                                _______,  /**/  _______
  ),

  [LYR_HLD] = LAYOUT(
    _______, _______, _______, _______, _______,  /**/  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, SFT_HLD,  /**/  SYM_HLD, _______, _______, _______, _______,
    _______, _______, _______, _______, ALT_HLD,  /**/  FUN_HLD, _______, _______, _______, _______,
    _______, _______, _______, _______, DIA_HLD,  /**/  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  /**/  NAV_HLD, _______, _______, _______, _______,
    /**/                                CTL_HLD,  /**/  _______
  ),
};


/**************
 *** Combos ***
 **************/


static const uint16_t PROGMEM tnav_combo[] = { OS_LSFT, OSL_SYM, COMBO_END };

static const uint16_t PROGMEM lclk_combo[] = { FR_EACU, FR_D,    COMBO_END };
static const uint16_t PROGMEM mclk_combo[] = { FR_EGRV, FR_EACU, COMBO_END };
static const uint16_t PROGMEM rclk_combo[] = { FR_AGRV, FR_EGRV, COMBO_END };


combo_t key_combos[] = {
  COMBO(tnav_combo, TGL_NAV),

  COMBO(lclk_combo, MS_BTN1),
  COMBO(mclk_combo, MS_BTN2),
  COMBO(rclk_combo, MS_BTN3),
};


/*********************
 *** Key Overrides ***
 *********************/


const key_override_t *key_overrides[] = {
  &KO_MAKE_REPEAT(MOD_MASK_SHIFT, FR_QUOT, FR_GRV,  FR_GRV),
  &KO_MAKE_REPEAT(MOD_MASK_SHIFT, FR_DOT,  FR_DOTS, FR_DOTS),

  &ko_make_basic(MOD_MASK_SHIFT, FR_GRV,  FR_GRV),
  &ko_make_basic(MOD_MASK_SHIFT, FR_DOTS, FR_DOTS),

  &ko_make_basic(MOD_MASK_SHIFT, FR_AGRV, SAGR(FR_AGRV)),
  &ko_make_basic(MOD_MASK_SHIFT, FR_CCED, SAGR(FR_CCED)),
  &ko_make_basic(MOD_MASK_SHIFT, FR_EACU, SAGR(FR_EACU)),
  &ko_make_basic(MOD_MASK_SHIFT, FR_EGRV, SAGR(FR_EGRV)),
  &ko_make_basic(MOD_MASK_SHIFT, FR_UGRV, SAGR(FR_UGRV)),
};


/***************************
 *** Userspace Variables ***
 ***************************/


const keypos_t vow_v_scroll_keypos = { .col = 2, .row = 5 };
const keypos_t vow_h_scroll_keypos = { .col = 3, .row = 5 };

const uint8_t vow_mod_led = 0;
const uint8_t vow_lyr_led = 1;

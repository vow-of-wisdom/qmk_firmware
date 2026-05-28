/* keymaps/vow/keymap.c */


#include QMK_KEYBOARD_H


#include "vow.h"


/****************
 *** Keycodes ***
 ****************/


enum keycode_id {
  WIN_MAX = LGUI(KC_UP),
  WIN_RST = LGUI(KC_DOWN),

  MED_HLD = LT(LYR_MED, KC_TRNS),
};


/***************
 *** Keymaps ***
 ***************/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LYR_DEF] = LAYOUT(
    FR_AGRV, FR_Y,    FR_O,    FR_P,    OS_LSFT,  /**/  KC_TAB,  FR_F,    FR_L,    FR_X,    FR_K,
    FR_A,    FR_I,    FR_E,    FR_T,    OSL_SYM,  /**/  KC_SPC,  FR_S,    FR_N,    FR_R,    FR_U,
    FR_Q,    FR_EACU, FR_EGRV, FR_D,    OSL_DIA,  /**/  KC_ENT,  FR_C,    FR_H,    FR_W,    FR_Z,
    FR_COMM, FR_DQUO, FR_UNDS, FR_V,    QK_REP,   /**/  KC_BSPC, FR_J,    FR_MINS, FR_QUOT, FR_DOT,
    FR_SCLN, FR_QUES, FR_AT,   FR_B,    KC_ESC,   /**/  KC_DEL,  FR_G,    FR_M,    FR_EXLM, FR_COLN,
    /**/                                CW_TOGG,  /**/  TGL_NAV
  ),

  [LYR_DIA] = LAYOUT(
    FR_AELG, FR_YDIA, FR_OCIR, _______, _______,  /**/  _______, _______, _______, _______, FR_UGRV,
    FR_ACIR, FR_ICIR, FR_ECIR, _______, _______,  /**/  FR_EURO, _______, _______, _______, FR_UCIR,
    FR_ADIA, FR_IDIA, FR_EDIA, _______, _______,  /**/  _______, FR_CCED, _______, _______, FR_UDIA,
    _______, _______, FR_OELG, _______, _______,  /**/  FR_DCIR, _______, _______, FR_GRV,  FR_DOTS,
    _______, _______, FR_ODIA, FR_OG,   _______,  /**/  FR_DDIA, FR_FG,   _______, _______, _______,
    /**/                                _______,  /**/  _______
  ),

  [LYR_SYM] = LAYOUT(
    FR_7,    FR_5,    FR_1,    FR_3,    _______,  /**/  _______, FR_2,    FR_0,    FR_4,    FR_6,
    FR_EQL,  FR_LBRC, FR_LCBR, FR_LPRN, _______,  /**/  _______, FR_RPRN, FR_RCBR, FR_RBRC, FR_TILD,
    FR_BSLS, FR_PIPE, FR_SLSH, FR_MINS, _______,  /**/  _______, FR_PLUS, FR_ASTR, FR_AMPR, FR_PERC,
    _______, _______, _______, FR_LABK, _______,  /**/  _______, FR_RABK, FR_HASH, _______, _______,
    _______, _______, FR_CIRC, FR_9,    _______,  /**/  _______, FR_8,    FR_DLR,  _______, _______,
    /**/                                _______,  /**/  _______
  ),

  [LYR_NAV] = LAYOUT(
    FR_7,    FR_5,    FR_1,    FR_3,    _______,  /**/  _______, FR_2,    FR_0,    FR_4,    FR_6,
    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,  /**/  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,  /**/  _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    _______, MS_BTN3, MS_BTN2, MS_BTN1, _______,  /**/  _______, CH_DESK, WIN_RST, WIN_MAX, _______,
    _______, _______, _______, FR_9,    _______,  /**/  _______, FR_8,    _______, _______, _______,
    /**/                                _______,  /**/  _______
  ),

  [LYR_FUN] = LAYOUT(
    VI_WSGL, VI_WDEL, VI_VRTL, VI_HRZL, VI_SAVE,  /**/  _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,
    VI_WLFT, VI_WDWN, VI_WUP,  VI_WRGT, VI_MAKE,  /**/  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,
    VI_CPRV, VI_CNXT, VI_BPRV, VI_BNXT, _______,  /**/  _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,
    _______, _______, _______, VI_BDEL, VI_QUIT,  /**/  _______, TRM_LGT, KC_BRIU, KC_PSCR, _______,
    _______, _______, _______, VI_BCLR, _______,  /**/  _______, TRM_DRK, KC_BRID, KC_INS,  _______,
    /**/                                _______,  /**/  _______
  ),

  [LYR_MED] = LAYOUT(
    _______, _______, _______, _______, _______,  /**/  _______, MOC_NXT, MOC_JMP, MOC_SFL, _______,
    _______, _______, _______, _______, _______,  /**/  _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,
    _______, _______, _______, _______, _______,  /**/  _______, KC_VOLD, KC_MUTE, KC_VOLU, _______,
    _______, _______, _______, _______, _______,  /**/  _______, _______, _______, KC_MFFD, _______,
    _______, _______, _______, _______, _______,  /**/  _______, KC_MRWD, _______, _______, _______,
    /**/                                _______,  /**/  _______
  ),

  [LYR_HLD] = LAYOUT(
    _______, _______, _______, _______, SFT_HLD,  /**/  NAV_HLD, _______, _______, _______, _______,
    _______, _______, _______, _______, SYM_HLD,  /**/  FUN_HLD, _______, _______, _______, _______,
    _______, _______, _______, _______, DIA_HLD,  /**/  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, CTL_HLD,  /**/  MED_HLD, _______, _______, _______, _______,
    _______, _______, _______, _______, ALT_HLD,  /**/  _______, _______, _______, _______, _______,
    /**/                                _______,  /**/  _______
  ),
};


/**************
 *** Combos ***
 **************/


static const uint16_t PROGMEM lclk_combo[] = { FR_EGRV, FR_D,    COMBO_END };
static const uint16_t PROGMEM mclk_combo[] = { FR_EACU, FR_EGRV, COMBO_END };
static const uint16_t PROGMEM rclk_combo[] = { FR_Q,    FR_EACU, COMBO_END };


combo_t key_combos[] = {
  COMBO(lclk_combo, MS_BTN1),
  COMBO(mclk_combo, MS_BTN2),
  COMBO(rclk_combo, MS_BTN3),
};


/*********************
 *** Key Overrides ***
 *********************/


const key_override_t *key_overrides[] = {
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

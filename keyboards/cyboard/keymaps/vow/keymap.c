/* keymaps/vow/keymap.c */


#include QMK_KEYBOARD_H


#include "vow.h"


/**************
 *** Layers ***
 **************/


#define IS_LAYER_NUM  (IS_LAYER_ON(LYR_SYM) || IS_LAYER_ON(LYR_NAV))


/****************
 *** Keycodes ***
 ****************/


enum keycode_id {
  SFT_TAB = S(KC_TAB),

  UP_DIR  = VOW_SAFE_RANGE,
};


/***************
 *** Keymaps ***
 ***************/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LYR_DEF] = LAYOUT(
    MV_DESK, CH_DESK, FR_Y,    FR_O,    FR_P,    FR_B,              /**/           FR_J,    FR_F,    FR_L,    FR_QUOT, TRM_LGT, TRM_DRK,
    KC_CAPS, FR_AGRV, FR_I,    FR_E,    FR_T,    FR_V,              /**/           FR_G,    FR_S,    FR_N,    FR_R,    FR_K,    FR_DQUO,
    FR_COMM, FR_A,    FR_EACU, FR_EGRV, FR_D,    FR_W,              /**/           FR_X,    FR_C,    FR_H,    FR_M,    FR_U,    FR_DOT,
    KC_BSPC, FR_Q,    KC_MPRV, KC_MNXT, QK_AREP, QK_REP,  OS_LSFT,  /**/  KC_ENT,  KC_SPC,  OSL_SYM, KC_VOLD, KC_VOLU, FR_Z,    KC_ESC,
    /**/                                         FR_AT,   FR_EURO,  /**/  FR_UNDS, OSL_DIA
  ),

  [LYR_DIA] = LAYOUT(
    _______, _______, FR_YDIA, FR_OCIR, FR_ODIA, _______,           /**/           _______, _______, _______, FR_GRV,  _______, _______,
    _______, FR_AELG, FR_ICIR, FR_ECIR, FR_EDIA, FR_OG,             /**/           FR_FG,   _______, _______, _______, FR_UGRV, _______,
    _______, FR_ACIR, FR_IDIA, FR_OELG, _______, _______,           /**/           _______, FR_CCED, _______, _______, FR_UCIR, FR_DOTS,
    _______, FR_ADIA, _______, _______, FR_DDIA, FR_DCIR, _______,  /**/  _______, _______, _______, _______, _______, FR_UDIA, _______,
    /**/                                         _______, _______,  /**/  _______, _______
  ),

  [LYR_SYM] = LAYOUT(
    _______, _______, FR_5,    FR_1,    FR_3,    FR_9,              /**/           FR_8,    FR_2,    FR_0,    FR_4,    _______, _______,
    _______, FR_7,    FR_LBRC, FR_LCBR, FR_LPRN, FR_LABK,           /**/           FR_RABK, FR_RPRN, FR_RCBR, FR_RBRC, FR_6,    FR_HASH,
    _______, FR_EQL,  FR_PIPE, FR_SLSH, FR_MINS, FR_CIRC,           /**/           FR_DLR,  FR_PLUS, FR_ASTR, FR_AMPR, FR_TILD, _______,
    _______, FR_BSLS, _______, _______, _______, _______, _______,  /**/  _______, _______, _______, _______, _______, FR_PERC, _______,
    /**/                                         _______, _______,  /**/  _______, _______
  ),

  [LYR_NAV] = LAYOUT(
    _______, _______, FR_5,    FR_1,    FR_3,    FR_9,              /**/           FR_8,    FR_2,    FR_0,    FR_4,    _______, _______,
    _______, FR_7,    KC_DOWN, KC_UP,   KC_RGHT, FR_PAST,           /**/           FR_COPY, KC_LEFT, KC_DOWN, KC_UP,   FR_6,    _______,
    _______, KC_LEFT, KC_PGDN, KC_PGUP, KC_END,  FR_SALL,           /**/           FR_CUT,  KC_HOME, KC_PGDN, KC_PGUP, KC_RGHT, _______,
    _______, KC_HOME, _______, _______, _______, _______, _______,  /**/  _______, _______, _______, _______, _______, KC_END,  _______,
    /**/                                         _______, _______,  /**/  _______, _______
  ),

  [LYR_FUN] = LAYOUT(
    _______, _______, VI_WDEL, VI_VRTL, VI_HRZL, _______,           /**/           KC_BRIU, KC_F9,   KC_F10,  KC_F11,  _______, _______,
    _______, VI_WSGL, VI_WDWN, VI_WUP,  VI_WRGT, VI_BCLR,           /**/           KC_PSCR, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,
    _______, VI_WLFT, VI_CNXT, VI_BPRV, VI_BNXT, VI_BDEL,           /**/           KC_BRID, KC_F5,   KC_F6,   KC_F7,   KC_F4,   _______,
    _______, VI_CPRV, KC_MRWD, KC_MFFD, VI_MAKE, VI_SAVE, VI_QUIT,  /**/  _______, _______, _______, MOC_NXT, MOC_SFL, KC_F8,   _______,
    /**/                                         _______, _______,  /**/  _______, _______
  ),

  [LYR_HLD] = LAYOUT(
    _______, _______, _______, _______, _______, _______,           /**/           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,           /**/           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,           /**/           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, ALT_HLD, CTL_HLD, SFT_HLD,  /**/  FUN_HLD, NAV_HLD, SYM_HLD, _______, _______, _______, _______,
    /**/                                         _______, _______,  /**/  _______, DIA_HLD
  ),
};


/**************
 *** Combos ***
 **************/


static const uint16_t PROGMEM tnav_combo[] = { QK_REP,  KC_SPC,  COMBO_END };

static const uint16_t PROGMEM lclk_combo[] = { FR_EGRV, FR_D,    COMBO_END };
static const uint16_t PROGMEM mclk_combo[] = { FR_Q,    FR_EACU, COMBO_END };
static const uint16_t PROGMEM rclk_combo[] = { FR_EACU, FR_EGRV, COMBO_END };

static const uint16_t PROGMEM play_combo[] = { KC_MPRV, KC_MNXT, COMBO_END };
static const uint16_t PROGMEM mute_combo[] = { KC_VOLD, KC_VOLU, COMBO_END };


combo_t key_combos[] = {
  COMBO(tnav_combo, TGL_NAV),

  COMBO(lclk_combo, MS_BTN1),
  COMBO(mclk_combo, MS_BTN2),
  COMBO(rclk_combo, MS_BTN3),

  COMBO(play_combo, KC_MPLY),
  COMBO(mute_combo, KC_MUTE),
};


/*********************
 *** Key Overrides ***
 *********************/


#define KO_MAKE_REPEAT(mods, trig, repl, rept)                  \
  (const key_override_t) {                                      \
    .options         = ko_options_default | ko_option_one_mod,  \
    .trigger_mods    = mods,                                    \
    .suppressed_mods = MOD_MASK_SHIFT,                          \
    .custom_action   = repeat_override,                         \
    .context         = (void*) rept,                            \
    .trigger         = trig,                                    \
    .replacement     = repl,                                    \
    .layers          = ~0,                                      \
  }


static bool
repeat_override(bool pressed, void *vkc) {
  if (pressed) {
    set_last_keycode((uint16_t) (uintptr_t) vkc);
    set_last_mods(0);
  }
  return true;
}


const key_override_t *key_overrides[] = {
  &KO_MAKE_REPEAT(MOD_MASK_SHIFT, KC_BSPC, KC_DEL,  KC_DEL),
  &KO_MAKE_REPEAT(MOD_MASK_CSA,   KC_SPC,  KC_TAB,  KC_TAB),
  &KO_MAKE_REPEAT(MOD_MASK_CSA,   KC_ENT,  SFT_TAB, KC_TAB),

  &KO_MAKE_REPEAT(MOD_MASK_SHIFT, FR_DOT,  FR_COLN, FR_COLN),
  &KO_MAKE_REPEAT(MOD_MASK_SHIFT, FR_DQUO, FR_EXLM, FR_EXLM),
  &KO_MAKE_REPEAT(MOD_MASK_SHIFT, FR_QUOT, FR_QUES, FR_QUES),
  &KO_MAKE_REPEAT(MOD_MASK_SHIFT, FR_COMM, FR_SCLN, FR_SCLN),

  &ko_make_basic(MOD_MASK_SHIFT, KC_DEL, KC_DEL),
  &ko_make_basic(MOD_MASK_SHIFT, KC_TAB, KC_TAB),

  &ko_make_basic(MOD_MASK_SHIFT, FR_DCIR, FR_DCIR),
  &ko_make_basic(MOD_MASK_SHIFT, FR_COLN, FR_COLN),
  &ko_make_basic(MOD_MASK_SHIFT, FR_EXLM, FR_EXLM),
  &ko_make_basic(MOD_MASK_SHIFT, FR_SCLN, FR_SCLN),

  &ko_make_basic(MOD_MASK_SHIFT, FR_AGRV, SAGR(FR_AGRV)),
  &ko_make_basic(MOD_MASK_SHIFT, FR_CCED, SAGR(FR_CCED)),
  &ko_make_basic(MOD_MASK_SHIFT, FR_EACU, SAGR(FR_EACU)),
  &ko_make_basic(MOD_MASK_SHIFT, FR_EGRV, SAGR(FR_EGRV)),
  &ko_make_basic(MOD_MASK_SHIFT, FR_UGRV, SAGR(FR_UGRV)),
};


/******************
 *** Repeat Key ***
 ******************/


uint16_t
get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
  case FR_A    : return FR_Q;
  case FR_B    : return FR_D;
  case FR_C    : return FR_S;
  case FR_D    : return FR_V;
  case FR_E    : return FR_O;
  case FR_F    : return FR_S;
  case FR_G    : return FR_S;
  case FR_H    : return FR_L;
  case FR_I    : return FR_EACU;
  case FR_K    : return FR_U;
  case FR_L    : return FR_H;
  case FR_M    : return FR_QUOT;
  case FR_N    : return FR_L;
  case FR_O    : return FR_E;
  case FR_P    : return FR_T;
  case FR_Q    : return FR_A;
  case FR_R    : return FR_M;
  case FR_S    : return FR_C;
  case FR_T    : return FR_W;
  case FR_U    : return FR_Z;
  case FR_V    : return FR_D;
  case FR_W    : return FR_O;
  case FR_X    : return FR_C;
  case FR_Y    : return FR_EACU;
  case FR_Z    : return FR_U;
  case FR_EACU : return FR_I;

  case FR_QUOT : return FR_R;
  case FR_COMM : return FR_7;
  case FR_DOT  : return IS_LAYER_NUM ? FR_6 : UP_DIR;
  case FR_RPRN : return FR_SCLN;

  case FR_0    : return FR_X;
  case FR_2    : return FR_8;
  case FR_3    : return FR_9;
  case FR_6    : return FR_DOT;
  case FR_7    : return FR_COMM;
  case FR_8    : return FR_2;
  case FR_9    : return FR_3;

  case FR_BSLS : return FR_EQL;
  case FR_EXLM : return FR_EQL;

  case KC_BSPC : return KC_DEL;
  case KC_DEL  : return KC_BSPC;

  case QK_MOUSE_BUTTON_1 ... QK_MOUSE_BUTTON_8 :
    return QK_MOUSE_BUTTON_3;
  }

  return KC_NO;
}


/*********************************
 *** Custom Keycode Processing ***
 *********************************/


bool
process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  static bool play_combo_overriden = false;
  static bool mute_combo_overriden = false;

  switch (keycode) {
  case UP_DIR :
    if (record->event.pressed) {
      if (get_repeat_key_count() == -1) {
        SEND_STRING("./");
      } else if (get_repeat_key_count() < 0) {
        SEND_STRING("../");
      }
    }
    break;

  case KC_MPLY :
    if (record->event.pressed) {
      if (IS_LAYER_ON(LYR_FUN)) {
        register_code16(MOC_JMP);
        play_combo_overriden = true;
        return false;
      }
    } else {
      if (play_combo_overriden) {
        unregister_code16(MOC_JMP);
        play_combo_overriden = false;
        return false;
      }
    }
    break;

  case KC_MUTE :
    if (record->event.pressed) {
      if (IS_LAYER_ON(LYR_FUN)) {
        register_code16(SND_DEV);
        mute_combo_overriden = true;
        return false;
      }
    } else {
      if (mute_combo_overriden) {
        unregister_code16(SND_DEV);
        mute_combo_overriden = false;
        return false;
      }
    }
    break;
  }

  return true;
}


/***************************
 *** Userspace Variables ***
 ***************************/


const keypos_t vow_v_scroll_keypos = { .col = 1, .row = 7 };
const keypos_t vow_h_scroll_keypos = { .col = 2, .row = 7 };

const uint8_t vow_mod_led =  1;
const uint8_t vow_lyr_led = 28;

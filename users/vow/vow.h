/* vow.h */


#pragma once


#include "french_oss_keycodes.h"


enum vow_layer_id {
  LYR_DEF,
  LYR_DIA,
  LYR_SYM,
  LYR_NAV,
  LYR_FUN,
#ifdef VOW_EXTRA_LAYERS
  VOW_EXTRA_LAYERS,
#endif
  LYR_HLD,
};


enum vow_keycode_id {
  FR_SALL = C(FR_A),
  FR_COPY = C(FR_C),
  FR_PAST = C(FR_V),
  FR_CUT  = C(FR_X),

  TGL_NAV = TG(LYR_NAV),

  OSL_DIA = OSL(LYR_DIA),
  OSL_SYM = OSL(LYR_SYM),

  DIA_HLD = LT(LYR_DIA, KC_TRNS),
  SYM_HLD = LT(LYR_SYM, KC_TRNS),
  NAV_HLD = LT(LYR_NAV, KC_TRNS),
  FUN_HLD = LT(LYR_FUN, KC_TRNS),

  ALT_HLD = LALT_T(KC_TRNS),
  CTL_HLD = LCTL_T(KC_TRNS),
  SFT_HLD = LSFT_T(KC_TRNS),

  CH_DESK = LGUI(KC_RGHT),
  MV_DESK = LSG(KC_RGHT),
  TRM_LGT = LCA(FR_W),
  TRM_DRK = LCA(FR_B),

  MOC_NXT = LGUI(FR_N),
  MOC_SFL = LGUI(FR_S),
  MOC_JMP = LGUI(FR_G),
  SND_DEV = LGUI(FR_D),

  VI_BCLR = SAFE_RANGE,
  VI_BDEL,
  VI_BNXT,
  VI_BPRV,
  VI_CNXT,
  VI_CPRV,
  VI_MAKE,
  VI_QUIT,
  VI_SAVE,

  VI_HRZL,
  VI_VRTL,
  VI_WDEL,
  VI_WSGL,
  VI_WLFT,
  VI_WDWN,
  VI_WUP,
  VI_WRGT,

  VOW_SAFE_RANGE
};


extern const keypos_t vow_v_scroll_keypos;
extern const keypos_t vow_h_scroll_keypos;

extern const uint8_t vow_lyr_led;
extern const uint8_t vow_mod_led;


extern bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

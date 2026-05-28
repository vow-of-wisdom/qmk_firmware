/* vow.c */


#include QMK_KEYBOARD_H

#include "vow.h"

#include "print.h"
#include "transactions.h"


/********************
 *** Keymap Hooks ***
 ********************/


bool __attribute__((weak))
process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}


/**************
 *** Layers ***
 **************/


#define LYR_BIT(lyr)  (1 << lyr)


/******************
 *** Repeat Key ***
 ******************/


bool
remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *mods) {
  switch (keycode) {
  case KC_AUDIO_MUTE     ... KC_MEDIA_PLAY_PAUSE   :
  case QK_ONE_SHOT_MOD   ... QK_ONE_SHOT_MOD_MAX   :
  case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX :
    return false;
  case QK_LAYER_TAP ... QK_LAYER_TAP_MAX :
    return QK_LAYER_TAP_GET_TAP_KEYCODE(keycode) != KC_TRNS;
  case QK_MOD_TAP ... QK_MOD_TAP_MAX :
    return QK_MOD_TAP_GET_TAP_KEYCODE(keycode) != KC_TRNS;
  }
  return true;
}


/****************
 *** LED Data ***
 ****************/


struct led_data {
  uint8_t layer_tg;
  uint8_t layer_os;
  uint8_t mod_tg;
  uint8_t mod_lk;
  uint8_t mod_os;
  bool bright;
};


#define LED_DATA_INIT  { 0 }


static struct led_data led_data = LED_DATA_INIT;
static uint8_t layer_dn = 0;
static uint8_t mod_dn = 0;


static const rgb_t lyrs_colors[] = {
  { RGB_OFF    }, { RGB_ORANGE }, { RGB_RED }, { RGB_ORANGE },
  { RGB_YELLOW }, { RGB_ORANGE }, { RGB_OFF }, { RGB_ORANGE },
};


static const rgb_t mods_colors[] = {
  { RGB_OFF    }, { RGB_CYAN }, { RGB_ORANGE }, { RGB_MAGENTA },
  { RGB_YELLOW }, { RGB_CYAN }, { RGB_ORANGE }, { RGB_MAGENTA },
  { RGB_OFF    }, { RGB_CYAN }, { RGB_ORANGE }, { RGB_MAGENTA },
  { RGB_RED    }, { RGB_CYAN }, { RGB_ORANGE }, { RGB_MAGENTA },
};


#define SET_COLOR(lid, cid, tab)                 \
  do {                                           \
    uint8_t r = tab[cid].r >> !led_data.bright;  \
    uint8_t g = tab[cid].g >> !led_data.bright;  \
    uint8_t b = tab[cid].b >> !led_data.bright;  \
    rgblight_setrgb_at(r, g, b, lid);            \
  } while (0)


#define IS_LAYER_OS(layer)  (is_os_on && led_data.layer_os == layer)
#define IS_LAYER_TG(layer)  (led_data.layer_tg == layer)

#define IS_SHIFT_OS  (is_os_on && led_data.mod_os & MOD_LSFT)
#define IS_SHIFT_TG  ((bool) (led_data.mod_tg & MOD_LSFT))
#define IS_SHIFT_LK  ((bool) (led_data.mod_lk & MOD_LSFT))


static void
update_leds(bool force) {
  static uint16_t timer = 0;
  if (force || sync_timer_elapsed(timer) > 0x100) {
    timer = sync_timer_read();
    bool is_os_on = timer & 0x200;

    uint8_t lyrs_index =
      IS_LAYER_OS(LYR_SYM)
      | IS_LAYER_TG(LYR_SYM) << 1
      | IS_LAYER_TG(LYR_NAV) << 2;

    uint8_t mods_index =
      IS_LAYER_OS(LYR_DIA)
      | IS_SHIFT_OS << 1
      | IS_SHIFT_TG << 2
      | IS_SHIFT_LK << 3;

    SET_COLOR(vow_lyr_led, lyrs_index, lyrs_colors);
    SET_COLOR(vow_mod_led, mods_index, mods_colors);
  }
}


static void
led_data_recv(uint8_t src_len, const void *src, uint8_t dst_len, void *dst) {
  memcpy(&led_data, src, src_len);
  update_leds(true);
}


static void
led_data_send(void) {
  static struct led_data led_data_sent = LED_DATA_INIT;
  if (memcmp(&led_data_sent, &led_data, sizeof led_data)) {
    if (transaction_rpc_send(LED_DATA, sizeof led_data, &led_data)) {
      led_data_sent = led_data;
      update_leds(true);
    }
  }
}


/************************************
 *** Modifier and Layer Utilities ***
 ************************************/


static bool one_shot_used = false;


static void
layer_update(void) {
  layer_state_t state = LYR_BIT(LYR_HLD);
  if (layer_dn) {
    if (layer_dn != led_data.layer_tg) {
      state |= LYR_BIT(layer_dn);
    }
  } else if (led_data.layer_os) {
    if (led_data.layer_os != led_data.layer_tg) {
      state |= LYR_BIT(led_data.layer_os);
    }
  } else if (led_data.layer_tg) {
    state |= LYR_BIT(led_data.layer_tg);
  }
  layer_state_set(state);
}


static void
clear_one_shot(void) {
  if (one_shot_used) {
    led_data.mod_os = led_data.layer_os = 0;
    one_shot_used = false;
    layer_update();
  }
}


static void
mod_toggle_action(keyrecord_t *record, uint8_t mask, uint8_t lock) {
  if (record->event.pressed) {
    led_data.mod_tg ^= mask & ~(led_data.mod_tg & ~led_data.mod_lk & lock);
    led_data.mod_lk ^= mask & (led_data.mod_lk | lock);
    unregister_mods(mask & led_data.mod_tg & mod_dn);
    register_mods(mask & ~led_data.mod_tg & mod_dn);
    led_data.mod_os = 0;
  }
}


static void
mod_one_shot_action(keyrecord_t *record, uint8_t mask) {
  if (record->tap.count == 2 && mask & MOD_LSFT) {
    mod_toggle_action(record, mask, 0);
  } else if (record->event.pressed) {
    led_data.mod_os ^= mask;
  }
}


static void
mod_clear_toggled(uint8_t mask, bool force) {
  if (force || mask & ~led_data.mod_lk) {
    led_data.mod_tg &= ~mask;
    led_data.mod_lk &= ~mask;
    register_mods(mask & mod_dn);
  }
}


static void
mod_press_action(keyrecord_t *record, uint8_t mask) {
  if (record->event.pressed) {
    mod_dn |= mask;
  } else {
    mod_dn &= ~mask;
  }
  unregister_mods(mask & ~mod_dn);
  register_mods(mask & ~led_data.mod_tg & mod_dn);
  if (mask & ~MOD_LSFT) {
    mod_clear_toggled(MOD_LSFT, true);
  }
  led_data.mod_os = 0;
}


static void
mod_set_enabled(keyrecord_t *record, uint8_t invert) {
  uint8_t mods = led_data.mod_tg ^ led_data.mod_os ^ mod_dn ^ invert;
  set_weak_mods(record->event.pressed ? mods : 0);
}


static void
layer_toggle_action(keyrecord_t *record, uint8_t layer) {
  if (record->event.pressed) {
    led_data.layer_tg = layer == led_data.layer_tg ? 0 : layer;
    led_data.layer_os = layer_dn = 0;
    layer_update();
  }
}


static void
layer_one_shot_action(keyrecord_t *record, uint8_t layer) {
  if (record->tap.count == 2 && layer == LYR_SYM) {
    layer_toggle_action(record, layer);
  } else if (record->event.pressed) {
    led_data.layer_os = layer == led_data.layer_os ? 0 : layer;
    layer_dn = 0;
    layer_update();
  }
}


static void
layer_press_action(keyrecord_t *record, uint8_t layer) {
  if (record->event.pressed) {
    layer_dn = layer;
    led_data.layer_os = 0;
  } else if (layer_dn == layer) {
    layer_dn = 0;
  }
  layer_update();
}


static void
layer_clear_toggled(uint8_t layer) {
  if (layer == led_data.layer_tg) {
    led_data.layer_tg = 0;
  }
  layer_update();
}


/*****************
 *** Trackball ***
 *****************/


static bool h_scroll_enabled = false;
static bool v_scroll_enabled = false;


report_mouse_t
pointing_device_task_user(report_mouse_t report) {
  if (get_last_keycode() != QK_MOUSE_BUTTON_1 && (report.x || report.y)) {
    set_last_keycode(QK_MOUSE_BUTTON_1);
  }
  report.h = h_scroll_enabled ?  report.x : 0;
  report.v = v_scroll_enabled ? -report.y : 0;
  if (h_scroll_enabled || v_scroll_enabled) {
    report.x = report.y = 0;
  }
  return report;
}


/****************************
 *** Transparent Tap-Hold ***
 ****************************/


static void
transparent_tap_action(keyrecord_t *record) {
  keypos_t key = record->event.key;
  keyrecord_t tap_record = *record;

  if (record->event.pressed) {
    uint8_t default_layer = get_highest_layer(default_layer_state);
    tap_record.keycode = keymap_key_to_keycode(default_layer, key);
    update_source_layers_cache(key, default_layer);

    uint8_t layer = layer_switch_get_layer(key);
    while (--layer > default_layer) {
      if (IS_LAYER_ON(layer)) {
        uint16_t keycode = keymap_key_to_keycode(layer, key);

        switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX :
          keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
          break;
        case QK_MOD_TAP ... QK_MOD_TAP_MAX :
          keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
          break;
        }

        if (keycode != KC_TRNS) {
          update_source_layers_cache(key, layer);
          tap_record.keycode = keycode;
          break;
        }
      }
    }
  }

  process_record(&tap_record);
}


/*********************************
 *** Custom Keycode Processing ***
 *********************************/


bool
pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (KEYEQ(vow_v_scroll_keypos, record->event.key)) {
    v_scroll_enabled = record->event.pressed;
  }
  if (KEYEQ(vow_h_scroll_keypos, record->event.key)) {
    h_scroll_enabled = record->event.pressed;
  }
  return true;
}


bool
process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QK_LAYER_TAP ... QK_LAYER_TAP_MAX :
    if (!record->tap.count) {
      layer_press_action(record, QK_LAYER_TAP_GET_LAYER(keycode));
      return false;
    } else if (QK_LAYER_TAP_GET_TAP_KEYCODE(keycode) == KC_TRNS) {
      transparent_tap_action(record);
      return false;
    }
    break;

  case QK_MOD_TAP ... QK_MOD_TAP_MAX :
    if (!record->tap.count) {
      mod_press_action(record, QK_MOD_TAP_GET_MODS(keycode));
      return false;
    } else if (QK_MOD_TAP_GET_TAP_KEYCODE(keycode) == KC_TRNS) {
      transparent_tap_action(record);
      return false;
    }
    break;

  case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX :
    mod_one_shot_action(record, QK_ONE_SHOT_MOD_GET_MODS(keycode));
    return true;

  case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX :
    layer_one_shot_action(record, QK_ONE_SHOT_LAYER_GET_LAYER(keycode));
    return true;

  case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX :
    layer_toggle_action(record, QK_TOGGLE_LAYER_GET_LAYER(keycode));
    return false;

  case CW_TOGG :
    mod_toggle_action(record, MOD_LSFT, 0);
    return false;

  case KC_CAPS :
    mod_toggle_action(record, MOD_LSFT, MOD_LSFT);
    return false;
  }

  switch (keycode) {
  case FR_A : case FR_B : case FR_C : case FR_D : case FR_E : case FR_F :
  case FR_G : case FR_H : case FR_I : case FR_J : case FR_K : case FR_L :
  case FR_M : case FR_N : case FR_O : case FR_P : case FR_Q : case FR_R :
  case FR_S : case FR_T : case FR_U : case FR_V : case FR_W : case FR_X :
  case FR_Y : case FR_Z : case FR_1 : case FR_2 : case FR_3 : case FR_4 :
  case FR_5 : case FR_6 : case FR_7 : case FR_8 : case FR_9 : case FR_0 :

  case FR_ACIR : case FR_ADIA : case FR_AELG : case FR_AGRV : case FR_CCED :
  case FR_DCIR : case FR_DDIA : case FR_EACU : case FR_ECIR : case FR_EDIA :
  case FR_EGRV : case FR_ICIR : case FR_IDIA : case FR_OCIR : case FR_ODIA :
  case FR_OELG : case FR_UCIR : case FR_UDIA : case FR_UGRV : case FR_YDIA :
    mod_set_enabled(record, 0);
    break;

  case KC_BSPC : case KC_DEL  : case FR_UNDS :
    mod_set_enabled(record, led_data.mod_tg & MOD_LSFT);
    break;

  case QK_MOUSE_BUTTON_1 ... QK_MOUSE_BUTTON_8 :
    set_last_keycode(QK_MOUSE_BUTTON_1);
    // fall through

  case KC_SPC  : case KC_TAB  : case KC_ENT  :
  case KC_LEFT : case KC_RGHT : case KC_DOWN : case KC_UP   :
  case KC_HOME : case KC_END  : case KC_PGDN : case KC_PGUP :
    mod_clear_toggled(MOD_LSFT, false);
    mod_set_enabled(record, led_data.mod_lk);
    break;

  case KC_ESC :
    mod_clear_toggled(MOD_LSFT, true);
    mod_set_enabled(record, led_data.mod_lk);
    layer_clear_toggled(LYR_SYM);
    break;

  case TRM_DRK :
    if (record->event.pressed) {
      led_data.bright = false;
    }
    mod_clear_toggled(MOD_LSFT, false);
    break;

  case TRM_LGT :
    if (record->event.pressed) {
      led_data.bright = true;
    }
    mod_clear_toggled(MOD_LSFT, false);
    break;

  case CH_DESK : case MV_DESK :
    mod_clear_toggled(MOD_LSFT, false);
    break;

  default :
    mod_clear_toggled(MOD_LSFT, false);
    mod_set_enabled(record, led_data.mod_lk);
  }

  if (record->event.pressed) {
    one_shot_used = led_data.mod_os || led_data.layer_os;

    switch (keycode) {
    case VI_BCLR : SEND_STRING(":Bd\n"); break;
    case VI_BDEL : SEND_STRING(":bd\n"); break;
    case VI_BNXT : SEND_STRING(":bn\n"); break;
    case VI_BPRV : SEND_STRING(":bp\n"); break;
    case VI_CNXT : SEND_STRING(":cn\n"); break;
    case VI_CPRV : SEND_STRING(":cp\n"); break;
    case VI_MAKE : SEND_STRING(":MK\n"); break;
    case VI_QUIT : SEND_STRING(":qa\n"); break;
    case VI_SAVE : SEND_STRING(":wa\n"); break;

    case VI_HRZL : SEND_STRING(SS_LCTL("w") "s"); break;
    case VI_VRTL : SEND_STRING(SS_LCTL("w") "v"); break;
    case VI_WDEL : SEND_STRING(SS_LCTL("w") "c"); break;
    case VI_WSGL : SEND_STRING(SS_LCTL("w") "o"); break;
    case VI_WLFT : SEND_STRING(SS_LCTL("w") "h"); break;
    case VI_WDWN : SEND_STRING(SS_LCTL("w") "j"); break;
    case VI_WUP  : SEND_STRING(SS_LCTL("w") "k"); break;
    case VI_WRGT : SEND_STRING(SS_LCTL("w") "l"); break;
    }
  }

  return process_record_keymap(keycode, record);
}


void
post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  clear_one_shot();
}


/***************************************
 *** Housekeeping and Initialization ***
 ***************************************/


void
housekeeping_task_user(void) {
  if (is_keyboard_master()) {
    led_data_send();
  }
  update_leds(false);
}


void
keyboard_post_init_user(void) {
  transaction_register_rpc(LED_DATA, led_data_recv);
  layer_update();

#ifdef CONSOLE_ENABLE
  debug_enable = true;
#endif
}

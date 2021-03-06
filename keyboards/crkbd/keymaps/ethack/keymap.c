#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _GAME 1
#define _NUMPAD 2
#define _EDIT 3
#define _SYMBOL 4
#define _SHORTCUT 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  GAME,
  NUMPAD,
  EDIT,
  SYMBOL,
  SHORTCUT,
  BACKLIT,
  RGBRST,
};

enum macro_keycodes {
  KC_SHRUG,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define XXXXX KC_NO

#define KC_CUT   C(KC_X)
#define KC_COPY  C(KC_C)
#define KC_PASTE C(KC_V)
#define KC_SALL  C(KC_A)
#define KC_UNDO  C(KC_Z)
#define KC_SAVE  C(KC_S)
#define KC_FIND  C(KC_F)

// Browser
#define KC_TABN  C(KC_T)
#define KC_TABX  C(KC_W)
#define KC_RLOAD C(KC_R)

// Code editor
#define IDENT C(KC_RBRACKET)    // code editor indent
#define DDENT C(KC_LBRACKET)    // code editor dedent
#define CMENT C(KC_SLASH)       // code editor comment toggle

// Google Docs Headings
#define HEAD1 C(A(KC_1))
#define HEAD2 C(A(KC_2))
#define HEAD3 C(A(KC_3))
#define HEAD4 C(A(KC_4))
#define HEAD5 C(A(KC_5))

#define SHOT  S(C(KC_PSCREEN))  // screenshot area to clipboard
// #define KC_HYPRA  HYPR(KC_A)
#define TERM  HYPR(KC_L)  // quake terminal

// workspace movement
#define WKUP C(A(KC_UP))
#define WKDN C(A(KC_DOWN))
#define WKLT C(A(KC_LEFT))
#define WKRT C(A(KC_RIGHT))

// Chrome extension media keys chrome://extensions/shortcuts
// Key Socket Media Keys or Streamkeys
// When these don't work you have to:
// 1. Change the shortcut in Chrome. It has to be one that hasn't been registered globally before (maybe since reboot or restarting Chrome?).
// 2. Switch the shortcut to Chrome-only.
// 3. Switch the shortcut to Global
#define CPRV  A(S(KC_3))
#define CPLY  A(S(KC_2))
#define CNXT  A(S(KC_1))

// Ctrl-Alt-Del
#define CAD LCTL(LALT(KC_DEL))

// #define KC_HYPESC HYPR_T(KC_ESC)
// Actually switches to shortcut layer not hyper key
#define KC_HYPESC LT(_SHORTCUT, KC_ESC)
// #define KC_CTLGUI LCTL_T(KC_LGUI)  // doesn't work

// Dual purpose keys
// #define KC_BSPC_E LT(_EDIT,   KC_BSPC)
// #define KC_TAB_N  LT(_NUMPAD, KC_TAB)
#define KC_ENT_W   LWIN_T(KC_ENT)
#define KC_SPC_S   LT(_SYMBOL, KC_SPC)
#define KC_TAB_CTL LCTL_T(KC_TAB)
#define KC_DEL_ALT LALT_T(KC_DEL)
#define KC_SPC_E   LT(_EDIT, KC_SPC)
#define KC_BSPC_N  LT(_NUMPAD, KC_BSPC)
#define KC_GRV_CTL LCTL_T(KC_GRV)

// Layer toggles
#define QWER TO(_QWERTY)
#define GAME TO(_GAME)
#define NUMP TO(_NUMPAD)
#define EDTI TO(_EDIT) // purpose misspelling to avoid name conflict
#define SYMB TO(_SYMBOL)
#define SHOR TO(_SHORTCUT)

// RGB
#define R_MOD RGB_MOD
#define R_HUI RGB_HUI
#define R_HUD RGB_HUD
#define R_M_P RGB_MODE_PLAIN
#define R_M_X RGB_MODE_XMAS
#define R_M_G RGB_MODE_GRADIENT


// Keymap v2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
    GRV_CTL,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSPO,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSPC,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               TAB_CTL, SPC_E, BSPC_N,    ENT_W, SPC_S, DEL_ALT \
                              //`--------------------'  `--------------------'
  ),

  [_GAME] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    TAB,  SPC,   BSPC,      ENT,   SPC,   DEL \
                              //`--------------------'  `--------------------'
  ),

  [_NUMPAD] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
    GRV_CTL,     1,     2,     3,     4,     5,                      7,     8,     9,  MINS,   EQL,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC, XXXXX, XXXXX, XXXXX, XXXXX,   SPC,                      4,     5,     6,  PLUS,  ASTR,  COMM,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSPO, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                      1,     2,     3,   DOT,  SLSH,   DLR,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               TAB_CTL, SPC_E, BSPC_N,      ENT,     0, DEL_ALT \
                              //`--------------------'  `--------------------'
  ),

  [_EDIT] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
    GRV_CTL, XXXXX,  TABX, XXXXX, RLOAD,  TABN,                   HOME,  PGDN,  PGUP,   END, XXXXX,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC,  SALL,  SAVE, XXXXX,  FIND, XXXXX,                   LEFT,  DOWN,    UP, RIGHT, XXXXX,  LGUI,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSPO,  UNDO,   CUT,  COPY, PASTE, XXXXX,                  XXXXX,  LEFT,  DOWN, RIGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               TAB_CTL, SPC_E, BSPC_N,    ENT_W, SPC_S,  DEL \
                              //`--------------------'  `--------------------'
  ),

  [_SYMBOL] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
         F1,    F2,    F3,    F4,    F5,    F6,                     F7,    F8,    F9,   F10,   F11,   F12,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC,  EXLM,    AT,  HASH,   DLR,  PERC,                   MINS,  LBRC,  RBRC,  PIPE,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSPO, XXXXX, XXXXX,  CIRC,  AMPR,  ASTR,                   PLUS,  LCBR,  RCBR,  BSLS,  SLSH,   EQL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               TAB_CTL, SPC_E,   BSPC,    ENT_W, SPC_S, DEL_ALT \
                              //`--------------------'  `--------------------'
  ),

  [_SHORTCUT] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
        CAD, HEAD1, HEAD2, HEAD3, HEAD4, HEAD5,                  XXXXX,  CPRV,  CPLY,  CNXT, KC_PPLS, KC_VOLU,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  KC_HYPESC,  SHOT, R_M_P, R_HUD, R_HUI, R_M_G,                  DDENT, IDENT,  WKUP,  TERM, KC_PMNS, KC_VOLD,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       QWER,  GAME,  NUMP,  EDTI,  SYMB,  SHOR,                  XXXXX,  WKLT,  WKDN,  WKRT, CMENT, KC_MUTE,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   QWER,  EDTI,  NUMP,     GAME,  SYMB, XXXXX \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting SYMBOL layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        layer_on(_NUMPAD);
        update_tri_layer_RGB(_NUMPAD, _EDIT, _SYMBOL);
      } else {
        layer_off(_NUMPAD);
        update_tri_layer_RGB(_NUMPAD, _EDIT, _SYMBOL);
      }
      return false;
      break;
    case EDIT:
      if (record->event.pressed) {
        layer_on(_EDIT);
        update_tri_layer_RGB(_NUMPAD, _EDIT, _SYMBOL);
      } else {
        layer_off(_EDIT);
        update_tri_layer_RGB(_NUMPAD, _EDIT, _SYMBOL);
      }
      return false;
      break;
    case SYMBOL:
        if (record->event.pressed) {
          layer_on(_SYMBOL);
        } else {
          layer_off(_SYMBOL);
        }
        return false;
        break;
    case SHORTCUT:
        if (record->event.pressed) {
          layer_on(_SHORTCUT);
        } else {
          layer_off(_SHORTCUT);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

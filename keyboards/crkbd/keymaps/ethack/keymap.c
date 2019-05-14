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
#define _NUMPAD 1
#define _EDIT 2
#define _SYMBOL 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD,
  EDIT,
  SYMBOL,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

#define KC_HYPESC HYPR_T(KC_ESC)
// #define KC_CTLGUI LCTL_T(KC_LGUI)

#define KC_BSPC_E LT(_EDIT,   KC_BSPC)
#define KC_TAB_N  LT(_NUMPAD, KC_TAB)
#define KC_ENT_S  LT(_SYMBOL, KC_ENT)
#define KC_SPC_S  LT(_SYMBOL, KC_SPC)

// Keymap v2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSPO,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSPC,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LCTL, BSPC_E, TAB_N,    ENT_S, SPC_S,  LALT \
                              //`--------------------'  `--------------------'
  ),

  [_NUMPAD] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX,     1,     2,     3,     4,     5,                      6,     7,     8,     9,  ASTR,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   MINS,     4,     5,     6,  SCLN,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSPO, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   PLUS,     1,     2,     3,  SLSH,   EQL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LCTL, BSPC_E, TAB_N,      ENT,     0,   DOT \
                              //`--------------------'  `--------------------'
  ),  // Missing comma (under DOT), dollar sign (under 4), and space from numpad layer.

  [_EDIT] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   HOME,  PGDN,  PGUP,   END,  VOLU,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC,  MUTE,  VOLD,  VOLU,  PGUP,  PGDN,                   LEFT,  DOWN,    UP, RIGHT,  COPY,   CUT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSPO,  UNDO,   CUT,  COPY, PASTE, XXXXX,                  PASTE,  LEFT,  DOWN, RIGHT,  VOLD,  MUTE,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LCTL, BSPC_E, TAB_N,   ENT_S, SPC_S,  LALT \
                              //`--------------------'  `--------------------'
  ),

  [_SYMBOL] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   UNDS,  LBRC,  RBRC, XXXXX,  ASTR,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     HYPESC,  EXLM,    AT,  HASH,   DLR,  PERC,                   MINS,  LPRN,  RPRN,  PIPE,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX,  CIRC,  AMPR, XXXXX,                   PLUS,  LCBR,  RCBR,  BSLS,  SLSH, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LCTL, BSPC_E, TAB_N,   ENT_S, SPC_S,  LALT \
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

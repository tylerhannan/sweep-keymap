#include QMK_KEYBOARD_H

/*
 * Compile-time default layout. The live layout is managed in Vial
 * (vial/sweep.vil) and stored in EEPROM, which overrides this at runtime.
 * QMK still requires keymaps[] to exist, so this serves as the fallback that
 * seeds a fresh/reset EEPROM; it is generated to mirror sweep.vil (with the
 * deprecated keycode aliases mapped to current QMK names).
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G, KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_QUOTE),
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH,
        MO(1), KC_SPACE, ALL_T(KC_ENTER), MO(2)
    ),
    [1] = LAYOUT_split_3x5_2(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_ESCAPE, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_BSPC,
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_TRNS, KC_TRNS, MO(3)
    ),
    [2] = LAYOUT_split_3x5_2(
        LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0),
        LSFT(KC_SCLN), LSFT(KC_EQUAL), KC_MINUS, KC_EQUAL, LSFT(KC_MINUS), KC_NO, CW_TOGG, KC_NO, KC_LBRC, KC_RBRC,
        KC_SCLN, KC_GRAVE, LSFT(KC_GRAVE), LSFT(KC_BSLS), KC_BSLS, QK_BOOT, KC_NO, KC_NO, LSFT(KC_LBRC), LSFT(KC_RBRC),
        MO(3), KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_split_3x5_2(
        KC_NO, MS_BTN1, MS_UP, MS_BTN2, MS_WHLD, KC_NO, KC_NO, KC_VOLU, KC_MFFD, KC_NO,
        KC_NO, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLU, KC_NO, KC_NO, KC_MPLY, KC_MRWD, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

/*
 * No get_tapping_term() here: vial-qmk's quantum/vial.c already defines a
 * (non-weak) get_tapping_term() under TAPPING_TERM_PER_KEY, which routes the
 * tapping term through the Vial QMK Settings slider (runtime-adjustable) and
 * per-tap-dance custom terms. Defining one here would collide at link time.
 * The TAPPING_TERM in config.h is the reset/default value for that slider.
 *
 * To restore a static per-finger split instead, see docs/per-finger-tapping-term.md.
 */

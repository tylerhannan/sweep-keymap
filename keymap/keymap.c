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
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_P, KC_O, KC_I, KC_U, KC_Y,
        LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G, RCTL_T(KC_QUOTE), RALT_T(KC_L), RGUI_T(KC_K), RSFT_T(KC_J), KC_H,
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_SLASH, KC_DOT, KC_COMMA, KC_M, KC_N,
        MO(1), KC_SPACE, MO(2), ALL_T(KC_ENTER)
    ),
    [1] = LAYOUT_split_3x5_2(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_0, KC_9, KC_8, KC_7, KC_6,
        KC_ESCAPE, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, KC_RIGHT, KC_UP, KC_DOWN, KC_LEFT,
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_TRNS, MO(3), KC_TRNS
    ),
    [2] = LAYOUT_split_3x5_2(
        LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_0), LSFT(KC_9), LSFT(KC_8), LSFT(KC_7), LSFT(KC_6),
        LSFT(KC_SCLN), LSFT(KC_EQUAL), KC_MINUS, KC_EQUAL, LSFT(KC_MINUS), KC_RBRC, KC_LBRC, KC_NO, KC_NO, KC_NO,
        KC_SCLN, KC_GRAVE, LSFT(KC_GRAVE), LSFT(KC_BSLS), KC_BSLS, LSFT(KC_RBRC), LSFT(KC_LBRC), KC_NO, KC_NO, QK_BOOT,
        MO(3), KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_split_3x5_2(
        KC_NO, MS_BTN1, MS_UP, MS_BTN2, MS_WHLD, KC_NO, KC_MFFD, KC_VOLU, KC_NO, KC_NO,
        KC_NO, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLU, KC_NO, KC_MRWD, KC_MPLY, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// Give the weak-finger home-row mods a longer tapping term to reduce misfires.
// Uses the TAPPING_TERM constant (250 -> 290 on the weak fingers). Reconciling
// this with Vial's runtime tapping-term setting is tracked in the TODO; using
// g_tapping_term here would require DYNAMIC_TAPPING_TERM_ENABLE.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
        case RCTL_T(KC_QUOTE):
        case LALT_T(KC_S):
        case RALT_T(KC_L):
            return TAPPING_TERM + 40;
        default:
            return TAPPING_TERM;
    }
}

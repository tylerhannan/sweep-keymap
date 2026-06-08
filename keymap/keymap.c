#include QMK_KEYBOARD_H

/*
 * TODO: The actual layer layout is managed in Vial (see vial/sweep.vil) and is
 * not defined here. This file only carries compile-time behavior (per-key
 * tapping terms) that Vial does not own.
 */

// Give the weak-finger home-row mods a longer tapping term to reduce misfires.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
        case RCTL_T(KC_QUOTE):
        case LALT_T(KC_S):
        case RALT_T(KC_L):
            return 290;
        default:
            return 250;
    }
}

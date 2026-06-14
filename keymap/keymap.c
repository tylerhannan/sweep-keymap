#include QMK_KEYBOARD_H

/*
 * TODO: The actual layer layout is managed in Vial (see vial/sweep.vil) and is
 * not defined here. This file only carries compile-time behavior (per-key
 * tapping terms) that Vial does not own.
 */

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

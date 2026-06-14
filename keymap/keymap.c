#include QMK_KEYBOARD_H

/*
 * TODO: The actual layer layout is managed in Vial (see vial/sweep.vil) and is
 * not defined here. This file only carries compile-time behavior (per-key
 * tapping terms) that Vial does not own.
 */

// Give the weak-finger home-row mods a longer tapping term to reduce misfires.
// Use g_tapping_term (the runtime value) rather than the TAPPING_TERM constant
// so Vial's runtime tapping-term setting still applies as the baseline.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
        case RCTL_T(KC_QUOTE):
        case LALT_T(KC_S):
        case RALT_T(KC_L):
            return g_tapping_term + 40;
        default:
            return g_tapping_term;
    }
}

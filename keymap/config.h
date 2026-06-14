#pragma once

/*
 * Vial identity and capacities.
 *
 * UID, layer count, and tap-dance/combo/key-override counts are matched to the
 * exported vial/sweep.vil so it re-imports cleanly. The unlock combo is the
 * set of keys held to unlock Vial's secure features.
 */
#define VIAL_KEYBOARD_UID {0xCB, 0x00, 0xFE, 0xED, 0x20, 0x04, 0xCA, 0xFE}
#define VIAL_UNLOCK_COMBO_ROWS { 2, 3, 0, 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1, 0, 2, 4 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define VIAL_TAP_DANCE_ENTRIES 32
#define VIAL_COMBO_ENTRIES 32
#define VIAL_KEY_OVERRIDE_ENTRIES 32

/*
 * Tap-hold tuning. The tapping term is owned by vial-qmk (quantum/vial.c
 * defines get_tapping_term() under TAPPING_TERM_PER_KEY) and is adjustable at
 * runtime from Vial's QMK Settings; TAPPING_TERM below is its reset/default.
 */

// Default/reset value for the runtime (Vial QMK Settings) tapping term.
// Tuned to 275 ms after testing; adjust live in Vial, this is just the reset.
#define TAPPING_TERM 275

// Keep TAPPING_TERM_PER_KEY defined so QMK routes the term through vial.c's
// get_tapping_term(), which is what makes the Vial QMK Settings slider (and
// per-tap-dance custom terms) take effect. Guarded because the ferris/sweep
// keyboard config already enables it. Do NOT define get_tapping_term() in
// keymap.c (it collides with vial.c's). See docs/per-finger-tapping-term.md.
#ifndef TAPPING_TERM_PER_KEY
#    define TAPPING_TERM_PER_KEY
#endif

// Permissive Hold is not set at compile time; it's controlled at runtime via
// Vial's QMK Settings and is currently enabled (favours intended home-row chords).

// Note: IGNORE_MOD_TAP_INTERRUPT was removed from QMK; its behavior (don't
// select the hold action on interrupt) is now the default for mod-taps.

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
#define VIAL_TAP_DANCE_ENTRIES 8
#define VIAL_COMBO_ENTRIES 8
#define VIAL_KEY_OVERRIDE_ENTRIES 8

/*
 * Global tap-hold tuning (compile-time). QMK_SETTINGS is disabled (see
 * rules.mk), so these are not runtime-editable from Vial; the per-key overrides
 * in keymap.c are authoritative.
 */

// Baseline tapping term; per-key overrides live in keymap.c (get_tapping_term).
#define TAPPING_TERM 250

// Required for get_tapping_term() to be consulted at all; without it the
// per-key overrides in keymap.c are silently ignored. Guarded because the
// ferris/sweep keyboard config already enables it.
#ifndef TAPPING_TERM_PER_KEY
#    define TAPPING_TERM_PER_KEY
#endif

// Permissive Hold intentionally left undefined (off).

// Note: IGNORE_MOD_TAP_INTERRUPT was removed from QMK; its behavior (don't
// select the hold action on interrupt) is now the default for mod-taps.

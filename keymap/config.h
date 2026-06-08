#pragma once

/*
 * Global tap-hold tuning.
 *
 * These are baseline/compile-time defaults. With Vial, the global tap-hold
 * settings (tapping term, permissive hold, etc.) are also editable at runtime
 * from the Vial GUI, so changes here are mostly a sensible starting point.
 */

// Baseline tapping term; per-key overrides live in keymap.c (get_tapping_term).
#define TAPPING_TERM 250

// Permissive Hold intentionally left undefined (off).

// Treat a mod-tap as a tap if another key is pressed/released during the term.
#define IGNORE_MOD_TAP_INTERRUPT

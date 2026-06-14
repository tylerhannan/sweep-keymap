# Follow-up: static per-finger tapping terms (Option 2)

This repo currently uses a **single global tapping term** that's adjustable at
runtime from Vial (QMK Settings). See the README *Settings* section for the why.

If, after living with it, the weak fingers (pinky `A`/`'`, ring `S`/`L`) still
misfire at your chosen global term, you can switch to a **static per-finger
split** (e.g. 290 ms on those keys, 250 ms elsewhere). The catch is that
vial-qmk's `quantum/vial.c` defines a non-`weak` `get_tapping_term()`, so a
keymap-level override collides at link time. Two small changes are needed.

## 1. Make vial-qmk's definition overridable (one-line patch to vial-qmk)

This edits the **vial-qmk tree**, not this repo, so you must reapply it after a
`git pull` in vial-qmk.

In `quantum/vial.c`, find:

```c
#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
```

and add the `weak` attribute:

```c
#ifdef TAPPING_TERM_PER_KEY
__attribute__((weak)) uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
```

Apply it as a patch from this repo (run inside your vial-qmk checkout):

```bash
git apply /path/to/sweep-keymap/docs/vial-weak-tapping-term.patch
```

(Generate that patch file once with `git diff > vial-weak-tapping-term.patch`
from vial-qmk after making the edit, and commit it here.)

## 2. Add the override back to this repo's keymap

In `keymap/keymap.c`, add:

```c
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):    // left pinky  (Ctrl)
        case RCTL_T(KC_QUOTE):// right pinky (Ctrl)
        case LALT_T(KC_S):    // left ring   (Alt)
        case RALT_T(KC_L):    // right ring  (Alt)
            return TAPPING_TERM + 40;  // ~290 ms on weak fingers
        default:
            return TAPPING_TERM;       // 250 ms elsewhere
    }
}
```

## Tradeoffs

- You lose the runtime Vial slider for the tapping term (it's now compile-time).
- Every adjustment means recompile + reflash both halves.
- The vial-qmk patch must be reapplied whenever you update vial-qmk.

## Cheaper alternative to try first

Before committing to the patch, try toggling **Permissive Hold** and/or
**Hold On Other Key Press** in Vial's QMK Settings. These change *how*
interruptions resolve rather than the timing, and often cut misfires more
effectively than ±20–40 ms on the term — with zero rebuilds.

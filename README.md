# Ferris Sweep Keymap & Firmware

Personal keymap, firmware config, and notes for my 34-key Ferris Sweep Bling LP
(Choc low-profile, MX-less) running Vial firmware on a 0xCB Helios (RP2040) controller.

## Hardware

| | |
|---|---|
| Board | Ferris Sweep Bling LP (3×5 + 2 thumbs per half, 34 keys) |
| Switches | Choc V1 (low-profile) |
| Controller | 0xCB Helios (RP2040, USB-C, Pro Micro footprint) |
| Connection | Wired TRRS split |
| Firmware | Vial-QMK (`CONVERT_TO=helios` over `ferris/sweep`) |

There's no PCB reset button, and the Helios sits flush, so bootloader entry is software-only
(see *Flashing* below). Don't flash a firmware without a bootloader key bound.

## Layout

QWERTY base with home-row mods.

### Layer 0: Base
```
Q  W  E  R  T        Y  U  I  O  P
A* S* D* F* G        H  J* K* L* '*
Z  X  C  V  B        N  M  ,  .  /
      MO1 SPC        Ent MO2
```
Home-row mods (CAGS, pinky→index): `A`=Ctrl `S`=Alt `D`=Gui `F`=Shift / `J`=Shift `K`=Gui `L`=Alt `'`=Ctrl

### Layer 1: Numbers / Nav  (hold left thumb, MO1)
```
1   2  3  4  5        6  7  8  9  0
Esc ·  ·  ·  ·        ←  ↓  ↑  →  Bksp
·   ·  ·  ·  ·        ·  ·  ·  ·  ·
      MO1 SPC         Ent MO3
```

### Layer 2: Symbols  (hold right thumb, MO2)
```
!  @  #  $  %        ^  &  *  (  )
:  +  -  =  _        ·  CW ·  [  ]
;  `  ~  |  \        ·  ·  ·  {  }
```
Brackets stack vertically: open on the ring, close on the pinky, running round → square → curly.
`CW` (right index home, `J` position) = Caps Word toggle (`CW_TOGG`).

### Layer 3: Mouse / Media  (MO1 + MO3)
```
·  M1 M↑ M2 WhD       ·    Next Vol+ ·   ·
·  M← M↓ M→ WhU       ·    Prev Play ·    ·
·  ·  ·  ·  ·         ·    ·    Vol- ·   ·
```

## Why it's set up this way

- Operators left / brackets right so common code sequences (`= (`, `=>`, `: [`) alternate hands.
- Vertical bracket stack: open on the ring, close on the pinky.
- `=` on the left index (strongest finger), since it's the most-typed operator.
- CAGS mod order (Ctrl-Alt-Gui-Shift, pinky→index), with Shift on the index and Ctrl out on the pinky.

## Settings (tap-hold)

Tuned to minimize accidental home-row mods:

| Setting | Value |
|---|---|
| Tapping Term | 275 ms (set live in Vial; compile-time default 275) |
| Permissive Hold | on (runtime, via QMK Settings) |
| Mod-tap interrupt | QMK default (hold not selected on interrupt) |
| Retro Tapping | off |

The tapping term is a single global value, tunable at runtime from Vial's QMK
Settings (no reflash); currently 275 ms. Permissive Hold is enabled (also a
runtime QMK Setting) to favour intended chords on the home-row mods. A static
per-finger split (longer term on the pinky/ring mods) is a documented
follow-up — see [`docs/per-finger-tapping-term.md`](docs/per-finger-tapping-term.md).

Combos: `Q+W` → Tab, `I+O` → Bksp
Right inner thumb: `ALL_T(KC_ENTER)`, tap = Enter, hold = Hyper (window management on macOS); outer thumb = `MO2`. This mirrors the left (outer = `MO1`, inner = Space).

## Firmware-only customizations

These live in code rather than the Vial GUI. The source is committed here (`keymap/`),
but it only takes effect once the next firmware build is flashed (see *TODO* below):

- Caps Word: `CAPS_WORD_ENABLE = yes` in `rules.mk`, bound to `CW_TOGG`. Auto-ends on space, so it's good for `SCREAMING_SNAKE_CASE`.
- Bootloader keys: covered under Flashing.

## Flashing

RP2040 → drag-and-drop UF2. The split flashes one half at a time.

```bash
# one-time setup
qmk setup   # or clone vial-qmk and point qmk at it
cp -r keymap vial-qmk/keyboards/ferris/sweep/keymaps/<me>

# build (produces a .uf2)
# CONVERT_TO=helios is set in rules.mk, so no -e flag is needed.
qmk compile -kb ferris/sweep -km <me>
```

Then per half:
1. Plug in one half via USB.
2. Enter bootloader in software (no buttons, since the controller is flush):
   - Left half: hold left thumb (MO1) → Layer 1 → tap the bootloader key (bottom-left pinky).
   - Right half: hold right thumb (MO2) → Layer 2 → tap the bootloader key (innermost bottom-row key).
   - Keycode is `QK_BOOT` ("Bootloader" in Vial), not `QK_REBOOT`.
3. The `RPI-RP2` drive mounts; copy the `.uf2` onto it. It reboots into the new firmware.
4. Repeat for the other half.

> The bootloader key must be reachable on each half independently (Layer 1 left / Layer 2 right),
> because when only one half is plugged in, the other half's keys are dead.

## Restoring the keymap

If a flash wipes the on-board keymap or anything looks off:

1. Open Vial.
2. File → Import → `vial/sweep.vil`.

Keep `sweep.vil` updated whenever you change layers, combos, or keymaps in the GUI.

## Applying the layout to both halves

The Vial layout lives in **each half's own EEPROM**, written live over USB (HID, so
no flashing — this works even on a machine that blocks external media). For daily
typing only the USB-connected (master) half needs it, **but each half must carry
`QK_BOOT` to enter the bootloader when it's flashed alone** — so apply `sweep.vil`
to both before relying on per-half flashing:

1. Plug in the **left** half alone → Vial → File → Import → `vial/sweep.vil`.
2. Plug in the **right** half alone → Vial → Import → `vial/sweep.vil` again.

`QK_BOOT` is a standard keycode that also works on the *current* firmware, so do this
first — it's what gets you into the bootloader to flash the new build.

## TODO (next firmware build)

Pending until I'm on a machine that can write to the board (work laptop blocks
external media; flash from an unrestricted computer):

- [ ] Upload the most recent `sweep.vil` export to the repo after any layout
      change, so `vial/sweep.vil` always matches what's on the board.
- [x] Bind per-half bootloader keys: `QK_BOOT` on a left-hand Layer 1 key
      (bottom-left pinky) and a right-hand Layer 2 key (innermost bottom-row key).
      Each half can reach it alone, since only the plugged-in half is live during flashing.
- [x] Enable Caps Word: `CAPS_WORD_ENABLE = yes` in `rules.mk`, flashed and
      bound to `CW_TOGG` on Layer 2 (right index). Auto-ends on space; good for
      `SCREAMING_SNAKE_CASE`.
- [ ] Optional follow-up — static per-finger tapping terms: tune the global term
      live in Vial first; if the pinky/ring mods still misfire, switch to a static
      split (~290 ms on `LCTL_T(KC_A)`, `RCTL_T(KC_QUOTE)`, `LALT_T(KC_S)`,
      `RALT_T(KC_L)`). Requires a one-line vial-qmk patch — see
      [`docs/per-finger-tapping-term.md`](docs/per-finger-tapping-term.md).
- [x] Resolve the `get_tapping_term()` vs. QMK Settings question: vial-qmk's
      `quantum/vial.c` owns a non-`weak` `get_tapping_term()` (it wires up the
      QMK Settings runtime slider + per-tap-dance terms), so a keymap-level
      override collides at link time. Dropped the custom function; the term is now
      a single global value tunable live in Vial.
- [x] Remove `IGNORE_MOD_TAP_INTERRUPT` — deleted from QMK; its behavior (don't
      select hold on interrupt) is now the default. If hold-on-interrupt is ever
      wanted, switch to `PERMISSIVE_HOLD` / `HOLD_ON_OTHER_KEY_PRESS`.
- [x] Re-evaluate the `E+R` → Tab combo (`er` is a top English bigram on the
      synchronized index+middle pair, so it misfired): moved Tab to `Q+W`, a
      rare bigram that stays one-handed (left) for use with the mouse hand.
- [x] Remove the unused `TD0` tap-dance entry in Vial (the thumb uses
      `ALL_T(KC_ENTER)` directly, so TD0 is dead config).

## Changelog

- _2026-06-08_ Initial commit: layout, tap-hold tuning, symbol layer.
- _2026-06-14_ Bound per-half `QK_BOOT` keys, removed the stray Layer 3 `RGUI`, and cleared the unused `TD0`.
- _2026-06-14_ Set `CONVERT_TO=helios` in `rules.mk` so the build always targets the RP2040 Helios; reverted the AVR-only workarounds (LTO, `QMK_SETTINGS=no`, 8-entry Vial caps) now that we build for the correct MCU.
- _2026-06-14_ Removed the custom `get_tapping_term()` (it collided with vial-qmk's own definition); the tapping term is now a single global value, tunable live in Vial. Static per-finger split documented as a follow-up.
- _2026-06-14_ Fixed a mirrored right half: the original `.vil` export had the right-hand columns (alphas rows 4–6 and the two thumbs) entered in reverse order, so the right side typed mirrored. Reversed them in `vial/sweep.vil` and regenerated `keymap.c` to match the firmware's `LAYOUT_split_3x5_2` matrix (right index = innermost).
- _2026-06-14_ Bound Caps Word (`CW_TOGG`) on Layer 2; enabled Permissive Hold and set the tapping term to 275 ms (both runtime QMK Settings, persisted in `sweep.vil`). Aligned the compile-time `TAPPING_TERM` default to 275.
- _2026-06-14_ Moved the Tab combo from `E+R` (a common, misfire-prone bigram) to `Q+W`, and relocated Caps Word to the right index home key.

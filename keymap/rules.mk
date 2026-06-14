# Vial keymap for the Ferris Sweep (built with vial-qmk).

# Target the 0xCB Helios (RP2040) controller. Baking this in means the build
# always targets the right MCU even if a -e CONVERT_TO=... flag is mistyped.
CONVERT_TO = helios

# VIA is a prerequisite for VIAL; both must be enabled for a Vial keymap.
VIA_ENABLE = yes
VIAL_ENABLE = yes

# LTO keeps the firmware within the flash region.
LTO_ENABLE = yes

# QMK Settings off: it would define its own get_tapping_term() (colliding with
# ours) and bloats the build. With it off, our per-key get_tapping_term() in
# keymap.c is the sole authority (no runtime tapping-term slider in Vial).
QMK_SETTINGS = no

# Runtime "Caps Word" toggle, also surfaced in Vial.
CAPS_WORD_ENABLE = yes

# Layer 3 uses mouse keys (KC_BTN*/KC_MS_*/KC_WH_*) and consumer/media keys
# (volume + transport), which need these enabled to function.
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

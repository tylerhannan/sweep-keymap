# /// script
# requires-python = ">=3.10"
# dependencies = ["keymap-drawer==0.23.0"]
# ///
"""Draw docs/keymap.svg from vial/sweep.vil with keymap-drawer.

Run with: uv run scripts/draw_keymap.py
"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
VIL = ROOT / "vial" / "sweep.vil"
CONFIG = ROOT / "keymap_drawer.config.yaml"
OUT_YAML = ROOT / "docs" / "keymap.yaml"
OUT_SVG = ROOT / "docs" / "keymap.svg"
LAYER_NAMES = ["Base", "Nav", "Sym", "Mouse"]

# Vial still exports some pre-2023 QMK names that keymap-drawer doesn't know.
ALIASES = {
    "KC_SCOLON": "KC_SCLN",
    "KC_BSLASH": "KC_BSLS",
    "KC_LBRACKET": "KC_LBRC",
    "KC_RBRACKET": "KC_RBRC",
    "KC_BSPACE": "KC_BSPC",
    "QK_CAPS_WORD_TOGGLE": "CW_TOGG",
}


def norm(code: str) -> str:
    for old, new in ALIASES.items():
        code = code.replace(old, new)
    return code


def flatten(layer):
    # .vil rows are matrix rows (-1 = no key); left half first, right index innermost,
    # which matches LAYOUT_split_3x5_2 order once halves are interleaved row by row.
    half = len(layer) // 2
    keys = []
    for left, right in zip(layer[:half], layer[half:]):
        keys += [norm(k) for k in left if k != -1]
        keys += [norm(k) for k in right if k != -1]
    return keys


def main():
    vil = json.loads(VIL.read_text())
    layers = [flatten(layer) for layer in vil["layout"]]
    base = layers[0]

    # Combo outputs ride along as an extra layer so they get the same labels.
    combos = []
    for *triggers, output in vil.get("combo", []):
        triggers = [norm(t) for t in triggers if t not in ("KC_NO", -1)]
        if triggers and output not in ("KC_NO", -1):
            combos.append(([base.index(t) for t in triggers], norm(output)))
    extra = [out for _, out in combos] + ["KC_NO"] * (len(base) - len(combos))

    qmk = {"keyboard": "ferris/sweep", "layout": "LAYOUT_split_3x5_2", "layers": layers + [extra]}
    with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False) as f:
        json.dump(qmk, f)
    parsed = subprocess.run(
        ["keymap", "-c", str(CONFIG), "parse", "-q", f.name, "-l", *LAYER_NAMES, "_combos"],
        check=True, capture_output=True, text=True,
    ).stdout
    keymap = yaml.safe_load(parsed)
    combo_labels = keymap["layers"].pop("_combos")
    if combos:
        keymap["combos"] = [
            {"p": pos, "k": combo_labels[i], "l": ["Base"]} for i, (pos, _) in enumerate(combos)
        ]

    OUT_YAML.parent.mkdir(exist_ok=True)
    OUT_YAML.write_text(yaml.safe_dump(keymap, sort_keys=False, allow_unicode=True))
    svg = subprocess.run(
        ["keymap", "-c", str(CONFIG), "draw", str(OUT_YAML)],
        check=True, capture_output=True, text=True,
    ).stdout
    OUT_SVG.write_text(svg)
    print(f"wrote {OUT_SVG.relative_to(ROOT)}", file=sys.stderr)


if __name__ == "__main__":
    main()

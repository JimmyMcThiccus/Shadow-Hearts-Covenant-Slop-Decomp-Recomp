#!/usr/bin/env bash
# Run the port's in-game menu on the US disc with a key script and screenshots:  menu_dev.sh OUTDIR "w70,shot:01_top,down,shot:02" [map]
# (SH2_SCREEN_DEV=menu: new game on a map, entries as in the live capture; see sh2_field::screens_dev::parse_menu_script)
set -e
OUT="$1"; STEPS="${2:-w70,shot:01_top}"; MAP="${3:-AP_02_U}"
export CARGO_TARGET_DIR="${CARGO_TARGET_DIR:-$USERPROFILE/.cache/sh2-decomp-target}"
export SH2_DISC_DIR="C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2JP" SH2_US_DISC_DIR="C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2US"
mkdir -p "$OUT"
cd "$(dirname "$0")/../../port"
cargo build -q -p sh2_app
# a Bash tool timeout does not kill the window on Windows: run the exe itself under timeout -k
SH2_SCREEN_DEV="menu:$MAP" SH2_SCREEN_SHOTS="$OUT" SH2_MENU_SCRIPT="$STEPS" timeout -k 5 240 "$CARGO_TARGET_DIR/debug/sh2_app.exe" --us > "$OUT/run.log" 2>&1 || true
ls "$OUT"/*.png 2>/dev/null | wc -l

#!/bin/sh
# Launch the Rust/Bevy port on the Japanese demo disc. Works from any directory.
ROOT="$(cd "$(dirname "$0")" && pwd)"
# Discs: drop your .iso images next to this script (any file names; identified by their boot executable).
# Set SH2_DISC_DIR / SH2_US_DISC_DIR / SH2_US_DISC2_DIR to an .iso or an extracted folder, or SH2_DISCS to another folder, to override.
export SH2_DISCS="${SH2_DISCS:-$ROOT}"
export CARGO_TARGET_DIR="${CARGO_TARGET_DIR:-$HOME/.cache/sh2-decomp-target}"   # keep the build cache off the ExFAT drive
cd "$ROOT/port" && exec cargo run -p sh2_app -- "$@"

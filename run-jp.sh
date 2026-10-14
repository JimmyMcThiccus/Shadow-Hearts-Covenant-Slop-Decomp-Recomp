#!/bin/sh
# Launch the Rust/Bevy port on the Japanese demo disc. Works from any directory.
ROOT="$(cd "$(dirname "$0")" && pwd)"
export SH2_DISC_DIR="${SH2_DISC_DIR:-/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)}"
export SH2_US_DISC_DIR="${SH2_US_DISC_DIR:-/Volumes/work/Sh2 Decomp/Shadow Hearts - Covenant (USA) (Disc 1)-1}"
export CARGO_TARGET_DIR="${CARGO_TARGET_DIR:-$HOME/.cache/sh2-decomp-target}"   # keep the build cache off the ExFAT drive
cd "$ROOT/port" && exec cargo run -p sh2_app -- "$@"

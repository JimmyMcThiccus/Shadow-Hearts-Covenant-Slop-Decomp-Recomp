#!/bin/sh
# Launch the Rust/Bevy port on the US retail disc. Works from any directory. Extra args are passed through (e.g. --autoplay --boost 80).
ROOT="$(cd "$(dirname "$0")" && pwd)"
# Discs: drop your .iso images next to this script (any file names; identified by their boot executable).
# Set SH2_DISC_DIR / SH2_US_DISC_DIR / SH2_US_DISC2_DIR to an .iso or an extracted folder, or SH2_DISCS to another folder, to override.
export SH2_DISCS="${SH2_DISCS:-$ROOT}"
export CARGO_TARGET_DIR="${CARGO_TARGET_DIR:-$HOME/.cache/sh2-decomp-target}"
# `play` profile (port/Cargo.toml): optimised + incremental, so the game is not CPU-bound; SH2_PROFILE=dev for the dev profile
cd "$ROOT/port" && exec cargo run --profile "${SH2_PROFILE:-play}" -p sh2_app -- --us "$@"

# Launch the Rust/Bevy port on the US retail disc. Works from any directory.
# Extra args are passed through (e.g. --autoplay --boost 80)

$ROOT = Split-Path -Parent $MyInvocation.MyCommand.Path
# Discs: drop your .iso images next to this script (any file names; identified by their boot executable).
# Set SH2_DISC_DIR / SH2_US_DISC_DIR / SH2_US_DISC2_DIR to an .iso or an extracted folder, or SH2_DISCS to another folder, to override.
if (-not $env:SH2_DISCS) { $env:SH2_DISCS = $ROOT }
$env:CARGO_TARGET_DIR = "$HOME\.cache\sh2-decomp-target"

Set-Location "$ROOT\port"
cargo run -p sh2_app -- --us $args

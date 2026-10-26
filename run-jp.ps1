# Launch the Rust/Bevy port on the Japanese demo disc. Works from any directory.
# Extra args are passed through (e.g. --autoplay --boost 80)

$ROOT = Split-Path -Parent $MyInvocation.MyCommand.Path
if (-not $env:SH2_DISC_DIR) { $env:SH2_DISC_DIR = "$ROOT\..\SH2JP" }
if (-not $env:SH2_US_DISC_DIR) { $env:SH2_US_DISC_DIR = "$ROOT\..\SH2US" }
$env:CARGO_TARGET_DIR = "$HOME\.cache\sh2-decomp-target"

Set-Location "$ROOT\port"
cargo run -p sh2_app -- $args

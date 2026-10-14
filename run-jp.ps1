# Launch the Rust/Bevy port on the Japanese demo disc. Works from any directory.
# Extra args are passed through (e.g. --autoplay --boost 80)

$ROOT = Split-Path -Parent $MyInvocation.MyCommand.Path
$env:SH2_DISC_DIR = "C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2JP"
$env:SH2_US_DISC_DIR = "C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2US"
$env:CARGO_TARGET_DIR = "$HOME\.cache\sh2-decomp-target"

Set-Location "$ROOT\port"
cargo run -p sh2_app -- $args

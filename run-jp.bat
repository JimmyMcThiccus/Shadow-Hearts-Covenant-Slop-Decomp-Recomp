@echo off
REM Launch the Rust/Bevy port on the Japanese demo disc. Works from any directory.
REM Extra args are passed through (e.g. --autoplay --boost 80)

set "SH2_DISC_DIR=C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2JP"
set "SH2_US_DISC_DIR=C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2US"
set "CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-decomp-target"

cd /d "%~dp0port"
cargo run -p sh2_app -- %*

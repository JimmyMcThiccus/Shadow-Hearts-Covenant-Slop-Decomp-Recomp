@echo off
REM Launch the Rust/Bevy port on the US retail disc. Works from any directory.
REM Extra args are passed through (e.g. --autoplay --boost 80)

set "ROOT=%~dp0"
REM Use hardcoded paths since folder structure is fixed
set "SH2_DISC_DIR=C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2JP"
set "SH2_US_DISC_DIR=C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2US"
set "CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-decomp-target"

cd /d "%ROOT%port"
cargo run -p sh2_app -- --us %*

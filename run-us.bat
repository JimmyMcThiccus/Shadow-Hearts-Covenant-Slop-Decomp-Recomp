@echo off
REM Launch the Rust/Bevy port on the US retail disc. Works from any directory.
REM Extra args are passed through (e.g. --autoplay --boost 80)

set "ROOT=%~dp0"
REM Use hardcoded paths since folder structure is fixed
set "SH2_DISC_DIR=C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2JP"
set "SH2_US_DISC_DIR=C:\Users\jamie\Documents\SH2\Sh2 Decomp\SH2US"
set "SH2_US_DISC2_DIR=C:\Users\jamie\Documents\SH2\Sh2 Decomp\disk2extracted"
set "CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-decomp-target"

cd /d "%ROOT%port"
REM `play` profile (port/Cargo.toml): everything optimised like release, incremental, so the game logic / UI / render prep is not
REM CPU-bound (the dev profile builds the game crates at opt-level 1).  First build ~10 min, later rebuilds about as fast as dev.
REM set SH2_PROFILE=dev to use the dev profile instead.
if not defined SH2_PROFILE set "SH2_PROFILE=play"
cargo run --profile %SH2_PROFILE% -p sh2_app -- --us %*

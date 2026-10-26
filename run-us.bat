@echo off
REM Launch the Rust/Bevy port on the US retail disc. Works from any directory.
REM Extra args are passed through (e.g. --autoplay --boost 80)

set "ROOT=%~dp0"
REM Discs: drop your .iso images next to this script (any file names; identified by their boot executable).
REM Set SH2_DISC_DIR / SH2_US_DISC_DIR / SH2_US_DISC2_DIR to an .iso or an extracted folder, or SH2_DISCS to another folder, to override.
if not defined SH2_DISCS set "SH2_DISCS=%~dp0."
set "CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-decomp-target"

cd /d "%ROOT%port"
REM `play` profile (port/Cargo.toml): everything optimised like release, incremental, so the game logic / UI / render prep is not
REM CPU-bound (the dev profile builds the game crates at opt-level 1).  First build ~10 min, later rebuilds about as fast as dev.
REM set SH2_PROFILE=dev to use the dev profile instead.
if not defined SH2_PROFILE set "SH2_PROFILE=play"
cargo run --profile %SH2_PROFILE% -p sh2_app -- --us %*

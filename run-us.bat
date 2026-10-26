@echo off
REM Launch the Rust/Bevy port on the US retail disc. Works from any directory.
REM Extra args are passed through (e.g. --autoplay --boost 80)

set "ROOT=%~dp0"
REM Disc folders default to siblings of this repo; set the variables beforehand to override
if not defined SH2_DISC_DIR set "SH2_DISC_DIR=%~dp0..\SH2JP"
if not defined SH2_US_DISC_DIR set "SH2_US_DISC_DIR=%~dp0..\SH2US"
if not defined SH2_US_DISC2_DIR set "SH2_US_DISC2_DIR=%~dp0..\disk2extracted"
set "CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-decomp-target"

cd /d "%ROOT%port"
REM `play` profile (port/Cargo.toml): everything optimised like release, incremental, so the game logic / UI / render prep is not
REM CPU-bound (the dev profile builds the game crates at opt-level 1).  First build ~10 min, later rebuilds about as fast as dev.
REM set SH2_PROFILE=dev to use the dev profile instead.
if not defined SH2_PROFILE set "SH2_PROFILE=play"
cargo run --profile %SH2_PROFILE% -p sh2_app -- --us %*

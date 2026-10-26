@echo off
REM Launch the Rust/Bevy port on the Japanese demo disc. Works from any directory.
REM Extra args are passed through (e.g. --autoplay --boost 80)

REM Discs: drop your .iso images next to this script (any file names; identified by their boot executable).
REM Set SH2_DISC_DIR / SH2_US_DISC_DIR / SH2_US_DISC2_DIR to an .iso or an extracted folder, or SH2_DISCS to another folder, to override.
if not defined SH2_DISCS set "SH2_DISCS=%~dp0."
set "CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-decomp-target"

cd /d "%~dp0port"
cargo run -p sh2_app -- %*

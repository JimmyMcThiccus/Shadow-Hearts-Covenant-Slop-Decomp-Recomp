@echo off
REM Launch the Rust/Bevy port on the Japanese demo disc. Works from any directory.
REM Extra args are passed through (e.g. --autoplay --boost 80)

if not defined SH2_DISC_DIR set "SH2_DISC_DIR=%~dp0..\SH2JP"
if not defined SH2_US_DISC_DIR set "SH2_US_DISC_DIR=%~dp0..\SH2US"
set "CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-decomp-target"

cd /d "%~dp0port"
cargo run -p sh2_app -- %*

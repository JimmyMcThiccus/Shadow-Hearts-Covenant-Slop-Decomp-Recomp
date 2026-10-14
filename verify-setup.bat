@echo off
echo ================================
echo Shadow Hearts II Decomp Setup
echo ================================
echo.

REM Check if Rust/Cargo is installed
where cargo >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Rust/Cargo not found!
    echo Please install from https://rustup.rs/
    echo.
    pause
    exit /b 1
)
echo [OK] Rust/Cargo installed

REM Check project structure
if not exist "port\Cargo.toml" (
    echo [ERROR] port\Cargo.toml not found!
    echo Make sure you are in the sh2-decomp directory.
    pause
    exit /b 1
)
echo [OK] Project structure intact

REM Check for disc folders (optional - will use default paths if missing)
set "JP_DISC=%~dp0..\SH2JP"
set "US_DISC=%~dp0..\SH2US"

if exist "%JP_DISC%\SLPM_602.19" (
    echo [OK] JP Demo disc found: %JP_DISC%
) else (
    echo [WARN] JP Demo disc not found at: %JP_DISC%
    echo        Will use SH2_DISC_DIR environment variable if set
)

if exist "%US_DISC%\SLUS_210.41" (
    echo [OK] US Retail disc found: %US_DISC%
) else (
    echo [WARN] US Retail disc not found at: %US_DISC%
    echo        Will use SH2_US_DISC_DIR environment variable if set
)

echo.
echo ================================
echo Setup looks good!
echo ================================
echo.
echo To run the JP demo:
echo   run-jp.bat --autoplay
echo.
echo To run the US retail:
echo   run-us.bat --us --autoplay --boost 80
echo.
pause

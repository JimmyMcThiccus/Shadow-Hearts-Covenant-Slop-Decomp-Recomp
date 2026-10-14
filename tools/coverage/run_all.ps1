# Whole-game coverage harness (round 5 QA).
#   tools\coverage\run_all.ps1 [all | run <cat>... | report] [--fresh] [--only NAME] [--jobs N]
# cats: field fx battle party lsd msd story.  Writes tools\coverage\out\*.tsv and notes\integration\coverage.md.
$root = Resolve-Path (Join-Path $PSScriptRoot "..\..")
if (-not $env:SH2_US_DISC_DIR) { $env:SH2_US_DISC_DIR = Join-Path $root "..\SH2US" }
if (-not $env:SH2_US_DISC2_DIR) { $env:SH2_US_DISC2_DIR = Join-Path $root "..\disk2extracted" }
if (-not $env:SH2_DISC_DIR) { $env:SH2_DISC_DIR = Join-Path $root "..\SH2JP" }
if (-not $env:CARGO_TARGET_DIR) { $env:CARGO_TARGET_DIR = Join-Path $env:USERPROFILE ".cache\sh2-r5-qa" }
$a = $args
if ($a.Count -eq 0) { $a = @("all") }
Push-Location (Join-Path $root "port")
try {
  $exe = Join-Path $env:CARGO_TARGET_DIR "release\examples\coverage.exe"
  $good = Join-Path $env:CARGO_TARGET_DIR "cov-good.exe"
  cargo build --release -p sh2_app --example coverage
  # the tree is shared: when another agent's half-done edit breaks the build, run the last binary that built
  if ($LASTEXITCODE -eq 0) { Copy-Item $exe $good -Force }
  elseif (Test-Path $good) { Write-Warning "run_all: build failed, using the last good binary $good" }
  else { exit 1 }
  # run a copy: Windows locks a running .exe, so a rebuild during a run would fail to link
  $run = Join-Path $env:CARGO_TARGET_DIR ("cov-run-" + $PID + ".exe")
  Copy-Item $good $run -Force
  & $run @a
  $st = $LASTEXITCODE
  Remove-Item $run -ErrorAction SilentlyContinue
  exit $st
} finally { Pop-Location }

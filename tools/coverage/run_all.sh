#!/bin/sh
# Whole-game coverage harness (round 5 QA).
#   tools/coverage/run_all.sh [all | run <cat>... | report] [--fresh] [--only NAME] [--jobs N]   (default 6 workers per category; or SH2_COV_JOBS=N)
# cats: field fx battle battleapp party lsd msd story (an unknown one exits 2 without touching coverage.md).  Writes tools/coverage/out/*.tsv and notes/integration/coverage.md.
# The binary is copied before it runs so that a rebuild while a run is going does not fail to link (Windows locks running .exe files).
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
export SH2_US_DISC_DIR="${SH2_US_DISC_DIR:-$ROOT/../SH2US}"
export SH2_US_DISC2_DIR="${SH2_US_DISC2_DIR:-$ROOT/../disk2extracted}"
export SH2_DISC_DIR="${SH2_DISC_DIR:-$ROOT/../SH2JP}"
export CARGO_BUILD_JOBS="${CARGO_BUILD_JOBS:-6}"
export CARGO_TARGET_DIR="${CARGO_TARGET_DIR:-$HOME/.cache/sh2-r6-qa2}"
EXE="$CARGO_TARGET_DIR/release/examples/coverage"
X=""; [ -f "$EXE.exe" ] && X=".exe"
GOOD="$CARGO_TARGET_DIR/cov-good$X"
# the tree is shared: when another agent's half-done edit breaks the build, run the last binary that built
if (cd "$ROOT/port" && cargo build --release -p sh2_app --example coverage); then
  cp "$EXE$X" "$GOOD"
elif [ -f "$GOOD" ]; then
  echo "run_all: build failed, using the last good binary $GOOD" >&2
else
  exit 1
fi
RUN="$CARGO_TARGET_DIR/cov-run-$$$X"
cp "$GOOD" "$RUN"
cd "$ROOT/port" && "$RUN" "${@:-all}"
st=$?
rm -f "$RUN"
exit $st

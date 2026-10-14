# Integration status (2026-10-09)

**Superseded by `final_status.md`** (360 tests green, 0 warnings, black-3D-layer bug fixed, autoplay reaches the scripted battle).

## Tests

`cargo test --workspace` with `SH2_DISC_DIR` (JP Furokuban) and `SH2_US_DISC_DIR` (US disc 1) set: **206 passed, 0 failed**
(this includes every real-data test: `sh2_core::fileio` 1734-file/11-archive size check and a new `list_dir_matches_walk`
on both discs, `sh2_field` `real_data` 4 incl. `us_maps_parse`, `sh2_script` `lsd_real`/`real_scripts`/`vsm_real`,
`sh2_formats` `model_real`, `sh2_battle` real tables, `sh2_menu` MSD tests).
`cargo test -p sh2_core --no-default-features` (no Bevy) passes too. `cargo check --workspace --all-targets` is clean apart from
the warnings below.

## Lints

`cargo clippy` is **not installed** in this toolchain (`rustup component add clippy` needs a download that I was not allowed
to do), so triage was done on `rustc` warnings:

* fixed: 3 `sh2_script::cscript` warnings (dead layout fields, a dead initial assignment) with narrow `#[allow]`s;
* open, in files owned by other agents (see requests.md): `sh2_gfx/src/bevy/model.rs:17` unused import `AtomicKind`;
  `sh2_app/src/viewer.rs:239` `hud_text` assigned but never read.

## Open items

1. ~~Two VEC (effect-script) interpreters~~ merged: `sh2_script::vsm` is the only one, `sh2_gfx::effects::{vsm,efmg}` re-export it (`vec_merge.md`). Next: real `SysCalls` handlers for the 269 ids (the Bevy/effect layer).
2. `sh2_battle::data::Container` could sit on a relaxed `sh2_formats::pkb` parser.
3. `sh2_core::fileio::Disc::read` opens the archive per call; the Bevy asset loader should keep file handles / mmap.
4. fdlibm vs Rust `sin/cos` (not bit-identical) is only relevant if recorded-battle replay is ever needed (docs/SDK_MAP.md).
5. clippy unavailable, see above.

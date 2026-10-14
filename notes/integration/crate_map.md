# Crate map after consolidation (2026-10-09)

Dependency direction (no cycles): `sh2_formats` and `sh2_core` (no Bevy needed) -> `sh2_script` -> `sh2_gfx`
-> `sh2_menu` -> `sh2_field` / `sh2_battle` -> `sh2_app`.
`glam` is workspace-pinned to **0.32** (the version Bevy 0.19 re-exports). `sh2_core` has a default `bevy` feature;
the workspace dependency is `default-features = false`, crates that need the Bevy glue write
`sh2_core = { workspace = true, features = ["bevy"] }` (sh2_app, sh2_gfx, sh2_field, sh2_menu, sh2_battle).
`sh2_script` and `sh2_formats` build without Bevy.

| Crate | Section | What it contains | Notes |
|---|---|---|---|
| `sh2_core` | A | `app` (CApp state/counters), `boot`, `thread`, `poller`, `pause`, `ssh_sys` (SSHSys scene manager, `SshSysPlugin` with `bevy`), `overlay` (MWo3 overlay loader model), `dvdrom_order`, **`fileio`** (canonical `PKFINFO.TBL`/`*.PKB` reader: `encode_name`/`decode_name`, `PkfInfo` with `search_file`/`walk`/`list_dir`/`dir_start`, `Disc` with `read`/`read_opt`/`listing`/`from_env`), `bufmem`, `regdat` (RegDatApi), `pad`/`vibe` (CPad, CPadMan, CVibe), `brn`, `dbg`, `game` (Bevy `Scene` states + `GameSet`, `bevy` feature only) | the only PKB reader in the workspace |
| `sh2_formats` | C (+A/E data) | `math` (**canonical** `FVector`/`Matrix`/`Quaternion`/`SVector`, column-major `Mat4` layout, `Matrix::rot` = `Rx*Ry*Rz`), `model` (SSH1.01a models), `motion` (SQHD), `dynamics`, `pkb` (package directories *inside* extracted files; not the archive reader) | Bevy-free, depends only on glam |
| `sh2_script` | E | `cscript` (CScript event VM), `vsm` (**the** VEC effect VM: `VsmThread` opcode core + `Machine` thread scheduler + `SysCalls` trait), `efmg` (EFMG container + HECO image), `opcodes` (CScript opcode tables, **`VEC_FUNC_TABLE`**, the single source of the 269 VEC system calls), `image`, `lsd` (LSD cutscene container + player), `memory`, `audio` (Sdrv protocol, `SoundBackend`), `pkb_compat` (aliases over `sh2_core::fileio`) | Bevy-free |
| `sh2_gfx` | B + D (+C runtime) | `gs`/`dma`/`packet`/`world`/`camera`/`light`/`sprite`/`texture`/`psm` (GS emulation, ordering tables, textures), `renderer` (`GfxBackend`), `bevy/` (Bevy render glue, in progress by the renderer agent), `model/` (instance/skeleton/path/lips), `effects/` (`efmg`/`vsm` = re-exports of `sh2_script::{efmg,vsm}`, Effect/EffectCore driving `Machine` through `SysCalls`, `puti`, `fp`, `jring`, `motion`, `syscalls` = re-export of `sh2_script::opcodes::VEC_FUNC_TABLE`, `compat` = `Rand`/`Rgba32`/3x3 helpers over `sh2_formats::math`) | |
| `sh2_menu` | F | menu toolkit (`widget`, `window`, `cursor`, `message`, `gfx` traits), `msd` (MenuDataTable scene files; `pkf` = re-export of the fileio codec), `disc` (`FileSource` trait + `DiscDir` wrapper over `sh2_core::fileio::Disc`), save system (`save`, `storage`, `dataaccess`), **`btlsave`** (the one implementation of BtlSaveSec level/EXP/stat logic and row-slice helpers), `title`, `gameover`, `scene`, `session`, `sjis`, `plugin`/`bevy_ui` (Bevy layer) | |
| `sh2_field` | G | MPS/SDB map parser (`mps`), `floor`, `event`, `camera`, `movement`, `field`, `socket`, `cmd`/`registry`/`classes_*` (in-game menu pages), `overlay_data*`, `fld_ops`, `compat` (angle helpers + `[f32;3]` adapters over `sh2_formats::math`), `pkb_compat` (`PkbSet` adapter over `sh2_core::fileio::Disc`), `sim`/`bevy` (scene glue) | |
| `sh2_battle` | H | `rules` (pure battle maths; level helpers re-exported from `sh2_menu::btlsave`), `structs` (CBattle / 0x4f0 battle character layouts), `data` (SSHDAT/SSHMES parsers, `Container`), `flow` (phase machine), `pkb_compat` (aliases over `sh2_core::fileio`) | `integration` feature removed; all deps unconditional |
| `sh2_app` | A | Bevy app (`main`, `viewer`) | owned by the app agent |

## What was removed / re-plumbed in the consolidation

* PKB/PKFINFO: `sh2_menu::msd::pkf` (codec + table walk), `sh2_menu::disc` reader, `sh2_field::pkb_compat` reader,
  `sh2_script::pkb_compat` (a third copy), `sh2_battle::pkb_compat` (a fourth, with its own tests) are now adapters over
  `sh2_core::fileio`. Public names (`DiscDir`, `FileSource`, `PkbSet`, `PkbDisc`, `PkbError`, `decode_name`, ...) are kept.
* Math: `sh2_gfx::effects::compat::FVector` (`[f32;4]`) -> `sh2_formats::math::FVector` (+ `Index<usize>`); the hand-written
  Euler matrix in `compat::rot_matrix` now calls `Matrix::rot`. `Matrix::rot` itself was corrected (it composed X first; the
  SDK's `sceVu0RotMatrix` is Z, Y, X with left multiplication = `Rx*Ry*Rz`, confirmed in the JP binary at 0x002029b8). It
  had no other callers.
* BtlSaveSec overlap: `sh2_battle::rules::{LevelRow, level_for_exp, next_exp, level_stat}` -> `pub use sh2_menu::btlsave::*`;
  the EXP accumulation loop exists once (`level_acc`). `LevelRow` field names follow the menu version
  (`exp_next`, `stat_2c`; unsigned stats, same on-disc bytes).
* VEC system calls: `sh2_gfx::effects::syscalls` is a re-export of `sh2_script::opcodes::VEC_FUNC_TABLE` (verified identical
  id/name/ctx for all 269 entries before the copy was deleted).

## Duplication that remains (not re-plumbed, see status.md)

* ~~Two VEC interpreters~~ merged 2026-10-09 into `sh2_script::vsm` (see `notes/integration/vec_merge.md`).
* `sh2_battle::data::Container` vs `sh2_formats::pkb::parse_package` (same `{count,size,{tag,off}}` layout, different strictness).

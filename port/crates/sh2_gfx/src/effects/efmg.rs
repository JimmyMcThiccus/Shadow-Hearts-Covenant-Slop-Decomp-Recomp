//! `EFMG` effect container + `HECO` bytecode image — re-export of [`sh2_script::efmg`].
//!
//! The parser moved to `sh2_script` when the two VEC interpreters were merged (the VM and its container format now live
//! in one crate, which has no Bevy dependency).  Names are unchanged: `Efmg`, `EfmgEntry`, `EfmgError`, `Heco`, `Insn`, `kind`.
//! See `notes/D/effect_format.md` for the file format and `notes/integration/vec_merge.md` for the merge.

pub use sh2_script::efmg::*;

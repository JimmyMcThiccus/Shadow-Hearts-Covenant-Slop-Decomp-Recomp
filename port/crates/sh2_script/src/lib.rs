//! sh2_script — script VMs, LSD cutscene player and audio protocol (section E of docs/OUTLINE.md).
//!
//! * [`cscript`]  – `CScript` event-script VM (field events + LSD `LSCR` tracks)
//! * [`vsm`]      – `VEC` effect-script VM (opcode core + thread scheduler `Machine`); the single VEC interpreter of the workspace
//! * [`efmg`]     – `EFMG` effect container + `HECO` bytecode image
//! * [`image`]    – event-script image parser
//! * [`lsd`]      – LSD container format (track headers, packets, control track)
//! * [`opcodes`]  – opcode / handler tables for both VMs
//! * [`memory`]   – segmented address space used by the VMs
//! * [`pkb_compat`] – adapter over the canonical `sh2_core::fileio` PKB reader
//! * [`audio`]    – Sdrv (SDRV_IOP.IRX) command protocol constants / sound formats

pub mod audio;
pub mod cscript;
pub mod disasm;
pub mod efmg;
pub mod image;
pub mod lsd;
pub mod memory;
pub mod opcodes;
pub mod pkb_compat;
pub mod vsm;

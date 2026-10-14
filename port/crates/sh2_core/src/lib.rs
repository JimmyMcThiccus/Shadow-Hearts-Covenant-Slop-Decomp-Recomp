//! sh2_core — system layer of Shadow Hearts: Covenant (section A in docs/OUTLINE.md).
//! CApp / CThread / CPoller / CPolObj / CPause / SSHSys / SSHApi / Overlay / FileIOLib / BufMemory / RegDatApi / CPad.
//!
//! Cargo feature `bevy` (default): Bevy `Resource`/`Component` derives, `ssh_sys::SshSysPlugin` and the `game` module.
//! Without it the crate is Bevy-free (`default-features = false`): [`fileio`] (the canonical `PKFINFO.TBL`/`*.PKB`
//! reader used by every data crate), [`bufmem`], [`pad`], ... build in a second instead of minutes.

pub mod app;
pub mod boot;
pub mod brn;
pub mod bufmem;
pub mod dbg;
pub mod dvdrom_order;
pub mod fileio;
/// Bevy scene/schedule glue (needs the `bevy` feature).
#[cfg(feature = "bevy")]
pub mod game;
pub mod overlay;
pub mod pad;
pub mod pause;
pub mod poller;
pub mod regdat;
pub mod ssh_sys;
pub mod thread;
pub mod vibe;

//! PINE (PCSX2 IPC) client + typed runtime readers for Shadow Hearts: Covenant, used to validate the Rust port against the real game.
//! No Bevy; the only dependency is `thiserror`.  See `examples/dump.rs`, `examples/record.rs` and notes/integration/pine_validation.md.

pub mod addr;
pub mod client;
pub mod game;

pub use addr::{ApiKind, Region};
pub use client::{EmuStatus, Image, Mem, Pine, PineError};

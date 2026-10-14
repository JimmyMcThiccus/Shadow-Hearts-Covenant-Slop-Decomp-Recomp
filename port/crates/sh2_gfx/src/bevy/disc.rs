//! Shared disc handle for Bevy systems.

use ::bevy::prelude::*;
use sh2_core::fileio::{Disc, FileIoError};
use std::path::Path;
use std::sync::Arc;

/// The opened game disc (`PKFINFO.TBL` + `*.PKB`), canonical reader from `sh2_core::fileio`.
#[derive(Resource, Clone)]
pub struct Sh2Disc(pub Arc<Disc>);

impl Sh2Disc {
    pub fn open(root: impl AsRef<Path>) -> Result<Self, FileIoError> {
        Ok(Self(Arc::new(Disc::open(root)?)))
    }
    /// `SH2_DISC_DIR` (JP demo) or, with `us = true`, `SH2_US_DISC_DIR` (retail).
    pub fn from_env(us: bool) -> Option<Self> {
        let var = if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" };
        Self::open(std::env::var_os(var)?).ok()
    }
    pub fn read(&self, path: &str) -> Result<Vec<u8>, FileIoError> {
        self.0.read(path)
    }
}

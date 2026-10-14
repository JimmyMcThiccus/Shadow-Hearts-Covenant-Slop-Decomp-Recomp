//! Locating files inside `PKFINFO.TBL` / `*.PKB`: thin adapter over the canonical reader
//! `sh2_core::fileio` (section A; `FileIOLib::InitPkb/deCode/SearchFile`, JP 0x0022ae70 / 0x0022ca90 / 0x0022c7a0).
//! Section G independently derived the same format (see notes/G/mps_format.md section 1).
//!
//! The only addition here is directory *listing* (`list_dir_while`), which the original never needs because it
//! scans forward by name.

use sh2_core::fileio::Disc;
pub use sh2_core::fileio::DirEntry as Entry;
use std::path::Path;

pub struct PkbSet {
    disc: Disc,
}

impl PkbSet {
    pub fn open(dir: impl AsRef<Path>) -> std::io::Result<Self> {
        Disc::open(dir)
            .map(|disc| Self { disc })
            .map_err(|e| std::io::Error::new(std::io::ErrorKind::Other, e.to_string()))
    }

    /// `SH2_DISC_DIR` = folder with `PKFINFO.TBL` and the `*.PKB` files.
    pub fn from_env() -> Option<Self> {
        Disc::from_env().map(|disc| Self { disc })
    }

    /// The canonical reader.
    pub fn disc(&self) -> &Disc {
        &self.disc
    }

    /// `(archive name, byte offset in the archive, size)` of `"FIELD/MPS/AP_00_U.MPS"`.
    pub fn resolve(&self, path: &str) -> Option<(String, u64, u32)> {
        let loc = self.disc.info().search_file(path)?;
        Some((loc.container, loc.byte_offset, loc.size))
    }

    pub fn read(&self, path: &str) -> Option<Vec<u8>> {
        self.disc.read_opt(path)
    }

    /// Entries of directory `path` (e.g. `"FIELD/MPS"`) from its first child while `keep` holds. Child lists have no length field in
    /// the table; the game itself scans forward by name.
    pub fn list_dir_while(&self, path: &str, mut keep: impl FnMut(&Entry) -> bool) -> Option<Vec<Entry>> {
        let info = self.disc.info();
        let start = info.dir_start(path)?;
        Some(info.entries()[start..].iter().map(Entry::from).take_while(|e| keep(e)).collect())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn real_table_if_present() {
        let Some(set) = PkbSet::from_env() else { return };
        let (archive, off, size) = set.resolve("FIELD/MPS/AP_00_U.MPS").unwrap();
        assert_eq!(archive, "FIELD");
        assert_eq!(off, 0x20b0800);
        assert_eq!(size, 0xf71b0);
        let d = set.read("FIELD/MPS/AP_00_U.MPS").unwrap();
        assert_eq!(&d[..8], b"SBD 0.11");
        let dir = set.list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC")).unwrap();
        assert_eq!(dir.len(), 86); // 43 maps x (MPS + MSC)
    }
}

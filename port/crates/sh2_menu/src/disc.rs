//! Menu-side view of the PKB archives (`PKFINFO.TBL` + `*.PKB`) so the scene loaders and tools can pull
//! `MENU/MSD/*.MSD`, `COMMON/CMNMENU.DAT`, `SAVELOAD/SAVELOAD.DAT` etc. from an unpacked disc folder
//! (`SH2_DISC_DIR`).  The reader itself is `sh2_core::fileio::Disc` (section A, `FileIOLib`); this module only
//! adds the [`FileSource`] abstraction the scene loaders take (`DvdromOrder::ReadOrder` in the original).

use sh2_core::fileio::{Disc, DirEntry};
use std::path::Path;

/// Abstraction used by the scene loaders (`DvdromOrder::ReadOrder` in the original).
pub trait FileSource {
    /// Read a whole file by archive path (`"MENU/MSD/GAMEOVER.MSD"`).
    fn read(&self, path: &str) -> Option<Vec<u8>>;
}

/// Thin wrapper over [`sh2_core::fileio::Disc`] implementing [`FileSource`].
pub struct DiscDir {
    disc: Disc,
}

impl DiscDir {
    pub fn open(root: impl AsRef<Path>) -> std::io::Result<Self> {
        Disc::open(root).map(|disc| DiscDir { disc }).map_err(|e| std::io::Error::new(std::io::ErrorKind::Other, e.to_string()))
    }

    /// The canonical reader.
    pub fn disc(&self) -> &Disc {
        &self.disc
    }

    /// Entries of directory `path` (e.g. `"MENU/MSD"`).
    pub fn list_dir(&self, path: &str) -> Option<Vec<DirEntry>> {
        self.disc.info().list_dir(path)
    }
}

impl FileSource for DiscDir {
    fn read(&self, path: &str) -> Option<Vec<u8>> {
        self.disc.read_opt(path)
    }
}

impl FileSource for Disc {
    fn read(&self, path: &str) -> Option<Vec<u8>> {
        self.read_opt(path)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::msd::{ChunkType, Msd};

    /// Runs only when `SH2_DISC_DIR` points at the JP Furokuban folder.
    #[test]
    fn gameover_msd_from_disc() {
        let Ok(dir) = std::env::var("SH2_DISC_DIR") else { return };
        let d = DiscDir::open(dir).unwrap();
        let data = d.read("MENU/MSD/GAMEOVER.MSD").expect("file");
        assert_eq!(data.len(), 0x19c);
        let m = Msd::parse(data).unwrap();
        assert_eq!(m.count(ChunkType::Text), 3);
        assert_eq!(m.resource_name(0).unwrap(), "MENU/IMG/GO/GO_%03d.TEX");
        assert_eq!(m.window(1).unwrap().w as u32, 240);
        let t = m.menu_text(0).unwrap();
        assert_eq!((t.x, t.y), (40.0, 0.0));
    }

    #[test]
    fn common_scene_parses() {
        let Ok(dir) = std::env::var("SH2_DISC_DIR") else { return };
        let d = DiscDir::open(dir).unwrap();
        let data = d.read("COMMON/CMNMENU.DAT").expect("file");
        let m = Msd::parse(data).unwrap();
        assert_eq!(m.count(ChunkType::Sprite), 33);
        assert_eq!(m.count(ChunkType::Polygon), 2);
    }
}

//! `PKFINFO.TBL` / `*.PKB` access for the LSD tools: thin adapter over the canonical reader `sh2_core::fileio`
//! (section A; `FileIOLib::InitPkb` JP 0x0022ae70, `deCode` 0x0022ca90, `SearchFile` 0x0022c7a0).
//!
//! Section E only needs `LSD/N00x.LSD` (stand-alone cutscene streams stored in `LSD.PKB`) and `OPENING/DEMO.LSD`
//! (inside `OPENING.PKB`).  LSD directory on the JP demo disc: `LSD/N003.LSD` .. `LSD/N007.LSD`; each starts with
//! an `LSDH` header (see [`crate::lsd`]).

pub use sh2_core::fileio::{decode_name, encode_name, DirEntry as PkfEntry, FileIoError as PkbError, FileLoc as PkbFile};

/// A disc folder containing `PKFINFO.TBL` and the `*.PKB` archives (set via `SH2_DISC_DIR`).
pub type PkbSet = sh2_core::fileio::Disc;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn lsd_entries_if_present() {
        let Some(set) = PkbSet::from_env() else { return };
        let f = set.info().search_file("LSD/N004.LSD").unwrap();
        assert_eq!(f.container, "LSD");
        assert!(f.in_archive);
        assert_eq!(f.byte_offset, 0xe4a000);
        let d = set.read("LSD/N004.LSD").unwrap();
        assert_eq!(&d[..4], b"LSDH");
    }
}

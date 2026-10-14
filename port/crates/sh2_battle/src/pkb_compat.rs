//! `PKFINFO.TBL` + `*.PKB` access for the battle data loaders: thin aliases over the canonical reader
//! `sh2_core::fileio` (section A: `FileIOLib` JP 0x0022ae70 `InitPkb`, 0x0022c7a0 `SearchFile`, 0x0022cfb0 `enCode`,
//! 0x0022ca90 `deCode`).  Section H originally shipped a self-contained stand-in; it was byte-identical in behaviour
//! and has been replaced by these aliases (the tests below are the stand-in's, now running against the shared reader).
//!
//! Battle needs `COMMON/SSHDAT.JPN`, `COMMON/SSHMES.JPN` and `BTLDATA/...` (see [`crate::data`]).

pub use sh2_core::fileio::{decode_name, encode_name, FileIoError as PkbError, FileLoc as PkbFile};

/// A disc folder (`SH2_DISC_DIR`) with its `PKFINFO.TBL`.
pub type PkbDisc = sh2_core::fileio::Disc;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn name_roundtrip() {
        for n in ["COMMON", "SSHDAT.JPN", "BTL_000.BIN", "000_00.WPN", "M000_000.AIS", "A", "ABCDEFGHIJKL"] {
            assert_eq!(decode_name(&encode_name(n)), n.to_ascii_uppercase(), "{n}");
        }
        assert_eq!(encode_name("common"), encode_name("COMMON"));
    }

    #[test]
    fn known_codes() {
        // from PKFINFO.TBL of the JP Furokuban build: first entry is FIELD.BIN
        assert_eq!(encode_name("FIELD.BIN"), [0x03, 0x0e, 0xdd, 0x31, 0xd9, 0x77, 0x00, 0x19]);
    }

    fn disc() -> Option<PkbDisc> {
        let candidates = [
            std::env::var("SH2_DISC_DIR").ok(),
            Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string()),
        ];
        candidates.into_iter().flatten().find_map(|d| PkbDisc::open(d).ok())
    }

    #[test]
    fn real_table_layout() {
        let Some(d) = disc() else { return };
        let info = d.info();
        let f = info.search_file("COMMON/SSHDAT.JPN").unwrap();
        assert_eq!((f.container.as_str(), f.in_archive, f.byte_offset, f.size), ("COMMON", true, 1048576, 70648));
        let f = info.search_file("BTLDATA/AIS/M000_000.AIS").unwrap();
        assert_eq!((f.container.as_str(), f.size), ("BTLDATA", 368));
        let f = info.search_file("BATTLE.BIN").unwrap();
        assert!(!f.in_archive);
        assert_eq!(f.size, 2254336);
        assert!(info.search_file("BTLDATA/NOPE").is_none());
        // all files lie inside their archives
        let mut n = 0;
        info.walk(|p, f| {
            n += 1;
            if f.in_archive {
                let len = std::fs::metadata(d.root().join(format!("{}.PKB", f.container))).unwrap().len();
                assert!(f.byte_offset + f.size as u64 <= len, "{p} out of range");
            }
        });
        assert_eq!(n, 1734);
    }

    #[test]
    fn real_sshdat_header() {
        let Some(d) = disc() else { return };
        let b = d.read("COMMON/SSHDAT.JPN").unwrap();
        assert_eq!(u32::from_le_bytes(b[0..4].try_into().unwrap()), 33);
        assert_eq!(u32::from_le_bytes(b[4..8].try_into().unwrap()) as usize, b.len());
    }
}

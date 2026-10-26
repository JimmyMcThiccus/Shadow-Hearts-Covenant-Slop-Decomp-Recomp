//! Host-side ISO 9660 reader for PS2 DVD images (`*.iso`, 2048-byte sectors).
//!
//! The console reads its files through the ISO 9660 directory (`sceCdSearchFile("\\PKFINFO.TBL;1")` in `FileIOLib::InitPkb`);
//! this is the same lookup on a disc image, so the port can run straight from a user's `.iso` instead of an extracted folder.
//! Only what the game's discs use is supported: one primary volume descriptor at sector 16, single-extent files, 8.3 names
//! with a `;1` version suffix.  Names are matched case-insensitively, without the version suffix.
//!
//! ```text
//! sector 16  PVD: +0x00 type 1, +0x01 "CD001", +0x9c root directory record (34 bytes)
//! dir record: +0x00 u8 len, +0x02 u32le extent LBA, +0x0a u32le data length, +0x19 u8 flags (bit 1 = directory),
//!             +0x20 u8 name len, +0x21 name ("\0" = ".", "\1" = ".."); records never cross a sector boundary (len 0 = skip to next sector)
//! ```

use std::collections::HashMap;
use std::fs::File;
use std::io::{self, Read, Seek, SeekFrom};
use std::path::{Path, PathBuf};

pub const SECTOR: u64 = 2048;
const PVD_SECTOR: u64 = 16;

/// Byte range of one file in the image.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct IsoFile {
    pub offset: u64,
    pub size: u64,
}

/// An indexed disc image: every file of every directory, keyed by its upper-case path without the `;1` suffix
/// (`"PKFINFO.TBL"`, `"MODULES/FIO.IRX"`).
#[derive(Debug)]
pub struct IsoImage {
    path: PathBuf,
    files: HashMap<String, IsoFile>,
    volume_id: String,
}

fn bad(msg: impl Into<String>) -> io::Error {
    io::Error::new(io::ErrorKind::InvalidData, msg.into())
}

/// `true` when `path` is a regular file with an ISO 9660 primary volume descriptor at sector 16.
pub fn is_iso(path: &Path) -> bool {
    let Ok(mut f) = File::open(path) else { return false };
    let mut pvd = [0u8; 6];
    f.seek(SeekFrom::Start(PVD_SECTOR * SECTOR)).is_ok() && f.read_exact(&mut pvd).is_ok() && &pvd[1..6] == b"CD001"
}

/// Upper-case lookup key: `\` and `/` separators, no leading separator, no `;n` version, no trailing `.`.
pub fn key(name: &str) -> String {
    let n = name.trim_start_matches(['/', '\\']).replace('\\', "/");
    let n = match n.rfind(';') {
        Some(i) => &n[..i],
        None => &n[..],
    };
    n.trim_end_matches('.').to_ascii_uppercase()
}

impl IsoImage {
    pub fn open(path: impl AsRef<Path>) -> io::Result<IsoImage> {
        let path = path.as_ref().to_path_buf();
        let mut f = File::open(&path)?;
        let mut pvd = vec![0u8; SECTOR as usize];
        f.seek(SeekFrom::Start(PVD_SECTOR * SECTOR))?;
        f.read_exact(&mut pvd)?;
        if pvd[0] != 1 || &pvd[1..6] != b"CD001" {
            return Err(bad(format!("{}: no ISO 9660 primary volume descriptor", path.display())));
        }
        let volume_id = String::from_utf8_lossy(&pvd[40..72]).trim_end_matches([' ', '\0']).to_string();
        let root = &pvd[156..156 + 34];
        let (lba, len) = (u32::from_le_bytes(root[2..6].try_into().unwrap()), u32::from_le_bytes(root[10..14].try_into().unwrap()));
        let mut files = HashMap::new();
        // (directory prefix, extent LBA, byte length); depth-bounded against malformed images that loop
        let mut todo = vec![(String::new(), lba, len, 0u32)];
        while let Some((prefix, lba, len, depth)) = todo.pop() {
            if depth > 16 {
                return Err(bad(format!("{}: directory tree too deep", path.display())));
            }
            let mut dir = vec![0u8; len as usize];
            f.seek(SeekFrom::Start(lba as u64 * SECTOR))?;
            f.read_exact(&mut dir)?;
            let mut p = 0usize;
            while p < dir.len() {
                let rl = dir[p] as usize;
                if rl == 0 {
                    // the rest of this sector is padding
                    p = (p / SECTOR as usize + 1) * SECTOR as usize;
                    continue;
                }
                if p + rl > dir.len() || rl < 34 {
                    return Err(bad(format!("{}: bad directory record in {prefix:?}", path.display())));
                }
                let r = &dir[p..p + rl];
                p += rl;
                let nl = r[32] as usize;
                if 33 + nl > rl {
                    return Err(bad(format!("{}: bad name length in {prefix:?}", path.display())));
                }
                let raw = &r[33..33 + nl];
                if raw == [0] || raw == [1] {
                    continue;
                }
                let name = format!("{prefix}{}", key(&String::from_utf8_lossy(raw)));
                let (e_lba, e_len) = (u32::from_le_bytes(r[2..6].try_into().unwrap()), u32::from_le_bytes(r[10..14].try_into().unwrap()));
                if r[25] & 2 != 0 {
                    todo.push((format!("{name}/"), e_lba, e_len, depth + 1));
                } else {
                    files.insert(name, IsoFile { offset: e_lba as u64 * SECTOR, size: e_len as u64 });
                }
            }
        }
        Ok(IsoImage { path, files, volume_id })
    }

    pub fn path(&self) -> &Path {
        &self.path
    }

    /// PVD volume identifier (`"SH2"` on the US retail discs).
    pub fn volume_id(&self) -> &str {
        &self.volume_id
    }

    pub fn find(&self, name: &str) -> Option<IsoFile> {
        self.files.get(&key(name)).copied()
    }

    /// Upper-case paths of every file on the image (unordered).
    pub fn names(&self) -> impl Iterator<Item = &str> {
        self.files.keys().map(String::as_str)
    }

    /// `len` bytes of file `name` from byte `offset` (clamped to the file's end).
    pub fn read_range(&self, name: &str, offset: u64, len: u64) -> io::Result<Vec<u8>> {
        let e = self.find(name).ok_or_else(|| io::Error::new(io::ErrorKind::NotFound, format!("{name} is not on {}", self.path.display())))?;
        let start = offset.min(e.size);
        let n = len.min(e.size - start);
        let mut f = File::open(&self.path)?;
        f.seek(SeekFrom::Start(e.offset + start))?;
        let mut buf = vec![0u8; n as usize];
        f.read_exact(&mut buf)?;
        Ok(buf)
    }

    pub fn read(&self, name: &str) -> io::Result<Vec<u8>> {
        self.read_range(name, 0, u64::MAX)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn keys() {
        assert_eq!(key("\\PKFINFO.TBL;1"), "PKFINFO.TBL");
        assert_eq!(key("modules\\fio.irx;1"), "MODULES/FIO.IRX");
        assert_eq!(key("DUMMY.;1"), "DUMMY");
        assert_eq!(key("SLUS_210.41"), "SLUS_210.41");
    }

    /// Hand-built two-level image: root has `A.BIN;1` and directory `SUB` holding `B.TXT;1`.
    #[test]
    fn synthetic_image() {
        fn rec(lba: u32, len: u32, dir: bool, name: &[u8]) -> Vec<u8> {
            let mut r = vec![0u8; 33 + name.len() + (name.len() + 1) % 2];
            r[0] = r.len() as u8;
            r[2..6].copy_from_slice(&lba.to_le_bytes());
            r[10..14].copy_from_slice(&len.to_le_bytes());
            r[25] = if dir { 2 } else { 0 };
            r[32] = name.len() as u8;
            r[33..33 + name.len()].copy_from_slice(name);
            r
        }
        let s = SECTOR as usize;
        let mut img = vec![0u8; 22 * s];
        img[16 * s] = 1;
        img[16 * s + 1..16 * s + 6].copy_from_slice(b"CD001");
        img[16 * s + 40..16 * s + 43].copy_from_slice(b"SH2");
        let root = rec(18, s as u32, true, &[0]);
        img[16 * s + 156..16 * s + 156 + 34].copy_from_slice(&root);
        let mut d = Vec::new();
        d.extend(rec(18, s as u32, true, &[0]));
        d.extend(rec(18, s as u32, true, &[1]));
        d.extend(rec(20, 5, false, b"A.BIN;1"));
        d.extend(rec(19, s as u32, true, b"SUB"));
        img[18 * s..18 * s + d.len()].copy_from_slice(&d);
        let mut d = Vec::new();
        d.extend(rec(19, s as u32, true, &[0]));
        d.extend(rec(18, s as u32, true, &[1]));
        d.extend(rec(21, 3, false, b"B.TXT;1"));
        img[19 * s..19 * s + d.len()].copy_from_slice(&d);
        img[20 * s..20 * s + 5].copy_from_slice(b"hello");
        img[21 * s..21 * s + 3].copy_from_slice(b"abc");

        let dir = std::env::temp_dir().join(format!("sh2_iso_test_{}", std::process::id()));
        std::fs::create_dir_all(&dir).unwrap();
        let p = dir.join("t.iso");
        std::fs::write(&p, &img).unwrap();
        assert!(is_iso(&p));
        let iso = IsoImage::open(&p).unwrap();
        assert_eq!(iso.volume_id(), "SH2");
        assert_eq!(iso.read("a.bin").unwrap(), b"hello");
        assert_eq!(iso.read("\\SUB\\B.TXT;1").unwrap(), b"abc");
        assert_eq!(iso.read_range("A.BIN", 1, 3).unwrap(), b"ell");
        assert_eq!(iso.read_range("A.BIN", 3, 100).unwrap(), b"lo");
        assert!(iso.find("SUB").is_none());
        assert!(iso.read("NOPE").is_err());
        let _ = std::fs::remove_dir_all(&dir);
    }
}

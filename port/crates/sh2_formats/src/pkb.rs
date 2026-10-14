//! Package directories *inside* a file extracted from a PKB archive.
//!
//! This is **not** the `PKFINFO.TBL` / `*.PKB` archive reader -- that is `sh2_core::fileio` (section A:
//! `encode_name`/`decode_name`/`PkfInfo`/`Disc`), which maps game paths to byte ranges of the archives.  What lives
//! here is the next level down: many extracted files (character models, motions, textures) are themselves a
//! "package" with a small directory `u32 count; u32 total_size; { [u8;4] type; u32 offset }[count]`, entry payloads at
//! `package_start + offset` (16-byte aligned, usually 0x40 aligned).  Types seen: `mdl` (model, `SSH1.01a`), `anm`
//! (motion, `SQHD`), `bin` (texture / misc).  (`sh2_battle::data::Container` parses the same layout for
//! `SSHDAT.JPN`/`SSHMES.JPN` but accepts non-alphanumeric tags such as `PC_I`.)

#[derive(Clone, Debug)]
pub struct Entry {
    pub kind: [u8; 4],
    /// Absolute offset in the PKB (package start + entry offset).
    pub offset: usize,
}

impl Entry {
    pub fn kind_str(&self) -> String {
        self.kind.iter().take_while(|&&c| c != 0).map(|&c| c as char).collect()
    }
}

#[derive(Clone, Debug)]
pub struct Package {
    pub start: usize,
    pub size: usize,
    pub entries: Vec<Entry>,
}

/// Parse a package directory at `start`; returns `None` if it does not look valid.
pub fn parse_package(d: &[u8], start: usize) -> Option<Package> {
    let h = d.get(start..start + 8)?;
    let n = u32::from_le_bytes([h[0], h[1], h[2], h[3]]) as usize;
    let size = u32::from_le_bytes([h[4], h[5], h[6], h[7]]) as usize;
    if n == 0 || n > 256 || size == 0 {
        return None;
    }
    let mut entries = Vec::with_capacity(n);
    for i in 0..n {
        let o = start + 8 + i * 8;
        let b = d.get(o..o + 8)?;
        let kind = [b[0], b[1], b[2], b[3]];
        if !kind[..3].iter().all(|c| c.is_ascii_alphanumeric()) {
            return None;
        }
        let off = u32::from_le_bytes([b[4], b[5], b[6], b[7]]) as usize;
        if off >= size.max(8 + n * 8) && off > size {
            return None;
        }
        entries.push(Entry { kind, offset: start + off });
    }
    Some(Package { start, size, entries })
}

/// Offsets of every occurrence of `magic` that is 16-byte aligned.
pub fn scan_magic(d: &[u8], magic: &[u8]) -> Vec<usize> {
    let mut out = Vec::new();
    let mut o = 0usize;
    while o + magic.len() <= d.len() {
        if &d[o..o + magic.len()] == magic {
            out.push(o);
        }
        o += 16;
    }
    out
}

/// Find the package whose directory lists an entry at `offset` (searches backwards).
pub fn find_package_for(d: &[u8], offset: usize) -> Option<Package> {
    let mut base = offset.saturating_sub(0x10) & !0xf;
    let lim = offset.saturating_sub(0x40_0000);
    loop {
        if let Some(p) = parse_package(d, base) {
            if p.entries.iter().any(|e| e.offset == offset) && base + p.size > offset {
                return Some(p);
            }
        }
        if base <= lim || base < 0x10 {
            return None;
        }
        base -= 0x10;
    }
}

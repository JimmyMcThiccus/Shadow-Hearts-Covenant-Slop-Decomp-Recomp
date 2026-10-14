//! FileIOLib / PKFINFO.TBL / PKB archives (JP `dvdorder.cpp`-adjacent file I/O library, class `FileIOLib`).
//!
//! The PS2 build talks to a custom IOP module (`FIO.IRX`, sif-cmd id "FIOIRX") for all disc I/O.
//! The EE side keeps a copy of `\PKFINFO.TBL;1` in `FileIOLib+0x60` (header) / `+0x70` (entries,
//! max 5000) and resolves every game path ("common/sshmes.jpn", "opening/opening.dat", ...) through
//! it into `(disc LBA, size)`.  This module is the host-side equivalent: it parses the very same
//! table and reads the very same `*.PKB` archives from the original disc folder.
//!
//! # PKFINFO.TBL layout (all little endian)
//!
//! ```text
//! +0x00 u16 entry_count      (1775 in the JP demo; == total_bytes / entry_size)
//! +0x02 u16 entry_size       (0x10)
//! +0x04 u32 total_bytes      (entry_count * 0x10)
//! +0x08 u8[8] zero
//! +0x10 PkbEntry[entry_count]
//! ```
//!
//! ```text
//! PkbEntry (16 bytes):
//!   +0x00 u8[8] key   -- 12-character name packed as 3 groups of 4 base-40 digits (see [`encode_name`])
//!   +0x08 u32  off16  -- start offset *in 16 byte units*, relative to the parent archive/directory.
//!                        For top-level entries it is 0 in the file and the loader overwrites it with
//!                        the disc LBA of "\NAME.PKB;1" (or "\NAME;1" for plain files).
//!   +0x0c u32  size_or_dir
//!           bit31 clear : size in bytes of the file
//!           bit31 set   : directory; low 31 bits = byte distance from the *start of the containing
//!                         list* to the first entry of the child list  (child_start = list_start + low31/16)
//! ```
//!
//! Lists are laid out depth-first: the root list is entries `0..first_dir_child_start`
//! (`FIELD.BIN`, `BATTLE.BIN`, then one directory entry per `*.PKB`: BTLDATA, COMMON, EFFECT, MENU,
//! FIELD, OPENING, SAVELOAD, WORLDMAP, SHOP, SOLOMON, LSD), followed immediately by the child list of the
//! first directory, followed by that list's sub-directories' lists, and so on.  A child list has no
//! stored length; the game (`searchInfo`) simply scans forward from the list start to the end of the table
//! looking for the 8-byte key.
//!
//! The absolute byte offset of a file inside its `.PKB` is the sum of `off16*16` along the path
//! (the root-level entry contributes the archive itself, offset 0).  All files are 16-byte aligned and
//! every directory/file start is 2048-byte (sector) aligned, which is why `FileIOLib::SearchFile` computes the
//! start LBA as `lba(archive) + sum(off16 >> 7)`.
//!
//! Verified on the Furokuban disc: for each of the 11 archives `max(file_end) == size_of(PKB)` exactly
//! (BTLDATA 259 files, COMMON 14, EFFECT 261, MENU 581, FIELD 599, OPENING 3, SAVELOAD 1, WORLDMAP 5, SHOP 2,
//! SOLOMON 2, LSD 5 = 1734 files + 41 directory entries = 1775).

use std::collections::BTreeMap;
use std::fs::File;
use std::io::{Read, Seek, SeekFrom};
use std::path::{Path, PathBuf};

use thiserror::Error;

/// Alphabet used by `enCode`/`deCode` (JP 0x003fda00, index 0 is the NUL padding digit).
/// digit value = position in this string; value 0 terminates a name.
pub const NAME_ALPHABET: &[u8; 39] = b"\0.0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
/// Names are at most 12 characters (3 groups of 4).
pub const NAME_MAX: usize = 12;

#[derive(Debug, Error)]
pub enum FileIoError {
    #[error("PKFINFO.TBL is truncated or malformed")]
    BadTable,
    #[error("path not found in PKFINFO.TBL: {0}")]
    NotFound(String),
    #[error("io error on {path}: {source}")]
    Io { path: PathBuf, source: std::io::Error },
}

/// JP 0x0022cfb0 `enCode__9FileIOLibFPcPc` — pack a name into the 8-byte table key.
///
/// Characters are upper-cased (`ch - 0x20` also matches), characters outside the alphabet are *skipped*
/// (they do not advance the output position), only the first 12 input characters are examined.
/// Each group of four digits `a0..a3` becomes `u = a0 + a1*40 + a2*1600 + a3*64000` (22 bits);
/// `hi_g = u >> 16`, `lo_g = u & 0xffff`; the key is the big-endian bytes of
/// `[hi0 + hi1*40 + hi2*1600, lo0, lo1, lo2]` (four u16).
pub fn encode_name(name: &str) -> [u8; 8] {
    let mut digits = [0u32; NAME_MAX];
    let mut n = 0;
    for &ch in name.as_bytes().iter().take(NAME_MAX) {
        let c = ch.to_ascii_uppercase();
        // game searches indices 0x25..=0 of the alphabet, i.e. digit values 38..=1
        if let Some(pos) = NAME_ALPHABET[1..].iter().position(|&a| a == c) {
            digits[n] = pos as u32 + 1;
            n += 1;
        }
    }
    let (mut hi, mut lo) = ([0u32; 3], [0u32; 3]);
    for g in 0..3 {
        let a = &digits[g * 4..g * 4 + 4];
        let u = a[0] + a[1] * 40 + a[2] * 1600 + a[3] * 64000;
        hi[g] = u >> 16;
        lo[g] = u & 0xffff;
    }
    let h = hi[0] + hi[1] * 40 + hi[2] * 1600;
    let w = [h as u16, lo[0] as u16, lo[1] as u16, lo[2] as u16];
    let mut out = [0u8; 8];
    for (i, v) in w.iter().enumerate() {
        out[i * 2..i * 2 + 2].copy_from_slice(&v.to_be_bytes());
    }
    out
}

/// JP 0x0022ca90 `deCode__9FileIOLibFPcPc` — inverse of [`encode_name`].
pub fn decode_name(key: &[u8; 8]) -> String {
    let w = |i: usize| u16::from_be_bytes([key[i * 2], key[i * 2 + 1]]) as u32;
    let h = w(0);
    let hi = [h % 40, (h / 40) % 40, (h / 1600) % 40];
    let mut s = String::new();
    for g in 0..3 {
        let u = (hi[g] << 16) | w(g + 1);
        for d in [1u32, 40, 1600, 64000] {
            let v = ((u / d) % 40) as usize;
            if v != 0 && v < NAME_ALPHABET.len() {
                s.push(NAME_ALPHABET[v] as char);
            }
        }
    }
    s
}

/// One 16-byte `PKFINFO.TBL` record.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct PkbEntry {
    pub key: [u8; 8],
    /// offset in 16-byte units (relative to parent), or LBA for top-level entries once mounted
    pub off16: u32,
    pub size_or_dir: u32,
}

impl PkbEntry {
    #[inline]
    pub fn is_dir(&self) -> bool {
        self.size_or_dir & 0x8000_0000 != 0
    }
    /// byte size for files
    #[inline]
    pub fn size(&self) -> u32 {
        self.size_or_dir
    }
    /// For directories: offset (in entries) from the containing list's start to the child list.
    #[inline]
    pub fn child_delta(&self) -> usize {
        ((self.size_or_dir & 0x7fff_ffff) / 16) as usize
    }
    pub fn name(&self) -> String {
        decode_name(&self.key)
    }
}

/// Result of resolving a path (`FileIOLib::SearchFile(path, _CDVDRINFO*)`).
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct FileLoc {
    /// top-level container name: a plain disc file ("FIELD.BIN") or an archive stem ("COMMON" => COMMON.PKB)
    pub container: String,
    /// true when `container` is an archive (`<container>.PKB`), false for a plain disc file (`<container>;1`)
    pub in_archive: bool,
    /// byte offset inside the container (sum of off16*16 along the path); 0 for plain files
    pub byte_offset: u64,
    /// `_CDVDRINFO.+0x10`-style relative sector: sum over *nested* levels of (off16 >> 7), root level excluded
    pub sector_in_archive: u32,
    /// file size in bytes (`_CDVDRINFO.+0x18`)
    pub size: u32,
}

/// A decoded table entry as seen by directory listings (name already decoded; used by the tools and the
/// data crates that enumerate e.g. `FIELD/MPS`).
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct DirEntry {
    pub name: String,
    /// offset in 16-byte units relative to the parent (see [`PkbEntry::off16`])
    pub offset16: u32,
    /// byte size for files, `0x8000_0000 | child_list_byte_distance` for directories
    pub size_or_dir: u32,
}

impl DirEntry {
    #[inline]
    pub fn is_dir(&self) -> bool {
        self.size_or_dir & 0x8000_0000 != 0
    }
    /// file size in bytes (0 for directories)
    #[inline]
    pub fn size(&self) -> u32 {
        if self.is_dir() { 0 } else { self.size_or_dir }
    }
}

impl From<&PkbEntry> for DirEntry {
    fn from(e: &PkbEntry) -> Self {
        DirEntry { name: e.name(), offset16: e.off16, size_or_dir: e.size_or_dir }
    }
}

/// Parsed `PKFINFO.TBL` (what `InitPkb` leaves in `FileIOLib+0x60..`).
#[derive(Debug, Clone)]
pub struct PkfInfo {
    entries: Vec<PkbEntry>,
    /// number of leading root entries (`Dircount`); the game scans the root list only up to this index (inclusive)
    dircount: usize,
}

impl PkfInfo {
    /// Parse the table image (`\PKFINFO.TBL;1`).  JP 0x0022ae70 `InitPkb` (the parsing part).
    pub fn parse(bytes: &[u8]) -> Result<Self, FileIoError> {
        if bytes.len() < 0x10 {
            return Err(FileIoError::BadTable);
        }
        let ent_size = u16::from_le_bytes([bytes[2], bytes[3]]) as usize;
        let total = u32::from_le_bytes(bytes[4..8].try_into().unwrap()) as usize;
        if ent_size != 16 || total % 16 != 0 || bytes.len() < 0x10 + total {
            return Err(FileIoError::BadTable);
        }
        let count = total / ent_size; // FileIOLib+0x13ae0
        if count >= 5000 {
            return Err(FileIoError::BadTable); // the game refuses tables of 5000+ entries
        }
        let mut entries = Vec::with_capacity(count);
        for i in 0..count {
            let o = 0x10 + i * 16;
            entries.push(PkbEntry {
                key: bytes[o..o + 8].try_into().unwrap(),
                off16: u32::from_le_bytes(bytes[o + 8..o + 12].try_into().unwrap()),
                size_or_dir: u32::from_le_bytes(bytes[o + 12..o + 16].try_into().unwrap()),
            });
        }
        // Dircount: InitPkb walks the root list: first the plain files (bit31 clear) and then the
        // directory entries; it counts every one it resolves.  The root list ends where the first
        // directory's child list begins.
        let first_child = entries.iter().find(|e| e.is_dir()).map(|e| e.child_delta()).unwrap_or(entries.len());
        Ok(PkfInfo { entries, dircount: first_child })
    }

    pub fn entries(&self) -> &[PkbEntry] {
        &self.entries
    }
    pub fn dircount(&self) -> usize {
        self.dircount
    }

    /// JP 0x0022c980 `searchInfo__9FileIOLibFiPcPi` — scan from `start` for the 8-byte key.
    /// Root lookups (`start == 0`) stop after index `Dircount` (inclusive); all others run to the table end.
    fn search_info(&self, start: usize, key: &[u8; 8]) -> Option<usize> {
        let mut i = start;
        while i < self.entries.len() {
            if start == 0 && self.dircount < i {
                return None;
            }
            if &self.entries[i].key == key {
                return Some(i);
            }
            i += 1;
        }
        None
    }

    /// JP 0x0022c7a0 `SearchFile__9FileIOLibFPcP10_CDVDRINFO`.
    ///
    /// `path` uses '/' separators; a leading '/' is skipped (`gettokun`); components are
    /// matched case-insensitively and truncated to 12 characters.
    pub fn search_file(&self, path: &str) -> Option<FileLoc> {
        let mut list_start = 0usize;
        let mut container = String::new();
        let mut in_archive = false;
        let mut byte_offset = 0u64;
        let mut sector = 0u32;
        let mut size = 0u32;
        let mut first = true;
        let comps: Vec<&str> = path.split('/').filter(|c| !c.is_empty()).collect();
        if comps.is_empty() {
            return None;
        }
        for (n, comp) in comps.iter().enumerate() {
            let key = encode_name(comp);
            let idx = self.search_info(list_start, &key)?;
            let e = &self.entries[idx];
            if first {
                container = e.name();
                in_archive = e.is_dir();
                // the root entry's off16 is the disc LBA (filled by InitPkb), not an in-archive offset
            } else {
                byte_offset += e.off16 as u64 * 16;
                sector += e.off16 >> 7;
            }
            size = e.size_or_dir;
            if e.is_dir() {
                // iVar1 = iVar2 + (low31 / 0x10): relative to the start of the list just searched
                list_start += e.child_delta();
            } else if n + 1 != comps.len() {
                return None; // a file in the middle of a path
            }
            first = false;
        }
        Some(FileLoc { container, in_archive, byte_offset, sector_in_archive: sector, size: size & 0x7fff_ffff })
    }

    /// Index of the first entry of the child list of directory `path` (`"FIELD/MPS"`).  Child lists have no stored
    /// length: the game scans forward by name ([`PkfInfo::search_file`]); use [`PkfInfo::list_dir`] for the structural extent.
    pub fn dir_start(&self, path: &str) -> Option<usize> {
        self.dir_range(path).map(|(s, _)| s)
    }

    /// Entries of the directory `path` (files and sub-directories, in table order).
    ///
    /// The extent of a list is structural: it ends where the child list of its first directory entry begins, or --
    /// for a list without sub-directories -- where its parent's next sibling list begins (the same rule [`PkfInfo::walk`] uses).
    pub fn list_dir(&self, path: &str) -> Option<Vec<DirEntry>> {
        let (s, e) = self.dir_range(path)?;
        Some(self.entries[s..e].iter().map(DirEntry::from).collect())
    }

    /// Extent `[start, end)` of the list that starts at `start` and may not run beyond `limit`.
    fn list_extent(&self, start: usize, limit: usize) -> usize {
        let limit = limit.min(self.entries.len());
        let mut i = start;
        while i < limit {
            let e = &self.entries[i];
            i += 1;
            if e.is_dir() {
                return (start + e.child_delta()).min(limit).max(i);
            }
        }
        limit
    }

    /// `[start, end)` of the child list of directory `path` (empty path = the root list).
    fn dir_range(&self, path: &str) -> Option<(usize, usize)> {
        let n = self.entries.len();
        let (mut start, mut limit) = (0usize, n);
        let mut end = self.list_extent(0, n);
        for comp in path.split('/').filter(|c| !c.is_empty()) {
            let idx = self.search_info(start, &encode_name(comp))?;
            let e = &self.entries[idx];
            if !e.is_dir() {
                return None;
            }
            let next = self.entries[(idx + 1).min(end)..end]
                .iter()
                .find(|x| x.is_dir())
                .map(|x| start + x.child_delta())
                .unwrap_or(limit);
            start += e.child_delta();
            limit = next;
            end = self.list_extent(start, limit);
        }
        Some((start, end))
    }

    /// Walk the whole table in the same (depth first) order the build tool wrote it, calling `f(path, loc)`.
    pub fn walk<F: FnMut(&str, &FileLoc)>(&self, mut f: F) {
        let root_end = self.dircount.min(self.entries.len());
        for (n, e) in self.entries[..root_end].iter().enumerate() {
            let name = e.name();
            if e.is_dir() {
                let next_dir_child = self.entries[n + 1..root_end]
                    .iter()
                    .find(|x| x.is_dir())
                    .map(|x| x.child_delta())
                    .unwrap_or(self.entries.len());
                self.walk_list(e.child_delta(), next_dir_child, &name, 0, 0, &name, &mut f);
            } else {
                f(&name, &FileLoc { container: name.clone(), in_archive: false, byte_offset: 0, sector_in_archive: 0, size: e.size() });
            }
        }
    }

    #[allow(clippy::too_many_arguments)]
    fn walk_list<F: FnMut(&str, &FileLoc)>(&self, start: usize, limit: usize, prefix: &str, base: u64, base_sec: u32, container: &str, f: &mut F) {
        // determine list extent: up to the first dir's child list start
        let mut end = start;
        let mut first_child: Option<usize> = None;
        while end < limit.min(self.entries.len()) {
            let e = &self.entries[end];
            if e.is_dir() && first_child.is_none() {
                first_child = Some(start + e.child_delta());
            }
            end += 1;
            if let Some(c) = first_child {
                if end >= c {
                    break;
                }
            }
        }
        let idxs: Vec<usize> = (start..end).collect();
        for (n, &i) in idxs.iter().enumerate() {
            let e = &self.entries[i];
            let name = e.name();
            let path = format!("{prefix}/{name}");
            let off = base + e.off16 as u64 * 16;
            let sec = base_sec + (e.off16 >> 7);
            if e.is_dir() {
                let child = start + e.child_delta();
                let nxt = idxs[n + 1..]
                    .iter()
                    .find(|&&j| self.entries[j].is_dir())
                    .map(|&j| start + self.entries[j].child_delta())
                    .unwrap_or(limit);
                self.walk_list(child, nxt, &path, off, sec, container, f);
            } else {
                f(&path, &FileLoc { container: container.to_string(), in_archive: true, byte_offset: off, sector_in_archive: sec, size: e.size() });
            }
        }
    }
}

/// A disc image rooted at a host directory (`SH2_DISC_DIR`) that contains `PKFINFO.TBL`, `*.PKB`,
/// `FIELD.BIN`, `BATTLE.BIN`, `SLPM_602.19`, ...
pub struct Disc {
    root: PathBuf,
    info: PkfInfo,
}

impl Disc {
    pub fn open(root: impl AsRef<Path>) -> Result<Self, FileIoError> {
        let root = root.as_ref().to_path_buf();
        let p = root.join("PKFINFO.TBL");
        let bytes = std::fs::read(&p).map_err(|source| FileIoError::Io { path: p, source })?;
        Ok(Disc { info: PkfInfo::parse(&bytes)?, root })
    }
    pub fn info(&self) -> &PkfInfo {
        &self.info
    }
    /// Open the disc folder named by an environment variable (`SH2_DISC_DIR`, `SH2_US_DISC_DIR`); `None` when unset or unreadable.
    pub fn from_env_var(var: &str) -> Option<Self> {
        Self::open(std::env::var_os(var)?).ok()
    }
    /// `SH2_DISC_DIR` (the JP Furokuban folder).
    pub fn from_env() -> Option<Self> {
        Self::from_env_var("SH2_DISC_DIR")
    }
    pub fn root(&self) -> &Path {
        &self.root
    }
    /// Convenience for loaders that only care whether a file exists: `read` as an `Option`.
    pub fn read_opt(&self, path: &str) -> Option<Vec<u8>> {
        self.read(path).ok()
    }

    fn container_path(&self, loc: &FileLoc) -> PathBuf {
        if loc.in_archive {
            self.root.join(format!("{}.PKB", loc.container))
        } else {
            self.root.join(&loc.container)
        }
    }

    /// `FileIOLib::open` + `read` + `close` in one go (what `BlockRead` / `DvdromOrder::ReadOrder` end up doing).
    pub fn read(&self, path: &str) -> Result<Vec<u8>, FileIoError> {
        let loc = self.info.search_file(path).ok_or_else(|| FileIoError::NotFound(path.to_string()))?;
        let p = self.container_path(&loc);
        let io = |source| FileIoError::Io { path: p.clone(), source };
        let mut f = File::open(&p).map_err(io)?;
        f.seek(SeekFrom::Start(loc.byte_offset)).map_err(io)?;
        let mut buf = vec![0u8; loc.size as usize];
        f.read_exact(&mut buf).map_err(io)?;
        Ok(buf)
    }

    /// All files grouped by container (archive stem or plain file name) — used for listing/verification.
    pub fn listing(&self) -> BTreeMap<String, Vec<(String, FileLoc)>> {
        let mut m: BTreeMap<String, Vec<(String, FileLoc)>> = BTreeMap::new();
        self.info.walk(|p, l| m.entry(l.container.clone()).or_default().push((p.to_string(), l.clone())));
        m
    }
}

/// `SSHSys::GetFullPathName` + `SysTool::AddLocalPath` — language specific lookups.
///
/// `lang` is `SSHSys::Language` (see [`crate::boot::get_language`]).  The game first tries
/// `pDataPath + name`; if `SearchFile` fails it inserts the language directory *before the file name*:
/// "common/sshmes.jpn" -> "common/JPN/sshmes.jpn" (prefix table at JP 0x003f8870: "", "JPN/", "USA/",
/// "GBR/", "FRA/", "GER/", "ITA/", "SPA/").
pub fn add_local_path(path: &str, lang: usize) -> Option<String> {
    const LOCAL: [&str; 8] = ["", "JPN/", "USA/", "GBR/", "FRA/", "GER/", "ITA/", "SPA/"];
    let prefix = LOCAL.get(lang).copied().unwrap_or("");
    let (dir, file) = match path.rfind('/') {
        Some(i) => (&path[..=i], &path[i + 1..]),
        None => ("", path),
    };
    // already contains the prefix as its last directory component?
    if !prefix.is_empty() && dir.ends_with(prefix) {
        return None; // game returns -1
    }
    Some(format!("{dir}{prefix}{file}"))
}

// ----------------------------------------------------------------------------------------------------
// US retail FileIOLib differences (notes/I/us_delta.md)
// ----------------------------------------------------------------------------------------------------
//
// * `FileIOLib` is 0x20 bytes smaller (0x13ac8, JP 0x13ae8): the disc bookkeeping that used to live in the object
//   (`diskState` +0x13934, `diskResult` +0x13938, `diskNo` +0x1393c, layer +0x13940, volume label +0x13944) moved to
//   globals (state/result words near 0x0043fc60.., label buffer 0x0042cf40, disc number global read by `SSHSys::GetDiscNo` 0x003eeb10) and
//   `SSHSys::Polling` clears `fioBusy` when the *global* disk state (0x0043fc68) drops to 0.
// * `InitPkb(first)` takes a flag.  `first != 0` (called from `Initialize`) stores the volume label and the disc number
//   found in the ISO9660 primary volume descriptor (sector 0x10); `first == 0` (disc swap / retry) verifies them and fails
//   with `diskState = 3`, `diskResult = -1` on a mismatch.  JP only compared against the label "DEFAULT".
// * `sceCdPOffCallback(PowerOffCallBack)` is no longer registered by `SetHddDeviceName`; instead `ResetSystem` stops the
//   LSDPlayer and issues `sceDevctl("hdd0:", 0x5003)` (HDD cache flush) before the reset.
// * `Initialize` no longer calls `sceCdDiskReady(0)` / copies the default label; `fioCmdCall` takes more arguments.
// * New helper `FileIOLib::PrepareFile` (0x00229ea0): `gettokun` + `enCode` + `searchInfo` for a streaming path and clears the
//   0x100-byte read-ahead buffer at 0x0044ef60.

/// Volume identification kept by the retail `InitPkb` (label = PVD+0x28, 0x15 bytes compared with `strncmp`;
/// disc number = `sscanf(PVD+0xbe, "%d")` of the *volume set identifier*).
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct VolumeId {
    pub label: [u8; 0x15],
    pub disc_no: i32,
}

/// ISO9660 sector 0x10 offsets used by `InitPkb`.
pub const PVD_SECTOR: u32 = 0x10;
pub const PVD_LABEL_OFFSET: usize = 0x28;
pub const PVD_LABEL_LEN: usize = 0x15;
pub const PVD_VOLUME_SET_OFFSET: usize = 0xbe;

impl VolumeId {
    /// Parse a 2048-byte primary volume descriptor.  The disc number is the first decimal integer of the volume set
    /// identifier (`sscanf("%d")` skips leading white space); `0` when there is none.
    pub fn from_pvd(sector: &[u8]) -> Option<VolumeId> {
        if sector.len() < PVD_VOLUME_SET_OFFSET + 8 {
            return None;
        }
        let mut label = [0u8; PVD_LABEL_LEN];
        label.copy_from_slice(&sector[PVD_LABEL_OFFSET..PVD_LABEL_OFFSET + PVD_LABEL_LEN]);
        let tail = &sector[PVD_VOLUME_SET_OFFSET..(PVD_VOLUME_SET_OFFSET + 128).min(sector.len())];
        let s: String = tail.iter().map(|&b| b as char).collect();
        let s = s.trim_start();
        let digits: String = s.chars().take_while(|c| c.is_ascii_digit()).collect();
        Some(VolumeId { label, disc_no: digits.parse().unwrap_or(0) })
    }
}

/// `FileIOLib::diskState`/`diskResult` as left by the retail `InitPkb(first)`.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct DiskStatus {
    /// 0 ok, 2 (JP) / 3 (US) = wrong disc inserted
    pub state: u32,
    /// -1 after a failed verification
    pub result: i32,
}

/// Retail disc identity tracking (`InitPkb(this, first)`).
#[derive(Debug, Clone, Default)]
pub struct DiscIdentity {
    pub known: Option<VolumeId>,
    pub status: DiskStatus,
}

impl DiscIdentity {
    /// `first == true`: remember (label, disc no).  Otherwise verify; returns `false` (and sets the status) on mismatch.
    pub fn check(&mut self, first: bool, vol: &VolumeId) -> bool {
        if first || self.known.is_none() {
            self.known = Some(vol.clone());
            return true;
        }
        if self.known.as_ref() == Some(vol) {
            self.status = DiskStatus::default();
            true
        } else {
            self.status = DiskStatus { state: 3, result: -1 };
            false
        }
    }
    /// `SSHSys::GetDiscNo` (0x003eeb10)
    pub fn disc_no(&self) -> i32 {
        self.known.as_ref().map(|v| v.disc_no).unwrap_or(0)
    }
}

#[cfg(test)]
mod us_tests {
    use super::*;

    fn pvd(label: &str, set: &str) -> Vec<u8> {
        let mut s = vec![b' '; 2048];
        s[PVD_LABEL_OFFSET..PVD_LABEL_OFFSET + label.len()].copy_from_slice(label.as_bytes());
        s[PVD_VOLUME_SET_OFFSET..PVD_VOLUME_SET_OFFSET + set.len()].copy_from_slice(set.as_bytes());
        s
    }

    #[test]
    fn volume_id_and_disc_swap_check() {
        let d1 = VolumeId::from_pvd(&pvd("SHADOWHEARTS2", "  1")).unwrap();
        let d2 = VolumeId::from_pvd(&pvd("SHADOWHEARTS2", "2")).unwrap();
        assert_eq!((d1.disc_no, d2.disc_no), (1, 2));
        let mut id = DiscIdentity::default();
        assert!(id.check(true, &d1));
        assert_eq!(id.disc_no(), 1);
        assert!(id.check(false, &d1));
        assert!(!id.check(false, &d2));
        assert_eq!(id.status, DiskStatus { state: 3, result: -1 });
        assert!(id.check(false, &d1));
        assert_eq!(id.status, DiskStatus::default());
    }

    /// The retail disc resolves the `.NA` data tables through the same PKFINFO.TBL reader (`SH2_US_DISC_DIR`).
    #[test]
    fn retail_disc_resolves_na_names() {
        let Some(disc) = Disc::from_env_var("SH2_US_DISC_DIR") else { return };
        for name in ["common/sshmes.na", "common/sshdat.na", "opening/opening.dat", "opening/theater.dat", "opening/install.dat",
                     "opening/demo.lsd", "OPENING/BGM803.SSV", "saveLoad/saveLoad.dat", "OPENING.BIN", "FIELD.BIN", "BATTLE.BIN"] {
            let loc = disc.info().search_file(name).unwrap_or_else(|| panic!("{name} not found"));
            assert!(loc.size > 0, "{name}");
        }
        let mes = disc.read("common/sshmes.na").unwrap();
        assert_eq!(mes.len(), 77500);
        assert_eq!(u32::from_le_bytes(mes[..4].try_into().unwrap()), 0x2f); // 44 -> 47 tables (JP 0x2c)
        let dat = disc.read("common/sshdat.na").unwrap();
        assert_eq!(dat.len(), 222200);
        // the executable never asks for the language directories: no JPN/USA/... lists on the retail disc
        for lang in ["JPN", "USA", "GBR", "FRA", "GER", "ITA", "SPA"] {
            assert!(disc.info().search_file(&format!("common/{lang}/sshmes.na")).is_none());
        }
        // OPENING.BIN is a plain disc file: MWo3 group 3
        let ov = disc.read("OPENING.BIN").unwrap();
        let h = crate::overlay::OverlayHeader::parse(&ov).unwrap();
        assert_eq!((h.id, h.load_addr, h.text_size, h.name.as_str()), (3, 0x0045_ea80, 0xdc40, "OPENING.BIN"));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn name_codec_matches_game() {
        // first table entry of the Furokuban PKFINFO.TBL: FIELD.BIN
        assert_eq!(encode_name("FIELD.BIN"), [0x03, 0x0e, 0xdd, 0x31, 0xd9, 0x77, 0x00, 0x19]);
        assert_eq!(encode_name("field.bin"), encode_name("FIELD.BIN"));
        assert_eq!(decode_name(&encode_name("000W00.SSE")), "000W00.SSE");
        assert_eq!(decode_name(&encode_name("BTL_000.BIN")), "BTL_000.BIN");
    }

    #[test]
    fn local_path() {
        assert_eq!(add_local_path("common/sshmes.jpn", 1).unwrap(), "common/JPN/sshmes.jpn");
        assert_eq!(add_local_path("sshmes.jpn", 2).unwrap(), "USA/sshmes.jpn");
        assert!(add_local_path("common/JPN/x", 1).is_none());
    }

    /// Directory listings must agree with the depth-first walk on the real disc(s).
    #[test]
    fn list_dir_matches_walk() {
        for var in ["SH2_DISC_DIR", "SH2_US_DISC_DIR"] {
            let Some(disc) = Disc::from_env_var(var) else { continue };
            let mut parents: BTreeMap<String, Vec<String>> = BTreeMap::new();
            disc.info().walk(|p, _| {
                if let Some(i) = p.rfind('/') {
                    parents.entry(p[..i].to_string()).or_default().push(p[i + 1..].to_string());
                }
            });
            assert!(parents.contains_key("FIELD/MPS"), "{var}");
            for (dir, files) in &parents {
                let list = disc.info().list_dir(dir).unwrap_or_else(|| panic!("{var}: {dir}"));
                let got: Vec<&str> = list.iter().filter(|e| !e.is_dir()).map(|e| e.name.as_str()).collect();
                let want: Vec<&str> = files.iter().map(|s| s.as_str()).collect();
                assert_eq!(got, want, "{var}: {dir}");
            }
            assert!(disc.info().list_dir("FIELD/MPS/NOPE").is_none());
        }
    }

    /// Runs against the real disc when `SH2_DISC_DIR` is set; verifies archive sizes add up exactly.
    #[test]
    fn real_disc_archives_are_exact() {
        let Ok(dir) = std::env::var("SH2_DISC_DIR") else { return };
        let disc = Disc::open(&dir).unwrap();
        let listing = disc.listing();
        let mut n = 0;
        for (cont, files) in &listing {
            n += files.len();
            if let Some((_, l)) = files.first() {
                if l.in_archive {
                    let sz = std::fs::metadata(Path::new(&dir).join(format!("{cont}.PKB"))).unwrap().len();
                    let end = files.iter().map(|(_, l)| l.byte_offset + l.size as u64).max().unwrap();
                    assert_eq!(sz, end, "{cont}");
                }
            }
        }
        assert_eq!(n, 1734);
    }
}

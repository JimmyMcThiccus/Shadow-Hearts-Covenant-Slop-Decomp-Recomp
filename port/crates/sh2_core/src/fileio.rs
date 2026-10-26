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

use crate::iso::IsoImage;

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

/// Where a disc's files come from: an extracted folder or a `.iso` image of the disc ([`crate::iso`]).  Every `SH2_*_DISC*_DIR`
/// variable and every `root: &Path` handed around the crates may name either; [`read_disc_file`] & co. take such a root.
#[derive(Debug, Clone)]
pub enum DiscSource {
    Dir(PathBuf),
    Iso(std::sync::Arc<IsoImage>),
}

/// Parsed images by path, so the many loaders that each open "the disc" index an image's directory tree once.
fn iso_cache() -> &'static std::sync::Mutex<std::collections::HashMap<PathBuf, std::sync::Arc<IsoImage>>> {
    static CACHE: std::sync::OnceLock<std::sync::Mutex<std::collections::HashMap<PathBuf, std::sync::Arc<IsoImage>>>> = std::sync::OnceLock::new();
    CACHE.get_or_init(Default::default)
}

impl DiscSource {
    /// A folder, or a file holding an ISO 9660 image.
    pub fn open(root: impl AsRef<Path>) -> std::io::Result<DiscSource> {
        let root = root.as_ref();
        if !root.is_file() {
            return Ok(DiscSource::Dir(root.to_path_buf()));
        }
        let mut cache = iso_cache().lock().unwrap_or_else(|e| e.into_inner());
        if let Some(i) = cache.get(root) {
            return Ok(DiscSource::Iso(i.clone()));
        }
        let i = std::sync::Arc::new(IsoImage::open(root)?);
        cache.insert(root.to_path_buf(), i.clone());
        Ok(DiscSource::Iso(i))
    }

    /// The folder or image path.
    pub fn path(&self) -> &Path {
        match self {
            DiscSource::Dir(p) => p,
            DiscSource::Iso(i) => i.path(),
        }
    }

    /// Does the disc hold top-level (or `DIR/NAME`) file `name`?
    pub fn exists(&self, name: &str) -> bool {
        match self {
            DiscSource::Dir(p) => p.join(name).is_file(),
            DiscSource::Iso(i) => i.find(name).is_some(),
        }
    }

    /// Size in bytes of file `name`.
    pub fn len(&self, name: &str) -> std::io::Result<u64> {
        match self {
            DiscSource::Dir(p) => Ok(std::fs::metadata(p.join(name))?.len()),
            DiscSource::Iso(i) => i.find(name).map(|f| f.size).ok_or_else(|| std::io::Error::new(std::io::ErrorKind::NotFound, name.to_string())),
        }
    }

    /// `len` bytes of file `name` from `offset` (clamped to the end of the file).
    pub fn read_range(&self, name: &str, offset: u64, len: u64) -> std::io::Result<Vec<u8>> {
        match self {
            DiscSource::Dir(p) => {
                let mut f = File::open(p.join(name))?;
                let size = f.metadata()?.len();
                let start = offset.min(size);
                f.seek(SeekFrom::Start(start))?;
                let mut buf = vec![0u8; len.min(size - start) as usize];
                f.read_exact(&mut buf)?;
                Ok(buf)
            }
            DiscSource::Iso(i) => i.read_range(name, offset, len),
        }
    }

    pub fn read(&self, name: &str) -> std::io::Result<Vec<u8>> {
        match self {
            DiscSource::Dir(p) => std::fs::read(p.join(name)),
            DiscSource::Iso(i) => i.read(name),
        }
    }

    /// Upper-case names of the files in the disc's root directory.
    pub fn root_files(&self) -> Vec<String> {
        match self {
            DiscSource::Dir(p) => std::fs::read_dir(p)
                .map(|rd| rd.flatten().filter(|e| e.path().is_file()).map(|e| e.file_name().to_string_lossy().to_ascii_uppercase()).collect())
                .unwrap_or_default(),
            DiscSource::Iso(i) => i.names().filter(|n| !n.contains('/')).map(str::to_string).collect(),
        }
    }
}

/// `std::fs::read(root.join(name))` for a disc root that is a folder or a `.iso` image.
pub fn read_disc_file(root: impl AsRef<Path>, name: &str) -> std::io::Result<Vec<u8>> {
    DiscSource::open(root)?.read(name)
}

/// `root.join(name).exists()` for a disc root that is a folder or a `.iso` image.
pub fn disc_file_exists(root: impl AsRef<Path>, name: &str) -> bool {
    DiscSource::open(root).map(|s| s.exists(name)).unwrap_or(false)
}

/// The disc variable a disc image or folder belongs in, by the boot ELF on it: `SLPM_602.19` = the JP Furokuban demo (`SH2_DISC_DIR`),
/// `SLUS_210.41` / `SLUS_210.44` = US retail disc 1 / 2 (`SH2_US_DISC_DIR` / `SH2_US_DISC2_DIR`); `None` for any other disc.
pub fn disc_env_var(root: impl AsRef<Path>) -> Option<&'static str> {
    let src = DiscSource::open(root).ok()?;
    if !src.exists("PKFINFO.TBL") {
        return None;
    }
    [("SLPM_602.19", "SH2_DISC_DIR"), ("SLUS_210.41", "SH2_US_DISC_DIR"), ("SLUS_210.44", "SH2_US_DISC2_DIR")]
        .into_iter()
        .find(|(elf, _)| src.exists(elf))
        .map(|(_, var)| var)
}

/// Drag-and-drop discs: the user's disc images (`*.iso`, any file names) in the folder of the running executable, and in the folder
/// named by `SH2_DISCS` when set (searched first).  Each image is identified by its boot ELF ([`disc_env_var`]) and fills that disc
/// variable when it is unset, so the port runs from the images without extracting anything.  Returns the `(variable, image)` pairs it set.
pub fn discover_disc_images() -> Vec<(&'static str, PathBuf)> {
    let exe_dir = std::env::current_exe().ok().and_then(|p| p.parent().map(Path::to_path_buf));
    let dirs: Vec<PathBuf> = std::env::var_os("SH2_DISCS").map(PathBuf::from).into_iter().chain(exe_dir).collect();
    let mut images = Vec::new();
    for dir in dirs {
        let Ok(rd) = std::fs::read_dir(&dir) else { continue };
        let mut found: Vec<PathBuf> = rd
            .flatten()
            .map(|e| e.path())
            .filter(|p| p.is_file() && p.extension().is_some_and(|x| x.eq_ignore_ascii_case("iso")) && crate::iso::is_iso(p))
            .collect();
        found.sort();
        images.extend(found);
    }
    let mut set = Vec::new();
    for p in images {
        if let Some(var) = disc_env_var(&p) {
            if std::env::var_os(var).is_none() {
                std::env::set_var(var, &p);
                set.push((var, p));
            }
        }
    }
    set
}

/// A disc rooted at a host directory or `.iso` image (`SH2_DISC_DIR`) that contains `PKFINFO.TBL`, `*.PKB`,
/// `FIELD.BIN`, `BATTLE.BIN`, `SLPM_602.19`, ...
///
/// **Two-disc set (US retail, round 5 CS)**: the US game ships on two discs whose files are byte-identical except `LSD.PKB` /
/// `PKFINFO.TBL` (disc 1 = `SLUS_210.41`: 90 LSD scenes `N001..N076`, `M01..M15`, `MOVIE_A..D`, `G02`, `OPI_E00`; disc 2 = `SLUS_210.44`: 75
/// scenes `N077..N130`, `M16`, `M17`, `MOVIE_E..G`, `G01`, `G03..G07`, `GOOD_END`, `BAD_END`, `GY_MOV`, `OPI_J00`; no scene is on both).  When
/// a disc 1 folder is opened and `SH2_US_DISC2_DIR` names the disc 2 folder (or the other way round with `SH2_US_DISC_DIR`), the other
/// disc is attached: [`Disc::read`] / [`Disc::exists`] fall back to it for paths the opened disc does not hold, so every loader finds the
/// disc 2 cut scenes without a disc swap.  [`Disc::disc_of`] tells which disc holds a path (the console's `DiskChange` prompt).
pub struct Disc {
    root: PathBuf,
    src: DiscSource,
    info: PkfInfo,
    /// the other disc of a two-disc set (see above)
    other: Option<Box<Disc>>,
    /// 1 / 2 for the US retail discs (by the boot ELF in the folder), 0 otherwise
    number: u8,
}

/// Disc number of a folder or image by its boot ELF: `SLUS_210.41` = US disc 1, `SLUS_210.44` = US disc 2.
pub fn disc_number(root: &Path) -> u8 {
    DiscSource::open(root).map(|s| source_disc_number(&s)).unwrap_or(0)
}

fn source_disc_number(src: &DiscSource) -> u8 {
    if src.exists("SLUS_210.41") {
        1
    } else if src.exists("SLUS_210.44") {
        2
    } else {
        0
    }
}

impl Disc {
    fn open_single(root: &Path) -> Result<Self, FileIoError> {
        let root = root.to_path_buf();
        let io = |source| FileIoError::Io { path: root.join("PKFINFO.TBL"), source };
        let src = DiscSource::open(&root).map_err(io)?;
        let bytes = src.read("PKFINFO.TBL").map_err(io)?;
        let number = source_disc_number(&src);
        Ok(Disc { info: PkfInfo::parse(&bytes)?, root, src, other: None, number })
    }

    pub fn open(root: impl AsRef<Path>) -> Result<Self, FileIoError> {
        let mut d = Self::open_single(root.as_ref())?;
        let other_var = match d.number {
            1 => Some("SH2_US_DISC2_DIR"),
            2 => Some("SH2_US_DISC_DIR"),
            _ => None,
        };
        if let Some(dir) = other_var.and_then(std::env::var_os) {
            if let Ok(o) = Self::open_single(Path::new(&dir)) {
                if o.number != 0 && o.number != d.number {
                    d.other = Some(Box::new(o));
                }
            }
        }
        Ok(d)
    }

    /// Open without attaching the other disc of a set.
    pub fn open_one(root: impl AsRef<Path>) -> Result<Self, FileIoError> {
        Self::open_single(root.as_ref())
    }

    /// 1 / 2 = US retail disc 1 / 2, 0 = not a US retail disc.
    pub fn number(&self) -> u8 {
        self.number
    }

    /// The attached other disc of a two-disc set.
    pub fn other(&self) -> Option<&Disc> {
        self.other.as_deref()
    }

    /// Does this disc (or the attached other disc) hold `path`?
    pub fn exists(&self, path: &str) -> bool {
        self.info.search_file(path).is_some() || self.other.as_ref().map(|o| o.info.search_file(path).is_some()).unwrap_or(false)
    }

    /// Which disc holds `path`: this disc's number when it has it, else the attached disc's number; `None` when neither has it.
    pub fn disc_of(&self, path: &str) -> Option<u8> {
        if self.info.search_file(path).is_some() {
            Some(self.number)
        } else {
            self.other.as_ref().filter(|o| o.info.search_file(path).is_some()).map(|o| o.number)
        }
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
    /// The folder or `.iso` image this disc was opened from.
    pub fn root(&self) -> &Path {
        &self.root
    }
    /// Raw access to the disc's own files (`FIELD.BIN`, the boot ELF, `*.PKB`).
    pub fn source(&self) -> &DiscSource {
        &self.src
    }
    /// Convenience for loaders that only care whether a file exists: `read` as an `Option`.
    pub fn read_opt(&self, path: &str) -> Option<Vec<u8>> {
        self.read(path).ok()
    }

    fn container_name(loc: &FileLoc) -> String {
        if loc.in_archive {
            format!("{}.PKB", loc.container)
        } else {
            loc.container.clone()
        }
    }

    /// `FileIOLib::open` + `read` + `close` in one go (what `BlockRead` / `DvdromOrder::ReadOrder` end up doing).
    pub fn read(&self, path: &str) -> Result<Vec<u8>, FileIoError> {
        let Some(loc) = self.info.search_file(path) else {
            return match &self.other {
                Some(o) => o.read(path),
                None => Err(FileIoError::NotFound(path.to_string())),
            };
        };
        let name = Self::container_name(&loc);
        let io = |source| FileIoError::Io { path: self.root.join(&name), source };
        let buf = self.src.read_range(&name, loc.byte_offset, loc.size as u64).map_err(io)?;
        if buf.len() != loc.size as usize {
            return Err(io(std::io::Error::new(std::io::ErrorKind::UnexpectedEof, format!("{path}: container ends early"))));
        }
        Ok(buf)
    }

    /// Like [`Disc::listing`] over the attached other disc too (its paths that this disc does not hold).
    pub fn listing_all(&self) -> BTreeMap<String, Vec<(String, FileLoc)>> {
        let mut m = self.listing();
        if let Some(o) = &self.other {
            o.info.walk(|p, l| {
                if self.info.search_file(p).is_none() {
                    m.entry(format!("{}@disc{}", l.container, o.number)).or_default().push((p.to_string(), l.clone()));
                }
            });
        }
        m
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

    /// Images and folders are told apart by their boot ELF (`SH2_ISO_TEST` / `SH2_ISO_TEST_DIR` as below).
    #[test]
    fn disc_env_var_by_boot_elf() {
        let (Some(iso), Some(dir)) = (std::env::var_os("SH2_ISO_TEST"), std::env::var_os("SH2_ISO_TEST_DIR")) else { return };
        assert!(disc_env_var(&iso).is_some());
        assert_eq!(disc_env_var(&iso), disc_env_var(&dir));
        assert_eq!(disc_env_var(std::env::temp_dir()), None);
    }

    /// `SH2_ISO_TEST=<image>` + `SH2_ISO_TEST_DIR=<the same disc extracted>`: every table file and every root file reads the same from
    /// the image as from the folder, and the image's disc number matches.
    #[test]
    fn iso_matches_folder() {
        let (Some(iso), Some(dir)) = (std::env::var_os("SH2_ISO_TEST"), std::env::var_os("SH2_ISO_TEST_DIR")) else { return };
        let (a, b) = (Disc::open_one(&iso).unwrap(), Disc::open_one(&dir).unwrap());
        assert!(matches!(a.source(), DiscSource::Iso(_)));
        assert_eq!(a.number(), b.number());
        let mut n = 0;
        a.info().walk(|p, _| {
            assert_eq!(a.read(p).unwrap(), b.read(p).unwrap(), "{p}");
            n += 1;
        });
        assert!(n > 1000, "{n} files");
        for name in ["FIELD.BIN", "BATTLE.BIN", "SYSTEM.CNF"] {
            assert_eq!(read_disc_file(&iso, name).unwrap(), read_disc_file(&dir, name).unwrap(), "{name}");
        }
        assert!(disc_file_exists(&iso, "pkfinfo.tbl;1") && !disc_file_exists(&iso, "NOPE.BIN"));
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
                    let sz = disc.source().len(&format!("{cont}.PKB")).unwrap();
                    let end = files.iter().map(|(_, l)| l.byte_offset + l.size as u64).max().unwrap();
                    assert_eq!(sz, end, "{cont}");
                }
            }
        }
        assert_eq!(n, 1734);
    }
}

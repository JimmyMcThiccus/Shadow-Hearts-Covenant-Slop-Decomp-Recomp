//! Reader **and writer** for PS2 memory-card images (`Mcd001.ps2` of PCSX2 / ARMSX2, 8 MB with or without the 16 byte ECC spare per page).
//!
//! The card is a small FAT-like file system (see `libmc` and the PCSX2 `MemoryCardFile` sources):
//!
//! ```text
//! superblock (page 0, 512 B):  "Sony PS2 Memory Card Format 1.2.0.0", u16 page_len (512), u16 pages_per_cluster (2),
//!                              u16 pages_per_block (16), u16 0xff00, u32 clusters_per_card (8192),
//!                              u32 alloc_offset (41), u32 alloc_end (8135), u32 rootdir_cluster (0, relative), ...,
//!                              +0x50 u32 ifc_list[32]: absolute cluster numbers of the indirect FAT clusters
//! indirect FAT cluster:        u32[256] absolute cluster numbers of FAT clusters
//! FAT cluster:                 u32[256] entries, index = cluster relative to alloc_offset;
//!                              bit 31 = valid, low 31 bits = next cluster, 0x7fffffff = end of chain
//! directory entry (512 B):     u16 mode (0x8000 exists, 0x20 directory, 0x10 file, 0x4 / 0x2 / 0x1 exec / write / read),
//!                              u16, u32 length (file: bytes, directory: entry count), 8 B created, u32 cluster (relative),
//!                              u32 dir_entry, 8 B modified, u32 attr, 28 B, char name[32]
//! ```
//!
//! The retail save lives in the directory `BASLUS-21041-SH2` (system file of the same name, `SH2-000` .. `SH2-014`, `icon.sys`,
//! `SH2.ICO`); the port reads it through [`MemCardStorage`], a [`SaveStorage`] that serves those files.
//!
//! ## Writing (checked against the real emulator card `Mcd001.ps2`, which was written by the retail game through PCSX2 / ARMSX2)
//!
//! * **ECC**: every programmed page of a 528 byte image carries 16 spare bytes = 4 x 3 ECC bytes (one triple per 128 byte chunk) + 4 zero bytes; erased pages are
//!   `0xff` all over.  Per chunk: `column = 0x77 ^ XOR(mask[b])` with `mask[b] = XOR over the set bits j of b of ((j << 4) | (7 - j))`, `line0 = 0x7f ^ XOR(!i)` and
//!   `line1 = 0x7f ^ XOR(i)` over the byte indices `i` whose value has odd parity (all stored `& 0x7f`).  [`MemCard::ecc_errors`] re-computes it for a whole image:
//!   3199 of the 3200 programmed pages of the real card agree (page 1, the second half of the superblock, is the one the format tool leaves different).
//! * **FAT**: entry = `0x80000000 | next` for a used cluster, `0xffffffff` ends a chain, a *free* entry has bit 31 clear (`0x7fffffff` on a real card).
//! * **directories**: 512 byte entries, two per 1 KB cluster; the parent's entry of a folder and the folder's `.` entry... the folder entry's `length` is the
//!   entry count (including `.` / `..`), `.` of the root also holds the root's count, `.` / `..` of a sub folder have length 0, `.` has `dirent` = the folder's index
//!   in the parent.  Times are `{0, sec, min, hour, day, month, year u16}` in plain binary.  Modes: folder `0x8427`, file `0x8497`.
//! * [`MemCard::write_file`] frees the old chain of an existing file first (so a same-size overwrite always fits), then allocates first-fit, links the chain, writes the
//!   data pages with ECC, patches the directory entry (growing the directory chain by one cluster when the entry count is odd) and the parent's count / modified time.

use crate::storage::{DeviceStatus, SaveStorage, StorageError};
use std::path::{Path, PathBuf};

const MAGIC: &[u8] = b"Sony PS2 Memory Card Format ";
const ENTRY_SIZE: usize = 512;

#[derive(Debug, thiserror::Error)]
pub enum McError {
    #[error("io: {0}")]
    Io(String),
    #[error("not a PS2 memory card image")]
    BadMagic,
    #[error("unformatted / corrupt card: {0}")]
    Corrupt(&'static str),
    #[error("not enough free clusters on the card")]
    Full,
    #[error("no such folder / file")]
    NotFound,
    #[error("name too long (32 characters at most)")]
    BadName,
}

/// One directory entry.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct McEntry {
    pub name: String,
    pub mode: u16,
    /// file: size in bytes; directory: number of entries (including `.` and `..`)
    pub length: u32,
    /// first cluster relative to `alloc_offset`
    pub cluster: u32,
}

impl McEntry {
    pub fn exists(&self) -> bool {
        self.mode & 0x8000 != 0
    }
    pub fn is_dir(&self) -> bool {
        self.mode & 0x20 != 0
    }
    pub fn is_file(&self) -> bool {
        self.mode & 0x10 != 0
    }
}

pub struct MemCard {
    data: Vec<u8>,
    /// bytes per page in the image (512, or 528 with ECC)
    stride: usize,
    page_len: usize,
    pages_per_cluster: usize,
    alloc_offset: u32,
    /// number of allocatable clusters (`alloc_end`, superblock +0x38): FAT entries at and above this index are not data clusters
    alloc_end: u32,
    rootdir: u32,
    fat_clusters: Vec<u32>,
}

fn u16_at(b: &[u8], o: usize) -> u16 {
    u16::from_le_bytes([b[o], b[o + 1]])
}
fn u32_at(b: &[u8], o: usize) -> u32 {
    u32::from_le_bytes([b[o], b[o + 1], b[o + 2], b[o + 3]])
}

impl MemCard {
    pub fn open(path: impl AsRef<Path>) -> Result<Self, McError> {
        let d = std::fs::read(path.as_ref()).map_err(|e| McError::Io(e.to_string()))?;
        Self::from_bytes(d)
    }

    pub fn from_bytes(data: Vec<u8>) -> Result<Self, McError> {
        if data.len() < 2048 || !data.starts_with(MAGIC) {
            return Err(McError::BadMagic);
        }
        let page_len = u16_at(&data, 0x28) as usize;
        let pages_per_cluster = u16_at(&data, 0x2a) as usize;
        if page_len != 512 || pages_per_cluster == 0 || pages_per_cluster > 8 {
            return Err(McError::Corrupt("geometry"));
        }
        let clusters_per_card = u32_at(&data, 0x30) as usize;
        // with ECC every 512 byte page is followed by 16 spare bytes
        let stride = if data.len() >= clusters_per_card * pages_per_cluster * 528 { 528 } else { 512 };
        let mut card = MemCard {
            alloc_offset: u32_at(&data, 0x34),
            alloc_end: u32_at(&data, 0x38),
            rootdir: u32_at(&data, 0x3c),
            data,
            stride,
            page_len,
            pages_per_cluster,
            fat_clusters: Vec::new(),
        };
        let sb = card.cluster(0).ok_or(McError::Corrupt("superblock"))?;
        let ifc: Vec<u32> = (0..32).map(|i| u32_at(&sb, 0x50 + i * 4)).collect();
        let per = card.page_len * card.pages_per_cluster / 4;
        for ic in ifc {
            if ic == 0 || ic == u32::MAX {
                continue;
            }
            let Some(c) = card.cluster(ic) else { continue };
            for i in 0..per {
                let e = u32_at(&c, i * 4);
                if e != u32::MAX && e != 0 {
                    card.fat_clusters.push(e);
                }
            }
        }
        if card.fat_clusters.is_empty() {
            return Err(McError::Corrupt("no FAT"));
        }
        Ok(card)
    }

    /// Absolute cluster `n` (page_len * pages_per_cluster bytes, ECC stripped).
    fn cluster(&self, n: u32) -> Option<Vec<u8>> {
        let mut out = Vec::with_capacity(self.page_len * self.pages_per_cluster);
        for p in 0..self.pages_per_cluster {
            let page = n as usize * self.pages_per_cluster + p;
            let o = page * self.stride;
            out.extend_from_slice(self.data.get(o..o + self.page_len)?);
        }
        Some(out)
    }

    fn fat(&self, idx: u32) -> Option<u32> {
        let per = (self.page_len * self.pages_per_cluster / 4) as u32;
        let fc = *self.fat_clusters.get((idx / per) as usize)?;
        let c = self.cluster(fc)?;
        Some(u32_at(&c, (idx % per) as usize * 4))
    }

    /// Cluster chain starting at the relative cluster `start`.
    fn chain(&self, start: u32) -> Vec<u32> {
        let mut out = Vec::new();
        let mut c = start;
        while out.len() < 1 << 16 {
            out.push(c);
            let Some(e) = self.fat(c) else { break };
            if e & 0x8000_0000 == 0 {
                break;
            }
            let n = e & 0x7fff_ffff;
            if n == 0x7fff_ffff {
                break;
            }
            c = n;
        }
        out
    }

    fn read_chain(&self, start: u32, limit: Option<usize>) -> Vec<u8> {
        let mut out = Vec::new();
        for c in self.chain(start) {
            if let Some(d) = self.cluster(self.alloc_offset + c) {
                out.extend_from_slice(&d);
            }
            if limit.map(|l| out.len() >= l).unwrap_or(false) {
                break;
            }
        }
        if let Some(l) = limit {
            out.truncate(l);
        }
        out
    }

    fn entries(&self, cluster: u32, count: u32) -> Vec<McEntry> {
        let d = self.read_chain(cluster, Some(count as usize * ENTRY_SIZE));
        (0..count as usize)
            .filter_map(|i| {
                let e = d.get(i * ENTRY_SIZE..(i + 1) * ENTRY_SIZE)?;
                let name_end = e[0x40..0x60].iter().position(|&b| b == 0).unwrap_or(32);
                Some(McEntry {
                    name: String::from_utf8_lossy(&e[0x40..0x40 + name_end]).into_owned(),
                    mode: u16_at(e, 0),
                    length: u32_at(e, 4),
                    cluster: u32_at(e, 0x10),
                })
            })
            .collect()
    }

    /// Entries of the root directory (`.` / `..` omitted).
    pub fn root(&self) -> Vec<McEntry> {
        let first = self.entries(self.rootdir, 1);
        let count = first.first().map(|e| e.length).unwrap_or(0).min(4096);
        self.list_entries(self.rootdir, count)
    }

    fn list_entries(&self, cluster: u32, count: u32) -> Vec<McEntry> {
        self.entries(cluster, count).into_iter().filter(|e| e.exists() && e.name != "." && e.name != "..").collect()
    }

    /// Entries of the directory `name` in the root (`.` / `..` omitted); `None` when there is no such directory.
    pub fn list_dir(&self, name: &str) -> Option<Vec<McEntry>> {
        let d = self.root().into_iter().find(|e| e.is_dir() && e.name == name)?;
        Some(self.list_entries(d.cluster, d.length.min(4096)))
    }

    /// Read the file `file` of directory `dir`.
    pub fn read_file(&self, dir: &str, file: &str) -> Option<Vec<u8>> {
        let e = self.list_dir(dir)?.into_iter().find(|e| e.is_file() && e.name == file)?;
        Some(self.read_chain(e.cluster, Some(e.length as usize)))
    }

    pub fn has_dir(&self, name: &str) -> bool {
        self.root().iter().any(|e| e.is_dir() && e.name == name)
    }
}

// ----------------------------------------------------------------------------------------------------------------
// ECC, time stamps
// ----------------------------------------------------------------------------------------------------------------

/// The 3 ECC bytes of one 128 byte chunk (see the module docs).
pub fn ecc_chunk(chunk: &[u8]) -> [u8; 3] {
    let (mut col, mut l0, mut l1) = (0x77u8, 0x7fu8, 0x7fu8);
    for (i, &b) in chunk.iter().take(128).enumerate() {
        let mut m = 0u8;
        for j in 0..8 {
            if (b >> j) & 1 != 0 {
                m ^= ((j as u8) << 4) | (7 - j as u8);
            }
        }
        col ^= m;
        if b.count_ones() & 1 != 0 {
            l0 ^= !(i as u8);
            l1 ^= i as u8;
        }
    }
    [col, l0 & 0x7f, l1 & 0x7f]
}

/// The 16 spare bytes of a programmed 512 byte page: 4 ECC triples + 4 zero bytes.
pub fn page_spare(page: &[u8]) -> [u8; 16] {
    let mut s = [0u8; 16];
    for c in 0..4 {
        s[c * 3..c * 3 + 3].copy_from_slice(&ecc_chunk(&page[c * 128..(c + 1) * 128]));
    }
    s
}

/// A card time stamp `{0, sec, min, hour, day, month, year (u16 LE)}` (plain binary) for the Unix time `secs` (UTC).
pub fn stamp_from_unix(secs: u64) -> [u8; 8] {
    let days = (secs / 86400) as i64;
    let rem = secs % 86400;
    // civil from days (Howard Hinnant)
    let z = days + 719_468;
    let era = z.div_euclid(146_097);
    let doe = z.rem_euclid(146_097);
    let yoe = (doe - doe / 1460 + doe / 36_524 - doe / 146_096) / 365;
    let y = yoe + era * 400;
    let doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    let mp = (5 * doy + 2) / 153;
    let d = doy - (153 * mp + 2) / 5 + 1;
    let m = if mp < 10 { mp + 3 } else { mp - 9 };
    let y = if m <= 2 { y + 1 } else { y };
    let yb = (y as u16).to_le_bytes();
    [0, (rem % 60) as u8, (rem / 60 % 60) as u8, (rem / 3600) as u8, d as u8, m as u8, yb[0], yb[1]]
}

/// The current time as a card time stamp.
pub fn now_stamp() -> [u8; 8] {
    stamp_from_unix(std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH).map(|d| d.as_secs()).unwrap_or(0))
}

const MODE_DIR: u16 = 0x8427;
const MODE_FILE: u16 = 0x8497;
const FAT_END: u32 = 0xffff_ffff;
const FAT_FREE: u32 = 0x7fff_ffff;

fn dir_entry(name: &str, mode: u16, len: u32, created: [u8; 8], cluster: u32, dirent: u32, modified: [u8; 8]) -> Vec<u8> {
    let mut e = vec![0u8; ENTRY_SIZE];
    e[0..2].copy_from_slice(&mode.to_le_bytes());
    e[4..8].copy_from_slice(&len.to_le_bytes());
    e[8..16].copy_from_slice(&created);
    e[0x10..0x14].copy_from_slice(&cluster.to_le_bytes());
    e[0x14..0x18].copy_from_slice(&dirent.to_le_bytes());
    e[0x18..0x20].copy_from_slice(&modified);
    e[0x40..0x40 + name.len()].copy_from_slice(name.as_bytes());
    e
}

impl MemCard {
    /// A freshly formatted 8 MB card (`ecc`: 528 byte pages): superblock, one indirect FAT cluster, 32 FAT clusters, an empty root directory.
    /// Layout of the real card: 8192 clusters of 2 pages, FAT at clusters 9..40, data from cluster 41 (`alloc_offset`), 8135 allocatable clusters.
    pub fn format_new(ecc: bool) -> MemCard {
        const NCL: usize = 8192;
        const PPC: usize = 2;
        let stride = if ecc { 528 } else { 512 };
        let mut data = vec![0xffu8; NCL * PPC * stride];
        let mut card = MemCard { data: Vec::new(), stride, page_len: 512, pages_per_cluster: PPC, alloc_offset: 41, alloc_end: 8135, rootdir: 0, fat_clusters: (9..41).collect() };
        // superblock (cluster 0)
        let mut sb = vec![0u8; 1024];
        sb[..35].copy_from_slice(b"Sony PS2 Memory Card Format 1.2.0.0");
        let w32 = |b: &mut [u8], o: usize, v: u32| b[o..o + 4].copy_from_slice(&v.to_le_bytes());
        sb[0x28..0x2a].copy_from_slice(&512u16.to_le_bytes());
        sb[0x2a..0x2c].copy_from_slice(&2u16.to_le_bytes());
        sb[0x2c..0x2e].copy_from_slice(&16u16.to_le_bytes());
        sb[0x2e..0x30].copy_from_slice(&0xff00u16.to_le_bytes());
        w32(&mut sb, 0x30, NCL as u32);
        w32(&mut sb, 0x34, 41);
        w32(&mut sb, 0x38, 8135);
        w32(&mut sb, 0x3c, 0);
        w32(&mut sb, 0x40, 0x3ff);
        w32(&mut sb, 0x44, 0x3fe);
        w32(&mut sb, 0x50, 8); // ifc_list[0] = cluster 8
        for i in 1..32 {
            w32(&mut sb, 0x50 + i * 4, 0);
        }
        for b in &mut sb[0xd0..0x150] {
            *b = 0xff; // bad block list: none
        }
        sb[0x150] = 2; // card type: PS2
        sb[0x151] = 0x2b; // card flags
        w32(&mut sb, 0x154, 0x400);
        w32(&mut sb, 0x158, 0x100);
        w32(&mut sb, 0x15c, 8);
        w32(&mut sb, 0x160, 0xffff_ffff);
        w32(&mut sb, 0x170, 0x1f41);
        w32(&mut sb, 0x17c, 0xffff_ffff);
        w32(&mut sb, 0x18c, 0xffff_ffff);
        card.data = std::mem::take(&mut data);
        card.put_cluster(0, &sb);
        // indirect FAT cluster 8: the 32 FAT clusters 9..40, the rest 0xffffffff
        let mut ifc = vec![0xffu8; 1024];
        for i in 0..32u32 {
            w32(&mut ifc, i as usize * 4, 9 + i);
        }
        card.put_cluster(8, &ifc);
        // FAT: everything free, entries at / above alloc_end = 0xffffffff, the root directory (cluster 0) = one cluster
        for f in 0..32usize {
            let mut c = vec![0u8; 1024];
            for i in 0..256usize {
                let idx = f * 256 + i;
                let v = if idx >= 8135 { FAT_END } else if idx == 0 { FAT_END } else { FAT_FREE };
                w32(&mut c, i * 4, v);
            }
            card.put_cluster(9 + f as u32, &c);
        }
        let st = now_stamp();
        let mut root = dir_entry(".", MODE_DIR, 2, st, 0, 0, st);
        root.extend(dir_entry("..", 0xa426, 0, st, 0, 0, st));
        card.put_cluster(41, &root);
        card
    }

    /// The whole image (what is written to disk).
    pub fn to_bytes(&self) -> &[u8] {
        &self.data
    }

    /// Write the image to `path` atomically (temp file in the same directory + rename).
    pub fn save(&self, path: &Path) -> Result<(), McError> {
        if let Some(dir) = path.parent() {
            std::fs::create_dir_all(dir).map_err(|e| McError::Io(e.to_string()))?;
        }
        let mut tmp = path.as_os_str().to_owned();
        tmp.push(".tmp");
        let tmp = PathBuf::from(tmp);
        std::fs::write(&tmp, &self.data).map_err(|e| McError::Io(e.to_string()))?;
        std::fs::rename(&tmp, path).map_err(|e| McError::Io(e.to_string()))
    }

    pub fn has_ecc(&self) -> bool {
        self.stride == 528
    }

    fn cluster_bytes(&self) -> usize {
        self.page_len * self.pages_per_cluster
    }

    /// Program absolute cluster `n` (`data` is zero padded to the cluster size); spare bytes get their ECC on an ECC image.
    fn put_cluster(&mut self, n: u32, data: &[u8]) {
        for p in 0..self.pages_per_cluster {
            let page = n as usize * self.pages_per_cluster + p;
            let o = page * self.stride;
            let mut buf = vec![0u8; self.page_len];
            let src = &data[(p * self.page_len).min(data.len())..((p + 1) * self.page_len).min(data.len())];
            buf[..src.len()].copy_from_slice(src);
            self.data[o..o + self.page_len].copy_from_slice(&buf);
            if self.stride == 528 {
                let sp = page_spare(&buf);
                self.data[o + self.page_len..o + self.stride].copy_from_slice(&sp);
            }
        }
    }

    fn fat_set(&mut self, idx: u32, val: u32) {
        let per = (self.cluster_bytes() / 4) as u32;
        let Some(&fc) = self.fat_clusters.get((idx / per) as usize) else { return };
        let Some(mut c) = self.cluster(fc) else { return };
        let o = (idx % per) as usize * 4;
        c[o..o + 4].copy_from_slice(&val.to_le_bytes());
        self.put_cluster(fc, &c);
    }

    fn fat_free(&self, idx: u32) -> bool {
        self.fat(idx).map(|e| e & 0x8000_0000 == 0).unwrap_or(false)
    }

    /// Number of free data clusters.
    pub fn free_clusters(&self) -> u32 {
        (0..self.alloc_end).filter(|&i| self.fat_free(i)).count() as u32
    }

    /// Free space in kilobytes (1 KB clusters).
    pub fn free_kb(&self) -> u32 {
        self.free_clusters() * (self.cluster_bytes() as u32) / 1024
    }

    fn alloc(&self, n: usize) -> Result<Vec<u32>, McError> {
        let mut v = Vec::with_capacity(n);
        let mut i = 0;
        while v.len() < n && i < self.alloc_end {
            if self.fat_free(i) {
                v.push(i);
            }
            i += 1;
        }
        if v.len() < n {
            Err(McError::Full)
        } else {
            Ok(v)
        }
    }

    /// Link `clusters` into one chain ending in `0xffffffff`.
    fn link(&mut self, clusters: &[u32]) {
        for (k, &c) in clusters.iter().enumerate() {
            let v = match clusters.get(k + 1) {
                Some(&n) => 0x8000_0000 | n,
                None => FAT_END,
            };
            self.fat_set(c, v);
        }
    }

    fn free_chain(&mut self, start: u32) {
        for c in self.chain(start) {
            self.fat_set(c, FAT_FREE);
        }
    }

    /// Patch `bytes` into the directory whose chain starts at `cluster`, at byte offset `off`.
    fn patch_dir(&mut self, cluster: u32, off: usize, bytes: &[u8]) {
        let cb = self.cluster_bytes();
        let chain = self.chain(cluster);
        let mut written = 0;
        while written < bytes.len() {
            let pos = off + written;
            let Some(&c) = chain.get(pos / cb) else { return };
            let Some(mut data) = self.cluster(self.alloc_offset + c) else { return };
            let inner = pos % cb;
            let n = (cb - inner).min(bytes.len() - written);
            data[inner..inner + n].copy_from_slice(&bytes[written..written + n]);
            let abs = self.alloc_offset + c;
            self.put_cluster(abs, &data);
            written += n;
        }
    }

    /// Entry `idx` of the directory at `cluster`.
    fn raw_entry(&self, cluster: u32, idx: usize) -> Vec<u8> {
        let d = self.read_chain(cluster, Some((idx + 1) * ENTRY_SIZE));
        d.get(idx * ENTRY_SIZE..(idx + 1) * ENTRY_SIZE).map(|e| e.to_vec()).unwrap_or_default()
    }

    /// Make room for entry number `count` in the directory at `cluster` (grow the chain by one cluster when the last one is full).
    fn ensure_dir_room(&mut self, cluster: u32, count: usize) -> Result<(), McError> {
        let per = self.cluster_bytes() / ENTRY_SIZE;
        let chain = self.chain(cluster);
        if count < chain.len() * per {
            return Ok(());
        }
        let new = self.alloc(1)?[0];
        self.link(&[*chain.last().unwrap(), new]);
        // `link` closed the chain at `new`; the old last cluster now points to it
        let abs = self.alloc_offset + new;
        self.put_cluster(abs, &[]);
        Ok(())
    }

    fn root_count(&self) -> usize {
        self.entries(self.rootdir, 1).first().map(|e| e.length as usize).unwrap_or(0)
    }

    /// Index and entry of folder `name` in the root.
    fn find_root_dir(&self, name: &str) -> Option<(usize, McEntry)> {
        let n = self.root_count().min(4096);
        self.entries(self.rootdir, n as u32).into_iter().enumerate().find(|(_, e)| e.exists() && e.is_dir() && e.name == name)
    }

    /// Create folder `name` in the root (no-op when it exists).
    pub fn mkdir(&mut self, name: &str, stamp: [u8; 8]) -> Result<(), McError> {
        if name.len() > 32 || name.is_empty() {
            return Err(McError::BadName);
        }
        if self.find_root_dir(name).is_some() {
            return Ok(());
        }
        let count = self.root_count();
        self.ensure_dir_room(self.rootdir, count)?;
        let cl = self.alloc(1)?[0];
        self.link(&[cl]);
        let mut d = dir_entry(".", MODE_DIR, 0, stamp, 0, count as u32, stamp);
        d.extend(dir_entry("..", MODE_DIR, 0, stamp, 0, 0, stamp));
        let abs = self.alloc_offset + cl;
        self.put_cluster(abs, &d);
        self.patch_dir(self.rootdir, count * ENTRY_SIZE, &dir_entry(name, MODE_DIR, 2, stamp, cl, 0, stamp));
        // the root's `.` entry counts its entries
        let mut dot = self.raw_entry(self.rootdir, 0);
        dot[4..8].copy_from_slice(&(count as u32 + 1).to_le_bytes());
        dot[0x18..0x20].copy_from_slice(&stamp);
        self.patch_dir(self.rootdir, 0, &dot);
        Ok(())
    }

    /// Write (create or replace) `file` in folder `dir`.  All-or-nothing with respect to free space: the file's old clusters count as free.
    pub fn write_file(&mut self, dir: &str, file: &str, data: &[u8], stamp: [u8; 8]) -> Result<(), McError> {
        if file.len() > 32 || file.is_empty() {
            return Err(McError::BadName);
        }
        let (di, d) = self.find_root_dir(dir).ok_or(McError::NotFound)?;
        let cb = self.cluster_bytes();
        let count = d.length as usize;
        let ents = self.entries(d.cluster, count as u32);
        let existing = ents.iter().position(|e| e.exists() && e.is_file() && e.name == file);
        let need = data.len().div_ceil(cb);
        let old_chain = existing.map(|i| if ents[i].length > 0 { self.chain(ents[i].cluster) } else { Vec::new() }).unwrap_or_default();
        let dir_room_needed = existing.is_none() && count >= self.chain(d.cluster).len() * (cb / ENTRY_SIZE);
        if self.free_clusters() as usize + old_chain.len() < need + usize::from(dir_room_needed) {
            return Err(McError::Full);
        }
        for &c in &old_chain {
            self.fat_set(c, FAT_FREE);
        }
        let idx = match existing {
            Some(i) => i,
            None => {
                self.ensure_dir_room(d.cluster, count)?;
                count
            }
        };
        let clusters = self.alloc(need)?;
        self.link(&clusters);
        for (k, &c) in clusters.iter().enumerate() {
            let abs = self.alloc_offset + c;
            self.put_cluster(abs, &data[k * cb..((k + 1) * cb).min(data.len())]);
        }
        let created = existing.map(|i| {
            let e = self.raw_entry(d.cluster, i);
            let mut c = [0u8; 8];
            c.copy_from_slice(&e[8..16]);
            c
        });
        let first = clusters.first().copied().unwrap_or(0);
        self.patch_dir(d.cluster, idx * ENTRY_SIZE, &dir_entry(file, MODE_FILE, data.len() as u32, created.unwrap_or(stamp), first, 0, stamp));
        if existing.is_none() {
            // the folder entry in the root: entry count + modified time
            let mut fe = self.raw_entry(self.rootdir, di);
            fe[4..8].copy_from_slice(&(count as u32 + 1).to_le_bytes());
            fe[0x18..0x20].copy_from_slice(&stamp);
            self.patch_dir(self.rootdir, di * ENTRY_SIZE, &fe);
        } else {
            let mut fe = self.raw_entry(self.rootdir, di);
            fe[0x18..0x20].copy_from_slice(&stamp);
            self.patch_dir(self.rootdir, di * ENTRY_SIZE, &fe);
        }
        Ok(())
    }

    /// Delete `file` of folder `dir`: free its clusters and clear the entry's `exists` bit (the entry slot stays, like `sceMcDelete` does).
    pub fn delete_file(&mut self, dir: &str, file: &str, stamp: [u8; 8]) -> Result<(), McError> {
        let (di, d) = self.find_root_dir(dir).ok_or(McError::NotFound)?;
        let ents = self.entries(d.cluster, d.length);
        let i = ents.iter().position(|e| e.exists() && e.is_file() && e.name == file).ok_or(McError::NotFound)?;
        if ents[i].length > 0 {
            self.free_chain(ents[i].cluster);
        }
        let mut e = self.raw_entry(d.cluster, i);
        let mode = u16::from_le_bytes([e[0], e[1]]) & !0x8000;
        e[0..2].copy_from_slice(&mode.to_le_bytes());
        self.patch_dir(d.cluster, i * ENTRY_SIZE, &e);
        let mut fe = self.raw_entry(self.rootdir, di);
        fe[0x18..0x20].copy_from_slice(&stamp);
        self.patch_dir(self.rootdir, di * ENTRY_SIZE, &fe);
        Ok(())
    }

    /// Number of programmed pages (spare not all `0xff`) whose stored ECC differs from the recomputed one (`(checked, bad)`); only ECC images have spares.
    pub fn ecc_errors(&self) -> (usize, usize) {
        if self.stride != 528 {
            return (0, 0);
        }
        let (mut checked, mut bad) = (0, 0);
        for page in 0..self.data.len() / 528 {
            let o = page * 528;
            let spare = &self.data[o + 512..o + 528];
            if spare.iter().all(|&b| b == 0xff) {
                continue;
            }
            checked += 1;
            if spare[..12] != page_spare(&self.data[o..o + 512])[..12] {
                bad += 1;
            }
        }
        (checked, bad)
    }
}

/// Where emulators keep the first card (`SH2_MEMCARD` overrides): ARMSX2 / PCSX2 on macOS, PCSX2 on Linux / Windows.
pub fn default_card_paths() -> Vec<PathBuf> {
    if let Some(p) = std::env::var_os("SH2_MEMCARD") {
        return vec![PathBuf::from(p)];
    }
    let mut v = Vec::new();
    if let Some(home) = std::env::var_os("HOME").map(PathBuf::from) {
        v.push(home.join("Library/Application Support/ARMSX2/memcards/Mcd001.ps2"));
        v.push(home.join("Library/Application Support/PCSX2/memcards/Mcd001.ps2"));
        v.push(home.join(".config/PCSX2/memcards/Mcd001.ps2"));
    }
    if let Some(d) = std::env::var_os("USERPROFILE").map(PathBuf::from) {
        v.push(d.join("Documents/PCSX2/memcards/Mcd001.ps2"));
    }
    v
}

/// The `icon.sys` the retail game writes (`SaveDevice::CreateIcon`; title "Ｓｈａｄｏｗ Ｈｅａｒｔｓ ＩＩ", icon file `SH2.ICO`), 964 bytes.
pub const RETAIL_ICON_SYS: &[u8] = include_bytes!("data/us_icon.sys");

/// The `SH2.ICO` of the first chapter from the disc (`COMMON/SH2_000.ICO`: a 0x80 byte header `{u32 0x80, u32 size}` + the icon model), if the disc is available.
pub fn retail_icon_from_disc() -> Option<Vec<u8>> {
    let dir = std::env::var_os("SH2_US_DISC_DIR").or_else(|| if sh2_core::boot::is_retail() { std::env::var_os("SH2_DISC_DIR") } else { None })?;
    let disc = sh2_core::fileio::Disc::open(dir).ok()?;
    let raw = disc.read_opt("COMMON/SH2_000.ICO").or_else(|| disc.read_opt("COMMON/COMMON/SH2_000.ICO"))?;
    let hd = u32::from_le_bytes(raw.get(0..4)?.try_into().ok()?) as usize;
    let sz = u32::from_le_bytes(raw.get(4..8)?.try_into().ok()?) as usize;
    raw.get(hd..hd + sz).map(|b| b.to_vec())
}

/// [`SaveStorage`] over a memory-card image: serves the files of one save folder.  Read-only unless the card was opened for writing
/// ([`MemCardStorage::open_rw`] / [`MemCardStorage::open_or_new`]); every write / delete re-programs the card (FAT, directory, ECC, see [`MemCard`]) and
/// rewrites the image atomically.
pub struct MemCardStorage {
    card: MemCard,
    folder: String,
    pub path: PathBuf,
    writable: bool,
    /// the image exists on disk (a brand new port card is only created by its first write)
    on_disk: bool,
}

impl MemCardStorage {
    /// Open the card at `path` if it contains the save folder `folder` (read-only).
    pub fn open(path: impl Into<PathBuf>, folder: &str) -> Option<Self> {
        let path = path.into();
        let card = MemCard::open(&path).ok()?;
        card.has_dir(folder).then(|| MemCardStorage { card, folder: folder.to_string(), path, writable: false, on_disk: true })
    }
    /// Wrap an already parsed card (tests, in-memory images).
    pub fn from_card(card: MemCard, folder: &str) -> Option<Self> {
        card.has_dir(folder).then(|| MemCardStorage { card, folder: folder.to_string(), path: PathBuf::from("<memory>"), writable: false, on_disk: false })
    }
    /// Open an existing card image for writing (the save folder is created by the first write when it is missing).
    pub fn open_rw(path: impl Into<PathBuf>, folder: &str) -> Option<Self> {
        let path = path.into();
        let card = MemCard::open(&path).ok()?;
        Some(MemCardStorage { card, folder: folder.to_string(), path, writable: true, on_disk: true })
    }
    /// The port's own card: `path` when it is a valid image, else a freshly formatted one that is only written to disk by the first write.
    pub fn open_or_new(path: impl Into<PathBuf>, folder: &str) -> Self {
        let path = path.into();
        match MemCard::open(&path) {
            Ok(card) => MemCardStorage { card, folder: folder.to_string(), path, writable: true, on_disk: true },
            Err(e) => {
                // a file that exists but is not a card image is moved aside before a fresh card replaces it at the first write
                if path.is_file() {
                    let mut aside = path.as_os_str().to_owned();
                    aside.push(".corrupt");
                    log::warn!("save: {} is not a usable card image ({e}); keeping it as {}", path.display(), PathBuf::from(&aside).display());
                    let _ = std::fs::rename(&path, PathBuf::from(aside));
                }
                MemCardStorage { card: MemCard::format_new(true), folder: folder.to_string(), path, writable: true, on_disk: false }
            }
        }
    }
    /// A writable in-memory card (tests).
    pub fn in_memory(folder: &str) -> Self {
        MemCardStorage { card: MemCard::format_new(true), folder: folder.to_string(), path: PathBuf::from("<memory>"), writable: true, on_disk: false }
    }
    /// First of [`default_card_paths`] that holds `folder`.
    pub fn find(folder: &str) -> Option<Self> {
        default_card_paths().into_iter().find_map(|p| Self::open(p, folder))
    }
    pub fn card(&self) -> &MemCard {
        &self.card
    }
    pub fn is_writable(&self) -> bool {
        self.writable
    }
    pub fn folder_exists(&self) -> bool {
        self.card.has_dir(&self.folder)
    }
    /// Names of the files in the save folder.
    pub fn file_names(&self) -> Vec<String> {
        self.card.list_dir(&self.folder).map(|v| v.into_iter().filter(|e| e.is_file()).map(|e| e.name).collect()).unwrap_or_default()
    }
    fn persist(&mut self) -> Result<(), StorageError> {
        if self.path.as_os_str() == "<memory>" {
            return Ok(());
        }
        self.card.save(&self.path).map_err(|e| StorageError::Io(e.to_string()))?;
        self.on_disk = true;
        Ok(())
    }
    fn ro(&self) -> Result<(), StorageError> {
        if self.writable {
            Ok(())
        } else {
            Err(StorageError::Io("memory card image is read-only".into()))
        }
    }
    fn mc(e: McError) -> StorageError {
        match e {
            McError::Full => StorageError::Full,
            McError::NotFound => StorageError::NotFound,
            e => StorageError::Io(e.to_string()),
        }
    }
    /// Copy every file of `from`'s save folder into this card's folder (creating it): how the port card inherits the slots the real game made.
    pub fn import_folder(&mut self, from: &mut MemCardStorage) -> Result<usize, StorageError> {
        self.ro()?;
        let stamp = now_stamp();
        self.card.mkdir(&self.folder, stamp).map_err(Self::mc)?;
        let mut n = 0;
        for name in from.file_names() {
            let data = from.read(&name)?;
            self.card.write_file(&self.folder, &name, &data, stamp).map_err(Self::mc)?;
            n += 1;
        }
        // a card folder always has its icon files (the emulator card they came from may lack them in tests)
        if !self.file_names().iter().any(|f| f == "icon.sys") {
            self.card.write_file(&self.folder, "icon.sys", RETAIL_ICON_SYS, stamp).map_err(Self::mc)?;
        }
        if !self.file_names().iter().any(|f| f == "SH2.ICO") {
            if let Some(ico) = retail_icon_from_disc() {
                self.card.write_file(&self.folder, "SH2.ICO", &ico, stamp).map_err(Self::mc)?;
            }
        }
        self.persist()?;
        Ok(n)
    }
}

impl SaveStorage for MemCardStorage {
    fn status(&self) -> DeviceStatus {
        DeviceStatus::Formatted
    }
    fn free_kb(&self) -> u32 {
        if self.writable {
            self.card.free_kb()
        } else {
            0
        }
    }
    /// `SaveDeviceMC::Format`: a blank card (the whole image, like the real format).
    fn format(&mut self) -> Result<(), StorageError> {
        self.ro()?;
        self.card = MemCard::format_new(true);
        self.persist()
    }
    /// `SaveDevice::CreateSystem`: the save folder with `icon.sys` and `SH2.ICO` (the system file is written by the first save).
    fn create_system(&mut self) -> Result<(), StorageError> {
        self.ro()?;
        let stamp = now_stamp();
        self.card.mkdir(&self.folder, stamp).map_err(Self::mc)?;
        self.card.write_file(&self.folder, "icon.sys", RETAIL_ICON_SYS, stamp).map_err(Self::mc)?;
        if let Some(ico) = retail_icon_from_disc() {
            self.card.write_file(&self.folder, "SH2.ICO", &ico, stamp).map_err(Self::mc)?;
        }
        self.persist()
    }
    fn has_folder(&self) -> bool {
        self.card.has_dir(&self.folder)
    }
    fn read(&mut self, name: &str) -> Result<Vec<u8>, StorageError> {
        self.card.read_file(&self.folder, name).ok_or(StorageError::NotFound)
    }
    fn write(&mut self, name: &str, data: &[u8]) -> Result<(), StorageError> {
        self.ro()?;
        if !self.card.has_dir(&self.folder) {
            self.create_system()?;
        }
        self.card.write_file(&self.folder, name, data, now_stamp()).map_err(Self::mc)?;
        self.persist()
    }
    fn delete(&mut self, name: &str) -> Result<(), StorageError> {
        self.ro()?;
        self.card.delete_file(&self.folder, name, now_stamp()).map_err(Self::mc)?;
        self.persist()
    }
}

/// Test helper (also used by the integration tests): a tiny PS2 card image holding folder `dir` with `files`.
#[doc(hidden)]
/// Build a tiny card image: superblock (cluster 0), indirect FAT (1), FAT (2), data from cluster 3; root dir (rel 0..1),
/// folder `dir` (rel 2..3) with `files`, file data after.  `ecc` selects the 528 byte page layout.
pub fn synth_card(dir: &str, files: &[(&str, &[u8])], ecc: bool) -> Vec<u8> {
    let cl_bytes = 1024usize;
    let ncl = 64usize;
    let mut cl = vec![vec![0u8; cl_bytes]; ncl];
    let w32 = |c: &mut Vec<u8>, o: usize, v: u32| c[o..o + 4].copy_from_slice(&v.to_le_bytes());
    cl[0][..MAGIC.len()].copy_from_slice(MAGIC);
    cl[0][0x28..0x2a].copy_from_slice(&512u16.to_le_bytes());
    cl[0][0x2a..0x2c].copy_from_slice(&2u16.to_le_bytes());
    cl[0][0x2c..0x2e].copy_from_slice(&16u16.to_le_bytes());
    w32(&mut cl[0], 0x30, ncl as u32);
    w32(&mut cl[0], 0x34, 3); // alloc_offset
    w32(&mut cl[0], 0x38, 60);
    w32(&mut cl[0], 0x3c, 0); // root dir cluster
    for i in 0..32 {
        w32(&mut cl[0], 0x50 + i * 4, if i == 0 { 1 } else { u32::MAX });
    }
    w32(&mut cl[1], 0, 2); // indirect FAT: FAT cluster 2
    for i in 1..256 {
        w32(&mut cl[1], i * 4, u32::MAX);
    }
    // FAT: all free (0) except chains below
    let mut fat = vec![0u32; 256];
    let mut next_free = 4u32; // rel 0,1 root; 2,3 folder
    fat[0] = 0x8000_0001;
    fat[1] = 0xffff_ffff;
    fat[2] = 0x8000_0003;
    fat[3] = 0xffff_ffff;
    let entry = |name: &str, mode: u16, len: u32, cluster: u32| -> Vec<u8> {
        let mut e = vec![0u8; 512];
        e[0..2].copy_from_slice(&mode.to_le_bytes());
        e[4..8].copy_from_slice(&len.to_le_bytes());
        e[0x10..0x14].copy_from_slice(&cluster.to_le_bytes());
        e[0x40..0x40 + name.len()].copy_from_slice(name.as_bytes());
        e
    };
    // root: ".", "..", folder  (3 entries in 2 clusters)
    let mut root = Vec::new();
    root.extend(entry(".", 0x8427, 3, 0));
    root.extend(entry("..", 0xa426, 0, 0));
    root.extend(entry(dir, 0x8427, 2 + files.len() as u32, 2));
    root.resize(2048, 0);
    cl[3][..1024].copy_from_slice(&root[..1024]);
    cl[4][..1024].copy_from_slice(&root[1024..]);
    // folder entries
    let mut folder = Vec::new();
    folder.extend(entry(".", 0x8427, 0, 0));
    folder.extend(entry("..", 0xa426, 0, 0));
    let mut datas = Vec::new();
    for (name, content) in files {
        let n = (content.len() + cl_bytes - 1) / cl_bytes;
        let first = next_free;
        for k in 0..n {
            fat[(first as usize) + k] = if k + 1 == n { 0xffff_ffff } else { 0x8000_0000 | (first + k as u32 + 1) };
        }
        next_free += n as u32;
        folder.extend(entry(name, 0x8497, content.len() as u32, first));
        datas.push((first, *content));
    }
    folder.resize(4096.max(folder.len()), 0);
    // folder spans rel 2..3 only (2 clusters = 4 entries); callers use <= 2 files
    assert!(files.len() <= 2);
    cl[3 + 2][..1024].copy_from_slice(&folder[..1024]);
    cl[3 + 3][..1024].copy_from_slice(&folder[1024..2048]);
    for (first, content) in datas {
        for (k, ch) in content.chunks(cl_bytes).enumerate() {
            cl[3 + first as usize + k][..ch.len()].copy_from_slice(ch);
        }
    }
    for (i, v) in fat.iter().enumerate() {
        w32(&mut cl[2], i * 4, *v);
    }
    let mut out = Vec::new();
    for c in &cl {
        for p in 0..2 {
            out.extend_from_slice(&c[p * 512..(p + 1) * 512]);
            if ecc {
                out.extend_from_slice(&[0xa5; 16]);
            }
        }
    }
    out
}

#[cfg(test)]
pub(crate) mod tests {
    use super::*;


    #[test]
    fn synthetic_card_roundtrip() {
        let big: Vec<u8> = (0..3000u32).map(|i| (i * 7) as u8).collect();
        for ecc in [false, true] {
            let img = synth_card("BASLUS-21041-SH2", &[("SH2-000", &big), ("icon.sys", b"PS2D0123")], ecc);
            let card = MemCard::from_bytes(img).unwrap();
            assert!(card.has_dir("BASLUS-21041-SH2"));
            let names: Vec<String> = card.list_dir("BASLUS-21041-SH2").unwrap().into_iter().map(|e| e.name).collect();
            assert_eq!(names, ["SH2-000", "icon.sys"]);
            assert_eq!(card.read_file("BASLUS-21041-SH2", "SH2-000").unwrap(), big);
            assert_eq!(card.read_file("BASLUS-21041-SH2", "icon.sys").unwrap(), b"PS2D0123");
            assert!(card.read_file("BASLUS-21041-SH2", "nope").is_none());
            assert!(card.list_dir("OTHER").is_none());
        }
    }

    fn fill(n: usize, seed: u32) -> Vec<u8> {
        (0..n as u32).map(|i| (i.wrapping_mul(2654435761).wrapping_add(seed) >> 13) as u8).collect()
    }

    /// A formatted card parses back, has an empty root and the real card's geometry; every programmed page carries valid ECC.
    #[test]
    fn formatted_card_is_a_valid_empty_card() {
        for ecc in [true, false] {
            let c = MemCard::format_new(ecc);
            assert_eq!(c.to_bytes().len(), if ecc { 8192 * 2 * 528 } else { 8192 * 2 * 512 });
            let c2 = MemCard::from_bytes(c.to_bytes().to_vec()).expect("re-parse");
            assert!(c2.root().is_empty());
            assert_eq!(c2.free_clusters(), 8135 - 1, "all clusters but the root directory's are free");
            assert_eq!(c2.ecc_errors().1, 0);
        }
    }

    /// Files of every size class round-trip, the directory grows past two entries, overwrites free the old clusters, delete frees them.
    #[test]
    fn write_files_and_directories() {
        let mut c = MemCard::format_new(true);
        let st = stamp_from_unix(1_760_000_000);
        c.mkdir("BASLUS-21041-SH2", st).unwrap();
        c.mkdir("OTHER", st).unwrap();
        c.mkdir("BASLUS-21041-SH2", st).unwrap(); // existing: no-op
        assert_eq!(c.root().len(), 2);
        let free0 = c.free_clusters();
        let sizes = [0usize, 1, 1023, 1024, 1025, 12332, 39320, 4096];
        let names = ["a", "b", "c", "d", "e", "SH2-000", "SH2.ICO", "icon.sys"];
        for (k, (n, &sz)) in names.iter().zip(&sizes).enumerate() {
            c.write_file("BASLUS-21041-SH2", n, &fill(sz, k as u32), st).unwrap();
        }
        let c2 = MemCard::from_bytes(c.to_bytes().to_vec()).unwrap();
        for (k, (n, &sz)) in names.iter().zip(&sizes).enumerate() {
            assert_eq!(c2.read_file("BASLUS-21041-SH2", n).unwrap(), fill(sz, k as u32), "{n}");
        }
        assert_eq!(c2.list_dir("BASLUS-21041-SH2").unwrap().len(), 8, "the folder grew over four clusters");
        assert_eq!(c2.list_dir("OTHER").unwrap().len(), 0);
        assert_eq!(c2.ecc_errors(), (c2.ecc_errors().0, 0), "every programmed page has valid ECC");
        // the folder entry in the root counts `.`, `..` and the files
        let fe = c2.root().into_iter().find(|e| e.name == "BASLUS-21041-SH2").unwrap();
        assert_eq!(fe.length, 2 + 8);
        let data_clusters: usize = sizes.iter().map(|s| s.div_ceil(1024)).sum();
        // 4 directory clusters are needed for 10 entries (2 are already used by the empty folder: + 3)
        assert_eq!(free0 as usize - c2.free_clusters() as usize, data_clusters + 4, "dir growth + file clusters");
        // overwrite with a smaller / larger file, delete
        let mut c3 = MemCard::from_bytes(c.to_bytes().to_vec()).unwrap();
        c3.write_file("BASLUS-21041-SH2", "SH2-000", &fill(500, 99), st).unwrap();
        assert_eq!(c3.read_file("BASLUS-21041-SH2", "SH2-000").unwrap(), fill(500, 99));
        assert_eq!(c3.list_dir("BASLUS-21041-SH2").unwrap().len(), 8, "overwrite keeps the entry");
        c3.write_file("BASLUS-21041-SH2", "SH2-000", &fill(20000, 7), st).unwrap();
        assert_eq!(c3.read_file("BASLUS-21041-SH2", "SH2-000").unwrap(), fill(20000, 7));
        let before = c3.free_clusters();
        c3.delete_file("BASLUS-21041-SH2", "SH2.ICO", st).unwrap();
        assert_eq!(c3.free_clusters(), before + 39320u32.div_ceil(1024));
        assert!(c3.read_file("BASLUS-21041-SH2", "SH2.ICO").is_none());
        assert_eq!(c3.ecc_errors().1, 0);
        assert!(matches!(c3.write_file("NOPE", "x", b"1", st), Err(McError::NotFound)));
    }

    /// A card that is full refuses a file that does not fit and stays intact.
    #[test]
    fn full_card_is_refused() {
        let mut c = MemCard::format_new(false);
        let st = now_stamp();
        c.mkdir("F", st).unwrap();
        let big = fill(8_400_000, 1);
        assert!(matches!(c.write_file("F", "big", &big, st), Err(McError::Full)));
        c.write_file("F", "ok", &fill(5_000_000, 2), st).unwrap();
        assert!(matches!(c.write_file("F", "ok2", &fill(5_000_000, 3), st), Err(McError::Full)));
        // replacing the big file by a smaller one always fits (its own clusters count as free)
        c.write_file("F", "ok", &fill(6_000_000, 4), st).unwrap();
        assert_eq!(c.read_file("F", "ok").unwrap(), fill(6_000_000, 4));
    }

    /// The ECC formula against the real card written by the retail game (when this machine has one): all programmed pages but the superblock's second one.
    #[test]
    fn ecc_matches_the_real_card_and_writes_on_it_stay_valid() {
        let Some(path) = default_card_paths().into_iter().find(|p| p.is_file()) else { return };
        let Ok(card) = MemCard::open(&path) else { return };
        if !card.has_ecc() {
            return;
        }
        let (checked, bad) = card.ecc_errors();
        assert!(checked > 100 && bad <= 1, "{bad} of {checked} programmed pages disagree");
        // rewrite a file in a copy of the image: nothing else changes and every new page has valid ECC
        let Some(dir) = card.root().into_iter().find(|e| e.is_dir() && e.name.starts_with("BASLUS-21041")) else { return };
        let mut copy = MemCard::from_bytes(card.to_bytes().to_vec()).unwrap();
        let files = copy.list_dir(&dir.name).unwrap();
        let Some(f) = files.iter().find(|e| e.name.starts_with("SH2-0")) else { return };
        let old = copy.read_file(&dir.name, &f.name).unwrap();
        copy.write_file(&dir.name, &f.name, &old, now_stamp()).unwrap();
        assert_eq!(copy.read_file(&dir.name, &f.name).unwrap(), old);
        assert_eq!(copy.ecc_errors().1, bad, "the rewrite adds no ECC errors");
        for e in &files {
            if e.name != f.name {
                assert_eq!(copy.read_file(&dir.name, &e.name), card.read_file(&dir.name, &e.name), "{}", e.name);
            }
        }
        let other_dirs: Vec<_> = card.root().iter().map(|e| (e.name.clone(), e.length)).collect();
        let copy_dirs: Vec<_> = copy.root().iter().map(|e| (e.name.clone(), e.length)).collect();
        assert_eq!(other_dirs, copy_dirs, "the other save folders are untouched");
    }

    /// The icon files the port writes are the real ones: `icon.sys` byte for byte, and `SH2.ICO` from `COMMON/SH2_000.ICO` of the disc (the real card holds
    /// exactly those 39320 bytes).
    #[test]
    fn icon_files_are_the_retail_ones() {
        assert_eq!(RETAIL_ICON_SYS.len(), 0x3c4);
        assert_eq!(&RETAIL_ICON_SYS[..4], b"PS2D");
        let Some(ico) = retail_icon_from_disc() else { return };
        assert_eq!(ico.len(), 39320);
        assert_eq!(&ico[..8], &[0, 0, 1, 0, 4, 0, 0, 0]);
        let Some(path) = default_card_paths().into_iter().find(|p| p.is_file()) else { return };
        let Some(st) = MemCardStorage::open(path, "BASLUS-21041-SH2") else { return };
        let mut st = st;
        if let Ok(real) = st.read("SH2.ICO") {
            assert_eq!(real, ico, "same bytes as the icon the real game put on the card");
        }
        if let Ok(real) = st.read("icon.sys") {
            assert_eq!(real, RETAIL_ICON_SYS);
        }
    }

    /// A damaged card file is never overwritten: it is moved aside and a fresh card is created by the first write.
    #[test]
    fn a_corrupt_port_card_is_kept_aside() {
        let dir = std::env::temp_dir().join(format!("sh2_card_corrupt_{}", std::process::id()));
        let _ = std::fs::remove_dir_all(&dir);
        std::fs::create_dir_all(&dir).unwrap();
        let path = dir.join("mcd_sh2_port.ps2");
        std::fs::write(&path, b"this is not a memory card").unwrap();
        let mut st = MemCardStorage::open_or_new(&path, "BASLUS-21041-SH2");
        assert!(!path.exists() && dir.join("mcd_sh2_port.ps2.corrupt").exists());
        st.create_system().unwrap();
        st.write("SH2-000", b"abc").unwrap();
        assert!(path.exists());
        assert_eq!(std::fs::read(dir.join("mcd_sh2_port.ps2.corrupt")).unwrap(), b"this is not a memory card");
        let mut again = MemCardStorage::open_or_new(&path, "BASLUS-21041-SH2");
        assert_eq!(again.read("SH2-000").unwrap(), b"abc");
        let _ = std::fs::remove_dir_all(&dir);
    }

    #[test]
    fn card_time_stamps() {
        // 2026-10-10 11:07:24 UTC (the folder time of the real card is 0x18 / 0x07 / 0x0b / 0x0a / 0x0a / 0x07ea)
        assert_eq!(stamp_from_unix(1_791_630_444), [0, 24, 7, 11, 10, 10, 0xea, 0x07]);
        assert_eq!(stamp_from_unix(0), [0, 0, 0, 0, 1, 1, 0xb2, 0x07]);
    }

    #[test]
    fn bad_images_are_rejected() {
        assert!(matches!(MemCard::from_bytes(vec![0; 4096]), Err(McError::BadMagic)));
        assert!(matches!(MemCard::from_bytes(vec![0xff; 4096]), Err(McError::BadMagic)));
    }

    /// The emulator's own card, when this machine has one with a Shadow Hearts save: the real `SH2-000` must load.
    #[test]
    fn real_emulator_card_save_loads() {
        let Some(mut st) = MemCardStorage::find(crate::save::SAVE_FOLDER_RETAIL) else { return };
        let sys = st.read(crate::save::SAVE_FOLDER_RETAIL).expect("system file");
        let sys = crate::save::SystemFile::parse(&sys).unwrap();
        let Some(slot) = sys.first_used_slot() else { return };
        let bytes = st.read(&crate::storage::slot_file_name(slot)).expect("slot file");
        let f = crate::save::SaveFile::parse(&bytes).unwrap();
        assert!(f.checksum_ok && f.build.is_retail());
        assert_eq!(f.to_bytes(), bytes, "real save re-serialises identically");
    }
}

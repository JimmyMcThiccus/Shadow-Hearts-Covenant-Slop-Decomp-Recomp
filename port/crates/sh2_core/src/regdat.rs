//! RegDatApi — "registered data" heap + game database accessor (JP `RegDatApi.cpp`, 0x0037b130..0x0037d98c).
//!
//! # Heap (`RegDatApi::SetData / ReleaseData / DataRelease / RegKeepReset`)
//! A first-fit block allocator over the *reserved* EE region `0x00108000..0x00200000` (0xF8000 bytes, just below the
//! executable).  It survives soft resets (`RegKeepReset` is the post-reset sanity pass).
//! ```text
//! block header (16 bytes):  +0 char tag[4]   ("reg1", "reg2", ... ; 0 = free)
//!                           +4 prev block*   +8 next block* (== 0x00200000 at the end)   +0xc u32 size (payload)
//! payload at +0x10 (16-byte aligned sizes)
//! ```
//! `Initialize` creates one free block (`prev=0, next=0x200000, size=0xf7ff0`) and queues two `ReadOrder`s:
//! `common/sshmes.jpn` -> tag **"reg1"** (messages) and `common/sshdat.jpn` -> tag **"reg2"** (data tables); the callback
//! (`RegDatApi::ReadCallBack`) copies the file into the heap.  `SSHSys::Initialize` spins on `CheckRegDat()` until both exist.
//!
//! # RegFile format (both files)
//! ```text
//! +0x00 u32 count      (sshdat: 33 tables, sshmes: 44 tables)
//! +0x04 u32 total_size
//! +0x08 { u32 tag, u32 offset } * count      -- NOTE tag_i at +8+8i, offset_i at +0xc+8i
//! GetFileEntry(blob,i) = blob + offset_i ; GetFileSize(blob,i) = offset_{i+1} - offset_i (last: total - offset_i)
//! ```
//! Tags seen: `PC_I PC_N FUSM ...` (ASCII, little endian).
//!
//! # GetRegDat / GetRegCnt
//! `GetRegDat(kind, index, sub)` returns a pointer into the loaded blobs, `GetRegCnt(kind, sub)` the element count.
//! Kinds `0x00..=0x25` return **names/descriptions** (fixed width strings in sshmes: 0x12-byte names for kinds `0..=0x15`, 0x50-byte
//! descriptions for `0x16..=0x22`) found through the name index stored inside the matching data record (u16 at +2 unless noted);
//! kinds `0x26..=0x43` return **records** from sshdat.  A few data tables are *jagged* (array of `{u32 off, u32 count}` followed by
//! sub-records) — they take a non-negative `sub` index.  Kinds 4, 0x16 and 0x2c depend on the current difficulty/chapter level
//! `BtlSaveSec::ourBtlSaveDat+4` (0..3), which selects data table `6+level`.

use std::collections::BTreeMap;

pub const HEAP_BASE: u32 = 0x0010_8000;
pub const HEAP_END: u32 = 0x0020_0000;
pub const HEAP_SIZE: usize = (HEAP_END - HEAP_BASE) as usize;
pub const TAG_MES: [u8; 4] = *b"reg1";
pub const TAG_DAT: [u8; 4] = *b"reg2";

#[derive(Debug, Clone, Copy)]
struct Block {
    tag: [u8; 4],
    size: u32,
}

/// First-fit allocator with the exact policy of `SetData`: scan *all* blocks, keep the **last** free block that is large
/// enough (`size >= need && size < 0x100000`), split it if more than 16 bytes would remain.
#[derive(Debug, Default)]
pub struct RegHeap {
    /// blocks in address order: (start address, block)
    blocks: Vec<(u32, Block)>,
    mem: BTreeMap<u32, Vec<u8>>,
}

impl RegHeap {
    // JP: 0x0037b430 Initialize__9RegDatApiFv (heap part)
    pub fn new() -> Self {
        RegHeap { blocks: vec![(HEAP_BASE, Block { tag: [0; 4], size: 0xf7ff0 })], mem: BTreeMap::new() }
    }

    // JP: 0x0037d7f0 SetData__9RegDatApiFPvUiPc  -> payload address
    pub fn set_data(&mut self, data: &[u8], tag: [u8; 4]) -> Option<u32> {
        let need = (data.len() as u32 + 0xf) & !0xf;
        let mut pick: Option<usize> = None;
        for (i, (_, b)) in self.blocks.iter().enumerate() {
            if b.tag == [0; 4] && need <= b.size && b.size < 0x100000 {
                pick = Some(i);
            }
        }
        let i = pick?;
        let (addr, blk) = self.blocks[i];
        if blk.size - need > 0x10 {
            let new_addr = addr + need + 0x10;
            self.blocks.insert(i + 1, (new_addr, Block { tag: [0; 4], size: blk.size - need - 0x10 }));
        }
        self.blocks[i].1 = Block { tag, size: data.len() as u32 };
        self.mem.insert(addr + 0x10, data.to_vec());
        Some(addr + 0x10)
    }

    // JP: 0x0037d910 ReleaseData__9RegDatApiFPc / 0x0037b3d0 DataRelease (marks free, merges with free neighbours)
    pub fn release(&mut self, tag: [u8; 4]) {
        if let Some(i) = self.blocks.iter().position(|(_, b)| b.tag == tag) {
            let addr = self.blocks[i].0;
            self.mem.remove(&(addr + 0x10));
            self.blocks[i].1.tag = [0; 4];
            // merge with next free block
            if i + 1 < self.blocks.len() && self.blocks[i + 1].1.tag == [0; 4] {
                let next = self.blocks.remove(i + 1);
                self.blocks[i].1.size = self.blocks[i].1.size.max(0) + 0x10 + next.1.size;
            }
            // merge with previous free block
            if i > 0 && self.blocks[i - 1].1.tag == [0; 4] {
                let cur = self.blocks.remove(i);
                self.blocks[i - 1].1.size += 0x10 + cur.1.size;
            }
        }
    }

    pub fn find(&self, tag: [u8; 4]) -> Option<&[u8]> {
        let (addr, _) = self.blocks.iter().find(|(_, b)| b.tag == tag)?;
        self.mem.get(&(addr + 0x10)).map(|v| v.as_slice())
    }

    // JP: 0x0037b5e0 CheckRegDat__9RegDatApiFv
    pub fn check(&self) -> bool {
        self.find(TAG_MES).is_some() && self.find(TAG_DAT).is_some()
    }
}

/// A parsed RegFile blob (see module docs).
#[derive(Debug, Clone, Copy)]
pub struct RegFile<'a> {
    pub bytes: &'a [u8],
}

impl<'a> RegFile<'a> {
    pub fn new(bytes: &'a [u8]) -> Self {
        RegFile { bytes }
    }
    fn u32_at(&self, o: usize) -> u32 {
        u32::from_le_bytes(self.bytes[o..o + 4].try_into().unwrap())
    }
    pub fn count(&self) -> u32 {
        self.u32_at(0)
    }
    pub fn total(&self) -> u32 {
        self.u32_at(4)
    }
    /// JP: 0x00260c80 GetFileEntry — offset of table `i`
    pub fn entry(&self, i: usize) -> usize {
        self.u32_at(0xc + i * 8) as usize
    }
    pub fn tag(&self, i: usize) -> [u8; 4] {
        self.bytes[8 + i * 8..12 + i * 8].try_into().unwrap()
    }
    /// JP: 0x00260be0 GetFileSize
    pub fn size(&self, i: usize) -> usize {
        if (i as u32) + 1 < self.count() {
            self.entry(i + 1) - self.entry(i)
        } else {
            self.total() as usize - self.entry(i)
        }
    }
}

/// How a kind addresses its table.
#[derive(Debug, Clone, Copy)]
pub struct DataKind {
    /// data table index in sshdat (`6` is the first of the 4 level tables for [`LEVEL`])
    pub table: u8,
    pub stride: u8,
    /// jagged table: `{off,count}` header array then sub-records of `stride` bytes
    pub jagged: bool,
    /// default count for a jagged table when `sub < 0`
    pub default_cnt: u8,
}
const fn dk(table: u8, stride: u8) -> DataKind {
    DataKind { table, stride, jagged: false, default_cnt: 0 }
}
const fn jg(table: u8, stride: u8, default_cnt: u8) -> DataKind {
    DataKind { table, stride, jagged: true, default_cnt }
}
/// marker: table = `6 + level`
pub const LEVEL: u8 = 0xfe;

/// Record kinds `0x26..=0x43` (index = kind - 0x26).  JP 0x0037b6b0 `GetRegDat` / 0x0037c900 `GetRegCnt`.
pub const DATA_KINDS: [DataKind; 30] = [
    dk(0, 0x1c),     // 0x26
    dk(1, 0x1c),     // 0x27
    dk(2, 0x1c),     // 0x28
    dk(3, 0x1c),     // 0x29
    jg(4, 0x10, 0xd), // 0x2a
    jg(5, 0x20, 0xc), // 0x2b
    dk(LEVEL, 0x20), // 0x2c
    jg(10, 0x10, 0x11), // 0x2d
    dk(11, 0x38),    // 0x2e
    dk(12, 0x10),    // 0x2f
    dk(13, 0x34),    // 0x30
    dk(14, 0x18),    // 0x31
    dk(15, 0x2c),    // 0x32
    dk(16, 0x30),    // 0x33
    dk(17, 8),       // 0x34
    dk(18, 0xc),     // 0x35
    jg(19, 0x40, 0x18), // 0x36  (sub-stride 0x40 for kinds 0..0x15, 0x28 for 0x16, 0x20 for 0x17)
    dk(20, 0x1c),    // 0x37
    dk(21, 0x44),    // 0x38
    dk(22, 0x40),    // 0x39
    dk(23, 0x18),    // 0x3a
    dk(24, 0x48),    // 0x3b
    dk(25, 8),       // 0x3c
    dk(26, 0x40),    // 0x3d
    dk(27, 0x20),    // 0x3e
    jg(28, 4, 4),    // 0x3f
    dk(29, 0x10),    // 0x40
    dk(30, 0x1c),    // 0x41
    dk(31, 0x1c),    // 0x42
    dk(32, 0x1c),    // 0x43
];

/// Name kinds `0x00..=0x22`: (data table, data stride, field offset of the name index inside the record,
/// name table in sshmes, name stride).  `LEVEL` tables use `6+level` / `4+level` (kind 4) / `0x19+level` (kind 0x16).
#[derive(Debug, Clone, Copy)]
pub struct NameKind {
    pub data_table: u8,
    pub data_stride: u8,
    pub field_off: u8,
    pub field_is_byte: bool,
    pub mes_table: u8,
    pub mes_stride: u8,
}
const fn nk(data_table: u8, data_stride: u8, field_off: u8, mes_table: u8, mes_stride: u8) -> NameKind {
    NameKind { data_table, data_stride, field_off, field_is_byte: false, mes_table, mes_stride }
}
pub const NAME_KINDS: [NameKind; 35] = [
    nk(0, 0x1c, 2, 0, 0x12),      // 0
    nk(1, 0x1c, 2, 1, 0x12),      // 1
    nk(2, 0x1c, 2, 2, 0x12),      // 2
    nk(3, 0x1c, 2, 3, 0x12),      // 3
    NameKind { data_table: LEVEL, data_stride: 0x20, field_off: 1, field_is_byte: true, mes_table: LEVEL, mes_stride: 0x12 }, // 4 (mes 4+level)
    nk(11, 0x38, 2, 8, 0x12),     // 5
    nk(13, 0x34, 2, 9, 0x12),     // 6
    nk(14, 0x18, 2, 10, 0x12),    // 7
    nk(15, 0x2c, 2, 11, 0x12),    // 8
    nk(16, 0x30, 2, 12, 0x12),    // 9
    nk(17, 8, 2, 13, 0x12),       // 0xa
    nk(18, 0xc, 2, 14, 0x12),     // 0xb (signed short)
    nk(19, 0x40, 2, 15, 0x12),    // 0xc (jagged data; sub<0 => direct index)
    nk(20, 0x1c, 2, 16, 0x12),    // 0xd
    nk(21, 0x44, 2, 17, 0x12),    // 0xe
    nk(22, 0x40, 2, 18, 0x12),    // 0xf
    nk(25, 8, 2, 19, 0x12),       // 0x10
    nk(27, 0x20, 2, 20, 0x12),    // 0x11
    nk(29, 0x10, 2, 21, 0x12),    // 0x12
    nk(30, 0x1c, 2, 22, 0x12),    // 0x13
    nk(31, 0x1c, 2, 23, 0x12),    // 0x14
    nk(32, 0x1c, 2, 24, 0x12),    // 0x15
    NameKind { data_table: LEVEL, data_stride: 0x20, field_off: 0x1e, field_is_byte: false, mes_table: LEVEL, mes_stride: 0x50 }, // 0x16 (mes 0x19+level)
    nk(13, 0x34, 0x32, 29, 0x50), // 0x17
    nk(14, 0x18, 0x14, 30, 0x50), // 0x18
    nk(15, 0x2c, 0x28, 31, 0x50), // 0x19
    nk(16, 0x30, 0x22, 32, 0x50), // 0x1a
    nk(17, 8, 4, 33, 0x50),       // 0x1b
    nk(18, 0xc, 8, 34, 0x50),     // 0x1c
    nk(19, 0x40, 0x3e, 35, 0x50), // 0x1d (jagged)
    nk(20, 0x1c, 0x18, 36, 0x50), // 0x1e
    nk(21, 0x44, 0x3c, 37, 0x50), // 0x1f
    nk(22, 0x40, 0x3c, 38, 0x50), // 0x20
    nk(25, 8, 4, 39, 0x50),       // 0x21
    nk(27, 0x20, 0x1c, 40, 0x50), // 0x22
];

/// Loaded database (the two blobs).
pub struct RegDat<'a> {
    pub mes: RegFile<'a>,
    pub dat: RegFile<'a>,
}

impl<'a> RegDat<'a> {
    pub fn new(mes: &'a [u8], dat: &'a [u8]) -> Self {
        RegDat { mes: RegFile::new(mes), dat: RegFile::new(dat) }
    }

    fn data_table(&self, k: &DataKind, level: u8) -> usize {
        if k.table == LEVEL {
            6 + level as usize
        } else {
            k.table as usize
        }
    }

    /// JP: 0x0037c900 GetRegCnt (record kinds)
    pub fn cnt_data(&self, kind: u8, sub: i32, level: u8) -> Option<u32> {
        let k = DATA_KINDS.get(kind.checked_sub(0x26)? as usize)?;
        let t = self.dat.entry(self.data_table(k, level));
        if k.jagged {
            if sub < 0 {
                return Some(k.default_cnt as u32);
            }
            let o = t + sub as usize * 8 + 4;
            return Some(u32::from_le_bytes(self.dat.bytes[o..o + 4].try_into().ok()?));
        }
        Some((self.dat.size(self.data_table(k, level)) / k.stride as usize) as u32)
    }

    /// byte offset into sshdat of record `index` (non-jagged), or of sub-record `sub-1`? (see `GetRegDat`: jagged tables skip
    /// a header record, `+ (sub-1)*stride` when `sub>0`).
    pub fn rec_data(&self, kind: u8, index: u32, sub: i32, level: u8) -> Option<usize> {
        let k = DATA_KINDS.get(kind.checked_sub(0x26)? as usize)?;
        let ti = self.data_table(k, level);
        let t = self.dat.entry(ti);
        if k.jagged {
            let o = t + index as usize * 8;
            let off = u32::from_le_bytes(self.dat.bytes[o..o + 4].try_into().ok()?) as usize;
            let mut p = t + off;
            if sub > 0 {
                p += (sub as usize - 1) * k.stride as usize;
            }
            Some(p)
        } else {
            Some(t + index as usize * k.stride as usize)
        }
    }

    /// JP: GetRegDat kinds 0..=0x22 — offset into sshmes of the name/description for record `index` of the matching data table
    pub fn name(&self, kind: u8, index: u32, level: u8) -> Option<usize> {
        let k = NAME_KINDS.get(kind as usize)?;
        let dt = if k.data_table == LEVEL { 6 + level as usize } else { k.data_table as usize };
        let mt = if k.mes_table == LEVEL {
            if k.mes_stride == 0x12 { 4 + level as usize } else { 0x19 + level as usize }
        } else {
            k.mes_table as usize
        };
        let rec = self.dat.entry(dt) + index as usize * k.data_stride as usize + k.field_off as usize;
        let idx = if k.field_is_byte { self.dat.bytes[rec] as usize } else { u16::from_le_bytes(self.dat.bytes[rec..rec + 2].try_into().ok()?) as usize };
        Some(self.mes.entry(mt) + idx * k.mes_stride as usize)
    }
}

// ====================================================================================================
// US retail (SLUS_210.41): `GetRegDat` kinds 0x00..0x53, `sshdat.na` (37 tables) / `sshmes.na` (47 tables)
// ====================================================================================================
//
// `RegDatApi::GetRegDat` (US 0x003b9540, decompiled in Ghidra `SLUS_210.41`; notes/I/us_delta.md section 6) is the same
// switch as the demo's, regrown to 84 kinds:
//
// * kinds `0x00..=0x17` return an 0x12 byte *name* (`mes[table] + u16/u8 field of the data record * 0x12`),
// * kinds `0x18..=0x2e` return a *description*: the message table starts with `u32` offsets (relative to the table) and
//   the strings follow (variable length, `$` = line break, `%pN` / `%tN` colour codes) -- the demo's fixed 0x50 byte rows are gone,
// * kinds `0x2f..=0x53` return the record of data file `kind - 0x2f` (files 0..=0x24): `+ index * stride`, jagged tables
//   (`{u32 off, u32 count}` header per index, `sub > 0` selects `(sub - 1)` rows / `sub` rows) as listed in [`US_DATA_KINDS`].
//
// What changed against the demo (all verified on the retail disc, see `tests` below and notes/integration/us_retail.md):
// the four per-difficulty `PC_I` / `FUSM` tables are gone (one `PC_I`, one `FUSM`), `MONSET` records are 0x14 bytes
// (`{u16 id, u16 formation, u16 monsters[6], u32 flags}`), `KEYI` is 0x10 bytes, `YOAH` 0x18, six `DEMO` tables, new
// `TARO` (tarot, 8 B) / `PHOT` (photo, 0x20) / `STAR` / `ANNE` / `BTL_` / `PIT_` tables.

/// How a data file is addressed by a record kind.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct UsDataKind {
    /// index of the table in `sshdat.na`
    pub file: u8,
    pub stride: u8,
    /// `{u32 off, u32 count}` header per index, then rows (`GetRegDat(kind, index, sub)`: row `sub - 1`, or the header row when `sub <= 0`)
    pub jagged: bool,
}
const fn ud(file: u8, stride: u8) -> UsDataKind {
    UsDataKind { file, stride, jagged: false }
}
const fn uj(file: u8, stride: u8) -> UsDataKind {
    UsDataKind { file, stride, jagged: true }
}

/// Kinds `0x2f..=0x53` (index = kind - 0x2f).
pub const US_DATA_KINDS: [UsDataKind; 37] = [
    ud(0, 0x1c),  // 0x2f PC_I
    uj(1, 0x10),  // 0x30 PC_L (level rows)
    uj(2, 0x20),  // 0x31 PC_J
    ud(3, 0x20),  // 0x32 FUSM
    uj(4, 0x10),  // 0x33 FUSM grow
    ud(5, 0x38),  // 0x34 MON_  MONSTERParam
    ud(6, 0x14),  // 0x35 MON_  MONSET
    ud(7, 0x34),  // 0x36 WPN_
    ud(8, 0x18),  // 0x37 ARM_
    ud(9, 0x2c),  // 0x38 ACS_
    ud(10, 0x30), // 0x39 ITEM
    ud(11, 0x10), // 0x3a KEYI
    ud(12, 0xc),  // 0x3b CLOT
    uj(13, 0x40), // 0x3c SKIL (jagged; sub-stride 0x40 / 0x28 / 0x20 by the *index* range, see `us_skill_stride`)
    ud(14, 0x1c), // 0x3d MC_P
    ud(15, 0x44), // 0x3e MAGI
    ud(16, 0x40), // 0x3f COMB
    ud(17, 0x18), // 0x40 PATK
    ud(18, 0x48), // 0x41 PATK2
    ud(19, 8),    // 0x42 AROM
    ud(20, 0x40), // 0x43 AROM
    ud(21, 8),    // 0x44 TARO
    ud(22, 0x20), // 0x45 PHOT
    ud(23, 0x20), // 0x46 JRCI
    uj(24, 4),    // 0x47 SCEN (starting inventory per scenario: `{off,count}` then 4 byte records)
    ud(25, 0x10), // 0x48 YOAH (stride 0x10 in GetRegDat; the file holds 0x18 byte rows, see notes)
    ud(26, 0x1c), // 0x49 DEMO
    ud(27, 0x1c), // 0x4a
    ud(28, 0x1c), // 0x4b
    ud(29, 0x1c), // 0x4c
    ud(30, 0x1c), // 0x4d
    ud(31, 0x1c), // 0x4e
    ud(32, 0x20), // 0x4f STAR
    ud(33, 0x20), // 0x50 ANNE
    ud(34, 8),    // 0x51 BTL_
    ud(35, 0x24), // 0x52 BTL_
    ud(36, 0x3c), // 0x53 PIT_
];

/// First record kind of the retail `GetRegDat` (the demo's was 0x26).
pub const US_FIRST_DATA_KIND: u8 = 0x2f;
pub const US_LAST_KIND: u8 = 0x53;
/// Monster-set table (`StartBattle`): kind 0x35 in the retail build, 0x2f in the demo.
pub const US_KIND_MONSET: u8 = 0x35;
pub const US_KIND_MONSTER: u8 = 0x34;
pub const US_KIND_SCEN: u8 = 0x47;

/// `SKIL` rows are 0x40 bytes for the 24 sub tables 0..=0x17, 0x28 for 0x18 and 0x20 for 0x19 (`GetRegDat` kind 0x3c).
pub fn us_skill_stride(table: u32) -> usize {
    match table {
        0x18 => 0x28,
        0x19 => 0x20,
        _ => 0x40,
    }
}

/// How a name / description kind finds its string.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum UsStr {
    /// 0x12 byte name: `mes[mes] + idx * 0x12`, `idx` = u16 / u8 / i16 at `field` of data record `index`
    Name,
    /// description: `mes[mes] + u32 at (mes[mes] + idx * 4)`
    Desc,
}

/// One of kinds 0x00..=0x2e that follows the plain "record -> message index -> string" pattern.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct UsNameKind {
    pub dat_file: u8,
    pub stride: u8,
    pub field: u16,
    pub byte: bool,
    pub signed: bool,
    pub mes: u8,
    pub style: UsStr,
}
const fn un(dat_file: u8, stride: u8, field: u16, mes: u8) -> UsNameKind {
    UsNameKind { dat_file, stride, field, byte: false, signed: false, mes, style: UsStr::Name }
}
const fn ur(dat_file: u8, stride: u8, field: u16, mes: u8) -> UsNameKind {
    UsNameKind { dat_file, stride, field, byte: false, signed: false, mes, style: UsStr::Desc }
}

/// Name / description kinds.  `None` entries are the special kinds handled in [`UsRegDat::string_offset`] (0x09, 0x1f, 0x25, 0x27..0x29).
pub const US_NAME_KINDS: [Option<UsNameKind>; 0x2f] = [
    Some(un(0, 0x1c, 2, 0)),     // 0x00 PC name
    Some(UsNameKind { byte: true, ..un(3, 0x20, 1, 1) }), // 0x01 FUSM (monster fusion) name
    Some(un(5, 0x38, 2, 2)),     // 0x02 MON
    Some(un(7, 0x34, 2, 3)),     // 0x03 WPN
    Some(un(8, 0x18, 2, 4)),     // 0x04 ARM
    Some(un(9, 0x2c, 2, 5)),     // 0x05 ACS
    Some(un(10, 0x30, 2, 6)),    // 0x06 ITEM
    Some(un(11, 0x10, 2, 7)),    // 0x07 KEYI
    Some(UsNameKind { signed: true, ..un(12, 0xc, 2, 8) }), // 0x08 CLOT
    None,                        // 0x09 SKIL (jagged)
    Some(un(14, 0x1c, 2, 0xa)),  // 0x0a MC_P
    Some(un(15, 0x44, 2, 0xb)),  // 0x0b MAGI
    Some(un(16, 0x40, 2, 0xc)),  // 0x0c COMB
    Some(un(19, 8, 2, 0xd)),     // 0x0d AROM
    Some(un(21, 8, 2, 0xe)),     // 0x0e TARO
    Some(un(22, 0x20, 2, 0xf)),  // 0x0f PHOT
    Some(un(23, 0x20, 2, 0x10)), // 0x10 JRCI
    Some(un(25, 0x10, 2, 0x11)), // 0x11 YOAH
    Some(un(26, 0x1c, 2, 0x12)), // 0x12 DEMO
    Some(un(27, 0x1c, 2, 0x13)), // 0x13
    Some(un(28, 0x1c, 2, 0x14)), // 0x14
    Some(un(29, 0x1c, 2, 0x15)), // 0x15
    Some(un(30, 0x1c, 2, 0x16)), // 0x16
    Some(un(31, 0x1c, 2, 0x17)), // 0x17
    Some(ur(3, 0x20, 0x1e, 0x18)),  // 0x18 FUSM description
    Some(ur(7, 0x34, 0x32, 0x19)),  // 0x19 WPN
    Some(ur(8, 0x18, 0x14, 0x1a)),  // 0x1a ARM
    Some(ur(9, 0x2c, 0x28, 0x1b)),  // 0x1b ACS
    Some(ur(10, 0x30, 0x22, 0x1c)), // 0x1c ITEM
    Some(ur(11, 0x10, 0xc, 0x1d)),  // 0x1d KEYI
    Some(ur(12, 0xc, 8, 0x1e)),     // 0x1e CLOT
    None,                           // 0x1f SKIL description (jagged)
    Some(ur(14, 0x1c, 0x18, 0x20)), // 0x20 MC_P
    Some(ur(15, 0x44, 0x3c, 0x21)), // 0x21 MAGI
    Some(ur(16, 0x40, 0x3c, 0x22)), // 0x22 COMB
    Some(ur(19, 8, 4, 0x23)),       // 0x23 AROM
    Some(ur(20, 0x40, 0x3c, 0x24)), // 0x24 AROM2
    None,                           // 0x25 tarot description (4-way)
    Some(ur(23, 0x20, 0x1c, 0x26)), // 0x26 JRCI
    None,                           // 0x27 TUTO (jagged {_, off})
    None,                           // 0x28 TUTO
    None,                           // 0x29 PAUS (whole table)
    Some(un(34, 8, 2, 0x2a)),       // 0x2a BM_I (battle message, name style)
    Some(ur(34, 8, 4, 0x2b)),       // 0x2b BM_N
    Some(ur(34, 8, 6, 0x2c)),       // 0x2c BM_M
    Some(ur(36, 0x3c, 2, 0x2d)),    // 0x2d PFD_
    Some(ur(36, 0x3c, 4, 0x2e)),    // 0x2e PFD_
];

/// The retail databases (`common/sshdat.na` + `common/sshmes.na`), addressed with the retail `GetRegDat` kinds.
#[derive(Clone, Copy)]
pub struct UsRegDat<'a> {
    pub mes: RegFile<'a>,
    pub dat: RegFile<'a>,
}

fn rd_u16(b: &[u8], o: usize) -> Option<u16> {
    Some(u16::from_le_bytes(b.get(o..o + 2)?.try_into().ok()?))
}
fn rd_u32(b: &[u8], o: usize) -> Option<u32> {
    Some(u32::from_le_bytes(b.get(o..o + 4)?.try_into().ok()?))
}

impl<'a> UsRegDat<'a> {
    /// `dat` = `sshdat.na` (37 tables), `mes` = `sshmes.na` (47 tables)
    pub fn new(mes: &'a [u8], dat: &'a [u8]) -> Option<Self> {
        let me = RegFile::new(mes);
        let da = RegFile::new(dat);
        if mes.len() < 8 || dat.len() < 8 || da.count() != 37 || me.count() != 47 {
            return None;
        }
        Some(UsRegDat { mes: me, dat: da })
    }

    /// `true` when `dat` looks like a retail `sshdat` (37 tables) instead of the demo's (33).
    pub fn is_retail_dat(dat: &[u8]) -> bool {
        dat.len() >= 8 && RegFile::new(dat).count() == 37
    }

    /// Byte offset (into `sshdat`) of the record `GetRegDat(kind, index, sub)` returns, kinds `0x2f..=0x53`.
    pub fn rec_offset(&self, kind: u8, index: usize, sub: i32) -> Option<usize> {
        let k = US_DATA_KINDS.get(kind.checked_sub(US_FIRST_DATA_KIND)? as usize)?;
        let t = self.dat.entry(k.file as usize);
        if !k.jagged {
            return Some(t + index * k.stride as usize);
        }
        let off = rd_u32(self.dat.bytes, t + index * 8)? as usize;
        let mut p = t + off;
        if sub > 0 {
            let stride = if kind == 0x3c { us_skill_stride(index as u32) } else { k.stride as usize };
            // kinds 0x30 / 0x31 / 0x33 / 0x47 skip `sub - 1` rows, 0x3c skips `sub` rows
            let rows = if kind == 0x3c { sub as usize } else { sub as usize - 1 };
            p += rows * stride;
        }
        Some(p)
    }

    /// The record bytes (`stride` long; for jagged tables the row at `sub`).
    pub fn record(&self, kind: u8, index: usize, sub: i32) -> Option<&'a [u8]> {
        let k = US_DATA_KINDS.get(kind.checked_sub(US_FIRST_DATA_KIND)? as usize)?;
        let o = self.rec_offset(kind, index, sub)?;
        let stride = if kind == 0x3c { us_skill_stride(index as u32) } else { k.stride as usize };
        self.dat.bytes.get(o..o + stride)
    }

    /// Number of records (plain tables: file size / stride; jagged tables: the `count` of the header row of `index`).
    pub fn count(&self, kind: u8, index: usize) -> Option<usize> {
        let k = US_DATA_KINDS.get(kind.checked_sub(US_FIRST_DATA_KIND)? as usize)?;
        let t = self.dat.entry(k.file as usize);
        if k.jagged {
            return Some(rd_u32(self.dat.bytes, t + index * 8 + 4)? as usize);
        }
        Some(self.dat.size(k.file as usize) / k.stride as usize)
    }

    fn mes_entry(&self, table: u8) -> usize {
        self.mes.entry(table as usize)
    }

    /// Offset (into `sshmes`) of the string `GetRegDat(kind, index, sub)` returns for kinds `0x00..=0x2e`.
    pub fn string_offset(&self, kind: u8, index: usize, sub: i32) -> Option<usize> {
        let b = self.dat.bytes;
        let m = self.mes.bytes;
        match kind {
            0x09 | 0x1f => {
                // SKIL: `sub < 0` indexes the message table directly, otherwise the jagged data row picks the message
                let (name, mes) = if kind == 0x09 { (true, 9u8) } else { (false, 0x1f) };
                let idx = if sub < 0 {
                    index
                } else {
                    let row = self.rec_offset(0x3c, index, sub)?;
                    rd_u16(b, row + if name { 2 } else { 0x3e })? as usize
                };
                let base = self.mes_entry(mes);
                if name {
                    Some(base + idx * 0x12)
                } else {
                    Some(base + rd_u32(m, base + idx * 4)? as usize)
                }
            }
            0x25 => {
                // tarot description: `sub` 0..=3 picks one of four u16 fields of the BTL_ table (file 34) rows, else the TARO row
                let (f, o, base) = match sub {
                    3 => (34, 0x70c, 0x2b),
                    2 => (34, 0x704, 0x2b),
                    1 => (34, 0x6fc, 0x2b),
                    0 => (34, 0x6f4, 0x2b),
                    _ => (21, 6, 0x25),
                };
                let (stride, ix) = if sub >= 0 { (0x20, index) } else { (8, index) };
                let t = self.dat.entry(f);
                let idx = rd_u16(b, t + ix * stride + o)? as usize;
                let tb = self.mes_entry(base);
                Some(tb + rd_u32(m, tb + idx * 4)? as usize)
            }
            0x27 | 0x28 => {
                let tb = self.mes_entry(kind);
                if index < usize::MAX / 2 {
                    Some(tb + rd_u32(m, tb + index * 8 + 4)? as usize)
                } else {
                    Some(tb)
                }
            }
            0x29 => Some(self.mes_entry(0x29)),
            _ => {
                let k = US_NAME_KINDS.get(kind as usize).copied().flatten()?;
                let rec = self.dat.entry(k.dat_file as usize) + index * k.stride as usize + k.field as usize;
                let idx = if k.byte {
                    *b.get(rec)? as usize
                } else if k.signed {
                    (rd_u16(b, rec)? as i16) as isize as usize
                } else {
                    rd_u16(b, rec)? as usize
                };
                let tb = self.mes_entry(k.mes);
                match k.style {
                    UsStr::Name => Some(tb + idx * 0x12),
                    UsStr::Desc => Some(tb + rd_u32(m, tb + idx * 4)? as usize),
                }
            }
        }
    }

    /// The string (without the terminating NUL) of a name / description kind.
    pub fn string(&self, kind: u8, index: usize, sub: i32) -> Option<&'a [u8]> {
        let o = self.string_offset(kind, index, sub)?;
        let s = self.mes.bytes.get(o..)?;
        let cap = if kind <= 0x17 || kind == 0x2a { 0x12 } else { s.len() };
        let end = s.iter().take(cap).position(|&c| c == 0).unwrap_or(cap.min(s.len()));
        Some(&s[..end])
    }

    /// [`UsRegDat::string`] as text (ASCII + latin-1; the retail strings are plain 8 bit).
    pub fn text(&self, kind: u8, index: usize, sub: i32) -> Option<String> {
        self.string(kind, index, sub).map(|s| s.iter().map(|&c| c as char).collect())
    }

    /// Translate a demo (`JP`) name kind into the retail kind that returns the same thing (names of PCs, monsters, weapons ... and
    /// the matching descriptions); `None` where the retail build has no counterpart.
    pub fn from_jp_name_kind(kind: u8) -> Option<u8> {
        Some(match kind {
            0..=3 => 0,
            4 => 1,
            5 => 2,
            6 => 3,
            7 => 4,
            8 => 5,
            9 => 6,
            0xa => 7,
            0xb => 8,
            0xc => 9,
            0xd => 0xa,
            0xe => 0xb,
            0xf => 0xc,
            0x10 => 0xd,
            0x11 => 0x10,
            0x12 => 0x11,
            0x13..=0x15 => kind - 1,
            0x16..=0x21 => kind + 2,
            0x22 => 0x26,
            _ => return None,
        })
    }

    /// Translate a demo record kind (0x26..=0x43) into the retail kind (record layouts that differ keep the retail layout:
    /// `MONSET`, `KEYI`, `YOAH`).
    pub fn from_jp_data_kind(kind: u8) -> Option<u8> {
        Some(match kind {
            0x26..=0x29 => 0x2f, // PC_I per difficulty -> the single PC_I
            0x2a => 0x30,
            0x2b => 0x31,
            0x2c => 0x32,
            0x2d => 0x33,
            0x2e => 0x34,
            0x2f => 0x35,
            0x30 => 0x36,
            0x31 => 0x37,
            0x32 => 0x38,
            0x33 => 0x39,
            0x34 => 0x3a,
            0x35 => 0x3b,
            0x36 => 0x3c,
            0x37 => 0x3d,
            0x38 => 0x3e,
            0x39 => 0x3f,
            0x3a => 0x40,
            0x3b => 0x41,
            0x3c => 0x42,
            0x3d => 0x43,
            0x3e => 0x46,
            0x3f => 0x47,
            0x40 => 0x48,
            0x41..=0x43 => kind + 8,
            _ => return None,
        })
    }
}

/// Build a container (`{u32 count, u32 total, {tag, off}[count], data...}`) from `(tag, bytes)` sections.
fn build_container(sections: &[([u8; 4], Vec<u8>)]) -> Vec<u8> {
    let head = 8 + sections.len() * 8;
    let mut out = vec![0u8; head];
    out[0..4].copy_from_slice(&(sections.len() as u32).to_le_bytes());
    let mut offs = Vec::new();
    for (_, data) in sections {
        while out.len() % 4 != 0 {
            out.push(0);
        }
        offs.push(out.len());
        out.extend_from_slice(data);
    }
    while out.len() % 4 != 0 {
        out.push(0);
    }
    let total = out.len() as u32;
    out[4..8].copy_from_slice(&total.to_le_bytes());
    for (i, (tag, _)) in sections.iter().enumerate() {
        out[8 + i * 8..12 + i * 8].copy_from_slice(tag);
        out[12 + i * 8..16 + i * 8].copy_from_slice(&(offs[i] as u32).to_le_bytes());
    }
    out
}

/// Retail `sshdat.na` re-laid out as the demo's `sshdat.jpn` (33 sections), so the code written against the demo's section numbers
/// (`sh2_battle::data::SEC_*`, `RegDat` kinds 0x26..0x43) runs on retail data unchanged.  The four per-difficulty `PC_I` / `FUSM`
/// tables all become the single retail table, `MONSET` rows are narrowed from `{id, formation, monsters[6], u32 flags}` (0x14) to the
/// demo's `{formation, monsters[6], u16 flags}` (0x10); `KEYI` (0x10 B) and `YOAH` (0x18 B) keep the retail row size.
pub fn us_dat_as_jp(us_dat: &[u8]) -> Option<Vec<u8>> {
    let f = RegFile::new(us_dat);
    if f.count() != 37 {
        return None;
    }
    const MAP: [usize; 33] = [0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 23, 24, 25, 26, 27, 28];
    let mut secs: Vec<([u8; 4], Vec<u8>)> = Vec::new();
    for (jp, &us) in MAP.iter().enumerate() {
        let off = f.entry(us);
        let mut data = us_dat.get(off..off + f.size(us))?.to_vec();
        if jp == 12 {
            let mut out = Vec::new();
            for row in data.chunks_exact(0x14) {
                out.extend_from_slice(&row[2..4]); // formation
                out.extend_from_slice(&row[4..16]); // monsters[6]
                out.extend_from_slice(&row[0x10..0x12]); // flags (low half)
            }
            out.extend_from_slice(&[0; 4]);
            data = out;
        }
        secs.push((f.tag(us), data));
    }
    Some(build_container(&secs))
}

/// Retail `sshmes.na` re-laid out as the demo's `sshmes.jpn` (44 sections of 0x12 byte names, then 0x50 byte description rows
/// synthesised from the retail offset-indexed strings, cut at 0x4f characters).
pub fn us_mes_as_jp(us_mes: &[u8]) -> Option<Vec<u8>> {
    let f = RegFile::new(us_mes);
    if f.count() != 47 {
        return None;
    }
    // demo section -> retail section; names first (0..=24), descriptions after (25..=43)
    const MAP: [usize; 44] = [
        0, 0, 0, 0, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 17, 18, 19, 20, // names
        24, 24, 24, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 38, 39, 40, 41, // descriptions
    ];
    let mut secs: Vec<([u8; 4], Vec<u8>)> = Vec::new();
    for (jp, &us) in MAP.iter().enumerate() {
        let off = f.entry(us);
        let raw = us_mes.get(off..off + f.size(us))?;
        let data = if jp < 25 {
            raw.to_vec()
        } else {
            // description table: u32 offsets (relative to the table) then strings; count = first offset / 4
            let n = if raw.len() >= 4 { (u32::from_le_bytes(raw[0..4].try_into().ok()?) as usize / 4).min(raw.len() / 4) } else { 0 };
            let plausible = n > 0 && n < 4096 && (0..n).all(|i| (u32::from_le_bytes(raw[i * 4..i * 4 + 4].try_into().unwrap()) as usize) <= raw.len());
            let mut out = Vec::new();
            if plausible {
                for i in 0..n {
                    let o = u32::from_le_bytes(raw[i * 4..i * 4 + 4].try_into().unwrap()) as usize;
                    let s = &raw[o..];
                    let l = s.iter().position(|&c| c == 0).unwrap_or(s.len()).min(0x4f);
                    let mut row = [0u8; 0x50];
                    row[..l].copy_from_slice(&s[..l]);
                    out.extend_from_slice(&row);
                }
            }
            out
        };
        secs.push((f.tag(us), data));
    }
    Some(build_container(&secs))
}

impl<'a> RegDat<'a> {
    /// `true` when the loaded files are the retail `sshdat.na` / `sshmes.na`.
    pub fn is_retail(&self) -> bool {
        self.dat.count() == 37
    }

    /// Like [`RegDat::name`] but understands both builds: with retail data the demo name kind is translated
    /// ([`UsRegDat::from_jp_name_kind`]) and the offset of the retail string is returned.  Used by the callers that were written
    /// against the demo's kind numbers (`GetFieldData(0x1c)`, treasure messages).
    pub fn name_any(&self, kind: u8, index: u32, level: u8) -> Option<usize> {
        if self.is_retail() {
            let us = UsRegDat { mes: self.mes, dat: self.dat };
            us.string_offset(UsRegDat::from_jp_name_kind(kind)?, index as usize, -1)
        } else {
            self.name(kind, index, level)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn heap_split_and_release() {
        let mut h = RegHeap::new();
        let a = h.set_data(&[1; 100], TAG_MES).unwrap();
        let b = h.set_data(&[2; 40], TAG_DAT).unwrap();
        assert!(b != a);
        assert!(h.check());
        h.release(TAG_MES);
        assert!(!h.check());
        // freed block can be reused
        let c = h.set_data(&[3; 100], *b"tmp0").unwrap();
        assert_eq!(h.find(*b"tmp0").unwrap()[0], 3);
        let _ = c;
    }

    #[test]
    fn regfile_layout() {
        // two tables: [0x20..0x30) and [0x30..0x38)
        let mut v = vec![0u8; 0x38];
        v[0..4].copy_from_slice(&2u32.to_le_bytes());
        v[4..8].copy_from_slice(&0x38u32.to_le_bytes());
        v[8..12].copy_from_slice(b"AAAA");
        v[12..16].copy_from_slice(&0x20u32.to_le_bytes());
        v[16..20].copy_from_slice(b"BBBB");
        v[20..24].copy_from_slice(&0x30u32.to_le_bytes());
        let f = RegFile::new(&v);
        assert_eq!(f.size(0), 0x10);
        assert_eq!(f.size(1), 8);
        assert_eq!(&f.tag(1), b"BBBB");
    }

    #[test]
    fn real_regdat_if_available() {
        let Ok(dir) = std::env::var("SH2_DISC_DIR") else { return };
        let disc = crate::fileio::Disc::open(&dir).unwrap();
        let mes = disc.read("common/sshmes.jpn").unwrap();
        let dat = disc.read("common/sshdat.jpn").unwrap();
        let r = RegDat::new(&mes, &dat);
        assert_eq!(r.dat.count(), 33);
        assert_eq!(r.mes.count(), 44);
        // table 0 (PC info): 12 records of 0x1c bytes (+4 byte trailer); names are Shift-JIS, 0x12 bytes wide
        assert_eq!(r.cnt_data(0x26, -1, 0), Some(12));
        assert_eq!(r.dat.size(0), 12 * 0x1c + 4);
        let n0 = r.mes.entry(0);
        assert_eq!(&r.mes.bytes[n0..n0 + 6], &[0x83, 0x4a, 0x83, 0x8c, 0x83, 0x93]); // "\u30ab\u30ec\u30f3" (Karin)
    }

    fn us_files() -> Option<(Vec<u8>, Vec<u8>)> {
        let dir = std::env::var("SH2_US_DISC_DIR").ok()?;
        let disc = crate::fileio::Disc::open(&dir).ok()?;
        Some((disc.read("common/sshmes.na").ok()?, disc.read("common/sshdat.na").ok()?))
    }

    #[test]
    fn real_us_regdat_kinds() {
        let Some((mes, dat)) = us_files() else { return };
        let r = UsRegDat::new(&mes, &dat).expect("37 / 47 tables");
        assert!(UsRegDat::is_retail_dat(&dat));
        // names (kinds 0..0x17: 0x12 byte rows)
        assert_eq!(r.text(0, 5, -1).unwrap(), "Karin");
        assert_eq!(r.text(0, 11, -1).unwrap(), "Nicolai");
        assert_eq!(r.text(2, 0, -1).unwrap(), "Revenant");
        assert_eq!(r.text(6, 0, -1).unwrap(), "Thera Leaf");
        assert_eq!(r.text(6, 32, -1).unwrap(), "Tent");
        assert_eq!(r.text(3, 0, -1).unwrap(), "Galahad's Sword");
        // descriptions (kinds 0x18..: offset tables, `$` = line break)
        assert_eq!(r.text(0x1c, 0, -1).unwrap(), "Restores 75 HP.");
        // records: PC_I of Karin (level 1) and Nicolai (level 2), MONSTERParam of the Revenant, the tutorial monster set
        let karin = r.record(0x2f, 5, -1).unwrap();
        assert_eq!((karin[0], karin[6]), (5, 1));
        assert_eq!(r.record(0x2f, 11, -1).unwrap()[6], 2);
        let mon = r.record(US_KIND_MONSTER, 0, -1).unwrap();
        assert_eq!((u16::from_le_bytes([mon[6], mon[7]]), u16::from_le_bytes([mon[10], mon[11]])), (17, 20));
        let set = r.record(US_KIND_MONSET, 0, -1).unwrap();
        assert_eq!(set.len(), 0x14);
        assert_eq!(&set[..4], &[0, 0, 6, 0]); // id 0, formation 6 (4 monsters)
        assert_eq!(&set[4..12], &[0; 8]); // four Revenants
        assert_eq!(r.count(US_KIND_MONSET, 0), Some(327));
        assert_eq!(r.count(US_KIND_MONSTER, 0), Some(224));
        // SCEN (starting inventory): scene 0 has 8 rows, the first gives 8 Thera Leaves
        assert_eq!(r.count(US_KIND_SCEN, 0), Some(8));
        assert_eq!(r.record(US_KIND_SCEN, 0, 1).unwrap(), &[1, 8, 0, 0]);
        // demo kinds map onto the retail ones
        assert_eq!(UsRegDat::from_jp_data_kind(0x2f), Some(US_KIND_MONSET));
        assert_eq!(UsRegDat::from_jp_name_kind(9), Some(6));
        let rd = RegDat::new(&mes, &dat);
        assert!(rd.is_retail());
        let off = rd.name_any(9, 0, 0).unwrap();
        assert_eq!(&mes[off..off + 10], b"Thera Leaf");
    }

    #[test]
    fn real_us_regdat_as_jp_layout() {
        let Some((mes, dat)) = us_files() else { return };
        let jd = us_dat_as_jp(&dat).unwrap();
        let jm = us_mes_as_jp(&mes).unwrap();
        let (d, m) = (RegFile::new(&jd), RegFile::new(&jm));
        assert_eq!((d.count(), m.count()), (33, 44));
        // MON_ params stay 0x38 byte rows at section 11, MONSET narrowed to 0x10 byte rows at section 12
        assert_eq!(&d.tag(11), b"MON_");
        assert_eq!(d.size(11) / 0x38, 224);
        assert_eq!(d.size(12) / 0x10, 327);
        let r0 = &jd[d.entry(12)..d.entry(12) + 16];
        assert_eq!(u16::from_le_bytes([r0[0], r0[1]]), 6); // formation
        assert_eq!(&r0[2..14], &[0u8; 12][..12].iter().enumerate().map(|(i, _)| if i < 8 { 0 } else { 0xff }).collect::<Vec<u8>>()[..]);
        // names where the demo keeps them: section 9 = weapons, 12 = items, 3 = PC names
        let name = |sec: usize, i: usize| {
            let b = &jm[m.entry(sec) + i * 0x12..m.entry(sec) + (i + 1) * 0x12];
            String::from_utf8_lossy(&b[..b.iter().position(|&c| c == 0).unwrap_or(0x12)]).to_string()
        };
        assert_eq!(name(12, 0), "Thera Leaf");
        assert_eq!(name(9, 1), "Rusty Fang");
        assert_eq!(name(3, 5), "Karin");
        // descriptions: fixed 0x50 rows
        assert_eq!(&jm[m.entry(32)..m.entry(32) + 15], b"Restores 75 HP.");
    }
}

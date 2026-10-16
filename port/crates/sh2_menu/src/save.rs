//! Save-file formats of Shadow Hearts: Covenant (JP demo build **and** US retail).
//!
//! Ports `SaveData` / `SaveDataSection` / `BtlSaveSec` / `CFieldSaveData` /
//! `SaveMenuSection` / `SystemFile`. See `notes/F/save_format.md` (demo) and
//! `notes/integration/save_retail.md` (retail, validated against a real memory-card save) for the field tables.
//! Everything here is pure data (no I/O): feed it the bytes of a `SH2-%03d` slot file
//! or of the system file (`BISLPM-00000-SH2` demo, `BASLUS-21041-SH2` retail).
//!
//! # Two builds, one in-memory shape
//!
//! The demo (`SLPM_602.19`) and the retail (`SLUS_210.41`) `BTL0` sections differ (0x1d44 vs 0x21bc bytes, version 0 vs 4; retail
//! party records start at +0x3c, the bag arrays at +0xabc, key items / obtained bit sets / misc flag words exist).  Every other crate
//! (battle, field menu pages) indexes [`BtlSave::data`] with the demo constants (`OFF_ITEMS` ...), so the **working copy stays
//! demo-shaped** and [`BtlSave::retail`] carries the authoritative retail block next to it: loading a retail file maps the shared
//! fields (party records, bag arrays, skill bit sets, flags, fusion monsters) into `data`, saving maps them back over `retail`
//! and writes the 0x21bc block, so a retail save written by the port is byte-identical to the game's own for every field the port
//! models and preserves everything else verbatim.

use thiserror::Error;

/// `sm_folder__10SaveDevice` (JP demo). Directory on the memory card.
pub const SAVE_FOLDER: &str = "BISLPM-00000-SH2";
/// US retail folder (rodata 0x00434050 of `SLUS_210.41`; the system file inside has the same name).
pub const SAVE_FOLDER_RETAIL: &str = "BASLUS-21041-SH2";
/// `sm_slotName__10SaveDevice` printf template.
pub const SLOT_FILE_FMT: &str = "SH2-";
pub const SLOT_COUNT: usize = 15;
pub const SAVE_MAGIC: [u8; 8] = *b"SSH_SAVE";
pub const SYSTEM_MAGIC: [u8; 4] = *b"SYSH";

pub const SAVE_HDR_SIZE: usize = 0x20;
pub const SECTION_HDR_SIZE: usize = 0x10;
pub const BTL_SIZE: usize = 0x1d44;
/// US retail `BTL0` size (`memcpy(ourBtlSaveDat, data, 0x21bc)` in `BtlSaveSec::SetSection`, section version 4).
pub const BTL_SIZE_RETAIL: usize = 0x21bc;
pub const BTL_VERSION_RETAIL: u16 = 4;
pub const FLD_SIZE: usize = 0xa2 * 16;
pub const MENU_SIZE: usize = 0x400;
/// Total slot file size: 0x20 + 3 headers + 3 payloads = 0x2bb4.
pub const SAVE_FILE_SIZE: usize =
    SAVE_HDR_SIZE + 3 * SECTION_HDR_SIZE + BTL_SIZE + FLD_SIZE + MENU_SIZE;
/// Retail slot file: 0x20 + 3 * 0x10 + 0x21bc + 0xa20 + 0x400 = 0x302c (the real card file is 12332 bytes).
pub const SAVE_FILE_SIZE_RETAIL: usize =
    SAVE_HDR_SIZE + 3 * SECTION_HDR_SIZE + BTL_SIZE_RETAIL + FLD_SIZE + MENU_SIZE;

/// Which executable's layout a save follows.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum Build {
    /// JP Furokuban demo (`SLPM_602.19`)
    #[default]
    Demo,
    /// US retail (`SLUS_210.41`)
    Retail,
}

impl Build {
    /// The build the running process models (`--us` -> `Retail`).
    pub fn current() -> Build {
        if sh2_core::boot::is_retail() { Build::Retail } else { Build::Demo }
    }
    pub fn is_retail(self) -> bool {
        self == Build::Retail
    }
    /// Memory-card folder (and name of the system file inside it).
    pub fn folder(self) -> &'static str {
        match self {
            Build::Demo => SAVE_FOLDER,
            Build::Retail => SAVE_FOLDER_RETAIL,
        }
    }
    pub fn btl_size(self) -> usize {
        match self {
            Build::Demo => BTL_SIZE,
            Build::Retail => BTL_SIZE_RETAIL,
        }
    }
    pub fn btl_version(self) -> u16 {
        match self {
            Build::Demo => 0,
            Build::Retail => BTL_VERSION_RETAIL,
        }
    }
    pub fn file_size(self) -> usize {
        match self {
            Build::Demo => SAVE_FILE_SIZE,
            Build::Retail => SAVE_FILE_SIZE_RETAIL,
        }
    }
    /// Party sets of `MENU` (retail `FUN_00287130` fills 7 sets from +0x84 up to +0x164, the demo block only 5).
    pub fn party_sets(self) -> usize {
        match self {
            Build::Demo => 5,
            Build::Retail => 7,
        }
    }
}

/// Folder name of the active build (see [`Build::folder`]).
pub fn folder_name() -> &'static str {
    Build::current().folder()
}

pub const SYSTEM_FILE_SIZE: usize = 0x6c0;
pub const SYSTEM_COMMON_SIZE: usize = 0x100;
pub const SLOT_INFO_SIZE: usize = 0x60;

pub const PC_COUNT: usize = 12;
pub const PC_REC_BASE: usize = 0x44;
pub const PC_REC_SIZE: usize = 0xc0;

#[derive(Debug, Error)]
pub enum SaveError {
    #[error("file too short: need {need:#x} bytes, have {have:#x}")]
    TooShort { need: usize, have: usize },
    #[error("bad magic")]
    BadMagic,
    #[error("section {0:?} has unsupported version {1}")]
    BadVersion(String, u16),
    #[error("section {0:?} is malformed")]
    BadSection(String),
    #[error("required section {0} missing")]
    MissingSection(&'static str),
}

pub type Result<T> = std::result::Result<T, SaveError>;

// ---------------------------------------------------------------- helpers

fn rd_u16(b: &[u8], o: usize) -> u16 {
    u16::from_le_bytes([b[o], b[o + 1]])
}
fn rd_u32(b: &[u8], o: usize) -> u32 {
    u32::from_le_bytes([b[o], b[o + 1], b[o + 2], b[o + 3]])
}
fn wr_u16(b: &mut [u8], o: usize, v: u16) {
    b[o..o + 2].copy_from_slice(&v.to_le_bytes());
}
fn wr_u32(b: &mut [u8], o: usize, v: u32) {
    b[o..o + 4].copy_from_slice(&v.to_le_bytes());
}

/// JP: 0x003280c0 SetCRC__8SaveDataFPUcUi — the game's "CRC" is an additive byte sum
/// over `buf[4..len]`, stored in `buf[0..4]`.
pub fn compute_checksum(buf: &[u8], len: usize) -> u32 {
    buf[4..len.min(buf.len())]
        .iter()
        .fold(0u32, |a, &b| a.wrapping_add(b as u32))
}

/// JP: 0x003280c0 SetCRC__8SaveDataFPUcUi
pub fn set_checksum(buf: &mut [u8], len: usize) {
    let c = compute_checksum(buf, len);
    wr_u32(buf, 0, c);
}

/// JP: 0x00328170 CheckCRC__8SaveDataFPUcUi — the original always returns 1; this
/// helper actually verifies, for tooling only.
pub fn verify_checksum(buf: &[u8], len: usize) -> bool {
    rd_u32(buf, 0) == compute_checksum(buf, len)
}

/// NUL-terminated byte string -> lossy UTF-8 (names are Shift-JIS; TODO decode).
pub fn cstr_lossy(b: &[u8]) -> String {
    let end = b.iter().position(|&c| c == 0).unwrap_or(b.len());
    String::from_utf8_lossy(&b[..end]).into_owned()
}

// ------------------------------------------------------------- generic container

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct SectionHdr {
    pub name: [u8; 4],
    pub hdr_size: u16,
    pub version: u16,
    pub size: u32,
    pub aux: u32,
}

impl SectionHdr {
    pub fn name_str(&self) -> String {
        String::from_utf8_lossy(&self.name).into_owned()
    }
    fn parse(b: &[u8]) -> Self {
        SectionHdr {
            name: [b[0], b[1], b[2], b[3]],
            hdr_size: rd_u16(b, 4),
            version: rd_u16(b, 6),
            size: rd_u32(b, 8),
            aux: rd_u32(b, 0xc),
        }
    }
    fn write(&self, out: &mut Vec<u8>) {
        out.extend_from_slice(&self.name);
        out.extend_from_slice(&self.hdr_size.to_le_bytes());
        out.extend_from_slice(&self.version.to_le_bytes());
        out.extend_from_slice(&self.size.to_le_bytes());
        out.extend_from_slice(&self.aux.to_le_bytes());
    }
}

#[derive(Debug, Clone)]
pub struct RawSection {
    pub hdr: SectionHdr,
    pub data: Vec<u8>,
}

/// JP: 0x003283d0 CreateSection__8SaveDataFP12_SaveDataHdr — parse the container.
pub fn parse_container(buf: &[u8]) -> Result<(u32, Vec<RawSection>)> {
    if buf.len() < SAVE_HDR_SIZE {
        return Err(SaveError::TooShort { need: SAVE_HDR_SIZE, have: buf.len() });
    }
    if buf[4..12] != SAVE_MAGIC {
        return Err(SaveError::BadMagic);
    }
    let checksum = rd_u32(buf, 0);
    let hdr_size = rd_u16(buf, 0x16) as usize;
    let payload = rd_u32(buf, 0x18) as usize;
    let count = rd_u16(buf, 0x1c) as usize;
    if buf.len() < hdr_size + payload {
        return Err(SaveError::TooShort { need: hdr_size + payload, have: buf.len() });
    }
    let mut off = hdr_size;
    let mut out = Vec::with_capacity(count);
    for _ in 0..count {
        if off + SECTION_HDR_SIZE > buf.len() {
            return Err(SaveError::TooShort { need: off + SECTION_HDR_SIZE, have: buf.len() });
        }
        let h = SectionHdr::parse(&buf[off..]);
        let ds = off + h.hdr_size as usize;
        let de = ds + h.size as usize;
        if h.hdr_size < SECTION_HDR_SIZE as u16 || de > buf.len() {
            return Err(SaveError::BadSection(h.name_str()));
        }
        out.push(RawSection { hdr: h.clone(), data: buf[ds..de].to_vec() });
        off = de;
    }
    Ok((checksum, out))
}

// ------------------------------------------------------------------ BTL0

/// One playable-character record (0xc0 bytes) inside `BTL0`.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct PcRec {
    pub flags: u8,
    pub kind: u8,
    pub level: u8,
    pub model_nums: [u16; 3],
    pub name: Vec<u8>,
    pub hp_max: u16,
    pub hp: u16,
    pub mp_max: u16,
    pub mp: u16,
    pub sp_max: u8,
    pub sp: u8,
    pub str_: u8,
    pub vit: u8,
    pub int: u8,
    pub pow: u8,
    pub agl: u8,
    pub luc: u8,
    pub stat_2c: u8,
    pub weapon: i8,
    pub armor: i8,
    pub accessories: [i8; 3],
    pub skills: [i8; 8],
    pub misc16: u16,
    pub exp: u32,
    /// Raw record bytes (authoritative; typed fields are views).
    pub raw: [u8; PC_REC_SIZE],
}

impl PcRec {
    pub fn present(&self) -> bool {
        self.flags & 1 != 0
    }
    pub fn joined(&self) -> bool {
        self.flags & 2 != 0
    }
    pub fn name_lossy(&self) -> String {
        cstr_lossy(&self.name)
    }
    pub fn parse(b: &[u8]) -> Self {
        let mut raw = [0u8; PC_REC_SIZE];
        raw.copy_from_slice(&b[..PC_REC_SIZE]);
        PcRec {
            flags: b[0],
            kind: b[2],
            level: b[3],
            model_nums: [rd_u16(b, 4), rd_u16(b, 6), rd_u16(b, 8)],
            name: b[0x0a..0x1c].to_vec(),
            hp_max: rd_u16(b, 0x1c),
            hp: rd_u16(b, 0x1e),
            mp_max: rd_u16(b, 0x20),
            mp: rd_u16(b, 0x22),
            sp_max: b[0x24],
            sp: b[0x25],
            str_: b[0x26],
            vit: b[0x27],
            int: b[0x28],
            pow: b[0x29],
            agl: b[0x2a],
            luc: b[0x2b],
            stat_2c: b[0x2c],
            weapon: b[0x2d] as i8,
            armor: b[0x2e] as i8,
            accessories: [b[0x2f] as i8, b[0x30] as i8, b[0x31] as i8],
            skills: [
                b[0x32] as i8, b[0x33] as i8, b[0x34] as i8, b[0x35] as i8,
                b[0x36] as i8, b[0x37] as i8, b[0x38] as i8, b[0x39] as i8,
            ],
            misc16: rd_u16(b, 0x3a),
            exp: rd_u32(b, 0x3c),
            raw,
        }
    }
    /// Write typed fields back over the raw bytes and return the record.
    pub fn to_bytes(&self) -> [u8; PC_REC_SIZE] {
        let mut b = self.raw;
        b[0] = self.flags;
        b[2] = self.kind;
        b[3] = self.level;
        for (i, m) in self.model_nums.iter().enumerate() {
            wr_u16(&mut b, 4 + i * 2, *m);
        }
        let n = self.name.len().min(0x12);
        b[0x0a..0x1c].fill(0);
        b[0x0a..0x0a + n].copy_from_slice(&self.name[..n]);
        wr_u16(&mut b, 0x1c, self.hp_max);
        wr_u16(&mut b, 0x1e, self.hp);
        wr_u16(&mut b, 0x20, self.mp_max);
        wr_u16(&mut b, 0x22, self.mp);
        b[0x24] = self.sp_max;
        b[0x25] = self.sp;
        b[0x26] = self.str_;
        b[0x27] = self.vit;
        b[0x28] = self.int;
        b[0x29] = self.pow;
        b[0x2a] = self.agl;
        b[0x2b] = self.luc;
        b[0x2c] = self.stat_2c;
        b[0x2d] = self.weapon as u8;
        b[0x2e] = self.armor as u8;
        for i in 0..3 {
            b[0x2f + i] = self.accessories[i] as u8;
        }
        for i in 0..8 {
            b[0x32 + i] = self.skills[i] as u8;
        }
        wr_u16(&mut b, 0x3a, self.misc16);
        wr_u32(&mut b, 0x3c, self.exp);
        b
    }
}

/// Offsets of the US retail `BTL0` block (`BtlSaveSec`, version 4, 0x21bc bytes; decompiled from `SLUS_210.41`:
/// `GetPCParam` 0x003c1bb0, `SetPCParam` 0x003c1d30, `FUN_003bfbe0` = `PCInit`, `FUN_003bc710` = `SetSceneInit`,
/// `FUN_003be870` = `AddEquip`, `FUN_003bf2d0 / 5c0` = item list cache, `FUN_003c02f0` = per-scene PC init).
pub mod retail_btl {
    /// u16 Soul Energy pool (`*ourBtlSaveDat`; the Graveyard soul charge `CmdRetailPage01` spends it; battles add to it, capped at 9999 by `BtlResult::Polling` SLUS 0x398190)
    pub const OFF_SOUL: usize = 0x000;
    /// u8 active bag (the retail "scenario": it also selects the cash slot, `SetCurrentCash` = `MENU[4 + bag*4]`)
    pub const OFF_BAG: usize = 0x002;
    /// u8 flags (bit0 combo menu `SetComboMenuMode`, bit1 / bit2 `FUN_003bc420 / 3f0`)
    pub const OFF_FLAGS: usize = 0x003;
    /// 12 party records of 0xc0 bytes (record layout = the demo's up to +0x58, see `session::retail_pc_fields`)
    pub const PC_BASE: usize = 0x03c;
    /// two bags of 0x200 bytes: u8[0x30] consumables
    pub const ITEMS: usize = 0xabc;
    pub const ITEM_COUNT: usize = 0x30;
    /// two u8[0x20] bit sets (item obtained / seen; `SetSceneInit` kind 10 sets bit `idx` of the first)
    pub const SEEN1: usize = 0xaec;
    pub const SEEN2: usize = 0xb0c;
    pub const WEAPONS: usize = 0xb2c;
    pub const WEAPON_COUNT: usize = 0x60;
    pub const ARMOR: usize = 0xb8c;
    pub const ARMOR_COUNT: usize = 0x30;
    pub const ACCESSORIES: usize = 0xbbc;
    pub const ACCESSORY_COUNT: usize = 0x60;
    /// u8[0xa] skill / crest bit sets (kind 5 of `SetSceneInit`; the "equipped ever" set follows)
    pub const SKILL1: usize = 0xc1c;
    pub const SKILL2: usize = 0xc26;
    /// u8[0x40] key items (`SetSceneInit` kind 6: Holy Mistletoe, Periapt, ...) -- the first three bytes are the demo's `+0xab8` counters
    pub const KEY_ITEMS: usize = 0xc30;
    pub const KEY_ITEM_COUNT: usize = 0x40;
    pub const BAG_STRIDE: usize = 0x200;
    /// flag byte: bit2 `FUN_003bc3c0` (soul system), bit3 alternate PC7 table (`SetPCParam`)
    pub const MISC_FLAGS: usize = 0xec0;
    /// u32[23] fusion monster experience, u8[23] fusion monster level
    pub const FUSION_EXP: usize = 0xec8;
    pub const FUSION_LV: usize = 0xf24;
    pub const FUSION_COUNT: usize = 23;
    /// kind 7: u16 bit set; kind 9: u8[3] bit set (bit `idx`); kind 8: u8 bit set
    pub const MISC7: usize = 0xf3c;
    pub const MISC9: usize = 0xf3f;
    pub const MISC8: usize = 0xf42;
    /// 12 x 0x10 ability slots (`{u8 kind, u8 idx, u16 id = 0xffff}` x 4)
    pub const SKILL_SLOTS: usize = 0x10bc;
    /// 0x40 x {s16 id, u16 count}: the sorted item list built by `FUN_003bf2d0` for the item menu
    pub const LIST_CACHE: usize = 0x20bc;
}

/// `BTL0` section.  `data` is the **demo-shaped working copy** every other crate indexes (0x1d44 bytes); `retail` is the real
/// retail block (empty for the demo build).  See the module docs.
#[derive(Debug, Clone)]
pub struct BtlSave {
    pub data: Vec<u8>,
    /// authoritative US retail block (0x21bc bytes) or empty; [`BtlSave::sync_to_retail`] refreshes the shared fields before saving
    pub retail: Vec<u8>,
}

impl BtlSave {
    pub const OFF_BAG: usize = 0x002;
    pub const OFF_FLAGS: usize = 0x003;
    pub const OFF_SCENARIO: usize = 0x004;
    pub const OFF_ITEMS: usize = 0x944;
    pub const OFF_ITEM_SEEN: usize = 0x984;
    pub const OFF_WEAPONS: usize = 0x9c4;
    pub const OFF_ARMOR: usize = 0xa24;
    pub const OFF_ACCESSORIES: usize = 0xa54;
    pub const OFF_SKILL_BITS: usize = 0xaa4;
    pub const OFF_SKILL_BITS2: usize = 0xaae;
    /// three stat-up counters, retail `KEY_ITEMS[0..3]`
    pub const OFF_COUNTERS: usize = 0xab8;
    pub const OFF_MISC_FLAGS: usize = 0xd48;
    pub const OFF_FUSMON_EXP: usize = 0xd50;
    pub const OFF_FUSMON_LV: usize = 0xd94;
    pub const OFF_YOAHISM: usize = 0xe38;
    pub const BAG_STRIDE: usize = 0x200;

    /// JP: 0x0037da10 SetDefault__10BtlSaveSecFv (zero part only; scene init is data driven)
    pub fn new_zeroed() -> Self {
        BtlSave { data: vec![0; BTL_SIZE], retail: Vec::new() }
    }
    /// A fresh retail block: zeroed like `BtlSaveSec::SetDefault`'s `memset`, then the bag / flag bytes the first `SetSceneInit`
    /// leaves (live save of a new game: bag 1, `+0xec0 = 4`, `+0xfcc = 3`).  The flag byte stays 0: bit 0 (`SetComboMenuMode`, the battle
    /// Combo entry) is clear in the live game at the first fight of `AP_02_U` (read 2026-10-14) and is set later by the story.  The demo-shaped
    /// copy is derived from it.
    pub fn new_retail() -> Self {
        let mut raw = vec![0u8; BTL_SIZE_RETAIL];
        raw[retail_btl::OFF_BAG] = 1;
        raw[retail_btl::MISC_FLAGS] = 4;
        raw[0xfcc] = 3;
        let mut s = BtlSave { data: vec![0; BTL_SIZE], retail: raw };
        s.sync_from_retail();
        s
    }
    /// Demo `BTL0` payload (0x1d44 bytes, extra bytes are dropped).
    pub fn from_section(data: &[u8]) -> Result<Self> {
        if data.len() < BTL_SIZE {
            return Err(SaveError::BadSection("BTL0".into()));
        }
        Ok(BtlSave { data: data[..BTL_SIZE].to_vec(), retail: Vec::new() })
    }
    /// Retail `BTL0` payload (0x21bc bytes): kept verbatim in [`BtlSave::retail`], shared fields mapped into `data`.
    pub fn from_retail_section(data: &[u8]) -> Result<Self> {
        if data.len() < BTL_SIZE_RETAIL {
            return Err(SaveError::BadSection("BTL0".into()));
        }
        let mut s = BtlSave { data: vec![0; BTL_SIZE], retail: data[..BTL_SIZE_RETAIL].to_vec() };
        s.sync_from_retail();
        Ok(s)
    }
    pub fn is_retail(&self) -> bool {
        !self.retail.is_empty()
    }
    pub fn build(&self) -> Build {
        if self.is_retail() { Build::Retail } else { Build::Demo }
    }

    /// (demo offset, retail offset, length) of the byte ranges shared by both layouts, per bag (`bag * 0x200` is added to both).
    const BAG_MAP: [(usize, usize, usize); 9] = [
        (Self::OFF_ITEMS, retail_btl::ITEMS, retail_btl::ITEM_COUNT),
        (Self::OFF_ITEM_SEEN, retail_btl::SEEN1, 0x20),
        (Self::OFF_ITEM_SEEN + 0x20, retail_btl::SEEN2, 0x20),
        (Self::OFF_WEAPONS, retail_btl::WEAPONS, retail_btl::WEAPON_COUNT),
        (Self::OFF_ARMOR, retail_btl::ARMOR, retail_btl::ARMOR_COUNT),
        (Self::OFF_ACCESSORIES, retail_btl::ACCESSORIES, 0x50),
        (Self::OFF_SKILL_BITS, retail_btl::SKILL1, 0xa),
        (Self::OFF_SKILL_BITS2, retail_btl::SKILL2, 0xa),
        (Self::OFF_COUNTERS, retail_btl::KEY_ITEMS, 3),
    ];

    /// Map the retail block into the demo-shaped working copy (the loader's half of the translation).
    pub fn sync_from_retail(&mut self) {
        if self.retail.is_empty() {
            return;
        }
        let r = &self.retail;
        let d = &mut self.data;
        d[..4].copy_from_slice(&r[..4]);
        // the retail "scenario" is the bag index (cash slot), stored as the demo's u32 at +4
        d[4..8].copy_from_slice(&(r[retail_btl::OFF_BAG] as u32).to_le_bytes());
        for i in 0..PC_COUNT {
            let (dr, rr) = (PC_REC_BASE + i * PC_REC_SIZE, retail_btl::PC_BASE + i * PC_REC_SIZE);
            d[dr..dr + PC_REC_SIZE].copy_from_slice(&r[rr..rr + PC_REC_SIZE]);
        }
        for bag in 0..2 {
            let bo = bag * Self::BAG_STRIDE;
            for &(dd, rr, n) in &Self::BAG_MAP {
                d[dd + bo..dd + bo + n].copy_from_slice(&r[rr + bo..rr + bo + n]);
            }
        }
        d[Self::OFF_MISC_FLAGS] = r[retail_btl::MISC_FLAGS];
        for i in 0..15 {
            let o = retail_btl::FUSION_EXP + i * 4;
            d[Self::OFF_FUSMON_EXP + i * 4..Self::OFF_FUSMON_EXP + i * 4 + 4].copy_from_slice(&r[o..o + 4]);
        }
        d[Self::OFF_FUSMON_LV..Self::OFF_FUSMON_LV + 17].copy_from_slice(&r[retail_btl::FUSION_LV..retail_btl::FUSION_LV + 17]);
    }

    /// Map the working copy over the retail block (the saver's half; fields the port does not model stay as loaded).
    pub fn sync_to_retail(&mut self) {
        if self.retail.is_empty() {
            return;
        }
        let d = &self.data;
        let r = &mut self.retail;
        r[..4].copy_from_slice(&d[..4]);
        for i in 0..PC_COUNT {
            let (dr, rr) = (PC_REC_BASE + i * PC_REC_SIZE, retail_btl::PC_BASE + i * PC_REC_SIZE);
            r[rr..rr + PC_REC_SIZE].copy_from_slice(&d[dr..dr + PC_REC_SIZE]);
        }
        for bag in 0..2 {
            let bo = bag * Self::BAG_STRIDE;
            for &(dd, rr, n) in &Self::BAG_MAP {
                r[rr + bo..rr + bo + n].copy_from_slice(&d[dd + bo..dd + bo + n]);
            }
        }
        r[retail_btl::MISC_FLAGS] = d[Self::OFF_MISC_FLAGS];
        for i in 0..15 {
            let o = retail_btl::FUSION_EXP + i * 4;
            r[o..o + 4].copy_from_slice(&d[Self::OFF_FUSMON_EXP + i * 4..Self::OFF_FUSMON_EXP + i * 4 + 4]);
        }
        r[retail_btl::FUSION_LV..retail_btl::FUSION_LV + 17].copy_from_slice(&d[Self::OFF_FUSMON_LV..Self::OFF_FUSMON_LV + 17]);
    }

    /// The section payload for `build` (retail: after [`sync_to_retail`](Self::sync_to_retail)).
    pub fn section_bytes(&mut self, build: Build) -> Vec<u8> {
        match build {
            Build::Demo => self.data.clone(),
            Build::Retail => {
                if self.retail.is_empty() {
                    // demo-shaped data written as a retail save: start from a fresh retail block
                    let fresh = BtlSave::new_retail();
                    self.retail = fresh.retail;
                }
                self.sync_to_retail();
                self.retail.clone()
            }
        }
    }

    pub fn bag(&self) -> u8 {
        self.data[Self::OFF_BAG]
    }
    /// Demo: u32 at +4 (selects the `MENU` cash slot); retail: the bag index (the loader derives it).
    pub fn scenario(&self) -> u32 {
        rd_u32(&self.data, Self::OFF_SCENARIO)
    }
    /// `BTL0+3` bit 0 (`BtlSaveSec::SetComboMenuMode`, set by the combo tutorial and `SceneInit`): the battle's main menu lists `Combo`
    /// (`SetMainMenu`, US BATTLE 0x5f6918 / 0x600ca0 `andi 1`; JP BtlMenu.c 10539).
    pub fn combo_menu_enabled(&self) -> bool {
        self.data[Self::OFF_FLAGS] & 1 != 0
    }
    /// round 6 MN3: `BTL0+3` bit 1, the **combo shortcut switch** as the battle sees it.  Every battle copies it from the menu's Combo Switch
    /// (`MENU+0x276 & 3 != 0`, US `BtlSocket::Polling` SLUS 0x365f30..0x365f84, JP BtlSocket.c 299) and reads it for the combo shortcut menu
    /// (mode 0x17: JP CBattle.c 3435 / 9461 / 11301) and the triangle shortcut setting (mode 0x18: US `BtlMenu::Polling` 0x5d2ffc / 0x5d5e04 /
    /// 0x5da0d4, `MainMenuFunc` 0x5e6d9c, all `dsll32 30 / dsrl32 31`).
    pub fn combo_shortcut_enabled(&self) -> bool {
        self.data[Self::OFF_FLAGS] & 2 != 0
    }
    /// `BTL0+3` bit 1 (US `BtlSaveSec` 0x3bc420, the setter the clear-data defaults call with 0).
    pub fn set_combo_shortcut(&mut self, on: bool) {
        let f = &mut self.data[Self::OFF_FLAGS];
        *f = (*f & !2) | ((on as u8) << 1);
    }
    pub fn soul_system_enabled(&self) -> bool {
        self.data[Self::OFF_FLAGS] & 4 != 0
    }
    pub fn yoahism_mode(&self) -> bool {
        self.data[Self::OFF_MISC_FLAGS] & 4 != 0
    }
    pub fn yoahism_counter(&self) -> u32 {
        rd_u32(&self.data, Self::OFF_YOAHISM)
    }
    pub fn pc(&self, i: usize) -> Option<PcRec> {
        if i >= PC_COUNT {
            return None;
        }
        let o = PC_REC_BASE + i * PC_REC_SIZE;
        Some(PcRec::parse(&self.data[o..o + PC_REC_SIZE]))
    }
    pub fn set_pc(&mut self, i: usize, rec: &PcRec) {
        let o = PC_REC_BASE + i * PC_REC_SIZE;
        self.data[o..o + PC_REC_SIZE].copy_from_slice(&rec.to_bytes());
    }
    fn bag_base(&self) -> usize {
        self.bag() as usize * Self::BAG_STRIDE
    }
    /// consumable item count (JP stores item kind 1 at +0x944).
    pub fn item_count(&self, idx: usize) -> u8 {
        self.data.get(Self::OFF_ITEMS + self.bag_base() + idx).copied().unwrap_or(0)
    }
    pub fn weapon_count(&self, idx: usize) -> u8 {
        self.data.get(Self::OFF_WEAPONS + self.bag_base() + idx).copied().unwrap_or(0)
    }
    pub fn armor_count(&self, idx: usize) -> u8 {
        self.data.get(Self::OFF_ARMOR + self.bag_base() + idx).copied().unwrap_or(0)
    }
    pub fn accessory_count(&self, idx: usize) -> u8 {
        self.data.get(Self::OFF_ACCESSORIES + self.bag_base() + idx).copied().unwrap_or(0)
    }
    pub fn skill_learned(&self, skill: usize) -> bool {
        self.data
            .get(Self::OFF_SKILL_BITS + self.bag_base() + (skill >> 3))
            .map(|b| b & (1 << (skill & 7)) != 0)
            .unwrap_or(false)
    }
    pub fn fusmon_exp(&self, i: usize) -> u32 {
        if i < 15 { rd_u32(&self.data, Self::OFF_FUSMON_EXP + i * 4) } else { 0 }
    }

    // ---- retail-only state (lives in `retail`; the accessors create a fresh block on first write)

    fn retail_mut(&mut self) -> &mut Vec<u8> {
        if self.retail.is_empty() {
            self.retail = BtlSave::new_retail().retail;
        }
        &mut self.retail
    }
    fn retail_bag_base(&self) -> usize {
        self.bag_base()
    }
    /// Key item count (`KeyItem` id `idx` of the active bag, 0..0x40): Holy Mistletoe, Periapt ... (`SetSceneInit` kind 6).
    pub fn key_item(&self, idx: usize) -> u8 {
        if idx >= retail_btl::KEY_ITEM_COUNT {
            return 0;
        }
        if idx < 3 {
            // the first three slots are the demo's `+0xab8` counters: live in the shared working copy
            return self.data[Self::OFF_COUNTERS + self.retail_bag_base() + idx];
        }
        let o = retail_btl::KEY_ITEMS + self.retail_bag_base() + idx;
        if self.retail.is_empty() { 0 } else { self.retail.get(o).copied().unwrap_or(0) }
    }
    pub fn set_key_item(&mut self, idx: usize, n: u8) {
        if idx >= retail_btl::KEY_ITEM_COUNT {
            return;
        }
        let bo = self.retail_bag_base();
        let o = retail_btl::KEY_ITEMS + bo + idx;
        if idx < 3 {
            self.data[Self::OFF_COUNTERS + bo + idx] = n.min(99);
            if self.retail.is_empty() {
                return; // demo build: the working copy is the whole save
            }
        }
        self.retail_mut()[o] = n.min(99);
    }
    /// Bit `idx` of the "item obtained" set (kind 10 of `SetSceneInit`), the demo-shaped `OFF_ITEM_SEEN` array.
    pub fn item_obtained(&self, idx: usize) -> bool {
        self.data.get(Self::OFF_ITEM_SEEN + self.bag_base() + (idx >> 3)).map(|b| b & (1 << (idx & 7)) != 0).unwrap_or(false)
    }
    pub fn set_item_obtained(&mut self, idx: usize) {
        let o = Self::OFF_ITEM_SEEN + self.bag_base() + (idx >> 3);
        if let Some(b) = self.data.get_mut(o) {
            *b |= 1 << (idx & 7);
        }
    }
    /// Skill / crest "obtained" bit set 1 (kind 5), same array as [`skill_learned`](Self::skill_learned).
    pub fn set_skill_learned(&mut self, skill: usize) {
        let o = Self::OFF_SKILL_BITS + self.bag_base() + (skill >> 3);
        if let Some(b) = self.data.get_mut(o) {
            *b |= 1 << (skill & 7);
        }
    }
    /// Misc flag words of `SetSceneInit` kinds 7 / 8 / 9 (u16 @0xf3c, u8 @0xf42, bit array @0xf3f).
    pub fn misc_flag(&self, kind: u8, bit: usize) -> bool {
        if self.retail.is_empty() {
            return false;
        }
        match kind {
            7 => bit < 16 && rd_u16(&self.retail, retail_btl::MISC7) & (1 << bit) != 0,
            8 => bit < 8 && self.retail[retail_btl::MISC8] & (1 << bit) != 0,
            9 => (bit >> 3) < 3 && self.retail[retail_btl::MISC9 + (bit >> 3)] & (1 << (bit & 7)) != 0,
            _ => false,
        }
    }
    pub fn set_misc_flag(&mut self, kind: u8, bit: usize) {
        let r = self.retail_mut();
        match kind {
            7 if bit < 16 => {
                let v = rd_u16(r, retail_btl::MISC7) | (1 << bit);
                wr_u16(r, retail_btl::MISC7, v);
            }
            8 if bit < 8 => r[retail_btl::MISC8] |= 1 << bit,
            9 if (bit >> 3) < 3 => r[retail_btl::MISC9 + (bit >> 3)] |= 1 << (bit & 7),
            _ => {}
        }
    }
    /// `SetSceneInit` row `(kind, index, value)` for the kinds the demo-shaped save has no slot for (5..=10); kinds 1..=4 are the bag arrays.
    pub fn apply_scene_row(&mut self, kind: u8, index: usize, value: u8) {
        match kind {
            5 => self.set_skill_learned(index),
            6 => self.set_key_item(index, value),
            7 | 8 | 9 => self.set_misc_flag(kind, index),
            10 => self.set_item_obtained(index),
            _ => {}
        }
    }
    /// Combo-key shortcut command `slot` (0..4) of party member `pc`: `(kind, id)` of the `SHORTCUTCommand {u8 kind, u8 button, u16 id}` row
    /// (demo `+0xf44 + pc * 0x10`, retail `+0x10bc + pc * 0x10`); `id == 0xffff` with kind 0 = the plain attack.
    pub fn shortcut(&self, pc: usize, slot: usize) -> (u8, u16) {
        if pc >= PC_COUNT || slot >= 4 {
            return (0, 0xffff);
        }
        let (buf, base) = if self.retail.is_empty() { (&self.data, 0xf44) } else { (&self.retail, retail_btl::SKILL_SLOTS) };
        let o = base + pc * 0x10 + slot * 4;
        (buf[o], rd_u16(buf, o + 2))
    }
    /// Byte 1 of a shortcut row: the default attack style of the slot (`CmdParty::ConvertComboKey(1)` copies it, sign extended, into an
    /// empty attack row's id: retail `ConvertComboKeyDefault`).
    pub fn shortcut_default(&self, pc: usize, slot: usize) -> i8 {
        if pc >= PC_COUNT || slot >= 4 {
            return -1;
        }
        let (buf, base) = if self.retail.is_empty() { (&self.data, 0xf44) } else { (&self.retail, retail_btl::SKILL_SLOTS) };
        buf.get(base + pc * 0x10 + slot * 4 + 1).map(|&b| b as i8).unwrap_or(-1)
    }
    pub fn set_shortcut(&mut self, pc: usize, slot: usize, kind: u8, id: u16) {
        if pc >= PC_COUNT || slot >= 4 {
            return;
        }
        let retail = !self.retail.is_empty();
        let (base, buf) = if retail { (retail_btl::SKILL_SLOTS, &mut self.retail) } else { (0xf44, &mut self.data) };
        let o = base + pc * 0x10 + slot * 4;
        buf[o] = kind;
        buf[o + 1] = slot as u8;
        wr_u16(buf, o + 2, id);
    }
    /// The combination-technique "known" word (`CmdComboMagic`: bit `i` shows the name of `COMB` record `i`; demo `+0xd44`, retail `+0xebc`).
    pub fn combo_flags(&self) -> u32 {
        if self.retail.is_empty() { rd_u32(&self.data, 0xd44) } else { rd_u32(&self.retail, 0xebc) }
    }
    pub fn set_combo_flags(&mut self, v: u32) {
        if self.retail.is_empty() {
            wr_u32(&mut self.data, 0xd44, v);
        } else {
            wr_u32(&mut self.retail, 0xebc, v);
        }
    }

    /// Monster library flags (`CmdLibrary::SetMonster`): bit sets indexed by `MONSTERParam` id.
    /// * "defeated" (demo `+0xdaf`, retail `+0xf43`): set for the monsters of every **won** battle (`BtlResult::Polling`, US 0x396fa0, and the
    ///   chained / no-result-screen paths of `BtlSocket::Polling` 0x3657b0; never on escape or defeat); the library lists an entry once one of
    ///   its monsters has it.
    /// * "snapped" (demo `+0xdcf`, retail `+0xf63`): Anastasia's Snap Shot photo (JP `BtlFree` command kind 6, which also sets per-monster
    ///   album bits at demo `+0xe2f`); the library's second mode needs it and `TargetInfo` (US BATTLE 0xc68d0) shows the large plate with
    ///   the monster's HP only while it is set **and** party member 4 (Anastasia) is in the battle.
    /// * the two-bit "knowledge" array (demo `+0xdef`, retail `+0xf83`), also written at the battle result (source list not identified).
    fn monster_bit_off(&self, which: usize) -> (bool, usize) {
        let (demo, retail) = [(0xdaf, 0xf43), (0xdcf, 0xf63), (0xdef, 0xf83)][which];
        if self.retail.is_empty() { (false, demo) } else { (true, retail) }
    }
    pub fn monster_defeated(&self, id: usize) -> bool {
        let (r, o) = self.monster_bit_off(0);
        let buf = if r { &self.retail } else { &self.data };
        buf.get(o + (id >> 3)).map(|b| b & (1 << (id & 7)) != 0).unwrap_or(false)
    }
    pub fn monster_snapped(&self, id: usize) -> bool {
        let (r, o) = self.monster_bit_off(1);
        let buf = if r { &self.retail } else { &self.data };
        buf.get(o + (id >> 3)).map(|b| b & (1 << (id & 7)) != 0).unwrap_or(false)
    }
    /// Two-bit knowledge level of monster `id` (0..3; which drops / weaknesses the library may show).
    pub fn monster_knowledge(&self, id: usize) -> u8 {
        let (r, o) = self.monster_bit_off(2);
        let buf = if r { &self.retail } else { &self.data };
        buf.get(o + (id >> 2)).map(|b| (b >> ((id & 3) * 2)) & 3).unwrap_or(0)
    }
    pub fn set_monster_defeated(&mut self, id: usize) {
        let (r, o) = self.monster_bit_off(0);
        let buf = if r { &mut self.retail } else { &mut self.data };
        if let Some(b) = buf.get_mut(o + (id >> 3)) {
            *b |= 1 << (id & 7);
        }
    }
    pub fn set_monster_snapped(&mut self, id: usize) {
        let (r, o) = self.monster_bit_off(1);
        let buf = if r { &mut self.retail } else { &mut self.data };
        if let Some(b) = buf.get_mut(o + (id >> 3)) {
            *b |= 1 << (id & 7);
        }
    }

    /// `PCInit` (`FUN_003bfbe0`) ability-slot rows of party member `pc`: 4 x `{kind 0, 0, id 0xffff}` with the second byte 0..3;
    /// PCs 9 / 10 / 8 skip one column (`0xff, 0xff`).  (PC 0 / 6 / 7 additionally fill larger ability tables at +0x11ec / +0x130c; not modelled.)
    pub fn init_pc_slots(&mut self, pc: usize) {
        if pc >= PC_COUNT {
            return;
        }
        let r = self.retail_mut();
        let o = retail_btl::SKILL_SLOTS + pc * 0x10;
        r[o] = 0;
        r[o + 1] = 0;
        wr_u16(r, o + 2, 0xffff);
        if pc == 9 || pc == 10 {
            r[o + 4] = 0xff;
            r[o + 5] = 0xff;
        } else {
            r[o + 4] = 0;
            r[o + 5] = 1;
        }
        wr_u16(r, o + 6, 0xffff);
        if pc == 8 || pc == 10 {
            r[o + 8] = 0xff;
            r[o + 9] = 0xff;
        } else {
            r[o + 8] = 0;
            r[o + 9] = 2;
        }
        wr_u16(r, o + 10, 0xffff);
        if pc == 8 || pc == 9 {
            r[o + 12] = 0xff;
            r[o + 13] = 0xff;
        } else {
            r[o + 12] = 0;
            r[o + 13] = 3;
        }
        wr_u16(r, o + 14, 0xffff);
    }
}

// ------------------------------------------------------------------ FLDa

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct FieldChunk {
    pub tag: [u8; 2],
    /// size in 16-byte units, includes the 4-byte chunk header
    pub units: u8,
    pub flag: u8,
    /// payload (after the 4-byte header) — `units * 16 - 4` bytes
    pub payload: Vec<u8>,
}

/// `FLDa` section: chunk list (`CFieldSaveData`).
#[derive(Debug, Clone, Default)]
pub struct FieldSave {
    pub chunks: Vec<FieldChunk>,
    /// header `aux` as loaded.  The retail game never clears it: `SetDefault` runs twice during boot, so real saves carry 10 for 5 chunks.
    /// `SetSection` walks `aux` chunks and the unused ones have size 0, so any value >= the chunk count loads; kept for byte-identical re-saving.
    pub aux: Option<u32>,
}

impl FieldSave {
    pub const TAG_GS: [u8; 2] = *b"GS";
    pub const TAG_RG: [u8; 2] = *b"RG";
    pub const TAG_TR: [u8; 2] = *b"TR";
    pub const TAG_WM: [u8; 2] = *b"WM";
    pub const TAG_NP: [u8; 2] = *b"NP";

    /// JP: 0x003c96c0 SetDefault__14CFieldSaveDataFv
    pub fn new_default() -> Self {
        let mut f = FieldSave::default();
        for (tag, units) in [(Self::TAG_GS, 8u8), (Self::TAG_RG, 0x81), (Self::TAG_TR, 0x10), (Self::TAG_WM, 5), (Self::TAG_NP, 4)] {
            f.add_chunk(tag, units, 0);
        }
        f
    }
    fn units_used(&self) -> usize {
        self.chunks.iter().map(|c| c.units as usize).sum()
    }
    /// JP: 0x003c9970 AddChunk__14CFieldSaveDataFPCcii
    pub fn add_chunk(&mut self, tag: [u8; 2], units: u8, flag: u8) -> Option<&mut FieldChunk> {
        if self.units_used() + units as usize > FLD_SIZE / 16 {
            return None;
        }
        self.chunks.push(FieldChunk { tag, units, flag, payload: vec![0; units as usize * 16 - 4] });
        self.chunks.last_mut()
    }
    /// JP: 0x003c98b0 FindChunk__14CFieldSaveDataFPCc
    pub fn find(&self, tag: [u8; 2]) -> Option<&FieldChunk> {
        self.chunks.iter().find(|c| c.tag == tag)
    }
    pub fn find_mut(&mut self, tag: [u8; 2]) -> Option<&mut FieldChunk> {
        self.chunks.iter_mut().find(|c| c.tag == tag)
    }
    /// JP: 0x003c97a0 SetSection__14CFieldSaveDataFP19_SaveDataSectionHdrPUc
    pub fn from_section(hdr: &SectionHdr, data: &[u8]) -> Result<Self> {
        let mut f = FieldSave::default();
        let mut o = 0usize;
        f.aux = Some(hdr.aux);
        for _ in 0..hdr.aux {
            if o >= data.len() {
                break; // retail: aux over-counts once the 0xa20 bytes are used up
            }
            if o + 4 > data.len() {
                return Err(SaveError::BadSection("FLDa".into()));
            }
            let units = data[o + 2];
            let len = units as usize * 16;
            if units == 0 {
                break; // retail: aux over-counts (SetDefault ran twice), the spare chunk headers are empty
            }
            if o + len > data.len() {
                return Err(SaveError::BadSection("FLDa".into()));
            }
            f.chunks.push(FieldChunk {
                tag: [data[o], data[o + 1]],
                units,
                flag: data[o + 3],
                payload: data[o + 4..o + len].to_vec(),
            });
            o += len;
        }
        Ok(f)
    }
    pub fn to_section_data(&self) -> Vec<u8> {
        let mut out = vec![0u8; FLD_SIZE];
        let mut o = 0;
        for c in &self.chunks {
            out[o] = c.tag[0];
            out[o + 1] = c.tag[1];
            out[o + 2] = c.units;
            out[o + 3] = c.flag;
            let n = c.payload.len().min(c.units as usize * 16 - 4);
            out[o + 4..o + 4 + n].copy_from_slice(&c.payload[..n]);
            o += c.units as usize * 16;
        }
        out
    }

    // ---- typed views (all offsets relative to chunk start; payload starts at +4)

    /// `GetSavedMpsName(0)`: current field map name (GS +0x10).
    pub fn current_map(&self) -> Option<String> {
        self.find(Self::TAG_GS).map(|c| cstr_lossy(&c.payload[0x10 - 4..0x20 - 4]))
    }
    /// Retail `Retail_GetSavedDiscNo` (0x003f8250): u16 at GS chunk +0x64 (the disc the save was made on, 0 = disc 1).
    pub fn saved_disc_no(&self) -> Option<u16> {
        self.find(Self::TAG_GS).map(|c| u16::from_le_bytes([c.payload[0x64 - 4], c.payload[0x65 - 4]]))
    }
    /// `Retail_SetSavedDiscNo`
    pub fn set_saved_disc_no(&mut self, disc: u16) {
        if let Some(c) = self.find_mut(Self::TAG_GS) {
            c.payload[0x64 - 4..0x66 - 4].copy_from_slice(&disc.to_le_bytes());
        }
    }
    /// `GetSavedMpsName(1)`: previous map (GS +0x20).
    pub fn previous_map(&self) -> Option<String> {
        self.find(Self::TAG_GS).map(|c| cstr_lossy(&c.payload[0x20 - 4..0x30 - 4]))
    }
    /// `SaveScriptRegister`: i16 triple at GS +0x48 and facing+1 at +0x4e.
    pub fn saved_char_pos(&self) -> Option<([i16; 3], i16)> {
        self.find(Self::TAG_GS).map(|c| {
            let p = &c.payload;
            let g = |o: usize| i16::from_le_bytes([p[o - 4], p[o - 3]]);
            ([g(0x48), g(0x4a), g(0x4c)], g(0x4e) - 1)
        })
    }
    /// `SetTreasureFlag`: bit n of the TR bitset (starts at chunk +8).
    pub fn treasure_flag(&self, n: usize) -> bool {
        self.find(Self::TAG_TR)
            .and_then(|c| c.payload.get(4 + (n >> 3)))
            .map(|b| b & (1 << (n & 7)) != 0)
            .unwrap_or(false)
    }
    pub fn set_treasure_flag(&mut self, n: usize, v: bool) {
        if let Some(c) = self.find_mut(Self::TAG_TR) {
            if let Some(b) = c.payload.get_mut(4 + (n >> 3)) {
                if v { *b |= 1 << (n & 7) } else { *b &= !(1 << (n & 7)) }
            }
        }
    }
    /// `FieldNpcLibrary(idx, 0)`: the 4-bit "encountered" level of NPC `idx` (0 = never met).
    pub fn npc_level(&self, idx: usize) -> u8 {
        let Some(c) = self.find(Self::TAG_NP) else { return 0 };
        let b = c.payload.get(idx >> 1).copied().unwrap_or(0);
        if idx & 1 == 0 { b & 0xf } else { b >> 4 }
    }
    /// `FieldNpcLibrary(idx, level)`: nibble table at NP +4. Returns the stored value.
    pub fn npc_library(&mut self, idx: usize, level: u8) -> u8 {
        let Some(c) = self.find_mut(Self::TAG_NP) else { return 0 };
        let b = &mut c.payload[idx >> 1];
        let cur = if idx & 1 == 0 { *b & 0xf } else { *b >> 4 };
        let v = cur.max(level & 0xf);
        if idx & 1 == 0 { *b = (*b & 0xf0) | v } else { *b = (*b & 0x0f) | (v << 4) }
        v
    }
    /// Script register file (`CScript` regs), up to 0x200 u32 at RG +0x10.
    pub fn script_registers(&self) -> Vec<u32> {
        self.find(Self::TAG_RG)
            .map(|c| c.payload[0x10 - 4..].chunks_exact(4).take(0x200).map(|w| u32::from_le_bytes([w[0], w[1], w[2], w[3]])).collect())
            .unwrap_or_default()
    }
}

// ------------------------------------------------------------------ MENU

/// One party set (0x20 bytes at MENU+0x84+k*0x20).
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct PartySet {
    pub name: Vec<u8>,
    pub member_count: i8,
    pub battle_max: i8,
    pub battle_count: i8,
    pub members: [u8; 8],
    pub pinned_mask: u16,
    raw: [u8; 0x20],
}

impl PartySet {
    pub fn parse(b: &[u8]) -> Self {
        let mut raw = [0u8; 0x20];
        raw.copy_from_slice(&b[..0x20]);
        let mut members = [0u8; 8];
        members.copy_from_slice(&b[0x12..0x1a]);
        PartySet {
            name: b[..0xf].to_vec(),
            member_count: b[0xf] as i8,
            battle_max: b[0x10] as i8,
            battle_count: b[0x11] as i8,
            members,
            pinned_mask: rd_u16(b, 0x1a),
            raw,
        }
    }
    pub fn to_bytes(&self) -> [u8; 0x20] {
        let mut b = self.raw;
        b[..0xf].fill(0);
        let n = self.name.len().min(0xf);
        b[..n].copy_from_slice(&self.name[..n]);
        b[0xf] = self.member_count as u8;
        b[0x10] = self.battle_max as u8;
        b[0x11] = self.battle_count as u8;
        b[0x12..0x1a].copy_from_slice(&self.members);
        wr_u16(&mut b, 0x1a, self.pinned_mask);
        b
    }
    pub fn name_lossy(&self) -> String {
        cstr_lossy(&self.name)
    }
    /// JP: 0x00289be0 FindPC__15SaveMenuSectionFcP16SaveMenuPartySet
    pub fn find_pc(&self, pc: u8) -> bool {
        self.members[..(self.member_count.max(0) as usize).min(8)].contains(&pc)
    }
    /// JP: 0x00289c80 JoinParty (per-set)
    pub fn join(&mut self, pc: u8) {
        if (self.member_count as usize) < 8 {
            self.members[self.member_count as usize] = pc;
            self.member_count += 1;
        }
    }
    /// JP: 0x00289cd0 LeaveParty (per-set)
    pub fn leave(&mut self, pc: u8) {
        let n = self.member_count.max(0) as usize;
        let Some(pos) = self.members[..n.min(8)].iter().position(|&m| m == pc) else { return };
        if (pos as i8) < self.battle_count {
            self.battle_count -= 1;
        }
        self.pinned_mask &= !(pc as u16); // sic: original masks with the id, not 1<<id
        for i in pos..n - 1 {
            self.members[i] = self.members[i + 1];
        }
        self.members[n - 1] = 0xff;
        self.member_count -= 1;
    }
}

/// `MENU` section.
///
/// Retail differences (US `SaveMenuSection`, 0x00286c50..0x00288610): cash is `[4 + bag * 4]` (bag = `BTL0+2`), the location id moved
/// to `+0x10` (key 0x2f of the location table), `+0x82` is a u16 mask of the characters that ever joined, **seven** party sets sit
/// at `+0x84 + k*0x20` (`FUN_00287130`; set 6 is the Yuri-only team), `+0x14` keeps the best progress value, `+0x18` the language
/// index, `+0x40..0x64` a cached slot summary (`FUN_00288540`), default brightness is 7 and the pad assignment is `c e d f`.
#[derive(Debug, Clone)]
pub struct MenuSave {
    pub data: Vec<u8>,
    pub build: Build,
}

impl MenuSave {
    pub const OFF_CASH: usize = 0x004;
    pub const OFF_LOCATION: usize = 0x008;
    pub const OFF_PLAYTIME_MS: usize = 0x00c;
    pub const OFF_CUR_SET: usize = 0x080;
    pub const OFF_SET_LOCK: usize = 0x081;
    pub const OFF_SETS: usize = 0x084;
    pub const OFF_PAD_ASSIGN: usize = 0x26c;
    pub const OFF_OPT0: usize = 0x274;
    pub const OFF_OPT1: usize = 0x275;
    pub const OFF_BRIGHT: usize = 0x278;
    /// capacity of the set table (demo: 5 are initialised, retail: 7)
    pub const SET_COUNT: usize = 7;
    pub const OFF_LOCATION_RETAIL: usize = 0x010;
    pub const OFF_JOINED_MASK: usize = 0x082;
    pub const OFF_BEST_PROGRESS: usize = 0x014;
    pub const OFF_LANGUAGE: usize = 0x018;
    pub const MAX_CASH: u32 = 99_999_999;

    pub fn from_section(data: &[u8]) -> Result<Self> {
        Self::from_section_for(data, Build::Demo)
    }
    pub fn from_section_for(data: &[u8], build: Build) -> Result<Self> {
        if data.len() < MENU_SIZE {
            return Err(SaveError::BadSection("MENU".into()));
        }
        Ok(MenuSave { data: data[..MENU_SIZE].to_vec(), build })
    }
    /// u16 mask of every character that has joined (`JoinParty` sets bit `pc`; retail only).
    pub fn joined_mask(&self) -> u16 {
        rd_u16(&self.data, Self::OFF_JOINED_MASK)
    }
    pub fn set_joined(&mut self, pc: u8) {
        let m = self.joined_mask() | (1u16 << (pc & 15));
        wr_u16(&mut self.data, Self::OFF_JOINED_MASK, m);
    }
    /// The four pad entries of `MENU+0x26c` (`SaveMenuSection::UpdatePad`): physical button bit `0xc..=0xf` of menu / confirm / cancel / other.
    pub fn button_entries(&self) -> [u16; 4] {
        // an unwritten block (new game before `SetDefaultButton`, zeros) means the build default, not identity
        let mut e = sh2_core::game::default_buttons();
        for (k, v) in e.iter_mut().enumerate() {
            let x = rd_u16(&self.data, Self::OFF_PAD_ASSIGN + k * 2);
            if (0xc..=0xf).contains(&x) {
                *v = x;
            }
        }
        e
    }
    /// Option "battle cursor memory" (`MENU+0x274` >> 6 == 0, `BtlMenu` ctor 0x58c6a0): the battle command menu reopens on the last command.
    pub fn battle_cursor_memory(&self) -> bool {
        self.data[Self::OFF_OPT0] >> 6 == 0
    }
    /// round 6 MN3: the command menu's **Combo Switch** (`MENU+0x276` bits 0..1).  US `CmdTop::SelectMenu` (FIELD 0x4699e8..0x469a20) stores the
    /// picked row's value there (ON = 1, OFF = 0: the row's place `+0x16`) and `CmdRetailWin11` (0x4e95b4) puts the cursor on that row; each battle sets `BTL0+3` bit 1 = `value != 0`
    /// ([`BtlSave::combo_shortcut_enabled`]).  JP's Option page wrote the same bits (`Shortcuts` row, `value ^ 1`).
    pub const OFF_COMBO_SWITCH: usize = 0x276;
    pub fn combo_switch(&self) -> u8 {
        self.data[Self::OFF_COMBO_SWITCH] & 3
    }
    pub fn set_combo_switch(&mut self, v: u8) {
        let b = &mut self.data[Self::OFF_COMBO_SWITCH];
        *b = (*b & !3) | (v & 3);
    }
    /// Language index (`GetFullPathName` fallback index; retail default 1).
    pub fn language(&self) -> u32 {
        rd_u32(&self.data, Self::OFF_LANGUAGE)
    }
    pub fn cash(&self, scenario: u32) -> u32 {
        rd_u32(&self.data, Self::OFF_CASH + (scenario as usize & 3) * 4)
    }
    /// JP: 0x00289550 SetCurrentCash__15SaveMenuSectionFi
    pub fn set_cash(&mut self, scenario: u32, v: u32) {
        wr_u32(&mut self.data, Self::OFF_CASH + (scenario as usize & 3) * 4, v.min(Self::MAX_CASH));
    }
    pub fn location_id(&self) -> u32 {
        rd_u32(&self.data, if self.build.is_retail() { Self::OFF_LOCATION_RETAIL } else { Self::OFF_LOCATION })
    }
    pub fn set_location_id(&mut self, id: u32) {
        let o = if self.build.is_retail() { Self::OFF_LOCATION_RETAIL } else { Self::OFF_LOCATION };
        wr_u32(&mut self.data, o, id);
    }
    pub fn play_time_ms(&self) -> u32 {
        rd_u32(&self.data, Self::OFF_PLAYTIME_MS)
    }
    /// (hours, minutes, seconds) as `dispTime::mCalcTime` shows them.
    pub fn play_time_hms(&self) -> (u32, u32, u32) {
        let ms = self.play_time_ms();
        (ms / 3_600_000, (ms / 60_000) % 60, (ms / 1000) % 60)
    }
    pub fn current_set_index(&self) -> usize {
        self.data[Self::OFF_CUR_SET] as usize
    }
    pub fn party_set(&self, i: usize) -> Option<PartySet> {
        if i >= Self::SET_COUNT {
            return None;
        }
        let o = Self::OFF_SETS + i * 0x20;
        Some(PartySet::parse(&self.data[o..o + 0x20]))
    }
    pub fn set_party_set(&mut self, i: usize, s: &PartySet) {
        let o = Self::OFF_SETS + i * 0x20;
        self.data[o..o + 0x20].copy_from_slice(&s.to_bytes());
    }
    /// bits0-1 of OPT0 -> `CVibeMan::SetMode` (JP: 0x002894b0 UpdateVibration).
    pub fn vibration_mode(&self) -> u8 {
        self.data[Self::OFF_OPT0] & 3
    }
    /// bits2-3 of OPT0 -> `Sdrv::SetMode` code 0x1001/0x1000/0x1002.
    pub fn sound_out_sdrv_mode(&self) -> u32 {
        match (self.data[Self::OFF_OPT0] & 0xf) >> 2 {
            0 => 0x1001,
            1 => 0x1000,
            _ => 0x1002,
        }
    }
    /// `CApp::SetBright(v * 0.03 + 0.7)`.
    pub fn brightness(&self) -> f32 {
        self.data[Self::OFF_BRIGHT] as f32 * 0.03 + 0.7
    }
    /// Default block of the active build ([`Build::current`]).
    pub fn new_default() -> Self {
        Self::new_default_for(Build::current())
    }
    /// JP: 0x002890e0 SceneInit__15SaveMenuSectionFi + 0x0028a280 SetDefault; retail: 0x002882a0 `SetDefault` + `FUN_00287130`.
    pub fn new_default_for(build: Build) -> Self {
        let mut d = vec![0u8; MENU_SIZE];
        for k in 0..build.party_sets() {
            let o = Self::OFF_SETS + k * 0x20;
            d[o + 0xf] = 2;
            d[o + 0x11] = 2;
            d[o + 0x10] = 4;
            d[o + 0x12] = 0xb;
            d[o + 0x13] = 5;
            for i in 2..8 {
                d[o + 0x12 + i] = 0xff;
            }
        }
        if build.is_retail() {
            // FUN_00287130: sets are {5, 0xb} (Karin, Nicolai); the table starts with the joined mask (|= 0x20 | 0x800) and set 6 is Yuri alone
            for k in 0..build.party_sets() {
                let o = Self::OFF_SETS + k * 0x20;
                d[o + 0x12] = 5;
                d[o + 0x13] = 0xb;
            }
            wr_u16(&mut d, Self::OFF_JOINED_MASK, 0x20 | 0x800);
            d[0x153] = 1;
            d[0x154] = 1;
            d[0x155] = 1;
            d[0x156] = 0;
            for (k, n) in ["Team A", "Team B", "Team C", "Team D", "Team E"].iter().enumerate() {
                let o = Self::OFF_SETS + k * 0x20;
                d[o..o + n.len()].copy_from_slice(n.as_bytes());
            }
            // SetDefaultButton: c, e, d, f
            wr_u16(&mut d, 0x26c, 0xc);
            wr_u16(&mut d, 0x26e, 0xe);
            wr_u16(&mut d, 0x270, 0xd);
            wr_u16(&mut d, 0x272, 0xf);
            d[0x278] = 7;
            d[0x274] = (d[0x274] & 0xfc) | 1;
            d[0x274] = (d[0x274] & 0xcf) | 0x10;
            d[0x274] = (d[0x274] & 0x3f) | 0x40;
            d[0x275] = (d[0x275] & 0x3f) | 0x40;
            d[0x309] = 2;
            wr_u32(&mut d, Self::OFF_LANGUAGE, 1);
        } else {
            wr_u16(&mut d, 0x26c, 0xc);
            wr_u16(&mut d, 0x26e, 0xd);
            wr_u16(&mut d, 0x270, 0xe);
            wr_u16(&mut d, 0x272, 0xf);
            d[0x278] = 8;
            d[0x274] = (d[0x274] & 0xcf) | 0x10;
            d[0x275] = (d[0x275] & 0xcf) | 0x10;
            d[0x274] = (d[0x274] & 0xfc) | 1;
            d[0x274] = (d[0x274] & 0x3f) | 0x40;
        }
        for o in [0x2ac, 0x2ae, 0x2b0] {
            wr_u16(&mut d, o, 0xffff);
        }
        d[0x300] = 2;
        d[0x312] = 2;
        MenuSave { data: d, build }
    }
}

// ------------------------------------------------------------------ slot file

/// A parsed `SH2-nnn` slot file.
#[derive(Debug, Clone)]
pub struct SaveFile {
    /// which layout the sections follow (decided by the `BTL0` section when parsing)
    pub build: Build,
    pub btl: BtlSave,
    pub field: FieldSave,
    pub menu: MenuSave,
    /// Sections we do not know, preserved verbatim.
    pub extra: Vec<RawSection>,
    pub checksum_ok: bool,
}

impl SaveFile {
    pub fn parse(buf: &[u8]) -> Result<Self> {
        let (_, secs) = parse_container(buf)?;
        let total = rd_u16(buf, 0x16) as usize + rd_u32(buf, 0x18) as usize;
        let checksum_ok = verify_checksum(buf, total.min(buf.len()));
        // the build follows the BTL0 section: retail = version 4 / 0x21bc bytes
        let build = secs
            .iter()
            .find(|s| &s.hdr.name == b"BTL0")
            .map(|s| if s.hdr.version == BTL_VERSION_RETAIL || s.data.len() >= BTL_SIZE_RETAIL { Build::Retail } else { Build::Demo })
            .unwrap_or_default();
        let (mut btl, mut field, mut menu, mut extra) = (None, None, None, vec![]);
        for s in secs {
            match &s.hdr.name {
                b"BTL0" => {
                    btl = Some(if build.is_retail() { BtlSave::from_retail_section(&s.data)? } else { BtlSave::from_section(&s.data)? })
                }
                b"FLDa" => field = Some(FieldSave::from_section(&s.hdr, &s.data)?),
                b"MENU" => menu = Some(MenuSave::from_section_for(&s.data, build)?),
                _ => extra.push(s),
            }
        }
        Ok(SaveFile {
            build,
            btl: btl.ok_or(SaveError::MissingSection("BTL0"))?,
            field: field.ok_or(SaveError::MissingSection("FLDa"))?,
            menu: menu.ok_or(SaveError::MissingSection("MENU"))?,
            extra,
            checksum_ok,
        })
    }

    /// Serialise exactly as `SaveData::GetHeap` would hand it to the device.
    pub fn to_bytes(&self) -> Vec<u8> {
        let mut payload = Vec::new();
        let fld = self.field.to_section_data();
        let mut btl = self.btl.clone();
        let btl_bytes = btl.section_bytes(self.build);
        let mut push = |name: &[u8; 4], version: u16, aux: u32, data: &[u8]| {
            SectionHdr { name: *name, hdr_size: 0x10, version, size: data.len() as u32, aux }.write(&mut payload);
            payload.extend_from_slice(data);
        };
        push(b"BTL0", self.build.btl_version(), 0, &btl_bytes);
        push(b"FLDa", 0, self.field.aux.unwrap_or(self.field.chunks.len() as u32), &fld);
        push(b"MENU", 0, 0, &self.menu.data);
        let mut count = 3u16;
        for e in &self.extra {
            e.hdr.write(&mut payload);
            payload.extend_from_slice(&e.data);
            count += 1;
        }
        let mut out = vec![0u8; SAVE_HDR_SIZE];
        out[4..12].copy_from_slice(&SAVE_MAGIC);
        wr_u16(&mut out, 0x16, SAVE_HDR_SIZE as u16);
        wr_u32(&mut out, 0x18, payload.len() as u32);
        wr_u16(&mut out, 0x1c, count);
        out.extend_from_slice(&payload);
        let len = out.len();
        set_checksum(&mut out, len);
        out
    }

    pub fn new_default() -> Self {
        Self::new_default_for(Build::current())
    }
    pub fn new_default_for(build: Build) -> Self {
        let btl = if build.is_retail() { BtlSave::new_retail() } else { BtlSave::new_zeroed() };
        SaveFile { build, btl, field: FieldSave::new_default(), menu: MenuSave::new_default_for(build), extra: vec![], checksum_ok: true }
    }
}

// --------------------------------------------------------------- system file

/// `_SaveDataInfo` — per-slot summary shown in the file list (0x60 bytes).
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct SlotInfo {
    pub used: bool,
    pub level: u8,
    pub word0: u16,
    pub play_time_ms: u32,
    pub cash: u32,
    pub party_mask: u16,
    pub team_models: [u16; 4],
    pub leader_name: Vec<u8>,
    pub party_name: Vec<u8>,
    pub location: Vec<u8>,
}

impl SlotInfo {
    pub fn parse(b: &[u8]) -> Self {
        let mut team_models = [0u16; 4];
        for (i, m) in team_models.iter_mut().enumerate() {
            *m = rd_u16(b, 0x0e + i * 2);
        }
        SlotInfo {
            used: b[0] != 0xff,
            level: b[1],
            word0: rd_u16(b, 2),
            play_time_ms: rd_u32(b, 4),
            cash: rd_u32(b, 8),
            party_mask: rd_u16(b, 0xc),
            team_models,
            leader_name: b[0x16..0x28].to_vec(),
            party_name: b[0x28..0x38].to_vec(),
            location: b[0x38..0x60].to_vec(),
        }
    }
    pub fn to_bytes(&self) -> [u8; SLOT_INFO_SIZE] {
        let mut b = [0u8; SLOT_INFO_SIZE];
        b[0] = if self.used { 0 } else { 0xff };
        b[1] = self.level;
        wr_u16(&mut b, 2, self.word0);
        wr_u32(&mut b, 4, self.play_time_ms);
        wr_u32(&mut b, 8, self.cash);
        wr_u16(&mut b, 0xc, self.party_mask);
        for (i, m) in self.team_models.iter().enumerate() {
            wr_u16(&mut b, 0x0e + i * 2, *m);
        }
        let cp = |dst: &mut [u8], src: &[u8]| {
            let n = src.len().min(dst.len());
            dst[..n].copy_from_slice(&src[..n]);
        };
        cp(&mut b[0x16..0x28], &self.leader_name);
        cp(&mut b[0x28..0x38], &self.party_name);
        cp(&mut b[0x38..0x60], &self.location);
        b
    }
    pub fn leader_name_lossy(&self) -> String {
        cstr_lossy(&self.leader_name)
    }
    pub fn location_lossy(&self) -> String {
        cstr_lossy(&self.location)
    }
}

/// `SystemFile` (`SYSH`).
#[derive(Debug, Clone)]
pub struct SystemFile {
    pub current_slot: u8,
    pub common: [u8; SYSTEM_COMMON_SIZE],
    pub slots: Vec<SlotInfo>,
}

impl SystemFile {
    /// JP: 0x0032a780 Create__10SystemFileFi — fresh file, all slots empty (0xff).
    pub fn new_empty() -> Self {
        let mut empty = [0u8; SLOT_INFO_SIZE];
        empty[0] = 0xff;
        SystemFile {
            current_slot: 0,
            common: [0; SYSTEM_COMMON_SIZE],
            slots: (0..SLOT_COUNT).map(|_| SlotInfo::parse(&empty)).collect(),
        }
    }
    /// JP: 0x0032a930 SetData__10SystemFileFP14_SystemFileHdr
    pub fn parse(buf: &[u8]) -> Result<Self> {
        if buf.len() < SYSTEM_FILE_SIZE {
            return Err(SaveError::TooShort { need: SYSTEM_FILE_SIZE, have: buf.len() });
        }
        if buf[4..8] != SYSTEM_MAGIC {
            return Err(SaveError::BadMagic);
        }
        let common_off = rd_u32(buf, 0x14) as usize;
        let common_len = rd_u16(buf, 0x10) as usize;
        let slot_off = rd_u32(buf, 0x1c) as usize;
        let rec = rd_u16(buf, 0x18) as usize;
        let n = buf[0xd] as usize;
        let mut common = [0u8; SYSTEM_COMMON_SIZE];
        let l = common_len.min(SYSTEM_COMMON_SIZE);
        common[..l].copy_from_slice(&buf[common_off..common_off + l]);
        let slots = (0..n.min(SLOT_COUNT))
            .map(|i| SlotInfo::parse(&buf[slot_off + i * rec..slot_off + i * rec + SLOT_INFO_SIZE]))
            .collect();
        Ok(SystemFile { current_slot: buf[0xc], common, slots })
    }
    pub fn to_bytes(&self) -> Vec<u8> {
        let mut b = vec![0u8; SYSTEM_FILE_SIZE];
        b[4..8].copy_from_slice(&SYSTEM_MAGIC);
        wr_u32(&mut b, 8, (SYSTEM_FILE_SIZE - 0x20) as u32);
        b[0xc] = self.current_slot;
        b[0xd] = SLOT_COUNT as u8;
        wr_u16(&mut b, 0xe, 0x20);
        wr_u16(&mut b, 0x10, SYSTEM_COMMON_SIZE as u16);
        wr_u32(&mut b, 0x14, 0x20);
        wr_u16(&mut b, 0x18, SLOT_INFO_SIZE as u16);
        wr_u32(&mut b, 0x1c, 0x120);
        b[0x20..0x20 + SYSTEM_COMMON_SIZE].copy_from_slice(&self.common);
        for (i, s) in self.slots.iter().enumerate().take(SLOT_COUNT) {
            b[0x120 + i * SLOT_INFO_SIZE..0x120 + (i + 1) * SLOT_INFO_SIZE].copy_from_slice(&s.to_bytes());
        }
        set_checksum(&mut b, SYSTEM_FILE_SIZE);
        b
    }
    /// JP: 0x0032aa70 SetCurrentSlot__10SystemFileFv — first used slot.
    pub fn first_used_slot(&self) -> Option<u8> {
        self.slots.iter().position(|s| s.used).map(|i| i as u8)
    }
    /// JP: 0x00289e20 GetSaveDataSlot__15SaveMenuSectionFP13_SaveDataInfo
    pub fn build_slot_info(save: &SaveFile, location_name: &[u8]) -> SlotInfo {
        let scenario = save.btl.scenario();
        let set = save.menu.party_set(save.menu.current_set_index().min(4)).unwrap();
        let leader = save.btl.pc(set.members[0] as usize);
        let mut team_models = [0xffffu16; 4];
        for i in 0..(set.battle_count.clamp(0, 4) as usize) {
            if let Some(p) = save.btl.pc(set.members[i] as usize) {
                team_models[i] = p.model_nums[2];
            }
        }
        let mut mask = 0u16;
        for &m in &set.members[..(set.member_count.clamp(0, 8) as usize)] {
            mask |= 1 << (m & 0x1f);
        }
        SlotInfo {
            used: true,
            level: leader.as_ref().map(|p| p.level).unwrap_or(0),
            word0: rd_u16(&save.menu.data, 0),
            play_time_ms: save.menu.play_time_ms(),
            cash: save.menu.cash(scenario),
            party_mask: mask,
            team_models,
            leader_name: leader.map(|p| p.name).unwrap_or_default(),
            party_name: set.name.clone(),
            location: location_name.to_vec(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn combo_switch_and_shortcut_bit() {
        // round 6 MN3: the Combo command (bit 0) and the shortcut switch (bit 1) are separate bits of `BTL0+3`
        let mut b = BtlSave::new_retail();
        b.data[BtlSave::OFF_FLAGS] = 1;
        assert!(b.combo_menu_enabled() && !b.combo_shortcut_enabled());
        b.set_combo_shortcut(true);
        assert_eq!(b.data[BtlSave::OFF_FLAGS], 3);
        b.set_combo_shortcut(false);
        assert_eq!(b.data[BtlSave::OFF_FLAGS], 1);
        let mut m = MenuSave::from_section_for(&vec![0u8; MENU_SIZE], Build::Retail).unwrap();
        m.data[MenuSave::OFF_COMBO_SWITCH] = 0xf0;
        m.set_combo_switch(1);
        assert_eq!((m.combo_switch(), m.data[MenuSave::OFF_COMBO_SWITCH]), (1, 0xf1));
    }

    #[test]
    fn default_roundtrip() {
        let mut s = SaveFile::new_default();
        let mut p = s.btl.pc(0).unwrap();
        p.level = 12;
        p.name = b"Yuri".to_vec();
        s.btl.set_pc(0, &p);
        s.menu.set_cash(0, 12345);
        let bytes = s.to_bytes();
        assert_eq!(bytes.len(), SAVE_FILE_SIZE);
        let t = SaveFile::parse(&bytes).unwrap();
        assert!(t.checksum_ok);
        assert_eq!(t.btl.pc(0).unwrap().name_lossy(), "Yuri");
        assert_eq!(t.btl.pc(0).unwrap().level, 12);
        assert_eq!(t.menu.cash(0), 12345);
        assert_eq!(t.field.chunks.len(), 5);
    }

    #[test]
    fn system_roundtrip() {
        let mut sf = SystemFile::new_empty();
        sf.slots[3].used = true;
        sf.slots[3].level = 7;
        let b = sf.to_bytes();
        assert_eq!(b.len(), SYSTEM_FILE_SIZE);
        let t = SystemFile::parse(&b).unwrap();
        assert_eq!(t.first_used_slot(), Some(3));
        assert_eq!(t.slots[3].level, 7);
    }

    /// A real retail save written by the game on an emulated memory card (`BASLUS-21041-SH2/SH2-000`, 12332 bytes).
    const CARD_SAVE: &[u8] = include_bytes!("../tests/fixtures/us_card_SH2-000");
    const CARD_SYSTEM: &[u8] = include_bytes!("../tests/fixtures/us_card_system");

    #[test]
    fn real_retail_card_save_parses() {
        assert_eq!(CARD_SAVE.len(), SAVE_FILE_SIZE_RETAIL);
        let s = SaveFile::parse(CARD_SAVE).unwrap();
        assert_eq!(s.build, Build::Retail);
        assert!(s.checksum_ok, "the additive checksum of the real file must verify");
        assert!(s.btl.is_retail() && s.menu.build.is_retail());
        // Karin (PC 5, level 1) and Nicolai (PC 0xb, level 2) of a fresh retail game
        let karin = s.btl.pc(5).unwrap();
        assert_eq!((karin.name_lossy().as_str(), karin.level, karin.hp_max, karin.weapon), ("Karin", 1, 25, 0x22));
        let nic = s.btl.pc(0xb).unwrap();
        assert_eq!((nic.name_lossy().as_str(), nic.level, nic.hp_max, nic.mp_max), ("Nicolai", 2, 38, 33));
        // bag 1 holds the starting inventory: 8 Thera Leaf / Mana Leaf / Pure Leaf, 3 Talisman, 3 Tent
        assert_eq!(s.btl.bag(), 1);
        assert_eq!(s.btl.scenario(), 1);
        assert_eq!((s.btl.item_count(0), s.btl.item_count(4), s.btl.item_count(8)), (8, 8, 8));
        assert_eq!((s.btl.item_count(0xf), s.btl.item_count(0x20)), (3, 3));
        // key items (retail only): Holy Mistletoe x3, Periapt x3, "King" x1
        assert_eq!((s.btl.key_item(1), s.btl.key_item(2), s.btl.key_item(0x33)), (3, 3, 1));
        // MENU: cash lives at [4 + bag*4], location at +0x10, 7 party sets, current set 3 = {Karin, Nicolai}
        assert_eq!(s.menu.cash(s.btl.scenario()), 110);
        assert_eq!(s.menu.play_time_ms(), 0x308c37);
        assert_eq!(s.menu.current_set_index(), 3);
        let set = s.menu.party_set(3).unwrap();
        assert_eq!((set.name_lossy().as_str(), set.member_count, set.members[0], set.members[1]), ("Contingent 2", 2, 5, 0xb));
        assert_eq!(s.menu.party_set(6).unwrap().member_count, 1);
        assert_eq!(s.menu.joined_mask(), 0x20 | 0x800);
        // FLDa: five chunks, header aux = 10 (the game never resets it), field map AP_02_U
        assert_eq!(s.field.chunks.len(), 5);
        assert_eq!(s.field.aux, Some(10));
        assert_eq!(s.field.current_map().as_deref(), Some("AP_02_U"));
        assert_eq!(s.field.saved_disc_no(), Some(0));
    }

    #[test]
    fn real_retail_card_save_roundtrips_byte_for_byte() {
        let s = SaveFile::parse(CARD_SAVE).unwrap();
        let out = s.to_bytes();
        assert_eq!(out.len(), CARD_SAVE.len());
        assert_eq!(out, CARD_SAVE, "parse -> serialise must reproduce the game's own file (incl. checksum)");
        // edits through the demo-shaped working copy reach the retail block
        let mut t = SaveFile::parse(CARD_SAVE).unwrap();
        t.btl.data[BtlSave::OFF_ITEMS + BtlSave::BAG_STRIDE + 2] = 7;
        t.btl.set_key_item(5, 9);
        let u = SaveFile::parse(&t.to_bytes()).unwrap();
        assert_eq!(u.btl.item_count(2), 7);
        assert_eq!(u.btl.key_item(5), 9);
        assert_eq!(u.btl.key_item(1), 3);
    }

    #[test]
    fn real_retail_system_file() {
        let sf = SystemFile::parse(CARD_SYSTEM).unwrap();
        assert_eq!(sf.first_used_slot(), Some(0));
        let sl = &sf.slots[0];
        assert!(sl.used);
        assert_eq!(sl.leader_name_lossy(), "Karin");
        assert_eq!(sl.level, 1);
        assert!(!sf.slots[1].used);
        assert_eq!(sf.to_bytes(), CARD_SYSTEM, "system file reserialises identically");
    }

    #[test]
    fn retail_default_layout() {
        let s = SaveFile::new_default_for(Build::Retail);
        let b = s.to_bytes();
        assert_eq!(b.len(), SAVE_FILE_SIZE_RETAIL);
        let t = SaveFile::parse(&b).unwrap();
        assert!(t.checksum_ok && t.build == Build::Retail);
        assert_eq!(t.menu.party_set(6).unwrap().member_count, 1);
        assert_eq!(t.menu.party_set(0).unwrap().name_lossy(), "Team A");
        assert_eq!(t.btl.bag(), 1);
    }

    #[test]
    fn party_ops() {
        let m = MenuSave::new_default();
        let mut s = m.party_set(0).unwrap();
        assert!(s.find_pc(0xb) && s.find_pc(5));
        s.join(2);
        assert_eq!(s.member_count, 3);
        s.leave(0xb);
        assert_eq!(s.members[0], 5);
        assert_eq!(s.member_count, 2);
    }
}

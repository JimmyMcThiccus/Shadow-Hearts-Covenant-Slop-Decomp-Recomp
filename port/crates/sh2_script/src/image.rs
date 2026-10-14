//! Event-script image format (FIELD.PKB `.scr` files and the payload of LSD `LSCR` tracks).
//!
//! ```text
//! +0x00 ScriptHdr (0x20 bytes)
//! +hdr.nsec*16      directory sections ("EVNT" ...), total hdr.dir_units*16 bytes
//! +...              code  (hdr.code_units*16 bytes)
//! +...              data  (hdr.data_units*16 bytes; strings, tables, switch tables)
//! +hdr.reloc*16     relocation table (u16 count, u16 region size, count*{u16 flags,u16 off})
//! ```
// JP: 0x002923e0 InitScript__7CScriptFPcPUc

use crate::memory::{SEG_CODE, SEG_DATA};

pub const EVNT_MAGIC: u32 = 0x544e_5645; // 'E' 'V' 'N' 'T' little-endian

#[derive(Debug, Clone, Default)]
pub struct ScriptHdr {
    pub nsec_units: u8,
    pub valid: u8,
    pub dir_units: u16,
    pub code_units: u16,
    pub data_units: u16,
    pub bss_size: u16,
    pub start_func: u16,
    pub end_func: u16,
    pub reloc_unit: u16,
    pub flags_1a: u16,
}

#[derive(Debug, Clone, Copy)]
pub struct EventEntry {
    /// Event id (kind 0) or LSD tick (kind 1)
    pub id: u32,
    /// Code offset of the user function.
    pub func: u16,
}

#[derive(Debug, Clone)]
pub struct EventSection {
    /// 0 = by-id events (CallEvent), 1 = LSD-time events (CallEventT)
    pub kind: u16,
    pub entries: Vec<EventEntry>,
}

#[derive(Debug, Clone)]
pub struct ScriptImage {
    pub hdr: ScriptHdr,
    pub events: Vec<EventSection>,
    /// Relocated code bytes (pointers rebased onto `SEG_CODE`/`SEG_DATA`).
    pub code: Vec<u8>,
    pub data: Vec<u8>,
}

#[derive(Debug, thiserror::Error)]
pub enum ImageError {
    #[error("script image truncated at 0x{0:x}")]
    Truncated(usize),
    #[error("script header marked invalid")]
    Invalid,
}

fn u16_at(b: &[u8], o: usize) -> Result<u16, ImageError> {
    b.get(o..o + 2).map(|s| u16::from_le_bytes([s[0], s[1]])).ok_or(ImageError::Truncated(o))
}
fn u32_at(b: &[u8], o: usize) -> Result<u32, ImageError> {
    b.get(o..o + 4).map(|s| u32::from_le_bytes([s[0], s[1], s[2], s[3]])).ok_or(ImageError::Truncated(o))
}

impl ScriptImage {
    /// Parse and relocate an image.  `bytes` starts at the script header.
    pub fn parse(bytes: &[u8]) -> Result<Self, ImageError> {
        if bytes.len() < 0x20 {
            return Err(ImageError::Truncated(bytes.len()));
        }
        let hdr = ScriptHdr {
            nsec_units: bytes[1],
            valid: bytes[2],
            dir_units: u16_at(bytes, 6)?,
            code_units: u16_at(bytes, 8)?,
            data_units: u16_at(bytes, 0xa)?,
            bss_size: u16_at(bytes, 0xc)?,
            start_func: u16_at(bytes, 0xe)?,
            end_func: u16_at(bytes, 0x10)?,
            reloc_unit: u16_at(bytes, 0x18)?,
            flags_1a: u16_at(bytes, 0x1a)?,
        };
        if hdr.valid == 0 {
            return Err(ImageError::Invalid);
        }
        let sec0 = hdr.nsec_units as usize * 16;
        let code0 = sec0 + hdr.dir_units as usize * 16;
        let data0 = code0 + hdr.code_units as usize * 16;
        let data_end = data0 + hdr.data_units as usize * 16;
        // directory
        let mut events = Vec::new();
        let mut p = sec0;
        while p < code0 {
            let magic = u32_at(bytes, p)?;
            let tbl = u16_at(bytes, p + 4)? as usize;
            let units = u16_at(bytes, p + 6)? as usize;
            let kind = u16_at(bytes, p + 8)?;
            let count = u16_at(bytes, p + 10)? as usize;
            if magic == EVNT_MAGIC {
                let mut entries = Vec::with_capacity(count);
                for i in 0..count {
                    let e = p + tbl + i * 8;
                    entries.push(EventEntry { id: u32_at(bytes, e)?, func: u16_at(bytes, e + 6)? });
                }
                events.push(EventSection { kind, entries });
            }
            if units == 0 {
                break;
            }
            p += units * 16;
        }
        let mut code = bytes.get(code0..data0).ok_or(ImageError::Truncated(data0))?.to_vec();
        let mut data = bytes.get(data0..data_end.min(bytes.len())).ok_or(ImageError::Truncated(data_end))?.to_vec();
        // relocation table
        if hdr.reloc_unit != 0 {
            let r = hdr.reloc_unit as usize * 16;
            let n = u16_at(bytes, r)? as usize;
            // entries are 4 bytes `{u16 flags, u16 off}` starting at r+4; u16 at r+2 is the size of the
            // region (used by InitScript to decide whether BSS can reuse the relocation table's memory)
            for i in 0..n {
                let e = r + 4 + i * 4;
                let flags = u16_at(bytes, e)?;
                let off = u16_at(bytes, e + 2)? as usize;
                let (seg_where, base_sel) = (flags & 0xf, (flags >> 4) & 0xf);
                let target = if seg_where == 0 { &mut code } else { &mut data };
                if off + 4 <= target.len() {
                    let mut w = [0u8; 4];
                    w.copy_from_slice(&target[off..off + 4]);
                    let v = u32::from_le_bytes(w).wrapping_add(if base_sel == 0 { SEG_CODE } else { SEG_DATA });
                    target[off..off + 4].copy_from_slice(&v.to_le_bytes());
                }
            }
        }
        Ok(ScriptImage { hdr, events, code, data })
    }

    pub fn find_event(&self, kind: u16, id: u32) -> Option<u16> {
        self.events.iter().filter(|s| s.kind == kind).flat_map(|s| s.entries.iter()).find(|e| e.id == id).map(|e| e.func)
    }

    /// Every event id of table `kind`.
    pub fn event_ids(&self, kind: u16) -> Vec<u32> {
        self.events.iter().filter(|s| s.kind == kind).flat_map(|s| s.entries.iter()).map(|e| e.id).collect()
    }
}

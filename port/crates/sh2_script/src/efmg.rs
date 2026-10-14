//! `EFMG` effect container (one effect = one file inside `EFFECT.PKB`) and the `HECO` code
//! section it carries.  See `notes/D/effect_format.md`.
//!
//! JP: 0x00300ee0 `EffectCore::Create(BufMemory*)` walks the directory, 0x00301050
//! `EffectCore::CreateVec` validates the HECO section, 0x00303e40 `GetDataPtr` looks up sections.
//!
//! (Moved here from `sh2_gfx::effects::efmg` when the two VEC interpreters were merged; that module is now a
//! re-export of this one.)

use thiserror::Error;

#[derive(Debug, Error)]
pub enum EfmgError {
    #[error("bad magic (expected EFMG)")]
    BadMagic,
    #[error("truncated file")]
    Truncated,
    #[error("section {0:?} out of range")]
    BadSection(u8),
    #[error("HECO: {0}")]
    Heco(&'static str),
}

/// Section kinds (first byte of a directory entry).
pub mod kind {
    /// `HECO` — VSM bytecode (the effect "program").
    pub const CODE: u8 = b'C';
    /// `TXPS` — texture pack (only 4 of 261 JP effects use it; read by `vpTextureFile`).
    pub const TEXTURE: u8 = b'T';
    /// `SSH1` — model (same format as every other model, see section C).
    pub const MODEL: u8 = b'M';
    /// `SQHD` — motion (bit 7 of the index = standalone motion list for `EffectCore::CreateMotion`).
    pub const MOTION: u8 = b'A';
    /// `EFCM` — camera motion (key table of 0x40-byte keys).
    pub const CAMERA: u8 = b'E';
    /// `EFLT` — light motion.
    pub const LIGHT: u8 = b'L';
    /// `SDRH` — sound effect bank (`Sdrv::AutoLoad`).
    pub const SOUND: u8 = b'1';
    /// `BBPF` — BBPLine model ("custom model", `CreateCustomModel`).
    pub const LINE_MODEL: u8 = b'P';
    /// `HTFH` — hit data (cylinder / shot key table).
    pub const HIT: u8 = b'Y';
    /// `HTFH` — shadow/other hit data (see `mdlCreateShadow`).
    pub const SHADOW: u8 = b'S';
    /// `VIBE` (vibration pattern) or `TIHD` (texture header for `pph*` particles).
    pub const OTHER: u8 = b'O';
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct EfmgEntry {
    pub kind: u8,
    pub index: u8,
    pub offset: u32,
}

/// Parsed directory of an EFMG file; section data is borrowed from the file image.
pub struct Efmg<'a> {
    pub data: &'a [u8],
    pub version: u16,
    pub entries: Vec<EfmgEntry>,
}

fn rd_u16(d: &[u8], o: usize) -> Option<u16> {
    d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]))
}
fn rd_u32(d: &[u8], o: usize) -> Option<u32> {
    d.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]))
}

impl<'a> Efmg<'a> {
    /// Header: `"EFMG"`, u16 entry count (+4), u16 version (+6, always 1), 8 reserved bytes,
    /// then `count` entries of `{u8 kind, u8 index, u16 0, u32 offset}` starting at +0x10.
    pub fn parse(data: &'a [u8]) -> Result<Self, EfmgError> {
        if data.get(0..4) != Some(b"EFMG") {
            return Err(EfmgError::BadMagic);
        }
        let count = rd_u16(data, 4).ok_or(EfmgError::Truncated)? as usize;
        let version = rd_u16(data, 6).ok_or(EfmgError::Truncated)?;
        let mut entries = Vec::with_capacity(count);
        for i in 0..count {
            let o = 0x10 + i * 8;
            let k = *data.get(o).ok_or(EfmgError::Truncated)?;
            let idx = *data.get(o + 1).ok_or(EfmgError::Truncated)?;
            let off = rd_u32(data, o + 4).ok_or(EfmgError::Truncated)?;
            if off as usize > data.len() {
                return Err(EfmgError::BadSection(k));
            }
            entries.push(EfmgEntry { kind: k, index: idx, offset: off });
        }
        Ok(Efmg { data, version, entries })
    }

    /// Byte range of an entry: up to the next section (sections are stored in directory order).
    pub fn section(&self, e: &EfmgEntry) -> &'a [u8] {
        let start = e.offset as usize;
        let end = self
            .entries
            .iter()
            .map(|x| x.offset as usize)
            .filter(|&o| o > start)
            .min()
            .unwrap_or(self.data.len());
        &self.data[start..end.min(self.data.len())]
    }

    /// `FindXxx`: exact kind + index.
    pub fn find(&self, kind: u8, index: u8) -> Option<&'a [u8]> {
        self.entries.iter().find(|e| e.kind == kind && e.index == index).map(|e| self.section(e))
    }

    /// `EffectCore::GetDataPtr(kind, value, mask, mask2)` (0x00303e40): if `mask == None`
    /// exact index match, else `(index & mask) != 0 && value == (index & mask2)`.
    pub fn get_data_ptr(&self, kind: u8, value: u8, mask: Option<u8>, mask2: u8) -> Option<&'a [u8]> {
        self.entries
            .iter()
            .find(|e| {
                e.kind == kind
                    && match mask {
                        None => e.index == value,
                        Some(m) => (e.index & m) != 0 && value == (e.index & mask2),
                    }
            })
            .map(|e| self.section(e))
    }

    pub fn iter_kind(&self, kind: u8) -> impl Iterator<Item = (u8, &'a [u8])> + '_ {
        self.entries.iter().filter(move |e| e.kind == kind).map(move |e| (e.index, self.section(e)))
    }
}

/// One VSM instruction (8 bytes): `[op u8][fp_rel u8][pad u16][operand u32]`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Insn {
    pub op: u8,
    /// byte 1: when non-zero the operand is relative to the frame base register `bp` (`operand += fp`).
    pub rel: bool,
    pub operand: i32,
}

impl Insn {
    pub fn from_bytes(c: &[u8]) -> Insn {
        Insn { op: c[0], rel: c[1] != 0, operand: i32::from_le_bytes([c[4], c[5], c[6], c[7]]) }
    }
}

/// The `HECO` section (VSM bytecode image).
pub struct Heco {
    pub version: u32,
    /// initial `pc` of the main thread (the start stub `setbp; call main; end`).
    pub entry: u32,
    /// initial data segment image (`SGCN`), copied to offset 0 of the 40000 byte data memory.
    pub dseg: Vec<u8>,
    pub code: Vec<Insn>,
}

impl Heco {
    /// Layout: `"HECO"`, u32 version (3), u32 off(SGCN) (+8), u32 off(SGCD) (+0xc), u32 entry pc (+0x10).
    /// `SGCN`: magic, u32 size (<= 40000, +4), 8 zero bytes, data at +0x10.
    /// `SGCD`: magic, u32 instruction count (+4), 8 zero bytes, instructions at +0x10.
    pub fn parse(sec: &[u8]) -> Result<Self, EfmgError> {
        Self::parse_with(sec, false)
    }

    /// `lenient`: clamp the instruction count to the bytes that are really there (used when scanning an archive
    /// with a fixed-size window); strict mode rejects a truncated `SGCD` like the loader's size checks would.
    pub fn parse_with(sec: &[u8], lenient: bool) -> Result<Self, EfmgError> {
        if sec.get(0..4) != Some(b"HECO") {
            return Err(EfmgError::Heco("magic"));
        }
        let version = rd_u32(sec, 4).ok_or(EfmgError::Heco("truncated"))?;
        if version != 3 {
            return Err(EfmgError::Heco("version != 3"));
        }
        let doff = rd_u32(sec, 8).ok_or(EfmgError::Heco("truncated"))? as usize;
        let ioff = rd_u32(sec, 0xc).ok_or(EfmgError::Heco("truncated"))? as usize;
        let entry = rd_u32(sec, 0x10).ok_or(EfmgError::Heco("truncated"))?;
        if sec.get(doff..doff + 4) != Some(b"SGCN") {
            return Err(EfmgError::Heco("SGCN magic"));
        }
        let dsz = rd_u32(sec, doff + 4).ok_or(EfmgError::Heco("truncated"))? as usize;
        if dsz > 40000 {
            return Err(EfmgError::Heco("data segment > 40000"));
        }
        let dseg = sec.get(doff + 16..doff + 16 + dsz).ok_or(EfmgError::Heco("truncated"))?.to_vec();
        if sec.get(ioff..ioff + 4) != Some(b"SGCD") {
            return Err(EfmgError::Heco("SGCD magic"));
        }
        let mut n = rd_u32(sec, ioff + 4).ok_or(EfmgError::Heco("truncated"))? as usize;
        if lenient {
            n = n.min(sec.len().saturating_sub(ioff + 16) / 8);
        }
        let raw = sec.get(ioff + 16..ioff + 16 + n * 8).ok_or(EfmgError::Heco("truncated"))?;
        let code = raw.chunks_exact(8).map(Insn::from_bytes).collect();
        Ok(Heco { version, entry, dseg, code })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn build() -> Vec<u8> {
        // two sections: C at 0x40, M at 0x100
        let mut f = vec![0x40u8; 0x200];
        f[0..4].copy_from_slice(b"EFMG");
        f[4..6].copy_from_slice(&2u16.to_le_bytes());
        f[6..8].copy_from_slice(&1u16.to_le_bytes());
        f[8..16].fill(0);
        f[0x10] = b'C';
        f[0x11] = 0;
        f[0x12..0x14].fill(0);
        f[0x14..0x18].copy_from_slice(&0x40u32.to_le_bytes());
        f[0x18] = b'M';
        f[0x19] = 3;
        f[0x1a..0x1c].fill(0);
        f[0x1c..0x20].copy_from_slice(&0x100u32.to_le_bytes());
        f
    }

    #[test]
    fn directory() {
        let f = build();
        let e = Efmg::parse(&f).unwrap();
        assert_eq!(e.entries.len(), 2);
        assert_eq!(e.find(b'M', 3).unwrap().len(), 0x100);
        assert_eq!(e.find(b'C', 0).unwrap().len(), 0xc0);
        assert!(e.find(b'M', 0).is_none());
        // GetDataPtr with mask: A with bit7 set
        assert!(e.get_data_ptr(b'M', 3, None, 0).is_some());
    }

    #[test]
    fn bad_magic() {
        assert!(matches!(Efmg::parse(b"XXXXyyyyyyyyyyyyyyyy"), Err(EfmgError::BadMagic)));
    }

    #[test]
    fn heco_roundtrip() {
        let mut s = vec![0u8; 0x200];
        s[0..4].copy_from_slice(b"HECO");
        s[4..8].copy_from_slice(&3u32.to_le_bytes());
        s[8..12].copy_from_slice(&0x20u32.to_le_bytes());
        s[12..16].copy_from_slice(&0x60u32.to_le_bytes());
        s[16..20].copy_from_slice(&1u32.to_le_bytes());
        s[0x20..0x24].copy_from_slice(b"SGCN");
        s[0x24..0x28].copy_from_slice(&8u32.to_le_bytes());
        s[0x30..0x38].copy_from_slice(&[1, 2, 3, 4, 5, 6, 7, 8]);
        s[0x60..0x64].copy_from_slice(b"SGCD");
        s[0x64..0x68].copy_from_slice(&2u32.to_le_bytes());
        // insn 0: push 5 (op 28), insn 1: end (op 50)
        s[0x70] = 28;
        s[0x74..0x78].copy_from_slice(&5i32.to_le_bytes());
        s[0x78] = 50;
        let h = Heco::parse(&s).unwrap();
        assert_eq!(h.entry, 1);
        assert_eq!(h.dseg, vec![1, 2, 3, 4, 5, 6, 7, 8]);
        assert_eq!(h.code.len(), 2);
        assert_eq!(h.code[0], Insn { op: 28, rel: false, operand: 5 });
    }
}

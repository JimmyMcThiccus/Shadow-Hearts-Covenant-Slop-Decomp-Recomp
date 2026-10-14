//! The `SBD` container shared by battle backgrounds (`BTLDATA/BBG/%03d.BBG` section `mbs`) and field maps (`FIELD/MPS/*.MPS`): `CBgElement::Create` /
//! `CSTGDB` (JP 0x003c30a0 / 0x003c1f60).  A 0x20 byte file header is followed by a `LINKHDR` table (at `u32 +0x1c`, count at `+8`, entries of 0x10 bytes whose last
//! word is the offset of the chunk relative to the entry); every chunk starts with `{ tag[8], u32 count, u32 data offset (relative to the chunk) }`.
//!
//! Chunks decoded here: `FOG`, `BGCOLOR`, `LIGHT` (0x40 byte records, [`decode_lights`]) and `EFFECT` (16 byte records, [`StageEffect`], created by
//! `BgEffectMan::CreateEffect`, see [`super::bgfx`]).

#[derive(Clone, Debug, Default, PartialEq)]
pub struct StageFog {
    pub near: f32,
    pub far: f32,
    pub rgba: [u8; 4],
}

fn u32at(b: &[u8], o: usize) -> Option<u32> {
    b.get(o..o + 4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]]))
}
fn f32at(b: &[u8], o: usize) -> Option<f32> {
    u32at(b, o).map(f32::from_bits)
}

/// One `LIGHT   ` record of the SBD (`CBgElement::Create`, 0x40 bytes).  `SBD 0.11` layout: byte 0 = `kind | decline << 3 | level << 5 | shadow << 7`
/// (kind 0 ambient, 1 directional, 2 point, 3 spot; `level = (b & 0x7f) >> 5`, `decline = (b & 0x1f) >> 3`), byte 1 bit 0 = active, `+4` strength,
/// `+8` spot angle, `+0xc` spot drop-off, `+0x10` colour, `+0x20` position, `+0x30` direction (each an `FVector`).  `SBD 0.10`: word 0 = kind,
/// word 2 = level, everything else fixed (decline 1, active, angle 45, drop-off 1).
#[derive(Clone, Debug, PartialEq)]
pub struct StageLight {
    pub kind: u8,
    pub level: u8,
    pub decline: u8,
    pub shadow: bool,
    pub active: bool,
    pub strength: f32,
    pub angle: f32,
    pub drop_off: f32,
    pub color: [f32; 3],
    pub pos: [f32; 3],
    pub dir: [f32; 3],
}

/// One `EFFECT  ` record (16 bytes: `u16 slot, u16 type, u8 flags (bit 0 = enabled), .., i32 param offset (relative to the record)`),
/// created by `BgEffectMan::CreateEffect(set, index, type, params)`.  `param` holds the bytes from the parameter block to the end of the chunk data
/// (the length is class specific; the `Fp*` parsers read what they need).
#[derive(Clone, Debug, PartialEq)]
pub struct StageEffect {
    pub index: usize,
    pub slot: u16,
    pub kind: u16,
    pub flags: u8,
    pub param: Vec<u8>,
}

/// Everything `CBgElement::Create` reads from an SBD.
#[derive(Clone, Debug, Default, PartialEq)]
pub struct SbdChunks {
    pub fog: Option<StageFog>,
    pub bg_color: Option<[u8; 4]>,
    /// raw `LIGHT` chunk
    pub light: Option<Vec<u8>>,
    pub lights: Vec<StageLight>,
    pub effects: Vec<StageEffect>,
    /// `SBD 0.10` (old light layout)
    pub v10: bool,
}

impl SbdChunks {
    /// The enabled `EFFECT` records (`CBgElement::Create` skips the ones whose flag byte has bit 0 clear) for [`super::bgfx::BgFx`].
    pub fn fx_records(&self) -> Vec<super::bgfx::BgFxRecord> {
        self.effects.iter().filter(|e| e.flags & 1 != 0).map(|e| super::bgfx::BgFxRecord { slot: e.slot, kind: e.kind, param: e.param.clone() }).collect()
    }
}

/// Decode the LIGHT records of an SBD chunk (`CBgElement::Create`).
pub fn decode_lights(raw: &[u8], v10: bool) -> Vec<StageLight> {
    let f = |r: &[u8], o: usize| f32at(r, o).unwrap_or(0.0);
    let v3 = |r: &[u8], o: usize| [f(r, o), f(r, o + 4), f(r, o + 8)];
    raw.chunks_exact(0x40)
        .map(|r| {
            let (kind, level, decline, shadow, active, angle, drop_off) = if v10 {
                (u32at(r, 0).unwrap_or(0) as u8, u32at(r, 8).unwrap_or(0) as u8, 1u8, false, true, 45.0, 1.0)
            } else {
                (r[0] & 7, (r[0] & 0x7f) >> 5, (r[0] & 0x1f) >> 3, r[0] & 0x80 != 0, r[1] & 1 != 0, f(r, 8), f(r, 12))
            };
            StageLight { kind, level, decline, shadow, active, strength: f(r, 4), angle, drop_off, color: v3(r, 0x10), pos: v3(r, 0x20), dir: v3(r, 0x30) }
        })
        .collect()
}

/// `CBgElement::Create`: walk the `LINKHDR` table of an SBD and decode the chunks the battle / field engine uses.
pub fn parse_sbd_full(m: &[u8]) -> SbdChunks {
    let mut out = SbdChunks::default();
    // CheckVersion("SBD 0.10"): the file starts with the 8 byte tag
    out.v10 = m.get(0..8) == Some(b"SBD 0.10");
    let Some(hdr) = u32at(m, 0x1c).map(|v| v as usize) else { return out };
    let (Some(count), Some(tbl)) = (u32at(m, hdr + 8), u32at(m, hdr + 0xc)) else { return out };
    for e in 0..count.min(64) as usize {
        let entry = hdr + tbl as usize + e * 0x10;
        let Some(rel) = u32at(m, entry + 0xc) else { break };
        let chunk = entry + rel as usize;
        let (Some(tag), Some(size), Some(drel)) = (m.get(chunk..chunk + 8), u32at(m, chunk + 8), u32at(m, chunk + 0xc)) else { continue };
        let data = chunk + drel as usize;
        match tag {
            b"FOG     " => {
                if let (Some(near), Some(far), Some(c)) = (f32at(m, data), f32at(m, data + 4), m.get(data + 8..data + 12)) {
                    out.fog = Some(StageFog { near, far, rgba: [c[0], c[1], c[2], c[3]] });
                }
            }
            b"BGCOLOR " => {
                if let Some(c) = m.get(data..data + 4) {
                    out.bg_color = Some([c[0], c[1], c[2], c[3]]);
                }
            }
            b"LIGHT   " => {
                // `size` = record count (GetDataNum); each record is 0x40 bytes
                let bytes = (size as usize * 0x40).min(m.len().saturating_sub(data));
                if let Some(s) = m.get(data..data + bytes) {
                    out.light = Some(s.to_vec());
                    out.lights = decode_lights(s, out.v10);
                }
            }
            b"EFFECT  " => {
                for i in 0..size.min(64) as usize {
                    let rec = data + i * 0x10;
                    let (Some(slot), Some(kind), Some(flags), Some(off)) = (m.get(rec..rec + 2), m.get(rec + 2..rec + 4), m.get(rec + 4), u32at(m, rec + 8)) else { break };
                    let p = rec + off as usize;
                    let end = (p + 0x400).min(m.len());
                    let param = m.get(p..end).map(|s| s.to_vec()).unwrap_or_default();
                    out.effects.push(StageEffect { index: i, slot: u16::from_le_bytes([slot[0], slot[1]]), kind: u16::from_le_bytes([kind[0], kind[1]]), flags: *flags, param });
                }
            }
            _ => {}
        }
    }
    out
}


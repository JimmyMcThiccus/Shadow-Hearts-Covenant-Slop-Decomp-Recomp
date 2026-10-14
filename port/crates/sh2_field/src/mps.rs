//! MPS field-map package ("SBD 0.11" container) parser.
//!
//! JP: 0x003c1f60..0x003c2780 `CSTGDB` (main exe) — container loader; consumers are `CField::InitSDB`
//! (JP 0x004ab860), `CFloorMan::SetData` (0x004bc900), `CFieldBG::Create` (0x004da750), `CFieldEvent::Init`
//! (0x004bf020), `CNaviMap::SetData`, `CField::AutoLoadSE` (0x004d5f10), `CField::Polling` (MONSET encounter roll).
//! Full format description: `notes/G/mps_format.md`.
//!
//! The parser keeps the file as one `Vec<u8>` and hands out typed views; nothing is relocated in place (the
//! original relocates offsets to pointers on load).

use std::fmt;

#[derive(Debug, thiserror::Error)]
pub enum MpsError {
    #[error("file too small")]
    TooSmall,
    #[error("bad magic (expected `SBD 0.10`/`SBD 0.11`)")]
    BadMagic,
    #[error("bad FILEHDR/LINKHDR")]
    BadHeader,
    #[error("chunk `{0}` runs outside the file")]
    OutOfRange(String),
}

pub fn rd_u16(d: &[u8], o: usize) -> u16 {
    u16::from_le_bytes([d[o], d[o + 1]])
}
pub fn rd_u32(d: &[u8], o: usize) -> u32 {
    u32::from_le_bytes(d[o..o + 4].try_into().unwrap())
}
pub fn rd_f32(d: &[u8], o: usize) -> f32 {
    f32::from_le_bytes(d[o..o + 4].try_into().unwrap())
}
pub fn rd_v4(d: &[u8], o: usize) -> [f32; 4] {
    [rd_f32(d, o), rd_f32(d, o + 4), rd_f32(d, o + 8), rd_f32(d, o + 12)]
}
fn cstr(d: &[u8]) -> String {
    let n = d.iter().position(|&b| b == 0).unwrap_or(d.len());
    String::from_utf8_lossy(&d[..n]).into_owned()
}

/// 8-byte ASCII chunk tag (space padded), e.g. `b"TRIANGLE"`, `b"SLICE   "`.
#[derive(Clone, Copy, PartialEq, Eq)]
pub struct Tag(pub [u8; 8]);
impl Tag {
    pub const fn new(s: &[u8; 8]) -> Self {
        Tag(*s)
    }
    /// The 64-bit constant the original compares against (`CSTGDB::Find(unsigned long)`).
    pub fn as_u64(&self) -> u64 {
        u64::from_le_bytes(self.0)
    }
}
impl fmt::Debug for Tag {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", String::from_utf8_lossy(&self.0).trim_end())
    }
}

pub mod tags {
    use super::Tag;
    pub const FIELD: Tag = Tag::new(b"FIELD   ");
    pub const MODEL: Tag = Tag::new(b"MODEL   ");
    pub const LIGHT: Tag = Tag::new(b"LIGHT   ");
    pub const WORLD: Tag = Tag::new(b"WORLD   ");
    pub const ENTRYPOS: Tag = Tag::new(b"ENTRYPOS");
    pub const CAMERA: Tag = Tag::new(b"CAMERA  ");
    pub const FOG: Tag = Tag::new(b"FOG     ");
    pub const EVENTBOX: Tag = Tag::new(b"EVENTBOX");
    pub const CAMEVENT: Tag = Tag::new(b"CAMEVENT");
    pub const EFFECT: Tag = Tag::new(b"EFFECT  ");
    pub const VERTEX: Tag = Tag::new(b"VERTEX  ");
    pub const TRIANGLE: Tag = Tag::new(b"TRIANGLE");
    pub const SLICE: Tag = Tag::new(b"SLICE   ");
    pub const OBJSE: Tag = Tag::new(b"OBJSE   ");
    pub const MONSET: Tag = Tag::new(b"MONSET  ");
    pub const NAVIMAP: Tag = Tag::new(b"NAVIMAP ");
    pub const ENMYPATH: Tag = Tag::new(b"ENMYPATH");
    pub const GENERIC: Tag = Tag::new(b"GENERIC ");
    /// Referenced by the code, absent from the JP demo maps but present in the US retail ones (23 / 49 of 559):
    pub const MIRROR: Tag = Tag::new(b"MIRROR  ");
    pub const BGCOLOR: Tag = Tag::new(b"BGCOLOR ");
}

/// `SDB::tagHEADER` — 0x20-byte chunk header.
#[derive(Debug, Clone)]
pub struct Chunk {
    pub tag: Tag,
    /// Absolute offset of the chunk header in the file.
    pub hdr: usize,
    /// `+0x08` record count (for `FIELD` it is the ASCII version string instead).
    pub count: u32,
    /// `+0x0c` offset of the first record from the header start (always 0x20 in shipped data).
    pub data_off: u32,
    /// `+0x10` flag word; `CFloorMan::SetData` sets it to 1 once the chunk has been relocated.
    pub relocated: u32,
}

impl Chunk {
    pub fn data_start(&self) -> usize {
        self.hdr + self.data_off as usize
    }
}

pub struct Mps {
    pub data: Vec<u8>,
    pub version_minor: u8,
    pub chunks: Vec<Chunk>,
}

impl Mps {
    /// Parse the container (JP: `CSTGDB::InitSDB`, 0x003c2170).
    pub fn parse(data: Vec<u8>) -> Result<Self, MpsError> {
        if data.len() < 0x40 {
            return Err(MpsError::TooSmall);
        }
        // "SBD 0.10" / "SBD 0.11" (u64 compare in the original), then date stamp "01110623", "FILEHDR ".
        if &data[0..7] != b"SBD 0.1" || !(data[7] == b'0' || data[7] == b'1') {
            return Err(MpsError::BadMagic);
        }
        if &data[8..16] != b"01110623" || &data[16..24] != b"FILEHDR " {
            return Err(MpsError::BadHeader);
        }
        let link = rd_u32(&data, 0x1c) as usize;
        if link + 16 > data.len() || &data[link..link + 8] != b"LINKHDR " {
            return Err(MpsError::BadHeader);
        }
        let n = rd_u32(&data, link + 8) as usize;
        let eoff = rd_u32(&data, link + 12) as usize;
        if n == 0 {
            return Err(MpsError::BadHeader);
        }
        let mut chunks = Vec::with_capacity(n);
        for i in 0..n {
            let e = link + eoff + i * 16;
            if e + 16 > data.len() {
                return Err(MpsError::BadHeader);
            }
            // entry+0xc = offset of the chunk header relative to the entry itself
            let hdr = e + rd_u32(&data, e + 12) as usize;
            if hdr + 0x20 > data.len() {
                return Err(MpsError::BadHeader);
            }
            let mut t = [0u8; 8];
            t.copy_from_slice(&data[hdr..hdr + 8]);
            chunks.push(Chunk {
                tag: Tag(t),
                hdr,
                count: rd_u32(&data, hdr + 8),
                data_off: rd_u32(&data, hdr + 12),
                relocated: rd_u32(&data, hdr + 16),
            });
        }
        Ok(Mps { version_minor: data[7] - b'0', data, chunks })
    }

    pub fn file_size_field(&self) -> u32 {
        rd_u32(&self.data, 0x18)
    }

    /// `CSTGDB::Find(tag)`.
    pub fn find(&self, tag: Tag) -> Option<&Chunk> {
        self.chunks.iter().find(|c| c.tag == tag)
    }

    fn recs(&self, tag: Tag, stride: usize) -> Result<Option<(&Chunk, &[u8])>, MpsError> {
        let Some(c) = self.find(tag) else { return Ok(None) };
        let s = c.data_start();
        let e = s + c.count as usize * stride;
        if e > self.data.len() {
            return Err(MpsError::OutOfRange(format!("{tag:?}")));
        }
        Ok(Some((c, &self.data[s..e])))
    }

    /// Payload bytes of a chunk up to the next chunk header (or to the end of the table area).
    pub fn payload(&self, tag: Tag) -> Option<&[u8]> {
        let c = self.find(tag)?;
        let s = c.data_start();
        let end = self
            .chunks
            .iter()
            .map(|x| x.hdr)
            .filter(|&h| h > c.hdr)
            .min()
            .unwrap_or(self.data.len());
        Some(&self.data[s.min(self.data.len())..end.min(self.data.len())])
    }

    // ---------------------------------------------------------------- typed views

    pub fn field_header(&self) -> Option<FieldHeader> {
        let c = self.find(tags::FIELD)?;
        let h = c.hdr;
        let mut ver = [0u8; 8];
        ver.copy_from_slice(&self.data[h + 8..h + 16]);
        Some(FieldHeader {
            version: ver,
            field_byte: rd_u16(&self.data, h + 0x10) as u8,
            flags: rd_u16(&self.data, h + 0x12),
            layer_mode: self.data[h + 0x14],
        })
    }

    pub fn models(&self) -> Result<Vec<ModelRec>, MpsError> {
        let Some((c, b)) = self.recs(tags::MODEL, 64)? else { return Ok(vec![]) };
        let base = c.data_start();
        Ok((0..c.count as usize)
            .map(|i| {
                let r = &b[i * 64..i * 64 + 64];
                ModelRec {
                    name: cstr(&r[..16]),
                    kind: ModelKind::from(r[0x10]),
                    flags: r[0x11],
                    data_off: rd_u32(r, 0x14),
                    data_abs: base + i * 64 + rd_u32(r, 0x14) as usize,
                    target_model: rd_u32(r, 0x1c),
                    pos: rd_v4(r, 0x20),
                    rot: rd_v4(r, 0x30),
                }
            })
            .collect())
    }

    /// Embedded blob of a MODEL record (up to the next record's blob or EOF).
    pub fn model_blob(&self, m: &ModelRec) -> &[u8] {
        let mut starts: Vec<usize> = self
            .models()
            .unwrap_or_default()
            .iter()
            .map(|x| x.data_abs)
            .filter(|&a| a > m.data_abs)
            .collect();
        starts.sort_unstable();
        let end = starts.first().copied().unwrap_or(self.data.len());
        &self.data[m.data_abs.min(self.data.len())..end.min(self.data.len())]
    }

    pub fn lights(&self) -> Result<Vec<LightRec>, MpsError> {
        let Some((c, b)) = self.recs(tags::LIGHT, 64)? else { return Ok(vec![]) };
        Ok((0..c.count as usize)
            .map(|i| {
                let r = &b[i * 64..i * 64 + 64];
                LightRec {
                    kind: r[0] & 0x1f,
                    flags: rd_u32(r, 0) >> 5,
                    intensity: rd_f32(r, 4),
                    color: rd_v4(r, 0x10),
                    pos: rd_v4(r, 0x20),
                    raw: r.try_into().unwrap(),
                }
            })
            .collect())
    }

    pub fn world(&self) -> Result<Option<World>, MpsError> {
        let Some((_, b)) = self.recs(tags::WORLD, 32)? else { return Ok(None) };
        Ok(Some(World {
            size_x: rd_f32(b, 0),
            size_z: rd_f32(b, 4),
            slices_along_x: rd_u32(b, 8),
            slices_along_z: rd_u32(b, 12),
            origin_x: rd_f32(b, 0x10),
            origin_z: rd_f32(b, 0x14),
            unk18: rd_f32(b, 0x18),
            unk1c: rd_f32(b, 0x1c),
        }))
    }

    pub fn entry_points(&self) -> Result<Vec<EntryPoint>, MpsError> {
        let Some((c, b)) = self.recs(tags::ENTRYPOS, 16)? else { return Ok(vec![]) };
        Ok((0..c.count as usize)
            .map(|i| EntryPoint {
                pos: [rd_f32(b, i * 16), rd_f32(b, i * 16 + 4), rd_f32(b, i * 16 + 8)],
                dir: b[i * 16 + 12] as i8,
            })
            .collect())
    }

    pub fn fog(&self) -> Result<Option<Fog>, MpsError> {
        let Some((_, b)) = self.recs(tags::FOG, 16)? else { return Ok(None) };
        let col = rd_u32(b, 8);
        Ok(Some(Fog { near: rd_f32(b, 0), far: rd_f32(b, 4), color_rgba: col }))
    }

    pub fn event_boxes(&self) -> Result<Vec<EventBox>, MpsError> {
        self.event_recs(tags::EVENTBOX)
    }
    /// CAMEVENT shares the EVENTBOX record layout; `id` is the index into the CAMERA table.
    pub fn camera_events(&self) -> Result<Vec<EventBox>, MpsError> {
        self.event_recs(tags::CAMEVENT)
    }
    fn event_recs(&self, tag: Tag) -> Result<Vec<EventBox>, MpsError> {
        let Some((c, b)) = self.recs(tag, 0x70)? else { return Ok(vec![]) };
        Ok((0..c.count as usize)
            .map(|i| {
                let r = &b[i * 0x70..i * 0x70 + 0x70];
                let mut corners = [[0f32; 3]; 4];
                for (k, c) in corners.iter_mut().enumerate() {
                    // x, half-height (only corner 0 is used), z
                    *c = [rd_f32(r, 0x30 + k * 16), rd_f32(r, 0x34 + k * 16), rd_f32(r, 0x38 + k * 16)];
                }
                EventBox {
                    unk0: rd_u32(r, 0),
                    id: rd_u32(r, 4) as i32,
                    group: r[8] & 0x0f,
                    kind: (r[8] & 0x3f) >> 4,
                    flags: r[8],
                    center: rd_v4(r, 0x10),
                    rot_a: rd_f32(r, 0x20),
                    rot_b: rd_f32(r, 0x24),
                    corners,
                }
            })
            .collect())
    }

    /// CAMERA chunk: `count` 16-byte index entries followed by variable-size blobs.
    pub fn cameras(&self) -> Result<Vec<CameraDef>, MpsError> {
        let Some((c, b)) = self.recs(tags::CAMERA, 16)? else { return Ok(vec![]) };
        let base = c.data_start();
        let mut out = vec![];
        for i in 0..c.count as usize {
            let kind = rd_u32(b, i * 16);
            let count = rd_u32(b, i * 16 + 4);
            let off = rd_u32(b, i * 16 + 8) as usize;
            let flag = b[i * 16 + 12];
            out.push(CameraDef { index: i, kind, count, flag, blob_abs: base + i * 16 + off });
        }
        Ok(out)
    }

    pub fn effects(&self) -> Result<Vec<EffectRec>, MpsError> {
        let Some((c, b)) = self.recs(tags::EFFECT, 136)? else { return Ok(vec![]) };
        Ok((0..c.count as usize)
            .map(|i| {
                let r = &b[i * 136..i * 136 + 136];
                EffectRec { raw: r.to_vec() }
            })
            .collect())
    }

    pub fn floor(&self) -> Result<Option<crate::floor::FloorData>, MpsError> {
        crate::floor::FloorData::from_mps(self)
    }

    pub fn monster_sets(&self) -> Result<Option<MonSet>, MpsError> {
        let Some(c) = self.find(tags::MONSET) else { return Ok(None) };
        let h = c.hdr;
        let d = &self.data;
        let entries = (0..c.count as usize)
            .map(|i| {
                let o = c.data_start() + i * 4;
                (rd_u16(d, o), d[o + 2])
            })
            .collect();
        Ok(Some(MonSet { encounter_rate: d[h + 0x14], field_data6: rd_u16(d, h + 0x16), field_data7: rd_u16(d, h + 0x18), entries }))
    }

    pub fn objse(&self) -> Option<ObjSe> {
        let c = self.find(tags::OBJSE)?;
        let s = c.data_start();
        let d = &self.data;
        Some(ObjSe {
            count: rd_u16(d, s),
            unk2: rd_u16(d, s + 2),
            sound_data: rd_u16(d, s + 4),
            banks: [cstr(&d[s + 0x10..s + 0x20]), cstr(&d[s + 0x20..s + 0x30]), cstr(&d[s + 0x30..s + 0x40])],
            entries_off: s + 0x60,
        })
    }

    pub fn enemy_paths(&self) -> Result<Vec<EnemyPath>, MpsError> {
        let Some((c, b)) = self.recs(tags::ENMYPATH, 16)? else { return Ok(vec![]) };
        let base = c.data_start();
        let mut out = vec![];
        for i in 0..c.count as usize {
            let n = rd_u16(b, i * 16 + 10) as usize;
            let off = rd_u32(b, i * 16 + 12) as usize;
            let abs = base + i * 16 + off;
            let mut pts = vec![];
            for k in 0..n {
                let o = abs + k * 16;
                if o + 16 > self.data.len() {
                    return Err(MpsError::OutOfRange("ENMYPATH".into()));
                }
                pts.push(PathPoint { pos: [rd_f32(&self.data, o), rd_f32(&self.data, o + 4), rd_f32(&self.data, o + 8)], flags: rd_u32(&self.data, o + 12) });
            }
            out.push(EnemyPath { arg: rd_u16(b, i * 16 + 8), points: pts });
        }
        Ok(out)
    }

    /// MIRROR chunk (retail only): `count` 0x30-byte records = three vec4 triangle corners of a planar mirror
    /// (`CFieldBG::CheckMirror`, JP 0x004dafb0). Present in 23 of 559 US maps, none of the JP demo maps.
    pub fn mirrors(&self) -> Result<Vec<[[f32; 4]; 3]>, MpsError> {
        let Some((c, b)) = self.recs(tags::MIRROR, 0x30)? else { return Ok(vec![]) };
        Ok((0..c.count as usize)
            .map(|i| [rd_v4(b, i * 0x30), rd_v4(b, i * 0x30 + 0x10), rd_v4(b, i * 0x30 + 0x20)])
            .collect())
    }

    /// BGCOLOR chunk (retail only): first u32 = background clear colour (`CFieldBG::Dsp` → `GsxCamera::SetBgColor`).
    pub fn bg_color(&self) -> Option<u32> {
        let c = self.find(tags::BGCOLOR)?;
        let s = c.data_start();
        (s + 4 <= self.data.len()).then(|| rd_u32(&self.data, s))
    }

    /// GENERIC chunk: named opaque blocks (`CSTGDB::FindGenericData`, e.g. "VIBRATION").
    pub fn generic(&self) -> Vec<(String, &[u8])> {
        let Some(c) = self.find(tags::GENERIC) else { return vec![] };
        let mut out = vec![];
        let mut o = c.data_start();
        for _ in 0..c.count {
            if o + 0x20 > self.data.len() {
                break;
            }
            let stride = rd_u32(&self.data, o + 0x10) as usize;
            if stride < 0x20 || o + stride > self.data.len() {
                break;
            }
            out.push((cstr(&self.data[o..o + 16]), &self.data[o + 0x20..o + stride]));
            o += stride;
        }
        out
    }

    /// NAVIMAP payload starts with `"NAVM"` (`_NaviMapDataHdr`).
    pub fn navimap(&self) -> Option<NaviMapHeader> {
        let c = self.find(tags::NAVIMAP)?;
        let s = c.data_start();
        let d = &self.data;
        if &d[s..s + 4] != b"NAVM" {
            return None;
        }
        Some(NaviMapHeader {
            version: rd_u16(d, s + 4),
            hdr_size: rd_u16(d, s + 6),
            total_size: rd_u32(d, s + 8),
            width: rd_u16(d, s + 12),
            height: rd_u16(d, s + 14),
            origin_x: rd_f32(d, s + 16),
            origin_z: rd_f32(d, s + 20),
        })
    }
}

#[derive(Debug, Clone)]
pub struct FieldHeader {
    /// ASCII, e.g. `"1.309220"`.
    pub version: [u8; 8],
    pub field_byte: u8,
    /// bit0 → CFieldBG flag (`+0x1c4 bit1`).
    pub flags: u16,
    /// non-zero → `LayerMan_LoadLayer(0x558ff0)` (alternate layer table).
    pub layer_mode: u8,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ModelKind {
    /// 0: BG model with shadow caster flag (SetModel flag +0x81)
    Bg0,
    /// 1: BG model receiving shadows (flag +0x82)
    Bg1,
    /// 2: plain BG model
    Bg2,
    /// 3: motion (`createMotion`) for model index `target_model`
    Motion,
    Other(u8),
}
impl From<u8> for ModelKind {
    fn from(v: u8) -> Self {
        match v {
            0 => Self::Bg0,
            1 => Self::Bg1,
            2 => Self::Bg2,
            3 => Self::Motion,
            x => Self::Other(x),
        }
    }
}

#[derive(Debug, Clone)]
pub struct ModelRec {
    pub name: String,
    pub kind: ModelKind,
    pub flags: u8,
    pub data_off: u32,
    pub data_abs: usize,
    pub target_model: u32,
    pub pos: [f32; 4],
    pub rot: [f32; 4],
}

#[derive(Debug, Clone)]
pub struct LightRec {
    pub kind: u8,
    pub flags: u32,
    pub intensity: f32,
    pub color: [f32; 4],
    pub pos: [f32; 4],
    pub raw: [u8; 64],
}

#[derive(Debug, Clone, Copy)]
pub struct World {
    pub size_x: f32,
    pub size_z: f32,
    /// `!= 0`: floor is sliced along X into this many slices (`CFloorMan+0x14 == 0`).
    pub slices_along_x: u32,
    /// used when `slices_along_x == 0`: slices along Z.
    pub slices_along_z: u32,
    pub origin_x: f32,
    pub origin_z: f32,
    pub unk18: f32,
    pub unk1c: f32,
}

#[derive(Debug, Clone, Copy)]
pub struct EntryPoint {
    pub pos: [f32; 3],
    /// facing in 1/256 turn units passed to `CFieldModel::SetDir(dir, 2, 0)`.
    pub dir: i8,
}

#[derive(Debug, Clone, Copy)]
pub struct Fog {
    pub near: f32,
    pub far: f32,
    /// memory order R,G,B,A bytes of the u32 (`0x00c8b48c` => R=0x8c,G=0xb4,B=0xc8).
    pub color_rgba: u32,
}

#[derive(Debug, Clone)]
pub struct EventBox {
    pub unk0: u32,
    /// EVENTBOX: event/script id; CAMEVENT: CAMERA table index.
    pub id: i32,
    pub group: u8,
    pub kind: u8,
    pub flags: u8,
    pub center: [f32; 4],
    pub rot_a: f32,
    pub rot_b: f32,
    /// four XZ corners (index 1 of corner 0 is the half height).
    pub corners: [[f32; 3]; 4],
}

#[derive(Debug, Clone)]
pub struct CameraDef {
    pub index: usize,
    /// 0 fixed, 1 follow-height, 2 player-relative, 3 pivot with limits, 4 pivot+path, 5 spline path.
    pub kind: u32,
    pub count: u32,
    /// `m_pCAMDAT[3]` byte — non-zero allows `CompFrame` blending with the previous camera.
    pub flag: u8,
    pub blob_abs: usize,
}

#[derive(Debug, Clone)]
pub struct EffectRec {
    pub raw: Vec<u8>,
}

#[derive(Debug, Clone)]
pub struct MonSet {
    pub encounter_rate: u8,
    pub field_data6: u16,
    pub field_data7: u16,
    /// (monster-set id, weight in percent); `CField::Polling` rolls `rand()%100` against the running sum.
    pub entries: Vec<(u16, u8)>,
}

#[derive(Debug, Clone)]
pub struct ObjSe {
    pub count: u16,
    pub unk2: u16,
    pub sound_data: u16,
    pub banks: [String; 3],
    pub entries_off: usize,
}

#[derive(Debug, Clone)]
pub struct PathPoint {
    pub pos: [f32; 3],
    pub flags: u32,
}
#[derive(Debug, Clone)]
pub struct EnemyPath {
    pub arg: u16,
    pub points: Vec<PathPoint>,
}

#[derive(Debug, Clone, Copy)]
pub struct NaviMapHeader {
    pub version: u16,
    pub hdr_size: u16,
    pub total_size: u32,
    pub width: u16,
    pub height: u16,
    pub origin_x: f32,
    pub origin_z: f32,
}

impl Mps {
    /// Camera blob accessor (see [`crate::camera`] for the per-kind interpretation).
    pub fn camera_blob(&self, c: &CameraDef) -> &[u8] {
        let len = if c.kind == 5 { (c.count as usize * 0x40).max(0x60) } else { 0x60 };
        let end = (c.blob_abs + len).min(self.data.len());
        &self.data[c.blob_abs.min(self.data.len())..end]
    }
}

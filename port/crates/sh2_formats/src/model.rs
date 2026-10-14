//! Parser for the `SSH1.01a` model file ("mdl") — see `notes/C/model_format.md`.
//!
//! The file is the image that `Model::create(unsigned char*)` (JP 0x0023e710)
//! walks in place.  Everything is little-endian; sections are located through
//! the 0x30-byte file header; atomic vertex arrays are padded to 16 bytes
//! relative to the (16-byte aligned) start of the file.
//!
//! Decoded here: header, frame (bone) table, atomics (all inline-geometry
//! variants seen in the shipped PKBs), texture table (PSMT4/PSMT8 + CLUT),
//! bounding-box table, texture-animation table (raw), extension blocks (raw).

use crate::math::{FVector, Quaternion};
use thiserror::Error;

pub const MODEL_MAGIC: &[u8; 8] = b"SSH1.01a";

#[derive(Debug, Error)]
pub enum ModelError {
    #[error("bad magic")]
    BadMagic,
    #[error("truncated data at {0:#x}")]
    Truncated(usize),
    #[error("bad section tag at {0:#x}: expected {1}")]
    BadTag(usize, &'static str),
    #[error("unsupported atomic variant `{name}` (b14={b14:#x} b15={b15:#x}) at {at:#x}")]
    UnsupportedAtomic { name: String, b14: u8, b15: u8, at: usize },
}

pub type Result<T> = std::result::Result<T, ModelError>;

fn align16(x: usize) -> usize {
    (x + 15) & !15
}

fn u8_at(d: &[u8], o: usize) -> Result<u8> {
    d.get(o).copied().ok_or(ModelError::Truncated(o))
}
fn u16_at(d: &[u8], o: usize) -> Result<u16> {
    d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]])).ok_or(ModelError::Truncated(o))
}
fn i16_at(d: &[u8], o: usize) -> Result<i16> {
    u16_at(d, o).map(|v| v as i16)
}
fn u32_at(d: &[u8], o: usize) -> Result<u32> {
    d.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]])).ok_or(ModelError::Truncated(o))
}
fn f32_at(d: &[u8], o: usize) -> Result<f32> {
    u32_at(d, o).map(f32::from_bits)
}
fn name_at(d: &[u8], o: usize, n: usize) -> Result<String> {
    let b = d.get(o..o + n).ok_or(ModelError::Truncated(o))?;
    let end = b.iter().position(|&c| c == 0).unwrap_or(n);
    Ok(b[..end].iter().map(|&c| c as char).collect())
}

/// File header (0x30 bytes).  Offsets are relative to the start of the file.
#[derive(Clone, Debug, Default)]
pub struct ModelHeader {
    /// +0x08: observed `0x0011_0004` or `0x000e_0004`.  Byte 10 is the geometry flag
    /// byte used by `Model::setAtomic` (bits 0-1 != 0: has vertex data, bit 2: float
    /// "Pack2"/PLP2 layout instead of s16 "Pack1"/PLP1).
    pub flags: u32,
    /// +0x0c `ATHD` atomic section.
    pub atomics_off: u32,
    /// +0x10 `FRHD` frame section.
    pub frames_off: u32,
    /// +0x14 always 0 in shipped data.
    pub reserved14: u32,
    /// +0x18 `TXHD` texture section, 0 / 0xFFFFFFFF = none.
    pub textures_off: u32,
    /// +0x1c `BBHD` bounding box table (immediately follows the last atomic).
    pub bounds_off: u32,
    /// +0x20 blend shape block (0 in all shipped models; `BlendShapeControl::create`).
    pub blendshape_off: u32,
    /// +0x24 `TXAH` texture animation table, 0 = none.
    pub texanim_off: u32,
    /// +0x28 chain of `EXHD` extension blocks, 0 = none.
    pub ext_off: u32,
}

impl ModelHeader {
    pub fn geometry_flags(&self) -> u8 {
        (self.flags >> 16) as u8
    }
    pub fn has_vertex_data(&self) -> bool {
        self.geometry_flags() & 3 != 0
    }
    pub fn float_vertices(&self) -> bool {
        self.geometry_flags() & 4 != 0
    }
}

/// `Frame` record in the file (0x40 bytes).  JP: `Frame::Cleate` 0x002436d0.
#[derive(Clone, Debug)]
pub struct FrameDef {
    pub name: String,
    /// byte +0x0c: parent frame index, 0xFF = none.
    pub parent: Option<u8>,
    /// byte +0x0d: first child, 0xFF = none.
    pub child: Option<u8>,
    /// byte +0x0e: unknown (0 in nearly all data).
    pub unknown: u8,
    /// byte +0x0f: next sibling, 0xFF = none.
    pub sibling: Option<u8>,
    /// +0x20: bone pivot position (x, y, z, 1) in the *y-up authoring space*.
    pub translation: FVector,
    /// +0x30: bone orientation (usually (-1,0,0,0): 180 degrees around X, i.e. the
    /// y-up -> y-down flip of the PS2 world).
    pub rotation: Quaternion,
}

fn opt_idx(b: u8) -> Option<u8> {
    if b == 0xff { None } else { Some(b) }
}

/// Which `Atomic` subclass the original instantiates (`Model::setAtomic`, 0x0023e510).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum AtomicKind {
    /// `Pack1Atomic`: rigid, s16 positions (1/16 unit), bone = chunk byte 0.
    Pack1,
    /// `Pack2Atomic`: rigid, float positions.
    Pack2,
    /// `SkinAtomicPack2`: float positions, one matrix-palette bone per vertex (see [`SkinVertex`]).
    Skin,
    /// `SkinAtomicPack2NL`: as `Skin` but unlit (colour array instead of normals).
    SkinNL,
    /// `PLP1Atomic` (not present in shipped data).
    Plp1,
    /// `PLP2Atomic` (not present in shipped data).
    Plp2,
    /// `BAtomic`: billboard / sprite quads (5 s16 vec4 per element).
    Billboard,
    /// `WaterAtomicP1`: animated water surface.
    Water,
}

impl AtomicKind {
    /// Per-element byte sizes of the three arrays that follow the atomic header.
    pub fn array_strides(self) -> [usize; 3] {
        match self {
            AtomicKind::Pack1 => [8, 4, 4],
            AtomicKind::Pack2 => [16, 4, 4],
            AtomicKind::Skin => [16, 4, 8],
            AtomicKind::SkinNL => [16, 4, 4],
            AtomicKind::Plp1 => [8, 4, 8],
            AtomicKind::Plp2 => [16, 4, 8],
            AtomicKind::Billboard => [0x28, 4, 0],
            AtomicKind::Water => [8, 4, 4],
        }
    }
    pub fn n_arrays(self) -> usize {
        match self {
            AtomicKind::Billboard => 2,
            _ => 3,
        }
    }
}

/// Classification logic of `Model::setAtomic` (JP 0x0023e510).
pub fn classify_atomic(file_flags_byte10: u8, b14: u8, b15: u8) -> Option<AtomicKind> {
    match (b15 & 0xf) >> 1 {
        7 => return Some(AtomicKind::Water),
        6 => return Some(AtomicKind::Billboard),
        _ => {}
    }
    let lo = b14 & 0xf;
    if b14 & 0x80 != 0 || lo == 0 {
        if lo == 0 {
            return if file_flags_byte10 & 3 != 0 { Some(AtomicKind::Skin) } else { None };
        }
        return Some(AtomicKind::SkinNL);
    }
    if file_flags_byte10 & 3 == 0 {
        return None;
    }
    let f32v = file_flags_byte10 & 4 != 0;
    match lo {
        1 => Some(if f32v { AtomicKind::Pack2 } else { AtomicKind::Pack1 }),
        2 => Some(if f32v { AtomicKind::Plp2 } else { AtomicKind::Plp1 }),
        _ => None,
    }
}

/// Packet-table entry (0x10 bytes) following each atomic's vertex arrays.
///
/// The original turns each into one or more VU1 packets of <= 0x2a vertices.
#[derive(Clone, Copy, Debug)]
pub struct Chunk {
    /// Bytes 0..2.  `Pack1`/`Pack2`: `bones[0]` is the frame the vertices are local to.
    /// `Skin`: the (up to) three frames of the matrix palette; 0xFF = unused.
    pub bones: [u8; 3],
    /// byte 3: nonzero marks the first chunk of the atomic in skin data.
    pub flag: u8,
    /// +4: `atomic_index << 16` (written by the exporter).
    pub tag: u32,
    /// +8: first vertex of the chunk.
    pub start: u32,
    /// +12: vertex count.
    pub count: u32,
}

/// Per-vertex data packed into the `w` word of a skin vertex (`SkinAtomicPack2`).
///
/// Resolved from the VU1 microcode (`_dma_61` 0x003e3e00 / `_dma_202` 0x003e94a0, see `notes/C/model_format.md`):
/// the program does `MTIR vi13, vf15w; IADDIU vi13, vi13, 179; IAND vi13, vi13, 255` -- only the **low 16 bits** of `w`
/// are ever read (matrix register = `179 + slot*5 + bank`, bit 15 = strip ADC) and exactly **one** 4x4 matrix is applied
/// per vertex.  There is no second bone and no blend weight.  The upper 16 bits (bytes 2-3) are a per-vertex identity
/// number that the VU1 never sees (identical positions carry identical ids; the face atomic needs 9 bits).
#[derive(Clone, Copy, Debug, Default)]
pub struct SkinVertex {
    /// Palette slot (0..2) of the vertex's single bone (byte 0 of w); indexes [`Chunk::bones`].
    pub slot: u8,
    /// Vertex identity (bytes 2-3 of w, little endian): shared by all strip copies of one position; ignored by the VU1.
    pub id: u16,
}

impl SkinVertex {
    /// Decode the `w` word of a skin vertex as stored in the file (before `initPacket` patches bytes 0/1).
    pub fn from_w(w: u32) -> SkinVertex {
        SkinVertex { slot: (w & 0x3f) as u8, id: (w >> 16) as u16 }
    }
}

/// Decoded vertex streams of one atomic.
#[derive(Clone, Debug, Default)]
pub struct Geometry {
    pub positions: Vec<[f32; 3]>,
    /// Strip "ADC" flag (bit 15 of w): vertex does not complete a triangle.
    pub adc: Vec<bool>,
    /// UV in [0,1] (u16 / 4096).
    pub uvs: Vec<[f32; 2]>,
    /// RGBA8, 0x80 = 1.0 (PS2 alpha convention).
    pub colors: Vec<[u8; 4]>,
    /// Unit normals (Skin only: s16 / 32768).
    pub normals: Vec<[f32; 3]>,
    pub skin: Vec<SkinVertex>,
    /// Billboard elements: 5 x (x,y,z,w) s16 each (centre + 4 corners).
    pub billboard: Vec<[[i16; 4]; 5]>,
    /// `WaterAtomicP1` only: the low byte of every vertex's `w` word = the wave group whose amplitude / phase drives the vertex's U
    /// coordinate (`WaterAtomicP1::addTime` 0x0025ab60 indexes its random tables with `(char)byte[+6]`).
    pub group: Vec<u8>,
}

#[derive(Clone, Debug)]
pub struct AtomicDef {
    pub name: String,
    pub kind: AtomicKind,
    /// Vertex count (+0x0c).
    pub vertex_count: u32,
    /// +0x10 u16: 0x7c / 0x5c / 0x4c — render flags (bit 2: strip splitting rule of
    /// `calcNeedPacket`).
    pub flags: u16,
    /// +0x12: texture index into the model's texture table, 0xFF = external texture.
    pub texture: u8,
    /// +0x13: second texture / layer, 0xFF = none.
    pub texture2: u8,
    pub b14: u8,
    pub b15: u8,
    pub b16: u8,
    pub b17: u8,
    /// +0x18: -1 = vertex arrays inline; otherwise index of the atomic that owns them.
    pub shared_ref: i16,
    /// +0x1a: u16 (triangle count estimate, not used for decoding).
    pub tri_hint: u16,
    /// +0x20: u32 (0/1).
    pub extra20: u32,
    pub chunks: Vec<Chunk>,
    pub geometry: Geometry,
    /// File offset of the atomic header.
    pub file_offset: usize,
}

impl AtomicDef {
    /// Triangle list reconstructed from the strips (indices into `geometry`).
    pub fn triangles(&self) -> Vec<[u32; 3]> {
        let mut out = Vec::new();
        for ch in &self.chunks {
            let mut k = 0u32;
            for i in ch.start..ch.start + ch.count {
                let adc = self.geometry.adc.get(i as usize).copied().unwrap_or(true);
                if adc {
                    k = 0;
                    continue;
                }
                if i < ch.start + 2 {
                    continue;
                }
                if k & 1 == 0 {
                    out.push([i - 2, i - 1, i]);
                } else {
                    out.push([i - 2, i, i - 1]);
                }
                k += 1;
            }
        }
        out
    }
    /// Frame index each vertex is bound to (Pack1/Pack2: chunk byte 0; Skin: `chunk.bones[slot]`), 0xFF = none.
    ///
    /// Every vertex follows exactly one frame (see [`SkinVertex`]).
    pub fn vertex_bone_indices(&self) -> Vec<u8> {
        let mut v = vec![0xffu8; self.vertex_count as usize];
        for ch in &self.chunks {
            for i in ch.start..ch.start + ch.count {
                if let Some(slot) = v.get_mut(i as usize) {
                    *slot = match self.kind {
                        AtomicKind::Skin | AtomicKind::SkinNL => {
                            let sv = self.geometry.skin.get(i as usize).copied().unwrap_or_default();
                            ch.bones.get(sv.slot as usize).copied().unwrap_or(0xff)
                        }
                        _ => ch.bones[0],
                    };
                }
            }
        }
        v
    }

    /// Like [`Self::vertex_bone_indices`] but vertices whose palette entry names a frame >= `nframes` (the runtime-only
    /// `FRHD` extra frames: face / lip detail bones that have no file record) follow the chunk's first bone.
    pub fn vertex_bone_indices_clamped(&self, nframes: usize) -> Vec<u8> {
        let mut v = self.vertex_bone_indices();
        for ch in &self.chunks {
            for i in ch.start..ch.start + ch.count {
                if let Some(e) = v.get_mut(i as usize) {
                    if *e as usize >= nframes {
                        *e = ch.bones[0];
                    }
                }
            }
        }
        v
    }

    /// Compatibility shim: `(bone, bone, 0)` per vertex.  Older code expected a second bone and a blend weight; the
    /// format has neither.
    pub fn vertex_bones(&self) -> Vec<(u8, u8, u8)> {
        self.vertex_bone_indices().into_iter().map(|b| (b, b, 0)).collect()
    }
}

/// Texture pixel format (`_ModelTextureHeader` +8 & 0x3f).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum TexFormat {
    /// 4-bit paletted (GS PSMT4HH).
    Psmt4,
    /// 8-bit paletted (GS PSMT8H).
    Psmt8,
    /// 32-bit true colour.
    Ct32,
    /// IPU (MPEG-2 intra) compressed (flag 0x40) — not decoded.
    Ipu,
}

#[derive(Clone, Debug)]
pub struct TextureDef {
    pub width: u16,
    pub height: u16,
    pub format: TexFormat,
    pub raw_format: u8,
    pub mip_levels: u8,
    /// CLUT entries as RGBA8 (alpha 0x80 = opaque).
    pub palette: Vec<[u8; 4]>,
    pub data: Vec<u8>,
    /// +0x1c: GS ALPHA / blend bits for `Texture::changeGSAlpha`.
    pub alpha_bits: u16,
    /// +0x1e: alpha-test reference.
    pub alpha_ref: u8,
    pub flags: u8,
    pub file_offset: usize,
}

impl TextureDef {
    /// Decode to RGBA8 with alpha expanded to 0..255 (0x80 -> 255).
    pub fn to_rgba8(&self) -> Vec<u8> {
        let (w, h) = (self.width as usize, self.height as usize);
        let mut out = vec![0u8; w * h * 4];
        let exp = |a: u8| (a as u16 * 2).min(255) as u8;
        for i in 0..w * h {
            let px: [u8; 4] = match self.format {
                TexFormat::Psmt4 => {
                    let b = self.data.get(i >> 1).copied().unwrap_or(0);
                    let idx = if i & 1 == 1 { b >> 4 } else { b & 15 } as usize;
                    let p = self.palette.get(idx).copied().unwrap_or([0; 4]);
                    [p[0], p[1], p[2], exp(p[3])]
                }
                TexFormat::Psmt8 => {
                    let idx = self.data.get(i).copied().unwrap_or(0);
                    // CSM1 CLUT swizzle: bits 3 and 4 of the index are swapped
                    let idx = ((idx & 0xe7) | ((idx & 8) << 1) | ((idx & 16) >> 1)) as usize;
                    let p = self.palette.get(idx).copied().unwrap_or([0; 4]);
                    [p[0], p[1], p[2], exp(p[3])]
                }
                TexFormat::Ct32 => {
                    let o = i * 4;
                    let b = self.data.get(o..o + 4).unwrap_or(&[0, 0, 0, 0]);
                    [b[0], b[1], b[2], exp(b[3])]
                }
                TexFormat::Ipu => [255, 0, 255, 255],
            };
            out[i * 4..i * 4 + 4].copy_from_slice(&px);
        }
        out
    }
}

/// One `TXAD` entry of the `TXAH` table (`TextureAnim::CreateData`, JP 0x002489f0):
/// `+0 "TXAD"`, `+4 name[12]`, `+0x10 u8 texture`, `+0x11 u8 frames`, `+0x12 u16 w`, `+0x14 u16 h`, `+0x18 u16 frame stride (bytes)`,
/// `+0x1a u16 dstX`, `+0x1c u16 y inset`, `+0x20 u16 payload/16`, frames from `+0x30` (indexed pixels of the target texture's depth,
/// uploaded with `RefLoadImage` at `(dstX, texH - inset - h)`).
#[derive(Clone, Debug)]
pub struct TexAnimDef {
    pub name: String,
    /// Index into the model's `TXHD` table.
    pub texture: u8,
    pub frame_count: u8,
    pub width: u16,
    pub height: u16,
    pub stride: u16,
    pub dst_x: u16,
    pub inset: u16,
    /// Offset of frame 0 in the model file (frame `k` is at `data_off + k * stride`).
    pub data_off: usize,
    /// `frame_count * stride` bytes of indexed pixels.
    pub data: Vec<u8>,
}

impl TexAnimDef {
    /// Raw indexed pixels of frame `k` (`w * h` pixels at the target texture's depth: 4 bpp low nibble first, or 8 bpp).
    pub fn frame_bytes(&self, k: usize, bits: usize) -> Option<&[u8]> {
        let px = self.width as usize * self.height as usize;
        let bytes = if bits == 4 { px.div_ceil(2) } else { px };
        let s = k * self.stride as usize;
        self.data.get(s..s + bytes)
    }
}

/// One morph target of a [`BlendShapeDef`]: skin positions (x, y, z; the `w` word is kept in [`BlendTarget::ws`]) and unit normals.
#[derive(Clone, Debug, Default)]
pub struct BlendTarget {
    pub positions: Vec<[f32; 3]>,
    pub ws: Vec<u32>,
    pub normals: Vec<[f32; 3]>,
}

/// `BlendShape` (JP `create` 0x0024b700, `calcBlend` 0x0024beb0, `changeSlider` 0x0024bbe0): a skin mesh (own chunk table + UV array) with
/// `T >= 2` morph targets.  `out = (1 - w1) * P0 + w1 * P1 + sum_{k >= 2} w_k * (P_k - P0)` (normals blended with the same weights and
/// renormalised); the weights come from the motion event `BSASeq01` (`changeSliderGrp(byte / 255, group, k)`, `k = 1..n`).
///
/// File layout of a shape (offsets from the shape start, `*16` = 16-byte units): `+0 name[12]`, `+0x0d u8 group`, `+0x0e u16 T`,
/// `+0x10 u32 UV array (N x {u16 u, u16 v}/4096) *16`, `+0x14 u32 chunk table *16` (`u32 count, pad, chunk[]`), `+0x18 u32 next shape *16`,
/// `+0x20` a regular 0x30-byte atomic header (name, N, PRIM flags, texture, type bytes), `+0x50 u32[T]` target offsets `*16`; a target is
/// `0x10` header + `N x 16` positions (`f32 xyz`, `u32 w` = skin slot / strip ADC) + `N x 8` normals (`s16 xyz / 32768`).
#[derive(Clone, Debug)]
pub struct BlendShapeDef {
    pub name: String,
    /// Matched against the first value of `BSASeq*` events.
    pub group: u8,
    /// Index of the shape's atomic in [`Model::atomics`].
    pub atomic: usize,
    pub targets: Vec<BlendTarget>,
}

/// `BBHD` entry (0x110 bytes): frame ids + 8 box corners.
#[derive(Clone, Debug)]
pub struct BoundEntry {
    pub tag: u32,
    pub corners: [FVector; 8],
}

/// `EXHD` extension block (tags seen: `DYNH` dynamics, `WFRH` frame weights,
/// `DHSH` bounding circles, `LABL` labels).
#[derive(Clone, Debug)]
pub struct ExtBlock {
    pub tag: [u8; 4],
    /// u16 at +8 (version, 1 in shipped data).
    pub version: u16,
    /// u16 at +0xa (element count: chains for `DYNH`, circles for `DHSH`, ...).
    pub count: u16,
    pub data: Vec<u8>,
}

/// One virtual frame of the `WFRH` block (`FrameWeight`, JP `Create` 0x00257790 / `calcWeight` 0x002577b0):
/// its skinning matrix is the weighted blend of 2..4 real frames' matrices.  This is where the skin "weights" live: a
/// vertex only ever selects one matrix, but that matrix may be a blend (shoulder, elbow, wrist, jaw ...).
#[derive(Clone, Debug, PartialEq)]
pub struct FrameWeightDef {
    /// Source frame indices (2..=4, `entry[4..8]`).
    pub frames: Vec<u8>,
    /// u16 weights (`entry[8..16]`, 4096 = 1.0) matching `frames`.
    pub weights: Vec<u16>,
}

#[derive(Clone, Debug)]
pub struct Model {
    pub header: ModelHeader,
    /// +6 of `FRHD`: number of extra (runtime-only) frames appended after the file's frames.
    pub extra_frames: u16,
    pub frames: Vec<FrameDef>,
    pub atomics: Vec<AtomicDef>,
    pub textures: Vec<TextureDef>,
    pub bounds: Vec<BoundEntry>,
    /// Raw `TXAH` block (TextureAnim::CreateData), if present: the whole table (header + every `TXAD` entry with its frames), offsets
    /// of [`TexAnimDef::data_off`] are relative to the start of this block's *file* (`header.texanim_off`).
    pub texanim_raw: Option<Vec<u8>>,
    /// Decoded `TXAD` entries of the `TXAH` table (`TXA<name>` motion events select a frame of the entry called `<name>`).
    pub texanims: Vec<TexAnimDef>,
    pub extensions: Vec<ExtBlock>,
    /// `BSAH` blend-shape block (`BlendShapeControl::create` 0x0024cd40; only the US retail battle models 409 and 470 -- the eyelids of the
    /// frog monster -- carry one).  Each shape's mesh is appended to [`Model::atomics`] (index [`BlendShapeDef::atomic`]) in its first target's
    /// pose, so every renderer draws it as an ordinary skin atomic; [`BlendShapeDef::targets`] holds the morph targets.
    pub blend_shapes: Vec<BlendShapeDef>,
    /// Non-fatal problems (unsupported atomic variants etc.).
    pub warnings: Vec<String>,
}

pub fn is_model(data: &[u8]) -> bool {
    data.len() >= 8 && &data[..8] == MODEL_MAGIC
}

impl Model {
    /// Parse a model from the bytes of one `mdl` entry (the slice may extend beyond the
    /// model; trailing data is ignored).
    pub fn parse(d: &[u8]) -> Result<Model> {
        if !is_model(d) {
            return Err(ModelError::BadMagic);
        }
        let header = ModelHeader {
            flags: u32_at(d, 8)?,
            atomics_off: u32_at(d, 0x0c)?,
            frames_off: u32_at(d, 0x10)?,
            reserved14: u32_at(d, 0x14)?,
            textures_off: u32_at(d, 0x18)?,
            bounds_off: u32_at(d, 0x1c)?,
            blendshape_off: u32_at(d, 0x20)?,
            texanim_off: u32_at(d, 0x24)?,
            ext_off: u32_at(d, 0x28)?,
        };
        let mut warnings = Vec::new();

        // ---- frames
        let fo = header.frames_off as usize;
        if d.get(fo..fo + 4) != Some(b"FRHD") {
            return Err(ModelError::BadTag(fo, "FRHD"));
        }
        let nframes = u16_at(d, fo + 4)? as usize;
        let extra_frames = u16_at(d, fo + 6)?;
        let mut frames = Vec::with_capacity(nframes);
        for i in 0..nframes {
            let o = fo + 0x10 + i * 0x40;
            let rot = Quaternion::new(f32_at(d, o + 0x30)?, f32_at(d, o + 0x34)?, f32_at(d, o + 0x38)?, f32_at(d, o + 0x3c)?);
            frames.push(FrameDef {
                name: name_at(d, o, 12)?,
                parent: opt_idx(u8_at(d, o + 0x0c)?),
                child: opt_idx(u8_at(d, o + 0x0d)?),
                unknown: u8_at(d, o + 0x0e)?,
                sibling: opt_idx(u8_at(d, o + 0x0f)?),
                translation: FVector::new(f32_at(d, o + 0x20)?, f32_at(d, o + 0x24)?, f32_at(d, o + 0x28)?, f32_at(d, o + 0x2c)?),
                rotation: rot,
            });
        }

        // ---- atomics
        let ao = header.atomics_off as usize;
        if d.get(ao..ao + 4) != Some(b"ATHD") {
            return Err(ModelError::BadTag(ao, "ATHD"));
        }
        let natoms = u16_at(d, ao + 4)? as usize;
        let mut p = ao + 0x10;
        let mut atomics = Vec::with_capacity(natoms);
        for _ in 0..natoms {
            match parse_atomic(d, p, header.geometry_flags()) {
                Ok((a, next)) => {
                    atomics.push(a);
                    p = next;
                }
                Err(e) => {
                    warnings.push(format!("atomic parse stopped: {e}"));
                    break;
                }
            }
        }

        // ---- textures
        let mut textures = Vec::new();
        let to = header.textures_off as usize;
        if header.textures_off != 0 && header.textures_off != 0xffff_ffff {
            if d.get(to..to + 4) != Some(b"TXHD") {
                return Err(ModelError::BadTag(to, "TXHD"));
            }
            let n = u16_at(d, to + 4)? as usize;
            let mut p = to + 0x10;
            for _ in 0..n {
                match parse_texture(d, p) {
                    Ok((t, next)) => {
                        textures.push(t);
                        p = next;
                    }
                    Err(e) => {
                        warnings.push(format!("texture parse stopped: {e}"));
                        break;
                    }
                }
            }
        }

        // ---- bounding boxes
        let mut bounds = Vec::new();
        let bo = header.bounds_off as usize;
        if header.bounds_off != 0 && d.get(bo..bo + 4) == Some(b"BBHD") {
            let n = u32_at(d, bo + 4)? as usize + u32_at(d, bo + 8)? as usize;
            for i in 0..n {
                let o = bo + 0x10 + i * 0x110;
                if o + 0x110 > d.len() {
                    break;
                }
                let mut corners = [FVector::ZERO; 8];
                for (j, c) in corners.iter_mut().enumerate() {
                    *c = FVector::read_le(&d[o + 0x10 + j * 16..o + 0x20 + j * 16]);
                }
                bounds.push(BoundEntry { tag: u32_at(d, o)?, corners });
            }
        }

        // ---- texture animation (`TextureAnim::CreateData`, JP 0x002489f0)
        let mut texanim_raw = None;
        let mut texanims = Vec::new();
        if header.texanim_off != 0 && header.texanim_off != 0xffff_ffff {
            let o = header.texanim_off as usize;
            if d.get(o..o + 4) == Some(b"TXAH") {
                let n = u16_at(d, o + 4)? as usize;
                let mut p = o + 0x10;
                for _ in 0..n {
                    if d.get(p..p + 4) != Some(b"TXAD") {
                        break;
                    }
                    let Ok(name) = name_at(d, p + 4, 12) else { break };
                    let (Ok(texture), Ok(nframes)) = (u8_at(d, p + 0x10), u8_at(d, p + 0x11)) else { break };
                    let (Ok(w), Ok(h), Ok(stride), Ok(x0), Ok(inset), Ok(payload)) =
                        (u16_at(d, p + 0x12), u16_at(d, p + 0x14), u16_at(d, p + 0x18), u16_at(d, p + 0x1a), u16_at(d, p + 0x1c), u16_at(d, p + 0x20))
                    else {
                        break;
                    };
                    texanims.push(TexAnimDef {
                        name,
                        texture,
                        frame_count: nframes,
                        width: w,
                        height: h,
                        stride,
                        dst_x: x0,
                        inset,
                        data_off: p + 0x30,
                        data: d.get(p + 0x30..(p + 0x30 + nframes as usize * stride as usize).min(d.len())).unwrap_or(&[]).to_vec(),
                    });
                    p += 0x30 + payload as usize * 16;
                }
                texanim_raw = Some(d[o..p.min(d.len())].to_vec());
            }
        }

        // ---- extension chain
        let mut extensions = Vec::new();
        if header.ext_off != 0 {
            let mut o = header.ext_off as usize;
            while d.get(o..o + 4) == Some(b"EXHD") {
                let tag = [d[o + 4], d[o + 5], d[o + 6], d[o + 7]];
                let units = u32_at(d, o + 12)? as usize;
                if units == 0 {
                    break;
                }
                let end = (o + units * 16).min(d.len());
                extensions.push(ExtBlock { tag, version: u16_at(d, o + 8)?, count: u16_at(d, o + 10)?, data: d[o + 0x10..end].to_vec() });
                o += units * 16;
            }
        }

        // ---- blend shapes (`BlendShapeControl::create`)
        let mut blend_shapes = Vec::new();
        let bso = header.blendshape_off as usize;
        if header.blendshape_off != 0 && header.blendshape_off != 0xffff_ffff && d.get(bso..bso + 4) == Some(b"BSAH") {
            let count = u16_at(d, bso + 4)? as usize;
            let mut sh = bso + 0x10;
            for _ in 0..count {
                match parse_blend_shape(d, sh, atomics.len()) {
                    Ok((def, atom, next)) => {
                        atomics.push(atom);
                        blend_shapes.push(def);
                        sh = next;
                    }
                    Err(e) => {
                        warnings.push(format!("blend shape parse stopped: {e}"));
                        break;
                    }
                }
            }
        }

        Ok(Model { header, extra_frames, frames, atomics, textures, bounds, texanim_raw, texanims, extensions, blend_shapes, warnings })
    }

    /// Virtual frames of the `WFRH` extension block.  Entry `i` becomes frame `frames.len() + i`
    /// (`FrameWeight::calcWeight` writes it to `frames[count + i]`).
    pub fn frame_weights(&self) -> Vec<FrameWeightDef> {
        let mut out = Vec::new();
        for e in self.extensions.iter().filter(|e| &e.tag == b"WFRH") {
            for i in 0..e.count as usize {
                let Some(r) = e.data.get(i * 16..i * 16 + 16) else { break };
                let k = (r[1] as usize).clamp(0, 4);
                let frames: Vec<u8> = r[4..4 + k].to_vec();
                let weights: Vec<u16> = (0..k).map(|n| u16::from_le_bytes([r[8 + n * 2], r[9 + n * 2]])).collect();
                out.push(FrameWeightDef { frames, weights });
            }
        }
        out
    }

    /// File frames + `WFRH` virtual frames: the number of valid palette targets.
    pub fn total_frames(&self) -> usize {
        self.frames.len() + self.extensions.iter().filter(|e| &e.tag == b"WFRH").map(|e| e.count as usize).sum::<usize>()
    }

    pub fn find_frame(&self, name: &str) -> Option<usize> {
        self.frames.iter().position(|f| f.name == name)
    }
}

fn parse_blend_shape(d: &[u8], sh: usize, atomic_index: usize) -> Result<(BlendShapeDef, AtomicDef, usize)> {
    let name = name_at(d, sh, 12)?;
    let group = u8_at(d, sh + 0x0d)?;
    let nt = u16_at(d, sh + 0x0e)? as usize;
    let uv_off = sh + u32_at(d, sh + 0x10)? as usize * 16;
    let chunk_off = sh + u32_at(d, sh + 0x14)? as usize * 16;
    let next = sh + u32_at(d, sh + 0x18)? as usize * 16;
    let n = u32_at(d, sh + 0x2c)? as usize;
    let b14 = u8_at(d, sh + 0x34)?;
    let kind = if b14 & 0xf == 0 { AtomicKind::Skin } else { AtomicKind::SkinNL };
    let mut uvs = Vec::with_capacity(n);
    for i in 0..n {
        uvs.push([u16_at(d, uv_off + i * 4)? as f32 / 4096.0, u16_at(d, uv_off + i * 4 + 2)? as f32 / 4096.0]);
    }
    let nchunks = u32_at(d, chunk_off)? as usize;
    let mut chunks = Vec::with_capacity(nchunks);
    for i in 0..nchunks {
        let o = chunk_off + 0x10 + i * 0x10;
        chunks.push(Chunk {
            bones: [u8_at(d, o)?, u8_at(d, o + 1)?, u8_at(d, o + 2)?],
            flag: u8_at(d, o + 3)?,
            tag: u32_at(d, o + 4)?,
            start: u32_at(d, o + 8)?,
            count: u32_at(d, o + 12)?,
        });
    }
    let mut targets = Vec::with_capacity(nt);
    for t in 0..nt {
        let to = sh + u32_at(d, sh + 0x50 + t * 4)? as usize * 16;
        let mut tg = BlendTarget::default();
        for i in 0..n {
            let o = to + 0x10 + i * 16;
            tg.positions.push([f32_at(d, o)?, f32_at(d, o + 4)?, f32_at(d, o + 8)?]);
            tg.ws.push(u32_at(d, o + 12)?);
        }
        let no = to + 0x10 + n * 16;
        for i in 0..n {
            let o = no + i * 8;
            tg.normals.push([i16_at(d, o)? as f32 / 32768.0, i16_at(d, o + 2)? as f32 / 32768.0, i16_at(d, o + 4)? as f32 / 32768.0]);
        }
        targets.push(tg);
    }
    let first = targets.first().cloned().unwrap_or_default();
    let geometry = Geometry {
        positions: first.positions.clone(),
        adc: first.ws.iter().map(|w| w & 0x8000 != 0).collect(),
        uvs,
        colors: Vec::new(),
        normals: first.normals.clone(),
        skin: first.ws.iter().map(|&w| SkinVertex::from_w(w)).collect(),
        billboard: Vec::new(),
        group: Vec::new(),
    };
    let atom = AtomicDef {
        name: name_at(d, sh + 0x20, 12)?,
        kind,
        vertex_count: n as u32,
        flags: u16_at(d, sh + 0x30)?,
        texture: u8_at(d, sh + 0x32)?,
        texture2: u8_at(d, sh + 0x33)?,
        b14,
        b15: u8_at(d, sh + 0x35)?,
        b16: u8_at(d, sh + 0x36)?,
        b17: u8_at(d, sh + 0x37)?,
        shared_ref: -1,
        tri_hint: u16_at(d, sh + 0x3a)?,
        extra20: 0,
        chunks,
        geometry,
        file_offset: sh + 0x20,
    };
    Ok((BlendShapeDef { name, group, atomic: atomic_index, targets }, atom, next))
}

fn parse_atomic(d: &[u8], p: usize, file_flags: u8) -> Result<(AtomicDef, usize)> {
    let name = name_at(d, p, 12)?;
    let n = u32_at(d, p + 0x0c)?;
    let flags = u16_at(d, p + 0x10)?;
    let (b12, b13, b14, b15, b16, b17) =
        (u8_at(d, p + 0x12)?, u8_at(d, p + 0x13)?, u8_at(d, p + 0x14)?, u8_at(d, p + 0x15)?, u8_at(d, p + 0x16)?, u8_at(d, p + 0x17)?);
    let shared_ref = i16_at(d, p + 0x18)?;
    let tri_hint = u16_at(d, p + 0x1a)?;
    let extra20 = u32_at(d, p + 0x20)?;
    let kind = classify_atomic(file_flags, b14, b15).ok_or(ModelError::UnsupportedAtomic { name: name.clone(), b14, b15, at: p })?;
    if n > 0x20_0000 {
        return Err(ModelError::UnsupportedAtomic { name, b14, b15, at: p });
    }
    let n_us = n as usize;
    let mut q = p + 0x30;
    let mut geometry = Geometry::default();
    if shared_ref == -1 {
        let strides = kind.array_strides();
        let mut starts = [0usize; 3];
        for i in 0..kind.n_arrays() {
            starts[i] = q;
            q = align16(q + n_us * strides[i]);
        }
        if q > d.len() {
            return Err(ModelError::Truncated(q));
        }
        decode_geometry(d, kind, n_us, &starts, &mut geometry)?;
    }
    let nchunks = u32_at(d, q)? as usize;
    if nchunks > 0x10000 || q + 0x10 + nchunks * 0x10 > d.len() {
        return Err(ModelError::UnsupportedAtomic { name, b14, b15, at: p });
    }
    let mut chunks = Vec::with_capacity(nchunks);
    for j in 0..nchunks {
        let o = q + 0x10 + j * 0x10;
        chunks.push(Chunk {
            bones: [u8_at(d, o)?, u8_at(d, o + 1)?, u8_at(d, o + 2)?],
            flag: u8_at(d, o + 3)?,
            tag: u32_at(d, o + 4)?,
            start: u32_at(d, o + 8)?,
            count: u32_at(d, o + 12)?,
        });
    }
    let total: u64 = chunks.iter().map(|c| c.count as u64).sum();
    if shared_ref == -1 && total != n as u64 && !matches!(kind, AtomicKind::Billboard | AtomicKind::Water) {
        return Err(ModelError::UnsupportedAtomic { name, b14, b15, at: p });
    }
    let next = q + 0x10 + nchunks * 0x10;
    Ok((
        AtomicDef {
            name,
            kind,
            vertex_count: n,
            flags,
            texture: b12,
            texture2: b13,
            b14,
            b15,
            b16,
            b17,
            shared_ref,
            tri_hint,
            extra20,
            chunks,
            geometry,
            file_offset: p,
        },
        next,
    ))
}

fn decode_geometry(d: &[u8], kind: AtomicKind, n: usize, starts: &[usize; 3], g: &mut Geometry) -> Result<()> {
    let uv_of = |i: usize| -> Result<[f32; 2]> {
        let o = starts[1] + i * 4;
        Ok([u16_at(d, o)? as f32 / 4096.0, u16_at(d, o + 2)? as f32 / 4096.0])
    };
    let rgba_of = |i: usize| -> Result<[u8; 4]> {
        let o = starts[2] + i * 4;
        Ok([u8_at(d, o)?, u8_at(d, o + 1)?, u8_at(d, o + 2)?, u8_at(d, o + 3)?])
    };
    match kind {
        AtomicKind::Pack1 | AtomicKind::Plp1 | AtomicKind::Water => {
            for i in 0..n {
                let o = starts[0] + i * 8;
                g.positions.push([i16_at(d, o)? as f32 / 16.0, i16_at(d, o + 2)? as f32 / 16.0, i16_at(d, o + 4)? as f32 / 16.0]);
                g.adc.push(u16_at(d, o + 6)? & 0x8000 != 0);
                if kind == AtomicKind::Water {
                    g.group.push((u16_at(d, o + 6)? & 0xff) as u8);
                }
                g.uvs.push(uv_of(i)?);
                if kind != AtomicKind::Plp1 || true {
                    g.colors.push(rgba_of(i)?);
                }
            }
        }
        AtomicKind::Pack2 | AtomicKind::Plp2 | AtomicKind::SkinNL => {
            for i in 0..n {
                let o = starts[0] + i * 16;
                g.positions.push([f32_at(d, o)?, f32_at(d, o + 4)?, f32_at(d, o + 8)?]);
                let w = u32_at(d, o + 12)?;
                g.adc.push(w & 0x8000 != 0);
                if kind == AtomicKind::SkinNL {
                    g.skin.push(SkinVertex::from_w(w));
                }
                g.uvs.push(uv_of(i)?);
                g.colors.push(rgba_of(i)?);
            }
        }
        AtomicKind::Skin => {
            for i in 0..n {
                let o = starts[0] + i * 16;
                g.positions.push([f32_at(d, o)?, f32_at(d, o + 4)?, f32_at(d, o + 8)?]);
                let w = u32_at(d, o + 12)?;
                g.adc.push(w & 0x8000 != 0);
                g.skin.push(SkinVertex::from_w(w));
                g.uvs.push(uv_of(i)?);
                let no = starts[2] + i * 8;
                g.normals.push([
                    i16_at(d, no)? as f32 / 32768.0,
                    i16_at(d, no + 2)? as f32 / 32768.0,
                    i16_at(d, no + 4)? as f32 / 32768.0,
                ]);
            }
        }
        AtomicKind::Billboard => {
            for i in 0..n {
                let o = starts[0] + i * 0x28;
                let mut e = [[0i16; 4]; 5];
                for (k, v) in e.iter_mut().enumerate() {
                    for (c, x) in v.iter_mut().enumerate() {
                        *x = i16_at(d, o + k * 8 + c * 2)?;
                    }
                }
                g.billboard.push(e);
                let o2 = starts[1] + i * 4;
                g.colors.push([u8_at(d, o2)?, u8_at(d, o2 + 1)?, u8_at(d, o2 + 2)?, u8_at(d, o2 + 3)?]);
            }
        }
    }
    Ok(())
}

fn parse_texture(d: &[u8], p: usize) -> Result<(TextureDef, usize)> {
    if d.get(p..p + 4) != Some(b"TIHD") {
        return Err(ModelError::BadTag(p, "TIHD"));
    }
    let width = u16_at(d, p + 4)?;
    let height = u16_at(d, p + 6)?;
    let raw_format = u8_at(d, p + 8)?;
    let mip_levels = u8_at(d, p + 10)?;
    let nclut = u16_at(d, p + 0x0c)? as usize;
    let clut_off = u16_at(d, p + 0x0e)? as usize;
    let data_off = u32_at(d, p + 0x10)? as usize;
    let end_off = u32_at(d, p + 0x14)? as usize;
    let format = if raw_format & 0x40 != 0 {
        TexFormat::Ipu
    } else {
        match raw_format & 0x3f {
            4 => TexFormat::Psmt4,
            8 => TexFormat::Psmt8,
            _ => TexFormat::Ct32,
        }
    };
    let mut palette = Vec::with_capacity(nclut);
    for i in 0..nclut {
        let o = p + clut_off + i * 4;
        let b = d.get(o..o + 4).ok_or(ModelError::Truncated(o))?;
        palette.push([b[0], b[1], b[2], b[3]]);
    }
    let data = d.get(p + data_off..p + end_off).ok_or(ModelError::Truncated(p + end_off))?.to_vec();
    Ok((
        TextureDef {
            width,
            height,
            format,
            raw_format,
            mip_levels,
            palette,
            data,
            alpha_bits: u16_at(d, p + 0x1c)?,
            alpha_ref: u8_at(d, p + 0x1e)?,
            flags: u8_at(d, p + 0x1f)?,
            file_offset: p,
        },
        p + end_off,
    ))
}

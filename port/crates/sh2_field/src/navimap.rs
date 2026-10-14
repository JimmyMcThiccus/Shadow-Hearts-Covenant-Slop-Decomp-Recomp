//! `CNaviMap`: the circular radar ("Navi Map") in the top-left corner of the field screen.
//!
//! The `NAVIMAP` chunk of a map (`_NaviMapDataHdr`, tag `"NAVM"`, [`crate::mps::NaviMapHeader`]) holds a top-down floor picture, a triangle
//! grid that carries it (vertex positions in 1/16 units, UVs in 1/4096), a few static markers and the colours the floor is tinted with.  JP
//! decompile: `decomp/G/CNaviMap.c` (`SetData` 0x4cf440, `Update` 0x4cfa50, `CnvVertex` 0x4d33c0, `MakeMapPacket` 0x4d1670, `MakeMaskPacket`
//! 0x4d1f30, `SetCursor` 0x4d2cb0, `MakeItemPacket` 0x4d36f0); retail uses the same format and code (`notes/G_retail/CNaviMap.md`).
//!
//! Header (all little endian):
//!
//! | off | | |
//! |---|---|---|
//! | 0x00 | `"NAVM"` | |
//! | 0x04 | u16 | version (0 = one bare vertex list, 1 = records with a 16 byte header) |
//! | 0x06 | u16 | header size (0x40) |
//! | 0x0c | u16 x2 | grid size in cells (46 x 46); a cell is 10 units |
//! | 0x10 | f32 x2 | grid origin x / z |
//! | 0x18 | u16 | mesh count (version 1) |
//! | 0x1a | u16 | vertex count (version 0) |
//! | 0x1c | u16 | picture offset in 16 byte units after the header |
//! | 0x1f | u8 | bit 4: flat colours (no height tint), bit 5: circular mask, bits 2-3: quarter turns of the picture |
//! | 0x20 / 0x24 / 0x28 | RGBA | tint above / base / below the player (`+0x60 / +0x5c / +0x58` of the object) |
//! | 0x30 | u16 x2 | static marker count / offset in 16 byte units after the header |
//! | 0x34 | u8 | zoom in 1/16 (0 = 1.5) |
//!
//! Mesh record (version 1): `{u16 _; u16 vertex_count; u32 stride_and_flags (bit 24 = shown)}`, then `vertex_count` x `{s16 x, y, z, _}`
//! (position = value / 16), padding to 16, then `vertex_count` x `{s16 u, v}` (texture coordinate = value / 4096 over the whole 128 x 128
//! picture; the picture covers the `(w + 1) x (h + 1)` cell square around the origin).  Triangles are consecutive vertex triples.

use crate::mps::{rd_f32, rd_u16, rd_u32, Mps};

/// One 128 x 128 (or whatever the file says) picture decoded to RGBA8; alpha already scaled from the GS 0x80 range.
#[derive(Clone, Debug, Default)]
pub struct NaviPicture {
    pub w: usize,
    pub h: usize,
    pub rgba: Vec<u8>,
}

#[derive(Clone, Debug)]
pub struct NaviMesh {
    pub shown: bool,
    /// triangle vertices in map units, three per triangle
    pub pos: Vec<[f32; 3]>,
    /// texture coordinates (0..1), parallel to `pos`
    pub uv: Vec<[f32; 2]>,
}

/// Static marker (`MakeItemPacket`, first source): kinds 0 rectangle, 1 sprite, 2 arrow, 3 pulse, 4 icon quad, 5 big sprite.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct NaviMarker {
    pub pos: [f32; 3],
    /// record `+6 & 0x1ff`: rotation in degrees (rectangles / arrows) or icon index (kind 4)
    pub param: u16,
    /// record `+7 >> 1 & 0xf`: index into [`COL_TBL`]; 8..15 = take the floor colour at the marker
    pub color: u8,
    pub kind: u8,
    /// rectangle half sizes (`+8`, `+0xa` in 1/32 units)
    pub size: [f32; 2],
}

/// `colTbl` (FIELD.BIN 0x558f10): marker colours as GS RGBA words (r = low byte).
pub const COL_TBL: [u32; 8] = [0x7f7f7f, 0xff0000, 0xff, 0xff00ff, 0xff00, 0xa0f010, 0xffff, 0xffffff];

#[derive(Clone, Debug)]
pub struct NaviData {
    pub grid: [u16; 2],
    pub origin: [f32; 2],
    pub zoom: f32,
    /// `[above, base, below]` tint colours as `[r, g, b, a]` GS bytes (0x80 = 1.0)
    pub tint: [[u8; 4]; 3],
    pub flat: bool,
    pub mask: bool,
    pub quarter_turns: u8,
    pub meshes: Vec<NaviMesh>,
    pub picture: NaviPicture,
    pub markers: Vec<NaviMarker>,
}

fn gs_rgba(d: &[u8], o: usize) -> [u8; 4] {
    [d[o], d[o + 1], d[o + 2], d[o + 3]]
}

impl NaviData {
    /// Parse the `NAVIMAP` chunk of a map.  `None` when the map has none (or it is damaged).
    pub fn from_mps(mps: &Mps) -> Option<NaviData> {
        let c = mps.find(crate::mps::tags::NAVIMAP)?;
        Self::parse(&mps.data, c.data_start())
    }

    pub fn parse(d: &[u8], s: usize) -> Option<NaviData> {
        let get = |o: usize, n: usize| (s + o + n <= d.len()).then_some(());
        get(0, 0x40)?;
        if &d[s..s + 4] != b"NAVM" {
            return None;
        }
        let ver = rd_u16(d, s + 4);
        let hdr = rd_u16(d, s + 6) as usize;
        let grid = [rd_u16(d, s + 0xc), rd_u16(d, s + 0xe)];
        let origin = [rd_f32(d, s + 0x10), rd_f32(d, s + 0x14)];
        let mesh_count = rd_u16(d, s + 0x18) as usize;
        let vtx_count = rd_u16(d, s + 0x1a) as usize;
        let pic_off = rd_u16(d, s + 0x1c) as usize * 16;
        let flags = d[s + 0x1f];
        let tint = [gs_rgba(d, s + 0x20), gs_rgba(d, s + 0x24), gs_rgba(d, s + 0x28)];
        let marker_count = rd_u16(d, s + 0x30) as usize;
        let marker_off = rd_u16(d, s + 0x32) as usize * 16;
        let zoom = match d[s + 0x34] {
            0 => 1.5,
            z => z as f32 * 0.0625,
        };

        // meshes
        let mut meshes = Vec::new();
        let mut rec = s + hdr;
        let n_rec = if ver == 0 { 1 } else { mesh_count };
        for _ in 0..n_rec {
            let (count, shown, vtx0) = if ver == 0 {
                (vtx_count, true, rec)
            } else {
                get(rec - s, 16)?;
                (rd_u16(d, rec + 2) as usize, d[rec + 7] & 1 != 0, rec + 0x10)
            };
            let uv0 = (vtx0 + count * 8 + 0xf) & !0xf;
            if uv0 + count * 4 > d.len() {
                return None;
            }
            let mut pos = Vec::with_capacity(count);
            let mut uv = Vec::with_capacity(count);
            for i in 0..count {
                let o = vtx0 + i * 8;
                pos.push([rd_i16(d, o) as f32 / 16.0, rd_i16(d, o + 2) as f32 / 16.0, rd_i16(d, o + 4) as f32 / 16.0]);
                let t = uv0 + i * 4;
                uv.push([rd_i16(d, t) as f32 / 4096.0, rd_i16(d, t + 2) as f32 / 4096.0]);
            }
            meshes.push(NaviMesh { shown, pos, uv });
            // next record: the stride field (24 bits of the word at +4, in 16 byte units); a single mesh never needs it
            let stride = (rd_u32(d, rec + 4) & 0xff_ffff) as usize * 16;
            let natural = (uv0 + count * 4 + 0xf & !0xf) - rec;
            rec += if stride >= natural { stride } else { natural };
        }

        // picture
        let po = s + hdr + pic_off;
        let picture = if po + 16 <= d.len() { decode_picture(d, po).unwrap_or_default() } else { NaviPicture::default() };

        // static markers
        let mut markers = Vec::new();
        let mo = s + hdr + marker_off;
        if marker_count > 0 && mo + marker_count * 16 <= d.len() {
            for i in 0..marker_count {
                let r = mo + i * 16;
                markers.push(NaviMarker {
                    pos: [rd_i16(d, r) as f32 / 16.0, rd_i16(d, r + 2) as f32 / 16.0, rd_i16(d, r + 4) as f32 / 16.0],
                    param: rd_u16(d, r + 6) & 0x1ff,
                    color: (d[r + 7] >> 1) & 0xf,
                    kind: d[r + 0xe] & 0x1f,
                    size: [rd_u16(d, r + 8) as f32 * 0.03125, rd_u16(d, r + 10) as f32 * 0.03125],
                });
            }
        }

        Some(NaviData {
            grid,
            origin,
            zoom,
            tint,
            flat: flags & 0x10 != 0,
            mask: flags & 0x20 != 0,
            quarter_turns: (flags >> 2) & 3,
            meshes,
            picture,
            markers,
        })
    }

    /// `+0x40` of the object: centre of the grid square the picture covers (`origin + (cells + 1) * 5`).
    pub fn centre(&self) -> [f32; 2] {
        [self.origin[0] + (self.grid[0] as f32 + 1.0) * 5.0, self.origin[1] + (self.grid[1] as f32 + 1.0) * 5.0]
    }
}

fn rd_i16(d: &[u8], o: usize) -> i16 {
    rd_u16(d, o) as i16
}

/// `CImage::Create` + `CreatePal` as `SetData` calls them: `{u16 bpp-code, u16 palette entries, u16 w, u16 h, 8 bytes, RGBA palette, pixels}`.
fn decode_picture(d: &[u8], o: usize) -> Option<NaviPicture> {
    let bpp = rd_u16(d, o) as usize;
    let n_pal = rd_u16(d, o + 2) as usize;
    let (w, h) = (rd_u16(d, o + 4) as usize, rd_u16(d, o + 6) as usize);
    let pal_o = o + 16;
    let pix_o = pal_o + n_pal * 4;
    let mut rgba = vec![0u8; w * h * 4];
    let pal = |i: usize| -> [u8; 4] {
        if i < n_pal && pal_o + i * 4 + 4 <= d.len() {
            let p = &d[pal_o + i * 4..pal_o + i * 4 + 4];
            [p[0], p[1], p[2], ((p[3] as u32 * 255 + 64) / 128).min(255) as u8]
        } else {
            [0, 0, 0, 0]
        }
    };
    match bpp {
        4 => {
            if pix_o + w * h / 2 > d.len() {
                return None;
            }
            for i in 0..w * h {
                let b = d[pix_o + i / 2];
                let idx = if i & 1 == 0 { b & 15 } else { b >> 4 } as usize;
                rgba[i * 4..i * 4 + 4].copy_from_slice(&pal(idx));
            }
        }
        8 => {
            if pix_o + w * h > d.len() {
                return None;
            }
            for i in 0..w * h {
                rgba[i * 4..i * 4 + 4].copy_from_slice(&pal(d[pix_o + i] as usize));
            }
        }
        _ => return None,
    }
    Some(NaviPicture { w, h, rgba })
}

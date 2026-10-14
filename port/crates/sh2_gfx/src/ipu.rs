//! Minimal MPEG-2 *intra* decoder for the `ipum` movie textures (TIHD format flag 0x40, `IPUTexture`).
//!
//! JP `IPUTexture::create` 0x00248d70 / `decodeFrame` 0x00248e20, `Texture::CreateData` 0x002474e0.  The payload of such a texture is
//!
//! ```text
//! +0   "ipum"
//! +4   u32 payload size
//! +8   u16 width, u16 height
//! +0xc u32 frame count
//! +0x10 frame 0 | frame 1 | ...
//! frame = u8 params | width/16*height/16 macroblocks (raster order, bit packed; one `macroblock_address_increment` before every macroblock but the first) | byte alignment | start code 00 00 01 b0
//! params: bits 0-1 intra_dc_precision, bit 2 (DTD: a dct_type bit follows every macroblock_type), bit 4 alternate_scan, bit 5 intra_vlc_format, bit 6 q_scale_type, bit 7 MPEG-1
//! ```
//!
//! `decodeFrame` feeds the stream to the PS2 IPU: `FDEC` reads the params byte (`IPU_CTRL = (byte & 0xfb) << 16`: IDP/AS/IVF/QST/MP1),
//! `IDEC` (QSC = 1, DTD from bit 2) decodes the whole slice (all macroblocks, with their address increments) to RGB32, a `FDEC 32` skips the end code.  Each macroblock is
//! `macroblock_type` (`1` intra, `01` intra + `quantiser_scale_code`), optional `dct_type`, then 6 blocks (4:2:0): DC size / differential, AC run-level
//! codes of ISO 13818-2 table B.14 (or B.15 with intra_vlc_format) until EOB.  Dequantisation uses the default intra matrix (`sceIpuInit`), IDCT
//! is a float reference, colour conversion is the IPU CSC (BT.601 limited range, chroma replicated).  The VLC tables below are the standard's.
//!
//! Only GY_05_F (`SCREEN` model, 256x256, 120 frames) ships such a texture; `decode_ipum` decodes all frames in a few milliseconds.

use thiserror::Error;

pub mod mpeg2;

#[derive(Debug, Error, PartialEq, Eq)]
pub enum IpuError {
    #[error("not an ipum payload")]
    BadMagic,
    #[error("bitstream ended (frame {frame}, macroblock {mb})")]
    Truncated { frame: usize, mb: usize },
    #[error("invalid code (frame {frame}, macroblock {mb}): {what}")]
    Invalid { frame: usize, mb: usize, what: &'static str },
    #[error("MPEG-1 style streams are not supported")]
    Mpeg1,
}

/// All decoded frames of an `ipum` texture.
#[derive(Clone, Debug)]
pub struct IpuMovie {
    pub width: usize,
    pub height: usize,
    /// RGBA8 (alpha 0xff), `width * height * 4` bytes per frame.
    pub frames: Vec<Vec<u8>>,
}

pub fn is_ipum(data: &[u8]) -> bool {
    data.len() >= 0x10 && &data[..4] == b"ipum"
}

const B14: [(u16, u8); 113] = [
    (0x3, 2), (0x4, 4), (0x5, 5), (0x6, 7), (0x26, 8), (0x21, 8),
    (0xa, 10), (0x1d, 12), (0x18, 12), (0x13, 12), (0x10, 12), (0x1a, 13),
    (0x19, 13), (0x18, 13), (0x17, 13), (0x1f, 14), (0x1e, 14), (0x1d, 14),
    (0x1c, 14), (0x1b, 14), (0x1a, 14), (0x19, 14), (0x18, 14), (0x17, 14),
    (0x16, 14), (0x15, 14), (0x14, 14), (0x13, 14), (0x12, 14), (0x11, 14),
    (0x10, 14), (0x18, 15), (0x17, 15), (0x16, 15), (0x15, 15), (0x14, 15),
    (0x13, 15), (0x12, 15), (0x11, 15), (0x10, 15), (0x3, 3), (0x6, 6),
    (0x25, 8), (0xc, 10), (0x1b, 12), (0x16, 13), (0x15, 13), (0x1f, 15),
    (0x1e, 15), (0x1d, 15), (0x1c, 15), (0x1b, 15), (0x1a, 15), (0x19, 15),
    (0x13, 16), (0x12, 16), (0x11, 16), (0x10, 16), (0x5, 4), (0x4, 7),
    (0xb, 10), (0x14, 12), (0x14, 13), (0x7, 5), (0x24, 8), (0x1c, 12),
    (0x13, 13), (0x6, 5), (0xf, 10), (0x12, 12), (0x7, 6), (0x9, 10),
    (0x12, 13), (0x5, 6), (0x1e, 12), (0x14, 16), (0x4, 6), (0x15, 12),
    (0x7, 7), (0x11, 12), (0x5, 7), (0x11, 13), (0x27, 8), (0x10, 13),
    (0x23, 8), (0x1a, 16), (0x22, 8), (0x19, 16), (0x20, 8), (0x18, 16),
    (0xe, 10), (0x17, 16), (0xd, 10), (0x16, 16), (0x8, 10), (0x15, 16),
    (0x1f, 12), (0x1a, 12), (0x19, 12), (0x17, 12), (0x16, 12), (0x1f, 13),
    (0x1e, 13), (0x1d, 13), (0x1c, 13), (0x1b, 13), (0x1f, 16), (0x1e, 16),
    (0x1d, 16), (0x1c, 16), (0x1b, 16), (0x1, 6), (0x2, 2),
];
const B15: [(u16, u8); 113] = [
    (0x2, 2), (0x6, 3), (0x7, 4), (0x1c, 5), (0x1d, 5), (0x5, 6),
    (0x4, 6), (0x7b, 7), (0x7c, 7), (0x23, 8), (0x22, 8), (0xfa, 8),
    (0xfb, 8), (0xfe, 8), (0xff, 8), (0x1f, 14), (0x1e, 14), (0x1d, 14),
    (0x1c, 14), (0x1b, 14), (0x1a, 14), (0x19, 14), (0x18, 14), (0x17, 14),
    (0x16, 14), (0x15, 14), (0x14, 14), (0x13, 14), (0x12, 14), (0x11, 14),
    (0x10, 14), (0x18, 15), (0x17, 15), (0x16, 15), (0x15, 15), (0x14, 15),
    (0x13, 15), (0x12, 15), (0x11, 15), (0x10, 15), (0x2, 3), (0x6, 5),
    (0x79, 7), (0x27, 8), (0x20, 8), (0x16, 13), (0x15, 13), (0x1f, 15),
    (0x1e, 15), (0x1d, 15), (0x1c, 15), (0x1b, 15), (0x1a, 15), (0x19, 15),
    (0x13, 16), (0x12, 16), (0x11, 16), (0x10, 16), (0x5, 5), (0x7, 7),
    (0xfc, 8), (0xc, 10), (0x14, 13), (0x7, 5), (0x26, 8), (0x1c, 12),
    (0x13, 13), (0x6, 6), (0xfd, 8), (0x12, 12), (0x7, 6), (0x4, 9),
    (0x12, 13), (0x6, 7), (0x1e, 12), (0x14, 16), (0x4, 7), (0x15, 12),
    (0x5, 7), (0x11, 12), (0x78, 7), (0x11, 13), (0x7a, 7), (0x10, 13),
    (0x21, 8), (0x1a, 16), (0x25, 8), (0x19, 16), (0x24, 8), (0x18, 16),
    (0x5, 9), (0x17, 16), (0x7, 9), (0x16, 16), (0xd, 10), (0x15, 16),
    (0x1f, 12), (0x1a, 12), (0x19, 12), (0x17, 12), (0x16, 12), (0x1f, 13),
    (0x1e, 13), (0x1d, 13), (0x1c, 13), (0x1b, 13), (0x1f, 16), (0x1e, 16),
    (0x1d, 16), (0x1c, 16), (0x1b, 16), (0x1, 6), (0x6, 4),
];

/// ISO 13818-2 table B.14 / B.15 index -> (run, level): runs 0..31 with 40, 18, 5, 4, 3, 3, 3, 2 (x10), 1 (x15) levels.
fn run_level(index: usize) -> (u8, i32) {
    const COUNTS: [(u8, usize); 32] = {
        let mut a = [(0u8, 0usize); 32];
        let mut r = 0;
        while r < 32 {
            let n = match r {
                0 => 40,
                1 => 18,
                2 => 5,
                3 => 4,
                4..=6 => 3,
                7..=16 => 2,
                _ => 1,
            };
            a[r] = (r as u8, n);
            r += 1;
        }
        a
    };
    let mut i = index;
    for (run, n) in COUNTS {
        if i < n {
            return (run, i as i32 + 1);
        }
        i -= n;
    }
    (0, 1)
}

/// macroblock_address_increment (table B.1), increments 1..=3 (only 1 occurs in intra frames).
const MBAI: [(u16, u8); 3] = [(0b1, 1), (0b011, 3), (0b010, 3)];

const ESC: usize = 111;
const EOB: usize = 112;

const DC_LUM: [(u16, u8); 12] = [(0b100, 3), (0b00, 2), (0b01, 2), (0b101, 3), (0b110, 3), (0b1110, 4), (0b11110, 5), (0b111110, 6), (0b1111110, 7), (0b11111110, 8), (0b111111110, 9), (0b111111111, 9)];
const DC_CHR: [(u16, u8); 12] = [(0b00, 2), (0b01, 2), (0b10, 2), (0b110, 3), (0b1110, 4), (0b11110, 5), (0b111110, 6), (0b1111110, 7), (0b11111110, 8), (0b111111110, 9), (0b1111111110, 10), (0b1111111111, 10)];

const ZIGZAG: [u8; 64] = [
    0, 1, 8, 16, 9, 2, 3, 10, 17, 24, 32, 25, 18, 11, 4, 5, 12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6, 7, 14, 21, 28, 35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51, 58, 59, 52, 45,
    38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
];
const ALT_SCAN: [u8; 64] = [
    0, 8, 16, 24, 1, 9, 2, 10, 17, 25, 32, 40, 48, 56, 57, 49, 41, 33, 26, 18, 3, 11, 4, 12, 19, 27, 34, 42, 50, 58, 35, 43, 51, 59, 20, 28, 5, 13, 6, 14, 21, 29, 36, 44, 52, 60, 37, 45, 53, 61, 22, 30,
    7, 15, 23, 31, 38, 46, 54, 62, 39, 47, 55, 63,
];
const INTRA_MATRIX: [u8; 64] = [
    8, 16, 19, 22, 26, 27, 29, 34, 16, 16, 22, 24, 27, 29, 34, 37, 19, 22, 26, 27, 29, 34, 34, 38, 22, 22, 26, 27, 29, 34, 37, 40, 22, 26, 27, 29, 32, 35, 40, 48, 26, 27, 29, 32, 35, 40, 48, 58, 26, 27, 29,
    34, 38, 46, 56, 69, 27, 29, 35, 38, 46, 56, 69, 83,
];
/// quantiser_scale for q_scale_type = 1 (non-linear), indexed by quantiser_scale_code.
const QSCALE_NONLINEAR: [u8; 32] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 22, 24, 28, 32, 36, 40, 44, 48, 52, 56, 64, 72, 80, 88, 96, 104, 112];

struct Bits<'a> {
    d: &'a [u8],
    pos: usize, // bit position
}

impl<'a> Bits<'a> {
    fn peek(&self, n: usize) -> Option<u32> {
        if self.pos + n > self.d.len() * 8 {
            return None;
        }
        let mut v = 0u32;
        for i in 0..n {
            let p = self.pos + i;
            v = (v << 1) | ((self.d[p >> 3] >> (7 - (p & 7))) & 1) as u32;
        }
        Some(v)
    }
    fn read(&mut self, n: usize) -> Option<u32> {
        let v = self.peek(n)?;
        self.pos += n;
        Some(v)
    }
    fn align(&mut self) {
        self.pos = (self.pos + 7) & !7;
    }
    fn vlc(&mut self, table: &[(u16, u8)]) -> Option<usize> {
        for len in 1..=16usize {
            let Some(v) = self.peek(len) else { return None };
            if let Some(i) = table.iter().position(|&(c, l)| l as usize == len && c as u32 == v) {
                self.pos += len;
                return Some(i);
            }
        }
        None
    }
}

/// Separable float IDCT of one 8x8 block (input: dequantised coefficients in raster order).
fn idct8x8(f: &[i32; 64]) -> [u8; 64] {
    use std::sync::OnceLock;
    static C: OnceLock<[[f32; 8]; 8]> = OnceLock::new();
    let c = C.get_or_init(|| {
        let mut c = [[0f32; 8]; 8];
        for (x, row) in c.iter_mut().enumerate() {
            for (u, v) in row.iter_mut().enumerate() {
                let a = if u == 0 { (1.0f32 / 2.0).sqrt() } else { 1.0 };
                *v = 0.5 * a * (((2 * x + 1) as f32) * (u as f32) * std::f32::consts::PI / 16.0).cos();
            }
        }
        c
    });
    let mut tmp = [[0f32; 8]; 8];
    for v in 0..8 {
        for x in 0..8 {
            let mut s = 0.0;
            for u in 0..8 {
                s += c[x][u] * f[v * 8 + u] as f32;
            }
            tmp[v][x] = s;
        }
    }
    let mut out = [0u8; 64];
    for y in 0..8 {
        for x in 0..8 {
            let mut s = 0.0;
            for v in 0..8 {
                s += c[y][v] * tmp[v][x];
            }
            out[y * 8 + x] = s.round().clamp(0.0, 255.0) as u8;
        }
    }
    out
}

struct FrameParams {
    idp: u32,
    dtd: bool,
    alt: bool,
    ivf: bool,
    qst: bool,
}

struct Ctx {
    frame: usize,
    mb: usize,
}

impl Ctx {
    fn trunc(&self) -> IpuError {
        IpuError::Truncated { frame: self.frame, mb: self.mb }
    }
    fn bad(&self, what: &'static str) -> IpuError {
        IpuError::Invalid { frame: self.frame, mb: self.mb, what }
    }
}

fn decode_block(br: &mut Bits, ctx: &Ctx, comp: usize, pred: &mut [i32; 3], qscale: i32, p: &FrameParams) -> Result<[u8; 64], IpuError> {
    let dc_table: &[(u16, u8)] = if comp == 0 { &DC_LUM } else { &DC_CHR };
    let size = br.vlc(dc_table).ok_or_else(|| ctx.bad("dc size"))?;
    let diff = if size == 0 {
        0
    } else {
        let bits = br.read(size).ok_or_else(|| ctx.trunc())? as i32;
        if bits < (1 << (size - 1)) { bits + 1 - (1 << size) } else { bits }
    };
    pred[comp] += diff;
    let mut f = [0i32; 64];
    f[0] = pred[comp] * (8 >> p.idp);
    let table: &[(u16, u8)] = if p.ivf { &B15 } else { &B14 };
    let scan = if p.alt { &ALT_SCAN } else { &ZIGZAG };
    let mut i = 0usize;
    loop {
        let idx = br.vlc(table).ok_or_else(|| ctx.bad("ac code"))?;
        if idx == EOB {
            break;
        }
        let (run, level) = if idx == ESC {
            let run = br.read(6).ok_or_else(|| ctx.trunc())? as usize;
            let mut l = br.read(12).ok_or_else(|| ctx.trunc())? as i32;
            if l >= 2048 {
                l -= 4096;
            }
            (run as u8, l)
        } else {
            let (r, l) = run_level(idx);
            let sign = br.read(1).ok_or_else(|| ctx.trunc())?;
            (r, if sign == 1 { -l } else { l })
        };
        i += run as usize + 1;
        if i > 63 {
            return Err(ctx.bad("coefficient index"));
        }
        let pos = scan[i] as usize;
        f[pos] = ((level * INTRA_MATRIX[pos] as i32 * qscale) / 16).clamp(-2048, 2047);
    }
    // mismatch control
    let sum: i32 = f.iter().sum();
    if sum & 1 == 0 {
        f[63] += if f[63] & 1 != 0 { -1 } else { 1 };
    }
    Ok(idct8x8(&f))
}

fn yuv_to_rgba(y: u8, cb: u8, cr: u8) -> [u8; 4] {
    let (y, cb, cr) = (y as i32 - 16, cb as i32 - 128, cr as i32 - 128);
    let c = |v: i32| ((v + 128) >> 8).clamp(0, 255) as u8;
    [c(298 * y + 409 * cr), c(298 * y - 100 * cb - 208 * cr), c(298 * y + 516 * cb), 255]
}

/// Decode every frame of an `ipum` payload (the bytes at the TIHD image offset).
pub fn decode_ipum(data: &[u8]) -> Result<IpuMovie, IpuError> {
    if !is_ipum(data) {
        return Err(IpuError::BadMagic);
    }
    let width = u16::from_le_bytes([data[8], data[9]]) as usize;
    let height = u16::from_le_bytes([data[10], data[11]]) as usize;
    let nframes = u32::from_le_bytes([data[12], data[13], data[14], data[15]]) as usize;
    let (mbw, mbh) = (width / 16, height / 16);
    let mut br = Bits { d: data, pos: 0x10 * 8 };
    let mut frames = Vec::with_capacity(nframes);
    for frame in 0..nframes {
        let mut ctx = Ctx { frame, mb: 0 };
        let b0 = br.read(8).ok_or_else(|| ctx.trunc())?;
        let p = FrameParams { idp: b0 & 3, dtd: b0 & 4 != 0, alt: b0 & 0x10 != 0, ivf: b0 & 0x20 != 0, qst: b0 & 0x40 != 0 };
        if b0 & 0x80 != 0 {
            return Err(IpuError::Mpeg1);
        }
        let mut pred = [128i32 << p.idp; 3];
        let mut qcode = 1usize; // IDEC QSC = 1
        let mut rgba = vec![0u8; width * height * 4];
        for mb in 0..mbw * mbh {
            ctx.mb = mb;
            // macroblock_address_increment: every macroblock but the first (the IDEC slice starts after the first MBAI)
            if mb > 0 {
                let inc = br.vlc(&MBAI).ok_or_else(|| ctx.bad("macroblock_address_increment"))?;
                if inc != 0 {
                    return Err(ctx.bad("skipped macroblock in an intra frame"));
                }
            }
            // macroblock_type (I picture, table B.2): 1 = intra, 01 = intra + quantiser_scale_code
            let quant = match br.read(1).ok_or_else(|| ctx.trunc())? {
                1 => false,
                _ => {
                    if br.read(1).ok_or_else(|| ctx.trunc())? != 1 {
                        return Err(ctx.bad("macroblock_type"));
                    }
                    true
                }
            };
            if p.dtd {
                br.read(1).ok_or_else(|| ctx.trunc())?; // dct_type (field DCT not supported: treated as frame)
            }
            if quant {
                qcode = br.read(5).ok_or_else(|| ctx.trunc())? as usize;
            }
            let qscale = if p.qst { QSCALE_NONLINEAR[qcode.min(31)] as i32 } else { (qcode * 2) as i32 };
            let mut blocks: Vec<[u8; 64]> = Vec::with_capacity(6);
            for comp in [0usize, 0, 0, 0, 1, 2] {
                blocks.push(decode_block(&mut br, &ctx, comp, &mut pred, qscale, &p)?);
            }
            let (x0, y0) = ((mb % mbw) * 16, (mb / mbw) * 16);
            for py in 0..16 {
                for px in 0..16 {
                    let yb = &blocks[(py / 8) * 2 + px / 8];
                    let y = yb[(py % 8) * 8 + px % 8];
                    let cb = blocks[4][(py / 2) * 8 + px / 2];
                    let cr = blocks[5][(py / 2) * 8 + px / 2];
                    let o = ((y0 + py) * width + x0 + px) * 4;
                    rgba[o..o + 4].copy_from_slice(&yuv_to_rgba(y, cb, cr));
                }
            }
        }
        // end of the slice: byte alignment + 32-bit start code
        br.align();
        if br.peek(24) == Some(1) {
            br.pos += 32;
        }
        frames.push(rgba);
    }
    Ok(IpuMovie { width, height, frames })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn tables_are_prefix_free_and_complete() {
        for t in [&B14, &B15] {
            let mut kraft = 0f64;
            for (i, &(c, l)) in t.iter().enumerate() {
                assert!((c as u32) < (1 << l), "code {i} does not fit its length");
                kraft += 0.5f64.powi(l as i32);
                for (j, &(c2, l2)) in t.iter().enumerate() {
                    if i != j && l2 >= l {
                        assert_ne!(c2 >> (l2 - l), c, "code {i} is a prefix of {j}");
                    }
                }
            }
            assert!(kraft > 0.99 && kraft <= 1.0, "kraft sum {kraft}");
        }
    }

    #[test]
    fn run_level_layout() {
        assert_eq!(run_level(0), (0, 1));
        assert_eq!(run_level(39), (0, 40));
        assert_eq!(run_level(40), (1, 1));
        assert_eq!(run_level(110), (31, 1));
    }

    #[test]
    fn dc_only_block_is_flat() {
        let mut f = [0i32; 64];
        f[0] = 1024; // 128 * 8
        let b = idct8x8(&f);
        assert!(b.iter().all(|&v| v == 128));
    }
}

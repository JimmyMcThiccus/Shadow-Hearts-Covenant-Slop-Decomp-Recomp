//! GS pixel storage modes and the small helpers in `libgsx.cpp` that deal with them.
//!
//! JP: 0x002234c0 GetPSMtoBPP, 0x00223510 GetBufferWidth, 0x00223580 GetTexWidth, 0x002235c0 GetTexBit,
//!     0x00222fe0 Gsx::GetBPPtoPSM, 0x003c6990 P2GetBPPtoPSM, and the bit layout of `GsxFrameBuf`.

/// GS pixel storage mode (`GS_PSM` in the original).  Values are the hardware PSM codes.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
#[repr(u8)]
pub enum Psm {
    Ct32 = 0x00,
    Ct24 = 0x01,
    Ct16 = 0x02,
    Ct16S = 0x0a,
    T8 = 0x13,
    T4 = 0x14,
    /// 8-bit indices stored in bits 24..31 of a 32-bit word (alpha byte of a 24-bit buffer).
    T8H = 0x1b,
    /// 4-bit indices stored in bits 24..27 (low nibble of the top byte).
    T4HL = 0x24,
    /// 4-bit indices stored in bits 28..31 (high nibble of the top byte).
    T4HH = 0x2c,
    Z32 = 0x30,
    Z24 = 0x31,
    Z16 = 0x32,
    Z16S = 0x3a,
}

impl Psm {
    pub fn from_code(c: u8) -> Option<Psm> {
        use Psm::*;
        Some(match c {
            0x00 => Ct32,
            0x01 => Ct24,
            0x02 => Ct16,
            0x0a => Ct16S,
            0x13 => T8,
            0x14 => T4,
            0x1b => T8H,
            0x24 => T4HL,
            0x2c => T4HH,
            0x30 => Z32,
            0x31 => Z24,
            0x32 => Z16,
            0x3a => Z16S,
            _ => return None,
        })
    }

    /// JP: 0x002234c0 `GetPSMtoBPP` (table `PSMtoBPPtbl` @0x003fd8c0).
    pub fn bpp(self) -> u32 {
        use Psm::*;
        match self {
            Ct32 | Z32 => 32,
            Ct24 | Z24 => 24,
            Ct16 | Ct16S | Z16 | Z16S => 16,
            T8 | T8H => 8,
            T4 | T4HL | T4HH => 4,
        }
    }

    /// JP: 0x00222fe0 `Gsx::GetBPPtoPSM(bpp, z)`.
    pub fn from_bpp(bpp: u32, z: bool) -> Option<Psm> {
        Some(match (bpp, z) {
            (32, false) => Psm::Ct32,
            (32, true) => Psm::Z32,
            (24, false) => Psm::Ct24,
            (24, true) => Psm::Z24,
            (16, false) => Psm::Ct16,
            (16, true) => Psm::Z16S,
            (8, _) => Psm::T8,
            (4, _) => Psm::T4,
            _ => return None,
        })
    }

    /// JP: 0x003c6990 `P2GetBPPtoPSM(bpp, z)` — the 2D layer maps 8/4 bpp to the *H* formats.
    pub fn from_bpp_p2(bpp: u32, z: bool) -> Option<Psm> {
        match bpp {
            8 => Some(Psm::T8H),
            4 => Some(Psm::T4HH),
            _ => Psm::from_bpp(bpp, z),
        }
    }
}

/// One row of `PageSizeTbl` (@0x003fd7c0): geometry of a GS page for a given pixel size.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct PageGeom {
    pub bpp: u32,
    pub page_w: u32,
    pub page_h: u32,
    pub blocks_x: u32,
    pub blocks_y: u32,
    pub block_w: u32,
    pub block_h: u32,
}

pub const PAGE_TABLE: [PageGeom; 4] = [
    PageGeom { bpp: 32, page_w: 64, page_h: 32, blocks_x: 8, blocks_y: 4, block_w: 8, block_h: 8 },
    PageGeom { bpp: 16, page_w: 64, page_h: 64, blocks_x: 4, blocks_y: 8, block_w: 16, block_h: 8 },
    PageGeom { bpp: 8, page_w: 128, page_h: 64, blocks_x: 8, blocks_y: 4, block_w: 16, block_h: 16 },
    PageGeom { bpp: 4, page_w: 128, page_h: 128, blocks_x: 4, blocks_y: 8, block_w: 32, block_h: 16 },
];

/// JP: 0x00223510 `GetBufferWidth(psm)` — page width in pixels (24 bpp counts as 32).
pub fn buffer_width(psm: Psm) -> u32 {
    let mut bpp = psm.bpp();
    if bpp == 24 {
        bpp = 32;
    }
    PAGE_TABLE.iter().find(|g| g.bpp == bpp).map(|g| g.page_w).unwrap_or(0)
}

/// JP: 0x00223580 `GetTexWidth(n)` — next power of two >= n (min 1).
pub fn tex_width(n: u32) -> u32 {
    let mut v = 1u32;
    while v < n {
        v <<= 1;
    }
    v
}

/// JP: 0x002235c0 `GetTexBit(n)` — ceil(log2(n)).
pub fn tex_bit(n: u32) -> u32 {
    let mut v = 1u32;
    let mut b = 0;
    while v < n {
        v <<= 1;
        b += 1;
    }
    b
}

/// Decoded form of the 64-bit word at offset 0 of `GsxFrameBuf` / `GsxRaster`
/// (decompiled in `libgsx.cpp`, see decomp/B/GsxFrameBuf.c).
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct FrameBufDesc {
    /// Base in GS blocks (256 B units, TBP-style): bits 0..13.
    pub base: u16,
    /// Buffer width in 64-pixel units: bits 14..19.
    pub tbw: u8,
    /// PSM code: bits 20..25.
    pub psm: u8,
    /// log2 of the power-of-two texture width / height: bits 26..29 / 30..33.
    pub tw: u8,
    pub th: u8,
    /// Real pixel width / height: bits 35..45 / 46..56.
    pub width: u16,
    pub height: u16,
    /// byte 7 bit1: never recorded in the VRAM bitmap (`CreateS` with mark=false) so never freed.
    pub is_static: bool,
    /// byte 7 bit2: allocated through `MakeFlagsChain` (linear run of blocks, not a 2-D surface).
    pub is_chain: bool,
}

impl FrameBufDesc {
    pub fn pack(&self) -> u64 {
        (self.base as u64 & 0x3fff)
            | ((self.tbw as u64 & 0x3f) << 14)
            | ((self.psm as u64 & 0x3f) << 20)
            | ((self.tw as u64 & 0xf) << 26)
            | ((self.th as u64 & 0xf) << 30)
            | ((self.width as u64 & 0x7ff) << 35)
            | ((self.height as u64 & 0x7ff) << 46)
            | ((self.is_static as u64) << 57)
            | ((self.is_chain as u64) << 58)
    }

    pub fn unpack(v: u64) -> Self {
        FrameBufDesc {
            base: (v & 0x3fff) as u16,
            tbw: ((v >> 14) & 0x3f) as u8,
            psm: ((v >> 20) & 0x3f) as u8,
            tw: ((v >> 26) & 0xf) as u8,
            th: ((v >> 30) & 0xf) as u8,
            width: ((v >> 35) & 0x7ff) as u16,
            height: ((v >> 46) & 0x7ff) as u16,
            is_static: (v >> 57) & 1 != 0,
            is_chain: (v >> 58) & 1 != 0,
        }
    }

    /// `Create(psm, w, h)` field computation (the allocation search itself is irrelevant on a modern GPU).
    pub fn for_surface(base: u16, psm: Psm, w: u32, h: u32) -> Self {
        let pw = buffer_width(psm).max(1);
        let tbw = ((w + pw - 1) / pw * pw) >> 6;
        FrameBufDesc {
            base,
            tbw: tbw as u8,
            psm: psm as u8,
            tw: tex_bit(tex_width(w)) as u8,
            th: tex_bit(tex_width(h)) as u8,
            width: w as u16,
            height: h as u16,
            is_static: false,
            is_chain: false,
        }
    }
}

// ---------------------------------------------------------------------------------------------
// PSMCT32 swizzle (for reading VRAM dumps taken from PCSX2 when verifying the port).
// ---------------------------------------------------------------------------------------------

const CT32_BLOCK: [[u32; 8]; 4] = [
    [0, 1, 4, 5, 16, 17, 20, 21],
    [2, 3, 6, 7, 18, 19, 22, 23],
    [8, 9, 12, 13, 24, 25, 28, 29],
    [10, 11, 14, 15, 26, 27, 30, 31],
];
const CT32_COLUMN: [[u32; 8]; 2] = [[0, 1, 4, 5, 8, 9, 12, 13], [2, 3, 6, 7, 10, 11, 14, 15]];

/// Word (32-bit) address in GS local memory of pixel (x,y) of a PSMCT32 surface at block `base`
/// with buffer width `tbw` (in 64-px units).
pub fn ct32_word_addr(base_block: u32, tbw: u32, x: u32, y: u32) -> u32 {
    let page = (y >> 5) * tbw + (x >> 6);
    let block = CT32_BLOCK[((y >> 3) & 3) as usize][((x >> 3) & 7) as usize];
    let column = (y >> 1) & 3;
    let word = CT32_COLUMN[(y & 1) as usize][(x & 7) as usize];
    base_block * 64 + page * 2048 + block * 64 + column * 16 + word
}

/// Read a whole PSMCT32 surface out of a raw 4 MiB VRAM dump into linear RGBA8 (A kept raw: 0x80 = 1.0).
pub fn ct32_read_surface(vram: &[u8], base_block: u32, tbw: u32, w: u32, h: u32) -> Vec<u8> {
    let mut out = vec![0u8; (w * h * 4) as usize];
    for y in 0..h {
        for x in 0..w {
            let a = ct32_word_addr(base_block, tbw, x, y) as usize * 4;
            let o = ((y * w + x) * 4) as usize;
            out[o..o + 4].copy_from_slice(&vram[a..a + 4]);
        }
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn bpp_roundtrip() {
        for p in [Psm::Ct32, Psm::Ct24, Psm::Ct16, Psm::T8H, Psm::T4HH, Psm::Z24] {
            assert_eq!(Psm::from_code(p as u8), Some(p));
        }
        assert_eq!(Psm::T8H.bpp(), 8);
        assert_eq!(Psm::from_bpp(24, true), Some(Psm::Z24));
        assert_eq!(Psm::from_bpp_p2(4, false), Some(Psm::T4HH));
    }

    #[test]
    fn pow2() {
        assert_eq!(tex_width(448), 512);
        assert_eq!(tex_bit(448), 9);
        assert_eq!(tex_bit(1), 0);
        assert_eq!(buffer_width(Psm::Ct24), 64);
        assert_eq!(buffer_width(Psm::T4HH), 128);
    }

    #[test]
    fn framebuf_pack() {
        let d = FrameBufDesc::for_surface(0x0e00, Psm::Ct24, 512, 448);
        assert_eq!(d.tbw, 8);
        assert_eq!(d.tw, 9);
        assert_eq!(d.th, 9);
        assert_eq!(FrameBufDesc::unpack(d.pack()), d);
    }

    #[test]
    fn ct32_bijective_over_a_page() {
        let mut seen = std::collections::HashSet::new();
        for y in 0..32 {
            for x in 0..64 {
                assert!(seen.insert(ct32_word_addr(0, 1, x, y)));
            }
        }
        assert_eq!(seen.len(), 2048);
        assert!(seen.iter().all(|&a| a < 2048));
    }
}

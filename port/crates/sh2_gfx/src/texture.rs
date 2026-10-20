//! Texture container decoders -> RGBA8.  See notes/B/Texture.md for the evidence behind each layout.
//!
//! Conventions common to all of them:
//! * Pixel data is a *linear raster* (row-major, top row first) exactly as it was DMA'd into the GS: the GS does the swizzling,
//!   the files do not.  4-bit data is two pixels per byte, **low nibble first**.
//! * Palettes are PSMCT32 RGBA8 with GS alpha (0x80 = opaque).  `Rgba8Image` converts alpha to 0..255 (`min(a*2,255)`).
//! * 8-bit palettes of *file assets* (model textures, MenuTexture) are stored in the GS CSM1 order (entry bits 3 and 4 swapped);
//!   logical colour `p` is `file[csm1_swizzle(p)]`.  (Verified on SAVELOAD.PKB: the ramp restores monotonic after the swap.)
//!   Palettes built at run time (fonts, `ClutRaster`) are sorted by `ClutRaster::ClutSort`, the same permutation.

use thiserror::Error;

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Rgba8Image {
    pub width: u32,
    pub height: u32,
    /// `width*height*4` bytes, straight (non-premultiplied) RGBA with alpha 0..255.
    pub pixels: Vec<u8>,
}

impl Rgba8Image {
    pub fn new(width: u32, height: u32) -> Self {
        Rgba8Image { width, height, pixels: vec![0; (width * height * 4) as usize] }
    }
    pub fn px(&self, x: u32, y: u32) -> [u8; 4] {
        let o = ((y * self.width + x) * 4) as usize;
        [self.pixels[o], self.pixels[o + 1], self.pixels[o + 2], self.pixels[o + 3]]
    }
}

#[derive(Debug, Error, PartialEq, Eq)]
pub enum TexError {
    #[error("data truncated: need {need} bytes at offset {off}, have {have}")]
    Truncated { off: usize, need: usize, have: usize },
    #[error("unsupported bit depth {0}")]
    BadBpp(u32),
    #[error("IPU (MPEG-2 intra) texture: decode with an MPEG decoder (payload {len} bytes)")]
    Ipu { len: usize },
    #[error("palette required but missing")]
    NoPalette,
}

fn need(b: &[u8], off: usize, n: usize) -> Result<(), TexError> {
    if off.checked_add(n).map(|e| e <= b.len()).unwrap_or(false) {
        Ok(())
    } else {
        Err(TexError::Truncated { off, need: n, have: b.len() })
    }
}
fn u16le(b: &[u8], o: usize) -> u16 {
    u16::from_le_bytes([b[o], b[o + 1]])
}
fn u32le(b: &[u8], o: usize) -> u32 {
    u32::from_le_bytes([b[o], b[o + 1], b[o + 2], b[o + 3]])
}

/// GS alpha (0x80 = 1.0) -> 0..255.
#[inline]
pub fn gs_alpha(a: u8) -> u8 {
    a.saturating_mul(2)
}

/// CSM1 palette permutation for 256-entry palettes (swap bits 3 and 4). Involution.
#[inline]
pub fn csm1_swizzle(i: usize) -> usize {
    (i & !0x18) | ((i & 0x08) << 1) | ((i & 0x10) >> 1)
}

/// Read `count` RGBA8 palette entries (GS alpha kept raw).  For 256-entry palettes `csm1` selects file(=GS CSM1) -> logical order.
pub fn read_palette(b: &[u8], off: usize, count: usize, csm1: bool) -> Result<Vec<[u8; 4]>, TexError> {
    need(b, off, count * 4)?;
    let file: Vec<[u8; 4]> = (0..count).map(|i| [b[off + 4 * i], b[off + 4 * i + 1], b[off + 4 * i + 2], b[off + 4 * i + 3]]).collect();
    if csm1 && count == 256 {
        Ok((0..256).map(|p| file[csm1_swizzle(p)]).collect())
    } else {
        Ok(file)
    }
}

/// Decode a linear 4/8-bit indexed raster through a palette.
pub fn decode_indexed(pix: &[u8], w: u32, h: u32, bpp: u32, pal: &[[u8; 4]]) -> Result<Rgba8Image, TexError> {
    let n = (w * h) as usize;
    let mut img = Rgba8Image::new(w, h);
    match bpp {
        8 => {
            if pix.len() < n {
                return Err(TexError::Truncated { off: 0, need: n, have: pix.len() });
            }
            for i in 0..n {
                let c = pal.get(pix[i] as usize).copied().unwrap_or([0, 0, 0, 0]);
                img.pixels[i * 4..i * 4 + 4].copy_from_slice(&[c[0], c[1], c[2], gs_alpha(c[3])]);
            }
        }
        4 => {
            let nb = (n + 1) / 2;
            if pix.len() < nb {
                return Err(TexError::Truncated { off: 0, need: nb, have: pix.len() });
            }
            for i in 0..n {
                let byte = pix[i / 2];
                let idx = if i & 1 == 0 { byte & 0xf } else { byte >> 4 };
                let c = pal.get(idx as usize).copied().unwrap_or([0, 0, 0, 0]);
                img.pixels[i * 4..i * 4 + 4].copy_from_slice(&[c[0], c[1], c[2], gs_alpha(c[3])]);
            }
        }
        b => return Err(TexError::BadBpp(b)),
    }
    Ok(img)
}

/// PSMCT32 raster (RGBA8, GS alpha).
pub fn decode_rgba32(pix: &[u8], w: u32, h: u32) -> Result<Rgba8Image, TexError> {
    let n = (w * h * 4) as usize;
    if pix.len() < n {
        return Err(TexError::Truncated { off: 0, need: n, have: pix.len() });
    }
    let mut img = Rgba8Image::new(w, h);
    for i in 0..(w * h) as usize {
        img.pixels[i * 4..i * 4 + 3].copy_from_slice(&pix[i * 4..i * 4 + 3]);
        img.pixels[i * 4 + 3] = gs_alpha(pix[i * 4 + 3]);
    }
    Ok(img)
}

/// PSMCT24 raster (RGB, 3 bytes/pixel), opaque.
pub fn decode_rgb24(pix: &[u8], w: u32, h: u32) -> Result<Rgba8Image, TexError> {
    let n = (w * h * 3) as usize;
    if pix.len() < n {
        return Err(TexError::Truncated { off: 0, need: n, have: pix.len() });
    }
    let mut img = Rgba8Image::new(w, h);
    for i in 0..(w * h) as usize {
        img.pixels[i * 4..i * 4 + 3].copy_from_slice(&pix[i * 3..i * 3 + 3]);
        img.pixels[i * 4 + 3] = 255;
    }
    Ok(img)
}

/// PSMCT16 raster (A1 B5 G5 R5, little endian).
pub fn decode_rgba5551(pix: &[u8], w: u32, h: u32) -> Result<Rgba8Image, TexError> {
    let n = (w * h * 2) as usize;
    if pix.len() < n {
        return Err(TexError::Truncated { off: 0, need: n, have: pix.len() });
    }
    let mut img = Rgba8Image::new(w, h);
    for i in 0..(w * h) as usize {
        let v = u16::from_le_bytes([pix[i * 2], pix[i * 2 + 1]]);
        let r = (v & 31) as u8;
        let g = ((v >> 5) & 31) as u8;
        let b = ((v >> 10) & 31) as u8;
        let a = (v >> 15) as u8;
        img.pixels[i * 4..i * 4 + 4].copy_from_slice(&[r << 3 | r >> 2, g << 3 | g >> 2, b << 3 | b >> 2, a * 255]);
    }
    Ok(img)
}

// ---------------------------------------------------------------------------------------------------------------
// _ModelTextureHeader  (Texture::CreateData, JP 0x002474e0)
// ---------------------------------------------------------------------------------------------------------------

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct ModelTextureHeader {
    pub width: u16,
    pub height: u16,
    /// 4, 8 or 32.
    pub bpp: u8,
    /// bit6 of the format byte: payload is MPEG-2 (IPU) data.
    pub ipu: bool,
    pub mip_count: u8,
    pub clut_count: u16,
    pub clut_offset: u16,
    pub image_offset: u32,
    pub mip_offset: u32,
    /// +0x1c: packed ALPHA_1 (A=(v&2) B=(v&0xc)>>2 C=(v&0x20)>>4 D=(v&0xc0)>>6 FIX=v>>8), 0 = default blend.
    pub alpha_bits: u16,
    /// +0x1e: alpha-test reference (0 = no test); test is ATST=GEQUAL.
    pub atest_ref: u8,
    /// +0x1f & 3: AFAIL mode.
    pub atest_fail: u8,
}

impl ModelTextureHeader {
    pub const SIZE: usize = 0x20;
    pub fn parse(b: &[u8], off: usize) -> Result<Self, TexError> {
        need(b, off, Self::SIZE)?;
        let fmt = b[off + 8];
        Ok(ModelTextureHeader {
            width: u16le(b, off + 4),
            height: u16le(b, off + 6),
            bpp: fmt & 0x3f,
            ipu: fmt & 0x40 != 0,
            mip_count: b[off + 10],
            clut_count: u16le(b, off + 12),
            clut_offset: u16le(b, off + 14),
            image_offset: u32le(b, off + 16),
            mip_offset: u32le(b, off + 20),
            alpha_bits: u16le(b, off + 28),
            atest_ref: b[off + 30],
            atest_fail: b[off + 31] & 3,
        })
    }
}

#[derive(Clone, Debug)]
pub struct ModelTexture {
    pub header: ModelTextureHeader,
    /// Level 0 first.  Empty for IPU textures (see `ipu_payload`).
    pub levels: Vec<Rgba8Image>,
    /// For IPU textures: byte range of the MPEG-2 payload inside the blob.
    pub ipu_payload: Option<std::ops::Range<usize>>,
}

/// Decode a model texture at `off` inside `blob`, including its mip chain.
pub fn decode_model_texture(blob: &[u8], off: usize) -> Result<ModelTexture, TexError> {
    let hdr = ModelTextureHeader::parse(blob, off)?;
    if hdr.ipu {
        // size of the payload is not stored here; callers know the container extent. Report from image offset to end.
        let start = off + hdr.image_offset as usize;
        return Ok(ModelTexture { header: hdr, levels: vec![], ipu_payload: Some(start..blob.len()) });
    }
    let pal = if hdr.clut_count != 0 {
        Some(read_palette(blob, off + hdr.clut_offset as usize, hdr.clut_count as usize, true)?)
    } else {
        None
    };
    let mut levels = Vec::new();
    let mut cur = off;
    let mut h = hdr;
    for level in 0..=(hdr.mip_count as usize) {
        let w = h.width as u32;
        let ht = h.height as u32;
        let io = cur + h.image_offset as usize;
        let img = match hdr.bpp {
            4 | 8 => {
                let n = if hdr.bpp == 4 { ((w * ht + 1) / 2) as usize } else { (w * ht) as usize };
                need(blob, io, n)?;
                decode_indexed(&blob[io..io + n], w, ht, hdr.bpp as u32, pal.as_deref().ok_or(TexError::NoPalette)?)?
            }
            32 => {
                let n = (w * ht * 4) as usize;
                need(blob, io, n)?;
                decode_rgba32(&blob[io..io + n], w, ht)?
            }
            b => return Err(TexError::BadBpp(b as u32)),
        };
        levels.push(img);
        if level == hdr.mip_count as usize || h.mip_offset == 0 {
            break;
        }
        cur += h.mip_offset as usize;
        h = ModelTextureHeader::parse(blob, cur)?;
    }
    Ok(ModelTexture { header: hdr, levels, ipu_payload: None })
}

// ---------------------------------------------------------------------------------------------------------------
// MenuTexture image (primLayer/prim2D/primTex/FontDraw users)  — header verified against SAVELOAD.PKB
// ---------------------------------------------------------------------------------------------------------------

/// `{u16 w; u16 h; u8 bpp(4|8); u8 has_clut; u16 clut_count; u32 pix_off; u32 clut_off}` (offsets relative to the header).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct MenuTexHeader {
    pub width: u16,
    pub height: u16,
    pub bpp: u8,
    pub has_clut: bool,
    pub clut_count: u16,
    pub pix_off: u32,
    pub clut_off: u32,
}

impl MenuTexHeader {
    pub fn parse(b: &[u8], off: usize) -> Result<Self, TexError> {
        need(b, off, 16)?;
        Ok(MenuTexHeader {
            width: u16le(b, off),
            height: u16le(b, off + 2),
            bpp: b[off + 4],
            has_clut: b[off + 5] != 0,
            clut_count: u16le(b, off + 6),
            pix_off: u32le(b, off + 8),
            clut_off: u32le(b, off + 12),
        })
    }
}

pub fn decode_menu_texture(blob: &[u8], off: usize) -> Result<Rgba8Image, TexError> {
    let h = MenuTexHeader::parse(blob, off)?;
    let (w, ht) = (h.width as u32, h.height as u32);
    let n = if h.bpp == 4 { ((w * ht + 1) / 2) as usize } else { (w * ht) as usize };
    let po = off + h.pix_off as usize;
    need(blob, po, n)?;
    if !h.has_clut {
        return Err(TexError::NoPalette);
    }
    let pal = read_palette(blob, off + h.clut_off as usize, h.clut_count as usize, true)?;
    decode_indexed(&blob[po..po + n], w, ht, h.bpp as u32, &pal)
}

// ---------------------------------------------------------------------------------------------------------------
// P2 image blobs (P2TexTex / P2GraTex)
// ---------------------------------------------------------------------------------------------------------------

/// `P2TexTex`: `{u16 w; u16 h; u8 bpp @4; u16 clut_count @6; u32 image_off @8; u32 clut_off @0xc}`.
pub fn decode_p2_textex(blob: &[u8], off: usize) -> Result<Rgba8Image, TexError> {
    need(blob, off, 16)?;
    let w = u16le(blob, off) as u32;
    let h = u16le(blob, off + 2) as u32;
    let bpp = blob[off + 4] as u32;
    let nclut = u16le(blob, off + 6) as usize;
    let io = off + u32le(blob, off + 8) as usize;
    let co = off + u32le(blob, off + 12) as usize;
    match bpp {
        4 | 8 => {
            let n = if bpp == 4 { ((w * h + 1) / 2) as usize } else { (w * h) as usize };
            need(blob, io, n)?;
            let pal = read_palette(blob, co, nclut, true)?;
            decode_indexed(&blob[io..io + n], w, h, bpp, &pal)
        }
        16 => decode_rgba5551(&blob[io..], w, h),
        24 => decode_rgb24(&blob[io..], w, h),
        32 => decode_rgba32(&blob[io..], w, h),
        b => Err(TexError::BadBpp(b)),
    }
}

// ---------------------------------------------------------------------------------------------------------------
// JRCTex (judgement ring textures)
// ---------------------------------------------------------------------------------------------------------------

/// `{u32 ?; u16 w @4; u16 h @6; u8 fmt @8 (&7: 0=4bit 1=8bit); u16 clut_entries @0xa; u16 palettes-1 @0xc}`, then at +0x10
/// `palettes*clut_entries` RGBA8 colours followed by the pixels.
pub fn decode_jrc(blob: &[u8], off: usize, palette: usize) -> Result<Rgba8Image, TexError> {
    need(blob, off, 0x10)?;
    let w = u16le(blob, off + 4) as u32;
    let h = u16le(blob, off + 6) as u32;
    let fmt = blob[off + 8] & 7;
    let entries = u16le(blob, off + 10) as usize;
    let npal = u16le(blob, off + 12) as usize + 1;
    let pal_base = off + 0x10;
    let pix = pal_base + npal * entries * 4;
    let bpp = match fmt {
        0 => 4,
        1 => 8,
        _ => return Err(TexError::BadBpp(fmt as u32)),
    };
    let n = if bpp == 4 { ((w * h + 1) / 2) as usize } else { (w * h) as usize };
    need(blob, pix, n)?;
    let pal = read_palette(blob, pal_base + palette.min(npal - 1) * entries * 4, entries, true)?;
    decode_indexed(&blob[pix..pix + n], w, h, bpp, &pal)
}

/// [`decode_jrc`] through one 16 colour sub-palette of a 4 bit texture's CLUT (`TEX0.CSA`: the GS reads the 16 logical entries starting at `csa * 16`; textures such as
/// `BTL_000` section 10 (the `Combo Break!` title) hold several of them in one CLUT, e.g. 96 entries = 6 sub-palettes).  Verified live: CSA 3 of that title is the crimson
/// banner of a party actor, CSA 0 the blue one; the swizzle matters (without it CSA 3 reads an opaque gold ramp).
pub fn decode_jrc_csa(blob: &[u8], off: usize, csa: usize) -> Result<Rgba8Image, TexError> {
    need(blob, off, 0x10)?;
    let w = u16le(blob, off + 4) as u32;
    let h = u16le(blob, off + 6) as u32;
    let fmt = blob[off + 8] & 7;
    let entries = u16le(blob, off + 10) as usize;
    let npal = u16le(blob, off + 12) as usize + 1;
    if fmt != 0 || entries < (csa + 1) * 16 {
        return decode_jrc(blob, off, 0);
    }
    let pal_base = off + 0x10;
    let pix = pal_base + npal * entries * 4;
    let n = ((w * h + 1) / 2) as usize;
    need(blob, pix, n)?;
    // the CLUT is stored in GS CSM1 order (entry numbers with bits 3 and 4 swapped within every 32 entries); `CSA` counts logical entries
    let file = read_palette(blob, pal_base, entries, false)?;
    let pal: Vec<[u8; 4]> = (0..16).map(|i| file.get(csm1_swizzle(csa * 16 + i)).copied().unwrap_or([0; 4])).collect();
    decode_indexed(&blob[pix..pix + n], w, h, 4, &pal)
}

// ---------------------------------------------------------------------------------------------------------------
// Font (2 bits per pixel glyphs, SJIS indexed)
// ---------------------------------------------------------------------------------------------------------------

/// Index of a Shift-JIS double byte code in the glyph table (`Font::GetFontCode`, JP 0x00272ec0).
pub fn font_code_sjis(code: u16) -> u16 {
    let mut hi = code >> 8;
    if hi > 0xdf {
        hi = hi.wrapping_sub(0x40);
    }
    let mut lo = code & 0xff;
    if lo > 0x7f {
        lo -= 1;
    }
    (hi.wrapping_sub(0x81)).wrapping_mul(0xbc).wrapping_add(lo.wrapping_sub(0x40))
}

/// Expand a 2-bit-per-pixel glyph (4 px per byte, LSB first, rows byte-aligned) to levels 0..3.
pub fn decode_glyph_2bpp(data: &[u8], w: usize, h: usize) -> Vec<u8> {
    let stride = (w + 3) / 4;
    let mut out = vec![0u8; w * h];
    for y in 0..h {
        for x in 0..w {
            let b = data.get(y * stride + x / 4).copied().unwrap_or(0);
            out[y * w + x] = (b >> ((x & 3) * 2)) & 3;
        }
    }
    out
}

/// Header fields of a font blob (see decomp/B/Font.c; the offsets at +0x10.. are relative to the blob start).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct FontHeader {
    pub cell_w: u8,
    pub line_h: u8,
    pub pal_log: u8,
    pub full_glyph_bytes: u16,
    pub half_glyph_bytes: u16,
    pub n_ranges: u16,
    pub off_clut: u32,
    pub off_glyphs: u32,
    pub off_ranges: u32,
    pub off_aux: u32,
}
impl FontHeader {
    pub fn parse(b: &[u8], off: usize) -> Result<Self, TexError> {
        need(b, off, 0x24)?;
        Ok(FontHeader {
            cell_w: b[off],
            line_h: b[off + 1],
            pal_log: b[off + 2],
            full_glyph_bytes: u16le(b, off + 4),
            half_glyph_bytes: u16le(b, off + 6),
            n_ranges: u16le(b, off + 0xc),
            off_clut: u32le(b, off + 0x10),
            off_glyphs: u32le(b, off + 0x14),
            off_ranges: u32le(b, off + 0x18),
            off_aux: u32le(b, off + 0x1c),
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn csm1_is_involution() {
        for i in 0..256 {
            assert_eq!(csm1_swizzle(csm1_swizzle(i)), i);
        }
        assert_eq!(csm1_swizzle(8), 16);
        assert_eq!(csm1_swizzle(16), 8);
        assert_eq!(csm1_swizzle(7), 7);
        assert_eq!(csm1_swizzle(24), 24);
    }

    #[test]
    fn indexed4_low_nibble_first() {
        let pal: Vec<[u8; 4]> = (0..16).map(|i| [i as u8 * 16, 0, 0, 0x80]).collect();
        let img = decode_indexed(&[0x21, 0x43], 4, 1, 4, &pal).unwrap();
        assert_eq!(img.px(0, 0)[0], 16);
        assert_eq!(img.px(1, 0)[0], 32);
        assert_eq!(img.px(3, 0)[0], 64);
        assert_eq!(img.px(0, 0)[3], 255);
    }

    #[test]
    fn model_texture_8bit_roundtrip() {
        // header: w=2,h=2,bpp=8, clut 256 at 0x20, image at 0x420
        let mut b = vec![0u8; 0x420 + 4];
        b[4..6].copy_from_slice(&2u16.to_le_bytes());
        b[6..8].copy_from_slice(&2u16.to_le_bytes());
        b[8] = 8;
        b[12..14].copy_from_slice(&256u16.to_le_bytes());
        b[14..16].copy_from_slice(&0x20u16.to_le_bytes());
        b[16..20].copy_from_slice(&0x420u32.to_le_bytes());
        for i in 0..256usize {
            // file entry f holds logical colour csm1(f): make red = logical index
            let logical = csm1_swizzle(i);
            b[0x20 + i * 4] = logical as u8;
            b[0x20 + i * 4 + 3] = 0x80;
        }
        b[0x420..0x424].copy_from_slice(&[0, 8, 16, 255]);
        let t = decode_model_texture(&b, 0).unwrap();
        assert_eq!(t.levels.len(), 1);
        let im = &t.levels[0];
        // logical index p maps to file[csm1(p)] whose red = csm1(csm1(p)) = p
        assert_eq!(im.px(0, 0)[0], 0);
        assert_eq!(im.px(1, 0)[0], 8);
        assert_eq!(im.px(0, 1)[0], 16);
        assert_eq!(im.px(1, 1)[0], 255);
    }

    #[test]
    fn sjis_code() {
        assert_eq!(font_code_sjis(0x8140), 0); // first double-byte glyph
        assert_eq!(font_code_sjis(0x8141), 1);
        assert_eq!(font_code_sjis(0x8240), 0xbc);
    }

    #[test]
    fn glyph_2bpp() {
        let g = decode_glyph_2bpp(&[0b11_10_01_00, 0b00_00_00_11], 5, 1);
        assert_eq!(g, vec![0, 1, 2, 3, 3]);
    }

    /// Real asset check: SAVELOAD.PKB entry 0 (256x224 8bpp menu texture) when the disc folder is available.
    #[test]
    fn savedata_background_decodes() {
        let Ok(dir) = std::env::var("SH2_DISC_DIR") else { return };
        let p = std::path::Path::new(&dir).join("SAVELOAD.PKB");
        let Ok(b) = std::fs::read(p) else { return };
        let img = decode_menu_texture(&b, 0xb0).unwrap();
        assert_eq!((img.width, img.height), (256, 224));
        // CSM1 order restores the ramp: colours of consecutive logical indices 0..24 are non-decreasing in red.
        let pal = read_palette(&b, 0xb0 + 0xe010, 256, true).unwrap();
        for i in 1..24 {
            assert!(pal[i][0] >= pal[i - 1][0], "ramp broken at {i}");
        }
    }
}

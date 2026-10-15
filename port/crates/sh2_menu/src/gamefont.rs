//! The game's own bitmap menu fonts (`Font::CreateFont` / `Font::GetFont` / `GetFontCode`, JP 0x00272c90..0x00273470).
//!
//! A font blob (`COMMON/CMNMENU.DAT` attach 0 = font 0, `MENU/DAT/CMDMENU.MSD` attach 1 / 0 = fonts 2 / 3) is
//!
//! ```text
//! +0 u8 cell width   +1 u8 cell height   +4 u16 bytes per full-width glyph   +6 u16 bytes per half-width glyph
//! +8 u8 n8 (leading full glyphs, 0 in all three)   +9 u8 n9 half-width glyphs (95: 0x20..=0x7e)
//! +0xc u16 range count   +0x10 CLUT   +0x14 glyph bitmaps   +0x18 ranges {u16 start, u16 count}   +0x1c metrics
//! ```
//!
//! Glyph bitmaps are 2 bits per pixel, 4 pixels per byte LSB first, rows byte aligned; level 0 is transparent and 1..3 index a 4 entry
//! CLUT row (`CSA` colour set: row `n` = 4 RGBA entries at `CLUT + 16 n`, alpha 0x80 = opaque).  Half-width glyphs (ASCII) come first,
//! then the full-width glyphs in the order of the ranges, which are expressed in `GetFontCode` space (`(lead - 0x81) * 0xbc + trail - 0x40`
//! with the two Shift-JIS gaps removed).  The metrics table holds `{u8 x_offset, u8 advance}` per glyph (half-width first): only the columns
//! the stored bitmap is cropped to `advance` columns (rows are `ceil(advance / 4)` bytes), drawn `x_offset` pixels into the cell, and the pen
//! moves by `x_offset + advance` -- a proportional font.  Full-width glyphs with code >= 0x4c4 (most kanji) fill the whole cell.
//!
//! # Retail layout
//!
//! `Font::CreateFont` (US 0x0026fb90) tells the two layouts apart by the first u32 of the blob (0 = retail):
//!
//! ```text
//! +4 u8 cell width   +5 u8 cell height   +8 u16 bytes per full glyph   +0xa u16 bytes per half glyph
//! +0xc u16 n8 leading full glyphs   +0xe u16 n9a half glyphs of table 1 (codes 0x20..)   +0x10 u16 n9b half glyphs of table 2
//! +0x14 u16 range count   +0x18 CLUT   +0x1c glyph data   +0x20 ranges   +0x24 metrics   +0x28 u16 limit1   +0x2a u16 limit2
//! ```
//!
//! Glyph data order: n8 full glyphs, table 1, table 2, full-width glyphs; the metrics follow the same order.  Single bytes below `limit1`
//! use table 1 (`code - 0x20`), bytes in `limit1..limit2` use table 2 (`code - limit1`: the accented Latin letters, so 8 bit text such
//! as `Champs \xb5lys\xb6es` renders), everything else is the Shift-JIS path of the old layout.

use crate::sjis;

#[derive(Clone, Debug)]
pub struct GameFont {
    data: Vec<u8>,
    pub cell_w: usize,
    pub cell_h: usize,
    full_bytes: usize,
    half_bytes: usize,
    n8: usize,
    n9: usize,
    ranges: Vec<(usize, usize)>,
    /// glyph number of the first glyph of each range
    range_first: Vec<usize>,
    off_clut: usize,
    off_glyphs: usize,
    off_metrics: usize,
    /// retail layout: half-width table 2 (count, first code, limit of table 1 = first code of table 2)
    n9b: usize,
    limit1: usize,
    limit2: usize,
    /// FNV-1a hash of the blob: identifies the font for the hi-res fit cache ([`crate::hifont`])
    pub key: u64,
}

/// A rendered line of text.
#[derive(Clone, Debug)]
pub struct TextImage {
    pub width: u32,
    pub height: u32,
    /// straight RGBA8
    pub pixels: Vec<u8>,
}

fn u16at(d: &[u8], o: usize) -> usize {
    d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).unwrap_or(0)
}
fn u32at(d: &[u8], o: usize) -> usize {
    d.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]) as usize).unwrap_or(0)
}

fn fnv(d: &[u8]) -> u64 {
    d.iter().fold(0xcbf2_9ce4_8422_2325u64, |h, &b| (h ^ b as u64).wrapping_mul(0x100_0000_01b3))
}

/// `Font::GetFontCode`: Shift-JIS double byte -> glyph code space.
pub fn font_code(code: u16) -> u16 {
    let mut hi = code >> 8;
    if hi > 0xdf {
        hi = hi.wrapping_sub(0x40);
    }
    let mut lo = code & 0xff;
    if lo > 0x7f {
        lo -= 1;
    }
    hi.wrapping_sub(0x81).wrapping_mul(0xbc).wrapping_add(lo.wrapping_sub(0x40))
}

impl GameFont {
    pub fn parse(blob: &[u8]) -> Option<Self> {
        if blob.len() < 0x40 {
            return None;
        }
        if u32at(blob, 0) == 0 {
            return Self::parse_retail(blob);
        }
        let (cell_w, cell_h) = (blob[0] as usize, blob[1] as usize);
        let (full_bytes, half_bytes) = (u16at(blob, 4), u16at(blob, 6));
        let (n8, n9) = (blob[8] as usize, blob[9] as usize);
        let nr = u16at(blob, 0xc);
        let (off_clut, off_glyphs, off_ranges, off_metrics) = (u32at(blob, 0x10), u32at(blob, 0x14), u32at(blob, 0x18), u32at(blob, 0x1c));
        if cell_w == 0 || cell_h == 0 || full_bytes == 0 || off_glyphs >= blob.len() || off_ranges + nr * 4 > blob.len() || off_metrics >= blob.len() {
            return None;
        }
        let mut ranges = Vec::with_capacity(nr);
        let mut range_first = Vec::with_capacity(nr);
        let mut acc = 0;
        for i in 0..nr {
            let (s, c) = (u16at(blob, off_ranges + i * 4), u16at(blob, off_ranges + i * 4 + 2));
            ranges.push((s, c));
            range_first.push(acc);
            acc += c;
        }
        Some(GameFont { data: blob.to_vec(), cell_w, cell_h, full_bytes, half_bytes, n8, n9, ranges, range_first, off_clut, off_glyphs, off_metrics, n9b: 0, limit1: 0x20 + n9, limit2: 0x20 + n9, key: fnv(blob) })
    }

    /// Retail header (see the module docs).
    fn parse_retail(blob: &[u8]) -> Option<Self> {
        let (cell_w, cell_h) = (blob[4] as usize, blob[5] as usize);
        let (full_bytes, half_bytes) = (u16at(blob, 8), u16at(blob, 0xa));
        let (n8, n9, n9b, nr) = (u16at(blob, 0xc), u16at(blob, 0xe), u16at(blob, 0x10), u16at(blob, 0x14));
        let (off_clut, off_glyphs, off_ranges, off_metrics) = (u32at(blob, 0x18), u32at(blob, 0x1c), u32at(blob, 0x20), u32at(blob, 0x24));
        let (limit1, limit2) = (u16at(blob, 0x28), u16at(blob, 0x2a));
        if cell_w == 0 || cell_h == 0 || full_bytes == 0 || off_glyphs >= blob.len() || off_ranges + nr * 4 > blob.len() || off_metrics >= blob.len() {
            return None;
        }
        let mut ranges = Vec::with_capacity(nr);
        let mut range_first = Vec::with_capacity(nr);
        let mut acc = 0;
        for i in 0..nr {
            let (s, c) = (u16at(blob, off_ranges + i * 4), u16at(blob, off_ranges + i * 4 + 2));
            ranges.push((s, c));
            range_first.push(acc);
            acc += c;
        }
        Some(GameFont { data: blob.to_vec(), cell_w, cell_h, full_bytes, half_bytes, n8, n9, ranges, range_first, off_clut, off_glyphs, off_metrics, n9b, limit1, limit2, key: fnv(blob) })
    }

    /// CLUT row `set`: 4 RGBA entries.
    pub fn palette(&self, set: usize) -> [[u8; 4]; 4] {
        let mut p = [[0u8; 4]; 4];
        let base = self.off_clut + set * 16;
        for (k, e) in p.iter_mut().enumerate() {
            if let Some(b) = self.data.get(base + k * 4..base + k * 4 + 4) {
                e.copy_from_slice(b);
            }
        }
        if p[3][3] == 0 {
            // missing row: fall back to row 0
            if set != 0 {
                return self.palette(0);
            }
        }
        p
    }

    /// Glyph for `ch`: `(bitmap rows, bytes per row, x_offset, advance)`; `None` = not in the font.
    fn glyph(&self, ch: char) -> Option<(&[u8], usize, usize, usize)> {
        let sj = sjis::encode(&ch.to_string());
        let (bytes_per_row, glyph, metric_idx);
        let mut proportional = true;
        if sj.len() == 1 {
            let c = sj[0] as usize;
            // table 1: codes 0x20..limit1; retail table 2: limit1..limit2 (accented letters)
            let i = if (0x20..self.limit1).contains(&c) && c - 0x20 < self.n9 {
                c - 0x20
            } else if (self.limit1..self.limit2).contains(&c) && c - self.limit1 < self.n9b {
                self.n9 + (c - self.limit1)
            } else {
                return None;
            };
            let off = self.off_glyphs + self.n8 * self.full_bytes + i * self.half_bytes;
            glyph = self.data.get(off..off + self.half_bytes)?;
            bytes_per_row = self.half_bytes / self.cell_h;
            metric_idx = self.n8 + i;
        } else if sj.len() == 2 {
            let code = font_code(((sj[0] as u16) << 8) | sj[1] as u16) as usize;
            // `GetFont`: only code indices below 0x4c4 (kana, symbols, the first kanji block) have metrics; the rest use the full cell
            proportional = code < 0x4c4;
            let r = self.ranges.iter().position(|&(s, c)| code >= s && code < s + c)?;
            let g = self.range_first[r] + code - self.ranges[r].0;
            let off = self.off_glyphs + self.n8 * self.full_bytes + (self.n9 + self.n9b) * self.half_bytes + g * self.full_bytes;
            glyph = self.data.get(off..off + self.full_bytes)?;
            bytes_per_row = self.full_bytes / self.cell_h;
            metric_idx = self.n8 + self.n9 + self.n9b + g;
        } else {
            return None;
        }
        if !proportional {
            return Some((glyph, self.cell_w.div_ceil(4), 0, self.cell_w));
        }
        let m = self.off_metrics + metric_idx * 2;
        let (xo, adv) = (*self.data.get(m)? as usize, *self.data.get(m + 1)? as usize);
        // `SetFont`: the stored bitmap is cropped to the advance width (rows are `ceil(adv / 4)` bytes) and drawn `xo` pixels in
        let _ = bytes_per_row;
        Some((glyph, adv.div_ceil(4), xo, adv))
    }

    /// Glyph `ch` as `(x_offset, advance, levels)`: `levels` is `cell_h` rows of `advance` 2-bit levels (0 = transparent .. 3 = full).
    pub fn glyph_levels(&self, ch: char) -> Option<(usize, usize, Vec<u8>)> {
        let (g, bpr, xo, adv) = self.glyph(ch)?;
        let mut lv = vec![0u8; self.cell_h * adv];
        for y in 0..self.cell_h {
            for x in 0..adv {
                let b = g.get(y * bpr + x / 4).copied().unwrap_or(0);
                lv[y * adv + x] = (b >> ((x & 3) * 2)) & 3;
            }
        }
        Some((xo, adv, lv))
    }

    pub fn debug_ranges(&self) -> (&[(usize, usize)], &[usize]) {
        (&self.ranges, &self.range_first)
    }

    pub fn debug_raw(&self, ch: char) -> Vec<u8> {
        self.glyph(ch).map(|g| g.0.to_vec()).unwrap_or_default()
    }

    /// Debug: (font code, x offset, advance).
    pub fn debug_glyph(&self, ch: char) -> Option<(usize, usize, usize)> {
        let sj = sjis::encode(&ch.to_string());
        let code = if sj.len() == 2 { font_code(((sj[0] as u16) << 8) | sj[1] as u16) as usize } else { 0 };
        self.glyph(ch).map(|(_, _, xo, adv)| (code, xo, adv))
    }

    /// Pen advance of a string in cell pixels (unknown characters count as a half cell).
    pub fn measure(&self, s: &str, spacing: i32) -> f32 {
        s.chars()
            .map(|c| match self.glyph(c) {
                Some((_, _, xo, adv)) => (xo + adv) as i32 + spacing,
                None => self.cell_w as i32 / 2 + spacing,
            })
            .sum::<i32>()
            .max(0) as f32
    }

    /// Rasterise a single line with colour row `set`.
    pub fn render(&self, s: &str, set: usize, spacing: i32) -> Option<TextImage> {
        let w = (self.measure(s, spacing) as usize).max(1) + 1;
        let h = self.cell_h;
        let pal = self.palette(set);
        let mut px = vec![0u8; w * h * 4];
        let mut pen = 0i32;
        for ch in s.chars() {
            match self.glyph(ch) {
                Some((g, bpr, xo, adv)) => {
                    for y in 0..h {
                        for sx in 0..adv {
                            let x = xo + sx;
                            let b = g.get(y * bpr + sx / 4).copied().unwrap_or(0);
                            let level = ((b >> ((sx & 3) * 2)) & 3) as usize;
                            if level == 0 {
                                continue;
                            }
                            let dx = pen + x as i32;
                            if dx < 0 || dx as usize >= w {
                                continue;
                            }
                            let o = (y * w + dx as usize) * 4;
                            let e = pal[level];
                            px[o] = e[0];
                            px[o + 1] = e[1];
                            px[o + 2] = e[2];
                            px[o + 3] = (e[3] as u32 * 2).min(255) as u8;
                        }
                    }
                    pen += (xo + adv) as i32 + spacing;
                }
                None => pen += self.cell_w as i32 / 2 + spacing,
            }
        }
        Some(TextImage { width: w as u32, height: h as u32, pixels: px })
    }
}

/// The four font slots of `Font::fontWork` (0 and 1 from the common scene, 2 and 3 from the command menu); a missing slot falls back to 0.
#[derive(Clone, Debug, Default)]
pub struct FontBank {
    pub fonts: [Option<GameFont>; 4],
}

impl FontBank {
    pub fn get(&self, n: u8) -> Option<&GameFont> {
        self.fonts.get(n as usize).and_then(|f| f.as_ref()).or(self.fonts[0].as_ref())
    }

    /// Build from an unpacked disc folder (`COMMON/CMNMENU.DAT`, `MENU/DAT/MFIELD.MSD`, `MENU/DAT/CMDMENU.MSD`).  Font 1 is the field
    /// font (`MenuFieldStationed::GetReady`: `CreateFont(1, ..)` from the resident `MFIELD.MSD`): the condensed serif of the message
    /// windows and name plates (live: US dialogue boxes).
    pub fn load(files: &dyn crate::disc::FileSource) -> FontBank {
        use crate::msd::Msd;
        let mut bank = FontBank::default();
        let attach = |path: &str, i: usize| -> Option<Vec<u8>> {
            let m = Msd::parse(files.read(path)?).ok()?;
            m.attach_data(i).map(|b| b.to_vec())
        };
        bank.fonts[0] = attach("COMMON/CMNMENU.DAT", 0).and_then(|b| GameFont::parse(&b));
        bank.fonts[1] = attach("MENU/DAT/MFIELD.MSD", 0).and_then(|b| GameFont::parse(&b));
        if let Some(m) = files.read("MENU/DAT/CMDMENU.MSD").and_then(|d| Msd::parse(d).ok()) {
            bank.fonts[3] = m.attach_data(0).and_then(GameFont::parse);
            bank.fonts[2] = m.attach_data(1).and_then(GameFont::parse);
        }
        bank
    }

    /// Cell pixel height of the font the menu uses for `font_number`.
    pub fn cell_h(&self, n: u8) -> f32 {
        self.get(n).map(|f| f.cell_h as f32).unwrap_or(20.0)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn font_code_matches_the_decompiled_formula() {
        // あ = 0x82a0: (0x82 - 0x81) * 0xbc + (0xa0 - 1 - 0x40) = 283
        assert_eq!(font_code(0x82a0), 283);
        assert_eq!(font_code(0x8140), 0);
    }

    #[test]
    fn menu_fonts_render_real_glyphs() {
        let Ok(dir) = std::env::var("SH2_DISC_DIR") else { return };
        let d = crate::disc::DiscDir::open(dir).unwrap();
        let bank = FontBank::load(&d);
        let f = bank.get(0).expect("font 0");
        assert_eq!((f.cell_w, f.cell_h), (20, 20));
        // ASCII is proportional, kana are ~19 wide ('あ': x offset 2, width 17)
        let a = f.measure("あ", 0);
        assert_eq!(a, 19.0);
        assert!(f.measure("iii", 0) < f.measure("MMM", 0));
        let img = f.render("アイテム", 0, 0).unwrap();
        assert!(img.pixels.chunks(4).any(|p| p[3] > 0));
        assert!(bank.get(2).is_some() && bank.get(3).is_some());
        assert_eq!(bank.get(3).unwrap().cell_h, 12);
    }

    /// The US retail fonts use the retail header (first u32 = 0): `COMMON/CMNMENU.DAT` attach 0 = font 0, `CMDMENU.MSD` attach 1 / 0 = fonts 2 / 3.
    #[test]
    fn us_menu_fonts_render_ascii_and_accents() {
        let Ok(dir) = std::env::var("SH2_US_DISC_DIR") else { return };
        let d = crate::disc::DiscDir::open(dir).unwrap();
        let bank = FontBank::load(&d);
        let f = bank.get(0).expect("font 0 parses with the retail layout");
        assert_eq!((f.cell_w, f.cell_h), (20, 20));
        assert!(bank.get(2).is_some() && bank.get(3).is_some());
        assert_eq!(bank.fonts[2].as_ref().map(|f| f.cell_h), Some(20));
        // proportional Latin: narrow letters are narrower than wide ones, every printable ASCII code has a glyph
        assert!(f.measure("iii", 0) < f.measure("MMM", 0));
        for c in 0x20u8..0x7f {
            let ch = c as char;
            if ch != ' ' {
                let img = f.render(&ch.to_string(), 0, 0).unwrap();
                assert!(img.pixels.chunks(4).any(|p| p[3] > 0), "glyph {ch:?} is empty");
            }
        }
        // table 2: the accented letters of `Champs \xb5lys\xb6es` (single bytes 0x80..) decode through Shift-JIS to half-width katakana
        let text = crate::sjis::decode(b"Champs \xb5lys\xb6es");
        let img = f.render(&text, 0, 0).unwrap();
        assert!(img.width > 100);
        let plain = f.measure("Champs lyses", 0);
        assert!(f.measure(&text, 0) > plain, "the accented letters take space");
    }
}

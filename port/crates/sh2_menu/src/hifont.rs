//! Hi-res text: the game's 2-bit bitmap fonts ([`GameFont`]) redrawn with matched outline fonts at the window's resolution.
//!
//! No font on either US disc exists above 22 px (`COMMON/CMNMENU.DAT` 20x20, `MENU/DAT/CMNMENU.DAT` 20x20, `MENU/DAT/MFIELD.MSD` 22x22,
//! `MENU/DAT/CMDMENU.MSD` 22x20 + 12x12, all 2 bpp), so the port stretched them.  The Latin glyphs are the half-width glyphs of Japanese
//! PC typefaces; scoring every glyph against outline fonts (`examples/font_scan.rs`, `font_export.rs`, notes/integration/hires_fonts.md):
//!
//! * dialogue (`MFIELD.MSD`): a bold Century Schoolbook condensed to ~0.71 -- free clone: TeX Gyre Schola Bold;
//! * menus (`CMNMENU.DAT`): the MS Gothic skeleton at a heavier weight -- free match: BIZ UDGothic Bold (also has kana / kanji);
//! * command font (`CMDMENU.MSD` #1): the same gothic with a 1 px dark rim (CLUT level 2 = rim, level 3 = body); scored with the rim it
//!   looks like Impact, scored on the body alone it is BIZ UDGothic Bold again.  The rim is redrawn around the fitted body.
//!
//! The faces live in `port/assets/fonts` (`SH2_HIRES_FONT_DIR` overrides).  Layout never changes: every glyph keeps the game's own pen
//! advance, and its outline is fitted into the ink box of the game bitmap.  Which face (and how much stroke growth) fits a given
//! [`GameFont`] is measured against its bitmaps the first time it is drawn ([`fit_for`]); a font no face matches, and characters a face
//! lacks, fall back to the bitmap (bilinear).  The colour comes from the font's own 4-level CLUT row, so shaded / outlined palettes keep
//! their ramp.  `SH2_HIRES_TEXT=0` turns the whole path off.

use crate::gamefont::{GameFont, TextImage};
use ab_glyph::{Font, FontVec, OutlineCurve, Point};
use ab_glyph_rasterizer::{point, Rasterizer};
use std::collections::HashMap;
use std::path::PathBuf;
use std::sync::{Arc, Mutex, OnceLock};

/// An outline font the fitter may pick.
pub struct Face {
    pub name: String,
    font: Arc<FontVec>,
    /// synthetic oblique: x += y * slant (the cut-scene caption fonts are a bold italic serif; no italic face is bundled)
    slant: f32,
}

/// Slant of the synthetic oblique variant every bundled face gets (~11 degrees, a typical italic angle).
const OBLIQUE: f32 = 0.2;

/// The chosen face for one [`GameFont`].
#[derive(Clone, Debug)]
pub struct Fit {
    pub face: usize,
    /// stroke growth in game pixels (the bitmaps are bolder than the outlines at this size)
    pub grow: f32,
    /// mean absolute coverage error against the bitmaps (0 = identical)
    pub error: f32,
    /// characters drawn with another code point of the face (typographic quotes where the game draws curly ones)
    alts: Vec<(char, char)>,
    /// outlined font (`CMDMENU.MSD` #1: level 3 = body, level 2 = a 1 px dark rim): the face is fitted to the body and the rim redrawn
    pub outline: bool,
}

impl Fit {
    fn map(&self, c: char) -> char {
        self.alts.iter().find(|a| a.0 == c).map(|a| a.1).unwrap_or(c)
    }
}

/// Glyphs used to score a face (no symmetric / ambiguous ones like `I`, `l`, `o`).
const FIT_CHARS: &str = "ABCDEFGHJKMNPQRSWXYZabdefghkmnpqrstuyz2345678&?";
const GROWS: [f32; 7] = [0.0, 0.15, 0.3, 0.45, 0.6, 0.8, 1.0];
/// Above this the face is not the font's design; the bitmap stays.
const MAX_ERROR: f32 = 0.2;
const QUOTE_ALTS: [(char, char); 3] = [('\'', '\u{2019}'), ('"', '\u{201d}'), ('`', '\u{2018}')];

pub fn enabled() -> bool {
    static ON: OnceLock<bool> = OnceLock::new();
    *ON.get_or_init(|| !matches!(std::env::var("SH2_HIRES_TEXT").as_deref(), Ok("0") | Ok("off") | Ok("false")))
}

fn font_dirs() -> Vec<PathBuf> {
    let mut v = Vec::new();
    if let Some(d) = std::env::var_os("SH2_HIRES_FONT_DIR") {
        v.push(PathBuf::from(d));
    }
    if let Some(exe) = std::env::current_exe().ok().and_then(|p| p.parent().map(|p| p.to_path_buf())) {
        v.push(exe.join("assets/fonts"));
    }
    v.push(PathBuf::from(concat!(env!("CARGO_MANIFEST_DIR"), "/../../assets/fonts")));
    v
}

/// The outline faces found in the first font folder that has any.
pub fn faces() -> &'static [Face] {
    static FACES: OnceLock<Vec<Face>> = OnceLock::new();
    FACES.get_or_init(|| {
        for dir in font_dirs() {
            let Ok(rd) = std::fs::read_dir(&dir) else { continue };
            let mut paths: Vec<PathBuf> = rd
                .filter_map(|e| e.ok().map(|e| e.path()))
                .filter(|p| p.extension().and_then(|e| e.to_str()).is_some_and(|e| e.eq_ignore_ascii_case("ttf") || e.eq_ignore_ascii_case("otf")))
                .collect();
            paths.sort();
            let mut faces: Vec<Face> = paths
                .iter()
                .filter_map(|p| {
                    let font = Arc::new(FontVec::try_from_vec(std::fs::read(p).ok()?).ok()?);
                    Some(Face { name: p.file_name()?.to_string_lossy().into_owned(), font, slant: 0.0 })
                })
                .collect();
            let obliques: Vec<Face> = faces.iter().map(|f| Face { name: format!("{} (oblique)", f.name), font: f.font.clone(), slant: OBLIQUE }).collect();
            faces.extend(obliques);
            if !faces.is_empty() {
                log::info!("hi-res text: {} outline faces from {}", faces.len(), dir.display());
                return faces;
            }
        }
        log::warn!("hi-res text: no outline fonts found (port/assets/fonts or SH2_HIRES_FONT_DIR); text stays bitmap");
        Vec::new()
    })
}

/// The face that matches `font`, measured once per font.
pub fn fit_for(font: &GameFont) -> Option<Arc<Fit>> {
    static FITS: OnceLock<Mutex<HashMap<u64, Option<Arc<Fit>>>>> = OnceLock::new();
    let fits = FITS.get_or_init(Default::default);
    if let Some(f) = fits.lock().ok()?.get(&font.key) {
        return f.clone();
    }
    let t = std::time::Instant::now();
    let fit = compute_fit(font, faces()).map(Arc::new);
    match &fit {
        Some(f) => log::info!(
            "hi-res text: {}x{} font {:016x} -> {} (grow {:.2}, error {:.3}, {} ms)",
            font.cell_w, font.cell_h, font.key, faces()[f.face].name, f.grow, f.error, t.elapsed().as_millis()
        ),
        None => log::info!("hi-res text: {}x{} font {:016x}: no matching face, bitmap kept", font.cell_w, font.cell_h, font.key),
    }
    fits.lock().ok()?.insert(font.key, fit.clone());
    fit
}

/// A palette whose level 2 is much darker than level 3 draws a rim around the body (the command font), not anti-aliasing.
fn is_outline(pal: &[[u8; 4]; 4]) -> bool {
    let lum = |e: [u8; 4]| e[0] as f32 * 0.3 + e[1] as f32 * 0.59 + e[2] as f32 * 0.11;
    pal[2][3] >= 0x40 && lum(pal[2]) < 0.5 * lum(pal[3])
}

/// The body coverage a glyph's levels stand for: `levels / 3`, or only level 3 for an outlined font.
fn body(lv: &[u8], outline: bool) -> Vec<u8> {
    if outline {
        lv.iter().map(|&l| if l == 3 { 3 } else { 0 }).collect()
    } else {
        lv.to_vec()
    }
}

/// Ink box of a level bitmap: `(x0, y0, x1, y1)`, exclusive ends.
fn ink_box(lv: &[u8], w: usize, h: usize) -> Option<(usize, usize, usize, usize)> {
    let (mut x0, mut y0, mut x1, mut y1) = (usize::MAX, usize::MAX, 0, 0);
    for y in 0..h {
        for x in 0..w {
            if lv[y * w + x] > 0 {
                x0 = x0.min(x);
                y0 = y0.min(y);
                x1 = x1.max(x + 1);
                y1 = y1.max(y + 1);
            }
        }
    }
    (x1 > 0).then_some((x0, y0, x1, y1))
}

struct Shape {
    curves: Vec<OutlineCurve>,
    x0: f32,
    y0: f32,
    x1: f32,
    y1: f32,
}

/// The outline of `c` with its exact ink bounds (control points of curves may lie outside the ink).
fn shape(face: &Face, c: char) -> Option<Shape> {
    let id = face.font.glyph_id(c);
    if id.0 == 0 {
        return None;
    }
    let mut o = face.font.outline(id)?;
    if face.slant != 0.0 {
        let k = face.slant;
        let sh = |p: Point| point(p.x + p.y * k, p.y);
        for c in &mut o.curves {
            *c = match *c {
                OutlineCurve::Line(a, b) => OutlineCurve::Line(sh(a), sh(b)),
                OutlineCurve::Quad(a, b, d) => OutlineCurve::Quad(sh(a), sh(b), sh(d)),
                OutlineCurve::Cubic(a, b, d, e) => OutlineCurve::Cubic(sh(a), sh(b), sh(d), sh(e)),
            };
        }
    }
    let (mut x0, mut y0, mut x1, mut y1) = (f32::MAX, f32::MAX, f32::MIN, f32::MIN);
    let mut add = |p: Point| {
        x0 = x0.min(p.x);
        y0 = y0.min(p.y);
        x1 = x1.max(p.x);
        y1 = y1.max(p.y);
    };
    for c in &o.curves {
        for k in 0..=8 {
            let t = k as f32 / 8.0;
            let u = 1.0 - t;
            add(match *c {
                OutlineCurve::Line(a, b) => point(a.x * u + b.x * t, a.y * u + b.y * t),
                OutlineCurve::Quad(a, b, d) => point(a.x * u * u + 2.0 * b.x * u * t + d.x * t * t, a.y * u * u + 2.0 * b.y * u * t + d.y * t * t),
                OutlineCurve::Cubic(a, b, d, e) => point(
                    a.x * u * u * u + 3.0 * b.x * u * u * t + 3.0 * d.x * u * t * t + e.x * t * t * t,
                    a.y * u * u * u + 3.0 * b.y * u * u * t + 3.0 * d.y * u * t * t + e.y * t * t * t,
                ),
            });
        }
    }
    (x1 > x0 && y1 > y0).then_some(Shape { curves: o.curves, x0, y0, x1, y1 })
}

/// Coverage (`w * h`, 0..1) of `s` fitted into a `w x h` box, grown by `grow` pixels (the growth stays inside the box).
fn raster(s: &Shape, w: usize, h: usize, grow: f32) -> Vec<f32> {
    let g = grow.min(w as f32 * 0.3).min(h as f32 * 0.3).max(0.0);
    let (iw, ih) = (w as f32 - 2.0 * g, h as f32 - 2.0 * g);
    let (sx, sy) = (iw / (s.x1 - s.x0), ih / (s.y1 - s.y0));
    let m = |p: Point| point(g + (p.x - s.x0) * sx, g + (s.y1 - p.y) * sy);
    let mut r = Rasterizer::new(w, h);
    for c in &s.curves {
        match *c {
            OutlineCurve::Line(a, b) => r.draw_line(m(a), m(b)),
            OutlineCurve::Quad(a, b, d) => r.draw_quad(m(a), m(b), m(d)),
            OutlineCurve::Cubic(a, b, d, e) => r.draw_cubic(m(a), m(b), m(d), m(e)),
        }
    }
    let mut cov = vec![0f32; w * h];
    r.for_each_pixel_2d(|x, y, a| cov[y as usize * w + x as usize] = a.abs().min(1.0));
    if g > 0.05 {
        dilate(&cov, w, h, g)
    } else {
        cov
    }
}

/// Grey-scale dilation by a disc of radius `r` with a soft (anti-aliased) rim.
fn dilate(src: &[f32], w: usize, h: usize, r: f32) -> Vec<f32> {
    let n = (r + 0.5).ceil() as i32;
    let mut offs = Vec::new();
    for dy in -n..=n {
        for dx in -n..=n {
            let wgt = (r + 0.5 - ((dx * dx + dy * dy) as f32).sqrt()).clamp(0.0, 1.0);
            if wgt > 0.0 {
                offs.push((dx, dy, wgt));
            }
        }
    }
    let mut out = vec![0f32; w * h];
    for y in 0..h as i32 {
        for x in 0..w as i32 {
            let mut m = 0f32;
            for &(dx, dy, wgt) in &offs {
                let (sx, sy) = (x + dx, y + dy);
                if sx >= 0 && sy >= 0 && (sx as usize) < w && (sy as usize) < h {
                    m = m.max(src[sy as usize * w + sx as usize] * wgt);
                }
            }
            out[y as usize * w + x as usize] = m;
        }
    }
    out
}

/// Mean coverage error of `c` drawn with `face` against the game glyph (`lv`, `adv` wide), at 2x supersampling.
fn glyph_error(face: &Face, c: char, lv: &[u8], adv: usize, cell_h: usize, grow: f32) -> Option<f32> {
    const SS: usize = 2;
    let (x0, y0, x1, y1) = ink_box(lv, adv, cell_h)?;
    let (bw, bh) = (x1 - x0, y1 - y0);
    let s = shape(face, c)?;
    let cov = raster(&s, bw * SS, bh * SS, grow * SS as f32);
    let mut err = 0f32;
    for y in 0..bh {
        for x in 0..bw {
            let mut a = 0f32;
            for k in 0..SS * SS {
                a += cov[(y * SS + k / SS) * bw * SS + x * SS + k % SS];
            }
            err += (a / (SS * SS) as f32 - lv[(y0 + y) * adv + x0 + x] as f32 / 3.0).abs();
        }
    }
    Some(err / (bw * bh) as f32)
}

/// Round 6 MN3: ink area of `c` drawn with `face` (grown by `grow`) over the game glyph's body area (`lv` levels / 3).
fn glyph_area(face: &Face, c: char, lv: &[u8], adv: usize, cell_h: usize, grow: f32) -> Option<(f32, f32)> {
    const SS: usize = 2;
    let (x0, y0, x1, y1) = ink_box(lv, adv, cell_h)?;
    let (bw, bh) = (x1 - x0, y1 - y0);
    let s = shape(face, c)?;
    let cov = raster(&s, bw * SS, bh * SS, grow * SS as f32);
    let drawn = cov.iter().sum::<f32>() / (SS * SS) as f32;
    let game = lv.iter().map(|&l| l as f32 / 3.0).sum::<f32>();
    Some((drawn, game))
}

fn compute_fit(font: &GameFont, faces: &[Face]) -> Option<Fit> {
    let outline = is_outline(&font.palette(0));
    let glyphs: Vec<(char, usize, Vec<u8>)> = FIT_CHARS.chars().filter_map(|c| font.glyph_levels(c).map(|(_, adv, lv)| (c, adv, body(&lv, outline)))).collect();
    if glyphs.len() < FIT_CHARS.len() / 2 {
        return None;
    }
    let mut best: Option<Fit> = None;
    for (fi, face) in faces.iter().enumerate() {
        let mut per_grow = Vec::new();
        for &grow in &GROWS {
            let errs: Vec<f32> = glyphs.iter().filter_map(|(c, adv, lv)| glyph_error(face, *c, lv, *adv, font.cell_h, grow)).collect();
            if errs.len() < glyphs.len() * 3 / 4 {
                break;
            }
            per_grow.push((grow, errs.iter().sum::<f32>() / errs.len() as f32));
        }
        // the lightest weight within 2 % of this face's best: growth closes counters at high resolution sooner than the score shows
        let Some(min) = per_grow.iter().map(|g| g.1).reduce(f32::min) else { continue };
        let Some(&(mut grow, e)) = per_grow.iter().find(|g| g.1 <= min * 1.02) else { continue };
        // round 6 MN3: the outlined command font (body = level 3 only, a rim drawn around it) came out ~22 % lighter than the bitmap with the
        // lightest-within-2 % rule (live: the lavender `GRADE.` / `No.` / `Monsters` labels were thin); for it the growth that matches the
        // body's ink area wins, among the growths within 50 % of the best score: the score fits the grown outline into the bitmap's ink box,
        // so it always prefers the thinnest stroke (BIZ UDGothic: grow 0 = 0.84 of the bitmap's ink, error 0.165; 0.8 = 0.96, error 0.233).
        // `SH2_HIFONT_DEBUG=1` prints the table; `examples/mn3_weight.rs` the rendered ratio per font.
        if outline {
            let area = |g: f32| -> f32 {
                let (d, t) = glyphs.iter().filter_map(|(c, adv, lv)| glyph_area(face, *c, lv, *adv, font.cell_h, g)).fold((0.0, 0.0), |a, b| (a.0 + b.0, a.1 + b.1));
                if t > 0.0 { d / t } else { 1.0 }
            };
            if std::env::var_os("SH2_HIFONT_DEBUG").is_some() {
                for g in &per_grow {
                    eprintln!("hifont outline fit: face {fi} grow {:.2} error {:.4} area {:.3}", g.0, g.1, area(g.0));
                }
            }
            // (the face's acceptance keeps its best score: the area match is a weight correction, not a worse fit)
            if let Some(&(g2, _)) = per_grow.iter().filter(|g| g.1 <= min * 1.5).min_by(|a, b| (area(a.0) - 1.0).abs().total_cmp(&(area(b.0) - 1.0).abs())) {
                grow = g2;
            }
        }
        if best.as_ref().is_none_or(|b| min < b.error) {
            best = Some(Fit { face: fi, grow, error: e, alts: Vec::new(), outline });
        }
    }
    let mut fit = best.filter(|b| b.error <= MAX_ERROR)?;
    let face = &faces[fit.face];
    for (plain, curly) in QUOTE_ALTS {
        let Some((_, adv, lv)) = font.glyph_levels(plain) else { continue };
        let lv = body(&lv, outline);
        let (a, b) = (glyph_error(face, plain, &lv, adv, font.cell_h, fit.grow), glyph_error(face, curly, &lv, adv, font.cell_h, fit.grow));
        if let (Some(a), Some(b)) = (a, b) {
            if b < a {
                fit.alts.push((plain, curly));
            }
        }
    }
    Some(fit)
}

static WINDOW_H: std::sync::atomic::AtomicU32 = std::sync::atomic::AtomicU32::new(0);

/// Physical height of the primary window as the sprite-layer renderer last saw it ([`crate::bevy_ui`] publishes it every frame), for
/// screens that rasterise their own text without a window query (the save / load data screen).  448 before the first frame.
pub fn window_height() -> f32 {
    match WINDOW_H.load(std::sync::atomic::Ordering::Relaxed) {
        0 => 448.0,
        h => h as f32,
    }
}

pub fn set_window_height(h: u32) {
    WINDOW_H.store(h, std::sync::atomic::Ordering::Relaxed);
}

/// Raster factor for text drawn at `scale` virtual units per font pixel on a window `physical_h` pixels high: `ceil(physical_h / 448 * scale)`,
/// 1..8 (the factor [`crate::bevy_ui`] uses for the sprite layers).
pub fn factor(physical_h: f32, scale: f32) -> u32 {
    (physical_h / 448.0 * scale).ceil().clamp(1.0, 8.0) as u32
}

/// The factor an image of [`render_scaled`] was drawn at (1 when it fell back to the bitmap); its 1x size is `width / f` x `height / f`.
pub fn image_factor(font: &GameFont, img: &TextImage) -> u32 {
    (img.height / font.cell_h.max(1) as u32).max(1)
}

/// [`GameFont::render`] at `scale` times the resolution (same layout, `width * scale` x `cell_h * scale`).  Falls back to the bitmap
/// render when the path is off, `scale <= 1`, or no outline face matches the font.
pub fn render_scaled(font: &GameFont, s: &str, set: usize, spacing: i32, scale: u32) -> Option<TextImage> {
    render_scaled_layout(font, s, set, spacing, scale, false)
}

/// [`render_scaled`] with the glyph layout of [`GameFont::glyph_pen`] (`proportional` = retail `FontDraw::Order`).
pub fn render_scaled_layout(font: &GameFont, s: &str, set: usize, spacing: i32, scale: u32, proportional: bool) -> Option<TextImage> {
    if scale <= 1 || !enabled() {
        return font.render_layout(s, set, spacing, proportional);
    }
    let Some(fit) = fit_for(font) else { return font.render_layout(s, set, spacing, proportional) };
    let face = &faces()[fit.face];
    let sc = scale as usize;
    let (w1, h1) = ((font.measure_layout(s, spacing, proportional) as usize).max(1) + 1, font.cell_h);
    let (w, h) = (w1 * sc, h1 * sc);
    let mut cov = vec![0f32; w * h];
    let mut put = |x: i64, y: i64, a: f32| {
        if x >= 0 && y >= 0 && (x as usize) < w && (y as usize) < h {
            let o = y as usize * w + x as usize;
            cov[o] = cov[o].max(a);
        }
    };
    let mut pen = 0i64;
    for ch in s.chars() {
        let Some((xo, adv, lv)) = font.glyph_levels(ch) else {
            pen += (font.cell_w / 2) as i64 + spacing as i64;
            continue;
        };
        let lv = body(&lv, fit.outline);
        let (gx0, step) = GameFont::glyph_pen(xo, adv, proportional);
        if let Some((x0, y0, x1, y1)) = ink_box(&lv, adv, h1) {
            let gx = pen + gx0 as i64;
            let drawn = shape(face, fit.map(ch)).map(|sh| raster(&sh, (x1 - x0) * sc, (y1 - y0) * sc, fit.grow * scale as f32));
            match drawn {
                Some(r) => {
                    let (bw, bh) = ((x1 - x0) * sc, (y1 - y0) * sc);
                    for y in 0..bh {
                        for x in 0..bw {
                            put((gx + x0 as i64) * sc as i64 + x as i64, (y0 * sc + y) as i64, r[y * bw + x]);
                        }
                    }
                }
                None => {
                    // not in the face (kanji of a Latin face, symbols): the bitmap glyph, bilinear
                    let at = |x: i64, y: i64| if x < 0 || y < 0 || x as usize >= adv || y as usize >= h1 { 0.0 } else { lv[y as usize * adv + x as usize] as f32 / 3.0 };
                    for y in 0..h1 * sc {
                        for x in 0..adv * sc {
                            let (fx, fy) = ((x as f32 + 0.5) / scale as f32 - 0.5, (y as f32 + 0.5) / scale as f32 - 0.5);
                            let (ix, iy) = (fx.floor() as i64, fy.floor() as i64);
                            let (tx, ty) = (fx - ix as f32, fy - iy as f32);
                            let a = (at(ix, iy) * (1.0 - tx) + at(ix + 1, iy) * tx) * (1.0 - ty) + (at(ix, iy + 1) * (1.0 - tx) + at(ix + 1, iy + 1) * tx) * ty;
                            put(gx * sc as i64 + x as i64, y as i64, a);
                        }
                    }
                }
            }
        }
        pen += step as i64 + spacing as i64;
    }
    let pal = font.palette(set);
    let alpha = |e: [u8; 4]| (e[3] as f32 * 2.0).min(255.0);
    let mut px = vec![0u8; w * h * 4];
    if fit.outline {
        // body in level 3 over a 1 game-pixel rim in level 2
        let rim = dilate(&cov, w, h, scale as f32);
        let (cb, cu) = (pal[3], pal[2]);
        for i in 0..w * h {
            let (ab, au) = (cov[i] * alpha(cb) / 255.0, rim[i] * alpha(cu) / 255.0);
            let ao = ab + au * (1.0 - ab);
            if ao <= 1.0 / 255.0 {
                continue;
            }
            for j in 0..3 {
                px[i * 4 + j] = ((cb[j] as f32 * ab + cu[j] as f32 * au * (1.0 - ab)) / ao).round() as u8;
            }
            px[i * 4 + 3] = (ao * 255.0).round() as u8;
        }
        return Some(TextImage { width: w as u32, height: h as u32, pixels: px });
    }
    // colour: coverage walks the font's own 4-level ramp (level 0 = transparent)
    for (i, &c) in cov.iter().enumerate() {
        if c <= 1.0 / 255.0 {
            continue;
        }
        let l = (c * 3.0).min(3.0);
        let k = (l.floor() as usize).min(2);
        let t = l - k as f32;
        let (ea, eb) = (if k == 0 { pal[1] } else { pal[k] }, pal[k + 1]);
        let aa = if k == 0 { 0.0 } else { alpha(ea) };
        for j in 0..3 {
            px[i * 4 + j] = (ea[j] as f32 * (1.0 - t) + eb[j] as f32 * t).round() as u8;
        }
        px[i * 4 + 3] = (aa * (1.0 - t) + alpha(eb) * t).round() as u8;
    }
    Some(TextImage { width: w as u32, height: h as u32, pixels: px })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn dilate_grows_a_point_into_a_disc() {
        let mut src = vec![0f32; 9 * 9];
        src[4 * 9 + 4] = 1.0;
        let d = dilate(&src, 9, 9, 2.0);
        assert_eq!(d[4 * 9 + 4], 1.0);
        assert_eq!(d[4 * 9 + 5], 1.0);
        assert_eq!(d[4 * 9 + 6], 0.5); // the rim at exactly `r` is half covered
        assert_eq!(d[4 * 9 + 7], 0.0);
        assert_eq!(d[0], 0.0);
    }

    #[test]
    fn ink_box_is_exclusive() {
        let lv = [0, 0, 0, 0, 3, 1, 0, 0, 0];
        assert_eq!(ink_box(&lv, 3, 3), Some((1, 1, 3, 2)));
        assert_eq!(ink_box(&[0; 4], 2, 2), None);
    }

    /// With the US disc and the bundled faces: each menu font picks the face it was identified with.
    #[test]
    fn us_fonts_pick_their_faces() {
        let Ok(dir) = std::env::var("SH2_US_DISC_DIR") else { return };
        assert!(!faces().is_empty(), "no outline faces in port/assets/fonts");
        use crate::disc::{DiscDir, FileSource};
        use crate::msd::Msd;
        let d = DiscDir::open(dir).unwrap();
        let attach = |p: &str, i: usize| Msd::parse(d.read(p).unwrap()).unwrap().attach_data(i).and_then(GameFont::parse).unwrap();
        for (path, i, want) in [("MENU/DAT/MFIELD.MSD", 0, "texgyreschola"), ("COMMON/CMNMENU.DAT", 0, "BIZUDGothic"), ("MENU/DAT/CMDMENU.MSD", 1, "BIZUDGothic")] {
            let f = attach(path, i);
            let fit = fit_for(&f).unwrap_or_else(|| panic!("{path}: no fit"));
            eprintln!("{path}#{i}: {} grow {:.2} error {:.3} outline {} alts {:?}", faces()[fit.face].name, fit.grow, fit.error, fit.outline, fit.alts);
            assert!(faces()[fit.face].name.starts_with(want), "{path}: picked {} ({:.3})", faces()[fit.face].name, fit.error);
            let img = render_scaled(&f, "Yuri's Karin", 0, 0, 3).unwrap();
            let base = f.render("Yuri's Karin", 0, 0).unwrap();
            assert_eq!((img.width, img.height), (base.width * 3, base.height * 3));
        }
    }
}

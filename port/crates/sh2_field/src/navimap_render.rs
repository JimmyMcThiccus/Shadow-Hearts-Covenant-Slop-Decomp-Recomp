//! `CNaviMap` art, view math and the floor rasteriser (the CPU side of `MakePacket`), see [`crate::navimap`] for the data.

use crate::mps::rd_u16;
use crate::navimap::{NaviData, NaviPicture};

// ---------------------------------------------------------------------------------------------------------------------------------
// static art from the FIELD.BIN overlay (`naviFrame` 0x557680, `naviMask` 0x556270, `naviIcon` 0x558c90 in the JP image)
// ---------------------------------------------------------------------------------------------------------------------------------

/// `P2GraTex` blobs of the overlay: `{u16 w, h, _, _, bpp-code (1 = 8 bit, 2 = 4 bit), _, palette entries, _}`, RGBA palette, pixels.
#[derive(Clone, Debug, Default)]
pub struct NaviArt {
    /// 64 x 72 quadrant of the ring (RGBA8, alpha scaled to 0..255)
    pub frame: NaviPicture,
    /// 64 x 64 circular mask quadrant: palette index per pixel (0 = outside, 127 = inside; coverage = index / 128)
    pub mask: Vec<u8>,
    pub mask_size: (usize, usize),
    /// 16 x 64 marker sheet: gear (v 0), triangles, disc (v 32), square (v 48), white with alpha
    pub icons: NaviPicture,
}

const FRAME_SIG: [u8; 16] = [0x40, 0, 0x48, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1];
const MASK_SIG: [u8; 16] = [0x40, 0, 0x40, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0x80, 0, 0x80, 0];
const ICON_SIG: [u8; 16] = [0x10, 0, 0x40, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0x10, 0, 0x10, 0];

/// GS CSM1 palette order: entries are stored with index bits 3 and 4 swapped.
fn csm1(i: usize) -> usize {
    (i & !0x18) | ((i & 8) << 1) | ((i & 16) >> 1)
}

fn find_sig(d: &[u8], sig: &[u8]) -> Option<usize> {
    d.windows(sig.len()).position(|w| w == sig)
}

/// Decode a `P2GraTex` blob at `o`; returns `(w, h, palette indices, RGBA palette)`.
fn p2_gratex(d: &[u8], o: usize) -> Option<(usize, usize, Vec<u8>, Vec<[u8; 4]>)> {
    let (w, h) = (rd_u16(d, o) as usize, rd_u16(d, o + 2) as usize);
    let code = rd_u16(d, o + 8);
    let n = rd_u16(d, o + 12) as usize;
    let pal_o = o + 16;
    let pix_o = pal_o + ((n + 3) & !3) * 4;
    let mut pal = Vec::with_capacity(n);
    for i in 0..n {
        let e = if code == 1 { csm1(i) } else { i };
        let p = d.get(pal_o + e * 4..pal_o + e * 4 + 4)?;
        pal.push([p[0], p[1], p[2], ((p[3] as u32 * 255 + 64) / 128).min(255) as u8]);
    }
    let idx: Vec<u8> = match code {
        1 => d.get(pix_o..pix_o + w * h)?.to_vec(),
        2 => {
            let b = d.get(pix_o..pix_o + w * h / 2)?;
            (0..w * h).map(|i| if i & 1 == 0 { b[i / 2] & 15 } else { b[i / 2] >> 4 }).collect()
        }
        _ => return None,
    };
    Some((w, h, idx, pal))
}

impl NaviArt {
    /// Find the three blobs in a `FIELD.BIN` image (JP or retail: the data is the same, only the addresses differ).
    pub fn from_overlay(bin: &[u8]) -> Option<NaviArt> {
        let pic = |sig: &[u8]| -> Option<NaviPicture> {
            let (w, h, idx, pal) = p2_gratex(bin, find_sig(bin, sig)?)?;
            let mut rgba = Vec::with_capacity(w * h * 4);
            for &i in &idx {
                rgba.extend_from_slice(&pal.get(i as usize).copied().unwrap_or([0; 4]));
            }
            Some(NaviPicture { w, h, rgba })
        };
        let frame = pic(&FRAME_SIG)?;
        let icons = pic(&ICON_SIG)?;
        let (mw, mh, midx, _) = p2_gratex(bin, find_sig(bin, &MASK_SIG)?)?;
        Some(NaviArt { frame, mask: midx, mask_size: (mw, mh), icons })
    }

    /// Circle coverage (0 outside .. 1 inside) at texel `(u, v)` of the mask quadrant (bilinear).
    pub fn mask_at(&self, u: f32, v: f32) -> f32 {
        let (w, h) = self.mask_size;
        if w == 0 {
            return 1.0;
        }
        let (fu, fv) = ((u - 0.5).clamp(0.0, w as f32 - 1.001), (v - 0.5).clamp(0.0, h as f32 - 1.001));
        let (x0, y0) = (fu as usize, fv as usize);
        let (tx, ty) = (fu - x0 as f32, fv - y0 as f32);
        let g = |x: usize, y: usize| self.mask[y * w + x] as f32 / 128.0;
        let a = g(x0, y0) * (1.0 - tx) + g(x0 + 1, y0) * tx;
        let b = g(x0, y0 + 1) * (1.0 - tx) + g(x0 + 1, y0 + 1) * tx;
        (a * (1.0 - ty) + b * ty).clamp(0.0, 1.0)
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------
// view math (`Update`, `CnvVertex`) and the floor renderer (`MakeMapPacket`)
// ---------------------------------------------------------------------------------------------------------------------------------

/// Radar window in virtual screen pixels: the copy window is 108 x 108 at (26, 33) (`MakePacket`: `x0 + 10`, `y0 + 0x11` with `(x0, y0)` =
/// `this+0x9c/+0xa0` = (16, 16)); the ring is drawn at (16, 16) as four 64 x 72 quadrants, so the whole radar is centred on (80, 88).
pub const WIN_W: usize = 108;
pub const WIN_H: usize = 108;
pub const WIN_POS: [f32; 2] = [26.0, 33.0];
pub const CENTRE: [f32; 2] = [80.0, 88.0];
/// ring quadrant sprites: origin (16, 16), cell 64 x 72
pub const RING_POS: [f32; 2] = [16.0, 16.0];
/// final opacity of the copied picture (`0x50808080` in the copy packet: alpha 0x50 / 0x80)
pub const COPY_ALPHA: f32 = 0x50 as f32 / 128.0;

/// What the field feeds `CNaviMap::Update`.
#[derive(Clone, Copy, Debug, Default)]
pub struct NaviView {
    /// player position (`player_pos`)
    pub player: [f32; 3],
    /// player heading, radians (`CFieldModel +0x24`)
    pub heading: f32,
}

/// Floor picture orientation variants, used while calibrating against the live game.
#[derive(Clone, Copy, Debug)]
pub struct Orient {
    pub flip_y: bool,
    pub flip_x: bool,
    pub yaw_sign: f32,
}

impl Default for Orient {
    fn default() -> Self {
        Orient { flip_y: true, flip_x: false, yaw_sign: 1.0 }
    }
}

impl NaviData {
    /// Rotation of the picture by its quarter turns (`RotYMatrix`) then the lay-down (`RotXMatrix(pi/2)`), as `(x, z) -> (screen x, screen y)`
    /// before the zoom, relative to the grid centre.
    fn to_screen(&self, o: Orient, dx: f32, dz: f32) -> [f32; 2] {
        let a = self.quarter_turns as f32 * std::f32::consts::FRAC_PI_2 * o.yaw_sign;
        let (s, c) = a.sin_cos();
        let x1 = dx * c + dz * s;
        let z1 = -dx * s + dz * c;
        [if o.flip_x { -x1 } else { x1 }, if o.flip_y { -z1 } else { z1 }]
    }

    /// `Update`: the view centre (`this+0x20/+0x24`) = the player's grid offset, clamped so the window never leaves the picture.
    pub fn view_offset(&self, o: Orient, player: [f32; 3]) -> [f32; 2] {
        let c = self.centre();
        let (mut dx, mut dz) = (player[0] - c[0], player[2] - c[1]);
        let half = [(self.grid[0] as f32 + 1.0) * 5.0, (self.grid[1] as f32 + 1.0) * 5.0];
        let view = [(WIN_W as f32 - 48.0) * self.zoom, (WIN_H as f32 - 48.0) * self.zoom];
        let clamp = |d: &mut f32, half: f32, view: f32| {
            if half * 2.0 < view {
                *d = 0.0;
            } else {
                let hv = view * 0.5;
                if *d - hv < -half {
                    *d = hv - half;
                } else if half < *d + hv {
                    *d = half - hv;
                }
            }
        };
        clamp(&mut dx, half[0], view[0]);
        clamp(&mut dz, half[1], view[1]);
        self.to_screen(o, dx, dz)
    }

    /// `CnvVertex`: world position -> offset in window pixels from the window centre.
    pub fn project(&self, o: Orient, off: [f32; 2], p: [f32; 3]) -> [f32; 2] {
        let c = self.centre();
        let s = self.to_screen(o, p[0] - c[0], p[2] - c[1]);
        [(s[0] - off[0]) * 0.9 / self.zoom, (s[1] - off[1]) / self.zoom]
    }
}

fn lerp4(a: [f32; 4], b: [f32; 4], t: f32) -> [f32; 4] {
    [a[0] + (b[0] - a[0]) * t, a[1] + (b[1] - a[1]) * t, a[2] + (b[2] - a[2]) * t, a[3] + (b[3] - a[3]) * t]
}

fn col4(c: [u8; 4]) -> [f32; 4] {
    [c[0] as f32, c[1] as f32, c[2] as f32, c[3] as f32]
}

/// The floor as the copy window sees it: colour (0..255) blended over black, per pixel of the 108 x 108 window.
#[derive(Clone, Debug)]
pub struct NaviFloor {
    pub rgb: Vec<[f32; 3]>,
}

type Vtx = ([f32; 2], [f32; 2], [f32; 4]);

impl NaviData {
    /// Rasterise the visible meshes (`MakeMapPacket`): Gouraud triangles tinted by height (unless `flat`), modulating the picture, drawn with
    /// alpha onto black.
    pub fn render_floor(&self, o: Orient, view: &NaviView) -> NaviFloor {
        let mut rgb = vec![[0.0f32; 3]; WIN_W * WIN_H];
        let off = self.view_offset(o, view.player);
        let base = col4(self.tint[1]);
        let hi = col4(self.tint[0]);
        let lo = col4(self.tint[2]);
        let (cx, cy) = (WIN_W as f32 * 0.5, WIN_H as f32 * 0.5);
        for mesh in self.meshes.iter().filter(|m| m.shown) {
            for t in 0..mesh.pos.len() / 3 {
                let mut v: [Vtx; 3] = [([0.0; 2], [0.0; 2], [0.0; 4]); 3];
                let mut any_alpha = false;
                for k in 0..3 {
                    let p = mesh.pos[t * 3 + k];
                    let s = self.project(o, off, p);
                    // height tint: (y - player y) / 20 clamped to +-1; above uses the `+0x60` tint, below the `+0x58` one
                    let f = if self.flat { 0.0 } else { ((p[1] - view.player[1]) * 0.05).clamp(-1.0, 1.0) };
                    let col = if f < 0.0 { lerp4(base, lo, -f) } else { lerp4(base, hi, f) };
                    if col[3] > 0.0 {
                        any_alpha = true;
                    }
                    v[k] = ([s[0] + cx, s[1] + cy], mesh.uv[t * 3 + k], col);
                }
                if any_alpha {
                    self.fill_triangle(&mut rgb, &v);
                }
            }
        }
        NaviFloor { rgb }
    }

    fn sample(&self, u: f32, v: f32) -> [f32; 4] {
        let pic = &self.picture;
        if pic.w == 0 {
            return [128.0, 128.0, 128.0, 255.0];
        }
        // bilinear with clamp
        let fx = (u * pic.w as f32 - 0.5).clamp(0.0, pic.w as f32 - 1.001);
        let fy = (v * pic.h as f32 - 0.5).clamp(0.0, pic.h as f32 - 1.001);
        let (x0, y0) = (fx as usize, fy as usize);
        let (tx, ty) = (fx - x0 as f32, fy - y0 as f32);
        let px = |x: usize, y: usize| -> [f32; 4] {
            let i = (y * pic.w + x) * 4;
            [pic.rgba[i] as f32, pic.rgba[i + 1] as f32, pic.rgba[i + 2] as f32, pic.rgba[i + 3] as f32]
        };
        let (a, b, c, d) = (px(x0, y0), px(x0 + 1, y0), px(x0, y0 + 1), px(x0 + 1, y0 + 1));
        let mut out = [0.0; 4];
        for i in 0..4 {
            out[i] = (a[i] * (1.0 - tx) + b[i] * tx) * (1.0 - ty) + (c[i] * (1.0 - tx) + d[i] * tx) * ty;
        }
        out
    }

    fn fill_triangle(&self, buf: &mut [[f32; 3]], v: &[Vtx; 3]) {
        let (p0, p1, p2) = (v[0].0, v[1].0, v[2].0);
        let area = (p1[0] - p0[0]) * (p2[1] - p0[1]) - (p2[0] - p0[0]) * (p1[1] - p0[1]);
        if area.abs() < 1e-6 {
            return;
        }
        let minx = p0[0].min(p1[0]).min(p2[0]).floor().max(0.0) as i32;
        let maxx = p0[0].max(p1[0]).max(p2[0]).ceil().min(WIN_W as f32) as i32;
        let miny = p0[1].min(p1[1]).min(p2[1]).floor().max(0.0) as i32;
        let maxy = p0[1].max(p1[1]).max(p2[1]).ceil().min(WIN_H as f32) as i32;
        for y in miny..maxy {
            for x in minx..maxx {
                let (px, py) = (x as f32 + 0.5, y as f32 + 0.5);
                let w0 = ((p1[0] - px) * (p2[1] - py) - (p2[0] - px) * (p1[1] - py)) / area;
                let w1 = ((p2[0] - px) * (p0[1] - py) - (p0[0] - px) * (p2[1] - py)) / area;
                let w2 = 1.0 - w0 - w1;
                if w0 < 0.0 || w1 < 0.0 || w2 < 0.0 {
                    continue;
                }
                let u = v[0].1[0] * w0 + v[1].1[0] * w1 + v[2].1[0] * w2;
                let vv = v[0].1[1] * w0 + v[1].1[1] * w1 + v[2].1[1] * w2;
                let mut col = [0.0f32; 4];
                for i in 0..4 {
                    col[i] = v[0].2[i] * w0 + v[1].2[i] * w1 + v[2].2[i] * w2;
                }
                let t = self.sample(u, vv);
                // GS modulate: texel * vertex / 0x80.  The offscreen picture keeps the colour at full strength (the vertex alpha 0x40 only marks
                // the triangle as visible; calibrated against the live radar: the copy at alpha 0x50 / 0x80 gives the measured brightness)
                let a = t[3] / 255.0;
                let out = &mut buf[y as usize * WIN_W + x as usize];
                for i in 0..3 {
                    let c = (t[i] * col[i] / 128.0).clamp(0.0, 255.0);
                    out[i] = c * a + out[i] * (1.0 - a);
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::mps::Mps;
    use crate::pkb_compat::PkbSet;

    fn us_map(name: &str) -> Option<Mps> {
        let dir = std::env::var_os("SH2_US_DISC_DIR")?;
        let set = PkbSet::open(&dir).ok()?;
        Mps::parse(set.read(&format!("FIELD/MPS/{name}.MPS"))?).ok()
    }

    fn art() -> Option<NaviArt> {
        // the overlay art is identical on both discs; look it up by signature in whichever FIELD.BIN is available
        ["SH2_US_DISC_DIR", "SH2_DISC_DIR"].iter().find_map(|k| {
            NaviArt::from_overlay(&sh2_core::fileio::read_disc_file(std::env::var_os(k)?, "FIELD.BIN").ok()?)
        })
    }

    #[test]
    fn ap_02_u_navimap_matches_the_dump() {
        let Some(mps) = us_map("AP_02_U") else { return };
        let n = crate::navimap::NaviData::from_mps(&mps).expect("NAVIMAP");
        assert_eq!(n.grid, [46, 46]);
        assert_eq!(n.zoom, 2.5);
        assert!(n.flat && !n.mask);
        assert_eq!(n.quarter_turns, 0);
        assert_eq!(n.meshes.len(), 1);
        assert_eq!(n.meshes[0].pos.len(), 756);
        assert_eq!((n.picture.w, n.picture.h), (128, 128));
        assert_eq!(n.markers.len(), 2);
        assert!(n.markers.iter().all(|m| m.kind == 0 && m.color == 2));
        // the grid is centred on the origin + 235 and the picture covers +-229.375 around the world origin
        assert_eq!(n.centre(), [5.625, 5.625]);
        // every vertex lies inside the picture square and its uv is position / 458.75 + 0.5
        for (p, uv) in n.meshes[0].pos.iter().zip(&n.meshes[0].uv) {
            assert!((uv[0] - (p[0] / 458.75 + 0.5)).abs() < 0.003 && (uv[1] - (p[2] / 458.75 + 0.5)).abs() < 0.003, "{p:?} {uv:?}");
        }
    }

    #[test]
    fn every_retail_navimap_parses() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(set) = PkbSet::open(&dir) else { return };
        let Some(list) = set.list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC")) else { return };
        let mut with = 0;
        for name in list.iter().map(|e| e.name.clone()).filter(|n| n.ends_with(".MPS")) {
            let Some(d) = set.read(&format!("FIELD/MPS/{name}")) else { continue };
            let Ok(mps) = Mps::parse(d) else { continue };
            if mps.find(crate::mps::tags::NAVIMAP).is_none() {
                continue;
            }
            with += 1;
            let n = crate::navimap::NaviData::from_mps(&mps).unwrap_or_else(|| panic!("{name}: NAVIMAP does not parse"));
            assert!(n.picture.w > 0 && !n.meshes.is_empty(), "{name}");
            assert!(n.meshes.iter().all(|m| m.pos.len() % 3 == 0), "{name}: mesh is not a triangle list");
        }
        assert!(with > 300, "only {with} maps with a NAVIMAP");
    }

    #[test]
    fn overlay_art_decodes() {
        let Some(a) = art() else { return };
        assert_eq!((a.frame.w, a.frame.h), (64, 72));
        assert_eq!((a.icons.w, a.icons.h), (16, 64));
        assert_eq!(a.mask_size, (64, 64));
        // the mask is closed (coverage 0) in the outer corner and open in the circle
        assert!(a.mask_at(1.0, 1.0) < 0.05);
        assert!(a.mask_at(60.0, 60.0) > 0.95);
        // the ring has opaque metal pixels
        assert!(a.frame.rgba.chunks(4).any(|p| p[3] == 255));
    }

    #[test]
    fn view_follows_the_player_and_clamps_at_the_edge() {
        let Some(mps) = us_map("AP_02_U") else { return };
        let n = crate::navimap::NaviData::from_mps(&mps).unwrap();
        let o = Orient::default();
        // the picture is bigger than the window: the view follows the player ...
        let a = n.view_offset(o, [0.0, 0.0, 0.0]);
        let b = n.view_offset(o, [20.0, 0.0, 0.0]);
        assert!((b[0] - a[0] - 20.0).abs() < 1e-3);
        // ... and stops when the window would leave the picture
        let far = n.view_offset(o, [10_000.0, 0.0, 10_000.0]);
        let far2 = n.view_offset(o, [20_000.0, 0.0, 20_000.0]);
        assert_eq!(far, far2);
        // the player's own projection is the window centre while unclamped
        let s = n.project(o, a, [0.0, 0.0, 0.0]);
        assert!(s[0].abs() < 1e-3 && s[1].abs() < 1e-3);
    }

    #[test]
    fn floor_renders_something_inside_the_circle() {
        let (Some(mps), Some(_)) = (us_map("AP_02_U"), art()) else { return };
        let n = crate::navimap::NaviData::from_mps(&mps).unwrap();
        let f = n.render_floor(Orient::default(), &NaviView { player: [0.0, 0.0, 0.0], heading: 0.0 });
        let lit = f.rgb.iter().filter(|p| p[1] > 20.0 && p[2] > 20.0).count();
        assert!(lit > WIN_W * WIN_H / 3, "{lit} lit pixels");
        // flat maps are tinted with the base colour (0, 0x80, 0xa0): no red
        assert!(f.rgb.iter().all(|p| p[0] < 1.0));
    }
}

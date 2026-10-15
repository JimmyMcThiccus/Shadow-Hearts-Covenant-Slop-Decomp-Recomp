//! `BtlIn` -- the field -> battle encounter transition: the frame breaks into ~190 thick glass shards that flash, tumble and fall away while the battle
//! loads behind a black backdrop (US `BtlIn` ctor 0x003e5290, `CreatePolygon` 0x003e59e0, `Polling` 0x003e6710, `BI_PolGrp::CalcMatrix` 0x003e74f0,
//! `BI_Pol::GetPacket` 0x003e81b0; JP `decomp/H/BtlIn.c`).
//!
//! Retail flow: `CField::StartBattle` calls `CaptureBtlIn` (the current frame is stored in a 1024 x 1024 `FrameTexture` at (50, 50) with two RLE crack
//! images drawn over it: one added, one subtracted), the next `CField::Polling` calls `StartBtlIn` and deletes the field, and `CBattle` calls
//! `StopBtlIn` when its own intro begins.  The shards are 3D slabs at depth 1 in camera space (`PixelTo3D`: the screen pixel at z = 1), drawn as GS
//! triangle strips (front face, back face 0.01 behind, the side ring) with `FST` texel coordinates, so the texture is affine like on the console.
//!
//! Phases (`BtlIn +0x1f4`, 30 Hz): 0 = 8 ticks colour +16 / alpha +8 (from 0x80 / 0x40: the flash), 10 = 8 ticks colour -16, 1 = every group gets a
//! random velocity (left half to the left) and spin (0..6 degrees per tick about x and y), 2 = falling (gravity +0.0003 per tick) until `StopBtlIn`,
//! 3 = 64 ticks alpha -2, or 4 = 20 ticks alpha -6.4 when the battle took longer than 80 ticks; `StopBtlIn` also fades the black backdrop
//! (alpha 0x80 -16 per tick).
//!
//! Port: [`BtlInFx::capture`] takes a window screenshot, composes the cracks on the CPU and spawns an orthographic 512 x 448 overlay camera above the UI
//! ([`BTLIN_ORDER`], render layer [`BTLIN_LAYER`]) that lives across the field -> battle scene switch; [`BtlInFx::stop`] is `StopBtlIn`.
//! The shard pattern (`DAT_0042f620` polygons / `DAT_0042f340` vertices / `DAT_004305b0` pattern origins) is read from the boot ELF and the crack
//! images (US FIELD.BIN 0x5778a8 / 0x560fb0 with their 16 grey CLUT entries in front) from FIELD.BIN, both found by content so either disc works.
//! `boss = true` plays the retail `BtlInBoss` instead ([`super::btlin_boss`]: the frame stays, two `boss_in` models play over it, the screen washes out
//! to white), when its models are found in FIELD.BIN.

use std::path::Path;
use std::sync::{Arc, Mutex};

use ::bevy::asset::RenderAssetUsages;
use ::bevy::camera::visibility::RenderLayers;
use ::bevy::camera::{ClearColorConfig, ScalingMode};
use ::bevy::image::{ImageAddressMode, ImageFilterMode, ImageSampler, ImageSamplerDescriptor};
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;
use ::bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};
use ::bevy::render::view::screenshot::{Screenshot, ScreenshotCaptured};

use crate::bevy::material::{Sh2Blend, Sh2ColorSpace, Sh2Material};

/// Render layer of the overlay (shared namespace: 1 UI, 6 cutscene, 29 gfx2d, 30 presenter).
pub const BTLIN_LAYER: usize = 28;
/// Camera order of the overlay: above the UI camera (100) -- the retail capture holds the whole frame, windows included.
pub const BTLIN_ORDER: isize = 120;

/// Crack image size (`FUN_003e9b20(..., 0x300, 0x2a0)`).
const CRACK_W: usize = 768;
const CRACK_H: usize = 672;
/// `SetViewMatrix(scrz = 1200, ax = 0.8, ay = 0.9333)`: pixels per camera-space unit at z = 1 (`1 / (BtlIn +0x1e8)`, `1 / (+0x1ec)`).
const FOCAL_X: f32 = 960.0;
const FOCAL_Y: f32 = 1120.0;

/// One shard of the pattern: its group (`0x7000` record index) and vertex pixel offsets from the pattern origin (strip order).
#[derive(Clone, Debug, PartialEq)]
pub struct PolDef {
    pub group: usize,
    pub verts: Vec<[i16; 2]>,
}

/// Static data of the transition.
#[derive(Clone, Debug)]
pub struct BtlInData {
    pub pols: Vec<PolDef>,
    /// `DAT_004305b0`: 8 x (base x, base y, step x, step y); the origin is `base + step * (rand % 40)`
    pub origins: [[i16; 4]; 8],
    /// added / subtracted crack images: one grey level per pixel (768 x 672)
    pub cracks: Option<[Vec<u8>; 2]>,
}

fn find(hay: &[u8], needle: &[u8]) -> Option<usize> {
    hay.windows(needle.len()).position(|w| w == needle)
}

fn le16(b: &[u8], o: usize) -> Option<u16> {
    Some(u16::from_le_bytes([*b.get(o)?, *b.get(o + 1)?]))
}

impl BtlInData {
    /// Parse the pattern out of a boot ELF (`SLUS_210.41` / `.44`; the JP ELF has the same tables).
    pub fn from_elf(elf: &[u8]) -> Option<BtlInData> {
        // first two records: (0x7000, 0x100) group marker, then the centre triangle (3, 135, 125, 126)
        let mut pat = vec![];
        for v in [0x7000u16, 0x100, 0, 0, 0, 3, 135, 125, 126, 0xffff] {
            pat.extend_from_slice(&v.to_le_bytes());
        }
        let pol_at = find(elf, &pat)?;
        let mut vpat = vec![];
        for v in [0i16, 0, 0, 0, 0, 117, 0, 208, 0, 290, 0, 365] {
            vpat.extend_from_slice(&v.to_le_bytes());
        }
        let vtx_at = find(elf, &vpat)?;
        let mut gpat = vec![];
        for v in [176i16, 144, -1, -1, 176, 224, -1, 1] {
            gpat.extend_from_slice(&v.to_le_bytes());
        }
        let grp_at = find(elf, &gpat)?;
        let vert = |i: u16| -> Option<[i16; 2]> {
            let o = vtx_at + i as usize * 4;
            Some([le16(elf, o)? as i16, le16(elf, o + 2)? as i16])
        };
        let mut pols = vec![];
        let mut group = 0usize;
        let mut at = pol_at;
        // CreatePolygon: `0x7000` sets the group index, `0x8000` closes the group (the next one is index + 1), `0xffff` ends the table
        loop {
            let rec: Vec<u16> = (0..5).map(|k| le16(elf, at + k * 2)).collect::<Option<_>>()?;
            at += 10;
            match rec[0] {
                0xffff => break,
                0x7000 => {
                    group = (rec[1] as usize) >> 8;
                    continue;
                }
                0x8000 => {
                    group += 1;
                    continue;
                }
                n @ 3..=4 => {
                    let verts = (0..n as usize).map(|k| vert(rec[1 + k])).collect::<Option<Vec<_>>>()?;
                    pols.push(PolDef { group, verts });
                }
                _ => return None,
            }
            if pols.len() > 1024 {
                return None;
            }
        }
        let mut origins = [[0i16; 4]; 8];
        for (k, o) in origins.iter_mut().enumerate() {
            for (j, v) in o.iter_mut().enumerate() {
                *v = le16(elf, grp_at + k * 8 + j * 2)? as i16;
            }
        }
        Some(BtlInData { pols, origins, cracks: None })
    }

    /// The two crack images out of FIELD.BIN: 16 grey `CLUT` entries (0x40 bytes) followed by `(count, byte)` RLE of the 4-bit image.
    pub fn cracks_from_field_bin(bin: &[u8]) -> Option<[Vec<u8>; 2]> {
        let clut_add = hex("0000000008080880101010801b1b1b8029292980383838804d4d4d805c5c5c806a6a6a807f7f7f8095959580a6a6a680bbbbbb80cecece80e3e3e380ffffff80");
        let clut_sub = hex("0000000006060680101010801f1f1f802a2a2a803535358042424280505050805e5e5e8070707080808080808e8e8e809e9e9e80b7b7b780cecece80ffffff80");
        let one = |clut: &[u8]| -> Option<Vec<u8>> {
            let at = find(bin, clut)?;
            let grey: Vec<u8> = (0..16).map(|k| clut[k * 4]).collect();
            let need = CRACK_W * CRACK_H / 2;
            let mut packed = Vec::with_capacity(need);
            let mut o = at + 0x40;
            while packed.len() < need {
                let n = *bin.get(o)? as usize;
                let v = *bin.get(o + 1)?;
                o += 2;
                packed.extend(std::iter::repeat_n(v, n));
            }
            packed.truncate(need);
            let mut px = Vec::with_capacity(CRACK_W * CRACK_H);
            for b in packed {
                // PSMT4: the low nibble is the left pixel
                px.push(grey[(b & 15) as usize]);
                px.push(grey[(b >> 4) as usize]);
            }
            Some(px)
        };
        Some([one(&clut_add)?, one(&clut_sub)?])
    }

    /// Load from a disc folder (boot ELF + FIELD.BIN); `None` when the ELF tables are missing.
    pub fn load(root: &Path) -> Option<BtlInData> {
        let elf = ["SLUS_210.41", "SLUS_210.44", "SLPS_255.11", "SLPS_255.12"].iter().find_map(|n| std::fs::read(root.join(n)).ok()).or_else(|| {
            // any boot ELF in the folder
            std::fs::read_dir(root).ok()?.flatten().find_map(|e| {
                let n = e.file_name().to_string_lossy().to_ascii_uppercase();
                if (n.starts_with("SLUS_") || n.starts_with("SLPS_") || n.starts_with("SLPM_")) && n.len() == 11 {
                    std::fs::read(e.path()).ok()
                } else {
                    None
                }
            })
        })?;
        let mut d = Self::from_elf(&elf)?;
        d.cracks = std::fs::read(root.join("FIELD.BIN")).ok().and_then(|b| Self::cracks_from_field_bin(&b));
        Some(d)
    }
}

fn hex(s: &str) -> Vec<u8> {
    (0..s.len() / 2).map(|i| u8::from_str_radix(&s[i * 2..i * 2 + 2], 16).unwrap_or(0)).collect()
}

/// newlib `rand()` stand-in (31-bit)
#[derive(Clone, Debug)]
struct Rand(u64);

impl Rand {
    fn next(&mut self) -> u32 {
        self.0 = self.0.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);
        ((self.0 >> 33) & 0x7fff_ffff) as u32
    }
}

#[derive(Clone, Debug)]
struct Shard {
    group: usize,
    /// camera-space vertex offsets from the centre (z = 0)
    local: Vec<Vec3>,
    /// texel position in pattern pixels (`pixel`, the `+ 50` of the frame texture removed)
    texel: Vec<[f32; 2]>,
    centre: Vec3,
    /// `BI_Pol +0x90`: a vertex went far off screen -- the GS kick is disabled for good
    culled: bool,
}

#[derive(Clone, Debug)]
struct Group {
    rot: Mat3,
    spin: Vec2,
    vel: Vec2,
    gravity: f32,
    centre_x: f32,
}

/// The running transition (all values in the retail units: colour 0..255 with 0x80 = 1, camera space at z = 1).
#[derive(Clone, Debug)]
pub struct BtlInSim {
    shards: Vec<Shard>,
    groups: Vec<Group>,
    /// `+0x1f0`: camera-space x of the pattern origin (groups left of it fly left)
    mid_x: f32,
    /// `BI_Pol +0x80` (shared by every shard): r, g, b, a
    color: Vec4,
    /// `+0x194`: backdrop alpha
    back_alpha: f32,
    /// `+0x1f4` / `+0x1f8`
    pub phase: u32,
    count: i32,
    /// `+0x1fc` / `+0x200`: 0 running, 1 `StopBtlIn` (backdrop fading), 2 backdrop gone
    env: u32,
    env_count: i32,
    rng: Rand,
    /// pattern origin offset in pixels (`origin - (256, 224)`)
    pub base: [f32; 2],
}

/// Camera-space point of a screen pixel at depth 1 (`BtlIn::PixelTo3D`).
fn pixel_to_3d(px: f32, py: f32) -> Vec3 {
    Vec3::new((px - 256.0) / FOCAL_X, (py - 224.0) / FOCAL_Y, 1.0)
}

/// Screen pixel of a camera-space point.
fn project(p: Vec3) -> [f32; 2] {
    let z = p.z.max(0.05);
    [256.0 + p.x / z * FOCAL_X, 224.0 + p.y / z * FOCAL_Y]
}

/// `sceVu0RotMatrix(m, m, (rx, ry, 0))`: m = Rz * Ry * Rx * m.
fn rot_xy(m: Mat3, rx: f32, ry: f32) -> Mat3 {
    Mat3::from_rotation_y(ry) * Mat3::from_rotation_x(rx) * m
}

pub const PHASE_DONE: u32 = 9999;

impl BtlInSim {
    /// `CreatePolygon`: choose the pattern origin and build the shards (`seed` stands in for the console's `rand()` state).
    pub fn new(data: &BtlInData, seed: u64) -> BtlInSim {
        let mut rng = Rand(seed ^ 0x9e37_79b9_7f4a_7c15);
        let g = (rng.next() & 7) as usize;
        let o = data.origins[g];
        let ox = o[0] as i32 + o[2] as i32 * (rng.next() % 40) as i32;
        let oy = o[1] as i32 + o[3] as i32 * (rng.next() % 40) as i32;
        let base = [(ox - 0x100) as f32, (oy - 0xe0) as f32];
        let ngroups = data.pols.iter().map(|p| p.group + 1).max().unwrap_or(0);
        let mut shards = Vec::with_capacity(data.pols.len());
        for p in &data.pols {
            let pts: Vec<Vec3> = p.verts.iter().map(|v| pixel_to_3d(base[0] + v[0] as f32, base[1] + v[1] as f32)).collect();
            // `BI_Pol::CalcCenter`: the mean of the first three vertices, z = 1
            let c = (pts[0] + pts[1] + pts[2]) / 3.0;
            let centre = Vec3::new(c.x, c.y, 1.0);
            let local = pts.iter().map(|q| Vec3::new(q.x - centre.x, q.y - centre.y, 0.0)).collect();
            let texel = p.verts.iter().map(|v| [base[0] + v[0] as f32, base[1] + v[1] as f32]).collect();
            shards.push(Shard { group: p.group, local, texel, centre, culled: false });
        }
        let mut groups = vec![Group { rot: Mat3::IDENTITY, spin: Vec2::ZERO, vel: Vec2::ZERO, gravity: 0.0, centre_x: 0.0 }; ngroups];
        for (gi, gr) in groups.iter_mut().enumerate() {
            let xs: Vec<f32> = shards.iter().filter(|s| s.group == gi).map(|s| s.centre.x).collect();
            if !xs.is_empty() {
                gr.centre_x = xs.iter().sum::<f32>() / xs.len() as f32;
            }
        }
        BtlInSim {
            shards,
            groups,
            mid_x: pixel_to_3d(ox as f32, oy as f32).x,
            color: Vec4::new(128.0, 128.0, 128.0, 64.0),
            back_alpha: 128.0,
            phase: 0,
            count: 0,
            env: 0,
            env_count: 0,
            rng,
            base,
        }
    }

    fn set_phase(&mut self, p: u32) {
        self.phase = p;
        self.count = 0;
    }

    /// `StopBtlIn`.
    pub fn stop(&mut self) {
        if self.env == 0 {
            self.env = 1;
            self.env_count = 0;
        }
    }

    pub fn stopped(&self) -> bool {
        self.env != 0
    }

    /// Everything faded: the object deletes itself.
    pub fn finished(&self) -> bool {
        self.env == 2 && self.phase == PHASE_DONE
    }

    /// One 30 Hz `Polling`.
    pub fn tick(&mut self) {
        // BI_PolGrp::CalcMatrix: accumulate the spin, move every shard of the group (x: velocity * 10 px, y: gravity + velocity * 10 px)
        for s in &mut self.shards {
            let g = &self.groups[s.group];
            s.centre.x += g.vel.x * 10.0 / FOCAL_X;
            s.centre.y += g.gravity + g.vel.y * 10.0 / FOCAL_Y;
        }
        for g in &mut self.groups {
            g.rot = rot_xy(g.rot, g.spin.x, g.spin.y);
        }
        match self.phase {
            0 | 10 => {
                self.count += 1;
                if self.count < 9 {
                    let d = if self.phase == 0 { 16.0 } else { -16.0 };
                    self.color.x += d;
                    self.color.y += d;
                    self.color.z += d;
                    if self.phase == 0 {
                        self.color.w += 8.0;
                    }
                } else {
                    let next = if self.phase == 0 { 10 } else { 1 };
                    self.set_phase(next);
                }
            }
            1 => {
                self.set_phase(2);
                for gi in 0..self.groups.len() {
                    let r = self.rng.next() as f32 / 4.294_967_3e9;
                    let vx = if self.groups[gi].centre_x <= self.mid_x { -r } else { r };
                    let vy = (self.rng.next() as f32 - 1_073_741_823.0) / 1.073_741_8e9;
                    let ax = ((self.rng.next() % 7) as f32).to_radians();
                    let ay = ((self.rng.next() % 7) as f32).to_radians();
                    let g = &mut self.groups[gi];
                    g.vel = Vec2::new(vx * 0.5, vy * 0.5);
                    g.spin = Vec2::new(ax, ay);
                }
            }
            2 => {
                self.count += 1;
                if self.env == 1 {
                    let waited = self.count;
                    self.set_phase(3);
                    if waited > 0x50 {
                        self.phase = 4;
                        self.count = 0x2c;
                    }
                } else {
                    for g in &mut self.groups {
                        g.gravity += 0.0003;
                    }
                }
            }
            3 | 4 => {
                self.count += 1;
                if self.count < 0x41 {
                    for g in &mut self.groups {
                        g.gravity += 0.0003;
                    }
                    self.color.w -= if self.phase == 3 { 2.0 } else { 6.4 };
                } else {
                    self.set_phase(PHASE_DONE);
                }
            }
            _ => {}
        }
        if self.env == 1 {
            self.env_count += 1;
            if self.env_count < 9 {
                self.back_alpha = (self.back_alpha - 16.0).max(0.0);
            } else {
                self.env = 2;
            }
        }
    }

    pub fn back_alpha(&self) -> f32 {
        self.back_alpha
    }

    /// The draw list of this tick in PS2 screen pixels: one triangle list of `(screen, texel, rgba 0..255)` (`BI_Pol::GetPacket` strips).
    pub fn triangles(&mut self) -> Vec<([f32; 2], [f32; 2], [f32; 4])> {
        let c = self.color.clamp(Vec4::ZERO, Vec4::splat(255.0)).to_array();
        let mut out = vec![];
        for s in &mut self.shards {
            let rot = self.groups[s.group].rot;
            let front: Vec<[f32; 2]> = s.local.iter().map(|l| project(rot * *l + s.centre)).collect();
            // the GS coordinates must stay within 1000..3000 (offset 2048 - 256 / 2048 - 224)
            if front.iter().any(|p| p[0] + 1792.0 < 1000.0 || p[0] + 1792.0 > 3000.0 || p[1] + 1824.0 < 1000.0 || p[1] + 1824.0 > 3000.0) {
                s.culled = true;
            }
            if s.culled {
                continue;
            }
            let back: Vec<[f32; 2]> = s.local.iter().map(|l| project(rot * (*l + Vec3::new(0.0, 0.0, 0.01)) + s.centre)).collect();
            let n = s.local.len();
            // strip: front, back, then the side ring (`DAT_004305f0` 0,1,2 / `DAT_00430600` 0,2,3,1) closed on vertex 0
            let ring: &[usize] = if n == 3 { &[0, 1, 2] } else { &[0, 2, 3, 1] };
            let mut strip: Vec<([f32; 2], usize)> = Vec::with_capacity(4 * n + 2);
            strip.extend((0..n).map(|k| (front[k], k)));
            strip.extend((0..n).map(|k| (back[k], k)));
            for &k in ring {
                strip.push((front[k], k));
                strip.push((back[k], k));
            }
            strip.push((front[0], 0));
            strip.push((back[0], 0));
            for w in strip.windows(3) {
                for (p, k) in w {
                    out.push((*p, s.texel[*k], c));
                }
            }
        }
        out
    }
}

/// Composite the crack images over a captured frame (`rgba`, `w x h` pixels covering the 512 x 448 screen): image 0 added, image 1 subtracted
/// (`ALPHA_1` 0x48 / 0x42), placed at `base - (128, 112)` in screen pixels.
pub fn apply_cracks(rgba: &mut [u8], w: usize, h: usize, cracks: &[Vec<u8>; 2], base: [f32; 2]) {
    let (x0, y0) = (base[0] - 128.0, base[1] - 112.0);
    for y in 0..h {
        let py = (y as f32 + 0.5) * 448.0 / h as f32 - y0;
        if py < 0.0 || py >= CRACK_H as f32 {
            continue;
        }
        let row = py as usize * CRACK_W;
        for x in 0..w {
            let px = (x as f32 + 0.5) * 512.0 / w as f32 - x0;
            if px < 0.0 || px >= CRACK_W as f32 {
                continue;
            }
            let k = row + px as usize;
            let (a, s) = (cracks[0][k] as i32, cracks[1][k] as i32);
            if a == 0 && s == 0 {
                continue;
            }
            let o = (y * w + x) * 4;
            for c in 0..3 {
                let v = (rgba[o + c] as i32 + a).min(255);
                rgba[o + c] = (v - s).max(0) as u8;
            }
        }
    }
}

/// `BtlIn` state of the app.
#[derive(Resource, Default)]
pub struct BtlInFx {
    data: Option<Option<Arc<BtlInData>>>,
    sim: Option<BtlInSim>,
    /// screenshot requested, waiting for the image
    waiting: Option<Arc<Mutex<Option<Image>>>>,
    stop_req: bool,
    acc: f32,
    texture: Option<Handle<Image>>,
    ents: Vec<Entity>,
    mesh: Option<Handle<Mesh>>,
    back: Option<Handle<Sh2Material>>,
    /// ticks spent in phase 2 without a `stop` (safety net)
    idle: u32,
    seed: u64,
    shot: u32,
    /// `BtlInBoss` models (loaded once; `None` inside = not on this disc)
    boss_data: Option<Option<Arc<super::btlin_boss::BossInData>>>,
    /// the pending capture is for `BtlInBoss`
    boss_req: bool,
    boss: Option<super::btlin_boss::BossInRun>,
    test_done: bool,
}

impl BtlInFx {
    /// `CaptureBtlIn` + `StartBtlIn`: grab the current frame and start the shatter.  Returns `false` when the disc data is missing (the caller
    /// keeps its own transition).
    pub fn capture(&mut self, root: &Path, boss: bool) -> bool {
        // development: `SH2_BTLIN_BOSS=1` plays the boss variant on every encounter
        let boss = boss || std::env::var_os("SH2_BTLIN_BOSS").is_some();
        if boss && self.boss_data.is_none() {
            let d = super::btlin_boss::BossInData::load(root).map(Arc::new);
            if d.is_none() {
                log::warn!("btlin: boss_in models not found in {}/FIELD.BIN (normal shatter)", root.display());
            }
            self.boss_data = Some(d);
        }
        self.boss_req = boss && self.boss_data.as_ref().and_then(|d| d.as_ref()).is_some() && std::env::var_os("SH2_BTLIN_NO_BOSS").is_none();
        self.boss = None;
        if self.data.is_none() {
            let d = BtlInData::load(root).map(Arc::new);
            if d.is_none() {
                log::warn!("btlin: shard pattern not found under {} (no boot ELF?)", root.display());
            }
            self.data = Some(d);
        }
        if self.data.as_ref().and_then(|d| d.as_ref()).is_none() {
            return false;
        }
        self.sim = None;
        self.stop_req = false;
        self.idle = 0;
        self.waiting = Some(Arc::new(Mutex::new(None)));
        self.seed = intro_seed();
        true
    }

    /// `StopBtlIn`: the battle is ready -- fade the backdrop and the shards.
    pub fn stop(&mut self) {
        self.stop_req = true;
        // the shatter takes the stop once it falls (phase 2, see `drive_btlin`)
        if let Some(s) = self.sim.as_mut().filter(|s| s.phase == 2) {
            s.stop();
        }
        if let Some(b) = &mut self.boss {
            b.sim.stop();
        }
    }

    /// The overlay is up (the frame is covered): the field may be torn down.
    pub fn covering(&self) -> bool {
        self.sim.is_some() || self.boss.is_some()
    }

    /// Capture pending or overlay running.
    pub fn active(&self) -> bool {
        self.waiting.is_some() || self.sim.is_some() || self.boss.is_some()
    }

    /// Waiting for [`Self::stop`] (shards falling over black).
    pub fn wants_stop(&self) -> bool {
        (self.sim.as_ref().map(|s| !s.stopped()).unwrap_or(false) || self.boss.as_ref().map(|b| !b.sim.stopped()).unwrap_or(false)) && !self.stop_req
    }

    /// The running `BtlInBoss` phase machine, if the boss variant plays.
    pub fn boss_sim(&self) -> Option<&super::btlin_boss::BossInSim> {
        self.boss.as_ref().map(|b| &b.sim)
    }

    pub fn sim(&self) -> Option<&BtlInSim> {
        self.sim.as_ref()
    }
}

/// Crop the 4:3 picture out of a window screenshot and turn it into raw display values.
fn screenshot_rgba(img: &Image) -> Option<(Vec<u8>, usize, usize)> {
    let (w, h) = (img.width() as usize, img.height() as usize);
    let data = img.data.as_ref()?;
    if w == 0 || h == 0 || data.len() < w * h * 4 {
        return None;
    }
    let bgra = matches!(img.texture_descriptor.format, TextureFormat::Bgra8Unorm | TextureFormat::Bgra8UnormSrgb);
    let (x0, y0, cw, ch) = crate::bevy::screen::present_rect(w as u32, h as u32, false);
    let (x0, y0, cw, ch) = (x0 as usize, y0 as usize, (cw as usize).min(w), (ch as usize).min(h));
    let mut out = vec![0u8; cw * ch * 4];
    for y in 0..ch {
        for x in 0..cw {
            let i = ((y0 + y) * w + x0 + x) * 4;
            let o = (y * cw + x) * 4;
            if bgra {
                out[o] = data[i + 2];
                out[o + 1] = data[i + 1];
                out[o + 2] = data[i];
            } else {
                out[o..o + 3].copy_from_slice(&data[i..i + 3]);
            }
            out[o + 3] = 255;
        }
    }
    Some((out, cw, ch))
}

#[allow(clippy::too_many_arguments)]
fn drive_btlin(
    mut fx: ResMut<BtlInFx>,
    mut commands: Commands,
    time: Res<Time>,
    color: Option<Res<Sh2ColorSpace>>,
    images: Option<ResMut<Assets<Image>>>,
    meshes: Option<ResMut<Assets<Mesh>>>,
    materials: Option<ResMut<Assets<Sh2Material>>>,
) {
    let (Some(mut images), Some(mut meshes), Some(mut materials)) = (images, meshes, materials) else { return };
    let fx: &mut BtlInFx = &mut fx;
    // development: `SH2_BTLIN_TEST=<seconds>` starts the transition over whatever is on screen after that long (`SH2_BTLIN_BOSS=1` for the boss variant;
    // the stop comes from the 10 s safety net)
    if let Some(at) = std::env::var("SH2_BTLIN_TEST").ok().and_then(|v| v.parse::<f32>().ok()) {
        if !fx.test_done && time.elapsed_secs() >= at {
            fx.test_done = true;
            if let Some(root) = std::env::var_os("SH2_US_DISC_DIR").or_else(|| std::env::var_os("SH2_DISC_DIR")) {
                fx.capture(Path::new(&root), false);
            }
        }
    }
    // 1. capture requested: spawn the screenshot once, then wait for the image
    if let Some(slot) = fx.waiting.clone() {
        // `waiting` + this clone: nobody else holds the slot yet -- spawn the screenshot (its observer keeps a third reference)
        if Arc::strong_count(&slot) == 2 {
            let s2 = slot.clone();
            commands.spawn(Screenshot::primary_window()).observe(move |ev: On<ScreenshotCaptured>| {
                if let Ok(mut g) = s2.lock() {
                    *g = Some(ev.image.clone());
                }
            });
        }
        let got = slot.lock().ok().and_then(|mut g| g.take());
        let Some(img) = got else { return };
        fx.waiting = None;
        let Some(data) = fx.data.clone().flatten() else { return };
        let Some((mut rgba, w, h)) = screenshot_rgba(&img) else {
            log::warn!("btlin: unusable screenshot");
            return;
        };
        if fx.boss_req {
            if let Some(bd) = fx.boss_data.clone().flatten() {
                let gamma = color.as_ref().map(|c| c.gamma).unwrap_or(true);
                let mut image = Image::new(
                    Extent3d { width: w as u32, height: h as u32, depth_or_array_layers: 1 },
                    TextureDimension::D2,
                    rgba,
                    if gamma { TextureFormat::Rgba8Unorm } else { TextureFormat::Rgba8UnormSrgb },
                    RenderAssetUsages::default(),
                );
                image.sampler = ImageSampler::Descriptor(ImageSamplerDescriptor {
                    mag_filter: ImageFilterMode::Linear,
                    min_filter: ImageFilterMode::Linear,
                    address_mode_u: ImageAddressMode::ClampToEdge,
                    address_mode_v: ImageAddressMode::ClampToEdge,
                    ..default()
                });
                let tex = images.add(image);
                let mut run = super::btlin_boss::BossInRun::spawn(&mut commands, &bd, tex, BTLIN_LAYER, BTLIN_ORDER, &mut meshes, &mut images, &mut materials);
                if fx.stop_req {
                    run.sim.stop();
                }
                fx.acc = 0.0;
                fx.idle = 0;
                log::info!("btlin: boss transition started (capture {w}x{h})");
                fx.boss = Some(run);
                return;
            }
        }
        let mut sim = BtlInSim::new(&data, fx.seed);
        if let Some(c) = &data.cracks {
            apply_cracks(&mut rgba, w, h, c, sim.base);
        }
        if fx.stop_req {
            sim.stop();
        }
        // 1 px black border: texels outside the captured frame read black
        let (tw, th) = (w + 2, h + 2);
        let mut tex = vec![0u8; tw * th * 4];
        for p in tex.chunks_exact_mut(4) {
            p[3] = 255;
        }
        for y in 0..h {
            let o = ((y + 1) * tw + 1) * 4;
            tex[o..o + w * 4].copy_from_slice(&rgba[y * w * 4..(y + 1) * w * 4]);
        }
        let gamma = color.map(|c| c.gamma).unwrap_or(true);
        let mut image = Image::new(
            Extent3d { width: tw as u32, height: th as u32, depth_or_array_layers: 1 },
            TextureDimension::D2,
            tex,
            if gamma { TextureFormat::Rgba8Unorm } else { TextureFormat::Rgba8UnormSrgb },
            RenderAssetUsages::default(),
        );
        image.sampler = ImageSampler::Descriptor(ImageSamplerDescriptor {
            mag_filter: ImageFilterMode::Linear,
            min_filter: ImageFilterMode::Linear,
            address_mode_u: ImageAddressMode::ClampToEdge,
            address_mode_v: ImageAddressMode::ClampToEdge,
            ..default()
        });
        let th_ = images.add(image);
        fx.texture = Some(th_.clone());
        let layer = RenderLayers::layer(BTLIN_LAYER);
        let cam = commands
            .spawn((
                Name::new("btlin_camera"),
                Camera3d::default(),
                Projection::Orthographic(OrthographicProjection {
                    scaling_mode: ScalingMode::Fixed { width: 512.0, height: 448.0 },
                    near: -1000.0,
                    far: 1000.0,
                    ..OrthographicProjection::default_3d()
                }),
                Camera { order: BTLIN_ORDER, clear_color: ClearColorConfig::None, ..default() },
                Transform::from_xyz(256.0, -224.0, 100.0),
                layer.clone(),
            ))
            .id();
        // black backdrop (`+0x28` sprite, colour 0 / alpha `+0x194`)
        let mut quad = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
        quad.insert_attribute(Mesh::ATTRIBUTE_POSITION, vec![[0.0f32, 0.0, -1.0], [512.0, 0.0, -1.0], [512.0, -448.0, -1.0], [0.0, -448.0, -1.0]]);
        quad.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, 0.0, 1.0]; 4]);
        quad.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32, 0.0]; 4]);
        quad.insert_attribute(Mesh::ATTRIBUTE_COLOR, vec![[0.0f32, 0.0, 0.0, 1.0]; 4]);
        quad.insert_indices(Indices::U32(vec![0, 1, 2, 0, 2, 3]));
        let back = materials.add(Sh2Material::textured(None).with_lit(false).with_fog(false).with_blend(Sh2Blend::Normal, Some(1.0)).with_ztest_off(true).with_sort_bias(-10.0));
        let be = commands.spawn((Mesh3d(meshes.add(quad)), MeshMaterial3d(back.clone()), layer.clone(), Transform::default(), ::bevy::camera::visibility::NoFrustumCulling)).id();
        let mesh = meshes.add(Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default()));
        let mat = materials.add(Sh2Material::textured(Some(th_)).with_lit(false).with_fog(false).with_blend(Sh2Blend::Normal, None).with_ztest_off(true));
        let se = commands.spawn((Mesh3d(mesh.clone()), MeshMaterial3d(mat), layer, Transform::default(), ::bevy::camera::visibility::NoFrustumCulling)).id();
        fx.ents = vec![cam, be, se];
        fx.mesh = Some(mesh);
        fx.back = Some(back);
        fx.acc = 0.0;
        log::info!("btlin: shatter started ({} shards, capture {w}x{h}, origin {:?})", sim.shards.len(), sim.base);
        fx.sim = Some(sim);
        update_mesh(fx, (w, h), &mut meshes, &mut materials);
        return;
    }
    if let Some(run) = fx.boss.as_mut() {
        fx.acc += time.delta_secs();
        let mut stepped = false;
        while fx.acc >= 1.0 / 30.0 {
            fx.acc -= 1.0 / 30.0;
            run.sim.tick();
            stepped = true;
            if run.sim.phase == super::btlin_boss::PHASE_WAIT && !run.sim.stopped() {
                fx.idle += 1;
                if fx.idle > 300 {
                    run.sim.stop();
                }
            }
        }
        if !stepped {
            return;
        }
        if run.sim.finished() {
            if let Some(run) = fx.boss.take() {
                run.despawn(&mut commands, &mut images);
            }
            log::info!("btlin: boss transition done");
            return;
        }
        run.sync(&mut commands, &mut meshes, &mut materials);
        if let Some(dir) = std::env::var_os("SH2_BTLIN_SHOTS").map(std::path::PathBuf::from) {
            fx.shot += 1;
            if fx.shot % 4 == 1 {
                let _ = std::fs::create_dir_all(&dir);
                let name = format!("btlinboss_{:03}_p{:x}.png", fx.shot, run.sim.phase);
                commands.spawn(Screenshot::primary_window()).observe(::bevy::render::view::screenshot::save_to_disk(dir.join(name)));
            }
        }
        return;
    }
    let Some(sim) = fx.sim.as_mut() else { return };
    fx.acc += time.delta_secs();
    let mut stepped = false;
    while fx.acc >= 1.0 / 30.0 {
        fx.acc -= 1.0 / 30.0;
        sim.tick();
        stepped = true;
        // a `StopBtlIn` that came before the fall (phase 2) is applied now: `Polling` only leaves phase 2 while `env == 1`, and `env` runs on to 2
        // after 9 ticks -- a stop during the flash left the shards falling forever (the port's battle loads in a few frames, retail's never did)
        if fx.stop_req && sim.phase == 2 && !sim.stopped() {
            sim.stop();
        }
        if sim.phase == 2 && !sim.stopped() {
            fx.idle += 1;
            // safety net: nobody called `stop` (no battle) -- give up after 10 s
            if fx.idle > 300 {
                sim.stop();
            }
        }
    }
    if !stepped {
        return;
    }
    if sim.finished() {
        for e in fx.ents.drain(..) {
            commands.entity(e).despawn();
        }
        fx.sim = None;
        fx.mesh = None;
        fx.back = None;
        if let Some(t) = fx.texture.take() {
            images.remove(&t);
        }
        log::info!("btlin: done");
        return;
    }
    // development: `SH2_BTLIN_SHOTS=<dir>` photographs the transition every 4 ticks
    if let Some(dir) = std::env::var_os("SH2_BTLIN_SHOTS").map(std::path::PathBuf::from) {
        fx.shot += 1;
        if fx.shot % 4 == 1 {
            let _ = std::fs::create_dir_all(&dir);
            let name = format!("btlin_{:03}_p{}.png", fx.shot, fx.sim.as_ref().map(|s| s.phase).unwrap_or(0));
            commands.spawn(Screenshot::primary_window()).observe(::bevy::render::view::screenshot::save_to_disk(dir.join(name)));
        }
    }
    let size = fx.texture.as_ref().and_then(|t| images.get(t)).map(|i| (i.width() as usize - 2, i.height() as usize - 2)).unwrap_or((512, 448));
    update_mesh(fx, size, &mut meshes, &mut materials);
}

fn update_mesh(fx: &mut BtlInFx, (w, h): (usize, usize), meshes: &mut Assets<Mesh>, materials: &mut Assets<Sh2Material>) {
    let Some(sim) = fx.sim.as_mut() else { return };
    let tris = sim.triangles();
    let (tw, th) = ((w + 2) as f32, (h + 2) as f32);
    let n = tris.len();
    let mut pos = Vec::with_capacity(n);
    let mut uv = Vec::with_capacity(n);
    let mut col = Vec::with_capacity(n);
    for (i, (p, t, c)) in tris.iter().enumerate() {
        // later triangles a hair nearer the camera (no depth test anyway: draw order = GS order)
        pos.push([p[0], -p[1], i as f32 * 1e-5]);
        uv.push([(1.0 + t[0] * w as f32 / 512.0) / tw, (1.0 + t[1] * h as f32 / 448.0) / th]);
        col.push([c[0] / 128.0, c[1] / 128.0, c[2] / 128.0, c[3] / 128.0]);
    }
    let back = sim.back_alpha();
    if let Some(mut m) = fx.mesh.as_ref().and_then(|h| meshes.get_mut(h)) {
        m.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
        m.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, 0.0, 1.0]; n]);
        m.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
        m.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
        m.insert_indices(Indices::U32((0..n as u32).collect()));
    }
    if let Some(mut m) = fx.back.as_ref().and_then(|h| materials.get_mut(h)) {
        let a = back / 128.0;
        if (m.params.y - a).abs() > 1e-4 {
            *m = m.clone().with_blend(Sh2Blend::Normal, Some(a));
        }
    }
}

/// Registers [`BtlInFx`] and its driver.
pub struct BtlInPlugin;

impl Plugin for BtlInPlugin {
    fn build(&self, app: &mut App) {
        if !app.is_plugin_added::<::bevy::app::HierarchyPropagatePlugin<RenderLayers>>() {
            app.add_plugins(::bevy::app::HierarchyPropagatePlugin::<RenderLayers>::new(PostUpdate));
        }
        app.init_resource::<BtlInFx>().add_systems(PostUpdate, drive_btlin);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn disc() -> Option<std::path::PathBuf> {
        std::env::var_os("SH2_US_DISC_DIR").map(std::path::PathBuf::from).filter(|p| p.join("SLUS_210.41").exists())
    }

    #[test]
    fn us_pattern_and_cracks() {
        let Some(root) = disc() else { return };
        let d = BtlInData::load(&root).expect("pattern");
        assert!(d.pols.len() > 150, "{} shards", d.pols.len());
        assert_eq!(d.pols[0].verts.len(), 3);
        assert_eq!(d.origins[0], [176, 144, -1, -1]);
        let c = d.cracks.as_ref().expect("cracks");
        assert_eq!(c[0].len(), CRACK_W * CRACK_H);
        assert!(c[0].iter().any(|&v| v > 0) && c[1].iter().any(|&v| v > 0));
        let mut sim = BtlInSim::new(&d, 7);
        // at rest the shards reproduce the screen: every front vertex projects onto its own texel
        let tris = sim.triangles();
        assert!(!tris.is_empty());
        for _ in 0..18 {
            sim.tick();
        }
        assert_eq!(sim.phase, 1);
        sim.tick();
        assert_eq!(sim.phase, 2);
        for _ in 0..30 {
            sim.tick();
        }
        sim.stop();
        let mut n = 0;
        while !sim.finished() && n < 200 {
            sim.tick();
            n += 1;
        }
        assert!(sim.finished(), "finished after {n} ticks");
    }

    #[test]
    fn colour_ramp_matches_retail() {
        let d = BtlInData { pols: vec![PolDef { group: 0, verts: vec![[0, 0], [100, 0], [0, 100]] }], origins: [[256, 224, 0, 0]; 8], cracks: None };
        let mut s = BtlInSim::new(&d, 1);
        for _ in 0..8 {
            s.tick();
        }
        assert_eq!(s.color, Vec4::new(256.0, 256.0, 256.0, 128.0));
        s.tick();
        assert_eq!(s.phase, 10);
        for _ in 0..9 {
            s.tick();
        }
        assert_eq!(s.phase, 1);
        assert_eq!(s.color, Vec4::new(128.0, 128.0, 128.0, 128.0));
        // the unmoved shard sits on its texels
        let t = s.triangles();
        let (p, tx, _) = t[0];
        assert!((p[0] - tx[0]).abs() < 1e-3 && (p[1] - tx[1]).abs() < 1e-3);
    }
}

/// Seed of the intro cracks.  Wall-clock based normally; under `SH2_FIXED_DT` (frame-deterministic runs, round 6 GPA) a fixed sequence
/// (`n`-th intro of the process), so two runs break the frame the same way.
fn intro_seed() -> u64 {
    static COUNT: std::sync::atomic::AtomicU64 = std::sync::atomic::AtomicU64::new(0);
    let n = COUNT.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
    if std::env::var_os("SH2_FIXED_DT").is_some() {
        return 0x5eed_0000_0001 + n.wrapping_mul(0x9e37_79b9_7f4a_7c15);
    }
    std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH).map(|d| d.as_nanos() as u64).unwrap_or(1)
}

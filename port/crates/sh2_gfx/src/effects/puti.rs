//! `Puti*` — the billboard primitive/particle framework from `PutiEffect.cpp`
//! (JP 0x0025ca60 .. 0x00260b70).
//!
//! * [`PutiObject`]  one particle quad.  `Calculate` = `UpdateFrame` then, if still alive:
//!   `CalcColor`, `CalcUv`, `CalcGravity`, `CalcSpeed`, `CalcPos`, `CalcVertex`
//!   (vtable slots +0x20,+0x10,+0x14,+0xc,+0x18,+0x1c).
//! * [`PutiPrim`]    owns a list of objects sorted by draw priority (flags bits 5..12), a delayed-add
//!   queue, optional lifetime (`TimeCall` virtual) and a texture.
//! * [`PutiManager`] singleton with 16 layers of prims; `Polling` rebuilds the billboard matrix
//!   (`ourBBoardMatrix` 0x004213c0 = inverse camera rotation, translation zeroed) and updates every
//!   prim.  `AddPrim(layer, prim)` also registers the prim in `World` ordering table `layer`.
//!
//! Rendering (`SetPacket`/`getPacket`, GS register words in `tagPutiEnv`) is not reproduced:
//! [`PutiObject::vertices`] yields the four world-space corners and [`PutiObject::uv`] the UVs.

use super::compat::{apply3, rot_matrix, Rand};

/// `tagPutiFlags` (u16 @ +0x14).
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct PutiFlags {
    /// bit0: **world-space quad** (when clear the quad is oriented by `rot` only; when set it is also
    /// transformed by the camera inverse = billboard).  Name kept from the code path in `CalcVertex`.
    pub billboard: bool,
    /// bit1: gravity enabled.
    pub gravity: bool,
    /// bit2: scroll UVs by `uv_scroll` each frame.
    pub uv_scroll: bool,
    /// bit3: UVs come from the prim's `PutiTexAnim` (`GetUVA(frame)`).
    pub uv_anim: bool,
    /// bits 5..12: draw priority (objects are kept sorted ascending).
    pub priority: u16,
}

impl PutiFlags {
    pub fn from_bits(b: u16) -> Self {
        PutiFlags {
            billboard: b & 1 != 0,
            gravity: b & 2 != 0,
            uv_scroll: b & 4 != 0,
            uv_anim: b & 8 != 0,
            priority: (b & 0x1fff) >> 5,
        }
    }
}

/// One particle (`PutiObject`, 0x1f0+ bytes).
#[derive(Clone, Debug)]
pub struct PutiObject {
    pub flags: PutiFlags,
    /// +0x90 frame counter
    pub frame: i32,
    /// +0x1e0 lifetime in frames, -1 = forever
    pub life: i32,
    /// +0xa0 speed integrator (offset accumulated from `speed`)
    pub offset: [f32; 3],
    /// +0xb0 current speed
    pub speed: [f32; 3],
    /// +0x180 speed acceleration, +0x190 speed limit (terminal value per axis, clamp when passed)
    pub accel: [f32; 3],
    pub speed_limit: [f32; 3],
    /// +0xe0 gravity offset, +0xf0 gravity speed, +0x1b0 gravity accel, +0x1c0 gravity limit
    pub grav_offset: [f32; 3],
    pub grav_speed: [f32; 3],
    pub grav_accel: [f32; 3],
    pub grav_limit: [f32; 3],
    /// +0x100 position
    pub pos: [f32; 3],
    /// +0x110 size, +0x120 scale, +0x130 Euler rotation
    pub size: [f32; 3],
    pub scale: [f32; 3],
    pub rot: [f32; 3],
    /// +0xc0..+0xdc four corners' UV (u,v), strip order 0..3
    pub uv: [[f32; 2]; 4],
    /// +0x1a0/+0x1a4 UV scroll per frame
    pub uv_scroll: [f32; 2],
    /// output corners (world space, +0x140..+0x180)
    pub verts: [[f32; 3]; 4],
}

impl PutiObject {
    /// `PutiObject::PutiObject` defaults: life 100 frames, scale (1,1,1), size 128.
    pub fn new() -> Self {
        PutiObject {
            flags: PutiFlags::default(),
            frame: 0,
            life: 100,
            offset: [0.0; 3],
            speed: [0.0; 3],
            accel: [0.0; 3],
            speed_limit: [0.0; 3],
            grav_offset: [0.0; 3],
            grav_speed: [0.0; 3],
            grav_accel: [0.0; 3],
            grav_limit: [0.0; 3],
            pos: [0.0; 3],
            size: [128.0; 3],
            scale: [1.0; 3],
            rot: [0.0; 3],
            uv: [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]],
            uv_scroll: [0.0; 2],
            verts: [[0.0; 3]; 4],
        }
    }

    /// `UpdateFrame` (0x0025d3b0): frame++, alive while `life == -1 || frame < life`.
    pub fn update_frame(&mut self) -> bool {
        self.frame += 1;
        self.life == -1 || self.frame < self.life
    }

    fn clamp_axis(v: &mut f32, limit: f32) {
        // identical to the decompiled condition: a limit of 0 means "no limit" only because
        // `0 <= limit && limit < v` is false for v <= 0 ... reproduced verbatim.
        if (0.0 <= limit && limit < *v) || (limit < 0.0 && *v < limit) {
            *v = limit;
        }
    }

    /// `CalcSpeed` (0x0025db20): `speed += accel`, clamp to `speed_limit`, `offset += speed`.
    pub fn calc_speed(&mut self) {
        for a in 0..3 {
            self.speed[a] += self.accel[a];
            Self::clamp_axis(&mut self.speed[a], self.speed_limit[a]);
            self.offset[a] += self.speed[a];
        }
    }

    /// `CalcGravity` (0x0025d910).
    pub fn calc_gravity(&mut self) {
        if !self.flags.gravity {
            return;
        }
        for a in 0..3 {
            self.grav_speed[a] += self.grav_accel[a];
            Self::clamp_axis(&mut self.grav_speed[a], self.grav_limit[a]);
            self.grav_offset[a] += self.grav_speed[a];
        }
    }

    /// `CalcPos` (0x0025dcf0): `pos += offset + grav_offset` (cumulative offsets are re-added each frame).
    pub fn calc_pos(&mut self) {
        for a in 0..3 {
            self.pos[a] += self.offset[a] + self.grav_offset[a];
        }
    }

    /// `CalcUv` (0x0025d500): scrolling (bit2) with wrap by 1.0 when both corners of an axis passed the
    /// edge, or texture-animation lookup (bit3, caller supplies `(a,b,c,d)` from `PutiTexAnim::GetUVA`).
    pub fn calc_uv(&mut self, tex_anim: Option<[f32; 4]>) {
        if self.flags.uv_scroll {
            for c in self.uv.iter_mut() {
                c[0] += self.uv_scroll[0];
                c[1] += self.uv_scroll[1];
            }
            if self.uv[0][0] > 1.0 && self.uv[3][0] > 1.0 {
                for c in self.uv.iter_mut() {
                    c[0] -= 1.0;
                }
            }
            if self.uv[0][1] > 1.0 && self.uv[3][1] > 1.0 {
                for c in self.uv.iter_mut() {
                    c[1] -= 1.0;
                }
            }
            if self.uv[0][0] < 0.0 && self.uv[3][0] < 0.0 {
                for c in self.uv.iter_mut() {
                    c[0] += 1.0;
                }
            }
            if self.uv[0][1] < 0.0 && self.uv[3][1] < 0.0 {
                for c in self.uv.iter_mut() {
                    c[1] += 1.0;
                }
            }
        }
        if self.flags.uv_anim {
            if let Some([a, b, c, d]) = tex_anim {
                // GetUVA outputs (a,b,c,d); corner i = (a|c, b|d) in triangle-strip order 0,1,2,3
                self.uv = [[a, b], [a, d], [c, b], [c, d]];
            }
        }
    }

    /// `CalcVertex` (0x0025dd70).  `bboard` = camera-inverse rotation (identity if `None`).
    pub fn calc_vertex(&mut self, bboard: Option<&[[f32; 3]; 3]>) {
        let hx = self.size[0] / 2.0 * self.scale[0];
        let hy = self.size[1] / 2.0 * self.scale[1];
        let hz = self.size[2] / 2.0 * self.scale[2];
        let local = [[-hx, -hy, hz], [-hx, hy, -hz], [hx, -hy, hz], [hx, hy, -hz]];
        let m = rot_matrix(self.rot);
        for (i, l) in local.iter().enumerate() {
            let mut v = apply3(&m, *l);
            if self.flags.billboard {
                if let Some(b) = bboard {
                    v = apply3(b, v);
                }
            }
            self.verts[i] = [v[0] + self.pos[0], v[1] + self.pos[1], v[2] + self.pos[2]];
        }
    }

    /// `Calculate` (0x0025d420).  Returns `true` while alive.
    pub fn calculate(&mut self, bboard: Option<&[[f32; 3]; 3]>, tex_anim: Option<[f32; 4]>) -> bool {
        if !self.update_frame() {
            return false;
        }
        // CalcColor is empty in the base class
        self.calc_uv(tex_anim);
        self.calc_gravity();
        self.calc_speed();
        self.calc_pos();
        self.calc_vertex(bboard);
        true
    }

    /// `GetPos(rx,ry,rz,&base)` (0x0025e130): random point in a box above `base`.
    pub fn random_pos(rng: &mut dyn Rand, range: [f32; 3], base: [f32; 3]) -> [f32; 3] {
        [base[0] + range[0] * rng.rand1(), base[1] + range[1] * rng.rand1(), base[2] + range[2] * rng.rand1()]
    }
}

impl Default for PutiObject {
    fn default() -> Self {
        Self::new()
    }
}

struct Delayed {
    at: i32,
    obj: PutiObject,
}

/// `PutiPrim` (VIF1Prim + object list).
pub struct PutiPrim {
    objects: Vec<PutiObject>,
    delayed: Vec<Delayed>,
    /// +0x38 delay counter (frames since creation)
    delay_clock: i32,
    /// +0x3c lifetime in frames (-1 none), +0x40 counter
    pub lifetime: i32,
    pub lifetime_counter: i32,
    /// +0x44 etc: object-less prims delete themselves when `lifetime` expires
    pub expired: bool,
    /// layer registered with `PutiManager`
    pub layer: Option<usize>,
}

impl PutiPrim {
    pub fn new() -> Self {
        PutiPrim { objects: Vec::new(), delayed: Vec::new(), delay_clock: 0, lifetime: -1, lifetime_counter: 0, expired: false, layer: None }
    }

    pub fn objects(&self) -> &[PutiObject] {
        &self.objects
    }

    /// `AddObject` (0x0025f0e0): insert keeping ascending draw-priority order (stable: after equals).
    pub fn add_object(&mut self, o: PutiObject) {
        let p = o.flags.priority;
        let pos = self.objects.iter().position(|e| p < e.flags.priority).unwrap_or(self.objects.len());
        self.objects.insert(pos, o);
    }

    /// `DelayPutiObject`: add `o` after `frames` updates.
    pub fn add_delayed(&mut self, o: PutiObject, frames: i32) {
        self.delayed.push(Delayed { at: frames, obj: o });
    }

    /// `PutiPrim::Update` (0x0025ef60).  `on_time` models the `TimeCall` virtual (called once when the
    /// lifetime counter reaches `lifetime`); `dead_ok` models `OnDelete` returning true.
    pub fn update(&mut self, bboard: Option<&[[f32; 3]; 3]>, mut on_time: impl FnMut(&mut PutiPrim)) {
        // DelayAdd: promote queued objects whose time has come
        self.delay_clock += 1;
        let mut ready = Vec::new();
        let clock = self.delay_clock;
        self.delayed.retain_mut(|d| {
            if clock < d.at {
                true
            } else {
                ready.push(std::mem::take(&mut d.obj));
                false
            }
        });
        for o in ready {
            self.add_object(o);
        }
        if self.lifetime != -1 {
            self.lifetime_counter += 1;
            if self.lifetime <= self.lifetime_counter {
                on_time(self);
                self.lifetime_counter = 0;
            }
        }
        self.objects.retain_mut(|o| o.calculate(bboard, None));
    }

    /// `PutiPrim::SetState(n)` forwards to every object's `OnChangeState` (no-op in the base class).
    pub fn set_state(&mut self, _state: i32) {}
}

impl Default for PutiPrim {
    fn default() -> Self {
        Self::new()
    }
}

/// `PutiManager` — 16 layers.
pub struct PutiManager {
    layers: [Vec<PutiPrim>; 16],
    /// +0x18 enabled
    pub enabled: bool,
    /// `ourBBoardMatrix`
    pub bboard: [[f32; 3]; 3],
}

impl PutiManager {
    pub fn new() -> Self {
        PutiManager { layers: Default::default(), enabled: true, bboard: [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]] }
    }

    /// `AddPrim(layer, prim)` — returns the prim's handle `(layer, index)`.
    pub fn add_prim(&mut self, layer: usize, mut p: PutiPrim) -> (usize, usize) {
        p.layer = Some(layer);
        self.layers[layer].push(p);
        (layer, self.layers[layer].len() - 1)
    }

    pub fn prim_mut(&mut self, h: (usize, usize)) -> Option<&mut PutiPrim> {
        self.layers.get_mut(h.0).and_then(|l| l.get_mut(h.1))
    }

    /// `DeleteAll` (0x0025f7a0).
    pub fn delete_all(&mut self) {
        for l in self.layers.iter_mut() {
            l.clear();
        }
    }

    /// `Polling` (0x0025f860): `camera_rot_inv` is the inverse of the camera rotation.
    pub fn polling(&mut self, camera_rot_inv: [[f32; 3]; 3]) {
        self.bboard = camera_rot_inv;
        if !self.enabled {
            return;
        }
        let bb = self.bboard;
        for l in self.layers.iter_mut() {
            for p in l.iter_mut() {
                p.update(Some(&bb), |_| {});
            }
        }
    }

    pub fn total_objects(&self) -> usize {
        self.layers.iter().flatten().map(|p| p.objects.len()).sum()
    }
}

impl Default for PutiManager {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn particle_dies_after_life() {
        let mut o = PutiObject::new();
        o.life = 3;
        assert!(o.calculate(None, None));
        assert!(o.calculate(None, None));
        assert!(!o.calculate(None, None));
    }

    #[test]
    fn speed_clamped_to_limit() {
        let mut o = PutiObject::new();
        o.accel = [1.0, 0.0, 0.0];
        o.speed_limit = [2.5, 0.0, 0.0];
        for _ in 0..5 {
            o.calc_speed();
        }
        assert_eq!(o.speed[0], 2.5);
        // offsets accumulate (1 + 2 + 2.5 + 2.5 + 2.5)
        assert!((o.offset[0] - 10.5).abs() < 1e-5);
    }

    #[test]
    fn gravity_only_when_flagged() {
        let mut o = PutiObject::new();
        o.grav_accel = [0.0, -1.0, 0.0];
        o.calc_gravity();
        assert_eq!(o.grav_speed[1], 0.0);
        o.flags.gravity = true;
        o.calc_gravity();
        assert_eq!(o.grav_speed[1], -1.0);
    }

    #[test]
    fn uv_scroll_wraps() {
        let mut o = PutiObject::new();
        o.flags.uv_scroll = true;
        o.uv_scroll = [0.6, 0.0];
        o.calc_uv(None);
        o.calc_uv(None);
        assert!(o.uv[0][0] < 1.0 && o.uv[0][0] > 0.0, "{:?}", o.uv);
    }

    #[test]
    fn manager_updates_and_reaps() {
        let mut m = PutiManager::new();
        let mut p = PutiPrim::new();
        let mut o = PutiObject::new();
        o.life = 2;
        p.add_object(o);
        m.add_prim(3, p);
        assert_eq!(m.total_objects(), 1);
        m.polling([[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]);
        m.polling([[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]);
        assert_eq!(m.total_objects(), 0);
    }

    #[test]
    fn priority_ordering() {
        let mut p = PutiPrim::new();
        let mut a = PutiObject::new();
        a.flags.priority = 5;
        let mut b = PutiObject::new();
        b.flags.priority = 2;
        p.add_object(a);
        p.add_object(b);
        assert_eq!(p.objects()[0].flags.priority, 2);
    }

    #[test]
    fn delayed_objects_appear() {
        let mut p = PutiPrim::new();
        p.add_delayed(PutiObject::new(), 2);
        p.update(None, |_| {});
        assert_eq!(p.objects().len(), 0);
        p.update(None, |_| {});
        assert_eq!(p.objects().len(), 1);
    }
}

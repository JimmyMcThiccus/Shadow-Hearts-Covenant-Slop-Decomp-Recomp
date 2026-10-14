//! `LightData` / `LightControl` — JP LightControl.cpp 0x00227d60..0x0022a900. See decomp/B/Light.c.
//!
//! Pool of 32 lights (slot 0 is the tree root in the original and never a real light). `light_matrix` ports
//! `LightControl::getLightMatrix` (0x00228fb0) *without* the sticky 5-frame cross-fade between slot assignments
//! (see [`LightControl::light_matrix`] notes) — the output is what the VU0 `sceVu0NormalLightMatrix` / `sceVu0LightColorMatrix`
//! pair consumed: up to 3 directions toward the light, 3 colours, and an ambient colour.

use glam::Vec3;

pub const MAX_LIGHTS: usize = 32;
pub const SLOTS: usize = 3;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
#[repr(u8)]
pub enum LightType {
    Ambient = 1,
    Directional = 2,
    Point = 3,
    Spot = 4,
}

/// `LightData::DeclineType`: attenuation exponent (1: 1/d, 2: 1/d^2, 3: 1/d^3).
pub type Decline = u8;

#[derive(Clone, Debug)]
pub struct LightData {
    pub handle: u16,
    /// flags bits0-1
    pub level: u8,
    /// flags bit2
    pub active: bool,
    /// flags bit3 (slot in use)
    pub allocated: bool,
    /// flags bit4 (`changeInterFlg`)
    pub interpolate: bool,
    pub decline: Decline,
    pub ltype: LightType,
    pub color: Vec3,
    pub pos: Vec3,
    /// Stored direction: for directional and spot lights this is the *negated* user direction (toward the light).
    pub dir: Vec3,
    pub decline_k: f32,
    /// cos(cone half angle) for spots (default 45 deg set by `CreateSpot`; `changeAngle(deg)` -> cos(deg*pi/180)).
    pub cos_angle: f32,
    pub drop_off: f32,
    pub shadow_flg: bool,
    pub strength: f32,
    // work values (per evaluation)
    work_dir: Vec3,
    work_intensity: f32,
    work_length: f32,
}

impl LightData {
    fn empty() -> Self {
        LightData {
            handle: 0,
            level: 0,
            active: false,
            allocated: false,
            interpolate: true,
            decline: 1,
            ltype: LightType::Ambient,
            color: Vec3::ZERO,
            pos: Vec3::ZERO,
            dir: Vec3::ZERO,
            decline_k: 1.0,
            cos_angle: 1.0,
            drop_off: 1.0,
            shadow_flg: false,
            strength: 1.0,
            work_dir: Vec3::ZERO,
            work_intensity: 0.0,
            work_length: 0.0,
        }
    }

    /// JP 0x00228120 `changeDeclineType` constant table.
    pub fn decline_k_for(ltype: LightType, decline: Decline) -> f32 {
        match (ltype, decline) {
            (LightType::Spot, 3) => f32::from_bits(0x437e7333),
            (LightType::Spot, 2) => f32::from_bits(0x41cb999a),
            (LightType::Spot, 1) => f32::from_bits(0x40228f5c),
            (LightType::Point, 3) => f32::from_bits(0x4334d47b),
            (LightType::Point, 2) => f32::from_bits(0x4190a3d7),
            (LightType::Point, 1) => f32::from_bits(0x3fe7ae14),
            (LightType::Directional, _) => 2.5,
            (LightType::Ambient, _) => 1.0,
            _ => 1.0,
        }
    }

    pub fn change_decline_type(&mut self, d: Decline) {
        self.decline = d;
        self.decline_k = Self::decline_k_for(self.ltype, d);
    }

    /// JP 0x00228270 `changeAngle(deg)` — ignored unless 0 < deg <= 180.
    pub fn change_angle(&mut self, deg: f32) {
        if deg > 0.0 && deg <= 180.0 {
            self.cos_angle = (deg / 180.0 * 3.141592).cos();
        }
    }

    /// JP 0x00228090 `changeDir` — directional and spot lights store the negated direction.
    pub fn change_dir(&mut self, d: Vec3) {
        self.dir = if matches!(self.ltype, LightType::Spot | LightType::Directional) { -d } else { d };
    }
}

/// Output of `getLightMatrix`.
#[derive(Clone, Debug, Default, PartialEq)]
pub struct LightMatrix {
    /// Directions *toward* each light (rows of the "normal light matrix").
    pub dirs: [Vec3; SLOTS],
    /// Colour of each light (columns of the "light colour matrix"), already attenuated.
    pub colors: [Vec3; SLOTS],
    pub ambient: Vec3,
    pub count: usize,
    /// Handle and world position of the light designated to cast the drop shadow (point/spot: its position;
    /// directional: `subject + dir*500`).
    pub shadow_light: Option<(u16, Vec3)>,
}

#[derive(Clone, Debug)]
pub struct LightControl {
    lights: Vec<LightData>,
    pub num_light: i32,
}

impl Default for LightControl {
    fn default() -> Self {
        LightControl { lights: (0..MAX_LIGHTS).map(|_| LightData::empty()).collect(), num_light: 0 }
    }
}

impl LightControl {
    pub fn new() -> Self {
        Self::default()
    }

    /// JP 0x0022a200 `referenceEmpty`: first free slot in 1..32 (slot 0 is the permanent root).
    fn reference_empty(&self) -> Option<usize> {
        (1..MAX_LIGHTS).find(|&i| !self.lights[i].allocated)
    }

    fn create(&mut self, ltype: LightType, color: Vec3, pos: Vec3, dir: Option<Vec3>) -> Option<u16> {
        let i = self.reference_empty()?;
        let mut l = LightData::empty();
        l.handle = i as u16;
        l.level = 1;
        l.active = true;
        l.allocated = true;
        l.color = color;
        l.pos = pos;
        l.ltype = ltype;
        l.strength = 1.0;
        match ltype {
            LightType::Directional => l.dir = -dir.unwrap(),
            LightType::Spot => {
                l.dir = -dir.unwrap();
                l.drop_off = 1.0;
                l.change_angle(45.0);
            }
            LightType::Point => l.drop_off = 1.0,
            LightType::Ambient => {}
        }
        l.change_decline_type(1);
        self.lights[i] = l;
        self.num_light += 1;
        Some(i as u16)
    }

    /// JP 0x00228450.
    pub fn create_ambient(&mut self, color: Vec3) -> Option<u16> {
        self.create(LightType::Ambient, color, Vec3::ZERO, None)
    }
    /// JP 0x00228550.
    pub fn create_directional(&mut self, dir: Vec3, color: Vec3) -> Option<u16> {
        self.create(LightType::Directional, color, Vec3::ZERO, Some(dir))
    }
    /// JP 0x002286a0.
    pub fn create_point(&mut self, pos: Vec3, color: Vec3) -> Option<u16> {
        self.create(LightType::Point, color, pos, None)
    }
    /// JP 0x002287c0.
    pub fn create_spot(&mut self, pos: Vec3, dir: Vec3, color: Vec3) -> Option<u16> {
        self.create(LightType::Spot, color, pos, Some(dir))
    }

    /// JP 0x0022a7b0 `release(handle)`.
    pub fn release(&mut self, h: i32) -> bool {
        if !(0..MAX_LIGHTS as i32).contains(&h) || !self.lights[h as usize].allocated {
            return false;
        }
        self.num_light -= 1;
        self.lights[h as usize].allocated = false;
        true
    }

    /// JP 0x0022a750 `searchHnd` — find slot by handle id (handles can be re-assigned with `changeID`).
    pub fn search_hnd(&self, handle: u16) -> Option<usize> {
        self.lights.iter().position(|l| l.allocated && l.handle == handle)
    }

    /// Access a live light by slot for the `change*` family (they all no-op when the slot is not allocated).
    pub fn get_mut(&mut self, slot: usize) -> Option<&mut LightData> {
        self.lights.get_mut(slot).filter(|l| l.allocated)
    }
    pub fn get(&self, slot: usize) -> Option<&LightData> {
        self.lights.get(slot).filter(|l| l.allocated)
    }

    /// JP 0x0022a650 `changeID(slot, newId)` — fails if another live light already uses `newId`.
    pub fn change_id(&mut self, slot: usize, new_id: u16) -> bool {
        if self.get(slot).is_none() {
            return false;
        }
        if self.lights.iter().enumerate().any(|(i, l)| l.allocated && i != slot && l.handle == new_id) {
            return false;
        }
        self.lights[slot].handle = new_id;
        true
    }

    /// Priority ordering of `LightData::install` (highest first): level desc, active before inactive,
    /// lightType ascending (ambient, directional, point, spot), then evaluated length descending.
    fn priority_order(&self) -> Vec<usize> {
        let mut v: Vec<usize> = (1..MAX_LIGHTS).filter(|&i| self.lights[i].allocated).collect();
        v.sort_by(|&a, &b| {
            let (la, lb) = (&self.lights[a], &self.lights[b]);
            lb.level
                .cmp(&la.level)
                .then(lb.active.cmp(&la.active))
                .then((la.ltype as u8).cmp(&(lb.ltype as u8)))
                .then(lb.work_length.partial_cmp(&la.work_length).unwrap_or(std::cmp::Ordering::Equal))
        });
        v
    }

    /// Port of `getLightMatrix(subjectPos, keepLight*, outShadowPos)` (JP 0x00228fb0), simplified:
    ///   * ambient lights sum into `ambient` (clamped to 1.0 per channel),
    ///   * up to 3 active directional lights fill the slots with colour `color * 0.4 * declineK(2.5)` (= colour),
    ///   * remaining slots take point/spot lights ranked by `k*|color|` where
    ///     `k = declineK * 5.53 / d^n` (point) or `declineK * 3.93 / d^n` and `pow(cos, dropOff)` inside the cone (spot);
    ///     slot colour = `min(color, color*k*strength)` per channel,
    ///   * the shadow light is the candidate with `shadow_flg` and the largest scaled colour.
    /// Not ported: the cross-fade (`keepLight` 5-step lerp) that hides slot reassignment; do it in the renderer if needed.
    pub fn light_matrix(&mut self, subject: Vec3) -> LightMatrix {
        let mut out = LightMatrix::default();
        // evaluate work values
        for i in 1..MAX_LIGHTS {
            let l = &mut self.lights[i];
            l.work_length = 0.0;
            if !l.allocated || !l.active {
                continue;
            }
            match l.ltype {
                LightType::Directional => {
                    l.work_dir = l.dir;
                    l.work_length = 10000.0;
                }
                LightType::Point | LightType::Spot => {
                    let v = l.pos - subject;
                    let d = v.length().max(1e-6);
                    let dir = v / d;
                    let n = l.decline as i32;
                    let (base, strength) = if l.ltype == LightType::Spot {
                        let cos = dir.dot(l.dir);
                        if cos > l.cos_angle {
                            (3.93, cos.powf(l.drop_off))
                        } else {
                            (0.0, l.strength)
                        }
                    } else {
                        (5.53, l.strength)
                    };
                    let k = if base == 0.0 { 0.0 } else { l.decline_k * base / d.powi(n) };
                    l.work_dir = dir;
                    l.work_intensity = k;
                    l.strength = strength;
                    l.work_length = k * l.color.length();
                }
                LightType::Ambient => {}
            }
        }
        let order = self.priority_order();
        let mut best_shadow: Option<(f32, usize, Vec3)> = None;
        for &i in &order {
            let l = &self.lights[i];
            if !l.active {
                continue;
            }
            match l.ltype {
                LightType::Ambient => out.ambient += l.color,
                LightType::Directional if out.count < SLOTS => {
                    let c = l.color * 0.4 * l.decline_k;
                    out.dirs[out.count] = l.dir;
                    out.colors[out.count] = c;
                    out.count += 1;
                    if l.shadow_flg && best_shadow.map(|b| c.length() > b.0).unwrap_or(true) {
                        best_shadow = Some((c.length(), i, subject + l.dir * 500.0));
                    }
                }
                _ => {}
            }
        }
        // point / spot by descending work_length
        let mut cand: Vec<usize> = order
            .iter()
            .copied()
            .filter(|&i| matches!(self.lights[i].ltype, LightType::Point | LightType::Spot) && self.lights[i].active && self.lights[i].work_length > 0.0)
            .collect();
        cand.sort_by(|&a, &b| self.lights[b].work_length.partial_cmp(&self.lights[a].work_length).unwrap());
        for i in cand {
            if out.count >= SLOTS {
                break;
            }
            let l = &self.lights[i];
            let scaled = l.color * l.work_intensity * l.strength;
            let c = l.color.min(scaled);
            out.dirs[out.count] = l.work_dir;
            out.colors[out.count] = c;
            out.count += 1;
            if l.shadow_flg && best_shadow.map(|b| scaled.length() > b.0).unwrap_or(true) {
                best_shadow = Some((scaled.length(), i, l.pos));
            }
        }
        out.ambient = out.ambient.min(Vec3::ONE);
        out.shadow_light = best_shadow.map(|(_, i, p)| (self.lights[i].handle, p));
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pool_and_decline_constants() {
        let mut lc = LightControl::new();
        let a = lc.create_ambient(Vec3::splat(0.3)).unwrap();
        assert_eq!(a, 1); // slot 0 is the root
        let d = lc.create_directional(Vec3::new(0.0, -1.0, 0.0), Vec3::ONE).unwrap();
        assert_eq!(lc.get(d as usize).unwrap().dir, Vec3::new(0.0, 1.0, 0.0)); // stored negated
        assert!((LightData::decline_k_for(LightType::Point, 2) - 18.08).abs() < 0.01);
        assert!((LightData::decline_k_for(LightType::Spot, 1) - 2.54).abs() < 0.01);
        assert_eq!(lc.num_light, 2);
        assert!(lc.release(a as i32));
        assert_eq!(lc.create_ambient(Vec3::ONE), Some(1)); // slot reused
        assert!(!lc.release(0));
    }

    #[test]
    fn matrix_ambient_and_directional() {
        let mut lc = LightControl::new();
        lc.create_ambient(Vec3::splat(0.7));
        lc.create_ambient(Vec3::splat(0.7));
        lc.create_directional(Vec3::new(0.0, 0.0, -1.0), Vec3::new(1.0, 0.5, 0.25));
        let m = lc.light_matrix(Vec3::ZERO);
        assert_eq!(m.ambient, Vec3::ONE); // clamped
        assert_eq!(m.count, 1);
        assert_eq!(m.dirs[0], Vec3::new(0.0, 0.0, 1.0));
        assert!((m.colors[0] - Vec3::new(1.0, 0.5, 0.25)).length() < 1e-5);
    }

    #[test]
    fn point_light_falls_off() {
        let mut lc = LightControl::new();
        lc.create_point(Vec3::new(0.0, 10.0, 0.0), Vec3::ONE);
        let near = lc.light_matrix(Vec3::new(0.0, 5.0, 0.0));
        let far = lc.light_matrix(Vec3::new(0.0, -50.0, 0.0));
        assert!(near.colors[0].x >= far.colors[0].x);
        assert!((near.dirs[0] - Vec3::Y).length() < 1e-5);
    }

    #[test]
    fn spot_outside_cone_is_dark() {
        let mut lc = LightControl::new();
        lc.create_spot(Vec3::new(0.0, 10.0, 0.0), Vec3::new(0.0, -1.0, 0.0), Vec3::ONE);
        let inside = lc.light_matrix(Vec3::new(0.0, 0.0, 0.0));
        let outside = lc.light_matrix(Vec3::new(100.0, 0.0, 0.0));
        assert_eq!(inside.count, 1);
        assert_eq!(outside.count, 0);
    }
}

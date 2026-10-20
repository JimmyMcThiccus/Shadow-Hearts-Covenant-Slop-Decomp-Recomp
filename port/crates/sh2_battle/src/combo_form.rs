//! `ComboForm` (BATTLE.BIN, JP 0x004f0c00 .. 0x004f5820, US 0x00511ad0 ..): the combo "link area" markers on the battle floor, plus
//! `CBattle::CheckComboMenber` (JP 0x00622f10), the proximity clustering that decides who can link with whom.
//!
//! * `CheckComboMenber`: every fighter that is present, alive and combo capable (enemies always, party members with SP) starts with a mask
//!   holding its own bit; two fighters of the same side whose feet are closer than `r1 + r2 + 10` (`BtlChr+0x3b0` radii) link, and the links
//!   are closed transitively (a chain of neighbours is one group).  The result is `BtlChr+0x57e`.
//! * `ComboForm::ComboAreaReset` copies each mask (own bit removed) and drives the per-fighter state: 0 off, 1 fading in (+ SE `0x2001004`),
//!   2 shown, 3 fading out; `Polling` ramps the alpha by 640 / s up to 128 and turns the ring (`+0xd4`, -pi / s) and pulses the second /
//!   third layer by the group size (`(n - 1) * 0.25 - 0.25 * (0.5 + sin(phase) / 2)`, none for a single partner).
//! * `MakePacket`: under each marked fighter three textured fans on the floor (y = -0.2 in PS2 space): the glow disc (BTL_000 JRCTex JP 44 /
//!   US 26, radius `r + 7.5`, centre cyan 0x23,0x80,0x80 / rim blue 0x00,0x0f,0x55, enemies orange 0x80,0x50,0x28 / red 0x5a,0x05,0x05, alpha =
//!   the fade) and two rings (JP 45 / 46 = US 27 / 28, radius `r + 5`, turning; blue / cyan, alpha = fade x pulse).  16 rim points 24 degrees apart (0..360).
//!
//! The logic here is pure (positions in, geometry out); [`ComboFormPlugin`] reads the battle and draws the three meshes.

use bevy::prelude::*;
use std::f32::consts::TAU;

/// the 12 `BtlChr` slots of `CBattle`
pub const SLOTS: usize = 12;
/// 16 segments of 24 degrees (`0.41887903`)
const STEP: f32 = 0.41887903;

/// One fighter as `ComboForm` / `CheckComboMenber` see it.
#[derive(Clone, Copy, Debug, Default)]
pub struct CfChr {
    /// slot is in use and the fighter is alive
    pub present: bool,
    pub enemy: bool,
    /// can take part in a combo (an enemy, or a party member with SP; `BtlChr` state 8 / 9 / 10 in the original also counts)
    pub eligible: bool,
    /// away from its place (run-up / attack): the ring is faded out
    pub moving: bool,
    /// feet, horizontal plane (x, z)
    pub pos: [f32; 2],
    /// `BtlChr+0x3b0`
    pub radius: f32,
}

/// `CBattle::CheckComboMenber`: the linkable-partner mask of every slot (own bit included, the original's `+0x57e`).
pub fn check_combo_members(chrs: &[CfChr; SLOTS]) -> [u16; SLOTS] {
    let mut mask = [0u16; SLOTS];
    let cand: Vec<usize> = (0..SLOTS).filter(|&i| chrs[i].present && chrs[i].eligible && !chrs[i].moving).collect();
    for &i in &cand {
        mask[i] = 1 << i;
    }
    for &a in &cand {
        for &b in &cand {
            if a != b && chrs[a].enemy == chrs[b].enemy {
                let d = ((chrs[a].pos[0] - chrs[b].pos[0]).powi(2) + (chrs[a].pos[1] - chrs[b].pos[1]).powi(2)).sqrt();
                if d < chrs[a].radius + chrs[b].radius + 10.0 {
                    mask[a] |= 1 << b;
                    mask[b] |= 1 << a;
                }
            }
        }
    }
    // transitive closure
    let mut changed = true;
    while changed {
        changed = false;
        for &a in &cand {
            for &b in &cand {
                if a != b && chrs[a].enemy == chrs[b].enemy && mask[a] & (1 << b) != 0 {
                    let (ma, mb) = (mask[a], mask[b]);
                    mask[a] |= mb;
                    mask[b] |= ma;
                    changed |= mask[a] != ma || mask[b] != mb;
                }
            }
        }
    }
    mask
}

/// The per-fighter marker state (`ComboForm +0x50 / +0x5c / +0x74 / +0x78 / +0xd4`).
#[derive(Clone, Debug)]
pub struct ComboForm {
    /// 0 off, 1 in, 2 shown, 3 out
    pub state: [u8; SLOTS],
    /// linked partners (own bit removed)
    pub partners: [u16; SLOTS],
    /// fade, 0..128
    pub alpha: [f32; SLOTS],
    /// ring layer strength (0 for a single partner)
    pub intensity: [f32; SLOTS],
    /// ring turn angle, -pi..pi
    pub spin: [f32; SLOTS],
    /// pulse phase (`+0x3c`)
    phase: f32,
}

/// Ring layers a [`ComboForm`] draws for one fighter.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Ring {
    pub slot: usize,
    pub enemy: bool,
    pub centre: [f32; 2],
    /// `r + 7.5` (glow disc) and `r + 5` (rings)
    pub r_disc: f32,
    pub r_ring: f32,
    pub spin: f32,
    /// glow alpha 0..1 and ring alpha 0..1 (fade x intensity)
    pub a_disc: f32,
    pub a_ring: f32,
}

impl ComboForm {
    /// `ComboForm::__ct`: each ring starts at a random angle.
    pub fn new(mut rand: impl FnMut() -> f32) -> Self {
        let mut spin = [0.0; SLOTS];
        for s in &mut spin {
            *s = rand() * TAU - TAU / 2.0;
        }
        ComboForm { state: [0; SLOTS], partners: [0; SLOTS], alpha: [0.0; SLOTS], intensity: [0.0; SLOTS], spin, phase: 0.0 }
    }

    /// `ComboForm::ComboAreaReset` with the masks of [`check_combo_members`]; returns the slots whose ring just appeared (the SE `0x2001004`).
    pub fn area_reset(&mut self, chrs: &[CfChr; SLOTS], masks: &[u16; SLOTS]) -> Vec<usize> {
        let mut appeared = Vec::new();
        for i in 0..SLOTS {
            if !chrs[i].present || !chrs[i].eligible || chrs[i].moving {
                self.state[i] = 0;
                self.alpha[i] = 0.0;
                self.partners[i] = 0;
                continue;
            }
            self.partners[i] = masks[i] & !(1 << i);
            if self.partners[i] == 0 {
                match self.state[i] {
                    1 => self.state[i] = 3,
                    2 => {
                        self.state[i] = 3;
                        self.alpha[i] = 128.0;
                    }
                    _ => {}
                }
            } else if self.state[i] == 0 {
                self.state[i] = 1;
                self.alpha[i] = 0.0;
                appeared.push(i);
            } else if self.state[i] == 3 {
                self.state[i] = 1;
                appeared.push(i);
            }
        }
        appeared
    }

    /// `ComboForm::Polling`: `dt` seconds (0 while paused).
    pub fn polling(&mut self, dt: f32, chrs: &[CfChr; SLOTS]) {
        self.phase += dt * TAU;
        if self.phase >= PI32 {
            self.phase -= TAU;
        }
        for i in 0..SLOTS {
            self.spin[i] -= dt * PI32;
            if self.spin[i] < -PI32 {
                self.spin[i] += TAU;
            }
            if !chrs[i].present || !chrs[i].eligible || chrs[i].moving {
                self.state[i] = 0;
                self.alpha[i] = 0.0;
                self.partners[i] = 0;
                continue;
            }
            let n = self.partners[i].count_ones() as f32;
            let mut f = 0.0;
            if n != 0.0 {
                f = (n - 1.0) * 0.25;
                if n > 1.0 {
                    f -= 0.25 * (0.5 + self.phase.sin() / 2.0);
                }
            }
            self.intensity[i] = f;
            match self.state[i] {
                3 => {
                    self.alpha[i] -= dt * 640.0;
                    if self.alpha[i] <= 0.0 {
                        self.state[i] = 0;
                        self.alpha[i] = 0.0;
                    }
                }
                2 => self.alpha[i] = 128.0,
                1 => {
                    self.alpha[i] += dt * 640.0;
                    if self.alpha[i] >= 128.0 {
                        self.state[i] = 2;
                        self.alpha[i] = 128.0;
                    }
                }
                _ => {}
            }
        }
    }

    /// The rings to draw now.
    pub fn rings(&self, chrs: &[CfChr; SLOTS]) -> Vec<Ring> {
        (0..SLOTS)
            .filter(|&i| self.state[i] != 0 && chrs[i].present)
            .map(|i| Ring {
                slot: i,
                enemy: chrs[i].enemy,
                centre: chrs[i].pos,
                r_disc: chrs[i].radius + 7.5,
                r_ring: chrs[i].radius + 5.0,
                spin: self.spin[i],
                a_disc: (self.alpha[i] / 128.0).clamp(0.0, 1.0),
                a_ring: ((self.alpha[i] * self.intensity[i]).floor() / 128.0).clamp(0.0, 1.0),
            })
            .collect()
    }
}

const PI32: f32 = 3.1415927;

/// Vertex colours (RGB 0..1) of a layer: `(centre, rim)`.
pub fn layer_colours(enemy: bool, layer: usize) -> ([f32; 3], [f32; 3]) {
    let c = |r: u8, g: u8, b: u8| [r as f32 / 128.0, g as f32 / 128.0, b as f32 / 128.0];
    match (layer, enemy) {
        (0, false) => (c(0x23, 0x80, 0x80), c(0x00, 0x0f, 0x55)),
        (0, true) => (c(0x80, 0x50, 0x28), c(0x5a, 0x05, 0x05)),
        (1, false) => (c(0x00, 0x0f, 0x55), c(0x00, 0x0f, 0x55)),
        (1, true) => (c(0x5a, 0x05, 0x05), c(0x5a, 0x05, 0x05)),
        (_, false) => (c(0x23, 0x80, 0x80), c(0x23, 0x80, 0x80)),
        (_, true) => (c(0x80, 0x50, 0x28), c(0x80, 0x50, 0x28)),
    }
}

/// Triangles of one fan layer on the floor plane (Bevy space, y = `y`): positions, colours (RGBA) and uvs.
/// `layer` 0 = glow disc (radius `r_disc`, still), 1 / 2 = rings (radius `r_ring`, turned by `spin`).
pub fn fan(r: &Ring, layer: usize, y: f32) -> (Vec<[f32; 3]>, Vec<[f32; 4]>, Vec<[f32; 2]>) {
    let (radius, spin, a) = if layer == 0 { (r.r_disc, 0.0, r.a_disc) } else { (r.r_ring, r.spin, r.a_ring) };
    let (cc, cr) = layer_colours(r.enemy, layer);
    let pt = |k: usize| -> ([f32; 3], [f32; 2]) {
        let ang = k as f32 * STEP;
        // PS2: (x, z) = (-R cos, R sin); the ring layers are turned about Y
        let (x, z) = (-radius * ang.cos(), radius * ang.sin());
        let (s, c) = spin.sin_cos();
        let (x, z) = if layer == 0 { (x, z) } else { (x * c + z * s, -x * s + z * c) };
        ([r.centre[0] + x, y, r.centre[1] + z], [ang.cos() / 2.0 + 0.5, -ang.sin() / 2.0 + 0.5])
    };
    let mut pos = Vec::new();
    let mut col = Vec::new();
    let mut uv = Vec::new();
    let mut push = |p: [f32; 3], u: [f32; 2], c: [f32; 3]| {
        pos.push(p);
        uv.push(u);
        col.push([c[0], c[1], c[2], a]);
    };
    // 16 rim points from 0 to 360 degrees: 15 triangles
    for k in 0..15 {
        let (p0, u0) = pt(k);
        let (p1, u1) = pt(k + 1);
        push([r.centre[0], y, r.centre[1]], [0.5, 0.5], cc);
        push(p0, u0, cr);
        push(p1, u1, cr);
    }
    (pos, col, uv)
}

// ------------------------------------------------------------------------------------------------------------------
// Bevy side
// ------------------------------------------------------------------------------------------------------------------

/// Drawing state: the logic, the three layer materials (BTL_000 JRCTex JP 44 / 45 / 46 = US 26 / 27 / 28) and the dynamic meshes.
#[derive(Resource, Default)]
pub struct ComboFormDraw {
    cf: Option<ComboForm>,
    mats: Option<[Option<Handle<sh2_gfx::bevy::Sh2Material>>; 3]>,
    meshes: [Option<(Entity, Handle<Mesh>)>; 3],
    seed: u32,
}

/// `ComboForm::Polling` + `MakePacket` for the running battle: fighters -> [`CfChr`], masks, state, three fan meshes on the floor.
/// `SH2_COMBO_FORM=off` disables it.
#[allow(clippy::too_many_arguments)]
pub fn drive_combo_form(
    mut commands: Commands,
    rt: Option<Res<crate::plugin::BattleRuntime>>,
    disc: Option<Res<sh2_gfx::bevy::Sh2Disc>>,
    models: Query<&crate::models::BattleModel>,
    mut st: ResMut<ComboFormDraw>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<sh2_gfx::bevy::Sh2Material>>,
    mut images: ResMut<Assets<Image>>,
    time: Res<Time>,
) {
    use sh2_gfx::bevy::{Sh2Blend, Sh2Material};
    let (Some(rt), Some(disc)) = (rt, disc) else { return };
    if std::env::var_os("SH2_COMBO_FORM").map_or(false, |v| v == "off") {
        return;
    }
    let st = &mut *st;
    if st.mats.is_none() {
        let ks = if sh2_core::boot::is_retail() { [26usize, 27, 28] } else { [44, 45, 46] };
        let bin = disc.read("BTLDATA/BTL_000.BIN").unwrap_or_default();
        let secs = crate::stage::sections(&bin);
        st.mats = Some(ks.map(|k| {
            let (tag, sec) = secs.get(k)?;
            if tag != "tex" {
                return None;
            }
            let i = sh2_gfx::texture::decode_jrc(sec, 0, 0).ok()?;
            let img = images.add(sh2_gfx::bevy::image::rgba_image(i.width, i.height, i.pixels, sh2_gfx::bevy::TexFilter::Linear));
            Some(mats.add(Sh2Material::textured(Some(img)).with_lit(false).with_fog(false).with_blend(Sh2Blend::Normal, None).with_sort_bias(-0.5)))
        }));
    }
    let mut chrs = [CfChr::default(); SLOTS];
    for m in models.iter() {
        let i = m.chr;
        let Some(Some(f)) = rt.battle.fighters.get(i) else { continue };
        if i >= SLOTS {
            continue;
        }
        let pos = rt.positions.get(i).copied().unwrap_or(m.pos);
        chrs[i] = CfChr {
            // the win / lose / escape sequences destroy the form (`ComboForm::Destruct`, battle_ui_u2): no markers outside the running battle
            present: f.alive() && matches!(rt.stage, crate::plugin::Stage::Running),
            enemy: f.is_enemy,
            // a party member needs SP to link (`BtlChr+0x12c > 0`); enemies always can
            eligible: f.is_enemy || f.sp > 0,
            moving: (m.pos - m.home).length() > 5.0,
            // PS2 space: z is mirrored
            pos: [pos.x, -pos.z],
            radius: m.radius * dev_radius_scale(),
        };
    }
    let seed = &mut st.seed;
    let cf = st.cf.get_or_insert_with(|| {
        ComboForm::new(|| {
            *seed = seed.wrapping_mul(1664525).wrapping_add(1013904223);
            (*seed >> 8) as f32 / (1u32 << 24) as f32
        })
    });
    let masks = check_combo_members(&chrs);
    for _ in cf.area_reset(&chrs, &masks) {
        sh2_audio::post(sh2_audio::AudioRequest::PlayGlobalSe { id: 0x2001004 });
    }
    cf.polling(time.delta_secs().min(0.1), &chrs);
    let rings = cf.rings(&chrs);
    for layer in 0..3 {
        let Some(Some(mat)) = st.mats.as_ref().map(|m| m[layer].clone()) else { continue };
        let (mut pos, mut col, mut uv) = (Vec::new(), Vec::new(), Vec::new());
        for r in &rings {
            let (p, c, u) = fan(r, layer, -0.2);
            if c.first().map_or(true, |c| c[3] <= 0.0) {
                continue;
            }
            pos.extend(p);
            col.extend(c);
            uv.extend(u);
        }
        if pos.is_empty() {
            pos = vec![[0.0; 3]; 3];
            col = vec![[0.0; 4]; 3];
            uv = vec![[0.0; 2]; 3];
        }
        let mut mesh = Mesh::new(bevy::mesh::PrimitiveTopology::TriangleList, bevy::asset::RenderAssetUsages::default());
        mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
        mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
        mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
        match &st.meshes[layer] {
            Some((e, h)) if commands.get_entity(*e).is_ok() => {
                if let Some(mut mm) = meshes.get_mut(h) {
                    *mm = mesh;
                }
            }
            _ => {
                let h = meshes.add(mesh);
                let e = commands
                    .spawn((
                        Name::new("combo_form"),
                        Mesh3d(h.clone()),
                        MeshMaterial3d(mat),
                        Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)),
                        Visibility::default(),
                        bevy::camera::visibility::NoFrustumCulling,
                        DespawnOnExit(sh2_core::game::Scene::Battle),
                    ))
                    .id();
                st.meshes[layer] = Some((e, h));
            }
        }
    }
}

/// Dev aid `SH2_COMBO_FORM_SCALE=<x>`: scales every fighter's radius so far-apart fighters link (the rings are otherwise rare on the dev battles).
fn dev_radius_scale() -> f32 {
    std::env::var("SH2_COMBO_FORM_SCALE").ok().and_then(|v| v.parse().ok()).unwrap_or(1.0)
}

/// Forget the markers between battles.
pub fn reset_combo_form(mut st: ResMut<ComboFormDraw>) {
    *st = ComboFormDraw::default();
}

#[cfg(test)]
mod tests {
    use super::*;

    fn chr(x: f32, z: f32, enemy: bool) -> CfChr {
        CfChr { present: true, enemy, eligible: true, moving: false, pos: [x, z], radius: 12.0 }
    }

    #[test]
    fn neighbours_link_and_chains_close_transitively() {
        let mut c = [CfChr::default(); SLOTS];
        c[0] = chr(0.0, 0.0, false);
        c[1] = chr(30.0, 0.0, false); // 30 < 12 + 12 + 10
        c[2] = chr(60.0, 0.0, false); // linked to 1 only, but joins 0 through the closure
        c[3] = chr(200.0, 0.0, false);
        let m = check_combo_members(&c);
        assert_eq!(m[0], 0b0111);
        assert_eq!(m[2], 0b0111);
        assert_eq!(m[3], 0b1000);
    }

    #[test]
    fn sides_never_link_and_ineligible_fighters_are_ignored() {
        let mut c = [CfChr::default(); SLOTS];
        c[0] = chr(0.0, 0.0, false);
        c[1] = chr(10.0, 0.0, true);
        c[2] = CfChr { eligible: false, ..chr(5.0, 0.0, false) };
        let m = check_combo_members(&c);
        assert_eq!(m[0], 1);
        assert_eq!(m[1], 2);
        assert_eq!(m[2], 0);
    }

    #[test]
    fn ring_fades_in_to_128_pulses_with_group_size_and_fades_out() {
        let mut c = [CfChr::default(); SLOTS];
        c[0] = chr(0.0, 0.0, false);
        c[1] = chr(20.0, 0.0, false);
        let mut f = ComboForm::new(|| 0.5);
        let m = check_combo_members(&c);
        assert_eq!(f.area_reset(&c, &m), vec![0, 1]);
        for _ in 0..30 {
            f.polling(1.0 / 60.0, &c);
        }
        assert_eq!(f.state[0], 2);
        assert_eq!(f.alpha[0], 128.0);
        // one partner: the glow only
        assert_eq!(f.intensity[0], 0.0);
        let r = f.rings(&c);
        assert_eq!(r.len(), 2);
        assert_eq!(r[0].a_disc, 1.0);
        assert_eq!(r[0].a_ring, 0.0);
        // the partner leaves: both fade out
        c[1].pos = [500.0, 0.0];
        let m = check_combo_members(&c);
        assert!(f.area_reset(&c, &m).is_empty());
        assert_eq!(f.state[0], 3);
        for _ in 0..30 {
            f.polling(1.0 / 60.0, &c);
        }
        assert_eq!(f.state[0], 0);
        assert!(f.rings(&c).is_empty());
    }

    #[test]
    fn fan_has_15_triangles_closing_the_circle() {
        let r = Ring { slot: 0, enemy: false, centre: [10.0, 20.0], r_disc: 19.5, r_ring: 17.0, spin: 0.7, a_disc: 1.0, a_ring: 0.5 };
        for layer in 0..3 {
            let (p, c, u) = fan(&r, layer, 0.2);
            assert_eq!((p.len(), c.len(), u.len()), (45, 45, 45));
            // the last rim point is the first one (360 degrees)
            let first = p[1];
            let last = p[44];
            assert!((first[0] - last[0]).abs() < 1e-3 && (first[2] - last[2]).abs() < 1e-3);
        }
    }
}

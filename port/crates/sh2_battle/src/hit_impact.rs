//! `HitImpact` (JP 0x0051dca0.., US 0x00543400..; `decomp/H/HitImpact.c`): the shock wave of a combo finisher.
//!
//! * Created by `PAtkHitSet` (`CBattle.c` 47789: `CBtlPAfter2::SetHitImpact(8.0, atk, pos)`) for the **last hit of a swing** (`a7 + 1 == a5`) of a Link combo
//!   member (`nComboCnt != 0`) when that hit connected (`bVar11`).  `SetHitImpact` keeps one object per attacker (`BtlEff` type 0x12): a second call resets it.
//! * `Polling` (one step per 1/30 s: the battle clock is quantised to 30 Hz): `life` starts at 8 and loses 1 per step from the second step on, `radius` grows by
//!   4 world units per step (`dt * 4 * 30`); gone when `life <= 0` = 8 steps = 0.267 s.
//! * `MakePacket`: a 32 segment annulus in the camera plane around the hit position, outer radius = `radius`, inner = `radius * max(0, (8 - 1.2 life) / 8)` (a disc
//!   that opens into a thin ring).  The 64 vertices are projected; each is pulled towards the ring centre by `1 - life / (8 / 0.3)` (0.7 growing to 1.0) while its
//!   *texture coordinate* stays the unshrunk screen position, and `TEX0` is the frame buffer: the band shows the scene squeezed from `1 / shrink` further out.
//! * Port: a full-screen post pass ([`Sh2RingFx`], `hit_impact_ring.wgsl`, the same `ScreenFx` machinery as the effect VM's screen effects) that evaluates the same map
//!   per pixel; the screen clamps of `MakePacket` (vertices kept inside 0..512 x 0..448) are not reproduced.
//!
//! Dev aids: `SH2_HIT_IMPACT=off`, `SH2_HIT_IMPACT_TEST=<s>` (one impact on the first enemy `s` seconds after the battle starts, repeating every 2 s; `SH2_HIT_IMPACT_SCREEN=<depth>` puts it on the view axis),
//! `SH2_HIT_IMPACT_TINT=1` (the displaced band is tinted red), `SH2_HIT_IMPACT_SHOTS=<dir>` (a photograph every frame while a ring is alive).

use bevy::asset::{load_internal_asset, uuid_handle};
use bevy::prelude::*;
use bevy::render::extract_component::ExtractComponent;
use bevy::render::render_resource::ShaderType;
use bevy::shader::{Shader, ShaderRef};

use crate::plugin::{BattleCamera, BattleRuntime};
use sh2_gfx::effects::screenfx_pass::{ScreenFx, ScreenFxPass};

pub const RING_SHADER: Handle<Shader> = uuid_handle!("5b7d0a1e-6c32-4d0b-9a55-48c3e1f2a001");

/// `HitImpact::__ct` `+0x70 / +0x74`: the initial life (the `power` argument of `SetHitImpact`)
pub const LIFE0: f32 = 8.0;
/// `Polling` steps per second (`dt * 30`)
pub const STEP_RATE: f32 = 30.0;
/// world units the radius grows per step (`dt * 4 * 30`)
pub const GROW_PER_STEP: f32 = 4.0;

/// One `HitImpact` object.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Impact {
    /// PS2 world position of the hit (`+0x60`), Bevy space here: the owner converts
    pub pos: Vec3,
    pub attacker: usize,
    /// `+0x74`
    life: f32,
    /// `+0x70`
    life0: f32,
    /// `+0x78`
    radius: f32,
    /// `+0x5c`: time since the first `Polling`
    age: f32,
}

impl Impact {
    /// `HitImpact::__ct(power, atk, pos)`.
    pub fn new(pos: Vec3, attacker: usize) -> Self {
        Impact { pos, attacker, life: LIFE0, life0: LIFE0, radius: 0.0, age: 0.0 }
    }

    /// `HitImpact::Reset(pos, power)`.
    pub fn reset(&mut self, pos: Vec3) {
        *self = Impact::new(pos, self.attacker);
    }

    /// `HitImpact::Polling` for `dt` seconds (a whole number of 1/30 s steps is how the game calls it; the port steps continuously).  Returns false once the object is gone.
    pub fn tick(&mut self, dt: f32) -> bool {
        if self.age != 0.0 {
            self.life -= dt * STEP_RATE;
        }
        self.age += dt;
        self.radius += dt * GROW_PER_STEP * STEP_RATE;
        self.life > 0.0
    }

    /// Outer and inner radius of the annulus in world units (`MakePacket`: `fVar16` and `fVar13`).
    pub fn radii(&self) -> (f32, f32) {
        let inner = self.radius * ((self.life0 - self.life * 1.2) / self.life0);
        (self.radius, inner.max(0.0))
    }

    /// The pull of the projected vertices towards the centre (`1 - life / (life0 / 0.3)`).
    pub fn shrink(&self) -> f32 {
        1.0 - self.life / (self.life0 / 0.3)
    }
}

/// Source pixel of a displayed pixel: `centre + (px - centre) / shrink` when the pixel lies in the displayed annulus (the shader's map), else itself.
/// `px` / `centre` in virtual frame pixels, `aspect` = y radius per x radius.
pub fn warp(px: Vec2, centre: Vec2, outer: f32, inner: f32, shrink: f32, aspect: f32) -> Vec2 {
    let q = px - centre;
    let r = Vec2::new(q.x, q.y / aspect).length();
    if r >= shrink * inner && r <= shrink * outer {
        centre + q / shrink
    } else {
        px
    }
}

/// Up to two rings for the post pass: `rings[2k] = (centre x, centre y, outer, inner)` (virtual pixels), `rings[2k + 1] = (shrink, enabled, aspect, debug tint)`.
#[derive(Component, ExtractComponent, Clone, Copy, ShaderType, Default, Debug, PartialEq)]
pub struct Sh2RingFx {
    pub rings: [Vec4; 4],
}

impl ScreenFx for Sh2RingFx {
    fn fragment_shader() -> ShaderRef {
        ShaderRef::Handle(RING_SHADER)
    }
}

pub struct HitImpactPlugin;

impl Plugin for HitImpactPlugin {
    fn build(&self, app: &mut App) {
        load_internal_asset!(app, RING_SHADER, "hit_impact_ring.wgsl", Shader::from_wgsl);
        app.add_plugins(ScreenFxPass::<Sh2RingFx>::default());
    }
}

/// The impacts in flight and the swing bookkeeping.
#[derive(Resource, Default)]
pub struct HitImpacts {
    live: Vec<Impact>,
    /// impacts waiting for the hit frame of their swing: `(seconds left, attacker, position)`
    pending: Vec<(f32, usize, Vec3)>,
    seen_swing: u32,
    clock: f32,
    test_next: Option<f32>,
    shot_n: u32,
}

pub fn reset_hit_impacts(mut st: ResMut<HitImpacts>) {
    *st = HitImpacts::default();
}

/// Where `PAtkHitSet` puts the impact: the target's chest on the side facing the attacker (Bevy space).
fn impact_pos(rt: &BattleRuntime, attacker: usize, target: usize) -> Vec3 {
    let feet = rt.positions.get(target).copied().unwrap_or(Vec3::ZERO);
    let (radius, height) = rt.dims.get(target).copied().unwrap_or((8.0, 17.0));
    let towards = rt.positions.get(attacker).map(|a| (*a - feet) * Vec3::new(1.0, 0.0, 1.0)).unwrap_or(Vec3::ZERO).normalize_or_zero();
    feet + Vec3::Y * height * 0.55 + towards * radius * 0.8
}

/// `SetHitImpact`: start the attacker's object or reset the running one.
fn set_hit_impact(live: &mut Vec<Impact>, attacker: usize, pos: Vec3) {
    log::info!("battle: HitImpact by fighter {attacker} at {pos:?}");
    match live.iter_mut().find(|i| i.attacker == attacker) {
        Some(i) => i.reset(pos),
        None => live.push(Impact::new(pos, attacker)),
    }
}

#[allow(clippy::too_many_arguments)]
pub fn drive_hit_impact(
    mut commands: Commands,
    rt: Option<Res<BattleRuntime>>,
    mut st: ResMut<HitImpacts>,
    cams: Query<(Entity, &Camera, &GlobalTransform), With<BattleCamera>>,
    time: Res<Time>,
) {
    let Some(rt) = rt else { return };
    let Ok((cam_e, camera, gt)) = cams.single() else { return };
    if std::env::var_os("SH2_HIT_IMPACT").is_some_and(|v| v == "off") {
        return;
    }
    let st = &mut *st;
    let dt = time.delta_secs().min(0.1);
    st.clock += dt;
    // the swing the battle engine just resolved: the last hit of a combo member's swing, if it connected
    let sw = &rt.battle.swing;
    if sw.id != st.seen_swing {
        st.seen_swing = sw.id;
        if sw.combo && sw.hits > 0 && sw.landed.last() == Some(&(sw.hits - 1)) {
            let ordinal = sw.landed.len() - 1;
            let delay = rt.hit_offsets.get(ordinal).copied().unwrap_or(0.0).max(0.0);
            st.pending.push((delay, sw.attacker, impact_pos(&rt, sw.attacker, sw.target)));
        }
    }
    // development: a test impact on the first enemy
    if let Some(t0) = std::env::var("SH2_HIT_IMPACT_TEST").ok().and_then(|v| v.parse::<f32>().ok()) {
        let next = st.test_next.get_or_insert(t0);
        if st.clock >= *next {
            *next += 2.0;
            if let Some(e) = (0..rt.setup.fighters.len()).find(|&i| rt.setup.fighters[i].is_enemy) {
                let a = (0..rt.setup.fighters.len()).find(|&i| !rt.setup.fighters[i].is_enemy).unwrap_or(0);
                // `SH2_HIT_IMPACT_SCREEN=<depth>`: put it on the view axis `depth` units in front of the camera instead
                let pos = match std::env::var("SH2_HIT_IMPACT_SCREEN").ok().and_then(|v| v.parse::<f32>().ok()) {
                    Some(d) => gt.translation() + gt.forward().as_vec3() * d,
                    None => impact_pos(&rt, a, e),
                };
                st.pending.push((0.0, a, pos));
            }
        }
    }
    for p in st.pending.iter_mut() {
        p.0 -= dt;
    }
    let due: Vec<(f32, usize, Vec3)> = st.pending.iter().copied().filter(|p| p.0 <= 0.0).collect();
    st.pending.retain(|p| p.0 > 0.0);
    for (_, a, pos) in due {
        set_hit_impact(&mut st.live, a, pos);
    }
    st.live.retain_mut(|i| i.tick(dt));
    // project the rings
    let mut fx = Sh2RingFx::default();
    // `SH2_HIT_IMPACT_TINT=1` (development): the band is also tinted red
    let tint = if std::env::var_os("SH2_HIT_IMPACT_TINT").is_some() { 1.0 } else { 0.0 };
    let mut n = 0;
    let to_v = |p: Vec2| camera.logical_viewport_size().map(|w| Vec2::new(p.x * 512.0 / w.x.max(1.0), p.y * 448.0 / w.y.max(1.0))).unwrap_or(p);
    for i in st.live.iter().take(2) {
        let (c, r, u) = (camera.world_to_viewport(gt, i.pos), camera.world_to_viewport(gt, i.pos + *gt.right()), camera.world_to_viewport(gt, i.pos + *gt.up()));
        let (Ok(c), Ok(r), Ok(u)) = (c, r, u) else { continue };
        let (c, r, u) = (to_v(c), to_v(r), to_v(u));
        let per_unit_x = (r.x - c.x).abs().max(1e-3);
        let aspect = ((u.y - c.y).abs() / per_unit_x).clamp(0.5, 2.0);
        let (outer, inner) = i.radii();
        fx.rings[2 * n] = Vec4::new(c.x, c.y, outer * per_unit_x, inner * per_unit_x);
        fx.rings[2 * n + 1] = Vec4::new(i.shrink(), 1.0, aspect, tint);
        n += 1;
    }
    if n > 0 {
        commands.entity(cam_e).insert(fx);
        if let Some(dir) = std::env::var_os("SH2_HIT_IMPACT_SHOTS").map(std::path::PathBuf::from) {
            st.shot_n += 1;
            let _ = std::fs::create_dir_all(&dir);
            commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(dir.join(format!("impact_{:03}.png", st.shot_n))));
        }
    } else {
        commands.entity(cam_e).remove::<Sh2RingFx>();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn lives_eight_steps() {
        let mut i = Impact::new(Vec3::ZERO, 0);
        let dt = 1.0 / 30.0;
        let mut steps = 1;
        // the first Polling does not age the life
        while i.tick(dt) {
            steps += 1;
            assert!(steps < 20);
        }
        assert_eq!(steps, 9, "the first step is free, 8 more empty the life");
        assert!(steps as f32 * dt < 0.31);
    }

    #[test]
    fn annulus_opens_from_a_disc() {
        let mut i = Impact::new(Vec3::ZERO, 0);
        let dt = 1.0 / 30.0;
        i.tick(dt);
        i.tick(dt);
        let (o, inner) = i.radii();
        assert!(o > 0.0);
        assert_eq!(inner, 0.0, "life 7: (8 - 8.4) < 0, a full disc");
        for _ in 0..5 {
            i.tick(dt);
        }
        let (o2, inner2) = i.radii();
        assert!(o2 > o && inner2 > 0.0 && inner2 < o2);
        // the shrink pulls the picture in by 30 % at the start and lets go at the end
        let fresh = Impact::new(Vec3::ZERO, 0);
        assert!((fresh.shrink() - 0.7).abs() < 1e-6);
        let mut end = fresh;
        end.life = 0.0;
        assert!((end.shrink() - 1.0).abs() < 1e-6);
    }

    #[test]
    fn warp_reads_from_further_out_inside_the_band() {
        let c = Vec2::new(256.0, 224.0);
        // band [0.7 * 20, 0.7 * 40] = [14, 28]
        let p = c + Vec2::new(20.0, 0.0);
        let s = warp(p, c, 40.0, 20.0, 0.7, 7.0 / 6.0);
        assert!((s.x - (256.0 + 20.0 / 0.7)).abs() < 1e-4 && s.y == 224.0);
        // inside the hole and outside the ring the frame is untouched
        assert_eq!(warp(c + Vec2::new(5.0, 0.0), c, 40.0, 20.0, 0.7, 7.0 / 6.0), c + Vec2::new(5.0, 0.0));
        assert_eq!(warp(c + Vec2::new(60.0, 0.0), c, 40.0, 20.0, 0.7, 7.0 / 6.0), c + Vec2::new(60.0, 0.0));
        // the y axis is stretched by the aspect
        let q = c + Vec2::new(0.0, 20.0 * 7.0 / 6.0);
        assert_ne!(warp(q, c, 40.0, 20.0, 0.7, 7.0 / 6.0), q);
    }

    #[test]
    fn set_hit_impact_resets_the_attackers_object() {
        let mut live = vec![];
        set_hit_impact(&mut live, 1, Vec3::X);
        live[0].tick(0.1);
        set_hit_impact(&mut live, 1, Vec3::Y);
        set_hit_impact(&mut live, 2, Vec3::Z);
        assert_eq!(live.len(), 2);
        assert_eq!(live[0].pos, Vec3::Y);
        assert_eq!(live[0].radii().0, 0.0);
    }
}

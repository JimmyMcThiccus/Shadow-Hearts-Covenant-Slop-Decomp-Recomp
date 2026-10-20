//! `CmbBreak` (JP 0x00506f10.., US 0x0052c650..) and `BreakBBox` (JP 0x005483d0.., US 0x0056ef30..): the two "break" effects of the battle
//! (`decomp/H/CmbBreak.c`, `decomp/H/BreakBBox.c`, notes/integration/break_effects.md).
//!
//! # `CmbBreak`: the "Combo Break!" banner
//! * Created by `CBattle::Polling` phase "Death" step 0 (JP phase 0x10 / CBattle.c 4824, US `Polling` 0x46ed58 / 0x46ed84) after an action of a **Link combo member that
//!   still has partners to act** (`bFlags25` bit 2 = `wTurnPendMask != 0 && nComboCnt != 0` at the start of the action) in which **no hit connected** (bit 3 =
//!   `PAtkHitSet`'s `bVar11` was never set) and the fight goes on (`BtlEndCheck() == 0`).  The palette (`TEX0` CSA) is 3 for a party actor, 0 for a monster
//!   (`BtlChr+0xb4` bit 0 = `bFlagsB` bit 0 = enemy).  The US constructor also plays SE `0x2000005`.  Step 1 waits until the banner is gone before the next member acts.
//! * `Destruct(t)` (end of battle, phases "result" 0x13 / 0x17): fades the banner out over `t` seconds (`+0x48` = remaining / total multiplies the alpha).
//! * `MakePacket`: one 255 x 46 sprite (texels (0, 0)..(255, 46) of `BTL_000` US 10, 256 x 48, "Combo Break!"; the US build draws a 2 vertex GS sprite, the JP demo a 4 vertex strip) centred at (256, 224) of the 512 x 448 frame, alpha `0x80 * fade`:
//!   `t < 0.2` it zooms in from scale 6.6 to 1 (`(0.2 - t) / 0.25 * 7 + 1`), `0.2..0.3` it shakes (+-8 px random), `0.3..0.5` the shake dies out
//!   (`(0.5 - t) / 0.2`), `0.5..1.2` it stands, `1.2..1.4` the alpha fades `(1.4 - t) / 0.2`; gone at 1.4 s.
//!
//! # `BreakBBox`: a body breaking into stone chips
//! * `CBattle` creates it (`__ct__9BreakBBoxFiii(0, chr, 0)`) when a **petrified** (status record kind 'G' with value bit 0x20) fighter is hit / killed in state 0x24 / 0x25
//!   (CBattle.c 47356 / 48295), when a finishing effect kills a petrified one (5308) and when the stone is cured (18194 / 18249): the model is blanked (`ClutCtrl(0,0,0,0)`)
//!   and every body BBox of the model (12 triangles per box, the cube table at JP 0x650df0) becomes a flying chip.
//! * `InitParam`: per triangle the centroid is the chip's position, its corners (clamped to `|BtlChr+0x3a0| / 7.4` from the centroid) the local vertices; the velocity is
//!   `(centroid - box centre) * (0.35..0.45, 0.45..0.55, 0.35..0.45)` per 1/30 s, the spin (+-1 rad per 1/30 s about x and y) random; the colour is the scene light
//!   on the triangle's normal: `mean over the enabled lights of col * (n . L / 2 + 0.5) + ambient` (flat, untextured, alpha 0x80).
//! * `Polling` (per 1/30 s step): position `+= vel`, rotation `+= spin`, `vel.y += 0.12` (gravity, PS2 y is down); `life -= dt` from 1.0 and every chip is drawn at
//!   `life` times its size (`MakePacket` scales the rotation matrix); a chip all of whose vertices are below the floor (`y > 0`) is dropped; the object ends when no chip
//!   is left or `life <= 0`.
//! * Port trigger: a **monster** that falls while it carries the petrify status (the port's rules treat petrify as "down"); the party's petrified members have no statue state
//!   yet.  `SH2_BREAK_BBOX=<fighter>@<s>` breaks any fighter `s` seconds after the battle starts (development).
//!
//! Dev aids: `SH2_BREAK_FX=off`, `SH2_BREAK_PETRIFY=<fighter>` (with `SH2_BATTLE_KO=<fighter>@<s>`: the fallen monster shatters), `SH2_CMB_BREAK_TEST=<s>` (a banner `s` seconds after the start), `SH2_BREAK_SHOTS=<dir>` (a photograph every 0.05 s while an effect lives).

use bevy::prelude::*;
use std::collections::HashSet;

use crate::choreo::Act;
use crate::effects_bridge::frame_world;
use crate::flow::Phase;
use crate::models::BattleModel;
use crate::plugin::BattleRuntime;
use sh2_gfx::bevy::model::AnimatedModel;
use sh2_gfx::bevy::{Sh2Material, Sh2SceneLight};
use sh2_menu::bevy_ui::{UiCanvas, UiTextures};
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextureId, Vertex};

// ------------------------------------------------------------------------------------------------------------------
// CmbBreak
// ------------------------------------------------------------------------------------------------------------------

/// `CmbBreak::Polling`: the banner is gone after 1.4 s
pub const CMB_LIFE: f32 = 1.4;
/// the sprite's half size (`MakePacket`: +-127.5 x +-23 times the scale)
pub const CMB_HALF: [f32; 2] = [127.5, 23.0];
/// `World::AddOT(0xd)`: the sprite layers of the port are numbered by draw order; 13 sits above the battle HUD (9) and the extra effect layer (12)
pub const CMB_LAYER: u8 = sh2_menu::bevy_ui::layer::SPRITE_BASE + 5;
/// SE of the US constructor (`HNMSnd::PlaySE(0x2000005, 1, 0)`)
pub const CMB_SE: u32 = 0x2000005;

/// One `CmbBreak` object.
#[derive(Clone, Debug, PartialEq)]
pub struct CmbBreak {
    /// `+0x40`
    pub age: f32,
    /// `+0x44`: the CSA of the title palette (3 for a party actor, 0 for a monster)
    pub pal: u8,
    /// `Destruct`: `(+0x4c remaining, +0x50 total)`
    fade: Option<(f32, f32)>,
}

/// What `CmbBreak::MakePacket` draws at one instant.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct CmbLook {
    pub scale: f32,
    /// sprite centre in the 512 x 448 frame
    pub centre: [f32; 2],
    /// GS alpha 0..128 (`0x80` = opaque)
    pub alpha: f32,
}

impl CmbBreak {
    pub fn new(pal: u8) -> Self {
        CmbBreak { age: 0.0, pal, fade: None }
    }

    /// `CmbBreak::Destruct(t)`: start the fade-out (only the first call counts).
    pub fn destruct(&mut self, secs: f32) {
        if self.fade.is_none() {
            self.fade = Some((secs, secs));
        }
    }

    /// `+0x48`: the fade multiplier of `Destruct`
    pub fn fade_scale(&self) -> f32 {
        self.fade.map(|(left, total)| left / total).unwrap_or(1.0)
    }

    /// `CmbBreak::Polling`: false once the object is gone (age 1.4 or the destruct timer ran out).
    pub fn tick(&mut self, dt: f32) -> bool {
        self.age += dt;
        if let Some((left, _)) = self.fade.as_mut() {
            *left -= dt;
        }
        !(self.age >= CMB_LIFE || self.fade.is_some_and(|(left, _)| left <= 0.0))
    }

    /// `MakePacket`; `rnd` = two random numbers 0..1 (the shake).
    pub fn look(&self, rnd: [f32; 2]) -> CmbLook {
        let t = self.age;
        // `(int)(fade * 128) & 0xff`
        let mut alpha = ((self.fade_scale() * 128.0) as i32 & 0xff) as f32;
        let (mut scale, mut centre) = (1.0f32, [256.0f32, 224.0f32]);
        if t < 0.2 {
            scale = (0.2 - t) / 0.25 * 7.0 + 1.0;
        } else if t < 0.3 {
            centre = [256.0 + (rnd[0] * 16.0 - 8.0), 224.0 + (rnd[1] * 16.0 - 8.0)];
        } else if t < 0.5 {
            let k = (0.2 - (t - 0.3)) / 0.2;
            centre = [256.0 + (rnd[0] * 16.0 - 8.0) * k, 224.0 + (rnd[1] * 16.0 - 8.0) * k];
        } else if t >= 1.2 {
            alpha = ((alpha * ((1.4 - t) / 0.2)) as i32 & 0xff) as f32;
        }
        CmbLook { scale, centre, alpha }
    }

    /// The four corners (TL, BL, TR, BR) of the sprite.
    pub fn quad(l: &CmbLook) -> [[f32; 2]; 4] {
        let (hx, hy) = (CMB_HALF[0] * l.scale, CMB_HALF[1] * l.scale);
        let (cx, cy) = (l.centre[0], l.centre[1]);
        [[cx - hx, cy - hy], [cx - hx, cy + hy], [cx + hx, cy - hy], [cx + hx, cy + hy]]
    }
}

/// `CBattle::Polling` Death step 0: does the action that just ended break the combo?  `combo_pending` = more members still have to act (bit 2), `connected` = a hit
/// of the swing connected (bit 3), `battle_over` = `BtlEndCheck() != 0`.
pub fn breaks_combo(combo_pending: bool, connected: bool, battle_over: bool) -> bool {
    combo_pending && !connected && !battle_over
}

// ------------------------------------------------------------------------------------------------------------------
// BreakBBox
// ------------------------------------------------------------------------------------------------------------------

/// The cube table at JP 0x00650df0 (`InitParam`): per triangle three corner indices and the two corners whose difference is the lighting normal.
pub const TRI_TABLE: [[u8; 5]; 12] = [
    [0, 1, 2, 0, 6],
    [1, 2, 3, 1, 7],
    [4, 5, 6, 4, 2],
    [5, 6, 7, 5, 3],
    [0, 2, 6, 0, 1],
    [2, 6, 4, 2, 3],
    [1, 3, 7, 1, 0],
    [3, 7, 5, 3, 2],
    [0, 1, 6, 0, 2],
    [1, 6, 7, 1, 3],
    [2, 3, 4, 2, 0],
    [3, 4, 5, 3, 1],
];

/// `BreakBBox +0x80`: the object's life in seconds
pub const BREAK_LIFE: f32 = 1.0;
/// `Polling` steps per second
pub const STEP_RATE: f32 = 30.0;
/// `0.12 * dt * 30`: gravity per step (`+0x78.y`)
pub const GRAVITY_STEP: f32 = 0.12;

/// The lights `InitParam` reads from the `keepLight`: up to three (direction towards the light, colour 0..1) and the ambient colour.  Same space as the corners.
#[derive(Clone, Debug, Default)]
pub struct ChipLight {
    pub lights: Vec<(Vec3, Vec3)>,
    pub ambient: Vec3,
}

impl ChipLight {
    /// The colour of a triangle with normal `n`: `mean(col * (n . L / 2 + 0.5)) + ambient` (0..1 scale, 1 = GS 0x80).
    pub fn shade(&self, n: Vec3) -> Vec3 {
        if self.lights.is_empty() {
            return self.ambient;
        }
        let sum: Vec3 = self.lights.iter().map(|(d, c)| *c * (n.dot(*d) / 2.0 + 0.5)).sum();
        sum / self.lights.len() as f32 + self.ambient
    }
}

/// One chip: a triangle of a BBox.  PS2 world (y down).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Chip {
    pub pos: Vec3,
    local: [Vec3; 3],
    rot: [f32; 2],
    vel: Vec3,
    spin: [f32; 2],
    pub color: [f32; 3],
    done: bool,
}

/// One `BreakBBox` object.
#[derive(Clone, Debug)]
pub struct Shatter {
    pub chips: Vec<Chip>,
    /// `+0x80`
    pub life: f32,
}

impl Shatter {
    /// `InitParam` over the BBoxes (`boxes` = the 8 world corners of each); `max_edge` = `|BtlChr+0x3a0| / 7.4`; `rnd` yields 0..1.
    pub fn new(boxes: &[[Vec3; 8]], max_edge: f32, light: &ChipLight, rnd: &mut dyn FnMut() -> f32) -> Shatter {
        let mut chips = vec![];
        for e in boxes {
            let centre = e.iter().copied().sum::<Vec3>() / 8.0;
            for t in TRI_TABLE {
                let (a, b, c) = (e[t[0] as usize], e[t[1] as usize], e[t[2] as usize]);
                let centroid = (a + b + c) / 3.0;
                let clamp = |v: Vec3| if v.length() > max_edge { v.normalize_or_zero() * max_edge } else { v };
                let local = [clamp(a - centroid), clamp(b - centroid), clamp(c - centroid)];
                let n = (e[t[3] as usize] - e[t[4] as usize]).normalize_or_zero();
                let col = light.shade(n);
                let off = centroid - centre;
                // the three random numbers: z, x (0.35 + r * 0.1), y (0.45 + r * 0.1)
                let rz = rnd() * 0.1 + 0.35;
                let ry = rnd() * 0.1 + 0.45;
                let rx = rnd() * 0.1 + 0.35;
                let vel = off * Vec3::new(rx, ry, rz);
                let spin = [rnd() * 2.0 - 1.0, rnd() * 2.0 - 1.0];
                chips.push(Chip { pos: centroid, local, rot: [0.0; 2], vel, spin, color: col.to_array(), done: false });
            }
        }
        Shatter { chips, life: BREAK_LIFE }
    }

    /// The chip's three vertices now (`RotTransVector` of the local vertices by `RotMatrix(rot) * life` + position).
    pub fn vertices(&self, c: &Chip) -> [Vec3; 3] {
        let r = Mat3::from_rotation_x(c.rot[0]) * Mat3::from_rotation_y(c.rot[1]);
        c.local.map(|v| c.pos + r * v * self.life.max(0.0))
    }

    /// `Polling` + the floor test of `MakePacket` for `dt` seconds.  Returns false when the object is over.
    pub fn tick(&mut self, dt: f32) -> bool {
        let step = dt * STEP_RATE;
        let mut any = false;
        for i in 0..self.chips.len() {
            if self.chips[i].done {
                continue;
            }
            let c = &mut self.chips[i];
            c.pos += c.vel * step;
            c.vel.y += GRAVITY_STEP * step;
            for k in 0..2 {
                c.rot[k] += c.spin[k] * step;
                while c.rot[k] < -std::f32::consts::PI {
                    c.rot[k] += std::f32::consts::TAU;
                }
                while c.rot[k] >= std::f32::consts::PI {
                    c.rot[k] -= std::f32::consts::TAU;
                }
            }
            any = true;
        }
        self.life -= dt;
        // a chip whose three vertices are all below the floor (PS2 y > 0) is dropped
        for i in 0..self.chips.len() {
            if self.chips[i].done {
                continue;
            }
            let v = self.vertices(&self.chips[i]);
            if v.iter().all(|p| p.y > 0.0) {
                self.chips[i].done = true;
            }
        }
        any && self.life > 0.0 && self.chips.iter().any(|c| !c.done)
    }

    pub fn live_chips(&self) -> impl Iterator<Item = &Chip> {
        self.chips.iter().filter(|c| !c.done)
    }
}

// ------------------------------------------------------------------------------------------------------------------
// Bevy side
// ------------------------------------------------------------------------------------------------------------------

/// A banner waiting for the action to finish (`Polling` Death step 0 runs after the action's states).
#[derive(Clone, Copy, Debug)]
struct PendingBanner {
    pal: u8,
    waited: f32,
}

#[derive(Resource, Default)]
pub struct BreakFx {
    cmb: Option<CmbBreak>,
    pending: Option<PendingBanner>,
    seen_swing: u32,
    tex: Option<[Option<(TextureId, (u32, u32))>; 4]>,
    /// fighters that were already seen dead (the first frame a monster is in a death state decides whether it shatters)
    dead_seen: HashSet<usize>,
    shatters: Vec<Shatter>,
    mat: Option<Handle<Sh2Material>>,
    mesh: Option<(Entity, Handle<Mesh>)>,
    seed: u32,
    clock: f32,
    test_cmb_done: bool,
    test_break_done: HashSet<usize>,
    shot_clock: f32,
    shot_n: u32,
}

pub fn reset_break_fx(mut st: ResMut<BreakFx>, mut canvas: ResMut<UiCanvas>) {
    *st = BreakFx { seed: 0x2545_f491, ..Default::default() };
    canvas.clear(CMB_LAYER);
}

/// Hold the battle flow (`rt.wait`) while a banner is pending or showing.
const HOLD_PENDING: f32 = 0.25;
/// give up waiting for the action's animations after this long
const PENDING_TIMEOUT: f32 = 8.0;

/// PS2 body BBox corners of a fighter's model in its current pose: every BBox of the model whose first corner is not zero (`InitParam` skips empty ones); the model's
/// own list when it has none.
fn body_boxes(am: &AnimatedModel, gt: &GlobalTransform) -> Vec<[Vec3; 8]> {
    let mut out = vec![];
    for b in am.inst.model.bounds.iter() {
        if b.corners.len() < 8 || (b.corners[0].x == 0.0 && b.corners[0].y == 0.0 && b.corners[0].z == 0.0) {
            continue;
        }
        let Some(fw) = frame_world(am, gt, (b.tag & 0xff) as usize) else { continue };
        let mut o = [Vec3::ZERO; 8];
        for (k, c) in b.corners.iter().take(8).enumerate() {
            o[k] = fw.transform_point3(Vec3::new(c.x, c.y, c.z));
        }
        out.push(o);
    }
    out
}

/// The light the chips are shaded with, in PS2 space (the scene light is given in Bevy space: y and z flip).
fn chip_light(l: &Sh2SceneLight) -> ChipLight {
    let flip = |v: Vec3| Vec3::new(v.x, -v.y, -v.z);
    let lights = (0..3).filter(|&i| l.colors[i].max_element() > 1e-3).map(|i| (flip(l.dirs[i]), l.colors[i])).collect();
    ChipLight { lights, ambient: l.ambient }
}

#[allow(clippy::too_many_arguments)]
pub fn drive_break_fx(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    disc: Option<Res<sh2_gfx::bevy::Sh2Disc>>,
    mut models: Query<&mut BattleModel>,
    anims: Query<&AnimatedModel>,
    gts: Query<&GlobalTransform>,
    light: Option<Res<Sh2SceneLight>>,
    mut st: ResMut<BreakFx>,
    mut canvas: ResMut<UiCanvas>,
    mut textures: ResMut<UiTextures>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<Sh2Material>>,
    mut images: ResMut<Assets<Image>>,
    time: Res<Time>,
) {
    let (Some(mut rt), Some(disc)) = (rt, disc) else { return };
    if std::env::var_os("SH2_BREAK_FX").is_some_and(|v| v == "off") {
        return;
    }
    let st = &mut *st;
    let dt = time.delta_secs().min(0.1);
    st.clock += dt;
    if st.seed == 0 {
        st.seed = 0x2545_f491;
    }

    // ---- the banner texture: the 256 x 48 title of BTL_000 (US section 10), four palettes ----
    if st.tex.is_none() {
        let bin = disc.read("BTLDATA/BTL_000.BIN").unwrap_or_default();
        let secs = crate::stage::sections(&bin);
        let mut tex = [None; 4];
        if let Some((_, sec)) = secs.iter().find(|(tag, sec)| tag == "tex" && sh2_gfx::texture::decode_jrc(sec, 0, 0).map(|i| i.width == 256 && i.height == 48).unwrap_or(false)) {
            // `TEX0.CSA` = 0 / 3: the title's 96 entry CLUT holds 16 colour sub-palettes (0 = blue for a monster actor, 3 = red for a party actor, live US capture)
            for (p, slot) in tex.iter_mut().enumerate() {
                if let Ok(i) = sh2_gfx::texture::decode_jrc_csa(sec, 0, p) {
                    *slot = Some((textures.add(&mut images, i.width, i.height, i.pixels), (i.width, i.height)));
                }
            }
        }
        st.tex = Some(tex);
    }

    // ---- triggers ----
    let sw = rt.battle.swing.clone();
    if sw.id != st.seen_swing {
        st.seen_swing = sw.id;
        log::info!("battle: swing #{}: fighter {} -> {}, {} hits, connected {:?}, combo {}, members pending {}", sw.id, sw.attacker, sw.target, sw.hits, sw.landed, sw.combo, sw.pending);
        let over = !rt.battle.fighters.iter().flatten().any(|f| f.is_enemy && f.hp > 0 && !f.removed) || !rt.battle.fighters.iter().flatten().any(|f| !f.is_enemy && f.hp > 0 && !f.removed);
        // the swing's last target may have fallen: the fight is then over for the banner's purposes only when nobody is left
        if breaks_combo(sw.pending, !sw.landed.is_empty(), over) {
            let enemy = rt.battle.fighters.get(sw.attacker).and_then(|f| f.as_ref()).map(|f| f.is_enemy).unwrap_or(false);
            st.pending = Some(PendingBanner { pal: if enemy { 0 } else { 3 }, waited: 0.0 });
        }
    }
    if let Some(t0) = std::env::var("SH2_CMB_BREAK_TEST").ok().and_then(|v| v.parse::<f32>().ok()) {
        if !st.test_cmb_done && st.clock >= t0 {
            st.test_cmb_done = true;
            st.pending = Some(PendingBanner { pal: 3, waited: 0.0 });
        }
    }
    if let Some(p) = st.pending.as_mut() {
        p.waited += dt;
        // `Polling` step 1 holds the next member until the banner is gone; the action's own motions finish first
        if rt.anim_busy && p.waited < PENDING_TIMEOUT {
            rt.wait = rt.wait.max(HOLD_PENDING);
        } else {
            let pal = p.pal;
            log::info!("battle: CmbBreak banner (palette {pal}), phase {:?}", rt.battle.phase);
            st.pending = None;
            st.cmb = Some(CmbBreak::new(pal));
            rt.wait = rt.wait.max(CMB_LIFE);
            if sh2_core::boot::is_retail() {
                sh2_audio::post(sh2_audio::AudioRequest::PlayGlobalSe { id: CMB_SE });
            }
        }
    }
    // `Destruct(1.0)` when the fight ends
    if matches!(rt.battle.phase, Phase::Win | Phase::Lose | Phase::End) {
        if let Some(c) = st.cmb.as_mut() {
            c.destruct(0.5);
        }
        st.pending = None;
    }

    // ---- BreakBBox: a monster that falls petrified ----
    let mut to_break: Vec<usize> = vec![];
    for m in models.iter() {
        let dead = matches!(m.ch.act, Act::Down | Act::EnemyDown | Act::Dissolve);
        if !dead {
            continue;
        }
        if st.dead_seen.insert(m.chr) {
            let f = rt.battle.fighters.get(m.chr).and_then(|f| f.as_ref());
            // `SH2_BREAK_PETRIFY=<fighter>[,..]` (development): treat that fighter as petrified when it falls (the rules need a Stone effect to set the status)
            let forced = std::env::var("SH2_BREAK_PETRIFY").map(|v| v.split(',').any(|x| x.trim().parse::<usize>() == Ok(m.chr))).unwrap_or(false);
            if f.is_some_and(|f| f.is_enemy && (forced || crate::rules::status_of(&f.status) & crate::rules::status_bits::PETRIFY != 0)) {
                to_break.push(m.chr);
            }
        }
    }
    // development: `SH2_BREAK_BBOX=<fighter>@<s>`
    if let Some((c, t)) = std::env::var("SH2_BREAK_BBOX").ok().and_then(|v| v.split_once('@').map(|(a, b)| (a.to_string(), b.to_string()))).and_then(|(a, b)| Some((a.parse::<usize>().ok()?, b.parse::<f32>().ok()?))) {
        if st.clock >= t && st.test_break_done.insert(c) {
            to_break.push(c);
        }
    }
    for chr in to_break {
        let Some(mut m) = models.iter_mut().find(|m| m.chr == chr) else { continue };
        let (Ok(am), Ok(gt)) = (anims.get(m.holder), gts.get(m.holder)) else { continue };
        let mut boxes = body_boxes(am, gt);
        if boxes.is_empty() {
            // no BBox in the model: the fighter's own `bbx` body box around the feet
            let feet = Vec3::new(m.pos.x, -m.pos.y, -m.pos.z);
            let (r, h) = rt.dims.get(chr).copied().unwrap_or((8.0, 17.0));
            let mut o = [Vec3::ZERO; 8];
            for (i, c) in o.iter_mut().enumerate() {
                *c = feet + Vec3::new(if i & 1 == 0 { -r } else { r }, if i & 2 == 0 { 0.0 } else { -h }, if i & 4 == 0 { -r } else { r });
            }
            boxes.push(o);
        }
        let max_edge = rt.boxes.get(chr).copied().flatten().map(|b| b.size_len() / 7.4).filter(|v| *v > 0.1).unwrap_or(3.0);
        let lt = light.as_deref().map(chip_light).unwrap_or_else(|| chip_light(&Sh2SceneLight::default()));
        let mut seed = st.seed;
        let mut rnd = move || {
            seed = seed.wrapping_mul(1664525).wrapping_add(1013904223);
            (seed >> 8) as f32 / (1u32 << 24) as f32
        };
        let sh = Shatter::new(&boxes, max_edge, &lt, &mut rnd);
        st.seed = st.seed.wrapping_mul(22695477).wrapping_add(chr as u32 + 1);
        log::info!("battle: BreakBBox on fighter {chr}: {} boxes, {} chips, edge <= {max_edge:.2}", boxes.len(), sh.chips.len());
        st.shatters.push(sh);
        // `ClutCtrl(0, 0, 0, 0)`: the model is blanked
        m.ch.act = Act::Gone;
        m.ch.hidden = true;
    }

    // ---- simulate ----
    let mut seed_rng = st.seed;
    let mut rnd2 = || {
        seed_rng = seed_rng.wrapping_mul(1664525).wrapping_add(1013904223);
        (seed_rng >> 8) as f32 / (1u32 << 24) as f32
    };
    let shake = [rnd2(), rnd2()];
    st.seed = seed_rng;
    let mut cmb_done = false;
    if let Some(c) = st.cmb.as_mut() {
        cmb_done = !c.tick(dt);
    }
    if cmb_done {
        st.cmb = None;
    }
    st.shatters.retain_mut(|s| s.tick(dt));

    // ---- the banner on the sprite canvas ----
    match (&st.cmb, st.tex.as_ref()) {
        (Some(c), Some(tex)) => {
            let look = c.look(shake);
            let t = tex[(c.pal as usize).min(3)].or(tex[0]);
            if let (Some(t), true) = (t, look.alpha > 0.0) {
                let q = CmbBreak::quad(&look);
                let col = Rgba::new(0x80, 0x80, 0x80, look.alpha.clamp(0.0, 128.0) as u8);
                let v = |p: [f32; 2], u: f32, w: f32| Vertex { pos: Vec2::new(p[0], p[1]), uv: Vec2::new(u, w), color: col };
                let mut g = canvas.begin(CMB_LAYER);
                // the sprite's UVs are (0, 0) .. (255, 46) texels of the 256 x 48 title (US `MakePacket` static data `+0xd0 = 0x02e00ff0`)
                let (u1, w1) = (255.0 / 256.0, 46.0 / 48.0);
                g.draw(DrawCmd::Quad { tex: Some(t.0), v: [v(q[0], 0.0, 0.0), v(q[1], 0.0, w1), v(q[2], u1, 0.0), v(q[3], u1, w1)], blend: Blend::Alpha });
            }
        }
        _ => {
            canvas.clear(CMB_LAYER);
        }
    }

    // ---- the chips ----
    let (mut pos, mut col) = (Vec::<[f32; 3]>::new(), Vec::<[f32; 4]>::new());
    let to_bevy = |v: Vec3| [v.x, -v.y, -v.z];
    for s in &st.shatters {
        for c in s.live_chips() {
            let v = s.vertices(c);
            let k = [c.color[0].min(2.0), c.color[1].min(2.0), c.color[2].min(2.0), 1.0];
            // both windings: the chips are single sided
            for tri in [[0usize, 1, 2], [0, 2, 1]] {
                for i in tri {
                    pos.push(to_bevy(v[i]));
                    col.push(k);
                }
            }
        }
    }
    if st.mat.is_none() {
        st.mat = Some(mats.add(Sh2Material::textured(None).with_lit(false).with_fog(false)));
    }
    // dev aid: a photograph every 0.05 s while something is on screen
    if let Some(dir) = std::env::var_os("SH2_BREAK_SHOTS").map(std::path::PathBuf::from) {
        if st.cmb.is_some() || !st.shatters.is_empty() {
            st.shot_clock += dt;
            if st.shot_clock >= 0.05 {
                st.shot_clock = 0.0;
                st.shot_n += 1;
                let _ = std::fs::create_dir_all(&dir);
                commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(dir.join(format!("break_{:03}.png", st.shot_n))));
            }
        }
    }
    let n = pos.len();
    if n == 0 {
        pos = vec![[0.0; 3]; 3];
        col = vec![[0.0; 4]; 3];
    }
    let mut mesh = Mesh::new(bevy::mesh::PrimitiveTopology::TriangleList, bevy::asset::RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos.clone());
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32, 0.0]; pos.len()]);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    match &st.mesh {
        Some((e, h)) if commands.get_entity(*e).is_ok() => {
            if let Some(mut mm) = meshes.get_mut(h) {
                *mm = mesh;
            }
        }
        _ => {
            let h = meshes.add(mesh);
            let mat = st.mat.clone().unwrap();
            let e = commands.spawn((Name::new("break_bbox"), Mesh3d(h.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), bevy::camera::visibility::NoFrustumCulling, DespawnOnExit(sh2_core::game::Scene::Battle))).id();
            st.mesh = Some((e, h));
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn banner_zooms_in_shakes_stands_and_fades() {
        let c = |t: f32| CmbBreak { age: t, pal: 3, fade: None };
        let r = [0.5, 0.5];
        // zoom: 6.6 at t = 0 down to 1 at 0.2
        let l0 = c(0.0).look(r);
        assert!((l0.scale - 6.6).abs() < 1e-5 && l0.centre == [256.0, 224.0] && l0.alpha == 128.0);
        assert!((c(0.1).look(r).scale - (0.1 / 0.25 * 7.0 + 1.0)).abs() < 1e-5);
        assert_eq!(c(0.2).look(r).scale, 1.0);
        // shake: rnd 0 / 1 are the +-8 extremes; a fixed rnd 0.5 stands still
        assert_eq!(c(0.25).look([0.0, 1.0]).centre, [248.0, 232.0]);
        assert_eq!(c(0.25).look(r).centre, [256.0, 224.0]);
        // the shake dies out over 0.3..0.5
        let l = c(0.4).look([0.0, 1.0]);
        assert!((l.centre[0] - (256.0 - 8.0 * 0.5)).abs() < 1e-4);
        assert_eq!(c(0.5).look([0.0, 1.0]).centre, [256.0, 224.0]);
        // stands, then the alpha fades from 1.2 to 1.4
        assert_eq!(c(1.1).look(r).alpha, 128.0);
        assert!((c(1.3).look(r).alpha - 64.0).abs() < 1.0);
        assert_eq!(c(1.39).look(r).alpha, 6.0);
    }

    #[test]
    fn banner_lifetime_and_destruct() {
        let mut c = CmbBreak::new(0);
        let mut t = 0.0f32;
        while c.tick(1.0 / 60.0) {
            t += 1.0 / 60.0;
            assert!(t < 2.0);
        }
        assert!((t - 1.4).abs() < 0.03);
        // destruct(0.5): half way the alpha is halved, gone after 0.5 s
        let mut d = CmbBreak::new(3);
        d.tick(0.6);
        d.destruct(0.5);
        d.tick(0.25);
        assert!((d.fade_scale() - 0.5).abs() < 1e-6);
        assert_eq!(d.look([0.5; 2]).alpha, 64.0);
        assert!(!d.tick(0.3));
        // a second destruct does not restart the fade
        let mut e = CmbBreak::new(3);
        e.destruct(1.0);
        e.tick(0.5);
        e.destruct(1.0);
        assert!((e.fade_scale() - 0.5).abs() < 1e-6);
    }

    #[test]
    fn quad_is_255_by_46_times_the_scale() {
        let l = CmbLook { scale: 2.0, centre: [256.0, 224.0], alpha: 128.0 };
        let q = CmbBreak::quad(&l);
        assert_eq!(q[0], [256.0 - 255.0, 224.0 - 46.0]);
        assert_eq!(q[3], [256.0 + 255.0, 224.0 + 46.0]);
    }

    #[test]
    fn the_combo_breaks_only_for_a_missed_non_final_member() {
        assert!(breaks_combo(true, false, false));
        assert!(!breaks_combo(true, true, false), "a connecting hit keeps the combo");
        assert!(!breaks_combo(false, false, false), "the last member's miss is not a break");
        assert!(!breaks_combo(true, false, true), "no banner when the battle is over");
    }

    fn unit_box() -> [Vec3; 8] {
        // the table's cube: corners by index; any consistent assignment works for the topology test
        let p = |x: f32, y: f32, z: f32| Vec3::new(x, y, z);
        [p(-1.0, -1.0, -1.0), p(1.0, -1.0, -1.0), p(-1.0, 1.0, -1.0), p(1.0, 1.0, -1.0), p(-1.0, 1.0, 1.0), p(1.0, 1.0, 1.0), p(-1.0, -1.0, 1.0), p(1.0, -1.0, 1.0)]
    }

    #[test]
    fn the_table_describes_a_cube() {
        // each face is two triangles sharing an edge; every corner is used 3 * 2 = 6 times... check the 12 triangles cover the 6 faces of the unit box
        let b = unit_box();
        let mut faces = std::collections::BTreeSet::new();
        for t in TRI_TABLE {
            let (a, bb, c) = (b[t[0] as usize], b[t[1] as usize], b[t[2] as usize]);
            // all three corners share one coordinate value on exactly one axis: a face
            let axis = (0..3).find(|&k| a[k] == bb[k] && bb[k] == c[k]).expect("triangle lies in a face");
            faces.insert((axis, a[axis] as i32));
            // the normal corners differ along the face normal only
            let n = b[t[3] as usize] - b[t[4] as usize];
            assert!(n.length() > 0.0);
        }
        assert_eq!(faces.len(), 6);
    }

    #[test]
    fn chips_fly_outwards_fall_and_vanish() {
        let b = unit_box().map(|p| p * 5.0 + Vec3::new(0.0, -20.0, 0.0));
        let light = ChipLight { lights: vec![(Vec3::new(0.0, -1.0, 0.0), Vec3::splat(0.8))], ambient: Vec3::splat(0.2) };
        let mut k = 0.0f32;
        let mut rnd = || {
            k = (k + 0.37) % 1.0;
            k
        };
        let mut s = Shatter::new(&[b], 3.0, &light, &mut rnd);
        assert_eq!(s.chips.len(), 12);
        // chips start on the box surface, move away from its centre
        let centre = Vec3::new(0.0, -20.0, 0.0);
        let d0: Vec<f32> = s.chips.iter().map(|c| (c.pos - centre).length()).collect();
        s.tick(1.0 / 30.0);
        for (c, d) in s.chips.iter().zip(&d0) {
            assert!((c.pos - centre).length() > *d - 1e-3);
        }
        // local vertices are clamped to the edge limit
        assert!(s.chips.iter().all(|c| c.local.iter().all(|v| v.length() <= 3.0 + 1e-4)));
        // the whole thing is over after its one second life at the latest
        let mut t = 0.0f32;
        while s.tick(1.0 / 60.0) {
            t += 1.0 / 60.0;
            assert!(t < 1.2);
        }
        assert!(t <= 1.0 + 0.03);
    }

    #[test]
    fn chips_below_the_floor_are_dropped() {
        let b = unit_box().map(|p| p * 0.2 + Vec3::new(0.0, -0.1, 0.0));
        let light = ChipLight::default();
        let mut rnd = || 0.5;
        let mut s = Shatter::new(&[b], 3.0, &light, &mut rnd);
        // the box straddles y = 0: after a few steps of gravity every chip sank below the floor
        let mut alive = s.chips.iter().filter(|c| !c.done).count();
        for _ in 0..20 {
            s.tick(1.0 / 30.0);
            let a = s.chips.iter().filter(|c| !c.done).count();
            assert!(a <= alive);
            alive = a;
        }
        assert!(s.live_chips().count() < 12);
    }

    #[test]
    fn chip_shading_follows_the_normal() {
        let l = ChipLight { lights: vec![(Vec3::Y, Vec3::ONE)], ambient: Vec3::splat(0.1) };
        let up = l.shade(Vec3::Y);
        let down = l.shade(-Vec3::Y);
        assert!((up.x - 1.1).abs() < 1e-6 && (down.x - 0.1).abs() < 1e-6);
        // no light: ambient only
        assert_eq!(ChipLight { lights: vec![], ambient: Vec3::splat(0.3) }.shade(Vec3::X), Vec3::splat(0.3));
    }
}

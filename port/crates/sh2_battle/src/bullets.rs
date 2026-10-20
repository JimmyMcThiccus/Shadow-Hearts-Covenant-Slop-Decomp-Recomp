//! Projectiles of the ranged attacks (`Bullet1`, JP BATTLE.BIN 0x0053ba90.., US 0x005623b0..; simulation in [`sh2_gfx::effects::bullet`]).
//!
//! `CBattle::MotionEventCallBack` (JP 0x004a2bf0, US 0x004c2d30): when the attacker's current PATK2 hit row is class 0x16, every
//! `MosEvent` key fires a bullet from row `k` of the bullet table `PATK +0x14` (`atck`: the swing's hit counter; the reaction motions
//! `blwa` / `flya` / `koda` / `key2..4`: `PATK hits * PATK +0x16 + 0 / 1 / 2 / 3.. / 5.. / 8..`).  The damage lands when the bullet hits
//! (`Bullet1::Polling` -> `PAtkHitSet`, once per bullet with the swing's event counter at the shot and the bullet's damage scale), so the port
//! holds the attack (`BattleRuntime::bullet_hold` -> `anim_hold`) until the volley is over and applies each impact as its own hit
//! ([`crate::flow::Battle::ranged_hit`]; `do_attack` then only closes the action).  US data: monsters 83 / 85 / 86 / 88 / 89 / 102 / 103 / 105 / 123..125 / 208 / 209 / 213 (tables 0 / 1
//! / 5) and PATK 8 (table 2) shoot `Bullet1`s; table 6 (monster 172) fires `Bullet4`s, Yuri's fusions 13 / 14 (`FUSM +6` = PATK 29 / 30,
//! tables 3 / 7) `Bullet2`s and fusions 4 / 5 (PATK 20 / 21, tables 4 / 8) `Bullet3` streams (kind 1 / 3 / 2 of the row).  `Bullet2..4` start at
//! the centre of a BBox (or between two, or one per BBox of a paired row: [`blt::emit_points`]) and are drawn as camera sprites of BTL_000
//! textures (US 30 / 35, JP 48 / 53) plus `Bullet4`'s tube trail.

use std::collections::HashMap;

use bevy::prelude::*;
use sh2_gfx::bevy::model::AnimatedModel;
use sh2_gfx::bevy::{Sh2Disc, Sh2Material};
use sh2_gfx::effects::bullet::{self as blt, Bullet1, Bullet2, Bullet3, Bullet4, BulletRow, HitBox, ModelBoxIn};

use crate::effects_bridge::{bevy_to_ps2, frame_world, is_attack_motion, EffMdlQueue, EffMdlReq};
use crate::flow::Phase;
use crate::models::BattleModel;
use crate::plugin::BattleRuntime;

/// One projectile of [`blt`]: `Bullet1` .. `Bullet4` (row kind 0 .. 3).
enum Shot {
    B1(Bullet1),
    B2(Box<Bullet2>),
    /// the stream and its row / sub-bullet (the muzzle follows the attacker's BBox while it emits)
    B3(Bullet3, BulletRow, u8),
    B4(Box<Bullet4>),
}

impl Shot {
    fn scale(&self) -> f32 {
        match self {
            Shot::B1(b) => b.scale,
            Shot::B2(b) => b.scale,
            Shot::B3(b, ..) => b.scale,
            Shot::B4(b) => b.scale,
        }
    }
    /// still able to hit (the hold waits for these)
    fn in_flight(&self) -> bool {
        match self {
            Shot::B1(b) => !b.hit,
            Shot::B2(b) => !b.hit && !b.gone,
            Shot::B3(b, ..) => !b.hit && !b.finished(),
            Shot::B4(b) => !b.hit && !b.gone,
        }
    }
    /// nothing left to draw
    fn finished(&self) -> bool {
        match self {
            Shot::B1(_) => false,
            Shot::B2(b) => b.finished(),
            Shot::B3(b, ..) => b.finished(),
            Shot::B4(b) => b.finished(),
        }
    }
}

/// What a shot of the held attack hands to `PAtkHitSet` when it hits (the `Bullet1` fields `+0xa0..+0xb2`).
#[derive(Clone, Copy, Debug, PartialEq)]
struct ShotHit {
    /// event counter at the shot (`BtlChr+0x314`)
    n: i32,
    /// `PATK +1` hit groups
    groups: i32,
    /// `PATK +0x16` shots per group
    per: i32,
    /// `BtlChr+0x320 / +0x322` at the shot = `+0x44 / +0x46` of the PATK2 row in force: the target's push time / power
    push: (u16, u16),
}

struct BulletRun {
    owner: usize,
    target: Option<usize>,
    b: Shot,
    /// a shot of the held attack
    hit: Option<ShotHit>,
}

/// The target's hit box for the bullets (`VSCircleHitCheck`): the retail box from the corners of the model's own body BBoxes in their current pose
/// ([`HitBox::of_model`]), else the radius / height box.  `None` for a fighter that is gone (`BattleModel` and fighter slot).
pub(crate) fn target_box(rt: &BattleRuntime, models: &Query<&BattleModel>, anims: &Query<&AnimatedModel>, gts: &Query<&GlobalTransform>, t: usize) -> Option<HitBox> {
    // a knocked-out target still stops the bullet (`Bullet1::Polling` tests the box first, `PAtkHitSet` only when `nHp > 0`)
    rt.battle.fighters.get(t)?.as_ref()?;
    let m = models.iter().find(|m| m.chr == t);
    let feet = bevy_to_ps2(m.map(|m| m.pos).or_else(|| rt.positions.get(t).copied())?);
    // the model's yaw about Bevy +y is the negative PS2 yaw
    let yaw = -m.map(|m| m.yaw).unwrap_or(0.0);
    if let Some(m) = m.filter(|m| !m.hurt.is_empty()) {
        if let (Ok(am), Ok(gt)) = (anims.get(m.holder), gts.get(m.holder)) {
            let mut corners = vec![];
            for &bi in &m.hurt {
                let Some(b) = am.inst.model.bounds.get(bi) else { continue };
                let Some(fw) = frame_world(am, gt, (b.tag & 0xff) as usize) else { continue };
                corners.extend(b.corners.iter().map(|c| fw.transform_point3(Vec3::new(c.x, c.y, c.z))));
            }
            let cb = rt.boxes.get(t).copied().flatten();
            let v = |a: [f32; 3]| Vec3::new(a[0], a[1], a[2]);
            let inp = ModelBoxIn {
                feet,
                yaw,
                corners: &corners,
                chr_off: cb.map(|b| v(b.off)).unwrap_or(Vec3::ZERO),
                chr_size: cb.map(|b| v(b.size)).unwrap_or(Vec3::ZERO),
                airborne: m.ch.airborne(),
            };
            if let Some(b) = HitBox::of_model(&inp) {
                return Some(b);
            }
        }
    }
    let (r, h) = rt.dims.get(t).copied().unwrap_or((10.0, 30.0));
    Some(HitBox::of_fighter(feet, r, h, yaw))
}

/// World point of BBox `bbox` of a model (`Bullet2..4` constructors): `local` in the BBox's frame, or (`None`) the mean of its 8 corners
/// transformed by that frame.
fn bbox_point(am: &AnimatedModel, gt: &GlobalTransform, bbox: i16, local: Option<Vec3>) -> Option<Vec3> {
    let b = am.inst.model.bounds.get(bbox.max(0) as usize)?;
    let fw = frame_world(am, gt, (b.tag & 0xff) as usize)?;
    Some(match local {
        Some(l) => fw.transform_point3(l),
        None => b.corners.iter().map(|c| fw.transform_point3(Vec3::new(c.x, c.y, c.z))).sum::<Vec3>() / 8.0,
    })
}

/// The model a bullet row is anchored to (`row.source`: 0 body, 1 right weapon, 2 left weapon).
fn source_model<'a>(
    m: &BattleModel,
    source: i16,
    body: (&'a AnimatedModel, &'a GlobalTransform),
    anims: &'a Query<&AnimatedModel>,
    gts: &'a Query<&GlobalTransform>,
    mounts: &Query<&crate::models::WeaponMount>,
) -> Option<(&'a AnimatedModel, &'a GlobalTransform)> {
    if source == 0 {
        return Some(body);
    }
    let slot = if source == 1 { crate::models::WeaponSlot::Right } else { crate::models::WeaponSlot::Left };
    let w = m.weapons.iter().find(|w| mounts.get(**w).map(|mm| mm.slot == slot).unwrap_or(false))?;
    Some((anims.get(*w).ok()?, gts.get(*w).ok()?))
}

/// The battle's projectiles and the attack that waits for its volley.
#[derive(Resource, Default)]
pub struct Bullets {
    loaded: bool,
    table: Vec<Vec<BulletRow>>,
    live: Vec<BulletRun>,
    /// per fighter: (motion, frame) of the last update, for the `MosEvent` crossings
    last: HashMap<usize, (String, f32)>,
    /// the attack being held: (attacker, seconds held, a bullet was fired)
    hold: Option<(usize, f32, bool)>,
    /// the attacker of the `Phase::Attack` the hold was armed for (once per attack)
    armed_for: Option<usize>,
    mat: Option<Handle<Sh2Material>>,
    mesh: Option<(Entity, Handle<Mesh>)>,
    /// `Bullet2` / `Bullet4` heads and sparks (BTL_000 tex US 30), `Bullet3Child` puffs (tex US 35), `Bullet4` tubes (the tracer material)
    tex_mats: Option<[Option<Handle<Sh2Material>>; 2]>,
    sprite_mesh: [Option<(Entity, Handle<Mesh>)>; 2],
    tube_mesh: Option<(Entity, Handle<Mesh>)>,
    /// `rand()` of the sparks / puffs
    rng: u32,
    /// `SH2_BULLET_SHOTS` frame counter
    shots: u32,
    /// per attacker: the target of its attack, kept while the attack motion plays (`BtlChr+0xbc`: the later shots of a volley fire after
    /// the hit has resolved and the battle has left `Phase::Attack`)
    aim: HashMap<usize, usize>,
}

/// Whether the attack's hold ends: the volley is over (a shot fired, no `MosEvent` ahead, none of its bullets in flight), the attack is over, or the swing
/// has run 8 s (2.5 s without a shot).  `t` = seconds since the swing began.
pub fn hold_over(t: f32, fired: bool, more: bool, flying: bool, still_attacking: bool) -> bool {
    (fired && !more && !flying) || !still_attacking || t > 8.0 || (!fired && t > 2.5)
}

/// The hit group (row of the PATK2 hit rows) the `g`-th `MosEvent` of a swing with `keys_total` keys belongs to: the keys are spread evenly over the groups.
pub fn group_of(g: usize, keys_total: usize, groups: usize) -> usize {
    let per = (keys_total.max(1) + groups.max(1) - 1) / groups.max(1);
    g / per.max(1)
}

/// Row of the bullet table for the `g`-th `MosEvent` of `motion` (`None`: not a bullet row).
pub fn bullet_row(motion: &str, g: usize, keys_total: usize, hits: usize, patk16: i32, rows_bullet: &[bool]) -> Option<usize> {
    let nh = hits as i32 * patk16;
    let row = match motion {
        "blwa" => nh,
        "flya" => nh + 1,
        "koda" => nh + 2,
        "key2" => nh + 3 + g as i32,
        "key3" => nh + 5 + g as i32,
        "key4" => nh + 8 + g as i32,
        _ => {
            // the `MosEvent`s of a swing are spread over its hit groups (CHR 191 `atck`: 15 keys, 5 groups); the class 0x16 test is the
            // group's PATK2 row (`BtlChr+0x450`), the bullet row the swing's event counter
            if !rows_bullet.get(group_of(g, keys_total, rows_bullet.len())).copied().unwrap_or(false) {
                return None;
            }
            g as i32
        }
    };
    (row >= 0).then_some(row as usize)
}

/// Spawn, fly, hit and draw the bullets of the ranged attacks; every impact of the held attack is one hit, the hold lasts until the volley is over.
#[allow(clippy::too_many_arguments)]
pub fn drive_bullets(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    db: Option<Res<crate::plugin::BattleDb>>,
    disc: Option<Res<Sh2Disc>>,
    mut bl: ResMut<Bullets>,
    mut effq: ResMut<EffMdlQueue>,
    models: Query<&BattleModel>,
    anims: Query<&AnimatedModel>,
    gts: Query<&GlobalTransform>,
    mounts: Query<&crate::models::WeaponMount>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<Sh2Material>>,
    time: Res<Time>,
    (cams, mut images): (Query<&GlobalTransform, With<crate::plugin::BattleCamera>>, ResMut<Assets<Image>>),
) {
    let (Some(mut rt), Some(db), Some(disc)) = (rt, db, disc) else { return };
    let bl: &mut Bullets = &mut bl;
    if !bl.loaded {
        bl.loaded = true;
        if let Ok(b) = disc.read("BATTLE.BIN") {
            bl.table = blt::bullet_table(&b, sh2_core::boot::is_retail());
        }
        log::info!("battle: bullets: {} tables", bl.table.len());
    }
    let dt = time.delta_secs().min(0.1);
    // `CBattle+0x3f14 / +0x3f1c` (the stage's DAT x / z minus 10; the bullets leave at `(+ 10) / 2`)
    let arena = Some((rt.battle.arena[0], rt.battle.arena[1])).filter(|(w, d)| *w > 20.0 && *d > 20.0).unwrap_or((400.0, 400.0));
    // the target's box (`VSCircleHitCheck`), PS2 world
    let hitbox = |rt: &BattleRuntime, t: usize| target_box(rt, &models, &anims, &gts, t);
    let attacker = if rt.battle.phase == Phase::Attack { rt.battle.actor } else { None };
    if attacker.is_none() {
        bl.armed_for = None;
    }
    let target = attacker.and(Some(rt.battle.cmd.p48)).filter(|t| *t >= 0).map(|t| t as usize);
    // the held attacker's swing still has `MosEvent`s ahead (more shots to come)
    let mut more = false;
    for m in &models {
        let chr = m.chr;
        let Some(f) = rt.battle.fighters.get(chr).and_then(|f| f.as_ref()) else { continue };
        let pc = rt.setup.pc_ids.get(chr).copied().flatten();
        // the `PATK` record of the fighter's attack (`nAtkTbl`: the monster's attack table / the PC id / `FUSM +6` while fused) and its PATK2 hit rows
        let fused = rt.battle.fused.get(chr).and_then(|s| s.as_ref()).map(|s| s.id);
        let patk_idx = crate::models::patk_index(&db, f, pc, fused);
        let Some(patk) = patk_idx.and_then(|i| db.0.dat.record(23, i, 0x18)) else { continue };
        let hits = patk[1].max(1) as usize;
        let base = u16::from_le_bytes([patk[0xc], patk[0xd]]) as usize;
        let tbl_no = i16::from_le_bytes([patk[0x14], patk[0x15]]);
        let p16 = i16::from_le_bytes([patk[0x16], patk[0x17]]) as i32;
        let rows_bullet: Vec<bool> = (0..hits.min(16)).map(|g| db.0.dat.record(24, base + g, 0x48).map(|r| r[1] == 0x16).unwrap_or(false)).collect();
        if tbl_no < 0 || !rows_bullet.iter().any(|b| *b) {
            continue;
        }
        let Some(table) = bl.table.get(tbl_no as usize).cloned() else { continue };
        // arm the hold when this fighter's attack starts (its run-up / telegraph come long before the first `MosEvent`)
        if attacker == Some(chr) && bl.armed_for != Some(chr) {
            bl.armed_for = Some(chr);
            if !table.is_empty() {
                bl.hold = Some((chr, 0.0, false));
            }
        }
        let (Ok(am), Ok(gt)) = (anims.get(m.holder), gts.get(m.holder)) else { continue };
        let Some(cur) = am.current.clone() else { continue };
        let Some(motion) = am.motions.iter().find(|mm| mm.name == cur) else { continue };
        let frame = am.inst.time() * motion.fps.max(1) as f32;
        let prev = match bl.last.get(&chr) {
            Some((name, fr)) if *name == cur && *fr <= frame => *fr,
            _ => -1.0,
        };
        bl.last.insert(chr, (cur.clone(), frame));
        if attacker == Some(chr) {
            if let Some(t) = target {
                bl.aim.insert(chr, t);
            }
        }
        if !is_attack_motion(&cur) && !matches!(cur.as_str(), "blwa" | "flya" | "koda" | "key2" | "key3" | "key4") {
            if attacker != Some(chr) {
                bl.aim.remove(&chr);
            }
            continue;
        }
        let keys: Vec<f32> = motion.events.iter().filter(|e| e.base_name() == "MosEvent").flat_map(|e| e.keys()).map(|k| k.time as f32).collect();
        let held = bl.hold.is_some_and(|h| h.0 == chr) && attacker == Some(chr);
        if held {
            more |= keys.iter().any(|&k| k > frame);
        }
        for (g, &k) in keys.iter().enumerate() {
            if !(prev < k && k <= frame) {
                continue;
            }
            let Some(row) = bullet_row(&cur, g, keys.len(), hits, p16, &rows_bullet) else { continue };
            let Some(r) = table.get(row).copied() else { continue };
            // the source model: body / right / left weapon
            let Some((sa, sg)) = source_model(m, r.source, (am, gt), &anims, &gts, &mounts) else { continue };
            // `Bullet1`: the row's offset in the frame of BBox `r.bbox`; `Bullet2..4`: [`blt::emit_points`] (one per sub-bullet)
            let (count, scale) = if r.pair < 0 { (1u8, 1.0) } else { (2, 0.5) };
            let starts: Vec<(Vec3, Vec3)> = if r.kind == 0 {
                let Some(m0) = bbox_point(sa, sg, r.bbox, Some(r.offset)) else { continue };
                let Some(m1) = bbox_point(sa, sg, r.bbox, Some(r.offset + r.dir)) else { continue };
                vec![(m0, m1 - m0); count as usize]
            } else {
                (0..count).filter_map(|sub| blt::emit_points(&r, sub, &|b, l| bbox_point(sa, sg, b, l)).map(|(p, e)| (p, e.map(|e| e - p).unwrap_or(Vec3::ZERO)))).collect()
            };
            let tgt = bl.aim.get(&chr).copied();
            let tb = tgt.and_then(|t| hitbox(&rt, t));
            // the shots of the held attack deal its damage, one hit each; the push words are those of the PATK2 row of the shot's hit group
            let grp = group_of(g, keys.len(), rows_bullet.len()).min(hits - 1);
            let push = db.0.dat.record(24, base + grp, 0x48).map(|r| (u16::from_le_bytes([r[0x44], r[0x45]]), u16::from_le_bytes([r[0x46], r[0x47]]))).unwrap_or((0, 0));
            let hit = held.then_some(ShotHit { n: g as i32, groups: hits as i32, per: p16, push });
            for (sub, &(muzzle, barrel)) in starts.iter().enumerate() {
                // the attacker's facing (`BtlChr+0xc4`): a shooter turns to its target before firing, so the yaw of the line muzzle -> target
                // (the barrel's yaw without a target); the slot facing `m.facing` is wrong once the attacker has moved
                let yaw = match tb {
                    Some(t) => blt::aim((t.centre - muzzle).with_y(0.0)).1,
                    None => blt::aim(barrel.with_y(0.0)).1,
                };
                let aim_at = tb.map(|t| t.centre);
                let b = match r.kind {
                    0 => Shot::B1(Bullet1::new(muzzle, aim_at, yaw, scale)),
                    1 => Shot::B2(Box::new(Bullet2::new(muzzle, aim_at, yaw, scale))),
                    2 => Shot::B3(Bullet3::new(scale), r, sub as u8),
                    _ => Shot::B4(Box::new(Bullet4::new(muzzle, aim_at, yaw, scale))),
                };
                bl.live.push(BulletRun { owner: chr, target: tgt, b, hit });
            }
            if starts.is_empty() {
                continue;
            }
            if held {
                rt.battle.begin_ranged();
            }
            if let Some(h) = bl.hold.as_mut().filter(|h| h.0 == chr) {
                h.2 = true;
            }
            if r.kind == 0 {
                // the muzzle flash (`EffMdl(BTL_001 0x16, 0x17, 1.0, -1, 6)`, `bef_1`, turned along the barrel; `Bullet2..4` have none)
                let (muzzle, barrel) = starts[0];
                let (p, y) = blt::aim(barrel);
                effq.push(EffMdlReq { kind: 6, angle: Vec3::new(p.to_radians(), y.to_radians(), 0.0), ..EffMdlReq::new(0x16, 0x17, "bef_1", muzzle) });
            }
            log::debug!("battle: fighter {chr} fires Bullet{} x{} (table {tbl_no} row {row}) at {tgt:?} from {:?}", r.kind + 1, starts.len(), starts[0].0);
        }
    }
    // ---- flight
    let mut keep = vec![];
    let mut rng = bl.rng.max(1);
    let mut rand01 = move || {
        rng = rng.wrapping_mul(1_103_515_245).wrapping_add(12345);
        (rng >> 8) as f32 / (1u32 << 24) as f32
    };
    for mut run in std::mem::take(&mut bl.live) {
        let tb = run.target.and_then(|t| hitbox(&rt, t));
        let was_flying = run.b.in_flight();
        let step = match &mut run.b {
            Shot::B1(b) => b.step(dt, tb.as_ref(), arena),
            Shot::B2(b) => b.step(dt, tb.as_ref(), arena, &mut rand01),
            Shot::B4(b) => b.step(dt, tb.as_ref(), arena),
            Shot::B3(b, r, sub) => {
                // the stream follows the muzzle (`Bullet3::Polling` constructs each child at the current BBox frame)
                let emit = if b.age < blt::B3_EMIT {
                    models.iter().find(|m| m.chr == run.owner).and_then(|m| {
                        let body = (anims.get(m.holder).ok()?, gts.get(m.holder).ok()?);
                        let (sa, sg) = source_model(m, r.source, body, &anims, &gts, &mounts)?;
                        let (p, e) = blt::emit_points(r, *sub, &|bb, l| bbox_point(sa, sg, bb, l))?;
                        Some((p, e.unwrap_or(p + Vec3::NEG_Z)))
                    })
                } else {
                    None
                };
                b.step(dt, emit, tb.as_ref(), arena, &mut rand01)
            }
        };
        let scale = run.b.scale();
        match step {
            blt::Step::Flying => keep.push(run),
            blt::Step::Hit(p) => {
                // `PAtkHitSet` (only while the target has HP; the flow checks it)
                let counted = match (run.hit, run.target) {
                    (Some(h), Some(t)) => rt.battle.ranged_hit(t, h.n, h.groups, h.per, scale, h.push),
                    _ => false,
                };
                log::debug!("battle: bullet of {} hits {:?} at {p:?} (damage scale {scale}, hit {:?} counted {counted})", run.owner, run.target, run.hit);
                keep.push(run);
            }
            blt::Step::Gone => {
                if was_flying {
                    log::debug!("battle: bullet of {} gone without a hit, target box {:?}", run.owner, tb);
                }
                // `Bullet2..4` keep fading out (sparks / trail / puffs) after they stopped
                if !matches!(run.b, Shot::B1(_)) && !run.b.finished() {
                    keep.push(run);
                }
            }
        }
    }
    bl.rng = (rand01() * 16_777_216.0) as u32 | 1;
    bl.live = keep;
    bl.live.retain(|r| !r.b.finished());
    // ---- the hold ends when the volley is over (shots fired, no `MosEvent` ahead, none of them in flight), when the attack is over, or
    // after 8 s (2.5 s without a shot) of the swing: its clock starts with the swing, not with the command (a party member's Judgement Ring takes as
    // long as the player needs, an enemy telegraphs first)
    if let Some((chr, t, fired)) = bl.hold.as_mut() {
        let enemy = rt.setup.fighters.get(*chr).map(|f| f.is_enemy).unwrap_or(true);
        if if enemy { rt.attack_started } else { rt.ring_done && rt.ring.is_none() } {
            *t += dt;
        }
        let flying = bl.live.iter().any(|r| r.owner == *chr && r.hit.is_some() && r.b.in_flight());
        if hold_over(*t, *fired, more, flying, attacker == Some(*chr)) {
            bl.hold = None;
        }
    }
    rt.bullet_hold = bl.hold.is_some();
    if rt.bullet_hold {
        // each bullet's number / burst / reaction shows on its impact, not on the swing's hit frames
        rt.hit_offsets.clear();
    }
    // development: `SH2_BULLET_SHOTS=<dir>` photographs every 4th frame while a bullet flies (`bullet_<n>.png`, at most 40)
    if let Some(dir) = std::env::var_os("SH2_BULLET_SHOTS").map(std::path::PathBuf::from) {
        if bl.live.iter().any(|r| r.b.in_flight()) {
            bl.shots += 1;
            if bl.shots % 4 == 1 && bl.shots / 4 < 40 {
                let _ = std::fs::create_dir_all(&dir);
                let path = dir.join(format!("bullet_{:03}.png", bl.shots / 4));
                commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(path));
            }
        }
    }
    // ---- tracers (`Bullet1::MakePacket`: one additive Gouraud line, head at the new position)
    if bl.mat.is_none() {
        bl.mat = Some(mats.add(Sh2Material::textured(None).with_blend(sh2_gfx::bevy::Sh2Blend::Add, None).with_fog(false)));
    }
    let c = |rgba: [u8; 4]| rgba.map(|v| v as f32 / 128.0);
    let mut pos: Vec<[f32; 3]> = vec![];
    let mut col: Vec<[f32; 4]> = vec![];
    for b in bl.live.iter().filter_map(|r| if let Shot::B1(b) = &r.b { Some(b) } else { None }).filter(|b| !b.hit) {
        pos.push(b.pos.to_array());
        col.push(c(blt::HEAD_RGBA));
        pos.push(b.prev.to_array());
        col.push(c(blt::TAIL_RGBA));
    }
    if pos.is_empty() {
        // no empty vertex buffers (see the sword trails)
        pos = vec![[0.0; 3]; 2];
        col = vec![[0.0; 4]; 2];
    }
    let uv = vec![[0.0f32; 2]; pos.len()];
    let mut mesh = Mesh::new(bevy::mesh::PrimitiveTopology::LineList, bevy::asset::RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    match &bl.mesh {
        Some((e, h)) if commands.get_entity(*e).is_ok() => {
            if let Some(mut mm) = meshes.get_mut(h) {
                *mm = mesh;
            }
        }
        _ => {
            // a new battle: forget the last one's bullets
            bl.live.clear();
            bl.last.clear();
            bl.aim.clear();
            bl.hold = None;
            let h = meshes.add(mesh);
            let mat = bl.mat.clone().unwrap();
            // authored in PS2 world: the transform turns it into Bevy space like the weapon trails' root
            let e = commands
                .spawn((
                    Name::new("bullet_tracers"),
                    Mesh3d(h.clone()),
                    MeshMaterial3d(mat),
                    Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)),
                    Visibility::default(),
                    bevy::camera::visibility::NoFrustumCulling,
                    DespawnOnExit(sh2_core::game::Scene::Battle),
                ))
                .id();
            bl.mesh = Some((e, h));
        }
    }
    draw_glows(&mut commands, bl, &disc, cams.iter().next(), &mut meshes, &mut mats, &mut images);
}

/// A PS2-world mesh under the battle's x-180 root (like the tracers), rebuilt every frame; spawned again when its entity is gone.
#[allow(clippy::too_many_arguments)]
fn upload(
    commands: &mut Commands,
    meshes: &mut Assets<Mesh>,
    slot: &mut Option<(Entity, Handle<Mesh>)>,
    mat: &Handle<Sh2Material>,
    name: &'static str,
    mut pos: Vec<[f32; 3]>,
    mut col: Vec<[f32; 4]>,
    mut uv: Vec<[f32; 2]>,
) {
    if pos.is_empty() {
        // no empty vertex buffers
        pos = vec![[0.0; 3]; 3];
        col = vec![[0.0; 4]; 3];
        uv = vec![[0.0; 2]; 3];
    }
    let mut mesh = Mesh::new(bevy::mesh::PrimitiveTopology::TriangleList, bevy::asset::RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    match slot {
        Some((e, h)) if commands.get_entity(*e).is_ok() => {
            if let Some(mut mm) = meshes.get_mut(&*h) {
                *mm = mesh;
            }
        }
        _ => {
            let h = meshes.add(mesh);
            let e = commands
                .spawn((
                    Name::new(name),
                    Mesh3d(h.clone()),
                    MeshMaterial3d(mat.clone()),
                    Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)),
                    Visibility::default(),
                    bevy::camera::visibility::NoFrustumCulling,
                    DespawnOnExit(sh2_core::game::Scene::Battle),
                ))
                .id();
            *slot = Some((e, h));
        }
    }
}

/// `Bullet2` / `Bullet3Child` / `Bullet4` `MakePacket`: camera-facing textured quads (`PRIM 0x154` strips, `ALPHA_1 0x48` additive, depth tested,
/// corner UVs = the whole texture) and `Bullet4`'s tube (`PRIM 0x4c`, untextured Gouraud strips).  The quads' corners are the camera's
/// right / down axes (the `GsxCamera+0x240` rows of the original), PS2 world.
fn draw_glows(
    commands: &mut Commands,
    bl: &mut Bullets,
    disc: &Sh2Disc,
    cam: Option<&GlobalTransform>,
    meshes: &mut Assets<Mesh>,
    mats: &mut Assets<Sh2Material>,
    images: &mut Assets<Image>,
) {
    if bl.tex_mats.is_none() {
        // BTL_000 tex: US `CBattle+0x44fc` / `+0x4510` (JRCTex array at +0x4484: 30 / 35), JP `+0x42e4` / `+0x42f8` (array at +0x4224: 48 / 53)
        let ks = if sh2_core::boot::is_retail() { [30usize, 35] } else { [48, 53] };
        let bin = disc.read("BTLDATA/BTL_000.BIN").unwrap_or_default();
        let secs = crate::stage::sections(&bin);
        bl.tex_mats = Some(ks.map(|k| {
            let (tag, sec) = secs.get(k)?;
            if tag != "tex" {
                return None;
            }
            let i = sh2_gfx::texture::decode_jrc(sec, 0, 0).ok()?;
            let img = images.add(sh2_gfx::bevy::image::rgba_image(i.width, i.height, i.pixels, sh2_gfx::bevy::TexFilter::Linear));
            Some(mats.add(Sh2Material::textured(Some(img)).with_lit(false).with_fog(false).with_blend(sh2_gfx::bevy::Sh2Blend::Add, None)))
        }));
        log::info!("battle: Bullet2..4 textures {:?}", bl.tex_mats.as_ref().map(|t| t.each_ref().map(|m| m.is_some())));
    }
    if bl.live.iter().all(|r| matches!(r.b, Shot::B1(_))) && bl.sprite_mesh.iter().all(|s| s.is_none()) && bl.tube_mesh.is_none() {
        return;
    }
    // camera right / down in PS2 world (the root's x-180 turn: (x, y, z) -> (x, -y, -z))
    let (right, down) = cam
        .map(|gt| {
            let r = gt.right().as_vec3();
            let u = gt.up().as_vec3();
            (Vec3::new(r.x, -r.y, -r.z), Vec3::new(-u.x, u.y, u.z))
        })
        .unwrap_or((Vec3::X, Vec3::Y));
    // (pos, col, uv) per mesh: [tex 30 sprites, tex 35 sprites]
    let mut sp: [(Vec<[f32; 3]>, Vec<[f32; 4]>, Vec<[f32; 2]>); 2] = Default::default();
    let mut quad = |k: usize, c: Vec3, half: f32, roll: f32, rgba: [f32; 4]| {
        let (s, co) = roll.sin_cos();
        let corner = |x: f32, y: f32| c + (right * (x * co - y * s) + down * (x * s + y * co)) * half;
        let v = [(-1.0f32, -1.0f32, [0.0f32, 0.0f32]), (-1.0, 1.0, [0.0, 1.0]), (1.0, -1.0, [1.0, 0.0]), (1.0, 1.0, [1.0, 1.0])];
        for i in [0usize, 1, 2, 1, 3, 2] {
            let (x, y, uv) = v[i];
            sp[k].0.push(corner(x, y).to_array());
            sp[k].1.push(rgba);
            sp[k].2.push(uv);
        }
    };
    let g = |v: u8| v as f32 / 128.0;
    let mut tube: (Vec<[f32; 3]>, Vec<[f32; 4]>) = Default::default();
    for run in &bl.live {
        match &run.b {
            Shot::B1(_) => {}
            Shot::B2(b) => {
                if !b.gone {
                    quad(0, b.pos, 5.0, 0.0, [1.0; 4]);
                }
                for s in b.sparks.iter().filter(|s| s.live) {
                    quad(0, s.pos, 2.0 * s.fade(), 0.0, [1.0, 1.0, 1.0, s.fade()]);
                }
            }
            Shot::B3(b, ..) => {
                for c in &b.children {
                    let [r, gg, bb] = blt::B3_RGB;
                    quad(1, c.pos, c.half(), c.roll, [g(r), g(gg), g(bb), c.alpha() / 128.0]);
                }
            }
            Shot::B4(b) => {
                if !b.gone {
                    let [r, gg, bb, a] = blt::B4_HEAD_RGBA;
                    quad(0, b.pos(), 5.0, 0.0, [g(r), g(gg), g(bb), g(a)]);
                }
                let t = b.tube();
                // untextured: GS colour 0xff = 1.0, alpha 0x80 = 1.0
                let rgb = blt::B4_TUBE_RGB.map(|v| v as f32 / 255.0);
                for w in t.windows(2) {
                    let ((r0, a0), (r1, a1)) = (&w[0], &w[1]);
                    for k in 0..3 {
                        let k2 = (k + 1) % 3;
                        for (p, a) in [(r0[k], *a0), (r0[k2], *a0), (r1[k], *a1), (r0[k2], *a0), (r1[k2], *a1), (r1[k], *a1)] {
                            tube.0.push(p.to_array());
                            tube.1.push([rgb[0], rgb[1], rgb[2], a / 128.0]);
                        }
                    }
                }
            }
        }
    }
    let tex_mats = bl.tex_mats.clone().unwrap_or_default();
    for (k, (pos, col, uv)) in sp.into_iter().enumerate() {
        if let Some(mat) = &tex_mats[k] {
            upload(commands, meshes, &mut bl.sprite_mesh[k], mat, ["bullet_glows", "bullet_puffs"][k], pos, col, uv);
        }
    }
    if let Some(mat) = bl.mat.clone() {
        let uv = vec![[0.0f32; 2]; tube.0.len()];
        upload(commands, meshes, &mut bl.tube_mesh, &mat, "bullet_tubes", tube.0, tube.1, uv);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_hold_waits_for_the_volley_and_gives_up_on_a_dead_swing() {
        // a swing that has not shot yet is waited for 2.5 s, one that is shooting 8 s
        assert!(!hold_over(2.4, false, true, false, true));
        assert!(hold_over(2.6, false, true, false, true));
        assert!(!hold_over(7.9, true, true, false, true));
        assert!(hold_over(8.1, true, true, true, true));
        // over once everything is fired and landed, or the attack ended
        assert!(hold_over(1.0, true, false, false, true));
        assert!(!hold_over(1.0, true, false, true, true), "a bullet still flies");
        assert!(hold_over(0.0, false, true, false, false));
    }

    #[test]
    fn keys_spread_over_the_hit_groups() {
        // CHR 191: 15 keys, 5 groups of 3
        let groups: Vec<usize> = (0..15).map(|g| group_of(g, 15, 5)).collect();
        assert_eq!(groups, vec![0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4]);
        // an uneven spread rounds the group size up, no group beyond the last row
        assert_eq!(group_of(6, 7, 3), 2);
        assert_eq!(group_of(0, 0, 0), 0);
    }

    #[test]
    fn rows_follow_the_motion_event_callback() {
        let rows = [true, false, true];
        assert_eq!(bullet_row("atck", 0, 3, 3, 1, &rows), Some(0));
        assert_eq!(bullet_row("atck", 1, 3, 3, 1, &rows), None);
        assert_eq!(bullet_row("atck", 2, 3, 3, 1, &rows), Some(2));
        // CHR 191: 15 keys over 5 bullet groups -> rows 0..14
        let five = [true; 5];
        assert_eq!((0..15).filter_map(|g| bullet_row("atck", g, 15, 5, 1, &five)).collect::<Vec<_>>(), (0..15).collect::<Vec<_>>());
        // reaction motions: PATK hits * PATK +0x16 + c
        assert_eq!(bullet_row("flya", 0, 1, 5, 1, &rows), Some(6));
        assert_eq!(bullet_row("key3", 1, 2, 5, 1, &rows), Some(11));
    }
}

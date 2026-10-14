//! Battle formations: port of `CBattle::BtlChrPosInit(bool reset)` (JP BATTLE.BIN 0x004ab590, US 0x004cb920; `decomp/H/CBattle.c` line 31093).
//!
//! `BtlChrPosInit(true)` places the *party* (`reset`), `BtlChrPosInit(false)` the *enemies*; the two sides stand on the z axis of the stage (PS2 world,
//! the party at negative z facing +z (yaw 180), the enemies at positive z facing -z (yaw 0)), side by side along x, **packed by their bounding radii**
//! (`BtlChr+0x3b0` = `(box.size.x + box.size.z) / 2`, the first record of the `bbx` section of the model package; see [`ChrBox`]).
//!
//! * `zb = -(arena_z_dat / 10)` (`-((CBattle+0x3f1c + 10) / 10)`, `+0x3f1c` = BBG `DAT` z - 10): the **party row** stands at `zb - 15 - max radius`, the
//!   **enemy rows** at `zb + 15 + ...` (the first row `+ max radius`, a second row `2 * max radius + 12` further back, ...).
//! * Party (`+0xbc` = 0, 1, 3, 6 for 1, 2, 3, 4 members): 1 -> x = 0; 2 -> `+(R0 + 6)`, `-(R1 + 6)`; 3 -> `R0 + R1 + 12`, 0, `-(R1 + 12 + R2)`;
//!   4 -> `R0 + 2 R1 + 18`, `R1 + 6`, `-(R2 + 6)`, `-(2 R2 + 18 + R3)`.
//! * Enemies: the MONSET `formation` id (0..0x13) chooses the rows (1, 2, 3 ... 6 monsters, see [`monster_count`]); most ids pick one of several spreads at random
//!   (`rand() % 100` against 50 % / 25 % ... thresholds, always the tight one when `bNoEvade`); the wide variants are clamped to the arena (`|x| <= (DAT x - 10) / 2 - R`).
//!   Ids 0..6, 0xf..0x13 are ported with all variants; 7..0xe keep their rows but only the tight variant (documented gap: the wide spreads of 4 / 5 / 6 monster rows).
//! * Ambush (`bFlags24 >> 3` = 1 / 2): the surrounded side stands in the middle (2 -> `+-(max R + 6)`, more -> a ring `sum(2 R + 12) / 2 pi * 1.2`), the surrounding side on a
//!   circle around them (radius `ring + max R`, facing the middle).
//! * The final position is `home - Rot_y(yaw) * (box.off.x, box.off.z)` (`+0x390`), i.e. the box centre, not the feet, stands on the formation slot.
//!
//! Everything here works in PS2 `(x, z)`; [`to_bevy`] converts to the Bevy world (`z` flips).

use crate::rules::Ambush;

/// First record of the model package's `bbx` section (`BtlChr+0x390 / 0x3a0 / 0x3b0 / 0x3b4`).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct ChrBox {
    /// box centre (model space, PS2 y down) `+0x18 / +0x1c / +0x20`
    pub off: [f32; 3],
    /// box size `+0x24 / +0x28 / +0x2c`
    pub size: [f32; 3],
}

impl ChrBox {
    /// `BtlChr+0x3b0`: `(size.x + size.z) / 2` (`FUN` at CBattle.c:19135).
    pub fn radius(&self) -> f32 {
        (self.size[0] + self.size[2]) * 0.5
    }
    /// `|BtlChr+0x3a0|` as the camera uses it: the length of the size vector.
    pub fn size_len(&self) -> f32 {
        (self.size[0] * self.size[0] + self.size[1] * self.size[1] + self.size[2] * self.size[2]).sqrt()
    }
    /// Height of the box top above the feet (`-(off.y) + size.y`, PS2 y is down).
    pub fn height(&self) -> f32 {
        (-self.off[1] + self.size[1]).max(self.size[1])
    }
    /// Parse the `bbx` section bytes: six floats at `+0x18`.
    pub fn parse(b: &[u8]) -> Option<ChrBox> {
        let f = |o: usize| b.get(o..o + 4).map(|x| f32::from_le_bytes([x[0], x[1], x[2], x[3]]));
        let bx = ChrBox { off: [f(0x18)?, f(0x1c)?, f(0x20)?], size: [f(0x24)?, f(0x28)?, f(0x2c)?] };
        let ok = bx.off.iter().chain(bx.size.iter()).all(|v| v.is_finite() && v.abs() < 1000.0) && bx.size.iter().all(|&s| s >= 0.0);
        (ok && bx.radius() > 0.1).then_some(bx)
    }
}

/// `MonSetTbl::formation` -> number of monsters (`CBattle::MonsterEntry`).
pub fn monster_count(formation: u16) -> usize {
    match formation {
        0 => 1,
        1 | 2 | 0xf | 0x10 => 2,
        3 | 4 | 5 | 0x11 => 3,
        6..=9 => 4,
        10 | 0xb | 0x12 | 0x13 => 5,
        _ => 6,
    }
}

/// PS2 `(x, z)` on the floor -> Bevy world (y up, z flipped).
pub fn to_bevy(p: [f32; 2]) -> bevy::math::Vec3 {
    bevy::math::Vec3::new(p[0], 0.0, -p[1])
}

/// Inputs of [`layout`].
#[derive(Clone, Debug)]
pub struct Inputs<'a> {
    /// bounding radius of every party member / enemy in slot order (`BtlChr+0x3b0`)
    pub party: &'a [f32],
    pub enemy: &'a [f32],
    /// `MonSetTbl::formation`
    pub formation: u16,
    /// BBG `DAT` x, z (`CBattle+0x3f14 / 0x3f1c` are these minus 10)
    pub arena: [f32; 2],
    pub ambush: Ambush,
    /// `CBattle::bNoEvade`: always the tight spreads
    pub no_evade: bool,
}

/// Slot centres `(x, z)` (PS2) of the party and the enemies, in slot order.
pub fn layout(inp: &Inputs, rnd: &mut dyn FnMut() -> f32) -> (Vec<[f32; 2]>, Vec<[f32; 2]>) {
    // surrounded sides: `bFlags24 >> 3`: 1 = the party surrounds (PcFirst), 2 = the enemies surround (EnemyFirst)
    let (party_ring, enemy_ring) = (inp.ambush == Ambush::PcFirst, inp.ambush == Ambush::EnemyFirst);
    let party = if party_ring {
        ring(inp.party, inp.enemy, true)
    } else if enemy_ring {
        centre(inp.party, true)
    } else {
        party_row(inp.party, inp.arena[1])
    };
    let enemy = if enemy_ring {
        ring(inp.enemy, inp.party, false)
    } else if party_ring {
        centre(inp.enemy, false)
    } else {
        enemy_rows(inp, rnd)
    };
    (party, enemy)
}

fn party_row(r: &[f32], arena_z: f32) -> Vec<[f32; 2]> {
    let zb = -(arena_z / 10.0) - 15.0;
    let n = r.len();
    let m = r.iter().cloned().fold(0.0f32, f32::max);
    let z = zb - m;
    match n {
        0 => vec![],
        1 => vec![[0.0, zb - r[0]]],
        2 => vec![[r[0] + 6.0, z], [-(r[1] + 6.0), z]],
        3 => vec![[r[0] + r[1] + 12.0, z], [0.0, z], [-(r[1] + 12.0 + r[2]), z]],
        4 => vec![[r[0] + r[1] * 2.0 + 18.0, z], [r[1] + 6.0, z], [-(r[2] + 6.0), z], [-(r[2] * 2.0 + 18.0 + r[3]), z]],
        _ => {
            // more than four (not produced by the original): pack along x
            let mut out = vec![];
            let mut x: f32 = r.iter().map(|v| 2.0 * v + 12.0).sum::<f32>() * 0.5;
            for v in r {
                x -= v + 6.0;
                out.push([x + 0.0, z]);
                x -= v + 6.0;
            }
            out
        }
    }
}

/// the group in the middle of a ring ambush
fn centre(r: &[f32], reset: bool) -> Vec<[f32; 2]> {
    match r.len() {
        0 => vec![],
        1 => vec![[0.0, 0.0]],
        2 => {
            let m = r[0].max(r[1]);
            if reset {
                vec![[-6.0 - m, 0.0], [m + 6.0, 0.0]]
            } else {
                vec![[m + 6.0, 0.0], [-6.0 - m, 0.0]]
            }
        }
        n => {
            let sum: f32 = r.iter().map(|v| v * 2.0 + 12.0).sum();
            let rad = sum / std::f32::consts::TAU * 1.2;
            let (mut a, mut acc) = (0.0f32, 0.0f32);
            let mut out = vec![];
            for (i, v) in r.iter().enumerate() {
                let t = a.to_radians();
                out.push(if reset { [rad * -t.sin(), rad * t.cos()] } else { [rad * t.sin(), rad * -t.cos()] });
                if i + 1 < n {
                    acc += v + r[i + 1] + 12.0;
                    a = acc * 360.0 / sum;
                    if a >= 180.0 {
                        a -= 360.0;
                    }
                }
            }
            out
        }
    }
}

/// the surrounding side on a circle around `inner`
fn ring(r: &[f32], inner: &[f32], reset: bool) -> Vec<[f32; 2]> {
    let n = r.len();
    let mut rad = match inner.len() {
        2 => inner[0].max(inner[1]) * 2.0 + 36.0,
        1 => inner[0] + 30.0,
        0 => 0.0,
        k => {
            let m = inner.iter().cloned().fold(0.0f32, f32::max);
            let sum: f32 = inner.iter().map(|v| v * 2.0 + 12.0).sum();
            let _ = k;
            sum / std::f32::consts::TAU * 1.2 + m + 20.0
        }
    };
    rad += r.iter().cloned().fold(0.0f32, f32::max);
    let mut a = 0.0f32;
    let mut out = vec![];
    for _ in 0..n {
        let t = a.to_radians();
        out.push(if reset { [rad * t.sin(), rad * -t.cos()] } else { [rad * -t.sin(), rad * t.cos()] });
        a += 360.0 / n as f32;
        if a >= 180.0 {
            a -= 360.0;
        }
    }
    out
}

fn enemy_rows(inp: &Inputs, rnd: &mut dyn FnMut() -> f32) -> Vec<[f32; 2]> {
    let r = inp.enemy;
    let n = r.len();
    let (ax, az) = (inp.arena[0] - 10.0, inp.arena[1] - 10.0);
    let zb = -(inp.arena[1] / 10.0) + 15.0;
    let ne = inp.no_evade;
    let mut pct = || if ne { 0.0 } else { rnd() * 100.0 };
    // clamps: `-ARENA_X / 2 + R` lower, `ARENA_X / 2 - R` upper (x), `ARENA_Z / 2 - R` upper (z)
    let lo = |x: f32, i: usize| x.max(-ax / 2.0 + r[i]);
    let hi = |x: f32, i: usize| x.min(ax / 2.0 - r[i]);
    let zhi = |z: f32, i: usize| z.min(az / 2.0 - r[i]);
    let g = |i: usize| r.get(i).copied().unwrap_or(0.0);
    let (r0, r1, r2, r3, r4, r5) = (g(0), g(1), g(2), g(3), g(4), g(5));
    let m2 = |a: f32, b: f32| a.max(b);
    // positions as (x, z) per slot
    let mut p: Vec<[f32; 2]> = vec![[0.0, 0.0]; n.max(6)];
    let f = inp.formation;
    match f {
        0 => {
            p[0] = [0.0, zb + r0];
        }
        1 | 2 => {
            let m = m2(r0, r1);
            let (x0, x1) = if pct() < 50.0 { (-(r0 + 6.0), r1 + 6.0) } else { (lo(-(r0 + 24.0), 0), hi(r1 + 24.0, 1)) };
            p[0] = [x0, zb + m];
            p[1] = [x1, zb + if f == 2 { m * 2.0 } else { m }];
        }
        3 => {
            let m = r0.max(r1).max(r2);
            let q = pct();
            let (x0, x1, x2);
            if q < 25.0 {
                x0 = -(r1 + 12.0 + r0);
                x1 = 0.0;
                x2 = r2 + 12.0 + r1;
            } else if q < 50.0 {
                x0 = lo(-(r1 + 48.0 + r0) + 18.0, 0);
                x2 = hi(r2 + 12.0 + r1 + 18.0, 2);
                x1 = x2 - (r2 + 12.0 + r1);
            } else if q < 75.0 {
                x0 = lo(-(r1 + 12.0 + r0) - 18.0, 0);
                x1 = r1 + x0 + 12.0 + r0;
                x2 = hi(r2 + 48.0 + r1 - 18.0, 2);
            } else {
                x0 = lo(-(r1 + 48.0 + r0), 0);
                x1 = 0.0;
                x2 = hi(r2 + 48.0 + r1, 2);
            }
            let z = zb + 15.0 + m;
            p[0] = [x0, z];
            p[1] = [x1, z];
            p[2] = [x2, z];
        }
        4 => {
            let m = m2(r0, r1);
            let q = pct();
            let (x0, x1, mut x2, z2);
            if q < 100.0 / 3.0 {
                x0 = -(r2 + 6.0 + r0);
                x1 = r1 + 6.0 + r2;
                x2 = 0.0;
                z2 = if pct() < 50.0 { r2 + zb + m * 2.0 + 12.0 } else { zhi(r2 + zb + m * 2.0 + 48.0, 2) };
            } else {
                x0 = lo(-(r2 + 24.0 + r0), 0);
                x1 = hi(r1 + 24.0 + r2, 1);
                x2 = 0.0;
                let q = pct();
                if q < 25.0 {
                    z2 = r2 + zb + m * 2.0 + 12.0;
                } else if q < 50.0 {
                    z2 = r2 + zb + m * 2.0 + 12.0;
                    x2 = r2 + x0 + 6.0 + r0;
                } else if q < 75.0 {
                    z2 = r2 + zb + m * 2.0 + 12.0;
                    x2 = x1 - (r1 + 6.0 + r2);
                } else {
                    z2 = zhi(r2 + zb + m * 2.0 + 48.0, 2);
                }
            }
            p[0] = [x0, zb + m];
            p[1] = [x1, zb + m];
            p[2] = [x2, z2];
        }
        5 => {
            let m0 = r0;
            let m12 = m2(r1, r2);
            let q = pct();
            let (mut x0, x1, x2, z12);
            if q < 100.0 / 3.0 {
                x1 = -(r0 + 6.0 + r1);
                x2 = r2 + 6.0 + r0;
                x0 = 0.0;
                z12 = if pct() < 50.0 { m12 + zb + m0 * 2.0 + 12.0 } else { (m12 + zb + m0 * 2.0 + 48.0).min(az / 2.0 - m12) };
            } else {
                x1 = lo(-(r0 + 24.0 + r1), 1);
                x2 = hi(r2 + 24.0 + r0, 2);
                x0 = 0.0;
                let q = pct();
                if q < 25.0 {
                    z12 = m12 + zb + m0 * 2.0 + 12.0;
                } else if q < 50.0 {
                    z12 = m12 + zb + m0 * 2.0 + 12.0;
                    x0 = r0 + x1 + 6.0 + r1;
                } else if q < 75.0 {
                    z12 = m12 + zb + m0 * 2.0 + 12.0;
                    x0 = x2 - (r2 + 6.0 + r0);
                } else {
                    z12 = (m12 + zb + m0 * 2.0 + 48.0).min(az / 2.0 - m12);
                }
            }
            p[0] = [x0, zb + m0];
            p[1] = [x1, z12];
            p[2] = [x2, z12];
        }
        6 => {
            let m = r0.max(r1).max(r2).max(r3);
            let q = pct();
            let (x0, x1, x2, x3);
            if q < 20.0 {
                x0 = -(r1 * 2.0 + 18.0 + r0);
                x1 = -(r1 + 6.0);
                x2 = 6.0 + r2;
                x3 = r3 + 18.0 + r2 * 2.0;
            } else if q < 40.0 {
                x0 = lo(-(r1 * 2.0 + 6.0 + r0 + 48.0) + 18.0, 0);
                x3 = hi(r3 + 18.0 + r2 * 2.0 + 18.0, 3);
                x2 = x3 - (r3 + 12.0 + r2);
                x1 = x2 - (r2 + 12.0 + r1);
            } else if q < 60.0 {
                x0 = lo(-(r1 * 2.0 + 12.0 + r0 + 24.0), 0);
                x1 = r1 + x0 + 12.0 + r0;
                x3 = hi(r3 + 18.0 + r2 * 2.0 + 24.0, 3);
                x2 = x3 - (r3 + 12.0 + r2);
            } else if q < 80.0 {
                x0 = lo(-(r1 * 2.0 + 18.0 + r0) - 18.0, 0);
                x1 = r1 + x0 + 12.0 + r0;
                x2 = r2 + x1 + 12.0 + r1;
                x3 = hi(r3 + 6.0 + r2 * 2.0 + 48.0 - 18.0, 3);
            } else {
                x0 = lo(-(r1 * 2.0 + 6.0 + r0 + 48.0), 0);
                x1 = -(r1 + 6.0);
                x2 = 6.0 + r2;
                x3 = hi(r3 + 6.0 + r2 * 2.0 + 48.0, 3);
            }
            let z = zb + m;
            p[0] = [x0, z];
            p[1] = [x1, z];
            p[2] = [x2, z];
            p[3] = [x3, z];
        }
        // ---- 7..0xe: the tight variant only
        7 => {
            let (m01, m23) = (m2(r0, r1), m2(r2, r3));
            let (z0, z1) = (zb + m01, zb + m23 + m01 * 2.0 + 12.0);
            p[0] = [-(r0 + 6.0), z0];
            p[1] = [r1 + 6.0, z0];
            p[2] = [-(r0 * 2.0 + 12.0 + r2), z1];
            p[3] = [r3 + 12.0 + r1 * 2.0, z1];
        }
        8 => {
            let (m01, m23) = (m2(r0, r1), m2(r2, r3));
            let (z0, z1) = (zb + m01, zb + m23 + m01 * 2.0 + 12.0);
            p[0] = [-(r2 * 2.0 + 12.0 + r0), z0];
            p[1] = [r1 + 12.0 + r3 * 2.0, z0];
            p[2] = [-(r2 + 6.0), z1];
            p[3] = [6.0 + r3, z1];
        }
        9 => {
            let m = r0.max(r1).max(r2);
            let z0 = zb + m;
            p[0] = [-(r1 + 12.0 + r0), z0];
            p[1] = [0.0, z0];
            p[2] = [r2 + 12.0 + r1, z0];
            p[3] = [0.0, r3 + zb + m * 2.0 + 12.0];
        }
        10 => {
            let (m012, m34) = (r0.max(r1).max(r2), m2(r3, r4));
            let (z0, z1) = (zb + m012, zb + m34 + m012 * 2.0 + 12.0);
            p[0] = [-(r1 + 12.0 + r0), z0];
            p[1] = [0.0, z0];
            p[2] = [r2 + 12.0 + r1, z0];
            p[3] = [-(r3 + 6.0), z1];
            p[4] = [6.0 + r4, z1];
        }
        0xb => {
            let (m01, m234) = (m2(r0, r1), r2.max(r3).max(r4));
            let (z0, z1) = (zb + m01, zb + m234 + m01 * 2.0 + 12.0);
            p[0] = [-(r0 + 6.0), z0];
            p[1] = [r1 + 6.0, z0];
            p[2] = [-(r3 + 12.0 + r2), z1];
            p[3] = [0.0, z1];
            p[4] = [r4 + 12.0 + r3, z1];
        }
        0xc => {
            let (m012, m345) = (r0.max(r1).max(r2), r3.max(r4).max(r5));
            let (z0, z1) = (zb + m012, zb + m345 + m012 * 2.0 + 12.0);
            p[0] = [-(r1 + 12.0 + r0), z0];
            p[1] = [0.0, z0];
            p[2] = [r2 + 12.0 + r1, z0];
            p[3] = [-(r4 + 12.0 + r3), z1];
            p[4] = [0.0, z1];
            p[5] = [r5 + 12.0 + r4, z1];
        }
        0xd => {
            let (m0123, m45) = (r0.max(r1).max(r2).max(r3), m2(r4, r5));
            let (z0, z1) = (zb + m0123, zb + m45 + m0123 * 2.0 + 12.0);
            p[0] = [-(r1 * 2.0 + 18.0 + r0), z0];
            p[1] = [-(r1 + 6.0), z0];
            p[2] = [6.0 + r2, z0];
            p[3] = [r3 + 18.0 + r2 * 2.0, z0];
            p[4] = [-(r4 + 6.0), z1];
            p[5] = [6.0 + r5, z1];
        }
        0xe => {
            let (m01, m2345) = (m2(r0, r1), r2.max(r3).max(r4).max(r5));
            let (z0, z1) = (zb + m01, zb + m2345 + m01 * 2.0 + 12.0);
            p[0] = [-(r0 + 6.0), z0];
            p[1] = [r1 + 6.0, z0];
            p[2] = [-(r3 * 2.0 + 18.0 + r2), z1];
            p[3] = [-(r3 + 6.0), z1];
            p[4] = [6.0 + r4, z1];
            p[5] = [r5 + 18.0 + r4 * 2.0, z1];
        }
        0xf | 0x10 => {
            let m = m2(r0, r1);
            let x0 = lo(-(r0 + 24.0), 0);
            let x1 = hi(r1 + 24.0, 1);
            p[0] = [x0, zb + m];
            p[1] = [x1, zb + if f == 0x10 { m * 2.0 } else { m }];
        }
        0x11 => {
            let m = m2(r0, r1);
            p[0] = [lo(-(r2 + 24.0 + r0), 0), zb + m];
            p[1] = [hi(r1 + r2 + 24.0, 1), zb + m];
            p[2] = [0.0, zhi(r2 + zb + m * 2.0 + 48.0, 2)];
        }
        0x12 => {
            let (m01, m23) = (m2(r0, r1), m2(r2, r3));
            let x2 = lo(-(r3 + r2 + 48.0), 2);
            let x0 = lo((r2 + x2 + 12.0 + r3) - (r0 + 6.0), 0);
            let x3 = hi(r4 + r3 + 48.0, 4);
            let x1 = hi(r1 + (x3 - (r4 + 12.0 + r3)) + 6.0, 1);
            let z1 = m23 + zb + m01 * 2.0 + 12.0;
            p[0] = [x0, zb + m01];
            p[1] = [x1, zb + m01];
            p[2] = [x2, z1];
            p[3] = [x3, z1];
            p[4] = [0.0, zhi(r4 + m23 * 2.0 + zb + m01 * 2.0 + 12.0 + 48.0, 4)];
        }
        0x13 => {
            let m = r0.max(r1).max(r2).max(r3);
            let z = zb + m;
            p[0] = [-(r1 * 2.0 + 18.0 + r0), z];
            p[1] = [-(r1 + 6.0), z];
            p[2] = [r2 + 6.0, z];
            p[3] = [r3 + r2 * 2.0 + 18.0, z];
            p[4] = [0.0, zhi(r4 + zb + m * 2.0 + 48.0, 4)];
        }
        _ => {
            // unknown id: one tight row
            let m = r.iter().cloned().fold(0.0, f32::max);
            let mut x: f32 = -r.iter().map(|v| v * 2.0 + 12.0).sum::<f32>() * 0.5;
            for i in 0..n {
                x += r[i] + 6.0;
                p[i] = [x, zb + m];
                x += r[i] + 6.0;
            }
        }
    }
    // a formation id that disagrees with the number of spawned monsters: fall back to one tight row for the surplus
    if n > monster_count(f) && !matches!(f, 0..=0x13) {
        p.truncate(n);
    }
    // surplus units (fewer ids than monsters) share a back row
    for i in monster_count(f).min(6)..n.min(p.len()) {
        let m = r.iter().cloned().fold(0.0, f32::max);
        p[i] = [(i as f32 - n as f32 * 0.5) * (m * 2.0 + 12.0), zb + m * 4.0 + 24.0];
    }
    p.truncate(n);
    p
}

/// Formation slots of every fighter of a battle (Bevy world, feet): `boxes[i]` = the model's `bbx` box (radius 3 when unknown), `arena` = BBG `DAT` x, z.
/// The random spreads use a generator seeded from the monster set so that repeated calls (before / after the models load) agree.
pub fn homes_for(setup: &crate::bridge::BattleSetup, boxes: &[Option<ChrBox>], arena: [f32; 2]) -> Vec<bevy::math::Vec3> {
    let side: Vec<bool> = setup.fighters.iter().map(|f| f.is_enemy).collect();
    let radius = |i: usize| boxes.get(i).copied().flatten().map(|b| b.radius()).unwrap_or(3.0);
    let pi: Vec<usize> = (0..side.len()).filter(|&i| !side[i]).collect();
    let ei: Vec<usize> = (0..side.len()).filter(|&i| side[i]).collect();
    let (pr, er): (Vec<f32>, Vec<f32>) = (pi.iter().map(|&i| radius(i)).collect(), ei.iter().map(|&i| radius(i)).collect());
    let mut s = (setup.set as u32).wrapping_mul(2654435761) ^ (setup.formation as u32).wrapping_mul(40503) ^ 0x9e37_79b9;
    let mut rnd = move || {
        s = s.wrapping_mul(1664525).wrapping_add(1013904223);
        (s >> 8) as f32 / 16777216.0
    };
    let (pp, ep) = layout(&Inputs { party: &pr, enemy: &er, formation: setup.formation, arena, ambush: setup.ambush, no_evade: false }, &mut rnd);
    let mut out = vec![bevy::math::Vec3::ZERO; side.len()];
    for (k, &i) in pi.iter().enumerate() {
        let f = feet(pp[k], boxes.get(i).and_then(|b| b.as_ref()), 180.0);
        out[i] = to_bevy(f);
    }
    for (k, &i) in ei.iter().enumerate() {
        let f = feet(ep[k], boxes.get(i).and_then(|b| b.as_ref()), 0.0);
        out[i] = to_bevy(f);
    }
    // development aid (live comparisons): `SH2_BATTLE_ENEMY_POS="x,z;x,z;.."` = the enemies' feet in PS2 coordinates as read from a live battle (the retail
    // enemy rows are randomised per battle, so a pixel comparison needs the same positions)
    if let Ok(v) = std::env::var("SH2_BATTLE_PARTY_POS") {
        for (k, item) in v.split(';').enumerate() {
            let xz: Vec<f32> = item.split(',').filter_map(|s| s.trim().parse().ok()).collect();
            if let (Some(&i), [x, z]) = (pi.get(k), xz.as_slice()) {
                out[i] = to_bevy([*x, *z]);
            }
        }
    }
    if let Ok(v) = std::env::var("SH2_BATTLE_ENEMY_POS") {
        for (k, item) in v.split(';').enumerate() {
            let xz: Vec<f32> = item.split(',').filter_map(|s| s.trim().parse().ok()).collect();
            if let (Some(&i), [x, z]) = (ei.get(k), xz.as_slice()) {
                out[i] = to_bevy([*x, *z]);
            }
        }
    }
    out
}

/// Apply the box-centre correction: `pos = home - Rot_y(yaw) * (off.x, off.z)` (`yaw` PS2 degrees, 180 for the party, 0 for the enemies).
pub fn feet(home: [f32; 2], bx: Option<&ChrBox>, yaw_deg: f32) -> [f32; 2] {
    let Some(bx) = bx else { return home };
    let (s, c) = yaw_deg.to_radians().sin_cos();
    // sceVu0RotMatrixY: x' = x c + z s, z' = -x s + z c
    let (ox, oz) = (bx.off[0] * c + bx.off[2] * s, -bx.off[0] * s + bx.off[2] * c);
    [home[0] - ox, home[1] - oz]
}

#[cfg(test)]
mod tests {
    use super::*;

    fn inp<'a>(party: &'a [f32], enemy: &'a [f32], formation: u16) -> Inputs<'a> {
        Inputs { party, enemy, formation, arena: [150.0, 150.0], ambush: Ambush::None, no_evade: true }
    }

    #[test]
    fn party_rows_are_tight_and_behind_the_enemies() {
        let (p, _) = layout(&inp(&[3.0, 3.0], &[3.0], 0), &mut || 0.0);
        // zb = -(150 / 10) - 15 = -30; z = zb - max R = -33; x = +(R0 + 6), -(R1 + 6)
        assert_eq!(p, vec![[9.0, -33.0], [-9.0, -33.0]]);
        let (p, _) = layout(&inp(&[3.0, 3.0, 3.0, 3.0], &[3.0], 0), &mut || 0.0);
        assert_eq!(p.len(), 4);
        assert!(p[0][0] > p[1][0] && p[1][0] > p[2][0] && p[2][0] > p[3][0]);
    }

    #[test]
    fn enemy_formations_have_the_right_count_and_stay_in_the_arena() {
        for f in 0..=0x13u16 {
            let n = monster_count(f);
            let r = vec![5.0; n];
            for seed in 0..40 {
                let mut s = (seed as u32).wrapping_mul(2654435761);
                let mut rnd = move || {
                    s = s.wrapping_mul(1664525).wrapping_add(1013904223);
                    (s >> 8) as f32 / 16777216.0
                };
                let (_, e) = layout(&Inputs { party: &[4.0, 4.0], enemy: &r, formation: f, arena: [150.0, 150.0], ambush: Ambush::None, no_evade: false }, &mut rnd);
                assert_eq!(e.len(), n, "formation {f}");
                for p in &e {
                    assert!(p[0].abs() <= 75.0 + 1.0, "formation {f} x {p:?}");
                    assert!(p[1] > -16.0 && p[1] < 80.0, "formation {f} z {p:?}");
                }
            }
        }
    }

    #[test]
    fn two_enemies_tight() {
        let (_, e) = layout(&inp(&[4.0], &[5.0, 6.0], 1), &mut || 0.0);
        // zb = -15 + 15 = 0, z = max R = 6, x = -(R0 + 6), R1 + 6
        assert_eq!(e, vec![[-11.0, 6.0], [12.0, 6.0]]);
    }

    #[test]
    fn ambush_ring_surrounds_the_centre() {
        let mut i = inp(&[4.0, 4.0, 4.0], &[5.0, 5.0], 1);
        i.ambush = Ambush::PcFirst;
        let (p, e) = layout(&i, &mut || 0.0);
        let rad = (p[0][0].powi(2) + p[0][1].powi(2)).sqrt();
        assert!((rad - (5.0 * 2.0 + 36.0 + 4.0)).abs() < 0.01, "ring radius {rad}");
        assert!(e.iter().all(|q| q[1] == 0.0));
    }

    #[test]
    fn bbx_parse() {
        let mut b = vec![0u8; 0x40];
        for (i, v) in [0.17f32, -8.3, -0.7, 2.18, 5.74, 3.36].iter().enumerate() {
            b[0x18 + i * 4..0x1c + i * 4].copy_from_slice(&v.to_le_bytes());
        }
        let bx = ChrBox::parse(&b).unwrap();
        assert!((bx.radius() - 2.77).abs() < 1e-3);
        assert!(ChrBox::parse(&vec![0u8; 0x40]).is_none());
    }

    /// Live retail battle (PCSX2, save state at the first AP_03_U encounter, MONSET 2 = Revenant, Revenant, Statue on BBG 077, DAT z = 150): `BtlChr+0x160` positions read over PINE.
    /// Party home z -32.70, x +-8.7; enemies in the wide variant of formation 4: x -28.4 / +28.5 / -18.1, z 2.8 / 3.2 / 19.2 (final position = home - Rot * box offset).
    #[test]
    fn matches_the_live_retail_battle() {
        let (kar, nic) = (ChrBox { off: [0.167898, -8.30291, -0.708028], size: [2.181999, 5.743835, 3.362312] }, ChrBox { off: [0.802411, -9.484985, 0.775028], size: [2.876271, 7.092537, 2.495817] });
        let (rev, sta) = (ChrBox { off: [0.392832, -8.110571, -0.783825], size: [2.61626, 6.145757, 2.012423] }, ChrBox { off: [0.055093, -7.391292, -0.438289], size: [1.907446, 5.698247, 2.411584] });
        let pr = [kar.radius(), nic.radius()];
        let er = [rev.radius(), rev.radius(), sta.radius()];
        // formation 4, the wide spread (first roll >= 33.3 %, second roll 25..50 %)
        let mut rolls = [0.5f32, 0.3].into_iter();
        let mut rnd = move || rolls.next().unwrap_or(0.9);
        let (p, e) = layout(&Inputs { party: &pr, enemy: &er, formation: 4, arena: [150.0, 150.0], ambush: Ambush::None, no_evade: false }, &mut rnd);
        let near = |a: f32, b: f32, what: &str| assert!((a - b).abs() < 1.0, "{what}: {a} vs live {b}");
        near(p[0][0], 8.73, "Karin home x");
        near(p[0][1], -32.70, "Karin home z");
        near(p[1][0], -8.69, "Nicolai home x");
        near(p[1][1], -32.70, "Nicolai home z");
        let (a, b, c) = (feet(e[0], Some(&rev), 0.0), feet(e[1], Some(&rev), 0.0), feet(e[2], Some(&sta), 0.0));
        near(a[0], -29.2, "Revenant A x");
        near(a[1], 2.80, "Revenant A z");
        near(b[0], 28.52, "Revenant B x");
        near(b[1], 3.19, "Revenant B z");
        near(c[0], -18.13, "Statue x");
        near(c[1], 19.21, "Statue z");
        // the party's feet (yaw 180): Karin (8.53, -33.44), Nicolai (-8.40, -31.64)
        let (fk, fnn) = (feet(p[0], Some(&kar), 180.0), feet(p[1], Some(&nic), 180.0));
        near(fk[1], -33.44, "Karin z");
        near(fnn[1], -31.64, "Nicolai z");
    }
}

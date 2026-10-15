//! `GetWarpPos(int, bool)` (JP `BtlFree` 0x005e38a0, US BATTLE.BIN 0x00631xxx..0x00632760): where *Gathering* (effect program 080,
//! `btlGetWarpPos(kind, k, first, out)`) puts each gathered unit, and the last boss's part placement shares its "placed list"
//! (`CBattle+0x45d4` list / `+0x45c0` count; US `+0x4878` / `+0x4864`).
//!
//! * `first == true`: the last boss's core (CHR 499) stays where it is (it only joins the list).  Any other unit goes to the centre of the
//!   **largest free rectangle** of the arena (`CBattle+0x3f14 / 0x3f1c`, the BBG `DAT` size - 10) once the boxes of every unit on the other
//!   side of the *acting* unit (`CBattle+0x3d24`; for *Gathering* = the enemies themselves) are cut out: an integer rectangle
//!   subtraction (`[x - (r + .5), z - (r + .5), 2r + .5, 2r + .5]` per box) followed by a merge pass that joins side-by-side rectangles
//!   whenever the joined one is larger than both (areas in `short`, as retail).  The list restarts with this unit.
//! * `first == false`: for each unit of the list, candidate points on the circle of radius `(int)(R_placed + R_k + 5)` around it
//!   (64 steps of pi/32 from -pi), inside the arena by `R_k`, farther than `R_k + R_i + 3` from every living unit of the other side,
//!   and -- a retail slip kept as is -- farther than `R_k + R_u + 3` from the units with *index* `u < count` (not the listed units);
//!   one candidate is picked at random (truncated to integers) and the unit joins the list.  The loop counter is the register that
//!   receives `rand() % n` (US 0x006324c0 `mfhi s0`), so the search continues from that candidate index + 1 while it is below the count.
//!
//! Coordinates are PS2 battle `(x, z)` of the box centres (`BtlChr+0x160`, US `+0x170` = LV's slot `+0xc0`).

/// One battle unit as `GetWarpPos` sees it.
#[derive(Clone, Copy, Debug, Default)]
pub struct WarpUnit {
    /// box centre (PS2 x, z)
    pub pos: [f32; 2],
    /// `BtlChr+0x3b0`
    pub radius: f32,
    pub enemy: bool,
    /// in the battle, alive, not attached (`+0xb0` bits 0 / 1, `+0xb2` bit 2 clear, HP > 0)
    pub present: bool,
    /// CHR model number (`BtlChr+0x18c`)
    pub chr: u32,
}

type Rect = [i32; 4];

fn overlaps_incl(f: &Rect, o: &Rect) -> bool {
    let dx = ((f[0] + f[2] / 2) - (o[0] + o[2] / 2)).abs();
    if dx > (o[2] + f[2]) / 2 {
        return false;
    }
    let dz = ((f[1] + f[3] / 2) - (o[1] + o[3] / 2)).abs();
    dz <= (o[3] + f[3]) / 2
}

fn a16(w: i32, h: i32) -> i32 {
    (w.wrapping_mul(h)) as i16 as i32
}

/// The free rectangles of `arena` (`[x, z, w, h]`) minus `boxes`, merged like retail.
pub fn free_rects(arena: Rect, boxes: &[Rect]) -> Vec<Rect> {
    let mut f: Vec<Rect> = vec![arena];
    for &ob in boxes {
        let mut o: Vec<Rect> = vec![ob];
        while !o.is_empty() {
            if let Some(i) = f.iter().position(|fr| overlaps_incl(fr, &o[0])) {
                let mut fi = f[i];
                let mut o0 = o[0];
                if fi[0] < o0[0] {
                    f.push([fi[0], fi[1], o0[0] - fi[0], fi[3]]);
                    fi[2] -= o0[0] - fi[0];
                    fi[0] = o0[0];
                } else if o0[0] < fi[0] {
                    o.push([o0[0], o0[1], fi[0] - o0[0], o0[3]]);
                    o0[2] -= fi[0] - o0[0];
                    o0[0] = fi[0];
                }
                if fi[1] < o0[1] {
                    f.push([fi[0], fi[1], fi[2], o0[1] - fi[1]]);
                    fi[3] -= o0[1] - fi[1];
                    fi[1] = o0[1];
                } else if o0[1] < fi[1] {
                    o.push([o0[0], o0[1], o0[2], fi[1] - o0[1]]);
                    o0[3] -= fi[1] - o0[1];
                    o0[1] = fi[1];
                }
                if o0[0] + o0[2] < fi[0] + fi[2] {
                    let nx = o0[0] + o0[2];
                    f.push([nx, fi[1], fi[0] + fi[2] - nx, fi[3]]);
                    fi[2] = nx - fi[0];
                } else if fi[0] + fi[2] < o0[0] + o0[2] {
                    let nx = fi[0] + fi[2];
                    o.push([nx, o0[1], o0[0] + o0[2] - nx, o0[3]]);
                    o0[2] = nx - o0[0];
                }
                if o0[1] + o0[3] < fi[1] + fi[3] {
                    let nz = o0[1] + o0[3];
                    f.push([fi[0], nz, fi[2], fi[1] + fi[3] - nz]);
                    fi[3] = nz - fi[1];
                } else if fi[1] + fi[3] < o0[1] + o0[3] {
                    let nz = fi[1] + fi[3];
                    o.push([o0[0], nz, o0[2], o0[1] + o0[3] - nz]);
                    o0[3] = nz - o0[1];
                }
                let _ = (fi, o0);
                f.remove(i);
            }
            o.remove(0);
            if f.len() > 256 {
                break;
            }
        }
    }
    // merge pass (LAB_005e5f38): restart after every merge
    let mut guard = 0;
    loop {
        guard += 1;
        if guard > 4096 {
            break;
        }
        let mut merged = None;
        'outer: for i in 0..f.len() {
            for j in i + 1..f.len() {
                let (mut a, mut b) = (f[i], f[j]);
                let xo = ((a[0] + a[2] / 2) - (b[0] + b[2] / 2)).abs() < (a[2] + b[2]) / 2;
                let zo = ((a[1] + a[3] / 2) - (b[1] + b[3] / 2)).abs() < (a[3] + b[3]) / 2;
                let mut l: Vec<Rect> = vec![];
                if (a[0] == b[0] + b[2] || b[0] == a[0] + a[2]) && zo {
                    let mz = a[1].max(b[1]);
                    let m = [a[0].min(b[0]), mz, a[2] + b[2], (a[1] + a[3]).min(b[1] + b[3]) - mz];
                    let a6 = a16(m[2], m[3]);
                    if a16(a[2], a[3]) < a6 && a16(b[2], b[3]) < a6 {
                        if a[1] < b[1] {
                            l.push([a[0], a[1], a[2], b[1] - a[1]]);
                            a[3] -= b[1] - a[1];
                            a[1] = b[1];
                        } else if b[1] < a[1] {
                            l.push([b[0], b[1], b[2], a[1] - b[1]]);
                            b[3] -= a[1] - b[1];
                            b[1] = a[1];
                        }
                        if b[1] + b[3] < a[1] + a[3] {
                            let nz = b[1] + b[3];
                            l.push([a[0], nz, a[2], a[1] + a[3] - nz]);
                        } else if a[1] + a[3] < b[1] + b[3] {
                            let nz = a[1] + a[3];
                            l.push([b[0], nz, b[2], b[1] + b[3] - nz]);
                        }
                        merged = Some((i, j, m, l));
                        break 'outer;
                    }
                } else if (a[1] == b[1] + b[3] || b[1] == a[1] + a[3]) && xo {
                    let mx = a[0].max(b[0]);
                    let m = [mx, a[1].min(b[1]), (a[0] + a[2]).min(b[0] + b[2]) - mx, a[3] + b[3]];
                    let a6 = a16(m[2], m[3]);
                    if a16(a[2], a[3]) < a6 && a16(b[2], b[3]) < a6 {
                        if a[0] < b[0] {
                            l.push([a[0], a[1], b[0] - a[0], a[3]]);
                            a[2] -= b[0] - a[0];
                            a[0] = b[0];
                        } else if b[0] < a[0] {
                            l.push([b[0], b[1], a[0] - b[0], b[3]]);
                            b[2] -= a[0] - b[0];
                            b[0] = a[0];
                        }
                        if b[0] + b[2] < a[0] + a[2] {
                            let nx = b[0] + b[2];
                            l.push([nx, a[1], a[0] + a[2] - nx, a[3]]);
                        } else if a[0] + a[2] < b[0] + b[2] {
                            let nx = a[0] + a[2];
                            l.push([nx, b[1], b[0] + b[2] - nx, b[3]]);
                        }
                        merged = Some((i, j, m, l));
                        break 'outer;
                    }
                }
            }
        }
        let Some((i, j, m, l)) = merged else { break };
        f[i] = m;
        match l.len() {
            0 => {
                f.remove(j);
            }
            1 => f[j] = l[0],
            _ => {
                f[j] = l[0];
                f.push(l[1]);
            }
        }
    }
    f
}

/// `GetWarpPos(k, first)`: the new box centre of unit `k` (also written to `units[k].pos`); `actor_enemy` = side of the acting unit
/// (`CBattle+0x3d24`), `arena` = `CBattle+0x3f14 / 0x3f1c`, `placed` = the list at `CBattle+0x45d4`, `rand` = the C `rand()`.
pub fn get_warp_pos(units: &mut [WarpUnit], k: usize, first: bool, actor_enemy: bool, arena: [f32; 2], placed: &mut Vec<usize>, rand: &mut dyn FnMut() -> u32) -> [f32; 2] {
    let Some(me) = units.get(k).copied() else { return [0.0, 0.0] };
    if first {
        placed.clear();
        placed.push(k);
        if me.chr == 499 {
            return me.pos;
        }
        let boxes: Vec<Rect> = units
            .iter()
            .filter(|u| u.present && u.enemy != actor_enemy)
            .map(|u| {
                let w = (u.radius * 2.0 + 0.5) as i32;
                [(u.pos[0] - (u.radius + 0.5)) as i32, (u.pos[1] - (u.radius + 0.5)) as i32, w, w]
            })
            .collect();
        let ar: Rect = [(-(arena[0] / 2.0)) as i32, (-(arena[1] / 2.0)) as i32, arena[0] as i32, arena[1] as i32];
        let f = free_rects(ar, &boxes);
        let mut best = 0;
        for (i, r) in f.iter().enumerate() {
            if f[best][2] * f[best][3] < r[2] * r[3] {
                best = i;
            }
        }
        let Some(r) = f.get(best) else { return me.pos };
        let p = [(r[0] + r[2] / 2) as f32, (r[1] + r[3] / 2) as f32];
        units[k].pos = p;
        return p;
    }
    let mut out = me.pos;
    let mut li = 0usize;
    let mut guard = 0;
    while li < placed.len() && guard < 64 {
        guard += 1;
        let j = placed[li];
        let Some(pj) = units.get(j).copied() else {
            li += 1;
            continue;
        };
        let rr = (pj.radius + me.radius + 5.0) as i16 as i32;
        let mut cands: Vec<[i32; 2]> = vec![];
        let mut a: f32 = -std::f32::consts::PI;
        while a < std::f32::consts::PI {
            let x = pj.pos[0] + rr as f32 * a.cos();
            let z = (pj.pos[1] as f64 + rr as f64 * -(a as f64).sin()) as f32;
            let inside = -arena[0] / 2.0 + me.radius <= x && x <= arena[0] / 2.0 - me.radius && -arena[1] / 2.0 + me.radius <= z && z <= arena[1] / 2.0 - me.radius;
            if inside {
                let dist = |u: &WarpUnit| ((u.pos[0] - x).powi(2) + (u.pos[1] - z).powi(2)).sqrt();
                let foe_close = units.iter().any(|u| u.present && u.enemy != me.enemy && dist(u) < me.radius + u.radius + 3.0);
                // retail checks the units with index < count here (not the listed ones)
                let low_close = (0..placed.len()).filter_map(|u| units.get(u)).any(|u| dist(u) < me.radius + u.radius + 3.0);
                if !foe_close && !low_close {
                    cands.push([x as i32, z as i32]);
                }
            }
            a += 0.098_174_77;
        }
        if !cands.is_empty() {
            let pick = rand() as usize % cands.len();
            li = pick;
            out = [cands[pick][0] as f32, cands[pick][1] as f32];
            units[k].pos = out;
            placed.push(k);
        }
        li += 1;
    }
    out
}

/// `LastBossSpecial` (JP 0x00640840, separating branch): a random point of the part's arc in front of the core -- CHR 500 60..120 deg,
/// 501 30..60, 502 120..150 (steps of pi/32), radius `R_core + R_part + 12`, `(x, z) = core + R (cos a, -sin a)`, inside the arena by
/// `R_part` and farther than `R_part + R_i + 5` from every present unit of the other side.  `None` when no point is free (retail divides
/// by zero there).
pub fn last_boss_arc(units: &[WarpUnit], core: usize, part: usize, arena: [f32; 2], rand: &mut dyn FnMut() -> u32) -> Option<[f32; 2]> {
    let (c, p) = (units.get(core)?, units.get(part)?);
    let (lo, hi) = match p.chr {
        500 => (std::f32::consts::FRAC_PI_3, 2.094_395_2),
        501 => (0.523_598_8, std::f32::consts::FRAC_PI_3),
        _ => (2.094_395_2, 2.617_994),
    };
    let r = c.radius + p.radius + 12.0;
    let mut cands = vec![];
    let mut a = lo;
    while a < hi {
        let z = (c.pos[1] as f64 + r as f64 * -(a as f64).sin()) as f32;
        let x = c.pos[0] + r * a.cos();
        let inside = -arena[0] / 2.0 + p.radius <= x && x <= arena[0] / 2.0 - p.radius && -arena[1] / 2.0 + p.radius <= z && z <= arena[1] / 2.0 - p.radius;
        if inside {
            let close = units.iter().any(|u| u.present && u.enemy != p.enemy && ((u.pos[0] - x).powi(2) + (u.pos[1] - z).powi(2)).sqrt() < p.radius + u.radius + 5.0);
            if !close {
                cands.push([x, z]);
            }
        }
        a += 0.098_174_77;
    }
    if cands.is_empty() {
        return None;
    }
    Some(cands[rand() as usize % cands.len()])
}

/// *Gathering* on the side of `units[target]`: every present unit of that side, the target first (`first == true`), then the others in slot
/// order.  Returns `(unit, new box centre)` per moved unit.
pub fn gather(units: &mut [WarpUnit], target: usize, actor_enemy: bool, arena: [f32; 2], rand: &mut dyn FnMut() -> u32) -> Vec<(usize, [f32; 2])> {
    let Some(side) = units.get(target).map(|u| u.enemy) else { return vec![] };
    // US `EffectFunc` (us_battle_phases.c ~910): for effect 0x50 the last boss's core (CHR 499) is swapped to the front of the target list
    let target = (0..units.len()).find(|&k| units[k].present && units[k].enemy == side && units[k].chr == 499).unwrap_or(target);
    let mut order = vec![target];
    order.extend((0..units.len()).filter(|&k| k != target && units[k].present && units[k].enemy == side));
    let mut placed = vec![];
    let mut out = vec![];
    for (n, &k) in order.iter().enumerate() {
        let p = get_warp_pos(units, k, n == 0, actor_enemy, arena, &mut placed, rand);
        out.push((k, p));
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn free_rects_cut_a_box_out_of_the_arena() {
        let f = free_rects([-95, -95, 190, 190], &[[-5, -5, 10, 10]]);
        let area: i32 = f.iter().map(|r| r[2] * r[3]).sum();
        assert_eq!(area, 190 * 190 - 100);
        // no rectangle overlaps the box
        assert!(f.iter().all(|r| r[0] >= 5 || r[0] + r[2] <= -5 || r[1] >= 5 || r[1] + r[3] <= -5), "{f:?}");
    }

    /// Live r5_lv check 5 (MONSET 95, Anastasia's Gathering): the gathered monsters end in a compact cluster in front of the party (not a
    /// ring around the target), away from the party boxes.
    #[test]
    fn gathering_clusters_the_enemies_like_the_live_game() {
        let mut u = vec![
            WarpUnit { pos: [18.79, -39.08], radius: 2.7, enemy: false, present: true, chr: 5 },
            WarpUnit { pos: [0.0, -39.08], radius: 4.08, enemy: false, present: true, chr: 1 },
            WarpUnit { pos: [-17.96, -39.08], radius: 1.87, enemy: false, present: true, chr: 4 },
            WarpUnit { pos: [-67.6, -42.8], radius: 4.0, enemy: true, present: true, chr: 100 },
            WarpUnit { pos: [34.4, -66.7], radius: 4.0, enemy: true, present: true, chr: 101 },
            WarpUnit { pos: [13.2, 27.6], radius: 4.0, enemy: true, present: true, chr: 102 },
            WarpUnit { pos: [35.6, 2.1], radius: 4.0, enemy: true, present: true, chr: 103 },
        ];
        let mut s = 12345u32;
        let mut rnd = move || {
            s = s.wrapping_mul(1103515245).wrapping_add(12345);
            (s >> 16) & 0x7fff
        };
        let moved = gather(&mut u, 5, false, [190.0, 190.0], &mut rnd);
        eprintln!("gathered: {moved:?}");
        assert_eq!(moved.len(), 4);
        for &(k, p) in &moved {
            for &(k2, p2) in &moved {
                if k != k2 {
                    let d = ((p[0] - p2[0]).powi(2) + (p[1] - p2[1]).powi(2)).sqrt();
                    assert!(d < 60.0, "cluster spread {k} {k2} {d}");
                }
            }
            for pc in &u[..3] {
                let d = ((p[0] - pc.pos[0]).powi(2) + (p[1] - pc.pos[1]).powi(2)).sqrt();
                assert!(d >= u[k].radius + pc.radius + 3.0 - 1.5, "unit {k} on the party");
            }
        }
        // the followers stand on integer points next to an earlier one (retail stores the candidates as shorts)
        for &(_, p) in &moved[1..] {
            assert_eq!(p[0].fract(), 0.0);
        }
    }

    #[test]
    fn last_boss_parts_land_on_their_arcs() {
        let mut u = vec![
            WarpUnit { pos: [0.0, -39.08], radius: 4.08, enemy: false, present: true, chr: 1 },
            WarpUnit { pos: [0.0, 62.34], radius: 32.66, enemy: true, present: true, chr: 499 },
            WarpUnit { pos: [0.0, 62.34], radius: 5.82, enemy: true, present: false, chr: 500 },
            WarpUnit { pos: [0.0, 62.34], radius: 5.0, enemy: true, present: false, chr: 501 },
            WarpUnit { pos: [0.0, 62.34], radius: 5.0, enemy: true, present: false, chr: 502 },
        ];
        let mut n = 7u32;
        for (k, lo, hi) in [(2usize, 60.0f32, 120.0f32), (3, 30.0, 60.0), (4, 120.0, 150.0)] {
            let p = last_boss_arc(&u, 1, k, [190.0, 190.0], &mut || {
                n = n.wrapping_mul(69069).wrapping_add(1);
                n >> 8
            })
            .unwrap();
            let (dx, dz) = (p[0] - u[1].pos[0], p[1] - u[1].pos[1]);
            let d = (dx * dx + dz * dz).sqrt();
            assert!((d - (u[1].radius + u[k].radius + 12.0)).abs() < 0.01, "{d}");
            let a = (-dz).atan2(dx).to_degrees();
            assert!(a >= lo - 0.01 && a < hi, "part {k} at {a} deg");
            u[k].pos = p;
        }
    }

    #[test]
    fn the_last_boss_core_is_not_moved() {
        let mut u = vec![WarpUnit { pos: [0.0, 62.34], radius: 32.66, enemy: true, present: true, chr: 499 }];
        let mut placed = vec![];
        let p = get_warp_pos(&mut u, 0, true, false, [190.0, 190.0], &mut placed, &mut || 0);
        assert_eq!(p, [0.0, 62.34]);
        assert_eq!(placed, vec![0]);
    }
}

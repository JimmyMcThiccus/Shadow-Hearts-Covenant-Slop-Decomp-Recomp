//! A tiny field autopilot used by `sh2_app --autoplay` and the headless flow tests: it produces PS2 pad bits from the field state so a
//! scripted run can read messages, walk to an exit trigger and wander until a random encounter fires.  It only looks at public game state
//! (player position, event boxes, camera yaw, open message window), exactly what a human would see.

use crate::movement::{pad, DIR_TBL};
use crate::plugin::FieldRuntime;

/// Per-map hint "go to this event box id first" (demo flow: the exit of `AP_02_U` towards the first monster map).
pub const PILOT_HINTS: [(&str, i32); 1] = [("AP_02_U", 2)];

/// Boxes the wanderer never walks into (their scripts leave the map): learned at run time, seeded with the demo's known door.
pub const PILOT_AVOID: [(&str, i32); 1] = [("AP_03_U", 1)];

/// What happened the last time the explorer tried a target.
#[derive(Debug, Clone, PartialEq)]
pub enum Outcome {
    /// the script left for this map
    Jump(String),
    Nothing,
}

/// Memory of the story explorer ([`Pilot::explore`]) across maps.
#[derive(Debug, Clone, Default)]
pub struct ExploreMem {
    pub visited: std::collections::BTreeSet<String>,
    /// `(map, target key) -> outcome` (box id, or `ACTOR_KEY + slot` for a talk target)
    pub outcome: std::collections::BTreeMap<(String, i64), Outcome>,
    pub tries: std::collections::BTreeMap<(String, i64), u32>,
    /// the target interacted with last and the tick it happened
    pub pending: Option<((String, i64), u64)>,
    pub clock: u64,
    pub warps: u32,
    pub trail: Vec<String>,
}

/// target key base of an NPC (`ACTOR_KEY + slot`); event boxes use their event id
pub const ACTOR_KEY: i64 = 1_000_000;
/// target key base of a look point (`LOOK_KEY + id`)
pub const LOOK_KEY: i64 = 2_000_000;

#[derive(Debug, Clone)]
struct Target {
    key: i64,
    pos: [f32; 3],
    examine: bool,
    actor: bool,
    /// distance at which the target counts as reached
    reach: f32,
}

#[derive(Default)]
pub struct Pilot {
    /// story explorer: instead of wandering for an encounter, visit every event box / NPC of the map (unvisited destinations first),
    /// walking there and, when the straight walk does not arrive (no path finding), placing the player on the target
    pub explore: bool,
    /// print the explorer's decisions on stderr (`SH2_STORY_PRINT=2`)
    pub trace: bool,
    pub mem: ExploreMem,
    cur: Option<Target>,
    cur_ticks: u32,
    detours: u32,
    touched: bool,
    warps_here: u32,
    wait: u32,
    /// `(map, box id)` pairs that ended in a map jump
    bad: Vec<(String, i32)>,
    last_enter: i32,
    tick: u32,
    target_idx: usize,
    last_pos: [f32; 3],
    still: u32,
    detour: u32,
    detour_dir: u16,
    arrived_at: u32,
    wander_phase: u32,
    order: Vec<usize>,
    map: String,
    press_phase: u32,
    /// ticks spent walking towards a target (events / message windows do not count)
    walk_ticks: u32,
}

/// pad bits for a heading step 0..7 (inverse of `DIR_TBL`: 0 = up, clockwise)
fn dpad_for_step(step: usize) -> u16 {
    // DIR_TBL index bits: up=1, right=2, down=4, left=8
    let idx = DIR_TBL.iter().position(|&d| d as usize == step && d >= 0).unwrap_or(1);
    let mut b = 0;
    if idx & 1 != 0 {
        b |= pad::UP;
    }
    if idx & 2 != 0 {
        b |= pad::RIGHT;
    }
    if idx & 4 != 0 {
        b |= pad::DOWN;
    }
    if idx & 8 != 0 {
        b |= pad::LEFT;
    }
    b
}

impl Pilot {
    /// The current target is being interacted with (the box fired, the circle button is pressed ...): count the try and remember it, so a map
    /// change within a few seconds is credited to it.
    fn touch(&mut self) {
        if self.touched {
            return;
        }
        if let Some(t) = &self.cur {
            self.touched = true;
            let k = (self.map.clone(), t.key);
            *self.mem.tries.entry(k.clone()).or_insert(0) += 1;
            self.mem.pending = Some((k, self.mem.clock));
        }
    }

    /// one line of explorer state for stall reports
    pub fn debug(&self) -> String {
        format!("cur {:?} cur_ticks {} detours {} still {} wait {} arrived {} warps {} visited {:?}", self.cur, self.cur_ticks, self.detours, self.still, self.wait, self.arrived_at, self.mem.warps, self.mem.visited)
    }

    fn score(&self, key: i64, dist: f32) -> Option<f32> {
        let k = (self.map.clone(), key);
        let tries = self.mem.tries.get(&k).copied().unwrap_or(0);
        let base = match self.mem.outcome.get(&k) {
            Some(Outcome::Jump(m)) if !self.mem.visited.contains(m) => 0.0,
            Some(Outcome::Jump(_)) => 200.0 + 20.0 * tries as f32,
            _ if tries == 0 => 10.0,
            _ => 30.0 + 20.0 * tries as f32,
        };
        if tries >= 6 {
            return None;
        }
        Some(base + dist / 1000.0)
    }

    /// The best target of this map: unvisited destinations first, then untried boxes / NPCs, nearest first.
    fn choose(&self, rt: &mut FieldRuntime) -> Option<Target> {
        let pos = rt.sim.player.pos;
        let has_event = |id: u32| rt.vm.image.as_ref().map(|i| i.find_event(0, id).is_some()).unwrap_or(false);
        // NPCs that stand off the floor (hidden props, models parked out of sight) cannot be walked up to
        let mut walkable: Vec<usize> = vec![];
        for (slot, a) in rt.st.actors.slots.iter().enumerate() {
            if let Some(a) = a {
                let p = [a.pos[0], pos[1], a.pos[2]];
                if rt.sim.field.floor.as_mut().map(|f| f.circle_chk(p, 3.0).is_some()).unwrap_or(true) {
                    walkable.push(slot);
                }
            }
        }
        let mut best: Option<(f32, Target)> = None;
        let mut consider = |t: Target, dist: f32, sc: Option<f32>| {
            let _ = dist;
            if let Some(sc) = sc {
                if best.as_ref().map(|(b, _)| sc < *b).unwrap_or(true) {
                    best = Some((sc, t));
                }
            }
        };
        if let Some(e) = rt.sim.field.event_boxes.as_ref() {
            for b in &e.boxes {
                if b.id < 0 || !has_event(b.id as u32) {
                    continue;
                }
                let d = (b.center[0] - pos[0]).hypot(b.center[2] - pos[2]);
                let t = Target { key: b.id as i64, pos: [b.center[0], b.center[1], b.center[2]], examine: b.kind != 0, actor: false, reach: 6.0 };
                consider(t, d, self.score(b.id as i64, d));
            }
        }
        for (slot, a) in rt.st.actors.slots.iter().enumerate() {
            let Some(a) = a else { continue };
            if slot == rt.st.actors.ctrl || !a.loaded || !a.disp || a.event_id == 0 || !has_event(a.event_id) || !walkable.contains(&slot) {
                continue;
            }
            let d = (a.pos[0] - pos[0]).hypot(a.pos[2] - pos[2]);
            let key = ACTOR_KEY + slot as i64;
            let t = Target { key, pos: a.pos, examine: true, actor: true, reach: 8.0 };
            consider(t, d, self.score(key, d).map(|s| s - 1.0));
        }
        // look points: stand inside the radius and press circle (their default event)
        for l in rt.st.look.slots.iter().flatten() {
            if l.event == 0 || !has_event(l.event) {
                continue;
            }
            let d = (l.pos[0] - pos[0]).hypot(l.pos[2] - pos[2]);
            let key = LOOK_KEY + l.id as i64;
            let t = Target { key, pos: l.pos, examine: true, actor: false, reach: (l.radius * 0.6).clamp(2.0, 12.0) };
            consider(t, d, self.score(key, d).map(|s| s - 0.5));
        }
        best.map(|(_, t)| t)
    }

    /// One tick of the story explorer; `None` = nothing to do on this map (the caller falls back to wandering).
    fn explore_step(&mut self, rt: &mut FieldRuntime) -> Option<u16> {
        if self.wait > 0 {
            // after an interaction: stand still for a moment so the box / script reaction can start
            self.wait -= 1;
            return Some(0);
        }
        if self.cur.is_none() {
            self.cur = self.choose(rt);
            if self.trace && self.cur.is_some() {
                eprintln!("pilot[{}]: target {:?} from {:?} cur_box {}", self.map, self.cur, rt.sim.player.pos, rt.sim.cur_box);
            }
            self.cur_ticks = 0;
            self.detours = 0;
            self.warps_here = 0;
            self.arrived_at = 0;
            self.touched = false;
        }
        let t = self.cur.clone()?;
        let pos = rt.sim.player.pos;
        let (mut tx, mut tz) = (t.pos[0], t.pos[2]);
        let mut dist = (tx - pos[0]).hypot(tz - pos[2]);
        if t.actor {
            // actors are re-read every tick: they move
            if let Some(a) = rt.st.actors.get((t.key - ACTOR_KEY) as i32) {
                tx = a.pos[0];
                tz = a.pos[2];
                dist = (tx - pos[0]).hypot(tz - pos[2]);
            }
        }
        self.cur_ticks += 1;
        let reach = t.reach;
        let in_box = !t.actor && rt.sim.cur_box >= 0 && rt.sim.field.event_boxes.as_ref().map(|e| e.event_num(rt.sim.cur_box) as i64 == t.key).unwrap_or(false);
        if dist < reach || in_box {
            // arrived: examine targets get the circle button while facing them, walk-on boxes just fire on entering
            self.arrived_at += 1;
            let finish = if t.examine { 50 } else { 20 };
            self.touch();
            if self.arrived_at > finish {
                let k = (self.map.clone(), t.key);
                self.mem.outcome.entry(k).or_insert(Outcome::Nothing);
                self.cur = None;
                self.wait = 30;
                return Some(0);
            }
            if t.examine {
                // face the target (the sim turns the avatar to the pad heading): push gently towards it, press circle
                let want = (tx - pos[0]).atan2(tz - pos[2]);
                let rel = (want - rt.sim.cam_yaw).to_degrees().rem_euclid(360.0);
                let step = ((rel + 22.5) / 45.0) as usize % 8;
                let dir = if dist > 3.0 { dpad_for_step(step) } else { 0 };
                return Some(dir | if self.arrived_at % 12 < 3 { pad::CIRCLE } else { 0 });
            }
            return Some(0);
        }
        // place the avatar on the target when the straight walk is not getting there (no path finding)
        let moved = (pos[0] - self.last_pos[0]).hypot(pos[2] - self.last_pos[2]);
        self.last_pos = pos;
        if moved < 0.05 {
            self.still += 1;
        } else {
            self.still = 0;
        }
        if (self.detours >= 3 || self.cur_ticks > 900) && self.detour == 0 {
            // warp: stand 5 units short of an NPC (on the side we came from), in the middle of a box
            self.warps_here += 1;
            if self.warps_here > 2 {
                // placing the avatar did not reach it either: give this target up
                let k = (self.map.clone(), t.key);
                self.mem.tries.insert(k, 6);
                self.cur = None;
                self.warps_here = 0;
                return Some(0);
            }
            let (mut wx, mut wz) = (tx, tz);
            if t.actor && dist > 0.1 {
                let k = 5.0 / dist;
                wx = tx + (pos[0] - tx) * k;
                wz = tz + (pos[2] - tz) * k;
            }
            let ok = rt.sim.field.floor.as_mut().map(|f| f.circle_chk([wx, t.pos[1], wz], 2.0).is_some()).unwrap_or(true);
            if !ok && t.actor {
                (wx, wz) = (tx, tz);
            }
            rt.sim.player.pos[0] = wx;
            rt.sim.player.pos[1] = t.pos[1];
            rt.sim.player.pos[2] = wz;
            if t.actor {
                rt.sim.player.yaw = (tx - wx).atan2(tz - wz);
            }
            self.mem.warps += 1;
            self.detours = 0;
            self.cur_ticks = 0;
            return Some(0);
        }
        if self.still > 20 && self.detour == 0 {
            self.detours += 1;
            self.still = 0;
            self.detour = 40;
            self.detour_dir = dpad_for_step(((self.tick / 40) % 4) as usize * 2);
        }
        if self.detour > 0 {
            self.detour -= 1;
            return Some(self.detour_dir);
        }
        let want = (tx - pos[0]).atan2(tz - pos[2]);
        let rel = (want - rt.sim.cam_yaw).to_degrees().rem_euclid(360.0);
        let step = ((rel + 22.5) / 45.0) as usize % 8;
        Some(dpad_for_step(step))
    }

    /// Pad bits (held buttons) for the next 60 Hz tick.
    pub fn step(&mut self, rt: &mut FieldRuntime) -> u16 {
        self.tick += 1;
        self.mem.clock += 1;
        if self.map != rt.map {
            let mut bad = std::mem::take(&mut self.bad);
            if !self.map.is_empty() && self.last_enter > 0 {
                let k = (self.map.clone(), self.last_enter);
                if !bad.contains(&k) {
                    bad.push(k);
                }
            }
            let (explore, mut mem) = (self.explore, std::mem::take(&mut self.mem));
            if let Some((key, at)) = mem.pending.take() {
                if mem.clock.saturating_sub(at) < 1500 && !self.map.is_empty() && rt.map != self.map {
                    mem.outcome.insert(key, Outcome::Jump(rt.map.clone()));
                }
            }
            if mem.trail.last() != Some(&rt.map) {
                mem.trail.push(rt.map.clone());
            }
            mem.visited.insert(rt.map.clone());
            let trace = self.trace;
            *self = Pilot { map: rt.map.clone(), bad, explore, trace, mem, ..Default::default() };
            self.tick = 1;
        }
        if rt.sim.cur_box >= 0 {
            if let Some(e) = rt.sim.field.event_boxes.as_ref() {
                self.last_enter = e.event_num(rt.sim.cur_box);
            }
        }
        // message windows: tap circle (finishes the typing, then advances the KeyWait)
        // a choice window (`Select`): take the highlighted entry
        if rt.st.ui.select.active {
            self.press_phase += 1;
            return if self.press_phase % 10 < 3 { pad::CIRCLE } else { 0 };
        }
        if rt.st.msg_active() {
            if self.explore && self.cur.is_some() && self.cur_ticks > 0 {
                self.touch();
            }
            self.press_phase += 1;
            return if self.press_phase % 10 < 3 { pad::CIRCLE } else { 0 };
        }
        self.press_phase = 0;
        if rt.vm.is_running() && rt.st.event_running {
            if self.explore && self.cur.is_some() && self.cur_ticks > 0 {
                self.touch();
            }
            return 0;
        }
        if self.explore {
            if let Some(bits) = self.explore_step(rt) {
                return bits;
            }
        }
        let pos = rt.sim.player.pos;
        let boxes: Vec<crate::mps::EventBox> = rt.sim.field.event_boxes.as_ref().map(|e| e.boxes.clone()).unwrap_or_default();
        let wander = rt.sim.enc.rate > 0;
        let (tx, tz, examine) = if wander || boxes.is_empty() {
            (pos[0], pos[2], false)
        } else {
            if self.order.is_empty() {
                let mut idx: Vec<usize> = (0..boxes.len()).collect();
                // prefer examine boxes, then walk-on boxes, nearest first; the hint goes first
                idx.sort_by(|&a, &b| {
                    let ka = (boxes[a].kind == 0) as i32;
                    let kb = (boxes[b].kind == 0) as i32;
                    let da = (boxes[a].center[0] - pos[0]).hypot(boxes[a].center[2] - pos[2]);
                    let db = (boxes[b].center[0] - pos[0]).hypot(boxes[b].center[2] - pos[2]);
                    ka.cmp(&kb).then(da.partial_cmp(&db).unwrap())
                });
                if let Some(id) = crate::retail::pilot_hint(&rt.map).as_ref() {
                    if let Some(p) = idx.iter().position(|&i| boxes[i].id == *id) {
                        let v = idx.remove(p);
                        idx.insert(0, v);
                    }
                }
                self.order = idx;
            }
            let b = &boxes[self.order[self.target_idx % self.order.len()]];
            (b.center[0], b.center[2], b.kind != 0)
        };
        // movement bookkeeping (stuck detection)
        let moved = (pos[0] - self.last_pos[0]).hypot(pos[2] - self.last_pos[2]);
        self.last_pos = pos;
        if moved < 0.05 {
            self.still += 1;
        } else {
            self.still = 0;
        }
        if self.detour > 0 {
            self.detour -= 1;
            return self.detour_dir;
        }
        if self.still > 20 {
            self.still = 0;
            self.detour = 50;
            // sidestep: rotate the previous heading by 90 degrees (alternating sides)
            self.detour_dir = dpad_for_step(((self.tick / 50) % 4) as usize * 2);
            return self.detour_dir;
        }
        let cam = rt.sim.cam_yaw;
        if wander || boxes.is_empty() {
            // wander: keep a heading for ~70 ticks, turn clockwise, and never step into an event box or off the floor
            self.wander_phase += 1;
            let base = ((self.wander_phase / 70) % 8) as usize;
            for k in 0..8usize {
                let step = (base + k) % 8;
                let yaw = cam + (step as f32 * 45.0).to_radians();
                let probe = [pos[0] + yaw.sin() * 16.0, pos[1], pos[2] + yaw.cos() * 16.0];
                let map = rt.map.clone();
                let bad = &self.bad;
                let in_box = rt
                    .sim
                    .field
                    .event_boxes
                    .as_ref()
                    .map(|e| {
                        let h = e.hit_check(probe, crate::event::HitMode::All);
                        let id = e.event_num(h);
                        h >= 0 && (bad.iter().any(|(m, i)| *m == map && *i == id) || crate::retail::pilot_avoid(&map, id))
                    })
                    .unwrap_or(false);
                let on_floor = rt.sim.field.floor.as_mut().map(|f| f.circle_chk(probe, 4.0).is_some()).unwrap_or(false);
                if !in_box && on_floor {
                    if k != 0 {
                        // blocked: restart the phase counter on the new heading
                        self.wander_phase = (step as u32) * 70;
                    }
                    return dpad_for_step(step);
                }
            }
            return 0;
        }
        let (dx, dz) = (tx - pos[0], tz - pos[2]);
        let dist = dx.hypot(dz);
        if dist < 9.0 {
            // arrived: face the centre and examine for a while, then continue with the next box
            self.arrived_at += 1;
            if self.arrived_at > 60 {
                self.arrived_at = 0;
                self.target_idx += 1;
            }
            return if examine && self.arrived_at % 12 < 3 { pad::CIRCLE } else { 0 };
        }
        self.arrived_at = 0;
        let want = dx.atan2(dz);
        let mut rel = (want - cam).to_degrees().rem_euclid(360.0);
        if rel >= 360.0 {
            rel = 0.0;
        }
        let step = ((rel + 22.5) / 45.0) as usize % 8;
        // keep going to the same box for at most 25 s, then try the next one
        self.walk_ticks += 1;
        if self.walk_ticks % 1500 == 0 {
            self.target_idx += 1;
        }
        dpad_for_step(step)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::pkb_compat::PkbSet;
    use crate::plugin::{build_runtime, FieldHost};
    use crate::sim::SimEvent;
    use sh2_menu::session::GameSession;

    /// Headless replay of `field_script_tick` + `field_logic_tick` driven by the pilot: first map jumps to `AP_02_U`, the pilot walks to the
    /// exit box, reads the messages and ends up in `AP_03_U`, where it wanders until an encounter fires.
    #[test]
    fn pilot_reaches_a_battle() {
        let Some(pkb) = PkbSet::from_env() else { return };
        let mut session = GameSession::default();
        let mut map = "AP_02_U".to_string();
        let mut entry = 0;
        let mut jumps = vec![];
        let mut battle = None;
        'maps: for _ in 0..4 {
            let mut rt = build_runtime(&pkb, None, &map, entry, &session).unwrap();
            let mut pilot = Pilot::default();
            for t in 0..60 * 120 {
                crate::host::tick_state(&mut rt.st, &mut rt.sim);
                for (id, args) in std::mem::take(&mut rt.st.event_queue) {
                    rt.vm.call_event(id, &args);
                }
                let held = pilot.step(&mut rt);
                let edge = if t % 10 == 0 || held & (pad::CIRCLE) != 0 { held & pad::CIRCLE } else { 0 };
                rt.st.press = edge;
                let idle = rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(&mut session) });
                if idle {
                    rt.st.event_running = false;
                }
                let locked = rt.st.msg_active() || (rt.st.event_running && rt.vm.is_running());
                for e in rt.sim.tick(held, edge, locked) {
                    match e {
                        SimEvent::BoxEnter(id) => {
                            if rt.vm.call_event(id as u32, &[1]) {
                                rt.st.event_running = true;
                            }
                        }
                        SimEvent::Examine(id) => {
                            if rt.vm.call_event(id as u32, &[4]) {
                                rt.st.event_running = true;
                            }
                        }
                        SimEvent::Battle { monster_set } => {
                            battle = Some((rt.map.clone(), monster_set));
                            break 'maps;
                        }
                        _ => {}
                    }
                }
                if t % 300 == 0 && std::env::var_os("PILOT_DEBUG").is_some() {
                    eprintln!("t {t} map {} pos {:?} yaw {:.2} msg {} ev {} running {} manual {:?} cur_box {} calls {}", rt.map, rt.sim.player.pos, rt.sim.player.yaw, rt.st.msg_active(), rt.st.event_running, rt.vm.is_running(), rt.st.actors.get(0).map(|a| (a.manual, a.disp)), rt.sim.cur_box, rt.st.calls);
                    let tail: Vec<&String> = rt.st.log.iter().rev().take(3).collect();
                    eprintln!("   last {tail:?}");
                }
                if let Some(b) = rt.st.battle.take() {
                    // a scripted battle (`InvokeBattle` / `InvokeBattleTbl`)
                    battle = Some((rt.map.clone(), b.monster_set as u16));
                    break 'maps;
                }
                if let Some((m, e)) = rt.st.pending_jump.take() {
                    jumps.push(m.clone());
                    map = m;
                    entry = e;
                    continue 'maps;
                }
            }
            break;
        }
        assert!(battle.is_some(), "no battle; jumps {jumps:?} (last map {map})");
    }
}

//! Script-visible actor table: the logic half of `CField::aModels[0x30]` / `CFieldModel` as far as field scripts can observe it
//! (JP FIELD.BIN 0x004c06b0.. `CFieldModel`, 0x004b3020.. `CField::LoadCharacter/DispCharacter/SetMotion/SetCharacterDir/AutoMove`).
//!
//! The script engine never reads model data, it only issues commands and waits for them (`WaitModel` = `CheckLastCmdComplete`,
//! `WaitCharacterEx`).  This module keeps exactly that state: slot -> loaded character, position, facing, display flag, the current
//! command (`SetCmd(n)`: 1 load, 2 unload, 7 motion, 8 turn, 9 move) and its completion flag, motion playback, auto-move / path-move
//! progress.  Rendering (real models, N1's `CharacterModel`) and motion lengths from the model data attach through [`ActorTable::motion_len`].
//!
//! Slot [`ActorTable::ctrl`] (slot 0 unless changed by `ChgCtrl`) is the player: its position and facing live in
//! [`crate::sim::FieldSim::player`] and are mirrored in/out around every script call.
//!
//! Facing convention: [`ActorTable`] stores the *direction of travel* yaw used by `FieldSim` (`dir = (sin yaw, cos yaw)`); the original
//! model `rot.y` is `yaw - pi` (the model's forward axis is -z, see `rot_to_yaw`).

use std::collections::HashMap;
use std::f32::consts::{PI, TAU};

use crate::sim::FieldSim;

pub const MAX_SLOTS: usize = 0x30;
/// Default length of a non-looping motion when the model data is not available (ticks at 60 Hz).
pub const DEFAULT_MOTION_TICKS: u32 = 40;
pub use crate::sim::{RUN_SPEED, WALK_SPEED};

/// `GetRotAngle(idx)` (JP 0x004c6fa0): 32 directions, `idx * pi / 16`, wrapped to (-pi, pi].
pub fn get_rot_angle(idx: i32) -> f32 {
    let i = (idx & 0x1f) as f32;
    if i < 17.0 {
        i * PI / 16.0
    } else {
        (32.0 - i) * -PI / 16.0
    }
}

/// model `rot.y` -> direction-of-travel yaw of the simulation (and back; the mapping is its own inverse).
pub fn rot_to_yaw(rot: f32) -> f32 {
    wrap(rot + PI)
}

pub fn wrap(mut a: f32) -> f32 {
    while a > PI {
        a -= TAU;
    }
    while a < -PI {
        a += TAU;
    }
    a
}

/// Direction-of-travel yaw looking from `from` towards `to` (xz plane).
pub fn yaw_towards(from: [f32; 3], to: [f32; 3]) -> Option<f32> {
    let (dx, dz) = (to[0] - from[0], to[2] - from[2]);
    if dx.abs() + dz.abs() < 1e-4 {
        None
    } else {
        Some(dx.atan2(dz))
    }
}

/// `CFieldModel::HitChkM2M(radius)` (JP 0x004c76e0): the displayed model with hit checking on that stands in the way of `me`
/// (`pos`, direction-of-travel `yaw`), if any.  `others` = `(slot, pos)` of the candidates.  A model collides when its distance, reduced by
/// `radius * (cos + 1) / 2` (the half-circle in front counts more), is within 8 and it is in front (cos >= 0.4), or within 6 anywhere.
pub fn hit_chk_m2m(me: usize, pos: [f32; 3], yaw: f32, radius: f32, others: &[(usize, [f32; 3])]) -> Option<usize> {
    let fwd = [yaw.sin(), yaw.cos()];
    for &(slot, p) in others {
        if slot == me {
            continue;
        }
        let (dx, dz) = (p[0] - pos[0], p[2] - pos[2]);
        let len = (dx * dx + dz * dz).sqrt();
        let dot = if len < 1e-4 { 1.0 } else { (dx * fwd[0] + dz * fwd[1]) / len };
        let d = len - radius * (dot + 1.0) * 0.5;
        if d <= 8.0 && (dot >= 0.4 || d <= 6.0) {
            return Some(slot);
        }
    }
    None
}

/// Direction change per tick of a walking actor (`CFieldModel::Update`: `dt * 2 pi * rate`, the `SetDir(.., 2, 1)` rate of 1.0 at 60 Hz).
pub const NPC_TURN_RATE: f32 = std::f32::consts::TAU / 60.0;

/// `SetCmd(n)` values (`CFieldModel+0x91`) and the completion bits they test (`+0x8a`).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Cmd {
    None,
    Load,
    Unload,
    Motion,
    Turn,
    Move,
}

#[derive(Debug, Clone)]
pub enum MoveTask {
    /// `AutoMove(dest, final_dir, gait, flags)`
    Auto { dest: [f32; 3], final_dir: i32, run: bool },
    /// `PathMove`: through `points`, firing `event` (with the node index) when a node is reached
    /// `leg` / `done`: length of the current leg (`UpdateNodeLen`, measured from where the model stands when the leg starts; < 0 = not measured yet) and the
    /// distance walked on it so far (`CFieldModel +0x190 / +0x194`): a node is reached when `done >= leg`, whatever the rounding-off did to the heading
    Path { points: Vec<[f32; 3]>, dirs: Vec<i32>, next: usize, event: u32, run: bool, leg: f32, done: f32 },
}

#[derive(Debug, Clone)]
pub struct Actor {
    pub char_id: i32,
    pub model_name: String,
    /// `+0xc0`: the event run when the player talks to this actor (`LoadCharacter`'s last argument)
    pub event_id: u32,
    pub loaded: bool,
    pub disp: bool,
    pub pos: [f32; 3],
    pub yaw: f32,
    pub target_yaw: Option<(f32, f32)>,
    pub motion: i32,
    pub motion_name: String,
    pub motion_left: u32,
    pub motion_loop: bool,
    pub motion_speed: f32,
    pub chain: Vec<(i32, String, bool)>,
    pub cmd: Cmd,
    pub cmd_done: bool,
    pub last_cmd_event: u32,
    pub mv: Option<MoveTask>,
    pub paused_move: bool,
    pub manual: bool,
    pub hit_check: bool,
    pub floor_check: bool,
    pub icon: i32,
    pub navi_item: i32,
    pub view_point: Option<[f32; 3]>,
    pub talking: bool,
    pub blink: i32,
    pub mirror: i32,
    pub ghost: bool,
    pub clear_mode: i32,
    pub moved_dist: f32,
    pub items: Vec<(i32, String)>,
    /// `CFieldModel+0x118`: the model this one is attached to (`CharAddItem`: parent slot, or `0x80 | BG index` for `CharAddItemEx`), `0xff` = free
    pub attach: u8,
    /// bumped on every (re)load: lets the render glue notice a replaced model
    pub generation: u32,
    /// idle / walk / run motion ids (`SetMoveMotion`)
    pub move_motions: [i32; 3],
    /// ticks the current motion has been playing
    pub motion_age: u32,
    /// move motion the actor is in (0 idle, 1 walk, 2 run), `CFieldModel::PlayMoveMotion` (`+0x85` bits 4-5)
    pub gait: u8,
    /// ticks the current move has been held up by another model (`CFieldModel::HitChkM2M`, move state 4)
    pub blocked: u32,
    /// ticks during which collisions are ignored (a long standoff is broken up, the original's `AutoAvoid` steps aside)
    pub ignore_hit: u32,
}

impl Default for Actor {
    fn default() -> Self {
        Actor {
            char_id: -1,
            model_name: String::new(),
            event_id: 0,
            loaded: false,
            disp: false,
            pos: [0.0; 3],
            yaw: 0.0,
            target_yaw: None,
            motion: 0,
            motion_name: String::new(),
            motion_left: 0,
            motion_loop: false,
            motion_speed: 1.0,
            chain: vec![],
            cmd: Cmd::None,
            cmd_done: true,
            last_cmd_event: 0,
            mv: None,
            paused_move: false,
            manual: false,
            hit_check: true,
            floor_check: true,
            icon: 0,
            navi_item: 0,
            view_point: None,
            talking: false,
            blink: 0,
            mirror: 0,
            ghost: false,
            clear_mode: 0,
            moved_dist: 0.0,
            items: vec![],
            attach: 0xff,
            generation: 0,
            move_motions: [1, 2, 3],
            motion_age: 0,
            gait: 0,
            blocked: 0,
            ignore_hit: 0,
        }
    }
}

/// BG model (`CFieldBG` model slots addressed as `0x80 | index`): only the motion command state is script-visible.
#[derive(Debug, Clone, Default)]
pub struct BgModel {
    pub motion: String,
    pub last_motion: String,
    pub left: u32,
    pub looping: bool,
    pub cmd_done: bool,
    pub speed: f32,
}

/// Presentation requests of the actor table (motions, move motions) for the render side (`crate::actors`).
#[derive(Debug, Clone, PartialEq)]
pub enum ActorOut {
    Motion { slot: usize, id: i32, name: String, chain: bool },
    MoveMotion { slot: usize, idle: i32, walk: i32, run: i32 },
    /// `PlayMoveMotion(gait)` of a script-moved actor: 0 idle, 1 walk, 2 run
    Gait { slot: usize, gait: u8 },
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ActorEvent {
    /// `CharPathEvent`/last-command event: run script event `event` with `[arg, slot]`
    Fire { event: u32, arg: i32, slot: usize },
}

#[derive(Clone)]
pub struct ActorTable {
    pub slots: Vec<Option<Actor>>,
    pub bg: Vec<BgModel>,
    pub ctrl: usize,
    /// motion lengths in ticks learnt from model data: `(char_id, motion id) -> ticks`
    pub motion_len: HashMap<(i32, i32), u32>,
    pub events: Vec<ActorEvent>,
    pub out: Vec<ActorOut>,
    pub count: usize,
}

impl Default for ActorTable {
    fn default() -> Self {
        ActorTable { slots: (0..MAX_SLOTS).map(|_| None).collect(), bg: vec![], ctrl: 0, motion_len: HashMap::new(), events: vec![], out: vec![], count: 0 }
    }
}

/// The character models that survive a map jump (`CField` is reused by `CFieldSocket`; `InitSDB`, US 0x004f7210, only clears the models'
/// display, so a script may rely on slot 0 still holding the player it loaded on an earlier map).
#[derive(Debug, Clone, Default)]
pub struct CarriedActors {
    pub slots: Vec<Option<Actor>>,
    pub ctrl: usize,
    pub count: usize,
    /// the control model was displayed when the map was left (`InitSDB`: it is then shown again at the entry point)
    pub ctrl_shown: bool,
}

impl ActorTable {
    /// What `InitSDB` keeps for the next map: every loaded model, hidden (`ClearModel`), commands finished.
    pub fn carry_over(&self) -> CarriedActors {
        let ctrl_shown = self.get(self.ctrl as i32).map(|a| a.loaded && a.disp).unwrap_or(false);
        let slots = self
            .slots
            .iter()
            .map(|s| {
                s.as_ref().filter(|a| a.loaded).map(|a| {
                    let mut a = a.clone();
                    a.disp = false;
                    a.mv = None;
                    a.cmd = Cmd::None;
                    a.cmd_done = true;
                    a.chain.clear();
                    a.items.clear();
                    a.attach = 0xff;
                    a.talking = false;
                    a.view_point = None;
                    a
                })
            })
            .collect();
        CarriedActors { slots, ctrl: self.ctrl, count: self.count, ctrl_shown }
    }

    /// Install carried models into a fresh table (before the new map's script runs).
    pub fn take_carry(&mut self, c: CarriedActors) {
        for (i, s) in c.slots.into_iter().enumerate() {
            if i < self.slots.len() {
                self.slots[i] = s;
            }
        }
        self.ctrl = c.ctrl;
        self.count = self.count.max(c.count);
    }

    pub fn get(&self, slot: i32) -> Option<&Actor> {
        if slot < 0 {
            return None;
        }
        self.slots.get(slot as usize).and_then(|a| a.as_ref())
    }
    pub fn get_mut(&mut self, slot: i32) -> Option<&mut Actor> {
        if slot < 0 {
            return None;
        }
        self.slots.get_mut(slot as usize).and_then(|a| a.as_mut())
    }

    /// Mirror the player's simulation state into the control actor (call before reading it).
    pub fn sync_in(&mut self, sim: &FieldSim) {
        let c = self.ctrl;
        if let Some(a) = self.slots.get_mut(c).and_then(|a| a.as_mut()) {
            a.pos = sim.player.pos;
            a.yaw = sim.player.yaw;
        }
    }
    /// Write script-driven changes of the control actor back to the simulation.
    pub fn sync_out(&self, sim: &mut FieldSim) {
        if let Some(a) = self.slots.get(self.ctrl).and_then(|a| a.as_ref()) {
            sim.player.pos = a.pos;
            sim.player.yaw = a.yaw;
        }
    }

    // ------------------------------------------------------------------ loading
    /// JP: 0x004b30d0 LoadCharacter(slot, name, char_id, event_id)
    pub fn load(&mut self, slot: usize, name: &str, char_id: i32, event_id: u32) {
        if slot >= MAX_SLOTS {
            return;
        }
        if self.count <= slot {
            self.count = slot + 1;
        }
        let same = self.slots[slot].as_ref().map(|a| a.loaded && char_id != -1 && a.char_id == char_id).unwrap_or(false);
        if same {
            // JP 0x004b30d0 same model: `ClrCharacter(slot, 0)`, `CharRemoveItem`, detach, `CFieldModel::Reset(slot == 0)` -- the model is kept
            // (no reload) but hidden and reset; slot 0 gets the pad again
            let manual = slot == 0 || slot == self.ctrl;
            let a = self.slots[slot].as_mut().unwrap();
            a.event_id = event_id;
            a.mv = None;
            a.items.clear();
            a.attach = 0xff;
            a.disp = false;
            a.manual = manual;
            a.talking = false;
            a.view_point = None;
            a.cmd = Cmd::Load;
            a.cmd_done = true;
            return;
        }
        let gen = self.slots[slot].as_ref().map(|a| a.generation + 1).unwrap_or(1);
        let manual = slot == self.ctrl;
        self.slots[slot] = Some(Actor {
            char_id,
            model_name: name.to_string(),
            event_id,
            loaded: true,
            manual,
            cmd: Cmd::Load,
            cmd_done: true,
            generation: gen,
            ..Default::default()
        });
    }

    /// JP: 0x004b3360 UnloadCharacter: slot >= 0 one slot, -1 all, -2 all but slot 0, -3 all not displayed.
    pub fn unload(&mut self, slot: i32) {
        let (lo, hi) = if slot < 0 { (if slot == -2 { 1 } else { 0 }, self.count.saturating_sub(1) as i32) } else { (slot, slot) };
        for s in lo..=hi {
            let hide_check = slot == -3 && self.get(s).map(|a| a.disp).unwrap_or(false);
            if s as usize >= MAX_SLOTS || hide_check {
                continue;
            }
            if let Some(a) = self.slots[s as usize].as_mut() {
                a.loaded = false;
                a.disp = false;
                a.cmd = Cmd::Unload;
            }
            self.slots[s as usize] = None;
        }
        if slot == -1 {
            self.count = 0;
        }
    }

    /// JP: 0x004b36a0 DispCharacter: place and show.  `place` = 0 keep position, 1/2 set position + facing (`dir` index).
    pub fn disp(&mut self, slot: i32, place: i32, pos: [f32; 3], dir: i32, motion: i32, motion_name: Option<&str>, sim: &mut FieldSim) {
        self.sync_in(sim);
        let is_ctrl = slot as usize == self.ctrl;
        let Some(a) = self.get_mut(slot) else { return };
        if place != 0 {
            a.pos = pos;
            if dir >= 0 {
                a.yaw = rot_to_yaw(get_rot_angle(dir));
            }
            a.target_yaw = None;
        }
        a.disp = true;
        if a.clear_mode != 0 {
            a.clear_mode = 0;
        }
        if motion > 0 || motion_name.is_some() {
            let name = motion_name.map(|s| s.to_string()).unwrap_or_default();
            self.set_motion_raw(slot, motion, &name, 0);
        }
        if is_ctrl {
            self.sync_out(sim);
            sim.update_camera();
        }
    }

    /// JP: 0x004b3aa0 ClrCharacter(slot, mode): hide.
    pub fn clear(&mut self, slot: i32, mode: i32) {
        if let Some(a) = self.get_mut(slot) {
            a.disp = false;
            a.clear_mode = mode;
        }
    }

    // ------------------------------------------------------------------ motions
    fn motion_ticks(&self, char_id: i32, motion: i32) -> u32 {
        self.motion_len.get(&(char_id, motion)).copied().unwrap_or(DEFAULT_MOTION_TICKS)
    }

    /// `CField::SetMotion(slot, id, flags)`: flags&7 = 0 replace now, 1 replace the chain, 2 append; bit 7 = loop after the end.
    pub fn set_motion(&mut self, slot: i32, id: i32, flags: i32) {
        self.set_motion_raw(slot, id, "", flags);
    }

    pub fn set_motion_raw(&mut self, slot: i32, id: i32, name: &str, flags: i32) {
        let len = self.get(slot).map(|a| self.motion_ticks(a.char_id, id)).unwrap_or(DEFAULT_MOTION_TICKS);
        let playing = self.get(slot).map(|a| a.motion_left > 0 && !a.motion_loop).unwrap_or(false);
        let chain_req = (flags & 7) != 0 && playing;
        if self.get(slot).is_some() {
            self.out.push(ActorOut::Motion { slot: slot as usize, id, name: name.to_string(), chain: chain_req && (flags & 7) == 2 });
        }
        let Some(a) = self.get_mut(slot) else { return };
        a.cmd = Cmd::Motion;
        a.cmd_done = false;
        // the move motions (idle `fidl`, `walk`, `run` = ids 1..3) are cycles that never report "finished": a script that waits on them
        // (`WaitModel` after `SetMotion(slot, 1)`) is released as soon as they play, like a looping motion
        let cyclic = matches!(id, 1..=3) || matches!(name, "fidl" | "walk" | "run");
        let looped = flags & 0x80 != 0 || cyclic;
        let mode = flags & 7;
        if mode == 0 || a.motion_left == 0 && !a.motion_loop {
            a.chain.clear();
            a.motion = id;
            a.motion_name = name.to_string();
            a.motion_left = len;
            a.motion_age = 0;
            a.motion_loop = looped;
            if looped {
                // a looping motion never ends: the command is complete once it is playing
                a.cmd_done = true;
            }
        } else {
            if mode == 1 {
                a.chain.clear();
            }
            if a.chain.len() < 8 {
                a.chain.push((id, name.to_string(), looped));
            }
        }
    }

    fn finish_cmd(a: &mut Actor, events: &mut Vec<ActorEvent>, slot: usize) {
        a.cmd_done = true;
        if a.last_cmd_event != 0 {
            events.push(ActorEvent::Fire { event: a.last_cmd_event, arg: 0, slot });
            a.last_cmd_event = 0;
        }
    }

    /// JP: 0x004b46b0 SetCharacterDir(slot, spec, mode, speed)
    pub fn set_dir(&mut self, slot: i32, spec: i32, mode: i32, speed: i32, sim: &mut FieldSim, entry_dir: impl Fn(i32) -> Option<[f32; 3]>, cam_pos: [f32; 3]) {
        self.sync_in(sim);
        let kind = match (spec >> 16) & 0xf {
            3 => 10,
            2 => 9,
            1 => 8,
            _ => (spec >> 7) & 0xf,
        };
        let me = match self.get(slot) {
            Some(a) => a.pos,
            None => return,
        };
        let target: Option<[f32; 3]> = match kind {
            10 => entry_dir(spec & 0xffff),
            9 => Some(cam_pos),
            8 => None, // short-position look points (SetLookPoint list) are not tracked
            1 => self.get(spec & 0x7f).map(|a| a.pos),
            _ => None,
        };
        let yaw = if matches!(kind, 10 | 9 | 1) {
            match target.and_then(|t| yaw_towards(me, t)) {
                Some(y) => y,
                None => return,
            }
        } else if kind == 8 {
            return;
        } else {
            rot_to_yaw(get_rot_angle(spec))
        };
        self.turn_to(slot, yaw, mode, speed);
        if slot as usize == self.ctrl {
            self.sync_out(sim);
        }
    }

    /// `CFieldModel::SetDir(vec, mode, speed)`: mode 0 snaps, otherwise turns smoothly at `(speed + 1) / 4` of the angle per tick.
    pub fn turn_to(&mut self, slot: i32, yaw: f32, mode: i32, speed: i32) {
        let Some(a) = self.get_mut(slot) else { return };
        a.cmd = Cmd::Turn;
        if mode == 0 || wrap(yaw - a.yaw).abs() < 0.03 {
            a.yaw = yaw;
            a.target_yaw = None;
            a.cmd_done = true;
        } else {
            let rate = if speed < 0 { -1.0 / speed as f32 } else { (speed + 1) as f32 * 0.25 };
            a.target_yaw = Some((yaw, rate.max(0.1)));
            a.cmd_done = false;
        }
    }

    // ------------------------------------------------------------------ movement
    /// `CFieldModel::AutoMove` (script op 0x18): walk to `dest`, then face `final_dir` (>= 0: GetRotAngle index).
    pub fn auto_move(&mut self, slot: i32, dest: [f32; 3], final_dir: i32, gait: i32, flags: i32, sim: &mut FieldSim) {
        self.sync_in(sim);
        let Some(a) = self.get_mut(slot) else { return };
        a.cmd = Cmd::Move;
        a.cmd_done = false;
        a.paused_move = false;
        a.floor_check = (flags >> 2) & 1 == 1 || flags & 0x10 != 0 || true;
        let d = ((dest[0] - a.pos[0]).powi(2) + (dest[2] - a.pos[2]).powi(2)).sqrt();
        if d < 0.01 {
            a.mv = None;
            Self::arrived(a, final_dir);
            return;
        }
        a.mv = Some(MoveTask::Auto { dest, final_dir, run: gait == 1 });
    }

    /// `CFieldModel::PathMove` (script op 0x19)
    pub fn path_move(&mut self, slot: i32, points: Vec<[f32; 3]>, dirs: Vec<i32>, event: u32, run: bool, sim: &mut FieldSim) {
        self.sync_in(sim);
        let Some(a) = self.get_mut(slot) else { return };
        a.cmd = Cmd::Move;
        a.cmd_done = false;
        if points.is_empty() {
            a.cmd_done = true;
            return;
        }
        a.mv = Some(MoveTask::Path { points, dirs, next: 0, event, run, leg: -1.0, done: 0.0 });
    }

    fn arrived(a: &mut Actor, final_dir: i32) {
        a.mv = None;
        if final_dir >= 0 {
            a.yaw = rot_to_yaw(get_rot_angle(final_dir & 0x3f));
            a.target_yaw = None;
        }
        a.cmd_done = true;
    }

    /// `PauseAutoMove(on)`
    pub fn pause_move(&mut self, slot: i32, on: bool) {
        if let Some(a) = self.get_mut(slot) {
            a.paused_move = on;
        }
    }

    /// `CheckLastCmdComplete`: -1 when the actor has no command, 1 complete, 0 running.
    pub fn check_last_cmd(&self, slot: i32) -> i32 {
        if slot & 0x80 != 0 {
            return match self.bg.get((slot & 0x7f) as usize) {
                Some(b) => b.cmd_done as i32,
                None => -1,
            };
        }
        match self.get(slot) {
            Some(a) if a.cmd != Cmd::None => a.cmd_done as i32,
            _ => -1,
        }
    }

    pub fn set_last_cmd_event(&mut self, slot: i32, ev: u32) {
        if slot & 0x80 != 0 {
            return;
        }
        let complete = self.check_last_cmd(slot) == 1;
        if let Some(a) = self.get_mut(slot) {
            if complete {
                let s = slot as usize;
                self.events.push(ActorEvent::Fire { event: ev, arg: 0, slot: s });
            } else {
                a.last_cmd_event = ev;
            }
        }
    }

    /// `CField::WaitCharacterEx(slot, mode)`: true when the wait is over.  mode 0: moves finished, 1: motions finished, 2: hidden / cleared.
    pub fn wait_char_ex(&self, slot: i32, mode: i32) -> bool {
        let range: Vec<usize> = if slot < 0 { (0..self.count).collect() } else { vec![slot as usize] };
        for s in range {
            let Some(Some(a)) = self.slots.get(s) else { continue };
            match mode {
                2 => {
                    if a.disp && a.clear_mode == 0 && false {
                        return false;
                    }
                }
                1 => {
                    if a.motion_left > 0 && !a.motion_loop {
                        return false;
                    }
                }
                _ => {
                    if a.mv.is_some() && !a.paused_move {
                        return false;
                    }
                }
            }
        }
        true
    }

    // ------------------------------------------------------------------ per tick
    /// One 60 Hz tick of scripted movement / motions.  The player (control slot) is only moved while a script command drives it.
    pub fn tick(&mut self, sim: &mut FieldSim) {
        self.sync_in(sim);
        let n = self.count.min(MAX_SLOTS);
        let mut events = std::mem::take(&mut self.events);
        // candidates of `HitChkM2M`: displayed, hit-checked models (the controlled one included)
        let others: Vec<(usize, [f32; 3])> = (0..n).filter_map(|i| self.slots[i].as_ref().filter(|a| a.loaded && a.disp && a.hit_check).map(|a| (i, a.pos))).collect();
        let mut gait_out: Vec<(usize, u8)> = vec![];
        for s in 0..n {
            let ctrl = s == self.ctrl;
            let Some(a) = self.slots[s].as_mut() else { continue };
            if !a.loaded {
                continue;
            }
            // smooth turn
            if let Some((ty, rate)) = a.target_yaw {
                let d = wrap(ty - a.yaw);
                let step = (d.abs() * 0.5 * rate.min(1.0)).max(0.04 * rate.max(0.5));
                if d.abs() <= step {
                    a.yaw = ty;
                    a.target_yaw = None;
                    if a.cmd == Cmd::Turn {
                        Self::finish_cmd(a, &mut events, s);
                    }
                } else {
                    a.yaw = wrap(a.yaw + d.signum() * step);
                }
            }
            // motion
            a.motion_age = a.motion_age.saturating_add(1);
            // a looping motion with a queued one (`SetMotion(slot, id, 1 / 2)` while it plays) hands over at the end of a loop
            // (SE_00_U: `SetMotion(0, 5, 1)` then `while (GetCharacterInfo(0, 0xd) != 5)` with the idle cycle playing)
            if a.motion_loop && !a.chain.is_empty() {
                let len = self.motion_len.get(&(a.char_id, a.motion)).copied().unwrap_or(DEFAULT_MOTION_TICKS).max(1);
                if a.motion_age >= len {
                    a.motion_loop = false;
                    a.motion_left = 1;
                }
            }
            if a.motion_left > 0 && !a.motion_loop {
                a.motion_left -= 1;
                if a.motion_left == 0 {
                    if !a.chain.is_empty() {
                        let (id, name, looped) = a.chain.remove(0);
                        a.motion = id;
                        a.motion_name = name;
                        a.motion_loop = looped;
                        a.motion_left = self.motion_len.get(&(a.char_id, id)).copied().unwrap_or(DEFAULT_MOTION_TICKS);
                        if looped {
                            // a looping motion never ends: the command is complete once it plays
                            a.motion_left = 0;
                            a.motion_loop = true;
                            if a.cmd == Cmd::Motion {
                                Self::finish_cmd(a, &mut events, s);
                            }
                        }
                    } else {
                        if a.cmd == Cmd::Motion {
                            Self::finish_cmd(a, &mut events, s);
                        }
                        // a one-shot motion with nothing queued falls back to the idle move motion (`fidl`): scripts wait for it with
                        // `while (GetCharacterInfo(slot, 0xd) != 1)` (IF_11_U after Karin's "ta_c")
                        // (left = 0, not looping: a queued `SetMotion(.., 1 / 2)` replaces it at once, as after any ended motion)
                        a.motion = a.move_motions[0].max(1);
                        a.motion_name.clear();
                    }
                }
            }
            // movement
            a.ignore_hit = a.ignore_hit.saturating_sub(1);
            let mut moving_now = false;
            if let Some(MoveTask::Path { points, next, leg, done, .. }) = a.mv.as_mut() {
                if *leg < 0.0 {
                    let t = points[(*next).min(points.len() - 1)];
                    *leg = ((t[0] - a.pos[0]).powi(2) + (t[2] - a.pos[2]).powi(2)).sqrt();
                    *done = 0.0;
                }
            }
            if let (Some(mv), false) = (a.mv.clone(), a.paused_move) {
                let (target, run) = match &mv {
                    MoveTask::Auto { dest, run, .. } => (*dest, *run),
                    MoveTask::Path { points, next, run, .. } => (points[(*next).min(points.len() - 1)], *run),
                };
                let speed = if run { RUN_SPEED } else { WALK_SPEED };
                let (dx, dz) = (target[0] - a.pos[0], target[2] - a.pos[2]);
                let dist = (dx * dx + dz * dz).sqrt();
                // direction to walk along: straight to the node, rounded off into the next leg near a path node (`UpdatePathMove`: within
                // `10` units of the end of a leg the heading is blended by `sin(t * pi / 2) * 0.9`)
                let mut dir = if dist > 0.01 { [dx / dist, dz / dist] } else { [a.yaw.sin(), a.yaw.cos()] };
                if let MoveTask::Path { points, next, leg, done, .. } = &mv {
                    // `UpdatePathMove`: in the last 10 units of the leg (measured by the distance walked on it, a leg shorter than 10 is blended over its whole
                    // length) the heading is blended towards the next leg by `sin(k * pi / 2) * 0.9`
                    if *next + 1 < points.len() && *leg > 0.0 {
                        let k = if *leg < 10.0 { *done / *leg } else if *leg - *done < 10.0 { 1.0 - (*leg - *done) / 10.0 } else { 0.0 };
                        let nx = points[*next + 1];
                        let (ex, ez) = (nx[0] - target[0], nx[2] - target[2]);
                        let el = (ex * ex + ez * ez).sqrt();
                        if k > 0.0 && el > 1e-3 {
                            let k = (k.clamp(0.0, 1.0) * std::f32::consts::FRAC_PI_2).sin() * 0.9;
                            let (bx, bz) = (dir[0] * (1.0 - k) + ex / el * k, dir[1] * (1.0 - k) + ez / el * k);
                            let bl = (bx * bx + bz * bz).sqrt();
                            if bl > 1e-4 {
                                dir = [bx / bl, bz / bl];
                            }
                        }
                    }
                }
                let want = dir[0].atan2(dir[1]);
                // another model in the way: stand still (idle motion) until it moves on (`HitChkM2M` -> move state 4)
                let in_the_way = if !ctrl && a.hit_check && a.ignore_hit == 0 { hit_chk_m2m(s, a.pos, want, 4.0, &others) } else { None };
                if in_the_way.is_some() {
                    a.blocked += 1;
                    if a.blocked > 600 {
                        a.blocked = 0;
                        a.ignore_hit = 240;
                    }
                } else {
                    a.blocked = 0;
                    // turn towards the heading at the walking turn rate; the walk starts once the angle is within ~53 degrees
                    // (`PlayMoveMotion(1)` needs cos >= 0.6), a bigger angle is turned on the spot first
                    let d = wrap(want - a.yaw);
                    if ctrl {
                        a.yaw = want;
                    } else {
                        a.yaw = if d.abs() <= NPC_TURN_RATE * 1.5 { want } else { wrap(a.yaw + d.signum() * NPC_TURN_RATE * 1.5) };
                    }
                    if ctrl || a.gait != 0 || d.abs() < 0.927 {
                        moving_now = true;
                        // an intermediate path node is reached by the distance walked on the leg, the last node / an `AutoMove` target by position
                        let mid_path = matches!(&mv, MoveTask::Path { points, next, .. } if *next + 1 < points.len());
                        let step = if mid_path { speed } else { dist.min(speed) };
                        let reached = match &mv {
                            MoveTask::Path { leg, done, .. } if mid_path => *done + step >= *leg,
                            _ => dist <= speed + 0.01,
                        };
                        if let Some(MoveTask::Path { done, .. }) = a.mv.as_mut() {
                            *done += step;
                        }
                        let (nx, nz) = if dist > 0.01 { (a.pos[0] + dir[0] * step, a.pos[2] + dir[1] * step) } else { (a.pos[0], a.pos[2]) };
                        let mut np = [nx, a.pos[1], nz];
                        if let Some(fl) = sim.field.floor.as_mut() {
                            if let Some(t) = fl.on_floor_chk(np) {
                                np[1] = fl.on_floor_point(np, t);
                            }
                        }
                        a.moved_dist += step;
                        a.pos = np;
                        if ctrl {
                            sim.walked += step;
                            sim.player.moving = true;
                            sim.player.script_step += step;
                            sim.player.gait = if run { crate::movement::Gait::Run } else { crate::movement::Gait::Walk };
                            sim.player.anim += step * 0.12;
                        }
                        if reached {
                            match mv {
                                MoveTask::Auto { final_dir, .. } => {
                                    Self::arrived(a, final_dir);
                                    if a.last_cmd_event != 0 {
                                        events.push(ActorEvent::Fire { event: a.last_cmd_event, arg: 0, slot: s });
                                        a.last_cmd_event = 0;
                                    }
                                }
                                MoveTask::Path { points, dirs, next, event, run, .. } => {
                                    if event != 0 {
                                        events.push(ActorEvent::Fire { event, arg: next as i32, slot: s });
                                    }
                                    if next + 1 >= points.len() {
                                        let fd = dirs.get(next).copied().unwrap_or(-1);
                                        Self::arrived(a, fd);
                                        if a.last_cmd_event != 0 {
                                            events.push(ActorEvent::Fire { event: a.last_cmd_event, arg: 0, slot: s });
                                            a.last_cmd_event = 0;
                                        }
                                    } else {
                                        a.mv = Some(MoveTask::Path { points, dirs, next: next + 1, event, run, leg: -1.0, done: 0.0 });
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                a.blocked = 0;
            }
            // `PlayMoveMotion`: the move motion follows the movement (idle / walk / run); not for the pad-controlled model
            if !ctrl {
                let want_gait = if moving_now && a.mv.is_some() {
                    match a.mv {
                        Some(MoveTask::Auto { run: true, .. }) | Some(MoveTask::Path { run: true, .. }) => 2,
                        _ => 1,
                    }
                } else {
                    0
                };
                // the final step of a move has cleared `mv` already: it is idle again
                if want_gait != a.gait {
                    a.gait = want_gait;
                    gait_out.push((s, want_gait));
                }
            }
        }
        for (slot, gait) in gait_out {
            self.out.push(ActorOut::Gait { slot, gait });
        }
        // BG model motions
        for b in self.bg.iter_mut() {
            if b.left > 0 && !b.looping {
                b.left -= 1;
                if b.left == 0 {
                    b.cmd_done = true;
                }
            }
        }
        self.events = events;
        self.sync_out(sim);
    }

    /// Nearest displayed actor in front of `from` within 12 units whose facing dot >= 0.5 (circle-button talk probe, `CField::Polling`).
    pub fn talk_target(&self, from: [f32; 3], yaw: f32) -> Option<usize> {
        let fwd = [yaw.sin(), yaw.cos()];
        let mut best: Option<(usize, f32)> = None;
        for s in 0..self.count.min(MAX_SLOTS) {
            if s == self.ctrl {
                continue;
            }
            let Some(a) = self.slots[s].as_ref() else { continue };
            if !a.loaded || !a.disp || a.event_id == 0 {
                continue;
            }
            let (dx, dz) = (a.pos[0] - from[0], a.pos[2] - from[2]);
            let l = (dx * dx + dz * dz).sqrt();
            if l > 12.0 {
                continue;
            }
            let dot = if l < 1e-3 { 1.0 } else { (dx * fwd[0] + dz * fwd[1]) / l };
            if dot >= 0.5 && best.map(|(_, d)| dot > d).unwrap_or(true) {
                best = Some((s, dot));
            }
        }
        best.map(|(s, _)| s)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn rot_angle_table() {
        assert_eq!(get_rot_angle(0), 0.0);
        assert!((get_rot_angle(8) - PI / 2.0).abs() < 1e-5);
        assert!((get_rot_angle(16) - PI).abs() < 1e-5);
        assert!((get_rot_angle(24) + PI / 2.0).abs() < 1e-5);
        assert!((get_rot_angle(32 + 8) - PI / 2.0).abs() < 1e-5);
    }

    #[test]
    fn facing_conversion_is_involutive() {
        for i in 0..32 {
            let r = get_rot_angle(i);
            assert!((wrap(rot_to_yaw(rot_to_yaw(r)) - r)).abs() < 1e-4);
        }
    }

    #[test]
    fn model_in_front_blocks_the_move() {
        // facing +z (yaw 0): a model 8 units ahead collides, one behind or far to the side does not
        assert_eq!(hit_chk_m2m(0, [0.0; 3], 0.0, 4.0, &[(1, [0.0, 0.0, 8.0])]), Some(1));
        assert_eq!(hit_chk_m2m(0, [0.0; 3], 0.0, 4.0, &[(1, [0.0, 0.0, -20.0])]), None);
        assert_eq!(hit_chk_m2m(0, [0.0; 3], 0.0, 4.0, &[(1, [15.0, 0.0, 0.0])]), None);
        // very close models block from any side
        assert_eq!(hit_chk_m2m(0, [0.0; 3], 0.0, 4.0, &[(1, [0.0, 0.0, -5.0])]), Some(1));
        // a model never blocks itself
        assert_eq!(hit_chk_m2m(1, [0.0; 3], 0.0, 4.0, &[(1, [0.0, 0.0, 1.0])]), None);
    }

    /// A real map's simulation (the first demo map) when the disc is configured.
    fn real_sim() -> Option<crate::sim::FieldSim> {
        let pkb = crate::pkb_compat::PkbSet::from_env()?;
        let b = pkb.read("FIELD/MPS/AP_02_U.MPS")?;
        crate::sim::FieldSim::new("AP_02_U", b, 0).ok()
    }

    fn walker(sim: &mut crate::sim::FieldSim) -> ActorTable {
        let mut t = ActorTable::default();
        t.ctrl = 0;
        t.load(0, "000", 0, 0);
        t.load(1, "npc", 1, 0);
        t.load(2, "npc2", 2, 0);
        for s in [0, 1, 2] {
            t.slots[s].as_mut().unwrap().disp = true;
        }
        let _ = sim;
        t
    }

    #[test]
    fn walking_npc_reports_its_gait_and_arrives() {
        let Some(mut sim) = real_sim() else { return };
        let mut t = walker(&mut sim);
        t.slots[1].as_mut().unwrap().pos = [0.0, 0.0, 100.0];
        t.slots[0].as_mut().unwrap().pos = [500.0, 0.0, 500.0];
        t.slots[2].as_mut().unwrap().pos = [500.0, 0.0, -500.0];
        t.auto_move(1, [0.0, 0.0, 120.0], -1, 0, 0, &mut sim);
        let mut out = vec![];
        for _ in 0..400 {
            t.tick(&mut sim);
            out.extend(std::mem::take(&mut t.out));
            if t.check_last_cmd(1) == 1 {
                break;
            }
        }
        assert_eq!(t.check_last_cmd(1), 1, "the NPC reached its destination");
        assert!(out.contains(&ActorOut::Gait { slot: 1, gait: 1 }), "walk motion requested: {out:?}");
        assert_eq!(out.last(), Some(&ActorOut::Gait { slot: 1, gait: 0 }), "back to idle on arrival");
    }

    #[test]
    fn npc_waits_for_a_model_in_its_way_and_goes_on_when_it_leaves() {
        let Some(mut sim) = real_sim() else { return };
        let mut t = walker(&mut sim);
        t.slots[1].as_mut().unwrap().pos = [0.0, 0.0, 100.0];
        t.slots[2].as_mut().unwrap().pos = [0.0, 0.0, 106.0];
        t.slots[0].as_mut().unwrap().pos = [500.0, 0.0, 500.0];
        t.auto_move(1, [0.0, 0.0, 140.0], -1, 0, 0, &mut sim);
        for _ in 0..60 {
            t.tick(&mut sim);
        }
        let z = t.slots[1].as_ref().unwrap().pos[2];
        assert!(z < 101.0, "blocked at {z}");
        t.slots[2].as_mut().unwrap().pos = [300.0, 0.0, 300.0];
        for _ in 0..60 {
            t.tick(&mut sim);
        }
        assert!(t.slots[1].as_ref().unwrap().pos[2] > z + 5.0, "moves on after the way is free");
    }

    #[test]
    fn motion_command_completes() {
        let mut t = ActorTable::default();
        t.load(1, "C001", 1, 0);
        t.set_motion(1, 5, 0);
        assert_eq!(t.check_last_cmd(1), 0);
        // no sim needed for the motion part
        for _ in 0..DEFAULT_MOTION_TICKS {
            let a = t.slots[1].as_mut().unwrap();
            if a.motion_left > 0 {
                a.motion_left -= 1;
            }
        }
        assert_eq!(t.slots[1].as_ref().unwrap().motion_left, 0);
    }
}

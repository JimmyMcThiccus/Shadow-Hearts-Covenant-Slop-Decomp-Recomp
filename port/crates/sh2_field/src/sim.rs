//! `FieldSim` — the renderer-independent per-frame logic of `CField::Polling` (JP 0x004a6260): player control on the floor, event-box
//! triggers, random encounters and the camera.  The Bevy glue ([`crate::plugin`]) feeds it pad state at 60 Hz; everything here is
//! plain data so it runs (and is tested) without a GPU.
//!
//! Coordinates are the game's: x right, **y down**, z forward; angles in radians, heading 0 = +z, positive = clockwise from above.

use crate::camera::CameraPose;
use crate::event::HitMode;
use crate::field::Field;
use crate::movement::{make_move_control, pad, step_forward, Gait};
use crate::mps::{Mps, MpsError};

/// Walk / run speed in game units per 60 Hz tick: the ROOT translation of the player's `walk` / `run` motions
/// (`CharacterAsset::root_speed`, 0.30 / 0.83 for the party models); the original moves the actor by that translation
/// (`CFieldModel::TransCallBack`).  PINE check (notes/integration/pine_validation.md): the real game runs the field at 30 fps (`SSHSys+0x20`
/// frame delta = 33 ms in steady state) and a walking actor showed 0.594 units of root translation per game frame = 18.0 units/s = 0.30 x 60.
///
/// Measured live on the US build (PINE, AP_03_U, notes/integration/pine_us_refinement.md): `CFieldModel+0x40` (the per-frame root translation)
/// is `-0.5942 .. -0.5949` along local z in the `walk` motion and `-1.6435 .. -1.6535` (mean 1.6487) in the `run` motion per 30 fps game frame,
/// i.e. 0.297 / 0.8244 per 60 Hz tick (the demo-derived 0.30 / 0.83 were rounded).
pub const WALK_SPEED: f32 = 0.297;
pub const RUN_SPEED: f32 = 0.8244;
/// Reach of the circle-button probe in front of the player (`CField::Polling` examines 6 units ahead).
pub const PROBE_DIST: f32 = 6.0;
/// Visible turn rate of the avatar, rad/s (`CFieldModel::Update`: `dt * 2 pi * model+0x314`, `+0x314 = 1.0` for the player's `SetDir(.., 2, 3)`).
pub const TURN_RATE: f32 = std::f32::consts::TAU;

#[derive(Debug, Clone)]
pub struct Player {
    pub pos: [f32; 3],
    pub yaw: f32,
    pub gait: Gait,
    /// heading the avatar is moving along (`CFieldModel+0x34`, the `SetDir` target): the real game translates along this at once while the
    /// visible `yaw` turns towards it at 2 pi * dt rad/s (PINE-measured, notes/integration/pine_us_refinement.md)
    pub move_yaw: f32,
    pub moving: bool,
    /// walking animation phase (render only)
    pub anim: f32,
}

/// Goal of the script camera: position, look-at point and view angle (`SetViewAngle` value).
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct ScrCamGoal {
    pub pos: [f32; 3],
    pub target: [f32; 3],
    pub view_angle: f32,
}

/// `CField::CheckEncount` state (`+0x3c4` miss counter, `+0x3c5` distance threshold, `+0x3c6` rate, `+0x3cc` distance walked).
#[derive(Debug, Clone, Default)]
pub struct Encounter {
    pub rate: u8,
    pub dist: f32,
    pub thresh: u8,
    pub misses: u8,
}

impl Encounter {
    /// JP: 0x004b8cc0 CField::CheckEncount (the distance/roll part). `table` = `encDist` (FIELD.BIN 0x00555e48), `rand` = libc `rand()`.
    pub fn check(&mut self, table: &[u8; 3], rand: &mut dyn FnMut() -> u32) -> bool {
        if self.rate == 0 {
            return false;
        }
        if self.thresh == 0 {
            self.thresh = table[(rand() % 3) as usize].max(1);
        }
        if self.dist * 0.1 < self.thresh as f32 {
            return false;
        }
        let roll = (rand() % 100) as i32;
        self.thresh = 0;
        self.dist = 0.0;
        if self.misses < 2 && (self.rate as i32) <= roll {
            self.misses += 1;
            return false;
        }
        true
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum SimEvent {
    /// `SetFieldEvent(1, id, 2, ..)`: the player stepped into box `id`
    BoxEnter(i32),
    /// the player left box `id` (arg 1)
    BoxLeave(i32),
    /// circle pressed in front of a box (`SetFieldEvent(1, id, 4, ..)`)
    Examine(i32),
    /// random encounter: MONSET id (`MONSETTbl` index)
    Battle { monster_set: u16 },
    /// triangle pressed
    MenuRequest,
}

#[derive(Clone)]
pub struct FieldSim {
    pub map: String,
    pub field: Field,
    pub player: Player,
    pub enc: Encounter,
    pub enc_table: [u8; 3],
    pub cur_box: i32,
    /// camera facing yaw (radians, game convention) used to make the pad camera relative
    pub cam_yaw: f32,
    /// left analog stick `(gauge 0..1, degrees)` as `MakeMoveControl` reads it from the pad (`CPad+0x7c / +0x84`); `(0, 0)` = digital pad only.
    /// A gauge >= 0.95 runs (unless X is held), anything above the 0.1 dead zone walks at the stick heading.
    pub stick: (f32, f32),
    pub pose: Option<CameraPose>,
    /// `rand()` state (newlib: `s = s*6364136223846793005 + 1; (s>>32) & 0x7fffffff`, u64 at reent+0xa8), as verified live by the PINE agent.
    pub rng: u64,
    pub ticks: u64,
    /// total xz distance walked
    pub walked: f32,
    /// bits 2-4 of `CField+0x18c`: which event-box triggers are enabled (1 enter, 2 leave, 4 examine); `InitSDB` sets 5
    pub evt_mask: u8,
    /// camera set by the script (`SetCamera*`, JP `UpdateScrCamera`); overrides the CAMEVENT camera while set
    pub scr_cam: Option<ScrCamGoal>,
    /// chase-camera fallback: the frozen facing while the CAMERA pose kept the player off screen, and a counter of consecutive good ticks
    chase: Option<f32>,
    chase_ok: u32,
}

impl FieldSim {
    /// `CField::Init(map)` + `InitSDB`: build everything from the parsed map.  `entry` = ENTRYPOS index.
    pub fn new(map: &str, mps_bytes: Vec<u8>, entry: i32) -> Result<Self, MpsError> {
        let mps = Mps::parse(mps_bytes)?;
        let mut field = Field::new();
        field.entry_id = entry.max(0) as i16;
        let setup = field.init_sdb(mps)?;
        let pos = setup.start_pos.unwrap_or([0.0; 3]);
        // facing = dir/256 turn (JP SetDir(dir, 2, 0)); sign/offset follow the model yaw convention
        // `SetDir(dir, 2, 0)` with `GetRotAngle`: 32 directions, model forward is -z (see `script_actors`)
        let yaw = setup.start_dir.map(|d| crate::script_actors::rot_to_yaw(crate::script_actors::get_rot_angle(d as i32))).unwrap_or(0.0);
        let enc = Encounter { rate: field.encounter_rate.clamp(0, 255) as u8, ..Default::default() };
        let mut sim = FieldSim {
            map: map.to_string(),
            field,
            player: Player { pos, yaw, gait: Gait::Walk, move_yaw: yaw, moving: false, anim: 0.0 },
            enc,
            enc_table: [30, 40, 50],
            cur_box: -1,
            cam_yaw: 0.0,
            stick: (0.0, 0.0),
            pose: None,
            rng: (0x2545_f491u32 ^ map.bytes().fold(0u32, |a, b| a.wrapping_mul(31).wrapping_add(b as u32))) as u64,
            ticks: 0,
            walked: 0.0,
            evt_mask: 5,
            scr_cam: None,
            chase: None,
            chase_ok: 0,
        };
        // snap to the floor
        sim.snap_floor();
        sim.update_camera();
        Ok(sim)
    }

    /// libc `rand()` exactly as the game's newlib implements it (JP/US disassembly; live-checked over PINE).
    pub fn lcg_rand(state: &mut u64) -> u32 {
        *state = state.wrapping_mul(6364136223846793005).wrapping_add(1);
        ((*state >> 32) & 0x7fff_ffff) as u32
    }

    fn rand(&mut self) -> u32 {
        Self::lcg_rand(&mut self.rng)
    }

    fn snap_floor(&mut self) {
        if let Some(fl) = self.field.floor.as_mut() {
            if let Some(t) = fl.on_floor_chk(self.player.pos) {
                self.player.pos[1] = fl.on_floor_point(self.player.pos, t);
            }
        }
    }

    /// Camera selection + `CFieldCamera::Apply` (JP `CField::CameraUpdate` 0x004a84c0).  Falls back to a chase camera when the map has no
    /// CAMEVENT under the player.
    pub fn update_camera(&mut self) {
        let p = self.player.pos;
        self.field.player_pos = [p[0], p[1], p[2], 1.0];
        self.field.ctrl_rot_y = self.player.yaw;
        if let Some(g) = self.scr_cam {
            self.field.camera.set_target_pos([g.target[0], g.target[1], g.target[2], 1.0]);
            self.field.camera.set_camera_pos([g.pos[0], g.pos[1], g.pos[2], 1.0]);
            self.field.camera.set_view_angle(g.view_angle);
            if let Some(pose) = self.field.camera.apply(1.0) {
                self.cam_yaw = (pose.target[0] - pose.pos[0]).atan2(pose.target[2] - pose.pos[2]);
                self.pose = Some(pose);
            }
            return;
        }
        let had = self.field.update_field_camera(-1);
        if !had && self.field.cam_cur.is_none() {
            // fallback: 130 units behind (-z), 60 above (y is down)
            let t = [p[0], p[1] - 30.0, p[2], 1.0];
            let c = [p[0], p[1] - 70.0, p[2] - 130.0, 1.0];
            self.field.camera.set_target_pos(t);
            self.field.camera.set_camera_pos(c);
            self.field.camera.set_view_angle(0.625);
        }
        if let Some(pose) = self.field.camera.apply(1.0) {
            let visible = self.player_visible(&pose);
            match self.chase {
                None if !visible => {
                    self.chase = Some(self.cam_yaw);
                    self.chase_ok = 0;
                }
                Some(_) if visible => {
                    self.chase_ok += 1;
                    if self.chase_ok >= 45 {
                        self.chase = None;
                    }
                }
                Some(_) => self.chase_ok = 0,
                None => {}
            }
            let pose = match self.chase {
                Some(yaw) => self.chase_pose(&pose, yaw),
                None => pose,
            };
            self.cam_yaw = (pose.target[0] - pose.pos[0]).atan2(pose.target[2] - pose.pos[2]);
            self.pose = Some(pose);
        }
    }

    /// Is the player inside the view frustum of `pose` (about 0.42 of the focal length off axis, at least 20 units in front)?  The ported
    /// CAMERA evaluation (kind 4 / rounded kind 5 missing) can place a rail camera so that the player is off screen.
    fn player_visible(&self, pose: &CameraPose) -> bool {
        let p = self.player.pos;
        let f = [pose.target[0] - pose.pos[0], pose.target[1] - pose.pos[1], pose.target[2] - pose.pos[2]];
        let fl = (f[0] * f[0] + f[1] * f[1] + f[2] * f[2]).sqrt().max(1e-3);
        let f = [f[0] / fl, f[1] / fl, f[2] / fl];
        let v = [p[0] - pose.pos[0], p[1] - 14.0 - pose.pos[1], p[2] - pose.pos[2]];
        let depth = v[0] * f[0] + v[1] * f[1] + v[2] * f[2];
        if depth < 20.0 {
            return false;
        }
        // right = f x up (up = -y in the game's y-down space)
        let up = [0.0f32, -1.0, 0.0];
        let r = [f[1] * up[2] - f[2] * up[1], f[2] * up[0] - f[0] * up[2], f[0] * up[1] - f[1] * up[0]];
        let rl = (r[0] * r[0] + r[1] * r[1] + r[2] * r[2]).sqrt();
        if rl < 1e-3 {
            return true;
        }
        let r = [r[0] / rl, r[1] / rl, r[2] / rl];
        let u = [r[1] * f[2] - r[2] * f[1], r[2] * f[0] - r[0] * f[2], r[0] * f[1] - r[1] * f[0]];
        let hx = (v[0] * r[0] + v[1] * r[1] + v[2] * r[2]).abs() / depth;
        let vy = (v[0] * u[0] + v[1] * u[1] + v[2] * u[2]).abs() / depth;
        hx < 0.42 && vy < 0.4
    }

    /// Chase camera behind the player, keeping the previous facing.
    fn chase_pose(&self, bad: &CameraPose, yaw: f32) -> CameraPose {
        let p = self.player.pos;
        let (s, c) = yaw.sin_cos();
        let tgt = [p[0], p[1] - 30.0, p[2], 1.0];
        let cam = [p[0] - s * 120.0, p[1] - 64.0, p[2] - c * 120.0, 1.0];
        CameraPose { pos: cam, target: tgt, yaw_deg: bad.yaw_deg, pitch_deg: bad.pitch_deg, roll_deg: 0.0, focal: 512.0 }
    }

    /// One 60 Hz tick.  `real` = held buttons, `press` = buttons pressed this tick.  `frozen` = a script / window holds the player.
    pub fn tick(&mut self, real: u16, press: u16, frozen: bool) -> Vec<SimEvent> {
        self.ticks += 1;
        let mut ev = Vec::new();
        self.player.moving = false;
        if !frozen {
            self.control(real);
            // event boxes (walk-on)
            let p = self.player.pos;
            let hit = match &self.field.event_boxes {
                Some(e) => e.hit_check(p, HitMode::KindZero),
                None => -1,
            };
            if hit != self.cur_box {
                // JP CField::Polling: the leave event needs (mask & flags & 2), the enter event (mask & !flags & 1), where `flags` is the
                // low nibble of the box flag byte and `mask` bits 2-4 of +0x18c
                let mask = self.evt_mask;
                if self.cur_box >= 0 {
                    if let Some(e) = &self.field.event_boxes {
                        let fl = e.boxes.get(self.cur_box as usize).map(|b| b.flags & 0xf).unwrap_or(0);
                        if mask & fl & 2 != 0 {
                            ev.push(SimEvent::BoxLeave(e.event_num(self.cur_box)));
                        }
                    }
                }
                if hit >= 0 {
                    if let Some(e) = &self.field.event_boxes {
                        let fl = e.boxes.get(hit as usize).map(|b| b.flags & 0xf).unwrap_or(0);
                        if mask & !fl & 1 != 0 {
                            ev.push(SimEvent::BoxEnter(e.event_num(hit)));
                        }
                    }
                }
                self.cur_box = hit;
            }
            if press & pad::CIRCLE != 0 {
                let (s, c) = self.player.yaw.sin_cos();
                let q = [p[0] + s * PROBE_DIST, p[1], p[2] + c * PROBE_DIST];
                if let Some(e) = &self.field.event_boxes {
                    let h = e.hit_check(q, HitMode::All);
                    if h >= 0 && self.evt_mask & e.boxes[h as usize].flags & 4 != 0 {
                        ev.push(SimEvent::Examine(e.event_num(h)));
                    }
                }
            }
            if press & pad::TRIANGLE != 0 {
                ev.push(SimEvent::MenuRequest);
            }
            // encounters
            let table = self.enc_table;
            let mut rng = self.rng;
            let hit_enc = {
                let mut r = || Self::lcg_rand(&mut rng);
                self.enc.check(&table, &mut r)
            };
            self.rng = rng;
            if hit_enc {
                let r = self.rand();
                let set = self.field.roll_monster_set(r);
                ev.push(SimEvent::Battle { monster_set: set });
            }
        }
        self.update_camera();
        ev
    }

    /// `MakeMoveControl` + camera relative heading + floor movement.
    ///
    /// Retail `CField::Polling` -> `SetDir(model, heading, 2, 3)`: the model's target yaw (`+0x34`) jumps to the stick heading at once and
    /// `TransCallBack` translates along that target; `CFieldModel::Update` turns the visible yaw (`+0x24`) by `dt * 2 pi * (+0x314 = 1.0)` per
    /// update (6.28 rad/s; the port ticks at 60 Hz -> `TAU / 60`).  Turns of more than ~60 degrees additionally play the `0x29/0x2a` turn
    /// motion with a smoothed profile (not modelled).
    fn control(&mut self, real: u16) {
        let (gauge, deg) = self.stick;
        let (speed, angle, gait) = make_move_control(gauge, deg, real);
        if speed < 0.1 {
            return;
        }
        let heading = self.cam_yaw + angle.to_radians();
        let mut m = heading % std::f32::consts::TAU;
        if m > std::f32::consts::PI {
            m -= std::f32::consts::TAU;
        } else if m < -std::f32::consts::PI {
            m += std::f32::consts::TAU;
        }
        self.player.move_yaw = m;
        // turn the visible yaw towards the target (shortest way)
        let mut d = (m - self.player.yaw) % std::f32::consts::TAU;
        if d > std::f32::consts::PI {
            d -= std::f32::consts::TAU;
        } else if d < -std::f32::consts::PI {
            d += std::f32::consts::TAU;
        }
        let step = TURN_RATE / 60.0;
        self.player.yaw += d.clamp(-step, step);
        self.player.gait = gait;
        let v = if gait == Gait::Run { RUN_SPEED } else { WALK_SPEED };
        let old = self.player.pos;
        if let Some(fl) = self.field.floor.as_mut() {
            self.player.pos = step_forward(fl, old, self.player.move_yaw, v);
        }
        let moved = ((self.player.pos[0] - old[0]).powi(2) + (self.player.pos[2] - old[2]).powi(2)).sqrt();
        if moved > 0.01 {
            self.player.moving = true;
            self.player.anim += moved * 0.12;
            self.walked += moved;
            // JP UpdateMoveDistance: only counts while the encounter rate is non-zero
            if self.enc.rate != 0 {
                self.enc.dist += moved;
            }
        }
    }
}

/// `encDist` bytes from a `FIELD.BIN` image (JP 0x00555e48); `None` if the table cannot be read.
pub fn read_enc_dist(field_bin: &[u8]) -> Option<[u8; 3]> {
    let img = crate::overlay_data::OverlayImage::new(field_bin.to_vec()).ok()?;
    let b = img.raw("encDist")?;
    Some([b[0], b[1], b[2]])
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::pkb_compat::PkbSet;

    fn load(map: &str, entry: i32) -> Option<FieldSim> {
        let set = PkbSet::from_env()?;
        let d = set.read(&format!("FIELD/MPS/{map}.MPS"))?;
        Some(FieldSim::new(map, d, entry).unwrap())
    }

    #[test]
    fn encounter_logic() {
        let mut e = Encounter { rate: 20, ..Default::default() };
        let mut n = 0u32;
        let mut rnd = || {
            n += 1;
            n * 7
        };
        e.dist = 10.0;
        assert!(!e.check(&[30, 40, 50], &mut rnd), "below threshold");
        e.dist = 10_000.0;
        // forced misses at most twice, then guaranteed
        let mut hits = 0;
        for _ in 0..3 {
            e.dist = 10_000.0;
            if e.check(&[30, 40, 50], &mut || 99) {
                hits += 1;
            }
        }
        assert_eq!(hits, 1, "two misses then an encounter");
    }

    #[test]
    fn walks_on_real_map_and_stays_on_floor() {
        let Some(mut s) = load("AP_02_U", 0) else { return };
        let start = s.player.pos;
        for _ in 0..300 {
            s.tick(pad::UP, 0, false);
        }
        let moved = ((s.player.pos[0] - start[0]).powi(2) + (s.player.pos[2] - start[2]).powi(2)).sqrt();
        assert!(moved > 20.0, "moved {moved}");
        let fl = s.field.floor.as_mut().unwrap();
        assert!(fl.circle_chk(s.player.pos, 4.0).is_some());
        assert!(s.pose.is_some());
    }

    #[test]
    fn encounter_fires_when_walking_a_monster_map() {
        let Some(mut s) = load("AP_03_U", 0) else { return };
        assert_eq!(s.enc.rate, 20);
        assert!(s.field.monsters.is_some());
        let mut battle = None;
        'outer: for round in 0..80 {
            let dirs = [pad::UP, pad::RIGHT, pad::DOWN, pad::LEFT];
            for _ in 0..120 {
                for e in s.tick(dirs[round % 4], 0, false) {
                    if let SimEvent::Battle { monster_set } = e {
                        battle = Some(monster_set);
                        break 'outer;
                    }
                }
            }
        }
        assert!(battle.is_some(), "walked {} units without an encounter", s.walked);
    }
}

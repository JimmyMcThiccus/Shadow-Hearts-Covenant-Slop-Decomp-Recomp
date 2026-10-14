//! `CField` — the field controller. This module ports the *data-driven* core (SDB consumption, entry points, encounter roll,
//! camera selection) and the flag/state vocabulary; engine side effects (models, windows, sound, script VM) stay behind
//! traits/stubs to be provided by the Bevy layer and by `sh2_script`.
//!
//! JP: 0x004a2b00 `CField::CField`, 0x004a30b0 `Init`, 0x004ab860 `InitSDB`, 0x004ac100 `GetEntryPoint`,
//! 0x004a84c0 `CameraUpdate`, 0x004a8be0 `UpdateFieldCamera`, 0x004a6260 `Polling` (encounter roll part).

use crate::camera::{eval_camera, FieldCamera};
use crate::event::{FieldEvent, HitMode};
use crate::floor::FloorMan;
use crate::mps::{CameraDef, EntryPoint, Mps, MpsError, MonSet};
use crate::retail::{start_position, Build, CamFollow, ChrPosSave};

/// `CField+0x18c` (u8).
#[derive(Debug, Clone, Copy, Default)]
pub struct Flags18c(pub u8);
impl Flags18c {
    pub fn deleting(self) -> bool {
        self.0 & 1 != 0
    }
    pub fn game_over_on_delete(self) -> bool {
        self.0 & 2 != 0
    }
    /// bits 5-7: camera follow mode (0 none, 1 init, 2 reset, 3 track, 4 ease out, ...)
    pub fn cam_follow(self) -> u8 {
        self.0 >> 5
    }
    pub fn set_cam_follow(&mut self, m: u8) {
        self.0 = (self.0 & 0x1f) | (m << 5);
    }
}

/// `CField+0x18d` (u8).
#[derive(Debug, Clone, Copy, Default)]
pub struct Flags18d(pub u8);
impl Flags18d {
    /// bits 0-1: pending battle (1 = normal `BtlIn`, 2 = boss `BtlInBoss`)
    pub fn battle_pending(self) -> u8 {
        self.0 & 3
    }
    /// bits 2-3: 0 running, 1 paused (script/menu), 2 sleeping (only ObjSE polled)
    pub fn pause_state(self) -> u8 {
        (self.0 >> 2) & 3
    }
    pub fn set_pause_state(&mut self, v: u8) {
        self.0 = (self.0 & 0xf3) | ((v & 3) << 2);
    }
    pub fn displayed(self) -> bool {
        self.0 & 0x10 != 0
    }
    pub fn set_displayed(&mut self, d: bool) {
        self.0 = (self.0 & 0xef) | if d { 0x10 } else { 0 };
    }
    /// bit5: main menu requested (set when triangle pressed and `CheckCmdMenu`)
    pub fn menu_requested(self) -> bool {
        self.0 & 0x20 != 0
    }
}

/// `CField+0x28` (u16) scene state.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum FieldState {
    /// 1: constructed, SDB not yet applied — `Polling` waits until all models finished loading, then goes to 2
    LoadingModels,
    /// 2: running
    Running,
    /// 3: frozen (frame delta forced to 0)
    Frozen,
    Other(u16),
}
impl From<u16> for FieldState {
    fn from(v: u16) -> Self {
        match v {
            1 => Self::LoadingModels,
            2 => Self::Running,
            3 => Self::Frozen,
            x => Self::Other(x),
        }
    }
}

/// Everything `CField::InitSDB` instantiates from one MPS.
#[derive(Clone)]
pub struct Field {
    pub state: u16,
    pub entry_id: i16,
    pub flags_18c: Flags18c,
    pub flags_18d: Flags18d,
    pub mps: Option<Mps>,
    /// the map's radar data (`CNaviMap::SetData`), see [`crate::navimap`]
    pub navi: Option<crate::navimap::NaviData>,
    pub floor: Option<FloorMan>,
    pub event_boxes: Option<FieldEvent>,
    pub cam_events: Option<FieldEvent>,
    pub cameras: Vec<CameraDef>,
    pub monsters: Option<MonSet>,
    pub camera: FieldCamera,
    /// active CAMERA table index (`m_pCAMDAT`) and the previous one (`m_pCAMOLD`)
    pub cam_cur: Option<usize>,
    pub cam_old: Option<usize>,
    /// `CField+0x6c8` (s16): camera id of the last CAMEVENT hit, -1 none
    pub camera_id: i16,
    pub player_pos: [f32; 4],
    pub ctrl_rot_y: f32,
    pub encounter_rate: i32,
    /// `SetFieldData(6/7, ..)` values from MONSET (battle background / bgm)
    pub field_data: [i32; 8],
    /// Which executable pair this instance follows (see [`crate::retail`]); only affects the retail-specific branches.
    pub build: Build,
    /// Camera-relative heading ease state (`flags_18c >> 5`, +0x6e0 ...), advanced by `CamFollow::step` from `Polling`.
    pub follow: CamFollow,
    /// `cam_angle.y` (degrees) of the last applied camera, needed when the active CAMEVENT changes.
    pub cam_angle_y: f32,
}

impl Default for Field {
    fn default() -> Self {
        Self::new()
    }
}

impl Field {
    /// JP: 0x004a2b00 CField::CField (zeroes 0xe98 bytes from +0x24, state = 1)
    pub fn new() -> Self {
        Self {
            state: 1,
            entry_id: 0,
            flags_18c: Flags18c(0),
            flags_18d: Flags18d(0),
            mps: None,
            navi: None,
            floor: None,
            event_boxes: None,
            cam_events: None,
            cameras: vec![],
            monsters: None,
            camera: FieldCamera::new(),
            cam_cur: None,
            cam_old: None,
            camera_id: -1,
            player_pos: [0.0, 0.0, 0.0, 1.0],
            ctrl_rot_y: 0.0,
            encounter_rate: 0,
            field_data: [0; 8],
            build: Build::Demo,
            follow: CamFollow::default(),
            cam_angle_y: 0.0,
        }
    }

    /// Same as [`Field::new`] for an explicit build.
    pub fn with_build(build: Build) -> Self {
        Self { build, ..Self::new() }
    }

    /// `InitSDB` for either build. The map consumers are shared (they are the same code in both executables); the player start differs:
    /// the demo takes `ENTRYPOS[entry_id]`, retail first resolves a saved position (`entry_id < -1` -> save block slot, else the
    /// battle-return `ChrPosSave` slot 0) and only then lets `ENTRYPOS[entry_id]` (entry_id >= 0) win. `saved_slot(i)` models
    /// `GetSavedChrPos(i)` for the save-block slots (0 = last save point, 1 = last warp).
    pub fn init_sdb_ex(&mut self, mps: Mps, chr: &ChrPosSave, saved_slot: impl Fn(i32) -> Option<[f32; 4]>) -> Result<SdbSetup, MpsError> {
        let eps = mps.entry_points()?;
        let entry0 = eps.first().map(|e| e.pos);
        let entry_id = self.entry_id;
        let mut setup = self.init_sdb(mps)?;
        let mut p = start_position(self.build, entry0, entry_id, saved_slot, chr);
        if entry_id >= 0 {
            if let Some(ep) = eps.get(entry_id as usize) {
                p = [ep.pos[0], ep.pos[1], ep.pos[2], 1.0];
                setup.start_dir = Some(ep.dir);
            }
        }
        self.player_pos = p;
        setup.start_pos = Some([p[0], p[1], p[2]]);
        Ok(setup)
    }

    /// JP: 0x004ab860 CField::InitSDB — consume a parsed MPS. (`CFieldBG::Create`, model loading and `AutoLoadSE` are engine work and are
    /// reported through the returned [`SdbSetup`].)
    pub fn init_sdb(&mut self, mps: Mps) -> Result<SdbSetup, MpsError> {
        self.cam_cur = None;
        self.camera.comp_clear();
        self.camera_id = -1;
        self.player_pos = [0.0, 0.0, 0.0, 1.0];
        self.monsters = mps.monster_sets()?;
        match &self.monsters {
            Some(ms) => {
                self.encounter_rate = ms.encounter_rate as i32;
                self.field_data[6] = ms.field_data6 as i32;
                self.field_data[7] = ms.field_data7 as i32;
            }
            None => self.encounter_rate = 0,
        }
        self.floor = mps.floor()?.and_then(FloorMan::new);
        self.cameras = mps.cameras()?;
        let eb = mps.event_boxes()?;
        self.event_boxes = (!eb.is_empty() || mps.find(crate::mps::tags::EVENTBOX).is_some()).then(|| FieldEvent::new(eb, false));
        let ce = mps.camera_events()?;
        self.cam_events = (!ce.is_empty() || mps.find(crate::mps::tags::CAMEVENT).is_some()).then(|| FieldEvent::new(ce, true));
        // player start: ENTRYPOS[entry_id]
        let mut setup = SdbSetup::default();
        if self.entry_id >= 0 {
            if let Some(ep) = self.entry_point(&mps, self.entry_id as i32) {
                self.player_pos = [ep.pos[0], ep.pos[1], ep.pos[2], 1.0];
                setup.start_dir = Some(ep.dir);
                setup.start_pos = Some(ep.pos);
            }
        }
        setup.models = mps.models()?.len();
        setup.has_navimap = mps.navimap().is_some();
        setup.objse = mps.objse().is_some();
        // round 5 CS hook: `CField::AutoLoadSE` -- the map's object sounds (OBJSE chunk: SE banks + positional ambient sounds) go to the audio layer
        match mps.find(crate::mps::tags::OBJSE) {
            Some(c) => sh2_audio::post(sh2_audio::AudioRequest::MapObjSe { chunk: std::sync::Arc::new(mps.data.get(c.data_start()..).unwrap_or(&[]).to_vec()) }),
            None => sh2_audio::post(sh2_audio::AudioRequest::SetObjSe { slot: -1, rec: None, one_shot: false }),
        }
        setup.bg_color = mps.bg_color();
        self.navi = crate::navimap::NaviData::from_mps(&mps);
        self.mps = Some(mps);
        self.state = 2;
        Ok(setup)
    }

    /// JP: 0x004ac100 CField::GetEntryPoint(i, &dir)
    pub fn entry_point(&self, mps: &Mps, i: i32) -> Option<EntryPoint> {
        let eps = mps.entry_points().ok()?;
        if i < 0 {
            return None;
        }
        eps.get(i as usize).copied()
    }

    /// Number of entry points (`GetEntryPoint(-1, &n)`).
    pub fn entry_count(&self, mps: &Mps) -> usize {
        mps.entry_points().map(|v| v.len()).unwrap_or(0)
    }

    /// Battle roll in `CField::Polling` (JP 0x004a6260): `rand() % 100`, walk the MONSET list subtracting weights; returns the monster-set id (0 if none).
    pub fn roll_monster_set(&self, rand: u32) -> u16 {
        let Some(ms) = &self.monsters else { return 0 };
        let mut r = (rand % 100) as i32;
        for &(id, weight) in &ms.entries {
            if r < weight as i32 {
                return id;
            }
            r -= weight as i32;
        }
        0
    }

    /// Camera selection + evaluation (JP 0x004a8be0 / US 0x004f4ef0 `UpdateFieldCamera`, kinds 0-5). `saved_camera_id` is `FieldCameraID(-2)`
    /// (camera remembered in the save block, used when the player stands in no CAMEVENT). Returns true when the camera goal was updated.
    pub fn update_field_camera(&mut self, saved_camera_id: i16) -> bool {
        let pos = [self.player_pos[0], self.player_pos[1], self.player_pos[2]];
        if let Some(ev) = &self.cam_events {
            let mut hit = ev.hit_check(pos, HitMode::KindZero);
            if hit < 0 {
                hit = saved_camera_id as i32;
            }
            if hit >= 0 {
                let idx = ev.event_num(hit);
                if idx >= 0 && (idx as usize) < self.cameras.len() {
                    let new = idx as usize;
                    // blend from the previous camera if both allow it (flag byte != 0) and they differ
                    if let Some(old) = self.cam_old {
                        if old != new && self.cameras[new].flag != 0 && self.cameras[old].flag != 0 {
                            self.camera.comp_frame(50.0);
                        }
                    }
                    self.cam_cur = Some(new);
                    if hit as i16 != self.camera_id {
                        // JP/US `UpdateFieldCamera`: a camera change while the previous id was valid starts the heading re-aim
                        if self.camera_id >= 0 {
                            self.follow.on_camera_switch(self.cam_angle_y);
                        }
                        self.camera_id = hit as i16;
                    }
                }
            }
        }
        let mut updated = false;
        if let (Some(i), Some(mps)) = (self.cam_cur, &self.mps) {
            let def = &self.cameras[i];
            let blob = mps.camera_blob(def);
            // the original takes the player position y - 12 for target kinds; mirror reversal is identity here
            let same = self.cam_old == Some(i);
            let goal = eval_camera(def.kind, blob, def.count, self.player_pos, self.ctrl_rot_y, (self.camera.target, self.camera.cam_pos), same);
            if let Some(g) = goal {
                self.camera.set_view_angle(g.view_angle);
                self.camera.set_target_pos(g.target);
                self.camera.set_camera_pos(g.cam);
                updated = true;
            }
        }
        if self.cam_cur.is_some() {
            self.cam_old = self.cam_cur;
        }
        updated
    }
}

/// What `InitSDB` asks the engine to do next.
#[derive(Debug, Default, Clone)]
pub struct SdbSetup {
    pub start_pos: Option<[f32; 3]>,
    pub start_dir: Option<i8>,
    pub models: usize,
    pub has_navimap: bool,
    pub objse: bool,
    pub bg_color: Option<u32>,
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn flags() {
        let mut f = Flags18d(0);
        f.set_pause_state(2);
        assert_eq!(f.pause_state(), 2);
        f.set_displayed(true);
        assert!(f.displayed());
        let mut g = Flags18c(0x03);
        g.set_cam_follow(4);
        assert!(g.deleting() && g.game_over_on_delete());
        assert_eq!(g.cam_follow(), 4);
    }

    #[test]
    fn monster_roll() {
        let mut f = Field::new();
        f.monsters = Some(MonSet { encounter_rate: 5, field_data6: 0, field_data7: 0, entries: vec![(10, 25), (11, 25), (12, 50)] });
        assert_eq!(f.roll_monster_set(0), 10);
        assert_eq!(f.roll_monster_set(30), 11);
        assert_eq!(f.roll_monster_set(99), 12);
    }
}

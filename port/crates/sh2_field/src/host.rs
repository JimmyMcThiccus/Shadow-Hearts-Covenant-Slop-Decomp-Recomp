//! `FieldHost` — the field half of the script engine: `CField::CallFunc` (JP FIELD.BIN 0x004ac950, US 0x004f7fb0), the `ex == 0xc2`
//! command set of the event-script VM, plus the state those commands act on ([`ScriptState`]).
//!
//! Every command the 40 JP map scripts and the 546 US map scripts use is implemented here (see `notes/integration/script_ops.md`
//! for the table).  The host never touches Bevy: the commands change [`ScriptState`] / [`crate::sim::FieldSim`] and queue *requests*
//! (map jump, battle, menu, world map, audio, script events) which [`crate::plugin`] executes.
//!
//! Conventions: a command returns `Void` when it finishes immediately, `Int` after storing a result in argument 0, and `Yield(token)`
//! (token < 0) to suspend the script - the VM re-issues the same call next tick with `ctx.nargs == token` (the argument block stays
//! valid).  "First call" is `ctx.nargs >= 0`.

use std::collections::{BTreeMap, HashSet};
use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::message::{MsgState, TextSpeed};
use sh2_menu::session::GameSession;
use sh2_script::cscript::{ExCtx, ExResult, ScriptHost};

use crate::script_actors::{get_rot_angle, rot_to_yaw, wrap, ActorEvent, ActorTable, Cmd};
use crate::script_ui::UiState;
use crate::sim::FieldSim;

// ----------------------------------------------------------------------------------------------------------------
// static tables
// ----------------------------------------------------------------------------------------------------------------

/// Data tables `CallFunc` indexes: `FIELD/FIELD_T.DAT` chunks (`FindDTCInfo`) and a few arrays inside FIELD.BIN.
#[derive(Clone)]
pub struct FieldTables {
    /// `TRES` (treasure): `{u8 item, u8 kind (low 6 bits = InventoryChange kind), u16 count}`
    pub tres: Vec<[u8; 4]>,
    /// `BBTL` (script battles): `{u16 background, u16 bgm, u16 monster set, u8 boss flag, u8 pad}`
    pub bbtl: Vec<[u8; 8]>,
    /// FIELD.BIN `paramChgTbl` (JP 0x00555a30): `ParamChange` selector -> `GetPCParam` kind
    pub param_chg: [u8; 10],
    /// FIELD.BIN `RDnumTbl` (JP 0x00555d90): script table index -> RegDat name kind
    pub rd_num: [u8; 11],
    /// `PC_L`-independent name lookup (kind, index) -> Shift-JIS bytes, built from `SSHMES` (optional)
    pub names: Option<Arc<dyn Fn(u8, u32) -> Option<Vec<u8>> + Send + Sync>>,
}

impl Default for FieldTables {
    fn default() -> Self {
        FieldTables {
            tres: vec![],
            bbtl: vec![],
            param_chg: [1, 3, 5, 0x12, 0, 0, 0, 2, 4, 6],
            rd_num: [0, 9, 6, 7, 8, 0xd, 0x11, 0xb, 0x10, 0, 0xa],
            names: None,
        }
    }
}

impl FieldTables {
    /// Parse the `DTCH` container of `FIELD_T.DAT` (JP `CFieldSocket` global `pFldData`): header 0x10 bytes (`u16 count @4`), then
    /// chunks `{tag[4], .., u16 units @6, u16 elem @8, u16 count @0xa}` + data.
    pub fn from_field_t(&mut self, d: &[u8]) {
        if d.len() < 0x10 || &d[0..4] != b"DTCH" {
            return;
        }
        let count = u16::from_le_bytes([d[4], d[5]]) as usize;
        let mut p = 0x10usize;
        for _ in 0..count {
            if p + 0x10 > d.len() {
                break;
            }
            let tag = &d[p..p + 4];
            let units = u16::from_le_bytes([d[p + 6], d[p + 7]]) as usize;
            let elem = u16::from_le_bytes([d[p + 8], d[p + 9]]) as usize;
            let n = u16::from_le_bytes([d[p + 10], d[p + 11]]) as usize;
            let data = &d[p + 0x10..];
            match tag {
                b"TRES" if elem == 4 => {
                    self.tres = (0..n).filter_map(|i| data.get(i * 4..i * 4 + 4)).map(|b| [b[0], b[1], b[2], b[3]]).collect();
                }
                b"BBTL" if elem == 8 => {
                    self.bbtl = (0..n).filter_map(|i| data.get(i * 8..i * 8 + 8)).map(|b| b.try_into().unwrap()).collect();
                }
                _ => {}
            }
            if units == 0 {
                break;
            }
            // JP demo: `units` counts the header paragraph too; US retail `FIELD.DAT`: it counts the data only (next tag at +0x10 + units * 16)
            let is_tag = |q: usize| d.get(q..q + 4).map(|t| t.iter().all(|c| c.is_ascii_uppercase() || c.is_ascii_digit())).unwrap_or(false);
            p = if is_tag(p + units * 16) || !is_tag(p + 0x10 + units * 16) { p + units * 16 } else { p + 0x10 + units * 16 };
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// requests the host queues for the Bevy layer
// ----------------------------------------------------------------------------------------------------------------

/// Sound requests (`CField::LoadBgm/PlayBgm/PlaySe/..`, JP 0x004d7e60..).  The audio layer (`sh2_script::audio::SoundBackend`) executes them.
#[derive(Debug, Clone, PartialEq)]
pub enum FieldAudio {
    LoadBgm(String),
    /// `PlayBgm(id, flags)`
    PlayBgm { id: i32, flags: u32 },
    BgmFade { ms: u32, flags: u32 },
    SetBgmVolume(i32),
    SetBattleBgm(String),
    PlayStreamBgm { name: String, flags: i32 },
    /// `LoadSe(bank name, slot)`
    LoadSe { name: String, slot: i32 },
    /// `UnloadSe(name)`; `None` = all banks
    UnloadSe(Option<String>),
    PlaySe { id: u32, volume: i32 },
    /// `PlaySeR(mode 0, id, vol)` / fade (mode 4)
    PlaySeR { mode: i32, id: u32, a: i32, b: i32 },
    SetSeVolume(i32),
    StopSe(u32),
    /// `SetObjSE(index, ..)`: positional environment sound
    SetObjSe { index: i32, a: u32, b: u32, c: i32, pos: Option<[f32; 3]> },
    SetSoundData { which: i32, a: i32, b: i32 },
    ReverbMode(i32),
    StreamFade(i32),
}

/// `CField::InvokeBattle(boss, bg, bgm, party_set, monster_set, flag)`
#[derive(Debug, Clone, PartialEq)]
pub struct BattleReq {
    pub boss: bool,
    pub background: i32,
    pub bgm: i32,
    pub party_set: i32,
    pub monster_set: i32,
    pub flag: i32,
}

/// `SpecialMenu(kind, arg)` requests.
#[derive(Debug, Clone, PartialEq)]
pub enum MenuReq {
    /// `CommandMenu(4, arg)`: the main menu
    Main { arg: u32 },
    /// `CommandMenu(5, arg)`: tutorial
    Tutorial { arg: u32 },
    /// `CommandMenu(6, arg)`: sub menu (page 8)
    Sub { arg: u32 },
    /// `CommandMenu(0x10, ..)`: save screen
    Save,
    /// shop #id (`shop::initialize`)
    Shop { id: i32 },
    Tailor,
    /// retail op 0x4d `InvokeCmdScene(a, b)`
    CmdScene { a: i32, b: i32 },
    /// `SpecialMenu(0x5xx)`: game over on field teardown
    GameOver,
    /// `SpecialMenu(0x7xx)`: the field ends and the game returns to the title (the ending)
    EndToTitle,
    /// (round 5 MN) `SpecialMenu(0x400, ..)`: the retail name entry (`CommandMenu(7)`, page 18, SM_20_U)
    NameEntry,
    /// (round 5 MN) `SpecialMenu(0x600, bout)`: the retail Wolf Bout stamp card (`CmdRetailSel02`)
    WolfStamp { bout: i32 },
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct SavePointSlot {
    pub active: bool,
    pub pos: [f32; 3],
    pub shown: bool,
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct WarpPointSlot {
    pub active: bool,
    pub pos: [f32; 3],
    pub kind: i32,
    pub shown: bool,
}

/// `DoWarp` effect in progress (`WarpPoint::WarpOut/WarpIn`, the screen flash)
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct WarpFx {
    pub ticks_left: u32,
    pub incoming: bool,
    pub color: [u8; 3],
    pub total: u32,
}

/// Script camera (`CField::SetCamera*`, `UpdateScrCamera`)
#[derive(Debug, Clone, Copy, PartialEq)]
pub enum ScrCamMode {
    /// follow actor `slot` from a fixed position (`SetCameraA`)
    Look { slot: i32, aim: i32 },
    /// frame two actors (`SetCameraB`)
    TwoShot { a: i32, b: i32 },
    /// camera position + target point (`SetCameraC` type 0), type 1: target is a direction, type 2: pitch/yaw angles
    Fixed,
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct ScrCam {
    pub mode: ScrCamMode,
    pub pos: [f32; 3],
    /// view parameter (`w` of the position vector): < 4 selects an automatic framing, otherwise a field of view in degrees
    pub fov_param: f32,
    pub target: [f32; 3],
    pub frames: f32,
}

/// Fog set by retail op 0x06 and the location name of op 0x2b.
#[derive(Debug, Clone, Default)]
pub struct RetailState {
    pub fog_near: f32,
    pub fog_far: f32,
    pub fog_color: u32,
    pub fog_level: i32,
    pub far_plane: f32,
    pub location_name: String,
    /// op 0x2b sub 2: the `CFieldSocket` map name was replaced -- after the next battle the field reloads this map instead of the current one
    pub socket_map: Option<String>,
    pub name_slots: BTreeMap<i32, String>,
    pub cam_blur: Vec<i32>,
    /// op 0x1b: armed observers `(observer, target, sight, event)`
    pub sight: Vec<(i32, i32, i32, u32)>,
    pub effect_cmds: Vec<(i32, Vec<i32>)>,
    /// retail-only `SetFieldData` selectors (0x24 camera blur gain, 0x25, 0x27, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30 box sweep off, 0x31, 0x32, 0x33, 0x34, 0x35, 0x38 ...): last `(a, b)` per selector
    pub field_data_ex: BTreeMap<i32, (i32, i32)>,
}

#[derive(Default, Clone)]
pub struct ScriptState {
    /// `CField::MapJumpA(name, entry)`
    pub pending_jump: Option<(String, i32)>,
    /// `CFieldSocket::SetFader`: `(slot, mode, frames)`; slot 1 is the front fader (op 0x28), slot 0 the back one (op 0x29)
    pub faders: Vec<(u8, i32, i32)>,
    pub field_data: [i32; 8],
    /// pad edge of this tick (for `KeyWait`/`Select`)
    pub press: u16,
    pub warned: HashSet<(u8, u8)>,
    /// log of every engine call (tests and notes)
    pub log: Vec<String>,
    pub calls: u64,
    pub ticks: u64,
    /// an *event* job (not the start function) is running: the player is locked while it runs
    pub event_running: bool,
    pub unlock_watchdog: u32,
    /// calls to ops that fall through to the unknown-op arm: `(ex, sub) -> count`
    pub unimplemented: BTreeMap<(u8, u8), u64>,
    // -- UI / actors
    pub ui: UiState,
    pub actors: ActorTable,
    // -- requests
    pub audio: Vec<FieldAudio>,
    pub event_queue: Vec<(u32, Vec<u32>)>,
    pub battle: Option<BattleReq>,
    pub menu_req: Option<MenuReq>,
    /// a menu / shop opened by the script is still up: the script waits
    pub menu_wait: bool,
    pub world_map_jump: Option<(i32, i32, u32)>,
    pub game_over: bool,
    // -- data
    pub tables: Option<Arc<FieldTables>>,
    /// entry id the map was loaded with (`CField::nEntry_id`; -2 = coming back from a battle / load)
    pub map_entry: i32,
    /// saved character position to restore on `DispCharacterEP(slot, <0)` (position, yaw)
    pub restore: Option<([f32; 3], f32)>,
    // -- map state
    pub map_string: String,
    pub cmd_menu_mask: u16,
    pub help_flags: i32,
    pub menu_flags: (i32, i32),
    pub save_points: [Option<SavePointSlot>; 8],
    pub warp_points: [Option<WarpPointSlot>; 8],
    pub warp_fx: Option<WarpFx>,
    pub warp_state: i32,
    /// `CField::ChkSavePoint`: the save point slot under the player (updated every frame by `points::sync_points`)
    pub on_save_point: Option<usize>,
    pub on_warp_point: Option<usize>,
    /// the main menu was opened on a save point (`CommandMenu(4, on_save_point)` -> `CmdMenu +0x4a = 3`): the Data page may save
    pub menu_save_ok: bool,
    pub camera: Option<ScrCam>,
    pub look_points: Vec<(i32, [f32; 3])>,
    /// `CField` look-point table (`SetLookPoint`, 16 slots at +0x3f0): the circle-button hot spots of a map
    pub look: LookPoints,
    pub retail: RetailState,
    // -- sound estimates (until a backend reports the real state)
    pub se_until: BTreeMap<u32, u64>,
    /// ticks spent blocked in WaitBgm (0x54); released at AUDIO_WAIT_CAP_TICKS
    pub bgm_wait_ticks: u32,
    pub bgm_loaded: bool,
    // -- movie cut scenes
    pub mces: McesState,
    /// `CField::pEffect_list`: effects started by the script (`StartEffect`); they "run" for a fixed time
    pub effect_list: Vec<EffectSlot>,
    /// runner handles of effects the script removed (the plugin stops them)
    pub effect_removed: Vec<u32>,
    pub ring_result: i32,
    /// the field ring set up by `SetRing` (op 0x63)
    pub ring: Option<FieldRing>,
    /// result `RingControl` reports instead of "every area hit" (tests / the story walker)
    pub ring_override: Option<i32>,
    pub treasure_msg_quiet: bool,
    pub bg_models: usize,
    /// cumulative count of events queued for the VM (tests)
    pub events_queued: u64,
    pub navi: Vec<(i32, [f32; 3])>,
    pub vib_active: [bool; 4],
    pub equip_log: Vec<[i32; 5]>,
    pub disk_state: i32,
    pub world_flags: Vec<(i32, i32)>,
    /// party changes that need the battle databases (`SceneInit` = `BtlSaveSec::SetSceneInit`, `PCAddInit`): applied by the plugin /
    /// the story walker where `sh2_battle::BattleData` is available ([`crate::party::apply_party_ops`])
    pub party_ops: Vec<PartyOp>,
    /// `SetFieldData(0x17)`: the `GS` chunk flag bit 0 (`a1 == 0`)
    pub gs_flag0: bool,
    /// `SetFieldData(0x12)`: `GraveYardEnable(a1)`
    pub graveyard: i32,
    /// log of party changes (tests / the story walker)
    pub party_log: Vec<String>,
    /// running vibration sequences (`CField::aVib[]`) and their mixer, and the mixed motor output of the last tick
    pub vibes: BTreeMap<i32, sh2_audio::vibe::Vibe>,
    pub vibe_man: sh2_audio::vibe::VibeMan,
    pub vib_out: (f32, bool),
    /// message variable buffer (`CField+0x2170`): the name entered in the name entry screen, read back by `SpecialMenu(-1)`
    pub name_buffer: Vec<u8>,
    /// the map this one was entered from (fallback of `MapJump(1)` when the save's GS +0x20 is empty)
    pub prev_map: String,
}

/// `SetRing(kind, lap ms, ?, x, y, areas)` (op 0x63).
#[derive(Debug, Clone, PartialEq)]
pub struct FieldRing {
    pub kind: i32,
    pub lap_ms: i32,
    /// number of hit areas in the spec
    pub areas: i32,
    pub spec: String,
    /// colour code of each area (`C<n>` before each `S`), in order
    pub colours: Vec<i32>,
}

/// The colour codes of a `SetRing` area spec (`C4S10E70C2S100E125...`): one per `C<n>S..E..` area.
pub fn ring_colours(spec: &str) -> Vec<i32> {
    let b = spec.as_bytes();
    let mut out = vec![];
    let mut i = 0;
    while i < b.len() {
        if b[i] == b'C' {
            let mut j = i + 1;
            let mut v = 0i32;
            while j < b.len() && b[j].is_ascii_digit() {
                v = v * 10 + (b[j] - b'0') as i32;
                j += 1;
            }
            if j < b.len() && b[j] == b'S' {
                out.push(v);
            }
            i = j;
        } else {
            i += 1;
        }
    }
    out
}

/// A party change the field host cannot apply alone (it needs `SSHDAT` through the battle crate).
#[derive(Debug, Clone, PartialEq)]
pub enum PartyOp {
    /// `SetFieldData(0x13, scene)` = `SceneInit(scene)` -> `BtlSaveSec::SetSceneInit(scene, MENU[0] != 0)` (US 0x003f7bc0 / 0x003bc710)
    SceneInit(i32),
    /// `SetFieldData(0x20, pc)` = `BtlSaveSec::PCAddInit(pc)` (US 0x003c1600): create the record of a member joining later
    PcAdd(i32),
}

/// One `SetLookPoint(id, pos, radius, event, icon, view)` record (JP `CField+0x3f0 + slot * 0x10`: short pos + radius, `+8` event, `+0xc` id, `+0xe` icon / view nibbles).
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct LookPoint {
    pub id: i32,
    pub pos: [f32; 3],
    pub radius: f32,
    /// script event called when circle is pressed inside the radius (`SetFieldEvent(1, event, 0, 0, id)`)
    pub event: u32,
    /// icon shown over the avatar while attached (0xf = none)
    pub icon: u8,
    /// head turn towards the point while attached (0 = none)
    pub view: u8,
}

/// The 16-slot look point table plus the attached slot (`CField::bClr_flag_5ec - 1`).
#[derive(Debug, Clone, Default)]
pub struct LookPoints {
    pub slots: [Option<LookPoint>; 16],
    pub attached: Option<usize>,
}

impl LookPoints {
    /// JP 0x004b6a80 `SetLookPoint`: reuses the slot with the same id, else the first free one; -1 when full, 1 for a new record, 0 for an update.
    pub fn set(&mut self, p: LookPoint) -> i32 {
        let same = self.slots.iter().position(|s| s.map(|s| s.id == p.id).unwrap_or(false));
        let free = self.slots.iter().position(|s| s.is_none());
        match (same, free) {
            (Some(i), _) => {
                self.slots[i] = Some(p);
                0
            }
            (None, Some(i)) => {
                self.slots[i] = Some(p);
                1
            }
            _ => -1,
        }
    }

    /// JP 0x004b6c60 `ClrLookPoint(id)`: `id < 0` clears every record.  Returns true when the attached record was removed.
    pub fn clear(&mut self, id: i32) -> bool {
        let mut detached = false;
        for i in 0..self.slots.len() {
            if self.slots[i].map(|s| id < 0 || s.id == id).unwrap_or(false) {
                if self.attached == Some(i) {
                    self.attached = None;
                    detached = true;
                }
                self.slots[i] = None;
            }
        }
        detached
    }

    /// JP 0x004b6d40 `ChkLookPoint(attach)`: the first record whose radius contains `pos`; the attached record is dropped when the avatar left it.
    /// Returns `(newly attached, detached)` slot numbers.
    pub fn check(&mut self, pos: [f32; 3]) -> (Option<usize>, Option<usize>) {
        let inside = |s: &LookPoint| {
            let d = [s.pos[0] - pos[0], s.pos[1] - pos[1], s.pos[2] - pos[2]];
            (d[0] * d[0] + d[1] * d[1] + d[2] * d[2]).sqrt() <= s.radius
        };
        let mut first_in: Option<usize> = None;
        let mut leave: Option<usize> = None;
        for (i, s) in self.slots.iter().enumerate() {
            let Some(s) = s else { continue };
            if inside(s) {
                if first_in.is_none() {
                    first_in = Some(i);
                }
            } else if self.attached == Some(i) {
                leave = Some(i);
            }
        }
        if leave.is_none() && first_in.is_some() && self.attached.is_some() && first_in != self.attached {
            leave = self.attached;
        }
        let mut attached = None;
        let mut detached = None;
        if let Some(l) = leave {
            self.attached = None;
            detached = Some(l);
        }
        if let Some(i) = first_in {
            if self.attached != Some(i) {
                self.attached = Some(i);
                attached = Some(i);
            }
        }
        (attached, detached)
    }

    /// The default circle event of the attached record: `(event, id)`.
    pub fn circle_event(&self) -> Option<(u32, i32)> {
        let s = self.slots.get(self.attached?).copied().flatten()?;
        (s.event != 0).then_some((s.event, s.id))
    }
}

/// An effect (`.EFD`) started by `StartEffect(name, flags, gen, target)`.
#[derive(Debug, Clone)]
pub struct EffectSlot {
    pub name: String,
    pub flags: u32,
    /// `EffectControl(h, 0)`: 1 loading, 3 running (retail scripts wait for 3), 0 finished
    pub state: u8,
    pub ticks: u32,
    /// generating / target sets (`SetEffParameter`: flags byte 0 / 1 = counts, bits 16-19 / 20-23 = kinds; kind 0 = field model numbers,
    /// else 12-byte PS2-world positions)
    pub gen: Vec<EffPlace>,
    pub tar: Vec<EffPlace>,
    /// the renderer runs this effect (`FxRunner` handle): its state then comes from the program, not from the timer
    pub runner: Option<u32>,
    /// the renderer looked at this slot already (started it, or found no program)
    pub runner_tried: bool,
}

/// Where an effect is generated / aimed.
#[derive(Debug, Clone, Copy, PartialEq)]
pub enum EffPlace {
    /// a field model (slot number)
    Model(i32),
    /// a PS2-world position
    Pos([f32; 3]),
}

/// Ticks an effect is reported as loading / running before it ends (the real length lives in the .EFD).
pub const EFFECT_LOAD_TICKS: u32 = 2;
pub const EFFECT_RUN_TICKS: u32 = 180;

/// `CField::bMces_state` as far as scripts can tell: a movie ("MCES" = LSD cut scene) is played with `PlayMCES(name, flags, event)`.
/// The LSD player is not wired into the field yet, so a movie runs as a short placeholder whose end event fires normally.
#[derive(Debug, Clone, Default)]
pub struct McesState {
    pub state: u8,
    pub name: String,
    pub flags: i32,
    pub event: i32,
    pub ticks: u32,
    pub next_map: String,
    pub mode: i32,
    pub played: Vec<String>,
    /// the stream ran (state != 0) since the last time it was idle: its end triggers the `SetMCESMode` jump
    pub seen_active: bool,
}

impl ScriptState {
    pub fn new() -> Self {
        ScriptState { ..Default::default() }
    }
    pub fn msg_active(&self) -> bool {
        self.ui.msg_active()
    }
    /// SE playing estimate for `WaitSe/PlaySeR`
    fn se_playing(&self, id: u32) -> bool {
        self.se_until.get(&id).map(|&t| t > self.ticks).unwrap_or(false)
    }
}

/// WaitBgm safety cap (10 s at 60 Hz) so null/headless audio never deadlocks a script.
const AUDIO_WAIT_CAP_TICKS: u32 = 600;
pub const SE_ESTIMATE_TICKS: u64 = 40;

// ----------------------------------------------------------------------------------------------------------------
// the host
// ----------------------------------------------------------------------------------------------------------------

pub struct FieldHost<'a> {
    pub st: &'a mut ScriptState,
    pub sim: &'a mut FieldSim,
    pub session: Option<&'a mut GameSession>,
}

/// Raw bytes of the NUL-terminated string at script address `a` (Shift-JIS).
/// `SaveMenuSection::JoinBattle(pc, set, pin)` (JP 0x00289a60, US 0x00287770): move member `pc` (already in the set, at or after the battle
/// slots) to the end of the battle members (`+0x11` count, capacity `+0x10`); `pin` sets its bit in the pinned mask (`+0x1a`).
pub fn join_battle(p: &mut sh2_menu::save::PartySet, pc: u8, pin: bool) -> bool {
    if p.battle_count >= p.battle_max {
        return false;
    }
    let n = (p.member_count.max(0) as usize).min(8);
    let start = p.battle_count.max(0) as usize;
    for k in start..n {
        if p.members[k] == pc {
            let mut j = k;
            while j >= start && j > 0 {
                if j == start {
                    break;
                }
                p.members[j] = p.members[j - 1];
                j -= 1;
            }
            p.members[start] = pc;
            p.battle_count += 1;
            if pin {
                p.pinned_mask |= 1 << (pc & 15);
            }
            return true;
        }
    }
    false
}

/// US 0x003f4fe0: the s16 at `GS + 0x46` (a mini-game / scene counter): `a >= -1` stores it, `a == -3` restores it from `GS + 0x66`; returns the old value.
pub fn gs_word46(s: &mut GameSession, a: i32) -> i32 {
    let Some(c) = s.save.field.find_mut(sh2_menu::save::FieldSave::TAG_GS) else { return -1 };
    let (o, r) = (0x46 - 4, 0x66 - 4);
    if c.payload.len() < r + 2 {
        return -1;
    }
    let old = i16::from_le_bytes([c.payload[o], c.payload[o + 1]]) as i32;
    if a >= -1 {
        c.payload[o..o + 2].copy_from_slice(&(a as i16).to_le_bytes());
        return old;
    }
    if a == -3 {
        let v = [c.payload[r], c.payload[r + 1]];
        c.payload[o..o + 2].copy_from_slice(&v);
        return i16::from_le_bytes(v) as i32;
    }
    old
}

/// `CharacterEquip` on the demo-shaped save copy (record `+0x2d` weapon, `+0x2e` armour, `+0x2f..` accessories, `+0x32..` crests; bag counts).
pub fn character_equip(s: &mut GameSession, pc: i32, kind: i32, item: i32, slot: i32, mode: i32) {
    use sh2_menu::save::BtlSave;
    if !(0..sh2_menu::save::PC_COUNT as i32).contains(&pc) {
        return;
    }
    let rec = sh2_menu::save::PC_REC_BASE + pc as usize * sh2_menu::save::PC_REC_SIZE;
    let bag = s.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
    let (first, n, count) = match kind {
        2 => (0x2d, 1, Some(BtlSave::OFF_WEAPONS)),
        3 => (0x2e, 1, Some(BtlSave::OFF_ARMOR)),
        4 => (0x2f, 3, Some(BtlSave::OFF_ACCESSORIES)),
        5 => (0x32, 8, None),
        _ => return,
    };
    let (lo, hi) = if n > 1 && slot >= 0 { (slot.min(n - 1) as usize, slot.min(n - 1) as usize + 1) } else { (0, n as usize) };
    let d = &mut s.save.btl.data;
    let bump = |d: &mut Vec<u8>, idx: i8, delta: i32| {
        if let (Some(base), true) = (count, idx >= 0) {
            if let Some(c) = d.get_mut(base + bag + idx as usize) {
                *c = (*c as i32 + delta).clamp(0, 99) as u8;
            }
        }
    };
    if mode == 0 {
        for k in lo..hi {
            let old = d[rec + first + k] as i8;
            if old >= 0 {
                d[rec + first + k] = 0xff;
                bump(d, old, -1);
            }
        }
    } else if mode == 1 && item >= 0 {
        let free = (lo..hi).find(|&k| d[rec + first + k] as i8 == -1).unwrap_or(lo);
        let old = d[rec + first + free] as i8;
        bump(d, old, -1);
        d[rec + first + free] = item as u8;
        bump(d, item as i8, 1);
    }
}

/// Set / clear bit `bit` of the flag byte of party record `pc` (`BTL0 + pc * 0xc0 + 0x3c` retail, `+0x44` in the demo-shaped copy).
pub fn set_pc_flag(s: &mut GameSession, pc: u8, bit: u8, on: bool) {
    if pc as usize >= sh2_menu::save::PC_COUNT {
        return;
    }
    let o = sh2_menu::save::PC_REC_BASE + pc as usize * sh2_menu::save::PC_REC_SIZE;
    if let Some(b) = s.save.btl.data.get_mut(o) {
        if on {
            *b |= bit;
        } else {
            *b &= !bit;
        }
    }
}

pub fn raw_cstr(ctx: &ExCtx<'_>, a: u32) -> Vec<u8> {
    let mut v = Vec::new();
    for i in 0..1024u32 {
        match ctx.mem.r8(a.wrapping_add(i)) {
            Ok(0) | Err(_) => break,
            Ok(b) => v.push(b),
        }
    }
    v
}

fn put_f32s(ctx: &mut ExCtx<'_>, ptr: u32, v: &[f32]) {
    for (k, f) in v.iter().enumerate() {
        let _ = ctx.mem.w32(ptr + 4 * k as u32, f.to_bits());
    }
}

fn ascii(raw: &[u8]) -> String {
    String::from_utf8_lossy(raw).to_string()
}

struct NoLevels;
impl sh2_menu::btlsave::LevelTable for NoLevels {
    fn row(&self, _pc: usize, _level: u8) -> Option<sh2_menu::btlsave::LevelRow> {
        None
    }
}

impl FieldHost<'_> {
    fn tables(&self) -> Arc<FieldTables> {
        self.st.tables.clone().unwrap_or_default()
    }

    fn entry_point(&self, i: i32) -> Option<([f32; 3], i32)> {
        if i < 0 {
            return None;
        }
        let mps = self.sim.field.mps.as_ref()?;
        let eps = mps.entry_points().ok()?;
        eps.get(i as usize).map(|e| (e.pos, e.dir as i32))
    }

    fn queue_event(&mut self, id: u32, args: Vec<u32>) {
        self.st.events_queued += 1;
        self.st.event_queue.push((id, args));
    }

    /// Fire the events the actor table collected (path nodes, last-command events).
    fn drain_actor_events(&mut self) {
        for e in std::mem::take(&mut self.st.actors.events) {
            let ActorEvent::Fire { event, arg, slot } = e;
            if event != 0 {
                self.queue_event(event, vec![arg as u32, slot as u32]);
            }
        }
    }

    fn sync_actors_in(&mut self) {
        self.st.actors.sync_in(self.sim);
    }

    fn cam_pos(&self) -> [f32; 3] {
        self.sim.pose.map(|p| [p.pos[0], p.pos[1], p.pos[2]]).unwrap_or([0.0; 3])
    }

    // ------------------------------------------------------------------ audio
    fn audio(&mut self, a: FieldAudio) {
        self.st.audio.push(a);
    }

    // ------------------------------------------------------------------ inventory (JP main 0x003bc540 InventoryChange)
    /// `InventoryChange(kind, index, delta)`: returns the previous value.  Kinds: 1 items, 2 weapons, 3 armour, 4 accessories (byte
    /// counts, clamped 0..=99), 5/7/8/9/10/0x20/0x39/0x3c/0x3d/0x3e bit arrays (delta > 0 sets, < 0 clears), 0x3f/0x40 add / set cash.
    fn inventory_change(&mut self, kind: i32, idx: u32, delta: i32) -> i32 {
        let Some(s) = self.session.as_deref_mut() else { return 0 };
        let bag = s.save.btl.data[2] as usize * 0x200;
        let (base, bits): (usize, bool) = match kind {
            1 => (0x944 + bag, false),
            2 => (0x9c4 + bag, false),
            3 => (0xa24 + bag, false),
            4 => (0xa54 + bag, false),
            5 => (0xaa4 + bag, true),
            6 => (0xab8 + bag, false),
            7 => (0xda8, true),
            8 => (0xdae, true),
            9 => (0xdab, true),
            10 => (0x984 + bag, true),
            0x20 => (0xaae + bag, true),
            0x22 => (0xe37, false),
            0x23 => (0xe2f, false),
            0x24 => (0xdcf, false),
            0x25 => (0xe32, false),
            0x3c | 0x3e => (if kind == 0x3e { 0xe44 } else { 0xd4c }, true),
            0x3d => (0xd4c, true),
            0x40 => {
                let old = s.cash() as i32;
                s.add_cash(-old + delta.max(0));
                return old;
            }
            0x3f => {
                let old = s.cash() as i32;
                s.add_cash(delta);
                return old;
            }
            _ => return 0,
        };
        let idx = if kind == 0x3d { idx + 0xf } else { idx };
        let data = &mut s.save.btl.data;
        if bits {
            let o = base + (idx as usize >> 3);
            let Some(b) = data.get_mut(o) else { return 0 };
            let old = ((*b >> (idx & 7)) & 1) as i32;
            if delta > 0 {
                *b |= 1 << (idx & 7);
            } else if delta < 0 {
                *b &= !(1 << (idx & 7));
            }
            old
        } else {
            let o = base + idx as usize;
            let Some(b) = data.get_mut(o) else { return 0 };
            let old = *b as i32;
            *b = (old + delta).clamp(0, 99) as u8;
            old
        }
    }

    fn treasure_flag(&mut self, n: usize, v: i32) -> i32 {
        let Some(s) = self.session.as_deref_mut() else { return -1 };
        let old = s.save.field.treasure_flag(n);
        if v == 1 {
            s.save.field.set_treasure_flag(n, true);
        } else if v == 0 {
            s.save.field.set_treasure_flag(n, false);
        }
        // returns 1 while the chest is still closed
        (!old) as i32
    }

    // ------------------------------------------------------------------ the dispatcher
    fn op(&mut self, ctx: &mut ExCtx<'_>, sub: u8) -> ExResult {
        let first = ctx.nargs >= 0;
        match sub {
            // ---------------------------------------------------------------- characters
            // 0x00 GetCharacterInfo(slot, what) -> int
            0x00 => {
                self.sync_actors_in();
                let slot = ctx.arg_i32(0);
                let what = ctx.arg_i32(1);
                let v = if slot & 0x80 != 0 {
                    // BG model: only the motion state is tracked
                    match self.st.actors.bg.get((slot & 0x7f) as usize) {
                        Some(b) => match what {
                            3 => (!b.cmd_done) as i32,
                            _ => 0,
                        },
                        None => -1,
                    }
                } else {
                    match self.st.actors.get(slot) {
                        None => -1,
                        Some(a) => match what {
                            0 => a.char_id,
                            1 => {
                                let rot = wrap(a.yaw - std::f32::consts::PI);
                                let i = (rot * 5.0929594) as i32;
                                (if rot >= 0.0 { i } else { i + 0x20 }) % 0x1f
                            }
                            2 => a.event_id as i32,
                            3 => a.disp as i32,
                            4 => (a.cmd == Cmd::Move) as i32,
                            // US 0x004fe7e0: `+0x118` is the attach slot (0xff = none); 5 = 0 free / 1 on a character / 2 on a BG model, 6 = the slot
                            5 => match a.attach {
                                0xff => 0,
                                v if v & 0x80 == 0 => 1,
                                _ => 2,
                            },
                            6 => {
                                if a.attach == 0xff {
                                    -1
                                } else {
                                    (a.attach & 0x7f) as i32
                                }
                            }
                            7 => a.cmd_done as i32,
                            8 => (a.hit_check as i32) * 2 + a.floor_check as i32,
                            9 => a.talking as i32,
                            // US 0x004fe990 -> 0x00509c40: index (1..54) of the playing motion's name in the standard motion table
                            // (`fidl walk run sq_a ..`, FIELD.BIN 0x00610db4), 0 for any other motion
                            0xd => standard_motion_index(a.motion, &a.motion_name),
                            _ => 0,
                        },
                    }
                };
                ctx.set_ret(v as u32);
                ExResult::Int
            }
            // 0x01 SetCharacterInfo(slot, what, value)
            0x01 => {
                let (slot, what, v) = (ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2));
                if let Some(a) = self.st.actors.get_mut(slot) {
                    match what {
                        0x10 => a.ghost = true,
                        0xf => a.blink = v,
                        0xe => a.mirror = v,
                        0xc => a.paused_move = v != 0,
                        9 => a.talking = v & 1 != 0,
                        8 => {
                            a.floor_check = v & 1 != 0;
                            a.hit_check = (v >> 1) & 1 != 0;
                        }
                        2 => a.event_id = v as u32,
                        _ => {}
                    }
                }
                ExResult::Void
            }
            // 0x02 CharAddItem(slot, kind, name, flags) / 0x04 CharAddItemEx: attach a prop model
            // 0x02 CharAddItem(parent slot, child slot, frame name, mode) / 0x04 CharAddItemEx(child slot, BG model (< 0 = detach), frame name, mode):
            // US 0x004fdee0 `CField::CharAddItem` hangs the child model on a named frame of the parent; the child's `+0x118` records the parent
            // (`0x80 | index` for a BG model) and `GetCharacterInfo(child, 6)` reports it.
            0x02 | 0x04 => {
                let name = ascii(&raw_cstr(ctx, ctx.arg(2)));
                if sub == 0x02 {
                    let (parent, child) = (ctx.arg_i32(0), ctx.arg_i32(1));
                    if let Some(a) = self.st.actors.get_mut(parent) {
                        a.items.push((child, name));
                    }
                    if let Some(c) = self.st.actors.get_mut(child) {
                        c.attach = (parent & 0x7f) as u8;
                    }
                } else {
                    let (child, bg) = (ctx.arg_i32(0), ctx.arg_i32(1));
                    if let Some(c) = self.st.actors.get_mut(child) {
                        c.attach = if bg < 0 { 0xff } else { 0x80 | (bg & 0x7f) as u8 };
                    }
                }
                ExResult::Void
            }
            // 0x03 CharRemoveItem(slot, name): detach what hangs on `slot` (all of it for an empty name)
            0x03 => {
                let slot = ctx.arg_i32(0);
                let name = ascii(&raw_cstr(ctx, ctx.arg(1)));
                let mut freed: Vec<i32> = vec![];
                if let Some(a) = self.st.actors.get_mut(slot) {
                    if name.is_empty() {
                        freed = a.items.iter().map(|(c, _)| *c).collect();
                        a.items.clear();
                    } else {
                        freed = a.items.iter().filter(|(_, n)| *n == name).map(|(c, _)| *c).collect();
                        a.items.retain(|(_, n)| *n != name);
                    }
                }
                for c in freed {
                    if let Some(c) = self.st.actors.get_mut(c) {
                        c.attach = 0xff;
                    }
                }
                ExResult::Void
            }
            // 0x05 AttachFrame(kind, frame, light, model): light / navi attach points
            0x05 => ExResult::Void,
            // 0x07 LoadCharacterByName(slot, model name, event)
            0x07 => {
                let slot = ctx.arg_i32(0);
                let name = ascii(&raw_cstr(ctx, ctx.arg(1)));
                let ev = ctx.arg(2);
                self.st.actors.load(slot.max(0) as usize, &name, -1, ev);
                self.finish_load(slot)
            }
            // 0x08 LoadCharacter(slot, char_id, event)
            0x08 => {
                let slot = ctx.arg_i32(0);
                let id = ctx.arg_i32(1);
                let ev = ctx.arg(2);
                self.st.actors.load(slot.max(0) as usize, &format!("{id:03}"), id, ev);
                self.finish_load(slot)
            }
            // 0x09 UnloadCharacter(slot)
            0x09 => {
                self.st.actors.unload(ctx.arg_i32(0));
                ExResult::Void
            }
            // 0x0a DispCharacter(slot, x, y, z, dir, motion, flags)
            0x0a => {
                let slot = ctx.arg_i32(0);
                let pos = [ctx.arg_f32(1), ctx.arg_f32(2), ctx.arg_f32(3)];
                let (dir, motion) = (ctx.arg_i32(4), ctx.arg_i32(5));
                self.st.actors.disp(slot, 2, pos, dir, motion, None, self.sim);
                self.drain_actor_events();
                ExResult::Void
            }
            // 0x0b DispCharacterEP(slot, entry, motion, flags) / 0x12 with a motion name
            0x0b | 0x12 => {
                let slot = ctx.arg_i32(0);
                let entry = ctx.arg_i32(1);
                let (motion, name) = if sub == 0x0b { (ctx.arg_i32(2), None) } else { (0, Some(ascii(&raw_cstr(ctx, ctx.arg(2))))) };
                self.disp_ep(slot, entry, motion, name.as_deref());
                ExResult::Void
            }
            // 0x0c ClrCharacter(slot, mode)
            0x0c => {
                self.st.actors.clear(ctx.arg_i32(0), ctx.arg_i32(1));
                ExResult::Void
            }
            // 0x0d SetMoveMotion(slot, which, motion)
            0x0d => {
                let (slot, which, m) = (ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2));
                if let Some(a) = self.st.actors.get_mut(slot) {
                    if (0..3).contains(&which) {
                        a.move_motions[which as usize] = m;
                    }
                    let mm = a.move_motions;
                    self.st.actors.out.push(crate::script_actors::ActorOut::MoveMotion { slot: slot as usize, idle: if which == 0 { m } else { -1 }, walk: if which == 1 { m } else { -1 }, run: if which == 2 { m } else { -1 } });
                    let _ = mm;
                }
                ExResult::Void
            }
            // 0x0e LoadMotion(slot, name, flags) / 0x0f UnloadMotion(slot, name): asynchronous file loads, no state a script can see
            0x0e | 0x0f => ExResult::Void,
            // 0x10 SetMotion(slot, motion, flags)
            0x10 => {
                self.sync_actors_in();
                self.st.actors.set_motion(ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2));
                ExResult::Void
            }
            // 0x11 SetMotionByName(slot, name, flags)
            0x11 => {
                let name = ascii(&raw_cstr(ctx, ctx.arg(1)));
                let id = encode_motion_name(&name);
                self.st.actors.set_motion_raw(ctx.arg_i32(0), id, &name, ctx.arg_i32(2));
                ExResult::Void
            }
            // 0x14 WaitModel(slot, event): wait until the actor's last command finished, or (event != 0) call `event` when it does
            0x14 => {
                let slot = ctx.arg_i32(0);
                let ev = ctx.arg(1);
                if !(0..0x100).contains(&slot) {
                    return ExResult::Void;
                }
                let c = self.st.actors.check_last_cmd(slot);
                if c < 0 {
                    return ExResult::Void;
                }
                if c == 0 {
                    if !first || ev == 0 {
                        return ExResult::Yield(slot - 0x100);
                    }
                    self.st.actors.set_last_cmd_event(slot, ev);
                } else if first && ev != 0 {
                    self.st.actors.set_last_cmd_event(slot, ev);
                    self.drain_actor_events();
                }
                ExResult::Void
            }
            // 0x15 SetMotionSpeed(slot, speed)
            0x15 => {
                let slot = ctx.arg_i32(0);
                let sp = ctx.arg_f32(1);
                if let Some(a) = self.st.actors.get_mut(slot) {
                    a.motion_speed = sp;
                }
                ExResult::Void
            }
            // 0x16 SetCharacterDir(slot, spec, mode, speed)
            0x16 => {
                self.sync_actors_in();
                let cam = self.cam_pos();
                let eps: Vec<([f32; 3], i32)> = self.sim.field.mps.as_ref().and_then(|m| m.entry_points().ok()).map(|v| v.iter().map(|e| (e.pos, e.dir as i32)).collect()).unwrap_or_default();
                let (slot, spec, mode, speed) = (ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2), ctx.arg_i32(3));
                let sim = &mut *self.sim;
                self.st.actors.set_dir(slot, spec, mode, speed, sim, |i| eps.get(i as usize).map(|e| e.0), cam);
                ExResult::Void
            }
            // 0x17 GetPos(slot, vec*)
            0x17 => {
                self.sync_actors_in();
                let p = ctx.arg(1);
                let pos = self.st.actors.get(ctx.arg_i32(0)).map(|a| a.pos).unwrap_or([0.0; 3]);
                put_f32s(ctx, p, &pos);
                ExResult::Void
            }
            // 0x18 AutoMove(slot, vec*, final dir, gait, flags)
            0x18 => {
                let slot = ctx.arg_i32(0);
                let v = ctx.arg_vec(1, 3);
                let sim = &mut *self.sim;
                self.st.actors.auto_move(slot, [v[0], v[1], v[2]], ctx.arg_i32(2), ctx.arg_i32(3), ctx.arg_i32(4), sim);
                ExResult::Void
            }
            // 0x19 PathMove(slot, index / count, path*, event)
            0x19 => {
                let slot = ctx.arg_i32(0);
                let a1 = ctx.arg_i32(1);
                let ptr = ctx.arg(2);
                let ev = if ctx.argc > 3 { ctx.arg(3) } else { 0 };
                let (pts, dirs) = if ptr == 0 {
                    let paths = self.sim.field.mps.as_ref().and_then(|m| m.enemy_paths().ok()).unwrap_or_default();
                    match paths.get(a1.max(0) as usize) {
                        Some(p) => (p.points.iter().map(|q| q.pos).collect::<Vec<_>>(), p.points.iter().map(|q| (q.flags & 0xff) as i32).collect::<Vec<_>>()),
                        None => return ExResult::Int,
                    }
                } else {
                    let mut pts = vec![];
                    let mut dirs = vec![];
                    for k in 0..a1.clamp(0, 64) as u32 {
                        let o = ptr + k * 16;
                        let f = |j: u32| f32::from_bits(ctx.mem.r32(o + 4 * j).unwrap_or(0));
                        pts.push([f(0), f(1), f(2)]);
                        dirs.push((ctx.mem.r32(o + 12).unwrap_or(0) & 0xff) as i32);
                    }
                    (pts, dirs)
                };
                let sim = &mut *self.sim;
                self.st.actors.path_move(slot, pts, dirs, ev, false, sim);
                ExResult::Void
            }
            // 0x1a WaitCharacterEx(slot, mode)
            0x1a => {
                let slot = ctx.arg_i32(0);
                let mode = if ctx.argc > 1 { ctx.arg_i32(1) } else { 0 };
                if self.st.actors.wait_char_ex(slot, mode) {
                    ExResult::Void
                } else {
                    ExResult::Yield(slot - 0x80)
                }
            }
            // 0x1c SetManual(slot, on): script (0) or pad (1) control
            0x1c => {
                let (slot, on) = (ctx.arg_i32(0), ctx.arg_i32(1) != 0);
                if let Some(a) = self.st.actors.get_mut(slot) {
                    a.manual = on;
                    if on {
                        self.st.actors.ctrl = slot as usize;
                    }
                }
                ExResult::Void
            }
            // 0x1d SetViewPoint(slot, vec*, speed, limit) / 0x1e SetViewPointEP / 0x1f ClrViewPoint
            0x1d => {
                let v = ctx.arg_vec(1, 3);
                if let Some(a) = self.st.actors.get_mut(ctx.arg_i32(0)) {
                    a.view_point = Some([v[0], v[1], v[2]]);
                }
                ExResult::Void
            }
            0x1e => {
                let ep = ctx.arg_i32(1);
                let p = if ep < 0x80 { self.entry_point(ep).map(|e| e.0) } else { self.st.actors.get(ep & 0x7f).map(|a| a.pos) };
                if let Some(a) = self.st.actors.get_mut(ctx.arg_i32(0)) {
                    a.view_point = p;
                }
                ExResult::Void
            }
            0x1f => {
                if let Some(a) = self.st.actors.get_mut(ctx.arg_i32(0)) {
                    a.view_point = None;
                }
                ExResult::Void
            }
            // ---------------------------------------------------------------- map
            // 0x20 MapJump(name, entry, ?)
            0x20 => {
                if self.st.pending_jump.is_none() {
                    // `CField::MapJump(name)`: the pointer value 1 means `GetSavedMpsName(1)` (US 0x003f7c40: GS chunk +0x20 when set, else +0x10),
                    // the map the player came from -- the exits of shops, houses and dungeon rooms entered from several places
                    let given = if ctx.arg(0) == 1 { String::new() } else { ascii(&raw_cstr(ctx, ctx.arg(0))) };
                    let name = if given.is_empty() {
                        // fallbacks: the map this one was entered from, then GS +0x10 (`GetSavedMpsName` without a saved map), then this map
                        let saved = self.session.as_deref().and_then(|s| s.save.field.previous_map()).filter(|m| !m.is_empty());
                        let cur = self.session.as_deref().and_then(|s| s.save.field.current_map()).filter(|m| !m.is_empty());
                        saved
                            .or_else(|| (!self.st.prev_map.is_empty()).then(|| self.st.prev_map.clone()))
                            .or(cur)
                            .unwrap_or_else(|| self.sim.map.clone())
                    } else {
                        given
                    };
                    if ctx.arg(0) != 1 && name == self.sim.map {
                        self.st.log.push(format!("MapJump: empty name (pointer {:#x}) -> {name}", ctx.arg(0)));
                    }
                    self.st.pending_jump = Some((name, ctx.arg_i32(1)));
                    // US 0x004f8998: `SSHSys+0x54 = 1` (GetFieldData(0xd) in the next map)
                    if let Some(s) = self.session.as_deref_mut() {
                        s.ssh_sys[0] = 1;
                    }
                }
                // MapJumpA pauses the script; the map is torn down after the fade
                ExResult::Yield(-1)
            }
            // 0x21 SetMapString(name)
            0x21 => {
                self.st.map_string = ascii(&raw_cstr(ctx, ctx.arg(0)));
                ExResult::Void
            }
            // 0x22 AddLight(slot, frame, flags)
            0x22 => ExResult::Void,
            // 0x23 SetFieldData(sel, a, b)
            0x23 => {
                if ctx.arg_i32(0) == 0x2d {
                    // SetFieldData(0x2d, pc, name*): `strcpy(BTL0 + pc * 0xc0 + 0x46, name)` (the record name)
                    let name = raw_cstr(ctx, ctx.arg(2));
                    self.set_pc_name(ctx.arg_i32(1), &name);
                } else {
                    self.set_field_data(ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2));
                }
                ExResult::Void
            }
            // 0x24 GetFieldData(sel, a, b) -> int
            0x24 => {
                let v = self.get_field_data(ctx, ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2));
                ctx.set_ret(v as u32);
                ExResult::Int
            }
            // 0x25 SetBGMotion(bg index, motion, last motion)
            0x25 => {
                let i = (ctx.arg_i32(0) & 0x7f) as usize;
                let name = ascii(&raw_cstr(ctx, ctx.arg(1)));
                let last = if ctx.argc > 2 { ascii(&raw_cstr(ctx, ctx.arg(2))) } else { String::new() };
                while self.st.actors.bg.len() <= i {
                    self.st.actors.bg.push(Default::default());
                }
                let b = &mut self.st.actors.bg[i];
                b.motion = name;
                b.last_motion = if last.is_empty() { b.motion.clone() } else { last };
                b.left = 45;
                b.looping = false;
                b.cmd_done = false;
                ExResult::Void
            }
            // 0x26 GetFramePos(vec*, bg index, frame name) -> 1
            0x26 => {
                let p = ctx.arg(0);
                put_f32s(ctx, p, &[0.0, 0.0, 0.0, 1.0]);
                ctx.set_ret(1);
                ctx.mem.w32(p, 0).ok();
                ExResult::Int
            }
            // 0x27 GetEntryPoint(vec*, entry) -> dir (-1 when the entry does not exist)
            0x27 => {
                let (p, ep) = (ctx.arg(0), ctx.arg_i32(1));
                let r = self.entry_point(ep);
                if let Some((pos, _)) = r {
                    put_f32s(ctx, p, &pos);
                }
                let dir = r.map(|e| e.1).unwrap_or(-1);
                ctx.set_ret(dir as u32);
                ExResult::Int
            }
            // 0x28 / 0x29 SetFader(mode, frames): the front (1) and back (0) screen fader
            0x28 | 0x29 => {
                let slot = if sub == 0x28 { 1 } else { 0 };
                self.st.faders.push((slot, ctx.arg_i32(0), ctx.arg_i32(1)));
                ExResult::Void
            }
            // 0x2a SetBGMotionSpeed(bg index, speed)
            0x2a => {
                let i = (ctx.arg_i32(0) & 0x7f) as usize;
                if let Some(b) = self.st.actors.bg.get_mut(i) {
                    b.speed = ctx.arg_f32(1);
                }
                ExResult::Void
            }
            // 0x2c LoadImage(name, slot) / 0x2d DspImage(slot, x, y, a, b) / 0x2e ClrImage(slot, a, b, keep)
            0x2c => {
                let name = ascii(&raw_cstr(ctx, ctx.arg(0)));
                let slot = (ctx.arg_i32(1).max(0) as usize).min(7);
                self.st.ui.images[slot] = crate::script_ui::ImageSlot { name, ..Default::default() };
                ExResult::Void
            }
            0x2d => {
                let slot = (ctx.arg_i32(0).max(0) as usize).min(7);
                let im = &mut self.st.ui.images[slot];
                im.shown = true;
                im.x = ctx.arg_i32(1);
                im.y = ctx.arg_i32(2);
                im.a = ctx.arg_i32(3);
                im.b = ctx.arg_i32(4);
                ExResult::Void
            }
            0x2e => {
                let slot = (ctx.arg_i32(0).max(0) as usize).min(7);
                let keep = ctx.arg_i32(3) != 0;
                let im = &mut self.st.ui.images[slot];
                im.shown = false;
                if !keep {
                    *im = Default::default();
                }
                ExResult::Void
            }
            // ---------------------------------------------------------------- windows / messages / names / faces
            0x30 => {
                // CreateWindow(id, kind, flags, max chars)
                let id = (ctx.arg_i32(0).max(0) as usize).min(7);
                let w = &mut self.st.ui.windows[id];
                *w = Default::default();
                w.created = true;
                w.kind = ctx.arg_i32(1) as u8;
                w.flags = ctx.arg_i32(2) as u8;
                w.max_chars = (ctx.arg_i32(3).max(0x40)) as u16;
                self.st.ui.cur_win = id;
                ExResult::Void
            }
            0x31 => {
                self.st.ui.cur_win = (ctx.arg_i32(0).max(0) as usize).min(7);
                ExResult::Void
            }
            0x32 => {
                let w = self.st.ui.win();
                w.x = ctx.arg_i32(0);
                w.y = ctx.arg_i32(1);
                ExResult::Void
            }
            0x33 => {
                let w = self.st.ui.win();
                w.cols = ctx.arg_i32(0).clamp(1, 60) as u8;
                w.rows = ctx.arg_i32(1).clamp(1, 20) as u8;
                ExResult::Void
            }
            0x34 => {
                let w = self.st.ui.win();
                w.open(ctx.arg_i32(1));
                ExResult::Void
            }
            0x35 => {
                let w = self.st.ui.win();
                w.close(ctx.arg_i32(1));
                self.st.ui.select.active = false;
                ExResult::Void
            }
            // 0x36 OpenMessage(text, ?, talker slot)
            0x36 => {
                let raw = raw_cstr(ctx, ctx.arg(0));
                let talker = ctx.arg_i32(2);
                let speed = self.st.ui.speed;
                let w = self.st.ui.win();
                w.append(&raw, speed);
                w.talker = talker;
                if talker >= 0 {
                    if let Some(a) = self.st.actors.get_mut(talker) {
                        a.talking = true;
                    }
                }
                ExResult::Void
            }
            0x37 => {
                self.st.ui.win().clear();
                ExResult::Void
            }
            // 0x38 KeyWait: block until the message is typed and the circle button was pressed
            0x38 => self.key_wait(first),
            0x39 => {
                // CreateName(id, kind, flags, max)
                let id = (ctx.arg_i32(0).max(0) as usize).min(7);
                self.st.ui.names[id] = crate::script_ui::FieldWindow { created: true, kind: ctx.arg_i32(1) as u8, flags: ctx.arg_i32(2) as u8, cols: 16, rows: 1, ..Default::default() };
                self.st.ui.cur_name = id;
                ExResult::Void
            }
            0x3a => {
                self.st.ui.cur_name = (ctx.arg_i32(0).max(0) as usize).min(7);
                ExResult::Void
            }
            0x3b => {
                let w = self.st.ui.name();
                w.x = ctx.arg_i32(0);
                w.y = ctx.arg_i32(1);
                ExResult::Void
            }
            // 0x3c OpenName(text, frames kind, frames)
            0x3c => {
                let raw = raw_cstr(ctx, ctx.arg(0));
                let speed = TextSpeed::Instant;
                let w = self.st.ui.name();
                w.open(ctx.arg_i32(2));
                w.clear();
                w.append(&raw, speed);
                w.key_pending = false;
                ExResult::Void
            }
            0x3d => {
                let w = self.st.ui.name();
                w.close(ctx.arg_i32(1));
                ExResult::Void
            }
            // faces
            0x40 => {
                let id = (ctx.arg_i32(0).max(0) as usize).min(3);
                self.st.ui.cur_face = id;
                let f = &mut self.st.ui.faces[id];
                f.loaded = true;
                f.face_id = ctx.arg_i32(1);
                f.w = 96.0;
                f.h = 96.0;
                ExResult::Void
            }
            0x41 => {
                let i = ctx.arg_i32(0);
                if i < 0 {
                    for f in self.st.ui.faces.iter_mut() {
                        *f = Default::default();
                    }
                } else if let Some(f) = self.st.ui.faces.get_mut((i as usize).min(3)) {
                    *f = Default::default();
                }
                ExResult::Void
            }
            0x42 => {
                self.st.ui.cur_face = (ctx.arg_i32(0).max(0) as usize).min(3);
                ExResult::Void
            }
            0x43 => {
                let f = self.st.ui.face();
                f.x = ctx.arg_i32(0) as f32;
                f.y = ctx.arg_i32(1) as f32;
                ExResult::Void
            }
            0x44 => {
                let f = self.st.ui.face();
                f.w = ctx.arg_i32(0) as f32;
                f.h = ctx.arg_i32(1) as f32;
                ExResult::Void
            }
            0x45 => {
                self.st.ui.face().open = true;
                ExResult::Void
            }
            0x46 => {
                self.st.ui.face().open = false;
                ExResult::Void
            }
            // selection: 0x48 Select(mode, item..) -> index / -2 cancel; 0x49 SelectInit(mode); 0x4a SelectAddItem(text); 0x4b SelectWait -> index
            0x48 => self.select_op(ctx, first),
            0x49 => {
                self.select_init(ctx.arg_i32(0));
                ExResult::Void
            }
            0x4a => {
                let raw = raw_cstr(ctx, ctx.arg(0));
                self.st.ui.select.items.push(raw);
                ExResult::Void
            }
            0x4b => match self.select_poll() {
                Some(v) => {
                    ctx.set_ret(v as u32);
                    ExResult::Int
                }
                None => ExResult::Yield(-1),
            },
            // timers
            0x4e => {
                // TimerCreate(x, y, seconds, limit seconds, kind, alarm event)
                let t = &mut self.st.ui.timer;
                let limit = ctx.arg_i32(3);
                t.create(ctx.arg_i32(4), ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2) * 10, if limit > 0 { limit * 10 } else { limit }, ctx.arg(5));
                ExResult::Void
            }
            0x4f => {
                // TimerControl(op) -> count: 0 start, 1 stop, 3 show, 4 clear
                let t = &mut self.st.ui.timer;
                let c = if t.created { t.count } else { 0 };
                if t.created {
                    match ctx.arg_i32(0) {
                        4 => {
                            t.created = false;
                            t.running = false;
                            t.shown = false;
                        }
                        3 => t.shown = true,
                        1 => t.running = false,
                        0 => t.running = true,
                        _ => {}
                    }
                }
                ctx.set_ret(c as u32);
                ExResult::Int
            }
            // ---------------------------------------------------------------- audio
            0x50 => {
                let n = ascii(&raw_cstr(ctx, ctx.arg(0)));
                self.st.bgm_loaded = true;
                self.audio(FieldAudio::LoadBgm(n));
                ExResult::Void
            }
            0x51 => {
                self.audio(FieldAudio::PlayBgm { id: ctx.arg_i32(0), flags: ctx.arg(1) });
                ExResult::Void
            }
            0x52 => {
                self.audio(FieldAudio::BgmFade { ms: ctx.arg(0), flags: ctx.arg(1) });
                ExResult::Void
            }
            0x53 => {
                self.audio(FieldAudio::SetBgmVolume(ctx.arg_i32(0)));
                ExResult::Void
            }
            // 0x54 WaitBgm(kind): 0 = last fade finished, 1 = BGM finished, 2 = BGM loaded; bit 7 = non-blocking (poll only).
            // The audio engine tracks the condition (sh2_audio::status); a tick cap guards headless/null-audio runs.
            0x54 => {
                let w = sh2_audio::hooks::field_wait_op(sub, |i| ctx.arg_i32(i));
                let done = w.map(|w| w.done).unwrap_or(true);
                let blocking = w.map(|w| w.blocking).unwrap_or(false);
                if blocking && !done && self.st.bgm_wait_ticks < AUDIO_WAIT_CAP_TICKS {
                    self.st.bgm_wait_ticks += 1;
                    ExResult::Yield(-1)
                } else {
                    self.st.bgm_wait_ticks = 0;
                    ctx.set_ret(done as u32);
                    ExResult::Int
                }
            }
            0x55 => {
                let n = ascii(&raw_cstr(ctx, ctx.arg(0)));
                self.audio(FieldAudio::SetBattleBgm(n));
                ExResult::Void
            }
            0x56 => {
                let n = ascii(&raw_cstr(ctx, ctx.arg(0)));
                let slot = if ctx.argc > 1 { ctx.arg_i32(1) } else { 0 };
                self.audio(FieldAudio::LoadSe { name: n, slot });
                ExResult::Void
            }
            0x57 => {
                let a = ctx.arg(0);
                if a == 0 || a == u32::MAX {
                    // 0 -> all (the C swaps 0 / -1 before calling UnloadSe)
                    self.audio(FieldAudio::UnloadSe(None));
                } else {
                    let n = ascii(&raw_cstr(ctx, a));
                    self.audio(FieldAudio::UnloadSe(Some(n)));
                }
                ExResult::Void
            }
            0x58 => {
                let id = ctx.arg(0);
                self.st.se_until.insert(id, self.st.ticks + SE_ESTIMATE_TICKS);
                self.audio(FieldAudio::PlaySe { id, volume: ctx.arg_i32(1) });
                ExResult::Void
            }
            0x59 => {
                self.audio(FieldAudio::SetSeVolume(ctx.arg_i32(0)));
                ExResult::Void
            }
            0x5a => {
                let id = ctx.arg(0);
                self.st.se_until.remove(&id);
                self.audio(FieldAudio::StopSe(id));
                ExResult::Void
            }
            // 0x5b WaitSe(id, flags): wait for the SE to end unless bit 7 of the flags is set; result 1 = ended
            0x5b => {
                let id = ctx.arg(0);
                // real state from the audio engine, with the local duration estimate as a fallback (null/headless audio)
                let w = sh2_audio::hooks::field_wait_op(sub, |i| ctx.arg_i32(i));
                let engine_done = w.map(|w| w.done).unwrap_or(true);
                let playing = self.st.se_playing(id) && !engine_done;
                let nowait = ctx.arg(1) & 0x80 != 0;
                if !playing || nowait {
                    ctx.set_ret(!playing as u32);
                    ExResult::Int
                } else {
                    ExResult::Yield(-1)
                }
            }
            0x5c => {
                let pos = if ctx.argc > 4 && ctx.arg(4) != 0 {
                    let v = ctx.arg_vec(4, 3);
                    Some([v[0], v[1], v[2]])
                } else {
                    None
                };
                self.audio(FieldAudio::SetObjSe { index: ctx.arg_i32(0), a: ctx.arg(1), b: ctx.arg(2), c: ctx.arg_i32(3), pos });
                // round 5 CS hook: `CField::SetObjSE(slot, id, flags, n, FVector *points)` -> the audio layer's object sounds (id 0 clears the slot)
                {
                    let (slot, id, flags) = (ctx.arg_i32(0), ctx.arg(1), ctx.arg(2));
                    let n = if flags & 0xf == 2 { ctx.arg_i32(3).clamp(0, 15) as usize } else { 1 };
                    let pts: Vec<[f32; 3]> = if ctx.argc > 4 && ctx.arg(4) != 0 { ctx.arg_vec(4, 4 * n).chunks(4).map(|v| [v[0], v[1], v[2]]).collect() } else { Vec::new() };
                    let rec = (id != 0).then(|| sh2_audio::objse::ObjSeRec::from_script(id, flags, &pts));
                    sh2_audio::post(sh2_audio::AudioRequest::SetObjSe { slot, rec, one_shot: (flags >> 8) & 1 != 0 });
                }
                ExResult::Void
            }
            // 0x5d SetSoundData(which, a, b): 0 reverb, 1 flag, 2 stream fade, 3 query (-1 while a stream is busy)
            0x5d => {
                let w = ctx.arg_i32(0);
                match w {
                    0 => self.audio(FieldAudio::ReverbMode(ctx.arg_i32(1))),
                    2 => self.audio(FieldAudio::StreamFade(ctx.arg_i32(1))),
                    _ => self.audio(FieldAudio::SetSoundData { which: w, a: ctx.arg_i32(1), b: ctx.arg_i32(2) }),
                }
                ExResult::Void
            }
            0x5e => {
                let n = ascii(&raw_cstr(ctx, ctx.arg(0)));
                self.audio(FieldAudio::PlayStreamBgm { name: n, flags: ctx.arg_i32(1) });
                ExResult::Int
            }
            // 0x5f PlaySeR(mode, id, a, b): 0 play, 1 query (1 playing / -3 unknown), 2 play and wait for the end, 4 fade
            0x5f => {
                let mode = ctx.arg_i32(0);
                let id = ctx.arg(1);
                let r: i32 = match mode {
                    0 => {
                        self.st.se_until.insert(id, self.st.ticks + SE_ESTIMATE_TICKS);
                        self.audio(FieldAudio::PlaySeR { mode: 0, id, a: ctx.arg_i32(2), b: ctx.arg_i32(3) });
                        0
                    }
                    1 => {
                        if self.st.se_until.contains_key(&id) {
                            self.st.se_playing(id) as i32
                        } else {
                            -3
                        }
                    }
                    4 => {
                        self.audio(FieldAudio::PlaySeR { mode: 4, id, a: ctx.arg_i32(2), b: ctx.arg_i32(3) });
                        1
                    }
                    2 => {
                        if first {
                            self.st.se_until.insert(id, self.st.ticks + SE_ESTIMATE_TICKS);
                            self.audio(FieldAudio::PlaySeR { mode: 0, id, a: ctx.arg_i32(2), b: 0 });
                        }
                        if self.st.se_playing(id) {
                            return ExResult::Yield(-11);
                        }
                        0
                    }
                    _ => 0,
                };
                ctx.set_ret(r as u32);
                ExResult::Int
            }
            // 0x60 StartEffect(name, flags, pos*, rot*) -> handle; 0x61 EffectControl(handle, cmd, a, b) -> int
            0x60 => {
                let name = ascii(&raw_cstr(ctx, ctx.arg(0)));
                let flags = ctx.arg(1);
                let read = |ctx: &ExCtx<'_>, p: u32, n: u32, kind: u32| -> Vec<EffPlace> {
                    if p == 0 {
                        return vec![];
                    }
                    (0..n.min(16))
                        .map(|i| {
                            if kind == 0 {
                                EffPlace::Model(ctx.mem.r8(p + i).unwrap_or(0) as i8 as i32)
                            } else {
                                let f = |k: u32| f32::from_bits(ctx.mem.r32(p + i * 12 + k * 4).unwrap_or(0));
                                EffPlace::Pos([f(0), f(1), f(2)])
                            }
                        })
                        .collect()
                };
                let gen = read(ctx, ctx.arg(2), flags & 0xff, (flags >> 16) & 0xf);
                let tar = read(ctx, ctx.arg(3), (flags >> 8) & 0xff, (flags >> 20) & 0xf);
                self.st.effect_list.push(EffectSlot { name, flags, state: 1, ticks: 0, gen, tar, runner: None, runner_tried: false });
                ctx.set_ret(self.st.effect_list.len() as u32);
                ExResult::Int
            }
            // EffectControl(handle, cmd, a, b): cmd 0 -> state (0 ended, 1 loading, 2 running), cmd 1 -> remove; handle 0 and 1 both mean the first
            0x61 => {
                let h = ctx.arg_i32(0);
                let idx = (h - 1).max(0) as usize;
                let r = match self.st.effect_list.get(idx).map(|e| e.state) {
                    None => -1,
                    Some(state) => match ctx.arg_i32(1) {
                        1 => {
                            // RemoveEffect unlinks the node: later handles shift down
                            let e = self.st.effect_list.remove(idx);
                            if let Some(h) = e.runner {
                                self.st.effect_removed.push(h);
                            }
                            0
                        }
                        0 => state as i32,
                        _ => -1,
                    },
                };
                ctx.set_ret(r as u32);
                ExResult::Int
            }
            0x62 => self.mces(ctx, first),
            // 0x63 SetRing(id, kind, a, b, c, name); 0x64 RingControl(..) / RingResult
            // 0x63 SetRing(type, lap ms, ?, x, y, areas): the field Judgement Ring (US 0x004fad40); areas = "C<colour>S<start>E<end>..." per area
            0x63 => {
                let spec = if ctx.argc > 5 { ascii(&raw_cstr(ctx, ctx.arg(5))) } else { String::new() };
                let areas = spec.matches('S').count() as i32;
                let colours = ring_colours(&spec);
                self.st.ring = Some(FieldRing { kind: ctx.arg_i32(0), lap_ms: ctx.arg_i32(1), areas, spec, colours });
                ExResult::Void
            }
            // 0x64 RingControl(1, ..): run the ring and wait for its result (US 0x004f9948 -> 0x004fb3e0: `CField+0x8b0` once the ring is over).
            // The port has no field ring screen yet: the ring is "played" at once with `ring_result` (default: every area hit = the area count).
            0x64 => {
                if first {
                    return ExResult::Yield(-10);
                }
                // the JRing reports through its event 0x80 (`cbRing` US 0x004faf20 stores the result word at `CField+0x8b0`); for these
                // "event" rings with coloured areas the scripts compare it with the colour codes 1..4: the colour of the area the pointer
                // stopped in.  Without a ring screen the port answers the first area's colour (`ring_override` for tests / the walker)
                let r = self.st.ring_override.unwrap_or_else(|| self.st.ring.as_ref().and_then(|r| r.colours.first().copied()).unwrap_or(0));
                self.st.ring_result = r;
                ctx.set_ret(r as u32);
                ExResult::Int
            }
            0x65 => self.warp_op(ctx, first),
            0x66 => {
                // InventoryChange(kind, idx, count): script kinds 0..8 map onto the save kinds
                let k = ctx.arg_i32(0);
                let real = match k {
                    0 => 0x3c,
                    1 => 0x3e,
                    2 => 0x21,
                    3 => 0x39,
                    4 => 0x22,
                    5 => 0x23,
                    6 => 0x24,
                    7 => 0x25,
                    8 => 0x3d,
                    _ => return ExResult::Void,
                };
                self.inventory_change(real, ctx.arg(1), ctx.arg_i32(2));
                ExResult::Void
            }
            0x67 => {
                // NaviItem(op, id, slot/state, a, vec*, b, c)
                let op = ctx.arg_i32(0);
                let id = ctx.arg_i32(1);
                match op {
                    0 => {
                        let p = if ctx.argc > 4 && ctx.arg(4) != 0 { ctx.arg_vec(4, 3) } else { vec![0.0; 3] };
                        self.st.navi.push((id, [p[0], p[1], p[2]]));
                    }
                    3 => self.st.navi.retain(|(i, _)| *i != id),
                    _ => {}
                }
                ExResult::Void
            }
            0x68 => {
                // CharacterEquip(pc, kind, item, slot, mode) (US 0x003f4aa0): kind 2 weapon, 3 armour, 4 accessory (3 slots), 5 crest (8 slots), 7 dress;
                // mode 0 takes the equipment off (slot < 0: every slot) and out of the bag, mode 1 gives `item` and puts it in the first free slot
                let (pc, kind, item, slot, mode) = (ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2), ctx.arg_i32(3), ctx.arg_i32(4));
                self.st.equip_log.push([pc, kind, item, slot, mode]);
                if let Some(s) = self.session.as_deref_mut() {
                    character_equip(s, pc, kind, item, slot, mode);
                }
                ctx.set_ret(1);
                ExResult::Int
            }
            // vibration 0x69-0x6e (JP 0x004b8710 StartVib / 0x004b8950 VibControl): the map's `GENERIC` "VIBRATION" block holds the sequences
            // (`CVibeMan::GetSeqData(block, seq)`), run by `sh2_audio::vibe` (CS4); `tick_state` polls them, the plugin forwards the motor output
            0x69 | 0x6a => {
                let (slot, seq, vol) = (ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2));
                let ch = (slot.max(0) as usize).min(3);
                self.st.vib_active[ch] = true;
                if sub == 0x69 {
                    let blob = self.sim.field.mps.as_ref().and_then(|m| m.generic().into_iter().find(|(n, _)| n.eq_ignore_ascii_case("VIBRATION")).map(|(_, b)| b.to_vec()));
                    if let Some(sq) = blob.as_deref().and_then(sh2_audio::vibe::VibeBlob::parse).and_then(|b| b.sequence(seq.max(0) as usize)) {
                        let mut v = sh2_audio::vibe::Vibe::start(sq, &mut self.st.vibe_man);
                        v.set_master(vol.clamp(0, 0xff) as u8);
                        self.st.vibes.insert(slot, v);
                    }
                }
                ExResult::Void
            }
            // 0x6b StopVib(slot, fade ms): slot < 0 = all
            0x6b => {
                let (slot, fade) = (ctx.arg_i32(0), ctx.arg_i32(1));
                if slot < 0 {
                    if fade < 1 {
                        self.st.vibes.clear();
                    } else {
                        for v in self.st.vibes.values_mut() {
                            v.set_fader(0, fade as u32, true);
                        }
                    }
                    self.st.vib_active = [false; 4];
                } else {
                    let playing = self.st.vibes.get(&slot).map(|v| v.playing).unwrap_or(false);
                    if !playing || fade < 1 {
                        self.st.vibes.remove(&slot);
                    } else if let Some(v) = self.st.vibes.get_mut(&slot) {
                        v.set_fader(0, fade as u32, true);
                    }
                    self.st.vib_active[(slot as usize).min(3)] = false;
                }
                ExResult::Void
            }
            // 0x6c FadeVib(slot, volume, ms): slot < 0 = the mixer's master volume; 0x6d PauseVib(slot, on)
            0x6c => {
                let (slot, vol, ms) = (ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2));
                if slot < 0 {
                    self.st.vibe_man.volume = (vol.clamp(0, 0x80) / 2) as u8;
                } else if let Some(v) = self.st.vibes.get_mut(&slot).filter(|v| v.playing) {
                    v.set_fader(vol.clamp(0, 0x80) as u8, ms.max(0) as u32, false);
                }
                ExResult::Void
            }
            0x6d => {
                let (slot, on) = (ctx.arg_i32(0), ctx.arg_i32(1) != 0);
                if slot < 0 {
                    self.st.vibe_man.muted = on;
                } else if let Some(v) = self.st.vibes.get_mut(&slot) {
                    v.pause(on);
                }
                ExResult::Void
            }
            // 0x6e IsVib(slot)
            0x6e => {
                let slot = ctx.arg_i32(0);
                let playing = self.st.vibes.get(&slot).map(|v| v.playing).unwrap_or(false);
                ctx.set_ret(playing as u32);
                ExResult::Int
            }
            // 0x6f DiskChange(disc, event): single disc image => completes at once
            0x6f => {
                self.st.disk_state = 0;
                ExResult::Void
            }
            // ---------------------------------------------------------------- world map / battle
            // 0x70 SetWorldMapPoint(index, state): 2-bit state + flag at WM chunk +0x10+index
            0x70 => {
                let (idx, mut state) = (ctx.arg_i32(0), ctx.arg_i32(1));
                self.st.world_flags.push((idx, state));
                let three = state == 3;
                if three {
                    state = 2;
                }
                if let Some(s) = self.session.as_deref_mut() {
                    if let Some(c) = s.save.field.find_mut(sh2_menu::save::FieldSave::TAG_WM) {
                        if let Some(b) = c.payload.get_mut(0xc + idx.max(0) as usize) {
                            *b = (*b & 0xfc) | (state as u8 & 3);
                            let bit2 = ((*b >> 2) & 1) | three as u8;
                            *b = (*b & 0xfb) | (bit2 << 2);
                            if state == 1 {
                                *b &= 0xfb;
                            }
                        }
                    }
                }
                ExResult::Void
            }
            // 0x71 WorldMapJump(world, sub, extra)
            0x71 => {
                if self.st.world_map_jump.is_none() {
                    self.st.world_map_jump = Some((ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg(2)));
                }
                ExResult::Yield(-1)
            }
            // 0x72 InvokeBattle(boss, bg, bgm, party set, monster set)
            0x72 => {
                if self.st.battle.is_none() {
                    self.st.battle = Some(BattleReq {
                        boss: ctx.arg_i32(0) != 0,
                        background: ctx.arg_i32(1),
                        bgm: ctx.arg_i32(2),
                        party_set: ctx.arg_i32(3),
                        monster_set: ctx.arg_i32(4),
                        flag: 1,
                    });
                }
                ExResult::Yield(-1)
            }
            // 0x73 InvokeBattleTbl(table index, party set)
            0x73 => {
                if self.st.battle.is_none() {
                    let t = self.tables();
                    if let Some(r) = t.bbtl.get(ctx.arg_i32(0).max(0) as usize) {
                        let w = |o: usize| u16::from_le_bytes([r[o], r[o + 1]]) as i32;
                        self.st.battle = Some(BattleReq { boss: r[6] != 0, background: w(0), bgm: w(2), party_set: ctx.arg_i32(1), monster_set: w(4), flag: 1 });
                    } else {
                        return ExResult::Void;
                    }
                }
                ExResult::Yield(-1)
            }
            // ---------------------------------------------------------------- camera
            0x74 => {
                // SetCameraA(pos*, slot, frames, aim flags): fixed position looking at an actor
                let p = ctx.arg_vec(0, 4);
                self.st.camera = Some(ScrCam {
                    mode: ScrCamMode::Look { slot: ctx.arg_i32(1), aim: ctx.arg_i32(3) & 0xf },
                    pos: [p[0], p[1], p[2]],
                    fov_param: p[3],
                    target: [0.0; 3],
                    frames: ctx.arg_f32(2),
                });
                self.sim.field.camera.comp_frame(ctx.arg_f32(2));
                ExResult::Void
            }
            0x75 => {
                // SetCameraB(pos*, slotA, slotB, frames): frame two actors
                let p = ctx.arg_vec(0, 4);
                self.st.camera = Some(ScrCam {
                    mode: ScrCamMode::TwoShot { a: ctx.arg_i32(1), b: ctx.arg_i32(2) },
                    pos: [p[0], p[1], p[2]],
                    fov_param: p[3],
                    target: [0.0; 3],
                    frames: ctx.arg_f32(3),
                });
                self.sim.field.camera.comp_frame(ctx.arg_f32(3));
                ExResult::Void
            }
            // 0x76 SetCameraC(type, pos*, target*, frames) / WaitCamera when type < 0 or on resume
            0x76 => {
                let ty = ctx.arg_i32(0);
                if first && ty >= 0 {
                    let p = ctx.arg_vec(1, 4);
                    let t = ctx.arg_vec(2, 3);
                    let mut target = [t[0], t[1], t[2]];
                    let pos = [p[0], p[1], p[2]];
                    match ty {
                        1 => {
                            // direction: look 20 units along it
                            let l = (t[0] * t[0] + t[1] * t[1] + t[2] * t[2]).sqrt().max(1e-4);
                            target = [pos[0] + t[0] / l * 20.0, pos[1] + t[1] / l * 20.0, pos[2] + t[2] / l * 20.0];
                        }
                        2 => {
                            // angles (`UpdateScrCamera` case 5): target = pos + RotY(yaw) * RotX(pitch) * (0, 0, len) with `len` = the current camera
                            // distance (30 when it is 0); pitch (deg) in x, yaw (deg) in y.  (0, 0, +len) is the *+z* direction: yaw 0 looks along +z.
                            let len = self.sim.pose.map(|c| {
                                let d = [c.pos[0] - c.target[0], c.pos[1] - c.target[1], c.pos[2] - c.target[2]];
                                (d[0] * d[0] + d[1] * d[1] + d[2] * d[2]).sqrt()
                            }).filter(|l| *l > 0.0).unwrap_or(30.0);
                            target = angles_target(pos, t[0], t[1], len);
                        }
                        _ => {}
                    }
                    self.st.camera = Some(ScrCam { mode: ScrCamMode::Fixed, pos, fov_param: p[3], target, frames: ctx.arg_f32(3) });
                    self.sim.field.camera.comp_frame(ctx.arg_f32(3));
                    ExResult::Void
                } else if self.sim.field.camera.is_comp() {
                    ExResult::Yield(-10)
                } else {
                    ExResult::Void
                }
            }
            // 0x78 RestoreCamera(frames)
            0x78 => {
                self.st.camera = None;
                self.sim.scr_cam = None;
                let f = ctx.arg_f32(0);
                if f > 0.0 {
                    self.sim.field.camera.comp_frame(f);
                }
                ExResult::Void
            }
            // 0x79 TreasureControl(mode, index, ..) -> int
            0x79 => {
                let v = self.treasure(ctx, ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2));
                ctx.set_ret(v as u32);
                ExResult::Int
            }
            // 0x7a SetLookPoint(id, vec*, radius, flags, a, b) -> id
            // 0x7a SetLookPoint(id, pos, radius, event, icon, view): a circle-button hot spot (JP 0x004b6a80)
            0x7a => {
                let id = ctx.arg_i32(0);
                let v = ctx.arg_vec(1, 3);
                self.st.look_points.retain(|(i, _)| *i != id);
                self.st.look_points.push((id, [v[0], v[1], v[2]]));
                let r = self.st.look.set(LookPoint {
                    id,
                    pos: [v[0], v[1], v[2]],
                    radius: ctx.arg_f32(2),
                    event: ctx.arg(3),
                    icon: (ctx.arg_i32(4) & 0xf) as u8,
                    view: (ctx.arg_i32(5) & 0xf) as u8,
                });
                ctx.set_ret(r as u32);
                ExResult::Int
            }
            0x7b => {
                let id = ctx.arg_i32(0);
                if id < 0 {
                    self.st.look_points.clear();
                } else {
                    self.st.look_points.retain(|(i, _)| *i != id);
                }
                if self.st.look.clear(id) {
                    // `DetachLookPoint`: the icon goes away
                    let ctrl = self.st.actors.ctrl as i32;
                    if let Some(a) = self.st.actors.get_mut(ctrl) {
                        a.icon = -1;
                    }
                }
                ExResult::Void
            }
            // 0x7c DspIcon(slot, icon)
            0x7c => {
                if let Some(a) = self.st.actors.get_mut(ctx.arg_i32(0)) {
                    a.icon = ctx.arg_i32(1);
                }
                ExResult::Void
            }
            0x7d => self.param_change(ctx),
            0x7e => self.save_point(ctx),
            0x7f => self.special_menu(ctx, first),
            // ---------------------------------------------------------------- vector math (VectorOperation, JP 0x004b1590)
            0x80..=0x8c => self.vector_op(ctx, sub),
            // ---------------------------------------------------------------- retail-only commands (US build)
            0x06 => {
                // BgFog(mode, near/level, far, color)
                let m = ctx.arg_i32(0);
                let r = &mut self.st.retail;
                match m {
                    0 | 1 => {
                        r.fog_near = ctx.arg_f32(2);
                        r.fog_far = ctx.arg_f32(3);
                        r.fog_color = ctx.arg(1);
                    }
                    2 => r.fog_level = ctx.arg_i32(1),
                    3 => r.fog_level = -1,
                    _ => {}
                }
                ExResult::Void
            }
            0x1b => {
                // SetNpcSight(observer, target, sight, event) -> result code
                let (o, t, s, e) = (ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2), ctx.arg(3));
                let r = if o == t {
                    -9
                } else if t < 0 {
                    if t == -2 {
                        self.st.retail.sight.clear();
                    } else {
                        self.st.retail.sight.retain(|x| x.0 != o);
                    }
                    0
                } else if e != 0 {
                    self.st.retail.sight.retain(|x| x.0 != o);
                    self.st.retail.sight.push((o, t, s, e));
                    0
                } else {
                    -4 // no TRILIST => no line-of-sight data
                };
                ctx.set_ret(r as u32);
                ExResult::Int
            }
            0x2b => {
                // US 0x004f8be0: sub 0: far plane; sub 1 (a, name): the name of party set `a` (`MENU + 0x84 + a * 0x20`, <= 14 chars, the team
                // names of the story presets); sub 2 (name): `strcpy(CFieldSocket + 0x64, name)` = the socket's current map name -- the map the
                // field reloads after the next battle / load (AR_15_U: N013 -> boss -> HUB_NA) -- and `CField+0x17a` bit 6
                let m = ctx.arg_i32(0);
                match m {
                    0 => self.st.retail.far_plane = ctx.arg_f32(2),
                    1 => {
                        let raw = raw_cstr(ctx, ctx.arg(3));
                        let set = ctx.arg_i32(1);
                        let n = ascii(&raw);
                        self.edit_set(set, |p| {
                            let k = raw.iter().position(|&c| c == 0).unwrap_or(raw.len()).min(14);
                            p.name = raw[..k].to_vec();
                        });
                        self.st.retail.name_slots.insert(set, n);
                    }
                    2 => {
                        let n = ascii(&raw_cstr(ctx, ctx.arg(3)));
                        self.st.retail.location_name = n.clone();
                        self.st.retail.socket_map = Some(n);
                    }
                    _ => {}
                }
                ExResult::Void
            }
            0x2f => {
                let a: Vec<i32> = (0..ctx.argc).map(|i| ctx.arg_i32(i)).collect();
                self.st.retail.effect_cmds.push((a[0], a));
                ExResult::Void
            }
            0x4c => {
                // SelectInit2(mode, position)
                self.select_init(ctx.arg_i32(0));
                ExResult::Void
            }
            0x4d => {
                // InvokeCmdScene(a, b): open a command-menu scene and wait until it closes
                if first {
                    self.st.menu_req = Some(MenuReq::CmdScene { a: ctx.arg_i32(0), b: ctx.arg_i32(1) });
                    self.st.menu_wait = true;
                }
                if self.st.menu_wait {
                    ExResult::Yield(-1)
                } else {
                    ExResult::Void
                }
            }
            0x77 => {
                let a: Vec<i32> = (0..ctx.argc).map(|i| ctx.arg_i32(i)).collect();
                self.st.retail.cam_blur = a;
                ExResult::Void
            }
            _ => {
                *self.st.unimplemented.entry((0xc2, sub)).or_insert(0) += 1;
                if self.st.warned.insert((0xc2, sub)) {
                    log::debug!("field script: op {sub:#04x} is not implemented");
                }
                ExResult::Void
            }
        }
    }

    fn finish_load(&mut self, slot: i32) -> ExResult {
        // LoadCharacter + SetCmd(1): the model counts as loaded once the "read" finished; the placeholder loads at once
        let _ = slot;
        ExResult::Void
    }

    /// `InitSDB`: put the (carried) control model on entry point `entry` and show it.
    pub fn show_at_entry(&mut self, slot: i32, entry: i32) {
        self.disp_ep(slot, entry, 0, None);
    }

    /// Fallback for a scene that hands control back to a control slot that holds no model (seen: RU_00_U after the Louvre 1 scene, whose
    /// start function never loads slot 0 on that branch): load `char_id` (the "controlled character" register byte 0) into the control
    /// slot at the map's entry point and give it to the pad.  Returns true when it had to do so.  Unverified against the console (see r5_fs.md).
    pub fn ensure_control_model(&mut self, char_id: i32) -> bool {
        let ctrl = self.st.actors.ctrl;
        if self.st.actors.get(ctrl as i32).map(|a| a.loaded).unwrap_or(false) {
            return false;
        }
        self.st.actors.load(ctrl, &format!("{char_id:03}"), char_id, 0);
        let entry = self.st.map_entry.max(0);
        self.disp_ep(ctrl as i32, entry, 1, None);
        if let Some(a) = self.st.actors.get_mut(ctrl as i32) {
            a.manual = true;
        }
        self.st.log.push(format!("fallback: control model {char_id} loaded into slot {ctrl}"));
        true
    }

    /// `CField::DispCharacterEP(slot, entry, motion, ..)` (JP 0x004b34e0)
    fn disp_ep(&mut self, slot: i32, mut entry: i32, motion: i32, name: Option<&str>) {
        self.sync_actors_in();
        let mut place = if entry >= 0 { 2 } else { 0 };
        if entry == -1 && self.st.map_entry != -1 {
            entry = self.st.map_entry;
        }
        let mut pos = self.st.actors.get(slot).map(|a| a.pos).unwrap_or([0.0; 3]);
        let mut dir = -1;
        let mut restored = false;
        if entry < 0 {
            if slot as usize == self.st.actors.ctrl {
                if let Some((p, yaw)) = self.st.restore.take() {
                    pos = p;
                    place = 1;
                    restored = true;
                    // the saved heading is a direction-of-travel yaw: store it through a fake index-free path
                    if let Some(a) = self.st.actors.get_mut(slot) {
                        a.yaw = yaw;
                    }
                    dir = -1;
                }
            }
            if entry == -2 {
                place = 1;
            }
        } else if let Some((p, d)) = self.entry_point(entry) {
            pos = p;
            dir = d;
            if place == 0 {
                place = 1;
            }
        }
        if place == 1 && slot as usize == self.st.actors.ctrl && dir < 0 && !restored {
            // keep the player's current position (restored by the map loader)
            pos = self.sim.player.pos;
        }
        let sim = &mut *self.sim;
        self.st.actors.disp(slot, place, pos, dir, motion, name, sim);
        self.drain_actor_events();
    }

    fn key_wait(&mut self, first: bool) -> ExResult {
        let press = self.st.press & padbit::CIRCLE != 0;
        let i = self.st.ui.cur_win.min(7);
        let w = &mut self.st.ui.windows[i];
        if !w.created && w.msg.is_none() || w.msg.is_none() || !w.is_open() {
            return ExResult::Void;
        }
        if !w.key_pending {
            return ExResult::Void;
        }
        if press && !first {
            let m = w.msg.as_mut().unwrap();
            if m.state != MsgState::Done {
                m.finish();
                return ExResult::Yield(-1);
            }
            w.key_pending = false;
            let talker = w.talker;
            if talker >= 0 {
                if let Some(a) = self.st.actors.get_mut(talker) {
                    a.talking = false;
                }
            }
            return ExResult::Void;
        }
        ExResult::Yield(-1)
    }

    // ------------------------------------------------------------------ selection (CField::Select*)
    fn select_init(&mut self, mode: i32) {
        let i = self.st.ui.cur_win.min(7);
        let s = &mut self.st.ui.select;
        *s = Default::default();
        s.window = i;
        s.mode = mode & 3;
        s.cancel_ok = mode & 4 != 0;
        let w = &mut self.st.ui.windows[i];
        w.clear();
        if !w.is_open() {
            w.open(4);
        }
    }

    fn select_poll(&mut self) -> Option<i32> {
        let press = self.st.press;
        let s = &mut self.st.ui.select;
        if !s.active {
            s.active = true;
            s.cursor = 0;
            s.result = None;
            return None;
        }
        if s.items.is_empty() {
            s.active = false;
            return Some(-2);
        }
        if press & padbit::UP != 0 {
            s.cursor = (s.cursor + s.items.len() - 1) % s.items.len();
        }
        if press & padbit::DOWN != 0 {
            s.cursor = (s.cursor + 1) % s.items.len();
        }
        if press & padbit::CIRCLE != 0 {
            s.active = false;
            return Some(s.cursor as i32);
        }
        if press & padbit::CROSS != 0 && s.cancel_ok {
            s.active = false;
            return Some(-2);
        }
        None
    }

    fn select_op(&mut self, ctx: &mut ExCtx<'_>, first: bool) -> ExResult {
        if first {
            if ctx.nargs >= 1 || ctx.argc >= 1 {
                self.select_init(ctx.arg_i32(0));
                for i in 1..ctx.argc {
                    let p = ctx.arg(i as usize);
                    if p != 0 {
                        let raw = raw_cstr(ctx, p);
                        self.st.ui.select.items.push(raw);
                    }
                }
            }
            // Select(): activate
            let _ = self.select_poll();
            return ExResult::Yield(-1);
        }
        match self.select_poll() {
            Some(v) => {
                ctx.set_ret(v as u32);
                ExResult::Int
            }
            None => ExResult::Yield(-1),
        }
    }

    /// Edit party set `set` of the session's `MENU` block in place.
    fn edit_set(&mut self, set: i32, f: impl FnOnce(&mut sh2_menu::save::PartySet)) {
        let Some(s) = self.session.as_deref_mut() else { return };
        let i = set.clamp(0, 6) as usize;
        if let Some(mut p) = s.save.menu.party_set(i) {
            f(&mut p);
            s.save.menu.set_party_set(i, &p);
        }
    }

    /// `SetFieldData(0x2d, pc, name)`: the name of party record `pc` (0x12 bytes, NUL padded).
    fn set_pc_name(&mut self, pc: i32, name: &[u8]) {
        let Some(s) = self.session.as_deref_mut() else { return };
        if !(0..12).contains(&pc) {
            return;
        }
        let o = sh2_menu::save::PC_REC_BASE + pc as usize * sh2_menu::save::PC_REC_SIZE + 0x0a;
        let n = name.iter().position(|&c| c == 0).unwrap_or(name.len()).min(0x11);
        if let Some(dst) = s.save.btl.data.get_mut(o..o + 0x12) {
            dst.fill(0);
            dst[..n].copy_from_slice(&name[..n]);
        }
        self.st.party_log.push(format!("SetName(pc {pc}, {:?})", String::from_utf8_lossy(&name[..n])));
    }

    // ------------------------------------------------------------------ SetFieldData / GetFieldData (JP 0x004b1b70 / 0x004b24e0)
    fn set_field_data(&mut self, sel: i32, a: i32, b: i32) {
        match sel {
            0 => {
                self.sim.evt_mask = (a & 7) as u8;
                self.sim.field.flags_18c.0 = (self.sim.field.flags_18c.0 & 0xe3) | (((a & 7) as u8) << 2);
            }
            1 => {
                if let Some(ev) = self.sim.field.event_boxes.as_mut() {
                    for bx in ev.boxes.iter_mut().filter(|x| x.id == a) {
                        bx.flags = (bx.flags & 0xf0) | (((b as u8) ^ 1) & 0xf);
                        bx.group = bx.flags & 0xf;
                    }
                }
            }
            2 => {
                if let Some(ev) = self.sim.field.event_boxes.as_mut() {
                    for bx in ev.boxes.iter_mut().filter(|x| x.id == a) {
                        bx.flags = (bx.flags & 0xcf) | (((b as u8) & 3) << 4);
                        bx.kind = (bx.flags & 0x3f) >> 4;
                    }
                }
            }
            3 => {
                if let Some(ev) = self.sim.field.cam_events.as_mut() {
                    for bx in ev.boxes.iter_mut().filter(|x| x.group as i32 == a) {
                        bx.flags = (bx.flags & 0xcf) | (((b == 0) as u8) << 4);
                        bx.kind = (bx.flags & 0x3f) >> 4;
                    }
                }
            }
            4 => {} // CFieldSocket m_flags bit 5 (fader pause)
            5 => {
                let rate = if a < 0 { self.sim.field.encounter_rate } else { a };
                if a >= 0 {
                    self.sim.field.encounter_rate = a;
                }
                self.sim.enc.rate = rate.clamp(0, 255) as u8;
                self.sim.enc.dist = 0.0;
            }
            6 | 7 => self.st.field_data[sel as usize] = a,
            0x11 => {
                if let Some(fl) = self.sim.field.floor.as_mut() {
                    fl.set_obstacle(a as u8, b as u8);
                }
            }
            0x22 => {
                if let Some(fl) = self.sim.field.floor.as_mut() {
                    fl.set_rot_y(a as f32);
                }
            }
            // 0x0a ClearBattleTeam(set) (-1: sets 0..2), 0x0b JoinBattle(pc = a2 low 16 bits, set (-1: 0..2), pin flag = a2 >> 16): US 0x004fbad8
            0x0a => {
                for set in if a == -1 { 0..3 } else { a..a + 1 } {
                    self.edit_set(set, |p| {
                        p.battle_count = 0;
                        p.pinned_mask = 0;
                    });
                }

            }
            0x0b => {
                let pc = (b & 0xffff) as i16 as i32;
                let pin = (b >> 16) & 0xff != 0;
                for set in if a == -1 { 0..3 } else { a..a + 1 } {
                    self.edit_set(set, |p| {
                        join_battle(p, pc as u8, pin);
                    });
                }
                self.st.party_log.push(format!("JoinBattle(pc {pc}, set {a}, pin {pin})"));
            }
            0x12 => self.st.graveyard = a,
            // 0x13 SceneInit(scene): retail `SceneInit` (US 0x003f7bc0) sets BTL0+3 bit 0 for scene > 0, then `SetSceneInit(scene, ..)`
            0x13 => {
                if let Some(s) = self.session.as_deref_mut() {
                    if a > 0 && s.save.btl.data.len() > 3 {
                        s.save.btl.data[3] |= 1;
                    }
                }
                self.st.party_ops.push(PartyOp::SceneInit(a));
                self.st.party_log.push(format!("SceneInit({a})"));
            }
            // 0x14 JoinParty(set a (-1 = sets 0..2), pc b) / 0x15 LeaveParty: US 0x004fbba0 / 0x004fbbe8.  Join also sets the record's "in the
            // party" bit (`BTL0 + pc * 0xc0 + 0x3c` bit 1); leave writes that bit from `b >> 8` and uses `b & 0xff` as the member.
            0x14 | 0x15 => {
                let pc = (b & 0xff) as u8;
                if let Some(s) = self.session.as_deref_mut() {
                    let n = if s.save.build.is_retail() { 7 } else { 5 };
                    let sets: Vec<usize> = if a < 0 { (0..3).collect() } else { vec![(a as usize).min(n - 1)] };
                    if sel == 0x14 {
                        // JoinParty: refused when a set is full (> 7) or already holds the member
                        let ok = sets.iter().all(|&i| s.save.menu.party_set(i).map(|p| p.member_count <= 7 && !p.find_pc(pc)).unwrap_or(false));
                        if ok {
                            for &i in &sets {
                                if let Some(mut p) = s.save.menu.party_set(i) {
                                    p.join(pc);
                                    s.save.menu.set_party_set(i, &p);
                                }
                            }
                            if s.save.build.is_retail() {
                                s.save.menu.set_joined(pc);
                            }
                            self.st.party_log.push(format!("JoinParty(set {a}, pc {pc})"));
                        }
                        set_pc_flag(s, pc, 2, true);
                    } else {
                        let ok = sets.iter().all(|&i| s.save.menu.party_set(i).map(|p| p.find_pc(pc)).unwrap_or(false));
                        if ok {
                            for &i in &sets {
                                if let Some(mut p) = s.save.menu.party_set(i) {
                                    p.leave(pc);
                                    s.save.menu.set_party_set(i, &p);
                                }
                            }
                            self.st.party_log.push(format!("LeaveParty(set {a}, pc {pc})"));
                        }
                        set_pc_flag(s, pc, 2, (b >> 8) & 1 != 0);
                    }
                }

            }
            // 0x16 SetCurrentPartySet(set a, b = lock | battle count << 8): US 0x004fbc38
            0x16 => {
                if let Some(s) = self.session.as_deref_mut() {
                    s.save.menu.data[sh2_menu::save::MenuSave::OFF_SET_LOCK] = 0;
                    s.save.menu.data[sh2_menu::save::MenuSave::OFF_CUR_SET] = a as u8;
                    let count = (b >> 8) & 0xff;
                    if count != 0 {
                        // SetBattleCount(count, set): `+0x10` = count, `+0x11` clamped to it
                        let i = (a.max(0) as usize).min(6);
                        if let Some(mut p) = s.save.menu.party_set(i) {
                            p.battle_max = count as i8;
                            if p.battle_count > p.battle_max {
                                p.battle_count = p.battle_max;
                            }
                            s.save.menu.set_party_set(i, &p);
                        }
                    }
                    s.save.menu.data[sh2_menu::save::MenuSave::OFF_SET_LOCK] = (b & 0xff) as u8;
                }
                self.st.party_log.push(format!("SetCurrentPartySet({a}, {b:#x})"));
            }
            // 0x17: the `GS` chunk flag bit 0 = (a == 0); a == 2 also clears the Navi Map option bits (MENU+0x275 bits 2-3)
            0x17 => {
                self.st.gs_flag0 = a == 0;
                if a == 2 {
                    if let Some(s) = self.session.as_deref_mut() {
                        s.save.menu.data[sh2_menu::save::MenuSave::OFF_OPT1] &= 0xf3;
                    }
                }
            }
            // 8: `SSHSys+0x56` (JP +0x52) = a: a lost battle returns to the field instead of the game over (consumed by the battle)
            8 => {
                if let Some(s) = self.session.as_deref_mut() {
                    s.ssh_sys[2] = a as u8;
                }
            }
            // 0x1f: `MENU+0x10` (retail location / save id); 0x25: `MENU+0x14` best progress (max; set outright on a fresh block); 0x38: `MENU+0x18`
            0x1f => {
                if let Some(s) = self.session.as_deref_mut() {
                    s.save.menu.set_location_id(a as u32);
                }
            }
            0x25 => {
                if let Some(s) = self.session.as_deref_mut() {
                    let o = sh2_menu::save::MenuSave::OFF_BEST_PROGRESS;
                    let cur = i32::from_le_bytes(s.save.menu.data[o..o + 4].try_into().unwrap());
                    if (s.save.menu.data[0] == 0 && s.save.menu.data[1] == 0) || cur < a {
                        s.save.menu.data[o..o + 4].copy_from_slice(&a.to_le_bytes());
                    }
                }
                self.st.retail.field_data_ex.insert(sel, (a, b));
            }
            0x38 => {
                if let Some(s) = self.session.as_deref_mut() {
                    let o = sh2_menu::save::MenuSave::OFF_LANGUAGE;
                    s.save.menu.data[o..o + 4].copy_from_slice(&a.to_le_bytes());
                }
            }
            // 0x20 PCAddInit(pc)
            0x20 => {
                self.st.party_ops.push(PartyOp::PcAdd(a));
                self.st.party_log.push(format!("PCAddInit({a})"));
            }
            // 0x31: `MENU + 0x380 + a * 0x10` = b; 0x34: clear bytes +0x63..+0x67 of PC record a
            0x31 => {
                if let Some(s) = self.session.as_deref_mut() {
                    if let Some(x) = s.save.menu.data.get_mut(0x380 + (a.max(0) as usize) * 0x10) {
                        *x = b as u8;
                    }
                }
                self.st.retail.field_data_ex.insert(sel, (a, b));
            }
            0x34 => {
                if let Some(s) = self.session.as_deref_mut() {
                    let o = sh2_menu::save::PC_REC_BASE + (a.clamp(0, 11) as usize) * sh2_menu::save::PC_REC_SIZE;
                    for k in 0x63..0x68 {
                        if let Some(x) = s.save.btl.data.get_mut(o + k) {
                            *x = 0;
                        }
                    }
                }
            }
            0x1e | 0x18 | 0x19 | 0x1a | 0xe | 0xf => {
                self.st.retail.field_data_ex.insert(sel, (a, b));
            }
            // 0x2e: GS chunk word +0x46 (US 0x003f4fe0(a): set when a >= -1, a == -3 restores the copy at +0x66)
            0x2e => {
                if let Some(s) = self.session.as_deref_mut() {
                    gs_word46(s, a);
                }
                self.st.retail.field_data_ex.insert(sel, (a, b));
            }
            // retail-only selectors: recorded (their effects are presentation switches of the retail engine)
            0x24..=0x38 => {
                self.st.retail.field_data_ex.insert(sel, (a, b));
            }
            _ => {
                *self.st.unimplemented.entry((0xc3, sel as u8)).or_insert(0) += 1;
            }
        }
    }

    fn get_field_data(&mut self, ctx: &mut ExCtx<'_>, sel: i32, a: i32, b: i32) -> i32 {
        match sel {
            0 => ((self.sim.field.flags_18c.0 & 0x1f) >> 2) as i32,
            1 => self.sim.field.event_boxes.as_ref().and_then(|e| e.boxes.iter().find(|x| x.id == a)).map(|x| ((x.flags & 0xf) ^ 1) as i32).unwrap_or(-1),
            2 => self.sim.field.event_boxes.as_ref().and_then(|e| e.boxes.iter().find(|x| x.id == a)).map(|x| ((x.flags & 0x3f) >> 4) as i32).unwrap_or(-1),
            // 9: result of the last battle (`SSHSys+0x55`, JP +0x51, written by `SSHSys::cbBattleA`): 1 won, 0 lost (story goes on), -1 escaped
            9 => self.session.as_deref().map(|s| s.ssh_sys[1] as i8 as i32).unwrap_or(1),
            // 0xd: how the map was entered (`SSHSys+0x54`, JP +0x50): 1 = `MapJump`, 2 = back from a battle
            0xd => self.session.as_deref().map(|s| s.ssh_sys[0] as i32).unwrap_or(0),
            // 0x16: current party set (`MENU+0x80`); 0x1f: `MENU+0x10`; 0x25: `MENU+0x14`; 0x38: `MENU+0x18` (US 0x004fc170)
            0x16 => self.session.as_deref().map(|s| s.save.menu.data[sh2_menu::save::MenuSave::OFF_CUR_SET] as i8 as i32).unwrap_or(0),
            0x25 | 0x38 => {
                let o = if sel == 0x25 { sh2_menu::save::MenuSave::OFF_BEST_PROGRESS } else { sh2_menu::save::MenuSave::OFF_LANGUAGE };
                self.session.as_deref().map(|s| i32::from_le_bytes(s.save.menu.data[o..o + 4].try_into().unwrap())).unwrap_or(0)
            }
            // 0x29: position of PC `(a >> 8) & 0xff` in party set `a >> 16` (among the battle members when bit 0 of `a` is set), -1 when absent
            0x29 => {
                let Some(s) = self.session.as_deref() else { return -1 };
                let (set, pc, battle) = ((a >> 16) as usize & 0xff, ((a >> 8) & 0xff) as u8, a & 1 != 0);
                match s.save.menu.party_set(set.min(6)) {
                    Some(p) => {
                        let n = if battle { p.battle_max } else { p.member_count }.clamp(0, 8) as usize;
                        p.members[..n].iter().position(|&m| m == pc).map(|i| i as i32).unwrap_or(-1)
                    }
                    None => -1,
                }
            }
            // 0x2a: state of image object `b` (`CField + 0x9bc + b * 4`, the `LoadImage` / `DspImage` slots): 1 once it is loaded and shown
            0x2a => {
                let im = &self.st.ui.images[(b.max(0) as usize).min(7)];
                (!im.name.is_empty() && im.shown) as i32
            }
            // 0x2e: the GS chunk word +0x46 (US 0x003f4fe0(-2) = read)
            0x2e => self.session.as_deref_mut().map(|s| gs_word46(s, -2)).unwrap_or(-1),
            // 0x36: always 2 (retail); 0x37: availability bits of world-map point `a` (`WM` chunk byte & 3)
            0x36 => 2,
            0x37 => self
                .session
                .as_deref()
                .and_then(|s| s.save.field.find(sh2_menu::save::FieldSave::TAG_WM).and_then(|c| c.payload.get(0xc + a.max(0) as usize).copied()))
                .map(|b| (b & 3) as i32)
                .unwrap_or(0),
            0xc => self.session.as_deref_mut().map(|s| s.save.field.npc_library(a.max(0) as usize, b.clamp(0, 15) as u8) as i32).unwrap_or(0),
            0x10 => self.st.map_entry,
            0x1b => self.inventory_change(0x20, a as u32, 0),
            0x1c => {
                // name string of RegDat table `a`, record `b` (returned as a host pointer)
                let t = self.tables();
                let kind = t.rd_num.get(a.max(0) as usize).copied().unwrap_or(0);
                let s = if kind == 0 && a != 0 { None } else { t.names.as_ref().and_then(|f| f(kind, b.max(0) as u32)) };
                match s {
                    Some(bytes) => {
                        let end = bytes.iter().position(|&c| c == 0).unwrap_or(bytes.len());
                        let p = sh2_script::memory::SEG_HOST + ctx.mem.host.len() as u32;
                        ctx.mem.host.extend_from_slice(&bytes[..end]);
                        ctx.mem.host.push(0);
                        p as i32
                    }
                    None => 0,
                }
            }
            0x1d => (self.st.ticks * 1000 / 60) as i32,
            0x1f => self.session.as_deref().map(|s| s.save.menu.location_id() as i32).unwrap_or(0),
            // 0x21: battle member `b` of party set `a` (JP 0x004b24e0 / US: compared with the battle count `+0x11`), -1 past the end
            0x21 => {
                let Some(s) = self.session.as_deref() else { return -1 };
                match s.save.menu.party_set((a as i8).clamp(0, 6) as usize) {
                    Some(set) if (b as i64) < set.battle_count as i64 && (0..8).contains(&b) => set.members[b as usize] as i8 as i32,
                    _ => -1,
                }
            }
            // KeyWaitStat: 1 while the current window is still typing (it clears the pending-key flag, so no key press is needed)
            0x23 => {
                let w = &mut self.st.ui.windows[self.st.ui.cur_win.min(7)];
                w.key_pending = false;
                (w.is_open() && w.msg.is_some() && !w.typed()) as i32
            }
            _ => -1,
        }
    }

    // ------------------------------------------------------------------ treasure (JP 0x004b67d0)
    fn treasure(&mut self, ctx: &mut ExCtx<'_>, mode: i32, idx: i32, extra: i32) -> i32 {
        let t = self.tables();
        let rec = if mode < 5 { t.tres.get(idx.max(0) as usize).copied() } else { None };
        match mode {
            0 => self.treasure_flag(idx.max(0) as usize, -1),
            1 => match rec {
                Some(r) if r[1] & 0x3f != 0 && r[0] != 0xff => (((r[1] & 0x3f) as i32) << 8) | r[0] as i32,
                _ => -1,
            },
            2 => {
                let Some(r) = rec else { return 0 };
                let kind = t.rd_num.get((r[1] & 0x3f) as usize).copied().unwrap_or(0);
                match t.names.as_ref().and_then(|f| f(kind, r[0] as u32)) {
                    Some(bytes) => {
                        let end = bytes.iter().position(|&c| c == 0).unwrap_or(bytes.len());
                        let p = sh2_script::memory::SEG_HOST + ctx.mem.host.len() as u32;
                        ctx.mem.host.extend_from_slice(&bytes[..end]);
                        ctx.mem.host.push(0);
                        p as i32
                    }
                    None => 0,
                }
            }
            3 => {
                if self.treasure_flag(idx.max(0) as usize, -1) == 1 {
                    rec.map(|r| u16::from_le_bytes([r[2], r[3]]) as i32).unwrap_or(0)
                } else {
                    0
                }
            }
            4 => {
                if self.treasure_flag(idx.max(0) as usize, 1) == 1 {
                    if let Some(r) = rec {
                        let kind = (r[1] & 0x3f) as i32;
                        let n = u16::from_le_bytes([r[2], r[3]]) as i32;
                        return self.inventory_change(kind, r[0] as u32, n);
                    }
                }
                0
            }
            5 => self.inventory_change(idx >> 8, (idx & 0xff) as u32, extra),
            _ => -1,
        }
    }

    // ------------------------------------------------------------------ 0x7d ParamChange(pc, kind, mode, value)
    fn param_change(&mut self, ctx: &mut ExCtx<'_>) -> ExResult {
        let (pc, kind, mode, val) = (ctx.arg_i32(0), ctx.arg_i32(1), ctx.arg_i32(2), ctx.arg_i32(3));
        let t = self.tables();
        let r = if kind == 5 {
            let code = if mode == 0 { 0x40 } else { 0x3f };
            self.inventory_change(code, 0, if mode < 0 { 0 } else { val })
        } else if kind == 6 {
            if mode < 0 {
                self.inventory_change(0x3a, 0, val)
            } else {
                self.inventory_change(if mode == 0 { 0x3b } else { 0x3a }, 0, val)
            }
        } else if let Some(s) = self.session.as_deref_mut() {
            let code = t.param_chg.get(kind.max(0) as usize).copied().unwrap_or(0) as u32;
            match sh2_menu::btlsave::Param::from_code(code) {
                Some(p) => {
                    let cur = s.save.btl.pc_param(pc.max(0) as usize, p).unwrap_or(0);
                    match mode {
                        0 => {
                            let _ = s.save.btl.set_pc_param(pc.max(0) as usize, p, val, &NoLevels, 9999, 999, 255);
                        }
                        1 => {
                            let _ = s.save.btl.set_pc_param(pc.max(0) as usize, p, cur + val, &NoLevels, 9999, 999, 255);
                        }
                        _ => {}
                    }
                    cur
                }
                None => 0,
            }
        } else {
            0
        };
        ctx.set_ret(r as u32);
        ExResult::Int
    }

    // ------------------------------------------------------------------ 0x7e SavePoint(slot, pos*, flag)
    fn save_point(&mut self, ctx: &mut ExCtx<'_>) -> ExResult {
        let slot = ctx.arg_i32(0);
        let vp = ctx.arg(1);
        let mut a2 = ctx.arg_i32(2);
        let r: i32;
        if ctx.arg(1) == 0 {
            if a2 == -1 {
                // ClrSavePoint(slot)
                let (lo, hi) = if slot < 0 { (0, 7) } else { (slot as usize, slot as usize) };
                for i in lo..=hi.min(7) {
                    self.st.save_points[i] = None;
                }
                r = 0;
            } else if a2 == 0x1000 {
                // retail: show the save points
                for p in self.st.save_points.iter_mut().flatten() {
                    p.shown = true;
                }
                r = 0;
            } else {
                // position given by an entry point
                match self.entry_point(a2) {
                    Some((pos, _)) => r = self.set_save_point(slot, pos),
                    None => r = -1,
                }
            }
        } else {
            let v = ctx.arg_vec(1, 3);
            let _ = &mut a2;
            r = self.set_save_point(slot, [v[0], v[1], v[2]]);
        }
        let _ = vp;
        ctx.set_ret(r as u32);
        ExResult::Int
    }

    fn set_save_point(&mut self, slot: i32, pos: [f32; 3]) -> i32 {
        let mut i = slot;
        if i < 0 {
            match self.st.save_points.iter().position(|p| p.is_none()) {
                Some(f) => i = f as i32,
                None => return -1,
            }
        }
        if i as usize >= 8 {
            return -1;
        }
        self.st.save_points[i as usize] = Some(SavePointSlot { active: true, pos, shown: true });
        i
    }

    // ------------------------------------------------------------------ 0x65 WarpPoint
    fn warp_op(&mut self, ctx: &mut ExCtx<'_>, first: bool) -> ExResult {
        if first {
            let slot = ctx.arg_i32(0);
            let vp = ctx.arg(1);
            let kind = ctx.arg_i32(2);
            let a3 = ctx.arg_i32(3);
            let r: i32;
            if vp == 0 {
                match a3 {
                    -1 => {
                        // ClrWarpPoint
                        let (lo, hi) = if slot < 0 { (0, 7) } else { (slot as usize, slot as usize) };
                        for i in lo..=hi.min(7) {
                            self.st.warp_points[i] = None;
                        }
                        r = 0;
                    }
                    -2 => {
                        // DoWarp(slot, direction=kind): out (0) / in (1), the effect runs, the script waits for it
                        let incoming = kind != 0;
                        let total = if incoming { 84 } else { 72 };
                        self.st.warp_fx = Some(WarpFx { ticks_left: total, incoming, color: if incoming { [255, 255, 255] } else { [255, 240, 255] }, total });
                        self.st.warp_state = if incoming { 2 } else { 1 };
                        return ExResult::Yield(slot - 0x100);
                    }
                    -3 => {
                        // WarpFade(slot, show)
                        if let Some(Some(w)) = self.st.warp_points.get_mut(slot.max(0) as usize) {
                            w.shown = kind == 0;
                        }
                        r = 0;
                    }
                    _ => {
                        r = match self.entry_point(a3) {
                            Some((pos, _)) => self.set_warp_point(slot, pos, kind),
                            None => -1,
                        };
                    }
                }
            } else {
                let v = ctx.arg_vec(1, 3);
                r = self.set_warp_point(slot, [v[0], v[1], v[2]], kind);
            }
            ctx.set_ret(r as u32);
            return ExResult::Int;
        }
        // resumed: IsWarp(slot)
        if self.st.warp_fx.is_some() {
            return ExResult::Yield(ctx.nargs);
        }
        ctx.set_ret(0);
        ExResult::Int
    }

    fn set_warp_point(&mut self, slot: i32, pos: [f32; 3], kind: i32) -> i32 {
        let mut i = slot;
        if i < 0 {
            match self.st.warp_points.iter().position(|p| p.is_none()) {
                Some(f) => i = f as i32,
                None => return -1,
            }
        }
        if i as usize >= 8 {
            return -1;
        }
        self.st.warp_points[i as usize] = Some(WarpPointSlot { active: true, pos, kind: kind & 0xff, shown: true });
        i
    }

    // ------------------------------------------------------------------ 0x62 MCES
    fn mces(&mut self, ctx: &mut ExCtx<'_>, first: bool) -> ExResult {
        let m = &mut self.st.mces;
        if first {
            let mode = ctx.arg_i32(0);
            match mode {
                // SetMCESMode(next map, flag, flag)
                0 => {
                    m.next_map = ascii(&raw_cstr(ctx, ctx.arg(1)));
                    m.mode = ctx.arg_i32(2);
                    ctx.set_ret(0);
                    return ExResult::Int;
                }
                // PlayMCES(name, flags, event): the LSD stream; event < 0 = block the script until it ends
                1 => {
                    if m.state == 0 {
                        m.name = ascii(&raw_cstr(ctx, ctx.arg(1)));
                        m.flags = ctx.arg_i32(2);
                        m.event = ctx.arg_i32(3);
                        m.ticks = 0;
                        m.state = 1;
                        m.played.push(m.name.clone());
                        log::debug!("field: MCES {} started (the cut scene bridge plays it; headless: a placeholder wait)", m.name);
                    }
                    if ctx.arg_i32(3) < 0 {
                        return ExResult::Yield(-0x100);
                    }
                    ctx.set_ret(0);
                    return ExResult::Int;
                }
                // StartMCES: release a movie that waits at its event gate
                2 => {
                    if m.state == 3 {
                        m.state = 4;
                    }
                    ctx.set_ret(0);
                    return ExResult::Int;
                }
                // wait for the movie to be over
                3 => {
                    if m.state != 0 {
                        return ExResult::Yield(-0x100);
                    }
                    ctx.set_ret(0);
                    return ExResult::Int;
                }
                _ => {
                    ctx.set_ret(0);
                    return ExResult::Int;
                }
            }
        }
        if self.st.mces.state != 0 {
            ExResult::Yield(ctx.nargs)
        } else {
            ctx.set_ret(0);
            ExResult::Int
        }
    }

    // ------------------------------------------------------------------ 0x7f SpecialMenu(kind, arg)
    fn special_menu(&mut self, ctx: &mut ExCtx<'_>, first: bool) -> ExResult {
        if !first {
            // resumed: wait while the menu / shop is up
            return if self.st.menu_wait { ExResult::Yield(-1) } else { ExResult::Void };
        }
        let (k, a1) = (ctx.arg_i32(0), ctx.arg_i32(1));
        // US 0x004fa578: a negative kind returns the message variable buffer `CField+0x2170` (the name typed in the name entry,
        // `SpecialMenu(0x400)`), which the scripts `sprintf` into the dialogue
        if k < 0 {
            let bytes = self.st.name_buffer.clone();
            let p = sh2_script::memory::SEG_HOST + ctx.mem.host.len() as u32;
            ctx.mem.host.extend_from_slice(&bytes);
            ctx.mem.host.push(0);
            ctx.set_ret(p);
            return ExResult::Int;
        }
        match (k >> 8) & 0xf {
            0 => {
                if k == 2 {
                    self.st.help_flags = a1;
                } else if k == 3 {
                    self.st.menu_flags = (a1 & 0xff, (a1 >> 8) & 0xff);
                } else if k < 4 {
                    self.st.cmd_menu_mask = k as u16;
                } else {
                    let req = match k {
                        4 => MenuReq::Main { arg: a1 as u32 },
                        5 => MenuReq::Tutorial { arg: a1 as u32 },
                        6 => MenuReq::Sub { arg: a1 as u32 },
                        0x10 => MenuReq::Save,
                        _ => MenuReq::Main { arg: a1 as u32 },
                    };
                    self.st.menu_req = Some(req);
                    self.st.menu_wait = true;
                    return ExResult::Yield(-1);
                }
                ExResult::Void
            }
            1 => {
                self.st.menu_req = Some(MenuReq::Shop { id: a1 });
                self.st.menu_wait = true;
                ExResult::Yield(-1)
            }
            2 => {
                self.st.menu_req = Some(MenuReq::Sub { arg: if a1 == 1 { 5 } else { 0 } });
                self.st.menu_wait = true;
                ExResult::Yield(-1)
            }
            3 => {
                self.st.menu_req = Some(MenuReq::Tailor);
                self.st.menu_wait = true;
                ExResult::Yield(-1)
            }
            // (round 5 MN) retail name entry / Wolf Bout stamp: field screens, the script waits like for a shop
            4 => {
                self.st.menu_req = Some(MenuReq::NameEntry);
                self.st.menu_wait = true;
                ExResult::Yield(-1)
            }
            6 => {
                self.st.menu_req = Some(MenuReq::WolfStamp { bout: a1 });
                self.st.menu_wait = true;
                ExResult::Yield(-1)
            }
            5 => {
                self.st.game_over = true;
                self.st.menu_req = Some(MenuReq::GameOver);
                ExResult::Yield(-1)
            }
            // US 0x004faab0: `CField+0x178` delete reason 2 -- the field is deleted and the socket hands over to scene 0x40 = the title
            // (the end of the game: ED_00_U after the clear save, YO_00..02_U)
            7 => {
                self.st.menu_req = Some(MenuReq::EndToTitle);
                ExResult::Yield(-1)
            }
            _ => ExResult::Void,
        }
    }

    // ------------------------------------------------------------------ vector ops (JP 0x004b1590 VectorOperation)
    fn vector_op(&mut self, ctx: &mut ExCtx<'_>, op: u8) -> ExResult {
        let rd = |ctx: &ExCtx<'_>, i: usize| -> [f32; 3] {
            let v = ctx.arg_vec(i, 3);
            [v[0], v[1], v[2]]
        };
        let dst = ctx.arg(0);
        match op {
            0x80 => {
                put_f32s(ctx, dst, &[0.0; 3]);
                ExResult::Void
            }
            0x81 => {
                let s = rd(ctx, 1);
                put_f32s(ctx, dst, &s);
                ExResult::Void
            }
            0x82 => {
                let v = rd(ctx, 0);
                let l = (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]).sqrt();
                if l == 0.0 {
                    put_f32s(ctx, dst, &[0.0; 3]);
                } else {
                    put_f32s(ctx, dst, &[v[0] / l, v[1] / l, v[2] / l]);
                }
                ctx.set_ret_f32(l);
                ExResult::Float
            }
            0x83 => {
                let v = rd(ctx, 0);
                ctx.set_ret_f32((v[0] * v[0] + v[1] * v[1] + v[2] * v[2]).sqrt());
                ExResult::Float
            }
            0x84 | 0x85 | 0x86 => {
                let (a, b) = (rd(ctx, 1), rd(ctx, 2));
                let r = match op {
                    0x84 => [a[0] + b[0], a[1] + b[1], a[2] + b[2]],
                    0x85 => [a[0] - b[0], a[1] - b[1], a[2] - b[2]],
                    _ => [a[0] * b[0], a[1] * b[1], a[2] * b[2]],
                };
                put_f32s(ctx, dst, &r);
                ExResult::Void
            }
            0x87 | 0x88 => {
                let a = rd(ctx, 1);
                let f = ctx.arg_f32(2);
                let r = if op == 0x87 {
                    [a[0] * f, a[1] * f, a[2] * f]
                } else if f == 0.0 {
                    [0.0; 3]
                } else {
                    [a[0] / f, a[1] / f, a[2] / f]
                };
                put_f32s(ctx, dst, &r);
                ExResult::Void
            }
            0x89 => {
                let (a, b) = (rd(ctx, 0), rd(ctx, 1));
                ctx.set_ret_f32(a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
                ExResult::Float
            }
            0x8a => {
                let (a, b) = (rd(ctx, 1), rd(ctx, 2));
                let r = [a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]];
                put_f32s(ctx, dst, &r);
                ExResult::Void
            }
            0x8b => {
                // rotate vector 1 about Y by angle (radians): x' = x cos + z sin, z' = -x sin + z cos
                let a = rd(ctx, 1);
                let (s, c) = ctx.arg_f32(2).sin_cos();
                put_f32s(ctx, dst, &[a[0] * c + a[2] * s, a[1], -a[0] * s + a[2] * c]);
                ExResult::Void
            }
            0x8c => {
                let r = [ctx.arg_f32(1), ctx.arg_f32(2), ctx.arg_f32(3)];
                put_f32s(ctx, dst, &r);
                ExResult::Void
            }
            _ => ExResult::Void,
        }
    }
}

/// `EncodeMotionName(const char*)` (JP 0x004bff50): a stable id for a motion name (the original packs up to 6 base-37 characters).
/// The standard field motions (US FIELD.BIN 0x00610db4, 54 names; numeric motion ids are indices into it, 1 = `fidl`).
pub const STANDARD_MOTIONS: [&str; 54] = [
    "fidl", "walk", "run", "sq_a", "sq_b", "sq_c", "inve", "agre", "rejc", "ta_a", "ta_b", "ta_c", "he_a", "he_b", "he_c", "he_d", "la_a", "la_b", "la_c", "an_a",
    "an_b", "an_c", "lk_a", "lk_b", "lk_c", "fac1", "fac2", "fac3", "fac4", "fac5", "fac6", "fac7", "fac8", "fac9", "faca", "facb", "facc", "bt_a", "bt_b", "bt_c",
    "ltrn", "rtrn", "wake", "gi_a", "gi_b", "gi_c", "md_a", "md_b", "sd_a", "sd_b", "sd_c", "sd_d", "fdid", "facl",
];

/// `GetCharacterInfo(slot, 0xd)`: 1-based index of the motion in [`STANDARD_MOTIONS`], 0 when it is not one of them.
pub fn standard_motion_index(id: i32, name: &str) -> i32 {
    if !name.is_empty() {
        let n = name.to_ascii_lowercase();
        return STANDARD_MOTIONS.iter().position(|m| *m == n).map(|i| i as i32 + 1).unwrap_or(0);
    }
    if (1..=54).contains(&id) {
        id
    } else {
        0
    }
}

pub fn encode_motion_name(s: &str) -> i32 {
    let mut v: u32 = 0;
    for c in s.bytes().take(6) {
        let d = match c {
            b'0'..=b'9' => (c - b'0') as u32 + 1,
            b'a'..=b'z' => (c - b'a') as u32 + 11,
            b'A'..=b'Z' => (c - b'A') as u32 + 11,
            _ => 0,
        };
        v = v.wrapping_mul(37).wrapping_add(d);
    }
    (v & 0x7fff_ffff) as i32 | 0x100_0000
}

impl ScriptHost for FieldHost<'_> {
    fn timer(&self) -> u32 {
        (self.st.ticks * 1000 / 60) as u32
    }

    fn random(&mut self, n: i32) -> i32 {
        let r = crate::sim::FieldSim::lcg_rand(&mut self.sim.rng) as i32;
        if n <= 0 {
            r & 0x7fff
        } else {
            r % n
        }
    }

    fn dprint(&mut self, s: &str) {
        self.st.log.push(format!("dprintf {s}"));
    }

    /// JP: 0x004ac950 CField::CallFunc(op, argc, par_stack) for `ex == 0xc2`; `ex == 0xc0` is `LSDScrEx` (cutscene helper, not used by
    /// field scripts).
    fn call_ex(&mut self, ctx: &mut ExCtx<'_>, ex: u8, sub: u8) -> ExResult {
        self.st.calls += 1;
        if self.st.log.len() >= 4000 {
            self.st.log.drain(..2000);
        }
        {
            let args: Vec<i32> = (0..ctx.argc.min(8)).map(|i| ctx.arg_i32(i)).collect();
            self.st.log.push(format!("ex={ex:#04x} sub={sub:#04x} args={args:x?}"));
        }
        if ex != 0xc2 {
            *self.st.unimplemented.entry((ex, sub)).or_insert(0) += 1;
            if self.st.warned.insert((ex, sub)) {
                log::debug!("field script: LSDScrEx call {ex:#x}.{sub:#x} ignored");
            }
            return ExResult::Void;
        }
        // sound ops 0x50..=0x5f reach the audio layer directly (the request queue below is kept for tests / tools)
        if ctx.nargs >= 0 && (0x50..=0x5f).contains(&sub) {
            let argc = ctx.argc;
            sh2_audio::hooks::field_script_op(sub, argc, |i| ctx.arg_i32(i), |i| ctx.arg_str(i));
        }
        // keep the control actor's mirror up to date for every command
        self.st.actors.sync_in(self.sim);
        let r = self.op(ctx, sub);
        self.st.actors.sync_out(self.sim);
        // value-returning ops: the log line (for tests / the story tracer) shows what the script got back
        if r == ExResult::Int {
            if let (Some(v), Some(last)) = (ctx.mem.r32(ctx.args).ok(), self.st.log.last_mut()) {
                last.push_str(&format!(" => {:#x}", v as i32));
            }
        }
        r
    }
}

#[allow(dead_code)]
fn _unused() {
    let _ = (get_rot_angle(0), rot_to_yaw(0.0));
}

// ----------------------------------------------------------------------------------------------------------------
// per-tick state (CField::Polling parts that belong to the script engine)
// ----------------------------------------------------------------------------------------------------------------

/// `SetCameraC` type 2 (`UpdateScrCamera` case 5, JP 0x004aa750): the look-at point of a camera at `pos` turned by `pitch` / `yaw` degrees,
/// `len` units away: `pos + RotY(yaw) * RotX(pitch) * (0, 0, len)` -- yaw 0 / pitch 0 looks along **+z** (the models' forward is -z, the camera's is +z).
pub fn angles_target(pos: [f32; 3], pitch_deg: f32, yaw_deg: f32, len: f32) -> [f32; 3] {
    let v = crate::compat::rot_y(crate::compat::get_rad(yaw_deg), crate::compat::rot_x(crate::compat::get_rad(pitch_deg), [0.0, 0.0, len]));
    [pos[0] + v[0], pos[1] + v[1], pos[2] + v[2]]
}

/// View angle for a script camera: `fov_param < 4` = automatic framing (0.625 default), otherwise a field of view in degrees
/// (`tanf(GetRad(fov)) * 1.3333334`, JP `UpdateScrCamera`).
pub fn view_angle_of(param: f32) -> f32 {
    if param < 4.0 {
        0.625
    } else {
        crate::compat::get_rad(param).tan().abs().max(0.05) * 1.333_333_4
    }
}

/// One 60 Hz tick of everything the script engine owns: actor movement, windows, the timer, the warp effect, the movie placeholder and the
/// script camera.  Events that fell due are queued in `st.event_queue` for the VM.
pub fn tick_state(st: &mut ScriptState, sim: &mut FieldSim) {
    st.ticks += 1;
    // actors
    st.actors.tick(sim);
    for e in std::mem::take(&mut st.actors.events) {
        let ActorEvent::Fire { event, arg, slot } = e;
        if event != 0 {
            st.events_queued += 1;
            st.event_queue.push((event, vec![arg as u32, slot as u32]));
        }
    }
    // effects
    for e in st.effect_list.iter_mut().filter(|e| e.state != 0 && e.runner.is_none()) {
        e.ticks += 1;
        if e.ticks == EFFECT_LOAD_TICKS {
            e.state = 3; // US EffectControl(h, 0) = node+0x14 & 7: scripts wait for 3 once the .EFD is loaded and playing (HE_24_N `while (EffectControl(h, 0) != 3)`)
        } else if e.ticks >= EFFECT_LOAD_TICKS + EFFECT_RUN_TICKS {
            e.state = 0;
        }
    }
    // vibration sequences (`CVibeMan::Polling`, 1/60 s)
    if !st.vibes.is_empty() {
        let ScriptState { vibes, vibe_man, .. } = st;
        vibes.retain(|_, v| !v.poll(vibe_man, 17));
        st.vib_out = st.vibe_man.mix(st.vibes.values());
    } else {
        st.vib_out = (0.0, false);
    }
    // windows
    st.ui.tick();
    // field timer
    if st.ui.timer.tick() && st.ui.timer.alarm_event != 0 {
        let ev = st.ui.timer.alarm_event;
        st.ui.timer.alarm_event = 0;
        st.events_queued += 1;
        st.event_queue.push((ev, vec![0]));
    }
    // DoWarp effect
    if let Some(fx) = st.warp_fx.as_mut() {
        if fx.ticks_left > 0 {
            fx.ticks_left -= 1;
        }
        if fx.ticks_left == 0 {
            st.warp_fx = None;
            st.warp_state = 0;
        }
    }
    // MCES placeholder: the movie "plays" for 90 ticks, then its end event fires
    let m = &mut st.mces;
    match m.state {
        1 => {
            m.ticks += 1;
            if m.ticks >= 90 {
                if m.event > 0 {
                    // SetFieldEvent(3, event): the movie reached its script gate; the script resumes it with StartMCES
                    st.event_queue.push((m.event as u32, vec![0]));
                    st.events_queued += 1;
                    m.state = 3;
                    m.ticks = 0;
                } else {
                    m.state = 0;
                }
            }
        }
        3 => {
            // waiting at the gate: auto-release after a while so a script that never calls StartMCES cannot stall
            m.ticks += 1;
            if m.ticks > 600 {
                m.state = 4;
            }
        }
        4 => {
            m.ticks += 1;
            if m.ticks > 30 {
                m.state = 0;
                m.ticks = 0;
            }
        }
        _ => {}
    }
    // `SetMCESMode(next map, ..)`: when the stream is over the engine leaves for the stored map instead of letting the script run on.  Measured
    // live on the US disc (notes/integration/pine_us_refinement.md section 7): the first `AP_00_U` visit plays `N003.LSD` ("One week later.
    // Late night. Vatican.") and then lands in `AP_02_U` - the guard / `AP_02_A` branch behind the `MCES` call is never reached.
    if st.mces.state != 0 {
        st.mces.seen_active = true;
    } else if st.mces.seen_active {
        st.mces.seen_active = false;
        let next = std::mem::take(&mut st.mces.next_map);
        if !next.is_empty() && st.pending_jump.is_none() {
            log::info!("field: MCES over -> map jump {next}");
            st.pending_jump = Some((next, 0));
        }
    }
    // script camera
    st.sync_script_camera(sim);
}

impl ScriptState {
    fn sync_script_camera(&mut self, sim: &mut FieldSim) {
        let Some(c) = self.camera else {
            sim.scr_cam = None;
            return;
        };
        let aim_y = |aim: i32| match aim {
            2 => -8.0,
            1 => -11.0,
            _ => -15.0,
        };
        let actor_pos = |t: &ActorTable, s: i32| t.get(s).map(|a| a.pos);
        let (target, va) = match c.mode {
            ScrCamMode::Look { slot, aim } => {
                let p = actor_pos(&self.actors, slot).unwrap_or(c.target);
                ([p[0], p[1] + aim_y(aim), p[2]], view_angle_of(c.fov_param))
            }
            ScrCamMode::TwoShot { a, b } => {
                let (pa, pb) = (actor_pos(&self.actors, a), actor_pos(&self.actors, b));
                match (pa, pb) {
                    (Some(pa), Some(pb)) => ([(pa[0] + pb[0]) / 2.0, (pa[1] + pb[1]) / 2.0 - 12.0, (pa[2] + pb[2]) / 2.0], view_angle_of(c.fov_param)),
                    (Some(p), None) | (None, Some(p)) => ([p[0], p[1] - 12.0, p[2]], view_angle_of(c.fov_param)),
                    _ => (c.target, view_angle_of(c.fov_param)),
                }
            }
            ScrCamMode::Fixed => (c.target, view_angle_of(c.fov_param)),
        };
        sim.scr_cam = Some(crate::sim::ScrCamGoal { pos: c.pos, target, view_angle: va });
    }
}

#[cfg(test)]
mod tests {
    fn lp(id: i32, x: f32, event: u32) -> LookPoint {
        LookPoint { id, pos: [x, 0.0, 0.0], radius: 10.0, event, icon: 1, view: 0 }
    }

    /// JP 0x004b6a80 / 0x004b6c60 / 0x004b6d40: set reuses the slot of the same id, check picks the first record whose radius contains the avatar,
    /// the attached record is dropped when the avatar leaves it, clear(-1) empties the table.
    #[test]
    fn look_points_attach_detach_and_fire_the_circle_event() {
        let mut t = LookPoints::default();
        assert_eq!(t.set(lp(1, 0.0, 5)), 1);
        assert_eq!(t.set(lp(2, 100.0, 6)), 1);
        assert_eq!(t.set(lp(1, 0.0, 7)), 0, "same id: update in place");
        assert_eq!(t.slots.iter().flatten().count(), 2);
        assert_eq!(t.check([50.0, 0.0, 0.0]), (None, None));
        assert_eq!(t.circle_event(), None);
        assert_eq!(t.check([3.0, 0.0, 0.0]), (Some(0), None));
        assert_eq!(t.circle_event(), Some((7, 1)));
        assert_eq!(t.check([4.0, 0.0, 0.0]), (None, None), "still attached");
        assert_eq!(t.check([60.0, 0.0, 0.0]), (None, Some(0)), "left the radius");
        assert_eq!(t.circle_event(), None);
        assert_eq!(t.check([100.0, 0.0, 0.0]), (Some(1), None));
        assert!(t.clear(2), "the attached record was removed");
        assert!(!t.clear(-1));
        assert!(t.slots.iter().all(|s| s.is_none()));
        // a full table refuses a new id
        for i in 0..16 {
            assert_eq!(t.set(lp(i + 10, 0.0, 1)), 1);
        }
        assert_eq!(t.set(lp(99, 0.0, 1)), -1);
    }

    use super::*;
    use crate::pkb_compat::PkbSet;
    use sh2_script::memory::{Memory, SEG_STACK};

    fn rt() -> Option<(crate::plugin::FieldRuntime, GameSession)> {
        let set = PkbSet::from_env()?;
        let s = GameSession::default();
        let r = crate::plugin::build_runtime(&set, None, "AP_02_U", 0, &s)?;
        Some((r, s))
    }

    /// run op `sub` with integer arguments `args`; returns (result, first argument slot after the call)
    fn call(r: &mut crate::plugin::FieldRuntime, s: &mut GameSession, sub: u8, args: &[u32], nargs: i32) -> (ExResult, u32) {
        let mut mem = Memory::default();
        mem.stack = vec![0; 0x1000];
        mem.data = vec![0; 0x100];
        for (i, a) in args.iter().enumerate() {
            mem.w32(SEG_STACK + 0x100 + 4 * i as u32, *a).unwrap();
        }
        let mut ctx = ExCtx { mem: &mut mem, args: SEG_STACK + 0x100, argc: args.len(), nargs, event_id: 0 };
        let res = FieldHost { st: &mut r.st, sim: &mut r.sim, session: Some(s) }.call_ex(&mut ctx, 0xc2, sub);
        let v = ctx.arg(0);
        (res, v)
    }

    #[test]
    fn vector_math_ops() {
        let Some((mut r, mut s)) = rt() else { return };
        let mut mem = Memory::default();
        mem.stack = vec![0; 0x1000];
        // a = (3,4,0) at stack+0x200, dst at +0x240; VLength(a) -> 5
        for (i, f) in [3.0f32, 4.0, 0.0].iter().enumerate() {
            mem.w32(SEG_STACK + 0x200 + 4 * i as u32, f.to_bits()).unwrap();
        }
        mem.w32(SEG_STACK + 0x100, SEG_STACK + 0x200).unwrap();
        let mut ctx = ExCtx { mem: &mut mem, args: SEG_STACK + 0x100, argc: 1, nargs: 1, event_id: 0 };
        let res = FieldHost { st: &mut r.st, sim: &mut r.sim, session: Some(&mut s) }.call_ex(&mut ctx, 0xc2, 0x83);
        assert_eq!(res, ExResult::Float);
        assert!((ctx.arg_f32(0) - 5.0).abs() < 1e-5);
    }

    #[test]
    fn set_field_data_toggles_event_boxes_and_encounter_rate() {
        let Some((mut r, mut s)) = rt() else { return };
        // box id 7 starts with the "enter disabled" nibble (flags 0x01)
        let before = r.sim.field.event_boxes.as_ref().unwrap().boxes.iter().find(|b| b.id == 7).unwrap().flags;
        assert_eq!(before & 0xf, 1);
        call(&mut r, &mut s, 0x23, &[1, 7, 1], 3);
        let after = r.sim.field.event_boxes.as_ref().unwrap().boxes.iter().find(|b| b.id == 7).unwrap().flags;
        assert_eq!(after & 0xf, 0);
        call(&mut r, &mut s, 0x23, &[5, 33, 0], 3);
        assert_eq!(r.sim.enc.rate, 33);
        // GetFieldData(1, 7) reads it back as 1 (enabled)
        let (res, v) = call(&mut r, &mut s, 0x24, &[1, 7, 0], 3);
        assert_eq!(res, ExResult::Int);
        assert_eq!(v, 1);
    }

    #[test]
    fn wait_model_follows_the_motion_command() {
        let Some((mut r, mut s)) = rt() else { return };
        call(&mut r, &mut s, 0x08, &[3, 18, 0], 3); // LoadCharacter(3, 18)
        call(&mut r, &mut s, 0x0b, &[3, 0, 1, 0], 4); // DispCharacterEP(3, entry 0)
        call(&mut r, &mut s, 0x10, &[3, 5, 0, 1], 4); // SetMotion(3, 5)
        let (res, _) = call(&mut r, &mut s, 0x14, &[3, 0], 2);
        assert!(matches!(res, ExResult::Yield(t) if t < 0), "motion still running: {res:?}");
        for _ in 0..200 {
            crate::host::tick_state(&mut r.st, &mut r.sim);
        }
        let (res, _) = call(&mut r, &mut s, 0x14, &[3, 0], 2);
        assert_eq!(res, ExResult::Void);
    }

    #[test]
    fn do_warp_waits_for_the_effect() {
        let Some((mut r, mut s)) = rt() else { return };
        let (res, _) = call(&mut r, &mut s, 0x65, &[0, 0, 0, 0xfffffffe], 4);
        assert!(matches!(res, ExResult::Yield(_)));
        for _ in 0..100 {
            crate::host::tick_state(&mut r.st, &mut r.sim);
        }
        assert!(r.st.warp_fx.is_none());
    }

    #[test]
    fn inventory_and_treasure_use_the_save_block() {
        let Some((mut r, mut s)) = rt() else { return };
        // InventoryChange(kind 1 = item, 3, +2): item 3 count 0 -> 2 (script kinds map: 0 -> 0x3c ... use TreasureControl mode 5)
        let (_, old) = call(&mut r, &mut s, 0x79, &[5, (1 << 8) | 3, 2], 3);
        assert_eq!(old, 0);
        assert_eq!(s.save.btl.item_count(3), 2);
        let (_, old) = call(&mut r, &mut s, 0x79, &[5, (1 << 8) | 3, 1], 3);
        assert_eq!(old, 2);
        assert_eq!(s.save.btl.item_count(3), 3);
    }

    #[test]
    fn angle_camera_looks_along_plus_z_at_zero_angles() {
        let t = angles_target([10.0, -20.0, 30.0], 0.0, 0.0, 50.0);
        assert!((t[0] - 10.0).abs() < 1e-3 && (t[1] + 20.0).abs() < 1e-3 && (t[2] - 80.0).abs() < 1e-3, "{t:?}");
        // a half turn looks back along -z, any angles keep the distance
        let b = angles_target([0.0; 3], 0.0, 180.0, 50.0);
        assert!((b[2] + 50.0).abs() < 1e-2, "{b:?}");
        let c = angles_target([0.0; 3], 25.0, 70.0, 50.0);
        assert!(((c[0] * c[0] + c[1] * c[1] + c[2] * c[2]).sqrt() - 50.0).abs() < 1e-2);
    }
}

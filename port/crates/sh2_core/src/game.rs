//! Gameplay glue shared by the scene plugins (`FieldPlugin`, `BattlePlugin`, `MenuPlugin`) and `sh2_app`.
//!
//! Nothing in here exists as one class in the original: it is the data that the C++ code passes between scenes through
//! globals (`SSHSys+0x40` `_SysBtlParam`, `SSHSys+0x50` battle result, `SSHSys+0x54` next field name, `CFieldSocket::m_socket`,
//! the pad objects `CPad::GetActive(0)`).
//!
//! # Schedule (see `notes/integration/gameplay.md`)
//! ```text
//! CApp::Run                                  Bevy
//! ------------------------------------------ ---------------------------------------------------------------
//! World::BeginUpdate/WorldRender/EndUpdate   PostUpdate / render world (Bevy extracts meshes, UI, gizmos)
//! CPoller(0x60).Polling  (SSHSys, prio 0x40) Update : `system_poller` (SshSys::polling) + `scene_transition`
//! CPoller(0x48/0x54).Polling (scene objects) FixedUpdate @60 Hz : [`GameSet::Input`] -> `Script` -> `Logic` -> `Camera`
//!                                            (the PS2 game logic is frame based, so it runs on a fixed 60 Hz clock)
//! m_pAppFunc                                 Update : `app_func_hook`
//! ```

use bevy::input::gamepad::{Gamepad, GamepadButton};
use bevy::prelude::*;

use crate::pad::{CPadCore, CPadHandle, PadPriority};
use crate::ssh_sys::{SshApi, SshSys, SysAction, SysBtlParam};

/// Scene states mirror the concrete `SSHApi` subclasses that `SSHSys` swaps between: `CDMYStage` (title/opening),
/// `CFieldSocket`, `BtlSocket`, `GameOver`.  (Moved here from `sh2_app` so the scene crates can name it.)
#[derive(States, Debug, Clone, Copy, PartialEq, Eq, Hash, Default)]
pub enum Scene {
    #[default]
    Boot,
    Title,
    Field,
    Battle,
    GameOver,
}

/// Ordering of the per-frame (60 Hz) scene logic; mirrors the poller priorities of `CPoller(0x48)`.
#[derive(SystemSet, Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum GameSet {
    /// pad sampling (`CPad::Polling` runs inside the system poller in the original)
    Input,
    /// event script VMs (`CScript::Polling`, prio 0x70)
    Script,
    /// scene objects (`CField::Polling`, `CBattle::Polling`, `Menu::Run`; prio 0x80)
    Logic,
    /// camera apply (`CField::CameraUpdate` -> `CFieldCamera::Apply`)
    Camera,
}

/// PS2 pad bits (libpad word after inversion; see `notes/F/menu_toolkit.md` section 6).
pub mod padbit {
    pub const SELECT: u16 = 0x0001;
    pub const L3: u16 = 0x0002;
    pub const R3: u16 = 0x0004;
    pub const START: u16 = 0x0008;
    pub const UP: u16 = 0x0010;
    pub const RIGHT: u16 = 0x0020;
    pub const DOWN: u16 = 0x0040;
    pub const LEFT: u16 = 0x0080;
    pub const L2: u16 = 0x0100;
    pub const R2: u16 = 0x0200;
    pub const L1: u16 = 0x0400;
    pub const R1: u16 = 0x0800;
    /// main menu in the field
    pub const TRIANGLE: u16 = 0x1000;
    /// confirm / talk (JP convention)
    pub const CIRCLE: u16 = 0x2000;
    /// cancel / run
    pub const CROSS: u16 = 0x4000;
    pub const SQUARE: u16 = 0x8000;
}

/// `CPad::GetActive(0)`: the player-one pad.  Updated once per 60 Hz tick.
#[derive(Resource)]
pub struct GamePad {
    core: CPadCore,
    handle: CPadHandle,
}

impl Default for GamePad {
    fn default() -> Self {
        GamePad {
            core: CPadCore::default(),
            // Digital: `MakeMoveControl` takes the d-pad branch (heading = dirTbl * 45 degrees, speed 0.5)
            handle: CPadHandle { id: 0, mode: PadPriority::Digital, repeat_delay: 20, repeat_on: 1, repeat_off: 5 },
        }
    }
}

impl GamePad {
    /// `CPad::Polling` — feed the libpad button word of this frame (sticks centred).
    pub fn feed(&mut self, raw: u16) {
        self.feed_analog(raw, PadSticks::default());
    }
    /// `CPad::Polling` with the analog stick bytes of a DualShock (`pad[4..8]` = right x/y, left x/y).
    pub fn feed_analog(&mut self, raw: u16, sticks: PadSticks) {
        let buf = [0, 0, (raw & 0xff) as u8, (raw >> 8) as u8, sticks.right[0], sticks.right[1], sticks.left[0], sticks.left[1]];
        self.core.update(&buf, &self.handle);
    }
    /// buttons currently held (`CPad::GetReal`)
    pub fn real(&self) -> u16 {
        self.core.real
    }
    /// buttons pressed this frame (`CPad::GetPress` / trigger)
    pub fn press(&self) -> u16 {
        self.core.press
    }
    pub fn release(&self) -> u16 {
        self.core.release
    }
    /// auto-repeat mask (d-pad menu navigation)
    pub fn repeat(&self) -> u16 {
        self.core.repeat
    }
    /// `Menu::GetKey` word: buttons from the trigger word, d-pad from the repeat word.
    pub fn menu_keys(&self) -> u16 {
        (self.core.press & 0xff0f) | (self.core.repeat & 0xf0)
    }
    /// left stick gauge/degree for `MakeMoveControl` (gauge 0 for the keyboard / a centred stick; degrees 0 = up, clockwise)
    pub fn stick_gauge_degree(&self) -> (f32, f32) {
        (self.core.stick_l.gauge, self.core.stick_l.degree)
    }
    /// Clear edge state (used on scene changes so a button press does not leak into the next scene).
    pub fn swallow(&mut self) {
        self.core.press = 0;
        self.core.repeat = 0;
    }
}

/// Extra buttons injected by `--autoplay` / tests; OR-ed with the keyboard every tick.
#[derive(Resource, Default, Debug, Clone, Copy)]
pub struct PadInjection {
    pub raw: u16,
}

/// libpad stick bytes (`0x00` = left / up, `0x80` = centre, `0xff` = right / down).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct PadSticks {
    pub left: [u8; 2],
    pub right: [u8; 2],
}

impl Default for PadSticks {
    fn default() -> Self {
        PadSticks { left: [0x80; 2], right: [0x80; 2] }
    }
}

/// A Bevy stick vector (x right, y up, -1..1) as libpad bytes.
pub fn stick_bytes(v: Vec2) -> [u8; 2] {
    let b = |f: f32| (127.5 + f.clamp(-1.0, 1.0) * 127.5).round().clamp(0.0, 255.0) as u8;
    [b(v.x), b(-v.y)]
}

/// Gamepad -> *physical* PS2 pad (DualShock 2 layout: South = Cross, East = Circle, North = Triangle, West = Square), so it goes through
/// the same build remap as the keyboard: on the retail disc the bottom face button confirms, the right one cancels / runs.
pub fn gamepad_to_pad(pad: &Gamepad) -> (u16, PadSticks) {
    let map: [(GamepadButton, u16); 16] = [
        (GamepadButton::DPadUp, padbit::UP),
        (GamepadButton::DPadRight, padbit::RIGHT),
        (GamepadButton::DPadDown, padbit::DOWN),
        (GamepadButton::DPadLeft, padbit::LEFT),
        (GamepadButton::South, padbit::CROSS),
        (GamepadButton::East, padbit::CIRCLE),
        (GamepadButton::North, padbit::TRIANGLE),
        (GamepadButton::West, padbit::SQUARE),
        (GamepadButton::LeftTrigger, padbit::L1),
        (GamepadButton::RightTrigger, padbit::R1),
        (GamepadButton::LeftTrigger2, padbit::L2),
        (GamepadButton::RightTrigger2, padbit::R2),
        (GamepadButton::Select, padbit::SELECT),
        (GamepadButton::Start, padbit::START),
        (GamepadButton::LeftThumb, padbit::L3),
        (GamepadButton::RightThumb, padbit::R3),
    ];
    let mut raw = 0u16;
    for (b, bit) in map {
        if pad.pressed(b) {
            raw |= bit;
        }
    }
    (raw, PadSticks { left: stick_bytes(pad.left_stick()), right: stick_bytes(pad.right_stick()) })
}

/// Keyboard -> PS2 pad mapping (documented in `notes/integration/gameplay.md`).
pub fn keyboard_to_pad(keys: &ButtonInput<KeyCode>) -> u16 {
    let mut raw = 0u16;
    let map: [(&[KeyCode], u16); 9] = [
        (&[KeyCode::ArrowUp, KeyCode::KeyW], padbit::UP),
        (&[KeyCode::ArrowRight, KeyCode::KeyD], padbit::RIGHT),
        (&[KeyCode::ArrowDown, KeyCode::KeyS], padbit::DOWN),
        (&[KeyCode::ArrowLeft, KeyCode::KeyA], padbit::LEFT),
        (&[KeyCode::Space, KeyCode::KeyZ, KeyCode::Enter], padbit::CIRCLE),
        (&[KeyCode::KeyX, KeyCode::Backspace], padbit::CROSS),
        (&[KeyCode::KeyC, KeyCode::Tab], padbit::TRIANGLE),
        (&[KeyCode::KeyV], padbit::SQUARE),
        (&[KeyCode::Enter, KeyCode::Escape], padbit::START),
    ];
    for (ks, bit) in map {
        if ks.iter().any(|k| keys.pressed(*k)) {
            raw |= bit;
        }
    }
    raw
}

/// `SaveMenuSection::SetDefaultButton` (MENU save +0x26c..0x272, four u16 entries for the physical Triangle, Circle, Cross, Square):
/// JP demo `[0xc, 0xd, 0xe, 0xf]` (identity), **US retail `[0xc, 0xe, 0xd, 0xf]`**.  `SaveMenuSection::UpdatePad` turns them into the
/// `CPad` remap table (`assign[entry[k]] = 1 << (0xc + k)`, applied to the raw word: raw bit `i` -> logical mask `assign[i]`), so on the retail
/// disc the physical Cross button produces the logical Circle bit (`0x2000`: field examine / talk, menu "decide") and the physical Circle
/// produces the logical Cross bit (`0x4000`: cancel, run modifier) -- verified live: the US `CPad` core's `assign` table (core + 0x48) reads
/// `... 0x1000, 0x4000, 0x2000, 0x8000`.
pub const JP_DEFAULT_BUTTONS: [u16; 4] = [0xc, 0xd, 0xe, 0xf];
pub const US_DEFAULT_BUTTONS: [u16; 4] = [0xc, 0xe, 0xd, 0xf];

/// Apply the face-button remap of `SaveMenuSection::UpdatePad` to a raw (physical) pad word.
pub fn apply_button_assign(raw: u16, entries: [u16; 4]) -> u16 {
    let mut out = raw & !0xf000;
    for (k, &e) in entries.iter().enumerate() {
        // assign[e] = 1 << (0xc + k): raw bit `e` produces logical bit `0xc + k`
        if raw & (1u16 << e) != 0 {
            out |= 1u16 << (0xc + k);
        }
    }
    out
}

/// The default remap of the active build.
pub fn default_buttons() -> [u16; 4] {
    if crate::boot::is_retail() {
        US_DEFAULT_BUTTONS
    } else {
        JP_DEFAULT_BUTTONS
    }
}

/// The player's Key Customize choice (`MENU+0x26c`, [`apply_button_assign`] entries); `None` = the build default.  Written by
/// `sh2_menu::plugin::apply_system_options`, read by [`sample_pad`].
#[derive(Resource, Default, Debug, Clone, Copy, PartialEq, Eq)]
pub struct ButtonAssign(pub Option<[u16; 4]>);

/// First system of the 60 Hz tick: sample keyboard + gamepads + injection into [`GamePad`].  The keyboard and the gamepads are *physical* pads
/// (X = Cross, Z = Circle ...) and go through the build's button remap; the injection (autoplay / tests) is already logical.  All connected
/// gamepads drive player one; the left stick is the first one pushed past the libpad dead zone.
pub fn sample_pad(
    keys: Res<ButtonInput<KeyCode>>,
    gamepads: Query<&Gamepad>,
    inj: Res<PadInjection>,
    assign: Option<Res<ButtonAssign>>,
    mut pad: ResMut<GamePad>,
) {
    let entries = assign.and_then(|a| a.0).unwrap_or_else(default_buttons);
    let mut raw = keyboard_to_pad(&keys);
    let mut sticks = PadSticks::default();
    let off_centre = |b: [u8; 2]| b.iter().any(|&v| (v as i32 - 0x80).abs() > 0x30);
    for gp in &gamepads {
        let (b, s) = gamepad_to_pad(gp);
        raw |= b;
        if !off_centre(sticks.left) && off_centre(s.left) {
            sticks.left = s.left;
        }
        if !off_centre(sticks.right) && off_centre(s.right) {
            sticks.right = s.right;
        }
    }
    pad.feed_analog(apply_button_assign(raw, entries) | inj.raw, sticks);
}

/// Which field map to load when `Scene::Field` is entered (the C++ passes it as `SSHSys+0x54`/`InitFieldSocketM(name)`).
#[derive(Resource, Debug, Clone, PartialEq)]
pub struct FieldRequest {
    pub map: String,
    /// `ENTRYPOS` index; [`FieldRequest::RESTORE`] (-2, `FieldMapJump(name, -2)`) = come back from battle/load at the saved position.
    pub entry: i32,
}

impl FieldRequest {
    pub const RESTORE: i32 = -2;
    /// first map of the JP demo `FIELD.PKB` (`FIELD/MPS/AP_00_U.MPS`)
    pub const FIRST_MAP: &'static str = "AP_00_U";
    /// `WORLDMAP_NAME`: a field request for this name opens the world map (`CFieldSocket::fieldOverlay`)
    pub const WORLDMAP_NAME: &'static str = "WORLDMAP";
}

impl Default for FieldRequest {
    fn default() -> Self {
        FieldRequest { map: Self::FIRST_MAP.to_string(), entry: 0 }
    }
}

/// `_SysBtlParam` + return path of the battle that is about to start (`SSHSys::StartBattle(param, field)`).
#[derive(Resource, Debug, Clone, Default)]
pub struct BattleRequest {
    pub param: SysBtlParam,
    /// field to return to (`SSHSys+0x54`)
    pub return_map: String,
}

/// Battle outcome code stored in `BtlSocket+0x16c & 3` and consumed by `SSHSys::cbBattleA`.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum BattleOutcome {
    #[default]
    Win,
    /// escaped (`GetEscapeRate` succeeded): returns to the field without rewards
    Escaped,
    Lose,
}

impl BattleOutcome {
    /// `BtlSocket+0x16c & 3`: 0 win, 1 lose (game over unless the no-game-over flag is set), 2/3 escaped.
    pub fn bits(self) -> u8 {
        match self {
            BattleOutcome::Win => 0,
            BattleOutcome::Lose => 1,
            BattleOutcome::Escaped => 2,
        }
    }
}

/// The result record handed from `CBattle::MakeResultTrophy` to `BtlSocket::BtlCBFunc` (see `notes/H/battle_flow.md`).
#[derive(Resource, Debug, Clone, Default)]
pub struct BattleReport {
    pub outcome: BattleOutcome,
    pub exp: i32,
    pub cash: i32,
    pub sp: i32,
    pub items: Vec<(i16, u8)>,
    /// set by the battle plugin when it has finished and the field/session should apply it
    pub pending: bool,
}

/// Frame rate of the PS2 game logic (NTSC progressive fields).
pub const LOGIC_HZ: f64 = 60.0;

/// Apply the actions produced by `SSHSys::PollingApi` (`InitFieldSocketM`, `InitBtlSocket`, `new GameOver`).
/// Called from `sh2_app`'s `scene_transition`, right after `SshSys::polling`.
pub fn apply_sys_actions(sys: &mut SshSys, field: &mut FieldRequest, battle: &mut BattleRequest) {
    for a in sys.take_actions() {
        match a {
            // JP: 0x003bcfd0 InitFieldSocketM(name) — create/retarget the CFieldSocket and SetAPI it
            SysAction::StartField(name) => {
                if !name.is_empty() {
                    field.map = name;
                }
                let ok = sys.set_api(SshApi::FieldSocket);
                debug_assert!(ok || sys.current_kind().is_some());
                log::info!("SSHSys: field request -> {} (entry {})", field.map, field.entry);
            }
            // JP: 0x0032d4c0 InitBtlSocket + BtlSocket::SetPC/SetMonsterSet
            SysAction::StartBattle(param) => {
                battle.param = param;
                if !sys.field_name.is_empty() {
                    battle.return_map = sys.field_name.clone();
                }
                sys.set_api(SshApi::BtlSocket);
                log::info!("SSHSys: battle request monster set {} pcs {}", param.regdat_id, param.pc_count);
            }
            // JP: new GameOver
            SysAction::StartGameOver => {
                sys.set_api(SshApi::GameOver);
            }
        }
    }
}

/// Registers the shared resources and the 60 Hz tick.
pub struct GameCorePlugin;

impl Plugin for GameCorePlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<GamePad>()
            .init_resource::<PadInjection>()
            .init_resource::<ButtonAssign>()
            .init_resource::<FieldRequest>()
            .init_resource::<BattleRequest>()
            .init_resource::<BattleReport>()
            .insert_resource(Time::<Fixed>::from_hz(LOGIC_HZ))
            .configure_sets(FixedUpdate, (GameSet::Input, GameSet::Script, GameSet::Logic, GameSet::Camera).chain())
            .add_systems(FixedUpdate, sample_pad.in_set(GameSet::Input));
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn stick_bytes_follow_libpad() {
        use super::stick_bytes;
        use bevy::math::Vec2;
        assert_eq!(stick_bytes(Vec2::ZERO), [0x80, 0x80]);
        assert_eq!(stick_bytes(Vec2::new(1.0, 1.0)), [0xff, 0x00], "right / up");
        assert_eq!(stick_bytes(Vec2::new(-1.0, -1.0)), [0x00, 0xff], "left / down");
    }

    #[test]
    fn analog_stick_reaches_move_control() {
        use super::{stick_bytes, GamePad, PadSticks};
        use bevy::math::Vec2;
        let mut p = GamePad::default();
        p.feed_analog(0, PadSticks { left: stick_bytes(Vec2::new(0.0, 1.0)), ..Default::default() });
        let (g, d) = p.stick_gauge_degree();
        assert!(g > 0.95 && d.abs() < 1e-3, "full up = run heading 0 ({g}, {d})");
        p.feed_analog(0, PadSticks { left: stick_bytes(Vec2::new(0.5, 0.0)), ..Default::default() });
        let (g, d) = p.stick_gauge_degree();
        assert!(g > 0.1 && g < 0.95 && (d - 90.0).abs() < 1e-3, "half right = walk heading 90 ({g}, {d})");
        p.feed(0);
        assert_eq!(p.stick_gauge_degree().0, 0.0);
    }

    #[test]
    fn retail_swaps_circle_and_cross() {
        use super::{apply_button_assign, padbit, JP_DEFAULT_BUTTONS, US_DEFAULT_BUTTONS};
        let all = padbit::CIRCLE | padbit::CROSS | padbit::TRIANGLE | padbit::SQUARE | padbit::UP;
        assert_eq!(apply_button_assign(all, JP_DEFAULT_BUTTONS), all);
        assert_eq!(apply_button_assign(padbit::CROSS, US_DEFAULT_BUTTONS), padbit::CIRCLE);
        assert_eq!(apply_button_assign(padbit::CIRCLE, US_DEFAULT_BUTTONS), padbit::CROSS);
        assert_eq!(apply_button_assign(all, US_DEFAULT_BUTTONS), all);
        assert_eq!(apply_button_assign(padbit::TRIANGLE | padbit::LEFT, US_DEFAULT_BUTTONS), padbit::TRIANGLE | padbit::LEFT);
    }

    use super::*;

    #[test]
    fn pad_edges() {
        let mut p = GamePad::default();
        p.feed(padbit::CIRCLE);
        assert_eq!(p.press(), padbit::CIRCLE);
        p.feed(padbit::CIRCLE);
        assert_eq!(p.press(), 0);
        assert_eq!(p.real(), padbit::CIRCLE);
        p.feed(0);
        assert_eq!(p.release(), padbit::CIRCLE);
    }

    #[test]
    fn outcome_bits_match_cb_battle() {
        let mut s = SshSys::default();
        s.cb_battle(0, BattleOutcome::Lose.bits());
        s.polling(std::time::Duration::from_millis(16));
        assert_eq!(s.take_actions(), vec![SysAction::StartGameOver]);
        let mut s = SshSys::default();
        s.cb_battle(0, BattleOutcome::Win.bits());
        s.polling(std::time::Duration::from_millis(16));
        assert!(matches!(s.take_actions()[..], [SysAction::StartField(_)]));
    }
}

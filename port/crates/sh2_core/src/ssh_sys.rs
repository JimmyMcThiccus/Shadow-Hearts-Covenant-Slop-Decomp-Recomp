//! SSHSys / SSHApi / SysTool — the scene manager (JP `SSHmain.cpp`, 0x003b6130..0x003b74a0 and 0x0023bcc0..0x0023c9ff).
//!
//! # SSHSys layout (0xB0 bytes, `new SSHSys` in `SSHMain`, global `SSHSys::sys` 0x0040ad60)
//! ```text
//! +0x00 CPolObj base (0x18; vtable@+0x14 = { +8 __dt, +0xc Polling })   -- lives in CApp's *system* poller (prio 0x40)
//! +0x18 SysTool base (vtable { +8 dt, +0xc Initialize, +0x10 Terminate, +0x14 SysInitialize, +0x18 SysTerminate,
//!                              +0x1c PluginAttach, +0x20 CBPause })
//! +0x1c i32  lastTime          SysTool::GetTimer() of the previous Polling
//! +0x20 i32  frameDelta        GetFrameDelta()
//! +0x24 SSHApi* pending        +0x28 SSHApi* current
//! +0x2c CPad*  pad0 (Initialize: new CPad(0); Enable(); +8 priority = _6412)
//! +0x30 i32  initPhase         1 until MenuObj::IsReady && BgEffectMan::cmnTexture, then 0
//! +0x34 u8   pendingState      0 none, 1 preLoad requested, 2 preLoad done (ready for handover)
//! +0x35 u8   currentState      0 running, 3 closeInquiry requested, 4 closed (may be destroyed)
//! +0x36 u8   request           0x10 field, 0x20 battle armed, 0x21 battle go, 0x30 game over, (US retail) 0x40 return to title
//! +0x37 u8   fioBusy           DiskChange() set; cleared when FileIOLib+0x13934 (diskState) becomes 0
//! +0x38 i16  pauseTimer        counts down by frameDelta; Pause button re-arm
//! +0x3a i16  pauseReload       500 (ms)  (SetPauseTmr)
//! +0x3c u16  flags             bit6 = pauser type (1 = CLSDPauser, 0 = CPauser)  (SetPauserType)
//! +0x40 _SysBtlParam {u32; u32 regdatId; u16 bgm; u8 pcCount; u8 monsterSet; u8 pc[4]}   (0x10)
//! +0x50 u8 btlResult[4]        [0]=2 after a battle, [1]=outcome code (0xff / 0 / 1), [2]=no-gameover flag
//! +0x54 char fieldName[0x14]   next field map name (passed to InitFieldSocketM / FieldPreLoad)
//! +0x68 Overlay overlay (0x40)  +0xa8 CScreenCap* screenCap   +0xac pad
//! ```
//! US retail layout (SLUS_210.41, still 0xb0 bytes, ctor 0x003edb80): `_SysBtlParam` is 0x14 bytes (5 party slots, +0x40..+0x54),
//! `btlResult[4]` moves to +0x54, `fieldName` to +0x58 (only 0x10 bytes left before the unchanged `Overlay` at +0x68); the ctor also
//! clears the battle-extras globals 0x00459ae0..0x00459af0.  See `notes/I/us_delta.md` and the `*Us` items below.
//!
//! # SSHApi (8 bytes: `+0 ?`, `+4 vtable`)
//! vtable: `+8 __dt, +0xc preLoad, +0x10 Start, +0x14 closeInquiry, +0x18 Pause(bool), +0x1c Reset(int)`.
//! In derived classes (CDMYStage, CFieldSocket, BtlSocket) SSHApi is the *first* base and `CPolObj` is the
//! second base at +8 (so their CPolObj vtable is at +0x1c and `Polling` is reached through an `@8@` thunk).
//!
//! # State machine (`SSHSys::Polling`, `SetAPI`)
//! ```text
//! SetAPI(api)       only if pending == null.  If current != null && curState < 3 => curState = 3 (ask it to close).
//!                   pendState = 1; pending = api.
//! each Polling (initPhase == 0):
//!   if curState == 3:  current == null ? curState = 0 : (current.closeInquiry() == 0 ? curState = 4)
//!   if pendState == 1: if pending == null { pendState = 0 } else if pending.preLoad() != 0 { pendState = 2 }
//!   if pendState == 2 (or just became 2) and (current == null or curState == 4):
//!        delete current (if any); curState = 0;
//!        if pending: pending.Start(); current = pending; pending = null; pendState = 0
//!   PollingApi()      -- handles `request`
//! ```
use std::time::Duration;

use crate::fileio::add_local_path;

/// Scene kinds (the concrete `SSHApi` subclasses).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SshApi {
    DummyStage,
    FieldSocket,
    BtlSocket,
    GameOver,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SceneRequest {
    Title,
    Field,
    Battle,
    GameOver,
}

/// The `SSHApi` virtual interface (vtable +0xc..+0x1c).
pub trait SshApiObj: Send + Sync {
    fn kind(&self) -> SshApi;
    /// vtable +0xc — base returns 1.  Returns true when pre-loading is finished.
    fn pre_load(&mut self) -> bool {
        true
    }
    /// vtable +0x10 — base returns 1; called once when the API becomes current.
    fn start(&mut self) -> bool {
        true
    }
    /// vtable +0x14 — base returns 0.  Non-zero means "still busy closing"; the SSHSys keeps asking.
    fn close_inquiry(&mut self) -> bool {
        false
    }
    /// vtable +0x18 — `SSHApi::Pause(bool)`: base creates the CPauser (`false`) or lets it go (`true`).
    fn pause(&mut self, _resume: bool) {}
    /// vtable +0x1c — base returns 0.
    fn reset(&mut self, _reason: i32) -> i64 {
        0
    }
}

/// Trivial API carrying only its kind (what `set_api(SshApi)` creates).
pub struct KindApi(pub SshApi);
impl SshApiObj for KindApi {
    fn kind(&self) -> SshApi {
        self.0
    }
}

/// `_SysBtlParam` (0x10 bytes) as passed to `SSHSys::StartBattle`.
#[derive(Debug, Clone, Copy, Default, PartialEq, Eq)]
pub struct SysBtlParam {
    pub w0: u32,
    /// +4: id handed to `RegDatApi::GetRegDat(0x2f, id, -1)` (monster-set table)
    pub regdat_id: i32,
    /// +8: battle BGM number (`BtlSocket::SetBtlBGMNumber`)
    pub bgm: u16,
    /// +0xa: number of party members (`BtlSocket::SetPC(count, pc)`)
    pub pc_count: u8,
    /// +0xb: monster set index (`BtlSocket::SetMonsterSet`)
    pub monster_set: u8,
    /// +0xc..+0xf: party member ids
    pub pc: [u8; 4],
}

/// request byte values (`SSHSys+0x36`)
pub mod req {
    pub const NONE: u8 = 0;
    pub const FIELD: u8 = 0x10;
    pub const BATTLE_ARMED: u8 = 0x20;
    pub const BATTLE_GO: u8 = 0x21;
    pub const GAME_OVER: u8 = 0x30;
    /// US retail only: `SSHSys::RequestTitle` (0x003ee600) -> `PollingApi` releases the resident field objects and calls
    /// `opening()` (= `SetAPI(new CDMYStage)`), i.e. a soft return to the title screen.
    pub const TITLE: u8 = 0x40;
}

/// US retail `_SysBtlParam` is 0x14 bytes: one more party slot than the JP demo (`pc[5]` at +0x4c..+0x50 in SSHSys).
#[derive(Debug, Clone, Copy, Default, PartialEq, Eq)]
pub struct SysBtlParamUs {
    pub w0: u32,
    /// +4: monster-set id; with `monster_set == 0` it is handed straight to `BtlSocket::SetMonsterSet(id)` (0x003687d0),
    /// otherwise `RegDatApi::GetRegDat(0x35, id, -1)` (JP: kind 0x2f) + `SetMonsterSet(count, table)` (0x003686b0)
    pub regdat_id: i32,
    pub bgm: u16,
    pub pc_count: u8,
    pub monster_set: u8,
    pub pc: [u8; 5],
}

impl From<SysBtlParam> for SysBtlParamUs {
    fn from(p: SysBtlParam) -> Self {
        SysBtlParamUs { w0: p.w0, regdat_id: p.regdat_id, bgm: p.bgm, pc_count: p.pc_count, monster_set: p.monster_set, pc: [p.pc[0], p.pc[1], p.pc[2], p.pc[3], 0xff] }
    }
}

impl From<SysBtlParamUs> for SysBtlParam {
    fn from(p: SysBtlParamUs) -> Self {
        SysBtlParam { w0: p.w0, regdat_id: p.regdat_id, bgm: p.bgm, pc_count: p.pc_count, monster_set: p.monster_set, pc: [p.pc[0], p.pc[1], p.pc[2], p.pc[3]] }
    }
}

/// Retail battle start extras kept in globals (0x00459ae0..0x00459aef): set through `SetBattleFlags` (0x003ee620) and
/// `SetBattleBgmStream` (0x003ee670) before `StartBattle`, consumed by `PollingApi` request 0x21.
#[derive(Debug, Clone, Copy, Default, PartialEq, Eq)]
pub struct BattleExtrasUs {
    /// 0x00459ae8: non-zero (and != 2 -> kept) selects `BtlSocket::SetBtlBgmStream(a, b)` (0x00368b10) instead of `SetBtlBGMNumber`;
    /// bit0 is copied to `BtlSocket+0x18d`; the value 2 is reset to 0 by `PollingApi`
    pub flag0: u8,
    /// 0x00459ae9 -> `BtlSocket+0x18e`
    pub flag1: u8,
    /// 0x00459aea -> `BtlSocket+0x18f`
    pub flag2: u8,
    /// 0x00459ae0 / 0x00459ae4: streamed battle BGM (Sdrv stream handle, size/id)
    pub stream_a: u32,
    pub stream_b: u32,
}

/// What [`StreamFade::step`] asks the sound driver to do.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum StreamCmd {
    /// `Sdrv` command 0xf: fade the stream out over `ms`
    FadeOut { handle: u32, ms: u16 },
    /// `Sdrv` command 0x11 with arg 1: close; repeated until the driver stops answering -1
    Close { handle: u32 },
}

/// `SSHSys::StepStreamFade` (0x003eda50, global state byte 0x00459aeb): once a custom battle BGM stream has been
/// armed and the battle ended in a game over, `cbBattleA` sets the state to 1; each `PollingApi` then fades the stream
/// out for 500 ms and closes it.
#[derive(Debug, Clone, Copy, Default, PartialEq, Eq)]
pub struct StreamFade {
    /// 0 idle, 1 start, 2 waiting 500 ms, 3 closing
    pub state: u8,
    pub started_ms: i32,
}

impl StreamFade {
    pub const FADE_MS: i32 = 500;
    pub fn arm(&mut self) {
        self.state = 1;
    }
    /// `close_ok(handle)`: result of the driver close call (`!= -1` finishes the sequence).
    pub fn step(&mut self, now_ms: i32, handle: u32, close_ok: impl FnOnce(u32) -> bool) -> Option<StreamCmd> {
        match self.state {
            1 => {
                self.started_ms = now_ms;
                self.state = 2;
                Some(StreamCmd::FadeOut { handle, ms: Self::FADE_MS as u16 })
            }
            2 => {
                if (now_ms.wrapping_sub(self.started_ms) as u32) >= Self::FADE_MS as u32 {
                    self.state = 3;
                }
                None
            }
            3 => {
                if close_ok(handle) {
                    self.state = 0;
                }
                Some(StreamCmd::Close { handle })
            }
            _ => None,
        }
    }
}

/// What `PollingApi` asks the world to do (the C++ code calls `InitFieldSocketM`, `InitBtlSocket`, `new GameOver`).
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum SysAction {
    /// `InitFieldSocketM(fieldName)`: create or re-target the CFieldSocket and `SetAPI` it
    StartField(String),
    /// `GetRegDat(0x2f, id, -1)` + `InitBtlSocket()` + `SetBtlBGMNumber/SetPC/SetMonsterSet` + callbacks
    StartBattle(SysBtlParam),
    /// `new GameOver` (a `Menu` driven by GameOverScene) + `SetAPI(0)`: GameOver registers itself
    StartGameOver,
}

#[cfg_attr(feature = "bevy", derive(bevy::prelude::Resource))]
pub struct SshSys {
    pending: Option<Box<dyn SshApiObj>>,
    current: Option<Box<dyn SshApiObj>>,
    pub pending_state: u8,
    pub current_state: u8,
    pub init_phase: i32,
    request: u8,
    fio_busy: bool,
    pause_timer: i32,
    pause_reload: i32,
    pub flags: u16,
    pub frame_delta: Duration,
    last_time: i32,
    pub btl: SysBtlParam,
    /// +0x50..+0x53: [0]=2 after a battle, [1]=outcome, [2]=no-game-over flag
    pub btl_result: [u8; 4],
    pub field_name: String,
    /// last request produced for the Bevy layer
    scene_request: Option<SceneRequest>,
    actions: Vec<SysAction>,
    /// `SSHSys::Language` (0x0040ad64)
    pub language: u8,
    /// Model the US retail behaviour (`PollingApi` request 0x40, resident-object release on game over, battle extras ...)
    pub retail: bool,
    /// US: language directory index taken from the MENU section byte +0x18 (default 1) instead of `language`
    pub menu_language: u32,
    /// US: `_SysBtlParam` 5th party slot
    pub btl_pc5: u8,
    /// US: battle start extras (globals 0x00459ae0..)
    pub btl_extras: BattleExtrasUs,
    /// US: deferred BGM stream fade (global 0x00459aeb)
    pub stream_fade: StreamFade,
    residents_release: bool,
}

impl Default for SshSys {
    // JP: 0x003b6560 __ct__6SSHSysFv  (pause timer reload = 500)
    fn default() -> Self {
        SshSys {
            pending: None,
            current: None,
            pending_state: 0,
            current_state: 0,
            init_phase: 0, // set to 1 by Initialize(); the plugin starts with the assets ready
            request: 0,
            fio_busy: false,
            pause_timer: 0,
            pause_reload: 500,
            flags: 0,
            frame_delta: Duration::ZERO,
            last_time: 0,
            btl: SysBtlParam::default(),
            btl_result: [0; 4],
            field_name: String::new(),
            scene_request: None,
            actions: Vec::new(),
            language: 1,
            retail: false,
            menu_language: crate::boot::MENU_LANGUAGE_DEFAULT,
            btl_pc5: 0xff,
            btl_extras: BattleExtrasUs::default(),
            stream_fade: StreamFade::default(),
            residents_release: false,
        }
    }
}

impl SshSys {
    // JP: 0x003b6130 SetAPI__6SSHSysFP6SSHApi — only accepted when nothing is pending.
    pub fn set_api_obj(&mut self, api: Box<dyn SshApiObj>) -> bool {
        if self.pending.is_some() {
            return false;
        }
        if self.current.is_some() && self.current_state < 3 {
            self.current_state = 3;
        }
        self.pending_state = 1;
        self.pending = Some(api);
        true
    }
    /// compatibility with the first skeleton (kind-only APIs)
    pub fn set_api(&mut self, api: SshApi) -> bool {
        self.set_api_obj(Box::new(KindApi(api)))
    }

    // JP: 0x003b61c0 isPrevApiGone__6SSHSysFv
    pub fn is_prev_api_gone(&self) -> bool {
        self.current.is_none() || self.current_state == 4
    }

    pub fn current_kind(&self) -> Option<SshApi> {
        self.current.as_ref().map(|a| a.kind())
    }
    pub fn current_mut(&mut self) -> Option<&mut (dyn SshApiObj + 'static)> {
        self.current.as_deref_mut()
    }

    /// JP: 0x003b6230 Polling__6SSHSysFv (the SSHApi handover part; timer/pad/fio are done by the host systems)
    pub fn polling(&mut self, dt: Duration) {
        self.frame_delta = dt;
        let delta_ms = dt.as_millis() as i32;
        self.last_time = self.last_time.wrapping_add(delta_ms);
        if self.fio_busy {
            // original: cleared once FileIOLib+0x13934 (disk change state) is 0 — host calls disk_change_done()
        }
        if self.pause_timer != 0 {
            self.pause_timer -= delta_ms;
            if self.pause_timer < 0 {
                self.pause_timer = 0;
            }
        }
        if self.init_phase == 1 {
            // wait until MenuObj::IsReady() && BgEffectMan::cmnTexture != 0 -- host calls assets_ready()
        } else if self.init_phase == 0 {
            if self.current_state != 4 && self.current_state == 3 {
                match self.current.as_mut() {
                    None => self.current_state = 0,
                    Some(cur) => {
                        if !cur.close_inquiry() {
                            self.current_state = 4;
                        }
                    }
                }
            }
            let mut ready = self.pending_state == 2;
            if self.pending_state == 1 {
                match self.pending.as_mut() {
                    None => self.pending_state = 0,
                    Some(p) => {
                        if p.pre_load() {
                            self.pending_state = 2;
                            ready = true;
                        }
                    }
                }
            }
            if ready && (self.current.is_none() || self.current_state == 4) {
                self.current = None; // virtual dtor (delete)
                self.current_state = 0;
                if let Some(mut p) = self.pending.take() {
                    p.start();
                    self.scene_request = Some(match p.kind() {
                        SshApi::DummyStage => SceneRequest::Title,
                        SshApi::FieldSocket => SceneRequest::Field,
                        SshApi::BtlSocket => SceneRequest::Battle,
                        SshApi::GameOver => SceneRequest::GameOver,
                    });
                    self.current = Some(p);
                    self.pending_state = 0;
                }
            }
        }
        self.polling_api();
    }

    /// host: MenuObj ready and common texture loaded
    pub fn assets_ready(&mut self) {
        if self.init_phase == 1 {
            self.init_phase = 0;
        }
    }

    pub fn take_request(&mut self) -> Option<SceneRequest> {
        self.scene_request.take()
    }
    pub fn take_actions(&mut self) -> Vec<SysAction> {
        std::mem::take(&mut self.actions)
    }

    // JP: 0x003b6f40 PollingApi__6SSHSysFv  (only runs when initPhase == 0)
    fn polling_api(&mut self) {
        if self.init_phase != 0 {
            return;
        }
        match self.request {
            req::FIELD => {
                self.actions.push(SysAction::StartField(self.field_name.clone()));
                self.request = req::NONE;
            }
            req::TITLE => {
                // US 0x003ee6a0: ReleaseResidentA/B (0x003f7790 / 0x003f77c0), opening() (= SetAPI(new CDMYStage)), clear +0x54
                self.residents_release = true;
                self.btl_result[0] = 0;
                self.request = req::NONE;
                self.set_api(SshApi::DummyStage);
            }
            req::GAME_OVER => {
                if self.retail {
                    // US also releases the two resident objects before creating GameOver and clears btlResult[0]
                    self.residents_release = true;
                    self.btl_result[0] = 0;
                }
                self.actions.push(SysAction::StartGameOver);
                self.request = req::NONE;
            }
            req::BATTLE_GO => {
                self.actions.push(SysAction::StartBattle(self.btl));
                self.request = req::NONE;
            }
            _ => {}
        }
    }

    // US: 0x003ee600 RequestTitle__6SSHSysFv -- request byte 0x40
    /// Ask `PollingApi` for a soft return to the title (retail only).
    pub fn request_title(&mut self) {
        self.request = req::TITLE;
    }
    /// US: true once after a title / game-over request: the host must destroy the two resident objects
    /// (`ReleaseResidentA` 0x003f7790, `ReleaseResidentB` 0x003f77c0) before the new scene starts.
    pub fn take_residents_release(&mut self) -> bool {
        std::mem::take(&mut self.residents_release)
    }
    // US: 0x003ee620 SetBattleFlags / 0x003ee670 SetBattleBgmStream
    pub fn set_battle_flags(&mut self, f0: u8, f1: u8, f2: u8) {
        self.btl_extras.flag0 = f0;
        self.btl_extras.flag1 = f1;
        self.btl_extras.flag2 = f2;
    }
    pub fn set_battle_bgm_stream(&mut self, a: u32, b: u32) {
        self.btl_extras.stream_a = a;
        self.btl_extras.stream_b = b;
    }
    /// US `cbBattleA(code, arg, arg3)` extras: a lost battle (request 0x30) with a custom BGM stream armed
    /// (`flag0 != 0 && stream_a != 0 && stream_b != 0`) starts the 500 ms stream fade.
    pub fn arm_stream_fade_on_game_over(&mut self) {
        let e = self.btl_extras;
        if e.flag0 != 0 && e.stream_a != 0 && e.stream_b != 0 {
            self.stream_fade.arm();
        }
    }
    // US: 0x003eeb10 GetDiscNo is `FileIOLib` state, see [`crate::fileio::DiscIdentity::disc_no`].

    /// US `SSHSys::GetFullPathName` (0x003edc40): same as [`SshSys::get_full_path_name`] but the language directory
    /// index comes from the MENU section (`menu_language`).
    pub fn get_full_path_name_us(&self, name: &str, exists: impl Fn(&str) -> bool) -> String {
        let p = name.to_string();
        if exists(&p) {
            return p;
        }
        add_local_path(&p, self.menu_language as usize).unwrap_or(p)
    }

    // JP: 0x003b6c20 StartBattle__6SSHSysFP12_SysBtlParamPCc
    /// Two-step API: `start_battle(Some(param), name)` arms (request 0x20, optional field name for the return trip);
    /// `start_battle(None, name)` while armed fires it (request 0x21).
    pub fn start_battle(&mut self, param: Option<SysBtlParam>, field: Option<&str>) {
        match param {
            None => {
                if self.request == req::BATTLE_ARMED {
                    self.request += 1;
                }
            }
            Some(p) => {
                self.btl = p;
                self.request = req::BATTLE_ARMED;
                self.field_name.clear();
            }
        }
        if let Some(f) = field {
            if !f.is_empty() {
                self.field_name = f.to_string();
            }
        }
        if self.pending.is_none() && self.current.is_none() {
            // original does nothing else; (compat: old skeleton switched immediately)
        }
    }

    // JP: 0x003b6d90 cbBattleA__6SSHSysFii  (BtlSocket callback)
    /// `code == 0`: battle finished with `outcome = BtlSocket+0x16c & 3`; `code == 1`: request `FieldPreLoad(fieldName)`.
    /// Returns an optional action for pre-load.
    pub fn cb_battle(&mut self, code: i32, outcome_bits: u8) -> Option<SysAction> {
        match code {
            0 => {
                self.btl_result[0] = 2;
                match outcome_bits & 3 {
                    2 | 3 => {
                        self.btl_result[1] = 0xff;
                        self.request = req::FIELD; // + SetChrPosSaveState(2)
                    }
                    1 => {
                        self.btl_result[1] = 0;
                        if self.btl_result[2] == 0 {
                            self.request = req::GAME_OVER; // + FieldPreLoadCancel()
                        } else {
                            self.request = req::FIELD; // + SetChrPosSaveState(2)
                        }
                    }
                    _ => {
                        self.btl_result[1] = 1;
                        self.request = req::FIELD; // + SetChrPosSaveState(2)
                    }
                }
                self.btl_result[2] = 0;
                None
            }
            1 => Some(SysAction::StartField(self.field_name.clone())), // FieldPreLoad(name)
            _ => None,
        }
    }

    // JP: 0x003b6f20 InvokeGameOver__6SSHSysFv
    pub fn invoke_game_over(&mut self) {
        self.request = req::GAME_OVER;
        // compat with the first skeleton
        if self.pending.is_none() {
            self.scene_request = None;
        }
    }

    // JP: 0x003b6850 SetPauseTmr__6SSHSysFi   returns the old reload value; -2 => 500; <= 0 ignored
    pub fn set_pause_tmr(&mut self, ms: i32) -> i32 {
        let old = self.pause_reload;
        let ms = if ms == -2 { 500 } else { ms };
        if ms > 0 {
            self.pause_reload = ms;
            self.pause_timer = ms;
        }
        old
    }

    // JP: 0x004a4d00 SetPauserType__6SSHSysFi (FIELD.BIN copy): bit6 of flags
    pub fn set_pauser_type(&mut self, lsd: bool) {
        self.flags = (self.flags & !0x40) | ((lsd as u16) << 6);
    }
    pub fn pauser_is_lsd(&self) -> bool {
        self.flags & 0x40 != 0
    }

    // JP: 0x004a83a0 GetFrameDelta__6SSHSysFv
    pub fn get_frame_delta(&self) -> i32 {
        self.frame_delta.as_millis() as i32
    }

    // JP: 0x003b7160 DiskChange / 0x003b71b0 DiskChangeStat / 0x003b7220 DiskChangeRetry
    pub fn disk_change(&mut self) {
        self.fio_busy = true;
    }
    /// 2 = idle, 1 = waiting for the right disc, 3 = disc error (FileIOLib+0x13938 != 0)
    pub fn disk_change_stat(&self, disk_result: i32) -> i32 {
        if !self.fio_busy {
            2
        } else if disk_result == 0 {
            1
        } else {
            3
        }
    }
    pub fn disk_change_done(&mut self) {
        self.fio_busy = false;
    }

    // JP: 0x003b6600 GetFullPathName__6SSHSysFPcPc
    /// `sprintf(buf, "%s%s", pDataPath, name)`; if `SearchFile` fails fall back to the language directory.
    pub fn get_full_path_name(&self, name: &str, exists: impl Fn(&str) -> bool) -> String {
        let p = format!("{}{}", "", name); // pDataPath is the empty string (_6355)
        if exists(&p) {
            return p;
        }
        add_local_path(&p, self.language as usize).unwrap_or(p)
    }
}

#[cfg(feature = "bevy")]
pub struct SshSysPlugin;
#[cfg(feature = "bevy")]
impl bevy::prelude::Plugin for SshSysPlugin {
    fn build(&self, app: &mut bevy::prelude::App) {
        app.init_resource::<SshSys>();
    }
}

/// Boot modules (SSHMain): `sceSifRebootIop("IOPRP271.IMG")` (the path prefix depends on region: JPN/USA/GBR),
/// then `SSHLoadModules` for two lists.  Mode word semantics in the list: values 0..=3 select the loader for the
/// following names (1 = `sceSifLoadModule(path,0,0)`, 2 = `sceSifLoadStartModule`, 3 = `sceSifLoadModule` with an argument
/// string), 0 terminates, anything larger is a string pointer.
pub const IOP_MODULES_PASS1: [&str; 4] = ["SIO2MAN.IRX", "MCMAN.IRX", "MCSERV.IRX", "PADMAN.IRX"];
pub const IOP_MODULES_PASS2: [&str; 4] = ["IOPUTY.IRX", "FIO.IRX", "LIBSD.IRX", "SDRV_IOP.IRX"];

#[cfg(test)]
mod tests {
    use super::*;

    struct Slow(u32, SshApi);
    impl SshApiObj for Slow {
        fn kind(&self) -> SshApi {
            self.1
        }
        fn pre_load(&mut self) -> bool {
            if self.0 == 0 {
                true
            } else {
                self.0 -= 1;
                false
            }
        }
    }

    #[test]
    fn handover_waits_for_preload() {
        let mut s = SshSys::default();
        assert!(s.set_api_obj(Box::new(Slow(2, SshApi::DummyStage))));
        assert!(!s.set_api(SshApi::FieldSocket)); // refused while one is pending
        s.polling(Duration::from_millis(16));
        s.polling(Duration::from_millis(16));
        assert!(s.take_request().is_none());
        s.polling(Duration::from_millis(16));
        assert_eq!(s.take_request(), Some(SceneRequest::Title));
        // now replace: current must close first
        assert!(s.set_api(SshApi::FieldSocket));
        assert_eq!(s.current_state, 3);
        s.polling(Duration::from_millis(16));
        assert_eq!(s.take_request(), Some(SceneRequest::Field));
    }

    #[test]
    fn battle_cycle() {
        let mut s = SshSys::default();
        s.start_battle(Some(SysBtlParam { pc_count: 3, ..Default::default() }), Some("map01"));
        s.polling(Duration::from_millis(16));
        assert!(s.take_actions().is_empty()); // armed only
        s.start_battle(None, None);
        s.polling(Duration::from_millis(16));
        assert!(matches!(s.take_actions()[..], [SysAction::StartBattle(_)]));
        // defeat without the "no game over" flag
        s.cb_battle(0, 1);
        s.polling(Duration::from_millis(16));
        assert_eq!(s.take_actions(), vec![SysAction::StartGameOver]);
    }

    #[test]
    fn retail_title_request_and_residents() {
        let mut s = SshSys { retail: true, ..Default::default() };
        s.btl_result[0] = 2;
        s.request_title();
        s.polling(Duration::from_millis(16));
        assert!(s.take_residents_release());
        assert!(!s.take_residents_release());
        assert_eq!(s.btl_result[0], 0);
        s.polling(Duration::from_millis(16));
        assert_eq!(s.take_request(), Some(SceneRequest::Title));
        // game over also releases the residents in the retail build
        s.cb_battle(0, 1);
        s.polling(Duration::from_millis(16));
        assert!(s.take_residents_release());
        assert_eq!(s.take_actions(), vec![SysAction::StartGameOver]);
        // JP flavour leaves them alone
        let mut j = SshSys::default();
        j.cb_battle(0, 1);
        j.polling(Duration::from_millis(16));
        assert!(!j.take_residents_release());
    }

    #[test]
    fn stream_fade_runs_500ms_then_closes() {
        let mut f = StreamFade::default();
        assert_eq!(f.step(0, 7, |_| true), None);
        f.arm();
        assert_eq!(f.step(1000, 7, |_| true), Some(StreamCmd::FadeOut { handle: 7, ms: 500 }));
        assert_eq!(f.step(1200, 7, |_| true), None);
        assert_eq!(f.step(1500, 7, |_| true), None); // reached 500 ms -> state 3
        assert_eq!(f.step(1516, 7, |_| false), Some(StreamCmd::Close { handle: 7 }));
        assert_eq!(f.state, 3);
        assert_eq!(f.step(1532, 7, |_| true), Some(StreamCmd::Close { handle: 7 }));
        assert_eq!(f.state, 0);
        let mut s = SshSys::default();
        s.set_battle_flags(1, 0, 0);
        s.set_battle_bgm_stream(3, 4);
        s.arm_stream_fade_on_game_over();
        assert_eq!(s.stream_fade.state, 1);
    }

    #[test]
    fn us_battle_param_is_one_slot_wider() {
        let us = SysBtlParamUs { regdat_id: 5, pc_count: 3, pc: [1, 2, 3, 0xff, 9], ..Default::default() };
        let jp: SysBtlParam = us.into();
        assert_eq!(jp.pc, [1, 2, 3, 0xff]);
        assert_eq!(SysBtlParamUs::from(jp).pc[4], 0xff);
    }

    #[test]
    fn us_path_uses_menu_language() {
        let s = SshSys { menu_language: 2, ..Default::default() };
        assert_eq!(s.get_full_path_name_us("common/sshmes.na", |_| true), "common/sshmes.na");
        assert_eq!(s.get_full_path_name_us("common/x.dat", |_| false), "common/USA/x.dat");
    }
}

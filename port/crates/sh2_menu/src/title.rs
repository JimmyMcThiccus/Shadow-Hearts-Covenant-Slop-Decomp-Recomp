//! Title / opening flow: `openingMessage` (the title screen driver) and `openingBattleDemo`
//! (the attract-mode battle), plus the data tables they use.
//!
//! JP: `openingMessage` 0x003a83f0..0x003ab500 (`Polling` = a `switch(state)` at +0xe0),
//! `openingBattleDemo` 0x003ab510..0x003abd40, `opening()` 0x003a7ea0 (creates the object and
//! `SSHSys::SetAPI(new CDMYStage)`; section A owns `CDMYStage`).
//!
//! The JP *demo* (Furokuban) title is a trial version: splash ("TRIAL" texture 0x14), opening movie
//! `OPENING/DEMO.LSD`, a title with logo + "press start" pulse, then a two item menu
//! (ゲームを始める / 振動設定) and attract-mode battles. State numbers are the original ones.
//!
//! The retail (US) flow lives in [`retail`] behind [`Build::Retail`]: boot device check, fiction disclaimer, opening movie,
//! PRESS START, a five slot menu (New Game / Continue / Options / Installation / Theater) and six attract battles, driven by
//! the `OPENING.BIN` overlay (see `notes/I/opening.md`).  It has its own command/input types so `plugin.rs` keeps compiling.

use crate::scene::pad;

/// Pad bits that count as "press start" on the title (`uVar1 & 0x2008` = CIRCLE | START).
pub const ANY_KEY: u16 = pad::CIRCLE | pad::START;

// ----- states (openingMessage+0xe0) ---------------------------------------------------------
pub const S_DEV_CHECK: u32 = 0x00;
pub const S_DEV_WAIT_CB: u32 = 0x01;
pub const S_DEV_WAIT_END: u32 = 0x03;
pub const S_MOVIE_START: u32 = 0x0a;
pub const S_MOVIE_PLAY: u32 = 0x0b;
pub const S_MOVIE_FADE: u32 = 0x0c;
pub const S_TITLE_SETUP: u32 = 0x10;
pub const S_TITLE_WAIT: u32 = 0x11;
pub const S_MENU: u32 = 0x12;
pub const S_LEAVE: u32 = 0x13;
pub const S_INSTALL: u32 = 0x14;
pub const S_LOAD_START: u32 = 0x15;
pub const S_LOAD_WAIT: u32 = 0x16;
pub const S_LOAD_BACK: u32 = 0x17;
pub const S_VIB_SETUP: u32 = 0x18;
pub const S_VIB_MENU: u32 = 0x19;
pub const S_TRIAL_SPLASH: u32 = 0x1a;
pub const S_TRIAL_WAIT: u32 = 0x1b;
pub const S_TRIAL_FADE: u32 = 0x1c;
pub const S_CM_START: u32 = 0x1d;
pub const S_CM_PLAY: u32 = 0x1e;
pub const S_CM_FADE: u32 = 0x1f;
pub const S_SUBMENU_SETUP: u32 = 0x20;
pub const S_SUBMENU_WAIT: u32 = 0x21;
pub const S_SUBMENU_FADE: u32 = 0x22;
pub const S_DEMO_START: u32 = 0x23;
pub const S_DEMO_RUN: u32 = 0x24;
pub const S_DEMO_END: u32 = 0x25;
pub const S_GAME_START: u32 = 0x26;
pub const S_DONE: u32 = 0x27;

/// Idle frames on the title before the attract battle starts (`0x4b1` => 1201 frames).
pub const TITLE_IDLE_FRAMES: u32 = 0x4b0;
/// Idle frames on the menu before the attract battle (`0xe10` = 3600).
pub const MENU_IDLE_FRAMES: u32 = 0xe10;
/// Frames the trial splash is shown (`0x1c2` = 450).
pub const SPLASH_FRAMES: u32 = 0x1c2;

/// Movie paths (rodata 0x401370..0x4013b8).
pub const MOVIE_OPENING: &str = "opening/demo.lsd";
pub const MOVIE_CM_A: &str = "lsd/cm_a.lsd";
pub const MOVIE_CM_B: &str = "lsd/cm_b.lsd";
pub const MOVIE_PV: &str = "lsd/pv.lsd";
pub const TITLE_BGM: &str = "OPENING/BGM803.SSV";
/// First field map entered by "start game".
pub const FIRST_MAP: &str = "WORLDMAP";

#[derive(Clone, Debug, PartialEq)]
pub enum TitleCmd {
    /// create + start the initial device check (`dataAccess` mode 2)
    StartDeviceCheck,
    /// `changeDispMode(w, h)`: switch the GS display buffer (0x280x1c0 = 640x448 movie/title, 0x200x1c0 = 512x448 menus)
    DispMode(u32, u32),
    FadeIn(u32),
    FadeOut(u32),
    /// set the fader polygon colour (r,g,b,a)
    FaderColor(u8, u8, u8, u8),
    PlayMovie(&'static str),
    PauseExitMovie,
    SetupTitleWindow,
    ReleaseTitleWindow,
    SetupTrialSplash,
    ReleaseTrialSplash,
    SetupMainMenu,
    ReleaseMainMenu,
    SetupVibrationMenu,
    ReleaseVibrationMenu,
    /// "press start" pulse alpha (polygon 4 of the title window)
    PulseAlpha(u32),
    Se(u32),
    StopMusic,
    PlayMusic(&'static str),
    /// start the attract-mode battle (`openingBattleDemo::initialize/start`)
    StartBattleDemo(DemoBattle),
    StartLoadScreen,
    /// `SaveMenuSection` option bits0-1 (vibration mode) = value; then `UpdateVibration`
    SetVibration(u8),
    /// `GetWorldMapInfo` cleared + `FieldMapJump(map, 0)`
    StartNewGame(&'static str),
    /// continue from a loaded save (`FieldMapJump(GetSavedMpsName(0), -2)` is done by dataAccess)
    EnterLoadedGame,
    /// the title object destroys itself (state 0x27 -> 0x28)
    Finish,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct TitleInputs {
    /// pad trigger bits (`CPad` core +0x6c)
    pub trigger: u16,
    /// menu-navigation bits including d-pad repeat (`uVar2`)
    pub nav: u16,
    /// `fader+0x102`: true when the black cover has been fully removed
    pub fader_clear: bool,
    pub fading: bool,
    /// `LSDPlayer::Reset()` returned non-zero (player idle/ready for a new stream)
    pub lsd_idle: bool,
    /// `m_bLSDStart`: the stream began playing
    pub lsd_started: bool,
    /// `dataAccess` callback event (`openingMessage+0xf0`)
    pub cb_event: Option<u32>,
    /// currently highlighted menu row (`menuCheckKey` result), `menu_ready` = menu fade finished
    pub menu_sel: usize,
    pub menu_ready: bool,
    /// attract-mode battle: `+0x23` started / `+0x21` "ended without skip" flags
    pub demo_started: bool,
    pub demo_not_skipped: bool,
    /// `m_MenuNum == 2`
    pub submenu_ready: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct DemoBattle {
    pub monster_set: i32,
    pub scenario: i32,
    pub battle: i32,
    pub bgm: i32,
    pub party: [i8; 4],
}

/// JP: `openingBattleDemo::initialize` stack table (rodata 0x003fa550), cycled with `m_mons`.
pub const DEMO_BATTLES: [DemoBattle; 3] = [
    DemoBattle { monster_set: 3, scenario: 0, battle: 0x4d, bgm: 0x191, party: [5, 0xb, -1, -1] },
    DemoBattle { monster_set: 8, scenario: 1, battle: 6, bgm: 0x191, party: [0, 1, 2, -1] },
    DemoBattle { monster_set: 0x14, scenario: 2, battle: 0x1c, bgm: 0x191, party: [0, 1, 5, 6] },
];

pub struct OpeningMessage {
    pub state: u32,
    pub next_state: u32,
    /// +0xec frame counter
    pub timer: u32,
    /// +0xc4 pulse counter
    pub pulse: u32,
    /// +0x78 menu selection
    pub sel: usize,
    /// DAT_0040ad44: the splash has been shown once this boot
    pub splash_shown: bool,
    /// DAT_0040ad42: a save was found by the device check
    pub save_found: bool,
    /// m_mons: next attract battle index
    pub demo_index: usize,
    pub disp: (u32, u32),
}

impl OpeningMessage {
    /// JP: 0x003a8670 initialize — first boot shows the trial splash (0x1a), later returns go to the title (0x10).
    pub fn new(splash_shown_before: bool) -> Self {
        OpeningMessage {
            state: if splash_shown_before { S_TITLE_SETUP } else { S_TRIAL_SPLASH },
            next_state: 0,
            timer: 0,
            pulse: 0,
            sel: 0,
            splash_shown: true,
            save_found: false,
            demo_index: 0,
            disp: (0x200, 0x1c0),
        }
    }

    fn disp_mode(&mut self, w: u32, h: u32, out: &mut Vec<TitleCmd>) {
        if self.disp != (w, h) {
            self.disp = (w, h);
            out.push(TitleCmd::DispMode(w, h));
        }
    }

    fn begin_demo(&mut self, out: &mut Vec<TitleCmd>) {
        out.push(TitleCmd::FaderColor(0, 0, 0, 0x80));
        out.push(TitleCmd::FadeIn(0x20));
        self.state = S_LEAVE;
        self.next_state = S_DEMO_START;
        let d = DEMO_BATTLES[self.demo_index % 3];
        self.demo_index = (self.demo_index + 1) % 3;
        out.push(TitleCmd::StartBattleDemo(d));
    }

    /// JP: 0x003a8a60 Polling
    pub fn poll(&mut self, i: &TitleInputs) -> Vec<TitleCmd> {
        let mut out = Vec::new();
        let any = i.trigger & ANY_KEY != 0;
        match self.state {
            S_DEV_CHECK => {
                out.push(TitleCmd::StartDeviceCheck);
                out.push(TitleCmd::FadeOut(1));
                self.state = S_DEV_WAIT_CB;
            }
            S_DEV_WAIT_CB => match i.cb_event {
                Some(6) => self.disp_mode(0x200, 0x1c0, &mut out),
                Some(3) => {
                    self.save_found = true;
                    self.state = S_DEV_WAIT_END;
                }
                Some(2) => self.state = S_DEV_WAIT_END,
                _ => {}
            },
            S_DEV_WAIT_END => {
                if i.cb_event == Some(4) {
                    self.state = 7;
                    out.push(TitleCmd::FadeIn(1));
                }
            }
            S_MOVIE_START => {
                self.disp_mode(0x280, 0x1c0, &mut out);
                if i.lsd_idle {
                    out.push(TitleCmd::PlayMovie(MOVIE_OPENING));
                    self.state = S_MOVIE_PLAY;
                }
            }
            S_MOVIE_PLAY => {
                if i.lsd_started {
                    if !any {
                        if i.lsd_idle {
                            self.movie_done(&mut out);
                        }
                    } else {
                        out.push(TitleCmd::PauseExitMovie);
                        self.movie_done(&mut out);
                    }
                }
            }
            S_MOVIE_FADE => {
                if !i.fading {
                    self.state = S_TITLE_SETUP;
                }
            }
            S_TITLE_SETUP => {
                if !i.fader_clear {
                    if !i.fading {
                        self.disp_mode(0x280, 0x1c0, &mut out);
                        out.push(TitleCmd::SetupTitleWindow);
                        out.push(TitleCmd::PlayMusic(TITLE_BGM));
                        out.push(TitleCmd::FadeOut(0x20));
                    }
                } else {
                    self.timer = 0;
                    self.state = S_TITLE_WAIT;
                }
            }
            S_TITLE_WAIT => {
                self.timer += 1;
                if self.timer < TITLE_IDLE_FRAMES + 1 {
                    if !any {
                        self.pulse += 1;
                        if self.pulse < 0x40 {
                            out.push(TitleCmd::PulseAlpha(self.pulse * 2));
                        } else if self.pulse < 0x80 {
                            out.push(TitleCmd::PulseAlpha(((self.pulse as i32 - 0x40) * -2 + 0x80) as u32));
                        } else {
                            self.pulse = 0;
                        }
                    } else {
                        out.push(TitleCmd::Se(2));
                        out.push(TitleCmd::StopMusic);
                        out.push(TitleCmd::PulseAlpha(0));
                        out.push(TitleCmd::SetupMainMenu);
                        self.timer = 0;
                        self.state = S_MENU;
                    }
                } else {
                    out.push(TitleCmd::StopMusic);
                    self.begin_demo(&mut out);
                }
            }
            S_MENU => {
                if i.menu_ready {
                    if i.trigger & pad::CIRCLE != 0 {
                        out.push(TitleCmd::Se(2));
                        self.sel = i.menu_sel;
                        if self.sel == 0 {
                            out.push(TitleCmd::FaderColor(0, 0, 0, 0x80));
                            out.push(TitleCmd::FadeIn(0x20));
                            self.state = S_LEAVE;
                            self.next_state = S_GAME_START;
                        } else {
                            out.push(TitleCmd::ReleaseMainMenu);
                            self.state = S_VIB_SETUP;
                        }
                    } else if i.nav != 0 {
                        self.timer = 0;
                    }
                    if self.state == S_MENU {
                        self.timer += 1;
                        if self.timer > MENU_IDLE_FRAMES {
                            self.begin_demo(&mut out);
                        }
                    }
                }
            }
            S_LEAVE => {
                if !i.fading {
                    out.push(TitleCmd::ReleaseTitleWindow);
                    out.push(TitleCmd::ReleaseMainMenu);
                    self.state = self.next_state;
                }
            }
            S_LOAD_START => {
                self.disp_mode(0x200, 0x1c0, &mut out);
                out.push(TitleCmd::StartLoadScreen);
                out.push(TitleCmd::FadeOut(1));
                self.state = S_LOAD_WAIT;
            }
            S_LOAD_WAIT => match i.cb_event {
                Some(3) => self.state = S_LOAD_BACK,
                Some(5) => {
                    out.push(TitleCmd::EnterLoadedGame);
                    self.state = S_DONE;
                }
                _ => {}
            },
            S_LOAD_BACK => {
                if i.cb_event == Some(4) {
                    out.push(TitleCmd::FadeIn(1));
                    self.state = S_TITLE_SETUP;
                }
            }
            S_VIB_SETUP => {
                out.push(TitleCmd::SetupVibrationMenu);
                self.state = S_VIB_MENU;
            }
            S_VIB_MENU => {
                if i.trigger & pad::CIRCLE != 0 {
                    out.push(TitleCmd::Se(2));
                    // row 0 = ON -> mode 0, row 1 = OFF -> mode 2
                    out.push(TitleCmd::SetVibration(if i.menu_sel == 0 { 0 } else { 2 }));
                    out.push(TitleCmd::ReleaseVibrationMenu);
                    out.push(TitleCmd::SetupMainMenu);
                    self.state = S_MENU;
                } else if i.trigger & pad::CROSS != 0 {
                    out.push(TitleCmd::Se(3));
                    out.push(TitleCmd::ReleaseVibrationMenu);
                    out.push(TitleCmd::SetupMainMenu);
                    self.state = S_MENU;
                }
            }
            S_TRIAL_SPLASH => {
                if !i.fader_clear {
                    if !i.fading {
                        self.disp_mode(0x280, 0x1c0, &mut out);
                        out.push(TitleCmd::SetupTrialSplash);
                        out.push(TitleCmd::FadeOut(0x20));
                    }
                } else {
                    self.timer = 0;
                    self.state = S_TRIAL_WAIT;
                }
            }
            S_TRIAL_WAIT => {
                self.timer += 1;
                if self.timer > SPLASH_FRAMES || any {
                    out.push(TitleCmd::FadeIn(0x20));
                    self.state = S_TRIAL_FADE;
                }
            }
            S_TRIAL_FADE => {
                if !i.fading {
                    out.push(TitleCmd::ReleaseTrialSplash);
                    out.push(TitleCmd::FadeOut(1));
                    self.state = S_MOVIE_START;
                }
            }
            S_CM_START => {
                out.push(TitleCmd::FadeOut(1));
                self.disp_mode(0x280, 0x1c0, &mut out);
                if i.lsd_idle {
                    out.push(TitleCmd::PlayMovie(match self.sel {
                        2 => MOVIE_PV,
                        1 => MOVIE_CM_B,
                        _ => MOVIE_CM_A,
                    }));
                    self.state = S_CM_PLAY;
                }
            }
            S_CM_PLAY => {
                if i.lsd_started {
                    if !any {
                        if i.lsd_idle {
                            self.state = S_CM_FADE;
                            out.push(TitleCmd::FadeIn(8));
                        }
                    } else {
                        out.push(TitleCmd::PauseExitMovie);
                        self.state = S_CM_FADE;
                        out.push(TitleCmd::FadeIn(8));
                    }
                }
            }
            S_CM_FADE => {
                if !i.fading {
                    out.push(TitleCmd::FaderColor(0xff, 0xff, 0xff, 0x80));
                    self.state = S_TITLE_SETUP;
                }
            }
            S_SUBMENU_SETUP => {
                if !i.fader_clear {
                    if !i.fading {
                        self.disp_mode(0x200, 0x1c0, &mut out);
                        out.push(TitleCmd::FadeOut(0x20));
                    }
                } else {
                    self.state = S_SUBMENU_WAIT;
                }
            }
            S_SUBMENU_WAIT => {
                if i.submenu_ready {
                    self.state = S_SUBMENU_FADE;
                    out.push(TitleCmd::FadeIn(0x20));
                }
            }
            S_SUBMENU_FADE => {
                if !i.fading {
                    self.state = S_TITLE_SETUP;
                }
            }
            S_DEMO_START => {
                out.push(TitleCmd::FadeOut(1));
                self.disp_mode(0x200, 0x1c0, &mut out);
                self.timer = 0;
                self.state = S_DEMO_RUN;
            }
            S_DEMO_RUN => {
                if i.demo_started {
                    self.state = S_DEMO_END;
                }
            }
            S_DEMO_END => {
                // the demo object clears its `not_skipped` flag when a key ended it early
                self.state = if i.demo_not_skipped { S_MOVIE_START } else { S_TITLE_SETUP };
                if self.state != S_MOVIE_START {
                    out.push(TitleCmd::FadeOut(1));
                }
            }
            S_GAME_START => {
                out.push(TitleCmd::StartNewGame(FIRST_MAP));
                out.push(TitleCmd::FadeOut(1));
                self.disp_mode(0x200, 0x1c0, &mut out);
                self.state = S_DONE;
            }
            S_DONE => {
                out.push(TitleCmd::Finish);
                self.state = 0x28;
            }
            _ => {}
        }
        out
    }

    fn movie_done(&mut self, out: &mut Vec<TitleCmd>) {
        self.state = S_MOVIE_FADE;
        out.push(TitleCmd::FaderColor(0xff, 0xff, 0xff, 0x80));
        out.push(TitleCmd::FadeIn(8));
    }
}

// ----------------------------------------------------------------------------------------------------
// openingBattleDemo
// ----------------------------------------------------------------------------------------------------

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum DemoState {
    /// 0: waiting for `start()`
    Idle,
    /// 1: init the battle socket
    Init,
    /// 2: battle running
    Running,
    /// 3: battle ending (fade out), waits for the battle to confirm completion
    Ending,
    /// 4: finished (`finished` flag set)
    Finished,
}

#[derive(Clone, Debug, PartialEq)]
pub enum DemoCmd {
    ShowBanner,
    /// `InitBtlSocket`, set callbacks, `SetPC(party)`, `SetMonsterSet(RegDat 0x2f[monset])`, BGM
    InitBattle(DemoBattle),
    FadeOut(u32),
    BattleEnd,
    ReleaseBanner,
}

pub struct OpeningBattleDemo {
    pub state: DemoState,
    pub timer: u32,
    /// +0x22
    pub go: bool,
    /// +0x23
    pub finished: bool,
    /// +0x21: still 1 unless a key cut the demo short
    pub not_skipped: bool,
    /// +0x20, set by the battle callback with event 0
    pub battle_done: bool,
    pub battle: DemoBattle,
}

impl OpeningBattleDemo {
    pub fn new(b: DemoBattle) -> Self {
        OpeningBattleDemo { state: DemoState::Idle, timer: 0, go: false, finished: false, not_skipped: true, battle_done: false, battle: b }
    }
    pub fn start(&mut self) {
        self.go = true;
    }
    /// JP: 0x003ab800 Polling. `key` = any of CIRCLE/START, `fader_mode_ended` = `BtlFader::GetFaderMode()==3`.
    pub fn poll(&mut self, key: bool, fader_mode_ended: bool) -> Vec<DemoCmd> {
        let mut out = Vec::new();
        match self.state {
            DemoState::Idle if self.go => {
                out.push(DemoCmd::ShowBanner);
                out.push(DemoCmd::InitBattle(self.battle));
                self.state = DemoState::Running;
                self.timer = 0;
            }
            DemoState::Running => {
                self.timer += 1;
                if self.timer > 300 && key {
                    self.not_skipped = false;
                    self.timer = 0x708;
                }
                if (self.timer < 0x708 && fader_mode_ended) || self.timer >= 0x708 {
                    out.push(DemoCmd::FadeOut(0x20));
                    self.state = DemoState::Ending;
                }
            }
            DemoState::Ending => {
                out.push(DemoCmd::BattleEnd);
                if self.battle_done {
                    out.push(DemoCmd::ReleaseBanner);
                    self.timer = 0;
                    self.state = DemoState::Finished;
                }
            }
            DemoState::Finished => self.finished = true,
            _ => {}
        }
        out
    }
}

// ====================================================================================================
// Retail (US, Jul 2004) title flow -- OPENING.BIN overlay + CDMYStage / openingBattleDemo in SLUS_210.41
// ====================================================================================================
//
// The retail build moved `openingMessage` into the new `OPENING.BIN` overlay (group 3, load 0x0045ea80,
// functions 0x0045eb00..0x0046c6b8, see `notes/I/opening.md`).  The state machine below is a 1:1 port of
// `openingMessage::Polling` (US 0x0045f340, state word at +0x100) and of the pieces of `CDMYStage`
// (0x00415c50..0x00416500) and `openingBattleDemo` (0x00416510..0x00416ed0) that are main-image code.
// It is kept in a separate module with its own command/input types so the JP-demo types (and the
// exhaustive `match`es over `TitleCmd` in `plugin.rs`) are untouched.

/// Which executable the title flow is modelled after.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum Build {
    /// Furokuban demo `SLPM_602.19` (`openingMessage` in the main image; two-row menu; trial splash).
    #[default]
    JpDemo,
    /// US retail `SLUS_210.41` + `OPENING.BIN`.
    Retail,
}

/// Either build's title state machine behind one handle (`Build::Retail` selects the OPENING.BIN flow).
pub enum Machine {
    Jp(OpeningMessage),
    Retail(retail::OpeningMessage),
}

impl Machine {
    /// `splash_shown` is `DAT_0040ad44` (JP); for the retail build the equivalent is `TitleShared::intro_done`.
    pub fn new(build: Build, splash_shown: bool) -> Self {
        match build {
            Build::JpDemo => Machine::Jp(OpeningMessage::new(splash_shown)),
            Build::Retail => {
                let shared = retail::TitleShared { intro_done: splash_shown, ..Default::default() };
                Machine::Retail(retail::OpeningMessage::new(shared, None))
            }
        }
    }
    pub fn build(&self) -> Build {
        match self {
            Machine::Jp(_) => Build::JpDemo,
            Machine::Retail(_) => Build::Retail,
        }
    }
}

pub mod retail {
    use crate::scene::pad;

    // ----- openingMessage states (+0x100) -------------------------------------------------------
    /// 0x00: wait for `RegDatApi::CheckRegDat() && JRing::DataLoadEndCheck()`
    pub const S_WAIT_DATA: u32 = 0x00;
    /// 0x01: create the boot `dataAccess` (mode 2, initial device check) and reveal
    pub const S_DEVCHK_START: u32 = 0x01;
    /// 0x02: wait for the device-check events (6 = needs 512x448 UI, 3 = save found, 2 = nothing usable)
    pub const S_DEVCHK_WAIT: u32 = 0x02;
    /// 0x04: wait for event 4 (UI finished), then cover and show the disclaimer
    pub const S_DEVCHK_END: u32 = 0x04;
    /// 0x05: disclaimer screen ("This story is a work of fiction ...", opening.dat #0)
    pub const S_DISCLAIMER: u32 = 0x05;
    /// 0x06: hold 450 frames or until O/START
    pub const S_DISCLAIMER_WAIT: u32 = 0x06;
    /// 0x07: wait for the cover, release the disclaimer
    pub const S_DISCLAIMER_FADE: u32 = 0x07;
    /// 0x0b: start `opening/demo.lsd`
    pub const S_MOVIE_START: u32 = 0x0b;
    pub const S_MOVIE_PLAY: u32 = 0x0c;
    pub const S_MOVIE_FADE: u32 = 0x0d;
    pub const S_MOVIE_END: u32 = 0x0e;
    /// 0x12: build the title screen (logo, swirls, BGM803)
    pub const S_TITLE_SETUP: u32 = 0x12;
    /// 0x13: PRESS START
    pub const S_PRESS_START: u32 = 0x13;
    /// 0x14: menu (New Game / Continue / Options / Installation / Theater)
    pub const S_MENU: u32 = 0x14;
    /// 0x15: cover finished -> release title + menu, go to `next_state`
    pub const S_LEAVE: u32 = 0x15;
    /// 0x16: HDD install start (dead code in retail: `install` is never created)
    pub const S_INSTALL: u32 = 0x16;
    /// 0x17: Continue -> load screen
    pub const S_LOAD_START: u32 = 0x17;
    pub const S_LOAD_WAIT: u32 = 0x18;
    pub const S_LOAD_BACK: u32 = 0x19;
    /// 0x1d..0x1f: Options menu
    pub const S_OPTIONS_START: u32 = 0x1d;
    pub const S_OPTIONS_WAIT: u32 = 0x1e;
    pub const S_OPTIONS_FADE: u32 = 0x1f;
    /// 0x20..0x22: generic exit used by the Theater row (owner event 3 is raised in the menu)
    pub const S_EXIT_REVEAL: u32 = 0x20;
    pub const S_EXIT_WAIT: u32 = 0x21;
    pub const S_EXIT_BACK: u32 = 0x22;
    /// 0x23/0x24: attract battle (the object ends; `CDMYStage` runs the battle)
    pub const S_ATTRACT: u32 = 0x23;
    pub const S_ATTRACT_WAIT: u32 = 0x24;
    /// 0x26: New Game -> `FieldMapJump("OP_00_U", 0)`
    pub const S_NEW_GAME: u32 = 0x26;
    pub const S_DONE: u32 = 0x27;
    /// 0x28: terminal (`Finish`)
    pub const S_TERMINAL: u32 = 0x28;

    pub const ANY_KEY: u16 = pad::CIRCLE | pad::START;
    /// frames the disclaimer stays (0x1c2 = 450)
    pub const DISCLAIMER_FRAMES: u32 = 0x1c2;
    /// idle frames on PRESS START before the attract battle (`timer < 0x4b1` => 1201 frames)
    pub const PRESS_START_IDLE: u32 = 0x4b0;
    /// idle frames on the menu before the attract battle
    pub const MENU_IDLE: u32 = 0xe10;
    pub const MOVIE_OPENING: &str = "opening/demo.lsd";
    pub const TITLE_BGM: &str = "OPENING/BGM803.SSV";
    /// `FieldMapJump("OP_00_U", 0)` -- the JP demo used "WORLDMAP"
    pub const NEW_GAME_MAP: &str = "OP_00_U";
    pub const DISPLAY_W_MOVIE: u32 = 0x280;
    pub const DISPLAY_W_UI: u32 = 0x200;
    pub const DISPLAY_H: u32 = 0x1c0;

    /// Menu rows in `openingMessage+0xd8` order.  Textures: opening.dat #7/#8/#9 (disabled / normal / selected) rows of 32 px.
    #[derive(Clone, Copy, Debug, PartialEq, Eq)]
    pub enum Row {
        NewGame = 0,
        Continue = 1,
        Options = 2,
        Installation = 3,
        Theater = 4,
    }

    impl Row {
        pub fn from_index(i: usize) -> Row {
            match i {
                0 => Row::NewGame,
                1 => Row::Continue,
                2 => Row::Options,
                3 => Row::Installation,
                _ => Row::Theater,
            }
        }
        /// Screen position of the row sprite (table @0x0046c720, used by `mSetupMenuWin`).
        pub const POSITIONS: [(i32, i32); 5] = [(108, 264), (268, 296), (406, 264), (108, 324), (406, 324)];
    }

    /// The in-RAM image kept at `0x0045e940` (`GetTitleShared()`): the 0x100-byte *system common block* (EE 0x100000)
    /// merged from every device's system file, plus the title flags that follow it.
    #[derive(Clone, Debug, PartialEq, Eq)]
    pub struct TitleShared {
        /// +0x00..+0x100.  [0],[1],[2..0x42) flags1,[0x42..0x82) flags2,[0x82],[0x83],u32@0x84 (newest timestamp),u32@0x88,rest
        pub common: [u8; 0x100],
        /// +0x100: `common` has been OR-ed with the live block once (`CDMYStage::Start`)
        pub merged: bool,
        /// +0x101: a usable save was found by the boot device check (default row becomes "Continue")
        pub save_found: bool,
        /// +0x102: the boot intro (device check, disclaimer, opening movie) was already shown since power on
        pub intro_done: bool,
        /// +0x104 (`Get/SetDeviceSaveMask`)
        pub device_save_mask: u32,
    }

    impl Default for TitleShared {
        fn default() -> Self {
            TitleShared { common: [0; 0x100], merged: false, save_found: false, intro_done: false, device_save_mask: 0 }
        }
    }

    impl TitleShared {
        /// `deviceChecker::mCheckSystem/mCheckAll` merge of one device's common block: bytes 0..0x82 OR-ed,
        /// the newest timestamp (u32 @0x84) wins.
        pub fn merge_device(&mut self, block: &[u8; 0x100]) {
            for i in 0..0x82 {
                self.common[i] |= block[i];
            }
            let mine = u32::from_le_bytes(self.common[0x84..0x88].try_into().unwrap());
            let theirs = u32::from_le_bytes(block[0x84..0x88].try_into().unwrap());
            if mine < theirs {
                self.common[0x84..0x88].copy_from_slice(&block[0x84..0x88]);
            }
        }
        /// `CDMYStage::Start`: OR the live block (0x100000) back into the title copy (bytes 0..=0x82 only).
        pub fn merge_live(&mut self, live: &[u8; 0x100]) {
            for i in 0..=0x82 {
                self.common[i] |= live[i];
            }
            self.merged = true;
        }
        /// `Polling` state 0x14 / New Game: the whole block is copied to 0x100000.
        pub fn commit_new_game(&self) -> [u8; 0x100] {
            self.common
        }
        /// `common[1] != 0`: the "Theater" row is selectable.
        pub fn theater_enabled(&self) -> bool {
            self.common[1] != 0
        }
        /// `common[0x14]` bits 6/7: progress bits that unlock more attract battles
        pub fn attract_progress(&self) -> u8 {
            ((self.common[0x14] & 0x40 != 0) as u8) + ((self.common[0x14] & 0x80 != 0) as u8)
        }
    }

    /// Host -> machine inputs for one frame.
    #[derive(Clone, Copy, Debug, Default)]
    pub struct Inputs {
        /// `CPad` core +0x6c (edge triggered buttons)
        pub trigger: u16,
        /// `CPad` core +0x70 (auto-repeat), only the d-pad nibble (0xf0) is used
        pub repeat: u16,
        /// `fader+0x102`: a reveal (original `fadeout`) has finished
        pub fader_clear: bool,
        /// `fader+0x118`: a fade is running
        pub fader_busy: bool,
        /// `RegDatApi::CheckRegDat() && JRing::DataLoadEndCheck()`
        pub regdat_ready: bool,
        /// `LSDPlayer::Reset()` returned non-zero (idle / finished)
        pub lsd_idle: bool,
        /// `g_lsd_started` (LSD_CB ran)
        pub lsd_started: bool,
        /// event delivered by `dataAccess` through `CBEntry` this frame (stored in `+0x110`)
        pub cb_event: Option<u32>,
        /// `g_opening_event == 5`: the Options `Menu` object was destroyed
        pub options_closed: bool,
        /// `(SSHSys+0x3c & 7) != 0` : Installation row available (only used by `SetupMenu`)
        pub install_flag: bool,
    }

    /// Machine -> host commands (the original performs these inline).
    #[derive(Clone, Debug, PartialEq)]
    pub enum Cmd {
        /// `changeDispMode(w, h)`
        DispMode(u32, u32),
        /// original `fadein(n)`: fader to opaque (cover)
        Cover(u32),
        /// original `fadeout(n)`: fader to clear (reveal)
        Reveal(u32),
        /// fader polygon colour
        FaderColor(u8, u8, u8, u8),
        /// create + start the boot `dataAccess` in mode 2 (OPENING.BIN copy), callback = `CBEntry`
        StartDeviceCheck,
        SetupDisclaimer,
        ReleaseDisclaimer,
        /// new `LSDPlayer` + 3x `PlugDevice` + start callback
        SetupLsd,
        StartMovie(&'static str),
        /// `LSDPlayer::Pause` + stop (movie skipped)
        StopMovie,
        /// delete the `LSDPlayer`, `SetFFMode(0,1,1)`
        ReleaseMovie,
        /// 5 title polys + 7 swirls + BGM803 stream
        SetupTitle,
        ReleaseTitle,
        SetupMenu { default_row: usize, install_enabled: bool, theater_enabled: bool },
        ReleaseMenu,
        /// highlight `row` and move the cursor there
        MoveCursor(usize),
        /// PRESS START polygon alpha
        PulseAlpha(u32),
        /// menu SE (0 cursor, 2 confirm, 3 cancel)
        Se(u32),
        /// `primMusic::stop` (0x32 frame fade)
        StopMusic,
        /// delete the primMusic object
        ReleaseMusic,
        /// owner callback event 2: start the attract battle
        OwnerAttract,
        /// owner callback event 3: start the Theater (FIELD.BIN)
        OwnerTheater,
        /// owner callback event 4: object finished, owner forgets it
        OwnerDone,
        /// `memcpy(0x100000, common, 0x100)`; `mInitNewGame`; `InitNewGameFlags(device_save_mask)`
        CommitNewGame,
        /// `FieldMapJump(map, 0)`
        FieldMapJump(&'static str),
        /// new main-image `dataAccess` in load mode (Continue)
        CreateLoadScreen,
        /// `dataAccess::start(STARTMODE 1)`: go straight to the load list
        StartLoadScreen,
        /// new `OptionMenu` (first scene 0x10, callback `cbOpeningEvent`)
        CreateOptions,
        /// options menu start flag (`menu+0x41 = 0x11`)
        StartOptions,
        /// `DelayDelete()`
        DelayDelete,
        /// `SetFFMode(0, 1, n)`
        SetFfMode(u32),
    }

    /// `openingMessage` (retail).  `poll` is `Polling` (0x0045f340).
    pub struct OpeningMessage {
        pub state: u32,
        pub next_state: u32,
        /// +0x10c
        pub timer: u32,
        /// +0xdc
        pub pulse: u32,
        /// +0xd8 confirmed row
        pub sel: usize,
        /// +0xe0 row under the cursor
        pub cur: usize,
        /// +0xe4 / +0xe5: remembered row / column of the 5-slot cursor topology
        pub nav_a: bool,
        pub nav_b: bool,
        /// +0xe6 / +0xe7
        pub has_install: bool,
        pub has_theater: bool,
        /// +0x94: true = attract battle ended by itself (replay the movie), false = a key skipped it (straight to title)
        pub return_mode: bool,
        /// +0x110 last event reported through `CBEntry`
        pub cb_event: u32,
        /// `TitleShared` at 0x0045e940
        pub shared: TitleShared,
    }

    impl OpeningMessage {
        /// `__ct__14openingMessage` (0x0045eb60).  `return_mode` is `Some(mode)` when created by `opening(u8)`.
        pub fn new(shared: TitleShared, return_mode: Option<bool>) -> Self {
            OpeningMessage {
                state: 0,
                next_state: 0,
                timer: 0,
                pulse: 0,
                sel: 0,
                cur: 0,
                nav_a: false,
                nav_b: false,
                has_install: false,
                has_theater: false,
                return_mode: return_mode.unwrap_or(true),
                cb_event: 0,
                shared,
            }
        }

        /// `initialize` (0x0045ee90): creates the fader (`mSetupFader`: cover(1)), applies the saved options and picks the first state.
        pub fn initialize(&mut self) -> Vec<Cmd> {
            let mut out = vec![Cmd::Cover(1)];
            if !self.shared.intro_done {
                self.shared.intro_done = true;
                self.state = S_DEVCHK_START;
            } else if !self.return_mode {
                self.state = S_TITLE_SETUP;
            } else {
                out.push(Cmd::Reveal(1));
                self.state = S_MOVIE_START;
            }
            out
        }

        /// The `dataAccess`/`Menu` callback (0x00460ad0 `CBEntry`).
        pub fn cb_entry(&mut self, event: u32) {
            self.cb_event = event;
        }

        fn disp(&self, w: u32, out: &mut Vec<Cmd>) {
            out.push(Cmd::DispMode(w, DISPLAY_H));
        }

        fn menu_move(&mut self, keys: u16, out: &mut Vec<Cmd>) {
            let old = self.cur;
            let (has3, has4) = (self.has_install, self.has_theater);
            match self.cur {
                4 => {
                    if keys & pad::LEFT != 0 {
                        if !has3 {
                            self.cur = 1;
                        } else {
                            self.nav_b = false;
                            self.cur = 3;
                        }
                    } else if keys & pad::UP != 0 {
                        self.cur = 1;
                    }
                }
                3 => {
                    if keys & pad::RIGHT != 0 {
                        if !has4 {
                            self.cur = 1;
                        } else {
                            self.nav_b = true;
                            self.cur = 4;
                        }
                    } else if keys & pad::UP != 0 {
                        self.cur = 1;
                    }
                }
                2 => {
                    if keys & pad::LEFT != 0 {
                        self.nav_b = false;
                        self.cur = 0;
                    } else if keys & pad::DOWN != 0 {
                        self.cur = 1;
                    }
                }
                1 => {
                    if keys & pad::RIGHT != 0 {
                        if !self.nav_a || !has4 {
                            self.nav_a = false;
                            self.cur = 2;
                        } else {
                            self.nav_a = true;
                            self.cur = 4;
                        }
                    } else if keys & pad::LEFT != 0 {
                        if !self.nav_a || !has3 {
                            self.nav_a = false;
                            self.cur = 0;
                        } else {
                            self.nav_a = true;
                            self.cur = 3;
                        }
                    } else if keys & pad::UP != 0 {
                        self.cur = if self.nav_b { 2 } else { 0 };
                    } else if keys & pad::DOWN != 0 {
                        if (!self.nav_b || !has4) && has3 {
                            self.nav_b = false;
                            self.cur = 3;
                        } else if (self.nav_b || !has3) && has4 {
                            self.nav_b = true;
                            self.cur = 4;
                        }
                    }
                }
                _ => {
                    if keys & pad::RIGHT != 0 {
                        self.nav_b = true;
                        self.cur = 2;
                    } else if keys & pad::DOWN != 0 {
                        self.cur = 1;
                    }
                }
            }
            if old != self.cur {
                out.push(Cmd::Se(0));
            }
            self.sel = self.cur;
            out.push(Cmd::MoveCursor(self.sel));
        }

        /// `Polling` (0x0045f340).
        pub fn poll(&mut self, i: &Inputs) -> Vec<Cmd> {
            let mut out = Vec::new();
            if let Some(e) = i.cb_event {
                self.cb_entry(e);
            }
            let key = i.trigger & ANY_KEY != 0;
            let keys = (i.repeat & 0xf0) | i.trigger;
            match self.state {
                S_WAIT_DATA => {
                    if i.regdat_ready {
                        self.state = 1;
                    }
                }
                S_DEVCHK_START => {
                    out.push(Cmd::StartDeviceCheck);
                    out.push(Cmd::Reveal(1));
                    self.state = S_DEVCHK_WAIT;
                }
                S_DEVCHK_WAIT => match self.cb_event {
                    6 => self.disp(DISPLAY_W_UI, &mut out),
                    3 => {
                        self.shared.save_found = true;
                        self.state = S_DEVCHK_END;
                    }
                    2 => self.state = S_DEVCHK_END,
                    _ => {}
                },
                S_DEVCHK_END => {
                    if self.cb_event == 4 {
                        self.state = S_DISCLAIMER;
                        out.push(Cmd::Cover(1));
                    }
                }
                S_DISCLAIMER => {
                    if !i.fader_clear {
                        if !i.fader_busy {
                            self.disp(DISPLAY_W_MOVIE, &mut out);
                            out.push(Cmd::SetupDisclaimer);
                            out.push(Cmd::Reveal(0x20));
                        }
                    } else {
                        self.timer = 0;
                        self.state = S_DISCLAIMER_WAIT;
                    }
                }
                S_DISCLAIMER_WAIT => {
                    self.timer += 1;
                    if key {
                        out.push(Cmd::Se(2));
                        self.timer = DISCLAIMER_FRAMES;
                    }
                    if self.timer > DISCLAIMER_FRAMES {
                        self.state = S_DISCLAIMER_FADE;
                        out.push(Cmd::Cover(0x20));
                    }
                }
                S_DISCLAIMER_FADE => {
                    if !i.fader_busy {
                        out.push(Cmd::ReleaseDisclaimer);
                        out.push(Cmd::Reveal(1));
                        self.state = S_MOVIE_START;
                    }
                }
                S_MOVIE_START => {
                    self.disp(DISPLAY_W_MOVIE, &mut out);
                    out.push(Cmd::SetupLsd);
                    if i.lsd_idle {
                        out.push(Cmd::StartMovie(MOVIE_OPENING));
                        self.state = S_MOVIE_PLAY;
                    }
                }
                S_MOVIE_PLAY => {
                    if i.lsd_started {
                        out.push(Cmd::FaderColor(0xff, 0xff, 0xff, 0x80));
                        if key || i.lsd_idle {
                            let speed = if key { 0x20 } else { 4 };
                            self.state = S_MOVIE_FADE;
                            out.push(Cmd::Cover(speed));
                        }
                    }
                }
                S_MOVIE_FADE => {
                    if !i.fader_busy {
                        if !i.lsd_idle {
                            out.push(Cmd::StopMovie);
                        }
                        self.timer = 0x10;
                        self.state = S_MOVIE_END;
                    }
                }
                S_MOVIE_END => {
                    if self.timer == 0 {
                        out.push(Cmd::ReleaseMovie);
                        self.state = S_TITLE_SETUP;
                    } else {
                        self.timer -= 1;
                    }
                }
                S_TITLE_SETUP => {
                    if !i.fader_clear {
                        if !i.fader_busy {
                            self.disp(DISPLAY_W_MOVIE, &mut out);
                            out.push(Cmd::SetupTitle);
                            out.push(Cmd::Reveal(0x20));
                        }
                    } else {
                        self.timer = 0;
                        self.state = S_PRESS_START;
                    }
                }
                S_PRESS_START => {
                    self.timer += 1;
                    if self.timer <= PRESS_START_IDLE {
                        if !key {
                            self.pulse += 1;
                            if self.pulse < 0x40 {
                                out.push(Cmd::PulseAlpha(self.pulse * 2));
                            } else if self.pulse < 0x80 {
                                out.push(Cmd::PulseAlpha(((self.pulse as i32 - 0x40) * -2 + 0x80) as u32));
                            } else {
                                self.pulse = 0;
                            }
                        } else {
                            out.push(Cmd::Se(2));
                            self.begin_menu(i, &mut out);
                        }
                    } else {
                        out.push(Cmd::StopMusic);
                        out.push(Cmd::FaderColor(0, 0, 0, 0x80));
                        out.push(Cmd::Cover(0x20));
                        self.state = S_LEAVE;
                        self.next_state = S_ATTRACT;
                        out.push(Cmd::OwnerAttract);
                    }
                }
                S_MENU => {
                    if !key {
                        if keys != 0 {
                            self.timer = 0;
                            self.menu_move(keys, &mut out);
                        }
                    } else {
                        out.push(Cmd::StopMusic);
                        out.push(Cmd::ReleaseMusic);
                        out.push(Cmd::Se(2));
                        self.state = S_LEAVE;
                        out.push(Cmd::FaderColor(0, 0, 0, 0x80));
                        out.push(Cmd::Cover(0x20));
                        match Row::from_index(self.sel) {
                            Row::NewGame => {
                                out.push(Cmd::CommitNewGame);
                                self.next_state = S_NEW_GAME;
                            }
                            Row::Continue => {
                                self.next_state = S_LOAD_START;
                                out.push(Cmd::CreateLoadScreen);
                            }
                            Row::Options => {
                                self.next_state = S_OPTIONS_START;
                                out.push(Cmd::CreateOptions);
                            }
                            Row::Installation | Row::Theater => {
                                out.push(Cmd::OwnerTheater);
                                self.next_state = S_EXIT_REVEAL;
                            }
                        }
                    }
                    self.timer += 1;
                    if self.timer > MENU_IDLE {
                        out.push(Cmd::StopMusic);
                        self.state = S_LEAVE;
                        self.next_state = S_ATTRACT;
                        out.push(Cmd::OwnerAttract);
                        out.push(Cmd::FaderColor(0, 0, 0, 0x80));
                        out.push(Cmd::Cover(0x20));
                    }
                }
                S_LEAVE => {
                    if !i.fader_busy {
                        out.push(Cmd::ReleaseTitle);
                        out.push(Cmd::ReleaseMenu);
                        out.push(Cmd::ReleaseMusic);
                        self.state = self.next_state;
                    }
                }
                S_INSTALL => {
                    self.disp(DISPLAY_W_UI, &mut out);
                    out.push(Cmd::Reveal(1));
                    self.state = S_LOAD_WAIT;
                }
                S_LOAD_START => {
                    self.disp(DISPLAY_W_UI, &mut out);
                    out.push(Cmd::StartLoadScreen);
                    out.push(Cmd::Reveal(1));
                    self.state = S_LOAD_WAIT;
                }
                S_LOAD_WAIT => {
                    if self.cb_event == 3 {
                        self.state = S_LOAD_BACK;
                    } else if self.cb_event == 5 {
                        self.state = S_DONE;
                    }
                }
                S_LOAD_BACK => {
                    if self.cb_event == 4 {
                        out.push(Cmd::Cover(1));
                        self.state = S_TITLE_SETUP;
                    }
                }
                S_OPTIONS_START => {
                    if !i.fader_clear {
                        if !i.fader_busy {
                            self.disp(DISPLAY_W_UI, &mut out);
                            out.push(Cmd::StartOptions);
                            out.push(Cmd::Reveal(0x10));
                        }
                    } else {
                        self.state = S_OPTIONS_WAIT;
                    }
                }
                S_OPTIONS_WAIT => {
                    if i.options_closed {
                        self.state = S_OPTIONS_FADE;
                        out.push(Cmd::Cover(0x10));
                    }
                }
                S_OPTIONS_FADE => {
                    if !i.fader_busy {
                        self.state = S_TITLE_SETUP;
                    }
                }
                S_EXIT_REVEAL => {
                    if !i.fader_clear {
                        if !i.fader_busy {
                            self.disp(DISPLAY_W_UI, &mut out);
                            out.push(Cmd::Reveal(0x20));
                        }
                    } else {
                        out.push(Cmd::OwnerDone);
                        out.push(Cmd::DelayDelete);
                        self.state = S_EXIT_WAIT;
                    }
                }
                S_EXIT_BACK => {
                    if !i.fader_busy {
                        self.state = S_TITLE_SETUP;
                    }
                }
                S_ATTRACT => {
                    out.push(Cmd::ReleaseMusic);
                    out.push(Cmd::Reveal(1));
                    self.disp(DISPLAY_W_UI, &mut out);
                    out.push(Cmd::SetFfMode(2));
                    out.push(Cmd::OwnerDone);
                    out.push(Cmd::DelayDelete);
                    self.timer = 0;
                    self.state = S_ATTRACT_WAIT;
                }
                S_NEW_GAME => {
                    out.push(Cmd::FieldMapJump(NEW_GAME_MAP));
                    out.push(Cmd::Reveal(1));
                    self.disp(DISPLAY_W_UI, &mut out);
                    self.state = S_DONE;
                }
                S_DONE => {
                    self.state = S_TERMINAL;
                    out.push(Cmd::OwnerDone);
                    out.push(Cmd::DelayDelete);
                }
                _ => {}
            }
            out
        }

        /// PRESS START pressed: `mSetupMenuWin` (default row = Continue when a save exists).
        fn begin_menu(&mut self, i: &Inputs, out: &mut Vec<Cmd>) {
            let row = if self.shared.save_found { 1 } else { 0 };
            self.cur = row;
            self.sel = row;
            self.nav_a = false;
            self.nav_b = false;
            self.has_install = i.install_flag;
            self.has_theater = self.shared.theater_enabled();
            out.push(Cmd::SetupMenu { default_row: row, install_enabled: self.has_install, theater_enabled: self.has_theater });
            self.state = S_MENU;
            self.timer = 0;
            out.push(Cmd::PulseAlpha(0));
        }
    }

    // ------------------------------------------------------------------------------------------------
    // Attract-mode battles (main-image openingBattleDemo; table @0x004306b0, 6 x 16 bytes)
    // ------------------------------------------------------------------------------------------------
    #[derive(Clone, Copy, Debug, PartialEq, Eq)]
    pub struct AttractBattle {
        /// RegDat(0x35, monset) monster-set id (`+0x40`)
        pub monster_set: i16,
        /// scenario passed to `FUN_003c02f0(member, scenario)` (equipment/level preset)
        pub scenario: i16,
        /// battle number (`BtlSocket+0x190`)
        pub battle: i16,
        /// battle BGM (`SetBtlBGMNumber`)
        pub bgm: i16,
        /// party members (-1 = unused)
        pub party: [i16; 4],
    }

    pub const ATTRACT_BATTLES: [AttractBattle; 6] = [
        AttractBattle { monster_set: 3, scenario: 0, battle: 77, bgm: 401, party: [5, 11, -1, -1] },
        AttractBattle { monster_set: 16, scenario: 1, battle: 6, bgm: 401, party: [0, 1, 2, -1] },
        AttractBattle { monster_set: 82, scenario: 2, battle: 28, bgm: 401, party: [0, 2, 5, 6] },
        AttractBattle { monster_set: 146, scenario: 3, battle: 42, bgm: 407, party: [8, 9, 10, -1] },
        AttractBattle { monster_set: 227, scenario: 4, battle: 89, bgm: 405, party: [1, 4, 6, 7] },
        AttractBattle { monster_set: 249, scenario: 5, battle: 73, bgm: 403, party: [0, 2, 3, 5] },
    ];

    /// `openingBattleDemo::initialize` (0x004166b0) rotation over [`ATTRACT_BATTLES`] (static index @0x0043ff10).
    #[derive(Clone, Copy, Debug, Default)]
    pub struct AttractSelector {
        pub idx: usize,
    }

    impl AttractSelector {
        /// `progress` = [`TitleShared::attract_progress`] (0, 1 or 2 progress bits set).
        pub fn pick(&mut self, progress: u8) -> AttractBattle {
            let mut chosen = self.idx;
            match progress {
                2 => {
                    self.idx += 1;
                    if self.idx > 5 {
                        self.idx = 0;
                    }
                }
                1 => {
                    if self.idx < 3 {
                        self.idx = 3;
                    }
                    chosen = self.idx;
                    self.idx += 1;
                    if self.idx > 5 {
                        self.idx = 3;
                    }
                }
                _ => {
                    self.idx += 1;
                    if self.idx > 2 {
                        self.idx = 0;
                    }
                }
            }
            ATTRACT_BATTLES[chosen.min(5)]
        }
    }

    #[derive(Clone, Copy, Debug, PartialEq, Eq)]
    pub enum DemoState {
        /// 0: wait for `start()`
        Idle,
        /// 1: `InitBtlSocket` + party/monsters; this replaces `CDMYStage` in `SSHSys`
        Init,
        /// 2: battle running (skippable after 60 frames, hard limit 0xa8c = 2700 frames)
        Running,
        /// 3: banner fading, wait for the battle to report completion
        Ending,
        /// 4: finished
        Finished,
    }

    #[derive(Clone, Debug, PartialEq)]
    pub enum DemoCmd {
        /// banner `prim2D` (layer 0xe, uv (1,1,0xd2,0x78), fade in 0x10)
        ShowBanner,
        InitBattle(AttractBattle),
        FadeBanner(u32),
        /// `BtlSocket::BattleEnd` handling (FUN_00368b60)
        BattleEnd,
        ReleaseBanners,
        /// `opening(not_skipped)` -> `SetAPI(new CDMYStage)` again
        ReturnToTitle { replay_movie: bool },
        DelayDelete,
    }

    pub struct OpeningBattleDemo {
        pub state: DemoState,
        pub timer: u32,
        /// +0x2f set by `start()`
        pub go: bool,
        /// +0x2d battle callback event 2 seen (battle over / fader finished)
        pub battle_over: bool,
        /// +0x2c battle callback event 0 seen (battle torn down)
        pub battle_done: bool,
        /// +0x2e: cleared when a key cut the demo short
        pub not_skipped: bool,
        pub entry: AttractBattle,
    }

    impl OpeningBattleDemo {
        pub fn new(entry: AttractBattle) -> Self {
            OpeningBattleDemo { state: DemoState::Idle, timer: 0, go: false, battle_over: false, battle_done: false, not_skipped: true, entry }
        }
        /// 0x00416690
        pub fn start(&mut self) {
            self.go = true;
        }
        /// `BtlCBFunc` (0x00416ed0): 2 = battle over, 0 = battle finished
        pub fn battle_event(&mut self, code: i32) {
            match code {
                2 => self.battle_over = true,
                0 => self.battle_done = true,
                _ => {}
            }
        }
        /// `Polling` (0x004169a0). `key` = O/START (0x2008) this frame.
        pub fn poll(&mut self, key: bool) -> Vec<DemoCmd> {
            let mut out = Vec::new();
            match self.state {
                DemoState::Idle => {
                    if self.go {
                        out.push(DemoCmd::ShowBanner);
                        self.state = DemoState::Init;
                    }
                }
                DemoState::Init => {
                    out.push(DemoCmd::InitBattle(self.entry));
                    self.state = DemoState::Running;
                    self.timer = 0;
                }
                DemoState::Running => {
                    self.timer += 1;
                    if self.timer > 0x3c && key {
                        self.not_skipped = false;
                        self.timer = 0xa8c;
                    }
                    if (self.timer < 0xa8c && self.battle_over) || self.timer > 0xa8b {
                        out.push(DemoCmd::FadeBanner(0x20));
                        self.state = DemoState::Ending;
                    }
                }
                DemoState::Ending => {
                    out.push(DemoCmd::BattleEnd);
                    if self.battle_done {
                        out.push(DemoCmd::ReleaseBanners);
                        self.timer = 0;
                        self.state = DemoState::Finished;
                        out.push(DemoCmd::ReturnToTitle { replay_movie: self.not_skipped });
                        out.push(DemoCmd::DelayDelete);
                    }
                }
                DemoState::Finished => {}
            }
            out
        }
    }

    // ------------------------------------------------------------------------------------------------
    // CDMYStage (retail SSHApi that hosts the title)
    // ------------------------------------------------------------------------------------------------
    /// `CDMYStage` stage state (static @0x0043ff0c).
    #[derive(Clone, Copy, Debug, PartialEq, Eq)]
    pub enum StageState {
        Idle = 0,
        /// ctor value: OPENING.BIN must be loaded
        NeedLoad = 1,
        Loading = 2,
        /// overlay loaded, title running
        Running = 3,
        /// `closeInquiry` was called
        Closing = 4,
        /// title is gone, overlay can be unloaded
        ReadyToUnload = 5,
    }

    #[derive(Clone, Copy, Debug, PartialEq, Eq)]
    pub enum Pending {
        None,
        /// event 2
        Demo,
        /// event 3
        Theater,
    }

    #[derive(Clone, Debug, PartialEq)]
    pub enum StageCmd {
        /// `openingMessage::Finish` (0x0045ee20) on the title object
        FinishTitle,
        /// create `openingBattleDemo` + `initialize(opening.dat data, 0x13, shared)`
        CreateDemo,
        /// `openingBattleDemo::start()`
        StartDemo,
        /// `InitFieldSocketCB(StartTheater, 0)`
        StartTheater,
        /// `Overlay::Unload(group 3)`
        UnloadOverlay,
    }

    /// Result of `Overlay::Load("OPENING.BIN", ...)`: 0 loading started/pending, 3 loaded immediately (pre-buffer).
    #[derive(Clone, Copy, Debug, PartialEq, Eq)]
    pub enum LoadResult {
        Pending,
        Loaded,
        Other,
    }

    pub struct CdmyStage {
        pub state: StageState,
        /// +0x24 last owner event
        pub event: i32,
        /// +0x28 return mode (`opening(u8)`)
        pub mode: bool,
        /// +0x29 "special exit / resident data" flag (set by `opening(u8)` and by events 2/3)
        pub has_mode: bool,
        pub title_alive: bool,
        pub pending: Pending,
    }

    impl Default for CdmyStage {
        fn default() -> Self {
            Self::new()
        }
    }

    impl CdmyStage {
        /// 0x00415c50 `__ct__9CDMYStage`
        pub fn new() -> Self {
            CdmyStage { state: StageState::NeedLoad, event: 0, mode: false, has_mode: false, title_alive: false, pending: Pending::None }
        }
        /// `opening(u8)` / `CDMYStage::SetReturnMode` (0x00415cd0)
        pub fn set_return_mode(&mut self, mode: bool) {
            self.has_mode = true;
            self.mode = mode;
        }
        /// 0x00415f00 `preLoad`: returns true when the overlay is ready.
        pub fn pre_load(&mut self, load: impl FnOnce() -> LoadResult) -> bool {
            match self.state {
                StageState::Running => true,
                StageState::Loading => false,
                StageState::NeedLoad => {
                    match load() {
                        LoadResult::Pending => self.state = StageState::Loading,
                        LoadResult::Loaded => self.state = StageState::Running,
                        LoadResult::Other => {}
                    }
                    false
                }
                _ => false,
            }
        }
        /// 0x00415ee0: overlay load callback
        pub fn overlay_loaded(&mut self) {
            self.state = StageState::Running;
        }
        /// 0x00415d70 `CBTitle`
        pub fn cb_title(&mut self, event: i32) {
            self.event = event;
            if event == 4 {
                self.title_alive = false;
            }
        }
        /// 0x00416240: true while busy (SSHSys keeps asking), false once closed (overlay unloaded).
        pub fn close_inquiry(&mut self) -> (bool, Vec<StageCmd>) {
            if self.state != StageState::ReadyToUnload {
                self.state = StageState::Closing;
                (true, vec![])
            } else {
                self.state = StageState::Idle;
                (false, vec![StageCmd::UnloadOverlay])
            }
        }
        /// 0x004162a0 `Polling`
        pub fn poll(&mut self) -> Vec<StageCmd> {
            let mut out = Vec::new();
            if self.state == StageState::Closing {
                if self.event != 2 && self.event != 3 {
                    if !self.has_mode {
                        if !self.title_alive {
                            self.state = StageState::ReadyToUnload;
                        } else {
                            out.push(StageCmd::FinishTitle);
                            self.title_alive = false;
                        }
                    } else {
                        match self.pending {
                            Pending::Demo => out.push(StageCmd::StartDemo),
                            Pending::Theater => out.push(StageCmd::StartTheater),
                            Pending::None => {}
                        }
                        self.state = StageState::ReadyToUnload;
                    }
                }
            } else if self.state == StageState::Running && self.event == 2 {
                self.has_mode = true;
                out.push(StageCmd::CreateDemo);
                self.state = StageState::Closing;
                self.pending = Pending::Demo;
            } else if self.state == StageState::Running && self.event == 3 {
                self.has_mode = true;
                self.state = StageState::Closing;
                self.pending = Pending::Theater;
            }
            out
        }
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    fn clear() -> TitleInputs {
        TitleInputs { fader_clear: true, ..Default::default() }
    }

    #[test]
    fn splash_movie_title_menu_start() {
        let mut t = OpeningMessage::new(false);
        assert_eq!(t.state, S_TRIAL_SPLASH);
        // splash builds then waits
        let c = t.poll(&TitleInputs::default());
        assert!(c.contains(&TitleCmd::SetupTrialSplash));
        t.poll(&clear());
        assert_eq!(t.state, S_TRIAL_WAIT);
        t.poll(&TitleInputs { trigger: pad::CIRCLE, ..clear() });
        assert_eq!(t.state, S_TRIAL_FADE);
        t.poll(&TitleInputs::default());
        assert_eq!(t.state, S_MOVIE_START);
        let c = t.poll(&TitleInputs { lsd_idle: true, ..Default::default() });
        assert!(c.contains(&TitleCmd::PlayMovie(MOVIE_OPENING)));
        // skip the movie with START
        t.poll(&TitleInputs { lsd_started: true, trigger: pad::START, ..Default::default() });
        assert_eq!(t.state, S_MOVIE_FADE);
        t.poll(&TitleInputs::default());
        assert_eq!(t.state, S_TITLE_SETUP);
        t.poll(&TitleInputs::default());
        t.poll(&clear());
        assert_eq!(t.state, S_TITLE_WAIT);
        // press start -> menu
        t.poll(&TitleInputs { trigger: pad::START, ..clear() });
        assert_eq!(t.state, S_MENU);
        // choose "start game"
        let c = t.poll(&TitleInputs { trigger: pad::CIRCLE, menu_ready: true, menu_sel: 0, ..clear() });
        assert!(c.contains(&TitleCmd::FadeIn(0x20)));
        t.poll(&TitleInputs::default());
        assert_eq!(t.state, S_GAME_START);
        let c = t.poll(&TitleInputs::default());
        assert!(c.contains(&TitleCmd::StartNewGame("WORLDMAP")));
        t.poll(&TitleInputs::default());
        assert!(t.poll(&TitleInputs::default()).is_empty() || t.state == 0x28);
    }

    #[test]
    fn idle_title_starts_attract_battles_in_rotation() {
        let mut t = OpeningMessage::new(true);
        t.poll(&TitleInputs::default());
        t.poll(&clear());
        let mut seen = vec![];
        for _ in 0..3 {
            t.state = S_TITLE_WAIT;
            t.timer = 0;
            for _ in 0..(TITLE_IDLE_FRAMES + 3) {
                for c in t.poll(&clear()) {
                    if let TitleCmd::StartBattleDemo(d) = c {
                        seen.push(d.battle);
                    }
                }
            }
        }
        assert_eq!(seen, vec![0x4d, 6, 0x1c]);
    }

    #[test]
    fn battle_demo_runs() {
        let mut d = OpeningBattleDemo::new(DEMO_BATTLES[0]);
        assert!(d.poll(false, false).is_empty());
        d.start();
        assert_eq!(d.poll(false, false).len(), 2);
        for _ in 0..400 {
            d.poll(false, false);
        }
        assert_eq!(d.state, DemoState::Running);
        d.poll(true, false);
        assert!(!d.not_skipped);
        assert_eq!(d.state, DemoState::Ending);
        d.battle_done = true;
        d.poll(false, false);
        d.poll(false, false);
        assert!(d.finished);
    }
}

#[cfg(test)]
mod retail_tests {
    use super::retail::*;
    use super::{Build, Machine};
    use crate::scene::pad;

    fn clear() -> Inputs {
        Inputs { fader_clear: true, ..Default::default() }
    }
    fn busy() -> Inputs {
        Inputs { fader_busy: true, ..Default::default() }
    }

    #[test]
    fn machine_selects_build() {
        assert_eq!(Machine::new(Build::JpDemo, false).build(), Build::JpDemo);
        assert_eq!(Machine::new(Build::Retail, false).build(), Build::Retail);
        assert_eq!(Build::default(), Build::JpDemo);
    }

    #[test]
    fn first_boot_device_check_disclaimer_movie_title() {
        let mut t = OpeningMessage::new(TitleShared::default(), None);
        let c = t.initialize();
        assert_eq!(c, vec![Cmd::Cover(1)]);
        assert_eq!(t.state, S_DEVCHK_START);
        assert!(t.shared.intro_done);
        let c = t.poll(&Inputs::default());
        assert_eq!(c, vec![Cmd::StartDeviceCheck, Cmd::Reveal(1)]);
        assert_eq!(t.state, S_DEVCHK_WAIT);
        // the memory card UI asks for the 512x448 screen, then reports a save
        let c = t.poll(&Inputs { cb_event: Some(6), ..Default::default() });
        assert_eq!(c, vec![Cmd::DispMode(0x200, 0x1c0)]);
        t.poll(&Inputs { cb_event: Some(3), ..Default::default() });
        assert_eq!(t.state, S_DEVCHK_END);
        assert!(t.shared.save_found);
        let c = t.poll(&Inputs { cb_event: Some(4), ..Default::default() });
        assert_eq!(c, vec![Cmd::Cover(1)]);
        assert_eq!(t.state, S_DISCLAIMER);
        // disclaimer: build while the cover is closed, 450 frames or a key
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::SetupDisclaimer) && c.contains(&Cmd::Reveal(0x20)));
        t.poll(&clear());
        assert_eq!(t.state, S_DISCLAIMER_WAIT);
        t.poll(&Inputs { trigger: pad::CIRCLE, ..Default::default() });
        let c = t.poll(&Inputs::default());
        assert_eq!(c, vec![Cmd::Cover(0x20)]);
        assert_eq!(t.state, S_DISCLAIMER_FADE);
        t.poll(&busy());
        assert_eq!(t.state, S_DISCLAIMER_FADE);
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::ReleaseDisclaimer));
        assert_eq!(t.state, S_MOVIE_START);
        // movie: wait for an idle player, play, skip with START
        let c = t.poll(&Inputs { lsd_idle: true, ..Default::default() });
        assert!(c.contains(&Cmd::StartMovie(MOVIE_OPENING)));
        let c = t.poll(&Inputs { lsd_started: true, trigger: pad::START, ..Default::default() });
        assert!(c.contains(&Cmd::FaderColor(0xff, 0xff, 0xff, 0x80)) && c.contains(&Cmd::Cover(0x20)));
        t.poll(&busy());
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::StopMovie));
        assert_eq!(t.state, S_MOVIE_END);
        for _ in 0..0x10 {
            t.poll(&Inputs::default());
        }
        assert_eq!(t.state, S_MOVIE_END);
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::ReleaseMovie));
        assert_eq!(t.state, S_TITLE_SETUP);
    }

    #[test]
    fn later_runs_skip_the_intro() {
        let shared = TitleShared { intro_done: true, ..Default::default() };
        // returning from an attract battle that ran to its end: play the movie again
        let mut t = OpeningMessage::new(shared.clone(), Some(true));
        assert_eq!(t.initialize(), vec![Cmd::Cover(1), Cmd::Reveal(1)]);
        assert_eq!(t.state, S_MOVIE_START);
        // ... or one cut short with a key: straight to the title
        let mut t = OpeningMessage::new(shared, Some(false));
        assert_eq!(t.initialize(), vec![Cmd::Cover(1)]);
        assert_eq!(t.state, S_TITLE_SETUP);
    }

    fn at_menu(save: bool, theater: bool, install: bool) -> OpeningMessage {
        let mut shared = TitleShared { intro_done: true, save_found: save, ..Default::default() };
        shared.common[1] = theater as u8;
        let mut t = OpeningMessage::new(shared, Some(false));
        t.initialize();
        t.state = S_PRESS_START;
        let c = t.poll(&Inputs { trigger: pad::START, install_flag: install, ..Default::default() });
        assert!(c.contains(&Cmd::Se(2)));
        assert!(c.iter().any(|c| matches!(c, Cmd::SetupMenu { .. })));
        assert_eq!(t.state, S_MENU);
        t
    }

    fn press(t: &mut OpeningMessage, keys: u16) {
        t.poll(&Inputs { repeat: keys & 0xf0, ..Default::default() });
    }

    #[test]
    fn menu_default_row_and_topology() {
        // default row: Continue when a save exists, New Game otherwise
        assert_eq!(at_menu(true, false, false).cur, 1);
        assert_eq!(at_menu(false, false, false).cur, 0);
        let mut t = at_menu(false, true, true);
        // 0 -right-> 2 -left-> 0 ; 0 -down-> 1
        press(&mut t, pad::RIGHT);
        assert_eq!(t.cur, 2);
        press(&mut t, pad::LEFT);
        assert_eq!(t.cur, 0);
        press(&mut t, pad::DOWN);
        assert_eq!(t.cur, 1);
        // centre: down goes to the lower-left row (Installation), right from there to Theater
        press(&mut t, pad::DOWN);
        assert_eq!(t.cur, 3);
        press(&mut t, pad::RIGHT);
        assert_eq!(t.cur, 4);
        press(&mut t, pad::LEFT);
        assert_eq!(t.cur, 3);
        press(&mut t, pad::UP);
        assert_eq!(t.cur, 1);
        // without Installation the lower-left slot is skipped
        let mut t = at_menu(true, true, false);
        press(&mut t, pad::DOWN);
        assert_eq!(t.cur, 4);
        press(&mut t, pad::LEFT);
        assert_eq!(t.cur, 1);
        // without Theater nothing below
        let mut t = at_menu(true, false, false);
        press(&mut t, pad::DOWN);
        assert_eq!(t.cur, 1);
    }

    #[test]
    fn new_game_goes_to_op_00_u() {
        let mut t = at_menu(false, false, false);
        let c = t.poll(&Inputs { trigger: pad::CIRCLE, ..Default::default() });
        assert!(c.contains(&Cmd::CommitNewGame) && c.contains(&Cmd::Cover(0x20)));
        assert_eq!((t.state, t.next_state), (S_LEAVE, S_NEW_GAME));
        t.poll(&busy());
        assert_eq!(t.state, S_LEAVE);
        t.poll(&Inputs::default());
        assert_eq!(t.state, S_NEW_GAME);
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::FieldMapJump("OP_00_U")));
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::OwnerDone) && c.contains(&Cmd::DelayDelete));
        assert_eq!(t.state, S_TERMINAL);
    }

    #[test]
    fn continue_options_and_theater_paths() {
        let mut t = at_menu(true, true, false);
        // Continue -> load screen
        let c = t.poll(&Inputs { trigger: pad::CIRCLE, ..Default::default() });
        assert!(c.contains(&Cmd::CreateLoadScreen));
        t.poll(&Inputs::default());
        assert_eq!(t.state, S_LOAD_START);
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::StartLoadScreen));
        t.poll(&Inputs { cb_event: Some(5), ..Default::default() });
        assert_eq!(t.state, S_DONE);
        // Options
        let mut t = at_menu(true, true, false);
        press(&mut t, pad::UP);
        press(&mut t, pad::RIGHT);
        assert_eq!(Row::from_index(t.cur), Row::Options);
        let c = t.poll(&Inputs { trigger: pad::START, ..Default::default() });
        assert!(c.contains(&Cmd::CreateOptions));
        t.poll(&Inputs::default());
        assert_eq!(t.state, S_OPTIONS_START);
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::StartOptions) && c.contains(&Cmd::Reveal(0x10)));
        t.poll(&clear());
        assert_eq!(t.state, S_OPTIONS_WAIT);
        let c = t.poll(&Inputs { options_closed: true, ..Default::default() });
        assert_eq!(c, vec![Cmd::Cover(0x10)]);
        t.poll(&Inputs::default());
        assert_eq!(t.state, S_TITLE_SETUP);
        // Theater (row 4)
        let mut t = at_menu(true, true, false);
        press(&mut t, pad::DOWN);
        assert_eq!(Row::from_index(t.cur), Row::Theater);
        let c = t.poll(&Inputs { trigger: pad::CIRCLE, ..Default::default() });
        assert!(c.contains(&Cmd::OwnerTheater));
        assert_eq!(t.next_state, S_EXIT_REVEAL);
    }

    #[test]
    fn idle_title_requests_the_attract_battle() {
        let mut t = OpeningMessage::new(TitleShared { intro_done: true, ..Default::default() }, Some(false));
        t.initialize();
        t.state = S_PRESS_START;
        let mut asked = 0;
        for _ in 0..(PRESS_START_IDLE + 1) {
            for c in t.poll(&Inputs::default()) {
                if c == Cmd::OwnerAttract {
                    asked += 1;
                }
            }
        }
        assert_eq!(asked, 1);
        assert_eq!((t.state, t.next_state), (S_LEAVE, S_ATTRACT));
        t.poll(&Inputs::default());
        assert_eq!(t.state, S_ATTRACT);
        let c = t.poll(&Inputs::default());
        assert!(c.contains(&Cmd::OwnerDone) && c.contains(&Cmd::SetFfMode(2)));
        // idle menu: 3600 frames
        let mut t = at_menu(false, false, false);
        let mut asked = false;
        for _ in 0..(MENU_IDLE + 2) {
            asked |= t.poll(&Inputs::default()).contains(&Cmd::OwnerAttract);
        }
        assert!(asked);
    }

    #[test]
    fn attract_rotation_follows_progress_bits() {
        let mut s = AttractSelector::default();
        let seq: Vec<i16> = (0..4).map(|_| s.pick(0).battle).collect();
        assert_eq!(seq, vec![77, 6, 28, 77]);
        let mut s = AttractSelector::default();
        let seq: Vec<i16> = (0..4).map(|_| s.pick(1).battle).collect();
        assert_eq!(seq, vec![42, 89, 73, 42]);
        let mut s = AttractSelector::default();
        let seq: Vec<i16> = (0..7).map(|_| s.pick(2).battle).collect();
        assert_eq!(seq, vec![77, 6, 28, 42, 89, 73, 77]);
        let mut sh = TitleShared::default();
        assert_eq!(sh.attract_progress(), 0);
        sh.common[0x14] = 0x40;
        assert_eq!(sh.attract_progress(), 1);
        sh.common[0x14] = 0xc0;
        assert_eq!(sh.attract_progress(), 2);
    }

    #[test]
    fn battle_demo_runs_and_returns_to_title() {
        let mut d = OpeningBattleDemo::new(ATTRACT_BATTLES[3]);
        assert!(d.poll(false).is_empty());
        d.start();
        assert_eq!(d.poll(false), vec![DemoCmd::ShowBanner]);
        assert_eq!(d.poll(false), vec![DemoCmd::InitBattle(ATTRACT_BATTLES[3])]);
        for _ in 0..0x3d {
            assert!(d.poll(false).is_empty());
        }
        // a key after 60 frames cuts the demo short
        let c = d.poll(true);
        assert_eq!(c, vec![DemoCmd::FadeBanner(0x20)]);
        assert!(!d.not_skipped);
        let c = d.poll(false);
        assert_eq!(c, vec![DemoCmd::BattleEnd]);
        d.battle_event(0);
        let c = d.poll(false);
        assert_eq!(c, vec![DemoCmd::BattleEnd, DemoCmd::ReleaseBanners, DemoCmd::ReturnToTitle { replay_movie: false }, DemoCmd::DelayDelete]);
        // natural end: battle reports event 2 before the 2700 frame limit
        let mut d = OpeningBattleDemo::new(ATTRACT_BATTLES[0]);
        d.start();
        d.poll(false);
        d.poll(false);
        d.poll(false);
        d.battle_event(2);
        assert_eq!(d.poll(false), vec![DemoCmd::FadeBanner(0x20)]);
        d.battle_event(0);
        let c = d.poll(false);
        assert!(c.contains(&DemoCmd::ReturnToTitle { replay_movie: true }));
    }

    #[test]
    fn stage_load_and_attract_hand_over() {
        let mut s = CdmyStage::new();
        assert_eq!(s.state, StageState::NeedLoad);
        assert!(!s.pre_load(|| LoadResult::Pending));
        assert_eq!(s.state, StageState::Loading);
        s.overlay_loaded();
        assert!(s.pre_load(|| unreachable!()));
        s.title_alive = true;
        // title asks for the attract battle
        s.cb_title(2);
        assert_eq!(s.poll(), vec![StageCmd::CreateDemo]);
        assert_eq!(s.state, StageState::Closing);
        // still waiting for the title to say it is done
        assert!(s.poll().is_empty());
        s.cb_title(4);
        assert_eq!(s.poll(), vec![StageCmd::StartDemo]);
        assert_eq!(s.state, StageState::ReadyToUnload);
        let (busy, cmds) = s.close_inquiry();
        assert!(!busy);
        assert_eq!(cmds, vec![StageCmd::UnloadOverlay]);
        assert_eq!(s.state, StageState::Idle);
    }

    #[test]
    fn stage_theater_and_normal_close() {
        let mut s = CdmyStage::new();
        s.overlay_loaded();
        s.title_alive = true;
        s.cb_title(3);
        assert!(s.poll().is_empty());
        assert_eq!(s.pending, Pending::Theater);
        s.cb_title(4);
        assert_eq!(s.poll(), vec![StageCmd::StartTheater]);
        // normal close (e.g. New Game): SSHSys asks to close while the title is alive -> it is finished first
        let mut s = CdmyStage::new();
        s.overlay_loaded();
        s.title_alive = true;
        let (busy, _) = s.close_inquiry();
        assert!(busy);
        assert_eq!(s.poll(), vec![StageCmd::FinishTitle]);
        assert!(s.poll().is_empty());
        assert_eq!(s.state, StageState::ReadyToUnload);
        // opening(u8) marks the stage as returning
        let mut s = CdmyStage::new();
        s.set_return_mode(false);
        assert!(s.has_mode && !s.mode);
    }

    #[test]
    fn system_block_merge() {
        let mut sh = TitleShared::default();
        let mut a = [0u8; 0x100];
        a[0] = 1;
        a[0x30] = 0x0f;
        a[0x84..0x88].copy_from_slice(&10u32.to_le_bytes());
        let mut b = [0u8; 0x100];
        b[0x30] = 0xf0;
        b[0x84..0x88].copy_from_slice(&7u32.to_le_bytes());
        sh.merge_device(&a);
        sh.merge_device(&b);
        assert_eq!(sh.common[0], 1);
        assert_eq!(sh.common[0x30], 0xff);
        assert_eq!(u32::from_le_bytes(sh.common[0x84..0x88].try_into().unwrap()), 10);
        let mut live = [0u8; 0x100];
        live[0x82] = 5;
        sh.merge_live(&live);
        assert!(sh.merged);
        assert_eq!(sh.commit_new_game()[0x82], 5);
    }
}

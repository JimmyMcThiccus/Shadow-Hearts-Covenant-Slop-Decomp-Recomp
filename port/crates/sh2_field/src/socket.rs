//! `CFieldSocket` (main exe, JP 0x003bd590..0x003c1ee0) — the `SSHApi` that owns the FIELD.BIN overlay and drives
//! `CField` / the world map. Object size 0x6c.
//!
//! Only the pure state logic is ported here (screen faders, load phases, map file naming, warp state); everything that
//! touches the engine (overlay load, GsxCamera, ScreenBright, CScript, CSTGDB I/O) is described by [`FieldHost`].

/// `CFieldSocket+0x50` — scene phase.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Phase {
    /// 0: constructed; `preLoad` has not run yet
    Init,
    /// 1: overlay load/preload requested (`DisableReset`, texture layer switched)
    Loading,
    /// 2: `Start` called before the overlay was ready; `WakeUp` runs once `fieldOverlay` completes
    WakePending,
    /// 3: awake (cameras, faders, filters created), map script/SDB streaming
    Awake,
    /// 4: normal running state
    Running,
    /// 5: `closeInquiry` phase 1 (CField deleted)
    Closing1,
    /// 6: phase 2 (overlay unloaded, `ReleaseCmdMenu`, `FldMemory` released)
    Closing2,
    /// 7: closed
    Closed,
    /// 0x10 | n: world map transition (0: delete CField, 1: start worldMap)
    WorldMap(u8),
    /// 0x20: save-screen return, waiting for the fader before `CField::Pause(1)`
    SaveReturn,
    /// 0x30: field → other-map jump pending (`WakeMapJump`)
    MapJumpPending,
    Other(u32),
}

impl From<u32> for Phase {
    fn from(v: u32) -> Self {
        match v {
            0 => Self::Init,
            1 => Self::Loading,
            2 => Self::WakePending,
            3 => Self::Awake,
            4 => Self::Running,
            5 => Self::Closing1,
            6 => Self::Closing2,
            7 => Self::Closed,
            v if v & 0xf0 == 0x10 => Self::WorldMap((v & 0xf) as u8),
            0x20 => Self::SaveReturn,
            0x30 => Self::MapJumpPending,
            v => Self::Other(v),
        }
    }
}

/// `m_flags__12CFieldSocket` (byte at 0x0040ada0): low nibble = map load phase, high bits = view flags.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum MapLoad {
    /// 0: nothing pending
    Idle,
    /// 1: MSC being read from disc (`CScript::LoadScript`)
    MscLoading,
    /// 2: MSC found in `CSndBufCache`
    MscCached,
    /// 3: MSC loaded; MPS (CSTGDB) load not yet started
    MscDone,
    /// 4: MPS loading, will `Restart` + start the script when it completes
    MpsLoading,
    /// 5: `ReloadMPS` — MPS reload only (no script restart)
    MpsReloading,
    /// 8: preloaded MSC available (`pFldPreLoadMSC`), 9: ready to hand to `LoadScriptB`
    PreMsc(u8),
}
impl From<u8> for MapLoad {
    fn from(v: u8) -> Self {
        match v & 0xf {
            0 => Self::Idle,
            1 => Self::MscLoading,
            2 => Self::MscCached,
            3 => Self::MscDone,
            4 => Self::MpsLoading,
            5 => Self::MpsReloading,
            x => Self::PreMsc(x),
        }
    }
}

pub const FLAG_AWAKE: u8 = 0x10;
pub const FLAG_FILTER_SHOWN: u8 = 0x40;
pub const FLAG_CMDMENU: u8 = 0x80;

/// `CFieldSocket::FieldFader` — the two 12-byte fader slots at `+0x30` and `+0x3c` (slot 1 is the white/black
/// scene transition at OT layer 0xe, slot 0 the one at layer 0xb).
#[derive(Debug, Clone, Copy, Default)]
pub struct Fader {
    /// state nibble: 0 idle, 1 running, 2 finishing
    pub state: u8,
    pub paused: bool,
    /// bit0: direction (1 = fade to colour/opaque), bits1..: type (see `set`).
    pub mode: u8,
    pub cur: u16,
    pub total: i16,
    /// `ScreenBright+0x28` alpha (0..=0x80)
    pub alpha: u8,
    /// `ScreenBright+0x34` colour (RGB, 0x000000 black / 0xffffff white)
    pub color: u32,
}

impl Fader {
    /// JP: 0x003bedf0 SetFader(slot, mode, frames)
    pub fn set(&mut self, mode: u8, frames: i32) {
        let b = mode & 0x7f;
        if b == self.mode && frames != 0 {
            return;
        }
        self.mode = b;
        if mode & 0x80 == 0 || self.total as i32 == self.cur as i32 {
            self.cur = 0;
        } else {
            self.cur = (frames * self.cur as i32 / self.total as i32) as u16;
        }
        self.total = frames as i16;
        self.state = 1;
        if b < 4 {
            self.color = if mode & 2 != 0 { 0xffffff } else { 0 };
        }
        if b == 7 {
            self.color = 0;
        }
        if frames == 0 {
            self.alpha = if mode & 1 != 0 { 0x80 } else { 0 };
            if mode & 1 == 0 {
                self.state = 0;
            }
        }
    }

    /// JP: 0x003bf110 UpdateFader (per slot)
    pub fn update(&mut self, dt: u32) {
        if self.paused {
            return;
        }
        if self.cur as i32 == self.total as i32 {
            if self.state != 2 {
                return;
            }
            self.mode &= 1; // original clears the type byte (+5 = 0)
            self.mode = 0;
            self.state = 0;
        }
        let mut t = self.cur as i32 + dt as i32;
        if self.total as i32 <= t {
            self.state = self.mode & 1;
            t = self.total as i32;
        }
        self.cur = t as u16;
        let mut a = if self.mode & 1 == 0 {
            if t == self.total as i32 {
                0
            } else {
                0x80 - ((t << 7) / self.total as i32)
            }
        } else if t == self.total as i32 {
            0x80
        } else {
            (t << 7) / self.total as i32
        };
        if self.mode >> 1 == 3 {
            a >>= 1;
        }
        self.alpha = a as u8;
    }

    /// JP: 0x003bed00 GetFaderLevel — 0..=0x7f
    pub fn level(&self) -> i32 {
        if self.state & 0xf == 0 {
            return 0;
        }
        if self.total == 0 {
            return 0x7f;
        }
        let l = ((self.cur as i32) << 7) / self.total as i32;
        if self.mode & 1 == 0 {
            0x7f - l
        } else {
            l
        }
    }
    /// JP: 0x003becb0 isFaderDsp
    pub fn is_displayed(&self) -> bool {
        self.state & 0xf != 0
    }
    /// JP: 0x003bf020 ClrFader
    pub fn clear(&mut self) {
        if self.state & 0xf != 0 {
            self.state = 2;
        }
        self.total = 0;
        self.cur = 0;
    }
}

/// JP: 0x003bd1f0 `GetMapName(buf, map, kind)` — `"%sFIELD/MPS/%s.%s"` with `MSC` (kind 0) or `MPS` (kind 1).
/// Returns the path inside `FIELD.PKB`'s tree (use with [`crate::pkb_compat::PkbSet::read`]).
pub fn map_name(map: &str, mps: bool) -> String {
    format!("FIELD/MPS/{}.{}", map, if mps { "MPS" } else { "MSC" })
}

/// `CFieldSocket::SetWarp` (JP 0x003c0770) warp state stored in the two low bits of the byte at 0x0040ada1.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum WarpState {
    None = 0,
    Out = 1,
    In = 2,
}

/// JP: 0x003c0770 — returns the next warp state for `SetWarp(arg)`.
pub fn set_warp(cur: u8, arg: i32) -> u8 {
    let mut s = cur & 3;
    if arg < 0 {
        if arg == -1 && s == 1 {
            s = 2;
        }
    } else {
        s = (1u8.wrapping_sub(arg as u8)) & 3;
    }
    s
}

/// `CFieldSocket::CommandMenu(cmd, arg)` command codes (JP 0x003bf300).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum MenuCmd {
    /// 4: main menu (`CmdMenu` type 0; arg bit0 = allow-save, bit1 = hide-first-page)
    Main = 4,
    /// 5: `CmdMenuTutorial`
    Tutorial = 5,
    /// 6: `CmdMenu` type 8 (event-invoked sub-menu)
    SubMenu = 6,
    /// 0x10: save/load via `dataAccess`
    Save = 0x10,
}

/// Engine services `CFieldSocket` needs; implemented by the Bevy layer.
pub trait FieldHost {
    fn overlay_ready(&self) -> bool;
    fn begin_overlay_load(&mut self);
    fn load_script(&mut self, path: &str);
    fn load_sdb(&mut self, path: &str);
    fn start_battle(&mut self, map: &str);
}

/// The 0x6c-byte object (fields we actually reproduce).
#[derive(Debug, Clone)]
pub struct FieldSocket {
    pub phase_raw: u32,
    pub overlay_state: u32,
    pub entry_id: i32,
    /// `+0x58` map name buffer (char[16] + padding up to 0x68)
    pub map: String,
    pub faders: [Fader; 2],
    pub map_load: MapLoad,
    pub flags: u8,
    /// Retail only (`CFieldSocket+0x34/+0x38`, set by `InitFieldSocketCB`, US 0x003f4dc0): called once when the socket first reaches phase 4.
    pub start_callback: Option<StartCallback>,
}

/// Opaque `(function, argument)` pair stored by the retail `InitFieldSocketCB(cb, arg)` (the title/opening stage uses it to learn that
/// the first field map is up). The port keeps it as data; the host decides what the ids mean.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct StartCallback {
    pub func: u32,
    pub arg: u32,
}

/// What `Polling` does once the SDB (`CSTGDB.state == 2`) is ready.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SdbHandoff {
    /// Demo (JP 0x003bfb60): `ClearSDB(0)`, `InitSDB`, then `Restart` + `StartScript` when the load was a full map load (`map_load == MpsLoading`).
    Immediate { restart_script: bool },
    /// Retail (US 0x003f7000): `ClearSDB(0)`, then phase `0x40 | restart` and a loading-screen gadget (`new 0x2c` at US 0x00407380);
    /// `InitSDB` runs one or more frames later via [`retail_loading_done`].
    LoadingScreen { restart_script: bool },
}

/// Handoff chosen when the map data is ready; `map_load` is the low nibble of `m_flags` (4 = full load, 5 = `ReloadMPS`).
pub fn plan_handoff(build: crate::retail::Build, map_load: MapLoad) -> SdbHandoff {
    let restart_script = map_load == MapLoad::MpsLoading;
    if build.is_retail() {
        SdbHandoff::LoadingScreen { restart_script }
    } else {
        SdbHandoff::Immediate { restart_script }
    }
}

/// Retail phases with the loading gadget: `0x40` (reload only) / `0x41` (restart the script afterwards).
pub const PHASE_LOADING_SCREEN: u32 = 0x40;

/// Retail: the loading gadget finished (`FUN_00407530`): the fader slot 1 is raised to black (`SetFader(1, 1, 400)`) when it is not already
/// visible, then `InitSDB` runs, the script restarts if `phase & 1`, and the socket returns to phase 4. Returns `(raise_fader, restart_script)`.
pub fn retail_loading_done(phase: u32, fader1_displayed: bool) -> Option<(bool, bool)> {
    if phase & 0xf0 != PHASE_LOADING_SCREEN {
        return None;
    }
    Some((!fader1_displayed, phase & 1 != 0))
}

/// Retail world-map hand-over sub-states in phase `0x10 | n`: 0 delete the field, 1 start the world map (both builds), **8 = wait for the loading
/// gadget, then create the `worldMap` object** (retail only; the demo creates it directly in `WorldMapJumpA`).
pub const WORLDMAP_SUB_CREATE: u32 = 8;

impl FieldSocket {
    /// Retail `Polling` head: the first frame at phase < 4 moves to 4 and fires the start callback once.
    pub fn enter_running(&mut self) -> Option<StartCallback> {
        if self.phase_raw < 4 {
            self.phase_raw = 4;
            return self.start_callback.take();
        }
        None
    }
}

impl FieldSocket {
    /// JP: 0x003bd8e0 ctor + 0x003bd9c0 Init
    pub fn new(map: Option<&str>) -> Self {
        Self {
            phase_raw: 0,
            overlay_state: 0,
            entry_id: 0,
            map: map.unwrap_or("").to_string(),
            faders: [Fader::default(); 2],
            map_load: MapLoad::Idle,
            flags: 0,
            start_callback: None,
        }
    }
    pub fn phase(&self) -> Phase {
        Phase::from(self.phase_raw)
    }
    /// JP: 0x003bd980 SetMPS
    pub fn set_map(&mut self, m: &str) {
        if !m.is_empty() {
            self.map = m.to_string();
        }
    }
    /// JP: 0x003bf110 UpdateFader
    pub fn update_faders(&mut self, dt: u32) {
        for f in &mut self.faders {
            f.update(dt);
        }
    }
    /// JP: 0x003bf0a0 PauseFader(resume): bit4 of both slots' state byte = (resume == 0)
    pub fn pause_faders(&mut self, resume: bool) {
        for f in &mut self.faders {
            f.paused = !resume;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn retail_handoff_goes_through_the_loading_screen() {
        use crate::retail::Build;
        assert_eq!(plan_handoff(Build::Demo, MapLoad::MpsLoading), SdbHandoff::Immediate { restart_script: true });
        assert_eq!(plan_handoff(Build::Retail, MapLoad::MpsLoading), SdbHandoff::LoadingScreen { restart_script: true });
        assert_eq!(plan_handoff(Build::Retail, MapLoad::MpsReloading), SdbHandoff::LoadingScreen { restart_script: false });
        assert_eq!(retail_loading_done(0x41, false), Some((true, true)));
        assert_eq!(retail_loading_done(0x40, true), Some((false, false)));
        assert_eq!(retail_loading_done(4, true), None);
        let mut s = FieldSocket::new(Some("AP_00_U"));
        s.start_callback = Some(StartCallback { func: 1, arg: 2 });
        assert_eq!(s.enter_running(), Some(StartCallback { func: 1, arg: 2 }));
        assert_eq!(s.enter_running(), None);
        assert_eq!(s.phase_raw, 4);
    }

    #[test]
    fn fader_fade_out_runs() {
        let mut f = Fader::default();
        f.set(1, 10); // fade to opaque in 10 frames
        for _ in 0..10 {
            f.update(1);
        }
        assert_eq!(f.alpha, 0x80);
        assert_eq!(f.cur as i32, 10);
    }

    #[test]
    fn warp_state_machine() {
        assert_eq!(set_warp(0, 0), 1);
        assert_eq!(set_warp(1, -1), 2);
        assert_eq!(map_name("AP_00_U", true), "FIELD/MPS/AP_00_U.MPS");
    }
}

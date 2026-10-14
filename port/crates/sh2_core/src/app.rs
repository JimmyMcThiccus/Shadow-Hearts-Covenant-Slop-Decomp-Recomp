//! CApp (JP `app.cpp`) — the engine's main thread object.
//!
//! # CApp layout (0x150 bytes, allocated in `main`)
//! ```text
//! +0x00 CThread base (0x48; vtable @+0x44 = __vt__4CApp { +8 __dt, +0xc ExitInstance, +0x10 InitInstance, +0x14 Run })
//! +0x48 CPoller game0   +0x54 CPoller game1   +0x60 CPoller system
//! +0x6c DelayDeleteObject (CList@+0x6c, vtable@+0x74)  +0x78 CPause*   +0x7c ?
//! +0x80 ClutAdressControl (GsxRaster subclass, 0x20 bytes: ctor calls vtable+0x10(1,0x3eef,0,0x40,0x100))
//! +0xa0 FVector[10] (initialised by Run: [0]=[1]=(1/256, 1/256, DAT_0040a880, 0.875))
//! +0x140 u8 captureRequest
//! ```
//! Statics (JP .sbss/.bss): `app` 0x0040adfc, `m_scrw/m_scrh` 0x0040ae00/04 (u16), `camera` 0x0040ae08,
//! `m_pBright` 0x0040ae0c, `m_pAppFunc` 0x0040ae10, `m_vcount/hcount/ecount/wcount` 0x0040ae14/18/1c/20,
//! `m_capmd` 0x0040ae24, `m_capct` 0x0040ae28, `capTbl[60]` (60 screenshot slots), `rebootPath` 0x00430030 (0x80 B),
//! `m_World` 0x0042bf10 (0x4120 B).
//!
//! `main()` (JP 0x00221ea0): `FullAllocAndFree(); mwInit(); InitialReset(); SetRebootPath(argv[0]);
//! InitScreen(512, 448); app = new CApp(prio=1, flag=0xF, stack=0x10000); app->StartThread(); SleepThread(); mwExit();`
//! The CApp thread then runs `InitInstance` (`m_pPause = new CPause; InitMain()` => SSHMain + opening) and `Run`.
use std::path::PathBuf;
use std::time::Duration;

use crate::pause::CPause;
use crate::poller::{CPoller, DelayDeleteQueue};

#[cfg_attr(feature = "bevy", derive(bevy::prelude::Resource))]
#[derive(Debug, Clone)]
pub struct AppConfig {
    pub screen_w: u16, // CApp::m_scrw  JP 0x0040ae00
    pub screen_h: u16, // CApp::m_scrh  JP 0x0040ae04
    pub disc_dir: PathBuf,
}

/// CApp::m_vcount / m_hcount / m_wcount / m_ecount (JP 0x0040ae14..0x0040ae20)
#[cfg_attr(feature = "bevy", derive(bevy::prelude::Resource))]
#[derive(Debug, Default)]
pub struct AppStats {
    pub vcount: u64,
    pub hcount: u64,
    pub wcount: u64,
    pub ecount: u64,
    pub last_frame: Duration,
}

/// CApp::rebootPath (JP 0x00430030, 0x80 bytes) — `SetRebootPath(argv[0])`.
#[cfg_attr(feature = "bevy", derive(bevy::prelude::Resource))]
#[derive(Debug, Clone, Default)]
pub struct RebootPath(pub String);
impl RebootPath {
    // JP: 0x003d7150 SetRebootPath__4CAppFPc
    /// Original: skip a leading device prefix ("cdrom0:" / "host:", detected with `memcmp(arg, "cdrom", 5)`
    /// / `memcmp(arg, "host", 4)`) up to and including the first ':', store `"cdrom0:" + rest` (prefix string at
    /// JP `_1454`) and make sure the path ends with ';' (appends ";1").  `Reboot()` later passes it to `LoadExecPS2`.
    pub fn from_argv(argv0: Option<String>) -> Self {
        RebootPath(argv0.unwrap_or_default())
    }
}

/// Marker for entities queued in `DelayDeleteObject` (CApp+0x6c).
#[cfg_attr(feature = "bevy", derive(bevy::prelude::Component))]
pub struct DelayDelete;

/// `ScreenBright` (JP 0x003d8770): full-screen fade quad drawn last each frame.
/// `CApp::SetBright(f)` stores `(u8)(128 - clamp(f, ..1.0) * 128)` into `m_pBright+0x28` (the quad's alpha).
#[derive(Debug, Clone, Copy, Default)]
pub struct ScreenBright {
    pub alpha: u8,
}
impl ScreenBright {
    // JP: 0x003d7bf0 SetBright__4CAppFf
    pub fn set_bright(&mut self, f: f32) {
        let f = if f > 1.0 { 1.0 } else { f };
        self.alpha = (128.0 - f * 128.0) as i32 as u8;
    }
}

/// Hardware / renderer side of `CApp::Run`.  Everything that touched the GS, DMA, VSync or the capture
/// buffers in the original is a call on this trait so the Bevy layer can implement it.
pub trait AppBackend {
    /// `World::GetPacket`, `World::BeginUpdate`, `WorldRender`, `EndUpdate` (only when a camera is installed)
    fn world_update(&mut self, has_camera: bool);
    /// `ScreenBright::Draw`
    fn draw_bright(&mut self);
    /// `sceGsSyncPath(0,0)`
    fn gs_sync_path(&mut self);
    /// `GsxCamera::CaptureOut` – return an opaque capture handle (None when no camera/slot)
    fn capture_out(&mut self) -> Option<u32>;
    /// `Gsx::DrawSync(0,0)` – returns the hcount consumed (RCNT3)
    fn draw_sync(&mut self) -> u32;
    /// `Gsx::VSync(syncCount)` / `GsxForceFlip` when the frame took too long; returns nothing
    fn vsync_or_flip(&mut self);
    /// `DoReset()` — never returns on hardware (reboots through `LoadExecPS2`); the host decides what to do.
    fn do_reset(&mut self);
}

/// Per-frame hook `CApp::m_pAppFunc`.
pub type AppFunc = Box<dyn FnMut() + Send>;

/// The state `CApp::Run` loops over.
pub struct CApp {
    /// CApp+0x48
    pub game0: CPoller,
    /// CApp+0x54
    pub game1: CPoller,
    /// CApp+0x60 (SSHSys, CVibeMan, CPauser, FileIOLib's DvdromOrder live in system pollers)
    pub sys: CPoller,
    /// CApp+0x6c
    pub delay_delete: DelayDeleteQueue,
    /// CApp+0x78
    pub pause: CPause,
    pub bright: ScreenBright,
    pub app_func: Option<AppFunc>,
    pub has_camera: bool,
    /// CApp+0x140: capture requested this frame
    pub capture_req: bool,
    /// `m_capmd`: remaining continuous capture frames
    pub capture_mode: u8,
    /// `capTbl[60]`
    pub capture_tbl: [Option<u32>; 60],
    pub vcount: u64,
    pub hcount: u64,
    pub wcount: u32,
    pub ecount: u64,
}

impl Default for CApp {
    fn default() -> Self {
        CApp {
            game0: CPoller::new(),
            game1: CPoller::new(),
            sys: CPoller::new(),
            delay_delete: DelayDeleteQueue::default(),
            pause: CPause::new(),
            bright: ScreenBright::default(),
            app_func: None,
            has_camera: false,
            capture_req: false,
            capture_mode: 0,
            capture_tbl: [None; 60],
            vcount: 0,
            hcount: 0,
            wcount: 0,
            ecount: 0,
        }
    }
}

impl CApp {
    // JP: 0x003d7e00 isPaused__4CAppFv
    pub fn is_paused(&self) -> bool {
        self.pause.is_paused()
    }
    // JP: 0x003d7da0 Pause__4CAppFv
    pub fn pause(&mut self) {
        self.pause.pause();
    }
    // JP: 0x003d7dd0 Unpause__4CAppFv
    pub fn unpause(&mut self) {
        self.pause.unpause();
    }
    // JP: 0x003d7e60 Reset__4CAppFv
    pub fn reset(&mut self) {
        self.pause.request_reset();
    }
    // JP: 0x003d7cc0 CheckPause__4CAppFUiUi
    pub fn check_pause(&mut self, pad: u32, mask: u32) -> bool {
        self.pause.check_pause(pad, mask)
    }
    // JP: 0x003d7d30 CheckReset__4CAppFUiUiUi
    pub fn check_reset(&mut self, pad: u32, time: u32, mask: u32) -> bool {
        self.pause.check_reset(pad, time, mask)
    }

    /// One iteration of `CApp::Run` (JP 0x003d7730).  Order is exactly the original:
    ///
    /// 1. `World::BeginUpdate/WorldRender/EndUpdate` (if `camera != 0`)
    /// 2. system poller; if **not paused**: game poller 0 then 1
    /// 3. `m_pAppFunc()`
    /// 4. `World::GetPacket`, `ScreenBright::Draw`, `sceGsSyncPath`
    /// 5. drain the DelayDelete list (virtual dtors)
    /// 6. screenshot bookkeeping (`m_capmd`, `capTbl`)
    /// 7. `Gsx::DrawSync`, counters, VSync / forced flip, `UpdatePolBreakState`
    /// 8. if `pause.flags & 8` => `DoReset()`
    pub fn run_frame(&mut self, hw: &mut dyn AppBackend) {
        hw.world_update(self.has_camera);
        self.sys.polling();
        if !self.pause.is_paused() {
            self.game0.polling();
            self.game1.polling();
        }
        if let Some(f) = self.app_func.as_mut() {
            f();
        }
        hw.draw_bright();
        hw.gs_sync_path();
        self.delay_delete.flush();
        if self.capture_mode != 0 {
            self.capture_mode -= 1;
            self.capture_req = true;
        }
        if self.capture_req && self.has_camera {
            // find first free slot of 60; "printf(overflow)" when full
            if let Some(slot) = self.capture_tbl.iter().position(|s| s.is_none()) {
                self.capture_tbl[slot] = hw.capture_out();
            }
            self.capture_req = false;
        }
        let used = hw.draw_sync();
        self.hcount += used as u64;
        if used > self.wcount {
            self.wcount = used;
        }
        self.vcount += 1;
        hw.vsync_or_flip();
        if self.pause.reset_requested() {
            hw.do_reset();
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[derive(Default)]
    struct Hw {
        resets: u32,
        frames: u32,
    }
    impl AppBackend for Hw {
        fn world_update(&mut self, _: bool) {
            self.frames += 1;
        }
        fn draw_bright(&mut self) {}
        fn gs_sync_path(&mut self) {}
        fn capture_out(&mut self) -> Option<u32> {
            Some(1)
        }
        fn draw_sync(&mut self) -> u32 {
            100
        }
        fn vsync_or_flip(&mut self) {}
        fn do_reset(&mut self) {
            self.resets += 1;
        }
    }

    #[test]
    fn frame_counters_and_reset() {
        let mut app = CApp::default();
        let mut hw = Hw::default();
        app.run_frame(&mut hw);
        app.reset();
        app.run_frame(&mut hw);
        assert_eq!(app.vcount, 2);
        assert_eq!(app.hcount, 200);
        assert_eq!(hw.resets, 1);
    }

    #[test]
    fn bright() {
        let mut b = ScreenBright::default();
        b.set_bright(0.5);
        assert_eq!(b.alpha, 64);
        b.set_bright(2.0);
        assert_eq!(b.alpha, 0);
    }
}

//! Boot glue: `main`, `InitMain`, `SSHMain`, `SSHLoadModules`, `GetLanguage`, `DoReset`, C runtime (documentation + constants).
//!
//! ```text
//! _start (0x00200008, crt0) -> InitTLB (0x00212f30: GetMemorySize()==32MB ? InitTLB32MB() : _InitTLB())
//!                           -> supplement_crt0 (0x00213540: CreateSema x2 => __sce_sema_id, __sce_eh_sema_id; both count 1/1/1)
//!                           -> main (0x00221ea0)
//! main: FullAllocAndFree(); mwInit() [= __initialize_cpp_rts(0x404920, 0x404998, 0x40a830, 0x40a830) : run the static ctor table];
//!       CApp::InitialReset() [empty]; CApp::SetRebootPath(argv[0]); CApp::InitScreen(0x200, 0x1c0);
//!       app = new CApp(1, 0xF, 0x10000); app->StartThread(); SleepThread(); mwExit() [run global destructor chain].
//! InitScreen: memset(capTbl,0,0xf0); Gsx::Initialize(); CTimer::InitialReset(GS CSR bits 16..23 (video mode) as "short"):
//!             RCNT0 target = 0x823 (NTSC/PAL < 7) or 0x249f (else), mode 0xdd1, INTC 9 handler = TimerWatcher0;
//!             CThread::InitialReset(); Gsx::Open(0x200,0x1c0,0x18,0x18,0x21); Gsx::Start(); m_scrw/m_scrh; new ScreenBright.
//! InitMain = SSHMain() && opening();
//! SSHMain: sprintf(path,"<fmt>", "IOPRP271.IMG"/region dir); sceSifInitRpc; sceCdInit; sceCdMmode(1);
//!          do sceSifRebootIop(path) while(!ok); do sceSifSyncIop while(!ok); sceSifInitRpc; sceCdInit; sceCdMmode(1);
//!          sceSifInitIopHeap(); sceFsReset(); SSHLoadModules(pass1: SIO2MAN MCMAN MCSERV PADMAN) && SSHLoadModules(pass2: IOPUTY FIO LIBSD SDRV_IOP);
//!          SSHSys::PathInit() [pDataPath = "", Language = GetLanguage()]; FileIOLib::PluginAttach() [new FileIOLib(0x13ae8) + Initialize + StartThread
//!          + new DvdromOrder]; Sdrv::Reset(0); sys = new SSHSys(0xb0); sys->Initialize().
//! SSHSys::Initialize (0x003b68d0): SysTool::Initialize [two CTimers, CPause callback]; CPad::Initialize(0,0); new CPad(0)+Enable (mode _6412);
//!          lastTime = GetTimer(); initPhase = 1; Entry(system poller, prio 0x40); CPause::SetCallBack(SSHSys::CBPause, this);
//!          Overlay::Init(1) [group 1 = FIELD]; pSysSE = BlockRead("COMMON/SYSREG.SSE") -> Sdrv::AutoLoad;
//!          Model::Initialize(); RegDatApi::Initialize(); spin until CheckRegDat(); JRing::SystemInitialize(); new BgEffectMan+Init;
//!          LoadFieldData() [reads "<pDataPath>COMMON/SVP.BIN"-like blob via cbRead into pFldData]; Sdrv::SetReverb x2, CreateSoundBuffer(0x200000);
//!          LSDPlayer::InitialReset(); new BtlSaveSec; InitFieldSaveData(); BtlSaveSec::SetSceneInit(0,0); MenuObj::Initialize();
//!          new CVibeMan(700) + Create(0).
//! opening: SetAPI(new CDMYStage(0x60)).
//! DoReset (0x003b7410): Sdrv::Reset(2); CPad::ResetSystem(); FileIOLib::ResetSystem(); Gsx::Close/Reset; sceDmaReset; scePadEnd;
//!          sceSifExitCmd; CApp::SystemReset() [CTimer::SystemReset]; CApp::Reboot() [LoadExecPS2(rebootPath)].
//! ```
//! SSHLoadModules list word semantics: see [`crate::ssh_sys::IOP_MODULES_PASS1`].

/// `GetLanguage` (JP 0x003b5f60): `sceScfGetLanguage()` -> game language index into `SysTool::LocalPath`
/// (index 0 = "", 1 "JPN/", 2 "USA/", 3 "GBR/", 4 "FRA/", 5 "GER/", 6 "ITA/", 7 "SPA/").
pub fn get_language(scf_language: i64) -> usize {
    match scf_language {
        1 => 2, // English -> USA
        2 => 4, // French
        3 => 7, // Spanish
        4 => 5, // German
        5 => 6, // Italian
        _ => 1, // Japanese (0) and anything else
    }
}

/// `CApp::InitScreen` RCNT0 target (JP 0x003d5a60 `CTimer::InitialReset(short mode)`): 0x823 for modes < 7 else 0x249f.
pub fn rcnt0_target(video_mode: i16) -> u32 {
    if video_mode < 7 { 0x823 } else { 0x249f }
}

/// Rust-side stand-in for `main()`'s screen constants.
pub const SCREEN_W: u16 = 0x200;
pub const SCREEN_H: u16 = 0x1c0;
pub const APP_THREAD_PRIORITY: u16 = 1;
pub const APP_THREAD_FLAG: u16 = 0xf;
pub const APP_STACK_SIZE: u32 = 0x10000;
pub const SSHSYS_POLL_PRIORITY: u16 = 0x40;

// ----------------------------------------------------------------------------------------------------
// US retail (SLUS_210.41) differences, see notes/I/us_delta.md
// ----------------------------------------------------------------------------------------------------

/// Which executable the boot path is modelled after.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
#[repr(u8)]
pub enum Region {
    /// Furokuban demo `SLPM_602.19`
    #[default]
    Jp = 0,
    /// US retail `SLUS_210.41` (`.NA` data names, OPENING.BIN title overlay)
    Us = 1,
}

impl Region {
    /// `--us` / `SH2_BUILD=retail` on the command line / in the environment selects the retail disc.
    pub fn from_args_env(args: impl IntoIterator<Item = String>) -> Region {
        let by_arg = args.into_iter().any(|a| a == "--us" || a == "--retail");
        let by_env = std::env::var("SH2_BUILD").map(|v| matches!(v.to_ascii_lowercase().as_str(), "retail" | "us" | "usa" | "na")).unwrap_or(false);
        if by_arg || by_env {
            Region::Us
        } else {
            Region::Jp
        }
    }
    pub fn is_retail(self) -> bool {
        self == Region::Us
    }
    /// Environment variable that names this region's disc folder.
    pub fn disc_env(self) -> &'static str {
        match self {
            Region::Jp => "SH2_DISC_DIR",
            Region::Us => "SH2_US_DISC_DIR",
        }
    }
}

static ACTIVE_REGION: std::sync::atomic::AtomicU8 = std::sync::atomic::AtomicU8::new(0);

/// The build the running process is modelled after.  Set once by `sh2_app::main` (`--us`); every crate that has to know whether
/// it is playing the JP demo or the US retail disc (title flow, `GetRegDat` kind map, new-game defaults, world map) asks here.
pub fn set_active_region(r: Region) {
    ACTIVE_REGION.store(r as u8, std::sync::atomic::Ordering::Relaxed);
}
pub fn active_region() -> Region {
    match ACTIVE_REGION.load(std::sync::atomic::Ordering::Relaxed) {
        1 => Region::Us,
        _ => Region::Jp,
    }
}
/// `active_region() == Region::Us`
pub fn is_retail() -> bool {
    active_region().is_retail()
}

/// Bevy handle for the same information (inserted by `sh2_app`).
#[cfg(feature = "bevy")]
#[derive(bevy::prelude::Resource, Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct ActiveBuild(pub Region);

/// Message / data tables read by `RegDatApi::Initialize`: JP `common/sshmes.jpn` + `common/sshdat.jpn`, US `common/sshmes.na`
/// + `common/sshdat.na` (rodata 0x00434580 / 0x004345a0 in SLUS_210.41).  The US disc still carries the `.JPN` files but the
/// US executable has no reference to them (there are no `JPN/`, `USA/` ... language directories either, so the
/// `SysTool::AddLocalPath` fallback never fires on the retail disc).
pub const SSHMES_JP: &str = "common/sshmes.jpn";
pub const SSHDAT_JP: &str = "common/sshdat.jpn";
pub const SSHMES_NA: &str = "common/sshmes.na";
pub const SSHDAT_NA: &str = "common/sshdat.na";

impl Region {
    pub fn sshmes(self) -> &'static str {
        match self {
            Region::Jp => SSHMES_JP,
            Region::Us => SSHMES_NA,
        }
    }
    pub fn sshdat(self) -> &'static str {
        match self {
            Region::Jp => SSHDAT_JP,
            Region::Us => SSHDAT_NA,
        }
    }
    /// `FileIOLib+0x13944` default volume label (JP "DEFAULT" / US "NotSetDiskName", rodata 0x00432628).
    pub fn default_volume_label(self) -> &'static str {
        match self {
            Region::Jp => "DEFAULT",
            Region::Us => "NotSetDiskName",
        }
    }
    /// `sceCdMmode(mode)` argument used by `SSHMain` (both calls): JP demo on CD (1), US retail on DVD-ROM (2).  The IOP image
    /// and the two module lists (`SIO2MAN MCMAN MCSERV PADMAN` / `IOPUTY FIO LIBSD SDRV_IOP`) are identical in both builds.
    pub fn cd_media_mode(self) -> i32 {
        match self {
            Region::Jp => 1,
            Region::Us => 2,
        }
    }
    /// Title scene the boot ends in: JP `CDMYStage` hosting the main-image `openingMessage`; US `CDMYStage` hosting the
    /// `OPENING.BIN` overlay (loaded by `CDMYStage::preLoad`, `Overlay::Load("OPENING.BIN")`, group 3).
    pub fn title_overlay(self) -> Option<&'static str> {
        match self {
            Region::Jp => None,
            Region::Us => Some("OPENING.BIN"),
        }
    }
}

/// US `GetLanguage` (0x003ed470).  Returns `0x10 + <JP GetLanguage value>` (0x11 JP, 0x12 EN, 0x14 FR, 0x15 DE, 0x16 IT, 0x17 ES),
/// default 0x12.  `scf_language` is the value of the (inlined) `sceScfGetLanguage` -- see [`us_scf_language`].
pub fn get_language_us(scf_language: i64) -> u8 {
    match scf_language {
        0 => 0x11,
        1 => 0x12,
        2 => 0x14,
        3 => 0x17,
        4 => 0x15,
        5 => 0x16,
        _ => 0x12,
    }
}

/// The US build inlines `sceScfGetLanguage` (0x00239430) and adds a tool override: when the BIOS region letter
/// (`rom0:ROMVER`, 0x002393f0) is `'T'` the language comes from a debug variable instead of the OSD config.
/// `osd` is `GetOsdConfigParam()`: bits 13..15 = version, bits 16..20 = language, bit 4 = old 1-bit language.
pub fn us_scf_language(osd: u32, tool_region_t: bool, tool_override: u32) -> u32 {
    if tool_region_t {
        tool_override
    } else if (osd >> 13) & 7 == 0 {
        (osd >> 4) & 1
    } else {
        (osd >> 16) & 0x1f
    }
}

/// Retail `SSHSys::GetFullPathName` (0x003edc40) takes the language directory index from the MENU save section
/// (`sm_pSubstance->data + 0x18`, default `1` written by `SaveMenuSection::SetDefault`) instead of `SSHSys::Language`
/// (which `PathInit` still writes, as a byte at 0x0043fdfc, but nothing reads any more).
pub const MENU_LANGUAGE_DEFAULT: u32 = 1;

#[cfg(test)]
mod us_tests {
    use super::*;

    #[test]
    fn us_language_codes() {
        assert_eq!(get_language_us(0), 0x11);
        assert_eq!(get_language_us(1), 0x12);
        assert_eq!(get_language_us(2), 0x14);
        assert_eq!(get_language_us(3), 0x17);
        assert_eq!(get_language_us(4), 0x15);
        assert_eq!(get_language_us(5), 0x16);
        assert_eq!(get_language_us(99), 0x12);
        // every code is the JP value + 0x10
        for (scf, jp) in [(0, 1u8), (1, 2), (2, 4), (3, 7), (4, 5), (5, 6)] {
            assert_eq!(get_language_us(scf), 0x10 + jp);
            assert_eq!(get_language(scf) as u8, jp);
        }
    }

    #[test]
    fn us_osd_language_decode() {
        // old-style config word (version field 0): language is bit 4
        assert_eq!(us_scf_language(0x10, false, 9), 1);
        assert_eq!(us_scf_language(0x00, false, 9), 0);
        // new-style: bits 16..20
        assert_eq!(us_scf_language(0x0002_2000, false, 9), 2); // version 1 (bit 13), language field 2
        assert_eq!(us_scf_language(0, true, 3), 3);
    }

    #[test]
    fn region_data_names() {
        assert_eq!(Region::Jp.sshmes(), "common/sshmes.jpn");
        assert_eq!(Region::Us.sshmes(), "common/sshmes.na");
        assert_eq!(Region::Us.sshdat(), "common/sshdat.na");
        assert_eq!(Region::Us.title_overlay(), Some("OPENING.BIN"));
        assert_eq!(Region::Jp.title_overlay(), None);
        assert_eq!((Region::Jp.cd_media_mode(), Region::Us.cd_media_mode()), (1, 2));
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn lang() {
        assert_eq!(get_language(1), 2);
        assert_eq!(get_language(0), 1);
        assert_eq!(rcnt0_target(2), 0x823);
        assert_eq!(rcnt0_target(7), 0x249f);
    }
}

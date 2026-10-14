//! Global addresses and struct offsets per build.  JP = Furokuban demo `SLPM_602.19` (symbols/SLPM_602.19.syms), US = retail `SLUS_210.41`
//! (gp = 0x004479f0; globals found through the gp-relative accesses in Ghidra, see notes/integration/pine_validation.md).
//!
//! Only things that were read from code are filled in; `None` means "not located yet".

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Region {
    Jp,
    Us,
}

/// Which `SSHApi` subclass is current (identified through the destructor in vtable slot +8).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ApiKind {
    /// title / opening (`CDMYStage`)
    Title,
    Field,
    Battle,
    GameOver,
    Other(u32),
    None,
}

#[derive(Debug, Clone, Copy)]
pub struct Globals {
    /// `SSHSys::sys` (pointer)
    pub sys: u32,
    /// `CApp::app` (pointer)
    pub app: u32,
    /// `CField*` (`CFieldSocket::fld`)
    pub fld: u32,
    /// `CFieldSocket*`
    pub socket: u32,
    /// `Sys__7CBattle` (pointer)
    pub battle: u32,
    /// `BtlSocket::ourBtlSocket` (pointer)
    pub btl_socket: u32,
    /// `CPad::m_pCoreArray[2]` (two pointers)
    pub pad_cores: u32,
    /// first CApp counter (frames drawn); the u32 counters follow: frames, gs ticks, ...
    pub app_frame_counter: u32,
    /// pointer to the libc reent struct whose +0xa8 is the 64-bit `rand()` state
    pub rand_reent: Option<u32>,
    /// `JRing::JRTop` (head of the live ring list)
    pub jring_top: Option<u32>,
    /// vtable +8 destructor addresses of the SSHApi subclasses: (title, field, battle, gameover)
    pub api_dtors: [u32; 4],
}

#[derive(Debug, Clone, Copy)]
pub struct Layout {
    // CField
    pub f_state: u32,
    pub f_entry_id: u32,
    /// first of the flag bytes (JP 0x18c; US 0x178), `n` bytes
    pub f_flags: u32,
    pub f_model_count: u32,
    pub f_floor: u32,
    pub f_camera: u32,
    pub f_models: u32,
    pub f_cam_pos: u32,
    pub f_cam_angle: u32,
    pub f_player_pos: u32,
    pub f_gsx_pos: u32,
    pub f_gsx_at: u32,
    // CFieldModel
    pub m_pos: u32,
    pub m_rot: u32,
    pub m_move_rot: u32,
    pub m_last_trans: u32,
    /// state bytes (display mode, gait, move mode, ...), 12 bytes
    pub m_state: u32,
    pub m_walked: u32,
    pub m_motion_name: u32,
    pub m_slope: u32,
    // CBattle
    pub b_chr_stride: u32,
}

pub const JP_GLOBALS: Globals = Globals {
    sys: 0x0040ad60,
    app: 0x0040adfc,
    fld: 0x0040ad94,
    socket: 0x0040ad94, // JP: `fld__12CFieldSocket` is the CField*; the socket global is not needed for the dumps
    battle: 0x0040af24,
    btl_socket: 0x0040acac,
    pad_cores: 0x0040ac00,
    app_frame_counter: 0x0040ae14,
    rand_reent: Some(0x003f8338),
    jring_top: Some(0x0040ac8c),
    api_dtors: [0x003a7fa0, 0x003bda80, 0x0032d860, 0x003ac140],
};

pub const US_GLOBALS: Globals = Globals {
    sys: 0x0043fdf8,
    app: 0x0043fea0,
    fld: 0x0043ff34,
    socket: 0x0043fe2c,
    battle: 0x00440000,
    btl_socket: 0x0043fd5c,
    pad_cores: 0x0043fca8,
    app_frame_counter: 0x0043feb8,
    rand_reent: Some(0x0042d248),
    jring_top: Some(0x0043fd38), // gp - 0x7cb8 (JRing::Entry 0x331160); layout identical to the JP JRing (live-verified)
    api_dtors: [0x00415dc0, 0x003f5710, 0x003652d0, 0x003e3f10],
};

pub const JP_LAYOUT: Layout = Layout {
    f_state: 0x28,
    f_entry_id: 0x2a,
    f_flags: 0x18c,
    f_model_count: 0x192,
    f_floor: 0x1b8,
    f_camera: 0x1bc,
    f_models: 0x1c0,
    f_cam_pos: 0x1cd0,
    f_cam_angle: 0x1ce0,
    f_player_pos: 0x1cf0,
    f_gsx_pos: 0x1d10,
    f_gsx_at: 0x1d20,
    m_pos: 0x10,
    m_rot: 0x20,
    m_move_rot: 0x30,
    m_last_trans: 0x40,
    m_state: 0x80,
    m_walked: 0x194,
    m_motion_name: 0x2cc,
    m_slope: 0x2b0,
    b_chr_stride: 0x4f0,
};

pub const US_LAYOUT: Layout = Layout {
    f_state: 0x28,
    f_entry_id: 0x2a,
    f_flags: 0x178,
    f_model_count: 0x18a,
    f_floor: 0x1b0,
    f_camera: 0x1b4,
    f_models: 0x1b8,
    f_cam_pos: 0x2110,
    f_cam_angle: 0x2120,
    f_player_pos: 0x2130,
    f_gsx_pos: 0x2150,
    f_gsx_at: 0x2160,
    m_pos: 0x10,
    m_rot: 0x20,
    m_move_rot: 0x30,
    m_last_trans: 0x40,
    m_state: 0x90,
    m_walked: 0x1b4,
    m_motion_name: 0x31c,
    m_slope: 0x310,
    b_chr_stride: 0x510,
};

impl Region {
    pub fn globals(self) -> &'static Globals {
        match self {
            Region::Jp => &JP_GLOBALS,
            Region::Us => &US_GLOBALS,
        }
    }
    pub fn layout(self) -> &'static Layout {
        match self {
            Region::Jp => &JP_LAYOUT,
            Region::Us => &US_LAYOUT,
        }
    }
}

/// Is `a` a plausible EE RAM pointer (main RAM, 32 MiB)?
pub fn is_ptr(a: u32) -> bool {
    (0x0010_0000..0x0200_0000).contains(&a) && a % 4 == 0
}

/// Offsets of the US build that were measured live (notes/integration/pine_us_refinement.md sections 6-9).
pub mod us_live {
    /// `SSHSys` (0x749500): request byte (0x10 field, 0x20 / 0x21 battle armed / go, 0x30 game over, 0x40 title).
    pub const SYS_REQUEST: u32 = 0x36;
    /// `_SysBtlParam` at `SSHSys+0x40`: `+0 u32 w0` (the background id, 77 in the tower hall / corridor), `+4 u32 MONSETTbl index`, `+8 u16 bgm`,
    /// `+0xa u8 pc count`, `+0xb u8 monster-set count`, `+0xc u8 pc[4]`.  Writing the index and request 0x21 starts that battle straight from the field.
    pub const SYS_BTL_PARAM: u32 = 0x40;
    /// next field map name (`char[0x14]`) at `SSHSys+0x58` (request 0x10)
    pub const SYS_FIELD_NAME: u32 = 0x58;
    /// `CFieldSocket+0x64`: current map name (rewritten by every `FieldMapJump`)
    pub const SOCKET_MAP_NAME: u32 = 0x64;
    /// `CBattle` (US): phase u16 `+0x28`, step u16 `+0x2a`, actor i8 `+0x2c`, turn counter i32 `+0x40`, `bNoEvade` `+0x4866`.
    pub const BTL_PHASE: u32 = 0x28;
    pub const BTL_STEP: u32 = 0x2a;
    pub const BTL_ACTOR: u32 = 0x2c;
    pub const BTL_TURN_NO: u32 = 0x40;
    /// monster-set formation u16 and the six monster ids (u16, 0xffff = empty): JP `+0x43a4` / `+0x43a6` + 0x2a2.
    pub const BTL_FORMATION: u32 = 0x4646;
    pub const BTL_MON_IDS: u32 = 0x4648;
    /// result record: EXP `+0x48b4`, cash `+0x48b8`, sanity points `+0x48bc` (all u32; JP `+0x4610..` + 0x2a4).  The victory screen shows the same numbers.
    pub const BTL_REWARD_EXP: u32 = 0x48b4;
    pub const BTL_REWARD_CASH: u32 = 0x48b8;
    pub const BTL_REWARD_SP: u32 = 0x48bc;
    /// `BtlChr` (stride 0x510, base `CBattle+0xb0`), offsets relative to the slot: the cached stats that `GetEvasionRate` / `GetCriticalRate` /
    /// `GetPAtkDamage` read.  AGL is truncated to its low byte by the game when it refreshes the cache; LUC keeps 16 bits.
    pub const CHR_FLAGS_A: u32 = 0x00;
    pub const CHR_FLAGS_B: u32 = 0x04;
    pub const CHR_STATE: u32 = 0x08;
    pub const CHR_FORMATION: u32 = 0x0c;
    pub const CHR_MAX_HP: u32 = 0x7c;
    pub const CHR_HP: u32 = 0x80;
    pub const CHR_SP: u32 = 0x8a;
    pub const CHR_AGL: u32 = 0x8c;
    pub const CHR_LUC: u32 = 0x8e;
    pub const CHR_PATK: u32 = 0x90;
    pub const CHR_PDEF: u32 = 0x94;
    pub const CHR_TURN_TIMER: u32 = 0xd4;
    pub const CHR_TURN_INTERVAL: u32 = 0xe0;
    pub const CHR_VULN_COUNT: u32 = 0x460;
    pub const CHR_LAST_DAMAGE: u32 = 0x462;
    pub const CHR_VARIANCE: u32 = 0x46c;
}

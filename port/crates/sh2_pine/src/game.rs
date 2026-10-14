//! Typed readers for the game's runtime structures.  Everything is a *snapshot*: one call reads a handful of fields serially.
//! All offsets are documented in `notes/integration/pine_validation.md`; US offsets that were not confirmed against retail code carry a
//! `verified` flag or are `Option`.

use crate::addr::*;
use crate::client::{Mem, Result};

pub fn detect_region<M: Mem>(m: &mut M) -> Option<Region> {
    let a = m.r32(0x0021f6c0).ok()?;
    let b = m.r32(0x00221ea0).ok()?;
    match (a, b) {
        (0xfc64_0000, 0x27bd_ffc0) => Some(Region::Jp),
        (0x27bd_ffc0, 0x1460_ffed) => Some(Region::Us),
        _ => None,
    }
}

#[derive(Debug, Clone, Copy, Default, PartialEq)]
pub struct V4(pub [f32; 4]);
impl V4 {
    pub fn xyz(&self) -> [f32; 3] {
        [self.0[0], self.0[1], self.0[2]]
    }
}

// ---------------------------------------------------------------------------------------------------- SSHSys
#[derive(Debug, Clone)]
pub struct SshSysSnap {
    pub addr: u32,
    /// `SysTool` game clock in ms (+0x1c)
    pub timer_ms: i32,
    /// frame delta in ms (+0x20)
    pub delta_ms: i32,
    pub pending_api: u32,
    pub current_api: u32,
    pub current_kind: ApiKind,
    pub pad: u32,
    pub init_phase: u32,
    /// +0x34 pending state (0 none, 1 preLoad requested, 2 ready)
    pub pend_state: u8,
    /// +0x35 current state (0 run, 3 closeInquiry requested, 4 closed)
    pub cur_state: u8,
    /// +0x36 request (0x10 field, 0x20/0x21 battle, 0x30 game over, US 0x40 title)
    pub request: u8,
    pub fio_busy: u8,
    /// `_SysBtlParam` (+0x40, 0x10 bytes)
    pub btl_param: [u8; 16],
    pub btl_result: [u8; 4],
    pub next_field: String,
}

pub fn read_sys<M: Mem>(m: &mut M, r: Region) -> Result<Option<SshSysSnap>> {
    let g = r.globals();
    let a = m.r32(g.sys)?;
    if !is_ptr(a) {
        return Ok(None);
    }
    let cur = m.r32(a + 0x28)?;
    let kind = if cur == 0 {
        ApiKind::None
    } else {
        // SSHApi vtable pointer at +4, destructor at slot +8
        let vt = m.r32(cur + 4)?;
        if is_ptr(vt) {
            let dt = m.r32(vt + 8)?;
            let d = g.api_dtors;
            if dt == d[0] {
                ApiKind::Title
            } else if dt == d[1] {
                ApiKind::Field
            } else if dt == d[2] {
                ApiKind::Battle
            } else if dt == d[3] {
                ApiKind::GameOver
            } else {
                ApiKind::Other(dt)
            }
        } else {
            ApiKind::Other(vt)
        }
    };
    let hdr = m.read_bytes(a + 0x34, 4)?;
    let mut btl_param = [0u8; 16];
    btl_param.copy_from_slice(&m.read_bytes(a + 0x40, 16)?);
    let mut btl_result = [0u8; 4];
    btl_result.copy_from_slice(&m.read_bytes(a + 0x50, 4)?);
    Ok(Some(SshSysSnap {
        addr: a,
        timer_ms: m.r32(a + 0x1c)? as i32,
        delta_ms: m.r32(a + 0x20)? as i32,
        pending_api: m.r32(a + 0x24)?,
        current_api: cur,
        current_kind: kind,
        pad: m.r32(a + 0x2c)?,
        init_phase: m.r32(a + 0x30)?,
        pend_state: hdr[0],
        cur_state: hdr[1],
        request: hdr[2],
        fio_busy: hdr[3],
        btl_param,
        btl_result,
        next_field: m.cstr(a + 0x54, 0x14)?,
    }))
}

// ---------------------------------------------------------------------------------------------------- CApp
#[derive(Debug, Clone)]
pub struct AppSnap {
    pub addr: u32,
    pub scr_w: u16,
    pub scr_h: u16,
    /// the u32 at `app_frame_counter`: +1 per frame that went through DrawSync (the `vcount`-style frame counter)
    pub frames: u32,
    /// the three following u32 accumulators (GS busy ticks, max, ...) as `CApp::m_hcount/m_ecount/m_wcount`
    pub counters: [u32; 3],
    /// `CPause::flags` of `app+0x78` (b0 paused, b1 pausing, b2 unpausing, b3 reset)
    pub pause_flags: u8,
}

pub fn read_app<M: Mem>(m: &mut M, r: Region) -> Result<Option<AppSnap>> {
    let g = r.globals();
    let a = m.r32(g.app)?;
    if !is_ptr(a) {
        return Ok(None);
    }
    let w = m.r16(g.app + 4)?;
    let h = m.r16(g.app + 6)?;
    let frames = m.r32(g.app_frame_counter)?;
    let counters = [m.r32(g.app_frame_counter + 4)?, m.r32(g.app_frame_counter + 8)?, m.r32(g.app_frame_counter + 12)?];
    let pause = m.r32(a + 0x78)?;
    let pause_flags = if is_ptr(pause) { m.r8(pause)? } else { 0 };
    Ok(Some(AppSnap { addr: a, scr_w: w, scr_h: h, frames, counters, pause_flags }))
}

// ---------------------------------------------------------------------------------------------------- CPad
#[derive(Debug, Clone, Default)]
pub struct StickSnap {
    pub up: u8,
    pub down: u8,
    pub left: u8,
    pub right: u8,
    pub gauge: f32,
    pub radian: f32,
    pub degree: f32,
}

#[derive(Debug, Clone, Default)]
pub struct PadSnap {
    pub core: u32,
    pub prev_real: u16,
    pub real: u16,
    pub press: u16,
    pub release: u16,
    pub repeat: u16,
    pub left: StickSnap,
    pub right: StickSnap,
}

pub fn read_pad<M: Mem>(m: &mut M, r: Region, port: u32) -> Result<Option<PadSnap>> {
    let core = m.r32(r.globals().pad_cores + 4 * port)?;
    if !is_ptr(core) {
        return Ok(None);
    }
    let b = m.read_bytes(core + 0x68, 0x10)?;
    let u = |o: usize| u16::from_le_bytes([b[o], b[o + 1]]);
    let stick = |m: &mut M, a: u32| -> Result<StickSnap> {
        let s = m.read_bytes(a, 16)?;
        let f = |o: usize| f32::from_le_bytes([s[o], s[o + 1], s[o + 2], s[o + 3]]);
        Ok(StickSnap { up: s[0], down: s[1], left: s[2], right: s[3], gauge: f(4), radian: f(8), degree: f(12) })
    };
    Ok(Some(PadSnap {
        core,
        prev_real: u(0),
        real: u(2),
        press: u(4),
        release: u(6),
        repeat: u(8),
        left: stick(m, core + 0x78)?,
        right: stick(m, core + 0x88)?,
    }))
}

// ---------------------------------------------------------------------------------------------------- RNG
/// The game's `rand()`: 64-bit LCG state in the libc reent (`reent + 0xa8`): `s = s * 6364136223846793005 + 1; return (s >> 32) & 0x7fffffff`
/// (disassembly of US 0x00232cc8: `dmult`/`daddiu 1`/`dsrl32`/`and 0x7fffffff`).
pub fn read_rand_state<M: Mem>(m: &mut M, r: Region) -> Result<Option<u64>> {
    match r.globals().rand_reent {
        Some(p) => {
            let reent = m.r32(p)?;
            if is_ptr(reent) {
                Ok(Some(m.r64(reent + 0xa8)?))
            } else {
                Ok(None)
            }
        }
        None => Ok(None),
    }
}

pub const RAND_MUL: u64 = 6364136223846793005;
pub fn rand_next(state: &mut u64) -> i32 {
    *state = state.wrapping_mul(RAND_MUL).wrapping_add(1);
    ((*state >> 32) & 0x7fff_ffff) as i32
}

/// How many `rand()` calls happened between two readings of the state (0..max), if any.
pub fn rand_steps(from: u64, to: u64, max: u32) -> Option<u32> {
    let mut s = from;
    for i in 0..=max {
        if s == to {
            return Some(i);
        }
        rand_next(&mut s);
    }
    None
}

// ---------------------------------------------------------------------------------------------------- CField
#[derive(Debug, Clone)]
pub struct ModelSnap {
    pub addr: u32,
    pub pos: V4,
    pub rot: V4,
    pub move_rot: V4,
    pub last_trans: V4,
    pub state: [u8; 12],
    pub walked: f32,
    pub motion: String,
    pub slope: f32,
}

#[derive(Debug, Clone)]
pub struct CameraSnap {
    pub addr: u32,
    pub flags: u8,
    pub roll: f32,
    pub trans_left: f32,
    pub trans_len: f32,
    pub view_angle: f32,
    pub delay: f32,
    pub target: V4,
    pub pos: V4,
    /// composed target / camera actually used (+0x70 / +0x80)
    pub comp_target: V4,
    pub comp_pos: V4,
    /// pitch / yaw / roll (deg, +180 offset) +0xc0..
    pub pitch: f32,
    pub yaw: f32,
    pub roll2: f32,
}

#[derive(Debug, Clone)]
pub struct FieldSnap {
    pub addr: u32,
    pub state: u16,
    pub entry_id: i16,
    /// raw flag bytes (JP 0x18c.., US 0x178..), 8 bytes
    pub flags: [u8; 8],
    pub model_count: u8,
    pub floor: u32,
    /// cached last-hit floor triangle (`CFloorMan+0x10`)
    pub floor_cached_tri: u32,
    pub floor_slice_count: u32,
    pub cam_pos: V4,
    pub cam_angle: V4,
    pub player_pos: V4,
    pub gsx_pos: V4,
    pub gsx_at: V4,
    pub ctrl: Option<ModelSnap>,
    pub camera: Option<CameraSnap>,
}

pub fn read_model<M: Mem>(m: &mut M, r: Region, a: u32) -> Result<ModelSnap> {
    let l = r.layout();
    let mut state = [0u8; 12];
    state.copy_from_slice(&m.read_bytes(a + l.m_state, 12)?);
    Ok(ModelSnap {
        addr: a,
        pos: V4(m.vec4(a + l.m_pos)?),
        rot: V4(m.vec4(a + l.m_rot)?),
        move_rot: V4(m.vec4(a + l.m_move_rot)?),
        last_trans: V4(m.vec4(a + l.m_last_trans)?),
        state,
        walked: m.f32(a + l.m_walked)?,
        motion: m.cstr(a + l.m_motion_name, 8)?,
        slope: m.f32(a + l.m_slope)?,
    })
}

pub fn read_camera<M: Mem>(m: &mut M, a: u32) -> Result<CameraSnap> {
    Ok(CameraSnap {
        addr: a,
        flags: m.r8(a + 6)?,
        roll: m.f32(a + 0x10)?,
        trans_left: m.f32(a + 0x14)?,
        trans_len: m.f32(a + 0x18)?,
        view_angle: m.f32(a + 0x1c)?,
        delay: m.f32(a + 0x28)?,
        target: V4(m.vec4(a + 0x30)?),
        pos: V4(m.vec4(a + 0x40)?),
        comp_target: V4(m.vec4(a + 0x70)?),
        comp_pos: V4(m.vec4(a + 0x80)?),
        pitch: m.f32(a + 0xc0)?,
        yaw: m.f32(a + 0xc4)?,
        roll2: m.f32(a + 0xc8)?,
    })
}

pub fn read_field<M: Mem>(m: &mut M, r: Region) -> Result<Option<FieldSnap>> {
    let a = m.r32(r.globals().fld)?;
    if !is_ptr(a) {
        return Ok(None);
    }
    let l = r.layout();
    let mut flags = [0u8; 8];
    flags.copy_from_slice(&m.read_bytes(a + l.f_flags, 8)?);
    let floor = m.r32(a + l.f_floor)?;
    let (tri, slices) = if is_ptr(floor) { (m.r32(floor + 0x10)?, m.r32(floor + 0x18)?) } else { (0, 0) };
    let m0 = m.r32(a + l.f_models)?;
    let ctrl = if is_ptr(m0) { Some(read_model(m, r, m0)?) } else { None };
    let cam = m.r32(a + l.f_camera)?;
    let camera = if is_ptr(cam) { Some(read_camera(m, cam)?) } else { None };
    Ok(Some(FieldSnap {
        addr: a,
        state: m.r16(a + l.f_state)?,
        entry_id: m.r16(a + l.f_entry_id)? as i16,
        flags,
        model_count: m.r8(a + l.f_model_count)?,
        floor,
        floor_cached_tri: tri,
        floor_slice_count: slices,
        cam_pos: V4(m.vec4(a + l.f_cam_pos)?),
        cam_angle: V4(m.vec4(a + l.f_cam_angle)?),
        player_pos: V4(m.vec4(a + l.f_player_pos)?),
        gsx_pos: V4(m.vec4(a + l.f_gsx_pos)?),
        gsx_at: V4(m.vec4(a + l.f_gsx_at)?),
        ctrl,
        camera,
    }))
}

// ---------------------------------------------------------------------------------------------------- CBattle
/// One `BtlChr` (JP stride 0x4f0, US 0x510).  Inner offsets are the JP ones (`sh2_battle::structs::chr`); for the US build they are only
/// confirmed once `verified_us` says so (see the notes).
#[derive(Debug, Clone)]
pub struct BtlChrSnap {
    pub index: usize,
    pub flags_a: u8,
    pub flags_b: u8,
    pub state: u8,
    pub char_id: i16,
    pub max_hp: u16,
    pub hp: i16,
    pub max_mp: u16,
    pub mp: i16,
    pub max_sp: u16,
    pub sp: i16,
    pub agl: u16,
    pub luc: u16,
    pub patk: u16,
    pub satk: u16,
    pub pdef: u16,
    pub sdef: u16,
    pub turn_interval: f32,
    pub turn_timer: f32,
    pub turn_waited: f32,
    pub param_ptr: u32,
}

impl BtlChrSnap {
    pub fn exists(&self) -> bool {
        self.flags_a & 1 != 0
    }
    pub fn is_enemy(&self) -> bool {
        self.flags_b & 1 != 0
    }
}

#[derive(Debug, Clone)]
pub struct BattleSnap {
    pub addr: u32,
    pub phase: u16,
    pub step: u16,
    pub flags24: u8,
    pub actor: i8,
    pub cur_turn_chr: i16,
    pub turn_no: i32,
    pub cmd: [i32; 6],
    pub chr: Vec<BtlChrSnap>,
}

/// element-relative offsets (decompiler offset - 0xb0) of the stat block of one `BtlChr`
struct ChrOffs {
    max_hp: usize,
    hp: usize,
    max_mp: usize,
    mp: usize,
    max_sp: usize,
    sp: usize,
    agl: usize,
    luc: usize,
    patk: usize,
    interval: usize,
    param: usize,
}

pub fn read_battle<M: Mem>(m: &mut M, r: Region) -> Result<Option<BattleSnap>> {
    let a = m.r32(r.globals().battle)?;
    if !is_ptr(a) {
        return Ok(None);
    }
    let stride = r.layout().b_chr_stride;
    let hdr = m.read_bytes(a + 0x24, 0x40)?;
    let u16at = |o: usize| u16::from_le_bytes([hdr[o], hdr[o + 1]]);
    let i32at = |o: usize| i32::from_le_bytes([hdr[o], hdr[o + 1], hdr[o + 2], hdr[o + 3]]);
    // element-relative offsets (decompiler offset - 0xb0).  US (retail) shifted everything after the char id: only agl/luc/interval/param
    // were read from code (GetTurnInterval 0x004dfe80); HP/MP/SP and the three timers are *assumed* (hp block unknown -> 0).
    // JP: MaxHP u16 @0x72, HP i16 @0x74, MaxMP @0x76, MP @0x78, MaxSP @0x7a, SP @0x7c, AGL @0x7e, LUC @0x80, PAtk/SAtk/PDef/SDef @0x82..0x88.
    // US (verified live 2026-10-09, opening battle of a new game, Karin/Nicolai/Statue/Revenant): MaxHP u32 @0x7c, HP i32 @0x80, MaxMP u16 @0x84,
    // MP @0x86, MaxSP @0x88, SP @0x8a, AGL @0x8c, LUC @0x8e, PAtk @0x90, SAtk @0x92, PDef @0x94, SDef @0x96; turn interval @0xe0, MONSTERParam* @0xa0.
    let o = match r {
        Region::Jp => ChrOffs { max_hp: 0x72, hp: 0x74, max_mp: 0x76, mp: 0x78, max_sp: 0x7a, sp: 0x7c, agl: 0x7e, luc: 0x80, patk: 0x82, interval: 0xd0, param: 0x98 },
        Region::Us => ChrOffs { max_hp: 0x7c, hp: 0x80, max_mp: 0x84, mp: 0x86, max_sp: 0x88, sp: 0x8a, agl: 0x8c, luc: 0x8e, patk: 0x90, interval: 0xe0, param: 0xa0 },
    };
    let mut chr = Vec::new();
    for i in 0..12u32 {
        let base = a + 0xb0 + i * stride;
        let b = m.read_bytes(base, 0x190)?;
        let u16b = |off: usize| u16::from_le_bytes([b[off], b[off + 1]]);
        let f32b = |off: usize| f32::from_le_bytes([b[off], b[off + 1], b[off + 2], b[off + 3]]);
        chr.push(BtlChrSnap {
            index: i as usize,
            flags_a: b[0],
            flags_b: b[4],
            state: b[8],
            char_id: u16b(0x70) as i16,
            max_hp: u16b(o.max_hp),
            hp: u16b(o.hp) as i16,
            max_mp: u16b(o.max_mp),
            mp: u16b(o.mp) as i16,
            max_sp: u16b(o.max_sp),
            sp: u16b(o.sp) as i16,
            agl: u16b(o.agl),
            luc: u16b(o.luc),
            patk: u16b(o.patk),
            satk: u16b(o.patk + 2),
            pdef: u16b(o.patk + 4),
            sdef: u16b(o.patk + 6),
            turn_interval: f32b(o.interval),
            turn_timer: f32b(o.interval + 4),
            turn_waited: f32b(o.interval + 8),
            param_ptr: u32::from_le_bytes([b[o.param], b[o.param + 1], b[o.param + 2], b[o.param + 3]]),
        });
    }
    Ok(Some(BattleSnap {
        addr: a,
        phase: u16at(4),
        step: u16at(6),
        flags24: hdr[0],
        actor: hdr[8] as i8,
        cur_turn_chr: u16at(0x0c) as i16,
        turn_no: i32at(0x1c),
        cmd: [i32at(0x20), i32at(0x24), i32at(0x28), i32at(0x2c), i32at(0x30), i32at(0x34)],
        chr,
    }))
}

/// Result record of a finished fight and the monster formation, read from the live `CBattle` (US layout, see [`crate::addr::us_live`]).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct BattleResultSnap {
    pub formation: u16,
    pub monsters: [u16; 6],
    pub exp: u32,
    pub cash: u32,
    pub sp: u32,
}

/// Reads the monster set and the reward record of the US battle at `battle` (`CBattle*`).
pub fn read_us_result<M: Mem>(m: &mut M, battle: u32) -> Result<BattleResultSnap> {
    use crate::addr::us_live::*;
    let f = m.read_bytes(battle + BTL_FORMATION, 14)?;
    let formation = u16::from_le_bytes([f[0], f[1]]);
    let mut monsters = [0u16; 6];
    for (i, v) in monsters.iter_mut().enumerate() {
        *v = u16::from_le_bytes([f[2 + i * 2], f[3 + i * 2]]);
    }
    Ok(BattleResultSnap { formation, monsters, exp: m.r32(battle + BTL_REWARD_EXP)?, cash: m.r32(battle + BTL_REWARD_CASH)?, sp: m.r32(battle + BTL_REWARD_SP)? })
}

// ---------------------------------------------------------------------------------------------------- JRing
/// Subset of the `JRing` object (JP layout, 0x5d0 bytes; see notes/D/judgement_ring.md §3).
#[derive(Debug, Clone)]
pub struct JRingSnap {
    pub addr: u32,
    pub flags: [u8; 4],
    pub state: i16,
    pub substate: i16,
    pub dt: f32,
    pub period: f32,
    pub lap_add: f32,
    pub lap_mul: f32,
    pub cur_angle: f32,
    pub prev_angle: f32,
    pub area_count: i32,
    pub hits: i32,
    pub laps_done: i32,
    pub result_flags: u8,
    pub hit_count: i16,
    pub percent: i32,
    pub damage_mult: i32,
    pub areas: Vec<JRAreaSnap>,
}

#[derive(Debug, Clone)]
pub struct JRAreaSnap {
    pub flags: u16,
    pub kind: i8,
    pub mod_pct: u8,
    pub start: i16,
    pub width: i16,
    pub strike: i16,
    pub sub: i16,
    pub tag: i16,
    pub result: u16,
}

pub fn read_jring<M: Mem>(m: &mut M, r: Region) -> Result<Option<JRingSnap>> {
    let Some(top) = r.globals().jring_top else { return Ok(None) };
    let a = m.r32(top)?;
    if !is_ptr(a) {
        return Ok(None);
    }
    let mut flags = [0u8; 4];
    flags.copy_from_slice(&m.read_bytes(a + 0x40, 4)?);
    let n = m.r32(a + 0xfc)? as i32;
    let mut areas = Vec::new();
    for i in 0..n.clamp(0, 12) as u32 {
        let b = m.read_bytes(a + 0x100 + i * 0x24, 0x24)?;
        let s16 = |o: usize| i16::from_le_bytes([b[o], b[o + 1]]);
        areas.push(JRAreaSnap {
            flags: u16::from_le_bytes([b[0], b[1]]),
            kind: b[2] as i8,
            mod_pct: b[3],
            start: s16(4),
            width: s16(6),
            strike: s16(8),
            sub: s16(10),
            tag: s16(0x18),
            result: u16::from_le_bytes([b[0x1a], b[0x1b]]),
        });
    }
    Ok(Some(JRingSnap {
        addr: a,
        flags,
        state: m.r16(a + 0x46)? as i16,
        substate: m.r16(a + 0x48)? as i16,
        dt: m.f32(a + 0x5c)?,
        period: m.f32(a + 0xbc)?,
        lap_add: m.f32(a + 0xc0)?,
        lap_mul: m.f32(a + 0xc4)?,
        cur_angle: m.f32(a + 0x4ac)?,
        prev_angle: m.f32(a + 0x4b0)?,
        area_count: n,
        hits: m.r32(a + 0x4e0)? as i32,
        laps_done: m.r32(a + 0x4e8)? as i32,
        result_flags: m.r8(a + 0x512)?,
        hit_count: m.r16(a + 0x514)? as i16,
        percent: m.r32(a + 0x51c)? as i32,
        damage_mult: m.r32(a + 0x524)? as i32,
        areas,
    }))
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::client::Sparse;

    #[test]
    fn rand_matches_newlib_lcg() {
        // srand(1): state 1 -> 1 * 6364136223846793005 + 1 = 0x5851f42d4c957f2e, rand() = high word & 0x7fffffff
        let mut s = 1u64;
        assert_eq!(rand_next(&mut s), 0x5851f42d);
        assert_eq!(s, 0x5851f42d4c957f2e);
        let mut a = 0x2F50296D95D7BBD3u64;
        let start = a;
        for _ in 0..7 {
            rand_next(&mut a);
        }
        assert_eq!(rand_steps(start, a, 100), Some(7));
        assert_eq!(rand_steps(start, 5, 100), None);
    }

    #[test]
    fn us_result_record_from_live_dump() {
        // CBattle 0xA09870: formation 6 with four Revenants (MONSET 4) at +0x4646, the first random encounter's reward at +0x48b4 (Exp 5, Cash 40)
        let mut s = Sparse::default();
        s.put(0xA09870 + 0x4646, vec![6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff]);
        s.put(0xA09870 + 0x48b4, vec![5, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0]);
        let r = read_us_result(&mut s, 0xA09870).unwrap();
        assert_eq!(r.formation, 6);
        assert_eq!(r.monsters, [0, 0, 0, 0, 0xffff, 0xffff]);
        assert_eq!((r.exp, r.cash, r.sp), (5, 40, 0));
    }

    #[test]
    fn region_detection_from_signature_words() {
        let mut s = Sparse::default();
        s.put(0x0021f6c0, 0xfc64_0000u32.to_le_bytes().to_vec());
        s.put(0x00221ea0, 0x27bd_ffc0u32.to_le_bytes().to_vec());
        assert_eq!(detect_region(&mut s), Some(Region::Jp));
        let mut u = Sparse::default();
        u.put(0x0021f6c0, 0x27bd_ffc0u32.to_le_bytes().to_vec());
        u.put(0x00221ea0, 0x1460_ffedu32.to_le_bytes().to_vec());
        assert_eq!(detect_region(&mut u), Some(Region::Us));
    }

    #[test]
    fn sys_snapshot_from_us_title_dump() {
        // bytes captured live from the US disc at the title (SSHSys @0x749500, CDMYStage @0x98a210, its vtbl @0x43c0e0)
        let head = "A0 46 71 00 50 9F 98 00 00 00 00 00 00 01 00 00 40 00 B5 3A C0 BA 43 00 40 80 43 00 76 ED 0D 00 21 00 00 00 00 00 00 00 10 A2 98 00 00 99 74 00";
        let mut sys_bytes: Vec<u8> = head.split(' ').map(|h| u8::from_str_radix(h, 16).unwrap()).collect();
        sys_bytes.resize(0xb0, 0);
        let mut s = Sparse::parse(
            "0x0043fdf8 [4 bytes]:\n00 95 74 00\n0x0098a210 [8 bytes]:\n88 D2 42 00 E0 C0 43 00\n0x0043c0e0 [16 bytes]:\n00 00 00 00 00 00 00 00 C0 5D 41 00 00 5F 41 00",
        );
        s.put(0x00749500, sys_bytes);
        let sys = read_sys(&mut s, Region::Us).unwrap().unwrap();
        assert_eq!(sys.current_kind, ApiKind::Title);
        assert_eq!((sys.pend_state, sys.cur_state, sys.request), (0, 0, 0));
        assert_eq!(sys.delta_ms, 33);
    }
}

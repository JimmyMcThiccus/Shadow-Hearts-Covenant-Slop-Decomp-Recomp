//! Game-level audio runtime: the semantic requests of `CField` / `CMusic` / `CSe` / `StreamBGM` mapped onto banks of the disc.
//!
//! The original goes script op -> `CField::LoadBgm/PlayBgm/LoadSe/PlaySe...` -> `CMusic` / `CSe` -> `Sdrv` -> IOP.  Here a script op becomes an
//! [`AudioRequest`] (queued with [`post`]), the [`AudioRuntime`] loads the file from the disc image (`FIELD/SOUND/BGM/<name>.SSQ`,
//! `FIELD/SOUND/SE/<name>.SSE`, `BTLDATA/SOUND/BGM/BGM%03d.SSQ`, `OPENING/BGM803.SSV` ...), parses it and drives the [`AudioEngine`].

use crate::engine::{AudioEngine, OutputKind};
use crate::synth::{PlayId, SynthEvent};
use sh2_core::fileio::Disc;
use sh2_script::audio::{BgmParam, SeParam, SoundBackend};
use std::collections::HashMap;
use std::sync::Mutex;

/// The retail 500 ms fade used when a streamed BGM is closed (`SSHSys::StepStreamFade`, notes/I/us_delta.md) and the default BGM crossfade.
pub const STREAM_FADE_MS: u32 = 500;

/// One audio request, in the vocabulary of the game's own sound API.
#[derive(Debug, Clone, PartialEq)]
pub enum AudioRequest {
    /// field script 0x50 `CField::LoadBgm(name)`: `FIELD/SOUND/BGM/<name>.SSQ`
    LoadBgm { name: String },
    /// 0x51 `CField::PlayBgm(index, mode)` – plays sequence `index` of the loaded BGM bank
    PlayBgm { index: u32, mode: u32 },
    /// 0x52 `CField::BgmFade(volume, time)` -> `CMusic::FadeBGM(volume, time * 100 ms)`
    BgmFade { volume: u32, time: u32 },
    /// 0x53 `CField::SetBgmVolume(volume 0..127)`
    SetBgmVolume { volume: i32 },
    /// stop the field BGM (fade in ms)
    StopBgm { fade_ms: u32 },
    /// 0x55 `CField::SetBattleBgm(name)` – remember the battle BGM file name
    SetBattleBgm { name: String },
    /// 0x56 `CField::LoadSe(name, slot)`: `FIELD/SOUND/SE/<name>.SSE`
    LoadSe { name: String, slot: i32 },
    /// 0x57 `CField::UnloadSe(name)`; `None` = all (`-1`)
    UnloadSe { name: Option<String> },
    /// 0x58 `CField::PlaySe(id, volume)`; `id` is the global SE id `(wave bank << 16) | local id`
    PlaySe { id: u32, volume: i32 },
    /// 0x5a `CField::StopSe(id)`
    StopSe { id: u32 },
    /// 0x5f `PlaySeR(4, id, volume, time)` -> `CSe::SeFade(SeFind2(id), volume, time)`: fade the first instance of `id` to `volume` (0..0x7f)
    /// over `time` ms (the unit is the driver's, read as ms like `SetBGMParam`)
    FadeSe { id: u32, volume: i32, time: i32 },
    /// 0x5e `CField::PlayStreamBgm(name, volume)`: `FIELD/SOUND/BGM/<name>` (an `*.SSV` stream)
    PlayStreamBgm { name: String, volume: i32 },
    /// `StreamBGM::SetVolume(volume 0..127)` of the playing stream BGM (the effect programs' `sbgSetVolume`)
    SetStreamBgmVolume { volume: i32 },
    /// 0x5d `SetSoundData(2, time)` -> `CField::FadeStreamBgm(time)`
    FadeStreamBgm { time: i32 },
    /// battle start: `BtlSocket::SetBtlBGMNumber(n)` -> `BTLDATA/SOUND/BGM/BGM%03d.SSQ`
    PlayBattleBgm { number: u16 },
    /// battle result jingle `BTLDATA/SOUND/BGM/BGM801.SSE`
    PlayBattleResultBgm,
    /// leave the battle: fade the battle BGM out
    StopBattleBgm,
    /// title screen: `OPENING/BGM803.SSV` stream
    PlayTitleBgm,
    /// stop (fade out) the title stream: `StopBgm` only knows the field / battle BGM slot
    StopTitleBgm { fade_ms: u32 },
    /// system sound from `COMMON/SYSREG.SSE` (menu cursor / ok / cancel / buzzer ...), local id
    PlaySystemSe { id: u16 },
    /// battle UI sound: ids below 0x1000 are `COMMON/SYSREG.SSE` ids exactly as `BtlMenu` passes them to `HNMSnd::PlaySE`
    /// (0 move, 2 decide, 3 cancel, 4 buzzer, 6 / 7 page, see [`crate::se_ids`]); ids from 0x1000 are `SYSBTL.SSE` local ids
    PlayBattleSe { id: u16 },
    /// any SE by its full global id `(wave bank id << 16) | local id` (system banks are loaded on demand)
    PlayGlobalSe { id: u32 },
    /// release the sounds started with [`AudioRequest::PlaySystemSe`] / [`AudioRequest::PlayBattleSe`] under this global id (`HNMSnd::StopSE`):
    /// the looping SYSREG sounds (0x2000, 0x2001, 0x3000 result-screen counter, 0x3001) sustain until they are released
    StopGlobalSe { id: u32 },
    /// LSD cut scene / movie `PCMS` track (`BGMServerHandler`): `hdr` = track header, `data` = every packet payload concatenated
    /// (SPU ADPCM, 0x800-byte chunks per channel, 48 kHz stereo).  Replaces the PCMS stream that is playing.
    PlayPcms { hdr: Vec<u8>, data: std::sync::Arc<Vec<u8>>, volume: f32 },
    /// `Event(PAUSE / RESUME)` of the PCMS track
    PausePcms { paused: bool },
    /// `Event(END)` of the PCMS track (fade in ms, 0 = immediate)
    StopPcms { fade_ms: u32 },
    /// effect sound bank (the `1` / `SDRH` section of an EFMG effect file, `ssePlaySe`): `key` identifies the effect + section, `id` is the local SE id
    PlayEffectSe { key: String, bank: std::sync::Arc<Vec<u8>>, id: u16 },
    /// a BGM bank held in memory (`CMusic::PlayBGM(0, mode, data)` on an `SDRH` blob: the LSD `SetNextBGM` of `LSDScrEx`, whose bank is an
    /// `LGDT` track of the scene): replaces the field / battle BGM like [`AudioRequest::PlayBgm`].  `key` names the bank in the cache.
    PlayBgmData { key: String, bank: std::sync::Arc<Vec<u8>>, index: u32 },
    /// map load (`CField::AutoLoadSE`): the map's `OBJSE` chunk (data from its `u16 count`): loads its SE banks and replaces every object sound
    MapObjSe { chunk: std::sync::Arc<Vec<u8>> },
    /// field script 0x5c `SetObjSE(slot, ..)`: add / replace (`Some`) or clear (`None`; `slot < 0` = all) an object sound
    SetObjSe { slot: i32, rec: Option<crate::objse::ObjSeRec>, one_shot: bool },
    /// the active field camera (`GsxCamera` position, "at" axis, focal length), PS2 world units: the listener of the object sounds
    SetListener { listener: Option<crate::objse::Listener> },
    /// battle start: the per-fighter SE banks of BATTLE.BIN (`BTLDATA/SOUND/SE/%03dM.SSE` per CHR model number = wave bank `0x9000 | chr`,
    /// `%03dW%02d.SSE` per PC weapon (same wave bank as the PC's `M`), `%03dC.SSE` per PC = `0x9100 | pc`); every bank stays resident until
    /// [`AudioRequest::UnloadBattleBanks`] so `PlayGlobalSe { id: (bank << 16) | local }` finds them (`Sdrv::PlaySE` -> `FindSE`)
    LoadBattleBanks { chrs: Vec<u16>, weapons: Vec<(u16, u8)>, voices: Vec<u16> },
    /// leave the battle: drop the banks of [`AudioRequest::LoadBattleBanks`] (and the `battle` banks of [`AudioRequest::LoadSeData`])
    UnloadBattleBanks,
    /// make an SE bank held in memory resident under `key` (once): the battle character packages carry their own banks
    /// (`BTLDATA/CHR/%03d.BCM` entries `ase` = SE set 0x6000 -- hits / swings, `HNMSnd::PlaySE(0x6000_1005)` .. -- and `dse` = SE set
    /// 0x7000, `0x7000_000x`; retail `CBattle` -> `HNMSnd::IOPEntry(BtlChr+0x4b0 / +0x4b8)`).  `battle = true` drops it with
    /// [`AudioRequest::UnloadBattleBanks`].  Global ids resolve through `FindSE` (`(id >> 16)` = the bank's `FE` SE-set id).
    LoadSeData { key: String, data: std::sync::Arc<Vec<u8>>, battle: bool },
    /// stop everything (game over / reset)
    StopAll,
    /// `SaveMenuSection::UpdateSoundOut` -> `Sdrv::SetMode(mode)`: the Option page's sound-out setting, in the driver's codes
    /// (`0x1001` stereo, `0x1000` mono, `0x1002` surround; the port renders surround as stereo)
    SetSoundOut { sdrv_mode: u32 },
}

static QUEUE: Mutex<Vec<AudioRequest>> = Mutex::new(Vec::new());

/// Shared playback state that script hosts poll for `WaitBgm` / `WaitSe` (`CField::WaitBgm` reads flags that `CField::cbMusicA` sets from the
/// `CMusic` callback events; `CField::WaitSe` is `CSe::SeFind(id) < 0`).  Requests that were posted but not yet handled count as started, so a
/// script that does `PlaySe` followed by `WaitSe` in the same frame blocks as intended.
pub mod status {
    use std::collections::HashMap;
    use std::sync::{LazyLock, Mutex};

    #[derive(Default)]
    pub struct State {
        /// SE global id -> number of instances playing (maintained by the runtime)
        pub playing_se: HashMap<u32, u32>,
        /// SE global id -> number of `PlaySe` requests posted but not yet handled
        pub pending_se: HashMap<u32, u32>,
        /// `WaitBgm(2)`: the requested BGM bank is loaded / ready
        pub bgm_ready: bool,
        /// `WaitBgm(1)`: the BGM finished or was stopped (`cbMusic` event 2)
        pub bgm_finished: bool,
        /// `WaitBgm(0)`: the last `BgmFade` completed (`cbMusic` event 3)
        pub fade_done: bool,
        /// a `PlayBgm` / `BgmFade` request is still in the queue
        pub pending_bgm: u32,
        pub pending_fade: u32,
    }

    pub static STATE: LazyLock<Mutex<State>> =
        LazyLock::new(|| Mutex::new(State { bgm_ready: true, bgm_finished: true, fade_done: true, ..Default::default() }));

    pub fn lock() -> std::sync::MutexGuard<'static, State> {
        STATE.lock().unwrap_or_else(|e| e.into_inner())
    }

    pub(super) fn note_posted(req: &super::AudioRequest) {
        use super::AudioRequest as R;
        let mut st = lock();
        match req {
            R::PlaySe { id, .. } | R::PlayGlobalSe { id } => *st.pending_se.entry(*id).or_default() += 1,
            R::PlayBgm { .. } | R::PlayBattleBgm { .. } | R::PlayBattleResultBgm => {
                st.pending_bgm += 1;
                st.bgm_finished = false;
            }
            R::BgmFade { time, .. } if *time > 0 => {
                st.pending_fade += 1;
                st.fade_done = false;
            }
            _ => {}
        }
    }

    /// `CField::WaitSe(id)`: true when no instance of the SE is playing or about to play (the script op may complete).
    pub fn wait_se(id: u32) -> bool {
        let st = lock();
        st.playing_se.get(&id).copied().unwrap_or(0) == 0 && st.pending_se.get(&id).copied().unwrap_or(0) == 0
    }

    /// `CField::WaitBgm(kind)`: 0 = the last fade finished, 1 = the BGM is finished / stopped, 2 = the BGM is loaded; other kinds are always satisfied.
    pub fn wait_bgm(kind: u32) -> bool {
        let st = lock();
        match kind {
            0 => st.fade_done && st.pending_fade == 0,
            1 => st.bgm_finished && st.pending_bgm == 0,
            2 => st.bgm_ready && st.pending_bgm == 0,
            _ => true,
        }
    }
}

/// Queue a request from anywhere (script hosts, plugins without Bevy access).  The Bevy [`AudioPlugin`](crate::AudioPlugin) drains it every frame.
pub fn post(req: AudioRequest) {
    status::note_posted(&req);
    QUEUE.lock().unwrap_or_else(|e| e.into_inner()).push(req);
}

/// Take all queued requests.
pub fn drain() -> Vec<AudioRequest> {
    std::mem::take(&mut *QUEUE.lock().unwrap_or_else(|e| e.into_inner()))
}

pub mod hooks {
    use super::*;

    /// Translate a field-script audio op (`ex 0xc2`, sub 0x50..=0x5f; JP `CField::CallFunc` 0x004ac950) into requests and [`post`] them.
    /// `int_arg(i)` / `str_arg(i)` read script argument `i` as an integer / C string.  Returns `true` for audio ops.
    ///
    /// `WaitBgm` (0x54) and `WaitSe` (0x5b) are acknowledged here; the host decides whether to yield with [`field_wait_op`].
    /// Result of polling a `WaitBgm` / `WaitSe` script op.
    #[derive(Debug, Clone, Copy, PartialEq, Eq)]
    pub struct WaitOp {
        /// the awaited condition holds
        pub done: bool,
        /// the op blocks the script until `done` (flag 0x80 clear in the argument); a non-blocking op just stores `done` as its result
        pub blocking: bool,
    }

    /// Poll a wait op of `CField::CallFunc` (ex 0xc2): `sub` 0x54 `WaitBgm(kind | 0x80?)` or 0x5b `WaitSe(id, flags)`.  `arg(i)` reads script
    /// argument `i`.  Returns `None` for other ops.  A blocking op (`blocking && !done`) must be re-executed on the next frame (the original
    /// returns `value | 0xffff0000` to the script VM, which repeats the instruction); otherwise the result `done as i32` goes to the result slot.
    ///
    /// * `WaitBgm(kind)`: kind 0 = the last `BgmFade` finished, 1 = the song finished / stopped, 2 = the BGM is loaded.
    /// * `WaitSe(id, flags)`: done when no instance of the SE `id` is playing (`CSe::SeFind(id) < 0`).
    pub fn field_wait_op(sub: u8, arg: impl Fn(usize) -> i32) -> Option<WaitOp> {
        match sub {
            0x54 => {
                let a = arg(0);
                Some(WaitOp { done: status::wait_bgm((a & 0x7f) as u32), blocking: a & 0x80 == 0 })
            }
            0x5b => {
                let flags = arg(1);
                Some(WaitOp { done: status::wait_se(arg(0) as u32), blocking: flags & 0x80 == 0 })
            }
            _ => None,
        }
    }

    pub fn field_script_op(sub: u8, argc: usize, int_arg: impl Fn(usize) -> i32, str_arg: impl Fn(usize) -> String) -> bool {
        let req = match sub {
            0x50 => AudioRequest::LoadBgm { name: str_arg(0) },
            0x51 => AudioRequest::PlayBgm { index: int_arg(0) as u32, mode: int_arg(1) as u32 },
            0x52 => AudioRequest::BgmFade { volume: int_arg(0) as u32, time: int_arg(1) as u32 },
            0x53 => AudioRequest::SetBgmVolume { volume: int_arg(0) },
            0x55 => AudioRequest::SetBattleBgm { name: str_arg(0) },
            0x56 => AudioRequest::LoadSe { name: str_arg(0), slot: if argc == 1 { 0 } else { int_arg(1) } },
            0x57 => AudioRequest::UnloadSe { name: if int_arg(0) == 0 || int_arg(0) == -1 { None } else { Some(str_arg(0)) } },
            0x58 => AudioRequest::PlaySe { id: int_arg(0) as u32, volume: int_arg(1) },
            0x5a => AudioRequest::StopSe { id: int_arg(0) as u32 },
            0x5d => {
                // SetSoundData(kind, a, b): 2 = FadeStreamBgm(a); 0 = reverb mode, 1 / 3 = flags (no audible effect here)
                if int_arg(0) == 2 {
                    AudioRequest::FadeStreamBgm { time: int_arg(1) }
                } else {
                    return true;
                }
            }
            0x5e => AudioRequest::PlayStreamBgm { name: str_arg(0), volume: int_arg(1) },
            // 0x5f `PlaySeR(mode, id, a, b)` (CField.c 3858 / 9103): 0 play with volume `a` (0 = 0x80), 4 fade (`SeFade(id, a, b)`), 2 play and wait
            // until it ends (the op is re-executed every frame: start it only while no instance of the id is playing), 1 = query (host)
            0x5f => match int_arg(0) {
                0 => AudioRequest::PlaySe { id: int_arg(1) as u32, volume: int_arg(2) },
                2 if status::wait_se(int_arg(1) as u32) => AudioRequest::PlaySe { id: int_arg(1) as u32, volume: int_arg(2) },
                4 => AudioRequest::FadeSe { id: int_arg(1) as u32, volume: int_arg(2), time: int_arg(3) },
                _ => return true,
            },
            // 0x59 `SetSeVolume` is an empty function on the console; 0x5c `SetObjSE` goes through `AudioRequest::SetObjSe` (host hook)
            0x54 | 0x59 | 0x5b | 0x5c => return true, // WaitBgm / SetSeVolume / WaitSe / SetObjSE: acknowledged here
            _ => return false,
        };
        post(req);
        true
    }
}

/// Where a request's file ended up.
#[derive(Debug, Default, Clone)]
pub struct RuntimeStats {
    pub requests: usize,
    pub banks_loaded: usize,
    pub missing_files: Vec<String>,
}

/// Disc-backed audio state machine behind the Bevy plugin (also usable from tools and tests).
#[cfg_attr(feature = "bevy", derive(bevy::prelude::Resource))]
pub struct AudioRuntime {
    pub engine: AudioEngine,
    pub disc: Option<Disc>,
    banks: HashMap<String, u32>,
    bgm_bank: Option<u32>,
    bgm_play: Option<PlayId>,
    field_bgm_name: Option<String>,
    battle_bgm_name: Option<String>,
    stream_play: Option<PlayId>,
    title_play: Option<PlayId>,
    pcms_play: Option<PlayId>,
    bgm_volume: f32,
    se_banks: HashMap<String, u32>,
    /// every SE started through `PlaySe` / `PlayGlobalSe`: (global id, play id), oldest first (per-id `StopSe`, `WaitSe`)
    se_plays: Vec<(u32, PlayId)>,
    /// banks of [`AudioRequest::LoadBattleBanks`]
    battle_banks: Vec<String>,
    /// field object sounds (`OBJSE`) and their play ids
    objse: crate::objse::ObjSeMan,
    objse_plays: HashMap<usize, PlayId>,
    listener: Option<crate::objse::Listener>,
    pub stats: RuntimeStats,
}

fn norm(path: &str) -> String {
    path.replace('\\', "/").to_uppercase()
}

impl AudioRuntime {
    pub fn new(engine: AudioEngine, disc: Option<Disc>) -> Self {
        AudioRuntime {
            engine,
            disc,
            banks: HashMap::new(),
            bgm_bank: None,
            bgm_play: None,
            field_bgm_name: None,
            battle_bgm_name: None,
            stream_play: None,
            title_play: None,
            pcms_play: None,
            bgm_volume: 1.0,
            se_banks: HashMap::new(),
            se_plays: Vec::new(),
            battle_banks: Vec::new(),
            objse: Default::default(),
            objse_plays: HashMap::new(),
            listener: None,
            stats: RuntimeStats::default(),
        }
    }

    fn read(&mut self, path: &str) -> Option<Vec<u8>> {
        match self.disc.as_ref()?.read(path) {
            Ok(b) => Some(b),
            Err(e) => {
                log::debug!("audio: {path}: {e}");
                self.stats.missing_files.push(path.to_string());
                None
            }
        }
    }

    /// Load (or fetch from the cache) an SDH bank file, returns the synth bank handle.
    pub fn bank(&mut self, path: &str) -> Option<u32> {
        let key = norm(path);
        if let Some(&h) = self.banks.get(&key) {
            return Some(h);
        }
        let bytes = self.read(&key)?;
        let h = self.engine.load_bank(&bytes)?;
        self.banks.insert(key, h);
        self.stats.banks_loaded += 1;
        Some(h)
    }

    fn unload(&mut self, path: &str) {
        let key = norm(path);
        if let Some(h) = self.banks.remove(&key) {
            self.engine.synth().remove_bank(h);
        }
    }

    fn fade_out(&mut self, id: Option<PlayId>, ms: u32) {
        if let Some(id) = id {
            self.engine.synth().stop(id, ms);
        }
    }

    fn start_bgm(&mut self, path: &str, index: usize) -> Option<PlayId> {
        let h = self.bank(path)?;
        self.start_bgm_bank(h, index)
    }

    fn start_bgm_bank(&mut self, h: u32, index: usize) -> Option<PlayId> {
        let old = self.bgm_play.take();
        self.fade_out(old, STREAM_FADE_MS);
        // keep only the BGM bank of the playing song resident (they are large)
        if let Some(prev) = self.bgm_bank.take() {
            if prev != h {
                // the faded-out song still needs its samples for 500 ms: drop the bank from the cache but let the synth keep its Arc
                self.banks.retain(|_, v| *v != prev);
                self.engine.synth().remove_bank(prev);
            }
        }
        self.bgm_bank = Some(h);
        let mut p = BgmParam::default();
        p.base.volume = (self.bgm_volume * 127.0) as u8;
        let seqs = self.engine.synth().bank(h).map(|b| b.sequences.len()).unwrap_or(0);
        if seqs == 0 {
            return None;
        }
        let idx = if index < seqs { index } else { 0 };
        let id = self.engine.synth().play_bgm(h, idx, &p);
        self.bgm_play = id;
        {
            let mut st = status::lock();
            st.pending_bgm = st.pending_bgm.saturating_sub(1);
            st.bgm_ready = true;
            st.bgm_finished = id.is_none();
        }
        id
    }

    /// Process one request.
    pub fn handle(&mut self, req: &AudioRequest) {
        self.stats.requests += 1;
        match req {
            AudioRequest::LoadBgm { name } => {
                // The bank is parsed when played (the original also only DMAs it to the SPU at PlayBGM time).
                self.field_bgm_name = Some(name.clone());
            }
            AudioRequest::PlayBgm { index, .. } => {
                if let Some(name) = self.field_bgm_name.clone() {
                    let path = format!("FIELD/SOUND/BGM/{}.SSQ", name.trim_end_matches(".SSQ").trim_end_matches(".ssq"));
                    self.start_bgm(&path, *index as usize);
                } else {
                    let mut st = status::lock();
                    st.pending_bgm = st.pending_bgm.saturating_sub(1);
                    st.bgm_finished = true;
                }
            }
            AudioRequest::BgmFade { volume, time } => {
                // CMusic::FadeBGM(volume, time * 100 ms): `fade_done` (WaitBgm 0) is set by the synth's FadeDone event
                let mut started = false;
                if let Some(id) = self.bgm_play {
                    let v = (*volume).min(127) as f32 / 127.0;
                    self.engine.synth().fade(id, v, time * 100, v <= 0.0);
                    started = *time > 0;
                }
                let mut st = status::lock();
                if *time > 0 {
                    st.pending_fade = st.pending_fade.saturating_sub(1);
                }
                st.fade_done = !started;
            }
            AudioRequest::SetBgmVolume { volume } => {
                self.bgm_volume = (*volume).clamp(0, 127) as f32 / 127.0;
                if let Some(id) = self.bgm_play {
                    let v = self.bgm_volume;
                    self.engine.synth().set_volume(id, v);
                }
            }
            AudioRequest::StopBgm { fade_ms } => {
                let id = self.bgm_play.take();
                self.fade_out(id, *fade_ms);
                status::lock().bgm_finished = true;
            }
            AudioRequest::SetBattleBgm { name } => self.battle_bgm_name = Some(name.clone()),
            AudioRequest::LoadSe { name, .. } => {
                let path = format!("FIELD/SOUND/SE/{name}.SSE");
                if let Some(h) = self.bank(&path) {
                    self.se_banks.insert(norm(name), h);
                }
            }
            AudioRequest::UnloadSe { name } => match name {
                Some(n) => {
                    let path = format!("FIELD/SOUND/SE/{n}.SSE");
                    self.se_banks.remove(&norm(n));
                    self.unload(&path);
                }
                None => {
                    let paths: Vec<String> = self.se_banks.keys().map(|n| format!("FIELD/SOUND/SE/{n}.SSE")).collect();
                    self.se_banks.clear();
                    for p in paths {
                        self.unload(&p);
                    }
                }
            },
            AudioRequest::PlaySe { id, volume } => {
                let mut p = SeParam::default();
                if *volume > 0 {
                    p.volume = (*volume).min(127) as u8;
                }
                self.play_global(*id, &p);
            }
            AudioRequest::PlayGlobalSe { id } => {
                // system banks are resident in the original (COMMON.PKB / BTLDATA): load them on demand
                self.ensure_system_bank((*id >> 16) as u16);
                self.play_global(*id, &SeParam::default());
            }
            AudioRequest::StopSe { id } => {
                // CField::StopSe -> CSe::SeFind2(id) -> CSe::SeRelease(slot): the *first* slot holding the id is released (key off, the
                // release tail rings out); other instances of the same id keep playing
                self.prune_se_plays();
                if let Some(i) = self.se_plays.iter().position(|(sid, _)| sid == id) {
                    let (_, pid) = self.se_plays.remove(i);
                    self.engine.synth().stop(pid, 0);
                }
                self.publish_se_status();
            }
            AudioRequest::FadeSe { id, volume, time } => {
                self.prune_se_plays();
                if let Some((_, pid)) = self.se_plays.iter().find(|(sid, _)| sid == id) {
                    let v = (*volume).clamp(0, 0x7f) as f32 / 127.0;
                    self.engine.synth().fade(*pid, v, (*time).max(0) as u32, v <= 0.0);
                }
            }
            AudioRequest::PlayStreamBgm { name, volume } => {
                // a name with a directory is a disc path (FX round 5 hook: the effect programs' `sbgCreate("EFFECT/EFX081.SSV")`)
                let path = if name.contains('/') { name.clone() } else { format!("FIELD/SOUND/BGM/{name}") };
                let old = self.stream_play.take();
                self.fade_out(old, STREAM_FADE_MS);
                if let Some(bytes) = self.read(&norm(&path)) {
                    let vol = if *volume <= 0 { 0x7f } else { *volume } as f32;
                    // StreamBGM volume register: (v + 1) * 0x80 - 1 of 0x3fff
                    let gain = (((vol + 1.0) * 128.0 - 1.0) / 16383.0).min(1.0);
                    self.stream_play = self.engine.play_stream_file(&bytes, gain);
                }
            }
            AudioRequest::SetStreamBgmVolume { volume } => {
                // `StreamBGM::SetVolume(v)`: the register `(v + 1) * 0x80 - 1` of 0x3fff
                if let Some(id) = self.stream_play {
                    let gain = (((*volume).clamp(0, 127) as f32 + 1.0) * 128.0 - 1.0) / 16383.0;
                    if let Some(st) = self.engine.synth().stream_mut(id) {
                        st.set_volume(gain.min(1.0));
                    }
                }
            }
            AudioRequest::FadeStreamBgm { time } => {
                let id = self.stream_play.take();
                self.fade_out(id, if *time <= 0 { STREAM_FADE_MS } else { *time as u32 });
            }
            AudioRequest::PlayBattleBgm { number } => {
                // the field (and its object sounds) is released for the battle
                self.release_objse(-1);
                let old = self.bgm_play.take();
                self.fade_out(old, STREAM_FADE_MS);
                let path = match &self.battle_bgm_name {
                    Some(n) if *number == 0 => format!("FIELD/SOUND/BGM/{n}.SSQ"),
                    _ => format!("BTLDATA/SOUND/BGM/BGM{:03}.SSQ", number),
                };
                if self.start_bgm(&path, 0).is_none() {
                    log::debug!("audio: no battle BGM {path}; falling back to BGM401");
                    if *number != 0x191 {
                        self.start_bgm("BTLDATA/SOUND/BGM/BGM401.SSQ", 0);
                    }
                }
            }
            AudioRequest::PlayBattleResultBgm => {
                self.start_bgm("BTLDATA/SOUND/BGM/BGM801.SSE", 0);
            }
            AudioRequest::StopBattleBgm => {
                let id = self.bgm_play.take();
                self.fade_out(id, STREAM_FADE_MS);
            }
            AudioRequest::StopTitleBgm { fade_ms } => {
                let id = self.title_play.take();
                self.fade_out(id, *fade_ms);
            }
            AudioRequest::PlayTitleBgm => {
                let old = self.title_play.take();
                self.fade_out(old, STREAM_FADE_MS);
                if let Some(bytes) = self.read("OPENING/BGM803.SSV") {
                    self.title_play = self.engine.play_stream_file(&bytes, 1.0);
                }
            }
            AudioRequest::PlaySystemSe { id } => {
                if let Some(h) = self.bank("COMMON/SYSREG.SSE") {
                    let p = self.engine.play_se(h, *id as u32, &SeParam::default());
                    self.remember_se(crate::se_ids::global(crate::se_ids::BANK_SYSREG, *id), p);
                }
            }
            AudioRequest::PlayBattleSe { id } => {
                let gid = crate::se_ids::battle_global(*id);
                self.ensure_system_bank((gid >> 16) as u16);
                let path = if gid >> 16 == crate::se_ids::BANK_SYSBTL as u32 { "BTLDATA/SOUND/SYSTEM/SYSBTL.SSE" } else { "COMMON/SYSREG.SSE" };
                if let Some(h) = self.bank(path) {
                    let p = self.engine.play_se(h, (gid & 0xffff) as u32, &SeParam::default());
                    self.remember_se(gid, p);
                }
            }
            AudioRequest::StopGlobalSe { id } => {
                // every instance: a looping UI sound may have been restarted before it was released
                self.prune_se_plays();
                let (stop, keep): (Vec<_>, Vec<_>) = std::mem::take(&mut self.se_plays).into_iter().partition(|(sid, _)| sid == id);
                self.se_plays = keep;
                for (_, pid) in stop {
                    self.engine.synth().stop(pid, 0);
                }
                self.publish_se_status();
            }
            AudioRequest::PlayPcms { hdr, data, volume } => {
                if let Some(old) = self.pcms_play.take() {
                    self.engine.synth().stop(old, 0);
                }
                match crate::stream::StreamPlayer::from_pcms(hdr, data) {
                    Some(mut p) => {
                        p.set_volume(*volume);
                        self.pcms_play = Some(self.engine.synth().add_stream(p));
                    }
                    None => log::warn!("audio: bad PCMS header"),
                }
            }
            AudioRequest::PausePcms { paused } => {
                if let Some(id) = self.pcms_play {
                    if let Some(s) = self.engine.synth().stream_mut(id) {
                        s.pause(*paused);
                    }
                }
            }
            AudioRequest::StopPcms { fade_ms } => {
                if let Some(id) = self.pcms_play.take() {
                    self.engine.synth().stop(id, *fade_ms);
                }
            }
            AudioRequest::PlayEffectSe { key, bank, id } => {
                let h = match self.banks.get(key) {
                    Some(&h) => Some(h),
                    None => {
                        let h = self.engine.load_bank(bank);
                        if let Some(h) = h {
                            self.banks.insert(key.clone(), h);
                            self.stats.banks_loaded += 1;
                        }
                        h
                    }
                };
                if let Some(h) = h {
                    self.engine.play_se(h, *id as u32, &SeParam::default());
                }
            }
            AudioRequest::SetSoundOut { sdrv_mode } => {
                // Sdrv::SetMode sub command 0: bit 0 of the low nibble selects stereo (0x1001, 0x1002) or mono (0x1000)
                let mono = sdrv_mode & 0xf == 0;
                self.engine.synth().set_output_mode(mono, true);
                log::info!("audio: sound out {}", if mono { "mono" } else if sdrv_mode & 0xf == 2 { "surround (rendered as stereo)" } else { "stereo" });
            }
            AudioRequest::PlayBgmData { key, bank, index } => {
                let k = format!("MEM:{}", norm(key));
                let h = match self.banks.get(&k) {
                    Some(&h) => Some(h),
                    None => {
                        let h = self.engine.load_bank(bank);
                        if let Some(h) = h {
                            self.banks.insert(k, h);
                            self.stats.banks_loaded += 1;
                        }
                        h
                    }
                };
                match h {
                    Some(h) => {
                        self.start_bgm_bank(h, *index as usize);
                    }
                    None => log::warn!("audio: BGM data '{key}' is not a sound bank"),
                }
            }
            AudioRequest::MapObjSe { chunk } => {
                let c = crate::objse::ObjSeChunk::parse(chunk);
                self.release_objse(-1);
                for (i, b) in c.banks.iter().enumerate() {
                    self.handle(&AudioRequest::LoadSe { name: b.clone(), slot: i as i32 + 1 });
                }
                for (i, r) in c.records.into_iter().enumerate() {
                    let _ = self.objse.set(i as i32, Some(r), false);
                }
                log::debug!("audio: map OBJSE: banks {:?}, {} sounds", c.banks, self.objse_count());
            }
            AudioRequest::SetObjSe { slot, rec, one_shot } => {
                let rel = self.objse.set(*slot, rec.clone(), *one_shot);
                for i in rel {
                    if let Some(id) = self.objse_plays.remove(&i) {
                        self.engine.synth().stop(id, 0);
                    }
                }
            }
            AudioRequest::SetListener { listener } => self.listener = *listener,
            AudioRequest::LoadBattleBanks { chrs, weapons, voices } => {
                let mut paths: Vec<String> = chrs.iter().map(|c| format!("BTLDATA/SOUND/SE/{c:03}M.SSE")).collect();
                paths.extend(weapons.iter().map(|(c, w)| format!("BTLDATA/SOUND/SE/{c:03}W{w:02}.SSE")));
                paths.extend(voices.iter().map(|c| format!("BTLDATA/SOUND/SE/{c:03}C.SSE")));
                for p in paths {
                    // a missing file is normal (not every monster has a bank)
                    if self.disc.as_ref().map(|d| d.exists(&p)).unwrap_or(false) && self.bank(&p).is_some() && !self.battle_banks.contains(&p) {
                        self.battle_banks.push(p);
                    }
                }
            }
            AudioRequest::LoadSeData { key, data, battle } => {
                let k = norm(key);
                if !self.banks.contains_key(&k) {
                    if let Some(h) = self.engine.load_bank(&data[..]) {
                        self.banks.insert(k.clone(), h);
                        self.stats.banks_loaded += 1;
                    }
                }
                if *battle && self.banks.contains_key(&k) && !self.battle_banks.contains(&k) {
                    self.battle_banks.push(k);
                }
            }
            AudioRequest::UnloadBattleBanks => {
                for p in std::mem::take(&mut self.battle_banks) {
                    self.unload(&p);
                }
            }
            AudioRequest::StopAll => {
                self.release_objse(-1);
                self.se_plays.clear();
                self.publish_se_status();
                {
                    let mut st = status::lock();
                    st.bgm_finished = true;
                    st.fade_done = true;
                    st.pending_fade = 0;
                    st.pending_bgm = 0;
                }
                self.pcms_play = None;
                self.engine.synth().stop_all();
                self.bgm_play = None;
                self.stream_play = None;
                self.title_play = None;
            }
        }
    }

    fn release_objse(&mut self, slot: i32) {
        let rel = self.objse.set(slot, None, false);
        let _ = rel;
        let ids: Vec<PlayId> = if slot < 0 { self.objse_plays.drain().map(|(_, v)| v).collect() } else { self.objse_plays.remove(&(slot as usize)).into_iter().collect() };
        for id in ids {
            self.engine.synth().stop(id, 0);
        }
    }

    /// Number of object sounds currently playing.
    pub fn objse_count(&self) -> usize {
        self.objse.active()
    }

    /// `UpdateObjSE`: place / start / release the object sounds for the current listener.
    fn update_objse(&mut self) {
        // sounds that ended by themselves
        let ended: Vec<usize> = self.objse_plays.iter().filter(|(_, id)| !self.engine.synth().is_playing(**id)).map(|(s, _)| *s).collect();
        for s in ended {
            self.objse_plays.remove(&s);
            self.objse.ended(s);
        }
        for a in self.objse.update(self.listener) {
            match a {
                crate::objse::ObjSeAction::Play { slot, id, volume, pan } => {
                    let p = SeParam { volume, pan, ..SeParam::default() };
                    let h = self.engine.play_se(0, id, &p);
                    if h != 0 {
                        self.objse_plays.insert(slot, h);
                    } else {
                        self.objse.ended(slot);
                    }
                }
                crate::objse::ObjSeAction::Update { slot, volume, pan } => {
                    if let Some(&h) = self.objse_plays.get(&slot) {
                        self.engine.set_se_param(h, &SeParam { volume, pan, ..SeParam::default() });
                    }
                }
                crate::objse::ObjSeAction::Release { slot } => {
                    if let Some(h) = self.objse_plays.remove(&slot) {
                        self.engine.synth().stop(h, 0);
                    }
                }
            }
        }
    }

    /// Per-frame housekeeping: advance the virtual clock of the null / WAV backends and drop finished-event notifications.
    pub fn update(&mut self, dt: f32) {
        self.update_objse();
        self.engine.pump(dt);
        for e in self.engine.take_events() {
            match e {
                // cbMusic event 3: the fade of the BGM reached its target
                SynthEvent::FadeDone(id) if Some(id) == self.bgm_play => status::lock().fade_done = true,
                // cbMusic event 2: the BGM ended (sequence end marker / stop)
                SynthEvent::BgmFinished(id) if Some(id) == self.bgm_play => {
                    self.bgm_play = None;
                    status::lock().bgm_finished = true;
                }
                _ => {}
            }
        }
        self.prune_se_plays();
        self.publish_se_status();
        let s = self.engine.synth();
        if let Some(id) = self.title_play {
            if !s.is_playing(id) {
                self.title_play = None;
            }
        }
    }

    /// Load one of the always-resident system banks (SYSREG = wave bank 0, SYSBTL = 0x0200) if it is not loaded yet.
    fn ensure_system_bank(&mut self, bank_id: u16) {
        let path = match bank_id {
            crate::se_ids::BANK_SYSREG => "COMMON/SYSREG.SSE",
            crate::se_ids::BANK_SYSBTL => "BTLDATA/SOUND/SYSTEM/SYSBTL.SSE",
            _ => return,
        };
        let _ = self.bank(path);
    }

    /// Start an SE by global id and remember the instance for `StopSe` / `WaitSe`.  System banks are resolved first (several field SE banks
    /// repeat wave-bank id 0, the lowest synth handle wins).
    fn play_global(&mut self, id: u32, p: &SeParam) {
        {
            let mut st = status::lock();
            if let Some(n) = st.pending_se.get_mut(&id) {
                *n = n.saturating_sub(1);
            }
        }
        let h = self.engine.play_se(0, id, p);
        if h != 0 {
            self.se_plays.push((id, h));
        }
        self.publish_se_status();
    }

    /// Keep the play id of a UI sound so that [`AudioRequest::StopGlobalSe`] can release it.
    fn remember_se(&mut self, gid: u32, h: PlayId) {
        if h != 0 {
            self.se_plays.push((gid, h));
        }
    }

    fn prune_se_plays(&mut self) {
        let s = self.engine.synth();
        self.se_plays.retain(|(_, pid)| s.is_playing(*pid));
    }

    fn publish_se_status(&mut self) {
        let mut st = status::lock();
        st.playing_se.clear();
        for (id, _) in &self.se_plays {
            *st.playing_se.entry(*id).or_default() += 1;
        }
    }

    /// Playback position (seconds) of the LSD `PCMS` stream, `None` when none is playing.
    pub fn pcms_position(&self) -> Option<f32> {
        let id = self.pcms_play?;
        self.engine.synth().stream_mut_ref(id).map(|s| s.position_secs())
    }

    pub fn bgm_playing(&self) -> bool {
        self.bgm_play.map(|id| self.engine.synth().is_playing(id)).unwrap_or(false)
    }
    pub fn stream_playing(&self) -> bool {
        self.stream_play.or(self.title_play).map(|id| self.engine.synth().is_playing(id)).unwrap_or(false)
    }
}

/// Output chosen from the environment: `SH2_AUDIO=null|wav:<path>|device` (default device).
pub fn output_from_env() -> OutputKind {
    match std::env::var("SH2_AUDIO").ok().as_deref() {
        Some("null") | Some("off") | Some("0") => OutputKind::Null,
        Some(s) if s.starts_with("wav:") => OutputKind::Wav(s[4..].into()),
        _ => OutputKind::Device,
    }
}

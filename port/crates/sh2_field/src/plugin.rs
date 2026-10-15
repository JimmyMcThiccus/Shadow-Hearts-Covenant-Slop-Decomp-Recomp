//! `FieldPlugin` — the Bevy side of `CFieldSocket` + `CField` (JP main 0x003bcfd0.., FIELD.BIN 0x004a2b00..).
//!
//! On `Scene::Field` entry ([`enter_field`], `CFieldSocket::fieldOverlay` -> `CField::Init(map)` -> `MapJump` -> `InitSDB`):
//! * the map package `FIELD/MPS/<map>.MPS` is parsed into a [`crate::sim::FieldSim`] (floor, event boxes, camera table, MONSET) and the
//!   map script `<map>.MSC` is loaded into a [`sh2_script::cscript::CScript`] whose engine calls (`ex 0xc2`, JP `CField::CallFunc`
//!   0x004ac950) are served by [`FieldHost`];
//! * the background geometry is rendered by [`crate::bevy::FieldMapPlugin`] (section B/C renderer) when a renderer is present;
//! * the player is a placeholder capsule (the character model/motion system is not wired yet) moved by [`crate::sim`].
//!
//! Per 60 Hz tick (`GameSet`): `Script` -> [`field_script_tick`] (`CScript::Polling`), `Logic` -> [`field_logic_tick`]
//! (`CField::Polling`: input, event boxes, encounters, menu request, map jump / battle start), `Camera` -> [`field_camera_tick`]
//! (`CameraUpdate`).  Scene requests go through `SshSys` exactly like the original (`SSHSys::StartBattle`, `InitFieldSocketM`).

use ::bevy::prelude::*;

use sh2_core::app::AppConfig;
use sh2_core::game::{padbit, FieldRequest, GamePad, GameSet, Scene};
use sh2_core::ssh_sys::{SshApi, SshSys, SysBtlParam};
use sh2_menu::bevy_ui::{self, layer, UiCanvas};
use sh2_menu::gfx::Rgba;
use sh2_menu::plugin::Cover;
use sh2_menu::session::{ChrPos, GameSession};
use sh2_script::cscript::{CScript, PadState};

use crate::host::{tick_state, FieldAudio, FieldTables, MenuReq};
pub use crate::host::{FieldHost, ScriptState};
use crate::menu_overlay::{menu_blocks_field, InGameMenu, MenuOverlayPlugin};
use crate::pkb_compat::PkbSet;
use crate::script_ui::{WinPhase, CELL_H, CELL_W};
use crate::sim::{read_enc_dist, FieldSim, SimEvent};

// ----------------------------------------------------------------------------------------------------------------
// runtime
// ----------------------------------------------------------------------------------------------------------------

/// Parameters of a battle started by the script (`InvokeBattle`) or by the encounter roll.
#[derive(Debug, Clone, PartialEq, Default)]
pub struct BattleOverride {
    pub background: Option<i32>,
    pub bgm: Option<i32>,
    pub boss: bool,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Phase {
    /// normal play
    Run,
    /// encounter flash before `StartBattle` (`BtlIn::CaptureBtlIn`)
    BattleFlash { timer: u32, monster_set: u16, over: BattleOverride },
    /// fade out for a map jump
    Leaving { timer: u32, map: String, entry: i32 },
    /// scene change requested; waiting for `SshSys` to swap the scene
    Handover,
}

#[derive(Clone, Resource)]
pub struct FieldRuntime {
    pub sim: FieldSim,
    pub vm: CScript,
    pub st: ScriptState,
    pub phase: Phase,
    /// scene fade (map enter / leave, battle flash)
    pub cover: Cover,
    /// the two script faders of `CFieldSocket` (`SetFader(slot, mode, ms)`: slot 1 = op 0x28 in front, slot 0 = op 0x29 behind the windows)
    pub faders: [crate::socket::Fader; 2],
    pub started: bool,
    pub debug: bool,
    /// map the runtime was built for
    pub map: String,
    pub events_fired: Vec<SimEvent>,
    /// the in-game menu was open last tick (clears `menu_wait` when it closes)
    pub menu_was_open: bool,
    last_calls: u64,
    stuck_ticks: u32,
    /// what the render side was last told about each script actor: `(generation, disp, pos, yaw)`
    published: std::collections::HashMap<usize, (u32, bool, [f32; 3], f32)>,
}

/// Sound requests queued by the field script; the audio layer drains this every frame (`sh2_script::audio::SoundBackend`).
#[derive(Resource, Default)]
pub struct FieldAudioQueue(pub Vec<FieldAudio>);

/// Disc / data handles of the field.
#[derive(Resource)]
pub struct FieldData {
    pub pkb: PkbSet,
    pub enc_table: Option<[u8; 3]>,
    pub tables: std::sync::Arc<FieldTables>,
}

#[derive(Component)]
pub struct FieldPlayerMesh;
#[derive(Component)]
pub struct FieldCamera3d;
/// A script-loaded actor other than the controlled one (placeholder capsule until real models are wired).
#[derive(Component)]
pub struct ScriptActorMesh {
    pub slot: usize,
    pub generation: u32,
}

pub(crate) fn disc_root(cfg: Option<&AppConfig>) -> std::path::PathBuf {
    if let Some(d) = std::env::var_os("SH2_DISC_DIR") {
        return d.into();
    }
    cfg.map(|c| c.disc_dir.clone()).unwrap_or_else(|| ".".into())
}

/// Item / monster / PC name lookup for `GetFieldData(0x1c)` and `TreasureControl(2)` from `COMMON/SSHMES.*` (RegDat name kinds).
pub(crate) fn name_lookup(pkb: &PkbSet) -> Option<std::sync::Arc<dyn Fn(u8, u32) -> Option<Vec<u8>> + Send + Sync>> {
    // retail build: the English `.NA` pair first (its kinds are translated by `RegDat::name_any`)
    let retail = sh2_core::boot::is_retail();
    let pick = |names: &[&str]| names.iter().find_map(|n| pkb.read(n));
    let mes = if retail { pick(&["COMMON/SSHMES.NA", "COMMON/SSHMES.JPN"]) } else { pick(&["COMMON/SSHMES.JPN", "COMMON/SSHMES.ENG", "COMMON/SSHMES.USA"]) }?;
    let dat = if retail { pick(&["COMMON/SSHDAT.NA", "COMMON/SSHDAT.JPN"]) } else { pick(&["COMMON/SSHDAT.JPN", "COMMON/SSHDAT.ENG", "COMMON/SSHDAT.USA"]) }?;
    Some(std::sync::Arc::new(move |kind: u8, idx: u32| {
        let rd = sh2_core::regdat::RegDat::new(&mes, &dat);
        let off = rd.name_any(kind, idx, 0)?;
        let b = mes.get(off..)?;
        let n = b.iter().position(|&c| c == 0).unwrap_or(b.len().min(0x40));
        Some(b[..n.min(0x40)].to_vec())
    }))
}

/// The retail `SSHMES.NA` / `SSHDAT.NA` pair (`FieldTables::us_rd`), `None` on the JP demo.
pub(crate) fn us_regdat(pkb: &PkbSet) -> Option<std::sync::Arc<(Vec<u8>, Vec<u8>)>> {
    let mes = pkb.read("COMMON/SSHMES.NA")?;
    let dat = pkb.read("COMMON/SSHDAT.NA")?;
    sh2_core::regdat::UsRegDat::new(&mes, &dat)?;
    Some(std::sync::Arc::new((mes, dat)))
}

/// The `DTCH` data container (`TRES`, `BBTL` ...): `FIELD/FIELD_T.DAT` on the JP demo, `FIELD/FIELD.DAT` on the US retail disc (same format; without it
/// every scripted battle `InvokeBattleTbl` and every treasure was silently skipped on the US disc).
pub fn read_field_t(pkb: &PkbSet) -> Option<Vec<u8>> {
    pkb.read("FIELD/FIELD_T.DAT").or_else(|| pkb.read("FIELD/FIELD.DAT")).filter(|d| d.starts_with(b"DTCH"))
}

fn load_field_data(mut commands: Commands, cfg: Option<Res<AppConfig>>) {
    let root = disc_root(cfg.as_deref());
    match PkbSet::open(&root) {
        Ok(pkb) => {
            let enc_table = std::fs::read(root.join("FIELD.BIN")).ok().and_then(|b| read_enc_dist(&b));
            let mut tables = FieldTables::default();
            if let Some(d) = read_field_t(&pkb) {
                tables.from_field_t(&d);
            }
            tables.names = name_lookup(&pkb);
            tables.us_rd = us_regdat(&pkb);
            commands.insert_resource(FieldData { pkb, enc_table, tables: std::sync::Arc::new(tables) });
        }
        Err(e) => log::error!("field: cannot open disc at {}: {e}", root.display()),
    }
}

/// Build the runtime for `map` (testable without Bevy).
pub fn build_runtime(pkb: &PkbSet, enc_table: Option<[u8; 3]>, map: &str, entry: i32, session: &GameSession) -> Option<FieldRuntime> {
    build_runtime_with(pkb, enc_table, None, map, entry, session)
}

pub fn build_runtime_with(
    pkb: &PkbSet,
    enc_table: Option<[u8; 3]>,
    tables: Option<std::sync::Arc<FieldTables>>,
    map: &str,
    entry: i32,
    session: &GameSession,
) -> Option<FieldRuntime> {
    build_runtime_carry(pkb, enc_table, tables, map, entry, session, None)
}

/// [`build_runtime_with`] after a `MapJump`: the models of the previous map survive (`CField::InitSDB`, US 0x004f7210, reuses the `CField`
/// and only hides its models; a displayed control model is shown again at the entry point).
pub fn build_runtime_carry(
    pkb: &PkbSet,
    enc_table: Option<[u8; 3]>,
    tables: Option<std::sync::Arc<FieldTables>>,
    map: &str,
    entry: i32,
    session: &GameSession,
    carry: Option<crate::script_actors::CarriedActors>,
) -> Option<FieldRuntime> {
    let mps = pkb.read(&format!("FIELD/MPS/{map}.MPS"))?;
    let mut sim = match FieldSim::new(map, mps, entry) {
        Ok(s) => s,
        Err(e) => {
            log::error!("field: map {map}: {e}");
            return None;
        }
    };
    if let Some(t) = enc_table {
        sim.enc_table = t;
    }
    let mut st = ScriptState::new();
    st.map_entry = entry;
    st.tables = Some(tables.unwrap_or_else(|| {
        let mut t = FieldTables::default();
        if let Some(d) = read_field_t(pkb) {
            t.from_field_t(&d);
        }
        std::sync::Arc::new(t)
    }));
    // come back from a battle / load: ChrPosSave
    if entry == FieldRequest::RESTORE {
        if let Some(cp) = session.chr_pos.as_ref().filter(|c| c.map == map) {
            sim.player.pos = cp.pos;
            sim.player.yaw = cp.yaw;
            sim.update_camera();
            st.restore = Some((cp.pos, cp.yaw));
        }
    }
    let mut vm = CScript::new(0x200, 0x400, 6000);
    match pkb.read(&format!("FIELD/MPS/{map}.MSC")) {
        Some(msc) => match vm.init_script(Some(map), &msc) {
            Ok(()) => {
                // LoadScriptRegister: the register file survives map jumps
                for (i, w) in session.regs.iter().take(vm.n_regs).enumerate() {
                    vm.mem.regs[i * 4..i * 4 + 4].copy_from_slice(&w.to_le_bytes());
                }
                vm.start_script();
            }
            Err(e) => log::warn!("field: script {map}.MSC: {e:?}"),
        },
        None => log::warn!("field: no script for {map}"),
    }
    if let Some(c) = carry {
        let shown = c.ctrl_shown;
        st.actors.take_carry(c);
        if shown && entry >= 0 {
            let ctrl = st.actors.ctrl as i32;
            let mut host = FieldHost { st: &mut st, sim: &mut sim, session: None };
            host.show_at_entry(ctrl, entry);
            // the shown control model is under pad control again on the new map (corridor maps such as AP_10_U never call `SetManual`)
            if let Some(a) = st.actors.get_mut(ctrl) {
                a.manual = true;
            }
        }
    }
    // BG models of the map (addressed 0x80|index by the script)
    if let Some(m) = sim.field.mps.as_ref().and_then(|m| m.models().ok()) {
        st.bg_models = m.len();
        st.actors.bg = vec![Default::default(); m.len()];
        for b in st.actors.bg.iter_mut() {
            b.cmd_done = true;
        }
    }
    Some(FieldRuntime {
        sim,
        vm,
        st,
        phase: Phase::Run,
        cover: Cover::opaque([0, 0, 0]),
        faders: [Default::default(); 2],
        started: false,
        debug: false,
        map: map.to_string(),
        events_fired: vec![],
        menu_was_open: false,
        last_calls: 0,
        stuck_ticks: 0,
        published: Default::default(),
    })
}

fn enter_field(
    mut commands: Commands,
    req: Res<FieldRequest>,
    data: Option<Res<FieldData>>,
    mut session: ResMut<GameSession>,
    mut pad: ResMut<GamePad>,
    mut menu: ResMut<InGameMenu>,
    sys: Option<Res<SshSys>>,
    mut carry: ResMut<FieldCarry>,
) {
    // `SSHSys::cbBattleA` (JP 0x003b6d90) keeps the result in `SSHSys+0x50..` (`SshSys::btl_result`); the scripts read it through
    // `GetFieldData(9)` / `(0xd)` (the session mirror `ssh_sys`)
    if req.entry == FieldRequest::RESTORE {
        if let Some(s) = sys.as_deref() {
            session.ssh_sys[0] = s.btl_result[0];
            session.ssh_sys[1] = s.btl_result[1];
            session.ssh_sys[2] = s.btl_result[2];
        }
    }
    // `CFieldSocket::fieldOverlay`: the map name WORLDMAP hands over to the world map instead of `CField`
    if req.map == crate::worldmap::WORLDMAP_NAME {
        commands.remove_resource::<FieldRuntime>();
        return;
    }
    let prev_map = std::mem::replace(&mut session.map, req.map.clone());
    pad.swallow();
    menu.open = false;
    menu.request = false;
    let Some(d) = data else {
        log::error!("field: no disc data");
        return;
    };
    let carried = carry.0.take().filter(|_| req.entry != FieldRequest::RESTORE);
    match build_runtime_carry(&d.pkb, d.enc_table, Some(d.tables.clone()), &req.map, req.entry, &session, carried) {
        Some(mut rt) => {
            // re-entering the same map (battle return, reload) keeps the map it was first entered from
            if prev_map != req.map {
                carry.1 = prev_map;
            }
            rt.st.prev_map = carry.1.clone();
            rt.cover.to_clear(30);
            log::info!(
                "field: entered {} (entry {}), {} event boxes, encounter rate {}",
                req.map,
                req.entry,
                rt.sim.field.event_boxes.as_ref().map(|e| e.boxes.len()).unwrap_or(0),
                rt.sim.enc.rate
            );
            commands.insert_resource(rt);
        }
        None => {
            log::error!("field: could not load map {}", req.map);
            commands.remove_resource::<FieldRuntime>();
        }
    }
}

/// FX X2: the field's `StartEffect` programs (`FIELD/EFF/<name>`) run on `sh2_gfx::effects::runner::FxRunner` (drawn by the effect renderer); the
/// script sees the program's state (`EffectControl(h, 0)`: 1 loading, 3 running, 0 ended).  Without the renderer the host's timer answers.
fn drive_field_effects(rt: Option<ResMut<FieldRuntime>>, runner: Option<ResMut<sh2_gfx::effects::runner::FxRunner>>, data: Option<Res<FieldData>>) {
    use sh2_gfx::effects::runner::RunState;
    use sh2_gfx::effects::scene::FxActor;
    let (Some(mut rt), Some(mut runner), Some(data)) = (rt, runner, data) else { return };
    let rt = &mut *rt;
    for h in std::mem::take(&mut rt.st.effect_removed) {
        runner.remove(h);
    }
    let place = |st: &crate::host::ScriptState, p: &crate::host::EffPlace| -> Option<FxActor> {
        match *p {
            crate::host::EffPlace::Pos(v) => Some(FxActor::at(Vec3::from_array(v), 30.0)),
            crate::host::EffPlace::Model(n) => st.actors.get(n).filter(|a| a.loaded).map(|a| FxActor::at(Vec3::from_array(a.pos), 30.0)),
        }
    };
    for i in 0..rt.st.effect_list.len() {
        let (gen, tar) = {
            let e = &rt.st.effect_list[i];
            (e.gen.iter().filter_map(|p| place(&rt.st, p)).collect::<Vec<_>>(), e.tar.iter().filter_map(|p| place(&rt.st, p)).collect::<Vec<_>>())
        };
        let e = &mut rt.st.effect_list[i];
        match e.runner {
            None if e.state != 0 && !e.runner_tried => {
                e.runner_tried = true;
                let file = format!("FIELD/EFF/{}", e.name.to_ascii_uppercase());
                if let Some(bytes) = data.pkb.read(&file) {
                    if let Some(h) = runner.start(&e.name, bytes, gen, tar) {
                        e.runner = Some(h);
                    }
                }
            }
            Some(h) => {
                runner.set_env(h, gen, tar);
                e.state = match runner.state(h) {
                    Some(RunState::Loading) => 1,
                    Some(RunState::Running) => 3,
                    Some(RunState::Finished) | None => 0,
                };
            }
            _ => {}
        }
    }
    for (key, bank, id) in runner.drain_sounds() {
        sh2_audio::post(sh2_audio::AudioRequest::PlayEffectSe { key: format!("FLDFX:{key}"), bank, id });
    }
}

fn clear_field_effects(runner: Option<ResMut<sh2_gfx::effects::runner::FxRunner>>) {
    if let Some(mut r) = runner {
        r.clear();
    }
}

/// The field's vibration sequences (ops 0x69..0x6e) -> `sh2_menu::vibration::VibrationRequest` pulses (CS4).
fn forward_field_vibration(rt: Option<Res<FieldRuntime>>, out: Option<ResMut<Messages<sh2_menu::vibration::VibrationRequest>>>) {
    let (Some(rt), Some(mut out)) = (rt, out) else { return };
    let (big, small) = rt.st.vib_out;
    if big > 0.0 || small {
        out.write(sh2_menu::vibration::VibrationRequest { strength: if big > 0.0 { big } else { 1.0 }, ms: 50 });
    }
}

/// Models kept from the map that was left by a `MapJump` (see [`build_runtime_carry`]).
#[derive(Resource, Default)]
pub struct FieldCarry(pub Option<crate::script_actors::CarriedActors>, pub String);

fn exit_field(
    mut commands: Commands,
    rt: Option<ResMut<FieldRuntime>>,
    mut session: ResMut<GameSession>,
    mut canvas: ResMut<UiCanvas>,
    req: Res<FieldRequest>,
    mut carry: ResMut<FieldCarry>,
) {
    carry.0 = None;
    if let Some(mut rt) = rt {
        // `CFieldSocket` reuses the `CField` for a map jump (not for a battle / the world map / the title)
        if req.entry != FieldRequest::RESTORE && req.map != crate::worldmap::WORLDMAP_NAME && matches!(rt.phase, Phase::Handover) && !rt.st.game_over {
            carry.0 = Some(rt.st.actors.carry_over());
        }
        // SaveScriptRegister
        let n = rt.vm.n_regs.min(session.regs.len());
        for i in 0..n {
            session.regs[i] = u32::from_le_bytes(rt.vm.mem.regs[i * 4..i * 4 + 4].try_into().unwrap());
        }
        session.map = rt.map.clone();
        rt.vm.delete_requested = true;
    }
    commands.remove_resource::<FieldRuntime>();
    for l in [layer::FIELD, layer::FADER] {
        canvas.clear(l);
    }
}

// ----------------------------------------------------------------------------------------------------------------
// per-tick systems
// ----------------------------------------------------------------------------------------------------------------

/// Pump the script's event queue into the VM (`CField::SetFieldEvent` -> `CScript::CallEvent`).
pub fn pump_events(rt: &mut FieldRuntime) {
    for (id, args) in std::mem::take(&mut rt.st.event_queue) {
        if rt.vm.call_event(id, &args) {
            rt.st.event_running = true;
        }
    }
}

/// `CScript::Polling` for the map script (prio 0x70).
pub fn field_script_tick(pad: Res<GamePad>, rt: Option<ResMut<FieldRuntime>>, menu: Res<InGameMenu>, mut session: ResMut<GameSession>) {
    let Some(mut rt) = rt else { return };
    if menu_blocks_field(&menu) && !rt.st.menu_wait {
        return;
    }
    let rt = &mut *rt;
    rt.st.press = pad.press();
    // Options consumer: `MenuMessage::SetDefault` takes the typewriter speed from the `MENU+0x274` option byte (bits 4-5: slow / normal / fast / instant)
    rt.st.ui.speed = sh2_menu::message::TextSpeed::from_option(session.save.menu.data[sh2_menu::save::MenuSave::OFF_OPT0]);
    {
        let FieldRuntime { st, sim, .. } = rt;
        tick_state(st, sim);
    }
    pump_events(rt);
    rt.vm.set_pad(PadState { raw: pad.real() as u32, new_press: pad.press() as u32, repeat: pad.repeat() as u32, consumed: 0 });
    let idle = rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(&mut session) });
    if idle {
        rt.st.event_running = false;
    }
    // watchdog: an event that blocks forever (unimplemented wait) must not lock the player for good
    if rt.st.event_running && !rt.st.msg_active() && rt.st.calls == rt.last_calls && rt.st.mces.state == 0 && !rt.st.menu_wait {
        rt.stuck_ticks += 1;
        if rt.stuck_ticks > 1800 {
            log::warn!("field: script event idle for 30 s without a window; releasing the player");
            rt.st.event_running = false;
            rt.stuck_ticks = 0;
        }
    } else {
        rt.stuck_ticks = 0;
    }
    rt.last_calls = rt.st.calls;
    rt.started = true;
}

fn drain_requests(rt: &mut FieldRuntime, audio: &mut FieldAudioQueue) {
    for a in std::mem::take(&mut rt.st.audio) {
        log::debug!("field audio: {a:?}");
        audio.0.push(a);
    }
    if audio.0.len() > 4096 {
        let n = audio.0.len() - 4096;
        audio.0.drain(..n);
    }
}

/// `CField::Polling` (prio 0x80).
#[allow(clippy::too_many_arguments)]
pub fn field_logic_tick(
    pad: Res<GamePad>,
    rt: Option<ResMut<FieldRuntime>>,
    mut menu: ResMut<InGameMenu>,
    mut session: ResMut<GameSession>,
    mut sys: ResMut<SshSys>,
    mut field_req: ResMut<FieldRequest>,
    mut canvas: ResMut<UiCanvas>,
    mut audio: ResMut<FieldAudioQueue>,
    mut wm_req: ResMut<crate::worldmap::WorldMapRequest>,
    mut screens: ResMut<crate::fscreen::FieldScreens>,
    keys: Option<Res<ButtonInput<KeyCode>>>,
    // round 5 FX: the encounter shatter (`BtlIn`, sh2_gfx::effects::btlin)
    (mut btlin, cfg): (Option<ResMut<sh2_gfx::effects::btlin::BtlInFx>>, Option<Res<AppConfig>>),
) {
    let Some(mut rt) = rt else { return };
    let rt = &mut *rt;
    // `CField::StartBattle` -> `CaptureBtlIn`: the frame shatters (falls back to the white flash without the disc tables)
    let mut shatter = |boss: bool| btlin.as_deref_mut().map(|b| b.capture(&disc_root(cfg.as_deref()), boss)).unwrap_or(false);
    // a shop / tailor / ... screen was closed: the script that opened it continues (`cbShop(3)` -> `CField::Pause(1)`)
    if screens.take_finished() {
        rt.st.menu_wait = false;
        // the name entry's result goes to the message variable buffer (`CField+0x2170`, read by `SpecialMenu(-1)`)
        if let Some(n) = screens.name_result.clone() {
            rt.st.name_buffer = n.into_bytes();
        }
        if let Some((map, entry)) = screens.jump.take() {
            rt.st.pending_jump = Some((map, entry));
        }
    }
    rt.cover.tick();
    // CFieldSocket::UpdateFader: the frame delta is in milliseconds
    let dt = 16 + (rt.st.ticks % 3 == 0) as u32;
    for f in rt.faders.iter_mut() {
        f.update(dt);
    }
    drain_requests(rt, &mut audio);
    if let Some(k) = keys.as_deref() {
        if k.just_pressed(KeyCode::F3) {
            rt.debug = !rt.debug;
        }
    }
    // script fader requests
    for (slot, mode, frames) in std::mem::take(&mut rt.st.faders) {
        if std::env::var_os("SH2_FIELD_DEBUG").is_some() {
            log::info!("field {}: SetFader(slot {slot}, mode {mode:#x}, frames {frames}) at tick {}", rt.map, rt.st.ticks);
        }
        rt.faders[(slot as usize).min(1)].set(mode as u8, frames);
    }
    if std::env::var_os("SH2_FIELD_DEBUG").is_some() && rt.st.ticks % 120 == 0 {
        log::info!("field {}: tick {} cover {:.2}->{:.2} faders {:#x}/{:#x} msg {} ev {} pos {:?}", rt.map, rt.st.ticks, rt.cover.alpha, rt.cover.target, rt.faders[0].alpha, rt.faders[1].alpha, rt.st.msg_active(), rt.st.event_running, rt.sim.player.pos);
    }
    // menu opened by the script has been closed
    // (a menu page that launched a field screen -- the real Save / Load screen -- keeps the script waiting until that screen ends)
    if rt.menu_was_open && !menu.open && !menu.request && !screens.is_active() {
        rt.st.menu_wait = false;
    }
    rt.menu_was_open = menu.open || menu.request;
    session.distance = rt.sim.walked;
    let locked = rt.st.msg_active()
        || rt.st.ui.select.active
        || (rt.st.event_running && rt.vm.is_running())
        || rt.st.menu_wait
        || screens.is_active()
        || menu_blocks_field(&menu)
        || menu.closed_at + 2 > menu.tick && menu.closed_at != 0
        // `CField::Polling` (US 0x004f32d0): the box / examine / encounter checks need a control model that exists, is displayed (`+0x90` bits 2-3) and
        // is under pad control (`+0x98` bit 0); a map whose script unloaded every model (a cut scene) cannot fire box events
        || !rt.st.actors.get(rt.st.actors.ctrl as i32).map(|a| a.manual && a.loaded && a.disp).unwrap_or(false);
    match rt.phase.clone() {
        Phase::Run => {
            // CField::Polling waits for `CFieldSocket::isStable` (the scene fader is not running)
            let fading = rt.faders.iter().any(|f| f.state & 0xf != 0 && f.cur as i32 != f.total as i32);
            let frozen = locked || fading || !rt.cover.clear() && rt.cover.alpha > 0.5 || rt.st.warp_fx.is_some() || rt.st.mces.state != 0;
            let mut press = if locked { 0 } else { pad.press() };
            let circle_pressed = press & padbit::CIRCLE != 0 && !frozen;
            let mut circle_used = false;
            // circle: talk to the NPC in front of the player (JP Polling: nearest displayed model within 12 units), else probe the event box
            if press & padbit::CIRCLE != 0 && !frozen {
                if let Some(slot) = rt.st.actors.talk_target(rt.sim.player.pos, rt.sim.player.yaw) {
                    let ev = rt.st.actors.slots[slot].as_ref().map(|a| a.event_id).unwrap_or(0);
                    if ev != 0 && rt.vm.call_event(ev, &[4]) {
                        rt.st.event_running = true;
                        press &= !padbit::CIRCLE;
                        circle_used = true;
                    }
                }
            }
            let menu_allowed = rt.st.cmd_menu_mask & 0xf == 0;
            if !menu_allowed {
                press &= !padbit::TRIANGLE;
            }
            // the sim's own player control is only active while the script gave control to the pad
            let events = rt.sim.tick(pad.real(), press, frozen);
            for e in events {
                log::debug!("field event {e:?} at {:?}", rt.sim.player.pos);
                rt.events_fired.push(e.clone());
                match e {
                    SimEvent::BoxEnter(id) => {
                        if rt.vm.call_event(id as u32, &[1]) {
                            rt.st.event_running = true;
                        }
                    }
                    SimEvent::BoxLeave(id) => {
                        if rt.vm.call_event(id as u32, &[2]) {
                            rt.st.event_running = true;
                        }
                    }
                    SimEvent::Examine(id) => {
                        circle_used = true;
                        if rt.vm.call_event(id as u32, &[4]) {
                            rt.st.event_running = true;
                        }
                    }
                    SimEvent::MenuRequest => {
                        // CField::Polling: triangle -> CFieldSocket::CheckCmdMenu -> CommandMenu(4, ChkSavePoint() >= 0)
                        rt.st.menu_save_ok = rt.st.on_save_point.is_some();
                        menu.save_gate = Some(rt.st.menu_save_ok);
                        menu.request = true;
                    }
                    SimEvent::Battle { monster_set } => {
                        // CheckEncount > 0 -> ScriptSuspend -> InvokeBattle
                        rt.vm.pause(true);
                        if !shatter(false) {
                            rt.cover.color = [255, 255, 255];
                            rt.cover.to_opaque(20);
                        }
                        rt.phase = Phase::BattleFlash { timer: 24, monster_set, over: BattleOverride::default() };
                        break;
                    }
                }
            }
            // look points (`SetLookPoint`): the nearest hot spot shows its icon; circle with nothing else in front fires its default event
            // (JP Polling: `ChkLookPoint(1)`; `SetFieldEvent(1, event, 0, 0, id)` -> the event gets `[0, id]`)
            if matches!(rt.phase, Phase::Run) && !frozen {
                let (att, det) = rt.st.look.check(rt.sim.player.pos);
                let ctrl = rt.st.actors.ctrl as i32;
                if det.is_some() {
                    if let Some(a) = rt.st.actors.get_mut(ctrl) {
                        a.icon = -1;
                    }
                }
                if let Some(i) = att {
                    let icon = rt.st.look.slots[i].map(|s| s.icon).unwrap_or(0xf);
                    if let Some(a) = rt.st.actors.get_mut(ctrl) {
                        a.icon = if icon == 0xf { -1 } else { icon as i32 };
                    }
                }
                if circle_pressed && !circle_used {
                    if let Some((ev, id)) = rt.st.look.circle_event() {
                        if rt.vm.call_event(ev, &[0, id as u32]) {
                            rt.st.event_running = true;
                        }
                    }
                }
            }
            // requests from the script
            if matches!(rt.phase, Phase::Run) {
                if let Some(b) = rt.st.battle.take() {
                    rt.vm.pause(true);
                    if !shatter(b.boss) {
                        rt.cover.color = [255, 255, 255];
                        rt.cover.to_opaque(20);
                    }
                    rt.phase = Phase::BattleFlash {
                        timer: 24,
                        monster_set: b.monster_set.clamp(0, 0xffff) as u16,
                        over: BattleOverride { background: (b.background >= 0).then_some(b.background), bgm: (b.bgm > 0).then_some(b.bgm), boss: b.boss },
                    };
                } else if let Some((world, sub, extra)) = rt.st.world_map_jump.take() {
                    *wm_req = crate::worldmap::WorldMapRequest { world, sub, extra, pending: true, from_title: false };
                    rt.cover.color = [0, 0, 0];
                    rt.cover.to_opaque(20);
                    rt.phase = Phase::Leaving { timer: 24, map: crate::worldmap::WORLDMAP_NAME.to_string(), entry: 0 };
                } else if let Some((map, entry)) = rt.st.pending_jump.take() {
                    rt.cover.color = [0, 0, 0];
                    rt.cover.to_opaque(20);
                    rt.phase = Phase::Leaving { timer: 24, map, entry };
                } else if let Some(req) = rt.st.menu_req.take() {
                    match req {
                        // (round 5 MN) retail `InvokeCmdScene(a, b)`: the Graveyard soul charge screen
                        MenuReq::CmdScene { a, b } => {
                            log::info!("field: soul charge {a} / {b} requested");
                            screens.req = Some(crate::fscreen::ScreenReq::SoulCharge { a, b });
                        }
                        MenuReq::Main { .. } | MenuReq::Sub { .. } | MenuReq::Tutorial { .. } => {
                            menu.request = true;
                        }
                        MenuReq::Save => {
                            // `CommandMenu(0x10)`: the save screen (`dataAccess`) opens straight away
                            menu.request = true;
                            menu.script.acts.push_back(crate::menu_overlay::Act::GotoData(false));
                        }
                        MenuReq::Shop { id } => {
                            log::info!("field: shop {id} requested");
                            screens.req = Some(crate::fscreen::ScreenReq::Shop { id });
                        }
                        MenuReq::NameEntry => {
                            screens.req = Some(crate::fscreen::ScreenReq::NameEntry { kind: 1, current: String::new() });
                        }
                        MenuReq::WolfStamp { bout } => {
                            screens.req = Some(crate::fscreen::ScreenReq::WolfStamp { bout });
                        }
                        MenuReq::Tailor => {
                            log::info!("field: tailor requested");
                            screens.req = Some(crate::fscreen::ScreenReq::Tailor);
                        }
                        MenuReq::GameOver => {
                            sys.set_api(SshApi::GameOver);
                            rt.phase = Phase::Handover;
                        }
                        MenuReq::EndToTitle => {
                            log::info!("field: SpecialMenu(7): the field ends, back to the title");
                            sys.request_title();
                            rt.phase = Phase::Handover;
                        }
                    }
                }
            }
        }
        Phase::BattleFlash { timer, monster_set, over } => {
            // the shatter overlay covers the frame as soon as its capture is in: hand over right away (`CField::Polling` deletes the field the next tick)
            let covered = btlin.as_deref().map(|b| b.covering()).unwrap_or(false);
            if timer > 0 && !covered {
                rt.phase = Phase::BattleFlash { timer: timer - 1, monster_set, over };
            } else {
                // SSHSys::StartBattle(&btlParam, field)
                let party = {
                    let p = session.battle_party();
                    if p.is_empty() {
                        vec![5u8, 0, 1]
                    } else {
                        p
                    }
                };
                let mut pc = [0xffu8; 4];
                for (i, id) in party.iter().take(4).enumerate() {
                    pc[i] = *id;
                }
                let fd = rt.st.field_data;
                // `SetFieldData(6, v)` stores the battle BGM (`GetFieldBattleInfo()+2`), `SetFieldData(7, v)` the battle background (`+4`); `CField::StartBattle`
                // passes `+4` as `_SysBtlParam` word 0 (BBG id) and `+2` as the BGM (decomp/G/CField.c:4739, 7557).  The MONSET header holds them in that order too.
                let mut fd = [if fd[7] != 0 { fd[7] } else { rt.sim.field.field_data[7] }, if fd[6] != 0 { fd[6] } else { rt.sim.field.field_data[6] }];
                if let Some(b) = over.background {
                    fd[0] = b;
                }
                if let Some(b) = over.bgm {
                    fd[1] = b;
                }
                let param = SysBtlParam {
                    w0: fd[0] as u32,
                    regdat_id: monster_set as i32,
                    bgm: if fd[1] == 0 { 0x191 } else { fd[1] as u16 },
                    pc_count: party.len().min(4) as u8,
                    monster_set: 1,
                    pc,
                };
                session.chr_pos = Some(ChrPos { map: rt.map.clone(), pos: rt.sim.player.pos, yaw: rt.sim.player.yaw });
                // op 0x2b sub 2 renamed the socket's map: the battle returns there (`CFieldSocket+0x64`)
                let back = rt.st.retail.socket_map.clone().unwrap_or_else(|| rt.map.clone());
                // `SetFieldData(8)`: a defeat in this battle returns to the field (`SSHSys+0x52`, read by `cbBattleA`)
                sys.btl_result[2] = session.ssh_sys[2];
                sys.start_battle(Some(param), Some(&back));
                sys.start_battle(None, None);
                field_req.map = back;
                field_req.entry = FieldRequest::RESTORE;
                rt.phase = Phase::Handover;
                log::info!("field: encounter -> battle (monster set {monster_set}) at {:?}", rt.sim.player.pos);
            }
        }
        Phase::Leaving { timer, map, entry } => {
            if timer > 0 {
                rt.phase = Phase::Leaving { timer: timer - 1, map, entry };
            } else {
                // InitFieldSocketM(name): retarget the socket and SetAPI it
                field_req.map = map.clone();
                field_req.entry = entry;
                if sys.set_api(SshApi::FieldSocket) {
                    log::info!("field: map jump {} -> {map} (entry {entry})", rt.map);
                    rt.phase = Phase::Handover;
                } else {
                    rt.phase = Phase::Leaving { timer: 0, map, entry };
                }
            }
        }
        Phase::Handover => {
            rt.sim.update_camera();
        }
    }
    draw_field_ui(rt, &mut canvas);
}

/// Script actors -> the real character models of [`crate::actors`] (op 0x08 `LoadCharacter` ... 0x16 `SetCharacterDir`).  Without the
/// `ActorPlugin` resources the placeholder capsules are used.  Motion lengths are taken from the model: a finite script motion lasts until
/// the model reports it finished.
pub fn bridge_actors(
    rt: Option<ResMut<FieldRuntime>>,
    cmds: Option<ResMut<crate::actors::ActorCommands>>,
    reg: Option<Res<crate::actors::ActorRegistry>>,
    models: Query<&crate::actors::CharacterModel>,
) {
    use crate::actors::{ActorCommand, ActorKind, ActorPose, ActorSpawn, MotionRef};
    use crate::script_actors::ActorOut;
    let (Some(mut rt), Some(mut cmds)) = (rt, cmds) else { return };
    let rt = &mut *rt;
    let ctrl = rt.st.actors.ctrl;
    // presentation requests first (motions / move motions)
    for o in std::mem::take(&mut rt.st.actors.out) {
        match o {
            ActorOut::Motion { slot, id, name, chain } => {
                let motion = if !name.is_empty() { MotionRef::Name(name) } else { MotionRef::Id(id) };
                cmds.push(if chain { ActorCommand::ChainMotion { slot: slot as i32, motion } } else { ActorCommand::SetMotion { slot: slot as i32, motion } });
            }
            ActorOut::MoveMotion { slot, idle, walk, run } => cmds.push(ActorCommand::SetMoveMotion { slot: slot as i32, idle, walk, run }),
            ActorOut::Gait { slot, gait } => cmds.push(ActorCommand::SetGait { slot: slot as i32, gait }),
        }
    }
    for slot in 0..crate::script_actors::MAX_SLOTS {
        let cur = rt.st.actors.slots[slot].as_ref().filter(|a| a.loaded);
        let Some(a) = cur else {
            if rt.published.remove(&slot).is_some() && slot != ctrl {
                cmds.push(ActorCommand::Unload(slot as i32));
            }
            continue;
        };
        let state = (a.generation, a.disp, a.pos, a.yaw);
        match rt.published.get(&slot).copied() {
            Some(p) if p == state => {}
            Some(p) if p.0 == a.generation => {
                if p.1 != a.disp {
                    cmds.push(ActorCommand::SetVisible { slot: slot as i32, visible: a.disp });
                }
                if slot != ctrl && (p.2 != a.pos || p.3 != a.yaw) {
                    cmds.push(ActorCommand::SetPose { slot: slot as i32, pose: ActorPose { pos: a.pos, yaw: a.yaw } });
                }
                rt.published.insert(slot, state);
            }
            _ => {
                // `LoadCharacterByName` slots carry the package name (`"037W00R.SET"` -> `FIELD/MODEL/037W00R.SET`); numbers load `%03d.SET`
                if slot != ctrl {
                    let spawn = if a.char_id >= 0 {
                        Some(ActorSpawn { slot: slot as i32, model_no: a.char_id as u32, kind: ActorKind::Npc, pose: ActorPose { pos: a.pos, yaw: a.yaw }, visible: a.disp, motion: None, file: None })
                    } else if !a.model_name.trim().is_empty() {
                        let mut sp = ActorSpawn::npc_by_name(slot as i32, &a.model_name, a.pos, a.yaw);
                        sp.visible = a.disp;
                        Some(sp)
                    } else {
                        None
                    };
                    if let Some(sp) = spawn {
                        cmds.push(ActorCommand::Load(sp));
                    }
                }
                rt.published.insert(slot, state);
            }
        }
    }
    // real motion lengths: hold a finite script motion until the model says it ended
    if let Some(reg) = reg {
        for slot in 0..crate::script_actors::MAX_SLOTS {
            let Some(e) = reg.get(slot as i32) else { continue };
            let Ok(cm) = models.get(e) else { continue };
            if let Some(a) = rt.st.actors.slots[slot].as_mut() {
                if a.motion_left > 0 && !a.motion_loop && a.motion_age < 1500 {
                    if cm.motion_finished() && a.motion_age > 3 {
                        a.motion_left = 1;
                    } else if a.motion_left < 4 {
                        a.motion_left = 4;
                    }
                }
            }
        }
    }
}

/// `CField::CameraUpdate` is part of `FieldSim::tick`; this stage only publishes the pose (kept for the schedule ordering).
pub fn field_camera_tick(rt: Option<ResMut<FieldRuntime>>) {
    let Some(mut rt) = rt else { return };
    if rt.sim.pose.is_none() {
        rt.sim.update_camera();
    }
}

/// A `CFieldSocket` fader: full screen colour with the fader's current alpha (0..=0x80).
fn draw_fader(f: &crate::socket::Fader, g: &mut dyn sh2_menu::gfx::MenuGfx) {
    if f.alpha > 0 && f.is_displayed() {
        let c = f.color;
        bevy_ui::rect(g, 0.0, 0.0, bevy_ui::VIRT_W, bevy_ui::VIRT_H, Rgba::new((c >> 16) as u8, (c >> 8) as u8, c as u8, f.alpha));
    }
}

fn draw_field_ui(rt: &FieldRuntime, canvas: &mut UiCanvas) {
    {
        let mut g = canvas.begin(layer::FIELD);
        // back fader (op 0x29) sits behind the windows
        draw_fader(&rt.faders[0], &mut g);
        // images (`FldSprite`) are not rendered yet; their state is tracked for the scripts
        // message windows (`FieldMessage` / `MenuWindowMessage`)
        let ui = &rt.st.ui;
        for (wi, w) in ui.windows.iter().enumerate() {
            if w.phase == WinPhase::Closed || (w.msg.is_none() && !ui.select.active) {
                continue;
            }
            let (pw, ph) = w.size_px();
            let anim = match w.phase {
                WinPhase::Opening(n) => 1.0 - n as f32 / 30.0,
                WinPhase::Closing(n) => n as f32 / 30.0,
                _ => 1.0,
            };
            let (x, y) = (w.x as f32, w.y as f32);
            let h = ph * anim.clamp(0.15, 1.0);
            bevy_ui::panel(&mut g, x, y + (ph - h) * 0.5, pw, h, 0x78);
            if anim < 0.9 {
                continue;
            }
            if let Some(m) = &w.msg {
                m.draw(&mut g, x + 12.0, y + 9.0, Rgba::NEUTRAL);
                if m.state == sh2_menu::message::MsgState::Done && w.key_pending {
                    bevy_ui::text(&mut g, x + pw - 22.0, y + ph - 20.0, "v", bevy_ui::FIELD_FONT, Rgba::new(0x80, 0x80, 0x30, 0x80), false);
                }
            }
            if ui.select.active && ui.select.window == wi {
                let base = y + 9.0 + (w.raw.iter().filter(|&&b| b == b'\n').count() as f32 + if w.raw.is_empty() { 0.0 } else { 1.0 }) * CELL_H;
                for (i, it) in ui.select.items.iter().enumerate() {
                    let sel = i == ui.select.cursor;
                    let ty = base + i as f32 * CELL_H * 0.9;
                    if sel {
                        bevy_ui::rect(&mut g, x + 8.0, ty - 2.0, pw - 16.0, CELL_H * 0.9, Rgba::new(0x60, 0x60, 0xc0, 0x50));
                    }
                    let mut m = sh2_menu::message::Message::new(64, sh2_menu::message::TextSpeed::Instant);
                    crate::script_ui::field_text_style(&mut m);
                    m.set_text(it, vec![]);
                    m.finish();
                    m.draw(&mut g, x + 30.0, ty, if sel { Rgba::new(0x80, 0x80, 0x40, 0x80) } else { Rgba::NEUTRAL });
                    if sel {
                        bevy_ui::text(&mut g, x + 12.0, ty, ">", bevy_ui::FIELD_FONT, Rgba::new(0x80, 0x80, 0x30, 0x80), false);
                    }
                }
            }
        }
        // name plates
        for w in ui.names.iter().filter(|w| w.phase != WinPhase::Closed && w.msg.is_some()) {
            let (pw, _) = w.size_px();
            let pw = pw.min(w.msg.as_ref().map(|m| m.glyphs.iter().map(|g| g.width as f32).sum::<f32>() + 28.0).unwrap_or(pw)).max(60.0);
            bevy_ui::panel(&mut g, w.x as f32, w.y as f32, pw, CELL_H + 12.0, 0x78);
            if let Some(m) = &w.msg {
                // the colour is the plate's CLUT row, not a tint
                let mut m = m.clone();
                m.clut_set = crate::script_ui::NAME_CLUT;
                m.draw(&mut g, w.x as f32 + 12.0, w.y as f32 + 6.0, Rgba::NEUTRAL);
            }
        }
        // faces (portraits are drawn as labelled frames until the face textures are wired)
        for f in ui.faces.iter().filter(|f| f.loaded && f.open) {
            bevy_ui::panel(&mut g, f.x, f.y, f.w.max(16.0), f.h.max(16.0), 0x60);
            bevy_ui::text(&mut g, f.x + 6.0, f.y + 6.0, &format!("face {}", f.face_id), 4, Rgba::NEUTRAL, true);
        }
        // timer (`FldTimer`)
        let t = &ui.timer;
        if t.created && t.shown {
            let secs = t.count / 10;
            bevy_ui::text(&mut g, t.x as f32, t.y as f32, &format!("{:02}:{:02}.{}", secs / 60, secs % 60, t.count % 10), 2, Rgba::NEUTRAL, true);
        }
        // HUD
        // dev map-name label: hidden while a cut scene / movie plays over the field (CS3)
        if rt.st.mces.state == 0 && std::env::var_os("SH2_HIDE_MAP_LABEL").is_none() {
            bevy_ui::text(&mut g, 8.0, 4.0, &rt.map, 4, Rgba::new(0x80, 0xc0, 0xff, 0x60), true);
        }
        if rt.debug {
            bevy_ui::text(
                &mut g,
                8.0,
                16.0,
                &format!("pos {:.0},{:.0},{:.0}  box {}  enc {}/{} dist {:.0}", rt.sim.player.pos[0], rt.sim.player.pos[1], rt.sim.player.pos[2], rt.sim.cur_box, rt.sim.enc.rate, rt.sim.enc.misses, rt.sim.enc.dist),
                4,
                Rgba::NEUTRAL,
                true,
            );
        }
    }
    let mut f = canvas.begin(layer::FADER);
    draw_fader(&rt.faders[1], &mut f);
    rt.cover.draw(&mut f);
    // DoWarp flash
    if let Some(fx) = rt.st.warp_fx {
        let k = fx.ticks_left as f32 / fx.total.max(1) as f32;
        let a = if fx.incoming { k } else { 1.0 - k };
        bevy_ui::rect(&mut f, 0.0, 0.0, bevy_ui::VIRT_W, bevy_ui::VIRT_H, Rgba::new(fx.color[0], fx.color[1], fx.color[2], (a * 128.0) as u8));
    }
    let _ = CELL_W;
}

// ----------------------------------------------------------------------------------------------------------------
// rendering glue
// ----------------------------------------------------------------------------------------------------------------

fn b(p: [f32; 3]) -> Vec3 {
    // PS2 y-down/z-forward -> Bevy y-up (rotation of PI about X, same as `sh2_gfx::bevy::model::ps2_to_bevy`)
    Vec3::new(p[0], -p[1], -p[2])
}

fn debug_cameras(cams: Query<(Entity, &Camera, Option<&Camera3d>, Option<&Transform>)>, maps: Query<&Visibility, With<crate::bevy::FieldMapRoot>>, rt: Option<Res<FieldRuntime>>, canvas: Res<UiCanvas>, wm: Option<Res<crate::worldmap_plugin::WorldMapRuntime>>) {
    if std::env::var_os("SH2_FIELD_DEBUG").is_none() {
        return;
    }
    let Some(rt) = rt else { return };
    if rt.st.ticks % 180 != 1 {
        return;
    }
    for (e, c, c3, t) in &cams {
        log::info!("camera {e:?} order {} active {} 3d {} at {:?}", c.order, c.is_active, c3.is_some(), t.map(|t| t.translation));
    }
    log::info!("pose {:?} scr_cam {:?} comp {}", rt.sim.pose, rt.sim.scr_cam, rt.sim.field.camera.is_comp());
    log::info!("map roots: {:?} ui cmds scene {} field {} fader {} menu {} worldmap {}", maps.iter().collect::<Vec<_>>(), canvas.live_commands(layer::SCENE), canvas.live_commands(layer::FIELD), canvas.live_commands(layer::FADER), canvas.live_commands(layer::MENU), wm.is_some());
}

fn spawn_scene(
    mut commands: Commands,
    rt: Option<Res<FieldRuntime>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<StandardMaterial>>,
    req: Res<FieldRequest>,
) {
    let Some(rt) = rt else { return };
    // background geometry: handled by `FieldMapPlugin` through this request (the map root is kept alive between visits)
    commands.insert_resource(crate::bevy::FieldMapRequest { name: req.map.clone() });
    // 3D camera
    commands.spawn((
        Camera3d::default(),
        Camera { order: 0, ..default() },
        Projection::Perspective(PerspectiveProjection { fov: 0.83, aspect_ratio: 512.0 / 448.0, near: 2.0, far: 30000.0, ..default() }),
        Transform::from_translation(b([0.0, -50.0, -150.0])).looking_at(Vec3::ZERO, Vec3::Y),
        FieldCamera3d,
        DespawnOnExit(Scene::Field),
    ));
    // placeholder player: capsule + nose cube (unlit so no light rig is needed)
    let body = materials.add(StandardMaterial { base_color: Color::srgb(0.85, 0.2, 0.25), unlit: true, ..default() });
    let nose = materials.add(StandardMaterial { base_color: Color::srgb(1.0, 0.9, 0.3), unlit: true, ..default() });
    let p = rt.sim.player.pos;
    commands
        .spawn((
            Mesh3d(meshes.add(Capsule3d::new(3.8, 16.0))),
            MeshMaterial3d(body),
            Transform::from_translation(b(p) + Vec3::Y * 17.0),
            FieldPlayerMesh,
            DespawnOnExit(Scene::Field),
        ))
        .with_children(|c| {
            c.spawn((Mesh3d(meshes.add(Cuboid::new(3.0, 3.0, 8.0))), MeshMaterial3d(nose), Transform::from_xyz(0.0, 6.0, -7.0)));
        });
}

/// Placeholder bodies for the other script actors (`LoadCharacter` + `DispCharacter`): one capsule per displayed slot.
fn sync_actor_meshes(
    mut commands: Commands,
    rt: Option<Res<FieldRuntime>>,
    reg: Option<Res<crate::actors::ActorRegistry>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<StandardMaterial>>,
    mut q: Query<(Entity, &ScriptActorMesh, &mut Transform, &mut Visibility)>,
) {
    let Some(rt) = rt else { return };
    let real = |slot: usize| reg.as_ref().map(|r| r.get(slot as i32).is_some()).unwrap_or(false);
    let mut have = std::collections::HashSet::new();
    for (e, tag, mut t, mut vis) in &mut q {
        let a = rt.st.actors.slots.get(tag.slot).and_then(|a| a.as_ref());
        match a {
            Some(a) if a.loaded && a.generation == tag.generation && tag.slot != rt.st.actors.ctrl && !real(tag.slot) => {
                have.insert(tag.slot);
                *vis = if a.disp { Visibility::Inherited } else { Visibility::Hidden };
                let dir = Vec3::new(a.yaw.sin(), 0.0, -a.yaw.cos());
                *t = Transform::from_translation(b(a.pos) + Vec3::Y * 17.0).looking_to(dir, Vec3::Y);
            }
            _ => commands.entity(e).despawn(),
        }
    }
    for (slot, a) in rt.st.actors.slots.iter().enumerate() {
        let Some(a) = a else { continue };
        if !a.loaded || have.contains(&slot) || slot == rt.st.actors.ctrl || real(slot) {
            continue;
        }
        let hue = (slot as f32 * 0.17 + a.char_id.max(0) as f32 * 0.05) % 1.0;
        let body = materials.add(StandardMaterial { base_color: Color::hsl(hue * 360.0, 0.55, 0.5), unlit: true, ..default() });
        let nose = materials.add(StandardMaterial { base_color: Color::srgb(1.0, 0.95, 0.6), unlit: true, ..default() });
        commands
            .spawn((
                Mesh3d(meshes.add(Capsule3d::new(3.8, 16.0))),
                MeshMaterial3d(body),
                Transform::from_translation(b(a.pos) + Vec3::Y * 17.0),
                if a.disp { Visibility::Inherited } else { Visibility::Hidden },
                ScriptActorMesh { slot, generation: a.generation },
                DespawnOnExit(Scene::Field),
            ))
            .with_children(|c| {
                c.spawn((Mesh3d(meshes.add(Cuboid::new(3.0, 3.0, 8.0))), MeshMaterial3d(nose), Transform::from_xyz(0.0, 6.0, -7.0)));
            });
    }
}

fn sync_render(
    rt: Option<Res<FieldRuntime>>,
    mut cam: Query<(&mut Transform, &mut Projection), (With<FieldCamera3d>, Without<FieldPlayerMesh>)>,
    mut player: Query<(&mut Transform, &mut Visibility), (With<FieldPlayerMesh>, Without<FieldCamera3d>)>,
) {
    let Some(rt) = rt else { return };
    if let Ok((mut t, mut vis)) = player.single_mut() {
        let p = rt.sim.player.pos;
        let bob = if rt.sim.player.moving { (rt.sim.player.anim * 2.0).sin().abs() * 1.2 } else { 0.0 };
        let dir = Vec3::new(rt.sim.player.yaw.sin(), 0.0, -rt.sim.player.yaw.cos());
        *t = Transform::from_translation(b(p) + Vec3::Y * (17.0 + bob)).looking_to(dir, Vec3::Y);
        // a script that loaded the control slot and has not displayed it yet (or cleared it) hides the player
        let shown = rt.st.actors.get(rt.st.actors.ctrl as i32).map(|a| a.disp).unwrap_or(true);
        *vis = if shown { Visibility::Inherited } else { Visibility::Hidden };
    }
    if let (Ok((mut t, mut proj)), Some(pose)) = (cam.single_mut(), rt.sim.pose) {
        let pos = b([pose.pos[0], pose.pos[1], pose.pos[2]]);
        let tgt = b([pose.target[0], pose.target[1], pose.target[2]]);
        if (tgt - pos).length_squared() > 1e-4 {
            *t = Transform::from_translation(pos).looking_at(tgt, Vec3::Y);
        }
        if let Projection::Perspective(p) = &mut *proj {
            // SetViewMatrix(320/fov, ...): focal length in pixels of the 512x448 frame
            p.fov = 2.0 * (224.0 / pose.focal.max(1.0)).atan();
        }
    }
}

/// Debug overlay (F3): event boxes, floor under the player, save / warp points.
fn debug_gizmos(rt: Option<Res<FieldRuntime>>, mut gizmos: Gizmos) {
    let Some(rt) = rt else { return };
    if !rt.debug {
        return;
    }
    // save points (green ring) and warp points (violet ring); debug overlay only (they used to be drawn always: the green line over the
    // retail cyan save point ring, round 6 GPA)
    for sp in rt.st.save_points.iter().flatten().filter(|p| p.shown) {
        let c = b(sp.pos);
        gizmos.circle(Isometry3d::new(c + Vec3::Y * 1.0, Quat::from_rotation_x(std::f32::consts::FRAC_PI_2)), 7.0, Color::srgb(0.3, 1.0, 0.5));
    }
    for wp in rt.st.warp_points.iter().flatten().filter(|p| p.shown) {
        let c = b(wp.pos);
        gizmos.circle(Isometry3d::new(c + Vec3::Y * 1.0, Quat::from_rotation_x(std::f32::consts::FRAC_PI_2)), 7.0, Color::srgb(0.8, 0.4, 1.0));
    }
    if let Some(ev) = &rt.sim.field.event_boxes {
        for (i, bx) in ev.boxes.iter().enumerate() {
            let col = if i as i32 == rt.sim.cur_box { Color::srgb(1.0, 0.3, 0.3) } else if bx.kind != 0 { Color::srgb(0.3, 0.9, 1.0) } else { Color::srgb(0.3, 1.0, 0.3) };
            let h = bx.corners[0][1];
            let ang = -(bx.rot_a + bx.rot_b);
            let pts: Vec<[f32; 3]> = bx
                .corners
                .iter()
                .map(|c| {
                    let r = crate::compat::rot_y(-ang, [c[0], 0.0, c[2]]);
                    [bx.center[0] + r[0], bx.center[1], bx.center[2] + r[2]]
                })
                .collect();
            for k in 0..4 {
                let a = pts[k];
                let n = pts[(k + 1) % 4];
                gizmos.line(b([a[0], a[1] - h, a[2]]), b([n[0], n[1] - h, n[2]]), col);
                gizmos.line(b([a[0], a[1] + h, a[2]]), b([n[0], n[1] + h, n[2]]), col);
                gizmos.line(b([a[0], a[1] - h, a[2]]), b([a[0], a[1] + h, a[2]]), col);
            }
        }
    }
}

fn show_map_root(req: Res<FieldRequest>, mut roots: Query<&mut Visibility, With<crate::bevy::FieldMapRoot>>) {
    if req.map == crate::worldmap::WORLDMAP_NAME {
        return;
    }
    for mut v in &mut roots {
        *v = Visibility::Inherited;
    }
}

fn hide_map_root(mut roots: Query<&mut Visibility, With<crate::bevy::FieldMapRoot>>) {
    for mut v in &mut roots {
        *v = Visibility::Hidden;
    }
}

pub struct FieldPlugin;

impl Plugin for FieldPlugin {
    fn build(&self, app: &mut App) {
        let rendering = app.is_plugin_added::<::bevy::pbr::PbrPlugin>();
        app.add_plugins((MenuOverlayPlugin, crate::worldmap_plugin::WorldMapPlugin, crate::fscreen::FieldScreensPlugin, crate::points::PointsPlugin))
            .init_resource::<FieldAudioQueue>()
            .init_resource::<FieldCarry>()
            .init_resource::<crate::worldmap::WorldMapRequest>()
            .add_systems(Startup, load_field_data)
            .add_systems(OnEnter(Scene::Field), enter_field)
            .add_systems(OnExit(Scene::Field), exit_field)
            .add_systems(
                FixedUpdate,
                (
                    field_script_tick.in_set(GameSet::Script),
                    crate::party::apply_party_ops_system.in_set(GameSet::Script).after(field_script_tick),
                    forward_field_vibration.in_set(GameSet::Script).after(field_script_tick),
                    field_logic_tick.in_set(GameSet::Logic),
                    field_camera_tick.in_set(GameSet::Camera),
                )
                    .run_if(in_state(Scene::Field)),
            );
        if rendering {
            if !app.is_plugin_added::<crate::bevy::FieldMapPlugin>() {
                app.add_plugins(crate::bevy::FieldMapPlugin);
            }
            if app.world().get_resource::<sh2_gfx::bevy::Sh2Disc>().is_none() {
                let root = disc_root(app.world().get_resource::<AppConfig>());
                match sh2_gfx::bevy::Sh2Disc::open(&root) {
                    Ok(d) => {
                        app.insert_resource(d);
                    }
                    Err(e) => log::warn!("field: renderer disc {}: {e}", root.display()),
                }
            }
            // LSD cut scenes (`MCES`): `cutscene_plugin` bridges `FieldRuntime::st.mces` itself (notes/integration/cutscenes.md)
            if !app.is_plugin_added::<crate::cutscene_plugin::CutscenePlugin>() {
                app.add_plugins(crate::cutscene_plugin::CutscenePlugin);
            }
            // FX X2: field effect programs (`StartEffect`)
            if !app.is_plugin_added::<sh2_gfx::effects::runner::FxRunnerPlugin>() {
                app.add_plugins(sh2_gfx::effects::runner::FxRunnerPlugin);
            }
            app.add_systems(Update, drive_field_effects.run_if(in_state(Scene::Field))).add_systems(OnExit(Scene::Field), clear_field_effects);
            // the radar in the top-left corner (`CNaviMap`)
            if !app.is_plugin_added::<crate::navimap_plugin::NaviMapPlugin>() {
                app.add_plugins(crate::navimap_plugin::NaviMapPlugin);
            }
            // round 6 RG: the field Judgement Ring screen (`RingControl` waits for it; headless runs answer at once)
            if !app.is_plugin_added::<crate::field_ring::FieldRingPlugin>() {
                app.add_plugins(crate::field_ring::FieldRingPlugin);
            }
            app.add_systems(OnEnter(Scene::Field), (spawn_scene.after(enter_field), show_map_root))
                .add_systems(OnExit(Scene::Field), hide_map_root)
                .add_systems(Update, (sync_render, sync_actor_meshes, debug_gizmos, debug_cameras).run_if(in_state(Scene::Field)))
                .add_systems(FixedUpdate, bridge_actors.after(field_logic_tick).run_if(in_state(Scene::Field)));
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::pkb_compat::PkbSet;

    fn run(rt: &mut FieldRuntime, session: &mut GameSession, n: usize) {
        for _ in 0..n {
            tick_state(&mut rt.st, &mut rt.sim);
            pump_events(rt);
            rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(session) });
        }
    }

    #[test]
    fn first_map_script_runs_and_jumps_to_ap_02() {
        let Some(pkb) = PkbSet::from_env() else { return };
        let mut session = GameSession::default();
        let mut rt = build_runtime(&pkb, None, "AP_00_U", 0, &session).unwrap();
        for _ in 0..200 {
            tick_state(&mut rt.st, &mut rt.sim);
            let idle = rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(&mut session) });
            if idle || rt.st.pending_jump.is_some() {
                break;
            }
        }
        let (map, entry) = rt.st.pending_jump.clone().expect("start function jumps");
        assert_eq!((map.as_str(), entry), ("AP_02_U", 0));
        assert!(rt.st.calls > 20);
    }

    #[test]
    fn event_box_fires_script_event() {
        let Some(pkb) = PkbSet::from_env() else { return };
        let mut session = GameSession::default();
        let mut rt = build_runtime(&pkb, None, "AP_02_U", 0, &session).unwrap();
        run(&mut rt, &mut session, 50);
        let before = rt.st.calls;
        let ids: Vec<i32> = rt.sim.field.event_boxes.as_ref().unwrap().boxes.iter().map(|b| b.id).collect();
        assert!(!ids.is_empty());
        assert!(rt.vm.call_event(ids[0] as u32, &[1]));
        run(&mut rt, &mut session, 100);
        assert!(rt.st.calls >= before);
    }

    /// The script ops that open the field screens: run every event of a map and collect the `SpecialMenu` requests they raise.
    fn menu_requests_of(pkb: &PkbSet, map: &str) -> Vec<MenuReq> {
        let mut found: Vec<MenuReq> = vec![];
        for id in 0..60u32 {
            // the player answers the shop's questions: variant 0 always takes the first choice, the others move the cursor down now and then
            for (variant, arg) in [(0usize, 1u32), (1, 1), (2, 1), (3, 1), (4, 1), (0, 4), (0, 2)] {
                let mut session = GameSession::default();
                let Some(mut rt) = build_runtime(pkb, None, map, 0, &session) else { return found };
                run(&mut rt, &mut session, 20);
                // a shopkeeper's event introduces himself on the first visit (flag set) and opens the counter on the next ones: run it twice
                for _visit in 0..2 {
                    rt.st.menu_req = None;
                    rt.st.menu_wait = false;
                    if !rt.vm.call_event(id, &[arg]) {
                        break;
                    }
                    rt.st.event_running = true;
                    for f in 0..1200usize {
                        // variant v: v cursor-down presses, then circle, every 16 frames (message pages ignore the downs; a selection takes choice v)
                        let ph = f % 16;
                        rt.st.press = if ph == 12 {
                            padbit::CIRCLE
                        } else if ph % 2 == 0 && ph / 2 < variant {
                            padbit::DOWN
                        } else {
                            0
                        };
                        run(&mut rt, &mut session, 1);
                        if let Some(r) = rt.st.menu_req.take() {
                            if !found.contains(&r) {
                                eprintln!("{map}: event {id} (visit {_visit}, answer variant {variant}, arg {arg}) requests {r:?}");
                                found.push(r);
                            }
                            rt.st.menu_wait = false;
                            break;
                        }
                    }
                    run(&mut rt, &mut session, 60);
                }
            }
        }
        found
    }

    #[test]
    fn script_events_open_the_shop_and_the_tailor() {
        let Some(pkb) = PkbSet::from_env() else { return };
        if sh2_core::boot::is_retail() {
            return;
        }
        // JP demo: `AR_01_U` sells (shop 1), `PA_03_U` has the tailor (`SpecialMenu(0x300)`) and shop 2
        let ar = menu_requests_of(&pkb, "AR_01_U");
        assert!(ar.contains(&MenuReq::Shop { id: 1 }), "AR_01_U requests {ar:?}");
        let pa = menu_requests_of(&pkb, "PA_03_U");
        assert!(pa.contains(&MenuReq::Tailor), "PA_03_U requests {pa:?}");
    }

    /// Retail build (US disc): `FI_01_U` (shop 4 and the tailor) and `CA_02_U` (shop 5 and the tailor).  `#[ignore]`: it flips the process-wide active
    /// region, run it alone: `cargo test -p sh2_field us_script_events -- --ignored`.
    #[test]
    #[ignore]
    fn us_script_events_open_the_shop_and_the_tailor() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
        let Ok(pkb) = PkbSet::open(dir) else { return };
        let ca = menu_requests_of(&pkb, "CA_02_U");
        assert!(ca.contains(&MenuReq::Shop { id: 5 }), "CA_02_U requests {ca:?}");
    }

    /// Retail `GI_00_U`: the town's NPC threads walk their `PathMove` routes (the rounded corners must not make a walker circle a node).  `#[ignore]`: flips the
    /// process-wide active region.
    #[test]
    #[ignore]
    fn us_npcs_walk_their_routes() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
        let Ok(pkb) = PkbSet::open(dir) else { return };
        let mut session = GameSession::default();
        let mut rt = build_runtime(&pkb, None, "GI_00_U", 0, &session).unwrap();
        run(&mut rt, &mut session, 200);
        let before: Vec<(usize, [f32; 3])> = rt.st.actors.slots.iter().enumerate().filter_map(|(i, a)| a.as_ref().filter(|a| a.loaded && a.mv.is_some()).map(|a| (i, a.pos))).collect();
        assert!(before.len() >= 4, "walkers: {before:?}");
        run(&mut rt, &mut session, 1000);
        let mut still = vec![];
        for (i, p0) in &before {
            let a = rt.st.actors.slots[*i].as_ref().unwrap();
            let d = ((a.pos[0] - p0[0]).powi(2) + (a.pos[2] - p0[2]).powi(2)).sqrt();
            if a.moved_dist < 150.0 {
                still.push((*i, d, a.moved_dist));
            }
        }
        assert!(still.is_empty(), "NPCs that did not walk their route: {still:?}");
    }
}

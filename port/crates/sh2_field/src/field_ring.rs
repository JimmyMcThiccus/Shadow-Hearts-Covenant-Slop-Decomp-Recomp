//! Round 6 RG: the field Judgement Ring (`SetRing` op 0x63 / `RingControl` op 0x64), ported from the retail field code.
//!
//! Retail (US `FIELD.BIN`, load base 0x45ea80; the JP demo `CField::SetRing / RingControl / cbRing / UpdateRing / RingResult` at
//! 0x004b0ce0.. are the same code, `CField+0x5b0` there, `+0x8a8` in retail):
//!
//! * `SetRing(kind, lap ms, arg, x, y, spec)` (US 0x004fad40) clears the 0x3c byte ring block, keeps `kind & 7`, the lap time, `arg`
//!   and parses `spec` ([`parse_spec`]): case-insensitive letters, blanks skipped, `C<n>` sets the colour of the area being built
//!   (default 1, reset to 1 after each area), `S<n>` its start, `E<n>` its end (both `& 0x1ff`; width = end - start + 1).  Then the
//!   ring object state goes to 2 ("create").
//! * `UpdateRing` (US 0x004fafc0, every frame): creates the `JRing(0, 0xd)` once, waits for `JRING.BIN`
//!   (`AutoLoadEndCheck`), then `SetEventRing(kind, false, kind == 1 ? arg : 1)`, `SetCallBack(cbRing, this, 0x280)`,
//!   `SetRingPos(341.33, 224)` and one `AddEventRingArea(start, width, colour)` per area.
//! * `RingControl(1)` (US 0x004fb3e0) starts the control sequence (`CField+0x8aa`), stepped by `UpdateRing` (jump table US 0x00610a00):
//!   1. `CApp::SetNoDraw(1)`, `CField::Clr` (the field stops drawing)  -> 2
//!   2. a `CScrCapture` of the current frame on OT layer 10 (the frozen field picture behind the ring) -> 3
//!   3. `SetNoDraw(0)`, `Gsx::SetFFMode(0,1,1)`, `SetFader(0, 7, 300)` (fader slot 0 mode 7: to **half** black in 300 ms),
//!      `SetRotSpeed(lap ms * 0.001, -0.15, 1)`, `SetEventRingAbnormal(arg)` unless kind 1, `RingActive()` -> 5
//!   5. wait for the result (`cbRing` event 0x80 stores `*(int*)arg` = the ring's `+0x588` event value at `+0x8b0` and sets flag bit 3);
//!      timer `CField+0x9fc` = 0 -> 6
//!   6. after 1000 ms: delete the capture, `CField::Dsp`, `SetFader(0, 6, 300)` (back from half black) -> 7
//!   7. when the fader is done: `SetFFMode(0,1,2)`, control = 0.
//! * `RingResult` returns the stored word once control is 0 and the flag is set, -1 before; the op keeps the script waiting until then.
//!
//! What the result means depends on the kind (`JRing::SetEventRing` / `MakeResult`, see `sh2_gfx::effects::jring`):
//! kind 2 = the spin ("slot") ring: a press decelerates the pointer, the result is the **colour code** of the area it stops in (0 = none);
//! kind 0 / 3 = the lap rings (every area must be hit in order, one lap): the result is the **number of areas hit**;
//! kind 1 = `arg` laps: the result is the number of **laps** cleared.  The field ring uses no ring customisation, no ring item and no
//! status (`UpdateRing` never calls `CustomConvert` / `SetJRingStatus`): it is the plain `JRing`.
//!
//! Port: [`FieldRingRun`] is the whole sequence (pure logic, 60 Hz ticks), [`FieldRingPlugin`] runs it while the host's
//! `RingControl` waits (`ScriptState::ring_wait`, answered through `ScriptState::ring_answer`), drawing with the battle crate's ring
//! renderer (`sh2_battle::hud_hits::{draw_ring, HitFx::ring_mes}`, the real `COMMON/JRING.BIN` art).  Without the plugin (the
//! headless story walker, tests) `ring_screen` stays off and the host answers at once ([`instant_result`]).

use bevy::prelude::*;
use sh2_core::game::{GamePad, GameSet, Scene};
use sh2_gfx::effects::jring::{self, JRing, JrEvent, XorShift};
use sh2_menu::bevy_ui::{self, layer, UiCanvas};
use sh2_menu::gfx::Rgba;

use crate::host::FieldRing;
use crate::plugin::FieldRuntime;

/// Sprite layer of the field ring (dim + ring + words); above the field screens (9), world map (10) and radar (11).
pub const RING_LAYER: u8 = layer::SPRITE_BASE + 5;

/// The ring centre every field ring uses (`SetRingPos(0x43aaaaab, 0x43600000)` after the area set-up).
pub const RING_POS: (f32, f32) = (1024.0 / 3.0, 224.0);

/// One `C<colour>S<start>E<end>` area of a `SetRing` spec.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct SpecArea {
    pub start: i16,
    pub width: i16,
    pub colour: i8,
}

/// `GetNumber(const char*&)`: decimal digits (an optional leading `-`), leaves the pointer after them.
fn get_number(b: &[u8], i: &mut usize) -> i32 {
    let neg = *i < b.len() && b[*i] == b'-';
    if neg {
        *i += 1;
    }
    let mut v = 0i32;
    while *i < b.len() && b[*i].is_ascii_digit() {
        v = v.wrapping_mul(10).wrapping_add((b[*i] - b'0') as i32);
        *i += 1;
    }
    if neg {
        -v
    } else {
        v
    }
}

/// The area list of a `SetRing` spec, exactly as `CField::SetRing` packs it (start / end 9 bits, colour 4 bits, default colour 1).
pub fn parse_spec(spec: &str) -> Vec<SpecArea> {
    let b = spec.as_bytes();
    let mut out = vec![];
    let (mut colour, mut start) = (1i32, 0i32);
    let mut i = 0;
    while i < b.len() {
        let c = b[i];
        i += 1;
        if c == b' ' || c == b'\t' {
            continue;
        }
        match c & 0xdf {
            b'E' => {
                let end = get_number(b, &mut i) & 0x1ff;
                // `AddEventRingArea(start, (end - start) + 1, colour)` (u16 arithmetic, the ring drops widths <= 0)
                let width = ((end - start + 1) as u16) as i16;
                out.push(SpecArea { start: start as i16, width, colour: (colour & 0xf) as i8 });
                colour = 1;
                start = 0;
            }
            b'S' => start = get_number(b, &mut i) & 0x1ff,
            b'C' => colour = get_number(b, &mut i),
            _ => {}
        }
    }
    out.truncate(jring::MAX_AREAS);
    out
}

/// What `RingControl` returns when nobody plays the ring (headless walker without an override, tests): a perfect run -- the first
/// area's colour for the spin ring (kind 2), every area hit for the lap rings (kinds 0 / 3), every lap for kind 1.
pub fn instant_result(r: &FieldRing) -> i32 {
    let areas = parse_spec(&r.spec);
    match r.kind & 7 {
        2 => areas.first().map(|a| a.colour as i32).unwrap_or(0),
        1 => r.arg.max(1),
        _ => areas.iter().filter(|a| a.width > 0).count() as i32,
    }
}

/// The results the story walker tries for this ring, [`instant_result`] first: the distinct area colours of the spin ring (stopping
/// outside every area, 0, is possible too but never helps), all laps / areas or none for the lap rings.
pub fn possible_results(r: &FieldRing) -> Vec<i32> {
    let areas = parse_spec(&r.spec);
    let mut v: Vec<i32> = match r.kind & 7 {
        2 => areas.iter().filter(|a| a.width > 0).map(|a| a.colour as i32).collect(),
        _ => vec![instant_result(r), 0],
    };
    let mut seen = std::collections::BTreeSet::new();
    v.retain(|x| seen.insert(*x));
    v
}

/// The control sequence of `UpdateRing` (`CField+0x8aa`).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Phase {
    /// 1..3: field frozen, capture, fade to half black (300 ms) while the ring's intro plays
    Start,
    /// 5: the ring runs until its result callback
    Run,
    /// 6: 1000 ms with the result (the ring's closing animation)
    Hold,
    /// 7: fade back (300 ms)
    FadeOut,
    Done,
}

/// One field ring from `RingControl(1)` to its result.
pub struct FieldRingRun {
    pub ring: JRing,
    rng: XorShift,
    pub phase: Phase,
    /// ms in the current phase (`CField+0x9fc` for the hold, the fader clock otherwise)
    pub ms: f32,
    pub result: Option<i32>,
    /// half-black dim alpha (0..=0x40, fader slot 0 mode 7 / 6)
    pub dim: u8,
    /// pointer trail (last 9 angles) for the renderer
    pub trail: [f32; 9],
    pub trail_i: usize,
    /// `HitMes` requests of the last ticks (drained by the renderer)
    pub mes: Vec<(Option<jring::JrArea>, i16)>,
    pub kind: i32,
    ticks: u32,
}

const TICK_MS: f32 = 1000.0 / 60.0;

impl FieldRingRun {
    /// `UpdateRing` from state 2 (create) to the end of control state 3 (`RingActive`).
    pub fn new(r: &FieldRing, seed: u64) -> Self {
        let mut rng = XorShift(seed | 1);
        let kind = r.kind & 7;
        let mut ring = JRing::new(0);
        ring.data_loaded = true;
        ring.set_ring_pos(r.x as f32, r.y as f32);
        // AutoLoadSet / AutoLoadEndCheck
        ring.update(1.0 / 60.0, 0, &mut rng);
        ring.events.clear();
        ring.set_event_ring(kind, false, if kind == 1 { r.arg } else { 1 });
        ring.set_callback_mask(0x280);
        ring.set_ring_pos(RING_POS.0, RING_POS.1);
        for a in parse_spec(&r.spec) {
            ring.add_event_ring_area(a.start, a.width, a.colour);
        }
        // control state 3
        let lap = if r.lap_ms > 0 { r.lap_ms as f32 * 0.001 } else { 1.6 };
        ring.set_rot_speed(lap, -0.15, 1.0);
        if kind != 1 {
            ring.set_event_ring_abnormal(r.arg);
        }
        ring.ring_active(&mut rng);
        ring.events.clear();
        FieldRingRun { ring, rng, phase: Phase::Start, ms: 0.0, result: None, dim: 0, trail: [0.0; 9], trail_i: 0, mes: vec![], kind, ticks: 0 }
    }

    /// One 60 Hz frame with the face buttons pressed this frame.  Returns the result once the whole sequence is over.
    pub fn tick(&mut self, face_press: u16) -> Option<i32> {
        self.ticks += 1;
        self.ms += TICK_MS;
        // the ring polls in every phase (its intro runs during the fade, its closing animation during the hold)
        let press = if matches!(self.phase, Phase::Start | Phase::Run) { face_press & jring::PAD_FACE_MASK } else { 0 };
        self.ring.update(1.0 / 60.0, press, &mut self.rng);
        for e in self.ring.events.drain(..) {
            match e {
                // `cbRing(0x80)`: the event value (`+0x588`)
                JrEvent::Callback { code: 0x80, result: Some(r) } => {
                    if self.result.is_none() {
                        self.result = Some(r.event_value.max(0));
                    }
                }
                JrEvent::HitMes { area, variant } => self.mes.push((area, variant)),
                _ => {}
            }
        }
        self.trail_i = (self.trail_i + 1) % 9;
        self.trail[self.trail_i] = self.ring.cur_angle;
        match self.phase {
            Phase::Start => {
                self.dim = ((self.ms.min(300.0) / 300.0) * 64.0) as u8;
                if self.ms >= 300.0 {
                    self.phase = Phase::Run;
                    self.ms = 0.0;
                }
                if self.result.is_some() {
                    self.phase = Phase::Hold;
                    self.ms = 0.0;
                }
            }
            Phase::Run => {
                self.dim = 64;
                if self.result.is_some() {
                    self.phase = Phase::Hold;
                    self.ms = 0.0;
                }
            }
            Phase::Hold => {
                if self.ms >= 1000.0 {
                    self.phase = Phase::FadeOut;
                    self.ms = 0.0;
                    // the capture is deleted: the ring is gone with it if its closing animation is still under way
                    if self.ring.state != jring::state::SLEEP {
                        self.ring.ring_sleep();
                        self.ring.events.clear();
                    }
                }
            }
            Phase::FadeOut => {
                self.dim = (64.0 - (self.ms.min(300.0) / 300.0) * 64.0) as u8;
                if self.ms >= 300.0 {
                    self.phase = Phase::Done;
                    self.dim = 0;
                }
            }
            Phase::Done => {}
        }
        if self.phase == Phase::Done {
            return Some(self.result.unwrap_or(0));
        }
        None
    }

    /// Play with a press whenever the pointer is inside an area of `colour` (spin ring: the first such frame; lap rings: every area)
    /// -- tests and the dev drive.  `None` never presses.
    pub fn auto_press(&self, colour: Option<i8>) -> u16 {
        let Some(c) = colour else { return 0 };
        let r = &self.ring;
        if r.state != jring::state::RUN {
            return 0;
        }
        let ang = if r.cur_angle < 0.0 { r.cur_angle + 360.0 } else { r.cur_angle };
        let inside = |a: &jring::JrArea| a.kind.is_some() && jring::easy_area_hit_check(ang, a.start, a.width);
        if self.kind == 2 {
            // the pointer decelerates over up to one more turn after the press: press only at the area's start so it stops inside
            // (the spin ring reads the press while the pointer turns freely)
            if r.sub != 1 {
                return 0;
            }
            for a in r.areas.iter().filter(|a| a.kind.is_some() && a.tag == c as i16) {
                if inside(a) {
                    return jring::PAD_CIRCLE;
                }
            }
            0
        } else {
            let set = if r.custom_in_use { &r.custom } else { &r.areas };
            let cur = r.cur_area.clamp(0, jring::MAX_AREAS as i32 - 1) as usize;
            let a = &set[cur];
            if inside(a) && (self.ticks & 1) == 0 {
                jring::PAD_CIRCLE
            } else {
                0
            }
        }
    }
}

/// Run a ring headless to its result with [`FieldRingRun::auto_press`] (tests).
pub fn simulate(r: &FieldRing, colour: Option<i8>, seed: u64) -> (i32, u32) {
    let mut run = FieldRingRun::new(r, seed);
    for t in 0..60 * 60 {
        let p = run.auto_press(colour);
        if let Some(v) = run.tick(p) {
            return (v, t);
        }
    }
    (-1, 3600)
}

// ------------------------------------------------------------------------------------------------------------------------------
// Bevy side
// ------------------------------------------------------------------------------------------------------------------------------

/// The running field ring (if any) and its `HitMes` sprites.
#[derive(Resource, Default)]
pub struct FieldRingScreen {
    pub run: Option<FieldRingRun>,
    pub hits: sh2_battle::hud_hits::HitFx,
    /// dev / tests: the colour the screen aims for instead of reading the pad (`SH2_FIELD_RING=<colour>`; 0 = never press)
    pub auto: Option<i8>,
    pub seed: u64,
    /// the results of every ring played (dev drive / tests)
    pub log: Vec<(String, i32, i32)>,
}

pub struct FieldRingPlugin;

impl Plugin for FieldRingPlugin {
    fn build(&self, app: &mut App) {
        let auto = std::env::var("SH2_FIELD_RING").ok().and_then(|s| s.trim().parse::<i8>().ok());
        app.insert_resource(FieldRingScreen { auto, seed: 0x5eed_0f1e_1d, ..Default::default() })
            .init_resource::<sh2_battle::hud_hits::HitArt>()
            .add_systems(Update, sh2_battle::hud_hits::load_hit_art.run_if(in_state(Scene::Field)))
            .add_systems(FixedUpdate, field_ring_tick.in_set(GameSet::Script).before(crate::plugin::field_script_tick).run_if(in_state(Scene::Field)))
            .add_systems(OnExit(Scene::Field), clear_ring);
        if let Some(d) = ring_dev_parse() {
            app.insert_resource(bevy::winit::WinitSettings::game());
            app.insert_resource(d);
            app.add_systems(FixedUpdate, ring_dev_driver.in_set(GameSet::Logic));
        }
    }
}

fn clear_ring(mut scr: ResMut<FieldRingScreen>, mut canvas: ResMut<UiCanvas>) {
    scr.run = None;
    scr.hits.ring_mes_clear();
    canvas.clear(RING_LAYER);
}

/// Start the ring when `RingControl` waits for it, step it with the pad, post the result, draw it.
pub fn field_ring_tick(
    pad: Res<GamePad>,
    rt: Option<ResMut<FieldRuntime>>,
    mut scr: ResMut<FieldRingScreen>,
    mut canvas: ResMut<UiCanvas>,
    art: Option<Res<sh2_battle::hud_hits::HitArt>>,
) {
    let Some(mut rt) = rt else { return };
    let scr = &mut *scr;
    // the host waits for this screen instead of answering at once
    rt.st.ring_screen = true;
    if scr.run.is_none() && rt.st.ring_wait && rt.st.ring_answer.is_none() {
        match rt.st.ring.clone() {
            Some(r) => {
                scr.seed = scr.seed.wrapping_mul(6364136223846793005).wrapping_add(rt.st.ticks as u64 | 1);
                log::info!("field ring: {} kind {} lap {} ms arg {} spec \"{}\"", rt.map, r.kind, r.lap_ms, r.arg, r.spec);
                scr.run = Some(FieldRingRun::new(&r, scr.seed));
                scr.hits.ring_mes_clear();
            }
            None => {
                // `RingControl` without a `SetRing`: retail's `RingResult` would never answer; do not hang the script
                log::warn!("field ring: {} RingControl without SetRing, answering 0", rt.map);
                rt.st.ring_answer = Some(0);
            }
        }
    }
    let Some(run) = scr.run.as_mut() else {
        return;
    };
    let press = match scr.auto {
        Some(c) => run.auto_press((c > 0).then_some(c)),
        None => pad.press(),
    };
    let done = run.tick(press);
    for (area, variant) in run.mes.drain(..) {
        scr.hits.ring_mes(&run.ring, area.as_ref(), variant);
    }
    scr.hits.tick_ring_mes(1.0 / 60.0);
    {
        let mut g = canvas.begin(RING_LAYER);
        if run.dim > 0 {
            bevy_ui::rect(&mut g, 0.0, 0.0, bevy_ui::VIRT_W, bevy_ui::VIRT_H, Rgba::new(0, 0, 0, run.dim));
        }
        if let Some(a) = art.as_deref().filter(|a| a.ring_ok()) {
            sh2_battle::hud_hits::draw_ring(&mut g, a, &run.ring, &run.trail, run.trail_i);
            scr.hits.draw_ring_mes(&mut g, a);
        }
    }
    if let Some(v) = done {
        log::info!("field ring: {} result {v}", rt.map);
        scr.log.push((rt.map.clone(), run.kind, v));
        rt.st.ring_answer = Some(v);
        scr.run = None;
        scr.hits.ring_mes_clear();
        canvas.clear(RING_LAYER);
    }
}

// ------------------------------------------------------------------------------------------------------------------------------
// dev drive: `SH2_RING_DEV=<map>:<event>[:<item kind>:<item id>]  SH2_RING_SHOTS=<dir>  [SH2_FIELD_RING=<colour>]  sh2_app --us`
// boots a new game on the map, gives the item (the lottery ticket: kind 1 id 0x26), calls the talk event, mashes Circle through
// the dialogue (choice 0) and photographs the ring: intro, run, result, hold, fade; exits after the ring.
// ------------------------------------------------------------------------------------------------------------------------------

#[derive(Resource)]
struct RingDev {
    map: String,
    event: u32,
    item: Option<(usize, usize)>,
    dir: Option<std::path::PathBuf>,
    ticks: u32,
    started: bool,
    called: bool,
    ring_at: Option<u32>,
    result_at: Option<u32>,
    done_at: Option<u32>,
    shots: Vec<(u32, String)>,
}

fn ring_dev_parse() -> Option<RingDev> {
    let v = std::env::var("SH2_RING_DEV").ok()?;
    let p: Vec<&str> = v.split(':').collect();
    let num = |s: &str| if let Some(h) = s.strip_prefix("0x") { usize::from_str_radix(h, 16).ok() } else { s.parse().ok() };
    let item = match (p.get(2).and_then(|s| num(s)), p.get(3).and_then(|s| num(s))) {
        (Some(k), Some(i)) => Some((k, i)),
        _ => None,
    };
    Some(RingDev {
        map: p.first().unwrap_or(&"RE_00_U").to_string(),
        event: p.get(1).and_then(|s| s.parse().ok()).unwrap_or(25),
        item,
        dir: std::env::var("SH2_RING_SHOTS").ok().map(std::path::PathBuf::from),
        ticks: 0,
        started: false,
        called: false,
        ring_at: None,
        result_at: None,
        done_at: None,
        shots: vec![],
    })
}

#[allow(clippy::too_many_arguments)]
fn ring_dev_driver(
    mut commands: Commands,
    mut dev: ResMut<RingDev>,
    mut session: ResMut<sh2_menu::session::GameSession>,
    db: Option<Res<sh2_battle::plugin::BattleDb>>,
    mut sys: ResMut<sh2_core::ssh_sys::SshSys>,
    mut field_req: ResMut<sh2_core::game::FieldRequest>,
    mut field: Option<ResMut<FieldRuntime>>,
    scene: Res<State<Scene>>,
    scr: Res<FieldRingScreen>,
    mut inj: ResMut<sh2_core::game::PadInjection>,
    mut exit: MessageWriter<AppExit>,
) {
    dev.ticks += 1;
    inj.raw = 0;
    let t = dev.ticks;
    if t == 40 && !dev.started {
        let Some(db) = db.as_ref() else { return };
        dev.started = true;
        session.new_game(&dev.map);
        sh2_battle::bridge::init_new_game(&db.0, &mut session);
        session.needs_party_init = false;
        if let Some((k, i)) = dev.item {
            // `InventoryChange` kind 1 = the item bag (`BTL0+0x944 + bag*0x200 + id`)
            let bag = session.save.btl.data[2] as usize * 0x200;
            let base = match k {
                1 => 0x944,
                2 => 0x9c4,
                _ => 0x944,
            };
            if let Some(b) = session.save.btl.data.get_mut(base + bag + i) {
                *b = 5;
            }
        }
        field_req.map = dev.map.clone();
        field_req.entry = 0;
        sys.set_api(sh2_core::ssh_sys::SshApi::FieldSocket);
        return;
    }
    let Some(f) = field.as_deref_mut() else { return };
    if *scene.get() != Scene::Field || f.map != dev.map {
        return;
    }
    if !dev.called {
        if f.cover.clear() && f.st.ticks > 120 && !f.st.msg_active() && !f.st.event_running {
            dev.called = true;
            log::info!("ring dev: calling map event {} (arg 1)", dev.event);
            if f.vm.call_event(dev.event, &[1]) {
                f.st.event_running = true;
            }
        }
        return;
    }
    let ringing = scr.run.is_some();
    if ringing && dev.ring_at.is_none() {
        dev.ring_at = Some(t);
        for (dt, n) in [(2, "ring_01_start"), (12, "ring_02_intro"), (40, "ring_03_run"), (70, "ring_04_run")] {
            dev.shots.push((t + dt, n.to_string()));
        }
    }
    if let Some(run) = scr.run.as_ref() {
        if run.result.is_some() && dev.result_at.is_none() {
            dev.result_at = Some(t);
            for (dt, n) in [(2, "ring_05_result"), (20, "ring_06_hold"), (55, "ring_07_hold_late"), (66, "ring_08_fade")] {
                dev.shots.push((t + dt, n.to_string()));
            }
        }
    }
    if dev.ring_at.is_some() && !ringing && dev.done_at.is_none() {
        dev.done_at = Some(t);
        log::info!("ring dev: ring over, results {:?}", scr.log);
        dev.shots.push((t + 30, "ring_09_after".to_string()));
    }
    // Circle through the dialogue (first choice) while no ring is up
    if !ringing && dev.done_at.is_none() && t % 10 == 0 {
        inj.raw = sh2_core::game::padbit::CIRCLE;
    }
    let due: Vec<String> = dev.shots.iter().filter(|(at, _)| *at == t).map(|(_, n)| n.clone()).collect();
    if let Some(dir) = dev.dir.clone() {
        for n in due {
            let _ = std::fs::create_dir_all(&dir);
            let path = dir.join(format!("{n}.png"));
            log::info!("ring dev: screenshot {}", path.display());
            commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(path));
        }
    }
    let end = dev.done_at.map(|d| t > d + 60).unwrap_or(false) || t > 60 * 120;
    if end {
        log::info!("ring dev: finished ({:?})", scr.log);
        exit.write(AppExit::Success);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn ring(kind: i32, lap: i32, arg: i32, spec: &str) -> FieldRing {
        FieldRing { kind, lap_ms: lap, arg, x: 256, y: 224, areas: spec.matches(['S', 's']).count() as i32, spec: spec.into(), colours: crate::host::ring_colours(spec) }
    }

    #[test]
    fn spec_parses_like_set_ring() {
        let a = parse_spec("C4S10E70C2S100E125 s200e230");
        assert_eq!(a, vec![SpecArea { start: 10, width: 61, colour: 4 }, SpecArea { start: 100, width: 26, colour: 2 }, SpecArea { start: 200, width: 31, colour: 1 }]);
        // the colour may follow the start; it is taken at the `E`
        assert_eq!(parse_spec("S5C3E9")[0], SpecArea { start: 5, width: 5, colour: 3 });
    }

    #[test]
    fn spin_ring_returns_the_colour_it_stops_in() {
        let r = ring(2, 1600, -1, "C4S10E70C2S100E160C3S200E260");
        for c in [4i8, 2, 3] {
            let (v, t) = simulate(&r, Some(c), 7);
            assert_eq!(v, c as i32, "aimed at colour {c}");
            assert!(t > 60 && t < 60 * 20, "takes {t} ticks");
        }
        assert_eq!(instant_result(&r), 4);
        assert_eq!(possible_results(&r), vec![4, 2, 3]);
    }

    #[test]
    fn lap_ring_counts_hits() {
        let r = ring(0, 1600, 0, "S30E70S150E190S260E300");
        let (v, _) = simulate(&r, Some(1), 3);
        assert_eq!(v, 3);
        let (miss, _) = simulate(&r, None, 3);
        assert_eq!(miss, 0);
        assert_eq!(instant_result(&r), 3);
    }

    #[test]
    fn sequence_holds_one_second_and_fades() {
        let r = ring(2, 1600, -1, "C1S0E359");
        let mut run = FieldRingRun::new(&r, 1);
        let mut phases = vec![];
        for _ in 0..3600 {
            let p = run.auto_press(Some(1));
            let done = run.tick(p);
            if phases.last() != Some(&run.phase) {
                phases.push(run.phase);
            }
            if done.is_some() {
                break;
            }
        }
        assert_eq!(phases, vec![Phase::Start, Phase::Run, Phase::Hold, Phase::FadeOut, Phase::Done]);
    }
}

#[cfg(test)]
mod live_cmp {
    use super::*;

    /// Live US (instance 4, debug map, `tools/live/fring.py`): spin ring 1800 ms; after the Circle press the pointer runs on at full speed,
    /// decelerates and stops **one full turn after the press angle** ~4.0 s later (r6_rg.md: press read at ~88 deg -> stop 88.4, result 0);
    /// control 6 (hold) 1.0 s, the ring object is gone ~0.8 s into it, control 7 fade ~0.4 s.
    /// Live US (`fring.py 1 2000 10 C1S10E110C1S130E230C1S250E350 --press -1`, the WE_01_U ring): 30 presses -> result **10** (laps);
    /// the lap period went 2.0, 1.75, 1.531, 1.34, 1.172, 1.026, 0.898, 0.785, 0.687, 0.601 (x 0.875 per lap, `SetRotSpeed`'s -0.15
    /// lap add is reset by `RingActive`); a ring left alone fails at 118.1 deg (area 0 ends at 110, + the 7.5 deg overshoot), result 0.
    #[test]
    fn lap_ring_matches_live() {
        let r = FieldRing { kind: 1, lap_ms: 2000, arg: 10, x: 10, y: 150, areas: 3, spec: "C1S10E110C1S130E230C1S250E350".into(), colours: vec![] };
        let mut run = FieldRingRun::new(&r, 9);
        let mut periods: Vec<f32> = vec![];
        let mut fail_angle = None;
        for _ in 0..60 * 60 {
            let p = run.auto_press(Some(1));
            if periods.last().map(|l| (l - run.ring.period).abs() > 1e-4).unwrap_or(true) && run.ring.state == jring::state::RUN {
                periods.push(run.ring.period);
            }
            if let Some(v) = run.tick(p) {
                assert_eq!(v, 10, "periods {periods:?}");
                break;
            }
        }
        let live = [2.0, 1.75, 1.531, 1.34, 1.172, 1.026, 0.898, 0.785, 0.687, 0.601];
        assert_eq!(periods.len(), live.len(), "{periods:?}");
        for (a, b) in periods.iter().zip(live) {
            assert!((a - b).abs() < 0.002, "{periods:?}");
        }
        let mut run = FieldRingRun::new(&r, 9);
        for _ in 0..60 * 60 {
            let st = run.ring.state;
            let a = run.ring.cur_angle;
            if let Some(v) = run.tick(0) {
                assert_eq!(v, 0);
                break;
            }
            if st == jring::state::RUN && run.ring.state == jring::state::END_MISS {
                fail_angle = Some(a);
            }
        }
        let f = fail_angle.expect("fails");
        assert!((f - 118.1).abs() < 4.0, "fail at {f}");
    }

    #[test]
    fn spin_deceleration_matches_live() {
        let r = FieldRing { kind: 2, lap_ms: 1800, arg: -1, x: 256, y: 224, areas: 7, spec: "C4S0E60C3S90E120C1S160E170C4S200E240C3S270E300C2S300E320".into(), colours: vec![] };
        let mut run = FieldRingRun::new(&r, 1);
        let mut pressed_at = None;
        let mut t_press = 0;
        let mut t_result = None;
        for t in 0..3600u32 {
            let a = run.ring.cur_angle;
            let p = if pressed_at.is_none() && run.ring.state == jring::state::RUN && run.ring.sub == 1 && (101.0..104.0).contains(&a) {
                pressed_at = Some(a);
                t_press = t;
                jring::PAD_CIRCLE
            } else {
                0
            };
            let had = run.result.is_some();
            let done = run.tick(p);
            if !had && run.result.is_some() {
                t_result = Some((t, run.ring.cur_angle));
            }
            if let Some(v) = done {
                let (tr, stop) = t_result.unwrap();
                println!("press {:?} at tick {t_press}, result {v} at tick {tr} ({:.2} s), stop {stop:.1}, done {:.2} s later", pressed_at, (tr - t_press) as f32 / 60.0, (t - tr) as f32 / 60.0);
                let dist = (stop - pressed_at.unwrap()).rem_euclid(360.0);
                assert!(dist < 3.0 || dist > 357.0, "decel distance {dist}");
                assert!(((tr - t_press) as f32 / 60.0 - 4.0).abs() < 0.3);
                assert_eq!(v, 3);
                return;
            }
        }
        panic!("no result");
    }
}

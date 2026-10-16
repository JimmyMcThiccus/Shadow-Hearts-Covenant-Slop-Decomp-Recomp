//! `--autoplay`: a scripted player that drives the real game through the pad, and takes Bevy screenshots at each stage.
//!
//! ```text
//! cargo run -p sh2_app -- --autoplay [--shots <dir>] [--timeout <seconds>] [--no-exit]
//! ```
//!
//! The autoplayer only injects PS2 pad bits (`PadInjection`, OR-ed with the keyboard in `sample_pad`), so the game logic that runs is
//! exactly the interactive one:
//!
//! * title: waits out the trial splash, presses START at "PRESS START", picks "New Game";
//! * world map: waits for the area select screen (`WORLDMAP`), shows the scroll to a second area and back, confirms the first area
//!   (`AP_00_U`, the tower of Apoina) with circle;
//! * field: `sh2_field::autopilot::Pilot` reads messages, walks to the exit trigger of `AP_02_U`, wanders in `AP_03_U` until the random
//!   encounter roll fires; opens the main menu once;
//! * battle: taps through the command menu (Attack -> shape -> target) and presses O when the Judgement Ring pointer is inside the zone;
//! * after the victory screen it returns to the field and finishes (exit code 0), or exit code 2 on timeout / game over.
//!
//! Screenshots are written as `<dir>/NN_name.png` (default `notes/integration/screens`).

use std::collections::HashSet;
use std::path::PathBuf;

use bevy::prelude::*;
use bevy::render::view::screenshot::{save_to_disk, Screenshot};

use sh2_battle::plugin::{BattleView, RingView};
use sh2_core::game::{padbit, GameSet, PadInjection, Scene};
use sh2_field::autopilot::Pilot;
use sh2_field::menu_overlay::InGameMenu;
use sh2_field::plugin::FieldRuntime;
use sh2_field::worldmap::WmState;
use sh2_field::worldmap_plugin::WorldMapRuntime;
use sh2_menu::plugin::TitleRuntime;
use sh2_menu::session::GameSession;
use sh2_menu::title;
use sh2_menu::title_retail_plugin::{RetailTitle, Screen as RtScreen};

/// story-mode log line: `log::info!`, and on stderr too when `SH2_STORY_PRINT` is set (headless tests have no logger)
macro_rules! story_log {
    ($($t:tt)*) => {{
        let m = format!($($t)*);
        if std::env::var_os("SH2_STORY_PRINT").is_some() {
            eprintln!("{m}");
        }
        log::info!("{m}");
    }};
}

pub struct AutoOpts {
    /// `--boost <level>`: set the party to this level once the game has started (retail encounters of the `_A` tower maps are tuned for a much
    /// stronger party than a new game's level 1 / 2 Karin and Nicolai)
    pub boost: Option<u8>,
    /// screenshot directory (`None` = no screenshots, headless runs)
    pub shots: Option<PathBuf>,
    pub timeout: f32,
    pub exit: bool,
    /// `--story`: keep playing the story after the first battle (explorer pilot, no menu tour, battles are fought on) until the timeout or
    /// the map named by `--until`; every map change is logged ("story: ...")
    pub story: bool,
    pub until: Option<String>,
}

pub struct AutoplayPlugin(pub Option<AutoOpts>);

impl AutoplayPlugin {
    pub fn from_args() -> Self {
        let args: Vec<String> = std::env::args().collect();
        if !args.iter().any(|a| a == "--autoplay") {
            return AutoplayPlugin(None);
        }
        let get = |k: &str| args.iter().position(|a| a == k).and_then(|i| args.get(i + 1)).cloned();
        // the scripted run cannot sit through the (real time, up to 7 minute) MCES movies: keep the placeholder waits unless the caller asked otherwise
        // (retail only: with the JP demo title `SH2_CUTSCENE=off` keeps the trial splash from ever finishing, see sh2_menu::plugin::title_tick)
        if sh2_core::boot::is_retail() && std::env::var_os("SH2_CUTSCENE").is_none() {
            std::env::set_var("SH2_CUTSCENE", "off");
        }
        AutoplayPlugin(Some(AutoOpts {
            shots: Some(get("--shots").map(PathBuf::from).unwrap_or_else(|| PathBuf::from("notes/integration/screens"))),
            timeout: get("--timeout").and_then(|s| s.parse().ok()).unwrap_or(240.0),
            exit: !args.iter().any(|a| a == "--no-exit"),
            boost: get("--boost").and_then(|s| s.parse().ok()),
            story: args.iter().any(|a| a == "--story"),
            until: get("--until"),
        }))
    }
}

#[derive(Resource)]
pub struct Autoplay {
    opts: AutoOpts,
    ticks: u64,
    taken: HashSet<String>,
    queue: Vec<String>,
    state_key: u32,
    state_ticks: u32,
    pilot: Pilot,
    scene_ticks: u32,
    last_scene: Scene,
    menu_done: bool,
    menu_scripted: bool,
    menu_ticks: u32,
    ring_zone_ticks: u32,
    /// ticks the battle command menu has been open (round 5 BP: the shot waits for the slide-in, QA12)
    battle_menu_ticks: u32,
    /// ticks since the battle's result stage began (round 6 QA2: the result window is photographed after it has come up)
    result_ticks: u32,
    tap: u32,
    battle_seen: bool,
    done_at: Option<u64>,
    exit_code: i32,
    seq: u32,
    field_after_battle: u32,
    wm_phase: u32,
    wm_wait: u32,
    wm_seen: bool,
    last_msg: String,
    last_map: String,
    last_box: i32,
    log_seen: usize,
    boosted: bool,
    /// story mode: (tick, map) of every field map entered, battles fought, the tick of the last map change
    story_trail: Vec<(u64, String)>,
    story_battles: u32,
    story_msg: String,
    story_last_op: String,
    story_wm_logged: Option<u64>,
    story_texts: HashSet<String>,
    tutorial_ticks: u32,
    story_seen: HashSet<String>,
    story_last_change: u64,
    story_last_report: u64,
}

impl Plugin for AutoplayPlugin {
    fn build(&self, app: &mut App) {
        let Some(o) = &self.0 else { return };
        if let Some(d) = &o.shots {
            let _ = std::fs::create_dir_all(d);
        }
        // the scripted run must keep ticking when the window is not frontmost
        app.insert_resource(bevy::winit::WinitSettings::game());
        app.insert_resource(Autoplay {
            opts: AutoOpts { shots: o.shots.clone(), timeout: o.timeout, exit: o.exit, boost: o.boost, story: o.story, until: o.until.clone() },
            ticks: 0,
            taken: HashSet::new(),
            queue: vec![],
            state_key: u32::MAX,
            state_ticks: 0,
            pilot: Pilot::default(),
            scene_ticks: 0,
            last_scene: Scene::Boot,
            menu_done: false,
            menu_scripted: false,
            menu_ticks: 0,
            ring_zone_ticks: 0,
            battle_menu_ticks: 0,
            result_ticks: 0,
            tap: 0,
            battle_seen: false,
            done_at: None,
            exit_code: 0,
            seq: 0,
            field_after_battle: 0,
            wm_phase: 0,
            wm_wait: 0,
            wm_seen: false,
            last_msg: String::new(),
            last_map: String::new(),
            last_box: -1,
            log_seen: 0,
            boosted: false,
            story_trail: vec![],
            story_battles: 0,
            story_msg: String::new(),
            story_last_op: String::new(),
            story_wm_logged: None,
            story_texts: HashSet::new(),
            tutorial_ticks: 0,
            story_seen: HashSet::new(),
            story_last_change: 0,
            story_last_report: 0,
        })
        .add_systems(FixedUpdate, autoplay_inject.in_set(GameSet::Input).before(sh2_core::game::sample_pad))
        .add_systems(Update, autoplay_shots);
    }
}

impl Autoplay {
    /// the scripted run has reached its end (success, game over or timeout)
    #[allow(dead_code)]
    pub fn finished(&self) -> bool {
        self.done_at.is_some()
    }
    #[allow(dead_code)]
    pub fn exit_code(&self) -> i32 {
        self.exit_code
    }
    fn shot(&mut self, name: &str) {
        if self.opts.shots.is_some() && self.taken.insert(name.to_string()) {
            self.seq += 1;
            self.queue.push(format!("gp_{:02}_{name}", self.seq));
        }
    }
    /// hold `bits` for 3 of every 10 ticks (a "tap")
    fn tap_bits(&mut self, bits: u16) -> u16 {
        self.tap += 1;
        if self.tap % 10 < 3 {
            bits
        } else {
            0
        }
    }
}

#[allow(clippy::too_many_arguments)]
fn autoplay_inject(
    mut ap: ResMut<Autoplay>,
    scene: Res<State<Scene>>,
    mut inj: ResMut<PadInjection>,
    title_rt: Option<Res<TitleRuntime>>,
    retail_title: Option<Res<RetailTitle>>,
    field_rt: Option<ResMut<FieldRuntime>>,
    wm_rt: Option<Res<WorldMapRuntime>>,
    mut menu: ResMut<InGameMenu>,
    battle: Res<BattleView>,
    ring: Res<RingView>,
    mut session: ResMut<GameSession>,
    battle_db: Option<Res<sh2_battle::plugin::BattleDb>>,
    mut exit: MessageWriter<AppExit>,
) {
    let ap = &mut *ap;
    ap.ticks += 1;
    let mut raw = 0u16;
    let sc = *scene.get();
    if ap.opts.story && ap.ticks % (60 * 120) == 0 {
        story_log!("story: [{:.0}s] heartbeat: scene {:?} field {} worldmap {} menu {}/{}", ap.ticks as f32 / 60.0, sc, field_rt.is_some(), wm_rt.is_some(), menu.open, menu.request);
    }
    if sc != ap.last_scene {
        ap.last_scene = sc;
        ap.scene_ticks = 0;
        ap.tap = 0;
    }
    ap.scene_ticks += 1;
    if let (Some(level), false, Some(db)) = (ap.opts.boost, ap.boosted, battle_db.as_deref()) {
        if sc == Scene::Field && session.in_game && !session.needs_party_init {
            let tbl = sh2_battle::bridge::level_table(&db.0);
            for pc in 0..sh2_menu::save::PC_COUNT {
                if session.save.btl.pc(pc).map(|r| r.present()).unwrap_or(false) {
                    session.save.btl.pc_level_init(pc, level, &tbl);
                }
            }
            ap.boosted = true;
            log::info!("autoplay: party boosted to level {level}");
        }
    }
    if ap.ticks as f32 / 60.0 > ap.opts.timeout && ap.done_at.is_none() {
        log::error!("autoplay: timeout in scene {sc:?}");
        ap.exit_code = 2;
        ap.done_at = Some(ap.ticks);
    }
    if let Some(at) = ap.done_at {
        if ap.ticks > at + 90 && ap.opts.exit {
            exit.write(if ap.exit_code == 0 { AppExit::Success } else { AppExit::from_code(ap.exit_code as u8) });
        }
        inj.raw = 0;
        return;
    }
    match sc {
        Scene::Boot => {}
        Scene::Title if sh2_core::boot::is_retail() => {
            // US retail title (OPENING.BIN flow): disclaimer -> (placeholder) movie -> PRESS START -> New Game
            if let Some(rt) = retail_title {
                let h = &rt.host;
                let key = h.om.state;
                if key != ap.state_key {
                    ap.state_key = key;
                    ap.state_ticks = 0;
                }
                ap.state_ticks += 1;
                match h.screen {
                    RtScreen::Disclaimer => {
                        if ap.state_ticks == 90 {
                            ap.shot("us_disclaimer");
                        }
                        if ap.state_ticks > 130 {
                            raw = ap.tap_bits(padbit::CIRCLE);
                        }
                    }
                    RtScreen::Movie => {
                        if ap.state_ticks == 20 {
                            ap.shot("us_movie_placeholder");
                        }
                        // the placeholder movie ends by itself
                    }
                    RtScreen::Title => {
                        if ap.state_ticks == 70 {
                            ap.shot("us_title_press_start");
                        }
                        if ap.state_ticks > 100 {
                            raw = ap.tap_bits(padbit::START);
                        }
                    }
                    RtScreen::Menu => {
                        if ap.state_ticks == 40 {
                            ap.shot("us_title_menu");
                        }
                        if ap.state_ticks > 70 {
                            raw = ap.tap_bits(padbit::CIRCLE);
                        }
                    }
                    _ => {}
                }
            }
        }
        Scene::Title => {
            if let Some(rt) = title_rt {
                let st = rt.om.state;
                if st != ap.state_key {
                    ap.state_key = st;
                    ap.state_ticks = 0;
                }
                ap.state_ticks += 1;
                match st {
                    title::S_TRIAL_WAIT => {
                        if ap.state_ticks == 40 {
                            ap.shot("title_trial_splash");
                        }
                        if ap.state_ticks > 80 {
                            raw = ap.tap_bits(padbit::CIRCLE);
                        }
                    }
                    title::S_TITLE_WAIT => {
                        if ap.state_ticks == 50 {
                            ap.shot("title_press_start");
                        }
                        if ap.state_ticks > 75 {
                            raw = ap.tap_bits(padbit::START);
                        }
                    }
                    title::S_MENU => {
                        if ap.state_ticks == 30 {
                            ap.shot("title_menu");
                        }
                        if ap.state_ticks > 60 {
                            raw = ap.tap_bits(padbit::CIRCLE);
                        }
                    }
                    _ => {}
                }
            }
        }
        Scene::Field => {
            if wm_rt.is_none() {
                ap.wm_seen = false;
            }
            if let Some(wm) = wm_rt {
                if !ap.wm_seen {
                    // a fresh world map screen
                    ap.wm_seen = true;
                    ap.wm_wait = 0;
                    ap.tutorial_ticks = 0;
                    ap.taken.remove(&format!("us_worldmap_world{}", wm.wm.world));
                }
                // world map: look at the first area, scroll to the next one and back, then confirm the first
                let w = &wm.wm;
                if ap.opts.story && ap.ticks % (60 * 60) == 0 {
                    story_log!(
                        "story: [{:.0}s] on the world map: world {} state {:?} sel {} scrolling {} tutorial {:?} retail {} wm_wait {} points {}",
                        ap.ticks as f32 / 60.0,
                        w.world,
                        w.state,
                        w.sel,
                        w.scrolling(),
                        w.tutorial,
                        w.retail,
                        ap.wm_wait,
                        w.maps.iter().map(|m| format!("{}:{}(st{})", m.id, m.map, m.state)).collect::<Vec<_>>().join(" ")
                    );
                }
                if let WmState::Tutorial(phase) = w.state {
                    // the first-visit tutorial window: look at it, then confirm
                    if phase == 1 {
                        ap.tutorial_ticks += 1;
                        if ap.tutorial_ticks == 90 {
                            ap.shot("us_worldmap_tutorial");
                        }
                        if ap.tutorial_ticks > 120 {
                            raw = ap.tap_bits(padbit::CIRCLE);
                        }
                    }
                } else if w.state == WmState::Select && !w.scrolling() && w.retail {
                    // retail point list: photograph it (once per world), then confirm the selected point
                    ap.wm_wait += 1;
                    if ap.wm_wait == 30 {
                        ap.shot(&format!("us_worldmap_world{}", w.world));
                        if ap.opts.story {
                            let pts: Vec<String> = w.maps.iter().map(|m| format!("{}:{}(st{})", m.id, m.map, m.state)).collect();
                            story_log!("story: world map {} sel {} points {}", w.world, w.sel, pts.join(" "));
                        }
                    }
                    if ap.wm_wait > 60 {
                        if ap.opts.story {
                            // story: go to the newest point, else one that was not visited yet, else stay on the selected one
                            let visited = &ap.pilot.mem.visited;
                            let want = w
                                .maps
                                .iter()
                                .position(|m| m.state == 2 && m.selectable)
                                .or_else(|| w.maps.iter().position(|m| m.state == 1 && m.selectable && m.portal < 0 && !visited.contains(&m.map)))
                                .or_else(|| w.maps.iter().position(|m| m.state == 1 && m.selectable && m.portal < 0))
                                .unwrap_or(w.sel);
                            if want != w.sel && ap.wm_wait % 20 == 0 {
                                // walk the list in the direction of the shorter way round
                                let n = w.maps.len();
                                raw = if (want + n - w.sel) % n <= n / 2 { padbit::DOWN } else { padbit::UP };
                            } else if want == w.sel {
                                raw = ap.tap_bits(padbit::CIRCLE);
                            }
                        } else {
                            raw = ap.tap_bits(padbit::CIRCLE);
                        }
                    }
                } else if w.state == WmState::Select && !w.scrolling() {
                    ap.wm_wait += 1;
                    match ap.wm_phase {
                        0 if ap.wm_wait == 20 => ap.shot("worldmap_select"),
                        0 if ap.wm_wait > 40 => {
                            raw = padbit::DOWN;
                            ap.wm_phase = 1;
                            ap.wm_wait = 0;
                        }
                        1 if ap.wm_wait == 30 => ap.shot("worldmap_scrolled"),
                        1 if ap.wm_wait > 50 => {
                            raw = padbit::UP;
                            ap.wm_phase = 2;
                            ap.wm_wait = 0;
                        }
                        2 if ap.wm_wait > 40 => {
                            raw = ap.tap_bits(padbit::CIRCLE);
                        }
                        _ => {}
                    }
                }
                inj.raw = raw;
                return;
            }
            let Some(mut rt) = field_rt else { return };
            let map = rt.map.clone();
            if ap.opts.story {
                if let Ok(want) = std::env::var("SH2_STORY_OPS") {
                    // op trace of one map: `SH2_STORY_OPS=DO_06_U`
                    if want == map {
                        if rt.vm.branch_trace.is_none() {
                            rt.vm.branch_trace = Some(vec![]);
                        }
                        for b in rt.vm.branch_trace.as_mut().map(std::mem::take).unwrap_or_default() {
                            story_log!("story:    branch [{map}] {b}");
                        }
                        if rt.st.log.len() < ap.log_seen {
                            ap.log_seen = 0;
                        }
                        for l in rt.st.log.iter().skip(ap.log_seen) {
                            if *l != ap.story_last_op {
                                story_log!("story:    op [{map}] {l}");
                                ap.story_last_op = l.clone();
                            }
                        }
                        ap.log_seen = rt.st.log.len();
                    } else {
                        ap.log_seen = 0;
                    }
                }
            }
            if ap.opts.story && std::env::var_os("SH2_STORY_TEXT").is_some() {
                let txt: String = rt.st.ui.windows.iter().filter(|w| w.is_open() && !w.raw.is_empty()).map(|w| String::from_utf8_lossy(&w.raw).replace('$', " / ")).collect::<Vec<_>>().join(" | ");
                if txt != ap.story_msg {
                    if !txt.is_empty() && ap.story_texts.insert(format!("{map} {txt}")) {
                        story_log!("story:    [{map}] text: {txt}");
                    }
                    ap.story_msg = txt;
                }
            }
            if ap.opts.story && rt.st.world_map_jump.is_some() && ap.story_wm_logged != Some(ap.ticks / 600) {
                ap.story_wm_logged = Some(ap.ticks / 600);
                let wf: Vec<String> = rt.st.world_flags.iter().map(|(i, s)| format!("{i}:{s}")).collect();
                story_log!("story: [{:.0}s] [{map}] WorldMapJump{:?}; SetWorldMapPoint calls so far {}", ap.ticks as f32 / 60.0, rt.st.world_map_jump, wf.join(" "));
                let tail: Vec<&String> = rt.st.log.iter().rev().take(40).collect();
                story_log!("story:    last ops (newest first) {:?}", tail);
            }
            if ap.opts.story {
                ap.pilot.explore = true;
                ap.pilot.trace = std::env::var("SH2_STORY_PRINT").as_deref() == Ok("2");
                if ap.story_trail.last().map(|(_, m)| m != &map).unwrap_or(true) {
                    let nz: Vec<String> = rt.vm.mem.regs.iter().enumerate().filter(|(_, v)| **v != 0).map(|(i, v)| format!("{i:#x}={v:#x}")).collect();
                    // repeated visits with unchanged registers (door ping-pong) are summarised, not printed
                    let sig = format!("{map} {}", nz.join(" "));
                    if ap.story_seen.insert(sig) {
                        story_log!("story: [{:.0}s] -> {map} (battles {}, warps {}) regs {}", ap.ticks as f32 / 60.0, session.battles_won, ap.pilot.mem.warps, nz.join(" "));
                    }
                    if std::env::var("SH2_STORY_PRINT").as_deref() == Ok("2") {
                        let has = |id: u32| rt.vm.image.as_ref().map(|i| i.find_event(0, id).is_some()).unwrap_or(false);
                        let bx: Vec<String> = rt.sim.field.event_boxes.as_ref().map(|e| e.boxes.iter().map(|b| format!("#{}k{}f{:x}{}@({:.0},{:.0},{:.0})", b.id, b.kind, b.flags & 0xf, if has(b.id as u32) { "" } else { "!" }, b.center[0], b.center[1], b.center[2])).collect()).unwrap_or_default();
                        let ac: Vec<String> = rt.st.actors.slots.iter().enumerate().filter_map(|(i, a)| a.as_ref().filter(|a| a.loaded && a.event_id != 0).map(|a| format!("s{i}ev{}{}@({:.0},{:.0})", a.event_id, if a.disp { "" } else { "(hidden)" }, a.pos[0], a.pos[2]))).collect();
                        story_log!("story:    boxes {} actors {} enc {}", bx.join(" "), ac.join(" "), rt.sim.enc.rate);
                    }
                    ap.story_trail.push((ap.ticks, map.clone()));
                    ap.story_last_change = ap.ticks;
                    ap.story_last_report = ap.ticks;
                    if ap.opts.until.as_deref() == Some(map.as_str()) {
                        story_log!("story: reached {map}: done");
                        ap.done_at = Some(ap.ticks);
                    }
                } else if ap.ticks - ap.story_last_report >= 60 * 90 {
                    ap.story_last_report = ap.ticks;
                    story_log!(
                        "story: [{:.0}s] still in {map} since {:.0}s: pos {:?} msg {} ev {} vm {} box {} phase {:?} boxes {} ctrl manual {:?} cover {:.2} mces {} menu_wait {} menu {}/{} sel {} windows {} pilot [{}] tries {:?}",
                        ap.ticks as f32 / 60.0,
                        ap.story_last_change as f32 / 60.0,
                        rt.sim.player.pos,
                        rt.st.msg_active(),
                        rt.st.event_running,
                        rt.vm.is_running(),
                        rt.sim.cur_box,
                        rt.phase,
                        rt.sim.field.event_boxes.as_ref().map(|e| e.boxes.len()).unwrap_or(0),
                        rt.st.actors.get(rt.st.actors.ctrl as i32).map(|a| a.manual),
                        rt.cover.alpha,
                        rt.st.mces.state,
                        rt.st.menu_wait,
                        menu.open,
                        menu.request,
                        rt.st.ui.select.active,
                        rt.st.ui.windows.iter().enumerate().filter(|(_, w)| w.created).map(|(i, w)| format!("[{i}: {:?} msg {} typed {} key {}]", w.phase, w.msg.is_some(), w.typed(), w.key_pending)).collect::<String>(),
                        ap.pilot.debug(),
                        ap.pilot.mem.tries.iter().filter(|((m, _), _)| *m == map).map(|((_, k), n)| (*k, *n)).collect::<Vec<_>>()
                    );
                }
            }
            if ap.ticks % 300 == 0 && std::env::var_os("SH2_AUTOPLAY_DEBUG").is_some() {
                let tail: Vec<&String> = rt.st.log.iter().rev().take(3).collect();
                let acts: Vec<String> = (0..3)
                    .filter_map(|i| rt.st.actors.get(i))
                    .map(|a| format!("[{} {:?} done {} mot {} left {} loop {} mv {} disp {}]", a.char_id, a.cmd, a.cmd_done, a.motion, a.motion_left, a.motion_loop, a.mv.is_some(), a.disp))
                    .collect();
                log::info!("autoplay actors: {}", acts.join(" "));
                log::info!(
                    "autoplay[{}]: map {} pos {:?} msg {} ev {} vm {} cur_box {} walked {:.0} menu {} menu_done {} last {tail:?}",
                    ap.scene_ticks, rt.map, rt.sim.player.pos, rt.st.msg_active(), rt.st.event_running, rt.vm.is_running(), rt.sim.cur_box, rt.sim.walked, menu.open, ap.menu_done
                );
            }
            if std::env::var_os("SH2_AUTOPLAY_DEBUG").is_some() {
                let txt: String = rt.st.ui.windows.iter().filter(|w| w.is_open() && !w.raw.is_empty()).map(|w| String::from_utf8_lossy(&w.raw).replace('$', " / ")).collect::<Vec<_>>().join(" | ");
                if txt != ap.last_msg && !txt.is_empty() {
                    log::info!("autoplay: [{}] text: {}", rt.map, txt);
                }
                ap.last_msg = txt;
                if std::env::var("SH2_AUTOPLAY_DEBUG").as_deref() == Ok("2") {
                    if rt.st.log.len() < ap.log_seen {
                        ap.log_seen = 0;
                    }
                    for l in rt.st.log.iter().skip(ap.log_seen) {
                        log::info!("autoplay: op {l}");
                    }
                    ap.log_seen = rt.st.log.len();
                }
                if rt.sim.cur_box != ap.last_box {
                    ap.last_box = rt.sim.cur_box;
                    let ev = rt.sim.field.event_boxes.as_ref().map(|e| e.event_num(rt.sim.cur_box)).unwrap_or(-1);
                    log::info!("autoplay: [{}] box {} (event {}) pos {:?} ev_running {}", rt.map, rt.sim.cur_box, ev, rt.sim.player.pos, rt.st.event_running);
                }
                if ap.last_map != rt.map {
                    log::info!("autoplay: map -> {}", rt.map);
                    let nz: Vec<String> = rt.vm.mem.regs.iter().enumerate().filter(|(_, v)| **v != 0).map(|(i, v)| format!("{i:#x}={v:#x}")).collect();
                    log::info!("autoplay: script registers on entry: {}", nz.join(" "));
                    ap.last_map = rt.map.clone();
                }
            }
            // screenshots
            // only photograph the field when no fader hides it
            let visible = rt.cover.clear() && rt.faders.iter().all(|f| f.alpha < 0x10);
            if ap.scene_ticks >= 150 && visible && !ap.battle_seen {
                ap.shot(&format!("field_{}", map.to_lowercase()));
            }
            if rt.st.msg_active() && ap.scene_ticks > 60 && visible && rt.st.ui.windows.iter().any(|w| w.is_open() && w.typed() && w.msg.is_some()) {
                ap.shot("field_message");
            }
            if rt.sim.walked > 120.0 && !ap.battle_seen && !rt.st.msg_active() && visible {
                ap.shot(&format!("field_walk_{}", map.to_lowercase()));
            }
            // returned from the battle: one more shot, then finish
            if ap.battle_seen && session.battles_won > 0 && !ap.opts.story {
                ap.field_after_battle += 1;
                if ap.field_after_battle == 150 {
                    ap.shot(&format!("field_after_battle_{}", map.to_lowercase()));
                }
                if ap.field_after_battle == 200 {
                    log::info!("autoplay: battle won and back in the field: done");
                    ap.done_at = Some(ap.ticks);
                }
                inj.raw = 0;
                return;
            }
            // open the main menu once while idle in the first walkable map, tour the pages (scripted keys inside the menu), close it
            if !ap.menu_done && !ap.opts.story && ap.scene_ticks > 360 && !rt.st.msg_active() && map == "AP_02_U" {
                if menu.open {
                    ap.menu_ticks += 1;
                    if !ap.menu_scripted {
                        ap.menu_scripted = true;
                        // the story unlocks the command entries one by one; the tour wants all of them
                        for i in 0..24 {
                            session.save.menu.data[sh2_field::cmd_top::OFF_ENTRY_FLAGS + i] = 2;
                        }
                        if let Some(d) = ap.opts.shots.clone() {
                            menu.script = sh2_field::menu_overlay::MenuScript::new(sh2_field::cmd_pages::autoplay_tour(), Some(d.join("menu")));
                        }
                    }
                    // headless runs (no screenshots, no script) just look at the menu for a second; a stuck script is cancelled out
                    if (ap.opts.shots.is_none() && ap.menu_ticks > 60) || ap.menu_ticks > 6000 {
                        raw = ap.tap_bits(padbit::CROSS);
                    }
                } else if ap.menu_ticks > 0 {
                    ap.menu_done = true;
                } else {
                    raw = ap.tap_bits(padbit::TRIANGLE);
                }
                inj.raw = raw;
                return;
            }
            if ap.opts.story && (menu.open || menu.request) {
                // a menu / save screen opened by the script (or by us): back out of it (cancel = cross on the US disc)
                ap.menu_ticks += 1;
                if ap.menu_ticks % (60 * 90) == 1 {
                    story_log!(
                        "story: [{:.0}s] [{map}] menu open {} request {} (script menu_wait {} req {:?}), {} ticks in it",
                        ap.ticks as f32 / 60.0,
                        menu.open,
                        menu.request,
                        rt.st.menu_wait,
                        rt.st.menu_req,
                        ap.menu_ticks
                    );
                }
                raw = ap.tap_bits(padbit::CROSS);
                inj.raw = raw;
                return;
            }
            ap.menu_ticks = 0;
            raw = ap.pilot.step(&mut rt);
        }
        Scene::Battle => {
            ap.battle_seen = true;
            if ap.opts.story && ap.scene_ticks > 0 && ap.scene_ticks % (60 * 60) == 0 {
                story_log!(
                    "story: [{:.0}s] battle #{} still running after {}s: stage {} menu {} result {} turn {} enemies {} party {} ring {}/{}",
                    ap.ticks as f32 / 60.0,
                    ap.story_battles,
                    ap.scene_ticks / 60,
                    battle.stage,
                    battle.menu_open,
                    battle.result_shown,
                    battle.turn,
                    battle.enemies_alive,
                    battle.party_alive,
                    ring.active,
                    ring.in_zone
                );
            }
            if ap.scene_ticks == 1 && ap.opts.story {
                ap.story_battles += 1;
                story_log!("story: [{:.0}s] battle #{} (return {:?})", ap.ticks as f32 / 60.0, ap.story_battles, session.chr_pos);
            }
            // the command rows slide in from the left and their labels appear when they have arrived (`BtlMenu`, live 07j / 07k):
            // photograph the menu once it has settled, and with screenshots on, leave it open that long
            ap.battle_menu_ticks = if battle.stage == "running" && battle.menu_open { ap.battle_menu_ticks + 1 } else { 0 };
            let menu_settled = ap.opts.shots.is_none() || ap.battle_menu_ticks > 50;
            if battle.stage == "running" && battle.menu_open && ap.scene_ticks > 60 && ap.battle_menu_ticks == 45 {
                ap.shot("battle_command_menu");
            }
            if ring.active {
                ap.ring_zone_ticks = if ring.in_zone { ap.ring_zone_ticks + 1 } else { 0 };
                if ring.in_zone && ap.ring_zone_ticks == 9 {
                    raw = padbit::CIRCLE;
                    ap.shot("battle_judgement_ring");
                }
            } else {
                ap.ring_zone_ticks = 0;
                ap.result_ticks = if battle.result_shown { ap.result_ticks + 1 } else { 0 };
                if battle.result_shown {
                    // win pose first, then the result window: with screenshots on, wait for both before confirming
                    if ap.result_ticks == 2 {
                        ap.shot("battle_victory");
                    }
                    if ap.result_ticks == 150 {
                        ap.shot("battle_result");
                    }
                    if ap.result_ticks == 330 {
                        ap.shot("battle_result_2");
                    }
                    if ap.opts.shots.is_none() || ap.result_ticks > 340 {
                        raw = ap.tap_bits(padbit::CIRCLE);
                    }
                } else if battle.menu_open && battle.stage == "running" && menu_settled {
                    raw = ap.tap_bits(padbit::CIRCLE);
                } else if battle.stage == "defeat" {
                    raw = ap.tap_bits(padbit::CIRCLE);
                }
            }
        }
        Scene::GameOver => {
            ap.shot("game_over");
            story_log!("story: [{:.0}s] GAME OVER (last map {}, battles won {})", ap.ticks as f32 / 60.0, ap.story_trail.last().map(|(_, m)| m.as_str()).unwrap_or("?"), session.battles_won);
            log::warn!("autoplay: game over");
            ap.exit_code = 2;
            ap.done_at = Some(ap.ticks);
        }
    }
    inj.raw = raw;
}

fn autoplay_shots(mut commands: Commands, ap: Option<ResMut<Autoplay>>) {
    let Some(mut ap) = ap else { return };
    let Some(dir) = ap.opts.shots.clone() else { return };
    for name in std::mem::take(&mut ap.queue) {
        let path = dir.join(format!("{name}.png"));
        log::info!("autoplay: screenshot {}", path.display());
        commands.spawn(Screenshot::primary_window()).observe(save_to_disk(path));
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use sh2_battle::plugin::BattlePlugin;
    use sh2_field::plugin::FieldPlugin;
    use sh2_core::ssh_sys::SshSys;
    use sh2_menu::plugin::MenuPlugin;
    use bevy::state::app::StatesPlugin;
    use bevy::time::TimeUpdateStrategy;
    use std::time::Duration;

    /// The whole game loop without a GPU: MinimalPlugins + the real scene plugins, driven by the autoplayer through the pad.  Asserts the
    /// `Scene` transitions Title -> Field -> Battle -> Field (and that the battle paid out).
    #[test]
    fn headless_title_field_battle_field() {
        let _g = SERIAL.lock().unwrap_or_else(|e| e.into_inner());
        if std::env::var_os("SH2_DISC_DIR").is_none() {
            return;
        }
        let dir = std::env::temp_dir().join(format!("sh2_headless_saves_{}", std::process::id()));
        let mut app = App::new();
        app.add_plugins((MinimalPlugins, StatesPlugin, bevy::input::InputPlugin))
            // The scene plugins build meshes/images/materials even without a renderer: give them asset
            // storage (no RenderPlugin) so their systems validate in this headless run.
            .add_plugins(bevy::asset::AssetPlugin::default())
            .init_asset::<Mesh>()
            .init_asset::<Image>()
            .init_asset::<bevy::text::Font>()
            .init_asset::<ColorMaterial>()
            .init_asset::<StandardMaterial>()
            .init_asset::<sh2_gfx::bevy::material::Sh2Material>()
            // Resources the renderer plugin would normally insert; the scene systems read them unconditionally.
            .init_resource::<sh2_gfx::renderer::Sh2RenderSettings>()
            .init_resource::<sh2_gfx::bevy::material::Sh2ColorSpace>()
            .init_resource::<sh2_gfx::bevy::screen::Sh2Screen>()
            .init_resource::<sh2_menu::bevy_ui::UiViewport>()
            .init_resource::<sh2_field::actors::ActorSettings>()
            .insert_resource(TimeUpdateStrategy::ManualDuration(Duration::from_micros(16_667)))
            .insert_resource(sh2_core::app::AppConfig { screen_w: 512, screen_h: 448, disc_dir: std::env::var("SH2_DISC_DIR").unwrap().into() })
            .insert_resource(sh2_menu::plugin::SaveDevice(sh2_menu::session::FileStorage::new(&dir)))
            .init_state::<Scene>()
            .add_plugins(sh2_core::ssh_sys::SshSysPlugin)
            .add_plugins((sh2_core::game::GameCorePlugin, MenuPlugin, FieldPlugin, BattlePlugin))
            // The game app registers the actor plugin too; its character cache is read by field/battle model systems.
            .add_plugins(sh2_field::actors::ActorPlugin)
            .init_resource::<sh2_gfx::bevy::character::CharacterCache>()
            .add_plugins(AutoplayPlugin(Some(AutoOpts { shots: None, timeout: 600.0, exit: false, boost: None, story: false, until: None })))
            .add_systems(Startup, crate::init_instance)
            .add_systems(Update, (crate::system_poller, crate::scene_transition).chain());
        let mut visited: Vec<Scene> = vec![];
        for _ in 0..60 * 400 {
            app.update();
            let s = *app.world().resource::<State<Scene>>().get();
            if visited.last() != Some(&s) {
                visited.push(s);
            }
            if app.world().resource::<Autoplay>().finished() {
                break;
            }
        }
        let ap = app.world().resource::<Autoplay>();
        assert!(ap.finished(), "autoplay did not finish; scenes {visited:?}");
        assert_eq!(ap.exit_code(), 0, "scenes {visited:?}");
        let pos = |s: Scene| visited.iter().position(|x| *x == s);
        assert!(pos(Scene::Title).is_some() && pos(Scene::Field).is_some() && pos(Scene::Battle).is_some(), "{visited:?}");
        assert_eq!(visited.last(), Some(&Scene::Field), "{visited:?}");
        assert!(visited.windows(3).any(|w| w == [Scene::Field, Scene::Battle, Scene::Field]), "{visited:?}");
        assert!(app.world().resource::<GameSession>().battles_won >= 1);
        let _ = std::fs::remove_dir_all(&dir);
    }

    /// Both full-game tests flip process-wide state (`SH2_DISC_DIR`, the active region): never run them side by side.
    static SERIAL: std::sync::Mutex<()> = std::sync::Mutex::new(());

    /// Headless US retail story run (no title): `GameSession::new_game("OP_00_U")` + `FieldMapJump("OP_00_U", 0)` like the retail title's New Game,
    /// then the explorer pilot (`--story`) plays on until `until` is reached or `max_secs` of game time passed.  Returns (trail, battles won).
    fn run_us_story(until: &str, max_secs: f32, boost: Option<u8>) -> Option<(Vec<String>, u32)> {
        let us = std::env::var_os("SH2_US_DISC_DIR")?;
        let old_disc = std::env::var_os("SH2_DISC_DIR");
        std::env::set_var("SH2_DISC_DIR", &us);
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
        let dir = std::env::temp_dir().join(format!("sh2_headless_us_story_{}", std::process::id()));
        let mut app = App::new();
        app.add_plugins((MinimalPlugins, StatesPlugin, bevy::input::InputPlugin))
            .add_plugins(bevy::asset::AssetPlugin::default())
            .init_asset::<Mesh>()
            .init_asset::<Image>()
            .init_asset::<bevy::text::Font>()
            .init_asset::<ColorMaterial>()
            .init_asset::<StandardMaterial>()
            .init_asset::<sh2_gfx::bevy::material::Sh2Material>()
            .init_resource::<sh2_gfx::renderer::Sh2RenderSettings>()
            .init_resource::<sh2_gfx::bevy::material::Sh2ColorSpace>()
            .init_resource::<sh2_gfx::bevy::screen::Sh2Screen>()
            .init_resource::<sh2_menu::bevy_ui::UiViewport>()
            .init_resource::<sh2_field::actors::ActorSettings>()
            .insert_resource(TimeUpdateStrategy::ManualDuration(Duration::from_micros(16_667)))
            .insert_resource(sh2_core::app::AppConfig { screen_w: 512, screen_h: 448, disc_dir: us.clone().into() })
            .insert_resource(sh2_core::boot::ActiveBuild(sh2_core::boot::Region::Us))
            .insert_resource(sh2_menu::plugin::SaveDevice(sh2_menu::session::FileStorage::new(&dir)))
            .init_state::<Scene>()
            .add_plugins(sh2_core::ssh_sys::SshSysPlugin)
            .add_plugins((sh2_core::game::GameCorePlugin, MenuPlugin, FieldPlugin, BattlePlugin))
            .add_plugins(sh2_field::actors::ActorPlugin)
            .init_resource::<sh2_gfx::bevy::character::CharacterCache>()
            .add_plugins(AutoplayPlugin(Some(AutoOpts { shots: None, timeout: max_secs, exit: false, boost, story: true, until: Some(until.to_string()) })))
            .add_systems(
                Startup,
                |mut sys: ResMut<SshSys>, mut session: ResMut<GameSession>, mut req: ResMut<sh2_core::game::FieldRequest>| {
                    sys.retail = true;
                    session.new_game("OP_00_U");
                    *req = sh2_core::game::FieldRequest { map: "OP_00_U".into(), entry: 0 };
                    sys.set_api(sh2_core::ssh_sys::SshApi::FieldSocket);
                },
            )
            .add_systems(Update, (crate::system_poller, crate::scene_transition).chain());
        let mut finished = false;
        let mut updates = 0u32;
        // the autoplayer's own clock (fixed-step ticks) times out after `max_secs`; the update bound only guards against a stuck app
        for _ in 0..(max_secs as u32 + 5) * 60 * 3 {
            updates += 1;
            app.update();
            if app.world().resource::<Autoplay>().finished() {
                finished = true;
                break;
            }
        }
        let ap = app.world().resource::<Autoplay>();
        let trail: Vec<String> = ap.story_trail.iter().map(|(_, m)| m.clone()).collect();
        let won = app.world().resource::<GameSession>().battles_won;
        let ok = finished && ap.exit_code() == 0;
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Jp);
        match old_disc {
            Some(d) => std::env::set_var("SH2_DISC_DIR", d),
            None => std::env::remove_var("SH2_DISC_DIR"),
        }
        let _ = std::fs::remove_dir_all(&dir);
        eprintln!(
            "us story trail {trail:?}, battles won {won}, finished {ok} ({updates} updates, {} autoplay ticks, scene {:?})",
            app.world().resource::<Autoplay>().ticks,
            app.world().resource::<State<Scene>>().get()
        );
        Some((trail, if ok { won } else { u32::MAX }))
    }

    /// The first scripted stretch of the US retail game, played by the explorer: opening scripts, world map, `AP_00_U` cut scene, `AP_02_U`,
    /// the scripted fight (stage 77, monster set 4), `AP_10_U`, `AP_03_U` (measured live, pine_us_refinement.md section 7).
    #[test]
    fn headless_us_story_reaches_ap_03_u() {
        let _g = SERIAL.lock().unwrap_or_else(|e| e.into_inner());
        let Some((trail, won)) = run_us_story("AP_03_U", 900.0, Some(30)) else { return };
        assert_ne!(won, u32::MAX, "did not reach AP_03_U: {trail:?}");
        for m in ["OP_00_U", "AP_00_U", "AP_02_U", "AP_10_U", "AP_03_U"] {
            assert!(trail.iter().any(|t| t == m), "{m} missing in {trail:?}");
        }
    }

    /// Exploration run for development: `SH2_STORY_UNTIL=<map>` (default none), `SH2_STORY_SECS` (game seconds, default 3600), `SH2_STORY_BOOST`
    /// (party level, default 60).  `SH2_STORY_PRINT=1|2` shows the trail live.  `cargo test -p sh2_app headless_us_story_explore -- --ignored --nocapture`
    #[test]
    #[ignore]
    fn headless_us_story_explore() {
        let _g = SERIAL.lock().unwrap_or_else(|e| e.into_inner());
        let until = std::env::var("SH2_STORY_UNTIL").unwrap_or_else(|_| "NONE".into());
        let secs = std::env::var("SH2_STORY_SECS").ok().and_then(|v| v.parse().ok()).unwrap_or(3600.0);
        let boost = std::env::var("SH2_STORY_BOOST").ok().and_then(|v| v.parse().ok()).or(Some(60));
        let _ = run_us_story(&until, secs, boost);
    }

    /// Game over: a lost fight (`SSHSys::cbBattleA` outcome 1) ends in `Scene::GameOver`, and confirming the screen returns to the title
    /// (`GameOverScene` -> `ShiftTitle` -> `opening()`).
    #[test]
    fn headless_game_over_returns_to_title() {
        // process-wide state (retail flag, env vars, the session) is shared with the US story tests: run one at a time
        let _g = SERIAL.lock().unwrap_or_else(|e| e.into_inner());
        let mut app = App::new();
        app.add_plugins((MinimalPlugins, StatesPlugin, bevy::input::InputPlugin))
            .insert_resource(TimeUpdateStrategy::ManualDuration(Duration::from_micros(16_667)))
            .insert_resource(sh2_core::app::AppConfig { screen_w: 512, screen_h: 448, disc_dir: ".".into() })
            .init_state::<Scene>()
            .add_plugins(sh2_core::ssh_sys::SshSysPlugin)
            .add_plugins((sh2_core::game::GameCorePlugin, MenuPlugin))
            .add_systems(Startup, crate::init_instance)
            .add_systems(Update, (crate::system_poller, crate::scene_transition).chain());
        let mut visited: Vec<Scene> = vec![];
        let mut triggered = false;
        let mut presses = 0;
        for i in 0..6000 {
            app.update();
            let s = *app.world().resource::<State<Scene>>().get();
            if visited.last() != Some(&s) {
                visited.push(s);
            }
            if s == Scene::Title && !triggered && i > 20 {
                // a lost battle: result bits 1 (lose) with the "no game over" flag clear
                app.world_mut().resource_mut::<SshSys>().cb_battle(0, sh2_core::game::BattleOutcome::Lose.bits());
                triggered = true;
            }
            if s == Scene::GameOver {
                presses += 1;
                app.world_mut().resource_mut::<PadInjection>().raw = if presses % 20 < 3 { padbit::CIRCLE } else { 0 };
            } else {
                app.world_mut().resource_mut::<PadInjection>().raw = 0;
            }
            if triggered && visited.len() >= 3 && s == Scene::Title {
                break;
            }
        }
        assert_eq!(visited, vec![Scene::Boot, Scene::Title, Scene::GameOver, Scene::Title]);
    }

    /// Save / load through the file-backed device: a slot written beforehand makes the title offer "Continue"; choosing it restores cash and
    /// the map and enters the field (`TitleCmd::EnterLoadedGame`).
    #[test]
    fn headless_continue_loads_the_save() {
        // process-wide state (retail flag, env vars, the session) is shared with the US story tests: run one at a time
        let _g = SERIAL.lock().unwrap_or_else(|e| e.into_inner());
        use sh2_menu::plugin::SaveDevice;
        use sh2_menu::session::{save_session, FileStorage};
        let dir = std::env::temp_dir().join(format!("sh2_headless_continue_{}", std::process::id()));
        let _ = std::fs::remove_dir_all(&dir);
        let mut dev = FileStorage::new(&dir);
        let mut s = GameSession::default();
        s.new_game("AP_02_U");
        s.needs_party_init = false;
        s.add_cash(777);
        save_session(&mut dev, &mut s, 0).unwrap();
        let mut app = App::new();
        app.add_plugins((MinimalPlugins, StatesPlugin, bevy::input::InputPlugin))
            .insert_resource(TimeUpdateStrategy::ManualDuration(Duration::from_micros(16_667)))
            .insert_resource(sh2_core::app::AppConfig { screen_w: 512, screen_h: 448, disc_dir: ".".into() })
            .insert_resource(SaveDevice(FileStorage::new(&dir)))
            .init_state::<Scene>()
            .add_plugins(sh2_core::ssh_sys::SshSysPlugin)
            .add_plugins((sh2_core::game::GameCorePlugin, MenuPlugin))
            .add_systems(Startup, crate::init_instance)
            .add_systems(Update, (crate::system_poller, crate::scene_transition).chain());
        let mut downs = 0;
        let mut state_ticks = 0u32;
        let mut last_state = u32::MAX;
        let mut reached_field = false;
        for _ in 0..6000 {
            app.update();
            let sc = *app.world().resource::<State<Scene>>().get();
            let mut raw = 0;
            if let Some(rt) = app.world().get_resource::<TitleRuntime>() {
                let st = rt.om.state;
                if st != last_state {
                    last_state = st;
                    state_ticks = 0;
                }
                state_ticks += 1;
                match st {
                    title::S_TRIAL_WAIT if state_ticks > 40 => raw = padbit::CIRCLE,
                    title::S_TITLE_WAIT if state_ticks > 40 => raw = padbit::START,
                    title::S_MENU if state_ticks > 40 => {
                        // two DOWN taps select "Continue" (row 2), then confirm
                        if downs < 2 {
                            raw = if state_ticks % 20 < 3 { padbit::DOWN } else { 0 };
                            if state_ticks % 20 == 3 {
                                downs += 1;
                            }
                        } else if state_ticks % 20 < 3 {
                            raw = padbit::CIRCLE;
                        }
                    }
                    _ => {}
                }
            }
            app.world_mut().resource_mut::<PadInjection>().raw = raw;
            if sc == Scene::Field {
                reached_field = true;
                break;
            }
        }
        assert!(reached_field, "never reached the field");
        assert_eq!(app.world().resource::<GameSession>().cash(), 777);
        assert_eq!(app.world().resource::<sh2_core::game::FieldRequest>().map, "AP_02_U");
        let _ = std::fs::remove_dir_all(&dir);
    }
}

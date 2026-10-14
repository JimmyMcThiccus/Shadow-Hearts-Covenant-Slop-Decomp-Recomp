//! Dev driver for the field screens (`SH2_SCREEN_DEV`): boots straight into a new game on a field map, opens one screen the way the game's
//! script does (the same `ScriptState::menu_req` the op `SpecialMenu` sets), plays a scripted pad run and photographs it.
//!
//! ```text
//! SH2_SCREEN_DEV=shop:1:AR_01_U  SH2_SCREEN_SHOTS=<dir>  cargo run -p sh2_app            # JP demo
//! SH2_SCREEN_DEV=shop:6:PA_03_U  SH2_SCREEN_SHOTS=<dir>  cargo run -p sh2_app -- --us    # US retail
//! ```
//! Kinds: `shop:<id>:<map>`, `tailor:<map>`, `solomon:<map>`, `warp:<map>` (needs a map with warp points), `save:<map>`.  The process exits when the
//! script has finished.

use std::path::PathBuf;

use ::bevy::prelude::*;

use sh2_battle::plugin::BattleDb;
use sh2_core::game::{padbit, FieldRequest, GameSet, Scene};
use sh2_core::ssh_sys::{SshApi, SshSys};
use sh2_menu::session::GameSession;

use crate::fscreen::{FieldScreens, ScreenAct, ScreenReq, ScreenScript};
use crate::host::MenuReq;
use crate::menu_overlay::Act;
use crate::plugin::FieldRuntime;

#[derive(Resource)]
struct Dev {
    /// world map dev run: its own pad / photo script
    wm_script: ScreenScript,
    wm_key_ticks: u32,
    kind: String,
    arg: i32,
    map: String,
    dir: Option<PathBuf>,
    started: bool,
    opened: bool,
    opened_at: u32,
    ticks: u32,
    idle: u32,
    /// `SH2_SCREEN_VIA=<event>[:<event>..]`: open the screen through the map script (events called in order, circle mashed through the dialogue)
    via: Vec<u32>,
    via_next: usize,
    via_wait: u32,
}

fn parse() -> Option<Dev> {
    let v = std::env::var("SH2_SCREEN_DEV").ok()?;
    let mut it = v.split(':');
    let kind = it.next()?.to_string();
    let (arg, map) = if kind == "shop" {
        let a = it.next().and_then(|s| s.parse().ok()).unwrap_or(0);
        (a, it.next().unwrap_or("AR_01_U").to_string())
    } else {
        (0, it.next().unwrap_or("AP_02_U").to_string())
    };
    Some(Dev { wm_script: ScreenScript::new(match kind.as_str() { "points" => script_for("points"), "npc" => script_for("npc"), _ => wm_script() }, std::env::var("SH2_SCREEN_SHOTS").ok().map(PathBuf::from)), wm_key_ticks: 0, kind, arg, map, dir: std::env::var("SH2_SCREEN_SHOTS").ok().map(PathBuf::from), started: false, opened: false, opened_at: 0, ticks: 0, idle: 0, via: std::env::var("SH2_SCREEN_VIA").ok().map(|v| v.split(':').filter_map(|e| e.parse().ok()).collect()).unwrap_or_default(), via_next: 0, via_wait: 0 })
}

fn k(b: u16) -> ScreenAct {
    ScreenAct::Key(b)
}
fn w(n: u32) -> ScreenAct {
    ScreenAct::Wait(n)
}
fn shot(n: &str) -> ScreenAct {
    ScreenAct::Shot(n.to_string())
}

/// The pad run of one screen kind.
pub fn script_for(kind: &str) -> Vec<ScreenAct> {
    use padbit::*;
    match kind {
        "shop" => {
            let u = |s: &str| ScreenAct::Until(s.to_string());
            let mash = |st: &str| ScreenAct::Mash { key: CIRCLE, state: st.to_string(), every: 13 };
            vec![
                u("main"), w(60), shot("shop_01_main"), k(CIRCLE), u("list"), w(20), shot("shop_02_buy_list"), k(RIGHT), w(6), k(RIGHT), w(6), k(DOWN), w(8), k(RIGHT), w(10), shot("shop_03_quantity"),
                k(CIRCLE), u("query"), w(20), shot("shop_04_query"), k(CIRCLE), u("rate"), w(20), shot("shop_05_rate"), k(CIRCLE), u("ringintro"), w(30), shot("shop_06_ring_intro"), u("ring"), w(50), shot("shop_07_ring_start"),
                mash("ring"), u("ringend"), w(20), shot("shop_08_ring_end"), u("result"), w(60), shot("shop_09_result"), k(CIRCLE), u("list"), w(20), shot("shop_10_after_buy"),
                k(CROSS), u("main"), w(10), k(DOWN), w(6), k(CIRCLE), u("list"), w(20), shot("shop_11_sell_list"), k(RIGHT), w(10), k(CIRCLE), u("query"), w(20), shot("shop_12_sell_query"),
                k(DOWN), w(5), k(CIRCLE), u("result"), w(40), shot("shop_13_sell_result"), k(CIRCLE), u("list"), w(20), k(CROSS), u("main"), w(10), shot("shop_14_main_after"), k(DOWN), w(6), ScreenAct::Menu(vec![Act::Wait(150), Act::Shot("shop_15_equip_menu".into()), Act::Key(CROSS), Act::Wait(40), Act::Key(CROSS), Act::Wait(60)]), k(CIRCLE), w(300), u("main"), w(10), shot("shop_16_back_in_shop"), k(CROSS), u("leaving"), w(60),
            ]
        }
        "tailor" => {
            let u = |s: &str| ScreenAct::Until(s.to_string());
            let mash = |st: &str| ScreenAct::Mash { key: CIRCLE, state: st.to_string(), every: 40 };
            vec![
                u("select"), w(20), shot("tailor_01_select"), k(RIGHT), w(30), k(RIGHT), w(30), shot("tailor_02_page3"), k(CIRCLE), u("ask"), w(260), shot("tailor_03_confirm_question"), k(CIRCLE), u("yesno"), w(20), shot("tailor_04_yes_no"),
                k(CIRCLE), u("work"), w(120), shot("tailor_05_working"), w(300), shot("tailor_06_presenting"), mash("work"), u("magic"), w(30), shot("tailor_07_class_note"), mash("magic"), u("comment"), w(30), shot("tailor_08_comment"), mash("comment"), u("leave"), w(30),
                // the same dress cannot be ordered twice: back in a new session the buzzer
            ]
        }
        "solomon" => {
            let u = |s: &str| ScreenAct::Until(s.to_string());
            vec![
                w(60), shot("solomon_01_tutorial"), ScreenAct::Mash { key: CIRCLE, state: "tutorial".to_string(), every: 20 }, u("menu"), w(30), shot("solomon_02_menu"), k(CIRCLE), u("list"), w(20), shot("solomon_03_crest_list"),
                k(DOWN), w(8), k(DOWN), w(8), shot("solomon_04_list_note"), k(CIRCLE), u("map"), w(30), shot("solomon_05_holding"), k(RIGHT), w(8), k(RIGHT), w(8), k(DOWN), w(8), shot("solomon_06_moved"), k(CIRCLE), w(30), shot("solomon_07_placed"),
                k(CROSS), w(20), shot("solomon_08_back_to_list"), k(CROSS), w(20), shot("solomon_09_menu_again"), k(DOWN), w(5), shot("solomon_10_hints_menu"), k(CIRCLE), u("hints"), w(20), shot("solomon_11_hints"),
            ]
        }
        "npc" => {
            // `SH2_NPC_SHOTS=<n>` photographs every `SH2_NPC_SPACING` ticks (default 6 x 150)
            let n: u32 = std::env::var("SH2_NPC_SHOTS").ok().and_then(|v| v.parse().ok()).unwrap_or(6);
            let sp: u32 = std::env::var("SH2_NPC_SPACING").ok().and_then(|v| v.parse().ok()).unwrap_or(150);
            let mut v = vec![w(60)];
            for i in 1..=n {
                v.push(shot(&format!("npc_{i:02}")));
                v.push(w(sp));
            }
            v
        }
        "points" => vec![
            w(150), shot("points_01_save_on"), k(TRIANGLE), w(70), shot("points_02_menu_on_save"), k(CROSS), w(60), shot("points_03_menu_closed"), ScreenAct::Note("warp_out".into()), w(30), shot("points_04_warp_out_start"), w(30), shot("points_05_warp_out_mid"), w(60),
            ScreenAct::Note("warp_in".into()), w(24), shot("points_06_warp_in"), w(60),
        ],
        // the real `dataAccess` screen (`SH2_SCREEN_DEV=data:<map>`: Save with two slots already used; `dataload:<map>`: Load)
        "data" => {
            let u = |s: &str| ScreenAct::Until(s.to_string());
            vec![
                u("devices"), w(30), shot("data_01_devices"), k(DOWN), w(12), shot("data_02_devices_slot2"), k(UP), w(6), k(CIRCLE), u("files"), w(40), shot("data_03_files"),
                k(DOWN), w(6), shot("data_04_scrolling"), w(30), shot("data_05_files_slot2"), k(UP), w(30), k(DOWN), w(30), k(DOWN), w(30), shot("data_06_files_slot3"), k(CIRCLE), u("query"), w(30), shot("data_07_query_new"),
                k(CROSS), u("files"), w(10), k(UP), w(30), k(UP), w(30), k(CIRCLE), u("query"), w(30), shot("data_08_query_overwrite"), k(UP), w(10), shot("data_09_query_yes"), k(CIRCLE), u("progress"), w(2), shot("data_10_progress"), u("done"), w(20),
                shot("data_11_done"), k(CIRCLE), w(60),
            ]
        }
        "dataload" => {
            let u = |s: &str| ScreenAct::Until(s.to_string());
            vec![
                u("devices"), w(30), k(DOWN), w(8), k(CIRCLE), u("warning"), w(20), shot("data_20_no_card"), k(CIRCLE), u("quit"), w(30), shot("data_21_quit"), k(CIRCLE), u("devices"), w(10), k(UP), w(8), k(CIRCLE), u("files"), w(40),
                shot("data_22_load_files"), k(CIRCLE), u("query"), w(30), shot("data_23_load_query"), k(CROSS), u("files"), w(10), k(CROSS), u("quit"), w(20), shot("data_24_quit_load"), k(UP), w(10), k(CIRCLE), w(80),
            ]
        }
        _ => vec![w(60), shot("screen")],
    }
}

/// Pad run of the world map (`SH2_SCREEN_DEV=worldmap`): the unlock demo (`SH2_WM_UNLOCK=<point>`), a scroll, the triangle menu.
fn wm_script() -> Vec<ScreenAct> {
    use padbit::*;
    if sh2_core::boot::is_retail() {
        // retail: the point list depends on progress; L1 / R1 switch the world, cross goes back, circle on a portal point opens its world
        return vec![w(40), shot("wm_01_retail_open"), shot("wm_02_retail_demo"), shot("wm_03_retail_select"), k(R1), w(60), shot("wm_04_after_r1"), k(L1), w(60), shot("wm_05_after_l1"), k(DOWN), w(30), shot("wm_06_down"), k(TRIANGLE), w(80), shot("wm_07_triangle_menu"), k(CROSS), w(50), k(CROSS), w(80), k(CROSS), w(60), shot("wm_08_after_cross"), k(UP), w(40)];
    }
    vec![w(36), shot("wm_01_scroll_to_new_point"), shot("wm_02_rays_growing"), shot("wm_03_rays_shrinking"), shot("wm_04_demo_over"), shot("wm_05_back_on_selection"), k(DOWN), w(10), shot("wm_06_scrolling"), w(40), shot("wm_07_scrolled"), k(TRIANGLE), w(80), shot("wm_08_triangle_menu"), k(CROSS), w(50), k(CROSS), w(80), shot("wm_09_back"), k(UP), w(40)]
}

/// Runs the world map script by injecting pad bits and photographing.
fn wm_driver(
    mut dev: ResMut<Dev>,
    mut inj: ResMut<sh2_core::game::PadInjection>,
    mut screens: ResMut<FieldScreens>,
    wm: Option<Res<crate::worldmap_plugin::WorldMapRuntime>>,
    mut field: Option<ResMut<FieldRuntime>>,
    mut exit: MessageWriter<AppExit>,
) {
    if matches!(dev.kind.as_str(), "worldmap" | "points" | "npc") {
        inj.raw = 0;
    }
    let ready = match dev.kind.as_str() {
        "worldmap" => wm.is_some(),
        "points" | "npc" => dev.opened,
        _ => false,
    };
    if !ready {
        return;
    }
    // NPC walking check: log where the script actors are every two seconds
    if dev.kind == "npc" && dev.ticks % 120 == 0 {
        if let Some(f) = field.as_deref() {
            for (i, a) in f.st.actors.slots.iter().enumerate() {
                if let Some(a) = a.as_ref().filter(|a| a.loaded && a.disp && i != f.st.actors.ctrl) {
                    log::info!("npc t={} slot {i} `{}` pos [{:.1} {:.1} {:.1}] yaw {:.2} gait {} move {}", dev.ticks, a.model_name, a.pos[0], a.pos[1], a.pos[2], a.yaw, a.gait, a.mv.is_some());
                }
            }
        }
    }
    dev.wm_key_ticks += 1;
    if dev.wm_script.wait > 0 {
        dev.wm_script.wait -= 1;
        return;
    }
    match dev.wm_script.acts.pop_front() {
        Some(ScreenAct::Key(kb)) => {
            inj.raw = kb;
            dev.wm_script.wait = 3;
        }
        Some(ScreenAct::Wait(n)) => dev.wm_script.wait = n,
        Some(ScreenAct::Shot(n)) => {
            screens.script.dir = dev.wm_script.dir.clone();
            screens.shot = Some(n);
            dev.wm_script.wait = 24;
        }
        // `CField::DoWarp(slot, out / in)`
        Some(ScreenAct::Note(n)) if n == "warp_out" || n == "warp_in" => {
            if let Some(f) = field.as_deref_mut() {
                let incoming = n == "warp_in";
                let total = if incoming { 84 } else { 72 };
                f.st.warp_fx = Some(crate::host::WarpFx { ticks_left: total, incoming, color: if incoming { [255, 255, 255] } else { [255, 240, 255] }, total });
                f.st.warp_state = if incoming { 2 } else { 1 };
            }
        }
        Some(_) => {}
        None => {
            dev.idle += 1;
            if dev.idle > 60 {
                exit.write(AppExit::Success);
            }
        }
    }
}

#[allow(clippy::too_many_arguments)]
fn dev_driver(
    mut dev: ResMut<Dev>,
    mut session: ResMut<GameSession>,
    db: Option<Res<BattleDb>>,
    mut sys: ResMut<SshSys>,
    mut field_req: ResMut<FieldRequest>,
    mut field: Option<ResMut<FieldRuntime>>,
    scene: Res<State<Scene>>,
    mut screens: ResMut<FieldScreens>,
    mut inj: ResMut<sh2_core::game::PadInjection>,
    mut menu: ResMut<crate::menu_overlay::InGameMenu>,
    mut savedev: ResMut<sh2_menu::plugin::SaveDevice>,
    mut exit: MessageWriter<AppExit>,
) {
    dev.ticks += 1;
    if dev.kind != "worldmap" && dev.kind != "points" && dev.kind != "npc" {
        inj.raw = 0;
    }
    if dev.kind == "points" {
        // the wm_driver owns the script of this kind
        dev.wm_script = std::mem::take(&mut dev.wm_script);
    }
    if dev.ticks == 40 && !dev.started {
        let Some(db) = db.as_ref() else { return };
        dev.started = true;
        session.new_game(&dev.map);
        sh2_battle::bridge::init_new_game(&db.0, &mut session);
        session.needs_party_init = false;
        if dev.kind != "menu" {
            session.add_cash(123_456);
            crate::cmd_pages::dev_seed(&mut session, &db.0);
        }
        // some shop points so the rank shows (rank C needs 25 on the demo's table)
        if let Some(b) = session.save.menu.data.get_mut(crate::shop::OFF_SHOP_POINTS..crate::shop::OFF_SHOP_POINTS + 4) {
            let v: i32 = std::env::var("SH2_SCREEN_POINTS").ok().and_then(|s| s.parse().ok()).unwrap_or(13);
            b.copy_from_slice(&v.to_le_bytes());
        }
        if dev.kind == "worldmap" && sh2_core::boot::is_retail() {
            // a retail new game has no open world-map points yet: open the first ones (state byte 1, `WM` chunk +0xc + id)
            if let Some(c) = session.save.field.find_mut(sh2_menu::save::FieldSave::TAG_WM) {
                for i in 0..24 {
                    if let Some(b) = c.payload.get_mut(0xc + i) {
                        *b = 1;
                    }
                }
            }
        }
        field_req.map = if dev.kind == "worldmap" { crate::worldmap::WORLDMAP_NAME.to_string() } else { dev.map.clone() };
        field_req.entry = 0;
        sys.set_api(SshApi::FieldSocket);
    }
    if dev.kind == "worldmap" {
        return;
    }
    if !dev.opened && dev.started {
        if let (Some(f), Scene::Field) = (field.as_deref_mut(), *scene.get()) {
            if f.map == dev.map && f.cover.clear() && f.st.ticks > 90 && !f.st.msg_active() {
                dev.opened = true;
                dev.opened_at = dev.ticks;
                // the op `SpecialMenu(0x100, id)` / `(0x300, 0)` sets exactly this (host.rs `special_menu`)
                match dev.kind.as_str() {
                    _ if !dev.via.is_empty() && matches!(dev.kind.as_str(), "shop" | "tailor") => {}
                    "shop" => f.st.menu_req = Some(MenuReq::Shop { id: dev.arg }),
                    "tailor" => f.st.menu_req = Some(MenuReq::Tailor),
                    "solomon" => {
                        // crests of the flame desert (region 4) and a few others
                        for d in [0usize, 1, 2, 3, 4, 17, 18, 19, 20, 21, 6, 7, 8, 9, 12, 13, 14] {
                            crate::shop::bag_add(&mut session.save.btl, 5, d, 1);
                        }
                        screens.req = Some(ScreenReq::Solomon)
                    }
                    "points" => {
                        // a save point under the player and a warp pad a few steps away (`SavePoint` / `WarpPoint` script ops)
                        let p = f.sim.player.pos;
                        f.st.save_points[0] = Some(crate::host::SavePointSlot { active: true, pos: p, shown: true });
                        f.st.warp_points[0] = Some(crate::host::WarpPointSlot { active: true, pos: [p[0] - 24.0, p[1], p[2] + 10.0], kind: 1, shown: true });
                    }
                    "data" | "dataload" => {
                        // two slots already used so the panels show data
                        for (slot, cash, ms) in [(0u8, 4321, 3_725_000u32), (2, 98_765, 36_000_000)] {
                            let c0 = session.cash();
                            session.add_cash(cash - c0 as i32);
                            session.play_ms = ms as u64;
                            let _ = sh2_menu::session::save_session(&mut savedev.0, &mut session, slot);
                        }
                        screens.req = Some(ScreenReq::Data { load: dev.kind == "dataload", reopen_menu: false });
                    }
                    "menu" => {
                        // the in-game command menu as an early retail save shows it (live capture of `AP_02_U`): Items, White Magic, Equipment, Personal, Data /
                        // Help, Score, Library, Inventory, Options.  `SH2_MENU_SCRIPT` = steps, see [`parse_menu_script`].  The battle dev overrides
                        // (`SH2_BATTLE_PARTY` / `_LEVEL` / `_SAVE` / `_MENU` / `_RECIPE`) apply here too, to mirror `tools/live/party.py` setups.
                        if let Some(db) = db.as_ref() {
                            let _ = sh2_battle::devdrive::party_overrides(&db.0, &mut session);
                        }
                        for i in 0..crate::cmd_top::ENTRY_COUNT {
                            session.save.menu.data[crate::cmd_top::OFF_ENTRY_FLAGS + i] = if [0, 1, 4, 6, 9, 15, 16, 17, 18, 19].contains(&i) { 2 } else { 0 };
                        }
                        f.st.menu_wait = false;
                        menu.request = true;
                        let steps = std::env::var("SH2_MENU_SCRIPT").unwrap_or_else(|_| "w70,shot:01_top".into());
                        menu.script = crate::menu_overlay::MenuScript::new(parse_menu_script(&steps), dev.dir.clone());
                    }
                    "save" => {
                        // `SpecialMenu(0x10)` opens the save page directly; the menu's own script photographs it
                        f.st.menu_wait = false;
                        menu.request = true;
                        menu.script = crate::menu_overlay::MenuScript::new(
                            vec![Act::GotoData(false), Act::Wait(120), Act::Shot("save_01_screen".into()), Act::Key(padbit::CIRCLE), Act::Wait(50), Act::Shot("save_02_after_circle".into()), Act::Key(padbit::CROSS), Act::Wait(30)],
                            dev.dir.clone(),
                        );
                    }
                    _ => {}
                }
                if dev.via.is_empty() && matches!(dev.kind.as_str(), "shop" | "tailor" | "solomon") {
                    f.st.menu_wait = true;
                }
                if dev.via.is_empty() {
                    screens.script = ScreenScript::new(script_for(&dev.kind), dev.dir.clone());
                }
            }
        }
    }
    // through the map script: call the events in turn (a shopkeeper introduces himself on the first visit), mash circle through the dialogue,
    // and start the pad run once the script has opened the screen
    if dev.opened && !dev.via.is_empty() && dev.via_next <= dev.via.len() {
        if let Some(f) = field.as_deref_mut() {
            if screens.is_active() || screens.req.is_some() {
                dev.via_next = dev.via.len() + 1;
                screens.script = ScreenScript::new(script_for(&dev.kind), dev.dir.clone());
                return;
            }
            let quiet = !f.st.event_running && !f.vm.is_running();
            dev.via_wait += 1;
            if dev.via_wait % 8 == 0 {
                inj.raw = padbit::CIRCLE;
            }
            if quiet && dev.via_wait > 30 && dev.via_next < dev.via.len() {
                let ev = dev.via[dev.via_next];
                dev.via_next += 1;
                dev.via_wait = 0;
                info!("screens dev: calling map event {ev} (arg 1)");
                if f.vm.call_event(ev, &[1]) {
                    f.st.event_running = true;
                }
            }
        }
        return;
    }
    if dev.opened && screens.script.acts.is_empty() && screens.shot.is_none() && !screens.is_active() && (dev.kind != "save" || menu.script.is_empty() || dev.ticks > dev.opened_at + 700) {
        dev.idle += 1;
        if dev.idle > 90 {
            info!("screens dev: finished, exiting");
            exit.write(AppExit::Success);
        }
    }
}

/// `SH2_MENU_SCRIPT` for `SH2_SCREEN_DEV=menu`: comma separated steps -- `w<ticks>` wait, `shot:<name>`, a pad key (`up down left right circle cross triangle
/// square l1 r1 l2 r2 start select`, one tick plus an 8 tick wait; the retail layout: circle = confirm, cross = cancel), `goto:<page>[:<pc>]` (`item`, `equipment`,
/// `private`, `magic`, `white`, `crest`, `formation`, `option`, `help`, `score`, `library`, `plist`, `ring`, `grave`, `keycustom`, `combokey`, `combomagic`), `pop`, `data` / `load`.
pub fn parse_menu_script(s: &str) -> Vec<Act> {
    use crate::cmd::CmdPage;
    let mut v = Vec::new();
    for t in s.split(',').map(str::trim).filter(|t| !t.is_empty()) {
        if let Some(n) = t.strip_prefix('w').and_then(|n| n.parse::<u32>().ok()) {
            v.push(Act::Wait(n));
        } else if let Some(n) = t.strip_prefix("shot:") {
            v.push(Act::Shot(n.to_string()));
        } else if let Some(g) = t.strip_prefix("goto:") {
            let mut it = g.split(':');
            let page = match it.next().unwrap_or("") {
                "item" => CmdPage::Item,
                "white" => CmdPage::WhiteMagic,
                "magic" => CmdPage::Magic,
                "crest" => CmdPage::Crest,
                "equipment" | "equip" => CmdPage::Equipment,
                "ring" => CmdPage::RingCustom,
                "private" | "personal" | "status" => CmdPage::Private,
                "formation" => CmdPage::Formation,
                "grave" => CmdPage::Graveyard,
                "combokey" => CmdPage::ComboKey,
                "combomagic" => CmdPage::ComboMagic,
                "help" => CmdPage::Help,
                "score" => CmdPage::Score,
                "library" => CmdPage::Library,
                "plist" | "inventory" => CmdPage::PropertyList,
                "option" => CmdPage::Option,
                "keycustom" => CmdPage::KeyCustom,
                _ => continue,
            };
            v.push(Act::Goto(page, it.next().and_then(|c| c.parse().ok())));
            v.push(Act::Wait(40));
        } else if t == "pop" {
            v.push(Act::PopPage);
            v.push(Act::Wait(20));
        } else if t == "data" || t == "load" {
            v.push(Act::GotoData(t == "load"));
            v.push(Act::Wait(40));
        } else {
            let bit = match t {
                "up" => padbit::UP,
                "down" => padbit::DOWN,
                "left" => padbit::LEFT,
                "right" => padbit::RIGHT,
                "circle" => padbit::CIRCLE,
                "cross" => padbit::CROSS,
                "triangle" => padbit::TRIANGLE,
                "square" => padbit::SQUARE,
                "l1" => padbit::L1,
                "r1" => padbit::R1,
                "l2" => padbit::L2,
                "r2" => padbit::R2,
                "start" => padbit::START,
                "select" => padbit::SELECT,
                _ => continue,
            };
            v.push(Act::Key(bit));
            v.push(Act::Wait(8));
        }
    }
    v
}

pub fn add(app: &mut App) {
    if let Some(d) = parse() {
        // scripted runs must keep ticking when the window is not frontmost
        app.insert_resource(::bevy::winit::WinitSettings::game());
        app.insert_resource(d);
        app.add_systems(FixedUpdate, (dev_driver, wm_driver).in_set(GameSet::Logic));
    }
}

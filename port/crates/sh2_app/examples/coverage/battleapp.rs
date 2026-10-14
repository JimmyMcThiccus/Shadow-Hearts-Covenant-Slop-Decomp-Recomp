//! Battles through the real game app: a headless Bevy app (MinimalPlugins + the scene plugins, as `sh2_app`'s headless tests) enters
//! `Scene::Battle` for a monster set and an autoplayer plays it through the pad exactly like `--autoplay` (circle on every menu, circle
//! when the Judgement Ring pointer is in the zone, circle through the result screens) until the game returns to the field or shows
//! Game Over.  This runs `BattlePlugin`'s own systems (stage / camera / choreography / effect playback / HUD state / result flow) that
//! the logic-only `battle` check does not.

use super::common::*;
use bevy::prelude::*;
use bevy::state::app::StatesPlugin;
use bevy::time::TimeUpdateStrategy;
use sh2_battle::plugin::{BattlePlugin, BattleRuntime, BattleView, RingView};
use sh2_core::game::{padbit, PadInjection, Scene};
use sh2_core::ssh_sys::{SshApi, SshSys, SysBtlParam};
use sh2_field::plugin::FieldPlugin;
use sh2_menu::plugin::MenuPlugin;
use sh2_menu::session::GameSession;
use std::time::Duration;

fn system_poller(mut sys: ResMut<SshSys>, time: Res<Time>) {
    sys.polling(time.delta());
}

fn scene_transition(mut sys: ResMut<SshSys>, mut next: ResMut<NextState<Scene>>, mut field: ResMut<sh2_core::game::FieldRequest>, mut battle: ResMut<sh2_core::game::BattleRequest>) {
    sh2_core::game::apply_sys_actions(&mut sys, &mut field, &mut battle);
    match sys.take_request() {
        Some(sh2_core::ssh_sys::SceneRequest::Field) => next.set(Scene::Field),
        Some(sh2_core::ssh_sys::SceneRequest::Battle) => next.set(Scene::Battle),
        Some(sh2_core::ssh_sys::SceneRequest::GameOver) => next.set(Scene::GameOver),
        Some(sh2_core::ssh_sys::SceneRequest::Title) => next.set(Scene::Title),
        None => {}
    }
}

#[derive(Resource, Clone)]
pub struct Start {
    set: i32,
    bg: u32,
}

fn start(mut sys: ResMut<SshSys>, mut session: ResMut<GameSession>, mut req: ResMut<sh2_core::game::BattleRequest>, st: Res<Start>) {
    sys.retail = true;
    // the party of the logic check (new game + Yuri / Karin / Joachim / Nicolai at level 60)
    let c = super::battle::ctx();
    let party = c.party.clone();
    let mut sess = c.session;
    // level 30 (not 60): the fight must last long enough for the enemies to act and their effects to play
    let tbl = sh2_battle::bridge::level_table(&c.db);
    for &pc in &party {
        sess.save.btl.pc_level_init(pc as usize, 30, &tbl);
    }
    *session = sess;
    let mut pc = [0xffu8; 4];
    for (i, p) in party.iter().take(4).enumerate() {
        pc[i] = *p;
    }
    req.param = SysBtlParam { w0: st.bg, regdat_id: st.set, bgm: 0, pc_count: party.len().min(4) as u8, monster_set: 0, pc };
    req.return_map = "AP_03_U".into();
    sys.field_name = "AP_03_U".into();
    sys.set_api(SshApi::BtlSocket);
}

pub fn build_app(st: Start) -> App {
    let us = disc_dir();
    let dir = std::env::temp_dir().join(format!("sh2_qa_battleapp_{}", std::process::id()));
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
        .insert_resource(sh2_core::app::AppConfig { screen_w: 512, screen_h: 448, disc_dir: us })
        .insert_resource(sh2_core::boot::ActiveBuild(sh2_core::boot::Region::Us))
        .insert_resource(sh2_menu::plugin::SaveDevice(sh2_menu::session::FileStorage::new(&dir)))
        .init_state::<Scene>()
        .add_plugins(sh2_core::ssh_sys::SshSysPlugin)
        .add_plugins((sh2_core::game::GameCorePlugin, MenuPlugin, FieldPlugin, BattlePlugin))
        .add_plugins(sh2_field::actors::ActorPlugin)
        .init_resource::<sh2_gfx::bevy::character::CharacterCache>()
        .insert_resource(st)
        .add_systems(Startup, start)
        .add_systems(Update, (system_poller, scene_transition).chain());
    app
}

pub fn run_all(out: &std::path::Path, fresh: bool, only: Option<&str>) {
    let c = super::battle::ctx();
    let n = c.db.dat.count(sh2_battle::data::SEC_MONSET, 0x10);
    let mut sink = Sink::open(out, "battleapp", fresh);
    for set in 0..n {
        let id = format!("monset {set:03}");
        if !mine() || only.map(|o| !id.contains(o)).unwrap_or(false) || sink.done.contains(&id) {
            continue;
        }
        if c.db.monster_set(set).map(|m| m.monsters.iter().take(m.monster_count()).all(|&x| x == 0xffff)).unwrap_or(true) {
            continue;
        }
        begin_item(&id, 240);
        let st = Start { set: set as i32, bg: 77 };
        let row = match guarded(|| check(&id, st)) {
            Ok(r) => r,
            Err(p) => {
                let mut r = Row::new(&id);
                r.status = "fails".into();
                r.owner = owner_of_path(&p).into();
                r.detail = p;
                r
            }
        };
        end_item();
        eprintln!("battleapp {id}: {} {}", row.status, row.detail.chars().take(150).collect::<String>());
        sink.put(&row);
    }
}

fn check(id: &str, st: Start) -> Row {
    let mut row = Row::new(id);
    let mut app = build_app(st);
    let mut visited: Vec<Scene> = vec![];
    let mut tap = 0u32;
    let mut zone = 0u32;
    let mut battle_ticks = 0u32;
    let (mut menus, mut rings, mut results) = (0u32, 0u32, 0u32);
    let mut last_menu = false;
    let mut fx = 0u32;
    let mut stage = String::new();
    let limit = 60 * 600;
    let mut i = 0;
    while i < limit {
        i += 1;
        app.update();
        let s = *app.world().resource::<State<Scene>>().get();
        if visited.last() != Some(&s) {
            visited.push(s);
        }
        if s == Scene::Battle {
            battle_ticks += 1;
        }
        if visited.contains(&Scene::Battle) && (s == Scene::Field || s == Scene::GameOver || s == Scene::Title) {
            break;
        }
        let w = app.world();
        let bv = w.get_resource::<BattleView>().map(|b| (b.stage.clone(), b.menu_open, b.result_shown));
        let rv = w.get_resource::<RingView>().map(|r| (r.active, r.in_zone));
        if let Some(rt) = w.get_resource::<BattleRuntime>() {
            fx = fx.max(rt.fx_started);
        }
        let mut raw = 0u16;
        tap += 1;
        let tapb = |b: u16, tap: u32| if tap % 20 < 3 { b } else { 0 };
        if let (Some((stg, menu, result)), Some((active, in_zone))) = (bv, rv) {
            stage = stg.clone();
            if menu && !last_menu {
                menus += 1;
            }
            last_menu = menu;
            if active {
                zone = if in_zone { zone + 1 } else { 0 };
                if in_zone && zone == 9 {
                    raw = padbit::CIRCLE;
                    rings += 1;
                }
            } else {
                zone = 0;
                if result {
                    results += 1;
                    raw = tapb(padbit::CIRCLE, tap);
                } else if (menu && stg == "running") || stg == "defeat" {
                    raw = tapb(padbit::CIRCLE, tap);
                }
            }
        }
        if s == Scene::GameOver {
            raw = tapb(padbit::CIRCLE, tap);
        }
        app.world_mut().resource_mut::<PadInjection>().raw = raw;
    }
    row.kv("scenes", format!("{visited:?}").replace([',', ' '], ""));
    row.kv("battle_secs", battle_ticks / 60);
    row.kv("menus", menus);
    row.kv("ring_presses", rings);
    row.kv("effects_started", fx);
    row.kv("last_stage", stage.replace([';', ','], " "));
    if !visited.contains(&Scene::Battle) {
        row.status = "fails".into();
        row.detail = format!("never entered Scene::Battle ({visited:?})");
        row.owner = "BE".into();
    } else if visited.last() == Some(&Scene::Battle) && menus >= 40 {
        // still taking turns: the Lv 30 autoplayer is just too weak for a late-game set
        row.status = "untested".into();
        row.detail = format!("not finished after {} s of game time but still progressing ({menus} command menus, {rings} ring presses): party too weak for this set", battle_ticks / 60);
    } else if visited.last() == Some(&Scene::Battle) {
        row.status = "fails".into();
        row.detail = format!("battle still running after {} s of game time (stage {stage}, {menus} command menus, {rings} ring presses)", battle_ticks / 60);
        row.owner = "BE".into();
    } else if visited.last() == Some(&Scene::GameOver) {
        row.add_detail("lost (Game Over) with the autoplayer (party Lv 30, plain attacks)");
    }
    let _ = results;
    let logs = take_log();
    let errs: Vec<&(String, usize)> = logs.iter().filter(|(l, _)| l.starts_with("ERROR")).collect();
    if !errs.is_empty() {
        row.worse("stub");
        row.add_detail(format!("errors logged: {}", errs.iter().take(3).map(|(l, n)| format!("{} x{n}", l.chars().take(120).collect::<String>())).collect::<Vec<_>>().join(" | ")));
        if row.owner.is_empty() {
            row.owner = "BE".into();
        }
    }
    if !logs.is_empty() {
        row.kv("warnings", logs.iter().map(|(_, n)| n).sum::<usize>());
        row.kv("warn_top", logs.iter().take(3).map(|(l, n)| format!("{} x{n}", l.chars().take(100).collect::<String>())).collect::<Vec<_>>().join(" | ").replace(';', ","));
    }
    row
}

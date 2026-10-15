//! Development aid: start a battle directly from the title screen and play it through the pad, taking screenshots of the interesting moments.
//!
//! Enabled by `SH2_BATTLE_DEMO=<monster set>` (e.g. `2`); `SH2_BATTLE_SHOTS=<dir>` selects the screenshot directory,
//! `SH2_BATTLE_CMDS=attack,item,magic,attack` the commands of the party turns (cycled), `SH2_BATTLE_BG=<id>` the background.
//! Commands: `attack`, `magic` (crest magic, or the character's special page), `skill`, `item`, `guard` (Block), `link` (Combo), `fusion`, `run`,
//! `tarot` (Lucia's Tarot Card: use the recipe `SH2_BATTLE_RECIPE=lucia`; `SH2_TAROT_STOP=<s>` = when the ring is stopped, shots `tarot_<n>_*`).
//! Shots (`bt_<n>_<name>.png`): `command_menu`, `target_select`, `magic_menu` / `skill_menu` / `item_menu` / `fusion_menu` / `guard_menu`,
//! `ally_target` / `link_target` / `magic_target` / `skill_target`, `combo_form`, `judgement_ring`, `effect`, `victory` ... (`SH2_BATTLE_MENU_AGE` = ticks a page
//! settles before its shot, default 70).
//! Party overrides (to reproduce the live capture agent's memory recipes): `SH2_BATTLE_PARTY=0,5,3,4` (PC ids, up to four; members the new game
//! does not create are initialised from `PC_I` like a member joining later), `SH2_BATTLE_LEVEL=<n>` (re-rolls every party member's stats at that
//! level), `SH2_BATTLE_SAVE=<hex off>:<hex bytes>,...` (bytes poked into the retail `BTL0` block at the offsets of
//! notes/integration/save_retail.md, e.g. `ec4:07` = fusions 0..2 known, `fd7:03` = three wolf bouts, `cff:08` = Karin's first Sword Art in
//! bag 1 (`0xabc + bag * 0x200 + 0x43`; a new game uses bag 1)) and `SH2_BATTLE_MENU=<hex off>:<hex bytes>` for the `MENU` block (`28c:01` = item sort mode 1).
//! Nothing is registered unless the variable is set.

use bevy::prelude::*;
use bevy::render::view::screenshot::{save_to_disk, Screenshot};
use std::collections::HashSet;

use sh2_core::game::{padbit, PadInjection, Scene};
use sh2_core::ssh_sys::{SshSys, SysBtlParam};
use sh2_menu::session::GameSession;

use crate::flow::Phase;
use crate::hud_result::{BonusPhase, ResultPhase, WinState};
use crate::plugin::{BattleRuntime, BattleView, RingView, Stage};
use crate::ui::{Page, Root};

#[derive(Resource, Default)]
pub struct DevDrive {
    set: u16,
    shots: Option<std::path::PathBuf>,
    cmds: Vec<String>,
    turn: usize,
    started: bool,
    ticks: u64,
    tap: u32,
    taken: HashSet<String>,
    queue: Vec<String>,
    seq: u32,
    last_menu_actor: Option<usize>,
    battle_ticks: u32,
    pub bg: u32,
    page_key: String,
    page_age: u32,
    ring_age: u32,
    fus_age: u32,
    exit_wait: u32,
    /// ticks spent in the game-over scene / back on the title (`SH2_BATTLE_LOSE=1` drives)
    go_ticks: u32,
    /// page key of the last committed command (a confirm tap lasts two ticks: the script advances once per page)
    last_commit: String,
    /// ticks spent in `Phase::Tarot` (`SH2_BATTLE_CMDS=tarot`), and whether the stop / result presses were already sent
    tarot_age: u32,
    tarot_stop_sent: bool,
    tarot_result_sent: bool,
    /// ticks the confirm press of the tarot script is still held (a one-tick press can fall between two game ticks)
    tarot_press: u8,
}

/// `SH2_BATTLE_BOOST_EXP=<n>`: the victory reward is replaced by `n` EXP for every party member that earned any (+ `n * 2` cash) so the result
/// screen's count-up / `Level Up!` can be photographed (live capture: notes/integration/battle_ui_u4.md).  Called by the plugin when the win
/// sequence is built.
pub fn boost_reward(r: Option<&mut crate::rules::BattleReward>) {
    let (Some(r), Some(n)) = (r, std::env::var("SH2_BATTLE_BOOST_EXP").ok().and_then(|v| v.parse::<i32>().ok())) else { return };
    r.exp_total = n;
    r.cash = n * 2;
    if r.items.is_empty() {
        r.items.push((0, 1));
    }
    for v in r.exp_per_pc.iter_mut() {
        if *v > 0 {
            *v = n;
        }
    }
}

pub fn enabled() -> bool {
    std::env::var_os("SH2_BATTLE_DEMO").is_some()
}

pub struct DevDrivePlugin;

impl Plugin for DevDrivePlugin {
    fn build(&self, app: &mut App) {
        let set = std::env::var("SH2_BATTLE_DEMO").ok().and_then(|s| s.parse().ok()).unwrap_or(2);
        let cmds = std::env::var("SH2_BATTLE_CMDS").unwrap_or_else(|_| "attack,item,magic,attack,attack".into()).split(',').map(|s| s.trim().to_string()).collect();
        app.insert_resource(DevDrive {
            set,
            shots: std::env::var_os("SH2_BATTLE_SHOTS").map(Into::into),
            cmds,
            bg: std::env::var("SH2_BATTLE_BG").ok().and_then(|s| s.parse().ok()).unwrap_or(0),
            ..Default::default()
        })
        .init_resource::<PadInjection>()
        .add_systems(Update, drive);
    }
}

/// `SH2_BATTLE_PARTY` / `SH2_BATTLE_LEVEL` / `SH2_BATTLE_SAVE` / `SH2_BATTLE_BAG` / `SH2_BATTLE_MENU` (module docs): returns the party
/// to hand to `SysBtlParam` when any override is set.  The new-game party is created first (the title's `init_party` would do it later).
pub fn party_overrides(data: &crate::data::BattleData, session: &mut GameSession) -> Option<(u8, [u8; 4])> {
    // `SH2_BATTLE_RECIPE=<name>`: the live capture agent's memory recipes (battle_live/INDEX.md "Memory recipe"), expanded into the
    // variables below (explicit variables win)
    let recipe = std::env::var("SH2_BATTLE_RECIPE").ok().and_then(|r| recipe(&r));
    let env_or = |key: &str, k: usize| std::env::var(key).ok().or_else(|| recipe.as_ref().and_then(|r| r[k].clone()));
    let party = env_or("SH2_BATTLE_PARTY", 0);
    let level = env_or("SH2_BATTLE_LEVEL", 1).and_then(|v| v.parse::<u8>().ok());
    let pokes: Vec<(String, String)> = [("SH2_BATTLE_SAVE", 2usize), ("SH2_BATTLE_MENU", 3)].iter().filter_map(|&(k, i)| env_or(k, i).map(|v| (k.to_string(), v))).collect();
    if party.is_none() && level.is_none() && pokes.is_empty() {
        return None;
    }
    if session.needs_party_init {
        crate::bridge::init_new_game(data, session);
    }
    let tbl = crate::bridge::level_table(data);
    let mut ids: Vec<u8> = session.battle_party();
    if let Some(p) = party {
        ids = p.split(',').filter_map(|s| s.trim().parse::<u8>().ok()).take(4).collect();
        for &pc in &ids {
            crate::bridge::ensure_pc(data, session, pc, &tbl);
        }
        session.set_party(&ids);
    }
    if let Some(lv) = level {
        for &pc in &ids {
            session.save.btl.pc_level_init(pc as usize, lv.max(1), &tbl);
        }
    }
    for (key, spec) in pokes {
        for item in spec.split(',') {
            let Some((off, hex)) = item.split_once(':') else { continue };
            let Ok(off) = usize::from_str_radix(off.trim().trim_start_matches("0x"), 16) else { continue };
            let bytes: Vec<u8> = (0..hex.trim().len() / 2).filter_map(|i| u8::from_str_radix(&hex.trim()[i * 2..i * 2 + 2], 16).ok()).collect();
            if key == "SH2_BATTLE_SAVE" && session.save.btl.is_retail() {
                // retail block offset: flush the working copy, poke, re-derive the working copy (the shared fields are mirrored both ways)
                session.save.btl.sync_to_retail();
                for (k, &b) in bytes.iter().enumerate() {
                    if let Some(d) = session.save.btl.retail.get_mut(off + k) {
                        *d = b;
                    }
                }
                if let Ok(fresh) = sh2_menu::save::BtlSave::from_retail_section(&session.save.btl.retail.clone()) {
                    session.save.btl = fresh;
                }
            } else if key == "SH2_BATTLE_MENU" {
                for (k, &b) in bytes.iter().enumerate() {
                    if let Some(d) = session.save.menu.data.get_mut(off + k) {
                        *d = b;
                    }
                }
            }
        }
    }
    let mut out = [0xffu8; 4];
    for (k, &pc) in ids.iter().take(4).enumerate() {
        out[k] = pc;
    }
    Some((ids.len().min(4) as u8, out))
}

/// `[party, level, SH2_BATTLE_SAVE, SH2_BATTLE_MENU]` of a named recipe: `yuri` / `vastitas` (Yuri, Karin, Lucia, Anastasia; fusions 0..2 +
/// Tsukiyomi / Jutendouji known at level 2), `lucia` (tarot bits, every oil, crest learned bits), `anastasia` (photo bits, crests),
/// `karin` (every Sword Art, bag 1), `blanca` (15 wolf bouts), `gepetto` (dress mask 3), `joachim` (Muscle Arts word), `kurando` /
/// `tsukiyomi` (Demon Morph), `nicolai` (the new game).  Offsets are the retail `BTL0` ones (bag 1 = `0xabc + 0x200`).
fn recipe(name: &str) -> Option<[Option<String>; 4]> {
    let crests = "e1c:ffffffffffffffffffffffffffffffffffffffff".to_string();
    let fus = "ec4:07006000,ec0:0c,f24:020202,f39:0202".to_string();
    let r = |p: &str, lv: Option<u8>, save: Option<String>, menu: Option<String>| Some([Some(p.to_string()), lv.map(|l| l.to_string()), save, menu]);
    match name {
        "yuri" | "vastitas" => r("0,5,3,4", Some(12), Some(fus), None),
        "lucia" => r("3,0,5,4", Some(12), Some(format!("f3f:ffff3f,f42:ff,{crests}")), None),
        "anastasia" => r("4,0,5,3", Some(12), Some(format!("fc3:ffffff,{crests}")), None),
        "karin" => r("5", None, Some("cff:f8,d00:1f".to_string()), None),
        "blanca" => r("1,2,6,7", Some(12), Some("fd7:0f".to_string()), None),
        "gepetto" => r("2,1,6,7", Some(12), None, Some("2fc:03000000".to_string())),
        "joachim" => r("6,1,2,7", Some(12), Some(format!("fcb:ff,{crests}")), None),
        "kurando" | "tsukiyomi" => r("7,1,2,6", Some(12), Some(fus), None),
        "nicolai" => r("5,11", None, None, None),
        _ => None,
    }
}

impl DevDrive {
    fn shot(&mut self, name: &str) {
        if self.shots.is_some() && self.taken.insert(name.to_string()) {
            self.seq += 1;
            self.queue.push(format!("bt_{:02}_{name}", self.seq));
        }
    }
    fn tap_bits(&mut self, bits: u16) -> u16 {
        self.tap += 1;
        if self.tap % 8 < 2 {
            bits
        } else {
            0
        }
    }
}

#[allow(clippy::too_many_arguments)]
fn drive(
    mut dd: ResMut<DevDrive>,
    scene: Res<State<Scene>>,
    mut session: ResMut<GameSession>,
    mut sys: ResMut<SshSys>,
    mut inj: ResMut<PadInjection>,
    rt: Option<ResMut<BattleRuntime>>,
    view: Res<BattleView>,
    ring: Res<RingView>,
    mut commands: Commands,
    mut exit: MessageWriter<AppExit>,
    cams: Query<(Entity, &Camera, Option<&Camera3d>, &GlobalTransform, Option<&Projection>)>,
    db: Option<Res<crate::plugin::BattleDb>>,
) {
    dd.ticks += 1;
    // hard frame cap (round 5 rule: every dev-drive run must end by itself): `SH2_BATTLE_MAX_TICKS`, default 30000 ticks (~8 min at 60 Hz)
    let cap = std::env::var("SH2_BATTLE_MAX_TICKS").ok().and_then(|v| v.parse::<u64>().ok()).unwrap_or(30_000);
    if dd.ticks > cap {
        log::warn!("devdrive: frame cap {cap} reached, exiting");
        exit.write(AppExit::Success);
        return;
    }
    inj.raw = 0;
    // screenshots queued by the previous frames
    if let Some(name) = dd.queue.pop() {
        if let Some(dir) = dd.shots.clone() {
            let _ = std::fs::create_dir_all(&dir);
            let path = dir.join(format!("{name}.png"));
            commands.spawn(Screenshot::primary_window()).observe(save_to_disk(path));
        }
    }
    match *scene.get() {
        Scene::Title if !dd.started && dd.ticks > 200 => {
            dd.started = true;
            session.new_game("AP_03_U");
            // retail: Karin + Nicolai (the new-game party); demo: Yuri, Ur, Blanca
            let (mut pc_count, mut pc) = if sh2_core::boot::is_retail() { (2, [5, 0xb, 0xff, 0xff]) } else { (3, [5, 0, 1, 0xff]) };
            if let Some(db) = db.as_ref() {
                if let Some((n, ids)) = party_overrides(&db.0, &mut session) {
                    pc_count = n;
                    pc = ids;
                }
            }
            let param = SysBtlParam { w0: dd.bg, regdat_id: dd.set as i32, bgm: 0x191, pc_count, monster_set: 1, pc };
            sys.start_battle(Some(param), Some("AP_03_U"));
            sys.start_battle(None, None);
        }
        Scene::Battle => {
            dd.battle_ticks += 1;
            let Some(mut rt) = rt else { return };
            let rt = &mut *rt;
            let lose = std::env::var_os("SH2_BATTLE_LOSE").is_some();
            // `SH2_BATTLE_LOSE`: the party falls as soon as the fight runs (phase 0x16 Lose -> game over -> title)
            if lose && dd.battle_ticks >= 150 && dd.go_ticks == 0 && matches!(rt.stage, Stage::Running) {
                dd.go_ticks = 1;
                for f in rt.battle.fighters.iter_mut().flatten().filter(|f| !f.is_enemy) {
                    f.hp = 0;
                }
                rt.menu = None;
                rt.battle.phase = Phase::Lose;
                rt.battle.step = 0;
            }
            // `SH2_BATTLE_KILL=<fighter>,..`: those fighters are out of the fight from the start (live comparisons with 1 / 2 enemies: place them far away with
            // `SH2_BATTLE_ENEMY_POS`, e.g. `9999,9999`)
            if dd.battle_ticks == 3 {
                if let Ok(list) = std::env::var("SH2_BATTLE_KILL") {
                    for i in list.split(',').filter_map(|s| s.trim().parse::<usize>().ok()) {
                        if let Some(Some(f)) = rt.battle.fighters.get_mut(i) {
                            f.hp = 0;
                            f.removed = true;
                        }
                    }
                }
            }
            if dd.battle_ticks == 40 || dd.battle_ticks == 41 {
                for (e, c, c3, t, p) in &cams {
                    log::info!("devdrive cam rot {:?} {e:?} order {} active {} 3d {} at {:?} proj {:?} target {:?}", t.rotation(), c.order, c.is_active, c3.is_some(), t.translation(), p.map(|p| match p { Projection::Perspective(p) => format!("persp fov {} near {} far {}", p.fov, p.near, p.far), _ => "other".into() }), c.viewport.as_ref().map(|v| (v.physical_position, v.physical_size)));
                }
            }
            if view.stage == "intro" && dd.battle_ticks == 40 {
                log::info!("devdrive intro pose eye {:?} look {:?} fov {} positions {:?}", rt.cam.pose.eye, rt.cam.pose.look_at, rt.cam.pose.fov_scale, rt.positions);
                dd.shot("intro");
            }
            let frozen = std::env::var_os("SH2_BATTLE_FXLIST").is_some() || std::env::var_os("SH2_BATTLE_CAMLIST").is_some();
            if let (Some(m), false) = (&rt.menu, frozen) {
                // the next command of the script (a command whose root entry this character lacks is skipped)
                let root_of = |cmd: &str, roots: &[Root]| match cmd {
                    "item" => Root::Item,
                    "magic" if roots.contains(&Root::Magic) => Root::Magic,
                    "magic" | "skill" => Root::Skill,
                    "guard" => Root::Guard,
                    "fusion" => Root::Fusion,
                    "link" => Root::Link,
                    "run" => Root::Run,
                    "tarot" => Root::Tarot,
                    "aroma" => Root::Aroma,
                    "snap" => Root::Snap,
                    _ => Root::Attack,
                };
                for _ in 0..dd.cmds.len() {
                    let cmd = dd.cmds[dd.turn % dd.cmds.len()].clone();
                    // (a greyed `Tarot Card` entry -- a card is already active -- is skipped like a missing one)
                    if m.roots.contains(&root_of(&cmd, &m.roots)) && !(cmd == "tarot" && rt.battle.tarot.menu_locked(None)) {
                        break;
                    }
                    dd.turn += 1;
                }
                let cmd = dd.cmds[dd.turn % dd.cmds.len()].clone();
                let want = match cmd.as_str() {
                    "item" => Root::Item,
                    // `magic` = the crest magic page, or the character's special page (White Magic ...) when there is none
                    "magic" if m.roots.contains(&Root::Magic) => Root::Magic,
                    "magic" | "skill" => Root::Skill,
                    "guard" => Root::Guard,
                    "fusion" => Root::Fusion,
                    "link" => Root::Link,
                    "run" => Root::Run,
                    "tarot" => Root::Tarot,
                    "aroma" => Root::Aroma,
                    "snap" => Root::Snap,
                    _ => Root::Attack,
                };
                if rt.battle.actor != dd.last_menu_actor {
                    dd.last_menu_actor = rt.battle.actor;
                    dd.tap = 0;
                }
                let page = m.page().clone();
                let key = format!("{:?}{:?}", std::mem::discriminant(&page), rt.battle.actor);
                if key != dd.page_key {
                    dd.page_key = key;
                    dd.page_age = 0;
                }
                dd.page_age += 1;
                if matches!(page, Page::Main) {
                    if dd.page_age == 70 && !dd.taken.contains("command_menu") {
                        log::info!("devdrive pose actor {:?} eye {:?} look {:?} fov {} positions {:?}", rt.battle.actor, rt.cam.pose.eye, rt.cam.pose.look_at, rt.cam.pose.fov_scale, rt.positions);
                    }
                    let age: u32 = std::env::var("SH2_BATTLE_MENU_AGE").ok().and_then(|v| v.parse().ok()).unwrap_or(70);
                    if dd.page_age == age {
                        dd.shot("command_menu");
                        // the fused character's own root menu (live `08h` / `17k`)
                        if rt.battle.actor.and_then(|a| rt.battle.fused.get(a).and_then(|s| s.as_ref())).is_some() {
                            dd.shot("fused_menu");
                        }
                    }
                }
                // every sub-menu page is photographed once it has settled (`SH2_BATTLE_MENU_AGE`, default 70 ticks)
                let shot_age: u32 = std::env::var("SH2_BATTLE_MENU_AGE").ok().and_then(|v| v.parse().ok()).unwrap_or(70);
                let page_shot = match &page {
                    Page::Item => Some("item_menu"),
                    Page::Magic => Some("magic_menu"),
                    Page::Skill => Some("skill_menu"),
                    Page::Fusion => Some("fusion_menu"),
                    Page::Guard => Some("guard_menu"),
                    Page::Aroma => Some("aroma_menu"),
                    Page::Aroma2 { .. } => Some("aroma2_menu"),
                    Page::Target { then, .. } => Some(match then {
                        crate::ui::Pending::Attack(_) => "target_select",
                        crate::ui::Pending::Item(_) => "ally_target",
                        crate::ui::Pending::Link => "link_target",
                        crate::ui::Pending::Magic(_) => "magic_target",
                        crate::ui::Pending::Skill(_) => "skill_target",
                        crate::ui::Pending::Snap => "snap_target",
                    }),
                    _ => None,
                };
                if let (Some(name), true) = (page_shot, dd.page_age == shot_age) {
                    dd.shot(name);
                }
                // the command window entering from the left (`hud::MENU_DELAY` 0.3 s + ~0.05 s of the slide)
                if matches!(page, Page::Main) && dd.page_age == 14 {
                    dd.shot("menu_slide_in");
                }
                if matches!(page, Page::Main) && m.cursor() >= 4 {
                    dd.shot("menu_page2");
                }
                // `SH2_BATTLE_HUD_DEMO=<page>`: the provisional page overlay (`hud::apply_demo`) photographed once the menu has settled
                if let (Ok(demo), true) = (std::env::var("SH2_BATTLE_HUD_DEMO"), matches!(page, Page::Main) && dd.page_age == shot_age + 5) {
                    dd.shot(&format!("demo_{demo}"));
                }
                // wait a moment on each page so that screenshots show it
                let hold_age: u32 = shot_age + 10;
                let hold = dd.page_age < hold_age.max(80) && dd.taken.len() < 14;
                if !hold {
                    inj.raw = match page {
                        Page::Main => {
                            let idx = m.roots.iter().position(|r| *r == want).unwrap_or(0);
                            if m.cursor() < idx {
                                dd.tap_bits(padbit::DOWN)
                            } else if m.cursor() > idx {
                                dd.tap_bits(padbit::UP)
                            } else {
                                dd.tap_bits(padbit::CIRCLE)
                            }
                        }
                        // `SH2_BATTLE_TARGET_ROW=<n>`: walk a target page down to row `n` first (e.g. Snap Shot on the 4th monster)
                        Page::Target { .. } if m.cursor() < std::env::var("SH2_BATTLE_TARGET_ROW").ok().and_then(|v| v.parse().ok()).unwrap_or(0) => dd.tap_bits(padbit::DOWN),
                        Page::Target { .. } => dd.tap_bits(padbit::CIRCLE),
                        // sub-menu: confirm; when the entry refuses (no valid target, too expensive) step to the next one, and give the page up
                        // after 400 ticks (back to the root, next command of the script)
                        _ => {
                            let k = (dd.page_age.saturating_sub(hold_age)) / 8;
                            // `SH2_BATTLE_PICK=<n>`: walk the cursor down to row `n` of a sub-menu first (e.g. Blessed Light = `magic` + 1)
                            let pick: usize = std::env::var("SH2_BATTLE_PICK").ok().and_then(|v| v.parse().ok()).unwrap_or(0);
                            if m.cursor() < pick && matches!(page, Page::Magic | Page::Skill | Page::Item) {
                                dd.tap_bits(padbit::DOWN)
                            } else if dd.page_age > hold_age + 400 {
                                dd.turn += 1;
                                dd.tap_bits(padbit::CROSS)
                            } else if k % 3 == 2 {
                                dd.tap_bits(padbit::DOWN)
                            } else {
                                dd.tap_bits(padbit::CIRCLE)
                            }
                        }
                    };
                }
                // the script advances once the command is committed (target confirmed, or a page that reports directly)
                if inj.raw & padbit::CIRCLE != 0 && (matches!(page, Page::Target { .. } | Page::Guard | Page::Fusion | Page::Aroma2 { .. }) || (matches!(page, Page::Main) && want == Root::Tarot && m.roots.get(m.cursor()) == Some(&Root::Tarot))) && dd.last_commit != dd.page_key {
                    dd.last_commit = dd.page_key.clone();
                    dd.turn += 1;
                }
            }
            if !rt.battle.combo.is_empty() && matches!(rt.stage, Stage::Running) && rt.menu.is_none() {
                dd.shot("combo_form");
            }
            // Lucia's `Tarot Card` (`SH2_BATTLE_CMDS=tarot`, recipe `lucia`): photographs of every stage of the command; the stop press comes
            // `SH2_TAROT_STOP` seconds into the spin (default 0.6), the result window is confirmed after 0.6 s
            if dd.tarot_press > 0 {
                dd.tarot_press -= 1;
                inj.raw = padbit::CIRCLE;
            }
            if rt.battle.phase == Phase::Tarot {
                dd.tarot_age += 1;
                if let Some(ui) = rt.tarot_ui.as_ref() {
                    use crate::tarot::ShowStage as S;
                    let stop_at: f32 = std::env::var("SH2_TAROT_STOP").ok().and_then(|v| v.parse().ok()).unwrap_or(0.6);
                    let st = ui.show.stage;
                    if matches!(st, S::Intro(t) if t < 0.3) {
                        dd.shot("tarot_0_name_window");
                    }
                    if matches!(st, S::Intro(t) if t > 1.2) {
                        dd.shot("tarot_1_sweep");
                    }
                    if let S::Spin(t) = st {
                        if t > 0.3 {
                            dd.shot("tarot_2_row");
                        }
                        if t >= stop_at && !dd.tarot_stop_sent {
                            dd.tarot_stop_sent = true;
                            dd.tarot_press = 3;
                        }
                    }
                    if matches!(st, S::Picked(t) if t > 0.3) {
                        dd.shot("tarot_3_picked");
                    }
                    if matches!(st, S::Flip(t) if t > 0.2) {
                        dd.shot("tarot_4_flip");
                    }
                    if let S::Result(t) = st {
                        if t > 0.3 {
                            dd.shot("tarot_5_result");
                        }
                        if t > 0.6 && !dd.tarot_result_sent {
                            dd.tarot_result_sent = true;
                            dd.tarot_press = 3;
                        }
                    }
                    if matches!(st, S::Fade(t) if t > 0.4) {
                        dd.shot("tarot_6_white");
                    }
                    if matches!(st, S::Effect(t) if t > 0.1) {
                        dd.shot("tarot_7_effect");
                    }
                    if matches!(st, S::Applied(t) if t > 0.4) {
                        dd.shot("tarot_8_result_window");
                    }
                    if matches!(st, S::Applied(t) if t > 1.2) {
                        dd.shot("tarot_9_after");
                    }
                    // a second ring after Judgment
                    if matches!(ui.show.stage, S::Intro(_)) && ui.show.redrawn {
                        dd.tarot_stop_sent = false;
                        dd.tarot_result_sent = false;
                    }
                }
            } else {
                dd.tarot_age = 0;
                dd.tarot_stop_sent = false;
                dd.tarot_result_sent = false;
            }
            // the Turn Priority plate / party panel sliding in at the start of a command phase
            if rt.hud_since.map(|t| rt.ticks == t + 3).unwrap_or(false) {
                dd.shot("hud_slide_in");
            }
            if !ring.active {
                dd.ring_age = 0;
            }
            if ring.active {
                dd.ring_age += 1;
                if dd.ring_age == 30 {
                    dd.shot(if matches!(rt.battle.phase, Phase::Attack) { "judgement_ring" } else { "effect_ring" });
                }
                // the ring after its 0.8 s intro, pointer under way
                if dd.ring_age == 75 {
                    dd.shot("judgement_ring_run");
                }
                if ring.in_zone {
                    inj.raw = dd.tap_bits(padbit::CIRCLE);
                }
            }
            // fusion sequence photographs (`fusion_<n>.png`, every 0.5 s while the transformation runs and 4 s after it)
            if rt.battle.phase == Phase::Fusion || (dd.fus_age > 0 && dd.fus_age < 60 * 8) {
                dd.fus_age += 1;
                if dd.fus_age > 60 * 8 - 20 {
                    dd.taken.insert("fusion_end".to_string());
                }
                if dd.fus_age % 30 == 15 {
                    if let Some(dir) = std::env::var_os("SH2_BATTLE_FXSHOTS").map(std::path::PathBuf::from) {
                        let _ = std::fs::create_dir_all(&dir);
                        commands.spawn(Screenshot::primary_window()).observe(save_to_disk(dir.join(format!("fusion_{:02}.png", dd.fus_age / 30))));
                    }
                }
            }
            // `SH2_BATTLE_CAMLIST`: photograph every requested camera once it has settled
            if let Some(name) = crate::plugin::dev_camera_name(&rt) {
                let secs: f32 = std::env::var("SH2_BATTLE_CAMSECS").ok().and_then(|v| v.parse().ok()).unwrap_or(3.0);
                let phase = (rt.ticks as f32 / 60.0) % secs;
                if phase > secs * 0.8 {
                    if let Some(dir) = std::env::var_os("SH2_BATTLE_FXSHOTS").map(std::path::PathBuf::from) {
                        if dd.taken.insert(format!("cam_{name}")) {
                            let _ = std::fs::create_dir_all(&dir);
                            commands.spawn(Screenshot::primary_window()).observe(save_to_disk(dir.join(format!("cam_{name}.png"))));
                        }
                    }
                }
            }
            if let Some(fx) = &rt.fx {
                if fx.prog.ticks > 6 {
                    dd.shot("effect");
                }
                // `SH2_BATTLE_FXSHOTS=<dir>`: a series of photographs of every effect (`fx_<id>_<tick>.png`)
                if let Some(dir) = std::env::var_os("SH2_BATTLE_FXSHOTS").map(std::path::PathBuf::from) {
                    let every: u32 = std::env::var("SH2_BATTLE_FXEVERY").ok().and_then(|s| s.parse().ok()).unwrap_or(8);
                    let t = fx.prog.ticks;
                    if t >= 3 && (t - 3) % every == 0 && dd.taken.insert(format!("fx_{}_{}", fx.prog.id, t)) {
                        let _ = std::fs::create_dir_all(&dir);
                        commands.spawn(Screenshot::primary_window()).observe(save_to_disk(dir.join(format!("fx_{:03}_{:03}.png", fx.prog.id, t))));
                    }
                }
            }
            if rt.spark_count() > 0 {
                dd.shot("weapon_hit");
            }
            // the total hit panel / counter once the floating numbers have gone (`hud_hits`)
            if !rt.hits.panels.is_empty() && rt.hits.texts.is_empty() && rt.hits.counters.is_empty() && rt.hits.panels.iter().all(|p| p.t > 0.4 && !p.closing) {
                dd.shot("hit_panel");
            }
            // the ring's `Good!!` / `Strike!!` sprite (`HitMes`) a few frames after a press
            if rt.hits.ring_mes.iter().any(|m| m.t > 0.25 && m.t < 0.3) {
                dd.shot("ring_hit");
            }
            // `Defeat` (type 4 spin-in) and the green `HP +n` (type 7) texts once they have settled
            if rt.hits.texts.iter().any(|t| t.kind == 4 && t.t > 0.3 && t.t < 0.4) {
                dd.shot("defeat_text");
            }
            if rt.hits.texts.iter().any(|t| t.kind == 7 && t.t > 0.3 && t.t < 0.4) {
                dd.shot("heal_text");
            }
            // the win / lose / escape sequences (`hud_result`): one photograph per stage
            match &rt.stage {
                Stage::Result { seq, .. } => match &seq.state {
                    WinState::Pose if seq.t > 1.2 => dd.shot("win_pose"),
                    WinState::Bonus(p) if p.phase == BonusPhase::Hold => dd.shot("battle_bonus"),
                    WinState::Screen(s) if s.phase == ResultPhase::Count && s.ticks > 60 => dd.shot("result_count"),
                    // `SH2_BATTLE_RESULT_SERIES=1`: one photograph every 30 ticks of the count-up (counts / `Level Up!` flip)
                    WinState::Screen(s) if std::env::var_os("SH2_BATTLE_RESULT_SERIES").is_some() && s.ticks % 30 == 5 => dd.shot(&format!("result_t{:03}", s.ticks)),
                    // the result screen waits for the button (`[x]:End`): photograph it, then confirm
                    WinState::Screen(s) if s.phase == ResultPhase::WaitEnd => {
                        dd.shot("result_end");
                        dd.exit_wait += 1;
                        if dd.exit_wait > 90 {
                            inj.raw = padbit::CIRCLE;
                        }
                    }
                    _ => {}
                },
                Stage::Defeat(seq) if seq.t > 2.0 => dd.shot("defeat"),
                Stage::Escaped(seq) => {
                    if seq.panel.is_none() && seq.t > 1.0 {
                        dd.shot("escape_message");
                    }
                    if seq.panel.as_ref().map(|p| p.phase == BonusPhase::Hold).unwrap_or(false) {
                        dd.shot("escape_panel");
                    }
                }
                _ => {}
            }
            if rt.hud_since.map(|t| rt.ticks == t + 20).unwrap_or(false) && rt.battle.actor.map(|a| rt.battle.fighters[a].as_ref().map(|f| f.is_enemy).unwrap_or(false)).unwrap_or(false) {
                dd.shot("enemy_turn");
            }
            let cam_done = std::env::var("SH2_BATTLE_CAMLIST").ok().map(|l| { let n = l.split(',').count(); let secs: f32 = std::env::var("SH2_BATTLE_CAMSECS").ok().and_then(|v| v.parse().ok()).unwrap_or(3.0); rt.ticks as f32 / 60.0 > secs * (n as f32 + 2.0) }).unwrap_or(false);
            let fx_done = cam_done || std::env::var_os("SH2_BATTLE_FXLIST").is_some() && frozen && rt.fx.is_none() && rt.fx_started as usize >= std::env::var("SH2_BATTLE_FXLIST").map(|l| l.split(',').count()).unwrap_or(0) && dd.battle_ticks > 400;
            // `SH2_BATTLE_EXIT_AFTER=<shot>`: leave a little after that photograph was taken (fast stage / camera tours)
            if let Ok(n) = std::env::var("SH2_BATTLE_EXIT_AFTER") {
                if dd.taken.contains(&n) && dd.queue.is_empty() {
                    dd.exit_wait += 1;
                    if dd.exit_wait > 45 {
                        exit.write(AppExit::Success);
                    }
                }
            }
            if dd.battle_ticks > 60 * 150 || (view.stage == "left" && !lose) || fx_done {
                log::info!("devdrive: done after {} battle ticks, shots {:?}, fx started {} hits {}", dd.battle_ticks, dd.taken, rt.fx_started, rt.fx_hits);
                if dd.queue.is_empty() {
                    exit.write(AppExit::Success);
                }
            }
        }
        Scene::GameOver => {
            // `SH2_BATTLE_LOSE`: photograph the game-over screen, confirm it, leave once the title is back
            dd.go_ticks += 1;
            if dd.go_ticks == 120 {
                dd.shot("game_over");
            }
            if dd.go_ticks > 200 && dd.go_ticks % 40 == 0 {
                inj.raw = padbit::CIRCLE;
            }
            if dd.go_ticks > 900 {
                exit.write(AppExit::Success);
            }
        }
        Scene::Title if dd.started && dd.go_ticks > 1 => {
            dd.go_ticks += 1;
            if dd.go_ticks > 300 && dd.queue.is_empty() {
                log::info!("devdrive: game over returned to the title");
                exit.write(AppExit::Success);
            }
        }
        _ => {}
    }
}

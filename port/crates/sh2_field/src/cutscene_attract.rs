//! The retail attract-mode battle (`openingBattleDemo`, US main image 0x00416510..0x00416ed0, notes/I/opening.md section 7), run through the
//! battle plugin.
//!
//! The retail title asks for it after 1201 idle frames on PRESS START / 3600 on the menu ([`AttractRequest`], the entry comes from the rotation
//! table `AttractSelector`).  This module
//!
//! 1. builds the party of the table entry (`SaveMenuSection::JoinBattle` + `FUN_003c02f0(member, scenario)`: the equipment / level preset of the
//!    story chapter `scenario`) in a fresh [`GameSession`] and starts `BtlSocket` with the monster set (`SetMonsterSet(RegDat(0x35, set))`) and the
//!    battle BGM,
//! 2. plays the party with the pad (the demo is driven by the original's demo AI; here the command menu is answered with attack / target / ring
//!    taps, like the dev driver of the battle crate), shows the logo banner (`opening.dat` #19),
//! 3. ends after 2700 frames (45 s) or when the battle is over, or 60+ frames after any key (`not_skipped = 0`), and requests the title again
//!    (`SSHSys::RequestTitle`, `opening(not_skipped)`): [`AttractReturn`] tells the title whether to replay the opening movie.
//!
//! The party levels are an estimate (the preset function was not decompiled): chapter 0..5 -> level 4, 12, 20, 28, 36, 44.

use ::bevy::prelude::*;
use sh2_battle::data::SEC_PC_INIT;
use sh2_battle::plugin::{BattleDb, BattleView, RingView};
use sh2_core::game::{padbit, GamePad, GameSet, PadInjection, Scene};
use sh2_core::ssh_sys::{SshSys, SysBtlParam};
use sh2_menu::bevy_ui::CanvasRoot;
use sh2_menu::session::GameSession;
use sh2_menu::title_retail_plugin::{AttractRequest, AttractReturn, RetailArt};

/// Frames the demo battle may run (`0xa8c`).
pub const MAX_FRAMES: u32 = 2700;
/// A key cuts the demo short only after this many frames.
pub const SKIP_AFTER: u32 = 60;

#[derive(Resource, Debug, Default)]
pub struct AttractRun {
    pub frames: u32,
    pub skipped: bool,
    pub ended: bool,
    tap: u32,
}

/// Party level of the story chapter of an attract entry (`scenario` 0..5).
pub fn level_for(scenario: i16) -> u8 {
    [4u8, 12, 20, 28, 36, 44][scenario.clamp(0, 5) as usize]
}

#[derive(Component)]
struct AttractBanner;

#[allow(clippy::too_many_arguments)]
fn start_attract(
    mut commands: Commands,
    req: Option<Res<AttractRequest>>,
    db: Option<Res<BattleDb>>,
    mut session: ResMut<GameSession>,
    mut sys: ResMut<SshSys>,
    scene: Res<State<Scene>>,
    mut ret: ResMut<AttractReturn>,
    art: Res<RetailArt>,
) {
    let Some(req) = req else { return };
    if *scene.get() != Scene::Title {
        return;
    }
    let Some(db) = db else {
        warn!("attract: no battle database, skipping the demo");
        commands.remove_resource::<AttractRequest>();
        ret.0 = Some(false);
        return;
    };
    commands.remove_resource::<AttractRequest>();
    let e = req.entry;
    // a throw-away game: the demo's party at the level of its chapter (the title's session is replaced when a game starts anyway)
    *session = GameSession::default();
    session.new_game("OP_00_U");
    let tbl = sh2_battle::bridge::level_table(&db.0);
    let level = level_for(e.scenario);
    let mut ids: Vec<u8> = Vec::new();
    for &pc in e.party.iter().filter(|&&p| p >= 0) {
        let pc = pc as usize;
        let Some(pc_i) = db.0.dat.record(SEC_PC_INIT[3], pc, 0x1c) else {
            warn!("attract: no PC_I record for party member {pc}");
            continue;
        };
        let name = db.0.mes.record(3, pc, 18).unwrap_or(&[]);
        session.init_pc(pc, pc_i, name, &tbl);
        session.save.btl.pc_level_init(pc, level, &tbl);
        ids.push(pc as u8);
    }
    session.set_party(&ids);
    session.needs_party_init = false;
    session.in_game = false;
    let mut pc = [0xffu8; 4];
    for (i, id) in ids.iter().take(4).enumerate() {
        pc[i] = *id;
    }
    // the banner `prim2D` (opening.dat #19, 216x120) in the corner
    if art.loaded {
        commands
            .spawn((
                AttractBanner,
                CanvasRoot(201),
                Node { position_type: PositionType::Absolute, left: px(0), top: px(0), width: px(512), height: px(448), overflow: Overflow::clip(), ..default() },
                GlobalZIndex(500),
                DespawnOnExit(Scene::Battle),
            ))
            .with_children(|p| {
                p.spawn((Node { position_type: PositionType::Absolute, left: px(4), top: px(326), width: px(216), height: px(120), ..default() }, ImageNode::new(art.banner.clone()).with_color(Color::srgba(1.0, 1.0, 1.0, 0.85))));
            });
    }
    let param = SysBtlParam { w0: 0, regdat_id: e.monster_set as i32, bgm: e.bgm as u16, pc_count: ids.len().min(4) as u8, monster_set: 1, pc };
    info!("attract: battle {} monster set {} party {:?} level {level} bgm {}", e.battle, e.monster_set, ids, e.bgm);
    // `BtlSocket::SetMonsterSet`; the field to return to is none: the run ends with a title request
    sys.start_battle(Some(param), Some(""));
    sys.start_battle(None, None);
    commands.insert_resource(AttractRun::default());
}

/// Plays the demo: answers the command menu / judgement ring with taps, watches the end conditions.
#[allow(clippy::too_many_arguments)]
fn drive_attract(
    run: Option<ResMut<AttractRun>>,
    scene: Res<State<Scene>>,
    keys: Option<Res<ButtonInput<KeyCode>>>,
    pad: Res<GamePad>,
    mut inj: ResMut<PadInjection>,
    mut sys: ResMut<SshSys>,
    report: Res<sh2_core::game::BattleReport>,
    ring: Res<RingView>,
    view: Res<BattleView>,
    mut commands: Commands,
    mut ret: ResMut<AttractReturn>,
    mut session: ResMut<GameSession>,
) {
    let Some(mut run) = run else { return };
    if run.ended {
        return;
    }
    if *scene.get() != Scene::Battle {
        return;
    }
    run.frames += 1;
    // the injection is this module's own; a real key (keyboard / pad without the injection) cuts the demo short
    let real = keys.map(|k| k.get_just_pressed().next().is_some()).unwrap_or(false) || (pad.real() & !inj.raw) != 0;
    inj.raw = 0;
    if real && run.frames > SKIP_AFTER {
        run.skipped = true;
    }
    // like the autoplayer: confirm while a menu / the result is up, press O once when the ring pointer is in the zone
    run.tap += 1;
    let tap = run.tap % 10 < 3;
    let press = if ring.active {
        ring.in_zone && run.tap % 4 == 0
    } else {
        (view.menu_open && view.stage == "running") || view.result_shown || view.stage == "defeat"
    } && (ring.active || tap);
    if press {
        inj.raw = padbit::CIRCLE;
    }
    let over = report.pending;
    if run.skipped || over || run.frames >= MAX_FRAMES {
        run.ended = true;
        inj.raw = 0;
        info!("attract: ended after {} frames (skipped {}, battle over {})", run.frames, run.skipped, over);
        ret.0 = Some(!run.skipped);
        // `SSHSys::RequestTitle` overrides whatever the battle callback asked for (field / game over)
        sys.request_title();
        commands.remove_resource::<AttractRun>();
        *session = GameSession::default();
    }
}

pub struct AttractPlugin;

impl Plugin for AttractPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<AttractReturn>().init_resource::<RetailArt>().add_systems(Update, start_attract.run_if(resource_exists::<AttractRequest>))
            .add_systems(FixedUpdate, drive_attract.in_set(GameSet::Camera).run_if(resource_exists::<AttractRun>));
    }
}

//! Story progression on the US retail disc (`SH2_US_DISC_DIR`; skipped when unset): party changes, battle results, map hand-overs and the
//! headless story walker (`sh2_field::story`).  See notes/integration/r5_fs.md.
use sh2_field::host::{tick_state, FieldHost, PartyOp};
use sh2_field::pkb_compat::PkbSet;
use sh2_field::plugin::{build_runtime, FieldRuntime};
use sh2_menu::session::GameSession;

fn us() -> Option<PkbSet> {
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    PkbSet::open(std::env::var_os("SH2_US_DISC_DIR")?).ok()
}

fn step(rt: &mut FieldRuntime, session: &mut GameSession, tick: u32) {
    let press = if tick % 12 == 0 { sh2_core::game::padbit::CIRCLE } else { 0 };
    rt.st.press = press;
    tick_state(&mut rt.st, &mut rt.sim);
    rt.sim.update_camera();
    for (id, args) in std::mem::take(&mut rt.st.event_queue) {
        rt.vm.call_event(id, &args);
    }
    rt.vm.set_pad(sh2_script::cscript::PadState { raw: press as u32, new_press: press as u32, repeat: 0, consumed: 0 });
    rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(session) });
    rt.st.faders.clear();
    rt.st.audio.clear();
    rt.st.menu_wait = false;
    rt.st.menu_req = None;
}

/// AR_15_U, first visit: the story-party preset (shared function 0x316e, `SetFieldData` 0x13 / 0x14 / 0x0b / 0x16) forms Yuri's party:
/// `SceneInit(1)`, Karin and Nicolai leave set 3, Yuri (0), Blanca (2) and Gepetto (1) join it and the battle team, set 3 becomes current.
#[test]
fn ar_15_u_forms_yuris_party() {
    let Some(pkb) = us() else { return };
    let mut s = GameSession::default();
    s.new_game("AR_15_U");
    let mut rt = build_runtime(&pkb, None, "AR_15_U", 0, &s).unwrap();
    for t in 0..3000 {
        step(&mut rt, &mut s, t);
        if rt.st.pending_jump.is_some() {
            break;
        }
    }
    assert_eq!(rt.st.pending_jump.as_ref().map(|j| j.0.as_str()), Some("AR_00_U"));
    assert!(rt.st.party_ops.contains(&PartyOp::SceneInit(1)), "{:?}", rt.st.party_ops);
    assert_eq!(s.save.menu.current_set_index(), 3);
    let set = s.save.menu.party_set(3).unwrap();
    let members: Vec<u8> = set.members[..set.member_count as usize].to_vec();
    assert_eq!(members, vec![0, 2, 1]);
    assert_eq!(set.battle_count, 3);
}

/// `JoinBattle` (US 0x00287770) moves a member to the end of the battle team.
#[test]
fn join_battle_moves_the_member_behind_the_fighters() {
    let mut s = GameSession::default();
    let mut p = s.save.menu.party_set(0).unwrap();
    p.member_count = 0;
    p.battle_count = 0;
    p.battle_max = 3;
    for pc in [0u8, 1, 2, 6] {
        p.join(pc);
    }
    assert!(sh2_field::host::join_battle(&mut p, 6, true));
    assert!(sh2_field::host::join_battle(&mut p, 1, false));
    assert_eq!(&p.members[..4], &[6, 1, 0, 2]);
    assert_eq!(p.battle_count, 2);
    assert_eq!(p.pinned_mask, 1 << 6);
    s.save.menu.set_party_set(0, &p);
}

/// `GetCharacterInfo(slot, 0xd)` = index of the playing motion in the standard table (US 0x00509c40).
#[test]
fn standard_motion_index_matches_the_table() {
    use sh2_field::host::standard_motion_index;
    assert_eq!(standard_motion_index(1, ""), 1);
    assert_eq!(standard_motion_index(0, "TA_C"), 12);
    assert_eq!(standard_motion_index(0, "TA_D"), 0);
    assert_eq!(standard_motion_index(0x1234567, ""), 0);
}

/// IF_11_U waits for Karin's one-shot motion to fall back to `fidl` (`while (GetCharacterInfo(0, 0xd) != 1)`); the port returned the motion
/// id for ever and the start function hung (the coverage run's IF_11_U failure).
#[test]
fn if_11_u_start_scene_runs_to_its_end() {
    let Some(pkb) = us() else { return };
    let mut s = GameSession::default();
    let mut rt = build_runtime(&pkb, None, "IF_11_U", 0, &s).unwrap();
    for t in 0..3000 {
        step(&mut rt, &mut s, t);
        if rt.st.pending_jump.is_some() {
            break;
        }
    }
    assert!(rt.st.pending_jump.is_some(), "the scene ends with a map jump; last calls {:?}", &rt.st.log[rt.st.log.len().saturating_sub(8)..]);
}

/// Headless walk from the new game: Apoina, Domremy, the Ardennes Forest (boss, `N013` renames the socket's map -> `HUB_NA`), Paris.
/// Release build ~1 min: `cargo test --release -p sh2_field --test retail_story -- --ignored`.
#[test]
#[ignore]
fn story_walk_reaches_paris() {
    if us().is_none() {
        return;
    }
    let env = sh2_field::story::Env::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let game = sh2_field::story::Game::new_game(&env, "OP_00_U", 0).unwrap();
    let mut w = sh2_field::story::Walker::new(&env, game);
    w.run(260);
    let regs = w.game.regs();
    for f in [9u32, 0xa, 0xb, 0xc] {
        assert!(sh2_field::story::flag(&regs, f), "story flag {f:#x} ({:?}) not reached; stuck: {:?}", sh2_field::story::story_flag_name(f), w.stuck);
    }
}

/// The ending (`ED_00_U`): the final battle (BBTL 0x85 = monster set 302), the ending films, the clear save and `SpecialMenu(0x700)` -- the
/// hand-over to the title (US 0x004faab0, `CField+0x178` delete reason 2).
#[test]
fn ed_00_u_ends_the_game() {
    if us().is_none() {
        return;
    }
    let env = sh2_field::story::Env::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let mut s = GameSession::default();
    s.new_game("ED_00_U");
    let game = sh2_field::story::Game::enter(&env, s, "ED_00_U", 0).unwrap();
    let mut w = sh2_field::story::Walker::new(&env, game);
    w.run(5);
    assert!(w.battles.iter().any(|b| b.1 == 302 && b.2), "final boss: {:?}", w.battles);
    assert!(w.ended, "the walk reaches the ending hand-over: {:?}", w.steps.iter().map(|s| &s.what).collect::<Vec<_>>());
}

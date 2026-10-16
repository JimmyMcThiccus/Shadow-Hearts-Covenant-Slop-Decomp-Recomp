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

fn walk_env() -> Option<sh2_field::story::Env> {
    us()?;
    sh2_field::story::Env::open(std::env::var_os("SH2_US_DISC_DIR")?)
}

fn fixture(name: &str) -> std::path::PathBuf {
    std::path::Path::new(env!("CARGO_MANIFEST_DIR")).join("tests/walk").join(name)
}

/// TD_14_U, Todo lab shooting range ("destroy the 30 targets"): the walker presses the button of the lane the script itself accepts
/// (`0x79a7`: lane state 4 / 5, lane button mask) and nothing else, so no press scores a miss.
#[test]
fn td_14_u_shooting_range_has_no_miss() {
    let Some(env) = walk_env() else { return };
    let mut g = sh2_field::story::Game::resume(&env, &fixture("td_14_u_range.walk")).unwrap();
    let mut pol = sh2_field::story::Policy::default();
    let mut texts = vec![];
    let mut stop = None;
    for _ in 0..8000 {
        if let Some(s) = g.tick(&mut pol) {
            stop = Some(s);
            break;
        }
        for w in g.rt.st.ui.windows.iter().filter(|w| w.is_open() && !w.raw.is_empty()) {
            let t = String::from_utf8_lossy(&w.raw).to_string();
            if !texts.contains(&t) {
                texts.push(t);
            }
        }
        if g.is_free() {
            stop = Some(sh2_field::story::Stop::Free);
            break;
        }
    }
    assert_eq!(stop, Some(sh2_field::story::Stop::Free), "texts {texts:?}");
    assert!(texts.iter().any(|t| t.contains("30 targets")), "the range ran: {texts:?}");
    assert!(!texts.iter().any(|t| t.contains("aiming at")), "a press missed: {texts:?}");
}

/// GT_10_U, pit fights: `GetFieldData(0x26, ..)` (US 0x004fc418) answers from `GetRegDat(0x53)` (the retail `SSHMES.NA` / `SSHDAT.NA`
/// pair the field tables now carry) instead of -1, so the arena's talks no longer loop.
#[test]
fn gt_10_u_pit_fight_table_answers() {
    let Some(env) = walk_env() else { return };
    let rd = env.tables.us_rd.clone().expect("retail RegDat pair");
    let db = sh2_core::regdat::UsRegDat::new(&rd.0, &rd.1).unwrap();
    let n = db.count(0x53, 0).expect("pit-fight records");
    assert!(n > 0);
    // every record answers every field; field 1 (rank, +6 & 7) is 0..7, an unknown field / record is -1
    for rec in 0..n {
        assert!((0..8).contains(&sh2_field::host::pit_fight_field(&db, rec, 1)), "record {rec}");
    }
    assert_eq!(sh2_field::host::pit_fight_field(&db, 0, 0), -1);
    assert_eq!(sh2_field::host::pit_fight_field(&db, 0, 10), -1);
}

/// Mt. Fuji (flag 0x4c): the crystal gates.  The puzzle search ([`Walker::search`]) finds the way from the mountain's foot: collect the
/// three crystals (FU_01 / FU_02 / FU_04), put crystal 4 into FU_06_U's gate, FU_12 .. FU_18_U.  Release build, ~15 min:
/// `cargo test --release -p sh2_field --test retail_story -- --ignored fuji`.
#[test]
#[ignore]
fn fuji_crystal_search_reaches_mt_fuji() {
    let Some(env) = walk_env() else { return };
    let g = sh2_field::story::Game::resume(&env, &fixture("fu_00_u_fuji.walk")).unwrap();
    let mut w = sh2_field::story::Walker::new(&env, g);
    w.search_world = false;
    assert!(w.search(3000), "{:?}", w.steps.iter().rev().take(5).map(|s| &s.what).collect::<Vec<_>>());
    assert!(sh2_field::story::flag(&w.game.regs(), 0x4c));
}

/// Mikasa (flag 0x3f): the two-party security-key puzzle, played from `tests/walk/mi_02_u_keys.plan` (the route of the user's walkthrough
/// reference, written as walker steps).  The keyholes move the keys (register bytes 0x110 / 0x111), the levers A / B / C open the doors,
/// the parties meet in MI_14_U, MI_15_U leads to the boss in MI_16_U.  Release build, ~8 min:
/// `cargo test --release -p sh2_field --test retail_story -- --ignored mikasa`.
#[test]
#[ignore]
fn mikasa_security_keys_plan_reaches_the_boss() {
    let Some(env) = walk_env() else { return };
    let g = sh2_field::story::Game::resume(&env, &fixture("mi_02_u_keys.walk")).unwrap();
    let mut w = sh2_field::story::Walker::new(&env, g);
    let plan = std::fs::read_to_string(fixture("mi_02_u_keys.plan")).unwrap();
    w.plan = plan.lines().filter(|l| !l.starts_with('#') && !l.trim().is_empty()).filter_map(|l| l.split_once(':')).map(|(m, t)| (m.to_string(), t.to_string())).collect();
    assert_eq!(w.plan.len(), 57);
    w.run(64);
    assert!(w.plan.is_empty(), "plan stuck at {:?}", w.plan.front());
    assert!(sh2_field::story::flag(&w.game.regs(), 0x3f), "{:?}", w.steps.iter().rev().take(5).map(|s| &s.what).collect::<Vec<_>>());
}

/// Todo lab 1, TD_02_U: the corridor gallery (walk-on box 6, event 6) is played -- the walker takes a walk-on box that changes the state
/// before it leaves the room (in the game the player walks through it) and holds still while the targets come (a press is a miss).
/// Event 6 sets 0x1c2e and clears 0x1c2f, the flag that TD_06_U's look point set and that TD_02_U's door reads as "wrong way" in the
/// lab-2 escape (with it still set the escape dead-ends at TD_02_U).
#[test]
fn td_02_u_lab1_gallery_clears_the_wrong_way_flag() {
    let Some(env) = walk_env() else { return };
    let g = sh2_field::story::Game::resume(&env, &fixture("td_02_u_lab1.walk")).unwrap();
    assert!(sh2_field::story::flag(&g.regs(), 0x1c2f));
    let mut w = sh2_field::story::Walker::new(&env, g);
    w.run(2);
    let regs = w.game.regs();
    assert!(sh2_field::story::flag(&regs, 0x1c2e) && !sh2_field::story::flag(&regs, 0x1c2f), "{:?}", w.steps.iter().map(|s| &s.what).collect::<Vec<_>>());
}

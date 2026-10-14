//! US retail new-game route against the real disc (`SH2_US_DISC_DIR`; skipped when unset).
//! Measured live (PINE, notes/integration/pine_us_refinement.md section 7): `OP_00_U` -> world map -> `AP_00_U` (`N003.LSD` cut scene) -> `AP_02_U`
//! (dialogue, free control, scripted fight with the "Battle Basics" window) -> east door -> `AP_10_U` -> `AP_03_U`.
use sh2_field::host::{tick_state, FieldHost};
use sh2_field::pkb_compat::PkbSet;
use sh2_field::plugin::{build_runtime, read_field_t};
use sh2_menu::session::GameSession;

fn us() -> Option<PkbSet> {
    PkbSet::open(std::env::var_os("SH2_US_DISC_DIR")?).ok()
}

#[test]
fn ap_00_u_first_visit_plays_n003_and_jumps_to_ap_02_u() {
    let Some(pkb) = us() else { return };
    let mut session = GameSession::default();
    let mut rt = build_runtime(&pkb, None, "AP_00_U", 0, &session).unwrap();
    for _ in 0..2500 {
        tick_state(&mut rt.st, &mut rt.sim);
        rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(&mut session) });
        if rt.st.pending_jump.is_some() {
            break;
        }
    }
    assert_eq!(rt.st.mces.played, vec!["N003.LSD".to_string()]);
    assert_eq!(rt.st.pending_jump, Some(("AP_02_U".to_string(), 0)), "the end of the MCES stream leaves for the SetMCESMode map");
    assert_eq!(rt.st.map_string, "", "the forecourt / guard branch behind the MCES call must not run");
}

#[test]
fn us_field_tables_come_from_field_dat() {
    let Some(pkb) = us() else { return };
    let d = read_field_t(&pkb).expect("FIELD/FIELD.DAT");
    let mut t = sh2_field::host::FieldTables::default();
    t.from_field_t(&d);
    assert_eq!((t.tres.len(), t.bbtl.len()), (537, 152));
    // InvokeBattleTbl 0 / 1 of AP_02_U: background 77, monster sets 4 and 5
    let w = |r: &[u8; 8], o: usize| u16::from_le_bytes([r[o], r[o + 1]]);
    assert_eq!((w(&t.bbtl[0], 0), w(&t.bbtl[0], 4)), (77, 4));
    assert_eq!((w(&t.bbtl[1], 0), w(&t.bbtl[1], 4)), (77, 5));
}

fn step(rt: &mut sh2_field::plugin::FieldRuntime, session: &mut GameSession, tick: u32) {
    // press circle every 12th tick: finishes typing, releases KeyWait
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

#[test]
fn ap_02_u_center_ring_starts_the_scripted_fight() {
    let Some(pkb) = us() else { return };
    let mut session = GameSession::default();
    let mut rt = build_runtime(&pkb, None, "AP_02_U", 0, &session).unwrap();
    // run the opening dialogue to its end (free control)
    let mut t = 0u32;
    while t < 20000 && rt.vm.is_running() {
        step(&mut rt, &mut session, t);
        t += 1;
    }
    assert!(!rt.vm.is_running(), "the start function ends (free control)");
    assert!(rt.vm.call_event(7, &[1]));
    for t in 0..2000u32 {
        step(&mut rt, &mut session, t);
        if rt.st.battle.is_some() {
            break;
        }
    }
    let b = rt.st.battle.as_ref().expect("event 7 invokes BBTL 0");
    assert_eq!((b.monster_set, b.background), (4, 77));
}

/// After the scripted fight the map is rebuilt with `FieldMapJump(map, -2)`: the start function plays `N004.LSD`, calls `LoadCharacter(0, ..)` (which
/// resets the model to the origin) and then `DispCharacterEP(0, -1, ..)`, which must put the player back where the battle started
/// (`CField::DispCharacterEP` with `entry == -2` uses the saved `ChrPos`).  The port used to overwrite the restored position with the
/// zeroed model position, so the player came back at (0, 0, 0) - off the floor, unable to move.
#[test]
fn battle_return_restores_the_player_position() {
    let Some(pkb) = us() else { return };
    let mut session = GameSession::default();
    let mut rt = build_runtime(&pkb, None, "AP_02_U", 0, &session).unwrap();
    let mut t = 0u32;
    while t < 20000 && rt.vm.is_running() {
        step(&mut rt, &mut session, t);
        t += 1;
    }
    assert!(rt.vm.call_event(7, &[1]));
    for t in 0..2000u32 {
        step(&mut rt, &mut session, t);
        if rt.st.battle.is_some() {
            break;
        }
    }
    assert!(rt.st.battle.is_some());
    let at = rt.sim.player.pos;
    assert!(at[0].abs() + at[2].abs() > 0.1, "the fight starts away from the origin: {at:?}");
    session.chr_pos = Some(sh2_menu::session::ChrPos { map: "AP_02_U".into(), pos: at, yaw: rt.sim.player.yaw });
    for r in 0..session.regs.len() {
        session.regs[r] = u32::from_le_bytes(rt.vm.mem.regs[r * 4..r * 4 + 4].try_into().unwrap());
    }
    let mut rt = build_runtime(&pkb, None, "AP_02_U", sh2_core::game::FieldRequest::RESTORE, &session).unwrap();
    for t in 0..1500u32 {
        step(&mut rt, &mut session, t);
    }
    assert!(!rt.vm.is_running(), "the post-battle scene ends");
    assert_eq!(rt.st.mces.played, vec!["N004.LSD".to_string()]);
    assert_eq!(rt.sim.player.pos, at, "the player is back where the battle started");
}

/// `SetLookPoint` (op 0x7a, JP 0x004b6a80): AP_04_U's start function registers the warp pad as a look point (id 0x3fff, radius 20, event 3);
/// standing on the pad attaches it and circle runs event 3 (`DoWarp` + `MapJump AP_05_U`).  The pad box itself has its enter bit disabled, which is
/// why the port never reached `AP_05_U` before the circle-button hot spots were implemented.
#[test]
fn ap_04_u_warp_pad_is_a_look_point_that_leads_to_ap_05_u() {
    let Some(pkb) = us() else { return };
    let mut session = GameSession::default();
    // registers of the story at this point (byte offsets): the tutorial part is done, the ring was granted
    let set = |s: &mut GameSession, k: usize, v: u8| {
        if s.regs.len() <= k / 4 {
            s.regs.resize(k / 4 + 1, 0);
        }
        let mut b = s.regs[k / 4].to_le_bytes();
        b[k % 4] = v;
        s.regs[k / 4] = u32::from_le_bytes(b);
    };
    for (k, v) in [(0x322, 0x1f), (0x323, 0x10), (0x32c, 2), (0x528, 1), (0x539, 1), (0x249, 1), (0x10, 1), (0x11, 1), (0x12, 1), (0, 0x12)] {
        set(&mut session, k, v);
    }
    let mut rt = build_runtime(&pkb, None, "AP_04_U", 0, &session).unwrap();
    for t in 0..1500u32 {
        step(&mut rt, &mut session, t);
    }
    let lp = rt.st.look.slots.iter().flatten().next().copied().expect("the start function registers a look point");
    assert_eq!((lp.id, lp.event, lp.radius, lp.icon), (0x3fff, 3, 20.0, 1));
    // far away: nothing attached; on the pad: attached, circle event = (3, 0x3fff)
    assert_eq!(rt.st.look.check([300.0, 0.0, 300.0]), (None, None));
    assert_eq!(rt.st.look.circle_event(), None);
    let (att, _) = rt.st.look.check(lp.pos);
    assert!(att.is_some());
    assert_eq!(rt.st.look.circle_event(), Some((3, 0x3fff)));
    // the default circle event is called with [0, id] (retail CallFieldEvent class 1)
    assert!(rt.vm.call_event(3, &[0, 0x3fff]));
    for t in 0..3000u32 {
        step(&mut rt, &mut session, t);
        if rt.st.pending_jump.is_some() {
            break;
        }
    }
    assert_eq!(rt.st.pending_jump.as_ref().map(|j| j.0.as_str()), Some("AP_05_U"));
}

/// The US tailor (`CA_02_U` event 6, shared function 0x13dc -> `SpecialMenu(0x300)`): Nelson asks for "what I want" - one of ten dress materials,
/// kind-10 goods `TreasureControl(5, 0xa8a..0xa93)` = bits 0x8a..0x93 of the bag's obtained set (`InventoryChange` kind 10, base 0x984).  Without one
/// he sends the party away, with one the tailor screen opens.  This is how the port reaches the US tailor from the script.
#[test]
fn us_tailor_opens_when_the_party_owns_a_dress_material() {
    let Some(pkb) = us() else { return };
    fn run(pkb: &PkbSet, material: Option<usize>) -> Vec<sh2_field::host::MenuReq> {
        let mut session = GameSession::default();
        session.new_game("CA_02_U");
        if let Some(m) = material {
            let bag = session.save.btl.data[2] as usize * 0x200;
            session.save.btl.data[0x984 + bag + (m >> 3)] |= 1 << (m & 7);
        }
        let mut rt = build_runtime(pkb, None, "CA_02_U", 0, &session).unwrap();
        let mut found = vec![];
        for t in 0..800u32 {
            step(&mut rt, &mut session, t);
            if !rt.vm.is_running() {
                break;
            }
        }
        assert!(rt.vm.call_event(6, &[4]));
        for t in 0..6000u32 {
            let press = if t % 12 == 0 { sh2_core::game::padbit::CIRCLE } else { 0 };
            rt.st.press = press;
            tick_state(&mut rt.st, &mut rt.sim);
            for (id, args) in std::mem::take(&mut rt.st.event_queue) {
                rt.vm.call_event(id, &args);
            }
            rt.vm.set_pad(sh2_script::cscript::PadState { raw: press as u32, new_press: press as u32, repeat: 0, consumed: 0 });
            rt.vm.poll(&mut sh2_field::host::FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(&mut session) });
            if let Some(r) = rt.st.menu_req.take() {
                found.push(r);
                rt.st.menu_wait = false;
            }
            if !rt.vm.is_running() {
                break;
            }
        }
        found
    }
    assert!(!run(&pkb, None).contains(&sh2_field::host::MenuReq::Tailor), "no material: Nelson sends the party away");
    assert!(run(&pkb, Some(0x8a)).contains(&sh2_field::host::MenuReq::Tailor), "with a material the tailor opens");
}

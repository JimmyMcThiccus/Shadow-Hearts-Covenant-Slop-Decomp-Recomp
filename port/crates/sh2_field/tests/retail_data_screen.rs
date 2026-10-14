//! The real `dataAccess` screen on the **US retail disc** (`SH2_US_DISC_DIR`; skipped when unset): a Save and a Load through the screen's own state machine,
//! driven with pad keys only, on a port memory-card image.

use sh2_battle::actions::ActionTables;
use sh2_battle::data::BattleData;
use sh2_battle::pkb_compat::PkbDisc;
use sh2_core::game::padbit as pad;
use sh2_field::cmd_page::{CmdCache, Env, HostReq};
use sh2_field::cmd_ui::TexReg;
use sh2_field::data_screen::{DataScreen, Outcome};
use sh2_field::fscreen::{FieldScreen, ScreenFlow, ScreenIo};
use sh2_menu::memcard::{MemCard, MemCardStorage};
use sh2_menu::plugin::MenuAssets;
use sh2_menu::session::{slot_used, FileStorage, GameSession};

struct H {
    session: GameSession,
    assets: MenuAssets,
    db: BattleData,
    tables: ActionTables,
    cache: CmdCache,
    dev: FileStorage,
    ses: Vec<sh2_menu::gfx::MenuSe>,
    req: Vec<HostReq>,
    tick: u64,
    card: std::path::PathBuf,
}

fn harness(tag: &str) -> Option<H> {
    let root = std::path::PathBuf::from(std::env::var_os("SH2_US_DISC_DIR")?);
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    std::env::set_var("SH2_DISC_DIR", &root);
    let disc = PkbDisc::open(&root).ok()?;
    let db = BattleData::load(&disc).ok()?;
    let tables = ActionTables::load(&db);
    let assets = MenuAssets::load(&root);
    let mut session = GameSession::default();
    session.new_game("AP_02_U");
    sh2_battle::bridge::init_new_game_retail(&db, &mut session, 0);
    let dir = std::env::temp_dir().join(format!("sh2_data_screen_{tag}_{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    let card = dir.join("mcd_sh2_port.ps2");
    let dev = FileStorage::new(&dir).with_port_card(MemCardStorage::open_or_new(&card, "BASLUS-21041-SH2"));
    Some(H { session, assets, db, tables, cache: CmdCache::default(), dev, ses: vec![], req: vec![], tick: 0, card })
}

impl H {
    fn run<R>(&mut self, f: impl FnOnce(&mut Env) -> R) -> R {
        let mut reg = TexReg::headless();
        let mut env = Env {
            session: &mut self.session,
            assets: &self.assets,
            db: Some(&self.db),
            tables: Some(&self.tables),
            reg: &mut reg,
            cache: &mut self.cache,
            ses: &mut self.ses,
            dev: &mut self.dev,
            req: &mut self.req,
            tick: self.tick,
        };
        f(&mut env)
    }
    /// One tick with `keys` held for one frame (`press` = the same bits).
    fn key(&mut self, s: &mut DataScreen, keys: u16) -> ScreenFlow {
        self.tick += 1;
        let mut io = ScreenIo::default();
        self.run(|env| s.tick(env, keys, keys, &mut io))
    }
    fn settle(&mut self, s: &mut DataScreen, n: usize) {
        for _ in 0..n {
            self.key(s, 0);
        }
    }
    fn press(&mut self, s: &mut DataScreen, k: u16) {
        self.key(s, k);
        self.settle(s, 3);
    }
}

#[test]
fn save_then_load_through_the_real_screen() {
    let Some(mut h) = harness("flow") else { return };
    h.session.add_cash(777);
    let cash = h.session.cash();
    // ---- Save: device select -> MEMORY CARD slot 1 -> file list -> slot 1 -> "No" by default -> Yes -> progress -> done
    let mut s = h.run(|env| DataScreen::new(env, false, false)).expect("the dataAccess art loads");
    h.settle(&mut s, 8);
    assert_eq!(s.state(), "devices", "the device select window comes first");
    h.press(&mut s, pad::CIRCLE); // MEMORY CARD slot 1
    assert_eq!(s.state(), "files");
    h.press(&mut s, pad::CIRCLE); // slot 1 (empty: create new)
    assert_eq!(s.state(), "query");
    h.press(&mut s, pad::CIRCLE); // the cursor starts on "No": back to the file list
    assert_eq!(s.state(), "files", "OK on the default No returns to the list");
    h.press(&mut s, pad::CIRCLE);
    h.press(&mut s, pad::UP); // "Yes"
    h.press(&mut s, pad::CIRCLE);
    assert_eq!(s.state(), "progress", "the progress bar runs before the card is written");
    assert!(!slot_used(&mut h.dev, 0), "nothing is written while the bar runs");
    h.settle(&mut s, 160);
    assert!(slot_used(&mut h.dev, 0), "slot 1 was written");
    assert_eq!(s.state(), "done");
    h.press(&mut s, pad::CIRCLE);
    let mut done = false;
    for _ in 0..40 {
        if h.key(&mut s, 0) == ScreenFlow::Done {
            done = true;
            break;
        }
    }
    assert!(done, "the screen ends after the done window");
    assert_eq!(s.outcome, Some(Outcome::Saved));
    // the port card on disk is a real card image with the save folder
    let img = MemCard::open(&h.card).expect("card image");
    assert!(img.list_dir("BASLUS-21041-SH2").unwrap().iter().any(|e| e.name == "SH2-000"));
    assert_eq!(img.ecc_errors().1, 0);

    // ---- Load it back
    h.session.add_cash(-500);
    let mut s = h.run(|env| DataScreen::new(env, true, false)).unwrap();
    h.settle(&mut s, 8);
    h.press(&mut s, pad::CIRCLE); // device
    assert_eq!(s.state(), "files");
    h.press(&mut s, pad::CIRCLE); // the used slot
    assert_eq!(s.state(), "query");
    h.press(&mut s, pad::UP);
    h.press(&mut s, pad::CIRCLE); // yes
    h.settle(&mut s, 120);
    h.press(&mut s, pad::CIRCLE); // done window
    assert_eq!(h.session.cash(), cash, "the loaded game is the saved one");
    assert!(h.req.contains(&HostReq::LoadedGame));
    assert_eq!(s.outcome, Some(Outcome::Loaded));
}

#[test]
fn load_without_saves_warns_and_cancel_asks_before_leaving() {
    let Some(mut h) = harness("empty") else { return };
    let mut s = h.run(|env| DataScreen::new(env, true, false)).unwrap();
    h.settle(&mut s, 8);
    h.press(&mut s, pad::DOWN); // MEMORY CARD slot 2: nothing inserted
    h.press(&mut s, pad::CIRCLE);
    assert_eq!(s.state(), "warning", "no memory card in slot 2");
    h.press(&mut s, pad::CIRCLE);
    h.settle(&mut s, 4);
    assert_ne!(s.state(), "warning");
    // slot 1 holds nothing to load: a warning too
    h.press(&mut s, pad::CIRCLE);
    h.settle(&mut s, 6);
    // cancel from the device select asks "Go back without loading?" (default No), Yes leaves
    for _ in 0..6 {
        if s.state() == "quit" {
            break;
        }
        h.press(&mut s, pad::CROSS);
    }
    assert_eq!(s.state(), "quit");
    h.press(&mut s, pad::UP);
    h.press(&mut s, pad::CIRCLE);
    let mut done = false;
    for _ in 0..40 {
        if h.key(&mut s, 0) == ScreenFlow::Done {
            done = true;
            break;
        }
    }
    assert!(done);
    assert_eq!(s.outcome, Some(Outcome::Cancelled));
}

#[test]
fn the_art_and_tables_are_the_real_ones() {
    let Some(mut h) = harness("art") else { return };
    let s = h.run(|env| DataScreen::new(env, false, false)).unwrap();
    let w = |i: usize| s.warning_text(&sh2_menu::dataaccess::Warning::NoDevice(if i == 0 { sh2_menu::storage::DeviceKind::Mc1 } else { sh2_menu::storage::DeviceKind::Mc2 }));
    assert!(w(0).contains("No memory card") && w(0).contains("slot 1"), "{}", w(0));
    assert!(w(1).contains("slot 2"));
}

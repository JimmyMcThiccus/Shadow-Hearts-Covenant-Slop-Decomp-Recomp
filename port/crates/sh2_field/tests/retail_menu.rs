//! The in-game command menu on the **US retail disc** (`SH2_US_DISC_DIR`; skipped when unset): the retail `CMDMENU.MSD` layout
//! (attach files shifted by one, renumbered data-table chunks, new submenus) and the pages that read the retail save block.
//!
//! One process = one active region, so these tests live in their own integration test binary.

use sh2_battle::actions::ActionTables;
use sh2_battle::data::BattleData;
use sh2_battle::pkb_compat::PkbDisc;
use sh2_core::game::padbit as pad;
use sh2_field::cmd::CmdPage;
use sh2_field::cmd_page::{CmdCache, Env, Flow, HostReq, Page};
use sh2_field::cmd_ui::TexReg;
use sh2_menu::plugin::MenuAssets;
use sh2_menu::session::{FileStorage, GameSession};

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
}

fn harness() -> Option<H> {
    let root = std::path::PathBuf::from(std::env::var_os("SH2_US_DISC_DIR")?);
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    // every crate reads "the disc" from SH2_DISC_DIR (what `sh2_app --us` does)
    std::env::set_var("SH2_DISC_DIR", &root);
    let disc = PkbDisc::open(&root).ok()?;
    let db = BattleData::load(&disc).ok()?;
    let tables = ActionTables::load(&db);
    let assets = MenuAssets::load(&root);
    let mut session = GameSession::default();
    session.new_game("AP_02_U");
    sh2_battle::bridge::init_new_game_retail(&db, &mut session, 0);
    for i in 0..24 {
        session.save.menu.data[sh2_field::cmd_top::OFF_ENTRY_FLAGS + i] = 2;
    }
    let dir = std::env::temp_dir().join(format!("sh2_cmd_menu_us_{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    Some(H { session, assets, db, tables, cache: CmdCache::default(), dev: FileStorage::new(dir), ses: vec![], req: vec![], tick: 0 })
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
    fn press(&mut self, page: &mut dyn Page, keys: u16) -> Flow {
        self.tick += 1;
        self.run(|env| page.tick(env, keys))
    }
    fn settle(&mut self, page: &mut dyn Page, n: usize) {
        for _ in 0..n {
            self.press(page, 0);
        }
    }
    fn draw_len(&mut self, page: &mut dyn Page) -> usize {
        self.settle(page, 40);
        let mut gfx = sh2_menu::gfx::CommandBuffer::default();
        page.draw(&mut gfx);
        gfx.cmds.len()
    }
}

#[test]
fn retail_top_menu_is_english_and_has_the_submenus() {
    let Some(mut h) = harness() else { return };
    let mut top = h.run(|env| sh2_field::cmd_top::TopPage::new(env)).expect("the retail CMDMENU layout loads");
    assert!(top.note().contains("Use Items"), "{}", top.note());
    assert!(h.draw_len(&mut top) > 50);
    // entry 13 "Combo Setup" (block 2) opens the retail combo submenu with "Assign Combo" / "Combo Switch"
    let tags: Vec<_> = (0..24).filter_map(|i| h.run(|env| env.scenes()).and_then(|s| s.top.msd.text_entry(i).map(|e| (i, e.2)))).collect();
    assert_eq!(tags[13].1 & 0xffff, 0xffff);
    assert_eq!(tags[9].1 >> 16, 3, "Data = submenu 3");
}

#[test]
fn retail_pages_open_with_the_english_data_tables() {
    let Some(mut h) = harness() else { return };
    h.session.save.btl.set_monster_defeated(0);
    h.session.save.btl.set_monster_defeated(1);
    for page in [
        CmdPage::Item,
        CmdPage::Equipment,
        CmdPage::Private,
        CmdPage::Option,
        CmdPage::Magic,
        CmdPage::RingCustom,
        CmdPage::PropertyList,
        CmdPage::Help,
        CmdPage::Score,
        CmdPage::Library,
        CmdPage::Graveyard,
        CmdPage::KeyCustom,
        CmdPage::ComboMagic,
        CmdPage::ComboKey,
    ] {
        let mut p = h.run(|env| sh2_field::cmd_pages::make_page(env, page, Some(5))).unwrap_or_else(|| panic!("{page:?} does not open on the retail data"));
        assert!(h.draw_len(p.as_mut()) > 2, "{page:?} drew nothing");
    }
}

#[test]
fn retail_library_shows_the_monsters_that_were_met() {
    let Some(mut h) = harness() else { return };
    h.session.save.btl.set_monster_defeated(0);
    h.session.save.btl.set_monster_defeated(1);
    let p = h.run(|env| sh2_field::cmd_view::LibraryPage::new(env)).expect("library");
    let mut p: Box<dyn Page> = Box::new(p);
    h.settle(p.as_mut(), 40);
    let mut gfx = sh2_menu::gfx::CommandBuffer::default();
    p.draw(&mut gfx);
    let texts: Vec<String> = gfx.cmds.iter().filter_map(|c| if let sh2_menu::gfx::DrawCmd::Text(t) = c { Some(sh2_menu::sjis::decode(&t.text)) } else { None }).collect();
    assert!(texts.iter().any(|t| t == "Revenant"), "{texts:?}");
    assert!(texts.iter().any(|t| t == "Statue"));
    assert!(!texts.iter().any(|t| t == "Gargoyle"), "monsters that were not met stay hidden");
}

#[test]
fn retail_graveyard_jumps_to_gy_00_d() {
    let Some(mut h) = harness() else { return };
    let mut p = h.run(|env| sh2_field::cmd_misc::GraveyardPage::new(env)).expect("graveyard");
    h.settle(&mut p, 10);
    assert!(matches!(h.press(&mut p, pad::CIRCLE), Flow::Stay), "yes starts the fade");
    h.settle(&mut p, 60);
    assert!(h.req.contains(&HostReq::MapJump { map: "GY_00_D".into(), entry: 0 }), "{:?}", h.req);
}

#[test]
fn retail_key_customize_defaults_swap_confirm_and_cancel() {
    let Some(mut h) = harness() else { return };
    assert_eq!(h.session.save.menu.button_entries(), [0xc, 0xe, 0xd, 0xf]);
    let mut p = h.run(|env| sh2_field::cmd_misc::KeyCustomPage::new(env)).expect("key custom");
    assert!(h.draw_len(&mut p) > 30);
}

/// `CommandMenu(4, ChkSavePoint() >= 0)`: off a save point the Save row of the Data entry is disabled (the cursor skips it, nothing opens), on a
/// save point (or when a script / the title opens the menu) Save is selectable.
#[test]
fn retail_data_entry_gates_save_to_save_points() {
    let Some(mut h) = harness() else { return };
    // walk to the Data entry (entry 9 of the command list) of a fresh top page and open it
    let open_data = |h: &mut H| {
        let mut top = h.run(|env| sh2_field::cmd_top::TopPage::new(env)).expect("top");
        h.settle(&mut top, 40);
        for _ in 0..12 {
            if top.selected_entry() == Some(9) {
                break;
            }
            h.press(&mut top, pad::DOWN);
        }
        assert_eq!(top.selected_entry(), Some(9), "the Data entry");
        h.press(&mut top, pad::CIRCLE);
        top
    };
    h.cache.save_gate = Some(false);
    let mut top = open_data(&mut h);
    assert_eq!(top.data_state(), Some((1, true)), "off a save point: Save disabled, the cursor starts on Load");
    h.press(&mut top, pad::UP);
    assert_eq!(top.data_state(), Some((1, true)), "the cursor skips the disabled row");
    h.cache.save_gate = Some(true);
    let top = open_data(&mut h);
    assert_eq!(top.data_state(), Some((0, false)), "on a save point Save is the first, selectable row");
    h.cache.save_gate = None;
    let top = open_data(&mut h);
    assert_eq!(top.data_state(), Some((0, false)), "menus opened by scripts are not gated");
}

/// `CmdComboMagic::SelectGoods`: a known combination explains itself with `GetRegDat(0x22, i)` (English on the retail disc); an unknown one keeps the scene's
/// own note.
#[test]
fn retail_combo_magic_explains_known_combinations() {
    let Some(mut h) = harness() else { return };
    for i in 0..3 {
        h.session.save.menu.data[sh2_field::cmd_misc::OFF_COMBO_SEEN + i] = 1;
    }
    h.session.save.btl.set_combo_flags(0b11);
    let p = h.run(|env| sh2_field::cmd_misc::ComboMagicPage::new(env)).expect("combo magic page");
    let note = p.note();
    assert!(note.is_ascii() && note.len() > 10, "retail combination text: {note:?}");
}

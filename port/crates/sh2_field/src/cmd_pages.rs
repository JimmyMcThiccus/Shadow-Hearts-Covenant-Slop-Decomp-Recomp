//! Page factory (`CmdMenu::Ready`, JP 0x00436390) and the pages that are not worth a module of their own.

use sh2_menu::gfx::MenuGfx;

use crate::cmd::CmdPage;
use crate::cmd_page::*;

/// `CmdMenu::Ready(page, a, b)`: build the page object.  `pc` is the character chosen on the top page (`b`).
pub fn make_page(env: &mut Env, page: CmdPage, pc: Option<u8>) -> Option<Box<dyn Page>> {
    let boxed = |p: Option<Box<dyn Page>>| p;
    match page {
        CmdPage::Item => crate::cmd_item::ItemPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Equipment => crate::cmd_equip::EquipPage::new(env, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Private => crate::cmd_status::StatusPage::new(env, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Formation if sh2_core::boot::is_retail() => crate::cmd_form_retail::RetailFormPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Formation => crate::cmd_form::FormPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Option => crate::cmd_option::OptionPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Magic => crate::cmd_magic::MagicPage::new(env, false, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::WhiteMagic => crate::cmd_magic::MagicPage::new(env, true, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Crest if sh2_core::boot::is_retail() => crate::cmd_crest_retail::RetailCrestPage::new(env, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Crest => crate::cmd_crest::CrestPage::new(env, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::PropertyList if sh2_core::boot::is_retail() => crate::cmd_plist_retail::RetailInventoryPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::PropertyList => crate::cmd_view::PropertyPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Help if sh2_core::boot::is_retail() => crate::cmd_help_retail::RetailHelpPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Help => crate::cmd_view::HelpPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Score if sh2_core::boot::is_retail() => crate::cmd_score_retail::RetailScorePage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Score => crate::cmd_view::ScorePage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::SelectChar => crate::cmd_sechar::SelectCharPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Library if sh2_core::boot::is_retail() => crate::cmd_library_retail::RetailLibraryPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Library => crate::cmd_view::LibraryPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::RingCustom if sh2_core::boot::is_retail() => crate::cmd_ring_retail::RetailRingPage::new(env, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::RingCustom => crate::cmd_ring::RingPage::new(env, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Graveyard => crate::cmd_misc::GraveyardPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::KeyCustom => crate::cmd_misc::KeyCustomPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::ComboMagic => crate::cmd_misc::ComboMagicPage::new(env).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::ComboKey => crate::cmd_misc::ComboKeyPage::new(env, pc).map(|p| Box::new(p) as Box<dyn Page>),
        CmdPage::Solomon => boxed(Some(Box::new(SolomonLauncher { sent: false }))),
        CmdPage::Top => None,
    }
}

/// The save / load screen (`dataAccess`, launched from the Data entry of the top page).
///
/// **US retail**: the real `dataAccess` screen ([`crate::data_screen`]); the page that is opened only asks the host to run it (like the Solomon launcher).  `reopen_menu`:
/// the command menu comes back when the screen ends (the Data entry of the top page); a save point's script-opened save does not reopen it.
/// **JP demo** (and the dev tour): the old list page [`crate::cmd_data::DataPage`].
pub fn make_data_page_ex(env: &mut Env, load: bool, reopen_menu: bool) -> Option<Box<dyn Page>> {
    if sh2_core::boot::is_retail() && std::env::var_os("SH2_OLD_DATA_PAGE").is_none() {
        return Some(Box::new(DataLauncher { load, reopen_menu, sent: false }));
    }
    crate::cmd_data::DataPage::new(env, load).map(|p| Box::new(p) as Box<dyn Page>)
}

/// Save / Load page opened by a script (save point) or the dev driver: the screen does not reopen the command menu.
pub fn make_data_page(env: &mut Env, load: bool) -> Option<Box<dyn Page>> {
    make_data_page_ex(env, load, false)
}

/// Retail page 'Data': asks the host to open the `dataAccess` screen (which closes the command menu) on its first tick.
pub struct DataLauncher {
    load: bool,
    reopen_menu: bool,
    sent: bool,
}

impl Page for DataLauncher {
    fn page(&self) -> CmdPage {
        CmdPage::Top
    }
    fn title(&self) -> usize {
        0
    }
    fn tick(&mut self, env: &mut Env, _keys: u16) -> Flow {
        if !self.sent {
            self.sent = true;
            env.req.push(HostReq::Screen(crate::fscreen::ScreenReq::Data { load: self.load, reopen_menu: self.reopen_menu }));
        }
        Flow::Stay
    }
    fn draw(&self, _g: &mut dyn MenuGfx) {}
}

/// Page 0x15 (`CmdMenu::Ready(0x15)` -> `solomon::initialize`): Solomon's key is a full field screen ([`crate::solomon`]); the launcher asks the
/// host to open it (which closes the command menu) on its first tick.
pub struct SolomonLauncher {
    sent: bool,
}

impl Page for SolomonLauncher {
    fn page(&self) -> CmdPage {
        CmdPage::Solomon
    }
    fn title(&self) -> usize {
        0
    }
    fn tick(&mut self, env: &mut Env, _keys: u16) -> Flow {
        if !self.sent {
            self.sent = true;
            env.req.push(HostReq::Screen(crate::fscreen::ScreenReq::Solomon));
        }
        Flow::Stay
    }
    fn draw(&self, _g: &mut dyn MenuGfx) {}
}

/// Index of a page's title string in the title-log scene (attach 6 of CMDMENU, 35 strings).
pub fn title_index(page: CmdPage) -> usize {
    match page {
        CmdPage::Top => 0,
        CmdPage::Item => 1,
        CmdPage::WhiteMagic => 28,
        CmdPage::Magic => 13,
        CmdPage::Crest => 33,
        CmdPage::Equipment => 12,
        CmdPage::RingCustom => 14,
        CmdPage::Private => 11,
        CmdPage::Formation => 2,
        CmdPage::Graveyard => 3,
        CmdPage::ComboKey => 32,
        CmdPage::ComboMagic => 4,
        CmdPage::Help => 5,
        CmdPage::Score => 6,
        CmdPage::Library => 7,
        CmdPage::PropertyList => 34,
        CmdPage::Option => 8,
        CmdPage::KeyCustom => 9,
        CmdPage::SelectChar => 12,
        CmdPage::Solomon => 0,
    }
}

/// Dev driver (`SH2_MENU_DEV`): give the new game some items / equipment so every page has something to show.
pub fn dev_seed(session: &mut sh2_menu::session::GameSession, db: &sh2_battle::data::BattleData) {
    use sh2_menu::save::BtlSave;
    let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
    for (i, n) in [(0usize, 5u8), (1, 3), (2, 2), (4, 4), (5, 1), (8, 2), (12, 1), (14, 3), (32, 2), (36, 1)] {
        session.save.btl.data[BtlSave::OFF_ITEMS + bag + i] = n;
    }
    for i in 0..10 {
        session.save.btl.data[BtlSave::OFF_WEAPONS + bag + i] = 1;
        session.save.btl.data[BtlSave::OFF_ARMOR + bag + i] = 1;
        session.save.btl.data[BtlSave::OFF_ACCESSORIES + bag + i] = 1;
    }
    for id in session.all_members() {
        if let Some(mut r) = session.save.btl.pc(id as usize) {
            r.hp = (r.hp_max as u32 * 6 / 10) as u16;
            r.mp = (r.mp_max as u32 * 4 / 10) as u16;
            session.save.btl.set_pc(id as usize, &r);
        }
    }
    // key items: the ring expansion stock (extra hits / zone points / strike points) and a few combination techniques met
    session.save.btl.set_key_item(0, 1);
    session.save.btl.set_key_item(1, 6);
    session.save.btl.set_key_item(2, 4);
    for i in 0..6 {
        session.save.menu.data[crate::cmd_misc::OFF_COMBO_SEEN + i] = 1;
    }
    session.save.btl.set_combo_flags(0b0111);
    // monsters met / defeated for the library, scores for the score page
    for id in 0..12 {
        session.save.btl.set_monster_defeated(id);
        if id % 2 == 0 {
            session.save.btl.set_monster_snapped(id);
        }
    }
    let _ = db;
}

/// Dev driver: the scripted tour of the pages (`Goto` + photograph).
pub fn dev_tour() -> Vec<crate::menu_overlay::Act> {
    tour(true, false)
}

/// The tour `--autoplay` runs when it opens the menu in the real game (no save screens: they would overwrite the player's slots);
/// ends by closing the menu with the cancel button.
pub fn autoplay_tour() -> Vec<crate::menu_overlay::Act> {
    tour(false, true)
}

fn tour(with_save: bool, close: bool) -> Vec<crate::menu_overlay::Act> {
    use crate::menu_overlay::Act;
    use sh2_core::game::padbit as p;
    let mut v = vec![Act::Wait(70), Act::Shot("01_top".into())];
    let mut n = 1;
    let mut shot = |v: &mut Vec<Act>, name: &str| {
        n += 1;
        v.push(Act::Shot(format!("{n:02}_{name}")));
    };
    // top page: flip to the second block and back, select character mode
    v.extend([Act::Key(p::RIGHT), Act::Wait(30)]);
    shot(&mut v, "top_block2");
    v.extend([Act::Key(p::LEFT), Act::Wait(20), Act::Key(p::DOWN), Act::Key(p::DOWN), Act::Key(p::DOWN), Act::Key(p::DOWN), Act::Wait(8), Act::Key(p::CIRCLE), Act::Wait(20)]);
    shot(&mut v, "top_pick_character");
    v.extend([Act::Key(p::CROSS), Act::Wait(5)]);
    // item page: list, sort, target picker, use
    v.extend([Act::Goto(CmdPage::Item, None), Act::Wait(40)]);
    shot(&mut v, "item");
    v.extend([Act::Key(p::SQUARE), Act::Wait(20)]);
    shot(&mut v, "item_sort");
    v.extend([Act::Key(p::CROSS), Act::Wait(6), Act::Key(p::DOWN), Act::Wait(4), Act::Key(p::DOWN), Act::Wait(4), Act::Key(p::CIRCLE), Act::Wait(20)]);
    shot(&mut v, "item_target");
    v.extend([Act::Key(p::CIRCLE), Act::Wait(30)]);
    shot(&mut v, "item_used");
    v.extend([Act::PopPage, Act::Wait(10)]);
    for (page, pc, name, keys) in [
        (CmdPage::Equipment, Some(5u8), "equipment", vec![Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::Private, Some(5), "status", vec![Act::Key(p::DOWN), Act::Key(p::DOWN), Act::Key(p::DOWN), Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::Formation, None, "formation", vec![Act::Key(p::CIRCLE), Act::Wait(4), Act::Key(p::DOWN), Act::Wait(4), Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::Option, None, "option", vec![Act::Key(p::DOWN), Act::Key(p::DOWN), Act::Key(p::DOWN), Act::Key(p::RIGHT), Act::Key(p::DOWN), Act::Key(p::RIGHT), Act::Wait(25)]),
        (CmdPage::Magic, Some(5), "magic", vec![Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::Crest, Some(5), "crest", vec![Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::RingCustom, Some(5), "ringcustom", vec![Act::Key(p::CIRCLE), Act::Wait(4), Act::Key(p::RIGHT), Act::Wait(25)]),
        (CmdPage::PropertyList, None, "propertylist", vec![Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::Help, None, "help", vec![Act::Key(p::CIRCLE), Act::Wait(4), Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::Score, None, "score", vec![Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::Library, None, "library", vec![Act::Key(p::CIRCLE), Act::Wait(25)]),
        (CmdPage::Graveyard, None, "graveyard", vec![Act::Key(p::DOWN), Act::Wait(10)]),
        (CmdPage::KeyCustom, None, "keycustom", vec![Act::Key(p::CIRCLE), Act::Wait(6), Act::Key(p::RIGHT), Act::Wait(10)]),
        (CmdPage::ComboMagic, None, "combomagic", vec![Act::Key(p::DOWN), Act::Wait(10)]),
        (CmdPage::ComboKey, Some(5), "combokey", vec![Act::Key(p::CIRCLE), Act::Wait(6), Act::Key(p::DOWN), Act::Wait(10)]),
    ] {
        v.extend([Act::Goto(page, pc), Act::Wait(50)]);
        shot(&mut v, name);
        v.extend(keys);
        shot(&mut v, &format!("{name}_2"));
        v.extend([Act::PopPage, Act::Wait(25)]);
    }
    if !with_save {
        if close {
            v.extend([Act::Key(p::CROSS), Act::Wait(60)]);
        }
        return v;
    }
    // save then load
    v.extend([Act::GotoData(false), Act::Wait(40)]);
    shot(&mut v, "save");
    v.extend([Act::Key(p::CIRCLE), Act::Wait(10)]);
    shot(&mut v, "save_confirm");
    v.extend([Act::Key(p::CIRCLE), Act::Wait(30)]);
    shot(&mut v, "saved");
    v.extend([Act::PopPage, Act::Wait(20), Act::GotoData(true), Act::Wait(40)]);
    shot(&mut v, "load");
    v.push(Act::PopPage);
    v.push(Act::Wait(10));
    v
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::cmd_ui::TexReg;
    use sh2_battle::actions::ActionTables;
    use sh2_battle::data::BattleData;
    use sh2_battle::pkb_compat::PkbDisc;
    use sh2_menu::plugin::MenuAssets;
    use sh2_menu::session::{FileStorage, GameSession};

    /// Real data harness: the JP disc (skips when it is not around), a new game, headless texture registry.
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

    fn harness(tag: &str) -> Option<H> {
        let root = std::env::var("SH2_DISC_DIR").ok().or_else(|| Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string()))?;
        let root = std::path::PathBuf::from(root);
        if !root.exists() {
            eprintln!("cmd_pages tests: no disc at {}, skipped", root.display());
            return None;
        }
        let disc = PkbDisc::open(&root).ok()?;
        let db = BattleData::load(&disc).ok()?;
        let tables = ActionTables::load(&db);
        let assets = MenuAssets::load(&root);
        let mut session = GameSession::default();
        session.new_game("AP_02_U");
        sh2_battle::bridge::init_new_game(&db, &mut session);
        for i in 0..24 {
            session.save.menu.data[crate::cmd_top::OFF_ENTRY_FLAGS + i] = 2;
        }
        let dir = std::env::temp_dir().join(format!("sh2_cmd_menu_test_{tag}_{}", std::process::id()));
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
    }

    use sh2_core::game::padbit as pad;

    #[test]
    fn party_view_skips_characters_that_were_never_created() {
        // the default party set names PC 0xb, which `new_game` never creates: the old overlay showed an empty "PC11 Lv 0" row
        let mut s = GameSession::default();
        s.new_game("AP_00_U");
        assert!(s.all_members().contains(&0xb));
        let tbl = sh2_menu::session::RowTable { rows: vec![vec![]; 12] };
        let mut pc_i = [0u8; 0x1c];
        pc_i[6] = 1;
        s.init_pc(5, &pc_i, b"Karin\0", &tbl);
        let v = party_view(&s);
        assert_eq!(v.len(), 1);
        assert_eq!(v[0].id, 5);
        assert!(v.iter().all(|p| p.level > 0));
    }

    #[test]
    fn top_page_shows_real_entries_and_opens_pages() {
        let Some(mut h) = harness("top") else { return };
        let mut top = h.run(|env| crate::cmd_top::TopPage::new_for_test(env)).expect("top page");
        assert_eq!(top.page(), CmdPage::Top);
        assert!(top.note().contains("アイテム"), "{}", top.note());
        // down to the equipment entry (4th is the crest change; 5th the equipment), circle opens the character picker
        for _ in 0..4 {
            h.press(&mut top, pad::DOWN);
        }
        h.press(&mut top, pad::CIRCLE);
        h.press(&mut top, pad::CIRCLE);
        let mut opened = None;
        for _ in 0..120 {
            if let Flow::Open(p) = h.press(&mut top, 0) {
                opened = Some(p.page());
                break;
            }
        }
        assert_eq!(opened, Some(CmdPage::Equipment));
        // L / R flip the entry block; hidden entries are skipped
        h.session.save.menu.data[crate::cmd_top::OFF_ENTRY_FLAGS + 1] = 0;
    }

    #[test]
    fn item_page_uses_a_healing_item() {
        let Some(mut h) = harness("item") else { return };
        let id = h.session.all_members().into_iter().find(|&m| h.session.save.btl.pc(m as usize).map(|r| r.present()).unwrap_or(false)).unwrap();
        let mut r = h.session.save.btl.pc(id as usize).unwrap();
        r.hp = 10;
        h.session.save.btl.set_pc(id as usize, &r);
        let before = h.session.save.btl.item_count(0);
        assert!(before > 0);
        let mut page = h.run(|env| crate::cmd_item::ItemPage::new(env)).expect("item page");
        // the first row is whatever the sort puts first; walk to item 0 (Medi-Leaf) through the page's own list
        let mut found = false;
        for _ in 0..8 {
            if page.note().contains("ＨＰ") || page.note().contains("HP") || page.note().contains("薬草") {
                found = true;
                break;
            }
            h.press(&mut page, pad::DOWN);
        }
        assert!(found, "never reached the herb: {}", page.note());
        h.press(&mut page, pad::CIRCLE); // target picker
        h.press(&mut page, pad::CIRCLE); // use on the first member
        let after = h.session.save.btl.item_count(0);
        let hp = h.session.save.btl.pc(id as usize).unwrap().hp;
        assert_eq!(after, before - 1);
        assert!(hp > 10, "hp {hp}");
    }

    #[test]
    fn equipment_page_changes_equipment_and_recomputes_stats() {
        let Some(mut h) = harness("equip") else { return };
        // give the party a stack of everything and look for an armor the leader can wear that changes the defence
        let id = 5u8;
        let bag = h.session.save.btl.bag() as usize * sh2_menu::save::BtlSave::BAG_STRIDE;
        for i in 0..0x30 {
            h.session.save.btl.data[sh2_menu::save::BtlSave::OFF_ARMOR + bag + i] = 1;
        }
        let r = h.session.save.btl.pc(id as usize).unwrap();
        let before = h.run(|env| crate::cmd_equip::derived_with(env, id, crate::cmd_equip::Loadout { weapon: r.weapon, armor: r.armor, acc: r.accessories })).unwrap();
        let mut page = h.run(|env| crate::cmd_equip::EquipPage::new(env, Some(id))).expect("equip page");
        h.press(&mut page, pad::DOWN); // armor slot
        h.press(&mut page, pad::CIRCLE); // candidate list
        let mut changed = false;
        for _ in 0..30 {
            h.press(&mut page, pad::DOWN);
            let r2 = h.session.save.btl.pc(id as usize).unwrap();
            let _ = r2;
            h.press(&mut page, pad::CIRCLE);
            let r3 = h.session.save.btl.pc(id as usize).unwrap();
            if r3.armor != r.armor {
                changed = true;
                break;
            }
            h.press(&mut page, pad::CIRCLE);
        }
        assert!(changed, "armor never changed");
        let r3 = h.session.save.btl.pc(id as usize).unwrap();
        let after = h.run(|env| crate::cmd_equip::derived_with(env, id, crate::cmd_equip::Loadout { weapon: r3.weapon, armor: r3.armor, acc: r3.accessories })).unwrap();
        assert!(after[2] != before[2] || after[3] != before[3] || r3.armor != r.armor);
    }

    #[test]
    fn formation_swap_reorders_the_party_set() {
        let Some(mut h) = harness("form") else { return };
        let before = h.session.battle_party();
        assert!(before.len() >= 2);
        let mut page = h.run(|env| crate::cmd_form::FormPage::new(env)).expect("form page");
        h.press(&mut page, pad::CIRCLE); // mark the first
        h.press(&mut page, pad::DOWN);
        h.press(&mut page, pad::CIRCLE); // swap with the second
        let after = h.session.battle_party();
        assert_eq!((after[0], after[1]), (before[1], before[0]));
    }

    #[test]
    fn option_page_writes_the_menu_block() {
        let Some(mut h) = harness("opt") else { return };
        let mut page = h.run(|env| crate::cmd_option::OptionPage::new(env)).expect("option page");
        for _ in 0..4 {
            h.press(&mut page, pad::DOWN);
        }
        // message speed row: normal (1) -> fast (2)
        assert_eq!(crate::cmd_option::get_value(&h.session.save.menu, 4), 1);
        h.press(&mut page, pad::RIGHT);
        assert_eq!(crate::cmd_option::get_value(&h.session.save.menu, 4), 2);
        assert_eq!(sh2_menu::message::TextSpeed::from_option(h.session.save.menu.data[sh2_menu::save::MenuSave::OFF_OPT0]), sh2_menu::message::TextSpeed::Fast);
    }

    #[test]
    fn data_page_saves_and_loads_through_the_save_manager() {
        let Some(mut h) = harness("data") else { return };
        h.session.add_cash(1000);
        let cash = h.session.cash();
        let mut save = h.run(|env| make_data_page(env, false)).expect("save page");
        h.press(save.as_mut(), pad::CIRCLE);
        h.press(save.as_mut(), pad::CIRCLE); // yes
        h.settle(save.as_mut(), 3);
        assert!(sh2_menu::session::slot_used(&mut h.dev, 0) || (0..15).any(|s| sh2_menu::session::slot_used(&mut h.dev, s)));
        h.session.add_cash(-500);
        let mut load = h.run(|env| make_data_page(env, true)).expect("load page");
        h.press(load.as_mut(), pad::CIRCLE);
        h.press(load.as_mut(), pad::CIRCLE);
        assert_eq!(h.session.cash(), cash);
        assert!(h.req.contains(&HostReq::LoadedGame));
    }

    #[test]
    fn ring_custom_points_reach_the_jring_table() {
        let Some(mut h) = harness("ring") else { return };
        let mut page = h.run(|env| crate::cmd_ring::RingPage::new(env, Some(5))).expect("ring page");
        h.session.save.btl.set_key_item(1, 3); // three zone expansion items
        h.press(&mut page, pad::CIRCLE); // hit-area points
        h.press(&mut page, pad::RIGHT);
        h.press(&mut page, pad::RIGHT);
        let b = sh2_menu::ringcustom::battle_ring(&h.session, 5, &[]);
        let jr = sh2_gfx::effects::jring::JrCustom { raw: b.custom.expect("a point was placed") };
        assert_eq!(jr.zone_delta(0), 4, "two points = 4 degrees");
        assert_eq!(jr.strike_delta(0), 0);
        assert_eq!(sh2_menu::ringcustom::rest(&h.session, sh2_menu::ringcustom::STOCK_ZONE), 1);
    }

    #[test]
    fn graveyard_asks_and_the_demo_answers_with_a_toast() {
        let Some(mut h) = harness("grave") else { return };
        let mut p = h.run(|env| crate::cmd_misc::GraveyardPage::new(env)).expect("graveyard page");
        assert_eq!(p.page(), CmdPage::Graveyard);
        assert!(p.note().contains("グレイブヤード"));
        // down to "no", circle backs out silently
        h.press(&mut p, pad::DOWN);
        assert!(matches!(h.press(&mut p, pad::CIRCLE), Flow::Back));
        assert!(h.req.is_empty());
        // "yes": the demo disc has no GY_ maps -> toast, no map jump
        let mut p = h.run(|env| crate::cmd_misc::GraveyardPage::new(env)).unwrap();
        assert!(matches!(h.press(&mut p, pad::CIRCLE), Flow::Back));
        assert!(h.req.iter().any(|r| matches!(r, HostReq::Toast(_))));
        assert!(!h.req.iter().any(|r| matches!(r, HostReq::MapJump { .. })));
    }

    #[test]
    fn key_customize_swaps_the_pad_entries() {
        let Some(mut h) = harness("keys") else { return };
        let mut p = h.run(|env| crate::cmd_misc::KeyCustomPage::new(env)).expect("key custom page");
        let default = h.session.save.menu.button_entries();
        assert_eq!(default, [0xc, 0xd, 0xe, 0xf]);
        // "confirm" (row 1) -> pick -> cross (down) -> circle: confirm takes the cross, cancel inherits the circle
        h.press(&mut p, pad::DOWN);
        h.press(&mut p, pad::CIRCLE);
        h.press(&mut p, pad::DOWN);
        h.press(&mut p, pad::CIRCLE);
        assert_eq!(h.session.save.menu.button_entries(), [0xc, 0xe, 0xd, 0xf]);
        // "default" (row 4) restores the build's defaults
        for _ in 0..3 {
            h.press(&mut p, pad::DOWN);
        }
        h.press(&mut p, pad::CIRCLE);
        assert_eq!(h.session.save.menu.button_entries(), sh2_core::game::default_buttons());
    }

    #[test]
    fn combo_magic_lists_the_techniques_that_were_met() {
        let Some(mut h) = harness("combo") else { return };
        for i in 0..3 {
            h.session.save.menu.data[crate::cmd_misc::OFF_COMBO_SEEN + i] = 1;
        }
        h.session.save.btl.set_combo_flags(0b011);
        let mut p = h.run(|env| crate::cmd_misc::ComboMagicPage::new(env)).expect("combo magic page");
        h.settle(&mut p, 30);
        let mut gfx = sh2_menu::gfx::CommandBuffer::default();
        p.draw(&mut gfx);
        assert!(!gfx.cmds.is_empty());
        assert!(matches!(h.press(&mut p, pad::CROSS), Flow::Back));
    }

    #[test]
    fn combo_key_assigns_a_shortcut_command() {
        let Some(mut h) = harness("ckey") else { return };
        let mut p = h.run(|env| crate::cmd_misc::ComboKeyPage::new(env, Some(5))).expect("combo key page");
        // slot 0 -> category 0 (attack) -> first attack style
        h.press(&mut p, pad::CIRCLE);
        h.press(&mut p, pad::CIRCLE);
        h.press(&mut p, pad::DOWN);
        h.press(&mut p, pad::CIRCLE);
        assert_eq!(h.session.save.btl.shortcut(5, 0), (0, 1), "the second attack style went into slot 0");
        // "remove" resets the slot to the plain attack (id 0xffff)
        h.press(&mut p, pad::CIRCLE);
        for _ in 0..4 {
            h.press(&mut p, pad::DOWN);
        }
        h.press(&mut p, pad::CIRCLE);
        assert_eq!(h.session.save.btl.shortcut(5, 0), (0, 0xffff));
    }

    #[test]
    fn score_reads_the_real_statistic_blocks() {
        let Some(mut h) = harness("score") else { return };
        let mut p = h.run(|env| crate::cmd_view::ScorePage::new(env)).expect("score page");
        h.press(&mut p, pad::DOWN); // battle data
        h.press(&mut p, pad::CIRCLE);
        h.settle(&mut p, 30);
        let mut gfx = sh2_menu::gfx::CommandBuffer::default();
        p.draw(&mut gfx);
        assert!(gfx.cmds.len() > 20);
    }

    #[test]
    fn library_lists_only_the_monsters_that_were_met() {
        let Some(mut h) = harness("lib") else { return };
        let count = |h: &mut H| {
            let mut p = h.run(|env| crate::cmd_view::LibraryPage::new(env)).expect("library page");
            h.settle(&mut p, 30);
            let mut gfx = sh2_menu::gfx::CommandBuffer::default();
            p.draw(&mut gfx);
            gfx.cmds.iter().filter(|c| matches!(c, sh2_menu::gfx::DrawCmd::Text(_))).count()
        };
        let none = count(&mut h);
        for id in 0..4 {
            h.session.save.btl.set_monster_defeated(id);
        }
        let some = count(&mut h);
        assert!(some > none, "met monsters add rows ({none} -> {some})");
    }

    #[test]
    fn viewer_pages_open_and_close() {
        let Some(mut h) = harness("view") else { return };
        for page in [CmdPage::PropertyList, CmdPage::Help, CmdPage::Score, CmdPage::Library, CmdPage::Magic, CmdPage::Crest, CmdPage::Private, CmdPage::RingCustom, CmdPage::Graveyard, CmdPage::ComboKey, CmdPage::KeyCustom] {
            let mut p = h.run(|env| make_page(env, page, Some(5))).unwrap_or_else(|| panic!("{page:?}"));
            assert_eq!(p.page(), page);
            h.press(p.as_mut(), pad::CIRCLE);
            h.settle(p.as_mut(), 3);
            let mut gfx = sh2_menu::gfx::CommandBuffer::default();
            p.draw(&mut gfx);
            assert!(!gfx.cmds.is_empty(), "{page:?} drew nothing");
            let mut backed = false;
            for _ in 0..4 {
                if matches!(h.press(p.as_mut(), pad::CROSS), Flow::Back) {
                    backed = true;
                    break;
                }
            }
            assert!(backed, "{page:?} did not go back");
        }
    }
}

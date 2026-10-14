//! The viewer pages of the command menu: property list (`CmdPropertyList`, page 15), help (`CmdHelp`, 12), score (`CmdScore`, 13)
//! and library (`CmdLibrary`, 14).
//!
//! All text comes from the menu data tables of `CMDMENU.MSD` (attach 11: help pages, library entries, item / weapon / armor /
//! accessory descriptions) and the page scenes `PLIST.MSD`, `HELP.MSD`, `SCORE.MSD`, `LIBRARY.MSD`; counts and numbers from the save.

use std::sync::Arc;

use sh2_battle::data::SEC_MONSTER;
use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::save::BtlSave;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 21.0;
const VISIBLE: usize = 10;

/// Help text of the data tables: `$` is a line break, `%p<n>` / `%i<n>` are colour / icon codes (dropped).
pub fn clean_text(s: &str) -> String {
    let cs: Vec<char> = s.chars().collect();
    let mut out = String::new();
    let mut i = 0;
    while i < cs.len() {
        match cs[i] {
            '$' => out.push('\n'),
            '%' if i + 1 < cs.len() && cs[i + 1].is_ascii_alphabetic() => {
                i += 2;
                while i < cs.len() && cs[i].is_ascii_digit() {
                    i += 1;
                }
                continue;
            }
            c => out.push(c),
        }
        i += 1;
    }
    out
}

/// The right-hand command list the viewer pages share (window at (380, 25), 18 px rows, arrow cursor).
fn side_menu(g: &mut dyn MenuGfx, cmn: &CommonScene, cursor: &CmdCursor, rows: &[String], sel: usize, active: bool, a: u8) {
    for (i, r) in rows.iter().enumerate() {
        let c = if i == sel { Rgba::new(0x80, 0x80, 0x80, a) } else { Rgba::new(0x6c, 0x6c, 0x78, a) };
        text_run(g, 380.0, 25.0 + i as f32 * 18.0, r, 0, c, Some((1, 1)));
    }
    if active {
        cursor.draw(g, cmn, a);
    }
}

// ----------------------------------------------------------------------------------------------------------------
// property list
// ----------------------------------------------------------------------------------------------------------------

struct PRow {
    id: usize,
    name: String,
    count: u8,
}

pub struct PropertyPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    fence: Option<Arc<SceneTex>>,
    cats: Vec<String>,
    cat: usize,
    in_list: bool,
    rows: Vec<PRow>,
    list: ListState,
    pic: Option<TextureId>,
    pic_key: Option<(usize, usize)>,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    title_img: Option<(TextureId, (u32, u32))>,
}

impl PropertyPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/PLIST.MSD")?;
        let fence = env.nested_scene("MENU/MSD/PLIST.MSD", 2);
        let cats = (0..7).map(|i| scene.msd.text(i).map(sj).unwrap_or_default()).collect();
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = PropertyPage {
            sc,
            slide: Slide::open(0, 240, (204.0, 272.0)),
            scene,
            fence,
            cats,
            cat: 1,
            in_list: false,
            rows: Vec::new(),
            list: ListState::new(VISIBLE, 0),
            pic: None,
            pic_key: None,
            cursor: CmdCursor::new(0.0, 0.0),
            time: 0.0,
            title_img,
        };
        p.rebuild(env);
        p.cursor_to_cat();
        p.cursor.snap();
        Some(p)
    }

    fn cursor_to_cat(&mut self) {
        self.cursor.set_target(378.0, 25.0 + self.cat as f32 * 18.0 + 9.0);
    }

    fn cursor_to_row(&mut self) {
        self.cursor.set_target(38.0, 124.0 + self.list.slot() as f32 * ROW_H + 10.0);
    }

    fn rebuild(&mut self, env: &mut Env) {
        let b = &env.session.save.btl;
        let mut rows = Vec::new();
        match self.cat {
            0 => {
                // crests: the equipped / learned ones
                let n = env.tables.map(|t| t.crests.len()).unwrap_or(0);
                for id in 0..n {
                    if b.skill_learned(id) {
                        let nm = env.name(16, id);
                        rows.push(PRow { id, name: if nm.trim().is_empty() { format!("紋章{}", id + 1) } else { nm }, count: 1 });
                    }
                }
            }
            1 => {
                let n = env.tables.map(|t| t.items.len()).unwrap_or(0);
                for id in 0..n {
                    let c = b.item_count(id);
                    if c > 0 {
                        rows.push(PRow { id, name: env.name(12, id), count: c });
                    }
                }
            }
            3 | 4 | 5 => {
                let (sec, name_sec, off, stride, label) = match self.cat {
                    3 => (sh2_battle::data::SEC_WEAPON, 9, BtlSave::OFF_WEAPONS, 0x34, "武器"),
                    4 => (sh2_battle::data::SEC_ARMOR, 10, BtlSave::OFF_ARMOR, 0x18, "防具"),
                    _ => (sh2_battle::data::SEC_ACCESSORY, 11, BtlSave::OFF_ACCESSORIES, 0x2c, "装飾"),
                };
                let total = env.db.map(|d| d.dat.count(sec, stride)).unwrap_or(0);
                let bag = b.bag() as usize * BtlSave::BAG_STRIDE;
                for id in 0..total {
                    let c = b.data.get(off + bag + id).copied().unwrap_or(0);
                    if c > 0 {
                        let nm = env.name(name_sec, id);
                        rows.push(PRow { id, name: if nm.trim().is_empty() { format!("{label}{id}") } else { nm }, count: c });
                    }
                }
            }
            _ => {}
        }
        self.rows = rows;
        self.list = ListState::new(VISIBLE, self.rows.len());
        self.pic_key = None;
        self.update_pic(env);
    }

    fn update_pic(&mut self, env: &mut Env) {
        let key = self.rows.get(self.list.sel).map(|r| (self.cat, r.id));
        if key != self.pic_key {
            self.pic_key = key;
            self.pic = key.and_then(|(c, id)| {
                let path = match c {
                    1 => format!("MENU/IMG/IT/IT_{id:03}.TEX"),
                    3 => format!("MENU/IMG/WE/WE_{id:03}.TEX"),
                    4 => format!("MENU/IMG/AM/AM_{id:03}.TEX"),
                    5 => format!("MENU/IMG/AC/AC_{id:03}.TEX"),
                    _ => return None,
                };
                env.image(&path)
            });
        }
    }

    fn description(&self) -> String {
        let Some(r) = self.rows.get(self.list.sel) else { return String::new() };
        let ty = match self.cat {
            1 => 11,
            3 => 8,
            4 => 9,
            5 => 10,
            _ => return String::new(),
        };
        clean_text(&sj(self.sc.mdt.mdt_str(ty, r.id, 1)))
    }
}

impl Page for PropertyPage {
    fn page(&self) -> CmdPage {
        CmdPage::PropertyList
    }
    fn title(&self) -> usize {
        34
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        if self.in_list {
            let d = self.description();
            if !d.is_empty() {
                return d;
            }
        }
        self.scene.msd.text_entry(self.cat).map(|e| sj(e.1)).unwrap_or_default()
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        if !self.in_list {
            if keys & padbit::UP != 0 {
                self.cat = (self.cat + 6) % 7;
                env.sound(MenuSe::CursorMove);
                self.cursor_to_cat();
                self.rebuild(env);
            } else if keys & padbit::DOWN != 0 {
                self.cat = (self.cat + 1) % 7;
                env.sound(MenuSe::CursorMove);
                self.cursor_to_cat();
                self.rebuild(env);
            } else if keys & padbit::CIRCLE != 0 {
                if self.rows.is_empty() {
                    env.sound(MenuSe::Buzzer);
                } else {
                    env.sound(MenuSe::Decide);
                    self.in_list = true;
                    self.cursor_to_row();
                    self.cursor.snap();
                }
            } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                env.sound(MenuSe::Cancel);
                return Flow::Back;
            }
        } else if self.list.key(keys) {
            env.sound(MenuSe::CursorMove);
            self.cursor_to_row();
            self.update_pic(env);
        } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
            env.sound(MenuSe::Cancel);
            self.in_list = false;
            self.cursor_to_cat();
            self.cursor.snap();
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        side_menu(g, &self.sc.cmn, &self.cursor, &self.cats, self.cat, !self.in_list, a);
        if let Some(f) = &self.fence {
            draw_fence(g, f, 38.0, 80.0, a, true);
        }
        if self.rows.is_empty() {
            let m = self.scene.msd.resource_bytes(self.cat).map(sj).unwrap_or_default();
            text_run(g, 50.0, 130.0, &m.replace('$', "\n"), 0, Rgba::new(0x70, 0x70, 0x78, a), None);
        }
        for (slot, row) in self.rows.iter().skip(self.list.top).take(VISIBLE).enumerate() {
            let y = 124.0 + slot as f32 * ROW_H;
            let sel = self.in_list && self.list.top + slot == self.list.sel;
            if sel {
                row_bar(g, 40.0, y, 184.0, ROW_H - 1.0, a);
            }
            draw_icon(g, &self.sc.cmn, 12, 42.0, y, a);
            let c = if sel { Rgba::new(0x80, 0x80, 0x30, a) } else { white };
            text_run(g, 58.0, y + 1.0, &row.name, 0, c, Some((1, 1)));
            text_run(g, 202.0, y + 1.0, &cfmt("%3d", &[row.count.into()]), 0, c, Some((1, 1)));
        }
        draw_scroll_marks(g, 130.0, 124.0, 124.0 + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        if let Some(r) = self.rows.get(self.list.sel) {
            if self.pic.is_some() || self.cat == 0 {
                general_frame(g, &self.sc.cmn, 262.0, 54.0, 214.0, 290.0, a);
                blit(g, self.pic, 266.0, 80.0, 204.0, 256.0, (0.0, 0.0, 204.0, 256.0), white);
                text_run(g, 270.0, 58.0, &r.name, 0, white, Some((1, 1)));
            }
        }
        if self.in_list {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// help
// ----------------------------------------------------------------------------------------------------------------

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum HelpMode {
    Cats,
    Entries,
    Text,
}

pub struct HelpPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    /// `(name, first entry, count)` of the categories (data table chunk 16)
    cats: Vec<(String, usize, usize)>,
    cat: usize,
    list: ListState,
    entries: Vec<(usize, String)>,
    page: usize,
    mode: HelpMode,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    title_img: Option<(TextureId, (u32, u32))>,
}

impl HelpPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/HELP.MSD")?;
        let m = &sc.mdt;
        let mut cats = Vec::new();
        let mut first = 0usize;
        for i in 0..m.mdt_count(16) {
            let count = m.mdt_data(16, i).first().copied().unwrap_or(0) as usize;
            cats.push((sj(m.mdt_str(16, i, 0)), first, count));
            first += count;
        }
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = HelpPage {
            sc,
            scene,
            cats,
            cat: 0,
            list: ListState::new(VISIBLE, 0),
            entries: Vec::new(),
            page: 0,
            mode: HelpMode::Cats,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(0, 240, (340.0, 316.0)),
            time: 0.0,
            title_img,
        };
        p.load_entries();
        p.cursor_to_cat();
        p.cursor.snap();
        Some(p)
    }

    fn load_entries(&mut self) {
        let (_, first, count) = self.cats.get(self.cat).cloned().unwrap_or((String::new(), 0, 0));
        let m = &self.sc.mdt;
        self.entries = (first..first + count).map(|i| (i, sj(m.mdt_str(17, i, 0)))).filter(|e| !e.1.is_empty()).collect();
        self.list = ListState::new(VISIBLE, self.entries.len());
    }

    fn pages(&self) -> Vec<String> {
        let Some((idx, _)) = self.entries.get(self.list.sel) else { return vec![] };
        (1..=6).map(|k| clean_text(&sj(self.sc.mdt.mdt_str(17, *idx, k)))).filter(|t| !t.trim().is_empty()).collect()
    }

    fn cursor_to_cat(&mut self) {
        self.cursor.set_target(378.0, 25.0 + self.cat as f32 * 18.0 + 9.0);
    }
    fn cursor_to_row(&mut self) {
        self.cursor.set_target(46.0, 80.0 + self.list.slot() as f32 * ROW_H + 10.0);
    }
}

impl Page for HelpPage {
    fn page(&self) -> CmdPage {
        CmdPage::Help
    }
    fn title(&self) -> usize {
        5
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        let name = match self.mode {
            HelpMode::Cats => self.cats.get(self.cat).map(|c| c.0.clone()).unwrap_or_default(),
            _ => self.entries.get(self.list.sel).map(|e| e.1.clone()).unwrap_or_default(),
        };
        let fmt = self.scene.msd.text_entry(0).map(|e| sj(e.1)).unwrap_or_default();
        cfmt(&fmt, &[name.into()])
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into()), (Button::Dpad, "ページ".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        match self.mode {
            HelpMode::Cats => {
                let n = self.cats.len().max(1);
                if keys & padbit::UP != 0 {
                    self.cat = (self.cat + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_cat();
                    self.load_entries();
                } else if keys & padbit::DOWN != 0 {
                    self.cat = (self.cat + 1) % n;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_cat();
                    self.load_entries();
                } else if keys & padbit::CIRCLE != 0 && !self.entries.is_empty() {
                    env.sound(MenuSe::Decide);
                    self.mode = HelpMode::Entries;
                    self.cursor_to_row();
                    self.cursor.snap();
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            HelpMode::Entries => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_row();
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.mode = HelpMode::Text;
                    self.page = 0;
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = HelpMode::Cats;
                    self.cursor_to_cat();
                    self.cursor.snap();
                }
            }
            HelpMode::Text => {
                let n = self.pages().len().max(1);
                if keys & (padbit::RIGHT | padbit::R1 | padbit::DOWN) != 0 && self.page + 1 < n {
                    self.page += 1;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::LEFT | padbit::L1 | padbit::UP) != 0 && self.page > 0 {
                    self.page -= 1;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE | padbit::CIRCLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = HelpMode::Entries;
                }
            }
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let names: Vec<String> = self.cats.iter().map(|c| c.0.clone()).collect();
        side_menu(g, &self.sc.cmn, &self.cursor, &names, self.cat, self.mode == HelpMode::Cats, a);
        if self.mode == HelpMode::Entries {
            general_frame(g, &self.sc.cmn, 40.0, 70.0, 320.0, 232.0, a);
            for (slot, (_, name)) in self.entries.iter().skip(self.list.top).take(VISIBLE).enumerate() {
                let y = 80.0 + slot as f32 * ROW_H;
                let sel = self.list.top + slot == self.list.sel;
                if sel && self.mode == HelpMode::Entries {
                    row_bar(g, 46.0, y, 300.0, ROW_H - 1.0, a);
                }
                text_run(g, 62.0, y + 1.0, name, 0, if sel { Rgba::new(0x80, 0x80, 0x30, a) } else { white }, Some((1, 1)));
            }
            draw_scroll_marks(g, 200.0, 80.0, 80.0 + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        }
        if self.mode == HelpMode::Text {
            let pages = self.pages();
            general_frame(g, &self.sc.cmn, 20.0, 72.0, 340.0, 316.0, a);
            let title = self.entries.get(self.list.sel).map(|e| e.1.clone()).unwrap_or_default();
            text_run(g, 34.0, 80.0, &title, 0, Rgba::new(0x80, 0xc0, 0xff, a), Some((1, 1)));
            if let Some(t) = pages.get(self.page) {
                for (i, l) in t.lines().take(14).enumerate() {
                    text_run(g, 34.0, 108.0 + i as f32 * 18.0, l, 14, white, Some((1, 1)));
                }
            }
            if pages.len() > 1 {
                text_run(g, 300.0, 368.0, &format!("{}/{}", self.page + 1, pages.len()), 14, white, None);
            }
        }
        if self.mode != HelpMode::Text {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// score
// ----------------------------------------------------------------------------------------------------------------

pub struct ScorePage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    sel: usize,
    detail: bool,
    totals: sh2_menu::score::ScoreTotals,
    play_ms: u64,
    cursor: CmdCursor,
    slide: Slide,
}

/// Rows of the score screens as `(label index of the score scene, GetScore case)`: screen 1 = battle data, screen 2 = ring data,
/// screens 0 / 3 (grand total, battles joined ranking) show the battle count only (the rank tables are not ported).
fn score_rows(screen: usize) -> Vec<(usize, usize)> {
    match screen {
        1 => vec![(4, 0), (14, 0xa), (15, 0xb), (16, 0xc), (17, 0xd), (18, 0xe), (19, 0xf), (20, 0x10), (21, 0x11), (22, 0x12), (23, 0x13), (13, 9)],
        2 => (1..=8).map(|c| (4 + c, c)).collect(),
        _ => vec![(4, 0), (13, 9)],
    }
}

impl ScorePage {
    /// The save's statistic blocks (retail) plus what the session keeps for the demo shaped save.
    fn totals(env: &Env) -> sh2_menu::score::ScoreTotals {
        let mut t = sh2_menu::score::ScoreTotals::from_save(&env.session.save.btl, &env.session.save.menu);
        if !env.session.save.btl.is_retail() {
            t.battles = env.session.battles_won;
        }
        t.distance_km = env.session.distance / 1000.0;
        t
    }

    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/SCORE.MSD")?;
        let mut p = ScorePage {
            sc,
            scene,
            sel: 0,
            detail: false,
            totals: Self::totals(env),
            play_ms: env.session.play_ms,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(0, 300, (434.0, 332.0)),
        };
        p.cursor.set_target(378.0, 25.0 + 9.0);
        p.cursor.snap();
        Some(p)
    }
}

impl Page for ScorePage {
    fn page(&self) -> CmdPage {
        CmdPage::Score
    }
    fn title(&self) -> usize {
        6
    }
    fn note(&self) -> String {
        let e = self.scene.msd.text_entry(self.sel).map(|e| sj(e.1)).unwrap_or_default();
        e.replace("%d位“%s”", "—").replace("%d", "-").replace("%s", "-")
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into())]
    }
    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.totals = Self::totals(env);
        self.play_ms = env.session.play_ms;
        if !self.detail {
            if keys & padbit::UP != 0 {
                self.sel = (self.sel + 3) % 4;
                env.sound(MenuSe::CursorMove);
            } else if keys & padbit::DOWN != 0 {
                self.sel = (self.sel + 1) % 4;
                env.sound(MenuSe::CursorMove);
            } else if keys & padbit::CIRCLE != 0 {
                env.sound(MenuSe::Decide);
                self.detail = true;
            } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                env.sound(MenuSe::Cancel);
                return Flow::Back;
            }
            self.cursor.set_target(378.0, 25.0 + self.sel as f32 * 18.0 + 9.0);
        } else if keys & (padbit::CROSS | padbit::TRIANGLE | padbit::CIRCLE) != 0 {
            env.sound(MenuSe::Cancel);
            self.detail = false;
        }
        Flow::Stay
    }
    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let m = &self.scene.msd;
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let rows: Vec<String> = (0..4).map(|i| m.text(i).map(sj).unwrap_or_default()).collect();
        side_menu(g, &self.sc.cmn, &self.cursor, &rows, self.sel, !self.detail, a);
        if !self.detail {
            return;
        }
        general_frame(g, &self.sc.cmn, 40.0, 58.0, 434.0, 332.0, a);
        text_run(g, 60.0, 66.0, &rows[self.sel], 0, Rgba::new(0x80, 0xc0, 0xff, a), Some((1, 1)));
        // value rows (labels = text table 4..24, values = `GetScore` over the save's statistic blocks)
        let rows = score_rows(self.sel);
        let t = (self.play_ms / 1000) as u32;
        let row_h = if rows.len() > 8 { 22.0 } else { 26.0 };
        for (k, (label, case)) in rows.iter().enumerate() {
            let y = 96.0 + k as f32 * row_h;
            text_run(g, 70.0, y, &m.text(*label).map(sj).unwrap_or_default(), 0, white, Some((1, 1)));
            text_right(g, 470.0, y, &self.totals.value(*case).text(), 0, white, Some((1, 1)));
        }
        if self.sel == 0 {
            let y = 96.0 + rows.len() as f32 * row_h;
            let label = if sh2_core::boot::is_retail() { "Play Time" } else { "プレイタイム" };
            text_run(g, 70.0, y, label, 0, white, Some((1, 1)));
            text_right(g, 470.0, y, &format!("{}:{:02}:{:02}", t / 3600, (t / 60) % 60, t % 60), 0, white, Some((1, 1)));
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// library
// ----------------------------------------------------------------------------------------------------------------

pub struct LibraryPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    tab: usize,
    in_list: bool,
    /// `(data table row, name)`
    rows: Vec<(usize, String)>,
    list: ListState,
    stats: Vec<(String, String)>,
    /// record -> the monster id that is shown for it
    first_met: std::collections::HashMap<usize, usize>,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
}

impl LibraryPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/LIBRARY.MSD")?;
        let mut p = LibraryPage {
            sc,
            scene,
            tab: 0,
            in_list: false,
            rows: Vec::new(),
            list: ListState::new(VISIBLE, 0),
            stats: Vec::new(),
            first_met: Default::default(),
            cursor: CmdCursor::new(378.0, 34.0),
            slide: Slide::open(0, 200, (172.0, 300.0)),
            time: 0.0,
        };
        p.cursor.snap();
        p.rebuild(env);
        Some(p)
    }

    /// Monster ids of library record `i` (`MenuDataMonster`: demo `+0x11` count / ids from `+0x12`, retail `+0x49 >> 3` / ids from `+0x4a`).
    fn monster_ids(&self, i: usize) -> Vec<usize> {
        let d = self.sc.mdt.mdt_data(20, i);
        let (n, first) = if sh2_core::boot::is_retail() { ((d.get(1).copied().unwrap_or(0) >> 3) as usize, 2) } else { (d.get(1).copied().unwrap_or(0) as usize, 2) };
        (0..n.min(8)).filter_map(|k| d.get(first + k * 2..first + k * 2 + 2)).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).collect()
    }

    /// `CmdLibrary::SetMonster` / `FindNPC`: a record is listed once one of its monsters has been met (`BTL0` met bit set) or the NPC has been
    /// encountered (`FLDa` NP nibble); the shown monster is the first met one.
    fn rebuild(&mut self, env: &mut Env) {
        let sc = self.sc.clone();
        let m = &sc.mdt;
        let (ty, count) = if self.tab == 0 { (20u16, m.mdt_count(20)) } else { (19u16, m.mdt_count(19)) };
        let reveal_all = std::env::var_os("SH2_LIBRARY_ALL").is_some();
        let base = m.mdt_base(19) as usize;
        let mut first_met = std::mem::take(&mut self.first_met);
        let this = &*self;
        self.rows = (0..count)
            .filter_map(|i| {
                let short = sj(m.mdt_str(ty, i, 1));
                if self.tab == 0 {
                    let met = this.monster_ids(i).into_iter().find(|&id| env.session.save.btl.monster_defeated(id));
                    let id = match met {
                        Some(id) => id,
                        None if reveal_all => this.monster_ids(i).first().copied()?,
                        None => return None,
                    };
                    if short.is_empty() || short == "未定" {
                        return None;
                    }
                    first_met.insert(i, id);
                    let n = env.name(8, id);
                    Some((i, if n.trim().is_empty() { short.clone() } else { n }))
                } else {
                    if env.session.save.field.npc_level(i + base) == 0 && !reveal_all {
                        return None;
                    }
                    if short.is_empty() {
                        return None;
                    }
                    Some((i, sj(m.mdt_str(ty, i, 0))))
                }
            })
            .collect();
        self.first_met = first_met;
        self.list = ListState::new(VISIBLE, self.rows.len());
        self.update_stats(env);
    }

    fn update_stats(&mut self, env: &Env) {
        self.stats.clear();
        if self.tab != 0 {
            return;
        }
        let Some((i, _)) = self.rows.get(self.list.sel) else { return };
        let Some(db) = env.db else { return };
        let id = self.first_met.get(i).copied().unwrap_or(*i);
        if let Some(mon) = db.monster(id) {
            let _ = SEC_MONSTER;
            // the retail scene inserted four path strings before `HP.` and one more before the status-down labels
            let lab = |k: usize| {
                let k = if sh2_core::boot::is_retail() {
                    match k {
                        8..=19 => k + 4,
                        29..=34 => k + 1,
                        o => o,
                    }
                } else {
                    k
                };
                self.scene.msd.resource_bytes(k).map(sj).unwrap_or_default()
            };
            self.stats = vec![
                (lab(8), cfmt("%3d", &[mon.hp.into()])),
                (lab(9), cfmt("%3d", &[mon.mp.into()])),
                (lab(11), cfmt("%7d", &[mon.exp.into()])),
                (lab(12), cfmt("%7d", &[mon.cash.into()])),
                (lab(29), cfmt("%3d", &[mon.patk.into()])),
                (lab(30), cfmt("%3d", &[mon.pdef.into()])),
                (lab(31), cfmt("%3d", &[mon.satk.into()])),
                (lab(32), cfmt("%3d", &[mon.sdef.into()])),
                (lab(33), cfmt("%3d", &[mon.agl.into()])),
                (lab(34), cfmt("%3d", &[mon.luc.into()])),
            ];
        }
    }

    fn desc(&self) -> String {
        let ty = if self.tab == 0 { 20 } else { 19 };
        let Some((i, _)) = self.rows.get(self.list.sel) else { return String::new() };
        let k = if self.tab == 0 { 2 } else { 3 };
        clean_text(&sj(self.sc.mdt.mdt_str(ty, *i, k)))
    }
}

impl Page for LibraryPage {
    fn page(&self) -> CmdPage {
        CmdPage::Library
    }
    fn title(&self) -> usize {
        7
    }
    fn note(&self) -> String {
        if self.in_list {
            let ty = if self.tab == 0 { 20 } else { 19 };
            return self.rows.get(self.list.sel).map(|(i, _)| sj(self.sc.mdt.mdt_str(ty, *i, if self.tab == 0 { 1 } else { 2 }))).unwrap_or_default();
        }
        self.scene.msd.text_entry(self.tab).map(|e| sj(e.1)).unwrap_or_default()
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        if !self.in_list {
            if keys & (padbit::UP | padbit::DOWN) != 0 {
                self.tab ^= 1;
                env.sound(MenuSe::CursorMove);
                self.cursor.set_target(378.0, 25.0 + self.tab as f32 * 18.0 + 9.0);
                self.rebuild(env);
            } else if keys & padbit::CIRCLE != 0 {
                if self.rows.is_empty() {
                    env.sound(MenuSe::Buzzer);
                } else {
                    env.sound(MenuSe::Decide);
                    self.in_list = true;
                }
            } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                env.sound(MenuSe::Cancel);
                return Flow::Back;
            }
        } else if self.list.key(keys) {
            env.sound(MenuSe::CursorMove);
            self.update_stats(env);
        } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
            env.sound(MenuSe::Cancel);
            self.in_list = false;
        }
        if self.in_list {
            self.cursor.set_target(32.0, 80.0 + self.list.slot() as f32 * ROW_H + 10.0);
        } else {
            self.cursor.set_target(378.0, 25.0 + self.tab as f32 * 18.0 + 9.0);
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let tabs: Vec<String> = (0..2).map(|i| self.scene.msd.text(i).map(sj).unwrap_or_default()).collect();
        side_menu(g, &self.sc.cmn, &self.cursor, &tabs, self.tab, !self.in_list, a);
        general_frame(g, &self.sc.cmn, 30.0, 70.0, 190.0, 232.0, a);
        if self.rows.is_empty() {
            text_run(g, 40.0, 90.0, &self.scene.msd.text(2).map(sj).unwrap_or_default(), 14, white, None);
        }
        for (slot, (_, name)) in self.rows.iter().skip(self.list.top).take(VISIBLE).enumerate() {
            let y = 80.0 + slot as f32 * ROW_H;
            let sel = self.in_list && self.list.top + slot == self.list.sel;
            if sel {
                row_bar(g, 36.0, y, 176.0, ROW_H - 1.0, a);
            }
            text_run(g, 42.0, y + 1.0, name, 0, if sel { Rgba::new(0x80, 0x80, 0x30, a) } else { white }, Some((1, 1)));
        }
        draw_scroll_marks(g, 125.0, 80.0, 80.0 + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        if let Some((_, name)) = self.rows.get(self.list.sel) {
            general_frame(g, &self.sc.cmn, 230.0, 70.0, 270.0, 300.0, a);
            text_run(g, 240.0, 76.0, name, 0, Rgba::new(0x80, 0xc0, 0xff, a), Some((1, 1)));
            for (i, l) in self.desc().lines().take(8).enumerate() {
                text_run(g, 240.0, 100.0 + i as f32 * 17.0, l, 14, white, Some((1, 1)));
            }
            for (k, (lab, val)) in self.stats.iter().enumerate() {
                let (cx, cy) = (240.0 + (k % 2) as f32 * 128.0, 250.0 + (k / 2) as f32 * 20.0);
                text_run(g, cx, cy, lab, 14, Rgba::new(0x70, 0xc0, 0xff, a), None);
                text_run(g, cx + 50.0, cy, val, 14, white, Some((1, 1)));
            }
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

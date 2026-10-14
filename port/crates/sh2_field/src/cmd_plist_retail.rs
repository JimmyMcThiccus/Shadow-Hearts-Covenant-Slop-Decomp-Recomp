//! Retail `CmdPropertyList` (page 15 "Inventory", US 0x4d75f0.., `Retail_CmdPropertyList_CreateFenceScene` 0x4d8220), checked against live
//! PCSX2 captures (`notes/integration/r5_mn.md`): streak backdrop, the category column of `PLIST.MSD` attach 1 at (380, 25) (Crests / Items /
//! Key Items / Weapons / Armor / Accessories, then Ring Items / Tarot Cards / Aroma Oils once any is owned), the list of the hovered category
//! in the fence of attach 2 at (38, 80) (`Name / Held`, crests `Name / LV`; window 0 (42, 124), 10 rows of 21 px, icon + name + `%3d`) shown
//! already while the column has the cursor, `You have no ...` when empty.  In the list: Notes = the one-line help (US text kinds 0x20 crest,
//! 0x1c item, 0x19 / 0x1a / 0x1b weapon / armour / accessory, 0x23 aroma, 0x25 tarot), crests add the `Crest Magic / MP Use` fence (attach
//! 8 at (260, 216)); report `triangle : Details / square : Sort / L2 R2 : Scroll` (items: `: Explanation`); triangle opens the Details view
//! (crests: attach 7 = the crest page's Info layout; the rest: attach 6 = icon + cyan name, typed description, the picture).

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, TextRun, TextureId};
use sh2_menu::save::BtlSave;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_retail::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 21.0;
const VISIBLE: usize = 10;
const PATH: &str = "MENU/MSD/PLIST.MSD";
/// the Details view: wait before the picture and the typing start, ms per character (as the item / equipment pages)
const VIEW_MS: f32 = 450.0;
const TYPE_DELAY_MS: f32 = 850.0;
const TYPE_MS: f32 = 70.0;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Column,
    List,
    Sort,
    Detail,
}

#[derive(Clone, Debug)]
struct Row {
    id: usize,
    name: String,
    count: i32,
    icon: usize,
    help: String,
}

pub struct RetailInventoryPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    column: Option<Arc<SceneTex>>,
    fence: Option<Arc<SceneTex>>,
    expl: Option<Arc<SceneTex>>,
    crest_detail: Option<Arc<SceneTex>>,
    magic: Option<Arc<SceneTex>>,
    sort_item: Option<Arc<SceneTex>>,
    sort_crest: Option<Arc<SceneTex>>,
    /// visible categories (text table entries 0..8 of the root scene)
    cats: Vec<usize>,
    cat: usize,
    rows: Vec<Row>,
    list: ListState,
    mode: Mode,
    sort_sel: usize,
    /// crest list: the hovered crest's spells (name, MP, help) for the fence / Details
    spells: Vec<(String, i32, String)>,
    pic: Option<TextureId>,
    detail_t: f32,
    cursor: CmdCursor,
    slide: Slide,
    title_img: Option<(TextureId, (u32, u32))>,
}

fn us_text(env: &Env, kind: u8, id: usize) -> String {
    env.db.and_then(|d| d.us()).and_then(|u| u.text(kind, id, -1)).unwrap_or_default()
}

impl RetailInventoryPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = RetailInventoryPage {
            column: env.nested_scene(PATH, 1),
            fence: env.nested_scene(PATH, 2),
            sort_item: env.nested_scene(PATH, 4),
            sort_crest: env.nested_scene(PATH, 5),
            expl: env.nested_scene(PATH, 6),
            crest_detail: env.nested_scene(PATH, 7),
            magic: env.nested_scene(PATH, 8),
            sc,
            scene,
            cats: Vec::new(),
            cat: 0,
            rows: Vec::new(),
            list: ListState::new(VISIBLE, 0),
            mode: Mode::Column,
            sort_sel: 0,
            spells: Vec::new(),
            pic: None,
            detail_t: 0.0,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(0, 240, (204.0, 272.0)),
            title_img,
        };
        p.cats = (0..9).filter(|&c| c < 6 || !p.collect(env, c).is_empty()).collect();
        p.rebuild(env);
        p.place_cursor();
        p.cursor.snap();
        Some(p)
    }

    fn kind(&self) -> usize {
        self.cats.get(self.cat).copied().unwrap_or(0)
    }

    /// The rows of category `c` (0 crests, 1 items, 2 key items, 3 weapons, 4 armour, 5 accessories, 6 ring items, 7 tarot, 8 aroma).
    fn collect(&self, env: &Env, c: usize) -> Vec<Row> {
        let b = &env.session.save.btl;
        let mut v = Vec::new();
        match c {
            0 => {
                let n = env.tables.map(|t| t.crests.len()).unwrap_or(0);
                for id in (0..n).filter(|&id| b.skill_learned(id)) {
                    let lv = env.db.and_then(|d| d.dat.section(20).get(id * 0x1c + 4).copied()).unwrap_or(0);
                    v.push(Row { id, name: us_text(env, 0xa, id), count: lv as i32, icon: 21, help: us_text(env, 0x20, id) });
                }
            }
            1 => {
                let n = env.tables.map(|t| t.items.len()).unwrap_or(0);
                let mode = env.session.save.menu.data.get(0x28c).copied().unwrap_or(0).min(2) as usize;
                let mut order: Vec<usize> = (0..self.sc.mdt.mdt_count(11))
                    .filter_map(|k| {
                        let r = self.sc.mdt.mdt_rec(11, k)?;
                        let o = 0x12 + mode * 2;
                        let id = i16::from_le_bytes([*r.get(o)?, *r.get(o + 1)?]);
                        (id >= 0).then_some(id as usize)
                    })
                    .collect();
                if order.is_empty() {
                    order = (0..n).collect();
                }
                for id in order.into_iter().filter(|&id| id < n && b.item_count(id) > 0) {
                    v.push(Row { id, name: us_text(env, 6, id), count: b.item_count(id) as i32, icon: 12, help: us_text(env, 0x1c, id) });
                }
            }
            2 => {
                // key items 3.. (0..2 are the ring-custom counters)
                for id in 3..sh2_menu::save::retail_btl::KEY_ITEM_COUNT {
                    let n = b.key_item(id);
                    if n > 0 {
                        v.push(Row { id, name: us_text(env, 8, id), count: n as i32, icon: 0x13, help: us_text(env, 0x1d, id).chars().filter(|c| c.is_ascii()).collect() });
                    }
                }
            }
            3 | 4 | 5 => {
                let (sec, off, stride, name_kind, help_kind, icon) = match c {
                    3 => (sh2_battle::data::SEC_WEAPON, BtlSave::OFF_WEAPONS, 0x34, 3u8, 0x19u8, 9usize),
                    4 => (sh2_battle::data::SEC_ARMOR, BtlSave::OFF_ARMOR, 0x18, 4, 0x1a, 10),
                    _ => (sh2_battle::data::SEC_ACCESSORY, BtlSave::OFF_ACCESSORIES, 0x2c, 5, 0x1b, 11),
                };
                let total = env.db.map(|d| d.dat.count(sec, stride)).unwrap_or(0);
                let bag = b.bag() as usize * BtlSave::BAG_STRIDE;
                for id in 0..total {
                    let n = b.data.get(off + bag + id).copied().unwrap_or(0);
                    if n > 0 {
                        let mdt = [8u16, 9, 10][c - 3];
                        let cell = self.sc.mdt.mdt_data(mdt, id).first().copied().map(|x| x as usize).unwrap_or(icon);
                        v.push(Row { id, name: us_text(env, name_kind, id), count: n as i32, icon: cell, help: us_text(env, help_kind, id) });
                    }
                }
            }
            8 => {
                let src = sh2_battle::menu_data::MenuSource { btl: &env.session.save.btl, menu: &env.session.save.menu, pc: 3, retail: true };
                let m = src.aroma_mask();
                for id in (0..8).filter(|i| m & (1 << i) != 0) {
                    v.push(Row { id, name: us_text(env, 0xd, id), count: 1, icon: 0x14, help: us_text(env, 0x23, id) });
                }
            }
            _ => {}
        }
        v
    }

    fn rebuild(&mut self, env: &mut Env) {
        self.rows = self.collect(env, self.kind());
        self.list = ListState::new(VISIBLE, self.rows.len());
        self.refresh(env);
    }

    fn refresh(&mut self, env: &mut Env) {
        self.spells.clear();
        self.pic = None;
        let Some(r) = self.rows.get(self.list.sel).cloned() else { return };
        if self.kind() == 0 {
            if let Some(t) = env.tables {
                if let Some(cr) = t.crests.get(r.id) {
                    let src = sh2_battle::menu_data::MenuSource { btl: &env.session.save.btl, menu: &env.session.save.menu, pc: 0, retail: true };
                    for (k, &m) in cr.magic.iter().enumerate() {
                        if m < 0 || (cr.flags & (1 << k) != 0 && !src.crest_learned(r.id)) {
                            continue;
                        }
                        if let Some(rec) = t.magic.get(m as usize) {
                            self.spells.push((t.magic_name(m as usize).to_string(), rec.mp, us_text(env, 0x21, m as usize)));
                        }
                    }
                }
            }
        } else if self.mode == Mode::Detail {
            let k = self.kind();
            let path = self.scene.msd.text(9 + k).map(sj).unwrap_or_default();
            if path.contains('%') {
                self.pic = env.image(&cfmt(&path, &[(r.id as i32).into()]));
            }
        }
    }

    fn column_origin(&self) -> (f32, f32) {
        self.column.as_ref().and_then(|c| c.msd.window(0)).map(|w| (w.x, w.y)).unwrap_or((380.0, 25.0))
    }
    fn list_origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((42.0, 124.0))
    }

    fn place_cursor(&mut self) {
        let (x, y) = match self.mode {
            Mode::Column => menu_column_tip(self.column_origin(), self.cat),
            Mode::List | Mode::Detail => {
                let (x, y) = self.list_origin();
                (x - 4.0, y + self.list.slot() as f32 * ROW_H + 10.0)
            }
            Mode::Sort => {
                let (x, y) = (260.0, 92.0);
                (x - 6.0, y + self.sort_sel as f32 * 20.0 + 10.0)
            }
        };
        self.cursor.set_target(x, y);
        self.cursor.visible = self.mode != Mode::Detail;
    }

    fn sort_scene(&self) -> Option<&Arc<SceneTex>> {
        if self.kind() == 0 {
            self.sort_crest.as_ref()
        } else {
            self.sort_item.as_ref()
        }
    }
    fn sort_off(&self) -> usize {
        if self.kind() == 0 {
            0x28d
        } else {
            0x28c
        }
    }
}

impl Page for RetailInventoryPage {
    fn page(&self) -> CmdPage {
        CmdPage::PropertyList
    }
    fn title(&self) -> usize {
        34
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn backdrop(&self) -> Option<usize> {
        Some(0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        Some(match self.mode {
            Mode::List if !self.rows.is_empty() => {
                // crests `: Details` (17), the others `: Explanation` (4); sort only for crests / items
                let mut v = vec![(Button::Triangle, if self.kind() == 0 { 17 } else { 4 })];
                if self.kind() <= 1 {
                    v.push((Button::Square, 6));
                }
                if self.rows.len() > VISIBLE {
                    v.push((Button::L2R2, 13));
                }
                v
            }
            _ => Vec::new(),
        })
    }
    fn note(&self) -> String {
        match self.mode {
            Mode::Column => self.scene.msd.text_entry(self.kind()).map(|e| sj(e.1)).unwrap_or_default(),
            Mode::List => self.rows.get(self.list.sel).map(|r| r.help.split("/%i").next().unwrap_or("").to_string()).unwrap_or_default(),
            Mode::Sort => self.sort_scene().and_then(|s| s.msd.text_entry(self.sort_sel)).map(|e| sj(e.1)).unwrap_or_default(),
            Mode::Detail => self.scene.msd.text_entry(9 + self.kind()).map(|e| sj(e.1)).unwrap_or_default(),
        }
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.detail_t += DT;
        match self.mode {
            Mode::Column => {
                let n = self.cats.len().max(1);
                if keys & padbit::UP != 0 {
                    self.cat = (self.cat + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                    self.rebuild(env);
                } else if keys & padbit::DOWN != 0 {
                    self.cat = (self.cat + 1) % n;
                    env.sound(MenuSe::CursorMove);
                    self.rebuild(env);
                } else if keys & padbit::CIRCLE != 0 {
                    if self.rows.is_empty() {
                        env.sound(MenuSe::Buzzer);
                    } else {
                        env.sound(MenuSe::Decide);
                        self.mode = Mode::List;
                        self.refresh(env);
                    }
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::List => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                    self.refresh(env);
                } else if keys & padbit::TRIANGLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Detail;
                    self.detail_t = 0.0;
                    self.refresh(env);
                } else if keys & padbit::SQUARE != 0 && self.kind() <= 1 {
                    env.sound(MenuSe::Decide);
                    self.sort_sel = env.session.save.menu.data.get(self.sort_off()).copied().unwrap_or(0).min(2) as usize;
                    self.mode = Mode::Sort;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Column;
                }
            }
            Mode::Sort => {
                if keys & padbit::UP != 0 {
                    self.sort_sel = (self.sort_sel + 2) % 3;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.sort_sel = (self.sort_sel + 1) % 3;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    let off = self.sort_off();
                    if let Some(b) = env.session.save.menu.data.get_mut(off) {
                        *b = self.sort_sel as u8;
                    }
                    self.rebuild(env);
                    self.mode = Mode::List;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                }
            }
            Mode::Detail => {
                if self.list.key(keys & (padbit::UP | padbit::DOWN)) {
                    env.sound(MenuSe::CursorMove);
                    self.detail_t = 0.0;
                    self.refresh(env);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                    self.refresh(env);
                }
            }
        }
        self.place_cursor();
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        // category column
        let labels: Vec<String> = self.cats.iter().map(|&c| self.scene.msd.text(c).map(sj).unwrap_or_default()).collect();
        let rec = self.column.as_ref().and_then(|c| c.msd.menu_text(0));
        draw_menu_column(g, self.column_origin(), &rec, &labels, Some(self.cat), &[], a);
        if self.mode == Mode::Detail {
            self.draw_detail(g, a);
            return;
        }
        self.draw_list(g, a);
        if self.kind() == 0 && self.mode != Mode::Column {
            self.draw_magic(g, a);
        }
        if self.mode == Mode::Sort {
            self.draw_sort(g, a);
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

impl RetailInventoryPage {
    /// The fence (attach 2: `Name / Held`, crests `Name / LV` = resources 2 / 3) and the rows of window 0.
    fn draw_list(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(f) = &self.fence else { return };
        let m = &f.msd;
        let (fx, fy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((38.0, 80.0));
        if let Some(p) = m.polygon(0) {
            gs_poly(g, &p, fx, fy, a);
        }
        for i in 0..m.count(sh2_menu::msd::ChunkType::Sprite) {
            if let Some(s) = m.sprite(i) {
                draw_sprite_rec(g, &s, self.sc.fence_tex, fx, fy, a);
            }
        }
        let crest = self.kind() == 0;
        for k in 0..2 {
            if let Some(t) = m.menu_text(k) {
                let label = m.resource_bytes(if crest { 2 + k } else { k }).map(sj).unwrap_or_default();
                text_run_h(g, fx + t.x, fy + t.y - 1.0, &label, 0, white(a), Some((1, 1)), TextRun::hscale_of(t.flags));
            }
        }
        let (lx, ly) = self.list_origin();
        let root = &self.scene.msd;
        let (nx, _, hs) = rec_at(&root.menu_text(0), 16.0, 0.0);
        let (cx, _, _) = rec_at(&root.menu_text(1), 160.0, 0.0);
        if self.rows.is_empty() {
            let s = root.resource_bytes(self.kind()).map(sj).unwrap_or_default();
            for (i, l) in s.split('$').enumerate() {
                text_run_h(g, lx, ly + i as f32 * 20.0, l, 0, white(a), None, hs);
            }
            return;
        }
        let fmt = root.resource_bytes(9).map(sj).unwrap_or_else(|| "%3d".into());
        for (k, r) in self.rows.iter().enumerate().skip(self.list.top).take(VISIBLE) {
            let y = ly + (k - self.list.top) as f32 * ROW_H;
            let sel = self.mode != Mode::Column && k == self.list.sel;
            let c = if sel { rgb(CYAN, a) } else { white(a) };
            draw_icon(g, &self.sc.cmn, r.icon, lx, y, a);
            text_run_h(g, lx + nx, y - 1.0, &r.name, 0, c, None, hs);
            text_run_h(g, lx + cx - 12.0, y - 1.0, &cfmt(&fmt, &[r.count.into()]), 0, c, None, hs);
        }
        if let Some(t) = self.sc.cmn.s.t(4) {
            let mx = fx + 102.0 - 12.0;
            if self.list.can_scroll_up() {
                blit(g, Some(t), mx, ly - 26.0, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), white(a));
            }
            if self.list.can_scroll_down() {
                blit(g, Some(t), mx, fy + 266.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), white(a));
            }
        }
    }

    /// Attach 8 (260, 216): `Crest Magic / MP Use` of the hovered crest.
    fn draw_magic(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(f) = &self.magic else { return };
        let m = &f.msd;
        let (x, y) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((260.0, 216.0));
        if let Some(p) = m.polygon(0) {
            gs_poly(g, &p, x, y, a);
        }
        for i in 0..10 {
            if let Some(s) = m.sprite(i) {
                draw_sprite_rec(g, &s, self.sc.fence_tex, x, y, a);
            }
        }
        let res = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        for k in 0..2 {
            let (tx, ty, hs) = rec_at(&m.menu_text(k), 0.0, 4.0);
            text_run_h(g, x + tx, y + ty - 1.0, &res(k, ["Crest Magic", "MP Use"][k]), 0, white(a), Some((1, 1)), hs);
        }
        let (nx, ny, hs) = rec_at(&m.menu_text(2), 6.0, 28.0);
        let (mx, _, _) = rec_at(&m.menu_text(3), 152.0, 28.0);
        for (i, (n, mp, _)) in self.spells.iter().enumerate().take(4) {
            let ry = y + ny + i as f32 * 20.0;
            text_run_h(g, x + nx, ry - 1.0, n, 0, white(a), None, hs);
            text_run_h(g, x + mx, ry - 1.0, &cfmt(&res(2, "%3d"), &[(*mp).into()]), 0, white(a), None, hs);
        }
    }

    fn draw_sort(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(s) = self.sort_scene() else { return };
        let (sx, sy) = s.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((260.0, 92.0));
        let (bx, by, bw) = (sx - 6.0, sy - 31.0, 113.0);
        let back = self.fence.as_ref().and_then(|f| f.msd.polygon(0));
        fence_box(g, back.as_ref(), self.sc.fence_tex, bx, by, bw, 101.0, a);
        if let Some(f) = &self.fence {
            if let (Some(t), Some(b)) = (f.msd.menu_text(0), f.msd.resource_bytes(0)) {
                let hs = TextRun::hscale_of(t.flags);
                let label = sj(b);
                let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&label));
                text_run_h(g, bx + (bw - tw * hs) * 0.5, by + t.y - 1.0, &label, 0, white(a), Some((1, 1)), hs);
            }
        }
        let hs = s.msd.menu_text(0).map(|t| TextRun::hscale_of(t.flags)).unwrap_or(1.0);
        for i in 0..3 {
            let t = s.msd.text(i).map(sj).unwrap_or_default();
            let c = if i == self.sort_sel { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, sx, sy + i as f32 * 20.0, &t, 0, c, None, hs);
        }
    }

    fn draw_detail(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(r) = self.rows.get(self.list.sel) else { return };
        if self.kind() == 0 {
            if let Some(d) = &self.crest_detail {
                draw_crest_detail(g, &self.sc, d, &r.name, &self.spells, a);
            }
        } else if let Some(e) = &self.expl {
            let text = match self.kind() {
                1 => sj(self.sc.mdt.mdt_str(11, r.id, 1)),
                3 => sj(self.sc.mdt.mdt_str(8, r.id, 1)),
                4 => sj(self.sc.mdt.mdt_str(9, r.id, 1)),
                5 => sj(self.sc.mdt.mdt_str(10, r.id, 1)),
                _ => r.help.clone(),
            };
            draw_explanation(g, &self.sc, e, r.icon, &r.name, self.pic, &text, self.detail_t, a);
        }
        // the pale arrows above / below while there are other rows to page to
        if let Some(t) = self.sc.cmn.s.t(4) {
            if self.list.sel > 0 {
                blit(g, Some(t), 184.0, 40.5, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), white(a));
            }
            if self.list.sel + 1 < self.rows.len() {
                blit(g, Some(t), 184.0, 401.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), white(a));
            }
        }
    }
}

/// Typed-out explanation view (`ITEM.MSD` attach 1 / `PLIST.MSD` attach 6 / `EQUIP.MSD` attach 4: window (12, 70)): icon + cyan name
/// (records 0 / sprite 0), the fading lavender rule (polygons 0 / 1), the description (message record 0, typed at 70 ms per character after
/// 850 ms) and the picture (sprite 1).
#[allow(clippy::too_many_arguments)]
pub fn draw_explanation(g: &mut dyn MenuGfx, sc: &CmdScenes, e: &SceneTex, icon: usize, name: &str, pic: Option<TextureId>, text: &str, t: f32, a: u8) {
    let m = &e.msd;
    let Some(w) = m.window(0) else { return };
    let (ox, oy) = (w.x, w.y);
    if t < VIEW_MS {
        return;
    }
    if let Some(s) = m.sprite(0) {
        draw_icon(g, &sc.cmn, icon, ox + s.x, oy + s.y, a);
    }
    if let Some(tr) = m.menu_text(0) {
        text_run_h(g, ox + tr.x, oy + tr.y, name, 0, rgb(CYAN, a), None, TextRun::hscale_of(tr.flags));
    }
    for i in 0..2 {
        if let Some(p) = m.polygon(i) {
            gs_poly(g, &p, ox, oy, a);
        }
    }
    if let Some(s) = m.sprite(1) {
        let k = ((t - VIEW_MS) / 300.0).clamp(0.0, 1.0);
        let off = (1.0 - k) * (1.0 - k) * 40.0;
        let (pw, ph) = (s.w * 0.82, s.h * 0.82);
        let (cx, cy) = (ox + s.x + s.w * 0.5 - 0.5 + off, oy + s.y + s.h * 0.5 + 3.0 - off);
        let pa = (a as f32 * k.max(0.3)) as u8;
        blit(g, pic, cx - pw * 0.5, cy - ph * 0.5, pw, ph, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(pa));
    }
    if let Some(msg) = m.message(0) {
        let hs = TextRun::hscale_of(msg.common.flags);
        let text = text.replace('$', "\n");
        let lines = text.split('\n').flat_map(|l| wrap_words(g, l, 0, (368.0 - msg.common.x) / hs)).collect::<Vec<_>>();
        let mut i = 0usize;
        'outer: for (li, l) in lines.iter().enumerate() {
            let y = oy + msg.common.y + li as f32 * 20.0;
            let mut x = ox + msg.common.x;
            for ch in l.chars() {
                let tt = t - TYPE_DELAY_MS - i as f32 * TYPE_MS;
                if tt <= 0.0 {
                    break 'outer;
                }
                let ca = (a as f32 * (tt / 140.0).min(1.0)) as u8;
                let cs = ch.to_string();
                text_run_h(g, x, y, &cs, 0, white(ca), None, hs);
                x += g.measure_text(0, &sh2_menu::sjis::encode(&cs)).0 * hs;
                i += 1;
            }
        }
    }
}

/// The crest Info / Details view (`CREST.MSD` attach 5, `PLIST.MSD` attach 7: window (32, 80)): icon + cyan name, the `Magic Name / MP
/// Use` header and one framed group per spell (name, cost, description).
pub fn draw_crest_detail(g: &mut dyn MenuGfx, sc: &CmdScenes, d: &SceneTex, name: &str, spells: &[(String, i32, String)], a: u8) {
    let m = &d.msd;
    let (x, y) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((32.0, 80.0));
    let res = |i: usize, dflt: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| dflt.into());
    if let Some(s) = m.sprite(0) {
        blit(g, sc.cmn.s.t(5), x + s.x, y + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(a));
    }
    let (tx, ty, ths) = rec_at(&m.menu_text(0), 16.0, 0.0);
    text_run_h(g, x + tx, y + ty - 1.0, name, 0, rgb(CYAN, a), None, ths);
    let (hx, hy) = m.group(0).map(|gr| (gr.x, gr.y)).unwrap_or((0.0, 30.0));
    if let Some(p) = m.polygon(0) {
        gs_poly(g, &p, x + hx, y + hy, a);
    }
    for i in 1..=5 {
        if let Some(s) = m.sprite(i) {
            draw_sprite_rec(g, &s, sc.fence_tex, x + hx, y + hy, a);
        }
    }
    for k in 0..2 {
        let (lx, ly, hs) = rec_at(&m.menu_text(1 + k), 5.0, 4.0);
        text_run_h(g, x + hx + lx, y + hy + ly - 1.0, &res(1 + k, ["Magic Name", "MP Use"][k]), 0, white(a), Some((1, 1)), hs);
    }
    let (gx, gy) = m.group(1).map(|gr| (gr.x, gr.y)).unwrap_or((0.0, 66.0));
    for (i, (n, mp, help)) in spells.iter().enumerate().take(4) {
        let (ox, oy) = (x + gx, y + gy + i as f32 * 60.0);
        if let Some(p) = m.polygon(1) {
            gs_poly(g, &p, ox, oy, a);
        }
        for k in 6..=9 {
            if let Some(s) = m.sprite(k) {
                gs_rect(g, ox + s.x, oy + s.y, s.w, s.h, s.rgba, a);
            }
        }
        for k in 1..=5 {
            if let Some(s) = m.sprite(k) {
                draw_sprite_rec(g, &s, sc.fence_tex, ox, oy, a);
            }
        }
        let (nx, ny, hs) = rec_at(&m.menu_text(3), 5.0, 4.0);
        let (mx, _, _) = rec_at(&m.menu_text(4), 192.0, 4.0);
        text_run_h(g, ox + nx, oy + ny - 1.0, n, 0, white(a), None, hs);
        text_run_h(g, ox + mx, oy + ny - 1.0, &cfmt(&res(0, "%3d"), &[(*mp).into()]), 0, white(a), None, hs);
        let (dx, dy, dhs) = rec_at(&m.menu_text(5), 5.0, 28.0);
        let help = help.split("/%i").next().unwrap_or("").replace('$', " ");
        text_run_h(g, ox + dx, oy + dy - 1.0, &help, 0, white(a), None, dhs);
    }
}

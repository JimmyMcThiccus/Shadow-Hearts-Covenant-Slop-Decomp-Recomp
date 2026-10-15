//! Retail `CmdLibrary` (page 14 "Library", US FIELD.BIN: GetReady 0x497b40, Update 0x498300, SelectMenu 0x49a000, SetMonster 0x4996a0,
//! SetNPC 0x499900, `CmdLibraryDetail` 0x49b240 / 0x49b650, `CmdLibraryList` 0x49c6b0, `CmdLibraryInfo` 0x4b45b0 / 0x4b48b0), checked
//! against live PCSX2 captures (`notes/integration/r6_mn2.md`: `libr_*`, `lchar_*`).
//!
//! The page is a 3D viewer: the streak backdrop 0, the record's model in the middle ([`crate::menu_model`], camera = the record's
//! `MenuDataModel`), the tab banner `Monsters  No. n` (LIBRARY.MSD attach 4: group (0, 42), three sprites, the lavender tab name and
//! `No.`), the name with `<` `>` while the tab has more than one entry, a fading rule, the description typed out (`CmdExplain`), the
//! element stone (`CmdElement`, ELEMENT.MSD) and, for people, the portrait medallion (`MENU/FACE/FI_<model>.TEX`, LIBRARY.MSD sprite 1
//! inside window 2 (12, 70)).  The right column holds `Monsters / Characters`.
//!
//! Keys: up / down change the tab, left / right page through the entries, square plays the next action motion (`MenuModelPack::SetAction`),
//! L1 / R1 (held; the retail right stick) turn the model, start / confirm open the list (`CmdLibraryList`), triangle toggles the data
//! view (`CmdLibraryDetail`) of a monster that has been photographed (Snap Shot), cancel leaves.  The report is
//! `Start : List / [triangle : Data] / square : Action / R : Rotate L/R` (`SetReport` 0xb, 0x11, 7, 0xc).
//!
//! Records (CMDMENU.MSD attach 13): monsters = MDT demo key 20 (18 pointers: k1 Notes text, k2 description, **k3 the camera**, k4 idle,
//! k5..k7 actions, k8.. `MenuMotionConnect` pairs; data `+0x48`: byte 1 = count << 3 | bit 1 battle model, ids from +0x4a, list number
//! +0x56); people = key 19 (30 pointers: k0 name, k4 / k5 Notes text by meeting level, k6 / k7 description, k8..k12 motions, k13.. pairs,
//! k29 the camera; data +0x88 = element << 2 | bit 1 battle model | bit 0 portrait, +0x89 bit 0 motion package, u16 +0x8a model).

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, MenuSe, Rgba, TextRun, TextureId};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_retail::*;
use crate::cmd_ui::*;
use crate::menu_model::{MenuCam, ModelReq};

const DT: f32 = 1000.0 / 60.0;
const PATH: &str = "MENU/MSD/LIBRARY.MSD";
/// Model turn per tick while L1 / R1 is held (radians).
const TURN_STEP: f32 = 0.05;
/// Typing of the description (the Items / Equipment explanation speed).
const TYPE_DELAY_MS: f32 = 250.0;
const TYPE_MS: f32 = 22.0;
const CHAR_FADE_MS: f32 = 120.0;
/// Layout measured on the live captures (virtual pixels).
const NAME_POS: (f32, f32) = (29.0, 71.0);
/// the name is drawn wider than the narrow description text (live: "Revenant" 56 px)
const NAME_HS: f32 = 1.1;
const DESC_HS: f32 = 0.87;
const RULE_Y: f32 = 113.0;
const RULE_W: f32 = 208.0;
const DESC_POS: (f32, f32) = (12.0, 120.5);
const DESC_PITCH: f32 = 19.7;
const DESC_W: f32 = 205.0;
const NUMBER_X: f32 = 166.0;
const LIST_VISIBLE: usize = 10;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Browse,
    List,
    Data,
}

#[derive(Clone, Debug, Default)]
struct Entry {
    /// MDT record
    rec: usize,
    /// list number (`No.`)
    no: usize,
    name: String,
    note: String,
    desc: String,
    /// the monster shown for a monster record
    monster: Option<usize>,
    element: u8,
    face: Option<u16>,
    model: Option<ModelReq>,
    /// Snap Shot data available (monsters)
    has_data: bool,
}

pub struct RetailLibraryPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    banner: Option<Arc<SceneTex>>,
    elem: Option<crate::cmd_magic::ElemArt>,
    tab: usize,
    entries: [Vec<Entry>; 2],
    /// current entry per tab (`MENU+0x2ac + tab * 2`)
    sel: [usize; 2],
    mode: Mode,
    list: ListState,
    face: Option<TextureId>,
    /// the data view's rows (label, value)
    stats: Vec<(String, String)>,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    /// time since the entry changed (typing)
    shown_t: f32,
    turn: f32,
    action: u32,
    title_img: Option<(TextureId, (u32, u32))>,
}

fn u16_at(d: &[u8], o: usize) -> usize {
    d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).unwrap_or(0)
}

impl RetailLibraryPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let banner = env.nested_scene(PATH, 4);
        let elem = crate::cmd_magic::ElemArt::load(env);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = RetailLibraryPage {
            sc,
            scene,
            banner,
            elem,
            tab: 0,
            entries: [Vec::new(), Vec::new()],
            sel: [0, 0],
            mode: Mode::Browse,
            list: ListState::new(LIST_VISIBLE, 0),
            face: None,
            stats: Vec::new(),
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(0, 200, (512.0, 448.0)),
            time: 0.0,
            shown_t: 0.0,
            turn: 0.0,
            action: 0,
            title_img,
        };
        p.entries = [p.build_monsters(env), p.build_people(env)];
        // the remembered entry of each tab (`MENU+0x2ac`)
        for t in 0..2 {
            let saved = env.session.save.menu.data.get(0x2ac + t * 2..0x2ae + t * 2).map(|b| i16::from_le_bytes([b[0], b[1]])).unwrap_or(-1);
            if saved >= 0 {
                if let Some(i) = p.entries[t].iter().position(|e| e.rec == saved as usize) {
                    p.sel[t] = i;
                }
            }
        }
        // the first tab with entries
        if p.entries[0].is_empty() && !p.entries[1].is_empty() {
            p.tab = 1;
        }
        p.cursor.set_target(menu_column_tip((380.0, 25.0), p.tab).0, menu_column_tip((380.0, 25.0), p.tab).1);
        p.cursor.snap();
        p.changed(env);
        Some(p)
    }

    fn build_monsters(&self, env: &Env) -> Vec<Entry> {
        let m = &self.sc.mdt;
        let reveal_all = std::env::var_os("SH2_LIBRARY_ALL").is_some();
        let b = &env.session.save.btl;
        let mut out = Vec::new();
        for i in 0..m.mdt_count(20) {
            let d = m.mdt_data(20, i);
            let n = (d.get(1).copied().unwrap_or(0) >> 3) as usize;
            let ids: Vec<usize> = (0..n.min(8)).map(|k| u16_at(d, 2 + k * 2)).collect();
            let found = ids.iter().copied().find(|&id| b.monster_defeated(id));
            let Some(id) = found.or_else(|| reveal_all.then(|| ids.first().copied()).flatten()) else { continue };
            let note = sj(m.mdt_str(20, i, 1));
            if note.is_empty() || note == "未定" {
                continue;
            }
            let raw = env.db.and_then(|db| db.dat.record(sh2_battle::data::SEC_MONSTER, id, 0x38));
            let (chr, element, weapon) = raw
                .map(|r| (u16::from_le_bytes([r[4], r[5]]) as u32, r[0x14] & 7, i16::from_le_bytes([r[0x2e], r[0x2f]])))
                .unwrap_or((0, 0, -1));
            let battle_model = d.get(1).map(|f| f & 2 != 0).unwrap_or(true);
            let motions: Vec<String> = (4..8).map(|k| sj(m.mdt_str(20, i, k))).collect();
            let pairs: Vec<String> = (8..18).map(|k| sj(m.mdt_str(20, i, k))).collect();
            let model = MenuCam::parse(m.mdt_ptr_bytes(20, i, 3, 16)).map(|cam| ModelReq {
                files: if battle_model {
                    sh2_battle::models::chr_files_for(true, chr).to_vec()
                } else {
                    vec![format!("FIELD/MODEL/{chr:03}.SET"), format!("MENU/DAT/{chr:03}.MMS")]
                },
                weapon: (battle_model && weapon >= 0).then(|| sh2_battle::models::weapon_files(true, chr, (weapon % 100) as u32)),
                motions,
                connect: connect_pairs(&pairs),
                cam,
            });
            out.push(Entry {
                rec: i,
                no: u16_at(d, 14) + 1,
                name: {
                    let n = env.name(8, crate::cmd_view::monster_name_row(env, id));
                    if n.trim().is_empty() { note.clone() } else { n }
                },
                note,
                desc: sj(m.mdt_str(20, i, 2)),
                monster: Some(id),
                element,
                face: None,
                model,
                has_data: ids.iter().any(|&id| b.monster_snapped(id)),
            });
        }
        out
    }

    fn build_people(&self, env: &Env) -> Vec<Entry> {
        let m = &self.sc.mdt;
        let reveal_all = std::env::var_os("SH2_LIBRARY_ALL").is_some();
        let base = m.mdt_base(19) as usize;
        let mut out = Vec::new();
        for i in 0..m.mdt_count(19) {
            let level = env.session.save.field.npc_level(i + base);
            let level = if level == 0 && reveal_all { 1 } else { level };
            if level == 0 {
                continue;
            }
            let name = sj(m.mdt_str(19, i, 0));
            if name.is_empty() {
                continue;
            }
            let d = m.mdt_data(19, i);
            let (f0, f1, model_no) = (d.first().copied().unwrap_or(0), d.get(1).copied().unwrap_or(0), u16_at(d, 2) as u32);
            let lv = (level as usize).clamp(1, 2) - 1;
            let pick = |k: usize| {
                let s = sj(m.mdt_str(19, i, k + lv));
                if s.is_empty() { sj(m.mdt_str(19, i, k)) } else { s }
            };
            let motions: Vec<String> = (8..13).map(|k| sj(m.mdt_str(19, i, k))).collect();
            let pairs: Vec<String> = (13..29).map(|k| sj(m.mdt_str(19, i, k))).collect();
            let battle_model = f0 & 2 != 0;
            let model = MenuCam::parse(m.mdt_ptr_bytes(19, i, 29, 16)).map(|cam| ModelReq {
                files: if battle_model {
                    sh2_battle::models::chr_files_for(true, model_no).to_vec()
                } else if f1 & 1 != 0 {
                    vec![format!("FIELD/MODEL/{model_no:03}.SET"), format!("MENU/DAT/{model_no:03}.MMS")]
                } else {
                    vec![format!("FIELD/MODEL/{model_no:03}.SET")]
                },
                weapon: None,
                motions,
                connect: connect_pairs(&pairs),
                cam,
            });
            out.push(Entry {
                rec: i,
                no: out.len() + 1,
                name,
                note: pick(4),
                desc: pick(6),
                monster: None,
                element: f0 >> 2,
                face: (f0 & 1 != 0).then_some(model_no as u16),
                model,
                has_data: false,
            });
        }
        out
    }

    fn cur(&self) -> Option<&Entry> {
        self.entries[self.tab].get(self.sel[self.tab])
    }

    /// `CmdLibrary::Update`: a new entry (or tab) is shown.
    fn changed(&mut self, env: &mut Env) {
        self.shown_t = 0.0;
        self.turn = 0.0;
        self.face = self.cur().and_then(|e| e.face).and_then(|f| env.face(f));
        if self.mode == Mode::Data && !self.cur().map(|e| e.has_data).unwrap_or(false) {
            self.mode = Mode::Browse;
        }
        self.update_stats(env);
        if let Some(e) = self.cur() {
            let (t, rec) = (self.tab, e.rec as i16);
            if let Some(b) = env.session.save.menu.data.get_mut(0x2ac + t * 2..0x2ae + t * 2) {
                b.copy_from_slice(&rec.to_le_bytes());
            }
        }
    }

    /// `CmdLibraryDetail::UpdateScene`: HP. / MP. / EXP. / Cash. / Souls. of the monster (LIBRARY.MSD res 12..18, values `%3d` / `%7d`).
    fn update_stats(&mut self, env: &Env) {
        self.stats.clear();
        let Some(id) = self.cur().and_then(|e| e.monster) else { return };
        let Some(mon) = env.db.and_then(|db| db.monster(id)) else { return };
        let res = |k: usize| self.scene.msd.resource_bytes(k).map(sj).unwrap_or_default();
        self.stats = vec![
            (res(12), cfmt("%3d", &[mon.hp.into()])),
            (res(13), cfmt("%3d", &[mon.mp.into()])),
            (res(15), cfmt("%7d", &[mon.exp.into()])),
            (res(16), cfmt("%7d", &[mon.cash.into()])),
        ];
    }

    fn model_req(&self) -> Option<ModelReq> {
        if self.mode == Mode::List {
            return None;
        }
        self.cur().and_then(|e| e.model.clone())
    }
}

/// `MenuMotionConnect` pairs out of a run of pointer strings (an empty `from` ends the table).
fn connect_pairs(s: &[String]) -> Vec<(String, String)> {
    s.chunks(2).take_while(|c| c.len() == 2 && !c[0].is_empty()).map(|c| (c[0].clone(), c[1].clone())).collect()
}

impl Page for RetailLibraryPage {
    fn backdrop(&self) -> Option<usize> {
        Some(0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        if self.mode == Mode::List || self.cur().is_none() {
            return Some(Vec::new());
        }
        // top to bottom: `Start : List`, [`triangle : Data`], `square : Action`, `R : Rotate L/R`
        let mut v = vec![(Button::Start, 11)];
        if self.cur().map(|e| e.has_data).unwrap_or(false) {
            v.push((Button::Triangle, 17));
        }
        v.extend([(Button::Square, 7), (Button::RStick, 12)]);
        Some(v)
    }
    fn page(&self) -> CmdPage {
        CmdPage::Library
    }
    fn title(&self) -> usize {
        7
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    /// Notes: the tab's explanation (`CmdNote::SetExplanation` with the tab text's second string), live "Details on monsters fought.".
    fn note(&self) -> String {
        // the list shows the selected entry's one-line text
        if self.mode == Mode::List {
            return self.entries[self.tab].get(self.list.sel).map(|e| e.note.clone()).unwrap_or_default();
        }
        let k = if self.cur().is_some() { self.tab } else { 2 };
        self.scene.msd.text_entry(k).map(|e| sj(e.1)).unwrap_or_default()
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        Vec::new()
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        self.shown_t += DT;
        let held = env.cache.held;
        match self.mode {
            Mode::Browse | Mode::Data => {
                if keys & (padbit::UP | padbit::DOWN) != 0 {
                    self.tab ^= 1;
                    env.sound(MenuSe::CursorMove);
                    let tip = menu_column_tip((380.0, 25.0), self.tab);
                    self.cursor.set_target(tip.0, tip.1);
                    self.mode = Mode::Browse;
                    self.changed(env);
                } else if keys & (padbit::LEFT | padbit::RIGHT) != 0 && self.entries[self.tab].len() > 1 {
                    let n = self.entries[self.tab].len();
                    let s = &mut self.sel[self.tab];
                    *s = if keys & padbit::LEFT != 0 { (*s + n - 1) % n } else { (*s + 1) % n };
                    env.sound(MenuSe::CursorMove);
                    self.changed(env);
                } else if keys & padbit::SQUARE != 0 && self.cur().is_some() {
                    self.action = self.action.wrapping_add(1);
                } else if keys & padbit::TRIANGLE != 0 && self.cur().map(|e| e.has_data).unwrap_or(false) {
                    self.mode = if self.mode == Mode::Data { Mode::Browse } else { Mode::Data };
                    self.shown_t = 0.0;
                    env.sound(MenuSe::Decide);
                } else if keys & (padbit::START | padbit::CIRCLE) != 0 {
                    if self.entries[self.tab].is_empty() {
                        env.sound(MenuSe::Buzzer);
                    } else {
                        env.sound(MenuSe::Decide);
                        self.mode = Mode::List;
                        self.list = ListState::new(LIST_VISIBLE, self.entries[self.tab].len());
                        for _ in 0..self.sel[self.tab] {
                            self.list.key(padbit::DOWN);
                        }
                    }
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
                if held & padbit::L1 != 0 {
                    self.turn -= TURN_STEP;
                }
                if held & padbit::R1 != 0 {
                    self.turn += TURN_STEP;
                }
            }
            Mode::List => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::CIRCLE | padbit::START) != 0 {
                    env.sound(MenuSe::Decide);
                    self.sel[self.tab] = self.list.sel;
                    self.mode = Mode::Browse;
                    self.changed(env);
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Browse;
                }
            }
        }
        env.cache.model = self.model_req();
        env.cache.model_ctl = crate::menu_model::ModelCtl { turn: self.turn, action: self.action };
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        if self.mode != Mode::List && self.cur().is_some() {
            crate::menu_model::draw_model_view(g, a);
        }
        self.draw_banner(g, a);
        let tabs: Vec<String> = (0..2).map(|i| self.scene.msd.text(i).map(sj).unwrap_or_default()).collect();
        draw_menu_column(g, (380.0, 25.0), &None, &tabs, Some(self.tab), &[], a);
        match self.cur() {
            None => {
                let s = self.scene.msd.text(2).map(sj).unwrap_or_default();
                text_run_h(g, DESC_POS.0, DESC_POS.1, &s, 0, white(a), Some((1, 1)), 0.8);
            }
            Some(e) => {
                if self.mode == Mode::List {
                    self.draw_list(g, a);
                } else {
                    self.draw_entry(g, e, a);
                }
            }
        }
        if self.mode != Mode::List {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}

impl RetailLibraryPage {
    /// LIBRARY.MSD attach 4 (`CmdLibraryTitle`): three sprites at group (0, 42), the tab name and `No.` in lavender, the number white.
    fn draw_banner(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(b) = &self.banner else { return };
        let m = &b.msd;
        let (ox, oy) = m.group(0).map(|gr| (gr.x, gr.y)).unwrap_or((0.0, 42.0));
        for i in 0..3 {
            if let Some(r) = m.sprite(i) {
                draw_sprite_rec(g, &r, b.t(0), ox, oy, a);
            }
        }
        let lav = rgb(LAVENDER, a);
        if let Some(t) = m.menu_text(0) {
            let s = m.resource_bytes(self.tab).map(sj).unwrap_or_default();
            text_run_h(g, ox + t.x, oy + t.y - 3.0, &s, 2, lav, Some((1, 0)), TextRun::hscale_of(t.flags));
        }
        if self.cur().is_some() {
            let hs = m.menu_text(1).map(|t| TextRun::hscale_of(t.flags)).unwrap_or(0.8);
            let nx = m.menu_text(1).map(|t| t.x).unwrap_or(135.0);
            text_run_h(g, ox + nx, oy + 0.0, &m.resource_bytes(3).map(sj).unwrap_or_else(|| "No.".into()), 2, lav, Some((1, 0)), hs);
            let no = self.cur().map(|e| e.no).unwrap_or(1);
            let fmt = self.scene.msd.resource_bytes(40).map(sj).unwrap_or_else(|| "%3d".into());
            text_run_h(g, NUMBER_X, oy + 0.0, &cfmt(&fmt, &[(no as i32).into()]), 2, white(a), None, 1.0);
        }
    }

    fn draw_entry(&self, g: &mut dyn MenuGfx, e: &Entry, a: u8) {
        // name with the paging arrows (common attach 4, cells left / right)
        let (nx, ny) = NAME_POS;
        let hs = NAME_HS;
        text_run_h(g, nx, ny, &e.name, 0, white(a), Some((1, 1)), hs);
        if self.entries[self.tab].len() > 1 {
            if let Some(t) = self.sc.cmn.s.t(4) {
                let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&e.name));
                blit(g, Some(t), nx - 26.0, ny, 24.0, 22.0, (0.0, 2.0 * 22.0, 24.0, 3.0 * 22.0), white(a));
                blit(g, Some(t), nx + tw * hs + 2.0, ny, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), white(a));
            }
        }
        // the rule (CBMAGIC / EQUIP explain scene polygons: (130, 125, 150) solid to x 100, then fading out to x 208, y 113..117)
        let c0 = Rgba::new(65, 62, 75, a);
        let c1 = Rgba::new(65, 62, 75, 0);
        let quad = |g: &mut dyn MenuGfx, x0: f32, x1: f32, l: Rgba, r: Rgba| {
            g.draw(DrawCmd::Quad { tex: None, v: [vtx(x0, RULE_Y, 0.0, 0.0, l), vtx(x0, RULE_Y + 4.0, 0.0, 0.0, l), vtx(x1, RULE_Y, 0.0, 0.0, r), vtx(x1, RULE_Y + 4.0, 0.0, 0.0, r)], blend: Blend::Alpha });
        };
        quad(g, 0.0, 100.0, c0, c0);
        quad(g, 100.0, RULE_W, c0, c1);
        if self.mode == Mode::Data {
            self.draw_data(g, a);
        } else {
            self.draw_desc(g, &e.desc, a);
        }
        if let Some(el) = &self.elem {
            el.draw(g, e.element, a);
        }
        if e.face.is_some() {
            if let (Some(w), Some(s)) = (self.scene.msd.window(2), self.scene.msd.sprite(1)) {
                face_frame(g, &self.sc.cmn, w.x + s.x - 8.0, w.y + s.y - 6.0, a);
                blit(g, self.face, w.x + s.x, w.y + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(a));
            }
        }
    }

    /// `CmdExplain`: the description typed out a glyph at a time, each glyph fading in.
    fn draw_desc(&self, g: &mut dyn MenuGfx, desc: &str, a: u8) {
        let hs = DESC_HS;
        let text = desc.replace('$', "\n");
        let lines: Vec<String> = text.split('\n').flat_map(|l| wrap_words(g, l, 0, DESC_W / hs)).collect();
        let mut i = 0usize;
        for (li, l) in lines.iter().enumerate() {
            let y = DESC_POS.1 + li as f32 * DESC_PITCH;
            let mut x = DESC_POS.0;
            for ch in l.chars() {
                let tt = self.shown_t - TYPE_DELAY_MS - i as f32 * TYPE_MS;
                if tt <= 0.0 {
                    return;
                }
                let ca = (a as f32 * (tt / CHAR_FADE_MS).min(1.0)) as u8;
                let cs = ch.to_string();
                text_run_h(g, x, y, &cs, 0, white(ca), Some((1, 1)), hs);
                x += g.measure_text(0, &sh2_menu::sjis::encode(&cs)).0 * hs;
                i += 1;
            }
        }
    }

    /// `CmdLibraryDetail` (LIBRARY.MSD window 2 (12, 70); labels mtext 1.. lavender, values mtext 8..): the Snap Shot data.
    fn draw_data(&self, g: &mut dyn MenuGfx, a: u8) {
        let m = &self.scene.msd;
        let (ox, oy) = m.window(2).map(|w| (w.x, w.y)).unwrap_or((12.0, 70.0));
        let rows = [(1usize, 8usize), (2, 9), (3, 10), (4, 11)];
        for (k, (lab, val)) in self.stats.iter().enumerate() {
            let (Some(lt), Some(vt)) = (m.menu_text(rows[k].0), m.menu_text(rows[k].1)) else { continue };
            text_run_h(g, ox + lt.x, oy + lt.y - 3.0, lab, 2, rgb(LAVENDER, a), None, TextRun::hscale_of(lt.flags));
            text_run_h(g, ox + vt.x, oy + vt.y - 1.0, val, 0, white(a), None, TextRun::hscale_of(vt.flags));
        }
    }

    /// `CmdLibraryList` (window 1 (46, 124), 10 rows of 21): `No.` and name, the selected one cyan.
    fn draw_list(&self, g: &mut dyn MenuGfx, a: u8) {
        let (wx, wy) = self.scene.msd.window(1).map(|w| (w.x, w.y)).unwrap_or((46.0, 124.0));
        general_frame(g, &self.sc.cmn, wx - 12.0, wy - 12.0, 300.0, LIST_VISIBLE as f32 * 21.0 + 24.0, a);
        for (slot, e) in self.entries[self.tab].iter().skip(self.list.top).take(LIST_VISIBLE).enumerate() {
            let y = wy + slot as f32 * 21.0;
            let c = if self.list.top + slot == self.list.sel { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, wx, y, &cfmt("%3d", &[(e.no as i32).into()]), 0, c, None, 0.8);
            text_run_h(g, wx + 40.0, y, &e.name, 0, c, None, 0.8);
        }
        draw_scroll_marks(g, wx + 130.0, wy, wy + LIST_VISIBLE as f32 * 21.0, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        // the cursor tip on the selected row
        let tip = (wx - 5.0, wy + self.list.slot() as f32 * 21.0 + 10.0);
        let mut c = self.cursor.clone();
        c.pos = tip;
        c.target = tip;
        c.draw(g, &self.sc.cmn, a);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn connect_pairs_stop_at_the_first_empty_source() {
        let s: Vec<String> = ["mags", "magi", "magi", "mage", "", "", "x", "y"].iter().map(|s| s.to_string()).collect();
        assert_eq!(connect_pairs(&s), vec![("mags".into(), "magi".into()), ("magi".into(), "mage".into())]);
    }
}

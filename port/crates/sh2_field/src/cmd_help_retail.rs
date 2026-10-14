//! Retail `CmdHelp` (page 12 "Help", US `GetReady` 0x48dd90, `CmdHelpMenu::SetNewIcon` 0x48fac0, `CmdHelpClause::UpdateScene` 0x490240,
//! `CmdHelpExplain` 0x490940 / 0x490c90), checked against live PCSX2 captures (`notes/integration/r5_mn.md`).
//!
//! * categories (`HELP.MSD` window 0 at (360, 25), menu data table retail key 18 = demo 16: name, pointer to a `u16` list of entry ids, count)
//!   with the orange `New` mark (attach 1) while one of their visible entries is unread;
//! * entries of the hovered category in window 1 (48, 80), 10 rows of 21 px: an entry (key 19 = demo 17: name, six page strings, flags
//!   `+0x1d`: bit 7 = always listed, bits 0..6 = page count) is listed when bit 7 is set or its `MENU+0x180` bit is (the script's
//!   `SpecialMenu(2, n)`); unread entries are orange, read ones white (`MENU+0x1d0` bit, set when the entry is opened);
//! * the page view (window 2 (20, 72)): the entry name in cyan, the page typed out (`%p4` .. `%p0` = cyan), the `n/m` box at (280, 284) and the
//!   pale arrows while there are other pages; up / down turn the pages.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextRun, TextureId};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_retail::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 21.0;
const VISIBLE: usize = 10;
const PATH: &str = "MENU/MSD/HELP.MSD";
const OFF_UNLOCKED: usize = 0x180;
const OFF_READ: usize = 0x1d0;
/// unread entry / `New` orange (live `help_a`: (242, 118, 32) on the 8-bit frame)
const ORANGE: (u8, u8, u8) = (0x7c, 0x3c, 0x10);
const TYPE_DELAY_MS: f32 = 300.0;
const TYPE_MS: f32 = 35.0;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Cats,
    List,
    Page,
}

struct Cat {
    name: String,
    entries: Vec<usize>,
}

pub struct RetailHelpPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    cats: Vec<Cat>,
    cat: usize,
    list: ListState,
    mode: Mode,
    page: usize,
    page_t: f32,
    /// MENU bit sets, refreshed each tick (unlocked, read)
    unlocked: Vec<u8>,
    read: Vec<u8>,
    cursor: CmdCursor,
    slide: Slide,
    title_img: Option<(TextureId, (u32, u32))>,
}

fn bit(v: &[u8], i: usize) -> bool {
    v.get(i >> 3).map(|b| b & (1 << (i & 7)) != 0).unwrap_or(false)
}

impl RetailHelpPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = RetailHelpPage {
            sc,
            scene,
            cats: Vec::new(),
            cat: 0,
            list: ListState::new(VISIBLE, 0),
            mode: Mode::Cats,
            page: 0,
            page_t: 0.0,
            unlocked: Vec::new(),
            read: Vec::new(),
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(0, 240, (340.0, 316.0)),
            title_img,
        };
        p.sync_bits(env);
        p.build();
        p.list = ListState::new(VISIBLE, p.cur_entries().len());
        p.place_cursor();
        p.cursor.snap();
        Some(p)
    }

    fn sync_bits(&mut self, env: &Env) {
        let d = &env.session.save.menu.data;
        self.unlocked = d.get(OFF_UNLOCKED..OFF_UNLOCKED + 0x20).map(|s| s.to_vec()).unwrap_or_default();
        self.read = d.get(OFF_READ..OFF_READ + 0x20).map(|s| s.to_vec()).unwrap_or_default();
    }

    fn flags(&self, e: usize) -> u8 {
        self.sc.mdt.mdt_data(17, e).get(1).copied().unwrap_or(0)
    }

    fn visible(&self, e: usize) -> bool {
        self.flags(e) & 0x80 != 0 || bit(&self.unlocked, e)
    }

    fn build(&mut self) {
        let m = &self.sc.mdt;
        self.cats = (0..m.mdt_count(16))
            .map(|i| {
                let n = m.mdt_data(16, i).get(0..2).map(|b| i16::from_le_bytes([b[0], b[1]]).max(0) as usize).unwrap_or(0);
                let entries = m.mdt_ptr_bytes(16, i, 1, n * 2).chunks(2).filter_map(|c| (c.len() == 2).then(|| i16::from_le_bytes([c[0], c[1]]))).filter(|&id| id >= 0).map(|id| id as usize).collect();
                Cat { name: sj(m.mdt_str(16, i, 0)), entries }
            })
            .collect();
    }

    fn cur_entries(&self) -> Vec<usize> {
        self.cats.get(self.cat).map(|c| c.entries.iter().copied().filter(|&e| self.visible(e)).collect()).unwrap_or_default()
    }

    fn entry(&self) -> Option<usize> {
        self.cur_entries().get(self.list.sel).copied()
    }

    fn pages(&self, e: usize) -> Vec<String> {
        let n = (self.flags(e) & 0x7f).clamp(1, 6) as usize;
        (1..=n).map(|k| sj(self.sc.mdt.mdt_str(17, e, k))).collect()
    }

    fn origin(&self, w: usize) -> (f32, f32) {
        self.scene.msd.window(w).map(|w| (w.x, w.y)).unwrap_or(match w {
            0 => (360.0, 25.0),
            1 => (48.0, 80.0),
            _ => (20.0, 72.0),
        })
    }

    fn place_cursor(&mut self) {
        let (x, y) = match self.mode {
            Mode::Cats => menu_column_tip(self.origin(0), self.cat),
            Mode::List | Mode::Page => {
                let (x, y) = self.origin(1);
                (x - 4.0, y + self.list.slot() as f32 * ROW_H + 10.0)
            }
        };
        self.cursor.set_target(x, y);
        self.cursor.visible = self.mode != Mode::Page;
    }
}

impl Page for RetailHelpPage {
    // live: the top-lit backdrop (image 1)
    fn page(&self) -> CmdPage {
        CmdPage::Help
    }
    fn title(&self) -> usize {
        5
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn backdrop(&self) -> Option<usize> {
        Some(1)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        Some(if self.mode == Mode::List && self.cur_entries().len() > VISIBLE { vec![(Button::L2R2, 13)] } else { Vec::new() })
    }
    fn note(&self) -> String {
        let res = |i: usize| self.scene.msd.resource_bytes(i).map(sj).unwrap_or_default();
        match self.mode {
            Mode::Cats => cfmt(&res(1), &[self.cats.get(self.cat).map(|c| c.name.as_str()).unwrap_or("").into()]),
            Mode::List => cfmt(&res(2), &[self.entry().map(|e| sj(self.sc.mdt.mdt_str(17, e, 0))).unwrap_or_default().as_str().into()]),
            Mode::Page => cfmt(&res(3), &[self.entry().map(|e| sj(self.sc.mdt.mdt_str(17, e, 0))).unwrap_or_default().as_str().into()]),
        }
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.page_t += DT;
        self.sync_bits(env);
        match self.mode {
            Mode::Cats => {
                let n = self.cats.len().max(1);
                let moved = if keys & padbit::UP != 0 {
                    self.cat = (self.cat + n - 1) % n;
                    true
                } else if keys & padbit::DOWN != 0 {
                    self.cat = (self.cat + 1) % n;
                    true
                } else {
                    false
                };
                if moved {
                    env.sound(MenuSe::CursorMove);
                    self.list = ListState::new(VISIBLE, self.cur_entries().len());
                } else if keys & padbit::CIRCLE != 0 {
                    if self.cur_entries().is_empty() {
                        env.sound(MenuSe::Buzzer);
                    } else {
                        env.sound(MenuSe::Decide);
                        self.mode = Mode::List;
                    }
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::List => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    if let Some(e) = self.entry() {
                        env.sound(MenuSe::Decide);
                        if let Some(b) = env.session.save.menu.data.get_mut(OFF_READ + (e >> 3)) {
                            *b |= 1 << (e & 7);
                        }
                        self.mode = Mode::Page;
                        self.page = 0;
                        self.page_t = 0.0;
                    }
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Cats;
                }
            }
            Mode::Page => {
                let n = self.entry().map(|e| self.pages(e).len()).unwrap_or(1);
                if keys & (padbit::UP | padbit::LEFT) != 0 && self.page > 0 {
                    self.page -= 1;
                    self.page_t = 0.0;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::DOWN | padbit::RIGHT) != 0 && self.page + 1 < n {
                    self.page += 1;
                    self.page_t = 0.0;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::CROSS | padbit::CIRCLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
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
        self.draw_cats(g, a);
        if self.mode == Mode::Page {
            self.draw_page(g, a);
        } else {
            self.draw_list(g, a);
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}

impl RetailHelpPage {
    fn draw_cats(&self, g: &mut dyn MenuGfx, a: u8) {
        let m = &self.scene.msd;
        let (ox, oy) = self.origin(0);
        let (_, _, hs) = rec_at(&m.menu_text(0), 0.0, 0.0);
        for (i, c) in self.cats.iter().enumerate() {
            let y = oy + i as f32 * 20.0;
            let col = if i == self.cat { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, ox, y, &c.name, 0, col, None, hs);
            let new = c.entries.iter().any(|&e| self.visible(e) && !bit(&self.read, e));
            if new {
                let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&c.name));
                if let Some(s) = m.sprite(0) {
                    blit(g, self.scene.t(1), ox + tw * hs + s.x, y + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(a));
                }
            }
        }
    }

    fn draw_list(&self, g: &mut dyn MenuGfx, a: u8) {
        let (ox, oy) = self.origin(1);
        let hs = self.scene.msd.menu_text(1).map(|t| TextRun::hscale_of(t.flags)).unwrap_or(0.8);
        let ents = self.cur_entries();
        for (k, &e) in ents.iter().enumerate().skip(self.list.top).take(VISIBLE) {
            let y = oy + (k - self.list.top) as f32 * ROW_H;
            let sel = self.mode == Mode::List && k == self.list.sel;
            let c = if sel {
                rgb(CYAN, a)
            } else if bit(&self.read, e) {
                white(a)
            } else {
                rgb(ORANGE, a)
            };
            text_run_h(g, ox, y, &sj(self.sc.mdt.mdt_str(17, e, 0)), 0, c, None, hs);
        }
        if let Some(t) = self.sc.cmn.s.t(4) {
            if self.list.can_scroll_up() {
                blit(g, Some(t), ox + 90.0, oy - 24.0, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), white(a));
            }
            if self.list.can_scroll_down() {
                blit(g, Some(t), ox + 90.0, oy + VISIBLE as f32 * ROW_H + 2.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), white(a));
            }
        }
    }

    /// Window 2: name (record 2, cyan), the typed page (message record 0 at (0, 24), 20 px lines, `%pN` colour codes), the page box.
    fn draw_page(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(e) = self.entry() else { return };
        let m = &self.scene.msd;
        let (ox, oy) = self.origin(2);
        let hs = m.menu_text(2).map(|t| TextRun::hscale_of(t.flags)).unwrap_or(0.8);
        text_run_h(g, ox, oy, &sj(self.sc.mdt.mdt_str(17, e, 0)), 0, rgb(CYAN, a), None, hs);
        let pages = self.pages(e);
        let text = pages.get(self.page).cloned().unwrap_or_default();
        let (mx, my) = m.message(0).map(|r| (r.common.x, r.common.y)).unwrap_or((0.0, 24.0));
        let mhs = m.message(0).map(|r| TextRun::hscale_of(r.common.flags)).unwrap_or(0.8);
        let budget = ((self.page_t - TYPE_DELAY_MS) / TYPE_MS).max(0.0) as usize;
        let mut shown = 0usize;
        let mut col = white(a);
        'lines: for (li, line) in text.split('$').enumerate() {
            let y = oy + my + li as f32 * 20.0;
            let mut x = ox + mx;
            let mut it = line.chars().peekable();
            while let Some(ch) = it.next() {
                if ch == '%' {
                    let code = it.next();
                    let mut num = 0u32;
                    while let Some(d) = it.peek().and_then(|c| c.to_digit(10)) {
                        num = num * 10 + d;
                        it.next();
                    }
                    if code == Some('p') {
                        col = if num == 4 { rgb(CYAN, a) } else if num == 1 { rgb(ORANGE, a) } else { white(a) };
                    } else if code == Some('i') {
                        if shown >= budget {
                            break 'lines;
                        }
                        shown += 1;
                        x += draw_inline_icon(g, &self.sc, num, x, y - 1.0, a);
                    }
                    continue;
                }
                if shown >= budget {
                    break 'lines;
                }
                shown += 1;
                // one glyph at a time (each is a cached texture; whole growing prefixes would rasterise a new line every frame)
                let cs = ch.to_string();
                text_run_h(g, x, y, &cs, 0, col, None, mhs);
                x += g.measure_text(0, &sh2_menu::sjis::encode(&cs)).0 * mhs;
            }
        }
        // page box: the four fence sprites at (280, 284) (alpha 64) and `%s/%s`
        for i in 2..=5 {
            if let Some(s) = m.sprite(i) {
                draw_sprite_rec(g, &s, self.sc.fence_tex, ox, oy, a);
            }
        }
        if let Some(p) = m.polygon(0) {
            gs_poly(g, &p, ox, oy, a);
        }
        let (px, py, phs) = rec_at(&m.menu_text(3), 284.0, 286.0);
        let fmt = m.resource_bytes(4).map(sj).unwrap_or_else(|| "%s/%s".into());
        fill(g, ox + 282.0, oy + 286.0, 44.0, 20.0, Rgba::new(0, 0, 0, a / 2));
        let s = cfmt(&fmt, &[format!("{}", self.page + 1).as_str().into(), format!("{}", pages.len()).as_str().into()]);
        let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&s));
        text_run_h(g, ox + px + (40.0 - tw * phs) * 0.5, oy + py - 1.0, &s, 0, white(a), None, phs);
        if let Some(t) = self.sc.cmn.s.t(4) {
            if self.page > 0 || pages.len() > 1 {
                blit(g, Some(t), 168.0, 58.0, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), white(a));
                blit(g, Some(t), 168.0, 384.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), white(a));
            }
        }
    }
}

/// An inline `%iN` button icon of a message string (16 x 20 cells of the common icon sheet, attach 6 of `CMNMENU.DAT`): 0..15 are the sheet
/// cells, 16..19 the logical Menu / Confirm / Cancel / Other buttons drawn as the US pad's physical triangle / cross / circle / square.
/// Returns the advance.
pub fn draw_inline_icon(g: &mut dyn MenuGfx, sc: &CmdScenes, code: u32, x: f32, y: f32, a: u8) -> f32 {
    let cell = match code {
        0..=15 => code as usize,
        16 => 12,
        17 => 14,
        18 => 13,
        19 => 15,
        _ => return 0.0,
    };
    let (cx, cy) = ((cell % 8) as f32 * 16.0, (cell / 8) as f32 * 20.0);
    blit(g, sc.cmn.s.t(6), x, y, 16.0, 20.0, (cx, cy, cx + 16.0, cy + 20.0), white(a));
    16.0
}

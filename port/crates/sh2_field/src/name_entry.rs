//! Retail name entry (`NENTRY.MSD`, `CmdMenu` page 18 = `CmdRetailPage02`, US 0x4e0880 `GetReady`, windows `CmdRetailWin14` (the entry)
//! / `CmdRetailWin12` (the query) / `CmdRetailWin13`).  Two callers: the Party Members page's `Team Name` (mode 0, the name of the party set,
//! 12 characters) and `SpecialMenu(0x400, ..)` (mode 1, SM_20_U: the odd creature's name, 16 characters, default "Roger"), which copies the
//! result into the field's message-variable buffer `CField + 0x2170` (`Sub4e0c40`: `strcpy(sel->buf, win14 + 188)`).
//!
//! Data: `NENTRY.MSD` text entries 0 / 1 = prompt per mode with the blank field as alt text (its length = the maximum), attach 0 MDT 56 =
//! the default name per mode (`{name, who}`), MDT 55 = the character table (`{rows 7, cols 15, ..}`, `$` separates the rows).
//! Layout: the full screen picture `MENU/IMG/EX/NE_000.TEX` (sprite 0), the prompt centred at (256, 60) (font 1), the name centred at
//! (256, 130) with the L1 / R1 caret icons, the L2 / R2 set tabs at y 174 (one set, `alphabet`, on the US disc), the table from (48, 214),
//! the `%i` button guide (resources 0..4) and the query window (154, 200, 204 x 100: `"%s"`, `Is this name okay?`, Yes / No).
//!
//! Controls (the guide): confirm types the character, cancel erases the last one, triangle voids the whole name, square puts the default
//! back, start asks `Is this name okay?`; L1 / R1 move the caret.  The live screen has not been captured (no save reaches SM_20_U's
//! naming; the team name needs the Party Members page with a named set): positions are the scene's.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::msd::{ChunkType, Msd};

use crate::cmd_common::{general_frame, white};
use crate::cmd_page::{CmdScenes, Env};
use crate::cmd_retail::{rgb, CYAN};
use crate::cmd_ui::{blit, draw_sprite_rec, fill, sj, text_run, SceneTex};
use crate::fscreen::{FieldScreen, ScreenFlow, ScreenIo, DT_MS};

pub const PATH: &str = "MENU/MSD/NENTRY.MSD";

#[derive(Debug, Clone, Copy, PartialEq)]
enum Mode {
    Entry,
    Query { yes: bool },
    Done { ok: bool },
}

/// The entry state and its drawing, shared by the page and the field screen.
pub struct NameEntry {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    bg: Option<TextureId>,
    pub kind: usize,
    pub name: Vec<char>,
    caret: usize,
    max: usize,
    default: String,
    prompt: String,
    rows: Vec<Vec<char>>,
    cx: usize,
    cy: usize,
    mode: Mode,
    t: f32,
}

/// The character table of MDT 55: `$`-separated rows, padded to `cols`.
pub fn char_table(m: &Msd) -> Vec<Vec<char>> {
    let cols = m.mdt_data(55, 0).get(2..4).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).unwrap_or(15).max(1);
    let s = sj(m.mdt_str(55, 0, 1));
    s.split('$').map(|r| {
        let mut v: Vec<char> = r.chars().collect();
        v.resize(cols, ' ');
        v
    }).collect()
}

impl NameEntry {
    /// `kind` 0 = team name, 1 = name; `current` = the name it starts from (empty: the default of MDT 56).
    pub fn new(env: &mut Env, kind: usize, current: &str) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let m = &scene.msd;
        let kind = kind.min(1);
        let (prompt, max) = m.text_entry(kind).map(|e| (sj(e.0), sj(e.1).chars().count())).unwrap_or_default();
        let tables = m.attach_scene(0)?;
        let default = sj(tables.mdt_str(56, kind, 0));
        let rows = char_table(&tables);
        let bg = env.image("MENU/IMG/EX/NE_000.TEX");
        let start = if current.is_empty() { default.clone() } else { current.to_string() };
        let name: Vec<char> = start.chars().take(max.max(1)).collect();
        Some(NameEntry { sc, scene, bg, kind, caret: name.len(), name, max: max.max(1), default, prompt, rows, cx: 0, cy: 0, mode: Mode::Entry, t: 0.0 })
    }

    /// `Some(Some(name))` confirmed, `Some(None)` left without a name change.
    pub fn result(&self) -> Option<Option<String>> {
        match self.mode {
            Mode::Done { ok } => Some(ok.then(|| self.text())),
            _ => None,
        }
    }

    pub fn text(&self) -> String {
        self.name.iter().collect::<String>().trim_end().to_string()
    }

    pub fn state(&self) -> &'static str {
        match self.mode {
            Mode::Entry => "entry",
            Mode::Query { .. } => "query",
            Mode::Done { .. } => "done",
        }
    }

    pub fn tick(&mut self, env: &mut Env, keys: u16) {
        self.t += DT_MS;
        match self.mode {
            Mode::Entry => {
                let (h, w) = (self.rows.len().max(1), self.rows.first().map(|r| r.len()).unwrap_or(1).max(1));
                if keys & padbit::UP != 0 {
                    self.cy = (self.cy + h - 1) % h;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.cy = (self.cy + 1) % h;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::LEFT != 0 {
                    self.cx = (self.cx + w - 1) % w;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::RIGHT != 0 {
                    self.cx = (self.cx + 1) % w;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::L1 != 0 {
                    if self.caret > 0 {
                        self.caret -= 1;
                        env.sound(MenuSe::CursorMove);
                    }
                } else if keys & padbit::R1 != 0 {
                    if self.caret < self.name.len() {
                        self.caret += 1;
                        env.sound(MenuSe::CursorMove);
                    }
                } else if keys & padbit::CIRCLE != 0 {
                    let c = self.rows.get(self.cy).and_then(|r| r.get(self.cx)).copied().unwrap_or(' ');
                    if self.caret < self.max {
                        if self.caret < self.name.len() {
                            self.name[self.caret] = c;
                        } else {
                            self.name.push(c);
                        }
                        self.caret += 1;
                        env.sound(MenuSe::Decide);
                    } else {
                        env.sound(MenuSe::Buzzer);
                    }
                } else if keys & padbit::CROSS != 0 {
                    if self.caret > 0 {
                        self.caret -= 1;
                        self.name.remove(self.caret);
                        env.sound(MenuSe::Cancel);
                    } else {
                        env.sound(MenuSe::Buzzer);
                    }
                } else if keys & padbit::TRIANGLE != 0 {
                    self.name.clear();
                    self.caret = 0;
                    env.sound(MenuSe::Cancel);
                } else if keys & padbit::SQUARE != 0 {
                    self.name = self.default.chars().take(self.max).collect();
                    self.caret = self.name.len();
                    env.sound(MenuSe::Decide);
                } else if keys & padbit::START != 0 {
                    if self.text().is_empty() {
                        env.sound(MenuSe::Buzzer);
                    } else {
                        env.sound(MenuSe::Decide);
                        self.mode = Mode::Query { yes: true };
                    }
                }
            }
            Mode::Query { yes } => {
                if keys & (padbit::LEFT | padbit::RIGHT) != 0 {
                    self.mode = Mode::Query { yes: !yes };
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(if yes { MenuSe::Decide } else { MenuSe::Cancel });
                    self.mode = if yes { Mode::Done { ok: true } } else { Mode::Entry };
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Entry;
                }
            }
            Mode::Done { .. } => {}
        }
    }

    pub fn draw(&self, g: &mut dyn MenuGfx, a: u8) {
        let m = &self.scene.msd;
        let cmn = &self.sc.cmn;
        fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, a));
        if let (Some(s), Some(bg)) = (m.sprite(0), self.bg) {
            draw_sprite_rec(g, &s, Some(bg), 0.0, 0.0, a);
        }
        let center = |g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, font: u8, c: Rgba| {
            let (w, _) = g.measure_text(font, &sh2_menu::sjis::encode(s));
            text_run(g, x - w * 0.5, y, s, font, c, Some((1, 1)));
        };
        let at = |i: usize| m.menu_text(i).map(|t| (t.x, t.y)).unwrap_or((256.0, 60.0));
        let (px, py) = at(3);
        center(g, px, py - 4.0, &self.prompt, 0, white(a));
        // the name: fixed-pitch cells over the blank field, the caret cell blinking
        let pitch = 12.0;
        let (nx, ny) = m.message(0).map(|r| (r.common.x, r.common.y)).unwrap_or((256.0, 130.0));
        let x0 = nx - self.max as f32 * pitch * 0.5;
        for k in 0..self.max {
            let x = x0 + k as f32 * pitch;
            let c = self.name.get(k).copied().unwrap_or('_');
            let blink = k == self.caret && self.mode == Mode::Entry && (self.t / 300.0) as u32 % 2 == 0;
            let col = if blink { rgb(CYAN, a) } else { white(a) };
            text_run(g, x, ny - 4.0, &c.to_string(), 0, col, Some((1, 1)));
        }
        // L1 / R1 beside the name, L2 / R2 around the set tabs
        let cell = |g: &mut dyn MenuGfx, s: &sh2_menu::msd::SpriteRec, x: f32, y: f32| {
            blit(g, cmn.s.t(6), x, y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(a));
        };
        if let Some(s) = m.sprite(1) {
            cell(g, &s, x0 + s.x, ny + s.y - 136.0);
        }
        if let Some(s) = m.sprite(2) {
            cell(g, &s, x0 + self.max as f32 * pitch + s.x, ny + s.y - 136.0);
        }
        for i in [3usize, 4] {
            if let Some(s) = m.sprite(i) {
                cell(g, &s, s.x, s.y);
            }
        }
        if let Some(t) = m.menu_text(1) {
            center(g, t.x, t.y - 4.0, "alphabet", 0, rgb(CYAN, a));
        }
        // the character table
        let (tx, ty) = m.message(2).map(|r| (r.common.x, r.common.y)).unwrap_or((48.0, 214.0));
        let (cw, ch) = (28.0, 24.0);
        for (r, row) in self.rows.iter().enumerate() {
            for (c, &chr) in row.iter().enumerate() {
                let sel = r == self.cy && c == self.cx && self.mode == Mode::Entry;
                let x = tx + c as f32 * cw;
                let y = ty + r as f32 * ch;
                if sel {
                    fill(g, x - 4.0, y - 2.0, cw - 2.0, ch - 4.0, Rgba::new(0x00, 0x40, 0x40, a / 2));
                }
                if chr != ' ' {
                    text_run(g, x, y - 2.0, &chr.to_string(), 0, if sel { rgb(CYAN, a) } else { white(a) }, Some((1, 1)));
                }
            }
        }
        // the guide (`%iN: label`), two columns along the bottom
        for k in 0..5 {
            let s = m.resource_bytes(k).map(sj).unwrap_or_default();
            let (x, y) = (60.0 + (k % 3) as f32 * 140.0, 402.0 + (k / 3) as f32 * 22.0);
            let mut cx = x;
            let mut rest = s.as_str();
            if let Some(r) = rest.strip_prefix("%i") {
                let n: String = r.chars().take_while(|c| c.is_ascii_digit()).collect();
                rest = &r[n.len()..];
                cx += crate::cmd_help_retail::draw_inline_icon(g, &self.sc, n.parse().unwrap_or(0), cx, y - 2.0, a);
            }
            text_run(g, cx, y, rest, 0, white(a), Some((1, 1)));
        }
        if let Mode::Query { yes } = self.mode {
            let (wx, wy, ww, wh) = m.window(2).map(|w| (w.x, w.y, w.w, w.h)).unwrap_or((154.0, 200.0, 204.0, 100.0));
            fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, a / 2));
            general_frame(g, cmn, wx - 16.0, wy - 10.0, ww + 32.0, wh + 20.0, a);
            let q = m.resource_bytes(8).map(sj).unwrap_or_else(|| "\"%s\"".into()).replace("%s", &self.text());
            center(g, wx + ww * 0.5, wy + 8.0, &q, 0, white(a));
            center(g, wx + ww * 0.5, wy + 40.0, &m.resource_bytes(9).map(sj).unwrap_or_default(), 0, white(a));
            for (k, ix) in [(0usize, 10usize), (1, 11)] {
                let (x, y) = m.menu_text(7 + k).map(|t| (t.x, t.y)).unwrap_or((32.0 + 96.0 * k as f32, 72.0));
                let sel = (k == 0) == yes;
                center(g, wx + x + 22.0, wy + y - 4.0, &m.resource_bytes(ix).map(sj).unwrap_or_default(), 0, if sel { rgb(CYAN, a) } else { white(a) });
            }
        }
        let _ = ChunkType::Sprite;
    }
}

/// `SpecialMenu(0x400, ..)` as a field screen: the result lands in [`crate::fscreen::FieldScreens::name_result`].
pub struct NameEntryScreen {
    e: NameEntry,
    fade: f32,
    closing: bool,
}

impl NameEntryScreen {
    pub fn new(env: &mut Env, kind: usize, current: &str) -> Option<Self> {
        Some(NameEntryScreen { e: NameEntry::new(env, kind, current)?, fade: 0.0, closing: false })
    }
}

impl FieldScreen for NameEntryScreen {
    fn name(&self) -> &'static str {
        "nameentry"
    }
    fn state(&self) -> String {
        self.e.state().into()
    }
    fn tick(&mut self, env: &mut Env, keys: u16, _press: u16, io: &mut ScreenIo) -> ScreenFlow {
        if self.closing {
            self.fade = (self.fade - DT_MS / 300.0).max(0.0);
            return if self.fade <= 0.0 { ScreenFlow::Done } else { ScreenFlow::Stay };
        }
        self.fade = (self.fade + DT_MS / 240.0).min(1.0);
        self.e.tick(env, keys);
        if let Some(r) = self.e.result() {
            io.name = Some(r.unwrap_or_else(|| self.e.text()));
            self.closing = true;
        }
        ScreenFlow::Stay
    }
    fn draw(&self, g: &mut dyn MenuGfx) {
        self.e.draw(g, (self.fade * 128.0) as u8);
    }
}

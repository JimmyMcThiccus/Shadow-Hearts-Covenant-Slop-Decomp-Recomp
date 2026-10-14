//! The smaller `Cmd*` pages that used to be placeholders: Graveyard (`CmdGraveyard`), Key Customize (`CmdKeyCustom`), Combo Magic
//! (`CmdComboMagic`), Combo Key (`CmdComboKey`) and the Solomon launcher (`CmdMenu` page 0x15).
//!
//! * **Graveyard**: the yes / no question of `GRAVE.MSD`; *yes* runs `CmdGraveyard::JumpGraveyard` (fade) and then `CmdMenu::Release`'s
//!   `FieldMapJumpGY("GY_00_D")` ([`HostReq::MapJump`]).  The demo disc has no `GY_*` maps: the answer is a toast there.
//! * **Key customize** edits the four u16 button entries of `MENU+0x26c` (`SaveMenuSection::SetDefaultButton / UpdatePad`): which physical
//!   button (triangle `0xc`, circle `0xd`, cross `0xe`, square `0xf`) triggers menu / confirm / cancel / other.  The retail default swaps confirm
//!   and cancel (`c e d f`).
//! * **Combo magic**: the combination techniques of the `COMB` table the party has met (`MENU+0x340+i != 0`), known ones with name and MP
//!   cost (`BTL0` flag word), the others as `????`.
//! * **Combo key**: the four shortcut commands per character (`BTL0` ability-slot rows `{u8 kind, u8 button, u16 id}` at `+0x10bc + pc*0x10`
//!   in the retail block): attack style, technique, crest magic or item; `ConvertComboKey` semantics.
//! * **Solomon**: opens the field screen ([`crate::fscreen::ScreenReq::Solomon`]) and closes the menu.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::msd::ChunkType;
use sh2_menu::save::MenuSave;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;

fn grey(a: u8) -> Rgba {
    Rgba::new(0x6c, 0x6c, 0x78, a)
}
fn yellow(a: u8) -> Rgba {
    Rgba::new(0x80, 0x80, 0x30, a)
}

/// The pad face-button icon of physical button `phys` (0 triangle, 1 circle, 2 cross, 3 square): CMNMENU attach 6, second row, 16 x 20 cells.
fn pad_icon(g: &mut dyn MenuGfx, cmn: &CommonScene, phys: usize, x: f32, y: f32, a: u8) {
    let cx = 4 + phys;
    blit(g, cmn.s.t(6), x, y, 16.0, 20.0, ((cx * 16) as f32, 20.0, (cx * 16 + 16) as f32, 40.0), Rgba::new(0x80, 0x80, 0x80, a));
}

/// Text `i` of a scene as the pages show it: the retail files keep the visible strings in the resource table and use the text table for
/// notes, the demo files the other way round.
fn scene_text(sc: &SceneTex, i: usize) -> String {
    sc.msd.text(i).map(sj).filter(|s| !s.is_empty()).or_else(|| sc.msd.resource_bytes(i).map(sj)).unwrap_or_default()
}

// ----------------------------------------------------------------------------------------------------------------
// Graveyard
// ----------------------------------------------------------------------------------------------------------------

/// Map the Graveyard loads (`FieldMapJumpGY` string at JP 0x00555798, US FIELD.BIN 0x001b1a00).
pub const GRAVEYARD_MAP: &str = "GY_00_D";

pub struct GraveyardPage {
    sc: Arc<CmdScenes>,
    win: (f32, f32),
    question: String,
    yes: String,
    no: String,
    /// retail: `You cannot go to the Graveyard now` (txt 1) / `This is the Graveyard` (txt 2) replace the question
    blocked: Option<String>,
    sel: usize,
    /// the map exists on the disc (the demo has no Graveyard)
    available: bool,
    slide: Slide,
    cursor: CmdCursor,
    /// `JumpGraveyard` fade 0..1 once the jump started
    jump: Option<f32>,
    note: String,
}

impl GraveyardPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/GRAVE.MSD")?;
        let retail = sh2_core::boot::is_retail();
        let m = &scene.msd;
        let win = m.window(0).map(|w| (w.x, w.y)).unwrap_or((56.0, 315.0));
        let (question, yes, no) = if retail {
            (scene_text_res(&scene, 0), scene_text_res(&scene, 1), scene_text_res(&scene, 2))
        } else {
            (scene_text(&scene, 0), scene_text(&scene, 1), scene_text(&scene, 2))
        };
        let note = m.text_entry(0).map(|e| sj(e.1)).unwrap_or_default();
        let in_gy = env.session.map.starts_with("GY_");
        let blocked = if retail && in_gy { m.text_entry(2).map(|e| sj(e.0)) } else { None };
        use sh2_menu::disc::FileSource;
        let available = env.assets.disc.as_ref().map(|d| d.read(&format!("FIELD/MPS/{GRAVEYARD_MAP}.MPS")).is_some()).unwrap_or(false);
        let w = m.window(0);
        let mut p = GraveyardPage {
            sc,
            win,
            question,
            yes,
            no,
            blocked,
            sel: 0,
            available,
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(240), (420.0, 94.0)),
            cursor: CmdCursor::new(0.0, 0.0),
            jump: None,
            note,
        };
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn cursor_to_sel(&mut self) {
        self.cursor.set_target(self.win.0 + 100.0, self.win.1 + 24.0 + self.sel as f32 * 22.0 + 10.0);
    }
}

fn scene_text_res(sc: &SceneTex, i: usize) -> String {
    sc.msd.resource_bytes(i).map(sj).unwrap_or_default()
}

impl Page for GraveyardPage {
    fn page(&self) -> CmdPage {
        CmdPage::Graveyard
    }
    fn title(&self) -> usize {
        crate::cmd_pages::title_index(CmdPage::Graveyard)
    }
    fn note(&self) -> String {
        self.note.clone()
    }
    fn wants_background(&self) -> bool {
        true
    }
    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        if let Some(f) = self.jump.as_mut() {
            // `CmdGraveyard::JumpGraveyard`: the screen fades (`SmoothFilter` level -0.005 per frame) before the map jump
            *f += DT / 400.0;
            if *f >= 1.0 {
                env.req.push(HostReq::MapJump { map: GRAVEYARD_MAP.into(), entry: 0 });
                self.jump = None;
            }
            return Flow::Stay;
        }
        if self.blocked.is_some() {
            if keys & (padbit::CIRCLE | padbit::CROSS | padbit::TRIANGLE) != 0 {
                env.sound(MenuSe::Cancel);
                return Flow::Back;
            }
            return Flow::Stay;
        }
        if keys & (padbit::UP | padbit::DOWN) != 0 {
            self.sel ^= 1;
            env.sound(MenuSe::CursorMove);
            self.cursor_to_sel();
        } else if keys & padbit::CIRCLE != 0 {
            if self.sel == 0 {
                if self.available {
                    env.sound(MenuSe::Decide);
                    self.jump = Some(0.0);
                    return Flow::Stay;
                }
                env.sound(MenuSe::Buzzer);
                env.req.push(HostReq::Toast("The Graveyard is not part of this build".into()));
            } else {
                env.sound(MenuSe::Cancel);
            }
            return Flow::Back;
        } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
            env.sound(MenuSe::Cancel);
            return Flow::Back;
        }
        Flow::Stay
    }
    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let (x, y) = self.win;
        message_frame(g, &self.sc.cmn, x - 20.0, y - 28.0, 430.0, a);
        let w = white(a);
        let q = self.blocked.as_deref().unwrap_or(&self.question);
        text_run(g, x, y, q, 0, w, Some((1, 1)));
        if self.blocked.is_none() {
            text_run(g, x + 110.0, y + 24.0, &self.yes, 0, if self.sel == 0 { yellow(a) } else { w }, Some((1, 1)));
            text_run(g, x + 110.0, y + 46.0, &self.no, 0, if self.sel == 1 { yellow(a) } else { w }, Some((1, 1)));
            self.cursor.draw(g, &self.sc.cmn, a);
        }
        if let Some(f) = self.jump {
            fill(g, 0.0, 0.0, SCREEN_W, SCREEN_H, Rgba::new(0, 0, 0, (f.min(1.0) * 128.0) as u8));
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// Key customize
// ----------------------------------------------------------------------------------------------------------------

/// Physical buttons in the order of the diagram boxes: triangle, circle, cross, square (pad bits 12..15).
const PHYS: [(&str, u16); 4] = [("△", 0xc), ("○", 0xd), ("✕", 0xe), ("□", 0xf)];

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum KeyMode {
    List,
    /// choosing the physical button that takes over function `.0`
    Pick(usize),
}

pub struct KeyCustomPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    title_img: Option<(TextureId, (u32, u32))>,
    /// `MENU+0x26c`: physical button bit (0xc..0xf) of function 0 menu, 1 confirm, 2 cancel, 3 other
    assign: [u16; 4],
    labels: Vec<String>,
    notes: Vec<String>,
    mode: KeyMode,
    sel: usize,
    pick: usize,
    cursor: CmdCursor,
    slide: Slide,
}

impl KeyCustomPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/KEYCUS.MSD")?;
        let m = &scene.msd;
        let labels = (0..7).map(|i| m.text(i).map(sj).unwrap_or_default()).collect();
        let notes = (0..7).map(|i| m.text_entry(i).map(|e| sj(e.1)).unwrap_or_default()).collect();
        let mut assign = [0xc, 0xd, 0xe, 0xf];
        for (k, a) in assign.iter_mut().enumerate() {
            let o = MenuSave::OFF_PAD_ASSIGN + k * 2;
            let v = u16::from_le_bytes([env.session.save.menu.data[o], env.session.save.menu.data[o + 1]]);
            if (0xc..=0xf).contains(&v) {
                *a = v;
            }
        }
        let w = m.window(0);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = KeyCustomPage {
            sc,
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(4), w.as_ref().map(|w| w.open_time).unwrap_or(120), (176.0, 180.0)),
            scene,
            title_img,
            assign,
            labels,
            notes,
            mode: KeyMode::List,
            sel: 0,
            pick: 0,
            cursor: CmdCursor::new(0.0, 0.0),
        };
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn list_origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((380.0, 24.0))
    }

    fn cursor_to_sel(&mut self) {
        match self.mode {
            KeyMode::List => {
                let (x, y) = self.list_origin();
                self.cursor.set_target(x - 2.0, y + self.sel as f32 * 21.0 + 10.0);
            }
            KeyMode::Pick(_) => {
                let (bx, by) = self.button_box(self.pick);
                self.cursor.set_target(bx - 2.0, by + 20.0);
            }
        }
    }

    /// Top-left of the diagram box of physical button `p` (0 triangle, 1 circle, 2 cross, 3 square): groups 2 / 0 / 1 / 3 of the scene.
    fn button_box(&self, p: usize) -> (f32, f32) {
        let group = [2usize, 0, 1, 3][p];
        self.scene.msd.group(group).map(|g| (g.x, g.y)).unwrap_or((200.0, 160.0))
    }

    fn function_of(&self, phys: usize) -> usize {
        let bit = PHYS[phys].1;
        self.assign.iter().position(|&a| a == bit).unwrap_or(phys)
    }

    fn store(&self, env: &mut Env) {
        for (k, a) in self.assign.iter().enumerate() {
            let o = MenuSave::OFF_PAD_ASSIGN + k * 2;
            env.session.save.menu.data[o..o + 2].copy_from_slice(&a.to_le_bytes());
        }
    }
}

impl Page for KeyCustomPage {
    fn page(&self) -> CmdPage {
        CmdPage::KeyCustom
    }
    fn title(&self) -> usize {
        crate::cmd_pages::title_index(CmdPage::KeyCustom)
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        match self.mode {
            KeyMode::List => self.notes.get(self.sel).cloned().unwrap_or_default().replace("%%i", "").replace("%i", ""),
            KeyMode::Pick(_) => self.notes.get(6).cloned().unwrap_or_default(),
        }
    }
    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        match self.mode {
            KeyMode::List => {
                if keys & padbit::UP != 0 {
                    self.sel = (self.sel + 5) % 6;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::DOWN != 0 {
                    self.sel = (self.sel + 1) % 6;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::CIRCLE != 0 {
                    match self.sel {
                        0..=3 => {
                            env.sound(MenuSe::Decide);
                            self.pick = (0..4).find(|&p| PHYS[p].1 == self.assign[self.sel]).unwrap_or(0);
                            self.mode = KeyMode::Pick(self.sel);
                            self.cursor_to_sel();
                        }
                        4 => {
                            // `SaveMenuSection::SetDefaultButton`
                            self.assign = if sh2_core::boot::is_retail() { sh2_core::game::US_DEFAULT_BUTTONS } else { sh2_core::game::JP_DEFAULT_BUTTONS };
                            env.sound(MenuSe::Decide);
                            self.store(env);
                        }
                        _ => {
                            env.sound(MenuSe::Decide);
                            self.store(env);
                            return Flow::Back;
                        }
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.store(env);
                    return Flow::Back;
                }
            }
            KeyMode::Pick(func) => {
                let dir = if keys & padbit::UP != 0 {
                    Some(0)
                } else if keys & padbit::RIGHT != 0 {
                    Some(1)
                } else if keys & padbit::DOWN != 0 {
                    Some(2)
                } else if keys & padbit::LEFT != 0 {
                    Some(3)
                } else {
                    None
                };
                if let Some(p) = dir {
                    self.pick = p;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::CIRCLE != 0 {
                    // the function that owned the chosen button receives the old button of `func` (a swap keeps the entries unique)
                    let bit = PHYS[self.pick].1;
                    if let Some(other) = self.assign.iter().position(|&a| a == bit) {
                        self.assign[other] = self.assign[func];
                    }
                    self.assign[func] = bit;
                    env.sound(MenuSe::Decide);
                    self.store(env);
                    self.mode = KeyMode::List;
                    self.cursor_to_sel();
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = KeyMode::List;
                    self.cursor_to_sel();
                }
            }
        }
        Flow::Stay
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "OK".into()), (Button::Cross, "Back".into())]
    }
    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let m = &self.scene.msd;
        let w = white(a);
        // controller diagram: pad picture (attach 1) with a box + connector line per physical button
        if let Some(r) = m.sprite(0) {
            draw_sprite_rec(g, &r, self.scene.t(1), 0.0, 0.0, a);
        }
        for i in 0..m.count(ChunkType::Polygon) {
            if let Some(p) = m.polygon(i) {
                let col = |k: usize| Rgba::new(p.rgba[k][0], p.rgba[k][1], p.rgba[k][2], ((p.rgba[k][3] as u32 * a as u32) / 0x80) as u8);
                g.draw(sh2_menu::gfx::DrawCmd::Quad {
                    tex: None,
                    v: [vtx(p.x[0], p.y[0], 0.0, 0.0, col(0)), vtx(p.x[1], p.y[1], 0.0, 0.0, col(1)), vtx(p.x[2], p.y[2], 0.0, 0.0, col(2)), vtx(p.x[3], p.y[3], 0.0, 0.0, col(3))],
                    blend: sh2_menu::gfx::Blend::Alpha,
                });
            }
        }
        for p in 0..4 {
            let (bx, by) = self.button_box(p);
            let f = self.function_of(p);
            let sel_here = matches!(self.mode, KeyMode::Pick(_)) && self.pick == p;
            general_frame_small(g, &self.scene, bx, by, 174.0, 40.0, a);
            pad_icon(g, &self.sc.cmn, p, bx + 10.0, by + 9.0, a);
            text_run(g, bx + 40.0, by + 9.0, self.labels.get(f).map(|s| s.as_str()).unwrap_or(""), 0, if sel_here { yellow(a) } else { w }, Some((1, 1)));
        }
        // function list
        let (lx, ly) = self.list_origin();
        general_frame(g, &self.sc.cmn, lx - 30.0, ly - 12.0, 170.0, 170.0, a);
        for (i, label) in self.labels.iter().take(6).enumerate() {
            let y = ly + i as f32 * 21.0;
            if i == self.sel && self.mode == KeyMode::List {
                row_bar(g, lx - 6.0, y - 1.0, 150.0, 20.0, a);
            }
            text_run(g, lx, y, label, 0, if i == self.sel { w } else { grey(a) }, Some((1, 1)));
            if i < 4 {
                pad_icon(g, &self.sc.cmn, PHYS.iter().position(|p| p.1 == self.assign[i]).unwrap_or(0), lx + 108.0, y, a);
            }
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

/// A small bevelled box (the 64 x 32 texture of attach 2) used for the diagram labels.
fn general_frame_small(g: &mut dyn MenuGfx, scene: &SceneTex, x: f32, y: f32, w: f32, h: f32, a: u8) {
    let c = Rgba::new(0x60, 0x60, 0x70, (a as u32 * 0x60 / 0x80) as u8);
    blit(g, scene.t(2), x, y, w, h, (0.0, 0.0, 64.0, 32.0), c);
}

// ----------------------------------------------------------------------------------------------------------------
// Combo magic
// ----------------------------------------------------------------------------------------------------------------

/// `MENU+0x340 + i`: per combination technique "has been met" flag (`CmdComboMagic::GetReady`).
pub const OFF_COMBO_SEEN: usize = 0x340;

struct ComboRow {
    name: String,
    mp: i32,
    known: bool,
    /// the explanation of the selected combination (`CmdComboMagic::SelectGoods`: `GetRegDat(0x22, i)`; unknown ones show the scene's own note)
    desc: String,
}

/// Retail combination descriptions: `sshmes.na` description kind 0x22 (`CmdComboMagic::SelectGoods` 0x004c7a20 calls `GetRegDat(0x22, row, -1)`).
fn combo_descriptions(env: &Env) -> Vec<String> {
    use sh2_menu::disc::FileSource;
    if !sh2_core::boot::is_retail() {
        return vec![];
    }
    let Some(d) = env.assets.disc.as_ref() else { return vec![] };
    let region = sh2_core::boot::active_region();
    let (Some(mes), Some(dat)) = (d.read(region.sshmes()), d.read(region.sshdat())) else { return vec![] };
    let Some(r) = sh2_core::regdat::UsRegDat::new(&mes, &dat) else { return vec![] };
    (0..0x40).map(|i| r.text(0x22, i, -1).unwrap_or_default().replace('$', "\n")).collect()
}

pub struct ComboMagicPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    fence: Option<Arc<SceneTex>>,
    rows: Vec<ComboRow>,
    list: ListState,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    unknown: String,
    note: String,
    title_img: Option<(TextureId, (u32, u32))>,
}

const COMBO_ROW_H: f32 = 21.0;
const COMBO_VISIBLE: usize = 10;

impl ComboMagicPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/CBMAGIC.MSD")?;
        let fence = env.nested_scene("MENU/MSD/CBMAGIC.MSD", 1);
        let mut rows = Vec::new();
        let descs = combo_descriptions(env);
        if let Some(db) = env.db {
            let n = db.dat.sections.get(sh2_battle::data::SEC_COMBO).map(|_| db.dat.section(sh2_battle::data::SEC_COMBO).len() / 0x40).unwrap_or(0);
            let known_bits = env.session.save.btl.combo_flags();
            for i in 0..n.min(0x40) {
                if env.session.save.menu.data[OFF_COMBO_SEEN + i] == 0 {
                    continue;
                }
                let rec = db.dat.record(sh2_battle::data::SEC_COMBO, i, 0x40).unwrap_or(&[]);
                let known = known_bits & (1u32 << (i & 31)) != 0;
                let mp = rec.get(0x1e..0x20).map(|b| u16::from_le_bytes([b[0], b[1]]) as i32).unwrap_or(0);
                let name = if known { Some(env.name(18, i)).filter(|n| !n.trim().is_empty()).unwrap_or_else(|| format!("#{}", i + 1)) } else { sj(scene.msd.resource_bytes(0).unwrap_or(&[])) };
                let desc = if known { descs.get(i).cloned().filter(|d| !d.trim().is_empty()) } else { None };
                rows.push(ComboRow { name, mp, known, desc: desc.unwrap_or_default() });
            }
        }
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let unknown = sj(scene.msd.resource_bytes(0).unwrap_or(&[]));
        let note = scene.msd.text_entry(0).map(|e| sj(e.1)).unwrap_or_default();
        let w = scene.msd.window(0);
        let mut p = ComboMagicPage {
            sc,
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(240), (210.0, 280.0)),
            list: ListState::new(COMBO_VISIBLE, rows.len()),
            scene,
            fence,
            rows,
            cursor: CmdCursor::new(0.0, 0.0),
            time: 0.0,
            unknown,
            note,
            title_img,
        };
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((42.0, 124.0))
    }

    fn cursor_to_sel(&mut self) {
        let (x, y) = self.origin();
        self.cursor.set_target(x - 4.0, y + self.list.slot() as f32 * COMBO_ROW_H + 10.0);
    }
}

impl Page for ComboMagicPage {
    fn page(&self) -> CmdPage {
        CmdPage::ComboMagic
    }
    fn title(&self) -> usize {
        crate::cmd_pages::title_index(CmdPage::ComboMagic)
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        match self.rows.get(self.list.sel) {
            Some(r) if !r.desc.is_empty() => r.desc.clone(),
            _ => self.note.clone(),
        }
    }
    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        if self.list.key(keys) {
            env.sound(MenuSe::CursorMove);
            self.cursor_to_sel();
        } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
            env.sound(MenuSe::Cancel);
            return Flow::Back;
        } else if keys & padbit::CIRCLE != 0 {
            env.sound(MenuSe::Buzzer);
        }
        Flow::Stay
    }
    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let (x, y) = self.origin();
        if let Some(f) = &self.fence {
            draw_fence(g, f, 38.0, 80.0, a, true);
        }
        let w = white(a);
        for k in 0..self.list.visible {
            let i = self.list.top + k;
            let Some(r) = self.rows.get(i) else { break };
            let yy = y + k as f32 * COMBO_ROW_H;
            if i == self.list.sel {
                row_bar(g, x - 4.0, yy - 1.0, 200.0, 20.0, a);
            }
            let c = if r.known { w } else { grey(a) };
            text_run(g, x, yy, &r.name, 0, c, Some((1, 1)));
            if r.known {
                text_right(g, x + 192.0, yy, &format!("{}", r.mp), 0, c, Some((1, 1)));
            }
        }
        if self.rows.is_empty() {
            text_run(g, x, y, &self.unknown, 0, grey(a), None);
        }
        draw_scroll_marks(g, x + 96.0, y - 4.0, y + COMBO_VISIBLE as f32 * COMBO_ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

// ----------------------------------------------------------------------------------------------------------------
// Combo key
// ----------------------------------------------------------------------------------------------------------------

/// Kinds of a shortcut command (`GetComboKeyData`): 0 attack style, 1 item, 2 crest magic, 3 technique.
const KIND_ATTACK: u8 = 0;
const KIND_ITEM: u8 = 1;
const KIND_MAGIC: u8 = 2;
const KIND_SKILL: u8 = 3;

#[derive(Clone, Debug)]
struct Choice {
    kind: u8,
    id: u16,
    name: String,
    note: String,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum CkMode {
    /// choose one of the four shortcut slots
    Slots,
    /// choose the category (attack / technique / crest magic / item / remove)
    Category,
    /// choose the command of the category
    Command,
}

pub struct ComboKeyPage {
    sc: Arc<CmdScenes>,
    /// keeps the page's scene textures alive (not read directly)
    #[allow(dead_code)]
    scene: Arc<SceneTex>,
    card: Option<Arc<SceneTex>>,
    pcs: Vec<PcView>,
    pc: usize,
    face: Option<TextureId>,
    mode: CkMode,
    slot: usize,
    cat: usize,
    cats: Vec<(String, Option<u8>)>,
    choices: Vec<Choice>,
    list: ListState,
    unset: String,
    #[allow(dead_code)]
    labels: Vec<String>,
    notes: Vec<String>,
    cursor: CmdCursor,
    slide: Slide,
    title_img: Option<(TextureId, (u32, u32))>,
    time: f32,
    /// the character's four shortcut commands as shown: `(kind, id, name)`
    slot_view: Vec<(u8, u16, String)>,
}

impl ComboKeyPage {
    pub fn new(env: &mut Env, pc: Option<u8>) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/CBKEY.MSD")?;
        let card = env.nested_scene("MENU/MSD/CBKEY.MSD", if sh2_core::boot::is_retail() { 1 } else { 2 });
        let pcs = party_view(env.session);
        if pcs.is_empty() {
            return None;
        }
        let pci = pc.and_then(|id| pcs.iter().position(|p| p.id == id)).unwrap_or(0);
        let m = &scene.msd;
        let labels: Vec<String> = (0..7).map(|i| m.text(i).map(sj).unwrap_or_default()).collect();
        let notes: Vec<String> = (0..7).map(|i| m.text_entry(i).map(|e| sj(e.1)).unwrap_or_default()).collect();
        let unset = labels.get(5).cloned().unwrap_or_default();
        let tech = if labels[1].is_empty() { if sh2_core::boot::is_retail() { "Technique".to_string() } else { "特技".to_string() } } else { labels[1].clone() };
        let cats = vec![
            (labels[0].clone(), Some(KIND_ATTACK)),
            (tech, Some(KIND_SKILL)),
            (labels[2].clone(), Some(KIND_MAGIC)),
            (labels[3].clone(), Some(KIND_ITEM)),
            (labels[4].clone(), None),
        ];
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = ComboKeyPage {
            sc,
            slide: Slide::open(0, 240, (300.0, 250.0)),
            scene,
            card,
            pcs,
            pc: pci,
            face: None,
            mode: CkMode::Slots,
            slot: 0,
            cat: 0,
            cats,
            choices: vec![],
            list: ListState::new(7, 0),
            unset,
            labels,
            notes,
            cursor: CmdCursor::new(0.0, 0.0),
            title_img,
            time: 0.0,
            slot_view: vec![],
        };
        p.face = env.face(p.pcs[p.pc].face);
        p.refresh(env);
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn pc_id(&self) -> u8 {
        self.pcs[self.pc].id
    }

    /// The four shortcut slots of the character (`BTL0` ability rows).
    fn slots(&self, session: &sh2_menu::session::GameSession) -> [(u8, u16); 4] {
        let mut out = [(KIND_ATTACK, 0xffffu16); 4];
        for (k, o) in out.iter_mut().enumerate() {
            let (kind, id) = session.save.btl.shortcut(self.pc_id() as usize, k);
            *o = (kind, id);
        }
        out
    }

    /// Re-read the four shortcut slots of the current character.
    fn refresh(&mut self, env: &Env) {
        let slots = self.slots(env.session);
        self.slot_view = slots
            .iter()
            .map(|&(kind, id)| {
                let name = if id == 0xffff && kind == KIND_ATTACK { self.unset.clone() } else { self.command_name(env, kind, id) };
                (kind, id, name)
            })
            .collect();
    }

    fn command_name(&self, env: &Env, kind: u8, id: u16) -> String {
        match kind {
            KIND_ATTACK => {
                let styles = &self.sc.mdt;
                let ty = if sh2_core::boot::is_retail() { 49 } else { 50 };
                let i = if id == 0xffff { 0 } else { id as usize };
                let s = sj(styles.mdt_str(ty, i, 0));
                if s.is_empty() { format!("{}", i + 1) } else { s }
            }
            KIND_ITEM => env.name(12, id as usize),
            KIND_MAGIC => env.name(17, id as usize),
            KIND_SKILL => env.name(15, id as usize),
            _ => String::new(),
        }
    }

    fn open_commands(&mut self, env: &mut Env) {
        let Some(kind) = self.cats[self.cat].1 else { return };
        let pc = self.pc_id() as usize;
        let mut v = Vec::new();
        match kind {
            KIND_ATTACK => {
                let ty = if sh2_core::boot::is_retail() { 49 } else { 50 };
                for i in 0..self.sc.mdt.mdt_count(ty).min(8) {
                    let name = sj(self.sc.mdt.mdt_str(ty, i, 0));
                    let note = sj(self.sc.mdt.mdt_str(ty, i, 1)).replace('$', "\n");
                    if !name.is_empty() {
                        v.push(Choice { kind, id: i as u16, name, note });
                    }
                }
            }
            KIND_ITEM => {
                for i in 0..0x40usize {
                    if env.session.save.btl.item_count(i) > 0 && env.session.save.btl.item_count(i) != 0xff {
                        let name = env.name(12, i);
                        if !name.trim().is_empty() {
                            v.push(Choice { kind, id: i as u16, name, note: String::new() });
                        }
                    }
                }
            }
            KIND_MAGIC => {
                if let (Some(t), Some(r)) = (env.tables, env.session.save.btl.pc(pc)) {
                    let learned = |c: usize| env.session.save.btl.skill_learned(c);
                    for id in t.crest_magic(&r.skills, &learned) {
                        v.push(Choice { kind, id: id as u16, name: env.name(17, id), note: String::new() });
                    }
                }
            }
            KIND_SKILL => {
                if let Some(t) = env.tables {
                    for (i, rec) in t.groups.get(pc).map(|g| g.iter().enumerate().collect::<Vec<_>>()).unwrap_or_default() {
                        if !rec.empty {
                            let n = env.name(15, rec.name_idx.max(0) as usize);
                            v.push(Choice { kind, id: i as u16, name: if n.trim().is_empty() { format!("#{}", i + 1) } else { n }, note: String::new() });
                        }
                    }
                }
            }
            _ => {}
        }
        self.list.set_len(v.len());
        self.choices = v;
    }

    fn cursor_to_sel(&mut self) {
        match self.mode {
            CkMode::Slots => self.cursor.set_target(218.0, 100.0 + self.slot as f32 * 28.0 + 12.0),
            CkMode::Category => self.cursor.set_target(402.0, 100.0 + self.cat as f32 * 22.0 + 12.0),
            CkMode::Command => self.cursor.set_target(278.0, 100.0 + self.list.slot() as f32 * 22.0 + 12.0),
        }
    }
}

impl Page for ComboKeyPage {
    fn page(&self) -> CmdPage {
        CmdPage::ComboKey
    }
    fn title(&self) -> usize {
        crate::cmd_pages::title_index(CmdPage::ComboKey)
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        match self.mode {
            CkMode::Slots => self.notes.get(6).cloned().unwrap_or_default().replace("%s", &self.pcs[self.pc].name),
            CkMode::Category => self.notes.get(self.cat).cloned().unwrap_or_default().replace("%s", &self.cats[self.cat].0),
            CkMode::Command => self.choices.get(self.list.sel).map(|c| c.note.clone()).filter(|n| !n.is_empty()).unwrap_or_else(|| self.notes.get(self.cat).cloned().unwrap_or_default().replace("%s", &self.cats[self.cat].0)),
        }
    }
    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        match self.mode {
            CkMode::Slots => {
                if keys & padbit::UP != 0 {
                    self.slot = (self.slot + 3) % 4;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.slot = (self.slot + 1) % 4;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::L1 | padbit::R1) != 0 && self.pcs.len() > 1 {
                    let d = if keys & padbit::L1 != 0 { self.pcs.len() - 1 } else { 1 };
                    self.pc = (self.pc + d) % self.pcs.len();
                    self.face = env.face(self.pcs[self.pc].face);
                    self.refresh(env);
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.mode = CkMode::Category;
                    self.cat = 0;
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            CkMode::Category => {
                if keys & padbit::UP != 0 {
                    self.cat = (self.cat + self.cats.len() - 1) % self.cats.len();
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.cat = (self.cat + 1) % self.cats.len();
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    if self.cats[self.cat].1.is_none() {
                        // "Remove": back to the plain attack of that button (`ConvertComboKey(0)`: id -1)
                        env.session.save.btl.set_shortcut(self.pc_id() as usize, self.slot, KIND_ATTACK, 0xffff);
                        env.sound(MenuSe::Decide);
                        self.mode = CkMode::Slots;
                        self.refresh(env);
                    } else {
                        self.open_commands(env);
                        if self.choices.is_empty() {
                            env.sound(MenuSe::Buzzer);
                        } else {
                            env.sound(MenuSe::Decide);
                            self.mode = CkMode::Command;
                        }
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = CkMode::Slots;
                }
            }
            CkMode::Command => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    if let Some(c) = self.choices.get(self.list.sel).cloned() {
                        env.session.save.btl.set_shortcut(self.pc_id() as usize, self.slot, c.kind, c.id);
                        env.sound(MenuSe::Decide);
                        self.mode = CkMode::Slots;
                        self.refresh(env);
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = CkMode::Category;
                }
            }
        }
        self.cursor_to_sel();
        Flow::Stay
    }
    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let w = white(a);
        let blue = blue(a);
        let pc = &self.pcs[self.pc];
        if let Some(card) = &self.card {
            let (cx, cy) = card.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((10.0, 52.0));
            face_card_back(g, &self.sc.cmn, &card.msd, self.face, cx, cy, a);
            let t = |k: usize| card.msd.menu_text(k).map(|t| (t.x, t.y)).unwrap_or((0.0, 0.0));
            let (x, y) = t(4);
            text_run(g, cx + x, cy + y - 2.0, &pc.name, 0, w, Some((1, 0)));
            let (x, y) = t(0);
            self.sc.font_small.draw(g, cx + x, cy + y, "LEVEL", blue);
            let (x, y) = t(5);
            self.sc.font_big.draw(g, cx + x - 20.0, cy + y - 4.0, &format!("{:>2}", pc.level), w);
        }
        // the four shortcut commands; the pad glyph of slot k is the physical button of the combo key table (inferred order)
        general_frame(g, &self.sc.cmn, 196.0, 74.0, 240.0, 170.0, a);
        for (k, (_, _, name)) in self.slot_view.iter().enumerate() {
            let y = 100.0 + k as f32 * 28.0;
            if self.mode == CkMode::Slots && k == self.slot {
                row_bar(g, 226.0, y - 3.0, 190.0, 24.0, a);
            }
            pad_icon(g, &self.sc.cmn, k, 232.0, y, a);
            text_run(g, 262.0, y, name, 0, if self.mode == CkMode::Slots && k == self.slot { w } else { grey(a) }, Some((1, 1)));
        }
        match self.mode {
            CkMode::Slots => {}
            CkMode::Category => {
                general_frame(g, &self.sc.cmn, 384.0, 92.0, 126.0, 160.0, a);
                for (i, (name, _)) in self.cats.iter().enumerate() {
                    let y = 100.0 + i as f32 * 22.0;
                    if i == self.cat {
                        row_bar(g, 408.0, y - 2.0, 92.0, 20.0, a);
                    }
                    text_run(g, 414.0, y, name, 0, if i == self.cat { w } else { grey(a) }, Some((1, 1)));
                }
            }
            CkMode::Command => {
                general_frame(g, &self.sc.cmn, 260.0, 86.0, 236.0, 214.0, a);
                for k in 0..self.list.visible {
                    let i = self.list.top + k;
                    let Some(c) = self.choices.get(i) else { break };
                    let y = 100.0 + k as f32 * 22.0;
                    if i == self.list.sel {
                        row_bar(g, 280.0, y - 2.0, 196.0, 20.0, a);
                    }
                    text_run(g, 288.0, y, &c.name, 0, if i == self.list.sel { w } else { grey(a) }, Some((1, 1)));
                }
                draw_scroll_marks(g, 378.0, 92.0, 100.0 + 7.0 * 22.0, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
            }
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

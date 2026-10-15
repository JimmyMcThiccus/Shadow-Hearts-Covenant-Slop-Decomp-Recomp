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
    /// retail: the stone board (live `gy_c`)
    board: Option<GraveBoard>,
}

/// Retail `CmdGraveyard` / `CmdGraveyardMenu` (US 0x493980 / 0x4946a0): GRAVE.MSD's full-screen picture (sprite 0), the six soul stones
/// at window 1 (24, 48) + groups (0 / 112 / 224, 0 / 136), each with `GRADE.` + grade (`1 2 3 MAX`), the element stone of `CmdElement`
/// and `SE.%3d/%3d` (charge towards the next grade / its need, MDT 54 of attach 0) over a dark band; the question at window 0 (24, 332)
/// centred on x 174 with `Yes` / `No` at (132, 22 / 43), the selected one cyan.
struct GraveBoard {
    scene: Arc<SceneTex>,
    elem: Option<crate::cmd_magic::ElemArt>,
    /// (group origin, stone, grade, charge)
    stones: Vec<((f32, f32), crate::soul_charge::Stone, usize, i32)>,
}

impl GraveBoard {
    fn new(env: &mut Env, scene: Arc<SceneTex>) -> Self {
        let elem = crate::cmd_magic::ElemArt::load(env);
        let mdt = scene.msd.attach_scene(0);
        let m = &scene.msd;
        let (wx, wy) = m.window(1).map(|w| (w.x, w.y)).unwrap_or((24.0, 48.0));
        let mut stones = Vec::new();
        for gi in 0..m.count(ChunkType::Group) {
            let Some(gr) = m.group(gi) else { continue };
            let idx = gr.label as usize;
            let Some(st) = mdt.as_ref().and_then(|d| crate::soul_charge::Stone::from_mdt(d, idx)) else { continue };
            let o = crate::soul_charge::OFF_STONES + idx * 0x10;
            let (grade, charge) = env.session.save.menu.data.get(o..o + 4).map(|b| ((b[0] as i8).max(0) as usize, i16::from_le_bytes([b[2], b[3]]) as i32)).unwrap_or((0, 0));
            stones.push(((wx + gr.x, wy + gr.y), st, grade, charge.max(0)));
        }
        GraveBoard { scene, elem, stones }
    }

    fn draw_picture(&self, g: &mut dyn MenuGfx, a: u8) {
        let m = &self.scene.msd;
        if let Some(r) = m.sprite(0) {
            // the picture is the 512 x 448 attach texture
            let t = (0..m.attach_files().len()).find(|&i| self.scene.tex_size(i) == (512, 448)).and_then(|i| self.scene.t(i));
            draw_sprite_rec(g, &r, t, 0.0, 0.0, a);
        }
    }

    fn draw(&self, g: &mut dyn MenuGfx, a: u8) {
        let m = &self.scene.msd;
        let res = |i: usize| m.resource_bytes(i).map(sj).unwrap_or_default();
        for ((ox, oy), st, grade, charge) in &self.stones {
            if let Some(el) = &self.elem {
                el.draw_at(g, st.element, *ox, *oy, a);
            }
            if let Some(t) = m.menu_text(2) {
                text_run_h(g, ox + t.x, oy + t.y, &res(3), 2, crate::cmd_retail::rgb(crate::cmd_retail::LAVENDER, a), Some((1, 1)), sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
            if let Some(t) = m.menu_text(3) {
                let v = if *grade >= st.grades as usize { res(7) } else { res(4 + grade) };
                text_run_h(g, ox + t.x, oy + t.y, &v, 2, white(a), Some((1, 1)), sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
            if let Some(p) = m.polygon(0) {
                crate::cmd_retail::gs_poly(g, &p, *ox, *oy, a);
            }
            if let Some(t) = m.menu_text(4) {
                let maxed = *grade >= st.grades as usize;
                let base = st.base(*grade);
                let need = st.need.get(*grade).copied().unwrap_or(0);
                let (cur, of) = if maxed { (need.max(st.need.last().copied().unwrap_or(0)), st.need.last().copied().unwrap_or(0)) } else { ((charge - base).clamp(0, need), need) };
                text_run_h(g, ox + t.x, oy + t.y, &cfmt(&res(8), &[cur.into(), of.into()]), 0, white(a), Some((1, 1)), sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
        }
    }
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
        let board = retail.then(|| GraveBoard::new(env, scene.clone()));
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
            board,
        };
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn cursor_to_sel(&mut self) {
        if self.board.is_some() {
            // `Yes` / `No` records at (132, 22 / 43): the arrow tip 5 px left of the text
            self.cursor.set_target(self.win.0 + 132.0 - 5.0, self.win.1 + 22.0 + self.sel as f32 * 21.0 + 10.0);
            return;
        }
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
    /// retail: the page shows its own picture (GRAVE.MSD sprite 0) over a black backdrop, with the root list on the right
    fn backdrop(&self) -> Option<usize> {
        self.board.as_ref().map(|_| 0)
    }
    fn shows_root_list(&self) -> bool {
        self.board.is_some()
    }
    fn shows_root_info(&self) -> bool {
        self.board.is_some()
    }
    fn own_backdrop(&self, g: &mut dyn MenuGfx) -> bool {
        let Some(b) = &self.board else { return false };
        b.draw_picture(g, 0x80);
        true
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.board.as_ref().and_then(|b| b.scene.t(1).map(|t| (t, b.scene.tex_size(1))))
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        self.board.as_ref().map(|_| Vec::new())
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
        if let Some(b) = &self.board {
            b.draw(g, a);
            let m = &b.scene.msd;
            let q = self.blocked.as_deref().unwrap_or(&self.question);
            let hs = 0.8;
            let qx = m.message(0).map(|r| r.common.x).unwrap_or(150.0);
            let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(q));
            text_run_h(g, x + qx - tw * hs * 0.5, y, q, 0, white(a), Some((1, 1)), hs);
            if self.blocked.is_none() {
                for (i, s) in [&self.yes, &self.no].into_iter().enumerate() {
                    let t = m.menu_text(i);
                    let (tx, ty) = t.as_ref().map(|t| (t.x, t.y)).unwrap_or((132.0, 22.0 + 21.0 * i as f32));
                    let c = if self.sel == i { Rgba::new(0x00, 0x80, 0x80, a) } else { white(a) };
                    text_run_h(g, x + tx, y + ty, s, 0, c, Some((1, 1)), hs);
                }
                self.cursor.draw(g, &self.sc.cmn, a);
            }
            if let Some(f) = self.jump {
                fill(g, 0.0, 0.0, SCREEN_W, SCREEN_H, Rgba::new(0, 0, 0, (f.min(1.0) * 128.0) as u8));
            }
            return;
        }
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
    retail: bool,
}

/// Retail rows of the Button Customization list (live `bc_b`): the physical buttons circle, cross, triangle, square (their pad bits), the
/// order of KEYCUS.MSD groups 0..3 (diagram boxes) and 4..7 (list rows).
const RETAIL_ROWS: [u16; 4] = [0xd, 0xe, 0xc, 0xf];
/// `pad_icon` index (0 triangle, 1 circle, 2 cross, 3 square) of each retail row.
const RETAIL_ROW_ICON: [usize; 4] = [1, 2, 0, 3];

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
            retail: sh2_core::boot::is_retail(),
        };
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn list_origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((380.0, 24.0))
    }

    fn cursor_to_sel(&mut self) {
        if self.retail {
            let (x, y) = self.list_origin();
            let row_y = |r: usize| if r < 4 { r as f32 * 21.0 } else { 110.0 + (r - 4) as f32 * 21.0 };
            self.cursor.set_target(x - 5.0, y + row_y(self.sel) + 10.0);
            return;
        }
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
    /// retail: the page sits on the `CMDMENUS.MSD` backdrop 1 (live captures) and has no JP hint bar
    fn backdrop(&self) -> Option<usize> {
        sh2_core::boot::is_retail().then_some(1)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        sh2_core::boot::is_retail().then(Vec::new)
    }
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
        if self.retail {
            return match self.mode {
                // the physical button of the row: text `bit - 12` ("Change setting for the %i13 button.")
                KeyMode::List if self.sel < 4 => self.notes.get(RETAIL_ROWS[self.sel] as usize - 12).cloned().unwrap_or_default(),
                KeyMode::List => self.notes.get(self.sel).cloned().unwrap_or_default(),
                KeyMode::Pick(_) => self.notes.get(6).cloned().unwrap_or_default(),
            };
        }
        match self.mode {
            KeyMode::List => self.notes.get(self.sel).cloned().unwrap_or_default().replace("%%i", "").replace("%i", ""),
            KeyMode::Pick(_) => self.notes.get(6).cloned().unwrap_or_default(),
        }
    }
    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        if self.retail {
            return self.tick_retail(env, keys);
        }
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
        if self.retail {
            self.draw_retail(g, a);
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

impl KeyCustomPage {
    /// Function (0 menu, 1 confirm, 2 cancel, 3 other) on the physical button of retail row `r`.
    fn retail_function(&self, r: usize) -> usize {
        self.assign.iter().position(|&a| a == RETAIL_ROWS[r]).unwrap_or(r)
    }

    /// Retail `CmdKeyCustom::SelectButton / SwapButton` (US 0x4b2820 / 0x4b2c00): pick a button row, then a second one; their functions
    /// change places.  Default restores the US assignment, Confirm (or cancel on the list) stores and leaves.
    fn tick_retail(&mut self, env: &mut Env, keys: u16) -> Flow {
        let n = if matches!(self.mode, KeyMode::Pick(_)) { 4 } else { 6 };
        if keys & padbit::UP != 0 {
            self.sel = (self.sel + n - 1) % n;
            env.sound(MenuSe::CursorMove);
            self.cursor_to_sel();
            return Flow::Stay;
        }
        if keys & padbit::DOWN != 0 {
            self.sel = (self.sel + 1) % n;
            env.sound(MenuSe::CursorMove);
            self.cursor_to_sel();
            return Flow::Stay;
        }
        match self.mode {
            KeyMode::List => {
                if keys & padbit::CIRCLE != 0 {
                    match self.sel {
                        0..=3 => {
                            env.sound(MenuSe::Decide);
                            self.mode = KeyMode::Pick(self.sel);
                        }
                        4 => {
                            self.assign = sh2_core::game::US_DEFAULT_BUTTONS;
                            env.sound(MenuSe::Decide);
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
            KeyMode::Pick(first) => {
                if keys & padbit::CIRCLE != 0 {
                    let (fa, fb) = (self.retail_function(first), self.retail_function(self.sel));
                    self.assign.swap(fa, fb);
                    env.sound(MenuSe::Decide);
                    self.mode = KeyMode::List;
                    self.sel = first;
                    self.cursor_to_sel();
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = KeyMode::List;
                    self.sel = first;
                    self.cursor_to_sel();
                }
            }
        }
        Flow::Stay
    }

    /// Retail layout (live `bc_b` / `bc_k`): the pad picture (sprite 0, attach 1), per button the connector (polygons 2i / 2i+1), the ring
    /// frame (sprite 1), the button icon (sprite 2) and the plate (sprites 3..5, attach 2) with the function name; the right list rows
    /// `icon : name` then `Default` / `Confirm`.  Highlighted rows (the one under the cursor and, while picking, the first one): cyan names,
    /// a dark plate, a bright frame and connector.
    fn draw_retail(&self, g: &mut dyn MenuGfx, a: u8) {
        let m = &self.scene.msd;
        if let Some(r) = m.sprite(0) {
            draw_sprite_rec(g, &r, self.scene.t(1), 0.0, 0.0, a);
        }
        let hl = |r: usize| match self.mode {
            KeyMode::List => self.sel == r,
            KeyMode::Pick(first) => first == r || self.sel == r,
        };
        let cyan = Rgba::new(0x00, 0x80, 0x80, a);
        let dim = Rgba::new(0x50, 0x50, 0x48, a);
        let modu = |v: u8| Rgba::new(v, v, v, a);
        for r in 0..4 {
            let Some(gr) = m.group(r) else { continue };
            let on = hl(r);
            for k in [2 * r, 2 * r + 1] {
                if let Some(p) = m.polygon(k) {
                    let v = if on { p.rgba[0][0] } else { p.rgba[0][0] / 2 };
                    let c = modu(v);
                    g.draw(sh2_menu::gfx::DrawCmd::Quad {
                        tex: None,
                        v: [vtx(p.x[0], p.y[0], 0.0, 0.0, c), vtx(p.x[1], p.y[1], 0.0, 0.0, c), vtx(p.x[2], p.y[2], 0.0, 0.0, c), vtx(p.x[3], p.y[3], 0.0, 0.0, c)],
                        blend: sh2_menu::gfx::Blend::Alpha,
                    });
                }
            }
            let (ox, oy) = (gr.x, gr.y);
            if let Some(s) = m.sprite(1) {
                blit(g, self.scene.t(2), ox + s.x, oy + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), modu(if on { 0x80 } else { 0x40 }));
            }
            for k in 3..6 {
                if let Some(s) = m.sprite(k) {
                    // the plate is cut from the common fence / frame texture (the same 64 x 28 cells as the fences' headers)
                    blit(g, self.sc.fence_tex, ox + s.x, oy + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), modu(0x60));
                }
            }
            if on {
                // the highlighted plate keeps its rim and goes black inside (live `bc_b`)
                if let (Some(l), Some(r)) = (m.sprite(3), m.sprite(5)) {
                    fill(g, ox + l.x + 4.0, oy + l.y + 4.0, r.x + r.w - l.x - 8.0, l.h - 8.0, Rgba::new(0, 0, 0, (a as u32 * 0x78 / 0x80) as u8));
                }
            }
            if let Some(s) = m.sprite(2) {
                pad_icon(g, &self.sc.cmn, RETAIL_ROW_ICON[r], ox + s.x, oy + s.y, a);
            }
            if let Some(t) = m.menu_text(0) {
                let f = self.retail_function(r);
                let c = if on { cyan } else { dim };
                text_run_h(g, ox + t.x, oy + t.y - 1.0, self.labels.get(f).map(|s| s.as_str()).unwrap_or(""), 0, c, Some((1, 1)), sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
        }
        // the list
        let (lx, ly) = self.list_origin();
        let hs = m.menu_text(1).map(|t| sh2_menu::gfx::TextRun::hscale_of(t.flags)).unwrap_or(0.8);
        let name_x = m.menu_text(1).map(|t| t.x).unwrap_or(30.0);
        let colon_x = m.menu_text(4).map(|t| t.x).unwrap_or(16.0);
        let colon = self.labels.get(6).cloned().unwrap_or_else(|| ":".into());
        for r in 0..4 {
            let gy = m.group(4 + r).map(|gr| gr.y).unwrap_or(r as f32 * 21.0);
            let y = ly + gy;
            pad_icon(g, &self.sc.cmn, RETAIL_ROW_ICON[r], lx, y, a);
            let c = if hl(r) { cyan } else { white(a) };
            text_run_h(g, lx + colon_x, y - 1.0, &colon, 0, c, None, hs);
            text_run_h(g, lx + name_x, y - 1.0, self.labels.get(self.retail_function(r)).map(|s| s.as_str()).unwrap_or(""), 0, c, None, hs);
        }
        let picking = matches!(self.mode, KeyMode::Pick(_));
        for (k, rec) in [(4usize, 2usize), (5, 3)] {
            let (tx, ty, ths) = m.menu_text(rec).map(|t| (t.x, t.y, sh2_menu::gfx::TextRun::hscale_of(t.flags))).unwrap_or((0.0, 110.0, 0.8));
            let c = if picking { Rgba::new(0x80, 0x80, 0x80, a / 2) } else if self.sel == k { cyan } else { white(a) };
            text_run_h(g, lx + tx, ly + ty - 1.0, self.labels.get(k).map(|s| s.as_str()).unwrap_or(""), 0, c, None, ths);
        }
        // picking: the white marker on the first row (common attach 4, right arrow cell)
        if let (KeyMode::Pick(first), Some(t)) = (self.mode, self.sc.cmn.s.t(4)) {
            let gy = m.group(4 + first).map(|gr| gr.y).unwrap_or(first as f32 * 21.0);
            blit(g, Some(t), lx - 26.0, ly + gy - 2.0, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), white(a));
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
    /// retail: the page sits on the `CMDMENUS.MSD` backdrop 0 (live captures) and has no JP hint bar
    fn backdrop(&self) -> Option<usize> {
        sh2_core::boot::is_retail().then_some(0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        sh2_core::boot::is_retail().then(Vec::new)
    }
    fn page(&self) -> CmdPage {
        CmdPage::ComboMagic
    }
    /// retail (live `cmg_b`): the root list stays on the right
    fn shows_root_list(&self) -> bool {
        sh2_core::boot::is_retail()
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
            // retail (live `cmg_b`): an unknown combination's Notes line is the `????` of the scene, like its name
            Some(r) if sh2_core::boot::is_retail() && !r.known => self.unknown.clone(),
            // the retail scene's own note is an untranslated Japanese leftover
            None if sh2_core::boot::is_retail() => String::new(),
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
        if sh2_core::boot::is_retail() {
            self.draw_retail(g, x, y, a);
            return;
        }
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

impl ComboMagicPage {
    /// Retail (live `cmg_b`): the textured `Name / MP` fence of attach 1 (window (38, 80)), the rows at window 0 (42, 124) with the name
    /// at record 0 and `%3d` MP at record 1 (x 160), narrow text; the selected row cyan, the others white -- also the unknown `????` ones,
    /// which keep their MP.
    fn draw_retail(&self, g: &mut dyn MenuGfx, x: f32, y: f32, a: u8) {
        if let Some(f) = &self.fence {
            let (fx, fy) = f.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((38.0, 80.0));
            draw_fence_tex(g, f, self.sc.fence_tex, fx, fy, a, true);
        }
        let m = &self.scene.msd;
        let (nr, mr) = (m.menu_text(0), m.menu_text(1));
        let hs = nr.as_ref().map(|t| sh2_menu::gfx::TextRun::hscale_of(t.flags)).unwrap_or(0.8);
        let mx = mr.as_ref().map(|t| t.x).unwrap_or(160.0);
        let fmt = m.resource_bytes(1).map(sj).unwrap_or_else(|| "%3d".into());
        for k in 0..self.list.visible {
            let i = self.list.top + k;
            let Some(r) = self.rows.get(i) else { break };
            let yy = y + k as f32 * COMBO_ROW_H;
            let c = if i == self.list.sel { Rgba::new(0x00, 0x80, 0x80, a) } else { white(a) };
            text_run_h(g, x, yy - 1.0, &r.name, 0, c, None, hs);
            text_run_h(g, x + mx, yy - 1.0, &cfmt(&fmt, &[r.mp.into()]), 0, c, None, hs);
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
    /// retail `CBKEY.MSD` attach 2 (banners) / attach 3 (`Command` fence)
    banner: Option<Arc<SceneTex>>,
    fence: Option<Arc<SceneTex>>,
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
        let retail = sh2_core::boot::is_retail();
        let banner = if retail { env.nested_scene("MENU/MSD/CBKEY.MSD", 2) } else { None };
        let fence = if retail { env.nested_scene("MENU/MSD/CBKEY.MSD", 3) } else { None };
        let mut p = ComboKeyPage {
            banner,
            fence,
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
        let retail = sh2_core::boot::is_retail();
        self.slot_view = slots
            .iter()
            .enumerate()
            .map(|(k, &(kind, id))| {
                // retail `ConvertComboKeyDefault` (US 0x46dc10 -> `CmdParty::ConvertComboKey(1)`): an empty attack row takes the default style of
                // its byte 1 (per member and slot; a negative default stays unset)
                let id = if retail && kind == KIND_ATTACK && id == 0xffff {
                    let d = env.session.save.btl.shortcut_default(self.pc_id() as usize, k);
                    if d >= 0 { d as u16 } else { id }
                } else {
                    id
                };
                // `GetComboKeyData` kind 0: a style the member cannot use (menu data table 0x31 per member, `+0xb` style mask) shows as unset
                let id = if kind == KIND_ATTACK && id != 0xffff && !self.style_allowed(id) { 0xffff } else { id };
                let name = if id == 0xffff && kind == KIND_ATTACK { self.unset.clone() } else { self.command_name(env, kind, id) };
                (kind, id, name)
            })
            .collect();
    }

    /// `CmdParty::GetComboKeyData` kind 0: bit `id` of the member's style mask (menu data table demo key 0x31, record = member, data byte 7).
    fn style_allowed(&self, id: u16) -> bool {
        let d = self.sc.mdt.mdt_data(0x31, self.pc_id() as usize);
        match d.get(7) {
            Some(&mask) if id < 8 => mask & (1 << id) != 0,
            Some(_) => false,
            None => true,
        }
    }

    fn command_name(&self, env: &Env, kind: u8, id: u16) -> String {
        match kind {
            KIND_ATTACK => {
                let styles = &self.sc.mdt;
                let ty = 50; // the attack-style table (demo key 0x32; retail raw 49 through `us_mdt_type`): Standard, Hard Hit, High Angle, Knock Down
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
                let ty = 50; // the attack-style table (demo key 0x32; retail raw 49 through `us_mdt_type`): Standard, Hard Hit, High Angle, Knock Down
                for i in 0..self.sc.mdt.mdt_count(ty).min(8) {
                    let name = sj(self.sc.mdt.mdt_str(ty, i, 0));
                    let note = sj(self.sc.mdt.mdt_str(ty, i, 1)).replace('$', "\n");
                    if !name.is_empty() && self.style_allowed(i as u16) {
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
        if sh2_core::boot::is_retail() {
            // retail rows (live `cb_page`): the four button rows from y 276 (21.5 px apart), the `Command` fence list from (236, 84)
            let (x, y) = match self.mode {
                CkMode::Slots => (36.0, CK_ROW_Y + self.slot as f32 * CK_ROW_H + 10.0),
                CkMode::Category => (232.0, CK_FENCE_Y + self.cat as f32 * 21.0 + 10.0),
                CkMode::Command => (232.0, CK_FENCE_Y + self.list.slot() as f32 * 21.0 + 10.0),
            };
            self.cursor.set_target(x, y);
            return;
        }
        match self.mode {
            CkMode::Slots => self.cursor.set_target(218.0, 100.0 + self.slot as f32 * 28.0 + 12.0),
            CkMode::Category => self.cursor.set_target(402.0, 100.0 + self.cat as f32 * 22.0 + 12.0),
            CkMode::Command => self.cursor.set_target(278.0, 100.0 + self.list.slot() as f32 * 22.0 + 12.0),
        }
    }
}

/// Retail combo-setup layout (live `cb_page`): first button row top, row pitch, first row of the `Command` fence list.
const CK_ROW_Y: f32 = 276.0;
const CK_ROW_H: f32 = 21.5;
const CK_FENCE_Y: f32 = 84.0;

impl ComboKeyPage {
    /// Retail `CmdComboKey` (`CBKEY.MSD`): member card (attach 1, `< Name >`), the `Character State` / `Command` banners (attach 2), the state
    /// row (the member's name), the four button rows L1 / R1 / L2 / R2 with the assigned command, the `Command` fence (attach 3 at (228, 40))
    /// with the categories or, while choosing, the commands of the category.
    fn draw_retail(&self, g: &mut dyn MenuGfx, a: u8) {
        use crate::cmd_retail::{draw_pc_card, gs_poly, rgb, CardView, CYAN, LAVENDER};
        let pc = &self.pcs[self.pc];
        if let Some(card) = &self.card {
            let arrows = self.mode == CkMode::Slots && self.pcs.len() > 1;
            draw_pc_card(g, &self.sc, card, self.face, &CardView::of(pc), arrows, a);
        }
        if let Some(b) = &self.banner {
            let m = &b.msd;
            for k in 0..2 {
                let Some(gr) = m.group(k) else { continue };
                for i in 0..m.count(sh2_menu::msd::ChunkType::Sprite) {
                    if let Some(sp) = m.sprite(i) {
                        draw_sprite_rec(g, &sp, b.t(0), gr.x, gr.y, a);
                    }
                }
                if let (Some(t), Some(sres)) = (m.menu_text(0), m.resource_bytes(k)) {
                    text_run_h(g, gr.x + t.x, gr.y + t.y - 3.0, &sj(sres), 2, rgb(LAVENDER, a), Some((1, 0)), sh2_menu::gfx::TextRun::hscale_of(t.flags));
                }
            }
        }
        // the state row under `Character State`
        text_run_h(g, 37.0, 225.0, &pc.name, 0, Rgba::new(0x58, 0x58, 0x60, a), None, 0.8);
        // L1 / R1 / L2 / R2 rows: icon cells 10 / 11 / 8 / 9 of the common sheet
        const CELLS: [usize; 4] = [10, 11, 8, 9];
        for (k, (_, _, name)) in self.slot_view.iter().enumerate().take(4) {
            let y = CK_ROW_Y + k as f32 * CK_ROW_H;
            let (cx, cy) = ((CELLS[k] % 8) as f32 * 16.0, (CELLS[k] / 8) as f32 * 20.0);
            blit(g, self.sc.cmn.s.t(6), 38.0, y, 16.0, 20.0, (cx, cy, cx + 16.0, cy + 20.0), white(a));
            let c = if k == self.slot { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, 52.0, y, name, 0, c, None, 0.8);
        }
        // the `Command` fence
        if let Some(f) = &self.fence {
            let m = &f.msd;
            let (fx, fy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((228.0, 40.0));
            if let Some(p) = m.polygon(0) {
                gs_poly(g, &p, fx, fy, a);
            }
            for i in 0..m.count(sh2_menu::msd::ChunkType::Sprite) {
                if let Some(sp) = m.sprite(i) {
                    draw_sprite_rec(g, &sp, self.sc.fence_tex, fx, fy, a);
                }
            }
            if let Some(t) = m.menu_text(0) {
                let head = m.resource_bytes(1).map(sj).unwrap_or_default();
                let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&head));
                text_run_h(g, fx + 72.0 - tw * 0.4, fy + t.y - 1.0, &head, 0, white(a), Some((1, 1)), 0.8);
            }
        }
        match self.mode {
            CkMode::Command => {
                for k in 0..self.list.visible.min(5) {
                    let i = self.list.top + k;
                    let Some(c) = self.choices.get(i) else { break };
                    let col = if i == self.list.sel { rgb(CYAN, a) } else { white(a) };
                    text_run_h(g, 236.0, CK_FENCE_Y + k as f32 * 21.0, &c.name, 0, col, None, 0.8);
                }
            }
            CkMode::Category => {
                for (k, (name, _)) in self.cats.iter().enumerate() {
                    let col = if k == self.cat { rgb(CYAN, a) } else { white(a) };
                    text_run_h(g, 236.0, CK_FENCE_Y + k as f32 * 21.0, name, 0, col, None, 0.8);
                }
            }
            CkMode::Slots => {
                // live `cb_page`: the fence names the category of the hovered button's command
                if let Some(&(kind, _, _)) = self.slot_view.get(self.slot) {
                    if let Some((name, _)) = self.cats.iter().find(|c| c.1 == Some(kind)) {
                        text_run_h(g, 236.0, CK_FENCE_Y, name, 0, white(a), None, 0.8);
                    }
                }
            }
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

impl Page for ComboKeyPage {
    /// retail: the page sits on the `CMDMENUS.MSD` backdrop 0 (live captures) and has no JP hint bar
    fn backdrop(&self) -> Option<usize> {
        sh2_core::boot::is_retail().then_some(0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        sh2_core::boot::is_retail().then(Vec::new)
    }
    fn shows_root_list(&self) -> bool {
        sh2_core::boot::is_retail()
    }
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
            CkMode::Slots if sh2_core::boot::is_retail() => {
                // live: the assigned command's description ("Attack enemy and push them backwards.")
                match self.slot_view.get(self.slot) {
                    Some(&(KIND_ATTACK, id, _)) => sj(self.sc.mdt.mdt_str(49, if id == 0xffff { 0 } else { id as usize }, 1)).replace('$', " "),
                    _ => self.notes.get(6).cloned().unwrap_or_default().replace("%s", &self.pcs[self.pc].name),
                }
            }
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
        if sh2_core::boot::is_retail() {
            self.draw_retail(g, a);
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

//! `CmdCrest` (page 4, "Crest change", JP 0x0045ea40): equip the eight crest slots of a character.
//!
//! Data: the character's crest slots (`BTL0` record skills 0..8, -1 = empty), the learned-crest bits of the bag section
//! (`BtlSave::skill_learned`), `MC_P` records (which `MAGI` ids a crest grants), crest names from `SSHMES` (section 16).
//! Layout: `MENU/MSD/CREST.MSD` (slot list at (0, 176), card = nested scene 3).

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 21.0;
const SLOTS: usize = 8;
const VISIBLE: usize = 5;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Slots,
    Pick,
}

pub struct CrestPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    card: Option<Arc<SceneTex>>,
    pcs: Vec<PcView>,
    pc: usize,
    slot: usize,
    mode: Mode,
    /// slot contents (-1 empty)
    slots: [i8; SLOTS],
    cands: Vec<i16>,
    list: ListState,
    names: Vec<String>,
    cand_names: Vec<String>,
    magic_of: Vec<String>,
    face: Option<TextureId>,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    title_img: Option<(TextureId, (u32, u32))>,
}

fn crest_name(env: &Env, id: usize) -> String {
    let n = env.name(16, id);
    if n.trim().is_empty() {
        format!("紋章{}", id + 1)
    } else {
        n
    }
}

impl CrestPage {
    pub fn new(env: &mut Env, pc: Option<u8>) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/CREST.MSD")?;
        let card = env.nested_scene("MENU/MSD/CREST.MSD", if sh2_core::boot::is_retail() { 2 } else { 3 });
        let pcs = party_view(env.session);
        if pcs.is_empty() {
            return None;
        }
        let pci = pc.and_then(|id| pcs.iter().position(|p| p.id == id)).unwrap_or(0);
        let w = scene.msd.window(0);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = CrestPage {
            sc,
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(300), (200.0, 180.0)),
            scene,
            card,
            pcs,
            pc: pci,
            slot: 0,
            mode: Mode::Slots,
            slots: [-1; SLOTS],
            cands: Vec::new(),
            list: ListState::new(VISIBLE, 0),
            names: vec![String::new(); SLOTS],
            cand_names: Vec::new(),
            magic_of: vec![String::new(); SLOTS],
            face: None,
            cursor: CmdCursor::new(0.0, 0.0),
            time: 0.0,
            title_img,
        };
        p.load(env);
        p.cursor_to_slot();
        p.cursor.snap();
        Some(p)
    }

    fn pc_id(&self) -> u8 {
        self.pcs[self.pc].id
    }

    fn load(&mut self, env: &mut Env) {
        self.face = env.face(self.pcs[self.pc].face);
        if let Some(r) = env.session.save.btl.pc(self.pc_id() as usize) {
            self.slots = r.skills;
        }
        let empty = self.scene.msd.text(2).map(sj).unwrap_or_default();
        for i in 0..SLOTS {
            self.names[i] = if self.slots[i] >= 0 { crest_name(env, self.slots[i] as usize) } else { "－－－－－－".to_string() };
            // magic granted by the crest
            self.magic_of[i] = match (self.slots[i], env.tables) {
                (c, Some(t)) if c >= 0 => t
                    .crests
                    .get(c as usize)
                    .map(|cr| cr.magic.iter().filter(|&&m| m >= 0).map(|&m| env.name(17, m as usize)).collect::<Vec<_>>().join(" "))
                    .unwrap_or_default(),
                _ => String::new(),
            };
        }
        let _ = empty;
    }

    fn origin(&self) -> (f32, f32) {
        let w = self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((0.0, 176.0));
        (w.0 + 38.0, w.1 + 27.0)
    }

    fn cursor_to_slot(&mut self) {
        let (x, y) = self.origin();
        self.cursor.set_target(x - 4.0, y + self.slot as f32 * ROW_H + 10.0 - if self.slot >= 5 { 0.0 } else { 0.0 });
    }

    fn open_pick(&mut self, env: &mut Env) {
        let total = env.tables.map(|t| t.crests.len()).unwrap_or(0);
        let mut c: Vec<i16> = vec![-1];
        for id in 0..total {
            let owned = env.session.save.btl.skill_learned(id) || self.slots.contains(&(id as i8));
            if owned && !self.slots.contains(&(id as i8)) {
                c.push(id as i16);
            }
        }
        self.cand_names = c.iter().map(|&id| if id < 0 { self.scene.msd.text(2).map(sj).unwrap_or_default() } else { crest_name(env, id as usize) }).collect();
        self.cands = c;
        self.list = ListState::new(VISIBLE, self.cands.len());
        self.mode = Mode::Pick;
        env.sound(MenuSe::Decide);
    }

    fn equip(&mut self, env: &mut Env) {
        let Some(&c) = self.cands.get(self.list.sel) else { return };
        if let Some(mut r) = env.session.save.btl.pc(self.pc_id() as usize) {
            r.skills[self.slot] = c as i8;
            env.session.save.btl.set_pc(self.pc_id() as usize, &r);
        }
        env.sound(MenuSe::Decide);
        self.load(env);
        self.mode = Mode::Slots;
    }
}

impl Page for CrestPage {
    fn page(&self) -> CmdPage {
        CmdPage::Crest
    }
    fn title(&self) -> usize {
        33
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        self.scene.msd.text_entry(0).map(|e| sj(e.1)).unwrap_or_default()
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into()), (Button::L1, "キャラ切替".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        match self.mode {
            Mode::Slots => {
                if keys & padbit::UP != 0 {
                    self.slot = (self.slot + SLOTS - 1) % SLOTS;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_slot();
                } else if keys & padbit::DOWN != 0 {
                    self.slot = (self.slot + 1) % SLOTS;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_slot();
                } else if keys & (padbit::L1 | padbit::R1 | padbit::LEFT | padbit::RIGHT) != 0 && self.pcs.len() > 1 {
                    let d = if keys & (padbit::L1 | padbit::LEFT) != 0 { self.pcs.len() - 1 } else { 1 };
                    self.pc = (self.pc + d) % self.pcs.len();
                    env.sound(MenuSe::CursorMove);
                    self.load(env);
                } else if keys & padbit::CIRCLE != 0 {
                    self.open_pick(env);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Pick => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    self.equip(env);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Slots;
                }
            }
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let Some(w) = self.scene.msd.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let blue = Rgba::new(0x70, 0xc0, 0xff, a);
        let hi = Rgba::new(0x80, 0x80, 0x30, a);
        if let Some(card) = &self.card {
            let pc = &self.pcs[self.pc];
            let cw = card.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((10.0, 52.0));
            let (cx, cy) = (cw.0 + dx, cw.1 + dy);
            face_card_back(g, &self.sc.cmn, &card.msd, self.face, cx, cy, a);
            let t = |k: usize| card.msd.menu_text(k).map(|t| (t.x, t.y)).unwrap_or((0.0, 0.0));
            let (x, y) = t(4);
            text_run(g, cx + x, cy + y - 2.0, &pc.name, 0, white, Some((1, 0)));
            let (x, y) = t(0);
            self.sc.font_small.draw(g, cx + x, cy + y, "LEVEL", blue);
            let (x, y) = t(5);
            self.sc.font_big.draw(g, cx + x - 20.0, cy + y - 4.0, &format!("{:>2}", pc.level), white);
            for (k, (label, cur, max)) in [("HP", pc.hp as i32, pc.hp_max as i32), ("MP", pc.mp as i32, pc.mp_max as i32), ("SP", pc.sp as i32, pc.sp_max as i32)].iter().enumerate() {
                let (x, y) = t(1 + k);
                self.sc.font_small.draw(g, cx + x, cy + y, label, blue);
                self.sc.font_small.draw(g, cx + x + 26.0, cy + y, &cfmt("%3d/%3d", &[(*cur).into(), (*max).into()]), white);
            }
        }
        let (sx, sy) = self.origin();
        let (sx, sy) = (sx + dx, sy + dy);
        general_frame(g, &self.sc.cmn, sx - 12.0, sy - 8.0, 300.0, 8.0 * ROW_H - 4.0 + 14.0, a);
        for i in 0..SLOTS {
            let y = sy + i as f32 * (ROW_H - 2.0);
            let sel = self.mode == Mode::Slots && i == self.slot;
            if sel {
                row_bar(g, sx - 4.0, y, 364.0, ROW_H - 3.0, a);
            }
            let empty = self.slots[i] < 0;
            let c = if empty { Rgba::new(0x70, 0x70, 0x78, a) } else if sel { hi } else { white };
            text_run(g, sx + 2.0, y, &self.names[i], 0, c, Some((1, 1)));
            text_run(g, sx + 120.0, y + 2.0, &self.magic_of[i], 14, Rgba::new(0xa0, 0xc0, 0xff, a), Some((1, 1)));
        }
        if self.mode == Mode::Pick {
            let (px, py) = (336.0 + dx, 90.0 + dy);
            general_frame(g, &self.sc.cmn, px - 12.0, py - 8.0, 176.0, VISIBLE as f32 * ROW_H + 14.0, a);
            for (slot, n) in self.cand_names.iter().skip(self.list.top).take(VISIBLE).enumerate() {
                let y = py + slot as f32 * ROW_H;
                let sel = self.list.top + slot == self.list.sel;
                if sel {
                    row_bar(g, px - 4.0, y, 156.0, ROW_H - 1.0, a);
                }
                text_run(g, px + 4.0, y + 1.0, n, 0, if sel { hi } else { white }, Some((1, 1)));
            }
            draw_scroll_marks(g, px + 100.0, py - 2.0, py + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        } else {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}

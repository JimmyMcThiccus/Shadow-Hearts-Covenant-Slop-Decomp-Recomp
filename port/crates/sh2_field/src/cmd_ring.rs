//! `CmdRingCustom` (page 6, "Ring custom", JP 0x00453ed0): per character Judgement Ring settings.
//!
//! The menu edits the real fields of the party record (see [`sh2_menu::ringcustom`]):
//!
//! * **hit areas** (`ヒットエリア N撃` / `ストライク N撃`): expansion *points* per hit (zone: 2 degrees each, strike tail: 1 degree each),
//!   paid from the stock of ring items (`GetRestRingItem`: key-item slots 1 / 2 of the bag minus the points every member already placed);
//! * **number of hits** (1..5): the natural count plus extra hits paid from key-item slot 0 (`CmdRingCustomCount`);
//! * **ring type** (normal / practice / technical / gamble, descriptions from the menu data table chunk 24) -> bits 6-7 of the record byte;
//! * **auto ring** (`CmdRingCustomAutoRing`: `+0x59` bit 0; resets the expansion and chooses the natural hit count).
//!
//! Battle reads the result through [`sh2_menu::ringcustom::battle_ring`] (exact hook: `notes/integration/requests.md`).  The "final slot" /
//! ring-item assignment (`CmdRingCustomFinalSlot` / `FinalGoods`) is listed but shows the item texts only.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::ringcustom::{self as rc, RingState};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Menu,
    Edit,
}

pub struct RingPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    card: Option<Arc<SceneTex>>,
    pcs: Vec<PcView>,
    pc: usize,
    params: RingState,
    face: Option<TextureId>,
    menu_sel: usize,
    edit_sel: usize,
    mode: Mode,
    ring_names: Vec<(String, String)>,
    cursor: CmdCursor,
    slide: Slide,
    title_img: Option<(TextureId, (u32, u32))>,
}

impl RingPage {
    pub fn new(env: &mut Env, pc: Option<u8>) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/RINGCTM.MSD")?;
        let card = env.nested_scene("MENU/MSD/RINGCTM.MSD", if sh2_core::boot::is_retail() { 1 } else { 2 });
        let pcs = party_view(env.session);
        if pcs.is_empty() {
            return None;
        }
        let pci = pc.and_then(|id| pcs.iter().position(|p| p.id == id)).unwrap_or(0);
        let ring_names = (0..sc.mdt.mdt_count(24)).map(|i| (sj(sc.mdt.mdt_str(24, i, 0)), sj(sc.mdt.mdt_str(24, i, 2)))).collect();
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let params = rc::ring_state(env.session, pcs[pci].id);
        let mut p = RingPage {
            sc,
            scene,
            card,
            pcs,
            pc: pci,
            params,
            face: None,
            menu_sel: 0,
            edit_sel: 0,
            mode: Mode::Menu,
            ring_names,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(0, 240, (300.0, 200.0)),
            title_img,
        };
        p.face = env.face(p.pcs[p.pc].face);
        p.cursor_to_menu();
        p.cursor.snap();
        Some(p)
    }

    fn pc_id(&self) -> u8 {
        self.pcs[self.pc].id
    }

    fn cursor_to_menu(&mut self) {
        self.cursor.set_target(34.0, 225.0 + self.menu_sel as f32 * 21.0 + 10.0);
    }

    fn save(&mut self, env: &mut Env) {
        rc::store_ring_state(env.session, self.pc_id(), &self.params);
    }

    fn rows_in_edit(&self) -> usize {
        match self.menu_sel {
            0 => self.params.hits as usize * 2,
            1 => 1,
            2 => 5,
            3 => self.ring_names.len().max(1),
            _ => 2,
        }
    }
}

impl Page for RingPage {
    /// retail: the page sits on the `CMDMENUS.MSD` backdrop 0 (live captures) and has no JP hint bar
    fn backdrop(&self) -> Option<usize> {
        sh2_core::boot::is_retail().then_some(0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        sh2_core::boot::is_retail().then(Vec::new)
    }
    fn page(&self) -> CmdPage {
        CmdPage::RingCustom
    }
    fn title(&self) -> usize {
        14
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        let m = &self.scene.msd;
        match self.mode {
            Mode::Menu => m.text_entry(self.menu_sel).map(|e| sj(e.1)).unwrap_or_default(),
            Mode::Edit => match self.menu_sel {
                0 => m.text_entry(5 + self.edit_sel).map(|e| sj(e.1)).unwrap_or_default(),
                2 => m.text_entry(15 + self.edit_sel).map(|e| sj(e.1)).unwrap_or_default(),
                3 => self.ring_names.get(self.edit_sel).map(|r| r.1.clone()).unwrap_or_default(),
                4 => m.text_entry(20 + self.edit_sel).map(|e| sj(e.1)).unwrap_or_default(),
                _ => m.text_entry(24).map(|e| sj(e.0)).unwrap_or_default(),
            },
        }
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into()), (Button::L1, "キャラ切替".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        match self.mode {
            Mode::Menu => {
                if keys & padbit::UP != 0 {
                    self.menu_sel = (self.menu_sel + 4) % 5;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_menu();
                } else if keys & padbit::DOWN != 0 {
                    self.menu_sel = (self.menu_sel + 1) % 5;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_menu();
                } else if keys & (padbit::L1 | padbit::R1) != 0 && self.pcs.len() > 1 {
                    let d = if keys & padbit::L1 != 0 { self.pcs.len() - 1 } else { 1 };
                    self.pc = (self.pc + d) % self.pcs.len();
                    self.params = rc::ring_state(env.session, self.pc_id());
                    self.face = env.face(self.pcs[self.pc].face);
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Edit;
                    self.edit_sel = match self.menu_sel {
                        2 => self.params.hits as usize - 1,
                        3 => self.params.ring_type as usize,
                        4 => !self.params.auto as usize,
                        _ => 0,
                    };
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Edit => {
                let n = self.rows_in_edit();
                if keys & padbit::UP != 0 {
                    self.edit_sel = (self.edit_sel + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.edit_sel = (self.edit_sel + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::LEFT | padbit::RIGHT) != 0 && self.menu_sel == 0 {
                    // `CmdRingCustomHitArea::Custom`: a point moves between the member and the party stock
                    let d: i32 = if keys & padbit::RIGHT != 0 { 1 } else { -1 };
                    let (i, strike) = (self.edit_sel / 2, self.edit_sel % 2 == 1);
                    let kind = if strike { rc::STOCK_STRIKE } else { rc::STOCK_ZONE };
                    let cur = if strike { self.params.strike[i] } else { self.params.zone[i] } as i32;
                    let ok = if d > 0 { rc::rest(env.session, kind) > 0 && cur < rc::MAX_POINTS as i32 } else { cur > 0 };
                    if ok {
                        let v = (cur + d) as u8;
                        if strike { self.params.strike[i] = v } else { self.params.zone[i] = v }
                        env.sound(MenuSe::Other(1));
                        self.save(env);
                    } else {
                        env.sound(MenuSe::Buzzer);
                    }
                } else if keys & padbit::CIRCLE != 0 {
                    match self.menu_sel {
                        2 => {
                            // hits above the natural count are bought with the extra-hit items (`CmdRingCustomCount::Select`)
                            let want = self.edit_sel as u8 + 1;
                            let extra = want.saturating_sub(self.params.base_hits) as i32;
                            let have = self.params.extra_hits() as i32 + rc::rest(env.session, rc::STOCK_HITS);
                            if extra <= have {
                                self.params.hits = want;
                            } else {
                                env.sound(MenuSe::Buzzer);
                            }
                        }
                        3 => self.params.ring_type = self.edit_sel as u8,
                        4 => {
                            // `CmdRingCustomAutoRing::Select` + the reset of `SelectAutoRing`: no expansion, natural hit count
                            self.params.auto = self.edit_sel == 0;
                            if self.params.auto {
                                self.params.reset_expansion();
                                self.params.hits = self.params.base_hits.clamp(1, 5);
                            }
                        }
                        _ => {}
                    }
                    env.sound(MenuSe::Decide);
                    self.save(env);
                    if self.menu_sel != 0 {
                        self.mode = Mode::Menu;
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
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
        let m = &self.scene.msd;
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let hi = Rgba::new(0x80, 0x80, 0x30, a);
        let blue = Rgba::new(0x70, 0xc0, 0xff, a);
        let pc = &self.pcs[self.pc];
        if let Some(card) = &self.card {
            let (cx, cy) = (10.0, 52.0);
            face_card_back(g, &self.sc.cmn, &card.msd, self.face, cx, cy, a);
            let t = |k: usize| card.msd.menu_text(k).map(|t| (t.x, t.y)).unwrap_or((0.0, 0.0));
            let (x, y) = t(4);
            text_run(g, cx + x, cy + y - 2.0, &pc.name, 0, white, Some((1, 0)));
            let (x, y) = t(0);
            self.sc.font_small.draw(g, cx + x, cy + y, "LEVEL", blue);
            let (x, y) = t(5);
            self.sc.font_big.draw(g, cx + x - 20.0, cy + y - 4.0, &format!("{:>2}", pc.level), white);
        }
        // command list (window 1 at (38, 225))
        let labels: Vec<String> = (0..5).map(|i| m.text(i).map(sj).unwrap_or_default()).collect();
        general_frame(g, &self.sc.cmn, 30.0, 215.0, 170.0, 120.0, a);
        for (i, l) in labels.iter().enumerate() {
            let y = 225.0 + i as f32 * 21.0;
            if i == self.menu_sel && self.mode == Mode::Menu {
                row_bar(g, 36.0, y - 1.0, 158.0, 20.0, a);
            }
            text_run(g, 44.0, y, l, 0, if i == self.menu_sel { white } else { Rgba::new(0x6c, 0x6c, 0x78, a) }, Some((1, 1)));
        }
        // detail panel (window 4 at (210, 128))
        general_frame(g, &self.sc.cmn, 206.0, 120.0, 290.0, 210.0, a);
        let (dx, dy) = (216.0, 128.0);
        let row_c = |i: usize| if self.mode == Mode::Edit && i == self.edit_sel { hi } else { white };
        match self.menu_sel {
            0 => {
                for k in 0..(self.params.hits as usize * 2) {
                    let (i, strike) = (k / 2, k % 2 == 1);
                    let y = dy + k as f32 * 19.0;
                    if self.mode == Mode::Edit && k == self.edit_sel {
                        row_bar(g, dx - 4.0, y - 1.0, 276.0, 18.0, a);
                    }
                    text_run(g, dx, y, &m.text(5 + k).map(sj).unwrap_or_default(), 14, row_c(k), Some((1, 1)));
                    let pts = if strike { self.params.strike[i] } else { self.params.zone[i] } as f32;
                    // bar: expansion points (the stock left is shown on the right)
                    let (bx, bw) = (dx + 150.0, 84.0);
                    fill(g, bx, y + 5.0, bw, 6.0, Rgba::new(0x30, 0x30, 0x48, a));
                    let unit = bw / rc::MAX_POINTS as f32;
                    fill(g, bx, y + 5.0, (pts * unit).max(1.0), 6.0, if strike { Rgba::new(0xf0, 0xa0, 0x30, a) } else { Rgba::new(0x60, 0xa0, 0xf0, a) });
                    text_run(g, bx + bw + 6.0, y, &format!("{}", pts as i32), 14, white, None);
                }
            }
            1 => text_run(g, dx, dy, &m.text(24).map(sj).unwrap_or_default(), 0, Rgba::new(0x70, 0x70, 0x78, a), None),
            2 => {
                for k in 0..5usize {
                    let y = dy + k as f32 * 21.0;
                    let cur = k + 1 == self.params.hits as usize;
                    if self.mode == Mode::Edit && k == self.edit_sel {
                        row_bar(g, dx - 4.0, y - 1.0, 276.0, 20.0, a);
                    }
                    text_run(g, dx, y, &m.text(15 + k).map(sj).unwrap_or_default(), 0, if cur { hi } else { row_c(k) }, Some((1, 1)));
                }
            }
            3 => {
                for (k, (name, _)) in self.ring_names.iter().enumerate() {
                    let y = dy + k as f32 * 21.0;
                    let cur = k == self.params.ring_type as usize;
                    if self.mode == Mode::Edit && k == self.edit_sel {
                        row_bar(g, dx - 4.0, y - 1.0, 276.0, 20.0, a);
                    }
                    text_run(g, dx, y, name, 0, if cur { hi } else { row_c(k) }, Some((1, 1)));
                }
            }
            _ => {
                for k in 0..2usize {
                    let y = dy + k as f32 * 21.0;
                    let cur = (k == 0) == self.params.auto;
                    if self.mode == Mode::Edit && k == self.edit_sel {
                        row_bar(g, dx - 4.0, y - 1.0, 276.0, 20.0, a);
                    }
                    text_run(g, dx, y, &m.text(20 + k).map(sj).unwrap_or_default(), 0, if cur { hi } else { row_c(k) }, Some((1, 1)));
                }
            }
        }
        if self.mode == Mode::Menu {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn points_become_the_jrcustom_table() {
        let mut st = RingState::default();
        st.zone[1] = 3;
        st.strike[0] = 2;
        let raw = st.jr_custom(&[]);
        let jr = sh2_gfx::effects::jring::JrCustom { raw };
        assert_eq!(jr.zone_delta(1), 6);
        assert_eq!(jr.strike_delta(0), 2);
        assert_eq!(jr.zone_delta(0), 0);
    }
}

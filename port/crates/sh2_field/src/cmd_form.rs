//! `CmdFormation` (page 8, "Battle members", JP 0x0047dd70): choose who fights.
//!
//! The party set of the `MENU` block (`PartySet`: `members[]`, `battle_count`) is the data: the first `battle_count` members enter
//! battles (`GameSession::battle_party`), the rest wait.  Selecting one member and then another swaps them in `members[]`.  Layout and
//! messages come from `MENU/MSD/FORM.MSD` (member rows at (134, 45), the team box at (0, 147), messages 6..11).

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 44.0;
const VISIBLE: usize = 4;

struct Row {
    /// index into `PartySet::members`
    idx: usize,
    pc: PcView,
    face: Option<TextureId>,
}

pub struct FormPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    rows: Vec<Row>,
    battle_count: usize,
    list: ListState,
    marked: Option<usize>,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    msg: Option<(String, f32)>,
    title_img: Option<(TextureId, (u32, u32))>,
}

impl FormPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/FORM.MSD")?;
        let w = scene.msd.window(0);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = FormPage {
            sc,
            scene,
            rows: Vec::new(),
            battle_count: 0,
            list: ListState::new(VISIBLE, 0),
            marked: None,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(300), (236.0, 180.0)),
            time: 0.0,
            msg: None,
            title_img,
        };
        p.refresh(env);
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn refresh(&mut self, env: &mut Env) {
        let set = env.session.save.menu.party_set(env.session.save.menu.current_set_index().min(4));
        let mut rows = Vec::new();
        if let Some(set) = &set {
            let all = party_view(env.session);
            for i in 0..(set.member_count.max(0) as usize).min(8) {
                if let Some(pc) = all.iter().find(|p| p.id == set.members[i]) {
                    let face = self.sc.top.t_by_id(pc.face as i16);
                    rows.push(Row { idx: i, pc: pc.clone(), face });
                }
            }
            // battle members are the first `battle_count` of the set (some leading entries may not exist yet)
            let nb = set.battle_count.max(0) as usize;
            self.battle_count = rows.iter().filter(|r| r.idx < nb).count();
        }
        self.rows = rows;
        self.list.set_len(self.rows.len());
    }

    fn row_origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((134.0, 45.0))
    }

    fn cursor_to_sel(&mut self) {
        let (x, y) = self.row_origin();
        self.cursor.set_target(x - 4.0, y + self.list.slot() as f32 * ROW_H + 20.0);
    }

    fn res(&self, i: usize) -> String {
        self.scene.msd.resource_bytes(i).map(sj).unwrap_or_default()
    }

    fn swap(&mut self, env: &mut Env, a: usize, b: usize) {
        let si = env.session.save.menu.current_set_index().min(4);
        let Some(mut set) = env.session.save.menu.party_set(si) else { return };
        let (ia, ib) = (self.rows[a].idx, self.rows[b].idx);
        set.members.swap(ia, ib);
        // at least one fighter must remain (the first member is always in the battle party)
        env.session.save.menu.set_party_set(si, &set);
        let name = self.rows[b].pc.name.clone();
        self.msg = Some((cfmt(&self.res(7), &[name.into()]), 2000.0));
        env.sound(MenuSe::Decide);
        self.refresh(env);
    }
}

impl Page for FormPage {
    fn page(&self) -> CmdPage {
        CmdPage::Formation
    }
    fn title(&self) -> usize {
        2
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        if let Some((m, _)) = &self.msg {
            return m.clone();
        }
        if self.marked.is_some() {
            self.res(9)
        } else {
            let who = self.rows.iter().take(self.battle_count).map(|r| r.pc.name.clone()).collect::<Vec<_>>().join("・");
            format!("{}\n{}", cfmt(&self.res(6), &[who.into()]), self.res(8))
        }
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "入れ替え".into()), (Button::Cross, "戻る".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        if let Some((_, t)) = self.msg.as_mut() {
            *t -= DT;
            if *t <= 0.0 {
                self.msg = None;
            }
        }
        if self.list.key(keys) {
            env.sound(MenuSe::CursorMove);
            self.cursor_to_sel();
        } else if keys & padbit::CIRCLE != 0 && !self.rows.is_empty() {
            match self.marked.take() {
                None => {
                    self.marked = Some(self.list.sel);
                    env.sound(MenuSe::Decide);
                }
                Some(a) if a == self.list.sel => env.sound(MenuSe::Cancel),
                Some(a) => self.swap(env, a, self.list.sel),
            }
        } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
            env.sound(MenuSe::Cancel);
            if self.marked.take().is_none() {
                return Flow::Back;
            }
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let m = &self.scene.msd;
        let Some(w) = m.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let blue = Rgba::new(0x70, 0xc0, 0xff, a);
        let font = &self.sc.font_small;
        let fp = |i: usize| m.font_pos(i).unwrap_or((0.0, 0.0));
        for (slot, row) in self.rows.iter().skip(self.list.top).take(VISIBLE).enumerate() {
            let i = self.list.top + slot;
            let (ox, oy) = (w.x + dx, w.y + dy + slot as f32 * ROW_H);
            let in_battle = i < self.battle_count;
            let marked = self.marked == Some(i);
            // row plate
            fill_v(g, ox, oy, 236.0, 38.0, Rgba::new(if marked { 0x60 } else { 0x28 }, if marked { 0x60 } else { 0x28 }, if marked { 0x20 } else { 0x30 }, (a as u32 * 0x70 / 0x80) as u8), Rgba::new(0x08, 0x08, 0x10, (a as u32 * 0x70 / 0x80) as u8));
            if let Some(r) = m.sprite(0) {
                blit(g, row.face, ox + r.x, oy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), white);
            }
            // battle member marker (the 36 x 48 slot figure, small)
            if in_battle {
                blit(g, m_tex(&self.scene, 1), ox - 20.0, oy + 4.0, 18.0, 24.0, (0.0, 0.0, 36.0, 48.0), white);
            }
            if let Some(t) = m.menu_text(0) {
                text_run(g, ox + t.x, oy + t.y - 2.0, &row.pc.name, 0, if self.list.sel == i { Rgba::new(0x80, 0x80, 0x30, a) } else { white }, Some((1, 1)));
            }
            let (x, y) = fp(0);
            font.draw(g, ox + x, oy + y, "LEVEL", blue);
            let (x, y) = fp(3);
            self.sc.font_big.draw(g, ox + x, oy + y - 4.0, &format!("{:>2}", row.pc.level), white);
            let vals = [(1usize, 4usize, "HP", row.pc.hp as i32, row.pc.hp_max as i32, 2usize), (2, 5, "MP", row.pc.mp as i32, row.pc.mp_max as i32, 3)];
            for (lab, val, label, cur, max, spr) in vals {
                let (x, y) = fp(lab);
                font.draw(g, ox + x, oy + y, label, blue);
                let (x, y) = fp(val);
                font.draw(g, ox + x, oy + y, &cfmt("%3d/%3d", &[cur.into(), max.into()]), white);
                if let (Some(back), Some(fill_r)) = (m.sprite(spr), m.sprite(spr + 2)) {
                    draw_sprite_rec(g, &back, self.sc.gauge, ox, oy, a);
                    let frac = if max > 0 { cur as f32 / max as f32 } else { 0.0 };
                    let wf = (fill_r.w * frac.clamp(0.0, 1.0)).round();
                    if wf > 0.0 {
                        blit(g, self.sc.gauge, ox + fill_r.x, oy + fill_r.y, wf, fill_r.h, (fill_r.u0 as f32, fill_r.v0 as f32, fill_r.u0 as f32 + wf, fill_r.v1 as f32), white);
                    }
                }
            }
        }
        draw_scroll_marks(g, w.x + 118.0, w.y - 4.0, w.y + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        // team box (window 1): the battle slots
        if let Some(tb) = m.window(1) {
            let (bx, by) = (tb.x + 10.0, tb.y + dy);
            panel(g, bx - 4.0, by - 4.0, 124.0, 86.0, a);
            for s in 0..3usize {
                let (sx, sy) = (bx + 4.0 + s as f32 * 38.0, by + 26.0);
                blit(g, m_tex(&self.scene, 1), sx, sy, 34.0, 46.0, (0.0, 0.0, 36.0, 48.0), Rgba::new(0x50, 0x50, 0x60, a));
                if let Some(r) = self.rows.iter().filter(|r| r.idx < self.rows.len() + 8).nth(s).filter(|_| s < self.battle_count) {
                    blit(g, r.face, sx + 1.0, sy + 4.0, 32.0, 32.0, (8.0, 2.0, 72.0, 34.0), white);
                }
            }
            text_run(g, bx, by - 20.0, &cfmt(&self.res(10), &[self.battle_count.into()]), 14, white, Some((1, 1)));
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

fn m_tex(scene: &SceneTex, i: usize) -> Option<TextureId> {
    scene.t(i)
}
